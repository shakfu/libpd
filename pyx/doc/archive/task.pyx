cdef extern from "task.h" nogil:
    int cplay(char* name, char* dir, int sample_rate, int blocksize, 
        int in_channels, int out_channels)


cpdef void task(char* cname, char* cdir, int sample_rate, int blocksize, int in_channels, int out_channels):
    with nogil:
        cplay(cname, cdir, sample_rate, blocksize, in_channels, out_channels)
