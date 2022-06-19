"""
a translation of the cpp implementation to cython
"""

#include "z_libpd.h"
#include "z_queued.h"
#include "z_print_util.h"

#include "PdTypes.hpp"
#include "PdReceiver.hpp"
#include "PdMidiReceiver.hpp"

# needed for libpd audio passing
#ifndef USEAPI_DUMMY
    #define USEAPI_DUMMY
#endif

#ifndef HAVE_UNISTD_H
    #define HAVE_UNISTD_H
#endif

ctypedef struct _atom t_atom




cdef class PdBase:
    """a Pure Data instance

    use this class directly or extend it and any of its virtual functions

    note: libpd currently does not support multiple states and it is
          suggested that you use only one PdBase-derived object at a time

          calls from multiple PdBase instances currently use a global context
          kept in a singleton object, thus only one Receiver & one MidiReceiver
          can be used within a single program

          multiple context support will be added if/when it is included within
          libpd

    """
    def __cinit__(self):
        self.clear()
        PdContext.instance().addBase()

    def __dealloc__(self):
        self.clear()
        PdContext.instance().removeBase()

# ----------------------------------------------------------------------------
# Initializing Pd


    def init(self, num_in_channels: int, num_out_channels: int,
             sample_rate: int, queued: bool = False) -> bool:
        """initialize resources and set up the audio processing

        set the audio latency by setting the libpd ticks per buffer:
        ticks per buffer * lib pd block size (always 64)

        ie 4 ticks per buffer * 64 = buffer len of 512

        you can call this again after loading patches & setting receivers
        in order to update the audio settings

        the lower the number of ticks, the faster the audio processing
        if you experience audio dropouts (audible clicks), increase the
        ticks per buffer

        set queued = true to use the built in ringbuffers for message and
        midi event passing, you will then need to call receive_messages() and
        receive_midi() in order to pass messages from the ringbuffers to your
        PdReceiver and PdMidiReceiver implementations

        the queued ringbuffers are useful when you need to receive events
        on a gui thread and don't want to use locking

        return true if setup successfully

        note: must be called before processing
        """
        PdContext.instance().clear()
        return PdContext.instance().init(num_in_channels, num_out_channels,
                                          sample_rate, queued)


    def clear(self):
        """clear resources"""
        PdContext.instance().clear()
        unsubscribe_all()

# ----------------------------------------------------------------------------
# Adding Search Paths

    def add_to_search_path(self, path: str):
        """
        Adds to the pd search path.

        takes an absolute or relative path (in data folder)
        note: fails silently if path not found
        
        :param      path:  The path
        :type       path:  str
        """
        libpd.libpd_add_to_search_path(path.encode('utf-8'))


    def clear_search_path(self):
        """clear the current pd search path."""
        libpd.libpd_clear_search_path()


# \section Opening Patches


    def open_patch(str patch, str path) -> Patch:
        """open a patch file (aka somefile.pd) at a specified parent dir path
        
        returns a Patch object

        use Patch::isValid() to check if a patch was opened successfully:

        Patch p1 = pd.open_patch("somefile.pd", "/some/dir/path/")
        if(!p1.isValid()):
            cout << "aww ... p1 couldn't be opened" << std::endl
        """
        # [ pd open file folder(
        cdef void *handle = libpd.libpd_openfile(patch.encode('utf-8'), path.encode('utf-8'))
        if(handle == NULL):
            return Patch() # return empty Patch
    
        cdef int dollarzero = libpd.libpd_getdollarzero(handle)
        return Patch(handle, dollarzero, patch, path)


    def open_patch(self, patch: Patch) -> Patch:
        """open a patch file using the filename and path of an existing patch

        set the filename within the patch object or use a previously opened
        object

        # open an instance of "somefile.pd"
        Patch p2("somefile.pd", "/some/path") # set file and path
        pd.open_patch(p2)
        
        # open a new instance of "somefile.pd"
        Patch p3 = pd.open_patch(p2)
        
        # p2 and p3 refer to 2 different instances of "somefile.pd"
        """
        return open_patch(patch.filename(), patch.path())


    def void close_patch(self, patch: str):
        """close a patch file
            
        takes only the patch's basename (filename without extension)
        """
        # [ pd-name menuclose 1(
        str patchname = (str)"pd-" + patch
        libpd.libpd_start_message(1)
        libpd.libpd_add_float(1)
        libpd.libpd_finish_message(patchname.encode('utf-8'), "menuclose")


    def close_patch(self, patch: Patch):
        """close a patch file, takes a patch object
        
        note: clears the given Patch object
        """
        if(!patch.isValid()):
            return
    
        libpd.libpd_closefile(patch.handle())
        patch.clear()


# ----------------------------------------------------------------------------
# Audio Processing

