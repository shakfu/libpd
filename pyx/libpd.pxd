
from libc.stdio cimport FILE
from libc.stdint cimport uint32_t, uint64_t

cdef extern from "../pure-data/src/m_pd.h":
    """
    #undef T_OBJECT
    """
    ctypedef float t_float
    ctypedef struct t_pdinstance
    ctypedef float t_floatarg
    ctypedef float t_sample
    ctypedef long t_int

    ctypedef struct t_class
    ctypedef struct t_object
    ctypedef struct t_outlet
    ctypedef struct t_inlet
    ctypedef struct t_binbuf
    ctypedef struct t_clock
    ctypedef struct t_outconnect
    ctypedef struct t_gpointer
    ctypedef struct t_glist 
    ctypedef struct t_canvas
    ctypedef struct t_scalar
    ctypedef struct t_text
    ctypedef struct t_gobj
    ctypedef struct t_widgetbehavior
    ctypedef struct t_parentwidgetbehavior
    ctypedef struct t_array

    ctypedef t_class *t_pd

    ctypedef void (*t_gotfn)(void *x)
    ctypedef void (*t_method)()
    ctypedef void *(*t_newmethod)()

    ctypedef struct t_symbol:
        const char *s_name
        # struct _class **s_thing
        # struct _symbol *s_next


    ctypedef union t_word:
        t_float w_float
        t_symbol *w_symbol
        # t_gpointer *w_gpointer
        # t_array *w_array
        # struct _binbuf *w_binbuf
        # int w_index

    ctypedef enum t_atomtype:
        A_NULL
        A_FLOAT
        A_SYMBOL
        A_POINTER
        A_SEMI
        A_COMMA
        A_DEFFLOAT
        A_DEFSYM
        A_DOLLAR
        A_DOLLSYM
        A_GIMME
        A_CANT

    ctypedef struct t_atom:
        t_atomtype a_type
    #     union word a_w

    # messaging
    cdef void pd_typedmess(t_pd *x, t_symbol *s, int argc, t_atom *argv)
    cdef void pd_forwardmess(t_pd *x, int argc, t_atom *argv)
    cdef t_symbol *gensym(const char *s)
    cdef t_gotfn getfn(const t_pd *x, t_symbol *s)
    cdef t_gotfn zgetfn(const t_pd *x, t_symbol *s)
    cdef void nullfn()
    cdef void pd_vmess(t_pd *x, t_symbol *s, const char *fmt, ...)

    cdef void mess0(x, s)
    cdef void mess1(x, s, a)
    cdef void mess2(x, s, a, b)
    cdef void mess3(x, s, a, b, c)
    cdef void mess4(x, s, a, b, c, d)
    cdef void mess5(x, s, a, b, c, d, e)

    cdef void obj_list(t_object *x, t_symbol *s, int argc, t_atom *argv)
    cdef t_pd *pd_newest()

    # memory mgmt
    cdef void *getbytes(size_t nbytes)
    cdef void *getzbytes(size_t nbytes)
    cdef void *copybytes(const void *src, size_t nbytes)
    cdef void freebytes(void *x, size_t nbytes)
    cdef void *resizebytes(void *x, size_t oldsize, size_t newsize)

    # atoms
    cdef void SETSEMI(t_atom *atom)
    cdef void SETCOMMA(t_atom *atom)
    cdef void SETPOINTER(t_atom *atom, t_gpointer *gp)
    cdef void SETFLOAT(t_atom *atom, float f)
    cdef void SETSYMBOL(t_atom *atom, char *s)
    cdef void SETDOLLAR(t_atom *atom, int n)
    cdef void SETDOLLSYM(t_atom *atom, char *s)

    cdef t_float atom_getfloat(const t_atom *a)
    cdef t_int atom_getint(const t_atom *a)
    cdef t_symbol *atom_getsymbol(const t_atom *a)
    cdef t_symbol *atom_gensym(const t_atom *a)
    cdef t_float atom_getfloatarg(int which, int argc, const t_atom *argv)
    cdef t_int atom_getintarg(int which, int argc, const t_atom *argv)
    cdef t_symbol *atom_getsymbolarg(int which, int argc, const t_atom *argv)
    cdef void atom_string(const t_atom *a, char *buf, unsigned int bufsize)

    # binbuf
    cdef t_binbuf *binbuf_new()
    cdef void binbuf_free(t_binbuf *x)
    cdef t_binbuf *binbuf_duplicate(const t_binbuf *y)
    cdef void binbuf_text(t_binbuf *x, const char *text, size_t size)
    cdef void binbuf_gettext(const t_binbuf *x, char **bufp, int *lengthp)
    cdef void binbuf_clear(t_binbuf *x)
    cdef void binbuf_add(t_binbuf *x, int argc, const t_atom *argv)
    cdef void binbuf_addv(t_binbuf *x, const char *fmt, ...)
    cdef void binbuf_addbinbuf(t_binbuf *x, const t_binbuf *y)
    cdef void binbuf_addsemi(t_binbuf *x)
    cdef void binbuf_restore(t_binbuf *x, int argc, const t_atom *argv)
    cdef void binbuf_print(const t_binbuf *x)
    cdef int binbuf_getnatom(const t_binbuf *x)
    cdef t_atom *binbuf_getvec(const t_binbuf *x)
    cdef int binbuf_resize(t_binbuf *x, int newsize)
    cdef void binbuf_eval(const t_binbuf *x, t_pd *target, int argc, const t_atom *argv)
    cdef int binbuf_read(t_binbuf *b, const char *filename, const char *dirname, int crflag)
    # cdef int binbuf_read_via_canvas(t_binbuf *b, const char *filename, const t_canvas *canvas, int crflag)
    cdef int binbuf_read_via_path(t_binbuf *b, const char *filename, const char *dirname, int crflag)
    cdef int binbuf_write(const t_binbuf *x, const char *filename, const char *dir, int crflag)
    cdef void binbuf_evalfile(t_symbol *name, t_symbol *dir)
    cdef t_symbol *binbuf_realizedollsym(t_symbol *s, int ac, const t_atom *av, int tonew)

    # clock
    cdef t_clock *clock_new(void *owner, t_method fn)
    cdef void clock_set(t_clock *x, double systime)
    cdef void clock_delay(t_clock *x, double delaytime)
    cdef void clock_unset(t_clock *x)
    cdef void clock_setunit(t_clock *x, double timeunit, int sampflag)
    cdef double clock_getlogicaltime()
    cdef double clock_gettimesince(double prevsystime)
    cdef double clock_gettimesincewithunits(double prevsystime, double units, int sampflag)
    cdef double clock_getsystimeafter(double delaytime)
    cdef void clock_free(t_clock *x)

    # pure data
    cdef t_pd *pd_new(t_class *cls)
    cdef void pd_free(t_pd *x)
    cdef void pd_bind(t_pd *x, t_symbol *s)
    cdef void pd_unbind(t_pd *x, t_symbol *s)
    cdef t_pd *pd_findbyclass(t_symbol *s, const t_class *c)
    cdef void pd_pushsym(t_pd *x)
    cdef void pd_popsym(t_pd *x)
    cdef void pd_bang(t_pd *x)
    cdef void pd_pointer(t_pd *x, t_gpointer *gp)
    cdef void pd_float(t_pd *x, t_float f)
    cdef void pd_symbol(t_pd *x, t_symbol *s)
    cdef void pd_list(t_pd *x, t_symbol *s, int argc, t_atom *argv)
    cdef void pd_anything(t_pd *x, t_symbol *s, int argc, t_atom *argv)
    # cdef void pd_class(x)

    # pointers
    cdef void gpointer_init(t_gpointer *gp)
    cdef void gpointer_copy(const t_gpointer *gpfrom, t_gpointer *gpto)
    cdef void gpointer_unset(t_gpointer *gp)
    cdef int gpointer_check(const t_gpointer *gp, int headok)

    # patchable objects
    cdef t_inlet *inlet_new(t_object *owner, t_pd *dest, t_symbol *s1, t_symbol *s2)
    cdef t_inlet *pointerinlet_new(t_object *owner, t_gpointer *gp)
    cdef t_inlet *floatinlet_new(t_object *owner, t_float *fp)
    cdef t_inlet *symbolinlet_new(t_object *owner, t_symbol **sp)
    cdef t_inlet *signalinlet_new(t_object *owner, t_float f)
    cdef void inlet_free(t_inlet *x)

    cdef t_outlet *outlet_new(t_object *owner, t_symbol *s)
    cdef void outlet_bang(t_outlet *x)
    cdef void outlet_pointer(t_outlet *x, t_gpointer *gp)
    cdef void outlet_float(t_outlet *x, t_float f)
    cdef void outlet_symbol(t_outlet *x, t_symbol *s)
    cdef void outlet_list(t_outlet *x, t_symbol *s, int argc, t_atom *argv)
    cdef void outlet_anything(t_outlet *x, t_symbol *s, int argc, t_atom *argv)
    cdef t_symbol *outlet_getsymbol(t_outlet *x)
    cdef void outlet_free(t_outlet *x)
    cdef t_object *pd_checkobject(t_pd *x)

    # canvases
    cdef void glob_setfilename(void *dummy, t_symbol *name, t_symbol *dir)
    cdef void canvas_setargs(int argc, const t_atom *argv)
    cdef void canvas_getargs(int *argcp, t_atom **argvp)
    cdef t_symbol *canvas_getcurrentdir()
    cdef t_glist *canvas_getcurrent()
    cdef void canvas_makefilename(const t_glist *c, const char *file, char *result, int resultsize)
    cdef t_symbol *canvas_getdir(const t_glist *x)
    cdef char sys_font[]
    cdef char sys_fontweight[]
    cdef int sys_hostfontsize(int fontsize, int zoom)
    cdef int sys_zoomfontwidth(int fontsize, int zoom, int worstcase)
    cdef int sys_zoomfontheight(int fontsize, int zoom, int worstcase)
    cdef int sys_fontwidth(int fontsize)
    cdef int sys_fontheight(int fontsize)
    cdef void canvas_dataproperties(t_glist *x, t_scalar *sc, t_binbuf *b)
    cdef int canvas_open(const t_canvas *x, const char *name, const char *ext, char *dirresult, char **nameresult, unsigned int size, int bin)

    # widget behaviours
    cdef const t_parentwidgetbehavior *pd_getparentwidget(t_pd *x)

    # classes
    cdef t_class *class_new(t_symbol *name, t_newmethod newmethod, t_method freemethod, size_t size, int flags, t_atomtype arg1, ...)
    cdef t_class *class_new64(t_symbol *name, t_newmethod newmethod, t_method freemethod, size_t size, int flags, t_atomtype arg1, ...)
    cdef void class_free(t_class *c)
    cdef t_class *class_getfirst()
    cdef void class_addcreator(t_newmethod newmethod, t_symbol *s, t_atomtype type1, ...)
    cdef void class_addmethod(t_class *c, t_method fn, t_symbol *sel, t_atomtype arg1, ...)
    cdef void class_addbang(t_class *c, t_method fn)
    cdef void class_addpointer(t_class *c, t_method fn)
    cdef void class_doaddfloat(t_class *c, t_method fn)
    cdef void class_addsymbol(t_class *c, t_method fn)
    cdef void class_addlist(t_class *c, t_method fn)
    cdef void class_addanything(t_class *c, t_method fn)
    cdef void class_sethelpsymbol(t_class *c, t_symbol *s)
    cdef void class_setwidget(t_class *c, const t_widgetbehavior *w)
    cdef void class_setparentwidget(t_class *c, const t_parentwidgetbehavior *w)
    cdef const char *class_getname(const t_class *c)
    cdef const char *class_gethelpname(const t_class *c)
    cdef const char *class_gethelpdir(const t_class *c)
    cdef void class_setdrawcommand(t_class *c)
    cdef int class_isdrawcommand(const t_class *c)
    cdef void class_domainsignalin(t_class *c, int onset)
    cdef void class_set_extern_dir(t_symbol *s)
    # cdef void CLASS_MAINSIGNALIN(t_class *c, type, field) # what type is type? field?
    ctypedef void (*t_savefn)(t_gobj *x, t_binbuf *b)
    cdef void class_setsavefn(t_class *c, t_savefn f)
    cdef t_savefn class_getsavefn(const t_class *c)
    cdef void obj_saveformat(const t_object *x, t_binbuf *bb) # add format to bb
    ctypedef void (*t_propertiesfn)(t_gobj *x, t_glist *glist)
    cdef void class_setpropertiesfn(t_class *c, t_propertiesfn f)
    cdef t_propertiesfn class_getpropertiesfn(const t_class *c)
    ctypedef void (*t_classfreefn)(t_class *)
    cdef void class_setfreefn(t_class *c, t_classfreefn fn)

    # printing
    cdef void post(const char *fmt, ...)
    cdef void startpost(const char *fmt, ...)
    cdef void poststring(const char *s)
    cdef void postfloat(t_floatarg f)
    cdef void postatom(int argc, const t_atom *argv)
    cdef void endpost()
    cdef void bug(const char *fmt, ...)
    cdef void pd_error(const void *object, const char *fmt, ...)

    ctypedef enum t_loglevel:
        PD_CRITICAL
        PD_ERROR
        PD_NORMAL
        PD_DEBUG
        PD_VERBOSE

    cdef void logpost(const void *object, int level, const char *fmt, ...)

    # system interface routines
    cdef int sys_isabsolutepath(const char *dir)
    cdef void sys_bashfilename(const char *from_, char *to)
    cdef void sys_unbashfilename(const char *from_, char *to)
    cdef int open_via_path(const char *dir, const char *name, const char *ext, char *dirresult, char **nameresult, unsigned int size, int bin)
    cdef int sched_geteventno()
    cdef double sys_getrealtime()
    cdef int (*sys_idlehook)()   # hook to add idle time computation
    cdef int sys_open(const char *path, int oflag, ...)
    cdef int sys_close(int fd)
    cdef FILE *sys_fopen(const char *filename, const char *mode)
    cdef int sys_fclose(FILE *stream)

    # threading
    cdef void sys_lock()
    cdef void sys_unlock()
    cdef int sys_trylock()

    # signals
    ctypedef float PD_FLOATTYPE # can also be double
    ctypedef uint32_t PD_FLOATUINTTYPE # can also be uint64_t    
    # ctypedef PD_FLOATTYPE t_sample
    ctypedef union t_sampleint_union:
      t_sample f
      PD_FLOATUINTTYPE i

    cdef int MAXLOGSIG
    cdef int MAXSIGSIZE

    ctypedef struct t_signal:
        int s_n                         # number of points in the array
        t_sample *s_vec                 # the array
        t_float s_sr                    # sample rate
        int s_refcount                  # number of times used
        int s_isborrowed                # whether we're going to borrow our array
        t_signal *s_borrowedfrom        # signal to borrow it from
        t_signal *s_nextfree            # next in freelist
        t_signal *s_nextused            # next in used list
        int s_vecsize                   # allocated size of array in points

    ctypedef t_int *(*t_perfroutine)(t_int *args)


    cdef t_int *plus_perform(t_int *args)
    cdef t_int *zero_perform(t_int *args)
    cdef t_int *copy_perform(t_int *args)

    cdef void dsp_add_plus(t_sample *in1, t_sample *in2, t_sample *out, int n)
    cdef void dsp_add_copy(t_sample *in_, t_sample *out, int n)
    cdef void dsp_add_scalarcopy(t_float *in_, t_sample *out, int n)
    cdef void dsp_add_zero(t_sample *out, int n)

    cdef int sys_getblksize()
    cdef t_float sys_getsr()
    cdef int sys_get_inchannels()
    cdef int sys_get_outchannels()

    cdef void dsp_add(t_perfroutine f, int n, ...)
    cdef void dsp_addv(t_perfroutine f, int n, t_int *vec)
    cdef void pd_fft(t_float *buf, int npoints, int inverse)
    cdef int ilog2(int n)

    cdef void mayer_fht(t_sample *fz, int n)
    cdef void mayer_fft(int n, t_sample *real, t_sample *imag)
    cdef void mayer_ifft(int n, t_sample *real, t_sample *imag)
    cdef void mayer_realfft(int n, t_sample *real)
    cdef void mayer_realifft(int n, t_sample *real)

    cdef float *cos_table
    cdef int LOGCOSTABSIZE
    cdef int COSTABSIZE

    cdef int canvas_suspend_dsp()
    cdef void canvas_resume_dsp(int oldstate)
    cdef void canvas_update_dsp()
    cdef int canvas_dspstate

    ctypedef struct t_resample:
        int method            # up/downsampling method ID
        int downsample        # downsampling factor
        int upsample          # upsampling factor
        t_sample *s_vec       # here we hold the resampled data
        int      s_n 
        t_sample *coeffs      # coefficients for filtering...
        int      coefsize 
        t_sample *buffer      # buffer for filtering
        int      bufsize 

    cdef void resample_init(t_resample *x)
    cdef void resample_free(t_resample *x)
    cdef void resample_dsp(t_resample *x, t_sample *in_, int insize, t_sample *out, int outsize, int method)
    cdef void resamplefrom_dsp(t_resample *x, t_sample *in_, int insize, int outsize, int method)
    cdef void resampleto_dsp(t_resample *x, t_sample *out, int insize, int outsize, int method)


    # utility functions for signals
    cdef t_float mtof(t_float)
    cdef t_float ftom(t_float)
    cdef t_float rmstodb(t_float)
    cdef t_float powtodb(t_float)
    cdef t_float dbtorms(t_float)
    cdef t_float dbtopow(t_float)
    cdef t_float q8_sqrt(t_float)
    cdef t_float q8_rsqrt(t_float)
    cdef t_float qsqrt(t_float)  # old names kept for extern compatibility
    cdef t_float qrsqrt(t_float)

    # data
    #   graphical arrays
    ctypedef struct t_garray

    cdef t_class *garray_class
    cdef int garray_getfloatarray(t_garray *x, int *size, t_float **vec)
    cdef int garray_getfloatwords(t_garray *x, int *size, t_word **vec)
    cdef void garray_redraw(t_garray *x)
    cdef int garray_npoints(t_garray *x)
    cdef char *garray_vec(t_garray *x)
    cdef void garray_resize_long(t_garray *x, long n)
    cdef void garray_usedindsp(t_garray *x)
    cdef void garray_setsaveit(t_garray *x, int saveit)
    cdef t_glist *garray_getglist(t_garray *x)
    cdef t_array *garray_getarray(t_garray *x)
    cdef t_class *scalar_class

    cdef t_float *value_get(t_symbol *s)
    cdef void value_release(t_symbol *s)
    cdef int value_getfloat(t_symbol *s, t_float *f)
    cdef int value_setfloat(t_symbol *s, t_float f)

    # GUI interface - functions to send strings to TK
    ctypedef void (*t_guicallbackfn)(t_gobj *client, t_glist *glist)

    cdef void sys_vgui(const char *fmt, ...)
    cdef void sys_gui(const char *s)
    cdef void sys_pretendguibytes(int n)
    cdef void sys_queuegui(void *client, t_glist *glist, t_guicallbackfn f)
    cdef void sys_unqueuegui(void *client)
    #   dialog window creation and destruction */
    cdef void gfxstub_new(t_pd *owner, void *key, const char *cmd)
    cdef void gfxstub_deleteforkey(void *key)

    # pd instance
    cdef void sys_getversion(int *major, int *minor, int *bugfix)

    ctypedef struct t_instancemidi
    ctypedef struct t_instanceinter
    ctypedef struct t_instancecanvas
    ctypedef struct t_instanceugen
    ctypedef struct t_instancestuff

    cdef struct _template

    ctypedef struct t_pdinstance:
        double pd_systime                   # global time in Pd ticks
        t_clock *pd_clock_setlist           # list of set clocks
        t_canvas *pd_canvaslist             # list of all root canvases
        _template *pd_templatelist          # list of all templates
        int pd_instanceno                   # ordinal number of this instance
        t_symbol **pd_symhash               # symbol table hash table
        t_instancemidi *pd_midi             # private stuff for x_midi.c
        t_instanceinter *pd_inter           # private stuff for s_inter.c
        t_instanceugen *pd_ugen             # private stuff for d_ugen.c
        t_instancecanvas *pd_gui            # semi-private stuff in g_canvas.h
        t_instancestuff *pd_stuff           # semi-private stuff in s_stuff.h
        t_pd *pd_newest                     # most recently created object
        t_symbol  pd_s_pointer
        t_symbol  pd_s_float
        t_symbol  pd_s_symbol
        t_symbol  pd_s_bang
        t_symbol  pd_s_list
        t_symbol  pd_s_anything
        t_symbol  pd_s_signal
        t_symbol  pd_s__N
        t_symbol  pd_s__X
        t_symbol  pd_s_x
        t_symbol  pd_s_y
        t_symbol  pd_s_
        int pd_islocked

    cdef t_pdinstance *pdinstance_new();
    cdef void pd_setinstance(t_pdinstance *x);
    cdef void pdinstance_free(t_pdinstance *x);

    cdef t_symbol* s_pointer
    cdef t_symbol* s_float 
    cdef t_symbol* s_symbol
    cdef t_symbol* s_bang  
    cdef t_symbol* s_list  
    cdef t_symbol* s_anything
    cdef t_symbol* s_signal
    cdef t_symbol* s__N  
    cdef t_symbol* s__X
    cdef t_symbol* s_x
    cdef t_symbol* s_y
    cdef t_symbol* s_

    cdef t_canvas *pd_getcanvaslist()
    cdef int pd_getdspstate()

    cdef t_binbuf *text_getbufbyname(t_symbol *s) # get binbuf from text obj
    cdef void text_notifybyname(t_symbol *s)      # notify it was modified
    
    cdef void pd_undo_set_objectstate(t_canvas*canvas, t_pd*x, t_symbol*s, int undo_argc, t_atom*undo_argv, int redo_argc, t_atom*redo_argv)


