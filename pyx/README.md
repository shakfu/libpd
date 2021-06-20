# Experimental Cython branch of libpd



## Objectives

- Provide an alternative to the swig-based pylibpd

- Builtin integration with `portaudio` or alternaitve (`miniaudio?`)

- Should be easy to use in ipython for scripting headless puredata

- Should perform without observable audio artifacts

  - `nogil` for audio processing functions


## Status

The `libpd` api is made available to `cython` code via `libpd.pxd`.

Currently, we are experimenting with two variations of pretty much the same codebase to make the `libpd` api accessible to python:

- `libpd.pyx` -- **functional api** -- `libpd` functions implemented in a python extension module

- `pd.pyx` -- **object-oriented api** (should check out the cpp version for comparison)

Both variation can generate sound from a pd patch via an embedded use of the `portaudio` library which is a dependency of this implementation.


## Requirements

- `portaudio` -- to be installed system-wide
  - on macOS: `brew install portaudio`
  - on debian-derived linux: 'apt install portaudio'


## Notes

- in `samples/c/pdtest_gui`, the makefile doesn't build, but using the following works:

```bash
gcc -I/usr/local/include/libpd -o pdtest_gui pdtest_gui.c -lpd

```


