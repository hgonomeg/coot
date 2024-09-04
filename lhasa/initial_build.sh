#!/bin/sh

if command -v greadlink > /dev/null 2>&1; then
    SOURCE_DIR=`dirname -- "$( greadlink -f -- "$0"; )"`
else
    SOURCE_DIR=`dirname -- "$( readlink -f -- "$0"; )"`
fi


if [ x`uname -s` = x"Darwin" ]; then
    NUMPROCS=`sysctl -n hw.ncpu`
else
    NUMPROCS=`nproc --all`
fi

source ./VERSIONS
source ./EMSCRIPTEN_CONFIG

if [ x"$1" = x"--64bit" ]; then
    MEMORY64=1
    shift
    MODULES=$*
elif [ x"$1" = x"--32bit" ]; then
    MEMORY64=0
    shift
    MODULES=$*
elif [ x"$1" = x"--clear" ]; then
    shift
    CLEAR_MODULES=$*
else
    MODULES=$*
fi

if test x"${MEMORY64}" = x"1"; then
    echo "#####################################################"
    echo "Building ** 64-bit ** (large memory) version of Lhasa"
    echo "#####################################################"
    echo
    LHASA_CMAKE_FLAGS="-sMEMORY64=1 -pthread"
    BUILD_DIR=${PWD}/build64
    INSTALL_DIR=${PWD}/prefix64
else
    echo "######################################"
    echo "Building ** 32-bit ** version of Lhasa"
    echo "######################################"
    echo
    LHASA_CMAKE_FLAGS="-pthread"
    BUILD_DIR=${PWD}/build
    INSTALL_DIR=${PWD}/prefix
fi

echo "Sources are in ${SOURCE_DIR}"
echo "Building in ${BUILD_DIR}"
echo "Installing in ${INSTALL_DIR}"

mkdir -p ${INSTALL_DIR}
mkdir -p ${BUILD_DIR}

if [ x"$CLEAR_MODULES" = x"" ]; then
    :
else
    for mod in $CLEAR_MODULES; do
        case $mod in
            boost) echo "Clear boost"
                rm -rf ${BUILD_DIR}/boost
                rm -rf ${INSTALL_DIR}/include/boost
                ;;
            rdkit) echo "Clear rdkit"
                rm -rf ${BUILD_DIR}/rdkit_build
                rm -rf ${INSTALL_DIR}/include/rdkit
                ;;
            gemmi) echo "Clear gemmi"
                rm -rf ${BUILD_DIR}/gemmi_build
                rm -rf ${INSTALL_DIR}/include/gemmi
                rm -rf ${INSTALL_DIR}/lib/libgemmi_cpp.a
                ;;
            sigcpp) echo "Clear sigc++"
                rm -rf ${BUILD_DIR}/libsigcplusplus_build
                rm -rf ${INSTALL_DIR}/include/sigc++-3.0
                rm -rf ${INSTALL_DIR}/lib/libsigc-3.0.a
                rm -rf ${INSTALL_DIR}/lib/sigc++-3.0
                rm -rf ${INSTALL_DIR}/lib/pkgconfig/sigc++-3.0.pc
                ;;
            graphene) echo "Clear graphene"
                rm -rf ${BUILD_DIR}/graphene_build
                rm -rf ${INSTALL_DIR}/include/graphene-1.0
                rm -rf ${INSTALL_DIR}/lib/libgraphene-1.0.a
                rm -rf ${INSTALL_DIR}/lib/graphene-1.0
                rm -rf ${INSTALL_DIR}/lib/pkgconfig/graphene-1.0.pc
                ;;
            maeparser) echo "Clear maeparser"
                rm -rf ${BUILD_DIR}/maeparser_build
                rm -rf ${INSTALL_DIR}/include/maeparser
                rm -rf ${INSTALL_DIR}/lib/libmaeparser.a
            ;;
            coordgen) echo "Clear coordgen"
                rm -rf ${BUILD_DIR}/coordgen_build
                rm -rf ${INSTALL_DIR}/include/coordgen
                rm -rf ${INSTALL_DIR}/lib/libcoordgen.a
            ;;
            *)  echo "Unknown module requested for clearing"
                echo "Modules are: sigcpp graphene gemmi rdkit boost maeparser coordgen"
               ;;
        esac
        done
    exit
