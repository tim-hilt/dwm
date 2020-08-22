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
    echo "$file"
    patch < "$file"
done

# Will activate focus on click, rather than on hover
sed -i '/\[EnterNotify\] = enternotify,/d' dwm.c
sed -i '/static void enternotify(XEvent \*e)\;/d' dwm.c

cp ../config.def.h .
make
sudo make install
