#!/bin/bash

rm -rf libsatcam
rm -rf build
mkdir build
cd build
cmake ..
make
cd -

