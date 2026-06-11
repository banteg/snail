#!/bin/sh
# Compile a scratch and diff it against the original image function.
# Usage: match.sh <scratch-dir> [extra snail match args...]
#
# A scratch dir contains:
#   scratch.cpp   candidate implementation
#   scratch.conf  shell vars: FUNCTION (required), COMPILER, CFLAGS, END, SYMBOL
set -eu

SCRATCH_DIR="$(cd "$1" && pwd)"
shift
MATCH_ROOT="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$MATCH_ROOT/../.." && pwd)"

COMPILER="msvc6.5"
CFLAGS="/O2 /G5 /W3"
END=""
SYMBOL=""
. "$SCRATCH_DIR/scratch.conf"

: "${FUNCTION:?scratch.conf must set FUNCTION}"
MATCH_ARGS=""
[ -n "$END" ] && MATCH_ARGS="$MATCH_ARGS --end $END"
[ -n "$SYMBOL" ] && MATCH_ARGS="$MATCH_ARGS --symbol $SYMBOL"

BUILD_DIR="$SCRATCH_DIR/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cp "$SCRATCH_DIR/scratch.cpp" .
# shellcheck disable=SC2086
MSVC_VER="$COMPILER" "$MATCH_ROOT/cl.sh" /c $CFLAGS scratch.cpp

cd "$REPO_ROOT"
# shellcheck disable=SC2086
exec uv run snail match diff "$BUILD_DIR/scratch.obj" "$FUNCTION" $MATCH_ARGS "$@"
