#!/bin/sh
# Compile and diff a scratch through the canonical Python matching pipeline.
# Usage: match.sh <scratch-dir> [extra snail match args...]
set -eu

SCRATCH_DIR="$(cd "$1" && pwd)"
shift
MATCH_ROOT="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$MATCH_ROOT/../.." && pwd)"

cd "$REPO_ROOT"
exec uv run snail match scratch "$SCRATCH_DIR" "$@"
