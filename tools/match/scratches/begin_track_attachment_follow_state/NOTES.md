# Residual diff — 94.55%, 28/27 insns

The heading-table tail now keeps the ×61 index in `edx`, loads
`data_4df904` into `ecx`, and schedules the `pop esi` like the target.
The remaining miss is that the typed row-heading table pointer materializes
the table base with `add ecx, ADDR`, then loads `[ecx + edx*4]`; the target
folds the same table base into the final memory displacement as
`[ecx + edx*4 + ADDR]`. Semantics and all offsets are pinned.

2026-06-13 pin audit: focused matcher still verifies 94.55%, 28/27 insns.
Keep this pinned; the remaining miss is only equivalent table-base folding.

2026-06-14 breadth pass: re-tested the table-base residual with typed
`GameImage` row-heading-table field forms. Direct field indexing folds the
global offset but regresses register ownership to 85.19%; a `GameImage*` local
improves that only to 88.89%; a `float*` field pointer keeps 94.55% but leaves
a dead `add ecx, ADDR`; and a scalar `float heading` local wrongly lowers
through x87. Keep the current table-pointer spelling until a source-plausible
form preserves both native index ownership and folded displacement.

Recovered: FollowState layout (+0x00 active, +0x04 template, +0x08 cell,
+0x0c sample_index, +0x10 progress = z - cell anchor z, +0x14
vertical_offset = y - 0.49f, +0x38 player); `get_track_cell_row_index`
is thiscall on the cell; the cell shares the +0x18 anchor-z / +0x38
template offsets with the golb path struct (likely sibling types).
