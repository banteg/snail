# load_segment_definitions @ 0x448160

Initial target:

- Parses `Segments/*.txt` into the runtime segment catalog at
  `game+0x1075ae4`.
- Confirms the catalog count aliases entry 0 at `+0x00`; entries still stride
  `0x4088`.
- Writes the authored display name from `Name:'...'` at entry `+0x04`, while
  the filename from enumeration is written at entry `+0x44`.
- Confirms row count at `+0x88`, glyph columns at `+0x8c`, and authored row
  records at `+0x88c` with 0x38-byte stride.

Status:

- 2026-06-18: 45.01%, 531/571 candidate/target instructions, prefix 5/571,
  masked operands 65 ok, 8 mismatches.

Corrections propagated to the reader:

- `copy_segment_definition_to_level_slot` searches the `+0x44` filename, not
  the internal display name.
- Authored row `+0x24..+0x2c` are the `Velocity=` vector, not rotation.
- Authored row `+0x30` is the `Path=` template index.
- Authored row `+0x34` is `RingSpeed=` float bits, not a row event id.

Call-shape notes:

- `load_or_reuse_cached_x_mesh` is called as a mesh-bank thiscall with
  `ecx = game+0x48e00`.
- `find_segment_path_index_by_name` is also called through a path-table owner
  at `game+0x1066f28` in this caller, even though the standalone callee scratch
  can match as a free stdcall helper.

Residuals:

- Native keeps the catalog owner in `esi` and walks row storage as
  `entry_base + row*0x38` with field accesses at `+0x88c`; this scratch uses a
  direct `AuthoredSegmentRow*`, so row-field offsets compile as `+0x00..+0x34`.
- The flag/string tail is semantically ordered, but the candidate block is
  shorter and alignment drifts after `Path=`, causing the remaining masked
  string mismatches.
