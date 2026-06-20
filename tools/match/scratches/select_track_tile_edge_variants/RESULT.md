# `select_track_tile_edge_variants` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 220 |
| Candidate instructions | 220 |
| Common prefix | 220 / 220 |
| Masked operands | 18 clean, 0 unresolved, 0 mismatched |

The retained source recovers the native `0x8` frame, row/lane cursor at
`TrackRowCell +0x3c`, neighbor probes, switch jump table, `ebx = 0x8000`
edge-variant flag, and all four variant-bank cases exactly.

The final source-shape fix keeps byte/dword pointers for the tile flag byte and
`lane_and_flags` word while walking the `TrackRowCell +0x3c` tile-byte view.
That matches the decompiler's pointer-style view and gives VC6 the native store
order for both the per-cell flag clear and the four edge-variant case bodies.

## Rejected shape

- Keeping one tile-id local live across the neighbor probes and switch body made
  VC6 cache it in `bl`, preventing the native `ebx = 0x8000` flag register.
  Score: 50.59%.
