# FontPrintReal

`FontPrintReal(cFontPrintBuffer*)` owns the Windows routine at `0x44a360`.
The focused match is exact: 272/272 instructions and 41 clean references.

It resolves alignment, remaps glyphs, selects atlas pages, applies shadow and
wave offsets, draws each glyph, and advances the cursor. Android and iOS both
export the same `Font.o` symbol. Live Windows analysis finds one caller:
`FontPrintRender`.

The directory and manifest retain `draw_font_text_instance` as the stable
matcher identifier.
