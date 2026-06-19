# `normalize_segment_glyph_for_track_flags` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 160 |
| Candidate instructions | 160 |
| Common prefix | 160 / 160 |
| Masked operands | 2 clean, 0 unresolved, 0 mismatched |

The retained source matches the native row-boundary guard, sparse glyph lookup,
case jump table, mirror cases, and branchless fallback character arithmetic for
`=`, `|`, `o`, and `$`.

Two table references were added to the shared manifest so the exact match is
audited instead of relying on anonymous masked displacements:

- `normalize_segment_glyph_for_track_flags_jump_table @ 0x437418`.
- `normalize_segment_glyph_for_track_flags_lookup_table @ 0x43744c`.

## Rejected shape

- A single common `result` return compiled to 47 candidate instructions and
  lost the native early-return layout. Score: 18.36%.
- The same early-return semantics with source cases in readable glyph order
  recovered the switch dispatch but not the physical case-body order. Score:
  36.19%.
- The physical case-body order before flipping the `=` / `|` `flags & 1`
  branches matched 157/160 instructions; the target returns `'.'` / `' '` first
  and falls through to the arithmetic ternary path.