cdef extern from "../libpd_wrapper/z_libpd.h":

## initialization

    # initialize libpd; it is safe to call this more than once
    # returns 0 on success or -1 if libpd was already initialized
    # note: sets SIGFPE handler to keep bad pd patches from crashing due to divide
    #       by 0, set any custom handling after calling this function
    int libpd_init()

    # clear the libpd search path for abstractions and externals
    # note: this is called by libpd_init()
    void libpd_clear_search_path()

    # add a path to the libpd search paths
    # relative paths are relative to the current working directory
    # unlike desktop pd, *no* search paths are set by default (ie. extra)
    void libpd_add_to_search_path(const char *path)

## opening patches

    # open a patch by filename and parent dir path
    # returns an opaque patch handle pointer or NULL on failure
    void *libpd_openfile(const char *name, const char *dir)

    # close a patch by patch handle pointer
    void libpd_closefile(void *p) nogil

    # get the $0 id of the patch handle pointer
    # returns $0 value or 0 if the patch is non-existent
    int libpd_getdollarzero(void *p)

## audio processing

    # return pd's fixed block size: the number of sample frames per 1 pd tick
    int libpd_blocksize()

    # initialize audio rendering
    # returns 0 on success
    int libpd_init_audio(int inChannels, int outChannels, int sampleRate)

    # process interleaved float samples from inBuffer -> libpd -> outBuffer
    # buffer sizes are based on # of ticks and channels where:
    #     size = ticks * libpd_blocksize() * (in/out)channels
    # returns 0 on success
    int libpd_process_float(const int ticks,
        const float *inBuffer, float *outBuffer) nogil

    # process interleaved short samples from inBuffer -> libpd -> outBuffer
    # buffer sizes are based on # of ticks and channels where:
    #     size = ticks * libpd_blocksize() * (in/out)channels
    # float samples are converted to short by multiplying by 32767 and casting,
    # so any values received from pd patches beyond -1 to 1 will result in garbage
    # note: for efficiency, does *not* clip input
    # returns 0 on success
    int libpd_process_short(const int ticks,
        const short *inBuffer, short *outBuffer) nogil

    # process interleaved double samples from inBuffer -> libpd -> outBuffer
    # buffer sizes are based on # of ticks and channels where:
    #     size = ticks * libpd_blocksize() * (in/out)channels
    # returns 0 on success
    int libpd_process_double(const int ticks,
        const double *inBuffer, double *outBuffer) nogil

    # process non-interleaved float samples from inBuffer -> libpd -> outBuffer
    # copies buffer contents to/from libpd without striping
    # buffer sizes are based on a single tick and # of channels where:
    #     size = libpd_blocksize() * (in/out)channels
    # returns 0 on success
    int libpd_process_raw(const float *inBuffer, float *outBuffer) nogil

    # process non-interleaved short samples from inBuffer -> libpd -> outBuffer
    # copies buffer contents to/from libpd without striping
    # buffer sizes are based on a single tick and # of channels where:
    #     size = libpd_blocksize() * (in/out)channels
    # float samples are converted to short by multiplying by 32767 and casting,
    # so any values received from pd patches beyond -1 to 1 will result in garbage
    # note: for efficiency, does *not* clip input
    # returns 0 on success
    int libpd_process_raw_short(const short *inBuffer, short *outBuffer) nogil

    # process non-interleaved double samples from inBuffer -> libpd -> outBuffer
    # copies buffer contents to/from libpd without striping
    # buffer sizes are based on a single tick and # of channels where:
    #     size = libpd_blocksize() * (in/out)channels
    # returns 0 on success
    int libpd_process_raw_double(const double *inBuffer, double *outBuffer) nogil

