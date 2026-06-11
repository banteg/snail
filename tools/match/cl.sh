#!/bin/sh
# Run VC6 cl.exe under wine. Compiler selected via MSVC_VER (default msvc6.5).
# Usage: cl.sh [cl args...]
set -eu

MATCH_ROOT="$(cd "$(dirname "$0")" && pwd)"
MSVC_VER="${MSVC_VER:-msvc6.5}"
MSVC_ROOT="$MATCH_ROOT/compilers/$MSVC_VER"

if [ ! -f "$MSVC_ROOT/Bin/CL.EXE" ]; then
    echo "error: $MSVC_ROOT/Bin/CL.EXE not found; see tools/match/README.md for setup" >&2
    exit 1
fi

WINE="${WINE:-/Applications/Wine Stable.app/Contents/Resources/wine/bin/wine}"
export WINEPREFIX="${WINEPREFIX:-$HOME/.wine-snail}"
export WINEDEBUG="${WINEDEBUG:--all}"

# wine maps Z: to /, so unix paths become Z:-prefixed windows paths
INCLUDE="Z:$(echo "$MSVC_ROOT/Include" | tr '/' '\\');Z:$(echo "$MATCH_ROOT/include" | tr '/' '\\')"
export INCLUDE

exec "$WINE" "$MSVC_ROOT/Bin/CL.EXE" /nologo "$@"
