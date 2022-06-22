#!/usr/bin/env python3

import sys
from os.path import dirname

sys.path.insert(0, dirname(dirname(__file__)))


from _libpd_cffi import lib

lib.libpd_init()
p = lib.libpd_openfile(b"test.pd", b"tests/pd")
lib.libpd_closefile(p)
