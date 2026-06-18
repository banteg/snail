# destroy_sub_lazer_projectile

First relationship scratch for `TrackRowCell::destroy_sub_lazer_projectile()`
at `0x439bc0`.

Current match: 91.19% (`130/131` candidate/target instructions), 87-instruction
exact prefix, `17` masked operands ok, no unresolved or mismatched operands.

Recovered behavior:

- the receiver is the full `TrackRowCell`/fringe runtime object, not a
  `SubLazerSlot`; the first `0x10` bytes are the shared `BodNode` prefix;
- tile ids `0x1d` and `0x1e` may clear the row-color BOD record at
  `game+0x6410e0 + row*0xf4`, gated by the row record's dirty bit `0x08`;
  this is the shared `TrackAttachmentRuntimeRow` record viewed from the outer
  game base, so the scratch keeps the native outer cursor and typed offset
  accesses instead of folding `0x6410e0` into the row pointer;
- the cell's own BOD node is removed when active;
- the four `TrackRowCell::fringe_*` pointers are scanned and any active fringe
  BOD is unlinked back into the shared free list.

This helper is called by the wall-2 emitter update path and by
`Game::remove_subgame_bods()`, so it is the smaller source-of-truth target
before writing the larger subgame teardown pool scratch.

Residual: the four-fringe-pointer loop is semantically aligned, but VC6 keeps
the active-flag precheck value live in the candidate instead of clobbering and
reloading it after forming the shared `BodList` anchor as native does. Leave
that as a source-shape residual unless another caller/header gives a cleaner
fringe-array spelling.

## 2026-06-18 BN/IDA name sync

Promoted the analysis-side `TrackRowCell` prefix to `BodNode`, renamed
`+0x40` to `lane_and_flags`, and synced the four directional fringe pointers as
`fringe_front/right/left/back`. BN now resolves the cell unlink block through
`cell->bod.*` and starts the final four-pointer scan at `cell->fringe_front`.
The IDA snapshot was corrected away from the stale `SubLazerSlot` wording.

The same BN type sync does help `wall2_emitter_maybe_fire_sub_lazer`, but that
export was intentionally not kept in this slice because BN reused the
`lane_and_flags` field name for a generic condition/temp value across the
function, making the artifact less honest than the previous `result` spelling.
