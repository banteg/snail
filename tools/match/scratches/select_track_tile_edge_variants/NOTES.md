# select_track_tile_edge_variants

- Walks the row-major `TrackRowCell +0x3c` tile-byte view.
- Clears `tile_flags_3d`, clears `lane_and_flags & 0x8000`, builds open-edge
  bits from left/right/back/front neighbors, and for edge masks `5`, `6`, `9`,
  and `10` swaps the current cell's BOD object to the matching edge variant.
- The straight-track family branch covers tile ids `1`, `0x14`, `0x15`,
  `0x1b`, `0x21`, and `0x22`; non-ramp non-excluded cells use the alternate
  variant banks.
- Current retained shape is 94.55% with 220/220 instructions, 18 clean masked
  operands, and no unresolved operands after naming
  `select_track_tile_edge_variants_jump_table`. The remaining gap is instruction
  scheduling around independent tile/flag loads versus stores; no artificial
  dependency was kept to force exact order.
