SYS_C_INCL=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
SYS_CPP_INCL=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1

generate_bindings() {
    rm -rf bind build
    mkdir -p bind

    binder \
        --root-module libpd \
        --prefix $PWD/bind \
        --config=config.txt \
        --bind pd \
        all_includes.hpp \
        -- -std=c++14 \
        -I$SYS_C_INCL -I$SYS_CPP_INCL -I$PWD/include \
        -I../pure-data/src -I../libpd_wrapper -I../libpd_wrapper/util \
        -DNDEBUG 
}



build_via_cmake() {
    echo "building via cmake"
    mkdir -p build
    cd build
    cmake ..
    make    
}


build_via_setup_py() {
    python3 setup.py build_ext --inplace
}


build() {
    # build_via_cmake
    build_via_setup_py
}

build
