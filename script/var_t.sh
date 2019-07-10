#!/bin/bash

project=""
tmp="/tmp/cpp-test/"
ide=""
tmp_remote="test"

#remote
ip=""
reader=""

#html file
html_ip="http://upload.cppreference.com"
html_dir="/mwiki/images/b/b2"
html_file="html_book_20190607.zip"
html_download="wget"

#env
export CC="clang-8"
export CXX="clang++-8"
export PATH="$PATH:${project}/script"

function start_ide()
{
	$ide "${tmp}/src" &
}
