# copy_segment_definition_to_level_slot @ 0x447300

Initial target:

- Copies one named segment from the runtime segment catalog at
  `game+0x1075ae4` into a level slot.
- Searches segment filenames with `strings_equal_case_insensitive_path`.
- Transposes the source glyph grid from catalog column-major storage into the
  level slot's eight 0x100-byte row lanes.
- Copies the per-row authored metadata records with the 0x38-byte row stride
  already seen in `populate_runtime_track_cells_from_segments`.

Status:

- 2026-06-18: 54.10%, 119/125 candidate/target instructions, prefix 42/125,
  5 masked operands ok.
- 2026-06-18: Promoted the shared authored segment catalog and
  `LevelSegmentSlot` layouts to `include/segment_catalog_types.h`; focused
  Wibo score stayed 54.10%.
- 2026-07-11: Recovered the constructor-proven leading count and moved the
  record fields to their true entry-relative offsets. Direct indexing through
  `catalog->entries[index]` lets VC6 fold the four-byte array offset into the
  native field displacements, preserving 54.10%, the 42-instruction prefix,
  and all five clean masked operands.

Corrections from the first pass:

- The catalog count is at `game+0x1075ae4`; the first entry begins four bytes
  later and its segment filename lives at entry `+0x40` (absolute catalog
  `+0x44`). Constructor iteration proves this header rather than an overlapping
  entry-0 alias.
- `load_segment_definitions` proves the internal `Name:'...'` display string is
  separate and starts at entry `+0x00` (absolute catalog `+0x04`).
- `load_segment_definitions` also corrects authored row names:
  `+0x24..+0x2c` are `Velocity=`, `+0x30` is `Path=`, and `+0x34` is
  `RingSpeed=` float bits.
- `load_level_definition_file` proves the level slot tail is not generic
  runtime state: `+0x4014` is `Angle=` radians, `+0x4018` starts optional
  `Message=` text, `+0x4218` is `Duration=`, and `+0x421c` is `Sample=`.
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
- 2026-06-21 selected-entry owner probe: carrying the search cursor forward as
  `source = scan` or scanning with an explicit filename cursor regresses to the
  mid-30% range by disturbing the prologue/search-loop ownership. Removing the
  separate `entries` local is codegen-neutral at 54.10%. Keep the recomputed
  `&entries[index]` source until a form preserves the 42-instruction prefix and
  still lets native own the selected entry in `edx`.
