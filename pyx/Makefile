
# BREW_PORTAUDIO_STATIC="/usr/local/opt/portaudio/lib/libportaudio.a"

all: pd

pd:
	@python3 setup.py build_ext --inplace	
	@rm -rf ./build ./pd.c


libpd:
	@python3 setup_libpd.py build_ext --inplace	
	@rm -rf ./build ./libpd.c	

audio_test:
	@gcc -o test_audio tests/test_audio.c ../libs/libpd.a \
	-framework CoreServices -framework CoreFoundation \
	-framework AudioUnit -framework AudioToolbox -framework CoreAudio \
	-I ../pure-data/src -I ../libpd_wrapper -I ../libpd_wrapper/util -lportaudio

.PHONY: test clean


test:
	@python3 ./tests/test_pd_play.py

clean:
	@rm -f *.so
	@rm -f test_audio