## atom creation

    # write a float value to the given atom
    void libpd_set_float(t_atom *a, float x)

    # write a symbol value to the given atom
    void libpd_set_symbol(t_atom *a, const char *symbol)

## array access

    # get the size of an array by name
    # returns size or negative error code if non-existent
    int libpd_arraysize(const char *name)

    # (re)size an array by name sizes <= 0 are clipped to 1
    # returns 0 on success or negative error code if non-existent
    int libpd_resize_array(const char *name, long size)

    # read n values from named src array and write into dest starting at an offset
    # note: performs no bounds checking on dest
    # returns 0 on success or a negative error code if the array is non-existent
    # or offset + n exceeds range of array
    int libpd_read_array(float *dest, const char *name, int offset, int n)

    # read n values from src and write into named dest array starting at an offset
    # note: performs no bounds checking on src
    # returns 0 on success or a negative error code if the array is non-existent
    # or offset + n exceeds range of array
    int libpd_write_array(const char *name, int offset, const float *src, int n)

## sending messages to pd

    # send a bang to a destination receiver
    # ex: libpd_bang("foo") will send a bang to [s foo] on the next tick
    # returns 0 on success or -1 if receiver name is non-existent
    int libpd_bang(const char *recv)

    # send a float to a destination receiver
    # ex: libpd_float("foo", 1) will send a 1.0 to [s foo] on the next tick
    # returns 0 on success or -1 if receiver name is non-existent
    int libpd_float(const char *recv, float x)

    # send a symbol to a destination receiver
    # ex: libpd_symbol("foo", "bar") will send "bar" to [s foo] on the next tick
    # returns 0 on success or -1 if receiver name is non-existent
    int libpd_symbol(const char *recv, const char *symbol)

