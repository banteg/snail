# initialize_render_camera_slot

Initial scratch for the render-camera slot initializer at `0x44e920`.

Recovered relationships:

- Called five times from `construct_game_runtime` over a `0x28`-byte stride at
  `Game + 0x5b4`.
- Initializes slot flags, viewport origin, viewport size, one `0.8725f` lane,
  and the draw-world byte at `+0x24`; it intentionally leaves `+0x00`,
  `+0x04`, and the source pointer at `+0x20` for the owning runtime setup.
- `render_game_frame` later scans these five slots by `flags & 1`, sorts by
  `sort_key +0x04`, and passes `+0x0c/+0x10/+0x14/+0x18`, source-derived camera
  state, and `draw_world +0x24` into `render_camera`.
- iOS names the constructor `cRViewport::cRViewport()` and its paired source
  setter `cRViewport::SetCamera(cRCamera*)`, proving the fixed array owns
  viewport records while each `+0x20` pointer only borrows a camera.

The `unknown_1c` lane is kept generic for now. The immediate value is exactly
`0x3f5f5c28` (`0.8725f`), but the render consumer that gives it a stable
semantic name is not yet matched.

Focused Wibo result: 100.00%, 11/11 instructions, no masked operands. The
source literal must be `0.87249994f`; spelling it as `0.8725f` rounds to
`0x3f5f5c29`, one bit above native.

The scratch uses `END=0x44e944` because the manifest gap after this helper
contains uncurated renderer/math thunks before `initialize_translation_matrix`;
counting the whole gap as this constructor would overstate matched bytes.
