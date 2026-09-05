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
5 regress. The tested forms leave this lane at
**98.99%** (`99/99`, prefix 79, no masked operands). The only difference is
still native's cell-cursor reload before the saved-row reload versus VC6's
opposite scheduling of those independent hazard-path loads. Further work needs
compiler provenance, not another declaration, comma expression, recurrence,
or synthetic dependency.

## 2026-08-09 suppression producer/consumer closure

The packed `cRSubLoc::lane_and_flags +0x40` contract is now closed across the
Windows image. `DeSaltTrack` loads the destination dword at `0x43558f`, ORs
literal `0x18` at `0x43559d`, and stores it back at `0x4355a0`. The two low
bits have separate gameplay consumers in `update_subgame`:

- `0x43937c` tests `0x10` and skips the ambient `AddGarbage` path when set;
  the authored garbage tile at id `0x21` is handled before this gate.
- `0x4394c5` tests `0x08` and skips the ambient salt-spawn path when set;
  the authored salt tile at id `0x22` is likewise handled before this gate.

The whole-image field-xref audit finds no consumer of `0x18` as a third,
independent flag. Other users of the packed word consume disjoint meanings:
lane index `0x0007`, warning/cache family `0x0020`, family swap `0x0040`,
merged width `0x0f00`, AI enable `0x2000`, uncached body `0x4000`, and corner
object `0x8000`. In particular, `build_track_render_caches` checks only
`0x20`, `0x40`, and `0x4000`, then clears `0x40`; it neither reads nor clears
the `0x08/0x10` suppression pair. The footprint is therefore gameplay spawn
policy, not a render/cache warning marker.

Android authored `cRSubGame::DeSaltTrack()` independently writes
`(flags & 0xe7) | 0x18` over the same six-row, two-lane footprint. Clearing
then setting exactly those two bits is equivalent to the Windows OR and pins
`SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED` as the composition of
`SUBLOC_FLAG_SUPPRESS_SALT_SPAWN | SUBLOC_FLAG_SUPPRESS_GARBAGE_SPAWN`, not a
separate bit. The source-shaped scratch already uses that combined semantic
name, so no local rewrite or further reload-order experiment is warranted.

## 2026-08-11 VC6 profile closure

The new recovery triage ranked this as a 2.54-byte fuzzy gap with verified
Android provenance, so the remaining reload-order residual was replayed under
all locally preserved VC6 game-code profiles. `msvc6.0`, canonical `msvc6.5`,
`msvc6.5pp`, and `msvc6.6`, each with `/O2 /G5 /W3`, emit the same 99
instructions, 98.99% score, 79-instruction prefix, and mismatch at candidate
offset `0xc7`: the saved-row load still precedes the independent cell-cursor
load.

The three noncanonical probes are recorded in `experiments.jsonl`. For this
source form, those four preserved profiles do not discriminate the tie-breaking
difference; that is not a per-function original-toolchain attribution.
Combined with the recorded ordinary source shapes and exact cross-port behavior
above, the scratch is explicitly classified `RECOVERY=semantic-complete` with
`RESIDUAL=compiler`; further source mutation needs a new semantic hypothesis.

## 2026-09-05 direct-grid traversal probes

`whole-grid-row-lifetimes-20260905.json` tests direct tile-field indexing with
row/hazard/outer saved-row lifetimes and do/for traversal. The valid variants
regress from 98.99% to 52.85% or below, with no reference debt. No source changed.

Review found that `direct-grid-saved-outer-for` was an invalid experiment: it
saved the row before the for-loop increment, so a subsequent hazard could
restore the previous row. Its score is excluded as matching evidence. The
separate `corrected-row-restoration-20260905.json` moves restoration-state
publication after the increment and reproduces 52.58%. The historical spec and
ledger are preserved to make this correction auditable. These results only
bound the tested indexed traversal, not all source shapes.

## 2026-09-05 goal-600 source ownership campaign

Eleven saved-row lifetime and outer-loop combinations do not improve 98.99%. The alternative placement of the two final saved-cursor loads remains unresolved; canonical source is unchanged.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-05 exact independent backward scan

The warning footprint now owns a separate `scan_row` inside the hazard branch,
while `row` remains the outer grid index. This replaces the reconstructed
save/mutate/restore lifetime with the natural independent backward traversal.
All six variants in `whole-warning-scan-row-20260905.json` reproduce **100%**,
99/99 instructions and 251 native bytes with no masked operands. The retained
version uses direct `runtime_cells[row][col]` indexing and the narrow hazard
scope, eliminating the byte-view cursor and saved-row variable.

The preceding one-load residual was caused by the source lifetime, not a
demonstrated compiler limitation. The six-row, two-column footprint, hazard
set, signed bounds, and flag OR remain unchanged.
