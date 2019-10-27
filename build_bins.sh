#!/bin/bash

if [ $# -lt 2 ]; then
   echo "Usage: $0 [raw image data file] [width]"
   exit 1
fi

if [ -f $1 ]; then
   raw=$1
else
   echo "Error: $1 is not a file"
   exit 1
fi

pal="$raw.pal"

if [ ! -f $pal ]; then
   echo "Error: $pal is not a file"
   exit 1
fi

./svgatilemap.exe TILEMAP.BIN $2 0000
./maketiles.exe $raw TILES.BIN $2 1000
./pal12bit.exe $pal PAL.BIN 1000