# one of these must be called for audio dsp and message io to occur
#
# in_buffer must be an array of the right size and never null
# use in_buffer = new type[0] if no input is desired
#
# out_buffer must be an array of size outBufferSize from openAudio call
#
# note: raw does not interlace the buffers
#


    cdef bint process_float(self, int ticks, const float *in_buffer, float *out_buffer) nogil:
        """process float buffers for a given number of ticks
        
        returns false on error
        """
        return libpd.libpd_process_float(ticks, in_buffer, out_buffer) == 0


    cdef bint process_short(self, int ticks, const short *in_buffer, short *out_buffer) nogil:
        """process short buffers for a given number of ticks
        
        returns false on error
        """
        return libpd.libpd_process_short(ticks, in_buffer, out_buffer) == 0


    cdef bint process_double(self, int ticks, const double *in_buffer, double *out_buffer) nogil:
        """process double buffers for a given number of ticks
        
        returns false on error
        """
        return libpd.libpd_process_double(ticks, in_buffer, out_buffer) == 0


    cdef bint process_raw(self, float *in_buffer, float *out_buffer) nogil:
        """process one pd tick, writes raw float data to/from buffers
        
        returns false on error
        """
        return libpd.libpd_process_raw(in_buffer, out_buffer) == 0


    cdef bint process_raw_short(self, short *in_buffer, short *out_buffer) nogil:
        """process one pd tick, writes raw short data to/from buffers
        
        returns false on error
        """
        return libpd.libpd_process_raw_short(in_buffer, out_buffer) == 0


    cdef bint process_raw_double(self, double *in_buffer, double *out_buffer) nogil:
        """process one pd tick, writes raw double data to/from buffers
        
        returns false on error
        """
        return libpd.libpd_process_raw_double(in_buffer, out_buffer) == 0

# ----------------------------------------------------------------------------
# Audio Processing Control

    # start/stop audio processing
    #
    # in general, once started, you won't need to turn off audio
    #
    # shortcut for [ pd dsp 1( & [ pd dsp 0(
    #
    def compute_audio(self, state: bool):
        PdContext.instance().compute_audio(state)

# ----------------------------------------------------------------------------
# Message Receiving


    # subscribe to messages sent by a pd send source
    #
    # aka this like a virtual pd receive object
    #
    #     [r source]
    #     |
    #
    def subscribe(self, source: str):
        if(exists(source)):
            std::cerr << "Pd: unsubscribe: ignoring duplicate source"
                      << std::endl
            return
    
        void *pointer = libpd.libpd_bind(source.encode('utf-8'))
        if(pointer != NULL):
            std::map<str,void*> &sources =
                PdContext.instance().sources
            sources.insert(std::pair<str,void*>(source, pointer))
    


    # unsubscribe from messages sent by a pd send source
    def unsubscribe(self, source: str):
        std::map<str,void*> &sources = PdContext.instance().sources
        std::map<str,void*>::iterator iter
        iter = sources.find(source)
        if(iter == sources.end()):
            std::cerr << "Pd: unsubscribe: ignoring unknown source"
                      << std::endl
            return
    
        libpd.libpd_unbind(iter->second)
        sources.erase(iter)


    # is a pd send source subscribed?
    def exists(self, source: str) -> bool:
        std::map<str,void*> &sources = PdContext.instance().sources
        if(sources.find(source) != sources.end()):
            return true
    
        return false


    #/ receivers will be unsubscribed from *all* pd send sources
    def unsubscribe_all(self):
        std::map<str,void*> &sources = PdContext.instance().sources
        std::map<str,void*>::iterator iter
        for(iter = sources.begin() iter != sources.end() ++iter):
            libpd.libpd_unbind(iter->second)
    
        sources.clear()


# ----------------------------------------------------------------------------
# Receiving from the Message Queues

# process the internal message queue if using the ringbuffer
#
# internally, libpd will use a ringbuffer to pass messages & midi without
# needing to require locking if you call init() with queued = true
#
# call these in a loop somewhere in order to receive waiting messages
# or midi data which are then sent to your PdReceiver & PdMidiReceiver
#

    # process waiting messages
    def receive_messages(self):
        libpd.libpd_queued_receive_pd_messages()


    # process waiting midi messages
    def receive_midi(self):
        libpd.libpd_queued_receive_midi_messages()

# ----------------------------------------------------------------------------
# Event Receiving via Callbacks

    # set the incoming event receiver, disables the event queue
    #
    # automatically receives from all currently subscribed sources
    #
    # set this to NULL to disable callback receiving and re-enable the
    # event queue
    #
    void set_receiver(pd::PdReceiver *receiver):
        PdContext.instance().receiver = receiver

