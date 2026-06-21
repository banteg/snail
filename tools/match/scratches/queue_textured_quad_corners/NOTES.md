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

2026-06-20 render-queue chunk: removing the final `return 0` matches the
decompiler's incidental-return shape in spirit, but Wibo aborts through the
MSVC missing-return warning path (`missing import lstrcpynA`) before producing
an object. This is the same harness limitation documented for other incidental
return scratches, so the explicit final zero remains. The residual masked
operand mismatches are still queue-store scheduling around the UV/layer/blend
tail, not evidence that the two unused zero arguments are consumed.

2026-06-21 count-store sweep: moving `g_font_queue_count = index + 1` later in
the entry-fill sequence improves focused Wibo from 64.29% to 87.14%, with 71
candidate instructions versus 69 target instructions and 18 clean masked
operands. The best-scoring spelling publishes the count after the final corner
coordinate (`y3`) and before clearing the axis-aligned width/height lanes;
placing it after the height clear removed the residual masked mismatches but
scored lower at 81.43%. Keep the corner-coordinate placement as the retained
shape for now.
