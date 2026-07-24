# attach_render_camera_source

Initial scratch for the tiny viewport camera setter at
`0x44e900`.

Recovered relationships:

- Only xrefed from `initialize_game_assets_and_world`.
- Stores a borrowed camera at viewport `+0x20`, then sets active flag bit 0 in
  the viewport flags at `+0x08`.
- The owning array is five `0x28`-byte viewports at `Game + 0x5b4`;
  `render_game_frame` counts and sorts active viewports before calling
  `render_camera`.
- The two startup callsites attach cameras embedded at `Game +0x1c4` and
  `Game +0x3bc` to viewports 1 and 4 respectively. These are the owned
  `camera +0xa0` subobjects of `GamePlayer[0]` and `GamePlayer[1]`, whose
  0x1f8-byte records begin at root `+0x124/+0x31c`. Neither viewport allocates
  or frees its camera.

iOS provenance names this exact ownership edge
`cRViewport::SetCamera(cRCamera*)`, while the paired viewport initializer is
`cRViewport::cRViewport()`. The Windows helper keeps its stable descriptive
name, while the owning type is now the cross-port `Viewport` and its borrowed
camera field is a typed `RenderCamera*`.

Focused Wibo result: 100.00%, 6/6 instructions, no masked operands.

## 2026-07-24 original viewport owner replay

The paired mobile symbols and the exact five-record Windows constructor loop
now promote the provisional render-camera-slot view to the original
`cRViewport` owner. Binary Ninja and IDA both receive the exact
`Viewport*`/borrowed `RenderCamera*` method ABI, so the two startup calls are
whole-owner method calls rather than references to the untouched dword at
viewport `+0x00`. That dword remains unnamed: its only apparent field xrefs
are the two `lea` instructions that form complete viewport receivers.
