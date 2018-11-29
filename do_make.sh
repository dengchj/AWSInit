#!/bin/bash

cp /dist/UMStor-OS/build/lib/librados.so* /usr/lib64/
cp /dist/UMStor-OS/build/lib/librgw.so*  /usr/lib64/
mkdir /usr/include/rados
cp /dist/UMStor-OS/src/include/rados/*  /usr/include/rados/

cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_FSAL_RGW=ON ../src/
make -j16
make install
