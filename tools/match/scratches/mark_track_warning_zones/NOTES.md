# Pinned — 36.27%, register allocation diverges

Control flow, constants, and operations all line up in the diff; our
build moves `this` out of ecx and spills differently, so the score is
low despite structural agreement. Needs more layout iteration if a full
match is ever wanted; the semantics below are already pinned by the asm
read and are what blind spot #6 needs:

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
