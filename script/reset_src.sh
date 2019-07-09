#!/bin/bash

. var.sh

if [ -e "${tmp}/src" ]
then
  rm -rf "${tmp}/src"
fi
if [ -e "${tmp}/remote" ]
then
	rm -rf "${tmp}/remote"
fi

cd $tmp
git clone --bare $project remote
git clone "${tmp}/remote" src
cd $project
t=$(git remote show | grep -x ${tmp_remote} )
if [ -z  $t]
then
	git remote add ${tmp_remote} "${tmp}/remote"
fi