# ----------------------------------------------------------------------------
# Midi Receiving via Callbacks

    # set the incoming midi event receiver, disables the midi queue
    #
    # automatically receives from all midi channels
    #
    # set this to NULL to disable midi events and re-enable the midi queue
    #
    void set_midi_receiver(pd::PdMidiReceiver *midi_receiver):
        PdContext.instance().midi_receiver = midi_receiver

# ----------------------------------------------------------------------------
# Send Functions

    # send a bang message
    def send_bang(str &dest):
        libpd.libpd_bang(dest.encode('utf-8'))


    # send a float
    def send_float(str &dest, float value):
        libpd.libpd_float(dest.encode('utf-8'), value)


    # send a symbol
    def sendSymbol(str &dest,
                            str &symbol):
        libpd.libpd_symbol(dest.encode('utf-8'), symbol.encode('utf-8'))

# ----------------------------------------------------------------------------
# Sending Compound Messages
#
#     pd.start_message()
#     pd.add_symbol("hello")
#     pd.add_float(1.23)
#     pd.finish_list("test") # "test" is the receiver name in pd
#
# sends [list hello 1.23( -> [r test],
# you will need to use the [list trim] object on the receiving end
#
# finishMsg sends a typed message -> [ test msg1 hello 1.23(
#
#     pd.start_message()
#     pd.add_symbol("hello")
#     pd.add_float(1.23)
#     pd.finish_message("test", "msg1")
#

    # start a compound list or message
    def start_message(self):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot start message, message in progress"
                      << std::endl
            return
    
        if(libpd.libpd_start_message(context.maxMsgLen) == 0):
            context.bMsgInProgress = true
            context.msgType = MSG
    


    # add a float to the current compound list or message
    def add_float(self, float num):
        PdContext &context = PdContext.instance()
        if(!context.bMsgInProgress):
            std::cerr << "Pd: cannot add float, message not in progress"
                      << std::endl
            return
    
        if(context.msgType != MSG):
            std::cerr << "Pd: cannot add float, midi byte stream in progress"
                      << std::endl
            return
    
        if(context.curMsgLen+1 >= context.maxMsgLen):
            std::cerr << "Pd: cannot add float, max message len of "
                      << context.maxMsgLen << " reached" << std::endl
            return
    
        libpd.libpd_add_float(num)
        context.curMsgLen++


    # add a symbol to the current compound list or message
    def add_symbol(self, str &symbol):
        PdContext &context = PdContext.instance()
        if(!context.bMsgInProgress):
            std::cerr << "Pd: cannot add symbol, message not in progress"
                      << std::endl
            return
    
        if(context.msgType != MSG):
            std::cerr << "Pd: cannot add symbol, midi byte stream in progress"
                      << std::endl
            return
    
        if(context.curMsgLen+1 >= context.maxMsgLen):
            std::cerr << "Pd: cannot add symbol, max message len of "
                      << context.maxMsgLen << " reached" << std::endl
            return
    
        libpd.libpd_add_symbol(symbol.encode('utf-8'))
        context.curMsgLen++


    # finish and send as a list
    def finish_list(self, str &dest):
        PdContext &context = PdContext.instance()
        if(!context.bMsgInProgress):
            std::cerr << "Pd: cannot finish list, "
                      << "message not in progress" << std::endl
            return
    
        if(context.msgType != MSG):
            std::cerr << "Pd: cannot finish list, "
                      << "midi byte stream in progress" << std::endl
            return
    
        libpd.libpd_finish_list(dest.encode('utf-8'))
        context.bMsgInProgress = false
        context.curMsgLen = 0


    # finish and send as a list with a specific message name
    def finish_message(self, str &dest, str &msg):
        PdContext &context = PdContext.instance()
        if(!context.bMsgInProgress):
            std::cerr << "Pd: cannot finish message, "
                      << "message not in progress" << std::endl
            return
    
        if(context.msgType != MSG):
            std::cerr << "Pd: cannot finish message, "
                      << "midi byte stream in progress" << std::endl
            return
    
        libpd.libpd_finish_message(dest.encode('utf-8'), msg.encode('utf-8'))
        context.bMsgInProgress = false
        context.curMsgLen = 0


    # send a list using the PdBase List type
    #
    #     List list
    #     list.add_symbol("hello")
    #     list.add_float(1.23)
    #     pd.sstd::endlist("test", list)
    #
    # sends [list hello 1.23( -> [r test]
    #
    # stream operators work as well:
    #
    #     list << "hello" << 1.23
    #     pd.sstd::endlist("test", list)
    #
    def send_list(self, str &dest, const pd::List &list):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot send list, message in progress"
                      << std::endl
            return
    
        libpd.libpd_start_message(list.len())
        context.bMsgInProgress = true
        # step through list
        for(int i = 0 i < (int)list.len() ++i):
            if(list.isFloat(i))
                add_float(list.getFloat(i))
            else if(list.isSymbol(i))
                add_symbol(list.getSymbol(i))
    
        finish_list(dest)


    # send a message using the PdBase List type
    #
    #     pd::List list
    #     list.add_symbol("hello")
    #     list.add_float(1.23)
    #     pd.send_message("test", "msg1", list)
    #
    # sends a typed message -> [ test msg1 hello 1.23(
    #
    # stream operators work as well:
    #
    #      list << "hello" << 1.23
    #     pd.send_message("test", "msg1", list)
    #
    def send_message(self, str dest, str msg, pd::List &list = pd::List()):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot send message, message in progress"
                      << std::endl
            return
    
        libpd.libpd_start_message(list.len())
        context.bMsgInProgress = true
        # step through list
        for(int i = 0 i < (int)list.len() ++i):
            if(list.isFloat(i))
                add_float(list.getFloat(i))
            else if(list.isSymbol(i))
                add_symbol(list.getSymbol(i))
    
        finish_message(dest, msg)


