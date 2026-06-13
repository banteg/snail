# Residual diff — 94.55%, 28/27 insns

The heading-table tail now keeps the ×61 index in `edx`, loads
`data_4df904` into `ecx`, and schedules the `pop esi` like the target.
The remaining miss is that the typed row-heading table pointer materializes
the table base with `add ecx, ADDR`, then loads `[ecx + edx*4]`; the target
folds the same table base into the final memory displacement as
`[ecx + edx*4 + ADDR]`. Semantics and all offsets are pinned.

2026-06-13 pin audit: focused matcher still verifies 94.55%, 28/27 insns.
Keep this pinned; the remaining miss is only equivalent table-base folding.

Recovered: FollowState layout (+0x00 active, +0x04 template, +0x08 cell,
+0x0c sample_index, +0x10 progress = z - cell anchor z, +0x14
vertical_offset = y - 0.49f, +0x38 player); `get_track_cell_row_index`
is thiscall on the cell; the cell shares the +0x18 anchor-z / +0x38
template offsets with the golb path struct (likely sibling types).
