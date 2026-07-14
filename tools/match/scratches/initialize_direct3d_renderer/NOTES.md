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
