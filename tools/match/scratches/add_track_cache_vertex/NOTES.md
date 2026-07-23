# Render-cache vertex helper

`add_track_cache_vertex` @ `0x433830` is a distinct native thiscall function,
not part of the public builder's extent. It borrows source geometry, transforms
one indexed vertex into the manager-owned family staging buffer, optionally
projects track UVs from `build_cache_row_base`, deduplicates the full position
and UV tuple, and reports capacity overflow before returning the emitted index.

Using an `int` source index (the native ABI) and a real transformed `Vector3`
recovers the exact 12-byte local frame. Staging the x addition separately keeps
the native x87 lifetime, and semantic x/y/z/u/v/diffuse assignment order leaves
only one scheduling window. Current result: 99.03%, 103/103, prefix 74/103,
seven clean operands.

## 2026-07-12 staging ownership and V lifetime

- The `vertices` argument borrows one of `SegmentCache::shared_vertex_buffers`
  selected by `build_track_render_caches`; the count pointer is a matching
  builder-local family counter. Neither belongs to an individual
  `TrackRenderCacheSlot`.
- `max_vertices` is enforced after appending. The adjacent `max_indices`
  argument is never read by this helper and is now named
  `unused_max_indices`; index-capacity ownership stays in
  `append_track_cache_object`, which checks it after emitting a complete face.
- Naming the derived texture coordinate as `flipped_v = 1.0f - v` keeps that
  value live in x87 past the Z store. The focused score remains 99.03% at
  103/103 instructions with seven clean operands, while the exact prefix grows
  from 74 to 76 instructions. The only residual is the equivalent U/V store
  scheduling immediately before the diffuse-color write; no barrier or
  register-shaped construct is used.
- Android's standalone `AddVertexUV` independently preserves the five-float
  position/UV deduplicate-or-append algorithm, but it lacks the Windows
  projected-UV, diffuse-color, and capacity wrapper. It is corroborating
  behavior, not asserted as this exact Windows owner or ABI.

## 2026-07-19 exact UV-pair cursor

The final scheduling residual identified one narrower borrowed owner inside
the staging record. Treating `ObjectRenderVertex::u` and `::v` as a two-float
cursor, writing U through `*vertex_uv++` and then the already-live flipped V
through `*vertex_uv`, gives VC6 the native store dependency without a barrier,
volatile qualifier, or register-shaped construct. Focused Wibo is now exact:
`100.00%`, `103/103` instructions, prefix `103`, with all seven masked
operands clean.

This does not invent a second retained object. The cursor borrows the
contiguous texture-coordinate lane at `ObjectRenderVertex +0x10..+0x17`, then
expires before the diffuse write and count update. A canonical `ObjectUv*`
view and moving or reversing the scalar declarations were tested: all remain
at `99.03%` because VC6 independently schedules the V store before U. The
post-increment cursor is therefore the smallest source-shaped expression that
both captures the pair ownership and explains the native order; the broader
record layout remains unchanged.

## 2026-07-23 source and staging record lifetimes

Exact Binary Ninja SSA now preserves the optimized source shape across the
helper. `source_vertex` borrows one `Vec3` from `Object::vertices`; VC6 keeps
the transformed X value in x87 while materializing transformed Y and Z in the
tail of one real `Vec3` stack home. The deduplication loop physically advances
a `float*` anchored at each staging record's Z lane, so its `[-2]`, `[-1]`,
`[0]`, `[2]`, and `[3]` accesses are the honest x/y/z/u/v comparison tuple.
Typing that cursor as an `ObjectRenderVertex*` was rejected because its
physical address is eight bytes inside the record.

After the first X store, the compiler materializes the real
`ObjectRenderVertex* staged_vertex`; the remaining y/z/u/v/diffuse stores now
resolve through that borrowed staging record before `next_vertex_count` is
written back. The replay guards `Vec3`, `ObjectRenderVertex`, `Object`, and
`SegmentCache` widths plus the source, staging-bank, and projected-UV owner
fields. x87 temporaries were deliberately left automatic: forcing a user type
rendered misleading `.q` conversions without recovering a new owner.

The matcher source is unchanged and remains exact at `100.00%`, `103/103`
instructions, prefix `103`, with seven clean operands.
