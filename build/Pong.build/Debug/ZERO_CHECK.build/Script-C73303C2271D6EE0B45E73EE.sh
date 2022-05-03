#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  make -f /Users/srburk/Developer/Playdate\ Projects/Pong/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  make -f /Users/srburk/Developer/Playdate\ Projects/Pong/build/CMakeScripts/ReRunCMake.make
fi

