# `build_track_render_caches` reconstruction notes

`build_track_render_caches` consumes the normalized track-row state and builds
five render-cache families: Floor, Slide, Warn, Ramp, and Fringe. The retained
scratch keeps the committed by-value member signature:

```cpp
int SegmentCache::build_track_render_caches(tColour skirt_color);
```

That signature agrees with the exact caller in
`rebuild_track_runtime_from_segments`: VC6 copies the resolved 16-byte color
onto the stack before this call.

## Recovered top-level flow

The public member now reproduces the native `0x4c` frame and the following
source-level behavior:

- constructs the local packed white color, packs the supplied skirt color into
  manager `+0x00`, and performs the initial no-op AI call;
- scans `owner_subgame->runtime_row_count`, using `% 24` and `/ 24` to select a
  row within a cache group and a cache-row index;
- clears five vertex and index counters and writes the row-base value into the
  five `TrackRenderCacheSlot::cache_row_base` fields at each 24-row boundary;
- scans eight row cells and four fringe-object slots per cell;
- dispatches warning, slide, floor, ramp, and fringe objects to the recovered
  mesh builder with the native family/color/projected-UV combinations;
- copies the first face texture into the destination cache object and clears
  the source cell's `0x4000` ownership bit;
- flushes each completed row group into the shared vertex/index buffers and
  updates grouped vertex, primitive, and vertex counts; and
- performs the final Floor/Slide/Warn/Ramp/Fringe maximum-count/name pass.

The active row slab is addressed from `SubgameRuntime + 0x3bfac8`, with the
anchor at `+0x10`, render object at `+0x24`, cache flags at `+0x40`, and the
four fringe pointers at `+0x44..+0x50`.

## Recovered adjacent mesh helpers

Binary Ninja function boundaries prove the code at `0x433830` and `0x433960`
is two adjacent native thiscall functions, not part of the public builder:

- `add_track_cache_vertex` transforms a source vertex, optionally generates
  projected UVs from `(x + 4) * 0.125` and
  `(z - build_cache_row_base) * 0.125`, deduplicates 24-byte render vertices,
  stores `1.0f - v`, and reports vertex overflow;
- `append_track_cache_object` emits the first triangle for every face, emits
  the second triangle for quads, advances the 3/6-index count, and reports
  index overflow.

They now have manifest entries and independent scratches. With the public
extent ending at `0x433830`, `build_track_render_caches` is 99.79% at 475/475
instructions with 20 clean operands. `add_track_cache_vertex` is 99.03% at
103/103; direct `Object::facequads[face_index]` indexing and the native local
position lifetime raise `append_track_cache_object` to 95.81% at 167/167.

## Matcher-sensitive source shape retained

Several ordinary C++ choices materially improved the match:

- keeping the five tile-family dispatches as repeated branch bodies preserved
  the native control-flow and register allocation;
- declaring the `cache_row_base` field cursor before the two counter clears, then
  using two `memset` calls, reproduces the complete native row-group
  initializer and extends the common prefix to 90 instructions;
- using an `int*` directly to `slots[cache_row][0].cache_row_base` emits the native
  single `lea ... + 0x90` rather than a base `lea` followed by `add 0x38`;
- expressing the flush counter as a normal `family_index` while independently
  incrementing the max-count pointer lets VC6 strength-reduce the array index
  to the native `+4` byte cursor without merging the two induction variables;
- repeatedly dereferencing the cache-object reference, rather than retaining
  an `Object*` temporary, reproduces the native lock/copy/unlock scheduling.
- the final cache-name switch is paired with
  `build_track_render_caches_cache_name_jump_table` at `0x43381c`, so the
  compiler-emitted Floor/Slide/Warn/Ramp/Fringe table is audited instead of
  left as an unresolved local-label relocation.

The first remaining public-body mismatch is an equivalent SIB encoding:

```text
target[90]    lea eax, [edi+eax+0x3bfad8]
candidate[90] lea eax, [eax+edi+0x3bfad8]
```

Multiple typed and integer expression reorderings canonicalized to the same
candidate encoding, so no unnatural pointer trick was retained.

## Primary evidence used

- Binary Ninja and IDA exports for `00433220-build_track_render_caches`;
- exact neighboring scratches for initialization, row updates, removal,
  color construction, tile-family classification, and the exact caller;
- `docs/re/track-runtime.md`, `docs/re/track-quad-tables.md`, and
  `analysis/runtime/track-render-cache-typing-2026-03-27.md`; and
- the supplied target dump and regional matcher reports.

## Ownership closure (2026-07-10)

The exact callers prove `SegmentCache` is embedded at
`SubgameRuntime +0x5c`; its exact `0xa7f8` extent ends at `+0xa854`, four bytes
before the tutorial controller. It owns `143 x 5` `BodBase` slots and the five
typed vertex/index staging allocations. Each slot retains an ObjectList handle,
while manager `+0x54` is a borrowed backlink to the enclosing SubgameRuntime.

