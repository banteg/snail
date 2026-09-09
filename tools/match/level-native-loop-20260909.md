# Exact level loader from native loop structure and VC6 profile

`cRSubTracks::Init(char*)` at `0x447480` is now proof-grade exact:
**926/926 instructions**, the complete 926-instruction prefix, and **183 clean
positional references**. This adds one port-relevant function and all **3,039
body bytes**, taking the board from **595/662 to 596/662** and from
137,602 to 140,641 proof-grade bytes. The [receipt](level-native-loop-20260909.json)
contains the crossed controls, byte accounting, source identities, and runtime
comparison summary.

The segment loop is a normal `while (cursor < segments_end)` with the null-cursor
diagnostic and return inside the loop. Native tests the returned cursor, branches
directly back from the end comparison, and places the message-quote and premature-EOF
error returns after the loop. The previous guarded `do/while` with a compound
condition and a following EOF check produced a different control-flow layout.
The new source preserves both an empty segment range and the filename used by
the premature-EOF diagnostic.

Both members of the existing `subtrack_copy_level_loader` source group now use
`msvc6.0 /O2 /G5 /W3`. The unchanged copy method still precedes the loader in
their independently established `Subtrack.o` order. The native Rich header
motivates testing VC6 builds 8168 and 8447; the same exact result under both
profiles does not identify the original service pack.

| Source | Profile | Match | Instructions | Prefix |
| --- | --- | ---: | ---: | ---: |
| Previous loop | msvc6.5 | 88.64% | 931/926 | 20 |
| Native loop | msvc6.5 | 90.29% | 928/926 | 20 |
| Previous loop | msvc6.0 / msvc6.3 | 96.93% | 929/926 | 529 |
| Native loop | msvc6.0 / msvc6.3 | 100.00% | 926/926 | 926 |

Source context remains necessary. Isolated, reversed, and peer-header-only
controls reach 96.30%, while the registered order is exact. The copy method
remains exact in all four controls at 125/125 instructions and five references.
The complete 24-control source-group check preserves every other exact member.

All 3,039 loader bytes are accounted for: **2,307 non-relocation bytes are
identical**, and the other 732 bytes are the 183 four-byte COFF relocations.
Every audited reference has the same instruction index and byte offset.
There are no unexplained bytes or non-relocation mismatches. The raw unlinked
body is **not byte-identical**, because its addresses have not been relocated.
The copy method likewise preserves its complete 379-byte body and 359 identical
non-relocation bytes.

The runtime oracle accepts the supported VC6 profiles while retaining each
function's compiler, flags, dependency, object and linked-reference evidence.
All four executables agree on **224 level cases**, covering the 133 shipped
segments and 53 shipped levels plus synthetic fixtures. Complete catalog,
level, galaxy and event-log comparisons pass. The fault control changes exactly
one byte in one region. Resource and file IO callbacks remain explicit harness
seams; this executes the original routines in fixtures, not the complete game.

Validation: **939 tests pass**, Ruff passes, and strict experiment/spec checks
pass. Of all 785 function rows, only the loader's matching metrics change; its
copy peer changes only its displayed compiler profile. The strict check also
required refreshing two unrecorded recipe anchors and moving a pre-existing
Tip report outside the directory reserved for mutation recipes. No Tip source
or historical experiment receipt was changed.

```sh
export WIBO=/Users/banteg/dev/banteg/crimson/tools/match/bin/wibo
uv run tools/match/probe_translation_unit_context.py --out artifacts/match/level-native-loop-unit-controls-20260909.json
uv run tools/match/compare_loaders_native.py --runtime-library /Users/banteg/dev/banteg/crimson/tools/native/providers/build/vc6-sp6/vc98/lib/msvcrt.lib --include-synthetic --out artifacts/match/level-native-loop-runtime-20260909
uv run snail match status --check --write tools/match/STATUS.md
uv run snail match experiments --check --strict --check-specs
uv run pytest -q
```
