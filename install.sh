#!/usr/bin/env bash
set -euo pipefail

if [ -d ./src/ ]
then
    rm -rf ./src/
fi

git clone https://git.suckless.org/dwm ./src/
cd ./src/

for file in ../patches/*
do
    patch < $file
done

cp ../config.def.h .
make
sudo make install
