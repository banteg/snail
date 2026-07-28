# `harmonize_center_lane_floor_slide_variants` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 226 |
| Candidate instructions | 226 |
| Common prefix | 226 / 226 |
| Masked operands | 28 clean, 0 unresolved, 0 mismatched |

The exact source recovers authored `cRSubGame::SlideSmoothTrack()` as a direct
row/lane pass over the owned `cRSubLoc` runtime grid. Rows with phase 3 inspect
the same lane in the following row; rows with phase 5 inspect the preceding
row. The four floor/slide object-family scans and `0x40` transition flag writes
match exactly.

The closing source-shape change follows the Android/iOS bodies and indexes
`runtime_cells[row][lane]` directly. That lets VC6 retain the owning
`cRSubGame*` plus the flattened `(lane + row * 8) * 0x54` cursor, matching
the native current/next/previous displacements without synthetic dependencies.

## Rejected trials

- Initial pointer-walk source: VC6 turned the lane loop into a cell-pointer
  increment and missed the native row/lane skeleton. Score: 42.34%.
- Explicit byte-offset cursor: recovered native-looking body displacements, but
  changed the prologue/register allocation and caused row-modulo block
  reordering. Score: 32.37%.
- Typed `cell`/`next`/`previous` pointer aliases recovered the semantics but
  shifted the cursor to the current cell and remained at 58.98%.
