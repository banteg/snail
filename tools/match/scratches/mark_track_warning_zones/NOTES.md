# Source-shaped — 98.99%, 99/99 instructions

The recovered source now keeps the native `SubgameRuntime` receiver in `ecx`
and names the complete runtime-cell owner. The sole remaining byte drift is
the independent cell-cursor/saved-row reload order documented below; no
synthetic dependency is warranted. The pinned semantics are:

- seed tile set: {2..14, 23, 25, 33} (literal 16-way compare chain)
- stamp footprint per seed at (row, col): rows row..row-5, cols
  {col-1, col}, bounds-checked `r >= 0 && r < rows-1 && 0 <= col+dc < 8`
  as signed pairs
- effect: `cells[idx].lane_and_flags |= 0x18`
- cell bank: game + 0x3bfb04, stride 84 (0x54), tile byte +0x00,
  lane/flags dword +0x04, 8 cells per row, row-major contiguous walk
- relation to shared `TrackRowCell`: this cursor starts at the tile byte, so
  its `+0x00/+0x04` fields are `TrackRowCell +0x3c/+0x40`. The shared
  header now records the full 0x54 stride and names `+0x40` as
  `lane_and_flags`; this scratch keeps the tile-byte view because it preserves
  the current register/offset shape.

2026-06-13 pin audit: focused matcher still verifies 32.51%, 104/99 insns.
Keep pinned at semantics; the remaining work would be layout/register golf
around the nested footprint loops.

2026-06-16 row-lifetime correction: BN/native disassembly mutates the outer row
local while walking the six backward rows, then restores the saved outer row
after the footprint. The scratch now spells that directly instead of using an
independent `r` local. Focused Wibo improves to 36.27% (105/99 insns), but the
remaining diff is still broad register ownership: VC6 keeps `this` outside
`ecx` and strength-reduces the two-lane stamp. Adjacent exact
`is_neighbor_cell_solid` independently confirms the same `TrackRowCell`
`tile_id +0x3c` and `lane_and_flags +0x40` layout.

2026-06-20 shared-owner consolidation: `runtime_row_count` and the
`+0x3bfb04` tile-byte cursor now live in `SubgameRuntime`, matching the exact
`rebuild_track_runtime_from_segments` caller and the Android `cRSubGame`
symbol. Focused Wibo stays at 36.27%; an index-only scan and a do/while
lateral-offset loop both regressed, so the prior pointer scan remains.

2026-07-10 runtime-grid ownership pass: the tile-byte cursor is now obtained
through `SubgameRuntime::runtime_cell_tile_views()`, an inline field-first view
of the owned `TrackRowCell[3200][8]` slab. This preserves the 0x54 cursor
stride without pretending the tile-byte view owns separate storage.

## 2026-07-14 cell-owner and cursor recovery

- The warning write now names the complete owned cell directly as
  `runtime_cells[row][col + dc].lane_and_flags`. This keeps the outer tile-byte
  scan as a field-first view while making the stamped destination a real
  `SubLoc`, and stops VC6 from strength-reducing the six-by-two footprint into
  a synthetic moving lane pointer.
- Native keeps two distinct scan cursors: an EAX next-row cursor and an EDX
  current-cell cursor. Each outer iteration borrows the row cursor, advances
  the cell cursor across eight lanes, then returns the advanced pointer to the
  row cursor. Preserving `row_cells` and `cell` separately recovers that owner
  split and the otherwise unexplained `mov eax, edx` at the row boundary.
- The saved outer row is live for the whole row scan, not created anew for each
  hazard. Hoisting that real owner and removing the now-dead linear `idx`
  restores the native 0x0c frame and all three stack lanes.
- Focused matching rises from 36.27% (105/99) to **98.99%, 99/99
  instructions, prefix 79/99, with no masked operands**. The sole residual is
  an independent reload order after a stamped hazard: native reloads the cell
  cursor before the saved row, while VC6 schedules the same two loads in the
  opposite order. No barrier or dummy dependency is retained.
- The only Windows caller discards EAX. The early exit leaves
  `runtime_row_count - 1`, while the populated exit leaves the advanced cell
  pointer, so those incompatible incidental values cannot form a semantic
  result. The shared method contract is therefore the cross-port
  `void cRSubGame::WarnTrack()` mutator.
