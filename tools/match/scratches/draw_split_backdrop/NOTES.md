# draw_split_backdrop

- `draw_split_backdrop @ 0x410f90` queues two axis-aligned quads using
  `active_primary_texture_id` and `active_secondary_texture_id`.
- The second quad starts at x=512 and is 128 pixels wide, so this path is for
  the script-level split backdrop pair rather than the normal distorted 7x7
  grid renderer.
