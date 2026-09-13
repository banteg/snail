# cRSubTracks::Init(cRSubSegmentRaw**)

## 2026-09-14 complete encoded-body recovery

The caller-owned row count and direct glyph-row input now reproduce all
256 native body bytes, 92 instructions and six literal local branches.
There are no external reference fields to mask. The ordinary SIB difference
at byte 55 is resolved; normalized agreement remains 100%.
See the [source stages and independent proof](../../glyph-row-count-ownership-20260914.md).
Earlier normalization-based exactness statements below are historical.

`0x448060` is the authored raw-table overload from `Subtrack.o`, retained by
Android and iOS. It builds the shipped Start, Finish, Filler, and related
segments from 0x48-byte `cRSubSegmentRaw` records and their eight glyph rows.

- VC6 symbol: `?Init@cRSubTracks@@QAEXPAPAUcRSubSegmentRaw@@@Z`
- semantic-complete Windows result: 98.91%, 92/92 instructions
- residual: one equivalent indexed-address operand ordering
- live callers: world initialization and `cRSubGame::Init`

## 2026-08-15 proof-grade SIB closure

The remaining indexed address used the same DS-default `base + index` value
with the two scale-one SIB fields exchanged. The matcher now canonicalizes
that architecture-safe equivalence, making the recovered authored overload
exact at 100.00% (92/92, prefix 92). The scratch source is unchanged.
