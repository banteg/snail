# measure_font_text_width

Initial scratch for the atlas-width accumulator at `0x449e90`.

Wibo result after casting mapper slots through `char`: 26.17%, 60 target
instructions versus 47 candidate instructions, 0/60 prefix, 3 masked operands
ok. The relationship is still useful, and the cast matches native's
`movsx eax, al` treatment of the `font_slot_index_for_char` result.

Remaining residual is still register/prologue shape: native keeps the text
cursor in saved `ebp`, font id in `esi`, pushes `ebx`/`edi` only for the
non-empty loop, and reuses the argument home for the width accumulator. The
current source keeps the cursor in `edi`, font id in `ebx`, and carries a
`FontSheet*` base instead of the native split glyph-index and sheet-offset
lanes.

Recovered relationships:

- Uses the exact `font_slot_index_for_char` mapper for each text byte.
- `FontSheet` stride is `0x828`; glyph width lanes begin at
  `FontSheet +0x40c` (`data_777704` for font 0).
- Per-font spacing and width scale live at `+0x818` and `+0x81c`.
- The return includes a trailing-space adjustment using the space glyph width
  and `(1.0 - width_scale)`.
