# copy_segment_definition_to_level_slot @ 0x447300

Initial target:

- Copies one named segment from the runtime segment catalog at
  `game+0x1075ae4` into a level slot.
- Searches segment names with `strings_equal_case_insensitive_path`.
- Transposes the source glyph grid from catalog column-major storage into the
  level slot's eight 0x100-byte row lanes.
- Copies the per-row authored metadata records with the 0x38-byte row stride
  already seen in `populate_runtime_track_cells_from_segments`.

Status:

- 2026-06-18: 54.10%, 119/125 candidate/target instructions, prefix 42/125,
  5 masked operands ok.

Corrections from the first pass:

- The catalog entry base is the count word at `game+0x1075ae4`; `name` lives at
  entry `+0x44`. Modeling an extra catalog header kept the same rough score but
  was structurally wrong.
- `data_74ec74` is a `char*` current level-definition name.
  `load_level_definition_file` writes its input there before segment-copy
  diagnostics consume it.

Residuals:

- Native keeps the selected source entry in `edx` for the glyph and row-copy
  blocks; this source shape keeps it in `esi`.
- The explicit row-record copy is grouped by how
  `populate_runtime_track_cells_from_segments` consumes the fields, but native
  scheduling remains different. A plain struct assignment regressed into
  `rep movsd`.

Rejected probes:

- Hoisting `row_count` into a local regressed to 39.00% and moved the argument
  owner back out of `ebx`; the baseline reads `source->row_count` at use sites.
