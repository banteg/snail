# is_neighbor_cell_solid @ 0x434b60

Current source-shaped match: exact, 100.00% (47/47 instructions,
2 masked operands ok).

Confirmed semantics:

- asks exact `get_track_cell_row_index` for the source row;
- extracts the source lane from `cell + 0x40` low three bits;
- rejects lateral probes outside `[0, 7]`;
- rejects row probes outside `[0, runtime_row_count)`;
- computes the neighbor runtime-cell stride as `21 * (lane + dx + row * 8)`;
- returns true only when the neighbor is not an open-neighbor family and its
  tile id is nonzero and not `35`, `28`, or `22`.

Source-shape note:

- The exact source needs an explicit `char* cell_base =
  (char*)this + (cell_index << 2)` before loading the tile byte and before
  forming the helper argument. This matches native's separate
  `lea eax, [this + cell_index * 4]`, then `esi = tile`, then
  `ecx = eax + 0x3bfac8` sequence.

Rejected source-shape probes:

- typed `runtime_cells[flat_index]` indexing moved the tile id into `esi` but
  changed the native `*21` multiply idiom;
- reading tile through the typed neighbor pointer kept the explicit stride but
  changed the byte-load register from `ecx` to `edx`.

2026-06-21 subgame-header consolidation: the helper now uses the shared
`SubgameRuntime` owner for `runtime_row_count` while keeping the proven raw
runtime-cell byte-offset idiom. Focused Wibo remains exact at `100.00%`,
`47/47` instructions, with `2` clean masked operands.

## Cross-port owner proof

Android preserves this method as `cRSubGame::TestLoc(cRSubLoc*, int, int)`.
Its body calls `cRSubLoc::Yi()`, performs the same lane and row bounds checks,
indexes the same eight-lane cell grid, calls `cRSubLoc::IsEmpty()`, and applies
the same final exclusions for tile ids `35`, `0`, `22`, and `28`. The Windows
scratch now calls the shared `SubLoc` predicate method directly and remains
exact at 47/47 with two clean operands.

## 2026-07-14 runtime-cell offset ownership

The native helper still requires its separate byte-offset base before loading
the tile id and forming the `SubLoc*` argument. Those two displacements now
derive from `SubgameRuntime::runtime_cells` and
`runtime_cells[0][0].tile_id` with `offsetof`, rather than repeating
`0x3bfac8` and `0x3bfb04`. Binary Ninja confirms the same `0x54` cell with
`tile_id +0x3c`. Focused output remains exact at 47/47 with both operands
clean.
