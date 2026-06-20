# load_level_definition_file @ 0x447480

Initial relationship scratch.

- Parses one `Levels/*.txt` file into the level-definition loader at
  `game+0x224804`.
- Confirms the object starts with the regular segment count, then 100 regular
  `LevelSegmentSlot` records, then special `First` and `Last` slots.
- Confirms `Name:'...'` writes the display name at loader `+0x1a58dc`.
- Confirms `Fringe:` writes RGB floats at `+0x1a58cc..+0x1a58d4`.
- Confirms `Speed:`, `Garbage:`, `Salt:`, `Background:`, `Parcels:`,
  `Track:`, and `Quota:` scalar fields at `+0x1a595c..+0x1a5974`.
- Focused Wibo status: 2026-06-18, 75.17%, 939/926 candidate/target
  instructions, prefix 20/926, masked operands 165 ok.
- 2026-06-18: Replaced the local segment row and slot layout with
  `include/segment_catalog_types.h`; focused Wibo score stayed 75.17%.
- 2026-06-20: Promoted the full loader storage into
  `include/level_definition_loader.h` after Binary Ninja and this scratch
  agreed on the `segment_slots`, `first_segment`, `last_segment`, display
  name, fringe color, speed, hazard-frequency, texture, and quota offsets.
  Focused matcher stayed 75.17% with the same 939/926 candidate/target
  instruction count and 147 ok / 18 unresolved masked operands.

Slot corrections from this loader:

- Slot `+0x4014` is the per-level segment `Angle=` in radians.
- Slot `+0x4018` starts `Message=` text, not a hidden flag.
- Slot `+0x4218` is `Duration=` with default `4.0f`.
- Slot `+0x421c` is the resolved `Sample=` id with default `-1`.

The segment slot field names are now shared with
`copy_segment_definition_to_level_slot` and
`load_builtin_segment_definitions` after focused retesting.

Residuals:

- Early fallback-file error handling still differs in stack cleanup scheduling.
- `GalaxyText:` parsing is structurally recovered, but the compact text-copy
  loop still uses different register ownership.
- `find_registered_sound_sample_id_by_name` resolves `Sample="..."` names to
  registered sound sample ids by scanning the path/name table populated by
  `register_sound_sample`.
