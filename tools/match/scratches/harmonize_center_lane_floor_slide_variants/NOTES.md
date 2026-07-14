# harmonize_center_lane_floor_slide_variants

- Row-modulo pass over runtime track cells. Rows where `row & 7 == 3` compare
  the current lane against the same lane eight rows ahead; rows where
  `row & 7 == 5` compare against the same lane eight rows behind.
- Promotes floor-object variants to slide-object variants, or the reverse, when
  the current/neighbor cache families match the center-lane transition shape.
- The scratch deliberately starts from the shared `TrackRowCell`/`BodBase`
  views. Native computes a byte offset cursor from `(lane + row * 8) * 0x54`;
  later passes can specialize the cursor if needed for register shape.
- Current retained shape is 58.98% with the native prologue and row/lane loop
  skeleton recovered. The typed cell cursor shifts the core body by
  `+0x3bfac8`; an explicit byte-offset cursor recovered the native offsets in
  the body but destabilized the prologue/register allocation and fell to
  32.37%, so it was rejected.
- 2026-06-20 continuation: removing the `next`/`previous` neighbor locals and
  spelling the neighbor cells inline looked closer to BN's direct-offset view,
  but regressed to 48.09%. VC6 shrank the frame to `0x0c`, moved the
  transition flag into `ebp`, and used `ebx` for the lane counter, losing the
  native prologue/register skeleton. Keep the neighbor locals with the typed
  `TrackRowCell*` cursor.
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
