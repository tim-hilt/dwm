#!/usr/bin/env bash
set -euo pipefail

if [ -d ./src/ ]; then
    rm -rf ./src/
fi

git clone https://git.suckless.org/dwm ./src/
cp config.def.h ./src/
cd ./src/
make
sudo make install
