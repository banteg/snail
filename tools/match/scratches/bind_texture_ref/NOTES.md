# bind_texture_ref

- Skips the Direct3D call when the requested `TextureRef` is already bound in
  `g_current_texture_ref`.
- `TextureRef::slot_index` indexes `g_d3d_texture_slots` (`data_5031c8`);
  successful and failed SetTexture attempts both increment
  `g_texture_bind_call_count`.
- `TEXTURE_REF_WRAP_ADDRESSING` (`TextureRef::flags & 0x1000`) selects texture-stage-state value `1`; otherwise
  both stage states are reset to `3`.

2026-07-11 device/type closure: the scratch-local texture device is the shared
IDirect3DDevice8 view (`SetTexture +0xf4`, `SetTextureStageState +0xfc`). The
current texture is consistently `TextureRef*`, and the slot bank is consistently
`Direct3DTexture8**`. The 62/62 instruction stream and 11 operands remain exact.

## 2026-07-15 Binary Ninja replay

Live replay types the argument as `TextureRef*`, names the current-texture and
bind-count globals, recovers `slot_index` and `flags`, and resolves every device
load through `g_direct3d_renderer.device`. The matcher may retain its linker
alias for exact operand comparison, while the analysis database deliberately
keeps `0x502fec` parent-owned.
