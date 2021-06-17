

/*
%typemap(in) float *inBuffer { 
  Py_ssize_t dummy; 
  if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy)) 
  return NULL; 
}

%typemap(in) float *outBuffer { 
  Py_ssize_t dummy;
  if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy))
  return NULL;
}


%typemap(in) short *inBuffer { 
  Py_ssize_t dummy;
  if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy))
  return NULL;
}

%typemap(in) short *outBuffer {
  Py_ssize_t dummy;
  if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy))
  return NULL;
}


%typemap(in) double *inBuffer {
  Py_ssize_t dummy;
  if (PyObject_AsReadBuffer($input, (const void **)&$1, &dummy)) 
  return NULL;
}

%typemap(in) double *outBuffer {
  Py_ssize_t dummy;
  if (PyObject_AsWriteBuffer($input, (void **)&$1, &dummy))
  return NULL;
}
*/

int libpd_set_print_callback(PyObject *callback);
int libpd_set_bang_callback(PyObject *callback);
int libpd_set_float_callback(PyObject *callback);
int libpd_set_symbol_callback(PyObject *callback);
int libpd_set_list_callback(PyObject *callback);
int libpd_set_message_callback(PyObject *callback);

int libpd_set_noteon_callback(PyObject *callback);
int libpd_set_controlchange_callback(PyObject *callback);
int libpd_set_programchange_callback(PyObject *callback);
int libpd_set_pitchbend_callback(PyObject *callback);
int libpd_set_aftertouch_callback(PyObject *callback);
int libpd_set_polyaftertouch_callback(PyObject *callback);
int libpd_set_midibyte_callback(PyObject *callback);