# ----------------------------------------------------------------------------
# Sending MIDI
#
# any out of range messages will be silently ignored
#
# number ranges:
# * channel             0 - 15 * dev# (dev #0: 0-15, dev #1: 16-31, etc)
# * pitch               0 - 127
# * velocity            0 - 127
# * controller value    0 - 127
# * program value       0 - 127
# * bend value          -8192 - 8191
# * touch value         0 - 127
#

    # send a MIDI note on
    #
    # pd does not use note off MIDI messages, so send a note on with vel = 0
    #
    def send_noteon(self, int channel, int pitch, int velocity=64):
        libpd.libpd_noteon(channel, pitch, velocity)


    # send a MIDI control change
    def send_controlchange(int channel, int controller, int value):
        libpd.libpd_controlchange(channel, controller, value)


    # send a MIDI program change
    def send_programchange(int channel, int value):
        libpd.libpd_programchange(channel, value)


    # send a MIDI pitch bend
    #
    # in pd: [bendin] takes 0 - 16383 while [bendout] returns -8192 - 8192
    #
    def send_pitchbend(int channel, int value):
        libpd.libpd_pitchbend(channel, value)


    # send a MIDI aftertouch
    def send_aftertouch(int channel, int value):
        libpd.libpd_aftertouch(channel, value)


    # send a MIDI poly aftertouch
    def send_polyaftertouch(int channel, int pitch, int value):
        libpd.libpd_polyaftertouch(channel, pitch, value)


    # send a raw MIDI byte
    #
    # value is a raw midi byte value 0 - 255
    # port is the raw portmidi port #, similar to a channel
    #
    # for some reason, [midiin], [sysexin] & [realtimein] add 2 to the
    # port num, so sending to port 1 in PdBase returns port 3 in pd
    #
    # however, [midiout], [sysexout], & [realtimeout] do not add to the
    # port num, so sending port 1 to [midiout] returns port 1 in PdBase
    #
    virtual void send_midibyte(const int port, const int value):
        libpd.libpd_midibyte(port, value)


    # send a raw MIDI sysex byte
    virtual void send_sysex(const int port, const int value):
        libpd.libpd_sysex(port, value)


    # send a raw MIDI realtime byte
    virtual void send_sysrealtime(const int port, const int value):
        libpd.libpd_sysrealtime(port, value)

# ----------------------------------------------------------------------------
# Stream Interface

# single messages
#
#     pd << Bang("test") # "test" is the receiver name in pd
#     pd << Float("test", 100)
#     pd << Symbol("test", "a symbol")
#

    # send a bang message
    PdBase& operator<<(const pd::Bang &var):
        if(PdContext.instance().bMsgInProgress):
            std::cerr << "Pd: cannot send Bang, message in progress"
                      << std::endl
            return *this
    
        send_bang(var.dest.encode('utf-8'))
        return *this


    # send a float message
    PdBase& operator<<(const pd::Float &var):
        if(PdContext.instance().bMsgInProgress):
            std::cerr << "Pd: cannot send Float, message in progress"
                      << std::endl
            return *this
    
        send_float(var.dest.encode('utf-8'), var.num)
        return *this


    # send a symbol message
    PdBase& operator<<(const pd::Symbol &var):
        if(PdContext.instance().bMsgInProgress):
            std::cerr << "Pd: cannot send Symbol, message in progress"
                      << std::endl
            return *this
    
        sendSymbol(var.dest.encode('utf-8'), var.symbol.encode('utf-8'))
        return *this

# ----------------------------------------------------------------------------
# Stream Interface for Compound Messages

