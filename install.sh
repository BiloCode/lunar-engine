#!/bin/bash
set -e

BASE_DIR="$(cd "$(dirname "$0")" && pwd)"
FOLDER_DIR="$BASE_DIR/libraries"

mkdir -p "$FOLDER_DIR"

# MRUBY
(
   cd "$FOLDER_DIR"
   if [ -d "mruby" ]; then
      rm -rf "mruby"
   fi
   git clone https://github.com/mruby/mruby.git
   cd mruby
   rake
)
