# merge_track_tile_runs

`cRSubGame::CondenseTrack` makes a second pass over the populated
runtime track cells. It seeds every cell with the independent
`SUBLOC_FLAG_AI_ENABLED | SUBLOC_FLAG_UNCACHED_BODY` (`0x6000`) bits,
then scans each row's eight lanes for horizontal slide, floor, and wall/pillar
runs. Multi-cell runs replace the first cell's object with a wider mesh and
clear render/contact bits on the continuation cells.

The retained scratch uses the shared `cRSubLoc` and
`TrackAttachmentRuntimeRow` owners, but follows the field-first cursors carried
by the native. Both passes walk `cRSubLoc::lane_and_flags` at a `0x54`-byte
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

Continuation cleanup is owned by `cRSubGame::runtime_cells[row][lane]`, not
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
- a `cRSubGame* game = this` alias was byte-neutral, and alternate outer
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
its containing `cRSubLoc` through `offsetof` rather than a duplicated `0x40`.

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

The cleanup write also names the containing `cRSubLoc` directly from its
`lane_and_flags` field cursor instead of keeping a redundant `clear_cell`
local alive. This removes six candidate instructions while retaining the
indexed `cRSubGame::runtime_cells[row][lane]` owner and the native
backward walk.

Focused matching rises from 54.77% (290/276) to **67.50% (284/276)** with all
12 masked operands clean. A slide-only flags cursor recovered native's
`mov edi, ebx` induction base but added an instruction and scored 67.38%;
removing the outer cell owner scored 66.43%. Both probes were rejected. The
remaining 0x14-versus-0x10 frame and parallel cell-base lifetime are left as
honest compiler-shape residuals.

The sole Windows caller discards EAX, while the zero-row and populated exits
leave incidental values in that register. Mobile code independently closes the
ABI: iOS `cRSubGame::CondenseTrack()` branches from the zero-row check to an
epilogue that leaves the incoming `this` pointer in R0, whereas Android reaches
its epilogue with a PC-relative GOT base in R0. Neither mobile epilogue
establishes a result. Those incompatible zero-row residues cannot implement a
shared return contract, so the authored member and Windows analysis prototype
are both `void`.

## 2026-07-14 row render-suppression flag

The `SubRow::flags` byte reached from the attachment-body cursor now tests
`SUBROW_FLAG_SUPPRESS_TRACK_RENDER`. Its effect is concrete: clear the cell's
render/list lanes, remove its uncached-body state, and suppress the row-owned
attachment body. Focused output remains 67.50%, 284/276 instructions, with all
12 operands clean.

## 2026-07-14 analysis receiver closure

The live Binary Ninja `Game*` receiver was a stale same-size named identity.
The guarded repair recreated only this exact function with the proven
`cRSubGame*` receiver and preserved its sole user-defined parameter. Both
tracked decompilers now expose `runtime_row_count`, `runtime_cells`,
`runtime_rows`, and `level_mode` through that owner with no raw aggregate
offsets. The remaining field-first cursor arithmetic is the native eight-lane
run scanner, not evidence for a separate container.

This analysis-only correction leaves the honest matcher result at 67.50%,
284/276 instructions, with all 12 operands clean.

## 2026-07-15 root catalog owner replay

The IDA listing now reaches the universe-hole, warning-slice, and pillar
objects through the exact `RootBodCatalog` embedded at `GameRoot +0x44100`.
That `0x4d00`-byte extent ends exactly where the independently recovered
`DirectXLoader` begins, so these names describe real root ownership rather
than a broad pointer overlay. The scratch source is unchanged; focused output
remains 67.50%, 284/276 instructions, with all 12 operands clean.

## 2026-07-17 native cursor identity replay

The native register lifetimes now replay explicitly in both decompilers. The
seed and current-cell owners are `uint32_t*` cursors over
`cRSubLoc::lane_and_flags`; the genuine containing-cell lifetime is a
`cRSubLoc*`; floor and wall scan `uint8_t*` tile cursors; slide scans a
`uint32_t*` lane-flags cursor; and each branch's backward continuation cleanup
has its own `uint32_t*` lane-flags cursor. The row stack slot is separately
owned by `SubRow::attachment_body.list_flags`.

This removes Binary Ninja's false register-reuse path through
`Player::squidge`, preserves IDA's exact definition-address identities, and
makes the three cleanup walks durable under replay. A temporary IDA operand
stroff experiment proved the native run-index displacements for
`floor_slices`, `slide_slices`, and `pillars`, but did not improve Hex-Rays'
pseudocode choice of adjacent arrays, so no overlapping catalog type or live
catalog-operand mutation was retained. The scratch already uses those
independently proven real banks.

