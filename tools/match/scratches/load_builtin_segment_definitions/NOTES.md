# load_builtin_segment_definitions @ 0x448060

Initial shape:

- Copies the built-in segment table at `0x4a63d0` into a slot store whose
  first dword is the live count and whose slots start at `base+4` with a
  `0x4220` stride.
- The built-in row count is recovered as the length of row 0, then copied into
  both the destination slot and the static table entry's first dword.
- The eight row strings are copied into the slot grid at `slot+0x14`, lane
  major with a 0x100-byte row buffer per lane.
- `slot[102].row_base` is seeded to `1000`; that offset matches
  `base+4+0x4220*102`, the same slot math used for the `First:` and `Last:`
  special slots in `load_level_definition_file`.

Status:

- 2026-06-18: 52.97%, 92 target instructions vs 93 candidate instructions,
  no masked operands.
- 2026-06-18: Reshaped the scratch around the shared `LevelSegmentSlot` layout
  and a typed `BuiltinSegmentDefinition`; score stayed at 52.97%, but the slot
  offsets now line up with `copy_segment_definition_to_level_slot`.
- Useful correction from the first pass: the row-copy loop should reload the
  row pointer through the table for each glyph; caching/incrementing the row
  pointer made the shape worse.
- The built-in definition has an unknown dword at `+0x24`; the eight row
  pointers start at `+0x28`. Omitting that gap moved the row table to `+0x24`
  and regressed the scratch to 48.65%.
- Authored row field names were kept in sync with `load_segment_definitions`:
  `Velocity=`, `Path=`, and `RingSpeed=` own row offsets `+0x24..+0x34`.
- `load_level_definition_file` corrects the slot tail names: `+0x4014`
  is the per-level segment angle, `+0x4018` starts optional message text,
  `+0x4218` is message duration, and `+0x421c` is the message sample id.
- Main residual: VC6 allocates the built-in table in `ebp` for this scratch,
  while native keeps it in `ebx` before the sentinel check and then uses `ebp`
  for the per-glyph destination offset. Pointer/integer/`register` spellings
  all compiled to the same non-native allocation, so this is left unresolved
  rather than forced.
