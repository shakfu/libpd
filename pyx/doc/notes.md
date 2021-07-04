# Dev Notes


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
