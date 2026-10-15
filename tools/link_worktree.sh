#!/bin/sh
# Symlink the main checkout's untracked inputs into this git worktree.
#
# A new worktree has none of the gitignored inputs: the reference binaries and
# mobile builds under artifacts/, the VC6 compilers, the DirectX 8.1 SDK and
# the matcher's helper binaries. This links them from the main checkout.
# Outputs that tools write under artifacts/ by default stay local, so
# worktrees never overwrite each other's reports, packs or screenshots.
#
# Usage: tools/link_worktree.sh   (from anywhere inside the worktree)
# Re-running is safe: existing links are refreshed, real files are left alone.
set -eu

here="$(git rev-parse --show-toplevel)"
main="$(git worktree list --porcelain | sed -n '1s/^worktree //p')"
if [ "$here" = "$main" ]; then
    echo "this is the main checkout; run it from a linked worktree" >&2
    exit 1
fi

# artifacts/ entries that tools write to by default; each worktree keeps its own.
local_artifacts="decomp differ-pilot match ownership screenshots web"

link() {
    target="$main/$1"
    dest="$here/$1"
    [ -e "$target" ] || return 0
    if [ -L "$dest" ]; then
        rm "$dest"
    elif [ -e "$dest" ]; then
        echo "kept $1 (not a symlink)"
        return 0
    fi
    mkdir -p "$(dirname "$dest")"
    ln -s "$target" "$dest"
    echo "linked $1"
}

mkdir -p "$here/artifacts"
for entry in "$main"/artifacts/*; do
    [ -e "$entry" ] || continue
    name="$(basename "$entry")"
    case " $local_artifacts " in
        *" $name "*) continue ;;
    esac
    link "artifacts/$name"
done

link tools/match/compilers
link tools/match/sdk
for tool in "$main"/tools/match/bin/wibo* "$main"/tools/match/bin/objdiff-cli; do
    [ -e "$tool" ] && link "tools/match/bin/$(basename "$tool")"
done
