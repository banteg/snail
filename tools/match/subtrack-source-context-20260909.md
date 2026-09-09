# Partial level-loader improvement from adjacent source context

Compiling `cRSubTracks::Init(char*)` after its actual native predecessor,
`cRSubTracks::ImportSegment`, improves the unchanged loader from **88.12% to
88.64%**. Candidate instructions fall from **942 to 931** against 926 native
instructions; the 20-instruction exact prefix is preserved, and both
candidate-only diagnostic references disappear. All 183 native references are
clean. This remains partial and adds no exact-function or proof-grade-byte credit.

The registered `subtrack_copy_level_loader` group uses the standard
`msvc6.5 /O2 /G5 /W3` profile. The Windows/mobile crosswalk identifies both
functions with `Subtrack.o`, in adjacent native order at `0x447300` and
`0x447480`. No canonical C++ body or compiler binary changed.

| Control | Loader match | Candidate/native instructions | Prefix | References |
|---|---:|---:|---:|---|
| Registered order | 88.64% | 931/926 | 20 | 183 clean |
| Isolated | 88.12% | 942/926 | 20 | 183 clean, 2 unaudited |
| Reversed | 88.12% | 942/926 | 20 | 183 clean, 2 unaudited |
| Peer headers only | 88.12% | 942/926 | 20 | 183 clean, 2 unaudited |

The changed code shares an early unexpected-EOF diagnostic and epilogue with
the existing later diagnostic. Other operations retain their order and operands,
with branches adjusted around removed code. The compiler's internal mechanism
is not established.

The segment-copy peer remains normalized exact in all four controls: 125/125
instructions and five clean references. Its registered body spans all 379 native
bytes, with 359 non-relocation bytes identical and no unexplained bytes. The five
COFF relocation offsets are 1, 32, 63, 70 and 75. Positional reference identity
holds; the raw unrelocated body is not byte-identical because its addresses have
not been linked. The partial loader receives no full-body exactness grade.

The [receipt](subtrack-source-context-20260909.json) records all eight controls,
source and runner identities, status comparison and runtime results. The full
24-control run also preserves the two previously registered exact groups.

## Runtime and tool integration

The loader oracle now copies each physical compilation object once. For each
native control it makes only the selected dedicated function section removable
and changes that function's definition to an undefined external at the same raw
symbol index. It clears the removed section's COMDAT flag so VC6 LINK can accept
the external definition. Peer code sections, symbols and relocations are checked
unchanged; their linked bytes and resolved references are independently checked.
The native replacement's original body and references are verified after linking.
This transformation is confined to runtime controls and grants no matching credit.

All four executables agree on **224 level cases** using all 133 shipped segment
files and 53 shipped levels, plus one synthetic segment and three synthetic levels.
Two object seeds and both galaxy-metadata states are exercised. Whole catalog,
level and galaxy objects and event logs agree. The deliberate catalog corruption
changes exactly one byte in one region, with no collateral event-log difference.
Resource callbacks and file IO remain explicit harness seams; this is fixture
execution evidence, not a reconstructed game run.

Compilation and execution used Wibo `1.2.0-3-g08b7997`, SHA-256
`917017253dac31557825aecffb117fc0c96221271b5c812fac3f704407fd0cc7`.
The runner includes the PCH file-publication and address-reservation fixes;
the VC6 compiler binaries are unchanged. Scratch cache keys and dependency
fingerprints now include the actual selected runner, including `WIBO` overrides,
so replacing or switching runners invalidates stale compiled results and
experiment epochs.

Validation: **939 tests pass**, strict experiment/spec checks pass, and changed
code adds no Ruff findings. A fresh full native status run remains **595/662**,
with **137602/294937** proof-grade bytes; platform helpers remain **114/120**.
Of all 785 function rows, only the loader changes. Overall fuzzy progress is
88.44%; changed historical-evidence labels reflect the new runner dependency.

```sh
export WIBO=/Users/banteg/dev/banteg/crimson/tools/match/bin/wibo
uv run tools/match/probe_translation_unit_context.py --out artifacts/match/unit-controls.json
uv run tools/match/compare_loaders_native.py --runtime-library /Users/banteg/dev/banteg/crimson/tools/native/providers/build/vc6-sp6/vc98/lib/msvcrt.lib --include-synthetic --out artifacts/match/subtrack-source-context-runtime-20260909
uv run snail match status --check -j 8 --write tools/match/STATUS.md
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```