fi

# Create an empty file silly.c and then compile it with USE_ZLIB and USE_LIBPNG to force emsdk to get zlib/png.
echo "Attempting to get emsdk zlib/png ports"
echo
echo "" > silly.c
emcc silly.c -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_FREETYPE=1 -pthread -sMEMORY64=1 -Wno-experimental
emcc silly.c -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_FREETYPE=1 -pthread
rm -f silly.c
rm -f a.out.js
rm -f a.out.wasm
rm -f a.out.worker.js

BUILD_BOOST=false
BUILD_RDKIT=false
BUILD_GRAPHENE=false
BUILD_LIBSIGCPP=false
BUILD_GEMMI=false
BUILD_MAEPARSER=false
BUILD_COORDGEN=false


if test -d ${INSTALL_DIR}/include/boost; then
    true
else
    BUILD_BOOST=true
fi

if test -d ${INSTALL_DIR}/include/rdkit; then
    true
else
    BUILD_RDKIT=true
fi

if test -d ${INSTALL_DIR}/include/graphene-1.0; then
    true
else
    BUILD_GRAPHENE=true
fi

if test -d ${INSTALL_DIR}/include/sigc++-3.0; then
    true
else
    BUILD_LIBSIGCPP=true
fi

if test -d ${INSTALL_DIR}/include/gemmi; then
    true
else
    BUILD_GEMMI=true
fi

if test -d ${INSTALL_DIR}/include/coordgen; then
    true
else
    BUILD_COORDGEN=true
fi

if test -d ${INSTALL_DIR}/include/maeparser; then
    true
else
    BUILD_MAEPARSER=true
fi

for mod in $MODULES; do
    case $mod in
       boost) echo "Force build boost"
       BUILD_BOOST=true
       ;;
       rdkit) echo "Force build rdkit"
       BUILD_RDKIT=true
       ;;
       gemmi) echo "Force build gemmi"
       BUILD_GEMMI=true
       ;;
       sigcpp) echo "Force build sigc++"
       BUILD_LIBSIGCPP=true
       ;;
       graphene) echo "Force build graphene"
       BUILD_GRAPHENE=true
       ;;
       maeparser) echo "Force build maeparser"
       BUILD_MAEPARSER=true
       ;;
       coordgen) echo "Force build coordgen"
       BUILD_COORDGEN=true
       ;;
    esac
done


echo "BUILD_BOOST     " $BUILD_BOOST
echo "BUILD_RDKIT     " $BUILD_RDKIT
echo "BUILD_GRAPHENE  " $BUILD_GRAPHENE
echo "BUILD_LIBSIGCPP " $BUILD_LIBSIGCPP
echo "BUILD_GEMMI     " $BUILD_GEMMI
echo "BUILD_MAEPARSER " $BUILD_MAEPARSER
echo "BUILD_COORDGEN  " $BUILD_COORDGEN

#Boost
#boost with cmake
if [ $BUILD_BOOST = true ]; then
    mkdir -p ${BUILD_DIR}/boost
    cd ${BUILD_DIR}/boost
    emcmake cmake -DCMAKE_C_FLAGS="${LHASA_CMAKE_FLAGS}" \
                  -DCMAKE_CXX_FLAGS="${LHASA_CMAKE_FLAGS}" \
                  -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} \
                  -DBUILD_SHARED_LIBS=OFF \
                  ${SOURCE_DIR}/checkout/boost-$boost_release \
                  -DBOOST_EXCLUDE_LIBRARIES="context;fiber;fiber_numa;asio;log;coroutine;cobalt;nowide"
    emmake make -j ${NUMPROCS}
    emmake make install
fi

BOOST_CMAKE_STUFF=`for i in ${INSTALL_DIR}/lib/cmake/boost*; do j=${i%-$boost_release}; k=${j#${INSTALL_DIR}/lib/cmake/boost_}; echo -Dboost_${k}_DIR=$i; done`

