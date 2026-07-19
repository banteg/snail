# is_sub_loc_slide @ 0x439ad0

Exact `SubLoc` predicate matching Android `cRSubLoc::IsSlide()`: both accept
the named `_`, health, speedup, jetpack, `0x1a`, `o`, slug, and `F` tile
identities. The authored name retires the former
`is_floor_cache_tile_family` label, which was reversed relative to
`cRSubLoc::IsFloor()`. The scratch remains exact at 21/21 instructions.
