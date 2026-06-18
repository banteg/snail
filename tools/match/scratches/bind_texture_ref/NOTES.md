# bind_texture_ref

- Skips the Direct3D call when the requested `TextureRef` is already bound in
  `g_current_texture_ref`.
- `TextureRef::slot_index` indexes `g_d3d_texture_slots` (`data_5031c8`);
  successful and failed SetTexture attempts both increment
  `g_texture_bind_call_count`.
- `TextureRef::flags & 0x1000` selects texture-stage-state value `1`; otherwise
  both stage states are reset to `3`.
