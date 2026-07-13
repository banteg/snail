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

- 2026-07-12: The final apparent `0x38` bytes of each catalog entry are not an
  unknown tail. Rows begin at `+0x888`, use the proven `0x38` authored-row
  stride, and the next entry begins at `+0x4088`, so exactly 256 rows fill the
  record: `0x888 + 256 * 0x38 == 0x4088`. The shared matcher and analysis
  layouts now own `rows[256]`, matching the Windows `SubSegment` row capacity
  and removing the synthetic `unknown_4050` field. This layout correction is
  codegen-neutral at the honest 49.29% parser baseline.
- 2026-07-12: Recovered the parser's actual stack-local ownership from the
  native frame: the reusable parse cursor is at `esp+0x10`, `path_name[64]`
  occupies `esp+0x30..+0x6f`, and `option_text[512]` begins exactly at
  `esp+0x70`. Reusing one `option_match` cursor for every metadata lookup and
  retaining that proven 64-byte path buffer recovers the exact `0x114e0`
  frame instead of the earlier accidental fit from a 60-byte buffer.
- Expressing the authored row and glyph writes through the containing
  `entries[segment_index]` array also recovers the native outer-loop strength
  reductions: `0x127 == 0x4088 / 0x38` for row ordinals and
  `0x811 == 0x4088 / 8` for glyph ordinals, alongside the direct `0x4088`
  entry stride. The combined ownership model raises the retained match from
  49.29% to 62.24%: 573/571 candidate/target instructions, prefix 5/571, with
  80 clean masked operands and 5 shifted mismatches. Isolated cursor, buffer,
  or container-indexing experiments regressed; their combination is what
  restores the native frame and all three related induction variables.

- The live Binary Ninja database still carried an older count-at-tail catalog
  layout, an empty `SubSegment`, and the wrong returning parser prototypes even
  though all of those type names existed. `sync_segment_catalog_types.py` now
  reapplies the checked-in header instead of treating a present name as proof
  that its layout is current; its normal readback verifies both the layouts and
  the six owner-aware prototypes.
- 2026-07-13: The enclosing `SubgameRuntime` now owns the complete `SMTracks`
  catalog at `+0x10014cc`. Its leading count plus 150 exact `0x4088` entries
  produces the verified `0x25cfb4` extent and lands exactly on the existing
  `ParcelManager +0x125e480`. A previewed Binary Ninja declaration preserved
  both boundaries and the `0x1272838` runtime size. This owner promotion is
  codegen-neutral at the honest 62.24% parser baseline; the five shifted
  call/string mismatches remain visible.

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
  at `game+0x1066f28` in this caller. Cross-port symbols prove that one-byte
  owner is `cRPathManager`, and the exact callee remains byte-identical when
  expressed as its unused-receiver thiscall method.
- Windows' unexplained extra push before `sprintf("Segments/%s", ...)` is an
  authored extra vararg, not padding: the symbol-rich iOS `cRSMTracks::Import`
  independently loads its segment-text buffer into `r3` for the same format.
  Preserving that unused fourth argument restores the shared call shape.

Residuals:

- Native keeps the complete catalog owner as its row anchor and addresses row
  fields at `owner + flattened_row*0x38 + 0x88c`; VC6 still materializes the
  typed candidate row at its final address and uses `+0x00..+0x34`. The
  containing-array spelling is nevertheless retained because it explains and
  reproduces the native `0x127` outer row induction without flattening casts.
- The candidate chooses different long-lived registers for the catalog,
  segment index, current entry, and data cursor. That changes the initial
  file-load schedule and shifts the diagnostic tail even though the strings
  and branches remain semantically ordered; the five masked mismatches are
  consequently shifted calls/strings rather than unresolved ownership.
- Directly spelling every header access as `entries[segment_index]` discards
  the meaningful per-entry pointer, changes the frame to `0x114dc`, and
  regresses to 38.60%. The native source shape combines an entry-relative
  header/count cursor with containing-owner row and glyph indexing.
- Removing the typed row pointer and repeating
  `entry->rows[row_index].field` expands the frame, drops the prefix to zero,
  and falls to 33.63%. Keep the real `AuthoredSegmentRow*` lifetime; native's
  larger displacements arise from a containing-owner anchor, not absent row
  ownership.
- Flattening the outer/inner row ordinal with casts would merely manufacture
  native displacements. The retained source gets the same induction from the
  real `SegmentCatalogEntry[150]` container and leaves the remaining row-anchor
  register choice visible rather than fakematching it.

## 2026-07-13 root services and cross-port cursor audit

- The mesh and path lookups now follow the canonical `GameRoot*` through its
  owned `DirectXLoader` and `SubgameRuntime::path_manager`; the last raw
  `g_game_base` declaration in this parser is gone. Focused output remains the
  honest 62.24%, 573/571 instructions, with 80 clean operands and the five
  shifted call/string mismatches.
- The iOS and Android `cRSMTracks::Import()` bodies independently advance one
  per-entry cursor (their later record is 0x90 bytes because row storage is
  allocated). That proves the semantic cursor, but two corresponding Windows
  source probes were rejected: advancing a typed `SegmentCatalogEntry*`
  regressed to 56.94% and using it for the row/glyph banks regressed to 56.91%
  while shrinking the exact 0x114e0 frame. Windows' inline 0x4088-byte rows
  instead produce the retained containing-array strength reductions; no
  pointer cast or synthetic spill was added to imitate the target register.
