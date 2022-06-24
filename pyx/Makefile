
# BREW_PORTAUDIO_STATIC="/usr/local/opt/portaudio/lib/libportaudio.a"

include libportaudio.mk

all:
	@python3 setup.py build_ext --inplace
	@rm -rf ./build ./cypd.c ./libpd.c

$(wildcard *.o):
	$(CC) -c $(PORTAUDIO_CFLAGS) $(PORTAUDIO_SOURCES)

$(PORTAUDIO_STATIC_LIB): 
	@ar rcs $(PORTAUDIO_STATIC_LIB) $(wildcard *.o)

portaudio: $(PORTAUDIO_STATIC_LIB)
	@rm *.o

cypd:
	@CYPD=1 python3 setup.py build_ext --inplace	
	@rm -rf ./build ./cypd.c

libpd:
	@LIBPD=1 python3 setup.py build_ext --inplace	
	@rm -rf ./build ./libpd.c

demo:
	@DEMO=1 python3 setup.py build_ext --inplace	
	@rm -rf ./build ./demo.c

audio_test:
	@echo "generating portaudio c implementation test"
	@gcc -o test_audio tests/test_audio.c ../libs/libpd.a \
		-framework CoreServices -framework CoreFoundation \
		-framework AudioUnit -framework AudioToolbox -framework CoreAudio \
		-I ../pure-data/src -I ../libpd_wrapper -I ../libpd_wrapper/util -lportaudio
	@echo "now run ./test_audio "


minim:
	@echo "generating minimal test"
	@gcc -o minim tests/minimal.c ../libs/libpd.a \
		-framework CoreServices -framework CoreFoundation \
		-framework AudioUnit -framework AudioToolbox -framework CoreAudio \
		-I ../pure-data/src -I ../libpd_wrapper -I ../libpd_wrapper/util -lportaudio
	@echo "now run ./minim"

.PHONY: test clean test_atom

test-libpd:
	@python3 ./tests/test_libpd_audio.py

test-cypd:
	@python3 ./tests/test_cypd_audio.py

test-atom:
	@python3 ./tests/test_atom.py

clean:
	@rm -f *.so
	@rm -f test_audio
	@rm -f minim