## sending compound messages: sequenced function calls

    # start composition of a new list or typed message of up to max element length
    # messages can be of a smaller length as max length is only an upper bound
    # note: no cleanup is required for unfinished messages
    # returns 0 on success or nonzero if the length is too large
    int libpd_start_message(int maxlen)

    # add a float to the current message in progress
    void libpd_add_float(float x)

    # add a symbol to the current message in progress
    void libpd_add_symbol(const char *symbol)

    # finish current message and send as a list to a destination receiver
    # returns 0 on success or -1 if receiver name is non-existent
    # ex: send [list 1 2 bar( to [s foo] on the next tick with:
    #     libpd_start_message(3)
    #     libpd_add_float(1)
    #     libpd_add_float(2)
    #     libpd_add_symbol("bar")
    #     libpd_finish_list("foo")
    int libpd_finish_list(const char *recv)

    # finish current message and send as a typed message to a destination receiver
    # note: typed message handling currently only supports up to 4 elements
    #       internally, additional elements may be ignored
    # returns 0 on success or -1 if receiver name is non-existent
    # ex: send [ pd dsp 1( on the next tick with:
    #     libpd_start_message(1)
    #     libpd_add_float(1)
    #     libpd_finish_message("pd", "dsp")
    int libpd_finish_message(const char *recv, const char *msg)


