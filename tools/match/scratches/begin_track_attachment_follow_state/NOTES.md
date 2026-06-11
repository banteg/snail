# Residual diff — 85.19%, 27/27 insns

Pure register renaming in the heading-table tail: target computes the
×61 index into edx and loads `data_4df904` into ecx; our build swaps the
two. Instruction sequence and addressing are otherwise identical, all
struct offsets and the `g_row_heading_table + game_base + 4*61*row`
addressing confirmed. Semantics fully pinned.

Recovered: FollowState layout (+0x00 active, +0x04 template, +0x08 cell,
+0x0c sample_index, +0x10 progress = z - cell anchor z, +0x14
vertical_offset = y - 0.49f, +0x38 player); `get_track_cell_row_index`
is thiscall on the cell; the cell shares the +0x18 anchor-z / +0x38
template offsets with the golb path struct (likely sibling types).
