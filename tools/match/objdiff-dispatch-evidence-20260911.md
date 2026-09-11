# Objdiff-guided gameplay dispatch work

The first supported-viewer session narrowed `update_subgame` to its early
dispatch, scan setup, and first row-list insertion. An independent check verifies
**2,417 bytes** of its existing tail after auditing **72 reference fields**. The
enclosing **2,423-byte** span differs at one byte in a six-byte loop backedge.
This is evidence about the current partial function, not new matching credit.

Eleven source controls produce no improvement. Ten preserve the complete
candidate function bytes; one regresses. The canonical source remains
**80.51453073%, 1,033/1,034 instructions, prefix 9, 129 clean references**, with
the same 60-byte frame. No compiler, header, source, matcher, or progress change
is retained from those controls.

The [receipt](objdiff-dispatch-evidence-20260911.json) contains the baseline,
every control, all changed viewer rows, script/tool/recipe identities, the strict
positional reference audit, original region bytes, and decoded backedge.

## Viewer correction discovered during use

Objdiff was decoding the trailing native jump tables as x86 instructions in the
single display symbol. The exporter now adds a separate
`_snail_data_and_padding` symbol at the native matcher's code boundary. The full
bytes remain in the COFF section and `.bin` files. Interior data followed by code
is rejected so shortening the view cannot hide executable instructions.

The corrected `update_subgame` viewer score is **99.0765%**, versus **94.4381%**
in the original snapshot, with no native change. All eight pilot functions and
both wrong-reference controls pass the new exporter. Objdiff still trims a
one-byte alignment instruction before this function's tables; the native matcher
and the independent tail check retain it.

## Source controls

The Windows body loads `level_mode_arg` before publishing the rebuild selector,
then reloads that field for the level-build call. Seven combinations give the
three galaxy/challenge branches an explicit local backdrop snapshot with that
lifetime. All seven leave the complete function bytes unchanged.

The native state-one dispatcher also reads `level_mode` before publishing the
challenge configuration. Three variants capture that local before both config
loads, between them, or before the two stores. All three are byte-neutral.
A fourth combines the early mode snapshot with direct config-field assignments;
it regresses to **80.32396379%**, keeping 1,033 candidate instructions and all
129 references clean. None is promoted.

These two receipts extend the existing lifetime experiments with specific
native-observed reads. They do not establish that other source forms are
impossible. Both mutation recipes remain checked in beside the scratch, and
the source ledger records the complete seven- and four-variant sweeps.

## Encoded tail evidence

Offsets below are relative to native `update_subgame @ 0x438b90` or the candidate
function. The candidate tail is eight bytes earlier. Only the 72 independently
audited relocation fields are normalized; ordinary addressing bytes, SIB bytes,
internal branch encodings, and the final alignment byte remain compared.

| Native offsets | Candidate offsets | Evidence |
| --- | --- | --- |
| `[0x4ed, 0xce2)` | `[0x4e5, 0xcda)` | 2,037 encoded-equal bytes after reference audit |
| `[0xce2, 0xce8)` | `[0xcda, 0xce0)` | Six-byte backedge; one encoded byte differs |
| `[0xce8, 0xe64)` | `[0xce0, 0xe5c)` | 380 encoded-equal bytes after reference audit |

The backedge is `0f8ca6f7ffff` (`jl 0x48e`) in native code and `0f8cacf7ffff`
(`jl 0x48c`) in the candidate. Its displacement byte is reported as a residual,
not masked. The two equal regions include the previously certified 766-byte
ring region; their larger coverage is not newly recovered source.

The certificate checks current measurement identities, original snapshot hashes,
candidate compiler identity, exact positional instruction offsets, reference
operand kind/index/key agreement, and complete byte equality in both intervals.
It does not rely on objdiff's equality labels to grant encoded evidence.

## Remaining work map

The corrected viewer has 59 changed rows, all before native offset `0x4ed`.
They include symbolic-name differences accepted by the native reference audit;
59 is not a count of bad native instructions. The useful source regions are:

| Native offsets | Source region |
| --- | --- |
| `0x26..0x34` | Pause-state initialization and fade-step load scheduling |
| `0x123..0x248` | Challenge configuration and state-one dispatch registers |
| `0x26c..0x3ad` | Replay/pause gates and control-source registers |
| `0x42c..0x46e` | Scan-end store sharing |
| `0x494..0x4ed` | Row-address calculation and active-list head lifetime |

The recorded source probes address the second region. The later tail is now
covered by stricter evidence, while the early source lifetimes and the backedge
remain visible. Whole-function encoded equality remains false.

## Reproduction and validation

The replay requires the baseline source at the receipt's commit, the ordinary
VC6 matching inputs, and the staged pinned objdiff 3.8.1 macOS arm64 executable.
It creates a fresh baseline and eleven candidate snapshots, rechecks the
certificate, and writes a new report without promoting source or appending logs:

```sh
uv run tools/match/objdiff_dispatch_probe.py --out artifacts/objdiff/new-dispatch-run
```

The integrated exporter passes 232 focused matcher/CLI tests, Ruff, and whitespace
checks. The scratch's strict ledger and recipe check report zero errors. Existing
status and published progress need no regeneration because matching inputs are
unchanged.
