
void libpd_clear_search_path(void);
void libpd_add_to_search_path(const char *path);


void *libpd_openfile(const char *name, const char *dir);
void libpd_closefile(void *p);
int libpd_getdollarzero(void *p);


int libpd_blocksize(void);
int libpd_init_audio(int inChannels, int outChannels, int sampleRate);

/*
%typemap(in) float *inBuffer { Py_ssize_t dummy; if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy)) return NULL; } %typemap(in) float *outBuffer { Py_ssize_t dummy; if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy)) return NULL; }
%typemap(in) short *inBuffer { Py_ssize_t dummy; if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy)) return NULL; } %typemap(in) short *outBuffer { Py_ssize_t dummy; if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy)) return NULL; }
%typemap(in) double *inBuffer { Py_ssize_t dummy; if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy)) return NULL; } %typemap(in) double *outBuffer { Py_ssize_t dummy; if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy)) return NULL; }
*/

int libpd_process_float(const int ticks, const float *inBuffer, float *outBuffer);
int libpd_process_short(const int ticks, const short *inBuffer, short *outBuffer);
int libpd_process_double(const int ticks, const double *inBuffer, double *outBuffer);

int libpd_process_raw(const float *inBuffer, float *outBuffer);
int libpd_process_raw_short(const short *inBuffer, short *outBuffer);
int libpd_process_raw_double(const double *inBuffer, double *outBuffer);



int libpd_arraysize(const char *name);
int libpd_resize_array(const char *name, long size);
int libpd_read_array(float *outBuffer, const char *name, int offset, int n);
int libpd_write_array(const char *name, int offset, const float *inBuffer, int n);



int libpd_bang(const char *recv);
int libpd_float(const char *recv, float x);
int libpd_symbol(const char *recv, const char *symbol);

int libpd_start_message(int maxlen);
void libpd_add_float(float x);
void libpd_add_symbol(const char *symbol);
int libpd_finish_list(const char *recv);
int libpd_finish_message(const char *recv, const char *msg);

void *libpd_bind(const char *recv);
void libpd_unbind(void *p);
int libpd_exists(const char *recv);




int libpd_set_print_callback(PyObject *callback);
int libpd_set_bang_callback(PyObject *callback);
int libpd_set_float_callback(PyObject *callback);
int libpd_set_symbol_callback(PyObject *callback);
int libpd_set_list_callback(PyObject *callback);
int libpd_set_message_callback(PyObject *callback);

int libpd_noteon(int channel, int pitch, int velocity);
int libpd_controlchange(int channel, int controller, int value);
int libpd_programchange(int channel, int value);
int libpd_pitchbend(int channel, int value);
int libpd_aftertouch(int channel, int value);
int libpd_polyaftertouch(int channel, int pitch, int value);
int libpd_midibyte(int port, int byte);
int libpd_sysex(int port, int byte);
int libpd_sysrealtime(int port, int byte);



int libpd_set_noteon_callback(PyObject *callback);
int libpd_set_controlchange_callback(PyObject *callback);
int libpd_set_programchange_callback(PyObject *callback);
int libpd_set_pitchbend_callback(PyObject *callback);
int libpd_set_aftertouch_callback(PyObject *callback);
int libpd_set_polyaftertouch_callback(PyObject *callback);
int libpd_set_midibyte_callback(PyObject *callback);



int libpd_start_gui(char *path);
void libpd_stop_gui(void);
int libpd_poll_gui(void);

void libpd_set_verbose(int verbose);
int libpd_get_verbose(void);


