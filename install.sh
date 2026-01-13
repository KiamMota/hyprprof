#!/bin/bash
set -e  

cd "$(dirname "$0")/build"

cmake ..
make -j$(nproc)

sudo cp hyprprof /usr/local/bin/
sudo chmod +x /usr/local/bin/hyprprof

echo "hyprprof installed!"
