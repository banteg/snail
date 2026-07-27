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

2026-06-16 type consolidation: this now uses the shared
`render_state_device.h` Direct3D device/vtable view, extracted from the
overlay and sprite-depth render-state helpers. Focused Wibo remains exact.

## 2026-07-27 GL.o identity and void contract

Android and iOS export this render-pass boundary as
`G0RenderSprite3DStart()` from `GL.o`. Their `cRGame::Render()` methods call it
immediately before the same sprite walk and pair it with
`G0RenderSprite3DEnd()`. Mobile initializes an OpenGL sprite batch while
Windows saves the view transform and installs its Direct3D state, so the
platform bodies differ but the authored phase identity is exact.

Both mobile exports are void and the sole Windows caller discards EAX. Changing
the Windows transcription from the synthetic Direct3D-status return to a
natural void tail is byte-identical: focused matching remains 100.00%, 60/60
instructions, with all seven operands clean.
