# FontPrintRender

`FontPrintRender(int)` owns the Windows routine at `0x44a730`. The focused
match is exact: 31/31 instructions and four clean references.

It drains the font/OSD queue backward, filters entries by the render mask, and
dispatches text records to `FontPrintReal` and quad records to `OSDPrintReal`.
Android and iOS both export the same `Font.o` symbol. Live Windows analysis
finds one render-frame caller.

The directory and manifest retain `draw_font_text_queue` as the stable matcher
identifier.
