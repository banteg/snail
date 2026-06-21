# `normalize_segment_glyph_for_track_flags` recovery notes

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
`SubgameRuntime` for the mirror flag, runtime flags, and completion-row fields.
Focused Wibo remains exact at `100.00%`, `160/160` instructions, with `2` clean
masked operands.
