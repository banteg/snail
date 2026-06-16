# draw_font_text_instance

Initial relationship scratch for the text queue renderer at `0x44a360`.

Recovered relationships:

- The native argument is a `FontQueueEntry*`; the old `float arg1` decompiler
  type is wrong.
- `horizontal_align` values `1/2/3` adjust the local x cursor from `anchor_x +
  320.0f`, with value `2` centering by half the measured width.
- Each glyph maps through `font_slot_index_for_char`, uses `FontSheet` atlas
  UVs/texture-page lanes, then calls `draw_textured_quad_immediate`.
- `FontSheet::font_kind` is the positive shadow offset used only when
  `text_wave_enabled` is set; it is not a font-family enum.
- Slot `0x35` advances the cursor without drawing.

Initial match: 32.66%, 224 candidate instructions versus 272 target
instructions. The residual is mostly source scheduling/register shape around
the glyph loop, shadow draw, and per-glyph advance. No masked operands were
unresolved or mismatched in the initial run.
