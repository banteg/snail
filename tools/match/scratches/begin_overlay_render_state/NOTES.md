# begin_overlay_render_state

Overlay/font render-state setup helper at `0x411e10`.

Current Wibo result: 100.00%, 97/97 instructions, masked operands 14 ok.

Recovered relationships:

- Saves Direct3D projection state `3` into
  `g_saved_d3d_projection_transform`.
- Saves Direct3D view state `2` into `g_saved_d3d_view_transform`.
- Sets texture-stage states `0xd` and `0xe` to `3`.
- Builds a 640 by -480 orthographic projection with near/far `0.0/1.0`.
- Installs identity into transform state `0x100`, then translates the view by
  `(-320.6, -240.6, 0.0)` before setting transform state `2`.
- Disables render states `7`, `0xe`, and `0x89`.

This helper is not font-only: `initialize_loading_screen` also calls it for
overlay-style rendering.

2026-06-16 type consolidation: this now uses the shared
`render_state_device.h` Direct3D device/vtable view, extracted from the
overlay and sprite-depth render-state helpers. Focused Wibo remains exact.

2026-07-11 device closure: `render_state_device.h` is now only a compatibility
alias for the complete shared IDirect3DDevice8 view. The overlay and
sprite-depth helpers agree on `GetTransform +0x98`, `SetTransform +0x94`,
`SetRenderState +0xc8`, and `SetTextureStageState +0xfc`; this helper remains
97/97 with 14 clean operands.

2026-07-16 render-pipeline state ownership: overlay and sprite-depth begin/end
helpers now share the canonical saved view/projection matrices instead of four
function-local declarations. This producer/restore family remains exact;
overlay begin is 97/97 with all 14 operands clean.
