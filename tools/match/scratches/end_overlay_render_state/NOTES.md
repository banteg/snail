# end_overlay_render_state

Small overlay/font render-state restore helper at `0x411de0`.

Current Wibo result: 100.00%, 13/13 instructions, masked operands 4 ok.

Recovered relationships:

- Restores Direct3D transform state `3` from
  `g_saved_d3d_projection_transform`.
- Restores Direct3D transform state `2` from `g_saved_d3d_view_transform`.
