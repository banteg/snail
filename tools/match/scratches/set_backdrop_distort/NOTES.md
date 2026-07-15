# set_backdrop_distort @ 0x410c40

Current scratch: 100.00% (73/73 target insns), 14 clean operands.

Seeds the 8x8 backdrop distortion grid from the parsed landscape `Distort:`
scalar.

Recovered layout:

- `Backdrop::distort_cells[64]` starts at `+0x58`.
- each `BackdropDistortCell` has stride `0x18`.
- the helper writes `phase +0x00`, `phase_step +0x04`, `x_offset +0x08`, and
  `y_offset +0x0c`.
- `update_backdrop` writes the derived per-frame `current_x_offset +0x10` and
  `current_y_offset +0x14` terms from sine/cosine, and `render_backdrop`
  consumes those values as warped quad corner offsets.
- border cells (`row == 0`, `row == 7`, `column == 0`, or `column == 7`) are
  hard-zeroed.

Recovered source shape: the authored loops use row and column indices over the
owned `Backdrop::distort_grid[8][8]`, and each store names a
`BackdropDistortCell` field directly. VC6 strength-reduces the row index into
the native `edi += 8` cell-base index while preserving `esi` as the column and
recomputing each branch-local cell address. An `interior` predicate leaves the
randomized path first and the shared border-zero path second, exactly matching
native control flow.

2026-06-21 direct-index retry: removing the `result`/`cell` pointer locals and
repeating the full indexed store expression is codegen-neutral at 50.70%. VC6
still strength-reduces to the moving pointer cursor, so direct source indexing
alone does not recover the native recomputed branch addresses.

2026-06-21 explicit border predicate: hoisting the four edge tests into a
`border` local and spelling the cell offset as `(row + column) * 6` improves the
focused Wibo score to 54.93% with the same clean masks. The remaining mismatch
is still structural: VC6 keeps a moving cell pointer and places one zero-store
case before the random path, while native keeps row/column registers and a
shared zero block after the random path.

## 2026-07-14 distortion-grid extent derivation

The flat seed count, row step, column bound, and final border indices now
derive from `Backdrop::distort_cells/distort_grid`. The normalized listing is
byte-identical
(`ace5b77e797fe52f5ec2b0b4fee88aea2dacc52902eb7ce906c2854452f4c31f`)
at the honest 54.93% result (`69/73`, prefix `3/73`, 14 clean operands).

## 2026-07-15 typed grid recovery

Replacing the flat float-stride approximation with direct
`distort_grid[row][column].field` accesses recovered the authored 8x8 owner and
raised the focused result from 54.93% to 76.71% without changing semantics.
Spelling the four non-border tests as an `interior` predicate then restored the
native randomized-first block order and reached an exact 100.00% match
(`73/73`, prefix `73/73`, 14 clean operands). No volatile state, dummy calls,
or other code-generation-only constructs are present.