static PyObject *convertArgs(const char *recv, const char *symbol, int n,
                             t_atom *args) {
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

static PyObject *print_callback = NULL;
static int libpd_set_print_callback(PyObject *callback) {
    Py_XDECREF(print_callback);
    if (PyCallable_Check(callback)) {
        print_callback = callback;
        Py_INCREF(print_callback);
        return 0;
    } else {
        print_callback = NULL;
        return -1;
    }
}
static void pylibpd_print(const char *s) {
    if (print_callback) {
        PyObject *pyargs = Py_BuildValue("(s)", s);
        PyObject *result = PyObject_CallObject(print_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *bang_callback = NULL;
static int libpd_set_bang_callback(PyObject *callback) {
    Py_XDECREF(bang_callback);
    if (PyCallable_Check(callback)) {
        bang_callback = callback;
        Py_INCREF(bang_callback);
        return 0;
    } else {
        bang_callback = NULL;
        return -1;
    }
}
static void pylibpd_bang(const char *recv) {
    if (bang_callback) {
        PyObject *pyargs = Py_BuildValue("(s)", recv);
        PyObject *result = PyObject_CallObject(bang_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *float_callback = NULL;
static int libpd_set_float_callback(PyObject *callback) {
    Py_XDECREF(float_callback);
    if (PyCallable_Check(callback)) {
        float_callback = callback;
        Py_INCREF(float_callback);
        return 0;
    } else {
        float_callback = NULL;
        return -1;
    }
}
static void pylibpd_float(const char *recv, float x) {
    if (float_callback) {
        PyObject *pyargs = Py_BuildValue("(sf)", recv, x);
        PyObject *result = PyObject_CallObject(float_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *symbol_callback = NULL;
static int libpd_set_symbol_callback(PyObject *callback) {
    Py_XDECREF(symbol_callback);
    if (PyCallable_Check(callback)) {
        symbol_callback = callback;
        Py_INCREF(symbol_callback);
        return 0;
    } else {
        symbol_callback = NULL;
        return -1;
    }
}
static void pylibpd_symbol(const char *recv, const char *symbol) {
    if (symbol_callback) {
        PyObject *pyargs = Py_BuildValue("(ss)", recv, symbol);
        PyObject *result = PyObject_CallObject(symbol_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *list_callback = NULL;
static int libpd_set_list_callback(PyObject *callback) {
    Py_XDECREF(list_callback);
    if (PyCallable_Check(callback)) {
        list_callback = callback;
        Py_INCREF(list_callback);
        return 0;
    } else {
        list_callback = NULL;
        return -1;
    }
}
static void pylibpd_list(const char *recv, int n, t_atom *pd_args) {
    if (list_callback) {
        PyObject *pyargs = convertArgs(recv, NULL, n, pd_args);
        PyObject *result = PyObject_CallObject(list_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *message_callback = NULL;
static int libpd_set_message_callback(PyObject *callback) {
    Py_XDECREF(message_callback);
    if (PyCallable_Check(callback)) {
        message_callback = callback;
        Py_INCREF(message_callback);
        return 0;
    } else {
        message_callback = NULL;
        return -1;
    }
}
static void pylibpd_message(const char *recv, const char *symbol, int n,
                            t_atom *pd_args) {
    if (message_callback) {
        PyObject *pyargs = convertArgs(recv, symbol, n, pd_args);
        PyObject *result = PyObject_CallObject(message_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *noteon_callback = NULL;
static int libpd_set_noteon_callback(PyObject *callback) {
    Py_XDECREF(noteon_callback);
    if (PyCallable_Check(callback)) {
        noteon_callback = callback;
        Py_INCREF(noteon_callback);
        return 0;
    } else {
        noteon_callback = NULL;
        return -1;
    }
}
static void pylibpd_noteon(int channel, int pitch, int velocity) {
    if (noteon_callback) {
        PyObject *pyargs = Py_BuildValue("(iii)", channel, pitch, velocity);
        PyObject *result = PyObject_CallObject(noteon_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *controlchange_callback = NULL;
static int libpd_set_controlchange_callback(PyObject *callback) {
    Py_XDECREF(controlchange_callback);
    if (PyCallable_Check(callback)) {
        controlchange_callback = callback;
        Py_INCREF(controlchange_callback);
        return 0;
    } else {
        controlchange_callback = NULL;
        return -1;
    }
}
static void pylibpd_controlchange(int channel, int controller, int velocity) {
    if (controlchange_callback) {
        PyObject *pyargs =
            Py_BuildValue("(iii)", channel, controller, velocity);
        PyObject *result = PyObject_CallObject(controlchange_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *programchange_callback = NULL;
static int libpd_set_programchange_callback(PyObject *callback) {
    Py_XDECREF(programchange_callback);
    if (PyCallable_Check(callback)) {
        programchange_callback = callback;
        Py_INCREF(programchange_callback);
        return 0;
    } else {
        programchange_callback = NULL;
        return -1;
    }
}
static void pylibpd_programchange(int channel, int value) {
    if (programchange_callback) {
        PyObject *pyargs = Py_BuildValue("(ii)", channel, value);
        PyObject *result = PyObject_CallObject(programchange_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *pitchbend_callback = NULL;
static int libpd_set_pitchbend_callback(PyObject *callback) {
    Py_XDECREF(pitchbend_callback);
    if (PyCallable_Check(callback)) {
        pitchbend_callback = callback;
        Py_INCREF(pitchbend_callback);
        return 0;
    } else {
        pitchbend_callback = NULL;
        return -1;
    }
}
static void pylibpd_pitchbend(int channel, int value) {
    if (pitchbend_callback) {
        PyObject *pyargs = Py_BuildValue("(ii)", channel, value);
        PyObject *result = PyObject_CallObject(pitchbend_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *aftertouch_callback = NULL;
static int libpd_set_aftertouch_callback(PyObject *callback) {
    Py_XDECREF(aftertouch_callback);
    if (PyCallable_Check(callback)) {
        aftertouch_callback = callback;
        Py_INCREF(aftertouch_callback);
        return 0;
    } else {
        aftertouch_callback = NULL;
        return -1;
    }
}
static void pylibpd_aftertouch(int channel, int velocity) {
    if (aftertouch_callback) {
        PyObject *pyargs = Py_BuildValue("(ii)", channel, velocity);
        PyObject *result = PyObject_CallObject(aftertouch_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *polyaftertouch_callback = NULL;
static int libpd_set_polyaftertouch_callback(PyObject *callback) {
    Py_XDECREF(polyaftertouch_callback);
    if (PyCallable_Check(callback)) {
        polyaftertouch_callback = callback;
        Py_INCREF(polyaftertouch_callback);
        return 0;
    } else {
        polyaftertouch_callback = NULL;
        return -1;
    }
}
static void pylibpd_polyaftertouch(int channel, int pitch, int velocity) {
    if (polyaftertouch_callback) {
        PyObject *pyargs = Py_BuildValue("(iii)", channel, pitch, velocity);
        PyObject *result = PyObject_CallObject(polyaftertouch_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}
static PyObject *midibyte_callback = NULL;
static int libpd_set_midibyte_callback(PyObject *callback) {
    Py_XDECREF(midibyte_callback);
    if (PyCallable_Check(callback)) {
        midibyte_callback = callback;
        Py_INCREF(midibyte_callback);
        return 0;
    } else {
        midibyte_callback = NULL;
        return -1;
    }
}
static void pylibpd_midibyte(int port, int byte) {
    if (midibyte_callback) {
        PyObject *pyargs = Py_BuildValue("(ii)", port, byte);
        PyObject *result = PyObject_CallObject(midibyte_callback, pyargs);
        Py_XDECREF(result);
        Py_DECREF(pyargs);
    }
}

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
