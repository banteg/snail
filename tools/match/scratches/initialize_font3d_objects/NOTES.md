# FontMake3D

`FontMake3D(short)` owns the Windows routine at `0x44ae10`. The recovery is
exact: 126/126 instructions and all 20 references clean.

It materializes one shared render object per glyph, selects the font texture
page, writes vertically flipped UVs, and scales the four vertex X lanes by the
glyph width. Android and iOS both retain the same authored `Font.o` symbol;
their object and font-sheet layouts differ from Windows.

The directory and manifest retain `initialize_font3d_objects` as the stable
matcher identifier.

## 2026-08-14 exact glyph-scale ownership

Each completed glyph now publishes its scale directly to
`g_font3d_scales[index]` instead of routing the store through a temporary
output pointer. This recovers the native tail schedule and leaves the glyph
object, texture-page, UV, and scale owners explicit. Focused matching is
exactly 100.00% (`126/126`, prefix 126) with all 20 references clean.
