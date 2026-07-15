# load_builtin_segment_definitions @ 0x448060

Initial shape:

- Copies the built-in segment table at `0x4a63d0` into a slot store whose
  first dword is the live count and whose slots start at `base+4` with a
  `0x4220` stride.
- The built-in row count is recovered as the length of row 0, then copied into
  both the destination slot and the static table entry's first dword.
- The eight row strings are copied into the slot grid at `slot+0x14`, lane
  major with a 0x100-byte row buffer per lane.
- The owner-level `random_length` field is seeded to `1000`; it follows the
  100 ordinary slots plus the separately named `first_segment` and
  `last_segment` records.

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
- The former `slots[102].row_base` view merely reached the same
  `random_length +0x1a58c4` address through array arithmetic. The source now
  names the owner field directly and no longer implies a nonexistent 103rd
  `SubSegment`.
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

## 2026-07-13 owner-field and glyph-grid cleanup

- The initialization now writes `SubTracks::random_length` directly instead
  of reaching the same `+0x1a58c4` field through the misleading
  `segment_slots[102].row_base` alias. Focused codegen is unchanged.
- Writing `segment_slots[active_slot].glyph_rows[row_index][column]` through
  the owned two-dimensional grid removes the last raw destination-offset
  calculation and improves the focused match from `97.83%` to `98.91%`, with
  the exact `92/92` instruction count.
- The only remaining difference is the commutative ModRM spelling
  `[esi+eax]` versus `[eax+esi]` in the row-0 length scan. Equivalent pointer
  syntax compiles identically, so the clear indexed source is retained.

## 2026-07-15 raw marker-row ownership

A read-only decode of all 32 pointers in `g_builtin_segment_definitions`
closes the raw record's former `+0x24` dword as a `char* marker_row`. Each of
the 31 live records points to a string whose width matches its longitudinal
glyph strings and which contains exactly one `*`; the terminating record
points to an empty string. The six dwords at `+0x04..+0x1b` are likewise real
static metadata words rather than byte padding, but this Windows initializer
never reads them and no surviving consumer proves stronger names, so their
roles remain deliberately generic.

This is a type/ownership correction only. `marker_row` is adjacent to, not a
member of, the eight-pointer `glyph_rows` array beginning at `+0x28`; the
focused body remains honestly 98.91%, 92/92 instructions, with the sole
equivalent `[esi+eax]` versus `[eax+esi]` ModRM ordering residual.

Refreshing the IDA lane exposed a stale manually typed stack alias named
`BuiltinSegmentDefinition** builtins`. It is the compiler-reused slot for the
scratch's integer `grid_offset`: native clears it, advances it by `0x100` per
glyph lane, and uses it only in destination address formation. The segment
catalog replay now replaces that synthetic owner with `int32_t grid_offset`
and verifies the local name/type after re-decompilation.
