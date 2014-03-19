#!/usr/bin/env sh

ROOTDIR=$(pwd)

mkdir opt

mkdir build
cd build
cmake $OPTIONS -DCMAKE_INSTALL_PREFIX=$ROOTDIR/opt ../src
make
make install
