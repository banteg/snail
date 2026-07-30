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
- 2026-07-13: The enclosing `cRSubGame` now owns the complete `SMTracks`
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
  owned `DirectXLoader` and `cRSubGame::path_manager`; the last raw
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

## 2026-07-14 authored row-flag ownership

The parser's packed metadata now belongs to `AuthoredSegmentRowFlag`. Its
names come directly from the accepted text (`Parcel`, `3DModel`, `NoFall`, the
five `Ring=` values, and `JetPack=Off`). `Path=` and model `Velocity=`
deliberately share `0x08`; the enum preserves that overload instead of
fakematching two independent bits. Focused output is byte-identical at 62.24%,
573/571 instructions, prefix 5/571, 80 clean operands, and the same five
shifted call/string mismatches.

## 2026-07-15 durable DirectX loader owner

The IDA consumer now receives the independently bounded
`DirectXLoader +0x48e00` member from the shared root composer, preserving
`load_or_reuse_cached_x_mesh(&v36->directx_loader, ...)` across later narrow
replays. Its exact `0x5e10` bytes meet `Backdrop +0x4ec10` with no invented
padding. This analysis-only change leaves the focused result at 62.24%,
573/571 instructions, prefix 5/571, 80 clean operands, and the same five
honest mismatches.

## 2026-07-16 flattened catalog-row ownership

- Native `chkstk` preserves `ECX`, but Binary Ninja conservatively splits the
  post-call register into a fresh `out_count` SSA variable. A global `chkstk`
  prototype/clobber experiment recovered the receiver but destabilized large
  stack-frame lifting, so it was rejected and not persisted. The durable sync
  instead retypes only the exact `RegisterVariableSourceType` identity
  `(index=5, storage=67)` as `SMTracks* tracks_after_stack_probe`, preserving
  the stable decompile while recovering `count`, `entries[0].row_count`, and
  `entries[0].glyph_columns`.
- The native row cursor is not an `AuthoredSegmentRow*`: it starts at the
  `SMTracks` base, advances by the exact `0x38` row stride, and consumes the row
  at `+0x88c`. `SegmentCatalogRowStrideAnchor` records that overlapping view,
  and the exact ESI SSA identity `(index=469, storage=72)` now resolves every
  consumed row member from `flags` through `path_template_index`. Only the
  `row` member is claimed; the `0x88c` prefix deliberately overlaps catalog
  storage rather than inventing a standalone allocation.
- The paired strict export also accepted IDA's now-propagated 4 KiB file buffer
  and 64 KiB enumerated-name bank owners from the canonical archive-shell
  prototype. Focused matching remains honestly unchanged at 62.24%, 571 target
  versus 573 candidate instructions, prefix 5, with 88 clean masked operands
  and one shifted call mismatch. No source-shape or operand fakematch was made.

## 2026-07-24 authored render-suppression ownership

The literal post-row `*` syntax now owns
`AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER` rather than an intentionally
weak marker-only name. `populate_runtime_track_cells_from_segments` copies
that bit one-for-one into `SUBROW_FLAG_SUPPRESS_TRACK_RENDER`; the independently
recovered `merge_track_tile_runs` and `build_track_fringe_objects` consumers
then clear row body/list and directional-fringe render ownership. This closes
the parser-to-runtime-to-render chain without guessing from the text syntax.

The enum rename is codegen-neutral: focused matching remains 62.24%, 573/571
instructions, prefix 5/571, with 88 clean masked operands and the one existing
shifted call mismatch.

## 2026-07-25 IDA importer lifetime closure

The tracked Hex-Rays lane now preserves the same importer owners already proved
by the matcher and Binary Ninja. Exact stack identities retain the post-probe
`SMTracks*`, the advancing filename cursor, the row index, `option_text[512]`,
`file_path[512]`, `file_buffer[4096]`, and the 512-by-128 enumerated filename
bank. The non-stack ESI lifetime defined at `0x448336` is the overlapping
`SegmentCatalogRowStrideAnchor*`; all authored metadata from `flags` through
`path_template_index` consequently resolves through its borrowed `row` member
instead of `_DWORD*` arithmetic.

The IDA wrapper now previews the complete replay on a temporary database before
touching the tracked database. Both the preview and a second replay read every
local back unchanged. A source-level `short` annotation for the row index was
explicitly rejected: native zeroes and increments its four-byte stack slot,
then sign-extends the low word for row addressing, so the narrow Hex-Rays type
rendered false `*(_DWORD *)&row_index` aliasing. The retained `int32_t` analysis
local keeps that physical behavior visible.

No matcher source changed. Focused matching remains honestly at 62.24%,
573/571 instructions, prefix 5/571, with 88 clean operands and the existing
shifted call mismatch.

## 2026-07-25 importer frame and cursor closure

