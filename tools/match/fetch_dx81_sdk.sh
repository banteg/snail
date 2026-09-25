#!/bin/sh
# Install the Microsoft DirectX 8.1 SDK headers into tools/match/sdk/dx81
# (gitignored). Snail Mail was built against this SDK: it calls
# Direct3DCreate8(220), D3D_SDK_VERSION for 8.1, and statically links D3DX8.
# include/rshell_prelude.h includes them by relative path. The SDK's own includes are
# quoted or standard VC6 headers, so they resolve beside each other.
# Usage: tools/match/fetch_dx81_sdk.sh
set -eu

MATCH_ROOT="$(cd "$(dirname "$0")" && pwd)"
DEST="$MATCH_ROOT/sdk/dx81"
URL="https://archive.org/download/dx81sdk_full/dx81sdk_full.exe"
SHA256="73f6791e0ae7f8a1d74f71d8ebe517a79c0cbf03fd344424696fd7a3816d2d02"

if [ -f "$DEST/d3d8.h" ]; then
    echo "DirectX 8.1 SDK headers already installed in $DEST"
    exit 0
fi
command -v 7z >/dev/null 2>&1 || { echo "error: 7z is required" >&2; exit 1; }

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT
curl -fsSL -o "$WORK/dx81sdk_full.exe" "$URL"
echo "$SHA256  $WORK/dx81sdk_full.exe" | shasum -a 256 -c -
7z x -y -o"$WORK" "$WORK/dx81sdk_full.exe" "DXF/DXSDK/include/*" >/dev/null
mkdir -p "$DEST"
cp -R "$WORK"/DXF/DXSDK/include/. "$DEST"/
echo "Installed $(ls "$DEST" | wc -l | tr -d ' ') headers into $DEST"
