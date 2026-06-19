#!/bin/sh
# Compile a scratch through match.sh, but run the Python CLI under Python 3.13.
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
export UV_PYTHON="${UV_PYTHON:-3.13}"
exec "$SCRIPT_DIR/match.sh" "$@"
