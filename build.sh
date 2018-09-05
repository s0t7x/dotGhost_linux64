#!/bin/sh
rm -rf dist
mkdir dist
cd dist
cmake ..
make
mv ./src/dotghost ./dotghost
rm -rf src CMakeFiles CMakeCache.txt Makefile
echo build done ./dist/dotGhost!
echo start with start.sh!