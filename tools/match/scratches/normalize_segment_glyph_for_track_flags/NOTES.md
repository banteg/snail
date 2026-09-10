# `normalize_segment_glyph_for_track_flags` recovery notes

## 2026-09-11 inline-table certification

The unchanged source now compares at **100%**, 210/210 code
instructions plus 52 bytes of explicitly compared jump-table data. All
2 reference audits are clean and positional. Encoded-body proof is
**exact**.
This is corrected table-data accounting, not newly reconstructed source code.

The [proof report](../../inline-jump-table-proof-20260911.md) and
[receipt](../../inline-jump-table-proof-20260911.json) preserve the full source,
compiled-object identity, data entries, reference audits, comparison ranges, and
encoded-body evidence. Earlier measurements below are historical.

Target: `normalize_segment_glyph_for_track_flags @ 0x437270` (`thiscall`, `ret 0xc`).

This helper normalizes authored segment glyphs against the active track feature
flags, row boundary, mirror state, and edge-row flag before runtime cells are
populated.

The exact source shape is a readable sparse glyph switch with early returns.
The first common-result form was too optimized by VC6.5 (`18.36%`, 47
candidate instructions). Rewriting each case as native-style returns restored
the sparse byte lookup and jump-table dispatch (`36.19%`, 155 candidate
instructions). Ordering the cases by the compiler's physical case-body order
recovered the full switch layout (`87.07%`, 157 candidate instructions), and
spelling the `=` / `|` feature-bit fallbacks as `flags & 1 == 0` early returns
matched the final three instructions.

Exact Wibo result: 100.00%, 160/160 instructions, full prefix, with two clean
masked table operands:

- `normalize_segment_glyph_for_track_flags_jump_table @ 0x437418`, 13 entries.
- `normalize_segment_glyph_for_track_flags_lookup_table @ 0x43744c`, 94 bytes
  for glyph indexes `0x20..0x7d`.

2026-06-21 subgame-header consolidation: the glyph normalizer now uses
`cRSubGame` for the mirror flag, runtime flags, and completion-row fields.
Focused Wibo remains exact at `100.00%`, `160/160` instructions, with `2` clean
masked operands.

## 2026-07-14 game-wide feature owner

All twelve feature tests now resolve through the shared
`SubgameRuntimeFlag` owner. The names describe only the glyph behavior this
exact helper proves, while the separate falling bit is also backed by the
player-floor consumer. The focused result remains exact at 100.00%, 160/160
instructions, full prefix, and two clean table operands.

## 2026-07-18 analyzer owner ABI

The exact member source, ECX data flow, and two native callsites prove the
analyzer ABI as `char __thiscall (cRSubGame*, char, int32_t, char)`.
The receiver reads the recovered `track_mirror_enabled` (+0x02),
`runtime_flags` (+0x4c), and `completion_row_start` (+0x58) fields. This
replaces Binary Ninja's residual `void*` receiver / `int32_t` return and IDA's
raw `sub_437270(int this, ...)` view without changing the exact matcher source.

## 2026-07-27 mobile-authored owner

Android preserves the exact authored symbol
`cRSubGame::LevelConvert(char, int, bool)`. Its `BuildLevel()` calls the method
on the active `cRSubGame` with the raw segment glyph, absolute build row, and
first-or-last edge-row byte, then dispatches the returned normalized glyph.
That is the same producer/callee/consumer chain as Windows
`populate_runtime_track_cells_from_segments`.

The later Android body extends the feature-policy switch, and iOS inlines that
policy into `BuildLevel()` rather than exporting a separate `LevelConvert`
body. The cross-port evidence therefore fixes the Windows owner and method ABI
without claiming byte-equivalent policy or transferring mobile field offsets.
The Windows matcher remains exact at 100.00%, 160/160 instructions, full
prefix, and two clean table operands.
