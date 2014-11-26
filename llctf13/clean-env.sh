#!/bin/bash
F="$1"
shift

ulimit -s unlimited

DIR=$(cd -P -- "$(dirname -- "$F")" && pwd -P)
FILE=$(basename -- "$F")
if [ "$DIR" != /home/nickolai/sp/talks/llctf13 ]; then
  echo "Warning: odd directory $DIR"
fi
exec env - PWD="$DIR" SHLVL=0 "$DIR/$FILE" "$@"
