# remove_track_render_cache_bods @ 0x433f20

First typed scratch for clearing the track-render-cache BOD slots.

The helper walks `0x8f` cache rows with five `TrackRenderCacheSlot` entries per
row. The shared `track_render_cache.h` layout keeps each slot as a
`BodBase`/`BodNode` overlay with stride `0x3c`, matching the
initializer/build-cache users that address the render object at the
`BodBase::object` lane (`slot + 0x24`).

Semantics: if a cached BOD is live (`list_flags & 0x200`), inline the standard
active-list unlink/free-stack push against the global BOD list at
`g_game_base + 0x5a8`, reporting the same `"List remove"` and
`"List remove NEXTBOD"` diagnostics used by the shared `BodList` remover.

Current match: 51.72%, 58/58 instructions, 7-instruction prefix, four masked
operands clean.

Important shape correction: native keeps `esi` as a cursor to
`BodNode::list_next` (`slot + 0x0c`), not to the slot/BOD base. The scratch uses
`next_ref = &slots[0][0].bod.list_next` to preserve that lane while still
documenting the owning slot as `TrackRenderCacheSlot { BodBase bod; ... }`.

Residuals:

- VC6 folds the `0x200` and `~0x200` flag masks into byte tests/updates
  (`test bh, 0x2`, `and ah, 0xfd`), while native keeps `0x200` in `ebx` and
  `0xfffffdff` in `ebp` for dword `test`/`and` operations.
- Because native keeps those mask registers live, `edi` remains the inner
  five-slot counter and the global list pointer stays in `ecx`; the scratch
  allocates those registers differently.

Rejected probe:

- Walking a `TrackRenderCacheSlot*` directly produced the right semantics but
  started from `slot + 0x00` (`lea esi, [ecx+0x58]`) instead of native's
  `slot + 0x0c` cursor (`lea esi, [ecx+0x64]`) and matched only 43.48%.
