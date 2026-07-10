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
