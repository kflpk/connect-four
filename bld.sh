#!/bin/sh

if [ "$1" == "clean" ]; then
	cmake --build ./build --target clean
	echo "Build directory cleaned"
else
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./build/
	cmake --build ./build
fi
# cd build
# make
