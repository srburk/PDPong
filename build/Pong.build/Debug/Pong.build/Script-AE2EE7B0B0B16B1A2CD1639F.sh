#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E copy /Users/srburk/Developer/Playdate\ Projects/Pong/build/Debug/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/Source/pdex.dylib
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E touch /Users/srburk/Developer/Playdate\ Projects/Pong/Source/pdex.bin
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /Users/srburk/Developer/PlaydateSDK/bin/pdc -sdkpath /Users/srburk/Developer/PlaydateSDK /Users/srburk/Developer/Playdate\ Projects/Pong/Source /Users/srburk/Developer/Playdate\ Projects/Pong/Pong.pdx
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E cmake_symlink_library /Users/srburk/Developer/Playdate\ Projects/Pong/build/Debug/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/build/Debug/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/build/Debug/libPong.dylib
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E copy /Users/srburk/Developer/Playdate\ Projects/Pong/build/Release/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/Source/pdex.dylib
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E touch /Users/srburk/Developer/Playdate\ Projects/Pong/Source/pdex.bin
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /Users/srburk/Developer/PlaydateSDK/bin/pdc -sdkpath /Users/srburk/Developer/PlaydateSDK /Users/srburk/Developer/Playdate\ Projects/Pong/Source /Users/srburk/Developer/Playdate\ Projects/Pong/Pong.pdx
  cd "/Users/srburk/Developer/Playdate Projects/Pong/build"
  /opt/homebrew/Cellar/cmake/3.23.1/bin/cmake -E cmake_symlink_library /Users/srburk/Developer/Playdate\ Projects/Pong/build/Release/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/build/Release/libPong.dylib /Users/srburk/Developer/Playdate\ Projects/Pong/build/Release/libPong.dylib
fi

