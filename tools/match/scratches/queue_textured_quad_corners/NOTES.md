# queue_textured_quad_corners

Initial scratch for the arbitrary four-corner textured quad queue helper at
`0x44aac0`.

Wibo result: 64.29%, 69 target instructions versus 71 candidate instructions,
masked operands 11 ok. The helper's entry/overflow gates, queue stores, and
caller stack layout are pinned; remaining residual is the same shared-zero
epilogue distance plus queue-store register scheduling seen in the other quad
producers.

Recovered relationships:

- Uses the shared `g_render_queue_active` gate and `g_font_queue_count` maximum
  as the other 2D queue producers.
- Appends a quad entry (`flags | 2`) into the shared `FontQueueEntry` array.
- Stores texture id (`+0x50`), all four authored corner pairs (`+0x04/+0x08`,
  `+0x10/+0x14`, `+0x1c/+0x20`, `+0x28/+0x2c`), explicit UV bounds
  (`+0x5c..+0x68`), `Color4f` (`+0x6c`), layer (`+0x7c`), and blend
  (`+0x80`).
- Both known callers pass two zero stack slots after the corner pairs and
  before the flags/color arguments; the helper does not consume them.
- Clears the axis-aligned width/height lanes (`+0x54/+0x58`) so the draw
  forwarder uses the stored corner coordinates instead.
