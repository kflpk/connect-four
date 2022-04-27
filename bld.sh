#!/bin/sh

cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./build/
cd build
make
