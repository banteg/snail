# OSDPrintReal

`OSDPrintReal(cFontPrintBuffer*)` owns the Windows routine at `0x44a6d0`.
The focused match is exact: 41/41 instructions and two clean references.

It forwards the queued quad corners, dimensions, UVs, color, blend mode, and
rotation to the immediate textured-quad renderer. Android retains the same
`Font.o` symbol; the iOS corpus has no retained export. Live Windows analysis
finds one caller: `FontPrintRender`.

The directory and manifest retain `draw_queued_font_quad_instance` as the
stable matcher identifier.
