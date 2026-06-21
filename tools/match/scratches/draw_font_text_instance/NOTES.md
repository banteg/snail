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

2026-06-21 glyph-loop shape pass:

- Reading the initial atlas UV/page fields directly through
  `g_font_sheets[font_id]`, while keeping a `FontSheet*` for the later texture,
  sizing, and advance fields, improves the per-glyph setup from 32.66% to
  33.47%.
- Replacing the staged `ch` local with a direct cursor-deref loop recovers the
  native `0x38` frame and the first instruction prefix. Combined with the
  direct initial atlas reads, the focused matcher improves to 35.67%, with
  227/272 candidate instructions, a 1/272 prefix, and 19 clean masked operands.
- Fully removing the `FontSheet*` pointer only reaches 32.68%, and combining it
  with the direct atlas reads stays there. Delaying the sheet pointer past the
  direct reads was not a valid source shape because later advance code still
  needs the sheet outside the draw block.
- Register hints, a copied `FontQueueEntry*`, a copied or volatile text cursor,
  and register/copy combinations are all codegen-neutral at 35.67%; they do not
  move the top-level entry pointer from candidate `edi` to native `esi`.
- Returning zero regresses to 35.34%, and explicit byte/int return locals are
  neutral. The retained `return *cursor` keeps the best score even though the
  remaining tail still has extra return-value materialization.