## sending compound messages: atom array

    # send an atom array of a given length as a list to a destination receiver
    # returns 0 on success or -1 if receiver name is non-existent
    # ex: send [list 1 2 bar( to [r foo] on the next tick with:
    #     t_atom v[3]
    #     libpd_set_float(v, 1)
    #     libpd_set_float(v + 1, 2)
    #     libpd_set_symbol(v + 2, "bar")
    #     libpd_list("foo", 3, v)
    int libpd_list(const char *recv, int argc, t_atom *argv)

    # send a atom array of a given length as a typed message to a destination
    # receiver, returns 0 on success or -1 if receiver name is non-existent
    # ex: send [ pd dsp 1( on the next tick with:
    #     t_atom v[1]
    #     libpd_set_float(v, 1)
    #     libpd_message("pd", "dsp", 1, v)
    int libpd_message(const char *recv, const char *msg, int argc, t_atom *argv)

## receiving messages from pd

    # subscribe to messages sent to a source receiver
    # ex: libpd_bind("foo") adds a "virtual" [r foo] which forwards messages to
    #     the libpd message hooks
    # returns an opaque receiver pointer or NULL on failure
    void *libpd_bind(const char *recv)

    # unsubscribe and free a source receiver object created by libpd_bind()
    void libpd_unbind(void *p)

    # check if a source receiver object exists with a given name
    # returns 1 if the receiver exists, otherwise 0
    int libpd_exists(const char *recv)

    # print receive hook signature, s is the string to be printed
    # note: default behavior returns individual words and spaces:
    #     line "hello 123" is received in 4 parts -> "hello", " ", "123\n"
    ctypedef void (*t_libpd_printhook)(const char *s)

    # bang receive hook signature, recv is the source receiver name
    ctypedef void (*t_libpd_banghook)(const char *recv)

    # float receive hook signature, recv is the source receiver name
    ctypedef void (*t_libpd_floathook)(const char *recv, float x)

    # symbol receive hook signature, recv is the source receiver name
    ctypedef void (*t_libpd_symbolhook)(const char *recv, const char *symbol)

    # list receive hook signature, recv is the source receiver name
    # argc is the list length and vector argv contains the list elements
    # which can be accessed using the atom accessor functions, ex:
    #     int i
    #     for (i = 0 i < argc i++) {
    #       t_atom *a = &argv[n]
    #       if (libpd_is_float(a)) {
    #         float x = libpd_get_float(a)
    #         // do something with float x
    #       } else if (libpd_is_symbol(a)) {
    #         char *s = libpd_get_symbol(a)
    #         // do something with c string s
    #       }
    #     }
    # note: check for both float and symbol types as atom may also be a pointer
    ctypedef void (*t_libpd_listhook)(const char *recv, int argc, t_atom *argv)

    # typed message hook signature, recv is the source receiver name and msg is
    # the typed message name: a message like [ foo bar 1 2 a b( will trigger a
    # function call like libpd_messagehook("foo", "bar", 4, argv)
    # argc is the list length and vector argv contains the
    # list elements which can be accessed using the atom accessor functions, ex:
    #     int i
    #     for (i = 0 i < argc i++) {
    #       t_atom *a = &argv[n]
    #       if (libpd_is_float(a)) {
    #         float x = libpd_get_float(a)
    #         // do something with float x
    #       } else if (libpd_is_symbol(a)) {
    #         char *s = libpd_get_symbol(a)
    #         // do something with c string s
    #       }
    #     }
    # note: check for both float and symbol types as atom may also be a pointer
    ctypedef void (*t_libpd_messagehook)(const char *recv, const char *msg,
        int argc, t_atom *argv)

    # set the print receiver hook, prints to stdout by default
    # note: do not call this while DSP is running
    void libpd_set_printhook(const t_libpd_printhook hook)

    # set the bang receiver hook, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_banghook(const t_libpd_banghook hook)

    # set the float receiver hook, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_floathook(const t_libpd_floathook hook)

    # set the symbol receiver hook, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_symbolhook(const t_libpd_symbolhook hook)

    # set the list receiver hook, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_listhook(const t_libpd_listhook hook)

    # set the message receiver hook, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_messagehook(const t_libpd_messagehook hook)

    # check if an atom is a float type: 0 or 1
    # note: no NULL check is performed
    int libpd_is_float(t_atom *a)

    # check if an atom is a symbol type: 0 or 1
    # note: no NULL check is performed
    int libpd_is_symbol(t_atom *a)

    # get the float value of an atom
    # note: no NULL or type checks are performed
    float libpd_get_float(t_atom *a)

    # note: no NULL or type checks are performed
    # get symbol value of an atom
    const char *libpd_get_symbol(t_atom *a)

    # increment to the next atom in an atom vector
    # returns next atom or NULL, assuming the atom vector is NULL-terminated
    t_atom *libpd_next_atom(t_atom *a)

