# Exact - cRSubLoc::Yi row index

This accessor pins Windows `SubLoc +0x40` as the lane/flags dword. The low
three bits are the lane, and `mark_track_warning_zones` now cross-checks that
the same dword carries the `0x18` warning footprint bits.

The iOS `cRSubLoc::Yi()` implementation independently proves the owner and
algorithm: it masks the low three bits of its lane byte at `+0x32`, subtracts
the first cell in the runtime slab, divides by the iOS `0x44` cell stride, then
divides by eight lanes. Windows performs the same operation with its `+0x40`
lane word and `0x54` cell stride. The exact matcher scratch now defines the
method on `SubLoc`; `TrackRowCell` remains only a compatibility alias for older
scratch names.

## 2026-07-14 cell-stride ownership

The lane rewind and runtime-slab index now derive their `0x54` stride from
`sizeof(SubLoc)`. The explicit `int` cast preserves the signed division implied
by the pointer-difference carrier. The function remains exact at 22/22
instructions with two clean masked operands.
