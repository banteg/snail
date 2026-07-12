# is_sub_loc_slide @ 0x439ad0

Exact `SubLoc` predicate matching Android `cRSubLoc::IsSlide()`: both accept
tiles `15, 23, 24, 25, 26, 16, 18, 19`. The authored name retires the former
`is_floor_cache_tile_family` label, which was reversed relative to
`cRSubLoc::IsFloor()`. The scratch remains exact at 21/21 instructions.
