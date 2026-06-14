# is_neighbor_cell_solid @ 0x434b60

Current source-shaped lead: 68.82% (47 target instructions, 46 candidate,
11-instruction prefix).

Confirmed semantics:

- asks exact `get_track_cell_row_index` for the source row;
- extracts the source lane from `cell + 0x40` low three bits;
- rejects lateral probes outside `[0, 7]`;
- rejects row probes outside `[0, runtime_row_count)`;
- computes the neighbor runtime-cell stride as `21 * (lane + dx + row * 8)`;
- returns true only when the neighbor is not an open-neighbor family and its
  tile id is nonzero and not `35`, `28`, or `22`.

Residual:

- Native computes `this + cell_index * 4` into `eax`, then reuses `esi` for
  the tile id before passing `eax + 0x3bfac8` to
  `is_open_neighbor_tile_family`.
- The clean source keeps the same semantics but folds the helper argument as
  `[esi + eax*4 + 0x3bfac8]` and keeps the tile id in `edi`, shortening the
  function by one instruction and shifting branch labels.

Rejected source-shape probes:

- naming `cell_base` as either `char*` or integer address still folded the
  helper argument;
- typed `runtime_cells[flat_index]` indexing moved the tile id into `esi` but
  changed the native `*21` multiply idiom;
- reading tile through the typed neighbor pointer kept the explicit stride but
  changed the byte-load register from `ecx` to `edx`.

Do not force the remaining register/base-address residual with volatile,
dummy aliasing, or fake helper calls.
