#SYS_CPP_INCLUDE=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1
#SYS_C_INCLUDE=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
SYS_CPP_INCLUDE=/Library/Developer/CommandLineTools/usr/include/c++/v1
SYS_C_INCLUDE=/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include
PWD=$(shell pwd)

NAME=libpd
ALL_INCLUDES=all_includes.hpp
CPP_STANDARD=-std=c++14
CONFIG_FILE=config.txt
NAMESPACE_TO_BIND=pd
NAMESPACE_TO_SKIP=''

all: regen build

bind:
	@mkdir -p bind
	@binder \
		--root-module $(NAME) \
		--prefix $(PWD)/bind \
		--config=$(CONFIG_FILE) \
		--bind $(NAMESPACE_TO_BIND) \
		--skip $(NAMESPACE_TO_SKIP) \
		$(ALL_INCLUDES) \
		-- $(CPP_STANDARD) \
		-isystem $(SYS_C_INCLUDE) \
		-I/usr/local/include \
		-I$(SYS_C_INCLUDE) \
		-I$(SYS_CPP_INCLUDE) \
		-I$(PWD)/include \
		-I../pure-data/src \
		-I../libpd_wrapper \
		-I../libpd_wrapper/util \
		-DNDEBUG


.PHONY: build clean regen test

setup:
	python3 setup.py build_ext --inplace

cmake:
	echo "building via cmake"
	mkdir -p build
	cd build; cmake ..; make

build: setup


clean:
	@rm -rf bind build

regen: clean bind