/*
%pythoncode %{
import array

def __process_args(args):
  if __libpd_start_message(len(args)): return -2
  for arg in args:
      if isinstance(arg, str):
        __libpd_add_symbol(arg)
      else:
        if isinstance(arg, int) or isinstance(arg, float):
          __libpd_add_float(arg)
        else:
          return -1
  return 0

def libpd_list(recv, *args):
  return __process_args(args) or __libpd_finish_list(recv)

def libpd_message(recv, symbol, *args):
  return __process_args(args) or __libpd_finish_message(recv, symbol)

__libpd_patches = {}

def libpd_open_patch(patchannel, dir = '.'):
  ptr = __libpd_openfile(patchannel, dir)
  if not ptr:
    raise IOError("unable to open patch: %s/%s" % (dir, patch))
  dz = __libpd_getdollarzero(ptr)
  __libpd_patches[dz] = ptr
  return dz

def libpd_close_patch(dz):
  __libpd_closefile(__libpd_patches[dz])
  del __libpd_patches[dz]

__libpd_subscriptions = {}

def libpd_subscribe(recv):
  if recv not in __libpd_subscriptions:
    __libpd_subscriptions[recv] = __libpd_bind(recv)

def libpd_unsubscribe(recv):
  __libpd_unbind(__libpd_subscriptions[recv])
  del __libpd_subscriptions[recv]

def libpd_compute_audio(flag):
  libpd_message('pd', 'dsp', flag)

def libpd_release():
  for p in __libpd_patches.values():
    __libpd_closefile(p)
  __libpd_patches.clear()
  for p in __libpd_subscriptions.values():
    __libpd_unbind(p)
  __libpd_subscriptions.clear()

class PdManager:
  def __init__(self, inChannels, outChannels, sampleRate, ticks):
    self.__ticks = ticks
    self.__outbuf = array.array('b', '\x00\x00'.encode() * outChannels * libpd_blocksize())
    libpd_compute_audio(1)
    libpd_init_audio(inChannels, outChannels, sampleRate)
  def process(self, inBuffer):
    libpd_process_short(self.__ticks, inBuffer, self.__outbuf)
    return self.__outbuf
%}

static PyObject *convertArgs(const char *recv, const char *symbol,
                              int n, t_atom *args) {
  int i = (symbol) ? 2 : 1;
  n += i;
  PyObject *result = PyTuple_New(n);
  PyTuple_SetItem(result, 0, PyString_FromString(recv));
  if (symbol) {
    PyTuple_SetItem(result, 1, PyString_FromString(symbol));
  }
  int j;
  for (j = 0; i < n; i++, j++) {
    t_atom *a = &args[j];
    PyObject *x = NULL;
    if (libpd_is_float(a)) {
      x = PyFloat_FromDouble(libpd_get_float(a));
    } else if (libpd_is_symbol(a)) {
      x = PyString_FromString(libpd_get_symbol(a));
    }
    PyTuple_SetItem(result, i, x);
  }
  return result;
}
*/

