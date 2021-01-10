cimport libpd as _pylibpd
cimport cpython


cdef extern from *:
    pass
#     int libpd_set_print_callback(cpython.PyObject *callback)
#     int libpd_set_bang_callback(cpython.PyObject *callback)
#     int libpd_set_float_callback(cpython.PyObject *callback)
#     int libpd_set_symbol_callback(cpython.PyObject *callback)
#     int libpd_set_list_callback(cpython.PyObject *callback)
#     int libpd_set_message_callback(cpython.PyObject *callback)

#     int libpd_set_noteon_callback(cpython.PyObject *callback)
#     int libpd_set_controlchange_callback(cpython.PyObject *callback)
#     int libpd_set_programchange_callback(cpython.PyObject *callback)
#     int libpd_set_pitchbend_callback(cpython.PyObject *callback)
#     int libpd_set_aftertouch_callback(cpython.PyObject *callback)
#     int libpd_set_polyaftertouch_callback(cpython.PyObject *callback)
#     int libpd_set_midibyte_callback(cpython.PyObject *callback)




def libpd_clear_search_path():
    return _pylibpd.libpd_clear_search_path()


def libpd_add_to_search_path(dir):
    return _pylibpd.libpd_add_to_search_path(dir)


def libpd_blocksize():
    return _pylibpd.libpd_blocksize()


def libpd_init_audio(inch, outch, srate):
    return _pylibpd.libpd_init_audio(inch, outch, srate)


# def libpd_process_raw(inb, outb):
#     return _pylibpd.libpd_process_raw(inb, outb)


# def libpd_process_float(ticks, inb, outb):
#     return _pylibpd.libpd_process_float(ticks, inb, outb)


# def libpd_process_short(ticks, inb, outb):
#     return _pylibpd.libpd_process_short(ticks, inb, outb)


# def libpd_process_double(ticks, inb, outb):
#     return _pylibpd.libpd_process_double(ticks, inb, outb)


# def libpd_arraysize(name):
#     return _pylibpd.libpd_arraysize(name)


# def libpd_read_array(outb, src, offset, n):
#     return _pylibpd.libpd_read_array(outb, src, offset, n)


# def libpd_write_array(dest, offset, inb, n):
#     return _pylibpd.libpd_write_array(dest, offset, inb, n)


def libpd_bang(dest):
    return _pylibpd.libpd_bang(dest)


def libpd_float(dest, val):
    return _pylibpd.libpd_float(dest, val)


def libpd_symbol(dest, sym):
    return _pylibpd.libpd_symbol(dest, sym)


def __libpd_start_message(arg1):
    return _pylibpd.libpd_start_message(arg1)


def __libpd_add_float(arg1):
    return _pylibpd.libpd_add_float(arg1)


def __libpd_add_symbol(arg1):
    return _pylibpd.libpd_add_symbol(arg1)


def __libpd_finish_list(arg1):
    return _pylibpd.libpd_finish_list(arg1)


def __libpd_finish_message(arg1, arg2):
    return _pylibpd.libpd_finish_message(arg1, arg2)


def libpd_exists(sym):
    return _pylibpd.libpd_exists(sym)


# def __libpd_bind(sym):
#     return _pylibpd.libpd_bind(sym)


# def __libpd_unbind(p):
#     return _pylibpd.libpd_unbind(p)


# cpdef void * __libpd_openfile(arg1, arg2):
#     return _pylibpd.libpd_openfile(arg1, arg2)


# def __libpd_closefile(void *arg1):
#     return _pylibpd.libpd_closefile(arg1)


# def __libpd_getdollarzero(void *arg1):
#     return _pylibpd.libpd_getdollarzero(arg1)


def libpd_noteon(ch, n, v):
    return _pylibpd.libpd_noteon(ch, n, v)


def libpd_controlchange(ch, n, v):
    return _pylibpd.libpd_controlchange(ch, n, v)


def libpd_programchange(ch, p):
    return _pylibpd.libpd_programchange(ch, p)


