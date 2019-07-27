#!/bin/bash

. var.sh

build="${tmp}/build"
test_src="${tmp}/src"
cmake_opt=""

if [ -e "$build" ]
then
  rm -rf "$build"
fi

if [ ${run} -eq 1 ]
then
  cmake_opt="-DRUN=\"ON\" -DRUN_HTML=\"${run_html}\" -DRUN_PDF=\"${run_pdf}\""
fi
if [ ${unit} -eq 1 ]
then
  cmake_opt="${cmake_opt} -DUNIT_TEST=\"ON\""
fi

mkdir "$build"
cd "$build"
cmake -DCMAKE_BUILD_TYPE="Debug" ${cmake_opt} $test_src
make
