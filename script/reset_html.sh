#!/bin/bash

. var.sh

if [ -e "${tmp}/reference" ]
then
  rm -rf "${tmp}/reference"
  rm -f "${tmp}/*.xml"
fi

${html_download} "${html_ip}${html_dir}/${html_file}" "${tmp}/"
unzip "${tmp}/${html_file}"
rm "${tmp}/${html_file}"
