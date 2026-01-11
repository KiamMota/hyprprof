#!/bin/bash

BASE_DIR="../build/my_hyprprof"

# cria diretório base
mkdir -p "$BASE_DIR"

# cria hyprprof.json se não existir
if [ ! -f "$BASE_DIR/hyprprof.json" ]; then
    echo '{}' > "$BASE_DIR/hyprprof.json"
fi

# cria estrutura de payload
mkdir -p \
  "$BASE_DIR/payload" \
  "$BASE_DIR/payload/bg" \
  "$BASE_DIR/payload/bar" \
  "$BASE_DIR/payload/hyprland"

