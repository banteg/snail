# measure_font_text_width

Initial scratch for the atlas-width accumulator at `0x449e90`.

Current Wibo result is 81.67%, 60/60 instructions, 39/60 prefix, and five
masked operands ok. Rewriting the body as native-style font lanes recovers the
saved-`ebp` text cursor, `esi` font id, the delayed `ebx`/`edi` saves inside the
non-empty path, the argument-home width accumulator, and the split
`font * 0x20a` glyph lane / `font * 0x828` sheet-offset lane.

The remaining residual is the trailing-space adjustment after the main loop:
native keeps the `font_slot_index_for_char(' ')` result in `al`, recomputes the
font lanes, then sign-extends into `eax`; VC6 sign-extends earlier and uses
`eax`/`ecx` for the sheet/glyph lanes. Tail-only attempts to delay the cast or
name a separate trailing accumulator regressed the prologue by forcing an early
`edi` save, so keep the accepted lane form.

Recovered relationships:

- Uses the exact `font_slot_index_for_char` mapper for each text byte.
- `FontSheet` stride is `0x828`; glyph width lanes begin at
  `FontSheet +0x40c` (`data_777704` for font 0).
- Per-font spacing and width scale live at `+0x818` and `+0x81c`.
- The return includes a trailing-space adjustment using the space glyph width
  and `(1.0 - width_scale)`.

2026-06-20 lane-shape update: the scratch now indexes `g_font_sheets` through
the same decompiler-visible narrow lanes used by `measure_font_text_width` and
`draw_font_text_instance`. The reference manifest now gives `g_font_sheets`
its `0x828` extent, so the raw `+0x40c`, `+0x818`, and `+0x81c` relocations
audit cleanly instead of appearing as unresolved symbol+addend operands.

2026-06-20 tail-width fix: keeping the trailing space slot as a `char` local
instead of immediately widening it to `int` gives VC6 the native schedule after
`font_slot_index_for_char(' ')`: both font lanes are recomputed from `font_id`
while the returned glyph remains live in `al`, then it is sign-extended for the
final glyph-width lookup. Focused Wibo is now exact: 100.00%, 60/60
instructions, 60/60 prefix, and 9 clean masked operands.
