#!/bin/bash

. var.sh

scripts="${project}/script"

#wait for ipad
echo "Press any key when remote device is ready"
read

if [ -e $tmp ]
then
	rm -rf $tmp
fi
mkdir $tmp
mkdir "${tmp}/output"
cd $tmp

reset_html.sh
reset_src.sh
reset_build.sh

start_ide
