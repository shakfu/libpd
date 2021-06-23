

cdef extern from "miniaudio.h":
    """
    #define MINIAUDIO_IMPLEMENTATION
    """
    ctypedef enum ma_device_type:
        ma_device_type_playback = 1
        ma_device_type_capture  = 2
        ma_device_type_playback = 3
        ma_device_type_loopback = 4
