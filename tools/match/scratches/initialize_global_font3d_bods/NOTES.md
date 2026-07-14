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
