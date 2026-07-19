# is_sub_loc_floor @ 0x439a40

Exact `SubLoc` predicate. Android preserves the authored method as
`cRSubLoc::IsFloor()` and tests the identical named tile set:
`FLOOR_DOT`, `FLOOR_VARIANT_14`, `FLOOR_DASH`, `GARBAGE_HAZARD`,
`SALT_HAZARD`, and `FLOOR_VARIANT_1B`. The authored owner name replaces the former
`is_slide_cache_tile_family` label; the scratch remains exact at 17/17
instructions.