static PyObject *print_callback = NULL; static int libpd_set_print_callback(PyObject *callback) { Py_XDECREF(print_callback); if (PyCallable_Check(callback)) { print_callback = callback; Py_INCREF(print_callback); return 0; } else { print_callback = NULL; return -1; } } static void pylibpd_print (const char *s) { if (print_callback) { PyObject *pyargs = Py_BuildValue ("(s)", s); PyObject *result = PyObject_CallObject(print_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *bang_callback = NULL; static int libpd_set_bang_callback(PyObject *callback) { Py_XDECREF(bang_callback); if (PyCallable_Check(callback)) { bang_callback = callback; Py_INCREF(bang_callback); return 0; } else { bang_callback = NULL; return -1; } } static void pylibpd_bang (const char *recv) { if (bang_callback) { PyObject *pyargs = Py_BuildValue ("(s)", recv); PyObject *result = PyObject_CallObject(bang_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *float_callback = NULL; static int libpd_set_float_callback(PyObject *callback) { Py_XDECREF(float_callback); if (PyCallable_Check(callback)) { float_callback = callback; Py_INCREF(float_callback); return 0; } else { float_callback = NULL; return -1; } } static void pylibpd_float (const char *recv, float x) { if (float_callback) { PyObject *pyargs = Py_BuildValue ("(sf)", recv, x); PyObject *result = PyObject_CallObject(float_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *symbol_callback = NULL; static int libpd_set_symbol_callback(PyObject *callback) { Py_XDECREF(symbol_callback); if (PyCallable_Check(callback)) { symbol_callback = callback; Py_INCREF(symbol_callback); return 0; } else { symbol_callback = NULL; return -1; } } static void pylibpd_symbol (const char *recv, const char *symbol) { if (symbol_callback) { PyObject *pyargs = Py_BuildValue ("(ss)", recv, symbol); PyObject *result = PyObject_CallObject(symbol_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *list_callback = NULL; static int libpd_set_list_callback(PyObject *callback) { Py_XDECREF(list_callback); if (PyCallable_Check(callback)) { list_callback = callback; Py_INCREF(list_callback); return 0; } else { list_callback = NULL; return -1; } } static void pylibpd_list (const char *recv, int n, t_atom *pd_args) { if (list_callback) { PyObject *pyargs = convertArgs (recv, NULL, n, pd_args); PyObject *result = PyObject_CallObject(list_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *message_callback = NULL; static int libpd_set_message_callback(PyObject *callback) { Py_XDECREF(message_callback); if (PyCallable_Check(callback)) { message_callback = callback; Py_INCREF(message_callback); return 0; } else { message_callback = NULL; return -1; } } static void pylibpd_message (const char *recv, const char *symbol, int n, t_atom *pd_args) { if (message_callback) { PyObject *pyargs = convertArgs (recv, symbol, n, pd_args); PyObject *result = PyObject_CallObject(message_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *noteon_callback = NULL; static int libpd_set_noteon_callback(PyObject *callback) { Py_XDECREF(noteon_callback); if (PyCallable_Check(callback)) { noteon_callback = callback; Py_INCREF(noteon_callback); return 0; } else { noteon_callback = NULL; return -1; } } static void pylibpd_noteon (int channel, int pitch, int velocity) { if (noteon_callback) { PyObject *pyargs = Py_BuildValue ("(iii)", channel, pitch, velocity); PyObject *result = PyObject_CallObject(noteon_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *controlchange_callback = NULL; static int libpd_set_controlchange_callback(PyObject *callback) { Py_XDECREF(controlchange_callback); if (PyCallable_Check(callback)) { controlchange_callback = callback; Py_INCREF(controlchange_callback); return 0; } else { controlchange_callback = NULL; return -1; } } static void pylibpd_controlchange (int channel, int controller, int velocity) { if (controlchange_callback) { PyObject *pyargs = Py_BuildValue ("(iii)", channel, controller, velocity); PyObject *result = PyObject_CallObject(controlchange_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *programchange_callback = NULL; static int libpd_set_programchange_callback(PyObject *callback) { Py_XDECREF(programchange_callback); if (PyCallable_Check(callback)) { programchange_callback = callback; Py_INCREF(programchange_callback); return 0; } else { programchange_callback = NULL; return -1; } } static void pylibpd_programchange (int channel, int value) { if (programchange_callback) { PyObject *pyargs = Py_BuildValue ("(ii)", channel, value); PyObject *result = PyObject_CallObject(programchange_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *pitchbend_callback = NULL; static int libpd_set_pitchbend_callback(PyObject *callback) { Py_XDECREF(pitchbend_callback); if (PyCallable_Check(callback)) { pitchbend_callback = callback; Py_INCREF(pitchbend_callback); return 0; } else { pitchbend_callback = NULL; return -1; } } static void pylibpd_pitchbend (int channel, int value) { if (pitchbend_callback) { PyObject *pyargs = Py_BuildValue ("(ii)", channel, value); PyObject *result = PyObject_CallObject(pitchbend_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *aftertouch_callback = NULL; static int libpd_set_aftertouch_callback(PyObject *callback) { Py_XDECREF(aftertouch_callback); if (PyCallable_Check(callback)) { aftertouch_callback = callback; Py_INCREF(aftertouch_callback); return 0; } else { aftertouch_callback = NULL; return -1; } } static void pylibpd_aftertouch (int channel, int velocity) { if (aftertouch_callback) { PyObject *pyargs = Py_BuildValue ("(ii)", channel, velocity); PyObject *result = PyObject_CallObject(aftertouch_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *polyaftertouch_callback = NULL; static int libpd_set_polyaftertouch_callback(PyObject *callback) { Py_XDECREF(polyaftertouch_callback); if (PyCallable_Check(callback)) { polyaftertouch_callback = callback; Py_INCREF(polyaftertouch_callback); return 0; } else { polyaftertouch_callback = NULL; return -1; } } static void pylibpd_polyaftertouch (int channel, int pitch, int velocity) { if (polyaftertouch_callback) { PyObject *pyargs = Py_BuildValue ("(iii)", channel, pitch, velocity); PyObject *result = PyObject_CallObject(polyaftertouch_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }
static PyObject *midibyte_callback = NULL; static int libpd_set_midibyte_callback(PyObject *callback) { Py_XDECREF(midibyte_callback); if (PyCallable_Check(callback)) { midibyte_callback = callback; Py_INCREF(midibyte_callback); return 0; } else { midibyte_callback = NULL; return -1; } } static void pylibpd_midibyte (int port, int byte) { if (midibyte_callback) { PyObject *pyargs = Py_BuildValue ("(ii)", port, byte); PyObject *result = PyObject_CallObject(midibyte_callback, pyargs); Py_XDECREF(result); Py_DECREF(pyargs); } }





libpd_set_printhook(pylibpd_print);
libpd_set_banghook(pylibpd_bang);
libpd_set_floathook(pylibpd_float);
libpd_set_symbolhook(pylibpd_symbol);
libpd_set_listhook(pylibpd_list);
libpd_set_messagehook(pylibpd_message);

libpd_set_noteonhook(pylibpd_noteon);
libpd_set_controlchangehook(pylibpd_controlchange);
libpd_set_programchangehook(pylibpd_programchange);
libpd_set_pitchbendhook(pylibpd_pitchbend);
libpd_set_aftertouchhook(pylibpd_aftertouch);
libpd_set_polyaftertouchhook(pylibpd_polyaftertouch);
libpd_set_midibytehook(pylibpd_midibyte);

libpd_init();

