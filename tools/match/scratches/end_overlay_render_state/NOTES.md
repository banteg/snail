# end_overlay_render_state

Small overlay/font render-state restore helper at `0x411de0`.

Current Wibo result: 100.00%, 13/13 instructions, masked operands 4 ok.

Recovered relationships:

- Restores Direct3D transform state `3` from
  `g_saved_d3d_projection_transform`.
- Restores Direct3D transform state `2` from `g_saved_d3d_view_transform`.

2026-06-16 type consolidation: this now uses the shared
`render_state_device.h` Direct3D device/vtable view, extracted from the
overlay and sprite-depth render-state helpers. Focused Wibo remains exact.
