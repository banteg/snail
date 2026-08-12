# cRBackdrop::SetDistort @ 0x410c40

Exact Windows member: 73/73 instructions with all 14 masked operands clean.
Android and iOS independently preserve `cRBackdrop::SetDistort(float)` and the
same random seed hierarchy.

The method seeds the owned 8x8 `BackdropDistortCell` grid. Border cells are
zeroed; interior cells receive phase, phase step, and signed x/y amplitudes
scaled by the landscape `Distort:` value. `cRBackdrop::AI` derives each cell's
current offsets, and the renderer consumes them as warped quad corners.

Direct `distort_grid[row][column]` field accesses and an `interior` predicate
are the exact source shape; no compiler-coercion constructs are retained.