# pd << StartMessage() << 100 << 1.2 << "a symbol" << FinishList("test")
#

    # start a compound message
    PdBase& operator<<(const pd::StartMessage &var):
        start_message()
        return *this


    # finish a compound message and send it as a list
    PdBase& operator<<(const pd::FinishList &var):
        finish_list(var.dest)
        return *this


    # finish a compound message and send it as a message
    PdBase& operator<<(const pd::FinishMessage &var):
        finish_message(var.dest, var.msg)
        return *this


    # add a boolean as a float to the compound message
    PdBase& operator<<(const bool var):
        add_float((float) var)
        return *this


    # add an integer as a float to the compound message
    PdBase& operator<<(const int var):
        PdContext &context = PdContext.instance()
        switch(context.msgType):
            case MSG:
                add_float((float) var)
                break
            case MIDI:
                send_midibyte(context.midiPort, var)
                break
            case SYSEX:
                send_sysex(context.midiPort, var)
                break
            case SYSRT:
                send_sysrealtime(context.midiPort, var)
                break
    
        return *this


    # add a float to the compound message
    PdBase& operator<<(const float var):
        add_float((float) var)
        return *this


    # add a double as a float to the compound message
    PdBase& operator<<(const double var):
        add_float((float) var)
        return *this


    # add a character as a symbol to the compound message
    PdBase& operator<<(const char var):
        str s
        s = var
        add_symbol(s)
        return *this


    # add a C-string char buffer as a symbol to the compound message
    PdBase& operator<<(const char *var):
        add_symbol((str)var)
        return *this


    # add a string as a symbol to the compound message
    PdBase& operator<<(str &var):
        add_symbol(var)
        return *this

# ----------------------------------------------------------------------------
# Stream Interface for MIDI

# pd << NoteOn(64) << NoteOn(64, 60) << NoteOn(64, 60, 1)
# pd << ControlChange(100, 64) << ProgramChange(100, 1)
# pd << Aftertouch(127, 1) << PolyAftertouch(64, 127, 1)
# pd << PitchBend(2000, 1)
#

    # send a MIDI note on
    PdBase& operator<<(const pd::NoteOn &var):
        send_noteon(var.channel, var.pitch, var.velocity)
        return *this


    # send a MIDI control change
    PdBase& operator<<(const pd::ControlChange &var):
        send_controlchange(var.channel, var.controller, var.value)
        return *this


    # send a MIDI program change
    PdBase& operator<<(const pd::ProgramChange &var):
        send_programchange(var.channel, var.value)
        return *this


    # send a MIDI pitch bend
    PdBase& operator<<(const pd::PitchBend &var):
        send_pitchbend(var.channel, var.value)
        return *this


    # send a MIDI aftertouch
    PdBase& operator<<(const pd::Aftertouch &var):
        send_aftertouch(var.channel, var.value)
        return *this


    # send a MIDI poly aftertouch
    PdBase& operator<<(const pd::PolyAftertouch &var):
        send_polyaftertouch(var.channel, var.pitch, var.value)
        return *this

# ----------------------------------------------------------------------------
# Stream Interface for Raw Bytes

# pd << StartMidi() << 0xEF << 0x45 << Finish()
# pd << StartSysex() << 0xE7 << 0x45 << 0x56 << 0x17 << Finish()
#

    # start a raw byte MIDI message
    PdBase& operator<<(const pd::StartMidi &var):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot start MidiByte stream, "
                      << "message in progress" << std::endl
            return *this
    
        context.bMsgInProgress = true
        context.msgType = MIDI
        context.midiPort = var.port
        return *this


    # start a raw byte MIDI sysex message
    PdBase& operator<<(const pd::StartSysex &var):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot start Sysex stream, "
                      << "message in progress" << std::endl
            return *this
    
        context.bMsgInProgress = true
        context.msgType = SYSEX
        context.midiPort = var.port
        return *this


    # start a raw byte MIDI realtime message
    PdBase& operator<<(const pd::StartSysRealTime &var):
        PdContext &context = PdContext.instance()
        if(context.bMsgInProgress):
            std::cerr << "Pd: cannot start SysRealRime stream, "
                      << "message in progress" << std::endl
            return *this
    
        context.bMsgInProgress = true
        context.msgType = SYSRT
        context.midiPort = var.port
        return *this


    # finish and send a raw byte MIDI message
    PdBase& operator<<(const pd::Finish &var):
        PdContext &context = PdContext.instance()
        if(!context.bMsgInProgress):
            std::cerr << "Pd: cannot finish midi byte stream, "
                      << "stream not in progress" << std::endl
            return *this
    
        if(context.msgType == MSG):
            std::cerr << "Pd: cannot finish midi byte stream, "
                      << "message in progress" << std::endl
            return *this
    
        context.bMsgInProgress = false
        context.curMsgLen = 0
        return *this


    # is a message or byte stream currently in progress?
    bool isMessageInProgress():
        return PdContext.instance().bMsgInProgress

