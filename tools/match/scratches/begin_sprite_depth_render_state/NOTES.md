# begin_sprite_depth_render_state

Renderer-state setup helper at `0x413540`.

Current Wibo result: 100.00%, 60/60 instructions, masked operands 7 ok.

Recovered relationships:

- Saves Direct3D transform state `2` into `g_saved_d3d_view_transform`.
- Installs an identity transform into transform states `2` and `0x100`.
- Sets texture-stage state `0xd` and `0xe` to `3`, then clears stage state
  `0x18` to `0`.

This is the state wrapper called immediately before `render_game_frame` walks
the sprite depth buckets.
