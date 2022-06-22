from setuptools import setup


setup(
    name="_libpd_cffi",
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["build.py:ffibuilder"],
    install_requires=["cffi>=1.0.0"],
)