# ----------------------------------------------------------------------------
# Array Access

    # get the size of a pd array
    # returns 0 if array not found
    int arraySize(str &name):
        int len = libpd.libpd_arraysize(name.encode('utf-8'))
        if(len < 0):
            std::cerr << "Pd: cannot get size of unknown array \""
                      << name << "\"" << std::endl
            return 0
    
        return len


    # (re)size a pd array
    # sizes <= 0 are clipped to 1
    # returns true on success, false on failure
    bool resizeArray(str &name, long size):
        int ret = libpd.libpd_resize_array(name.encode('utf-8'), size)
        if(ret < 0):
            std::cerr << "Pd: cannot resize unknown array \"" << name << "\""
                      << std::endl
            return false
    
        return true


    # read from a pd array
    #
    # resizes given vector to readLen, checks readLen and offset
    #
    # returns true on success, false on failure
    #
    # calling without setting readLen and offset reads the whole array:
    #
    # vector<float> array1
    # readArray("array1", array1)
    #
    virtual bool readArray(str &name,
                           std::vector<float> &dest,
                           int readLen=-1, int offset=0):
        int len = libpd.libpd_arraysize(name.encode('utf-8'))
        if(len < 0):
            std::cerr << "Pd: cannot read unknown array \"" << name << "\""
                      << std::endl
            return false
    
        # full array len?
        if(readLen < 0):
            readLen = len
    
        # check read len
        else if(readLen > len):
            std::cerr << "Pd: given read len " << readLen << " > len "
                      << len << " of array \"" << name << "\"" << std::endl
            return false
    
        # check offset
        if(offset + readLen > len):
            std::cerr << "Pd: given read len and offset > len " << readLen
                      << " of array \"" << name << "\"" << std::endl
            return false
    
        # resize if necessary
        if(dest.size() != readLen):
            dest.resize(readLen, 0)
    
        if(libpd.libpd_read_array(&dest[0], name.encode('utf-8'), offset, readLen) < 0):
            std::cerr << "Pd: libpd.libpd_read_array failed for array \""
                      << name << "\"" << std::endl
            return false
    
        return true


    # write to a pd array
    #
    # calling without setting writeLen and offset writes the whole array:
    #
    # writeArray("array1", array1)
    #
    virtual bool writeArray(str &name,
                            std::vector<float> &source,
                            int writeLen=-1, int offset=0):
        int len = libpd.libpd_arraysize(name.encode('utf-8'))
        if(len < 0):
            std::cerr << "Pd: cannot write to unknown array \"" << name << "\""
                      << std::endl
            return false
    

        # full array len?
        if(writeLen < 0):
            writeLen = len
    

        # check write len
        else if(writeLen > len):
            std::cerr << "Pd: given write len " << writeLen << " > len " << len
                 << " of array \"" << name << "\"" << std::endl
            return false
    

        # check offset
        if(offset+writeLen > len):
            std::cerr << "Pd: given write len and offset > len " << writeLen
                 << " of array \"" << name << "\"" << std::endl
            return false
    

        if(libpd.libpd_write_array(name.encode('utf-8'), offset,
                             &source[0], writeLen) < 0):
            std::cerr << "Pd: libpd.libpd_write_array failed for array \""
                 << name << "\"" << std::endl
            return false
    
        return true


    # clear array and set to a specific value
    virtual void clearArray(str &name, int value=0):
        int len = libpd.libpd_arraysize(name.encode('utf-8'))
        if(len < 0):
            std::cerr << "Pd: cannot clear unknown array \""
                 << name << "\"" << std::endl
            return
    
        std::vector<float> array
        array.resize(len, value)
        if(libpd.libpd_write_array(name.encode('utf-8'), 0, &array[0], len) < 0):
            std::cerr << "Pd: libpd.libpd_write_array failed while clearing array \""
                 << name << "\"" << std::endl
    

# ----------------------------------------------------------------------------
# Utils

    # has the global pd instance been initialized?
    bool isInited():
        return PdContext.instance().isInited()


    # is the global pd instance using the ringerbuffer queue
    # for message padding?
    bool isQueued():
        return PdContext.instance().isQueued()


    # get the blocksize of pd (sample length per channel)
    static int blockSize():
        return libpd.libpd_blocksize()


    # set the max length of messages and lists, default: 32
    void setMaxMessageLen(unsigned int len):
        PdContext.instance().maxMsgLen = len


    # get the max length of messages and lists
    unsigned int maxMessageLen():
        return PdContext.instance().maxMsgLen


