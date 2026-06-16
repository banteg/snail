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
