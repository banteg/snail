# harmonize_center_lane_floor_slide_variants

- Row-modulo pass over runtime track cells. Rows where `row & 7 == 3` compare
  the current lane against the same lane eight rows ahead; rows where
  `row & 7 == 5` compare against the same lane eight rows behind.
- Promotes floor-object variants to slide-object variants, or the reverse, when
  the current/neighbor cache families match the center-lane transition shape.
- The exact scratch keeps the shared `cRSubLoc`/`BodBase` views while
  indexing `runtime_cells[row][lane]` directly. VC6 consequently retains the
  owning `SubgameRuntime*` plus `(lane + row * 8) * 0x54`, matching the native
  base cursor instead of materializing shifted current/neighbor pointers.
- Current retained shape is 100.00%, with 226/226 instructions, a 226/226
  prefix, and all 28 operands audited cleanly.
- 2026-06-20 continuation: removing the `next`/`previous` neighbor locals and
  spelling the neighbor cells inline looked closer to BN's direct-offset view,
  but regressed to 48.09%. VC6 shrank the frame to `0x0c`, moved the
  transition flag into `ebp`, and used `ebx` for the lane counter, losing the
  native prologue/register skeleton. Keep the neighbor locals with the typed
  `cRSubLoc*` cursor.
- 2026-06-21 predicate-direction fix: the four floor/slide helper predicates
  were reversed relative to the object replacements. The native masked audit
  expects floor-current/slide-neighbor before promoting floor objects to slide
  variants, and slide-current/floor-neighbor before reverting them. Swapping
  those calls keeps the focused score at 58.98% but improves the masked audit
  from `20 ok / 4 mismatch` to `24 ok / 0 mismatch`; the remaining fuzzy gap is
  still the typed-cell cursor displacement/register tradeoff documented above.
- 2026-07-13 catalog-owner pass: floor and slide comparisons/replacements now
  use their typed `RootBodCatalog` banks. This ownership-only substitution keeps
  the honest 58.98% result and all 24 operands clean; the documented cursor and
  register-shape residual remains.

## 2026-07-14 predicate contract correction

The retained scratch had drifted back to the historical reversed predicate
labels despite the 2026-06-21 note claiming the correction. Native calls
`is_sub_loc_floor` at `0x435770`/`0x435901` before replacing the current floor
object with its slide variant, and calls `is_sub_loc_slide` at
`0x43582b`/`0x4359bc` before the reverse replacement. Android
`cRSubGame::SlideSmoothTrack()` independently preserves the same four
current/neighbor contracts.

The source now follows that behavior in both row-phase arms:

- floor current plus slide neighbor (or the authored special tile) promotes
  floor objects to slide objects;
- slide current plus floor neighbor restores slide objects to floor objects.

Focused instruction similarity remains 58.98% (`225/226`, prefix `9`). The
masked audit changes from 24 clean to 20 clean plus four mismatches because the
sequence aligner pairs each target call with the other same-shaped candidate
call across the still-unresolved typed-cell/base-offset block. Direct target
addresses and the Android body prove the corrected call order; retaining the
reversed semantics merely to make those four aligned references green would
be fakematching.

## 2026-07-14 canonical grid and catalog ownership

Both row-phase cursors now name `runtime_cells[row][lane]` directly, and the
forward/backward neighbor stride plus lane bound derive from the embedded
eight-cell row. Each reloadable catalog local is the canonical
`GameRoot* g_game`; slice replacements and the four corner scans retain the
root catalog owner across `set_bod_object` calls. Corner strides and bounds now
derive from `BodBase` and the recovered corner-bank arrays.

All substitutions are byte-identical at 58.98%, 225/226 instructions, prefix
9/226. The audit remains 20 clean plus the four documented alignment
mismatches caused by retaining the evidence-backed floor/slide predicate
semantics; those calls are not reversed for a greener report.

## 2026-07-14 analysis receiver closure

The live BN function no longer carries the stale `Game*` receiver. Guarded
recreation installs the matcher- and Android-proven `SubgameRuntime*`, and the
BN/IDA exports now agree on the runtime-grid owner and packed cell flags. This
does not alter the deliberately evidence-backed floor/slide predicate order or
the honest 58.98% matcher result; reversing those calls remains rejected as
fakematching.

## 2026-07-17 same-lane cell-neighborhood ownership

The native ESI value in each row-phase arm is not a `cRSubLoc*`. It retains
`SubgameRuntime + (row * 8 + lane) * 0x54`, so the current cell remains at
`+0x3bfac8` and the previous/next same-lane cells sit exactly one eight-cell
row stride (`0x2a0`) behind/ahead. The shared `RuntimeCellStrideAnchor` now
models all three real `cRSubLoc` owners instead of only the predecessor's
tile byte.

Binary Ninja's exact register lifetimes are `(index=98, storage=72)` for the
forward arm and `(index=492, storage=72)` for the backward arm. IDA independently
places them at definitions `0x435753` and `0x4358dd`. Both decompilers now show
the current and neighboring `lane_and_flags`, `tile_id`, object, and helper
arguments through those owners; the former raw `0x3bf828..0x3bfda8` accesses
are gone. IDA also folds the four proven floor/slide slice and corner banks
through `GameRoot::root_bod_catalog` after normalizing only their 16 exact
displacement operands.

The matcher source is unchanged at the honest **58.98%** (`225/226`, prefix
`9/226`) with all 12 masked operands clean. The remaining candidate/native
split is now clearer: the candidate materializes current/neighbor cell pointers,
while native retains the containing runtime-stride cursor. No padded matcher
view or register-shaped construct is introduced merely to force that schedule.

## 2026-07-19 void mutator ABI

The sole Windows caller invokes this pass at `0x437e17`, ignores EAX, and
immediately restores the same receiver for `CondenseTrack`. Native's empty path
leaves the prologue's zero in EAX, while the populated path leaves the final row
loop index. Those are control-flow temporaries, not one stable semantic result.
The void matcher member and the independent
`cRSubGame::SlideSmoothTrack()` body agree that the operation owns only its
in-place `cRSubLoc` mutations.

The replayed analysis prototype is therefore
`void __thiscall harmonize_center_lane_floor_slide_variants(SubgameRuntime*)`.
No matcher expression or operand was changed; the honest 58.98% result and the
evidence-backed predicate ordering remain intact.

The replay also exposed and fixed a tooling gap: required-type existence was
not enough to refresh an evolved analysis view. Mutable path analysis views now
compare exact parsed type equivalence, so a stale same-name layout is replaced
through the normal preview/apply/readback path instead of silently surviving.

## 2026-07-27 direct runtime-grid indexing

Android and iOS `cRSubGame::SlideSmoothTrack()` both retain source-level
indexing over the owned row/lane grid. In particular, the forward phase reads
the same lane in `row + 1`, the backward phase reads `row - 1`, and every
replacement writes the current `cRSubLoc` through the containing `cRSubGame`.

Mirroring that ownership in Windows by using
`runtime_cells[row][lane]` directly, rather than first materializing
`cRSubLoc* cell`, `next`, and `previous` aliases, lets VC6 retain the native
`SubgameRuntime* + flattened-index` cursor naturally. Rewriting only the
forward phase raised the focused result from 58.98% to 76.55%; applying the
same authored shape to the mirrored backward phase closes the function at
100.00%, 226/226 instructions, a 226/226 prefix, and 28 clean masked operands.

This is not a padded or register-shaped matcher view: the source now states the
mobile-preserved owner and two-dimensional indexing directly, and the existing
Windows `cRSubLoc[...][8]` layout produces the shipped code without
volatile reads, dummy dependencies, or duplicated operations.
