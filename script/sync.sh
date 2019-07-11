#!/bin/bash

. var.sh

cd $project
branch=$( git branch | grep "\*" | sed 's/\*//g' )

cd ${tmp}/src
git push origin
echo -e "\n"

cd $project
git pull ${tmp_remote} $branch


