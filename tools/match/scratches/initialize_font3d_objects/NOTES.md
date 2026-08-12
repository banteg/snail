# FontMake3D

`FontMake3D(short)` owns the Windows routine at `0x44ae10`. The recovery is
semantic-complete at 99.21%: 126/126 instructions and all 20 references clean.

It materializes one shared render object per glyph, selects the font texture
page, writes vertically flipped UVs, and scales the four vertex X lanes by the
glyph width. Android and iOS both retain the same authored `Font.o` symbol;
their object and font-sheet layouts differ from Windows. The only remaining
delta is the order of two independent tail cursor increments.

The directory and manifest retain `initialize_font3d_objects` as the stable
matcher identifier.
