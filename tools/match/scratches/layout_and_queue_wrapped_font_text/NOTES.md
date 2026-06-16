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
  `Color4f::a` with `sine(cursor_y * 0.00654498488f)` before queueing.
- The line step uses `FontSheet::height_scale * spacing_scale * line_marker_y *
  text_scale`.

Initial match: 39.87%, 146 candidate instructions versus 155 target
instructions. The residual is stack-frame/local placement plus branch-shape
around line copying and the measure-only/pulsed-alpha gates. No masked operands
were unresolved or mismatched in the initial run.