The exact `0x114e0` stack frame now replays as physical parser storage rather
than Binary Ninja's synthetic incoming arguments and return address. Its
borrowed slots are the reusable parse cursor, row-count and filename cursors,
the catalog receiver used by ring-speed writes, the segment-index spill, the
`0x811` glyph-row base, the `0x127` authored-row base, and the row index,
followed by the proven 64-, 512-, 128-, 512-, 4096-, and 65536-byte text
buffers. The two bases are induction units inside the sole `SMTracks` owner:
`0x127 == 0x4088 / 0x38` and `0x811 == 0x4088 / 8`.

Exact register definitions now preserve the segment, row, glyph, option,
model-name, and path-name cursors in both Binary Ninja and IDA. Both canonical
replays read every new lifetime back unchanged, and the paired export health
checks reject the former `arg_*`, `__return_addr`, `v19`, and anonymous cursor
forms. This is analysis-only ownership recovery: no matcher source or operand
shape changed, so the honest focused result remains 62.24%, 573/571
instructions, prefix 5/571, with 88 clean operands and the one shifted call
mismatch.

## 2026-07-27 cross-port member-cursor recovery

Android and iOS independently keep one advancing `cRSMTracks` entry owner
through `Import()`. Windows cannot copy their allocated glyph/row banks because
its entries instead own fixed inline storage, but the native outer loop exposes
the corresponding durable member cursor: it starts at the first entry's
`row_count`, advances by the exact `0x4088` entry stride, and derives the
current header and row banks from the same enclosing `SMTracks`.

Keeping that `row_count` borrow across the outer loop, while spelling the
header fields through their containing entry and retaining the typed
`AuthoredSegmentRow*` inside the row loop, substantially shrinks and realigns
the candidate's divergent peeled file-load tail. The focused result rises from
62.24% to 65.79%,
575/571 candidate/target instructions, and the exact prefix grows from 5 to 7;
all 91 resolved masked operands remain clean.

Two mobile/source-shape probes were rejected rather than imported blindly.
The mobile empty-option fast path adds five Windows instructions and regresses
to 61.62%; Windows demonstrably performs the first metadata search immediately
after terminating `option_text`. Writing `RingSpeed` through a fresh containing
array expression also expands the exact stack frame and regresses below 55%.
Those differences remain visible instead of being hidden with a cast or a
synthetic spill.

## 2026-07-28 authored cRSMTracks owner

The exact Android and iOS symbols now promote the Windows catalog's primary
owner from the semantic `SMTracks` name to authored `cRSMTracks`. Both ports
independently preserve `cRSMTracks::Import()` and
`cRSMTracks::OpenLevels()`; Windows independently supplies the authoritative
`0x25cfb4` inline layout, including its 150 complete `0x4088`-byte entries.
`SMTracks` remains only as a compatibility typedef.

The matcher definitions now use the exact `Import()` and `OpenLevels()` member
names while the Windows manifest retains its stable semantic function names
through explicit aliases. The root `cRSubGame::sm_tracks` embed, producer,
level loader, catalog-copy consumer, bootstrap caller, Binary Ninja replay,
and IDA replay all share `cRSMTracks` as their primary type.

The focused six-function BN/IDA 9.4 export has zero symbol mismatches, and all
1,144 strict decompile-health checks pass. The catalog-owner checks now require
`cRSMTracks` and reject the retired compatibility spelling at the recovered
local and receiver sites.

A direct source probe that derived `id`, `filename`, and `display_name`
backward from the retained `row_count` cursor was rejected: it reduced the
candidate from 575 to 572 instructions but regressed alignment from 65.79% to
64.92% and left the wrong long-lived register assignment intact. The proven
member-cursor semantics remain documented without replacing real containing
entry ownership with pointer arithmetic. The retained importer remains at
65.79%, 575/571 instructions, with 91 clean resolved operands and the same
five unaudited peeled-tail references.

## 2026-07-30 shared outer-loop header

The five candidate-only references were one duplicated outer-loop file-load
header, not missing parser behavior. The retained explicit `count <= 0` guard
plus `do/while` let VC6 specialize entry zero and peel the next
`sprintf`/load/`ID:` lookup at the tail. Native instead performs the same
zero-count guard generated by a natural `while (segment_index < count)` and
enters one shared header for every catalog entry.

Restoring that source shape raises the focused result from 65.79% to 68.26%
and shrinks the candidate from 575 to 560 instructions against 571 native.
The exact prefix remains 7 instructions, while all five peeled-tail references
disappear: all 91 resolved operands are now audited and clean.

Four recorded mutation sweeps bound the nearby schedules. The three equivalent
natural `while`/`for` control variants all gain the same 48 weighted bytes.
After retaining the plain `while`, three RingSpeed owner variants regress to
49.74%-59.15%; two late/current-entry header owners are neutral or 0.53 points
worse; and nine outer cursor publication/stride variants are neutral or
0.18-4.30 points worse. The remaining 11-instruction deficit is therefore an
honest register/row-anchor residual, not evidence for restoring the duplicated
header or manufacturing a containing-owner cast.
