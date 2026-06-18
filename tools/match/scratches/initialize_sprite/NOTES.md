# Exact - Sprite default initializer

`initialize_sprite` is exact at 33/33 instructions and now builds against the
promoted `tools/match/include/sprite.h` layout. The old `field_*` dwords were
replaced with the shared Sprite fields recovered from `update_sprite`,
`draw_sprite_quad`, `allocate_sprite`, `update_sprite_facing_angle`,
`set_sprite_texture_ref`, and exact allocation callers.

Confirmed fields include:

- `object_ref` at `+0x00`, initialized to the `-1` sentinel;
- texture refs at `+0x1c/+0x20/+0x24` and `draw_mode` at `+0x28`;
- `previous_position`, `position`, and `velocity` at `+0x3c/+0x48/+0x54`;
- `size_start`/`size_end` at `+0x60/+0x64`, interpolated by `progress`
  rather than X/Y scale axes, plus progress/lifetime/gravity/facing lanes
  through `+0x90`;
- `depth_offset` default `-500.0f` at `+0x94`;
- `reserved_84` at `+0x84`, still only known as an initialized zero lane;
- `depth_bias` at `+0x98`, consumed by `render_game_frame` when computing the
  projected sprite depth bucket;
- animation fields `texture_id`, `frame_count`, `frame`, `frame_step`,
  `frame_progress`, and `frame_progress_step` through `+0xb0`.

The initializer preserves native store order; only the field types/names were
cleaned up.

2026-06-18 audit: tracked Sprite callsites now use `size_start`/`size_end`.
Remaining `scale_x`/`scale_y` hits are unrelated local scale factors or notes
about rejected drafts, not `Sprite +0x60/+0x64` field names.
