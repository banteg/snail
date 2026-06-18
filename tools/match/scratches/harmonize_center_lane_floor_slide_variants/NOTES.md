# harmonize_center_lane_floor_slide_variants

- Row-modulo pass over runtime track cells. Rows where `row & 7 == 3` compare
  the current lane against the same lane eight rows ahead; rows where
  `row & 7 == 5` compare against the same lane eight rows behind.
- Promotes floor-object variants to slide-object variants, or the reverse, when
  the current/neighbor cache families match the center-lane transition shape.
- The scratch deliberately starts from the shared `TrackRowCell`/`BodBase`
  views. Native computes a byte offset cursor from `(lane + row * 8) * 0x54`;
  later passes can specialize the cursor if needed for register shape.
- Current retained shape is 58.98% with the native prologue and row/lane loop
  skeleton recovered. The typed cell cursor shifts the core body by
  `+0x3bfac8`; an explicit byte-offset cursor recovered the native offsets in
  the body but destabilized the prologue/register allocation and fell to
  32.37%, so it was rejected.
