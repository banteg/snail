# initialize_direct3d_renderer @ 0x4129c0

Composition root for the recovered Direct3D renderer lifecycle:

- seeds renderer and mouse-window defaults through
  `initialize_direct3d_renderer_defaults`;
- creates the Direct3D8 device with presentation-interval mode zero;
- allocates one eight-vertex FVF `0x142` `ObjectRenderBuffers` pool slot and
  stores that borrowed slot directly as `g_direct3d_renderer.renderer_state`
  (`+0xbb88`); its buffer at `+0x08` is the transient
  sprite/immediate-quad vertex buffer. The former duplicate `RendererState`
  view described the same 12-byte object and has been removed.

## 2026-07-15 Binary Ninja replay

The wrapper now reads back as `uint8_t __cdecl()` and composes all three steps
through `&g_direct3d_renderer`: defaults, device creation, and the nested vertex
factory at offset zero. The resulting buffer is stored on the same singleton as
`renderer_state`, preserving one ownership root across initialization.
