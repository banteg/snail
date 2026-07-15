# restore_texture_ref_stage_states @ 0x4143c0

Direct3DRenderer member called only after a device reset. It walks the owned
`TextureRefList` by its proven 0xa4-byte entry stride, rebinds each parallel
`g_d3d_texture_slots[index]` handle to stage zero, and restores stage state.

`TEXTURE_REF_HAS_ALPHA` selects the six alpha-stage settings, while
`TEXTURE_REF_WRAP_ADDRESSING` selects address mode 1 instead of the default 3
for both U and V. The native function deliberately binds through the member's
device pointer but writes stage state through the shared device alias.

2026-07-14 ownership pass: this is now declared directly on the canonical
`Direct3DRenderer` owner. The former reset-only derived class added no layout
or behavior and merely duplicated the real receiver. The consolidated method
remains exact at 110/110 instructions with all 15 masked operands clean.

## 2026-07-15 Binary Ninja replay

The refreshed artifact resolves the member's first device access through
`renderer->device`, the texture bank as `Direct3DTexture8**`, and all absolute
device accesses as `g_direct3d_renderer.device`. Binary Ninja retains some
indirect-call temporary noise, but the parent ownership is now explicit and
guarded without inventing an interior global.
