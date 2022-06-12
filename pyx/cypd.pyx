""" cypd.pyx

An cythoon extension class wrapping libpd in an 'object-orirented' way.


"""
cimport pd
cimport libpd
cimport libportaudio
from cpython cimport array

from libc.stdio cimport printf, fprintf, stderr, FILE
from posix.unistd cimport sleep

# from libc.string cimport strcpy, strlen
# from libc.stdlib cimport malloc



DEF N_TICKS = 1
DEF SAMPLE_RATE = 44100
DEF CHANNELS_IN = 1
DEF CHANNELS_OUT = 2
DEF BLOCKSIZE = 64
DEF IN_BUF = CHANNELS_IN * BLOCKSIZE
DEF OUT_BUF = CHANNELS_OUT * BLOCKSIZE
DEF PRERUN_SLEEP = 2000


cdef struct UserAudioData:
    # one input channel, two output channels
    double inbuf[N_TICKS * BLOCKSIZE * CHANNELS_IN]
    # block size 64, one tick per buffer
    double outbuf[N_TICKS * BLOCKSIZE * CHANNELS_OUT]
    # stereo outputs are interlaced, s[0] = RIGHT, s[1] = LEFT, etc..

# globals
cdef UserAudioData data



cdef int audio_callback(const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const libportaudio.PaStreamCallbackTimeInfo* timeInfo,
                        libportaudio.PaStreamCallbackFlags statusFlags,
                        void *userData ) nogil:
    """Called by the PortAudio engine when audio is needed.
    
    It may be called at interrupt level on some machines so don't do anything
    that could mess up the system like calling malloc() or free().
    """
    # Cast data passed through stream to our structure.
    cdef UserAudioData *data = <UserAudioData*>userData
    cdef float *out = <float*>outputBuffer
    cdef unsigned int i;
    
    libpd.libpd_process_double(N_TICKS, data.inbuf, data.outbuf)
    
    # dsp perform routine
    for i in range(framesPerBuffer * CHANNELS_OUT):
        if (i % 2):
            out[i] = data.outbuf[i]
        else:
            out[i] = data.outbuf[i]
    return 0


# use with libpd_printhook to print to console
cdef void pdprint(const char *s):
    printf("><> %s", s)