## sending MIDI messages to pd

    # send a MIDI note on message to [notein] objects
    # channel is 0-indexed, pitch is 0-127, and velocity is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: there is no note off message, send a note on with velocity = 0 instead
    # returns 0 on success or -1 if an argument is out of range
    int libpd_noteon(int channel, int pitch, int velocity)

    # send a MIDI control change message to [ctlin] objects
    # channel is 0-indexed, controller is 0-127, and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # returns 0 on success or -1 if an argument is out of range
    int libpd_controlchange(int channel, int controller, int value)

    # send a MIDI program change message to [pgmin] objects
    # channel is 0-indexed and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # returns 0 on success or -1 if an argument is out of range
    int libpd_programchange(int channel, int value)

    # send a MIDI pitch bend message to [bendin] objects
    # channel is 0-indexed and value is -8192-8192
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: [bendin] outputs 0-16383 while [bendout] accepts -8192-8192
    # returns 0 on success or -1 if an argument is out of range
    int libpd_pitchbend(int channel, int value)

    # send a MIDI after touch message to [touchin] objects
    # channel is 0-indexed and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # returns 0 on success or -1 if an argument is out of range
    int libpd_aftertouch(int channel, int value)

    # send a MIDI poly after touch message to [polytouchin] objects
    # channel is 0-indexed, pitch is 0-127, and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # returns 0 on success or -1 if an argument is out of range
    int libpd_polyaftertouch(int channel, int pitch, int value)

    # send a raw MIDI byte to [midiin] objects
    # port is 0-indexed and byte is 0-256
    # returns 0 on success or -1 if an argument is out of range
    int libpd_midibyte(int port, int byte)

    # send a raw MIDI byte to [sysexin] objects
    # port is 0-indexed and byte is 0-256
    # returns 0 on success or -1 if an argument is out of range
    int libpd_sysex(int port, int byte)

    # send a raw MIDI byte to [realtimein] objects
    # port is 0-indexed and byte is 0-256
    # returns 0 on success or -1 if an argument is out of range
    int libpd_sysrealtime(int port, int byte)

