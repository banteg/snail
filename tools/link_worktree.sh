#!/bin/sh
# Symlink the main checkout's untracked inputs into this git worktree.
#
# A new worktree has none of the gitignored inputs: the reference binaries and
# mobile builds under artifacts/, the VC6 compilers, the DirectX 8.1 SDK and
# the matcher's helper binaries. This links them from the main checkout.
# The bin/ and extracted/ asset trees contain both inputs and generated
# files. Seed private copies so unwrap, extras and extract stay local.
#
# Usage: tools/link_worktree.sh   (from anywhere inside the worktree)
# Re-running is safe: existing links are refreshed, real files are left alone.
set -eu

here="$(git rev-parse --show-toplevel)"
main="$(git worktree list --porcelain | sed -n '1s/^worktree //p')"
if [ "$here" -ef "$main" ]; then
    echo "this is the main checkout; run it from a linked worktree" >&2
    exit 1
fi

# Check every parent the script can write through before copying or unlinking
# anything. A symlink here could otherwise make a destination the input itself.
for parent in artifacts tools tools/match tools/match/bin; do
    dest="$here/$parent"
    if [ -L "$dest" ] || { [ -e "$dest" ] && [ ! -d "$dest" ]; }; then
        echo "expected a local worktree directory at $dest; move it aside first" >&2
        exit 1
    fi
done

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

# Migrate the whole-directory links made by earlier versions. Copy through
# source symlinks too: a generated .dat must have independent storage.
seed_asset_tree() {
    target="$main/artifacts/$1"
    dest="$here/artifacts/$1"
    [ -d "$target" ] || return 0
    if [ -L "$dest" ]; then
        if [ "$(readlink "$dest")" != "$target" ]; then
            echo "unexpected symlink at $dest; move it aside first" >&2
            exit 1
        fi
    elif [ -e "$dest" ]; then
        return 0
    fi
    staging=$(mktemp -d "$here/artifacts/.seed-$1.XXXXXXXX")
    trap 'rm -rf "$staging"' EXIT
    cp -RLp "$target" "$staging/tree"
    if [ -L "$dest" ]; then unlink "$dest"; fi
    mv "$staging/tree" "$dest"
    rmdir "$staging"
    trap - EXIT
    echo "copied artifacts/$1"
}

mkdir -p "$here/artifacts"
seed_asset_tree bin
seed_asset_tree extracted
for entry in "$main"/artifacts/*; do
    [ -e "$entry" ] || continue
    name="$(basename "$entry")"
    if [ "$entry" -ef "$main/artifacts" ]; then
        # Older runs could also leave this shortcut into every main output.
        dest="$here/artifacts/$name"
        if [ -L "$dest" ] && [ "$dest" -ef "$main/artifacts" ]; then unlink "$dest"; fi
        continue
    fi
    case " bin extracted $local_artifacts " in
        *" $name "*) continue ;;
    esac
    link "artifacts/$name"
done

link tools/match/compilers
link tools/match/sdk
for tool in "$main"/tools/match/bin/wibo* "$main"/tools/match/bin/objdiff-cli; do
    if [ -e "$tool" ]; then link "tools/match/bin/$(basename "$tool")"; fi
done