The previous cross-tool `TrackRenderCacheSlot::vertex_count +0x2c` was false:
that offset is inside `BodBase::color`. Exact activation and removal prove the
full embedded `BodBase` at `+0x00` and `cache_row_base +0x38`. The checked-in
headers and Binary Ninja sync now agree on that layout and on the owned
`runtime_cells[3200][8]` slab reached through the backlink.

2026-07-11 runtime-cell anchor cleanup: all seven mesh-builder position
arguments now name
`owner_subgame->runtime_cells[0][0].position + cell_offset` directly,
and the unused scratch-local cell layout duplicate has been removed. This
keeps the real owner and inherited `TrackRowCell +0x10` anchor visible while
preserving 99.79%, 475/475 instructions, and 20 clean operands. The lone
equivalent SIB base/index encoding remains honest scheduler debt.

2026-07-11 helper-owner cleanup: both mesh helpers now use the canonical
`Object*` input in source, Binary Ninja, and IDA. The old
`PathTemplateStripMesh*` prototype was a stale partial-object view; the cache
builder accepts track-cell and fringe `Object` instances from several owners,
so the generic object is the real borrowed geometry contract.

2026-07-11 cRSegmentCache ownership: the enclosing 0xa7f8-byte
`SegmentCache` name is fixed by the Windows runtime size ledger and its exact
SubgameRuntime boundaries. The 475/475 stream remains at the honest 99.79%
baseline with 20 clean operands.

2026-07-13 backlink ownership cleanup: `SegmentCache +0x54` is now uniformly
typed as the borrowed enclosing `SubgameRuntime*`. The former
`TrackRenderGrid` was not a distinct allocation or owner: it was a sparse
duplicate view of the same runtime pointer, carrying only `runtime_row_count`
and `runtime_cells`. Removing that synthetic type from the scratch, shared
analysis header, narrow Binary Ninja header, and sync script preserves the
honest 99.79%, 475/475 instruction result with 20 clean operands. The sole
remaining equivalent SIB base/index encoding is intentionally left visible.

2026-07-14 runtime-cell base closure: the seven cache position arguments now
reach inherited `SubLoc::position` through the actual `BodBase` owner. The
exact cell constructor and full dependency sweep preserve this near-match at
99.79%, 475/475 instructions, with all 20 operands clean.

2026-07-14 cache-object handle closure: destination cache slots and borrowed
`Fringe` sources now use their inherited `BodBase::object` handles directly.
This removes stale per-use `Object*` casts without changing the ownership
boundary: `ObjectList` owns the objects, while `SegmentCache` and `Fringe`
retain typed handles and borrow texture references from their facequads.

2026-07-14 runtime-cell and staging-lane closure: native keeps a byte-offset
induction variable across the 3200-by-8 `SubLoc` slab. Directly changing that
to a typed pointer perturbs register allocation across the function, so the
native induction shape remains; its cell base, render object, lifecycle flags,
and four fringe links now derive with `offsetof` from
`SubgameRuntime::runtime_cells` and the shared `SubLoc` fields. The eight-lane
row bound derives from the array extent.

The flush cursor's adjacent index-count, vertex-buffer, and index-buffer lanes
now derive from the `SegmentCache` field offsets, and its 75-pointer row step
derives from `sizeof(slots[0])`. The readable ownership rewrite preserves the
honest 99.79%, 475/475 result with all 20 operands clean; the sole residual is
still the equivalent position-address SIB ordering.

## 2026-07-14 cache-family ownership

The five dispatch arms, the final native debug-name switch, the manager's four
parallel capacity/buffer arrays, and every activated row agree on one stable
family order: Floor, Slide, Warn, Ramp, Fringe. `TrackRenderCacheFamily` now
owns those indices across construction, staging, activation, and reporting;
`TRACK_RENDER_CACHE_FAMILY_COUNT` and the independently proved 143-row extent
own the complete `SegmentCache::slots` grid.

This is semantic recovery rather than a score probe. All five affected
normalized listings remain byte-identical:

- manager initializer: `a421b1ebfce7d01a2f78bc5793fcdb89ae051d66b7d23f759e89e3918cbb513f`
- cache builder: `d4e28c9273db5fff1162899d9d9fd47aef5f85c3bf6a85a6903134086ba3d6cb`
- row activator: `7a3d44e214754537db62089ab05276774f460bee564f1661ed1ea7d41df99fda`
- teardown: `cf075f6f16abd639d3d16cffaaa2142e1fab47167fb39ec470d5a090059dac39`
- runtime constructor: `755c2d4b3862bccde9a1fae74b792b0500699dda1c378c9f673ef0c27b829bba`

## 2026-07-14 packed-colour owner

Android's symbol-preserving `tColourSmall` class proves the four-byte BGRA
owner stored at `SegmentCache +0x00`; its assignment operator uses the same
`+2/+1/+0/+3` stores as Windows `pack_color_rgba_u8`. The manager field and
local all-white value now use that authored type, while the fringe builder
still passes the same four packed bytes by value. Focused Wibo remains at the
honest 99.79%, 475/475 instructions, with all 20 operands clean and only the
equivalent SIB base/index ordering unresolved. Binary Ninja readback also
retains the borrowed `SubgameRuntime*` backlink alongside `tColourSmall`.
