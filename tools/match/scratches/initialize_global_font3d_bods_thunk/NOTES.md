# initialize_global_font3d_bods_thunk @ 0x449c10

CRT constructor-table entry at `0x4a1060`. The shipped body is a tail jump to
the adjacent fixed-array constructor loop at `0x449c20`; keeping this boundary
separate records both the linker-owned registration point and authored global.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`BodBase g_font3d_bods[FONT_GLYPH_CAPACITY]`, which replaces the hand-written
wrapper and initializer function. Both scratches compile the one source file,
the body as `_$E1` and the thunk as `_$E2` in the whole Font TU (VC6 numbers
each initialized declaration's pair in steps of three). Here the existing
out-of-line `cRBod::cRBod()` runs once per element in VC6's inline array loop.
Both functions stay exact, with every masked operand resolved through the
`function_alias` reference entries.
