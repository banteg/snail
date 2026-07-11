# is_open_neighbor_tile_family @ 0x439ab0

Exact `SubLoc` predicate matching Android `cRSubLoc::IsEmpty()`: both accept
tiles `0, 28, 35, 14, 29`. The retained Windows name describes its use by
track-neighbor builders rather than its authored class method. The scratch now
defines the helper on `SubLoc` and remains exact at 15/15 instructions.
