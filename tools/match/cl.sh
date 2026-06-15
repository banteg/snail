#!/bin/sh
# Run VC6 cl.exe under wibo. Compiler selected via MSVC_VER (default msvc6.5).
# Usage: cl.sh [cl args...]
set -eu

MATCH_ROOT="$(cd "$(dirname "$0")" && pwd)"
MSVC_VER="${MSVC_VER:-msvc6.5}"
MSVC_ROOT="$MATCH_ROOT/compilers/$MSVC_VER"
WIBO="${WIBO:-}"

if [ ! -f "$MSVC_ROOT/Bin/CL.EXE" ]; then
    echo "error: $MSVC_ROOT/Bin/CL.EXE not found; see tools/match/README.md for setup" >&2
    exit 1
fi

if [ -z "$WIBO" ]; then
    if [ -x "$MATCH_ROOT/bin/wibo" ]; then
        WIBO="$MATCH_ROOT/bin/wibo"
    elif command -v wibo >/dev/null 2>&1; then
        WIBO="wibo"
    else
        echo "error: wibo not found; install it, place it at tools/match/bin/wibo, or set WIBO=/path/to/wibo" >&2
        exit 1
    fi
elif [ "${WIBO#*/}" != "$WIBO" ]; then
    if [ ! -x "$WIBO" ]; then
        echo "error: WIBO=$WIBO is not executable" >&2
        exit 1
    fi
elif ! command -v "$WIBO" >/dev/null 2>&1; then
    echo "error: WIBO=$WIBO not found on PATH" >&2
    exit 1
fi

# wibo accepts Z:-prefixed host paths, so unix paths become Windows include paths.
INCLUDE="Z:$(echo "$MSVC_ROOT/Include" | tr '/' '\\');Z:$(echo "$MATCH_ROOT/include" | tr '/' '\\')"
export INCLUDE

exec "$WIBO" "$MSVC_ROOT/Bin/CL.EXE" /nologo "$@"