protected:

    # compound message status
    enum MsgType:
        MSG,
        MIDI,
        SYSEX,
        SYSRT


    # a singleton libpd instance wrapper
    class PdContext:

    public:

        # singleton data access
        # returns a reference to itself
        # note: only creates a new object on the first call
        static PdContext& instance():
            static PdBase::PdContext *singletonInstance = new PdContext
            return *singletonInstance
    

        # increments the num of pd base objects
        void addBase():numBases++}

        # decrements the num of pd base objects
        # clears if removing last base
        void removeBase():
            if(numBases > 0):
                numBases--
        
            else if(bInited): # double check clear
                clear()
        
    

        # init the pd instance
        bool init(const int numInChannels, const int numOutChannels,
                  const int sampleRate, bool queued):

            # attach callbacks
            bQueued = queued
            if(queued):
                libpd.libpd_set_queued_printhook(libpd.libpd_print_concatenator)
                libpd.libpd_set_concatenated_printhook(_print)

                libpd.libpd_set_queued_banghook(_bang)
                libpd.libpd_set_queued_floathook(_float)
                libpd.libpd_set_queued_symbolhook(_symbol)
                libpd.libpd_set_queued_listhook(_list)
                libpd.libpd_set_queued_messagehook(_message)

                libpd.libpd_set_queued_noteonhook(_noteon)
                libpd.libpd_set_queued_controlchangehook(_controlchange)
                libpd.libpd_set_queued_programchangehook(_programchange)
                libpd.libpd_set_queued_pitchbendhook(_pitchbend)
                libpd.libpd_set_queued_aftertouchhook(_aftertouch)
                libpd.libpd_set_queued_polyaftertouchhook(_polyaftertouch)
                libpd.libpd_set_queued_midibytehook(_midibyte)
                
                # init libpd, should only be called once!
                if(!bLibPdInited):
                    libpd.libpd_queued_init()
                    bLibPdInited = true
            
        
            else:
                libpd.libpd_set_printhook(libpd.libpd_print_concatenator)
                libpd.libpd_set_concatenated_printhook(_print)

                libpd.libpd_set_banghook(_bang)
                libpd.libpd_set_floathook(_float)
                libpd.libpd_set_symbolhook(_symbol)
                libpd.libpd_set_listhook(_list)
                libpd.libpd_set_messagehook(_message)

                libpd.libpd_set_noteonhook(_noteon)
                libpd.libpd_set_controlchangehook(_controlchange)
                libpd.libpd_set_programchangehook(_programchange)
                libpd.libpd_set_pitchbendhook(_pitchbend)
                libpd.libpd_set_aftertouchhook(_aftertouch)
                libpd.libpd_set_polyaftertouchhook(_polyaftertouch)
                libpd.libpd_set_midibytehook(_midibyte)

                # init libpd, should only be called once!
                if(!bLibPdInited):
                    libpd.libpd_init()
                    bLibPdInited = true
            
        

            # init audio
            if(libpd.libpd_init_audio(numInChannels,
                                numOutChannels,
                                sampleRate) != 0):
                return false
        
            bInited = true

            return bInited
    

        # clear the pd instance
        void clear():

            # detach callbacks
            if(bInited):
                compute_audio(false)
                if(bQueued):
                    libpd.libpd_set_queued_printhook(NULL)
                    libpd.libpd_set_concatenated_printhook(NULL)

                    libpd.libpd_set_queued_banghook(NULL)
                    libpd.libpd_set_queued_floathook(NULL)
                    libpd.libpd_set_queued_symbolhook(NULL)
                    libpd.libpd_set_queued_listhook(NULL)
                    libpd.libpd_set_queued_messagehook(NULL)

                    libpd.libpd_set_queued_noteonhook(NULL)
                    libpd.libpd_set_queued_controlchangehook(NULL)
                    libpd.libpd_set_queued_programchangehook(NULL)
                    libpd.libpd_set_queued_pitchbendhook(NULL)
                    libpd.libpd_set_queued_aftertouchhook(NULL)
                    libpd.libpd_set_queued_polyaftertouchhook(NULL)
                    libpd.libpd_set_queued_midibytehook(NULL)

                    libpd.libpd_queued_release()
            
                else:
                    libpd.libpd_set_printhook(NULL)
                    libpd.libpd_set_concatenated_printhook(NULL)

                    libpd.libpd_set_banghook(NULL)
                    libpd.libpd_set_floathook(NULL)
                    libpd.libpd_set_symbolhook(NULL)
                    libpd.libpd_set_listhook(NULL)
                    libpd.libpd_set_messagehook(NULL)

                    libpd.libpd_set_noteonhook(NULL)
                    libpd.libpd_set_controlchangehook(NULL)
                    libpd.libpd_set_programchangehook(NULL)
                    libpd.libpd_set_pitchbendhook(NULL)
                    libpd.libpd_set_aftertouchhook(NULL)
                    libpd.libpd_set_polyaftertouchhook(NULL)
                    libpd.libpd_set_midibytehook(NULL)
            
        
            bInited = false
            bQueued = false

            bMsgInProgress = false
            curMsgLen = 0
            msgType = MSG
            midiPort = 0
    

        # turn dsp on/off
        void compute_audio(bool state):
            # [ pd dsp $1(
            libpd.libpd_start_message(1)
            libpd.libpd_add_float((float) state)
            libpd.libpd_finish_message("pd", "dsp")
    

        # is the instance inited?
        inline bool isInited():return bInited}

        # is this instance queued?
        inline bool isQueued():return bQueued}

