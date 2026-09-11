# Differ pilot reproduction

For everyday matching, use the supported `snail match objdiff` command described
in the [objdiff workflow](../objdiff.md). The scripts here remain frozen with
their original receipt so the pilot can be reproduced independently.

The [decision and measured results](../differ-pilot-20260911.md) describe what is
adopted. `receipt.json` preserves the completed run's hashes, scores, controls,
and mapping evaluations. Generated objects, external tools, original analysis
exports, and full per-instruction diffs stay under ignored `artifacts/`.

## Stage objdiff and optionally asm-differ

Run from the repository root. No project dependencies or global installations
are required. The runner checks these hashes before loading either tool:

| Input | Pin | SHA-256 |
|---|---|---|
| objdiff CLI, macOS arm64 | 3.8.1 | `98f8275c27900c4fe2248fce3af37617658be49648fa7dbb5b376371f046dfdb` |
| asm-differ `diff.py` | `0dd09af8f8008f1f880327cf0aca3b26d2562ea2` | `10b8b1f21fba9ffe4294ecf21dc67d14a41473d9ec3ebf0bb60a6d50955d3873` |

```sh
mkdir -p artifacts/differ-pilot/tools
curl -fL https://github.com/encounter/objdiff/releases/download/v3.8.1/objdiff-cli-macos-arm64 \
  -o artifacts/differ-pilot/tools/objdiff-cli
chmod +x artifacts/differ-pilot/tools/objdiff-cli
curl -fL https://raw.githubusercontent.com/simonlindholm/asm-differ/0dd09af8f8008f1f880327cf0aca3b26d2562ea2/diff.py \
  -o artifacts/differ-pilot/tools/diff.py
```

To reproduce the original objdiff-only pilot export:

```sh
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run tools/match/differ_pilot/compare.py \
  --scratch update_subgame --out artifacts/differ-pilot/new-snapshot

artifacts/differ-pilot/tools/objdiff-cli diff \
  -p artifacts/differ-pilot/new-snapshot -u update_subgame _pilot
```

Press `q` to exit the interactive CLI. Repeat `--scratch` to select multiple
functions. Omit it for the eight-function pilot sample. Every `--out` must be a
new directory. `objdiff.json` is a static snapshot configuration with both
build switches disabled; source changes require another export.

To reproduce the complete asm-differ comparison and reductions, use a temporary
uv environment and GNU i686 objdump (the pilot used 2.47.20260726):

```sh
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run \
  --with colorama==0.4.6 --with watchdog==6.0.0 \
  --with levenshtein==0.27.1 --with cxxfilt==0.3.0 \
  tools/match/differ_pilot/compare.py \
  --out artifacts/differ-pilot/new-full-run --asm-differ \
  --objdump /opt/homebrew/bin/i686-w64-mingw32-objdump
```

Per-tool errors remain in the report alongside successful objdiff results.
The two reduced parser failures do not involve synthetic symbol names. The
generated COFF files contain independently named reference placeholders and
saved field-restoration receipts; they are not original translation units or
native relink proofs. Do not use an external score to publish matching credit.

## Reproduce BinDiff's mapping benchmark

The benchmark requires local `windows.BinExport`, `wii.BinExport`, and
`android.BinExport` under `artifacts/differ-pilot/`. Export the exact binaries
listed in `analysis/ports/builds.json` using Binary Ninja's **BinExport** plugin.
The completed pilot used the already-open Windows/Wii databases and a temporary
in-memory load of Android ARMv7, all with BN 6.1.10626-dev Personal. That edition
supports the GUI export but not the integrated BinDiff provider or headless
plugin initialization. No annotations were imported and no databases saved.

Stage standalone BinDiff by **extracting**, not installing, the official package:

```sh
curl -fL https://github.com/google/bindiff/releases/download/v8/BinDiff8.dmg \
  -o artifacts/differ-pilot/tools/BinDiff8.dmg
mkdir -p /tmp/snail-bindiff-volume
hdiutil attach -readonly -nobrowse -mountpoint /tmp/snail-bindiff-volume \
  artifacts/differ-pilot/tools/BinDiff8.dmg
pkgutil --expand-full '/tmp/snail-bindiff-volume/Install BinDiff.pkg' \
  artifacts/differ-pilot/tools/bindiff-package
cp artifacts/differ-pilot/tools/bindiff-package/BinDiff.pkg/Payload/Applications/BinDiff/BinDiff.app/Contents/MacOS/bin/bindiff \
  artifacts/differ-pilot/tools/bindiff
hdiutil detach /tmp/snail-bindiff-volume
```

The runner requires CLI SHA-256
`e6ff9d1b491d2d3c1efba3d9d12217766ba7f08000a44aa917fbc3bf3868b09b`.
It supplies the checked-in default matching configuration explicitly.

Generate the protobuf binding from the pinned official schema (the pilot used
`protoc` 35.1 and Python protobuf 7.36.1):

```sh
curl -fL https://raw.githubusercontent.com/google/binexport/c4c5b5f1c2793b03e5adc6264f100ba597430a1b/binexport2.proto \
  -o artifacts/differ-pilot/tools/binexport2.proto
protoc --python_out=artifacts/differ-pilot/tools \
  --proto_path=artifacts/differ-pilot/tools \
  artifacts/differ-pilot/tools/binexport2.proto

UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run --with protobuf==7.36.1 \
  tools/match/differ_pilot/binexport_benchmark.py \
  --out artifacts/differ-pilot/new-bindiff-run
```

The runner checks the schema and CLI hashes, source binary hashes, every
exported instruction byte, Android symbol/address bias, and the blinded
self-control. It preserves original exports, removes call-graph names from
derived inputs, supplies real executable hashes, and compares assignments with
the existing verified crosswalk. Exporter/analyzer changes can alter the result
even with an identical BinDiff engine; those changes require a new receipt.

## Reccmp preflight

The isolated reccmp 0.1.7 trial used `reccmp-project create`, then
`reccmp-project detect --what recompiled --search-path rebuilt` from the created
project directory. `rebuilt/SnailMail_unwrapped.exe` was a byte-identical copy
of `artifacts/match/rtext-runtime-20260909/rtext-smoke.exe`, renamed only to
satisfy target filename discovery. Detection reported the absent adjacent PDB.
No comparison ran; this is recorded separately in `receipt.json`.

## Validate the local tooling

```sh
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run pytest \
  tests/test_differ_pilot.py tests/test_match_diagnostics.py
UV_CACHE_DIR=/private/tmp/snail-uv-cache uv run ruff check \
  tools/match/differ_pilot tests/test_differ_pilot.py
git diff --check
```
