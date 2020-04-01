#!/bin/sh

apt-get update -y
apt-get upgrade -y
apt-get install build-essential -y
apt-get install pkg-config -y

apt-get install libfltk-dev -y
apt-get install libwebkit2gtk-4.0-dev -y
apt-get install libboost-dev -y
apt-get install libgtk3.0-dev -y
apt-get install xorg-dev -y
apt-get install libx11-dev -y
apt-get install libcanberra-gtk-module -y
apt-get install libcurl4-openssl-dev -y

apt-get install g++ -y
apt-get install gdb -y
apt-get install git -y
apt-get install autoconf -y
apt-get install libglu1-mesa-dev -y
apt-get install libasound2-dev -y
apt-get install libxft-dev -y
