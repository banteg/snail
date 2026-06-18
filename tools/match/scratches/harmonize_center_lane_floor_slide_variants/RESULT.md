# `harmonize_center_lane_floor_slide_variants` match result

## Score

| Metric | Result |
|---|---:|
| Match | **58.98%** |
| Target instructions | 226 |
| Candidate instructions | 225 |
| Common prefix | 9 / 226 |
| Masked operands | 20 clean, 0 unresolved, 4 mismatched |

The retained partial recovers the native `0x10` frame, saved-`this` prologue,
`0x40` transition flag register, row/lane loop skeleton, row-modulo gates, and
four direct promotion/reversion scans.

The remaining core mismatch is the cursor anchor. Native computes
`(lane + row * 8) * 0x54` as a byte offset from `this`, then reaches the current
cell at `+0x3bfac8`, the next-row cell at `+0x3bfd68`, and the previous-row cell
at `+0x3bf828`. The retained source uses a shared `TrackRowCell*` cursor instead,
which keeps the prologue and loop skeleton but shifts the body displacements.

## Rejected trials

- Initial pointer-walk source: VC6 turned the lane loop into a cell-pointer
  increment and missed the native row/lane skeleton. Score: 42.34%.
- Explicit byte-offset cursor: recovered native-looking body displacements, but
  changed the prologue/register allocation and caused row-modulo block
  reordering. Score: 32.37%.
