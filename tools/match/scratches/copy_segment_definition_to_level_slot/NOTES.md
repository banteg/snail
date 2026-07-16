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
  `SubSegment` layouts to `include/segment_catalog_types.h`; focused
  Wibo score stayed 54.10%.
- 2026-07-11: Recovered the constructor-proven leading count and moved the
  record fields to their true entry-relative offsets. Direct indexing through
  `catalog->entries[index]` lets VC6 fold the four-byte array offset into the
  native field displacements, preserving 54.10%, the 42-instruction prefix,
  and all five clean masked operands.
- 2026-07-11: The symbol-preserving iOS signature
  `void cRSubTracks::ImportSegment(char*, cRSubSegment*)` proves both the
  destination boundary and the return contract. Promoting the Windows inline
  0x4220-byte destination to `SubSegment`, removing a synthetic result
  lifetime, and expressing each parsed position/velocity triple as a real
  `Vector3` raises the match from 54.10% to 85.60%: 125/125 instructions,
  prefix 74/125, and all five masked operands clean.

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

Residuals after the ownership recovery:

- The remaining normalized differences are register and pointer-anchor
  scheduling within the metadata copy. The layout, instruction count, vector
  grouping, and masked addresses now agree, so contorting the source around
  those commutative scheduling differences would be fakematching.
- A plain whole-row struct assignment still regresses into `rep movsd`; the
  field-and-vector assignments preserve the native scalar copy family.

Rejected probes:

- Hoisting `row_count` into a local regressed to 39.00% and moved the argument
  owner back out of `ebx`; the baseline reads `source->row_count` at use sites.
- 2026-06-21 selected-entry owner probe: carrying the search cursor forward as
  `source = scan` or scanning with an explicit filename cursor regresses to the
  mid-30% range by disturbing the prologue/search-loop ownership. Removing the
  separate `entries` local is codegen-neutral at 54.10%. Keep the recomputed
  `&entries[index]` source until a form preserves the 42-instruction prefix and
  still lets native own the selected entry in `edx`.

## 2026-07-13 receiver ABI and ownership

- The three Windows caller sites at `0x447c19`, `0x447f9e`, and `0x44804d`
  each load the owning `SubTracks*` into `ecx` immediately before the call and
  push only the segment name and destination. Together with callee `ret 8` and
  the iOS `cRSubTracks::ImportSegment(char*, cRSubSegment*)` symbol, this proves
  a two-argument `thiscall`; the receiver is unused by the Windows body but is
  not absent.
- The scratch and shared declaration now model the real member ABI instead of
  a global `__stdcall` function. This is byte-neutral for the callee and keeps
  `load_level_definition_file` at its established `82.27%` caller shape.
- The bridge reads the root-owned `SMTracks` catalog through typed `g_game`.
  Glyphs and metadata are copied into the explicit caller-owned `SubSegment`;
  only `source_name` remains as a borrowed pointer into the stable catalog
  entry. The receiver can pass an ordinary slot, `first_segment`, or
  `last_segment`, matching the three callsite families.

## 2026-07-15 durable IDA ownership

The live IDA prototype already carried the recovered member ABI, but its
checked-in decompile still showed the old global `__stdcall` returning an
incidental `_DWORD*`. A focused strict refresh now exposes the unused
`SubTracks*` receiver, root-owned `SMTracks`, caller-owned `SubSegment`, inline
glyph rows, authored row bank, and void error path. A health check rejects the
stale raw global form so later narrow exports cannot silently lose this owner
graph. Matcher source remains unchanged at the honest 85.60% frontier: all
125 instructions and five masked operands agree, while the remaining register
schedule is not being reshaped for score.

## 2026-07-16 selected-entry stride anchor ownership

- Native computes its EDX catalog cursor by adding `index * 0x4088` to the
  `SMTracks` base, not to `entries[0]`. The register therefore remains four
  bytes before the selected `SegmentCatalogEntry`: its prefix is
  `SMTracks::count` for index zero and the previous entry's final word for
  later indices.
- A direct `SegmentCatalogEntry*` local probe was rejected because it shifted
  every field by four bytes: the decompiler rendered `row_count` as glyph
  bytes, `id` as `row_count`, and `filename` as `filename[4]`. That would have
  been a false ownership claim even though the register points near the entry.
- The analysis headers now carry the exact `SegmentCatalogEntryAnchor` view:
  one neutral `stride_prefix_word` followed by the real entry. Binary Ninja's
  proven EDX SSA identity (`RegisterVariableSourceType`, index 113, storage
  68) and IDA's corresponding register local (definition EA `0x447372`) both
  replay as
  `selected_entry_anchor`. Both exports now expose the selected entry's
  `row_count`, `filename`, `id`, column-major glyph grid, and authored row bank
  through `selected_entry_anchor->entry`.
- Both replays are idempotent: Binary Ninja verifies all 12 header types and
  skips the already-current local owner, while IDA reports the same local and
  all six catalog prototypes unchanged. Health checks reject both the old raw
  byte-pointer form and the four-byte-shifted direct-entry form.
- Matcher source remains unchanged at the honest 85.60% frontier: 125/125
  instructions, prefix 74/125, and five clean masked operands. The remaining
  metadata-copy differences are register scheduling, so no source was
  contorted to improve the score.
