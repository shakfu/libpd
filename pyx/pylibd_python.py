import array


def __process_args(args):
    if __libpd_start_message(len(args)):
        return -2
    for arg in args:
        if isinstance(arg, str):
            __libpd_add_symbol(arg)
        else:
            if isinstance(arg, int) or isinstance(arg, float):
                __libpd_add_float(arg)
            else:
                return -1
    return 0


def libpd_list(recv, *args):
    return __process_args(args) or __libpd_finish_list(recv)


def libpd_message(recv, symbol, *args):
    return __process_args(args) or __libpd_finish_message(recv, symbol)


__libpd_patches = {}


def libpd_open_patch(patchannel, dir="."):
    ptr = __libpd_openfile(patchannel, dir)
    if not ptr:
        raise IOError("unable to open patch: %s/%s" % (dir, patch))
    dz = __libpd_getdollarzero(ptr)
    __libpd_patches[dz] = ptr
    return dz


def libpd_close_patch(dz):
    __libpd_closefile(__libpd_patches[dz])
    del __libpd_patches[dz]


__libpd_subscriptions = {}


def libpd_subscribe(recv):
    if recv not in __libpd_subscriptions:
        __libpd_subscriptions[recv] = __libpd_bind(recv)


def libpd_unsubscribe(recv):
    __libpd_unbind(__libpd_subscriptions[recv])
    del __libpd_subscriptions[recv]


def libpd_compute_audio(flag):
    libpd_message("pd", "dsp", flag)


def libpd_release():
    for p in __libpd_patches.values():
        __libpd_closefile(p)
    __libpd_patches.clear()
    for p in __libpd_subscriptions.values():
        __libpd_unbind(p)
    __libpd_subscriptions.clear()


class PdManager:
    def __init__(self, inChannels, outChannels, sampleRate, ticks):
        self.__ticks = ticks
        self.__outbuf = array.array(
            "b", "\x00\x00".encode() * outChannels * libpd_blocksize()
        )
        libpd_compute_audio(1)
        libpd_init_audio(inChannels, outChannels, sampleRate)

    def process(self, inBuffer):
        libpd_process_short(self.__ticks, inBuffer, self.__outbuf)
        return self.__outbuf
