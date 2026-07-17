# update_active_bod @ 0x433e80

Exact match: 100.00%, 50/50 instructions.

This helper updates one `TrackRenderCacheSlot`: once
`cache_row_base + 24.0f` falls behind the embedded player's
`interaction_max_z`, the node is removed from `GameRoot::active_bod_list` and
pushed onto its shared free stack.

The exact source shape uses the same typed intrusive-list logic as exact
`recycle_bod_to_free_list` and `refresh_fringe_object_draw_list`.

2026-06-20 interim ABI cleanup: the runtime record was consolidated in an
`active_bod.h` overlay with the slot-zero callback, list flags/links at
`+0x04/+0x08/+0x0c`, and the consumed float at `+0x38`. Focused matching
stayed exact at 50/50 instructions with 7 clean masked operands. The concrete
owner recovery below supersedes that temporary generic view.

2026-07-14 owner closure: root `+0x4326fc` is
`subgame.player.interaction_max_z`, and root `+0x5a8` is the active/free BOD
list owner. Following both through the canonical `GameRoot` graph preserves
the exact 50/50 instructions and all seven operands.

2026-07-18 concrete-owner closure: `initialize_active_bod` is used only as the
constructor for the complete 143 by 5 `SegmentCache::slots` grid with the
exact `TrackRenderCacheSlot` stride `0x3c`. Its table at `0x497338` points here,
and this body reads the slot's established `cache_row_base +0x38`. The former
standalone `ActiveBod` ABI shell is retired; `TrackRenderCacheSlot : BodBase`
now owns both exact lifecycle methods, while the heterogeneous frame list uses
the cast-only `BodAiDispatch` surface. Focused matching remains exact at 50/50
instructions with all seven operands clean.
