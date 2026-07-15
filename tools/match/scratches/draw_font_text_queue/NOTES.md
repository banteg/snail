# draw_font_text_queue

Initial scratch for the font/2D-quad queue drain at `0x44a730`.

Wibo result: exact 100%, 31/31 instructions, masked operands 4 ok.

Recovered relationships:

- Iterates the `cFontPrintBuffer` array backward from `g_font_queue_count`.
- Masks entry flags against the caller render mask and `RENDER_SCENE_MASK`.
- Dispatches text entries (`flags & 1`) to `draw_font_text_instance`; queued
  quad entries go to `draw_queued_font_quad_instance`.

Android exports the same routine as `FontPrintRender(int)` and the two callees
as `FontPrintReal(cFontPrintBuffer*)` and
`OSDPrintReal(cFontPrintBuffer*)`. Both ports discard the renderer results, and
the sole Windows render-frame caller discards the queue-drain result, proving
all three authored contracts are `void` despite incidental return registers.

2026-07-14 shared scene-mask ownership: startup assigns one high-byte scene bit
to each of the five render camera slots, and `cRGame::Render()` passes that
slot word to this queue drain after BOD and sprite filtering. The mask is now
shared with those consumers instead of repeated as a font-local literal. The
focused object remains exact at 31/31 instructions with four clean references.

## 2026-07-14 font queue ownership closure

Both analysis databases now type the backward cursor as a
`cFontPrintBuffer*`, resolve the queue base as `g_font_queue`, and dispatch its
entries through the two recovered void draw owners. Binary Ninja's one-past
cursor still renders one subtraction as an `__offset(-0x84)` artifact, while
IDA expresses the same loop as `v1[-1]`; neither is evidence for another
record type. The matcher source remains exact at `31/31`.
