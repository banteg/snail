# initialize_global_font3d_bods_thunk @ 0x449c10

CRT constructor-table entry at `0x4a1060`. The shipped body is a tail jump to
the adjacent fixed-array constructor loop at `0x449c20`; keeping this boundary
separate records both the linker-owned registration point and authored global.
