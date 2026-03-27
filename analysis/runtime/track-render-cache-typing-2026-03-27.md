# Track Render Cache Typing 2026-03-27

This pass takes the smallest safe owner slices around the cache/fringe builders without pretending we fully understand the surrounding runtime object graph.

## Closed slices

- [`TrackRowCell`](../headers/path_template_types.h):
  - `render_flags` at `+0x40`
  - four fringe/cache object slots at `+0x44..+0x50`
- [`RenderObjectTextureGroups`](../headers/path_template_types.h):
  - generic render-object tail at `+0xc0..+0xd4`
  - `vertex_buffer`, `vertex_count`, `index_buffer`
  - texture-group ids, texture refs, and primcounts
- [`TrackRenderCacheSlot`](../headers/path_template_types.h):
  - `render_object` at `+0x24`
  - `vertex_count` at `+0x2c`
- [`TrackRenderCacheManager`](../headers/path_template_types.h):
  - five per-type vertex caps
  - five per-type index caps
  - five shared vertex buffers
  - five shared index buffers
  - `track_render_grid`
  - scratch maxima and the current row base offset at `+0xa7ec/+0xa7f0/+0xa7f4`
- [`TrackRenderGrid`](../headers/path_template_types.h):
  - `cell_count` at `+0x54`
  - the active row-cell slab at `+0x3bfac8`

## What this improves

The canonical checked-in header now carries the owner model for:

- [`initialize_track_render_cache_manager`](../decompile/ida/functions/00433060-initialize_track_render_cache_manager.c)
- [`build_track_render_caches`](../decompile/ida/functions/00433220-build_track_render_caches.c)
- [`remove_track_render_cache_bods`](../decompile/ida/functions/00433f20-remove_track_render_cache_bods.c)

The BN bridge timed out on live struct-field replay during this pass, so the
tracked improvement is currently in the canonical header plus IDA lane rather
than a new checked-in BN narrow-sync script.

## Deliberate non-claims

- `tile_flags_3d` stays conservative. It still behaves like a classifier/variant byte in some callers, not a closed semantic enum.
- The `TrackRenderGrid` tail before `+0x3bfac8` stays opaque. Only the row-count field and the active cell slab are named.
- `RenderObjectTextureGroups` is intentionally generic. The same tail is used outside the track-cache manager and should not be named as a cache-only object.
