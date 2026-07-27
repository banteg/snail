# end_sprite_depth_render_state

Small renderer-state restore helper at `0x413650`.

Current Wibo result: 100.00%, 7/7 instructions, masked operands 2 ok.

Recovered relationship:

- Restores Direct3D transform state `2` from `g_saved_d3d_view_transform`
  (`data_503178`) after the sprite-depth bucket pass.

2026-06-16 type consolidation: this now uses the shared
`render_state_device.h` Direct3D device/vtable view, extracted from the
overlay and sprite-depth render-state helpers. Focused Wibo remains exact.

## 2026-07-27 GL.o identity and void contract

Android and iOS export this pass terminator as `G0RenderSprite3DEnd()` from
`GL.o`, paired with `G0RenderSprite3DStart()` around their
`cRGame::Render()` sprite walk. Mobile flushes and dismantles its OpenGL batch;
Windows restores the saved Direct3D view transform.

Both mobile exports are void and the sole Windows caller discards EAX. Removing
the synthetic Direct3D-status return is byte-identical: focused matching
remains 100.00%, 7/7 instructions, with both operands clean.
