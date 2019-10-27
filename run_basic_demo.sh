#!/bin/bash

if [ -z "${X16EMU}" ]
then
   if [ -z "${X16EMU_HOME}" ]
   then
      X16EMU=../x16-emulator/x16emu
   else
      X16EMU=${X16EMU_HOME}/x16emu
   fi
else
   X16EMU=${X16EMU}
fi

if [ $# -lt 2 ]; then
   echo "Usage: $0 [raw image data file] [width]"
   exit 1
fi

if [ ! -f "maketiles.exe" ]; then
   ./build_tools.sh
fi

./build_bins.sh $1 $2
$X16EMU -bas svga.bas -run