def libpd_pitchbend(ch, b):
    return _pylibpd.libpd_pitchbend(ch, b)


def libpd_aftertouch(ch, v):
    return _pylibpd.libpd_aftertouch(ch, v)


def libpd_polyaftertouch(ch, n, v):
    return _pylibpd.libpd_polyaftertouch(ch, n, v)


def libpd_midibyte(p, b):
    return _pylibpd.libpd_midibyte(p, b)


def libpd_sysex(p, b):
    return _pylibpd.libpd_sysex(p, b)


def libpd_sysrealtime(p, b):
    return _pylibpd.libpd_sysrealtime(p, b)


def libpd_set_print_callback(callback):
    return libpd_set_print_callback(callback)


def libpd_set_bang_callback(callback):
    return libpd_set_bang_callback(callback)


def libpd_set_float_callback(callback):
    return libpd_set_float_callback(callback)


def libpd_set_symbol_callback(callback):
    return libpd_set_symbol_callback(callback)


def libpd_set_list_callback(callback):
    return libpd_set_list_callback(callback)


def libpd_set_message_callback(callback):
    return libpd_set_message_callback(callback)


def libpd_set_noteon_callback(callback):
    return libpd_set_noteon_callback(callback)


def libpd_set_controlchange_callback(callback):
    return libpd_set_controlchange_callback(callback)


def libpd_set_programchange_callback(callback):
    return libpd_set_programchange_callback(callback)


def libpd_set_pitchbend_callback(callback):
    return libpd_set_pitchbend_callback(callback)


def libpd_set_aftertouch_callback(callback):
    return libpd_set_aftertouch_callback(callback)


def libpd_set_polyaftertouch_callback(callback):
    return libpd_set_polyaftertouch_callback(callback)


def libpd_set_midibyte_callback(callback):
    return libpd_set_midibyte_callback(callback)


# import array


# def __process_args(args):
#     if __libpd_start_message(len(args)): return -2
#     for arg in args:
#         if isinstance(arg, str):
#             __libpd_add_symbol(arg)
#         else:
#             if isinstance(arg, int) or isinstance(arg, float):
#                 __libpd_add_float(arg)
#             else:
#                 return -1
#     return 0


# def libpd_list(dest, *args):
#     return __process_args(args) or __libpd_finish_list(dest)


# def libpd_message(dest, sym, *args):
#     return __process_args(args) or __libpd_finish_message(dest, sym)


# __libpd_patches = {}


# def libpd_open_patch(patch, dir='.'):
#     ptr = __libpd_openfile(patch, dir)
#     if not ptr:
#         raise IOError("unable to open patch: %s/%s" % (dir, patch))
#     dz = __libpd_getdollarzero(ptr)
#     __libpd_patches[dz] = ptr
#     return dz


# def libpd_close_patch(dz):
#     __libpd_closefile(__libpd_patches[dz])
#     del __libpd_patches[dz]


# __libpd_subscriptions = {}


# def libpd_subscribe(sym):
#     if not __libpd_subscriptions.has_key(sym):
#         __libpd_subscriptions[sym] = __libpd_bind(sym)


# def libpd_unsubscribe(sym):
#     __libpd_unbind(__libpd_subscriptions[sym])
#     del __libpd_subscriptions[sym]


# def libpd_compute_audio(flag):
#     libpd_message('pd', 'dsp', flag)


# def libpd_release():
#     for p in __libpd_patches.values():
#         __libpd_closefile(p)
#     __libpd_patches.clear()
#     for p in __libpd_subscriptions.values():
#         __libpd_unbind(p)
#     __libpd_subscriptions.clear()


# class PdManager:
#     def __init__(self, inch, outch, srate, ticks):
#         self.__ticks = ticks
#         self.__outbuf = array.array('h', b'\x00\x00' * outch * libpd_blocksize())
#         libpd_compute_audio(1)
#         libpd_init_audio(inch, outch, srate)

#     def process(self, inbuf):
#         libpd_process_short(self.__ticks, inbuf, self.__outbuf)
#         return self.__outbuf
