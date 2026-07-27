# load_level_definition_file @ 0x447480

Initial relationship scratch.

- Parses one `Levels/*.txt` file into the level-definition loader at
  `game+0x224804`.
- Confirms the object starts with the regular segment count, then 100 regular
  `SubSegment` records, then special `First` and `Last` slots.
- Confirms `Name:'...'` writes the display name at loader `+0x1a58dc`.
- Confirms `Fringe:` writes RGB floats at `+0x1a58cc..+0x1a58d4`.
- Confirms `Speed:`, `Garbage:`, `Salt:`, `Background:`, `Parcels:`,
  `Track:`, and `Quota:` scalar fields at `+0x1a595c..+0x1a5974`.
- Focused Wibo status: 2026-06-18, 75.17%, 939/926 candidate/target
  instructions, prefix 20/926, masked operands 165 ok.
- 2026-06-18: Replaced the local segment row and slot layout with
  `include/segment_catalog_types.h`; focused Wibo score stayed 75.17%.
- 2026-06-20: Promoted the full loader storage into
  `include/sub_tracks.h` after Binary Ninja and this scratch
  agreed on the `segment_slots`, `first_segment`, `last_segment`, display
  name, fringe color, speed, hazard-frequency, texture, and quota offsets.
  Focused matcher stayed 75.17% with the same 939/926 candidate/target
  instruction count and 147 ok / 18 unresolved masked operands.
- 2026-07-11: Cross-port ownership now proves this is the void member
  `cRSubTracks::Init(char*)`, and that each inline 0x4220-byte record is a
  Windows `SubSegment`. Replacing the synthetic pointer return and stale slot
  name preserves 75.17%, 939/926 instructions, prefix 20/926, and all 165
  masked operands clean. Its success and error paths merely leave unrelated
  cursor or diagnostic values in EAX; every caller discards them.

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

2026-06-21 level-file buffer curation:

- Curated `g_level_file_text_buffer` at `0x74ec78` in
  `analysis/symbols/gameplay-references.json`. This is the shared level-text
  buffer immediately following `g_current_level_definition_name`; the scratch
  previously spelled it as `(&g_current_level_definition_name + 4)`, which the
  masked-operand resolver could not resolve past the 4-byte pointer extent, so
  every buffer reference reported as unresolved.
- The scratch now declares `extern char g_level_file_text_buffer[];` and uses it
  directly as `LEVEL_FILE_BUFFER`. The focused score is unchanged at 75.17%
  (curation resolves masked operands without altering the normalized
  instruction stream), but the masked audit is now clean: `165 ok / 0
  unresolved / 0 mismatch`, down from `147 ok / 18 unresolved / 0 mismatch`.
  All 18 previously-unresolved `push ADDR`/`mov ... ADDR` buffer references
  now resolve to the curated global.

2026-07-12 Galaxy and landscape ownership closure:

- The root-relative `+0x12d4638` gate is `SubgameRuntime::galaxy.active`.
  Each parsed `ArcadeN` ordinal selects one owned `GalaxyRouteSlot` at the
  native `0x2a0` stride; the loader writes the level name to
  `record.detail_text` and `GalaxyText:` to `record.description_text`.
- The native compiler retains the selected route as a byte offset from slot 0
  rather than materializing a route pointer. Keeping that honest recurrence
  over the typed `route_slots` array preserves the focused `75.17%`,
  `939/926` instructions, and all `165` clean masked operands.
- The `Background:` receiver is the already-proved embedded
  `SubgameRuntime::landscape_manager`, not a standalone root-relative loader
  view. Naming both owners is codegen-neutral and removes the last raw
  `g_game_base` arithmetic from this parser.

2026-07-12 parser cursor and source-order recovery:

- The exact native `0x710` frame owns two reusable borrowed text cursors at
  `esp+0x10` and `esp+0x14`, followed by the parsed integer at `esp+0x18` and
  the `Segments End:` cursor at `esp+0x1c`. The five local buffers then begin
  at `esp+0x20` with the already-recovered `512, 128, 128, 512, 512` extents.
- The scratch had modeled the first cursor correctly but split the second
  cursor between `line_cursor` and a scoped `option_cursor`. Native reuses that
  one `esp+0x14` slot for copying the line options and parsing `Angle=`,
  `Message=`, `Duration=`, and `Sample=`. Unifying the lifetime restores the
  target's stack-backed line-copy loop and keeps all of those lookups on the
  proven secondary cursor.
- Native's missing-value blocks are authored as the first arm for `Fringe:`,
  `Track:`, the nested `Speed:` lookup, `Garbage:`, and `Salt:`. Retaining those
  natural negative tests aligns the fallback-first control flow. The Galaxy
  text close-brace sentinel is now a borrowed pointer into the shared file
  buffer rather than an integerized address, and the segment loop increments
  the owning `segment_count` before advancing its borrowed line cursor, in the
  order explicit in the target.
- Together these ownership and source-order corrections raise the focused
 match from 75.17% to 82.27%: 941/926 candidate/target instructions, prefix
  20/926, with 178 clean masked operands and no unresolved or mismatched
  references. The redundant `cursor = 0` after a failed `Name:` lookup was
  also removed; the lookup result already owns that state.

## 2026-07-16 parser replay and buffer ownership

- Both decompiler lanes now replay the canonical void
  `load_level_definition_file(SubTracks*, char*)` receiver and preserve the
  complete `SubTracks` owner graph: display metadata, Galaxy route text,
  landscape manager, regular segment array, and the `First` and `Last`
  `SubSegment` records. The parser context global used by
  `copy_segment_definition_to_level_slot` is also named consistently as
  `g_current_level_definition_name`.
