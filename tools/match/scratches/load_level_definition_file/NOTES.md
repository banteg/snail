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

- The root-relative `+0x12d4638` gate is `cRSubGame::galaxy.active`.
  Each parsed `ArcadeN` ordinal selects one owned `GalaxyStar` at the
  native `0x2a0` stride; the loader writes the level name to
  `record.detail_text` and `GalaxyText:` to `record.description_text`.
- The native compiler retains the selected route as a byte offset from slot 0
  rather than materializing a route pointer. Keeping that honest recurrence
  over the typed `route_slots` array preserves the focused `75.17%`,
  `939/926` instructions, and all `165` clean masked operands.
- The `Background:` receiver is the already-proved embedded
  `cRSubGame::landscape_manager`, not a standalone root-relative loader
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
kept its landscape lookup on the embedded `cRSubGame::landscape_manager`.
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

## 2026-07-30 bounded cold EOF tail

Localized target/candidate dumps close the remaining two one-sided references
to one duplicated candidate diagnostic. Native shares the initial
post-`Segments Begin:` level-path EOF block with the later `First:` line
advance, while retaining distinct filename and `Last:` diagnostics. The clean
source makes VC6 emit the initial block in place instead.

Three recorded sweeps cover the tempting alternatives. Changing the
segment-loop diagnostic from its correct `filename` owner to `level_path`
regresses to 77.88%. Reproducing the native shared branch with coupled labels
falls as low as 69.06% and increases unaudited reference entries from two to
twelve. Ordinary `!cursor` guards are byte-neutral; inverted success/else
forms fall to 71.90-75.15%.

Across 12 unique variants, none improve, three are byte-identical, and nine
regress or fail. The experiment ledger formally stalls this cold-tail lane.
The retained parser remains 84.63%, 941/926 instructions, prefix 20/926, with
183 clean references and the two candidate-only diagnostic entries. No wrong
path owner or explicit goto scaffold is kept to force tail sharing.

## 2026-07-31 message cursor ownership

The native message parser advances the already-address-taken `line_cursor`
past the opening quote and keeps that stack owner as the copy input. The
scratch instead introduced a third `message_start` pointer and copied it back
to `line_cursor` after every byte. Removing that synthetic owner restores the
native stack-backed input cursor and leaves one register-only closing-quote
sentinel. Android and iOS preserve the same single advancing message cursor.

All four direct increment/assignment/`for` spellings compile identically under
VC6. The retained direct form raises focused Wibo from 84.63% to 87.58%,
adding 89.73 weighted bytes. The candidate is 942 instructions against 926
native, with prefix 20 and the same 183 clean resolved operands. The only two
unaudited operands remain the already-bounded candidate-only cold EOF
diagnostic.

This owner correction also restores the downstream register chain rather than
only improving its local copy loop. The message end sentinel moves from EDI
to the native EDX lifetime, so EDI preserves the `-1` bit pattern first used
by the speed/hazard defaults and later reused for `message_sample_id`. The
sample-name scan, slot-stride arithmetic, default store, and registered-sample
lookup then align with the target.

The file loader declaration now matches its exact standalone wrapper:
`void* (char*, void*, int*)`. Pointer-return/buffer prototype variants are
byte-neutral. A seven-variant fallback-call sweep does not recover the
native's aggregated caller-stack cleanup; attempting a void diagnostic result
is rejected at compile time because the included canonical declaration
returns `int`, and no conflicting prototype is retained. The complete ledger
now contains five sweeps and 23 unique variants, with the message-cursor sweep
as its sole source-shape win.

## 2026-07-31 galaxy route index ownership

The parsed number after `Arcade` is the authored Galaxy route index, not a
manually scaled byte offset. Windows keeps its `sizeof(GalaxyStar)` product in
EDI and uses that owner for the detail string, all three diagnostic text
destinations, and the successful text-copy destination. Android and iOS
independently retain the same parsed index and reuse its `0x2a0` stride across
the complete `GalaxyText:` branch family.

Expressing all five destinations as `route_slots[galaxy_route_index]` restores
the native offset-first indexed-address form. Two recorded owner sweeps cover
42 combinations: each converted description destination contributes the same
local improvement, and converting any three or all four reaches the same best
alignment. The retained complete owner raises focused Wibo from 87.58% to
88.12%, or 2678/3039 weighted bytes, while keeping 942/926
candidate/target instructions, prefix 20, and 183 clean masked operands. The
only two unaudited operands remain the already-bounded cold EOF diagnostic.

The residual first mismatch is still the fallback caller-cleanup schedule.
Seven ordinary statement/comma/block groupings are byte-identical. A further
mobile-supported `void RShellError` contract probe, isolated from the
transitive Windows `int` declaration, is also byte-identical; the return type
does not explain VC6's cleanup boundary. Those two non-improving sweeps bound
the early cleanup hypothesis without retaining declaration shielding or
source-grouping scaffolds. The ledger now contains 11 sweeps and 81 unique
variants, with four improving sweeps and a trailing no-improvement streak of
two.

## 2026-07-31 CRT declaration cleanup bound

The remaining early difference is where VC6 reclaims cdecl argument space
across the fallback `report_errorf`/`sprintf`/file-load calls and the later
Galaxy parse/format calls. The exact standalone error reporter confirms its
integer return contract, while the file loader already has its exact wrapper
prototype. The final untested declaration owner was therefore the real CRT
`sprintf(char*, const char*, ...)` contract.

All four const-qualified, explicit-cdecl, and C-linkage spellings are
byte-identical at **88.12%**, 942/926 instructions, prefix 20/926, 183 clean
references, and the same two bounded unaudited EOF diagnostics. The standard
const-qualified declaration is retained as source truth, but it does not move
the cleanup boundary. The ledger now contains 12 sweeps, 86 evaluated and 85
unique variants, with a three-sweep no-improvement streak. The parser is
formally stalled pending new compiler or original-source provenance for that
cleanup schedule.
