# portaudio as a static convenience library

#########################################
##### Defaults & Paths #####
UNAME_S := $(shell uname -s)

PORTAUDIO := ../pure-data/portaudio/portaudio

PORTAUDIO_CFLAGS = -DNEWBUFFER \
    -I$(PORTAUDIO)/include \
    -I$(PORTAUDIO)/src/common

PORTAUDIO_CPPFLAGS += \
    -I$(PORTAUDIO)/include \
    -I$(PORTAUDIO)/src/common

PORTAUDIO_LDFLAGS = -lportaudio \
    -framework CoreAudio \
    -framework AudioToolbox \
    -framework AudioUnit \
    -framework CoreFoundation \
    -framework CoreServices

#########################################
##### Files, Binaries, & Libs #####

PORTAUDIO_STATIC_LIB = ../libs/libportaudio.a

PORTAUDIO_SOURCES = \
    $(PORTAUDIO)/src/common/pa_allocation.c \
    $(PORTAUDIO)/src/common/pa_converters.c \
    $(PORTAUDIO)/src/common/pa_cpuload.c \
    $(PORTAUDIO)/src/common/pa_debugprint.c \
    $(PORTAUDIO)/src/common/pa_dither.c \
    $(PORTAUDIO)/src/common/pa_front.c \
    $(PORTAUDIO)/src/common/pa_process.c \
    $(PORTAUDIO)/src/common/pa_ringbuffer.c \
    $(PORTAUDIO)/src/common/pa_stream.c \
    $(PORTAUDIO)/src/common/pa_trace.c

ifeq ($(UNAME_S),Linux)
PORTAUDIO_CPPFLAGS += -I$(PORTAUDIO)/src/os/unix
PORTAUDIO_SOURCES += \
    $(PORTAUDIO)/src/os/unix/pa_unix_hostapis.c \
    $(PORTAUDIO)/src/os/unix/pa_unix_util.c \
    $(PORTAUDIO)/src/hostapi/alsa/pa_linux_alsa.c
endif

ifeq ($(UNAME_S),Darwin)
PORTAUDIO_CFLAGS += -DPA_USE_COREAUDIO
PORTAUDIO_CPPFLAGS += -I$(PORTAUDIO)/src/os/unix
PORTAUDIO_SOURCES += \
    $(PORTAUDIO)/src/os/unix/pa_unix_hostapis.c \
    $(PORTAUDIO)/src/os/unix/pa_unix_util.c \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core.c \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core_blocking.c \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core_utilities.c
# required for PortAudio to build on newer versions of macOS as it
# disables deprecation warnings stopping the build
PORTAUDIO_CFLAGS += -Wno-error -Wno-deprecated
endif

# ifeq ($(OS),Windows_NT)
# PORTAUDIO_CFLAGS += -DPA_USE_WMME
# PORTAUDIO_CPPFLAGS += -I$(top_srcdir)/portaudio/portaudio/src/os/win
# PORTAUDIO_SOURCES += \
#     portaudio/src/os/win/pa_win_coinitialize.c \
#     portaudio/src/os/win/pa_win_hostapis.c \
#     portaudio/src/os/win/pa_win_util.c \
#     portaudio/src/os/win/pa_win_waveformat.c \
#     portaudio/src/hostapi/wmme/pa_win_wmme.c
# if ASIO
# PORTAUDIO_CFLAGS += -DPA_USE_ASIO
# if MINGW
# # hack for /asio/ASIOSDK/common/combase.h
# PORTAUDIO_CPPFLAGS += -DWINVER=0x0502 -D_WIN32_WINNT=0x0502
# endif
# PORTAUDIO_CPPFLAGS += \
#     -I$(top_srcdir)/asio/ASIOSDK/common -I$(top_srcdir)/asio/ASIOSDK/host \
# 	-I$(top_srcdir)/asio/ASIOSDK/host/pc
# PORTAUDIO_SOURCES += \
#     portaudio/src/hostapi/asio/iasiothiscallresolver.cpp \
#     portaudio/src/hostapi/asio/pa_asio.cpp
# endif
# endif


PORTAUDIO_OBJS = $(patsubst %.c, %.o, $(PORTAUDIO_SOURCES))

# empty var for headers list footer
empty =

# include the headers in the dist so you can build
# find portaudio -type file -name *.h | sort | awk '{print "   ", $1, "\\"}'; echo '     $(empty)'
PORTAUDIO_HEADERS = \
    $(PORTAUDIO)/include/pa_asio.h \
    $(PORTAUDIO)/include/pa_jack.h \
    $(PORTAUDIO)/include/pa_linux_alsa.h \
    $(PORTAUDIO)/include/pa_mac_core.h \
    $(PORTAUDIO)/include/pa_win_waveformat.h \
    $(PORTAUDIO)/include/pa_win_wmme.h \
    $(PORTAUDIO)/include/portaudio.h \
    $(PORTAUDIO)/src/common/pa_allocation.h \
    $(PORTAUDIO)/src/common/pa_converters.h \
    $(PORTAUDIO)/src/common/pa_cpuload.h \
    $(PORTAUDIO)/src/common/pa_debugprint.h \
    $(PORTAUDIO)/src/common/pa_dither.h \
    $(PORTAUDIO)/src/common/pa_endianness.h \
    $(PORTAUDIO)/src/common/pa_gitrevision.h \
    $(PORTAUDIO)/src/common/pa_hostapi.h \
    $(PORTAUDIO)/src/common/pa_memorybarrier.h \
    $(PORTAUDIO)/src/common/pa_process.h \
    $(PORTAUDIO)/src/common/pa_ringbuffer.h \
    $(PORTAUDIO)/src/common/pa_stream.h \
    $(PORTAUDIO)/src/common/pa_trace.h \
    $(PORTAUDIO)/src/common/pa_types.h \
    $(PORTAUDIO)/src/common/pa_util.h \
    $(PORTAUDIO)/src/hostapi/asio/iasiothiscallresolver.h \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core_blocking.h \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core_internal.h \
    $(PORTAUDIO)/src/hostapi/coreaudio/pa_mac_core_utilities.h \
    $(PORTAUDIO)/src/os/unix/pa_unix_util.h \
    $(PORTAUDIO)/src/os/win/pa_win_coinitialize.h \
     $(empty)
