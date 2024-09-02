#!/usr/bin/sh
source ./EMSCRIPTEN_CONFIG
if test x"${MEMORY64}" = x"1"; then
    echo Build Lhasa: Using 64-bit prefix: ${PWD}/prefix64
    echo
    INSTALL_DIR=${PWD}/prefix64
else
    echo Build Lhasa: Using 32-bit prefix: ${PWD}/prefix
    echo
    INSTALL_DIR=${PWD}/prefix
fi
emcmake cmake -DMEMORY64=${MEMORY64} -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -S . -B lhbuild &&\
cd lhbuild/;\
emmake make LDFLAGS=-all-static -j16;\
cd ..