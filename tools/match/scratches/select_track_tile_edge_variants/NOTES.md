# select_track_tile_edge_variants

- Walks the row-major `SubLoc +0x3c` tile-byte view.
- Clears `tile_flags_3d`, clears `lane_and_flags & 0x8000`, builds open-edge
  bits from left/right/back/front neighbors, and for edge masks `5`, `6`, `9`,
  and `10` swaps the current cell's BOD object to the matching edge variant.
- The straight-track family branch covers tile ids `1`, `0x14`, `0x15`,
  `0x1b`, `0x21`, and `0x22`; non-ramp non-excluded cells use the alternate
  variant banks.
- 2026-06-20 larger-chunk proof: exact at 100.00%, 220/220 instructions,
  prefix 220/220, with 18 clean masked operands and no unresolved operands.
  The key source shape is keeping byte/dword pointers for the tile flag byte
  and `lane_and_flags` word inside the row-cell tile-byte cursor. That pointer
  view matches the decompiler's byte-pointer walk and stops VC6 from hoisting
  the independent tile-id loads across the flag stores without using volatile
  or artificial dependencies.
- 2026-07-11 predicate-owner pass: the neighbor and ramp calls now resolve
  through the shared `SubLoc` methods proven against Android
  `cRSubLoc::IsEmpty()` and `cRSubLoc::IsRamp()`. The field-first cursor is
  retained for native source shape; the enclosing cell casts express the real
  owner. The function remains exact at 220/220 with all 18 operands clean.
