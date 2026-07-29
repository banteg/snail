# Source-shaped — 98.99%, 99/99 instructions

The recovered source now keeps the native `cRSubGame` receiver in `ecx`
and names the complete runtime-cell owner. The sole remaining byte drift is
the independent cell-cursor/saved-row reload order documented below; no
synthetic dependency is warranted. The pinned semantics are:

- seed tile set: {2..14, 23, 25, 33} (literal 16-way compare chain)
- stamp footprint per seed at (row, col): rows row..row-5, cols
  {col-1, col}, bounds-checked `r >= 0 && r < rows-1 && 0 <= col+dc < 8`
  as signed pairs
- effect: `cells[idx].lane_and_flags |= SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED`
  (`0x18`), suppressing both random salt (`0x08`) and garbage (`0x10`)
- cell bank: game + 0x3bfb04, stride 84 (0x54), tile byte +0x00,
  lane/flags dword +0x04, 8 cells per row, row-major contiguous walk
- relation to shared `cRSubLoc`: this cursor starts at the tile byte, so
  its `+0x00/+0x04` fields are `cRSubLoc +0x3c/+0x40`. The shared
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
`is_neighbor_cell_solid` independently confirms the same `cRSubLoc`
`tile_id +0x3c` and `lane_and_flags +0x40` layout.

2026-06-20 shared-owner consolidation: `runtime_row_count` and the
`+0x3bfb04` tile-byte cursor now live in `cRSubGame`, matching the exact
`rebuild_track_runtime_from_segments` caller and the Android `cRSubGame`
symbol. Focused Wibo stays at 36.27%; an index-only scan and a do/while
lateral-offset loop both regressed, so the prior pointer scan remains.

2026-07-10 runtime-grid ownership pass: the tile-byte cursor is now obtained
through `cRSubGame::runtime_cell_tile_views()`, an inline field-first view
of the owned `cRSubLoc[3200][8]` slab. This preserves the 0x54 cursor
stride without pretending the tile-byte view owns separate storage.

## 2026-07-14 cell-owner and cursor recovery

- The warning write now names the complete owned cell directly as
  `runtime_cells[row][col + dc].lane_and_flags`. This keeps the outer tile-byte
  scan as a field-first view while making the stamped destination a real
  `cRSubLoc`, and stops VC6 from strength-reducing the six-by-two footprint into
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
  `void cRSubGame::DeSaltTrack()` mutator.

2026-07-17 bounded reload-order retest: moving the cell increment from the
`for` iteration expression into the body and reversing the two ordinary
iteration-expression increments both preserved semantics but regressed focused
matching from `98.99%` to `97.98%`. Neither changed the saved-row-first reload;
the latter also scheduled the pointer add before the column increment. The
source-shaped `++col, ++cell` loop remains the best form, and the final two
independent loads remain intentionally unmatched rather than barrier-forced.

## 2026-07-19 field-first scan ownership

Binary Ninja now carries the source-level `TrackRowCellTileByteView` across all
three native pointer lifetimes: the EAX row cursor, EDX current-cell cursor,
and saved stack copy. This view begins at `cRSubLoc::tile_id +0x3c` and has
the exact `0x54` induction stride; its tail aliases surrounding grid storage
and does not claim a standalone allocation or full-cell ownership.

The tracked decompile consequently reads `cell_tile_cursor->tile_id`, names the
real `SubLocTileId` values in the seed predicate, advances
`cell_tile_cursor[1]`, and hands that exact pointer back to the next-row cursor.
The previous synthetic subtraction from the runtime base is gone. Destination
stamps remain rooted in the owning `cRSubGame::runtime_cells` slab, so the
field-first scan view and complete-cell owner stay distinct.

The guarded replay verifies the `0x54` cell and view widths, the exact tile and
flag fields, the `0x1272838` runtime extent, and all three SSA identities before
mutation; a second run is idempotent. Matching source remains unchanged at the
honest 98.99%, 99/99-instruction frontier with no masked operands. The sole
residual remains the independent reload order documented above.

## 2026-07-27 mobile pipeline correction

The Android body and dispatcher order correct the earlier name-only
association with `WarnTrack()`. Android `DeSaltTrack()` recognizes the same
tile-id set `{2..14, 23, 25, 33}`, walks the same six rows backward over
lanes `{column-1, column}`, performs the same bounds checks, and ORs the same
`0x18` suppression flags. It also follows `CondenseTrack()` immediately in
`GenerateLevel()`, matching this Windows call site exactly. `WarnTrack()` is
the preceding floor/slide-to-warning object promotion pass at `0x4355f0`.

## 2026-07-29 bounded reload-order audit

A five-variant mutation sweep over the `row`/`saved_row` declaration and
initialization order was codegen-neutral: every form retained 98.99%, 99/99
instructions, prefix 79/99, and the same saved-row-first reload.

Moving `row = saved_row` into the `for` update comma-expression does recover
the native hazard-path load order (`cell` cursor, then saved row). It also
makes the non-hazard path branch to the saved-row reload instead of skipping
both reloads as native does, leaving a different single branch-target
mismatch at the same 98.99%. An equivalent early-`continue` spelling is
codegen-neutral. These results pin the remaining debt to scheduling two
independent hazard-path reloads; no semantic source shape, barrier, or
translation-unit dependency has been found, so the clear source above remains
canonical.

## 2026-07-29 formal reload-order boundary

Three recorded sweeps cover the independent owners around that reload pair.
Five row/saved-row declaration, initialization, and chained-zero forms are all
byte-identical to the 98.99% baseline. Six cell-loop updates cover pre/post
increment, reversed comma order, compound increments, and an inequality bound;
three are neutral and three regress to 97.98% by adding a pointer/column update
ordering mismatch without swapping the reloads.

Five outer row recurrences then cover combined preincrement, explicit add,
cursor-last order, saved-row-derived advancement, and a staged next-row local.
Three are neutral. The two saved-row-dependent forms disturb the opening
register/frame ownership and regress to 88.44% and 67.01%.

The ledger contains 16 unique variants: 0 improve, 11 are byte-identical, and
5 regress. Three consecutive non-improving sweeps formally stall this lane at
**98.99%** (`99/99`, prefix 79, no masked operands). The only difference is
still native's cell-cursor reload before the saved-row reload versus VC6's
opposite scheduling of those independent hazard-path loads. Further work needs
compiler provenance, not another declaration, comma expression, recurrence,
or synthetic dependency.
