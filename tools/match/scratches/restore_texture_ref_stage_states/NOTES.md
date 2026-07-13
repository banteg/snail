# restore_texture_ref_stage_states @ 0x4143c0

Direct3DRenderer member called only after a device reset. It walks the owned
`TextureRefList` by its proven 0xa4-byte entry stride, rebinds each parallel
`g_d3d_texture_slots[index]` handle to stage zero, and restores stage state.

`TEXTURE_REF_HAS_ALPHA` selects the six alpha-stage settings, while
`TEXTURE_REF_WRAP_ADDRESSING` selects address mode 1 instead of the default 3
for both U and V. The native function deliberately binds through the member's
device pointer but writes stage state through the shared device alias.

Its narrow reset-only class view inherits the full shared renderer layout, so
the native `ECX` receiver and `device` ownership stay explicit without adding a
method declaration to every scratch that includes the broad renderer header.