No matching source changed. The retained result remains the honest 67.50%,
284/276-instruction frontier with all 12 masked operands clean; the catalog
presentation residual is documented instead of fakematched.

## 2026-07-24 row attachment-body ownership

The per-row suppression cursor now begins at
`runtime_rows[0].attachment_body.bod.list_flags`. Live IDA inspection proves
operand `0x4351cb:1` carries the numeric `0x5ccb7c` displacement from the
typed `cRSubGame*`; exact normalization removes the false
`unk_5CCB7C` global while retaining the native borrowed `uint32_t*` cursor.

No matcher source changed. The focused result remains honestly at 67.50%,
284/276 instructions, with all 12 masked operands clean.

## 2026-07-29 current-cell induction boundary

Three recorded mutation sweeps now bound the remaining current-cell and
continuation-cleanup source shapes. They evaluate 31 variants (29 unique):
zero improve the retained source, seven are byte-identical, and 24 regress.
The ledger therefore marks this scratch stalled after three consecutive
non-improving sweeps.

The first sweep replays the native slide owner as a `lane_and_flags` cursor.
That does recover the native `mov edi, ebx` induction base, but still preserves
the extra current-cell stack slot, adds one instruction, and falls to 67.38%.
Sharing the outer lane counter or spelling the scan as guarded `do`/`break`
control flow destroys the native alignment and introduces unaudited calls.

The second sweep combines that cursor with seven current-cell formations.
Typed field subtraction, split assignment, and `const` ownership are
byte-identical; direct row/lane and flat-array indexing regress to 23.99% and
lose four aligned references. None prevents VC6 from strength-reducing the
containing cell into the candidate's parallel `edi` induction variable.

The final sweep tests five honest continuation-store spellings, including an
explicit dword snapshot, direct assignment, a containing-cell local, and
separate bit clears, both alone and with the slide cursor. The source-order
variants are either byte-identical or worse; they cannot make the two
candidate byte-high clears adopt native's full-dword form. The retained
67.50%, `284/276` source remains the strongest shape with all 12 references
clean. The `0x14`-versus-`0x10` frame and parallel current-cell induction are
now a measured compiler-allocation boundary, not an untried alias or store
syntax.

## 2026-08-09 normalization contract and suppressed-record ownership

The complete Windows pipeline fixes this pass between the three normalization
producers and the hazard/fringe consumers:
`select_track_tile_edge_variants` (`0x437e09`),
`promote_track_tiles_to_fringe_variants` (`0x437e10`), and
`harmonize_center_lane_floor_slide_variants` (`0x437e17`) all run before the
call here at `0x437e1e`; `mark_track_warning_zones` and
`build_track_fringe_objects` follow at `0x437e25` and `0x437e2c`.
The typed producer scratches and their Windows/mobile evidence prove that the
low `0x20` and `0x40` lanes mean warning-family promotion and cache-family
swapping, while `0x8000`
marks a corner object. The opening `0x6000` seed remains two independent
AI/uncached-eligibility bits rather than one cache-family state.

That dependency order also closes two intentional branch asymmetries already
present in the retained source. A run start excludes corner and swapped-family
cells, but each floor/slide continuation must additionally retain the
uncached-body bit and exclude both low cache-family flags. `IsFloor()` accepts
tile `0x14`, while the condensible floor membership is deliberately only
`{1, 0x15, 0x1b, 0x21, 0x22}`; flattening the helper and membership predicates
would wrongly merge the excluded floor tile. In the wall branch, Windows and
Android both advance only the tile cursor: the uncached-body gate and merged
width remain owned by the first cell. No source rewrite is justified for any
of those paths.

One source-level record correction is retained. The row-suppression arm at
`0x43538e..0x4353a6` clears the current cell's independently proven
`BOD_FLAG_HAS_OBJECT | BOD_FLAG_RENDER_ENABLED | BOD_FLAG_LINKED` lifecycle
bits, removes its uncached-body state, and clears `BOD_FLAG_RENDER_ENABLED`
from the row attachment body. Naming these shared flags replaces the raw
`0x222` and `0x20` masks without changing code generation. A complete
three-variant sweep over the two substitutions is byte-neutral in every
combination. The retained source SHA-256 is
`7118dc2bffc93af621f2d8b592aafc71f1805e6d8d22b0201173d16c54f6cd03`;
focused matching remains **67.50%**, `284/276` instructions, prefix `0/276`,
with 12 clean and no unresolved, mismatched, or unaudited references.
