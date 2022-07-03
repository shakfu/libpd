SYS_C_INCL=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
SYS_CPP_INCL=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1


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

#     --suppress-errors \


echo "building via cmake"
mkdir -p build
cd build
cmake ..
make

