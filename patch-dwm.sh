#!/bin/bash

# Initializing variables
notitle_url=https://dwm.suckless.org/patches/notitle/dwm-notitle-6.2.diff
notitle=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $notitle_url)
# centertitle_url=https://dwm.suckless.org/patches/centeredwindowname/dwm-centeredwindowname-20180909-6.2.diff
# centertitle=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $centertitle_url)
pertag_url=https://dwm.suckless.org/patches/pertag/dwm-pertag-20170513-ceac8c9.diff
pertag=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $pertag_url)
hidevacanttags_url=https://dwm.suckless.org/patches/hide_vacant_tags/dwm-hide_vacant_tags-6.2.diff
hidevacanttags=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $hidevacanttags_url)
focusonnetactive_url=https://dwm.suckless.org/patches/focusonnetactive/dwm-focusonnetactive-2017-12-24-3756f7f.diff
focusonnetactive=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $focusonnetactive_url)
systray_url=https://dwm.suckless.org/patches/systray/dwm-systray-20190208-cb3f58a.diff
systray=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $systray_url)
nomonocleborders_url=https://gist.githubusercontent.com/SebastianJarsve/497b2014774c849df0132d7118cbab65/raw/20321cb4ada4e15edb93ab988a27be310158cf41/dwm-nomonocleborders-20190607-cb3f58a.diff
nomonocleborders=$(awk 'BEGIN { FS = "/" } ; { print $NF }' <<< $nomonocleborders_url)

FORMAT_RED="\033[0;31m"
FORMAT_GREEN="\033[0;32m"
# FORMAT_BLUE="\033[44m"
FORMAT_NONE="\033[0m"

# Download patches to /tmp/
if test -f "/tmp/$notitle" ; then
    echo -e "$FORMAT_RED$notitle exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $notitle_url
fi

if test -f "/tmp/$pertag" ; then
    echo -e "$FORMAT_RED$pertag exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $pertag_url
fi

if test -f "/tmp/$hidevacanttags" ; then
    echo -e "$FORMAT_RED$hidevacanttags exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $hidevacanttags_url
fi

if test -f "/tmp/$focusonnetactive" ; then
    echo -e "$FORMAT_RED$focusonnetactive exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $focusonnetactive_url;
    
fi

if test -f "/tmp/$systray" ; then
    echo -e "$FORMAT_RED$systray exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $systray_url
    sed -i '1,15d' "/tmp/$systray"
fi

if test -f "/tmp/$nomonocleborders" ; then
    echo -e "$FORMAT_RED$nomonocleborders exists in file system! Continuing...$FORMAT_NONE";
else
    wget -v -P /tmp/ $nomonocleborders_url
fi

sed -i 's/borderpx  = 1/borderpx  = 3/' "/tmp/$systray"
sed -i 's/snap      = 32/snap      = 25/' "/tmp/$systray"

# Uninstall and remove current version of dwm
if [ -d ./src/ ]; then
    echo -e "\n${FORMAT_RED}Uninstalling dwm$FORMAT_NONE"
    cd /home/tim/git/dwm/src/
    sudo make uninstall
    cd ../
    rm -rf ./src/
fi

# Clone fresh
echo -e "\n${FORMAT_RED}Clone fresh dwm$FORMAT_NONE"
git clone --depth 1 https://git.suckless.org/dwm ./src/

# Remove fresh config.def.h and replace with own file
rm ./src/config.def.h
cp ./config.def.h ./src/

# Apply patches
cd ./src/
echo -e "\n${FORMAT_RED}[Patching] $systray$FORMAT_NONE"
patch < "/tmp/$systray"

echo -e "\n${FORMAT_RED}[Patching] $notitle$FORMAT_NONE"
patch < "/tmp/$notitle"

echo -e "\n${FORMAT_RED}[Patching] $pertag$FORMAT_NONE"
patch < "/tmp/$pertag"

echo -e "\n${FORMAT_RED}[Patching] $hidevacanttags$FORMAT_NONE"
patch < "/tmp/$hidevacanttags"

echo -e "\n${FORMAT_RED}[Patching] dwm-center.diff$FORMAT_NONE"
patch < ../patches/dwm-center.diff

echo -e "\n${FORMAT_RED}[Patching] $focusonnetactive$FORMAT_NONE"
patch < "/tmp/$focusonnetactive"

echo -e "\n${FORMAT_RED}[Patching] $nomonocleborders$FORMAT_NONE"
patch < "/tmp/$nomonocleborders"

# Apply Cleanup-patch, that handles the remaining stuff that didn't succeed
echo -e "\n${FORMAT_RED}[Patching] 20190916_dwm-cleanup.diff$FORMAT_NONE"
patch < ../patches/20190916_dwm-cleanup.diff
echo -e "\n${FORMAT_GREEN}Patching ends here!$FORMAT_NONE"

# Will activate focus on click, rather than on hover
sed -i '/\[EnterNotify\] = enternotify,/d' dwm.c
sed -i '/static void enternotify(XEvent \*e)\;/d' dwm.c

# Install new Version
echo -e "\n${FORMAT_GREEN}Installing new dwm$FORMAT_NONE"
sudo make clean install
