#!/bin/bash
sudo ./update.sh
./build.sh
echo .
echo "Starting..."
sudo ./dist/dotghost
