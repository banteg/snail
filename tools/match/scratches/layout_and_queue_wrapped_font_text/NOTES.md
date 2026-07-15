# layout_and_queue_wrapped_font_text

Initial relationship scratch for the frontend wrapped-text layout helper at
`0x44abe0`.

Recovered relationships:

- Text is split on the native `>` delimiter into a 0x400-byte stack line
  buffer. Empty lines still advance the output height.
- The helper measures each line with `measure_font_text_width`, optionally queues
  it through `queue_font_text_instance`, and returns the computed x/y/width/
  height through four output pointers.
- `measure_only` suppresses queueing. `pulse_alpha` overwrites the copied
  `tColour::a` with `sine(cursor_y * 0.00654498488f)` before queueing.
- The line step uses `FontSheet::height_scale * spacing_scale * line_marker_y *
  text_scale`.

Initial match: 39.87%, 146 candidate instructions versus 155 target
instructions. The residual is stack-frame/local placement plus branch-shape
around line copying and the measure-only/pulsed-alpha gates. No masked operands
were unresolved or mismatched in the initial run.

2026-06-21 single-cursor layout pass:

- Rewriting the copy path as one outer loop with a persistent `out` cursor,
  reset only after a `>` delimiter or `NUL`, recovers the native line-buffer
  topology. This preserves empty-line height advancement while avoiding the
  earlier nested copy loop that rebuilt the line cursor for each segment.
- The native max-width update is strict (`right > max_right`), not `>=`.
  Combining the single-cursor loop with the strict comparison improves the
  focused matcher to 88.39%, with exact 155/155 instruction count, a 22/155
  prefix, and nine clean masked operands.
- Spelling the line-step through direct `g_font_sheets[font_id]` field reads
  recovers the native offset-loop shape and raises the score to 94.19%, but the
  plain expression swaps the `height_scale` and `line_marker_y` masked operands.
  The retained explicit `line_height` staging keeps the 94.19% score while
  clearing the audit to 12 clean masks and no mismatches.
- A dedicated pulse-alpha temporary and register/copy variants for the line
  cursor are codegen-neutral. Hoisting a long-lived `FontSheet*` outside the
  delimiter block regresses to 53.85% by expanding the frame to `0x420`.
- 2026-06-21 local-initialization retry: separating the `max_right`,
  `cursor_y`, `source`, and `out` initializers, moving `source` before the
  floats, and adding `register` hints for the text cursors are neutral or worse.
  The retained residual remains early local store order and line-buffer cursor
  register choice, not a missing line-layout branch.

## 2026-07-14 font queue ownership closure

Both decompilers now expose the typed `FontSheet` line-step expression through
`height_scale`, `spacing_scale`, and `line_marker_y`, and the queue call resolves
to the recovered void `queue_font_text_instance` owner. The focused matcher is
unchanged at `94.19%` (`155/155`, 12 clean operands); its residual is still the
documented local/cursor scheduling shape, not missing ownership or behavior.
