
# BREW_PORTAUDIO_STATIC="/usr/local/opt/portaudio/lib/libportaudio.a"

all:
	@python3 build.py
	@rm -rf _libpd_cffi.c _libpd_cffi.o



.PHONY: test clean test_atom

test-cffi:
	@python3 ./tests/test_libpd_audio.py


clean:
	@rm -f *.so