# ----------------------------------------------------------------------------
    # Variables

        bool bMsgInProgress    #< is a compound message being constructed?
        int maxMsgLen          #< maximum allowed message length
        int curMsgLen          #< the length of the current message

        # compound message status
        PdBase::MsgType msgType

        int midiPort   #< target midi port

        std::map<str,void*> sources    #< subscribed sources

        pd::PdReceiver *receiver               #< the message receiver
        pd::PdMidiReceiver *midi_receiver       #< the midi receiver

    private:

        bool bLibPdInited #< has libpd.libpd_init be called?
        bool bInited      #< is this pd context inited?
        bool bQueued #< is this context using the libpd.libpd_queued ringbuffer?

        unsigned int numBases #< number of pd base objects

        # hide all the constructors, copy functions here
        PdContext():                      # cannot create
            bLibPdInited = false
            bInited = false
            bQueued = false
            numBases = false
            receiver = NULL
            midi_receiver = NULL
            clear()
            maxMsgLen = 32
    
        virtual ~PdContext():             # cannot destroy
            # triple check clear
            if(bInited):clear()}
    
        void operator=(PdContext &from):} # not copyable

        # libpd static callback functions
        static void _print(const char *s):
            PdContext &context = PdContext.instance()
            if(context.receiver):
                context.receiver->print((str)s)
        
    

        static void _bang(const char *source):
            PdContext &context = PdContext.instance()
            if(context.receiver):
                context.receiver->receiveBang((str)source)
        
    

        static void _float(const char *source, float value):
            PdContext &context = PdContext.instance()
            if(context.receiver):
                context.receiver->receiveFloat((str)source, value)
        
    

        static void _symbol(const char *source, const char *symbol):
            PdContext &context = PdContext.instance()
            if(context.receiver):
                context.receiver->receiveSymbol((str)source,
                                                (str)symbol)
        
    

        static void _list(const char *source, int argc, t_atom *argv):
            PdContext &context = PdContext.instance()
            pd::List list
            for(int i = 0 i < argc i++):
                t_atom a = argv[i]
                if(a.a_type == A_FLOAT):
                    float f = a.a_w.w_float
                    list.add_float(f)
            
                else if(a.a_type == A_SYMBOL):
                    const char *s = a.a_w.w_symbol->s_name
                    list.add_symbol((str)s)
            
        
            if(context.receiver):
                context.receiver->receiveList((str)source, list)
        
    

        static void _message(const char *source, const char *symbol,
                             int argc, t_atom *argv):
            PdContext &context = PdContext.instance()
            pd::List list
            for(int i = 0 i < argc i++):
                t_atom a = argv[i]
                if(a.a_type == A_FLOAT):
                    float f = a.a_w.w_float
                    list.add_float(f)
            
                else if(a.a_type == A_SYMBOL):
                    const char *s = a.a_w.w_symbol->s_name
                    list.add_symbol((str)s)
            
        
            if(context.receiver):
                context.receiver->receiveMessage((str)source,
                                                 (str)symbol, list)
        
    

        static void _noteon(int channel, int pitch, int velocity):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receiveNoteOn(channel, pitch, velocity)
        
    

        static void _controlchange(int channel, int controller, int value):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receiveControlChange(channel,
                                                           controller,
                                                           value)
        
    

        static void _programchange(int channel, int value):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receiveProgramChange(channel, value)
        
    

        static void _pitchbend(int channel, int value):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receivePitchBend(channel, value)
        
    

        static void _aftertouch(int channel, int value):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receiveAftertouch(channel, value)
        
    

        static void _polyaftertouch(int channel, int pitch, int value):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receivePolyAftertouch(channel,
                                                            pitch,
                                                            value)
        
    

        static void _midibyte(int port, int byte):
            PdContext &context = PdContext.instance()
            if(context.midi_receiver):
                context.midi_receiver->receiveMidiByte(port, byte)
        
    

cdef class Singleton:
    _instances = {}
    @classmethod
    def instance(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = cls(*args, **kwargs)
        return cls._instances[cls]

cdef class MyCythonClass(Singleton):
    cdef int apple, orange
    def __cinit__(self, int apple, int orange):
        self.apple = apple
        self.orange = orange
    pass

# usage: MyCythonClass.instance(10, 21)

