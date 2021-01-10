gcc -o test_audio test_audio.c \
    ./portaudio/libportaudio.a ../libs/libpd.a \
    -framework CoreServices -framework CoreFoundation \
    -framework AudioUnit -framework AudioToolbox -framework CoreAudio \
    -I ./portaudio -I ../pure-data/src -I ../libpd_wrapper -I ../libpd_wrapper/util

./test_audio



