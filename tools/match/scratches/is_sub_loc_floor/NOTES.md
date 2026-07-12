# is_sub_loc_floor @ 0x439a40

Exact `SubLoc` predicate. Android preserves the authored method as
`cRSubLoc::IsFloor()` and tests the identical tile set:
`1, 20, 21, 33, 34, 27`. The authored owner name replaces the former
`is_slide_cache_tile_family` label; the scratch remains exact at 17/17
instructions.
