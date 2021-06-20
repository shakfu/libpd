# Experimental Cython branch of libpd

## Objectives

- Provide an alternative to the swig-based pylibpd

- Builtin integration with `portaudio`

- Should be easy to use in ipython for scripting puredata

- Should perform without observable audio artifacts



## Requirements

- `portaudio` -- to be installed system-wide
  - on macOS: `brew install portaudio`
  - on debian-derived linux: 'apt install portaudio'


## Notes

- in `samples/c/pdtest_gui`, the makefile doesn't build, but using the following works:

```bash
gcc -I/usr/local/include/libpd -o pdtest_gui pdtest_gui.c -lpd

```


