cdef extern from "../pure-data/src/m_pd.h":
    """
    #undef T_OBJECT
    """

    ctypedef struct t_atom
    ctypedef struct t_pdinstance
    ctypedef struct t_symbol
    ctypedef float t_float
    ctypedef float t_floatarg
    ctypedef float t_sample
    ctypedef long t_int

    void SETFLOAT(t_atom *atom, float f)
    void SETSYMBOL(t_atom *atom, char *s)

    # conversion
    t_float atom_getfloat(const t_atom *a)
    t_int atom_getint(const t_atom *a)
    t_symbol *atom_getsymbol(const t_atom *a)
    t_symbol *atom_gensym(const t_atom *a)
    t_float atom_getfloatarg(int which, int argc, const t_atom *argv)
    t_int atom_getintarg(int which, int argc, const t_atom *argv)
    t_symbol *atom_getsymbolarg(int which, int argc, const t_atom *argv)
    void atom_string(const t_atom *a, char *buf, unsigned int bufsize)

    # # printing -> causes crash
    # void post(const char *fmt, ...)
    # void startpost(const char *fmt, ...)
    # void poststring(const char *s)
    # void postfloat(t_floatarg f)
    # void postatom(int argc, const t_atom *argv)
    # void endpost()
    # void error(const char *fmt, ...)
    # void verbose(int level, const char *fmt, ...)
    # void bug(const char *fmt, ...)
    # void pd_error(const void *object, const char *fmt, ...)
    # void logpost(const void *object, const int level, const char *fmt, ...)


cdef extern from "../libpd_wrapper/z_libpd.h":

## initialization

    int libpd_init()
    void libpd_clear_search_path()
    void libpd_add_to_search_path(const char *path)

## opening patches

    void *libpd_openfile(const char *name, const char *dir)
    void libpd_closefile(void *p)
    int libpd_getdollarzero(void *p)

## audio processing

    int libpd_blocksize()
    int libpd_init_audio(int inChannels, int outChannels, int sampleRate)
    int libpd_process_float(const int ticks, const float *inBuffer, float *outBuffer) nogil
    int libpd_process_short(const int ticks, const short *inBuffer, short *outBuffer) nogil
    int libpd_process_double(const int ticks, const double *inBuffer, double *outBuffer) nogil
    int libpd_process_raw(const float *inBuffer, float *outBuffer) nogil
    int libpd_process_raw_short(const short *inBuffer, short *outBuffer) nogil
    int libpd_process_raw_double(const double *inBuffer, double *outBuffer) nogil

## array access

    int libpd_arraysize(const char *name)
    int libpd_resize_array(const char *name, long size)
    int libpd_read_array(float *dest, const char *name, int offset, int n)
    int libpd_write_array(const char *name, int offset, const float *src, int n)

## sending messages to pd

    int libpd_bang(const char *recv)
    int libpd_float(const char *recv, float x)
    int libpd_symbol(const char *recv, const char *symbol)

## sending compound messages: sequenced function calls

    int libpd_start_message(int maxlen)
    void libpd_add_float(float x)
    void libpd_add_symbol(const char *symbol)
    int libpd_finish_list(const char *recv)
    int libpd_finish_message(const char *recv, const char *msg)


## sending compound messages: atom array

    void libpd_set_float(t_atom *a, float x)
    void libpd_set_symbol(t_atom *a, const char *symbol)
    int libpd_list(const char *recv, int argc, t_atom *argv)
    int libpd_message(const char *recv, const char *msg, int argc, t_atom *argv)

## receiving messages from pd

    void *libpd_bind(const char *recv)
    void libpd_unbind(void *p)
    int libpd_exists(const char *recv)
    ctypedef void (*t_libpd_printhook)(const char *s)
    ctypedef void (*t_libpd_banghook)(const char *recv)
    ctypedef void (*t_libpd_floathook)(const char *recv, float x)
    ctypedef void (*t_libpd_symbolhook)(const char *recv, const char *symbol)
    ctypedef void (*t_libpd_listhook)(const char *recv, int argc, t_atom *argv)
    ctypedef void (*t_libpd_messagehook)(const char *recv, const char *msg, int argc, t_atom *argv)

    void libpd_set_printhook(const t_libpd_printhook hook)
    void libpd_set_banghook(const t_libpd_banghook hook)
    void libpd_set_floathook(const t_libpd_floathook hook)
    void libpd_set_symbolhook(const t_libpd_symbolhook hook)
    void libpd_set_listhook(const t_libpd_listhook hook)
    void libpd_set_messagehook(const t_libpd_messagehook hook)
    int libpd_is_float(t_atom *a)
    int libpd_is_symbol(t_atom *a)
    float libpd_get_float(t_atom *a)
    const char *libpd_get_symbol(t_atom *a)
    t_atom *libpd_next_atom(t_atom *a)

## sending MIDI messages to pd

    int libpd_noteon(int channel, int pitch, int velocity)
    int libpd_controlchange(int channel, int controller, int value)
    int libpd_programchange(int channel, int value)
    int libpd_pitchbend(int channel, int value)
    int libpd_aftertouch(int channel, int value)
    int libpd_polyaftertouch(int channel, int pitch, int value)
    int libpd_midibyte(int port, int byte)
    int libpd_sysex(int port, int byte)
    int libpd_sysrealtime(int port, int byte)

## receiving MIDI messages from pd

    ctypedef void (*t_libpd_noteonhook)(int channel, int pitch, int velocity)
    ctypedef void (*t_libpd_controlchangehook)(int channel, int controller, int value)
    ctypedef void (*t_libpd_programchangehook)(int channel, int value)
    ctypedef void (*t_libpd_pitchbendhook)(int channel, int value)
    ctypedef void (*t_libpd_aftertouchhook)(int channel, int value)
    ctypedef void (*t_libpd_polyaftertouchhook)(int channel, int pitch, int value)
    ctypedef void (*t_libpd_midibytehook)(int port, int byte)
    void libpd_set_noteonhook(const t_libpd_noteonhook hook)
    void libpd_set_controlchangehook(const t_libpd_controlchangehook hook)
    void libpd_set_programchangehook(const t_libpd_programchangehook hook)
    void libpd_set_pitchbendhook(const t_libpd_pitchbendhook hook)
    void libpd_set_aftertouchhook(const t_libpd_aftertouchhook hook)
    void libpd_set_polyaftertouchhook(const t_libpd_polyaftertouchhook hook)
    void libpd_set_midibytehook(const t_libpd_midibytehook hook)

## GUI

    int libpd_start_gui(char *path)
    void libpd_stop_gui()
    void libpd_poll_gui()

## multiple instances

    t_pdinstance *libpd_new_instance()
    void libpd_set_instance(t_pdinstance *p)
    void libpd_free_instance(t_pdinstance *p)
    t_pdinstance *libpd_this_instance()
    t_pdinstance *libpd_get_instance(int index)
    int libpd_num_instances()

## log level

    void libpd_set_verbose(int verbose)
    int libpd_get_verbose()



