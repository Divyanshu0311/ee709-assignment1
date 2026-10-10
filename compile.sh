#!/bin/bash
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
[ -z "$1" ] && { echo "Usage: $0 file.cpp [args...]"; exit 1; }
SRC="$1"; shift
case "$SRC" in *.cpp) CC=g++; BASE="${SRC%.cpp}";; *) CC=gcc; BASE="${SRC%.c}";; esac
OUT="$(cd "$(dirname "$SRC")" && pwd)/$(basename "$BASE")"
$CC -o "$OUT" "$SRC" -I "$DIR/include" -L "$DIR/lib" -lbdd -lmem
echo "Built $OUT"
"$OUT" "$@"