## receiving MIDI messages from pd

    # MIDI note on receive hook signature
    # channel is 0-indexed, pitch is 0-127, and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: there is no note off message, note on w/ velocity = 0 is used instead
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_noteonhook)(int channel, int pitch, int velocity)

    # MIDI control change receive hook signature
    # channel is 0-indexed, controller is 0-127, and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_controlchangehook)(int channel,
        int controller, int value)

    # MIDI program change receive hook signature
    # channel is 0-indexed and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_programchangehook)(int channel, int value)

    # MIDI pitch bend receive hook signature
    # channel is 0-indexed and value is -8192-8192
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: [bendin] outputs 0-16383 while [bendout] accepts -8192-8192
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_pitchbendhook)(int channel, int value)

    # MIDI after touch receive hook signature
    # channel is 0-indexed and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_aftertouchhook)(int channel, int value)

    # MIDI poly after touch receive hook signature
    # channel is 0-indexed, pitch is 0-127, and value is 0-127
    # channels encode MIDI ports via: libpd_channel = pd_channel + 16 * pd_port
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_polyaftertouchhook)(int channel, int pitch, int value)

    # raw MIDI byte receive hook signature
    # port is 0-indexed and byte is 0-256
    # note: out of range values from pd are clamped
    ctypedef void (*t_libpd_midibytehook)(int port, int byte)

    # set the MIDI note on hook to receive from [noteout] objects, NULL by default
    # note: do not call this while DSP is running
    void libpd_set_noteonhook(const t_libpd_noteonhook hook)

    # set the MIDI control change hook to receive from [ctlout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_controlchangehook(const t_libpd_controlchangehook hook)

    # set the MIDI program change hook to receive from [pgmout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_programchangehook(const t_libpd_programchangehook hook)

    # set the MIDI pitch bend hook to receive from [bendout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_pitchbendhook(const t_libpd_pitchbendhook hook)

    # set the MIDI after touch hook to receive from [touchout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_aftertouchhook(const t_libpd_aftertouchhook hook)

    # set the MIDI poly after touch hook to receive from [polytouchout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_polyaftertouchhook(const t_libpd_polyaftertouchhook hook)

    # set the raw MIDI byte hook to receive from [midiout] objects,
    # NULL by default
    # note: do not call this while DSP is running
    void libpd_set_midibytehook(const t_libpd_midibytehook hook)

