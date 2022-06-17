# Experimental Cython branch of libpd

## Objectives

- Provide a cython-based 'more hackable' alternative to the swig-based pylibpd

- Builtin integration with `portaudio` or alternative (`miniaudio?`)

- Should be easy to use in ipython for scripting headless puredata

- Should perform without observable audio artifacts

  - `nogil` for audio processing functions

- Provide two implementations:

  - Functional implentation: essentially a module with functions

  - Object-Oriented implementation: a more 'pythonic' approach with classes


## Status

The `m_pd` api is made available to `cython` code via `pd.pxd`.

The `libpd` api is made available to `cython` code via `libpd.pxd`.

Currently, experimenting with two variations of pretty much the same codebase to make the `libpd` api accessible to python:

- `libpd.pyx` -- **functional api** -- `libpd` functions implemented in a python extension module

- `cypd.pyx` -- **object-oriented api** (should check out the cpp version for comparison)

Both variation can generate sound from a pd patch via an embedded use of the `portaudio` library which is a dependency of this implementation.


## Requirements

- `portaudio` -- to be installed system-wide
  - on macOS: `brew install portaudio`
  - on debian-derived linux: 'apt install portaudio'


## Notes

- In `samples/c/pdtest_gui`, the makefile doesn't build, but using the following works:

```bash
gcc -I/usr/local/include/libpd -o pdtest_gui pdtest_gui.c -lpd
```