#Maeparser
if [ $BUILD_MAEPARSER = true ]; then
    mkdir -p ${BUILD_DIR}/maeparser_build
    cd ${BUILD_DIR}/maeparser_build
    emcmake cmake cmake -DCMAKE_EXE_LINKER_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DBoost_DIR=${INSTALL_DIR}/lib/cmake/Boost-$boost_release \
        -DBoost_INCLUDE_DIR=${INSTALL_DIR}/include \
        ${BOOST_CMAKE_STUFF} \
        -DBoost_USE_STATIC_LIBS=ON \
        -DBoost_USE_STATIC_RUNTIME=ON \
        -DMAEPARSER_BUILD_TESTS=OFF \
        -DMAEPARSER_BUILD_SHARED_LIBS=OFF \
        -DCMAKE_C_FLAGS="${LHASA_CMAKE_FLAGS}"\
        -DCMAKE_CXX_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ${SOURCE_DIR}/checkout/maeparser-$maeparser_release/
    emmake make -j ${NUMPROCS}
    emmake make install
fi

# Coordgen
if [ $BUILD_COORDGEN = true ]; then
    mkdir -p ${BUILD_DIR}/coordgen_build
    cd ${BUILD_DIR}/coordgen_build
    emcmake cmake cmake -DCMAKE_EXE_LINKER_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DBoost_DIR=${INSTALL_DIR}/lib/cmake/Boost-$boost_release \
        -DBoost_INCLUDE_DIR=${INSTALL_DIR}/include \
        ${BOOST_CMAKE_STUFF} \
        -DBoost_USE_STATIC_LIBS=ON \
        -DBoost_USE_STATIC_RUNTIME=ON \
        -DCOORDGEN_BUILD_SHARED_LIBS=OFF \
        -DCOORDGEN_BUILD_TESTS=OFF \
        -DCOORDGEN_BUILD_EXAMPLE=OFF \
        -DCOORDGEN_USE_MAEPARSER=ON \
        -DCOORDGEN_RIGOROUS_BUILD=OFF \
        -Dmaeparser_INCLUDE_DIRS=${INSTALL_DIR}/include \
        -Dmaeparser_LIBRARIES=${INSTALL_DIR}/lib \
        -Dmaeparser_DIR=${INSTALL_DIR} \
        -DCMAKE_C_FLAGS="${LHASA_CMAKE_FLAGS}"\
        -DCMAKE_CXX_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ${SOURCE_DIR}/checkout/coordgenlibs-$coordgen_release/
    emmake make -j ${NUMPROCS}
    emmake make install
fi

#RDKit
if [ $BUILD_RDKIT = true ]; then
    mkdir -p ${BUILD_DIR}/rdkit_build
    cd ${BUILD_DIR}/rdkit_build
    emcmake cmake -DBoost_DIR=${INSTALL_DIR}/lib/cmake/Boost-$boost_release \
                  ${BOOST_CMAKE_STUFF} \
                  -DRDK_BUILD_PYTHON_WRAPPERS=OFF \
                  -DRDK_INSTALL_STATIC_LIBS=ON \
                  -DRDK_INSTALL_INTREE=OFF \
                  -DRDK_BUILD_SLN_SUPPORT=OFF \
                  -DRDK_TEST_MMFF_COMPLIANCE=OFF \
                  -DRDK_BUILD_CPP_TESTS=OFF \
                  -DRDK_USE_BOOST_SERIALIZATION=ON \
                  -DRDK_BUILD_THREADSAFE_SSS=OFF \
                  -DBoost_INCLUDE_DIR=${INSTALL_DIR}/include \
                  -DBoost_USE_STATIC_LIBS=ON \
                  -DBoost_USE_STATIC_RUNTIME=ON \
                  -DBoost_DEBUG=TRUE \
                  -Dmaeparser_INCLUDE_DIRS=${INSTALL_DIR}/include \
                  -Dmaeparser_LIBRARIES=${INSTALL_DIR}/lib \
                  -Dmaeparser_DIR=${INSTALL_DIR} \
                  -Dcoordgen_INCLUDE_DIRS=${INSTALL_DIR}/include \
                  -Dcoordgen_LIBRARIES=${INSTALL_DIR}/lib \
                  -Dcoordgen_DIR=${INSTALL_DIR} \
                  -DCMAKE_CXX_FLAGS="${LHASA_CMAKE_FLAGS} -fwasm-exceptions -Wno-enum-constexpr-conversion -D_HAS_AUTO_PTR_ETC=0" \
                  -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ${SOURCE_DIR}/checkout/rdkit \
                  -DRDK_OPTIMIZE_POPCNT=OFF \
                  -DRDK_INSTALL_COMIC_FONTS=OFF \
                  -DCMAKE_C_FLAGS="${LHASA_CMAKE_FLAGS}" \
                  -DCMAKE_MODULE_PATH=${INSTALL_DIR}/lib/cmake
    emmake make -j ${NUMPROCS}
    emmake make install
