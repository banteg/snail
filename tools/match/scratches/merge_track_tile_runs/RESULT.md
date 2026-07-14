# `merge_track_tile_runs` match result

## Score

| Metric | Final |
|---|---:|
| Match | **21.78%** |
| Target instructions | 276 |
| Candidate instructions | 275 |
| Common prefix | 0 / 276 |
| Masked operands | 8 clean, 0 unresolved, 0 mismatched |

This is an early semantic baseline rather than a layout match. The function's
control flow is heavily cross-jumped in the native, while this source keeps the
three run families readable.

## Accepted Source Shape

- Seeds every runtime cell's `lane_and_flags` with the independent AI-enabled
  and uncached-body bits (`0x6000`).
- Recovers slide, floor, and worm-tunnel horizontal run scans over the eight
  lanes in each row.
- Uses the real run-width object tables:
  `g_game_base + run * 0x38 + 0x4477c`,
  `g_game_base + run * 0x38 + 0x44afc`, and
  `g_game_base + run * 0x38 + 0x445bc`.
- Clears continuation-cell render/contact bit `0x20` plus the AI-enabled and
  uncached-body bits.
- Handles empty/terminator tiles `0` and `0x23`, including the level-mode-2
  object replacement at `g_game_base + 0x44124`.

## Rejected Trials

- Walking raw `lane_and_flags` pointers from `+0x3bfb08` looked closer to the
  native disassembly, but it regressed to 18.83% and produced a real masked
  row-record-base mismatch. The typed `TrackRowCell*` walk is retained.
- Treating continuation cells as cache-family-swapped (`0x40`) gates was
  wrong; the native requires the uncached-body bit (`0x4000`) after the seed
  pass.
