#!/bin/bash

. var.sh

echo "Press any key when remote device is ready"
read

scp ${tmp}/output/*.pdf "${ip}${reader}"
rm ${tmp}/output/*.pdf

echo -e "\nFile has been copied to remote device"
