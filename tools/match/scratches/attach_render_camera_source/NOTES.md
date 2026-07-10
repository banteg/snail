# attach_render_camera_source

Initial scratch for the tiny render-camera slot attachment helper at
`0x44e900`.

Recovered relationships:

- Only xrefed from `initialize_game_assets_and_world`.
- Stores a borrowed camera at slot `+0x20`, then sets active flag bit 0 in the
  slot flags at `+0x08`.
- The owning array is five `0x28`-byte slots at `Game + 0x5b4`; `render_game_frame`
  counts and sorts active slots by fields inside that array before calling
  `render_camera`.
- The two startup callsites attach cameras embedded at `Game +0x1c4` and
  `Game +0x3bc` to slots 1 and 4 respectively. These are the owned
  `camera +0xa0` subobjects of `GamePlayer[0]` and `GamePlayer[1]`, whose
  0x1f8-byte records begin at root `+0x124/+0x31c`. Neither slot allocates or
  frees its source.

iOS provenance names this exact ownership edge
`cRViewport::SetCamera(cRCamera*)`, while the paired slot initializer is
`cRViewport::cRViewport()`. The Windows harness keeps its stable descriptive
names, but the shared source pointer is now a typed `RenderCamera*` rather than
an owning or untyped render-object pointer.

Focused Wibo result: 100.00%, 6/6 instructions, no masked operands.
