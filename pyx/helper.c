#include <Python.h>
#include "m_pd.h"
#include "z_libpd.h"




static PyObject *convertArgs(const char *dest, const char *sym, int n,
                             t_atom *args) {
  int i = (sym) ? 2 : 1;
  n += i;
  PyObject *result = PyTuple_New(n);
  PyTuple_SetItem(result, 0, PyString_FromString(dest));
  if (sym) {
    PyTuple_SetItem(result, 1, PyString_FromString(sym));
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

#define MAKE_CALLBACK(s, args1, cmd, args2) \
static PyObject *s##_callback = NULL; \
static int libpd_set_##s##_callback(PyObject *callback) { \
  Py_XDECREF(s##_callback); \
  if (PyCallable_Check(callback)) { \
    s##_callback = callback; \
    Py_INCREF(s##_callback); \
    return 0; \
  } else { \
    s##_callback = NULL; \
    return -1; \
  } \
} \
static void pylibpd_##s args1 { \
  if (s##_callback) { \
    PyObject *pyargs = cmd args2; \
    PyObject *result = PyObject_CallObject(s##_callback, pyargs); \
    Py_XDECREF(result); \
    Py_DECREF(pyargs); \
  } \
}

MAKE_CALLBACK(print, (const char *s), Py_BuildValue, ("(s)", s))
MAKE_CALLBACK(bang, (const char *dest), Py_BuildValue, ("(s)", dest))
MAKE_CALLBACK(float, (const char *dest, float val),
    Py_BuildValue, ("(sf)", dest, val))
MAKE_CALLBACK(symbol, (const char *dest, const char *sym),
    Py_BuildValue, ("(ss)", dest, sym))
MAKE_CALLBACK(list, (const char *dest, int n, t_atom *pd_args),
    convertArgs, (dest, NULL, n, pd_args))
MAKE_CALLBACK(message,
    (const char *dest, const char *sym, int n, t_atom *pd_args),
    convertArgs, (dest, sym, n, pd_args))
MAKE_CALLBACK(noteon, (int ch, int n, int v),
    Py_BuildValue, ("(iii)", ch, n, v))
MAKE_CALLBACK(controlchange, (int ch, int c, int v),
    Py_BuildValue, ("(iii)", ch, c, v))
MAKE_CALLBACK(programchange, (int ch, int pgm),
    Py_BuildValue, ("(ii)", ch, pgm))
MAKE_CALLBACK(pitchbend, (int ch, int bend),
    Py_BuildValue, ("(ii)", ch, bend))
MAKE_CALLBACK(aftertouch, (int ch, int v),
    Py_BuildValue, ("(ii)", ch, v))
MAKE_CALLBACK(polyaftertouch, (int ch, int n, int v),
    Py_BuildValue, ("(iii)", ch, n, v))
MAKE_CALLBACK(midibyte, (int p, int b),
    Py_BuildValue, ("(ii)", p, b))

void main() {

    #define ASSIGN_CALLBACK(s) libpd_set_##s##hook(pylibpd_##s);

    ASSIGN_CALLBACK(print)
    ASSIGN_CALLBACK(bang)
    ASSIGN_CALLBACK(float)
    ASSIGN_CALLBACK(symbol)
    ASSIGN_CALLBACK(list)
    ASSIGN_CALLBACK(message)

    ASSIGN_CALLBACK(noteon)
    ASSIGN_CALLBACK(controlchange)
    ASSIGN_CALLBACK(programchange)
    ASSIGN_CALLBACK(pitchbend)
    ASSIGN_CALLBACK(aftertouch)
    ASSIGN_CALLBACK(polyaftertouch)
    ASSIGN_CALLBACK(midibyte)

}
