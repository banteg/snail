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

2026-07-25 IDA replay closure: bounded invalidation now refreshes the texture
binding helper after installing the shared renderer and texture owners. IDA
therefore exposes `TextureRef::slot_index`, `TextureRef::flags`, the current
texture and slot-bank globals, the bind counter, and every device call through
`g_direct3d_renderer.device`. The exact 62/62 scratch is unchanged.

## 2026-07-26 mobile G0 owner and platform ABI

Android and iOS retain this helper as the void `G0BindTexture(int)` owner.
Their bodies preserve `gBindTextureRefLast`, `gBindCount`, the `0x1000` wrap
flag, and the same redundant-bind suppression before selecting wrap versus
clamp state. Mobile passes a texture-list index; Windows passes the
corresponding `TextureRef*` and resolves its Direct3D slot internally. The
stable Windows pointer prototype is therefore retained while the authored
function and global names are recorded as aliases. Focused matching remains
exact at 62/62 instructions with all 11 operands clean.

## 2026-07-29 primary cRTexture binding record

The Windows pointer ABI is now expressed as `cRTexture*`. Mobile proves the
record name through multiple exact symbols, while this exact desktop consumer
independently proves `slot_index +0x8c`, `flags +0x00`, and the borrowed
current-texture lifetime. The platform-specific pointer-versus-index calling
boundary remains unchanged, as do the exact 62/62 instructions and 11 clean
operands.