cdef class Patch:
    cdef readonly str name
    cdef readonly str dir
    cdef readonly int sample_rate
    cdef readonly int blocksize
    cdef readonly int ticks
    cdef readonly int in_channels
    cdef readonly int out_channels
    cdef void * handle
    cdef bint is_open

    def __cinit__(self, str name, str dir='.', 
            int sample_rate=SAMPLE_RATE, int ticks=N_TICKS, int blocksize=BLOCKSIZE,
            int in_channels=CHANNELS_IN, int out_channels=CHANNELS_OUT):
        # self.name = name.encode('UTF-8')
        # self.dir = dir.encode('UTF-8')
        self.name = name
        self.dir = dir
        self.blocksize = blocksize
        self.sample_rate = sample_rate
        self.ticks = ticks
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.handle = NULL
        self.is_open = False

    def play(self):

        print("portaudio version: ", libportaudio.Pa_GetVersion())
        print("pd version: ", self.pd_version())

        # init audio
        cdef libportaudio.PaStream *stream # opens the audio stream
        cdef libportaudio.PaError err
        
        # hooks
        self.set_printhook(pdprint)

        # init
        self.init()
        self.init_audio() #one channel in, one channel out


        ##---------------------------------------------------------------
        ## APP-SPECIFIC START 

        # open patch
        self.open()
        
        ## APP-SPECIFIC END         
        ##---------------------------------------------------------------

        # Initialize our data for use by callback.
        for i in range(self.blocksize):
            data.outbuf[i] = 0
        
        # Initialize library before making any other calls.
        err = libportaudio.Pa_Initialize()
        if err != libportaudio.paNoError:
            self.terminate(err, self.handle)

        # Open an audio I/O stream.
        err = libportaudio.Pa_OpenDefaultStream(
            &stream,
            self.in_channels,        # input channels
            self.out_channels,       # output channels
            libportaudio.paFloat32,  # 32 bit floating point output
            self.sample_rate,
            <long>self.blocksize,    # frames per buffer
            audio_callback,
            &data)
        if (err != libportaudio.paNoError):
            self.terminate(err, self.handle)

        err = libportaudio.Pa_StartStream(stream)
        if (err != libportaudio.paNoError):
            self.terminate(err, self.handle)

        libportaudio.Pa_Sleep(PRERUN_SLEEP)

        # -----------------------------------------------------------------
        # RUN HERE

        # self.run()
        self.dsp()
        sleep(4)
        self.dsp(0)


        # -----------------------------------------------------------------

        err = libportaudio.Pa_StopStream(stream)
        if err != libportaudio.paNoError:
            self.terminate(err, self.handle)

        err = libportaudio.Pa_CloseStream(stream)
        if err != libportaudio.paNoError:
            self.terminate(err, self.handle)

        libportaudio.Pa_Terminate()
        print(f"Ending Patch session: {err}")

        self.close()

        return err

    #-------------------------------------------------------------------------
    # Termination

    cdef terminate(self, libportaudio.PaError err, void *handle):
        libportaudio.Pa_Terminate()
        fprintf(stderr, "An error occured while using the portaudio stream\n")
        fprintf(stderr, "Error number: %d\n", err)
        fprintf(stderr, "Error message: %s\n", libportaudio.Pa_GetErrorText(err))
        libpd.libpd_closefile(handle)

    #-------------------------------------------------------------------------
    # Initialization


    def init(self) -> int:
        """initialize libpd

        It is safe to call this more than once
        returns 0 on success or -1 if libpd was already initialized
        note: sets SIGFPE handler to keep bad pd patches from crashing due to divide
        by 0, set any custom handling after calling this function
        """
        return libpd.libpd_init()

    def clear_search_path(self):
        """clear the libpd search path for abstractions and externals

        note: this is called by libpd_init()
        """
        libpd.libpd_clear_search_path()

    def add_to_search_path(self, path: str):
        """add a path to the libpd search paths

        relative paths are relative to the current working directory
        unlike desktop pd, *no* search paths are set by default (ie. extra)
        """
        libpd.libpd_add_to_search_path(path.encode('utf-8'))

    #-------------------------------------------------------------------------
    # Opening patches

    def open(self):
        """open a patch given filename and parent dir path

        Sets an opaque patch handle pointer to self.handle or
        or raise an IOError.
        """
        self.handle = libpd.libpd_openfile(
            self.name.encode('utf-8'), self.dir.encode('utf-8'))
        if self.handle:
            self.is_open = True
        else:
            raise IOError(f"could not open {self.name}/{self.dir}")

    def close(self):
        """close the open patch"""
        if self.is_open:
            libpd.libpd_closefile(self.handle)

    def getdollarzero(self) -> int:
        """get the $0 id of the patch handle pointer
        returns $0 value or 0 if the patch is non-existent
        """
        return libpd.libpd_getdollarzero(self.handle)

    #-------------------------------------------------------------------------
    # Audio processing

    def get_blocksize(self) -> int:
        """return pd's fixed block size

        the number of sample frames per 1 pd tick
        """
        return libpd.libpd_blocksize()


    def init_audio(self) -> int:
        """initialize audio rendering

        returns 0 on success
        """
        return libpd.libpd_init_audio(
            self.in_channels,
            self.out_channels,
            self.sample_rate)


    cdef int process_float(self, const int ticks, const float *in_buffer, float *out_buffer) nogil:
        """process interleaved float samples from in_buffer -> libpd -> out_buffer

        buffer sizes are based on # of ticks and channels where:
            size = ticks * libpd_blocksize() * (in/out)channels
        returns 0 on success
        """
        return libpd.libpd_process_float(ticks, in_buffer, out_buffer)


    cdef int process_short(self, const int ticks, const short *in_buffer, short *out_buffer) nogil:
        """process interleaved short samples from in_buffer -> libpd -> out_buffer

        buffer sizes are based on # of ticks and channels where:
            size = ticks * libpd_blocksize() * (in/out)channels
        float samples are converted to short by multiplying by 32767 and casting,
        so any values received from pd patches beyond -1 to 1 will result in garbage
        note: for efficiency, does *not* clip input
        returns 0 on success
        """
        return libpd.libpd_process_short(ticks, in_buffer, out_buffer)


    cdef int process_double(self, const int ticks, const double *in_buffer, double *out_buffer) nogil:
        """process interleaved double samples from in_buffer -> libpd -> out_buffer

        buffer sizes are based on # of ticks and channels where:
            size = ticks * libpd_blocksize() * (in/out)channels
        returns 0 on success
        """
        return libpd.libpd_process_double(ticks, in_buffer, out_buffer)


    cdef int process_raw(self, const float *in_buffer, float *out_buffer) nogil:
        """process non-interleaved float samples from in_buffer -> libpd -> out_buffer

        copies buffer contents to/from libpd without striping
        buffer sizes are based on a single tick and # of channels where:
            size = libpd_blocksize() * (in/out)channels
        returns 0 on success
        """
        return libpd.libpd_process_raw(in_buffer, out_buffer)


    cdef int process_raw_short(self, const short *in_buffer, short *out_buffer) nogil:
        """process non-interleaved short samples from in_buffer -> libpd -> out_buffer

        copies buffer contents to/from libpd without striping
        buffer sizes are based on a single tick and # of channels where:
            size = libpd_blocksize() * (in/out)channels
        float samples are converted to short by multiplying by 32767 and casting,
        so any values received from pd patches beyond -1 to 1 will result in garbage
        note: for efficiency, does *not* clip input
        returns 0 on success
        """
        return libpd.libpd_process_raw_short(in_buffer, out_buffer)


    cdef int process_raw_double(self, const double *in_buffer, double *out_buffer) nogil:
        """process non-interleaved double samples from in_buffer -> libpd -> out_buffer

        copies buffer contents to/from libpd without striping
        buffer sizes are based on a single tick and # of channels where:
            size = libpd_blocksize() * (in/out)channels
        returns 0 on success
        """
        return libpd.libpd_process_raw_double(in_buffer, out_buffer)


    #-------------------------------------------------------------------------
    # Array access

    def array_size(self, name: str) -> int:
        """get the size of an array by name

        returns size or negative error code if non-existent
        """
        return libpd.libpd_arraysize(name.encode('utf-8'))

    def resize_array(self, name: str, size: int) -> int:
        """(re)size an array by name sizes <= 0 are clipped to 1

        returns 0 on success or negative error code if non-existent
        """
        return libpd.libpd_resize_array(name.encode('utf-8'), <long>size)

    # TODO: add conversion to and from numpy arrays here
    cdef int read_array(self, float *dest, const char *name, int offset, int n):
        """read n values from named src array and write into dest starting at an offset

        note: performs no bounds checking on dest
        returns 0 on success or a negative error code if the array is non-existent
        or offset + n exceeds range of array
        """
        return libpd.libpd_read_array(dest, name, offset, n)

    cdef int write_array(self, const char *name, int offset, const float *src, int n):
        """read n values from src and write into named dest array starting at an offset

        note: performs no bounds checking on src
        returns 0 on success or a negative error code if the array is non-existent
        or offset + n exceeds range of array
        """
        return libpd.libpd_write_array(name, offset, src, n)

    #-------------------------------------------------------------------------
    # Sending messages to pd

    # TODO: is this two step necessary?
    def send_bang(self, receiver: str) -> int:
        """send a bang to a destination receiver

        ex: libpd_bang("foo") will send a bang to [s foo] on the next tick
        returns 0 on success or -1 if receiver name is non-existent
        """
        cdef bytes _recv = receiver.encode('utf-8')
        return libpd.libpd_bang(_recv)

    def send_float(self, receiver: str, f: float) -> int:
        """send a float to a destination receiver

        ex: libpd_float("foo", 1) will send a 1.0 to [s foo] on the next tick
        returns 0 on success or -1 if receiver name is non-existent
        """
        cdef bytes _recv = receiver.encode('utf-8')
        return libpd.libpd_float(_recv, f)

    def send_symbol(self, receiver: str, symbol: str) -> int:
        """send a symbol to a destination receiver

        ex: libpd_symbol("foo", "bar") will send "bar" to [s foo] on the next tick
        returns 0 on success or -1 if receiver name is non-existent
        """
        cdef bytes _recv = receiver.encode('utf-8')
        cdef bytes _symbol = symbol.encode('utf-8')
        return libpd.libpd_symbol(_recv, _symbol)

    #-------------------------------------------------------------------------
    # Sending compound messages: sequenced function calls

    def start_message(self, maxlen: int) -> int:
        """start composition of a new list or typed message of up to max element length

        messages can be of a smaller length as max length is only an upper bound
        note: no cleanup is required for unfinished messages
        returns 0 on success or nonzero if the length is too large
        """
        return libpd.libpd_start_message(maxlen)

    def add_float(self, x: float):
        """add a float to the current message in progress"""
        libpd.libpd_add_float(x)

    def add_symbol(self, symbol: str):
        """add a symbol to the current message in progress"""
        cdef bytes _symbol = symbol.encode('utf-8')
        libpd.libpd_add_symbol(_symbol)

    #-------------------------------------------------------------------------
    # Sending compound messages: atom array

    cdef void set_float(self, pd.t_atom *a, float x):
        """write a float value to the given atom"""
        libpd.libpd_set_float(a, x)

    cdef void set_symbol(self, pd.t_atom *a, const char *symbol):
        """write a symbol value to the given atom"""
        libpd.libpd_set_symbol(a, symbol)

    cdef int send_list(self, const char *recv, int argc, pd.t_atom *argv):
        """send an atom array of a given length as a list to a destination receiver

        returns 0 on success or -1 if receiver name is non-existent
        ex: send [list 1 2 bar( to [r foo] on the next tick with:
            t_atom v[3]
            libpd_set_float(v, 1)
            libpd_set_float(v + 1, 2)
            libpd_set_symbol(v + 2, "bar")
            libpd_list("foo", 3, v)
        """
        return libpd.libpd_list(recv, argc, argv)

    cdef int send_message(self, const char *recv, const char *msg, int argc, pd.t_atom *argv):
        """send an atom array of a given length as a typed message to a destination receiver

        returns 0 on success or -1 if receiver name is non-existent
        ex: send [ pd dsp 1( on the next tick with:
            t_atom v[1]
            libpd_set_float(v, 1)
            libpd_message("pd", "dsp", 1, v)
        """
        return libpd.libpd_message(recv, msg, argc, argv)

    cdef int finish_list(self, const char *recv):
        """finish current message and send as a list to a destination receiver

        returns 0 on success or -1 if receiver name is non-existent
        ex: send [list 1 2 bar( to [s foo] on the next tick with:
            libpd_start_message(3)
            libpd_add_float(1)
            libpd_add_float(2)
            libpd_add_symbol("bar")
            libpd_finish_list("foo")
        """
        return libpd.libpd_finish_list(recv)

    cdef int finish_message(self, const char *recv, const char *msg):
        """finish current message and send as a typed message to a destination receiver

        note: typed message handling currently only supports up to 4 elements
              internally, additional elements may be ignored
        returns 0 on success or -1 if receiver name is non-existent
        ex: send [ pd dsp 1( on the next tick with:
            libpd_start_message(1)
            libpd_add_float(1)
            libpd_finish_message("pd", "dsp")
        """
        return libpd.libpd_finish_message(recv, msg)

    #-------------------------------------------------------------------------
    # Convenience messages methods


    def dsp(self, on=True):
        """easy dsp switch"""
        if on:
            val = 1
        else:
            val = 0
        self.start_message(1)
        self.add_float(val)
        self.finish_message("pd", "dsp")

    #-------------------------------------------------------------------------
    # Receiving messages from pd

    cdef void *bind(self, const char *recv):
        """subscribe to messages sent to a source receiver

        ex: libpd_bind("foo") adds a "virtual" [r foo] which forwards messages to
            the libpd message hooks
        returns an opaque receiver pointer or NULL on failure
        """
        libpd.libpd_bind(recv)

    cdef void unbind(self, void *p):
        """unsubscribe and free a source receiver object created by libpd_bind()"""
        libpd.libpd_unbind(p)

    cdef int exists(self, const char *recv):
        """check if a source receiver object exists with a given name

        returns 1 if the receiver exists, otherwise 0
        """
        return libpd.libpd_exists(recv)

    cdef void set_printhook(self, const libpd.t_libpd_printhook hook):
        """set the print receiver hook, prints to stdout by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_printhook(hook)

    cdef void set_banghook(self, const libpd.t_libpd_banghook hook):
        """set the bang receiver hook, NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_banghook(hook)

    cdef void set_floathook(self, const libpd.t_libpd_floathook hook):
        """set the float receiver hook, NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_floathook(hook)

    cdef void set_symbolhook(self, const libpd.t_libpd_symbolhook hook):
        """set the symbol receiver hook, NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_symbolhook(hook)

    cdef void set_listhook(self, const libpd.t_libpd_listhook hook):
        """set the list receiver hook, NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_listhook(hook)

    cdef void set_messagehook(self, const libpd.t_libpd_messagehook hook):
        """set the message receiver hook, NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_messagehook(hook)

    cdef int is_float(self, pd.t_atom *a):
        """check if an atom is a float type: 0 or 1

        note: no NULL check is performed
        """
        return libpd.libpd_is_float(a)

    cdef int is_symbol(self, pd.t_atom *a):
        """check if an atom is a symbol type: 0 or 1

        note: no NULL check is performed
        """
        return libpd.libpd_is_symbol(a)

    cdef float get_float(self, pd.t_atom *a):
        """get the float value of an atom

        note: no NULL or type checks are performed
        """
        return libpd.libpd_get_float(a)

    cdef const char *get_symbol(self, pd.t_atom *a):
        """get symbol value of an atom

        note: no NULL or type checks are performed
        """
        return libpd.libpd_get_symbol(a)

    cdef pd.t_atom *next_atom(self, pd.t_atom *a):
        """increment to the next atom in an atom vector

        returns next atom or NULL, assuming the atom vector is NULL-terminated
        """
        return libpd.libpd_next_atom(a)

    #-------------------------------------------------------------------------
    # Sending MIDI messages to pd


    cdef int noteon(self, int channel, int pitch, int velocity):
        """send a MIDI note on message to [notein] objects

        channel is 0-indexed, pitch is 0-127, and velocity is 0-127
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        note: there is no note off message, send a note on with velocity = 0 instead
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_noteon(channel, pitch, velocity)

    cdef int controlchange(self, int channel, int controller, int value):
        """send a MIDI control change message to [ctlin] objects

        channel is 0-indexed, controller is 0-127, and value is 0-127
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_controlchange(channel, controller, value)

    cdef int programchange(self, int channel, int value):
        """send a MIDI program change message to [pgmin] objects

        channel is 0-indexed and value is 0-127
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_programchange(channel, value)

    cdef int pitchbend(self, int channel, int value):
        """send a MIDI pitch bend message to [bendin] objects

        channel is 0-indexed and value is -8192-8192
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        note: [bendin] outputs 0-16383 while [bendout] accepts -8192-8192
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_pitchbend(channel, value)

    cdef int aftertouch(self, int channel, int value):
        """send a MIDI after touch message to [touchin] objects

        channel is 0-indexed and value is 0-127
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_aftertouch(channel, value)

    cdef int polyaftertouch(self, int channel, int pitch, int value):
        """send a MIDI poly after touch message to [polytouchin] objects

        channel is 0-indexed, pitch is 0-127, and value is 0-127
        channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_polyaftertouch(channel, pitch, value)

    cdef int midibyte(self, int port, int byte):
        """send a raw MIDI byte to [midiin] objects

        port is 0-indexed and byte is 0-256
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_midibyte(port, byte)

    cdef int sysex(self, int port, int byte):
        """send a raw MIDI byte to [sysexin] objects

        port is 0-indexed and byte is 0-256
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_sysex(port, byte)

    cdef int sysrealtime(self, int port, int byte):
        """send a raw MIDI byte to [realtimein] objects

        port is 0-indexed and byte is 0-256
        returns 0 on success or -1 if an argument is out of range
        """
        return libpd.libpd_sysrealtime(port, byte)


    #-------------------------------------------------------------------------
    # Receiving MIDI messages from pd

    cdef void set_noteonhook(self, const libpd.t_libpd_noteonhook hook):
        """set the MIDI note on hook to receive from [noteout] objects, 
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_noteonhook(hook)

    cdef void set_controlchangehook(self, const libpd.t_libpd_controlchangehook hook):
        """set the MIDI control change hook to receive from [ctlout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_controlchangehook(hook)

    cdef void set_programchangehook(self, const libpd.t_libpd_programchangehook hook):
        """set the MIDI program change hook to receive from [pgmout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_programchangehook(hook)

    cdef void set_pitchbendhook(self, const libpd.t_libpd_pitchbendhook hook):
        """set the MIDI pitch bend hook to receive from [bendout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_pitchbendhook(hook)

    cdef void set_aftertouchhook(self, const libpd.t_libpd_aftertouchhook hook):
        """set the MIDI after touch hook to receive from [touchout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_aftertouchhook(hook)

    cdef void set_polyaftertouchhook(self, const libpd.t_libpd_polyaftertouchhook hook):
        """set the MIDI poly after touch hook to receive from [polytouchout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_polyaftertouchhook(hook)

    cdef void set_midibytehook(self, const libpd.t_libpd_midibytehook hook):
        """set the raw MIDI byte hook to receive from [midiout] objects,
        NULL by default

        note: do not call this while DSP is running
        """
        libpd.libpd_set_midibytehook(hook)

    #-------------------------------------------------------------------------
    # Gui

    def start_gui(self, str path):
        """open the current patches within a pd vanilla GUI

        requires the path to pd's main folder that contains bin/, tcl/, etc
        for a macOS .app bundle: /path/to/Pd-#.#-#.app/Contents/Resources
        returns 0 on success
        """
        return libpd.libpd_start_gui(path.encode('utf8'))

    # cdef int start_gui(self, char *path):
    #     """open the current patches within a pd vanilla GUI

    #     requires the path to pd's main folder that contains bin/, tcl/, etc
    #     for a macOS .app bundle: /path/to/Pd-#.#-#.app/Contents/Resources
    #     returns 0 on success
    #     """
    #     return libpd.libpd_start_gui(path)

    cdef void stop_gui(self):
        """stop the pd vanilla GUI"""

        libpd.libpd_stop_gui()

    cdef void poll_gui(self):
        """manually update and handle any GUI messages

        this is called automatically when using a libpd_process function,
        note: this also facilitates network message processing, etc so it can be
        useful to call repeatedly when idle for more throughput
        """
        libpd.libpd_poll_gui()


    #-------------------------------------------------------------------------
    # Multiple instances

    cdef pd.t_pdinstance *new_instance(self):
        """create a new pd instance

        returns new instance or NULL when libpd is not compiled with PDINSTANCE
        """
        return libpd.libpd_new_instance()

    cdef void set_instance(self, pd.t_pdinstance *p):
        """set the current pd instance

        subsequent libpd calls will affect this instance only
        does nothing when libpd is not compiled with PDINSTANCE
        """
        libpd.libpd_set_instance(p)

    cdef void free_instance(self, pd.t_pdinstance *p):
        """free a pd instance

        does nothing when libpd is not compiled with PDINSTANCE
        """
        libpd.libpd_free_instance(p)

    cdef pd.t_pdinstance *this_instance(self):
        """get the current pd instance"""

        return libpd.libpd_this_instance()

    cdef pd.t_pdinstance *get_instance(self, int index):
        """get a pd instance by index

        returns NULL if index is out of bounds or "this" instance when libpd is not
        compiled with PDINSTANCE
        """
        return libpd.libpd_get_instance(index)

    cdef int num_instances(self):
        """get the number of pd instances

        returns number or 1 when libpd is not compiled with PDINSTANCE
        """
        return libpd.libpd_num_instances()


    #-------------------------------------------------------------------------
    # Log level


    cdef int get_verbose(self):
        """get verbose print state: 0 or 1"""

        return libpd.libpd_get_verbose()


    cdef void set_verbose(self, int verbose):
        """set verbose print state: 0 or 1"""

        libpd.libpd_set_verbose(verbose)


    def pd_version(self) -> str:
        """returns pd version"""
        cdef int major, minor, bugfix
        pd.sys_getversion(&major, &minor, &bugfix)
        return f'{major}.{minor}.{bugfix}'


