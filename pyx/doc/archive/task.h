#include <unistd.h>
#include <stdio.h>

#include "../libpd_wrapper/z_libpd.h"
#include "portaudio.h"

int cplay(char* name, char* dir, int sample_rate, int blocksize, int in_channels, int out_channels);
