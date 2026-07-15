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

## 2026-07-14 runtime-grid dimensions

The fixed grid dimensions now have one shared owner:
`SUBGAME_RUNTIME_ROW_CAPACITY == 3200` and
`SUBGAME_TRACK_LANE_COUNT == 8`. `SubgameRuntime::runtime_cells` and
`runtime_rows` use those capacities directly, while row lookup, world-space
clamps, neighbor queries, edge selection, fringe promotion, fringe building,
the main subgame update, and the construction size ledger derive their bounds,
strides, or offsets from the same declarations.

This is source-shape and ownership recovery only. The normalized candidate
hashes remain byte-identical:

- `get_track_cell_row_index`: `2563e782fc88fc56e254f7e47932b51982fb1cbedb38cce7051d2d74b0583754`
- `get_track_grid_cell_at_world_position`: `cca36278acf8da7bc52fa3ae043d7f516fe1b6cc4cd2b36af53db1c8f43babe5`
- `is_neighbor_cell_solid`: `d0910a35a93e430b67a8896195a40f05c237d4f09fe5d911c50e99a5a10ac3b8`
- `select_track_tile_edge_variants`: `33fef27d87930422987a6bf1134f5d7f32d99fe02ae0466bf1d0b54c9cdd709d`
- `promote_track_tiles_to_fringe_variants`: `b4baae3d599d919dd03e3605c37128540926876923249681b594390ede13e098`
- `build_track_fringe_objects`: `d55f1a1237a5ad176ee5c81d70bf0d40949f5a089e62216f948bc14009d1955f`
- `update_subgame`: `e1887d3b83450fded5caa113d3c715e21e8b95836047df3cb9a6fc6f81eca4bd`
- `construct_game_runtime`: `bceb7d6c64d021b062effa8a55727c717e9314946286378f76f5667099405c35`

## 2026-07-14 analysis receiver closure

The exact 34/34 implementation is now also authoritative in both analysis
databases: `TrackRowCell* __thiscall(SubgameRuntime*, Vec3*)`. Binary Ninja's
stale `Game*` identity was guardedly recreated, and both exports now return
directly from `game->runtime_cells`. This exact helper is the strongest local
proof that the surrounding normalization and pickup helpers share the same
subgame owner.
