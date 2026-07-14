# draw_font_text_queue

Initial scratch for the font/2D-quad queue drain at `0x44a730`.

Wibo result: exact 100%, 31/31 instructions, masked operands 4 ok.

Recovered relationships:

- Iterates the `cFontPrintBuffer` array backward from `g_font_queue_count`.
- Masks entry flags against the caller render mask and `0xff000000`.
- Dispatches text entries (`flags & 1`) to `draw_font_text_instance`; queued
  quad entries go to `draw_queued_font_quad_instance`.

Android exports the same routine as `FontPrintRender(int)` and the two callees
as `FontPrintReal(cFontPrintBuffer*)` and
`OSDPrintReal(cFontPrintBuffer*)`. Both ports discard the renderer results, and
the sole Windows render-frame caller discards the queue-drain result, proving
all three authored contracts are `void` despite incidental return registers.
