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
  - embedded `BodBase` at `+0x00`
  - the retained ObjectList handle at `BodBase::object +0x24`
  - per-cache `cache_row_base` at `+0x38`
- [`TrackRenderCacheManager`](../headers/path_template_types.h):
  - embedded in `SubgameRuntime +0x5c`, exact size `0xa7f8`
  - packed skirt/fringe color at `+0x00`
  - five per-type vertex caps
  - five per-type index caps
  - five owned shared vertex buffers and five owned shared index buffers
  - borrowed `owner_subgame` backlink at `+0x54`
  - `143 x 5` owned cache BOD slots at `+0x58`
  - build/activation row state at `+0xa7ec/+0xa7f0/+0xa7f4`
- [`TrackRenderGrid`](../headers/path_template_types.h):
  - sparse field-first view of the enclosing SubgameRuntime
  - `runtime_row_count` at `+0x54`
  - owned `runtime_cells[3200][8]` slab at `+0x3bfac8`, ending `+0x5ccac8`

## What this improves

The canonical checked-in header now carries the owner model for:

- [`initialize_track_render_cache_manager`](../decompile/ida/functions/00433060-initialize_track_render_cache_manager.c)
- [`build_track_render_caches`](../decompile/ida/functions/00433220-build_track_render_caches.c)
- `add_track_cache_vertex @ 0x433830`
- `append_track_cache_object @ 0x433960`
- [`remove_track_render_cache_bods`](../decompile/ida/functions/00433f20-remove_track_render_cache_bods.c)

The BN lane now also replays the stable subset through
[`sync_track_render_cache_types.py`](../../tools/binja/sync_track_render_cache_types.py),
so the tracked BN exports also improved for:

- [`initialize_track_render_cache_manager`](../decompile/binja/functions/00433060-initialize_track_render_cache_manager.c)
- [`build_track_render_caches`](../decompile/binja/functions/00433220-build_track_render_caches.c)
- `add_track_cache_vertex @ 0x433830`
- `append_track_cache_object @ 0x433960`
- [`remove_track_render_cache_bods`](../decompile/binja/functions/00433f20-remove_track_render_cache_bods.c)
- [`is_slide_cache_tile_family`](../decompile/binja/functions/00439a40-is_slide_cache_tile_family.c)
- [`is_floor_cache_tile_family`](../decompile/binja/functions/00439ad0-is_floor_cache_tile_family.c)
- [`is_ramp_cache_tile_family`](../decompile/binja/functions/00439a70-is_ramp_cache_tile_family.c)

The BN view now reads the teardown path through the embedded
`slots[row][family].bod` list node and renders the build path through
`owner_subgame->runtime_row_count`, `runtime_cells`, typed staging buffers, and
the two real helper prototypes. This corrects the old false `vertex_count`
field at slot `+0x2c`, which is actually inside `BodBase::color`.

## Deliberate non-claims

- `tile_flags_3d` stays conservative. It still behaves like a classifier/variant byte in some callers, not a closed semantic enum.
- The sparse `TrackRenderGrid` name is retained for cross-tool compatibility;
  it is not separately allocated storage. It is the manager's field-first view
  of its enclosing SubgameRuntime.
- `RenderObjectTextureGroups` is intentionally generic. The same tail is used outside the track-cache manager and should not be named as a cache-only object.
