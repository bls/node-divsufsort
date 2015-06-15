#!/bin/bash -x

mkdir ~/build
cd ~/build
git clone https://github.com/y-256/libdivsufsort libdivsufsort
cd libdivsufsort
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX="/usr/local" ..
make && sudo make install

