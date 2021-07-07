# Dev Notes


## Python String to Char with allocation

```c
SWIGINTERN PyObject *_wrap___libpd_add_symbol(PyObject *SWIGUNUSEDPARM(self), PyObject *args) {
  PyObject *resultobj = 0;
  char *arg1 = (char *) 0 ;
  int res1 ;
  char *buf1 = 0 ;
  int alloc1 = 0 ;
  PyObject *swig_obj[1] ;
  
  if (!args) SWIG_fail;
  swig_obj[0] = args;
  res1 = SWIG_AsCharPtrAndSize(swig_obj[0], &buf1, NULL, &alloc1);
  if (!SWIG_IsOK(res1)) {
    SWIG_exception_fail(SWIG_ArgError(res1), "in method '" "__libpd_add_symbol" "', argument " "1"" of type '" "char const *""'");
  }
  arg1 = (char *)(buf1);
  libpd_add_symbol((char const *)arg1);
  resultobj = SWIG_Py_Void();
  if (alloc1 == SWIG_NEWOBJ) free((char*)buf1);
  return resultobj;
fail:
  if (alloc1 == SWIG_NEWOBJ) free((char*)buf1);
  return NULL;
}



SWIGINTERN int
SWIG_AsCharPtrAndSize(PyObject *obj, char** cptr, size_t* psize, int *alloc)
{
#if PY_VERSION_HEX>=0x03000000
#if defined(SWIG_PYTHON_STRICT_BYTE_CHAR)
  if (PyBytes_Check(obj))
#else
  if (PyUnicode_Check(obj))
#endif
#else  
  if (PyString_Check(obj))
#endif
  {
    char *cstr; Py_ssize_t len;
    int ret = SWIG_OK;
#if PY_VERSION_HEX>=0x03000000
#if !defined(SWIG_PYTHON_STRICT_BYTE_CHAR)
    if (!alloc && cptr) {
        /* We can't allow converting without allocation, since the internal
           representation of string in Python 3 is UCS-2/UCS-4 but we require
           a UTF-8 representation.
           TODO(bhy) More detailed explanation */
        return SWIG_RuntimeError;
    }
    obj = PyUnicode_AsUTF8String(obj);
    if (!obj)
      return SWIG_TypeError;
    if (alloc)
      *alloc = SWIG_NEWOBJ;
#endif
    if (PyBytes_AsStringAndSize(obj, &cstr, &len) == -1)
      return SWIG_TypeError;
#else
    if (PyString_AsStringAndSize(obj, &cstr, &len) == -1)
      return SWIG_TypeError;
#endif
    if (cptr) {
      if (alloc) {
    if (*alloc == SWIG_NEWOBJ) {
      *cptr = (char *)memcpy(malloc((len + 1)*sizeof(char)), cstr, sizeof(char)*(len + 1));
      *alloc = SWIG_NEWOBJ;
    } else {
      *cptr = cstr;
      *alloc = SWIG_OLDOBJ;
    }
      } else {
#if PY_VERSION_HEX>=0x03000000
#if defined(SWIG_PYTHON_STRICT_BYTE_CHAR)
    *cptr = PyBytes_AsString(obj);
#else
    assert(0); /* Should never reach here with Unicode strings in Python 3 */
#endif
#else
    *cptr = SWIG_Python_str_AsChar(obj);
        if (!*cptr)
          ret = SWIG_TypeError;
#endif
      }
    }
    if (psize) *psize = len + 1;
#if PY_VERSION_HEX>=0x03000000 && !defined(SWIG_PYTHON_STRICT_BYTE_CHAR)
    Py_XDECREF(obj);
#endif
    return ret;
  } else {
#if defined(SWIG_PYTHON_2_UNICODE)
#if defined(SWIG_PYTHON_STRICT_BYTE_CHAR)
#error "Cannot use both SWIG_PYTHON_2_UNICODE and SWIG_PYTHON_STRICT_BYTE_CHAR at once"
#endif
#if PY_VERSION_HEX<0x03000000
    if (PyUnicode_Check(obj)) {
      char *cstr; Py_ssize_t len;
      if (!alloc && cptr) {
        return SWIG_RuntimeError;
      }
      obj = PyUnicode_AsUTF8String(obj);
      if (!obj)
        return SWIG_TypeError;
      if (PyString_AsStringAndSize(obj, &cstr, &len) != -1) {
        if (cptr) {
          if (alloc) *alloc = SWIG_NEWOBJ;
          *cptr = (char *)memcpy(malloc((len + 1)*sizeof(char)), cstr, sizeof(char)*(len + 1));
        }
        if (psize) *psize = len + 1;

        Py_XDECREF(obj);
        return SWIG_OK;
      } else {
        Py_XDECREF(obj);
      }
    }
#endif
#endif

```



## Pure Data Atoms

```c
#define ATOMS_ALLOCA(x, n) ((x) = (t_atom *)getbytes((n) * sizeof(t_atom)))
#define ATOMS_FREEA(x, n) (freebytes((x), (n) * sizeof(t_atom)))
```

used:

```c
t_atom *outv;
int outc = 100;

ATOMS_ALLOCA(outv, outc);
...
ATOMS_FREEA(outv, outc);

```

alternatively:

```c
t_atom* at = (t_atom*)malloc(ac * sizeof(t_atom));

```


```c
/* -------------------- atoms ----------------------------- */

#define SETSEMI(atom) ((atom)->a_type = A_SEMI, (atom)->a_w.w_index = 0)
#define SETCOMMA(atom) ((atom)->a_type = A_COMMA, (atom)->a_w.w_index = 0)
#define SETPOINTER(atom, gp) ((atom)->a_type = A_POINTER, \
    (atom)->a_w.w_gpointer = (gp))v
#define SETFLOAT(atom, f) ((atom)->a_type = A_FLOAT, (atom)->a_w.w_float = (f))
#define SETSYMBOL(atom, s) ((atom)->a_type = A_SYMBOL, \
    (atom)->a_w.w_symbol = (s))
#define SETDOLLAR(atom, n) ((atom)->a_type = A_DOLLAR, \
    (atom)->a_w.w_index = (n))
#define SETDOLLSYM(atom, s) ((atom)->a_type = A_DOLLSYM, \
    (atom)->a_w.w_symbol= (s))

EXTERN t_float atom_getfloat(const t_atom *a);
EXTERN t_int atom_getint(const t_atom *a);
EXTERN t_symbol *atom_getsymbol(const t_atom *a);
EXTERN t_symbol *atom_gensym(const t_atom *a);
EXTERN t_float atom_getfloatarg(int which, int argc, const t_atom *argv);
EXTERN t_int atom_getintarg(int which, int argc, const t_atom *argv);
EXTERN t_symbol *atom_getsymbolarg(int which, int argc, const t_atom *argv);

EXTERN void atom_string(const t_atom *a, char *buf, unsigned int bufsize);
```

also see:

- [allocation example](https://github.com/pure-data/pure-data/blob/master/src/x_text.c)
- [forum question](https://www.mail-archive.com/pd-dev@lists.iem.at/msg02689.html)




## Portaudio Notes

Steps to writing a PortAudio application using the callback technique:

1. Write a callback function that will be called by PortAudio when audio processing is needed.

2. Initialize the PA library and open a stream for audio I/O.

3. Start the stream. Your callback function will be now be called repeatedly by PA in the background.

4. In your callback you can read audio data from the inputBuffer and/or write data to the outputBuffer.

5. Stop the stream by returning 1 from your callback, or by calling a stop function.

6. Close the stream and terminate the library.
