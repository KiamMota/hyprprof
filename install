#!/usr/bin/env bash
set -Eeuo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
BIN_NAME="hyprprof"
INSTALL_PATH="/usr/local/bin/$BIN_NAME"

CONFIG_DIR="$HOME/.config/hyprprof"
CONFIG_FILE="$CONFIG_DIR/profiles.json"

echo "[*] Building $BIN_NAME"

command -v cmake >/dev/null || { echo "cmake not found"; exit 1; }
command -v make  >/dev/null || { echo "make not found"; exit 1; }

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake ..
make -j"$(nproc)"

# Descobre o caminho real do binário
BIN_PATH=$(find . -type f -executable -name "$BIN_NAME" | head -n 1)

if [[ -z "$BIN_PATH" ]]; then
    echo "Binary was not generated"
    exit 1
fi


# Instala binário
echo "[*] Installing $BIN_PATH to $INSTALL_PATH"
sudo install -m 755 "$BIN_PATH" "$INSTALL_PATH"

