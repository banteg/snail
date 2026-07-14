# merge_track_tile_runs

`SubgameRuntime::merge_track_tile_runs` makes a second pass over the populated
runtime track cells. It seeds every cell with the independent
`SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY` (`0x6000`) bits,
then scans each row's eight lanes for horizontal slide, floor, and worm-tunnel
runs. Multi-cell runs replace the first cell's object with a wider mesh and
clear render/contact bits on the continuation cells.

The retained scratch uses the shared `TrackRowCell` and
`TrackAttachmentRuntimeRow` owners, but follows the field-first cursors carried
by the native. Both passes walk `TrackRowCell::lane_and_flags` at a `0x54`-byte
stride. The second pass derives the owning cell at `-0x40`, while its row cursor
starts at `SubRow::attachment_body.list_flags` and advances by the full `0xf4`
row stride.

That row cursor corrected a real ownership bug in the first draft. At
`0x435381`, the native tests `SubRow::flags` at cursor `-0xb4`, clears the
current cell's embedded `BodNode::list_flags`, then clears the row's embedded
`attachment_body.list_flags`. It does not touch `row_model.list_flags`.

Important flag distinction: the first cell's start gate excludes
`SUBLOC_FLAG_CACHE_FAMILY_SWAPPED` (`0x40`), but continuation cells require
`SUBLOC_FLAG_UNCACHED_BODY` (`0x4000`). Keeping those separate is required for
the run counts to match the native behavior after the initial AI/uncached-body
seed pass.

Continuation cleanup is owned by `SubgameRuntime::runtime_cells[row][lane]`, not
by an independently advancing borrowed cell pointer. Recomputing the indexed
field cursor matches the native row/lane address arithmetic and prevents a run
cursor from escaping its eight-cell row.

The `0x0e` wall-run path has another non-obvious ownership detail. Its tile
cursor advances across cells, but the uncached-body test and merged-run-width
updates remain on the first cell's `lane_and_flags`. Advancing a full cell
owner for those flag accesses changes behavior and is not equivalent.

Source-shape progression:

- indexed continuation ownership plus the corrected row actor raised the fuzzy
  match from 21.78% to 32.09%;
- delaying the tile read until both floor/slide helper checks fail recovered the
  native branch shape and raised it to 45.41%;
- the two field-first cursors and fixed wall-run flag owner bring the retained
  version to 54.77% (276 target instructions, 290 candidate instructions, ten
  clean masked operands);
- a `SubgameRuntime* game = this` alias was byte-neutral, and alternate outer
  cell scopes regressed the score, so neither is retained.

The remaining gap is mostly the compiler preserving a parallel cell-base
induction variable and scheduling the three continuation-cleanup stores
differently. No dummy locals, volatile qualifiers, or equivalent-instruction
normalization are used to force those differences.

## 2026-07-14 catalog and floor-family ownership

The first run predicate is the floor family, not the slide family. It follows
an `is_sub_loc_floor` gate and accepts floor ids `1, 21, 27, 33, 34` (the
authored floor set excluding id `20`); Android `cRSubGame::CondenseTrack()`
preserves the same split before its separate `IsSlide` path. The misleading
`IS_SLIDE_RUN_TILE` macro is now `IS_FLOOR_RUN_TILE`.

The four remaining raw root-object addresses also close against the shared
`RootBodCatalog`:

- a floor run of length N selects `floor_slices.storage[N - 1]`;
- a slide run selects `slide_slices.storage[N - 1]`;
- a tile-`0x0e` run selects `pillars[N - 1]` (`pillar1.x..pillar8.x`);
- the level-mode-2 empty-cell fallback borrows `universe_hole.object`.

These typed substitutions compile to the same honest frontier: 54.77%,
`290/276` instructions, with all ten masked operands clean. They replace
duplicate address arithmetic with producer/consumer ownership without changing
the pinned register/scheduling residual.

## 2026-07-14 canonical catalog and grid bounds

The four replacement objects now load through the canonical
`GameRoot* g_game` and its embedded `root_bod_catalog`: floor and slide slice
banks, the pillar bank, and the universe-hole fallback all retain their real
root owner across the native call boundaries. Every eight-lane bound derives
from `runtime_cells[0]`, and the field-first `lane_and_flags` cursor recovers
its containing `SubLoc` through `offsetof` rather than a duplicated `0x40`.

Focused output is byte-identical at 54.77%, 290/276 instructions, prefix
0/276, with all ten operands clean. The native/candidate frame and induction
variable schedule remain the same documented honest residual.

## 2026-07-14 consumed run-length ownership

The native does not create an independent `run_length - 1` cleanup counter.
After installing a wider floor, slide, or pillar object, it consumes that
branch's now-dead run length directly: one decrement selects the final
continuation cell and the cleanup loop decrements the same owner to zero.
Spelling that lifetime explicitly recovers the native `dec`/`test` entry and
loop counter at all three call sites.

The cleanup write also names the containing `SubLoc` directly from its
`lane_and_flags` field cursor instead of keeping a redundant `clear_cell`
local alive. This removes six candidate instructions while retaining the
indexed `SubgameRuntime::runtime_cells[row][lane]` owner and the native
backward walk.

Focused matching rises from 54.77% (290/276) to **67.50% (284/276)** with all
12 masked operands clean. A slide-only flags cursor recovered native's
`mov edi, ebx` induction base but added an instruction and scored 67.38%;
removing the outer cell owner scored 66.43%. Both probes were rejected. The
remaining 0x14-versus-0x10 frame and parallel cell-base lifetime are left as
honest compiler-shape residuals.

The sole Windows caller discards EAX, but the zero-row and populated exits both
leave `runtime_row_count`. Unlike the independently proven void warning pass,
that is not enough to exclude an integer contract, so analysis retains the
conservative `int32_t` result while the matching member remains a side-effect
only `cRSubGame::CondenseTrack()` transcription.
