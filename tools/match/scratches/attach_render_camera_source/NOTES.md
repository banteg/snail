# attach_render_camera_source

Initial scratch for the tiny render-camera slot attachment helper at
`0x44e900`.

Recovered relationships:

- Only xrefed from `initialize_game_assets_and_world`.
- Stores the source render object at slot `+0x20`, then sets active flag bit 0
  in the slot flags at `+0x08`.
- The owning array is five `0x28`-byte slots at `Game + 0x5b4`; `render_game_frame`
  counts and sorts active slots by fields inside that array before calling
  `render_camera`.

The `RenderCameraSlot` name is conservative: it reflects the render-frame
consumer, but backdrop/landscape setup still needs a larger class pass before
this should be treated as the final source name.

Focused Wibo result: 100.00%, 6/6 instructions, no masked operands.
