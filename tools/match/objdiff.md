# Objdiff snapshots

`snail match objdiff` exports one scratch as a static objdiff project. Use it to
inspect instruction alignment, branches, register changes, and named references.
The [pilot](differ-pilot-20260911.md) records the adoption decision and controls.

```sh
uv run snail match objdiff update_subgame --out artifacts/objdiff/subgame-1
```

Export requires the same compiler and inputs as `snail match scratch`; objdiff
itself is optional. Scratch paths, short directory names, and `--match-root`
work like the other matching commands. `--manifest` selects the function
manifest; `--image` must match its target SHA-256. `--json` prints the receipt.
Exit status 0 means export succeeded, including when the candidate has native
mismatches. Invalid inputs or export failures return 2.

Every `--out` must name a new directory. After changing source, export another
snapshot. Both objdiff build switches are disabled; the viewer does not rebuild
the scratch. Existing snapshots are never replaced.

## Open the project

The tested viewer is objdiff CLI 3.8.1. If it is already on PATH, run the command
printed by the exporter:

```sh
objdiff-cli diff -p artifacts/objdiff/subgame-1 -u update_subgame _snail_snapshot
```

Press `q` to exit. The pilot's staged macOS arm64 binary can be used directly:

```sh
artifacts/differ-pilot/tools/objdiff-cli diff \
  -p artifacts/objdiff/subgame-1 -u update_subgame _snail_snapshot
```

For a fresh setup, the [pilot reproduction guide](differ_pilot/README.md#stage-objdiff-and-optionally-asm-differ)
contains the download URL and pinned SHA-256. Only objdiff is needed for this
workflow. The export command downloads and launches no external tools.

## Saved evidence and limits

- `objdiff.json`, `target.obj`, and `candidate.obj`: the portable viewer project.
- `compiled.obj`: the original compiled candidate object, before display conversion.
- `target.bin` and `candidate.bin`: the unmodified function bytes.
- `target-refs.json` and `candidate-refs.json`: each converted field's original
  bytes, reference key, relocation type, alternatives, and explanation status.
- `native-diagnostics.json` and `native.diff`: native matcher results and audit.
- `receipt.json`: target/compiler-output identities, experiment epoch, exporter
  identity, byte-restoration checks, code-view boundaries, and hashes of all other
  snapshot files.

Display objects are generated single-function COFF containers. They preserve
literal bytes and represent masked operands using each side's independently
resolved reference keys. They do not reconstruct original translation units or
referenced data. Alternate reference keys are retained in the receipts but are
not merged for presentation, so even an accepted native match can show an
objdiff difference. A separate `_snail_data_and_padding` symbol bounds the main
code view before matcher-identified trailing jump tables and padding. Those
bytes remain intact in the object section and saved `.bin` files. Interior data
followed by more code is rejected because one shortened view would hide code.
Objdiff can still omit alignment bytes within the declared code boundary; the
native diagnostics and byte receipts retain them.

Export checks target identity and stable matching inputs, and verifies that
restoring every converted field exactly recovers its input bytes. Unknown keys,
unsupported fields (including masked inline jump-table data), or inconsistent
reference values abort export. Known but unexplained references remain visible
and are counted in the receipt; native audit failures remain in the diagnostics.

Objdiff's percentage is diagnostic. Native `snail match` scoring, reference
audits, encoded-byte checks, and relink evidence remain the acceptance criteria.
Export never updates `STATUS.md`, experiment logs, or published progress.

## Validation

The supported exporter was replayed on all eight pilot scratches with the pinned
objdiff 3.8.1 CLI. It reproduced all eight diagnostic scores, passed both
wrong-reference controls, and opened the mirror snapshot in the interactive
viewer. Subsequent use on `update_subgame` exposed trailing jump-table bytes
being decoded as instructions; the explicit code-boundary fix was replayed on
the same eight functions. The bounded viewer percentages can differ from the
original pilot percentages; native scoring is unchanged.

Unit and CLI checks cover field restoration and identity, invalid
references, wrong images, changing inputs, existing output preservation, partial
write cleanup, short-name resolution, and data boundaries:

```sh
uv run pytest tests/test_match_objdiff.py tests/test_differ_pilot.py \
  tests/test_match_diagnostics.py tests/test_match.py tests/test_match_directory.py
```
