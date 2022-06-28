# demo.pyx
"""
This cython file tests array access and conversion






"""

cimport pd
cimport libpd
cimport libportaudio

from libc.string cimport strcpy, strlen

from cpython cimport array
import array

import numpy as np
cimport numpy as np
np.import_array()

DEF N_TICKS = 1
DEF CHANNELS = 1
DEF BLOCKSIZE = 64
DEF BUFF_SIZE = N_TICKS * BLOCKSIZE * CHANNELS


# ----------------------------------------------------------------------------
# generic

def dump(float[:] view):
    for i in range(BUFF_SIZE):
        print(i, view[i])

cdef void zero(float[:] view):
    view[:] = 0.0
    # also
    # view[...] = 0.0

# cdef void zero(float *buf):
#     for i in range(BUFF_SIZE):
#         buf[i] = 0.0

# ----------------------------------------------------------------------------
# to test

cdef float inbuf[BUFF_SIZE]
cdef float outbuf[BUFF_SIZE]

# writing directly to c-buffer
zero(inbuf)
zero(outbuf)

# for i in range(BUFF_SIZE):
#     inbuf[i] = 0.0
#     outbuf[i] = 0.0

cdef int process_float(const float *in_buffer, float *out_buffer):
    for i in range(BUFF_SIZE):
        out_buffer[i] = in_buffer[i] + 5.1
    return 0

process_float(inbuf, outbuf)
xs = outbuf

assert(type(xs) == type(outbuf)) # now this is true


cdef float inbuf0[BUFF_SIZE]
cdef float outbuf0[BUFF_SIZE]

# writing directly to c-buffer
zero(inbuf0)
zero(outbuf0)

cdef int process_float0(float[:] in_buffer, float[:] out_buffer):
    for i in range(BUFF_SIZE):
        out_buffer[i] = in_buffer[i] + 4.1
    return 0

process_float0(inbuf0, outbuf0)
ys = outbuf0

# ----------------------------------------------------------------------------
# test regular c buffer interface

cdef float buf[BUFF_SIZE]
cdef float[:] buf_view = buf

# writing directly to c-buffer
for i in range(BUFF_SIZE):
    buf[i] = 0.0

for i in range(BUFF_SIZE):
    assert buf[i] == 0.0

# writing indirectly to c-buffer view
buf_view[:] = 1.0

for i in range(BUFF_SIZE):
    assert buf[i] == 1.0

dump_buf = lambda: dump(buf_view)

def process_buffer(float[:] in_buffer not None, float[:] out_buffer = None):
    if out_buffer is None:
        out_buffer[:] = in_buffer # full copy
        # also the below is valid
        #out_buffer = in_buffer.copy()
    cdef int i
    for i in range(out_buffer.size):
        out_buffer[i] += 1.5
    return out_buffer

# ----------------------------------------------------------------------------
# test python array.array buffer interface

cdef array.array arr = array.array('f', range(BUFF_SIZE))
cdef float[:] arr_view = arr

def cbuf_to_array():
    print('buf', type(buf))
    print('arr', type(arr))
    arr[:] = buf # TypeError: can only assign array (not "list") to array slice

def buf_view_to_array():
    print('buf_view', type(buf_view)) # <class 'demo._memoryviewslice'>
    print('arr', type(arr)) # <class 'array.array'>
    arr[:] = buf_view #TypeError: can only assign array (not "demo._memoryviewslice") to array slice

dump_arr = lambda: dump(arr_view)

def change_array():
    for i in range(BUFF_SIZE):
        arr[i] = buf[i]


# ----------------------------------------------------------------------------
# test numpy buffer interface

# narr = np.arange(BUFF_SIZE, dtype=np.dtype("f"))
narr = np.random.random(BUFF_SIZE).astype("f")
cdef float [:] narr_view = narr

dump_narr = lambda: dump(narr_view)


# ----------------------------------------------------------------------------
# test process function wrapping buffer interface
# 
# different ways of wrapping libpd.libpd_process_float

# cpdef process_float0(int ticks, float[:] in_buffer, float[:] out_buffer = None):
#     cdef float[BUFF_SIZE] inbuff
#     cdef float[BUFF_SIZE] outbuff
#     cdef int i
#     if out_buffer is None:
#         out_buffer = array.array('f', [0.0] * BUFF_SIZE)

#     for i in range(BUFF_SIZE):
#         inbuff[i] = in_buffer[i]
#         outbuff[i] = out_buffer[i]

#     libpd.libpd_process_float(ticks, <const float*>inbuff, <float*>outbuff)
#     return out_buffer


# def process_float1(int ticks, array.array in_buffer, array.array out_buffer = None):
#     cdef float[:] in_buffer_view = in_buffer
#     cdef float[:] out_buffer_view = out_buffer
#     if out_buffer is None:
#         out_buffer_view[:] = array.array('f', [0.0] * BUFF_SIZE)
#     cdef float[BUFF_SIZE] inbuff;
#     cdef float[BUFF_SIZE] outbuff;
#     cdef float[:] inbuff_view = inbuff
#     cdef float[:] outbuff_view = outbuff
#     inbuff_view[:] = in_buffer_view
#     outbuff_view[:] = out_buffer_view
#     libpd.libpd_process_float(ticks, <const float*>inbuff, <float*>outbuff)
#     return out_buffer

# def process_float2(int ticks, array.array in_buffer, array.array out_buffer = None):
#     cdef float[BUFF_SIZE] inbuff
#     cdef float[BUFF_SIZE] outbuff
#     cdef int i
#     if out_buffer is None:
#         out_buffer = array.array('f', [0.0] * BUFF_SIZE)

#     for i in range(BUFF_SIZE):
#         inbuff = in_buffer[i]
#         outbuff = out_buffer[i]

#     libpd.libpd_process_float(ticks, <const float*>inbuff, <float*>outbuff)
#     return out_buffer


# ----------------------------------------------------------------------------
# test cplay

cdef extern from "tests/task.h" nogil:
    int cplay(char* name, char* dir)


def play(name: str, dir: str):
    cdef char[512] filename
    cdef char[512] dirname

    strcpy(filename, name.encode('utf-8'))
    strcpy(dirname, dir.encode('utf-8'))

    with nogil:
        cplay(filename, dirname)






