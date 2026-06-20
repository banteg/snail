# `build_track_render_caches` reconstruction notes

`build_track_render_caches` consumes the normalized track-row state and builds
five render-cache families: Floor, Slide, Warn, Ramp, and Fringe. The retained
scratch keeps the committed by-value member signature:

```cpp
int TrackRenderCacheManager::build_track_render_caches(Color4f skirt_color);
```

That signature agrees with the exact caller in
`rebuild_track_runtime_from_segments`: VC6 copies the resolved 16-byte color
onto the stack before this call.

## Recovered top-level flow

The public member now reproduces the native `0x4c` frame and the following
source-level behavior:

- constructs the local packed white color, packs the supplied skirt color into
  manager `+0x00`, and performs the initial no-op AI call;
- scans `track_render_grid->cell_count`, using `% 24` and `/ 24` to select a
  row within a cache group and a cache-row index;
- clears five vertex and index counters and writes the row-base value into the
  five `TrackRenderCacheSlot::unknown_38` fields at each 24-row boundary;
- scans eight row cells and four fringe-object slots per cell;
- dispatches warning, slide, floor, ramp, and fringe objects to the recovered
  mesh builder with the native family/color/projected-UV combinations;
- copies the first face texture into the destination cache object and clears
  the source cell's `0x4000` ownership bit;
- flushes each completed row group into the shared vertex/index buffers and
  updates grouped vertex, primitive, and vertex counts; and
- performs the final Floor/Slide/Warn/Ramp/Fringe maximum-count/name pass.

The active row slab is addressed from `TrackRenderGrid + 0x3bfac8`, with the
anchor at `+0x10`, render object at `+0x24`, cache flags at `+0x40`, and the
four fringe pointers at `+0x44..+0x50`.

## Recovered internal mesh helpers

The target extent also covers the code at approximately `+0x610` and `+0x740`.
The scratch implements these as real `TrackRenderCacheBuilder` member methods,
not fake externs:

- `add_track_cache_vertex` transforms a source vertex, optionally generates
  projected UVs from `(x + 4) * 0.125` and
  `(z - build_cache_row_base) * 0.125`, deduplicates 24-byte render vertices,
  stores `1.0f - v`, and reports vertex overflow;
- `append_track_cache_object` emits the first triangle for every face, emits
  the second triangle for quads, advances the 3/6-index count, and reports
  index overflow.

VC6 emits these two recovered methods as separate COMDAT `.text` sections in
the candidate object. The current matcher counts only the 475-instruction
public-member section, while the linked target range continues through 288
instructions belonging to the two adjacent helper bodies. The helpers remain
in the scratch so the repeated calls have honest recovered source semantics.

## Matcher-sensitive source shape retained

Several ordinary C++ choices materially improved the match:

- keeping the five tile-family dispatches as repeated branch bodies preserved
  the native control-flow and register allocation;
- declaring the `unknown_38` field cursor before the two counter clears, then
  using two `memset` calls, reproduces the complete native row-group
  initializer and extends the common prefix to 90 instructions;
- using an `int*` directly to `slots[cache_row][0].unknown_38` emits the native
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
