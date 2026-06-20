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

2026-06-19 folded-load audit: focused matcher still verifies 94.55%,
27/28 instructions, 23/27 prefix, and 3 clean masked operands. Re-tested direct
raw loads from the real row-heading table symbol, an explicit `g_game_base`
local, a byte-offset local, raw `installed_heading_bits`, a `game_words`
dword-table view, and the authored `row * 60 + row` spelling. The direct forms
fold the `g_row_heading_table` displacement but consistently move the scaled
row index from native `edx` to `ecx` and drop to 85.19%; moving the template
reload after the table load regresses further to 78.57%. The raw-bit assignment
through the retained table pointer is codegen-neutral at 94.55%, so keep the
clear float `installed_heading_delta` assignment. Resume only with a new
source-owner lead that can preserve both native `edx` index ownership and the
folded table displacement.

2026-06-20 larger attachment retry: focused Wibo still reports 94.55%,
28/27 candidate/target instructions, 23/27 prefix, and three clean masked
operands. Rechecking the direct byte-address load again folds the displacement
but drops to 85.19% by moving the scaled row index into `ecx`. A raw `int*`
table, a named `installed_heading_bits` local, and a byte-base `char* table`
are all codegen-neutral at 94.55% and leave the same separate `add ecx, ADDR`.
Modeling the recovered table as `float rows[][61]` is semantically tempting but
regresses to 75.00% by disturbing saved-register ownership. Keep the flat
float-table source until a form preserves native `edx` index ownership and the
folded table displacement together.

Recovered: FollowState layout (+0x00 active, +0x04 template, +0x08 cell,
+0x0c sample_index, +0x10 progress = z - cell anchor z, +0x14
vertical_offset = y - 0.49f, +0x38 player); `get_track_cell_row_index`
is thiscall on the cell; the cell shares the +0x18 anchor-z / +0x38
template offsets with the golb path struct (likely sibling types).
