# `select_track_tile_edge_variants` match result

## Score

| Metric | Result |
|---|---:|
| Match | **94.55%** |
| Target instructions | 220 |
| Candidate instructions | 220 |
| Common prefix | 14 / 220 |
| Masked operands | 18 clean, 0 unresolved, 0 mismatched |

The retained partial recovers the native `0x8` frame, row/lane cursor at
`TrackRowCell +0x3c`, neighbor probes, switch jump table, `ebx = 0x8000`
edge-variant flag, and all four variant-bank cases.

The first remaining mismatch is scheduling:

```text
target[14]    mov byte [esi+0x1], 0x0
candidate[14] mov edx, dword [esi+0x4]
```

VC6 schedules the independent lane-flag and tile-byte loads before the
`tile_flags_3d` clear in the candidate. Similar independent scheduling remains
inside each switch case around `lane_and_flags |= 0x8000` and the tile-id reload.
No fake dependency, volatile access, or shim was retained to force the exact
order.

## Rejected shape

- Keeping one tile-id local live across the neighbor probes and switch body made
  VC6 cache it in `bl`, preventing the native `ebx = 0x8000` flag register.
  Score: 50.59%.
