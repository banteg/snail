# load_segment_definitions @ 0x448160

Initial target:

- Parses `Segments/*.txt` into the runtime segment catalog at
  `game+0x1075ae4`.
- Confirms the catalog count at receiver `+0x00`; its entries begin at `+0x04`
  and stride `0x4088`.
- Within each entry, writes the authored display name from `Name:'...'` at
  `+0x00`, while the filename from enumeration is written at `+0x40`.
- Confirms row count at entry `+0x84`, glyph columns at `+0x88`, and authored
  row records at `+0x888` with 0x38-byte stride.

Status:

- 2026-06-18: 45.01%, 531/571 candidate/target instructions, prefix 5/571,
  masked operands 65 ok, 8 mismatches.
- 2026-06-18: Promoted `AuthoredFloatBits`, `AuthoredSegmentRow`,
  `SegmentCatalogEntry`, and `SubSegment` to
  `include/segment_catalog_types.h`; focused Wibo score stayed 45.01%.
- 2026-07-11: Corrected the complete `SMTracks`/native `cRSMTracks`
  receiver after reconciling the constructor with both readers. The constructor
  starts 150 `0x4088`-byte entries at receiver `+0x04`; the leading count plus
  their `0x25cfb0` extent gives the exact reported size `0x25cfb4` and ends at
  the following parcel pool. There is no entry-0 count alias or terminal word.
- 2026-07-11: The symbol-preserving iOS member `cRSMTracks::Import()` and its
  common value-agnostic epilogue prove both the authored owner name and void
  contract. Windows has the same path-dependent EAX residue and its only
  caller discards it. Promoting `SegmentCatalog` to `SMTracks` and removing the
  synthetic result improves the focused match slightly from 45.01% to 45.05%
  (530/571 instructions); the remaining gap is source shape, not ABI.
- 2026-07-11: Modeling the enumerated directory as 512 fixed 0x80-byte rows,
  using indexed rows on diagnostic exits, restoring the cross-port-proven
  unused `sprintf` vararg, and spelling the decimal scanner as its direct
  head-guarded `while` raises the retained source to 49.29%: 553/571
  instructions, prefix 5/571, with 64 clean masked operands. The 11 reported
  mismatches are shifted call/string alignments across the still-different row
  anchor; no local-label or convenience aliases were added.

Corrections propagated to the reader:

- `copy_segment_definition_to_level_slot` searches the `+0x44` filename, not
  the internal display name.
- Authored row `+0x24..+0x2c` are the `Velocity=` vector, not rotation.
- Authored row `+0x30` is the `Path=` template index.
- Authored row `+0x34` is `RingSpeed=` float bits, not a row event id.

Call-shape notes:

- `load_or_reuse_cached_x_mesh` is called on the root-owned `DirectXLoader`
  with `ecx = game+0x48e00`; the loader owns the complete fixed cache bank.
- `find_segment_path_index_by_name` is also called through a path-table owner
  at `game+0x1066f28` in this caller, even though the standalone callee scratch
  can match as a free stdcall helper.
- Windows' unexplained extra push before `sprintf("Segments/%s", ...)` is an
  authored extra vararg, not padding: the symbol-rich iOS `cRSMTracks::Import`
  independently loads its segment-text buffer into `r3` for the same format.
  Preserving that unused fourth argument restores the shared call shape.

Residuals:

- Native keeps the catalog owner in `esi` and walks row storage as
  `entry_base + row*0x38` with field accesses at `+0x88c`; this scratch uses a
  direct `AuthoredSegmentRow*`, so row-field offsets compile as `+0x00..+0x34`.
- The flag/string tail is semantically ordered, but the candidate block is
  shorter and alignment drifts after `Path=`, causing the remaining masked
  string mismatches.
- Directly spelling every access as `entries[segment_index]` is a plausible
  member-indexing form, but VC6 expands the frame to `0x114e4`, drops the
  prefix to zero, and regresses from 45.05% to 42.61%. Retain the meaningful
  per-entry pointer; native's parallel induction variables need a different
  source-shape lead.
- Expanding `path_name` from 60 to the decompiler's apparent 64-byte span makes
  VC6 allocate a `0x114e4` frame and regresses to 42.87%. The native frame is
  `0x114e0`; its apparent final four bytes belong to adjacent compiler locals,
  so the retained 60-byte authored buffer is the stronger layout fit.
- Removing the typed row pointer and repeating
  `entry->rows[row_index].field` expands the frame, drops the prefix to zero,
  and falls to 33.63%. Keep the real `AuthoredSegmentRow*` lifetime; native's
  larger displacements arise from a containing-owner anchor, not absent row
  ownership.
- Deriving only the row pointer from `entries[segment_index]` recovers native's
  early `esi = this` ownership, but needs an extra stack slot, expands the
  frame, and regresses to 43.62%. Flattening the outer/inner row ordinal with
  casts would merely manufacture native displacements, so retain the honest
  entry-relative row pointer until a real container model explains the anchor.
