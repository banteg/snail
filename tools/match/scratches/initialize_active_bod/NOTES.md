# initialize_active_bod @ 0x4085e0

Exact match: 100.00%, 7/7 instructions, with both masked operands clean.

The stable Windows name predates the concrete owner recovery. Its only use is
the constructor callback passed over `SubgameRuntime::segment_cache.slots`:
stride `0x3c`, count `0x2cb`, exactly the complete 143 by 5
`TrackRenderCacheSlot` grid. The body calls `BodBase::initialize_bod_base()`,
installs `g_active_bod_vtable`, and returns the same slot.

The table at `0x497338` contains `update_active_bod @ 0x433e80`; that exact
callback consumes the slot's `cache_row_base +0x38`. The iOS binary also keeps
the `cRSegTrack` RTTI name, independently supporting a concrete track-cache
BOD owner rather than a generic second `ActiveBod` record.

The matcher therefore models `TrackRenderCacheSlot : BodBase` and keeps
`ActiveBod` only in the stable function label. This ownership correction is
codegen-neutral and preserves the exact constructor.
