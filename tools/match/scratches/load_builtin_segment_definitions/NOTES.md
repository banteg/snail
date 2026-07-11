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
- 2026-06-18: Reshaped the scratch around the shared `SubSegment` layout
  and the raw built-in record; score stayed at 52.97%, but the slot
  offsets now line up with `copy_segment_definition_to_level_slot`.
- 2026-06-18: Replaced the local authored row and slot copies with
  `include/segment_catalog_types.h`; focused Wibo score still stayed 52.97%.
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
- The old cached-glyph spelling made VC6 reserve `bl`, which in turn kept the
  raw table in `ebp` and displaced the native destination calculation. Direct
  indexed glyph access is both simpler source and the native register shape.

## 2026-07-11 receiver ownership correction

- Construction and the adjacent level-file parser prove the receiver is a
  complete `SubTracks`, not a standalone 103-slot store. The old
  `LevelSegmentSlotStore` declaration was too large and crossed the exact
  `0x1a5978` owner boundary into the following BodBase sentinels.
- `slots[102].row_base` is a deliberate overlapping access to the existing
  loader tail at `+0x1a58c4`; the function never owns or touches a complete
  103rd `0x4220`-byte slot.
- Moving the method onto the real owner initially left the honest focused
  result unchanged at `52.97%`, 93/92 candidate/target instructions.

## 2026-07-11 raw input and void contract

- The symbol-preserving iOS overload names the input type
  `cRSubSegmentRaw**`. Windows' shipped globals prove the corresponding static
  `SubSegmentRaw` record is `0x48` bytes: row count at `+0x00`, path index at
  `+0x1c`, source name at `+0x20`, and eight glyph-row pointers at `+0x28`.
- The empty Windows path leaves `eax = raw_segments[0]`, while the populated
  path leaves `eax = next->glyph_rows[0]`; all callers discard it. That
  inconsistent incidental register value proves this `Init` member is `void`,
  not the earlier decompiler-inferred `char*` function.
- Removing the forced return lifetime and cached glyph byte recovers native
  `ebx` ownership for the raw table, `ebp` for the destination offset, and the
  direct `dl` copy loop. The focused result rises from `52.97%` (93/92) to
  `97.83%` with the exact 92/92 instruction count.
- The remaining two differences are commutative encodings only:
  `[esi+eax]` versus `[eax+esi]`, and addition of the row base versus column.
  The clear source form is retained rather than swapping operands for bytes.
- iOS dynamically allocates its compact destination `cRSubSegment` glyph
  storage. That later-port destination layout is not transplanted onto the
  Windows inline `0x4220` `SubSegment` array.
