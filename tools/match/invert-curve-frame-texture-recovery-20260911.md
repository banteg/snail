# Invert curve, frame and texture recovery

`initialize_invert_path_template_pair @ 0x429250` improves from
**84.45552785% to 100% normalized agreement**: **600/600 instructions**, a
**600-instruction prefix**, the native **0x54 frame** and **35 clean references**.
The previous candidate had 603 instructions and a 120-instruction prefix.
The source-weighted gain is **340.7348 bytes**.

The [complete receipt](invert-curve-frame-texture-recovery-20260911.json)
preserves baseline and retained sources, native and candidate bytes, all
observations, full-source mutation plans and strict positional proof. Compiler
`msvc6.5`, flags `/O2 /G5 /W3`, shared headers, matcher and target extent are
unchanged. This is a normalized whole-function match; **encoded-body exactness
remains false** because of 13 equivalent SIB bytes.

## Recovered operations

The interior curve uses a physical `0xa8` sample cursor and a separate phase
counter. Primary metadata and identity initialization form one inline operation.
A second operation borrows the primary and secondary banks, builds the position
and basis, normalizes the forward vector, computes the cross product and copies
the transform. It consumes the derived floating-point Z coordinate. Every
retained formal argument is used; diagnostic unused-argument variants were not
retained.

Vertex construction now keeps complete ordinary and terminal vector expressions
inside their branches, with direct sample accesses and named vertex destinations.
Face UV assignment has its own winding dispatch after geometry and texture
assignment. The existing texture parity branches remain present.

The old scratch also contained a behavioral error: it passed arguments 5 and 6
to the strip builder. Native argument loads consume **argument 4 (`texture_a`)
for face 0** and **argument 5 (`texture_b`) for face 1**. The prologue allocates
`0x54`, saves four registers, and the texture call has two zero arguments already
pushed; accounting for that stack movement identifies these arguments without
relying on their old names. The exported Windows body independently names these
owners at `0x42998e`/`0x4299d7` and `0x429a47`/`0x429ad0`. Argument 6 remains unused.
This supersedes the incorrect texture ownership claim in the July 15 notes.

## Whole-function proof

All 600 normalized instructions match at identical offsets and sizes. All 35
reference-bearing instructions pass strict same-position operand kind, index
and identity checks. All 23 local branches have corresponding destinations
inside the body. The certificate compares **2,182 bytes** at native range
`[0x429250,0x429ad6)`; only ten terminal padding bytes at `[2182,2192)` are
excluded. No target range is unexplained.

After masking only audited external relocation fields, 13 ordinary addressing
bytes still differ. At body offsets **760, 770, 774, 870, 877, 881, 936, 951,
961, 968, 972, 1027 and 1043**, the SIB base and index are exchanged at scale
one. Every participating register uses the DS default segment; no EBP/ESP or
non-unit-scale equivalence is assumed. These are the existing matcher's bounded
normalizations, not new masking rules. The receipt retains both encodings and
all remaining bytes. No encoded-body or linked-exact credit is claimed.

## Bounded experiments

There are **148 forward observations**: 144 distinct successful sources and four
failed source-construction attempts. The active forward plan records the 144
successful sources. The failures are preserved separately: an initial shared-up
insertion targeted the mesh loop instead of the curve loop. The generator was
corrected afterward, but those four failures were not rerun or treated as valid
negative evidence.

The useful progression is coupled: transferred vertex construction reaches
87.0216%; separate UV dispatch alone regresses, but adding physical curve
traversal to that combination reaches 95.0083%. Correct texture routing reaches
95.6739%. Primary and frame operation boundaries reach 99.8333%, with only an
adjacent address-setup scheduling difference left. Passing the derived Z value
closes that difference. Cleanup and formatting preserve the same compiled body.

Nine retained-source controls establish the following bounded results:

| Reversal | Normalized agreement | Candidate instructions |
| --- | ---: | ---: |
| Old texture routing | 98.0000% | 600 |
| Old vertex operation | 94.5878% | 601 |
| Lateral temporary back to `double` | 100.0000% | 600 |
| UV writes inside geometry dispatch | 90.9091% | 599 |
| Inline primary initialization into the caller | 95.9201% | 601 |
| Inline frame operation into the caller | 95.9201% | 601 |
| Integer phase instead of derived Z argument | 99.8333% | 600 |
| Phase-counter loop bound | 90.8333% | 600 |
| Complete baseline | 84.4555% | 603 |

All nine controls retain 35 clean references. The complete reversal reproduces
the baseline code fingerprint. The neutral lateral control does not establish
the original scalar type. An initial malformed UV reversal accidentally moved
one UV block inside a texture parity arm; its source and result are preserved
as an invalid diagnostic, excluded from the formal controls, and the corrected
control is the one reported above. No finite sweep is treated as a compiler limit.

## Validation

All **1,104 tests** and **785 scratch checks** pass, with zero type findings and
no shared-declaration lint findings. The strict ledger contains **2,526 records**,
zero current errors and **14/14 runnable active specs**, with no stale active
specs. All 144 recorded forward and nine reverse sources reproduce their
independent fingerprints. Full public refresh, separate saved-evidence
validation and `git diff --check` pass. The receipt binds the canonical source
and COFF body to the public row and isolated proof.

Core normalized matches rise **606/662 to 607/662**; core fuzzy agreement rises
**94.06% to 94.17%**, and the rounded residual gap falls **12,380 to 12,040 bytes**.
Platform matches remain **113/120**. Public normalized totals rise from
**718 functions / 172,474 bytes** to **719 functions / 174,656 bytes**. Only
Invert changes its matching result; refreshed COFF container hashes also change
on recompilation. Encoded-body and linked credit remain unchanged. Measurement
identities and target spans are unchanged, with **2,182 newly matched native
code bytes and zero regressions**.
