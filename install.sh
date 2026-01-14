#!/usr/bin/env bash
set -Eeuo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
BIN_NAME="hyprprof"
INSTALL_PATH="/usr/local/bin/$BIN_NAME"

echo "[*] Building $BIN_NAME"

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v make  >/dev/null || { echo "make not found"; exit 1; }

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake ..
make -j"$(nproc)"

if [[ ! -f "$BIN_NAME" ]]; then
  echo "Binary was not generated"
  exit 1
fi

echo "[*] Installing to $INSTALL_PATH"
sudo install -m 755 "$BIN_NAME" "$INSTALL_PATH"

echo "[✓] $BIN_NAME installed successfully"
