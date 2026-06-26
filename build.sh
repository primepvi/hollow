#!/bin/bash
# build.sh

CC=gcc
CFLAGS="-Wall -Wextra -g"
SRC="src/vm/vm.c"
OUT="build/hollow"

mkdir -p build

echo "[1/1] Compilling hvm..." 
$CC $CFLAGS $SRC src/main.c -o $OUT
echo "[1/1] Ok!"
