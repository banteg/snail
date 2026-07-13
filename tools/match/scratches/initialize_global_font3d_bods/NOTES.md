# initialize_global_font3d_bods @ 0x449c20

Startup loop constructs exactly 128 `BodBase` objects beginning at
`g_font3d_bods` with the recovered `sizeof(BodBase) == 0x38` stride. This is
direct ownership proof for the complete 3D-font BOD pool rather than a size
inference from neighboring globals.
