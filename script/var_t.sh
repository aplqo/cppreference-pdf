#!/bin/bash

project=""
tmp="/tmp/cpp-test"
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

#ttf file
ttf_ip="http://en.cppreference.com"
ttf_dir="/"
readonly ttf_file="DejaVuSans-Bold.ttf  DejaVuSansMono-Bold.ttf  DejaVuSansMono.ttf  DejaVuSans.ttf"
ttf_download="wget"

#run setting
run_html="${tmp}/reference/en/c.html"
run_pdf="${tmp}/output/c.pdf"

#target setting
run="1"
unit="1"

#env
export CC="clang-8"
export CXX="clang++-8"
export PATH="$PATH:${project}/script"

function start_ide()
{
	$ide "${tmp}/src" &
}
