#!/bin/bash

. var.sh

build="${tmp}/build"
test_src="${tmp}/src"

if [ -e "$build" ]
then
  rm -rf "$build"
fi

mkdir "$build"
cd "$build"
cmake -DCMAKE_BUILD_TYPE="Debug" -DUNIT_TEST="YES" $test_src
make
