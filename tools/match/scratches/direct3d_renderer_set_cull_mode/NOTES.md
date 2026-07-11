# direct3d_renderer_set_cull_mode

Renderer-wrapper cull-state method at `0x411700`.

Current Wibo result: 100.00%, 16/16 instructions, no masked operands.

Recovered relationships:

- Reads the wrapped Direct3D device pointer at `Direct3DRenderer +0xbb94`.
- Maps a nonzero cull selector to render state `0x16 = 3`.
- Maps a zero cull selector to render state `0x16 = 1`.

This is the private method called by the cdecl `set_cull_mode` wrapper used by
`render_object`.

2026-07-11 owner closure: the formerly anonymous renderer prefix is now
bounded by consecutive interior globals. The 3000-entry vertex pool occupies
`+0x0000..+0x8ca4`, the embedded 3000-entry index pool ends at `+0xbb88`, the
renderer-state pointer is `+0xbb88`, and the device used here is `+0xbb94`.
Those fields preserve the proven `0xbcc0` total renderer size and the method
remains instruction-exact.
