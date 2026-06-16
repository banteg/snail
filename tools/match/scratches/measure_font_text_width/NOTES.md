# measure_font_text_width

Initial scratch for the atlas-width accumulator at `0x449e90`.

Wibo result: 22.86%, 60 target instructions versus 45 candidate instructions.
The relationships are useful, but the residual is still register/prologue shape:
native keeps the text cursor in saved `ebp`, font id in `esi`, and reuses the
argument home for the width accumulator.

Recovered relationships:

- Uses the exact `font_slot_index_for_char` mapper for each text byte.
- `FontSheet` stride is `0x828`; glyph width lanes begin at
  `FontSheet +0x40c` (`data_777704` for font 0).
- Per-font spacing and width scale live at `+0x818` and `+0x81c`.
- The return includes a trailing-space adjustment using the space glyph width
  and `(1.0 - width_scale)`.