- `g_level_file_text_buffer` is now an exact `LevelFileTextBuffer[0x2800]`
  owner. The next independently referenced global begins at `0x751478`,
  exactly `0x2800` bytes after the buffer base at `0x74ec78`; a complete code
  reference sweep of that interval found references only to the base, while
  `0x751478` has its own unrelated consumers. There are no interior Binary
  Ninja data variables that would split the extent.
- The speed lane is a named `AuthoredFloatBits selected_speed` union in both
  analysis headers. This removes Binary Ninja's anonymous-member
  `tracks->.selected_speed` rendering and lets both the parser and
  `build_subgame_level` expose the sentinel-bit and float-value views without
  changing matcher source.
- The Binary Ninja segment replay now performs an exact parsed-type equality
  audit before the expensive declaration preview. An idempotent run verified
  all 11 header types, both globals, both data-variable types, and all six
  prototypes as already current in 3.45 seconds, skipping the previous
  whole-header reanalysis path while still detecting same-size semantic type
  changes.
- Focused matching remains honestly unchanged at 82.27%: 941/926
  candidate/target instructions, prefix 20/926, and 178 clean masked operands
  with no unresolved references or mismatches. The residuals remain compiler
  scheduling and control-flow shape; no fakematch was introduced.

## 2026-07-18 exact owner-size replay

Both replay lanes now read back the complete catalog/import chain before
refreshing this parser: `AuthoredSegmentRow` `0x38`, `SegmentCatalogEntry`
`0x4088`, `SMTracks` `0x25cfb4`, `SubSegment` `0x4220`, `SubTracks`
`0x1a5978`, and `SubSegmentRaw` `0x48`, together with the two compiler cursor
views. IDA refuses name/prototype/local mutations if any extent is wrong.
Focused reanalysis also recovered the 512-byte `script_name` stack buffer and
kept its landscape lookup on the embedded `SubgameRuntime::landscape_manager`.
The scratch and its honest 82.27% matcher result are unchanged.

## 2026-07-25 complete parser-frame ownership

The native `0x710`-byte frame now has the same explicit ownership in both
decompiler lanes as in the matcher: the shared parser cursor, reused
`line_cursor`, parsed integer, and `Segments End:` borrow are followed by
`level_path[512]`, `line_options[128]`, `sample_name[128]`,
`segment_name[512]`, and `script_name[512]`. These are five adjacent buffers,
not one anonymous aggregate. In particular, the line-options bank is no
longer rendered as a zero-width `void` local in Binary Ninja.

VC6 materializes `SubTracks::level_display_name` in EBP and hands the borrowed
byte cursor to EDX for the copy loop. The two registers remain distinct
lifetimes; typing both as `char*` removes BN's false
`(edx - 0x1a58dc)->:0x1a58dc` subtraction without merging simultaneously live
values. IDA independently carries the same byte cursor and now shows the
direct `tracks->level_display_name` producer.

The six other hand-written byte-copy loops now retain their borrowed
`char*` cursors as well: background script, regular segment, line options,
sample name, first segment, and last segment. BN had widened each cursor to a
pointer-to-array solely because its producer was one of the owned stack
buffers; the native code increments every cursor by one byte. IDA independently
identifies the same six register lifetimes. The replay scripts and strict
health checks preserve the byte-stride owners and reject the stale widened
forms.

The BN mutation was previewed and read back as one guarded batch. IDA applied
the exact definition-address and stack-offset identities first to a temporary
database, then to the tracked database. No matcher source, operands, control
flow, or masks changed: focused matching remains honestly at 82.27%,
941/926 instructions, prefix 20/926, with 178 clean operands and no unresolved
or mismatched references.

## 2026-07-27 paired-mobile parser source recovery

Android `cRSubTracks::Init(char*)` at `0x850d4` and iOS
`cRSubTracks::Init(char*)` at `0x36fc4` independently preserve two useful
source-level invariants from the shared parser:

- `GalaxyText:` is copied with one borrowed input cursor. A control byte emits
  `>` and advances that same cursor to the next printable byte; there is no
  second text-cursor owner. Removing the synthetic alias from the Windows
  scratch is codegen-identical.
- After importing one authored segment row, the parser advances the owning
  line cursor, tests it for end-of-file, and only then compares it with the
  borrowed `Segments End:` sentinel. Expressing that as one compound loop
  condition and a post-loop diagnostic gives VC6 the closer cold-exit shape.

The ports also establish a strict boundary: their `Mode:*`, `ArcadePro`,
padding segment, and extra message/sample fields are mobile-only and were not
transplanted into the Windows layout. The focused Windows match rises from
82.27% to 82.50%: 943/926 candidate/target instructions, prefix 20/926, with
183 clean masked operands, no unresolved or mismatched references, and two
honestly unaudited candidate-only instructions in the still-unmatched cold
EOF diagnostic.

## 2026-07-27 mobile-supported cursor lifetimes

Android `cRSubTracks::Init(char*)` at `0x850d4` and iOS at `0x36fc4`
independently preserve the same two parser invariants as the Windows CFG:

- `Length:` is a pre-tested decimal scan. The lower bound controls the loop,
  while the upper bound exits from its head; the cursor and cached character
  advance together. Expressing that natural source shape removes VC6's
  duplicated tail upper-bound comparison.
- The `GalaxyText:` closing brace is a borrowed end sentinel whose only
  remaining use is the copy bound two bytes earlier. Narrowing that pointer in
  place, rather than introducing a second derived owner, restores the native
  EAX end-sentinel lifetime and the target's ECX input / EDX output copy loop.

These are source and ownership recoveries, not synthetic scheduling hints.
Focused matching rises from 82.50% to 84.63%: candidate instructions fall from
943 to 941 against 926 target instructions, all 183 masked operands remain
clean, and the only two unaudited operands remain the honest candidate-only
cold EOF diagnostic.
