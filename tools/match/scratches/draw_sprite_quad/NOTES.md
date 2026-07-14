# draw_sprite_quad

Mid-size renderer scratch for `draw_sprite_quad` @ `0x4137f0`.

Current recovered relationships:

- `arg1` is a `Vec3*` world position used only to build the world transform.
- `arg2` is the `Sprite*` record. This corrects the misleading decompiler `float`
  parameter and keeps `configure_sprite_render_state(sprite)` consistent with
  the native call.
- `Sprite +0x1c` is the current texture ref, `+0x28` is the draw-mode lane read
  by `configure_sprite_render_state`, `+0x2c..+0x38` is `Color4f`, `+0x60/+0x64`
  are size endpoints, `+0x68` is progress, `+0x7c` is facing angle, and
  `+0x88` is the rotated-corner scale/stretch lane.
- The 0x60-byte locked buffer is four 0x18-byte vertices:
  `float x, y, z; uint32 color; float u, v`.
- Those records are the shared, size-asserted `ObjectRenderVertex` FVF `0x142`
  payload rather than a sprite-private type. The same renderer-owned staging
  buffer and record are used by the immediate textured-quad path.
- The transform callsite targets `j_sub_44fd5c` @ `0x44fd8a`, a `jmp
  dword [0x4acea0]` thunk used by both `draw_sprite_quad` and `sub_411e10`.
  That is semantically `D3DXMatrixTranslation`, not a direct call to the curated
  body symbol `initialize_translation_matrix` @ `0x44fd90`.
- Normalized instruction stream is exact under the standard toolchain: 259/259
  instructions, 100.00% prefix. The renderer globals and D3DX thunk are curated
  in `analysis/symbols/gameplay-references.json`.

Open matching issues:

- Vector and matrix call surfaces still retain the narrow views needed by this
  helper. The Direct3D device no longer does: its recovered vtable slots are
  shared through `direct3d_device8_view.h`.
- The no-op color constructor at `0x44db50` is modeled locally as
  `ColorBGRA8::noop_this_constructor`; it is a real identity helper
  (`mov eax, ecx; ret`) already curated as a shared reference symbol.

2026-06-18 vector alias cleanup: the draw-position argument now aliases the
shared `Vector3` type. Focused Wibo stays exact at `100.00%`, `259/259`, with
`29 ok` masked operands.

2026-07-11 renderer-state owner closure: the transient sprite vertex buffer is
now reached as `g_direct3d_renderer.renderer_state->sprite_vertex_buffer`.
Manifesting the renderer's proven `0xbcc0` extent maps the emitted
`g_direct3d_renderer+0xbb88` relocation back to the interior renderer-state
reference. The full 259/259 stream and all 29 operands remain exact.

2026-07-14 shared vertex ownership: removed the private `SpriteVertex`
lookalike and used the common `ObjectRenderVertex` payload directly. The exact
259/259 sprite renderer is retained as the consolidation's regression oracle.
