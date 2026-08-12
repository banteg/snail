# initialize_global_font3d_bods @ 0x449c20

Startup loop constructs exactly 128 `BodBase` objects beginning at
`g_font3d_bods` with the recovered `sizeof(BodBase) == 0x38` stride. This is
direct ownership proof for the complete 3D-font BOD pool rather than a size
inference from neighboring globals.

## 2026-07-14 fixed glyph-runtime ownership

The BOD bank, adjacent scale bank, and four 128-lane `FontSheet` arrays now
share `FONT_GLYPH_CAPACITY` through `font3d_runtime.h`. This removes the
font-specific global from generic `bod_types.h`, co-locates the two materialized
glyph banks, and lets the constructor loop derive its extent from the owned BOD
array itself.

The normalized listings remain byte-identical for the exact initializer
(`0b95a7d742f16965bd6e86664c75020a5940c59b8d72d02b8556a72883f45e17`),
the 96.83% materializer
(`06306b4e1ad9d847b7000f5ce0554bf9033bc87df9c3e2b5c30e1092bef1c0b1`),
and the 88.31% intro-screen consumer
(`3a5965ee6e0119c7d73e491ca96d3c6acce785dcb6dea1c07c843752685b6c61`).

## 2026-08-12 Font source-unit recovery

The Android symbol table retains the local constructor name
`_GLOBAL__I_Font.cpp`. Its body first constructs the complete `RFont3D` BOD
bank and then walks the `FontPrintBuffer` bank, so it binds both startup loops
to the same authored source file rather than merely placing them near ordinary
Font functions. The independent iOS source catalog maps `Font.cpp` symbols to
`Font.o`; together these recover `Font.o` for this Windows body and its direct
CRT thunk at `0x449c10`.

Windows remains authoritative for its 128-entry count and 0x38-byte BodBase
stride. Android uses its own 44-byte cRBod stride, so no mobile layout is
transferred. The exact Windows 11/11 body and 1/1 thunk are unchanged.
