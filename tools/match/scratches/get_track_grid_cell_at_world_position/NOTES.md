# get_track_grid_cell_at_world_position @ 0x43d410

Exact helper: clamps world x to lane `0..7`, clamps world z to runtime row
`0..3199`, and returns the `TrackRowCell` at `game + 0x3bfac8` with stride
`0x54`.

2026-06-16 type pass: return type is now the shared `TrackRowCell*` from
`track_attachment_types.h` instead of `void*`. Focused match remains exact at
`34/34`.

2026-06-16 layout assertion pass: the shared `TrackRowCell` now asserts
`sizeof(TrackRowCell) == 0x54`. This exact accessor pins the row-major cell
stride, and the same stride is used by the builder, fringe, warning-zone, and
row-index scratches.

2026-06-21 subgame-header consolidation: the accessor now lives on the shared
`SubgameRuntime` owner instead of a scratch-local `Game` shell. Focused Wibo
remains exact at `100.00%`, `34/34` instructions, with `3` clean masked
operands.

2026-07-10 owner promotion: the exact return now uses
`&SubgameRuntime::runtime_cells[row][lane]`. It remains `34/34` with three
clean masked operands, proving the fixed 3200 x 8 slab without raw offset math.
