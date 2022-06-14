from pylibpd import *
import array

def print_receive(*s):
  print('print_receive:', s)

def float_receive(*s):
  print('float_receive:', s)

def list_receive(*s):
  print('list_receive:', s)

def symbol_receive(*s):
  print('symbol_receive:', s)

def noteon_receive(*s):
  print('noteon_receive:', s)

libpd_set_print_callback(print_receive)
libpd_set_float_callback(float_receive)
libpd_set_list_callback(list_receive)
libpd_set_symbol_callback(symbol_receive)
libpd_set_noteon_callback(noteon_receive)

libpd_subscribe('eggs')

m = PdManager(1, 2, 44100, 1)
patch = libpd_open_patch('test.pd', '.')
print("$0: ", patch)

libpd_float('spam', 42)
libpd_symbol('spam', "don't panic")
libpd_list('spam', 'test', 1, 'foo', 2)

libpd_release()
