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
- The transform callsite targets `j_sub_44fd5c` @ `0x44fd8a`, a `jmp
  dword [0x4acea0]` thunk used by both `draw_sprite_quad` and `sub_411e10`.
  That is semantically `D3DXMatrixTranslation`, not a direct call to the curated
  body symbol `initialize_translation_matrix` @ `0x44fd90`.
- Normalized instruction stream is exact under the standard toolchain: 259/259
  instructions, 100.00% prefix. The renderer globals and D3DX thunk are curated
  in `analysis/symbols/gameplay-references.json`.

Open matching issues:

- The scratch intentionally keeps renderer and `Sprite` layouts local. Promote
  only after more sprite draw/update callsites agree on names and extents.
- The no-op color constructor at `0x44db50` is modeled locally as
  `ColorBGRA8::noop_this_constructor`; it is a real identity helper
  (`mov eax, ecx; ret`) already curated as a shared reference symbol.