fi


# Setup for meson
if [ $BUILD_LIBSIGCPP = true ] || [ $BUILD_GRAPHENE = true ]; then
    cd ${BUILD_DIR}


    export CHOST="wasm32-unknown-linux"
    export ax_cv_c_float_words_bigendian=no

    export MESON_CROSS="${BUILD_DIR}/emscripten-crossfile.meson"

    cat > "${BUILD_DIR}/emscripten-crossfile.meson" <<END
[binaries]
c = 'emcc'
cpp = 'em++'
ld = 'wasm-ld'
ar = 'emar'
ranlib = 'emranlib'
pkgconfig = ['emconfigure', 'pkg-config']

# https://docs.gtk.org/glib/cross-compiling.html#cross-properties
[properties]
growing_stack = true
have_c99_vsnprintf = true
have_c99_snprintf = true
have_unix98_printf = true

# Ensure that '-s PTHREAD_POOL_SIZE=*' is not injected into .pc files
[built-in options]
c_thread_count = 0
cpp_thread_count = 0

[host_machine]
system = 'emscripten'
cpu_family = 'wasm32'
cpu = 'wasm32'
endian = 'little'
END

    export EM_PKG_CONFIG_PATH=${INSTALL_DIR}/lib/pkgconfig/
    export PKG_CONFIG_PATH=${INSTALL_DIR}/lib/pkgconfig/
    export EM_PKG_CONFIG_LIBDIR=${INSTALL_DIR}/lib/
    export PKG_CONFIG_LIBDIR=${INSTALL_DIR}/lib/
fi

# Graphene
if [ $BUILD_GRAPHENE = true ]; then
    pushd ${SOURCE_DIR}/checkout/graphene-$graphene_release/
    CFLAGS="-s USE_PTHREADS $LHASA_CMAKE_FLAGS" LDFLAGS=" -lpthread $LHASA_CMAKE_FLAGS" meson setup ${BUILD_DIR}/graphene_build \
        --prefix=${INSTALL_DIR} \
        --cross-file=$MESON_CROSS \
        --default-library=static \
        --buildtype=release \
        -Dtests=false && \
        meson install -C ${BUILD_DIR}/graphene_build
        popd
fi

# Libsigc++
if [ $BUILD_LIBSIGCPP = true ]; then
    pushd ${SOURCE_DIR}/checkout/libsigcplusplus-$libsigcpp_release/
    meson setup ${BUILD_DIR}/libsigcplusplus_build \
        --prefix=${INSTALL_DIR} \
        --libdir=lib \
        --cross-file=$MESON_CROSS \
        --default-library=static \
        -Dc_link_args="-pthread $LHASA_CMAKE_FLAGS" \
        -Dcpp_link_args="-pthread $LHASA_CMAKE_FLAGS" \
        -Dcpp_args="-s USE_PTHREADS=1 $LHASA_CMAKE_FLAGS" \
        --buildtype=release \
        -Dbuild-tests=false && \
        meson install -C ${BUILD_DIR}/libsigcplusplus_build
        popd
    
fi

#gemmi
if [ $BUILD_GEMMI = true ]; then
    mkdir -p ${BUILD_DIR}/gemmi_build
    cd ${BUILD_DIR}/gemmi_build
    emcmake cmake -DCMAKE_EXE_LINKER_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DCMAKE_C_FLAGS="${LHASA_CMAKE_FLAGS}"\
        -DCMAKE_CXX_FLAGS="${LHASA_CMAKE_FLAGS}" \
        -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} ${SOURCE_DIR}/checkout/gemmi-$gemmi_release/
    emmake make -j ${NUMPROCS}
    emmake make install
fi
