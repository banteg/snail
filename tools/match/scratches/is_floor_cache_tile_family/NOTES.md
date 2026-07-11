# is_floor_cache_tile_family @ 0x439ad0

Exact `SubLoc` predicate matching Android `cRSubLoc::IsSlide()`: both accept
tiles `15, 23, 24, 25, 26, 16, 18, 19`. This also explains why the historical
Windows cache-family name appears reversed relative to `is_slide_cache_tile_family`.
The scratch now defines the helper on `SubLoc` and remains exact at 21/21
instructions.
