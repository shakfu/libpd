import os
from distutils.core import setup
from distutils.extension import Extension

from Cython.Build import cythonize

os.environ['LDFLAGS'] = " ".join([
        "-framework CoreServices",
        "-framework CoreFoundation",
        "-framework AudioUnit",
        "-framework AudioToolbox",
        "-framework CoreAudio",
])

extensions = [
    Extension("libpd", ["libpd.pyx"],
        define_macros = [
            ('PD', 1),
            ('HAVE_UNISTD_H', 1),
            ('HAVE_LIBDL', 1),
            ('USEAPI_DUMMY', 1),
            ('LIBPD_EXTRA', 1)
        ],
        include_dirs=[
            "../libpd_wrapper",
            "../libpd_wrapper/util",
            "../pure-data/src",
        ],
        libraries = [
            'm',
            'dl',
            'pthread',
            'portaudio', # requires portaudio to be installed system-wide
        ],
        library_dirs=['../libs'],
        extra_objects=[
            '../libs/libpd.a',
        ],
    ),
]


setup(
    name="pd in cython",
    ext_modules=cythonize(extensions, 
        compiler_directives={
            'language_level' : '3',
            'embedsignature': True,
            # 'cdivision': True,      # use C division instead of Python
            # 'boundscheck': True,    # check arrays boundaries
            # 'wraparound': False,    # allow negative indexes to fetch the end of an array

        }),
)
