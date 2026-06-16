# end_sprite_depth_render_state

Small renderer-state restore helper at `0x413650`.

Current Wibo result: 100.00%, 7/7 instructions, masked operands 2 ok.

Recovered relationship:

- Restores Direct3D transform state `2` from `g_saved_d3d_view_transform`
  (`data_503178`) after the sprite-depth bucket pass.

2026-06-16 type consolidation: this now uses the shared
`render_state_device.h` Direct3D device/vtable view, extracted from the
overlay and sprite-depth render-state helpers. Focused Wibo remains exact.
