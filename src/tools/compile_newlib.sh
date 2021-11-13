#!/bin/bash

NEW_LIB_HOME=$(pwd)/newlib/build/../../newlib
mkdir newlib_build -p
cd newlib_build
# ../newlib-4.1.0/newlib/configure --prefix=$NEW_LIB_HOME --target=x86_64-none-elf --disable-multilib --disable-newlib-io-pos-args --disable-newlib-atexit-dynamic-alloc --disable-newlib-iconv --enable-newlib-nano-malloc --enable-newlib-nano-formatted-io --enable-target-optspace --disable-newlib-io-c99-formats --enable-newlib-reent-small --disable-newlib-reent-small CFLAGS='-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0'
../newlib-4.1.0/newlib/configure --prefix=$NEW_LIB_HOME --target=x86_64-none-elf --disable-multilib --disable-newlib-io-pos-args --disable-newlib-atexit-dynamic-alloc --disable-newlib-iconv --enable-newlib-nano-formatted-io --enable-target-optspace --disable-newlib-io-c99-formats --enable-newlib-reent-small --disable-newlib-reent-small CFLAGS='-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0'

make 2> error.log 1> process.log
make install
