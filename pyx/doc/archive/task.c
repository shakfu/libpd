#include "task.h"

#define SAMPLE_RATE 44100
#define N_TICKS 1
#define CHANNELS_IN 0
#define CHANNELS_OUT 2
#define BLOCKSIZE 64
#define IN_BUF (N_TICKS * CHANNELS_IN * BLOCKSIZE)
#define OUT_BUF (N_TICKS * CHANNELS_OUT * BLOCKSIZE)
#define PRERUN_SLEEP 2000

typedef struct {
    double inbuf[IN_BUF];
    double outbuf[OUT_BUF];
} UserAudioData;


static UserAudioData data;


static int audio_callback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags, void* userData)
{
    /* Cast data passed through stream to our structure. */
    UserAudioData* data = (UserAudioData*)userData;
    float* out = (float*)outputBuffer;
    unsigned int i;

    (void)inputBuffer; /* Prevent unused variable warning. */

    /*
    If this is not exactly called here, either no audio
    or audio becomes higher pitched
    */
    libpd_process_double(1, data->inbuf, data->outbuf);

    // dsp perform routine
    for (i = 0; i < framesPerBuffer * CHANNELS_OUT; i++) {
        if (i % 2)
            *out++ = data->outbuf[i];
        // right channel
        else
            *out++ = data->outbuf[i];
        // left channel
    }

    return 0;
}


void print_callback(const char* s)
{
    printf(">>> %s", s);
}


void dsp_switch(int cmd)
{
    libpd_start_message(1);
    libpd_add_float(cmd);
    libpd_finish_message("pd", "dsp");
}

void terminate(void* handle, int err)
{
    Pa_Terminate();
    fprintf(stderr, "An error occured while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", err);
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
    libpd_closefile(handle);
}

int cplay(char* name, char* dir, int sample_rate, int blocksize,
               int in_channels, int out_channels)
{

    PaStream *stream; // opens the audio stream
    PaError err;

    printf("portaudio version: %i", Pa_GetVersion());

    // set callbacks
    libpd_set_printhook(print_callback);

    void* handle = libpd_openfile(name, dir);
    
    // init
    libpd_init();
    libpd_init_audio(in_channels, out_channels, sample_rate);


    //---------------------------------------------------------------
    // APP-SPECIFIC START 

    // open patch
    handle = libpd_openfile(name, dir);

    // APP-SPECIFIC END         
    //---------------------------------------------------------------

    // Initialize our data for use by callback.
    for (int i =0; i < blocksize; i++) {
        data.outbuf[i] = 0;
    }

    // Initialize library before making any other calls.
    err = Pa_Initialize();
    if (err != paNoError)
        terminate(handle, err);


    // Open an audio I/O stream.
    err = Pa_OpenDefaultStream(
        &stream,
        in_channels,        // input channels
        out_channels,       // output channels
        paFloat32,  /       // 32 bit floating point output
        sample_rate,
        blocksize,          // frames per buffer
        audio_callback,
        &data);
    if (err != paNoError)
        terminate(handle, err);


    err = Pa_StartStream(stream);
    if (err != paNoError)
        terminate(handle, err);


    Pa_Sleep(PRERUN_SLEEP);

    // -----------------------------------------------------------------
    // RUN HERE

    // start
    dsp_switch(1);

    // CONTROL HERE!!!
    sleep(4);

    // stop
    dsp_switch(0);

    // -----------------------------------------------------------------

    err = Pa_StopStream(stream);
    if (err != paNoError)
        terminate(handle, err);

    err = Pa_CloseStream(stream);
    if (err != paNoError)
        terminate(handle, err);

    Pa_Terminate();
    printf("Ending Patch session: %i", err);

    libpd_closefile(handle);

    return err;
}