## GUI

    # open the current patches within a pd vanilla GUI
    # requires the path to pd's main folder that contains bin/, tcl/, etc
    # for a macOS .app bundle: /path/to/Pd-#.#-#.app/Contents/Resources
    # returns 0 on success
    int libpd_start_gui(char *path)

    # stop the pd vanilla GUI
    void libpd_stop_gui()

    # manually update and handle any GUI messages
    # this is called automatically when using a libpd_process function,
    # note: this also facilitates network message processing, etc so it can be
    #       useful to call repeatedly when idle for more throughput
    void libpd_poll_gui()

## multiple instances

    # create a new pd instance
    # returns new instance or NULL when libpd is not compiled with PDINSTANCE
    t_pdinstance *libpd_new_instance()

    # set the current pd instance
    # subsequent libpd calls will affect this instance only
    # does nothing when libpd is not compiled with PDINSTANCE
    void libpd_set_instance(t_pdinstance *p)

    # free a pd instance
    # does nothing when libpd is not compiled with PDINSTANCE
    void libpd_free_instance(t_pdinstance *p)

    # get the current pd instance
    t_pdinstance *libpd_this_instance()

    # get a pd instance by index
    # returns NULL if index is out of bounds or "this" instance when libpd is not
    # compiled with PDINSTANCE
    t_pdinstance *libpd_get_instance(int index)

    # get the number of pd instances
    # returns number or 1 when libpd is not compiled with PDINSTANCE
    int libpd_num_instances()

## log level

    # set verbose print state: 0 or 1
    void libpd_set_verbose(int verbose)

    # get the verbose print state: 0 or 1
    int libpd_get_verbose()
