# populate_runtime_track_cells_from_segments

Current recovery: semantic-complete (`analysis` residual). Exact
Android/iOS `cRSubGame::BuildLevel()` bodies, the live Windows member, and the
complete Windows producer/consumer chain establish session setup, segment and
row selection, all glyph dispatch arms, runtime cell/row construction,
attachments, parcels, rings, fringe objects, and completion handling. The
current candidate has 1,244/1,246 code instructions, a 76-instruction prefix,
and 165 clean aligned references with no reference debt. The function remains
partial at 85.8815%; its reference alignment is diagnostic, not positional
proof of exactness.

## 2026-09-11 completion and field-owner recovery

One completion-mode `if`/`else`, indexed authored-row parcel selection,
indexed runtime-cell attachment-template accesses, and a borrowed unsigned
stamped-row flags field recover native branch and store scheduling. The last
change restores the flag store before each primary/secondary cell-pointer
store. The 68-byte frame is unchanged. The Windows and exact mobile bodies
establish the behavior; the remaining code differences still require analysis.

Scoring policy 5 now recognizes the 94-byte guarded glyph remap as literal
data rather than instructions. The old source scores 75.8017% under that same
policy, versus the retained 85.8815%. Its previously published 74.6988% used
policy 4 and is not a directly comparable source baseline.

The two dated mutation recipes record 13 final controls under epoch v2.
None improves this source. Only the flags-pointer control has identical
code/relocation identity; negative selection and a `for` stamp loop preserve
the metrics with different identities. These are bounded results, not evidence
of a compiler ceiling. See the [report](../../buildlevel-and-lookup-20260911.md)
and [complete receipt](../../buildlevel-and-lookup-20260911.json) for source and
assembly differences, all reference rows, table ranges, and replay controls.

populate_runtime_track_cells_from_segments @ 0x435eb0. The function that
DEFINES the grid conventions the 2026-06-13 grid-alignment audit hinges
on.

## Historical scratch status

The subsequent `post-lookup-position-lifetimes-20260911.json` recipe tests
seven forms against the retained 85.8815% source. Removing the eager segment
cursor initialization reaches 80.2781% with prefix 77; replacing cell clearing
with a vector value reaches 79.5190% with prefix zero. Explicit indexed or
reference position owners preserve the metrics but have different relocation
identities; only the chained cell-zero stores preserve the code/relocation
identity. No source change is retained. The
[initializer-boundary receipt](../../initializer-boundaries-20260911.json)
contains the complete results under the current report-aware epoch.

Promoted to a matcher scratch on 2026-06-13. Historical result after the
glyph-dispatch, authored-row, attachment, clear-loop, segment-scoped row
builder, direct runtime-row, segment-extension, ring/lane, switch-field
ownership, and producer-backed trampoline cadence slices: 75.79%, 1254/1245
candidate instructions, with a
76-instruction exact prefix
(`uv run snail match scratch
tools/match/scratches/populate_runtime_track_cells_from_segments --regions
--max-regions 8`).

The first scratch is intentionally structure-first and covers the deterministic
setup before the authored-row/glyph pass:

- runtime build seed selection from selected-record replay, mode 4/7 zero seed,
  or the `"Seed"` RNG draw;
- mode 0/1/4 high-score entry initialization;
- replay cursor reset, subgame rebuild selector 3 -> 1, visible life stock
  reset to 3, score-bucket/timer clears, RNG seeding, and texture-set select;
- row-count seeding for modes 0/1/3/4/7, including challenge difficulty
  scaling, non-random segment row-count summing, completion row start, and the
  3100-row report gate;
- the 3200-row runtime-row/cell clear pass and random-segment visited-byte
  reset;
- the first main row-loop slice after the visited reset: empty-row return,
  Start/Last block selection, random or sequential segment choice, per-segment
  row owner store, negative-length report, mirror row flag, first authored
  row-flag bits (`0x100`/`0x8000`), and row source/owner fields;
- completion-row segment override/extension and the authored-row payload copy
  before glyph normalization: bod/parcel row payloads, pass-through row flags,
  and the authored row event id;
- the lane setup and first glyph normalization switch slice: lane word reset,
  cell payload clear, edge-row classification, bod reset, normalizer dispatch,
  hidden/floor/wall/ramp/simple bod tiles, digit row payloads, trampoline
  cadence, mirror glyph, warning tile, prior-row ramp retags, `P`/`p`
  attachment entry install, and shared post-switch anchor/color/UV/sub-object
  placement.

2026-06-14 type cleanup: `set_color_white` is now declared as a void mutator,
matching the exact standalone helper and `build_track_colours`. This removes
the stale ignored-float signature from the scratch without changing the broad
7.13% status.

2026-06-15 row-selection slice: focused score moved from 7.52% to 11.10%,
with masked operands 24 ok / 0 mismatch. The challenge random segment weighting
is `0.9 * difficulty + 0.1`, distinct from the earlier row-count scaling.

2026-06-15 row-copy slice: focused score moved from 11.10% to 13.51%, with
masked operands 26 ok / 0 mismatch. This covers the special completion-row
segment handoff plus the authored row bod/parcel payload fields and row flag
pass-through bits.

2026-06-15 lane/glyph slice: focused score moved from 13.51% to 18.90%, with
masked operands 46 ok / 0 mismatch and one unresolved jump-table displacement
on the candidate side. This keeps the switch source honest enough to preserve
call-target alignment; the earlier long-lived cell bod local regressed into a
set_bod_object/normalizer call mismatch and was avoided.

2026-06-16 attachment-entry cross-check: the native `P`/`p` path was decoded
but not kept as source yet. It sets tile 0x1e for `P` and 0x1d for `p`, selects
an attachment-template bank at `game + 0xff2914` or mirrored `game + 0xff29bc`
with a 0x150 stride from row +0xa0, stores that template at cell +0x38, clears
the cell visible-bod flag, and uses a separate per-row install latch so only
the first entry cell arms the row. That first entry cell installs template
bod pointers from template +0x24 and +0x84, writes row +0xac from
`active_segment + 0x4014`, and stamps row flags 0x40/0x80 plus
primary/secondary cell pointers over `Path::row_span_count`
rows. `Path +0x48` is therefore a runtime row-span count,
not an unknown field. A standalone source block for this path compiled to
17.21% because it shifted switch-region alignment before the shared post-switch
anchor was present, so keep the source unchanged until the entry path and
post-switch anchor can be landed together.

2026-06-16 entry/anchor slice: `P`/`p` plus the shared post-switch
anchor/color/UV/sub-object block are now in source. Focused score moved from
18.90% to 27.24%, with masked operands 57 ok / 1 unresolved / 0 mismatch. The
lane correction matters: anchor/UV math uses the runtime lane loop counter,
while glyph lookup uses the mirrored authored lane. The native entry-tile
anchor also puts `cell->position.z` at the row boundary (`row + 0.0`),
not the non-entry `row + 0.5` center. Remaining residuals are source-shape
issues: candidate frame is still `0x40` vs native `0x44`, and the jump-table
displacement remains unresolved. Do not pad the frame or force switch layout
with dummy code.

2026-06-16 high-score dispatch slice: replaced the scratch's temporary
`archive_kind` local with a source-level `switch (level_mode)` that calls
`initialize_high_score_entry` for modes `0`, `1`, and `4`. This recovers the
native merged case dispatch (`mode`, `mode-1`, `mode-4`) and moves focused Wibo
from `27.24%` to `28.20%`; region 2 improves from `38.38%` to `60.78%`.
Masked operands stay `57 ok / 1 unresolved / 0 mismatch`; the unresolved
jump-table displacement in the glyph switch is unchanged.

2026-06-16 segment-rate reset slice: the native random/sequential next-segment
handoff writes `Game::base_subgame_rate` (`+0x48`) back to `1.0f` before
selecting the next active segment. Landing that as a typed member assignment
moves focused Wibo from `28.20%` to `28.25%`, with candidate instructions
`1188/1245 -> 1190/1245`. Masked operands stay `57 ok / 1 unresolved /
0 mismatch`; the remaining local order difference (`random segment flag` load
vs the `+0x48` store) is compiler scheduling, and the equivalent raw field
write did not improve the match.

2026-06-16 entry shared-field pass: the `P`/`p` path now writes the shared
`cRSubLoc::attachment_template_record`, uses
`Path::row_span_count`, and stamps
`TrackAttachmentRuntimeRow::primary_attachment_cell` /
`secondary_attachment_cell` over the template span. Focused Wibo remains
`28.25%`, `1190/1245`, with `57 ok / 1 unresolved / 0 mismatch`. This is
relationship evidence rather than a score slice: the builder produces the same
fields consumed by `begin_track_attachment_follow_state`,
`project_position_onto_track_attachment`, `place_parcels_on_track`, and the
player attachment-entry path.

2026-06-16 layout assertion pass originally padded
`Path` to `0x150` to preserve the observed index stride.
The 2026-07-10 constructor callsite audit supersedes that temporary model: one
record is exactly `0xa8`, `PathPair` is `0x150`, and the two
former bank roots are the primary/secondary fields of one 63-pair array.

2026-07-11 cRPath ownership: symbol-preserving ports name each `0xa8` receiver
`cRPath`; the Windows root therefore owns 126 individual paths as 63 adjacent
`PathPair` records. The focused builder remains at 28.25%, so this is a
codegen-neutral ownership recovery, not a score-driven relabeling.

2026-06-17 runtime/root consolidation: the scratch now uses the shared sparse
`cRSubGame` root and the named `TrackAttachmentRuntimeRow` fields
`parcel_set_id` and `attachment_template_index`. Focused Wibo remains 28.25%,
1190/1245 candidate instructions, with masked operands 57 ok / 1 unresolved /
0 mismatch. This is a field-evidence pass, not a source-shape fix: the exact
helpers `get_track_skirt_color`, `spawn_track_parcel`,
`rebuild_track_runtime_from_segments`, and `refresh_fringe_object_draw_list`
prove the root offsets kept in `subgame_runtime.h`, while populate still needs
separate source-shape work for the frame and glyph-switch residuals.

2026-06-20 glyph switch-table audit: the normalized-glyph jump table at
`0x437194` and byte lookup at `0x437204` are now named. Focused Wibo remains
`28.25%`, `1190/1245`; masked audit is now `57 ok / 0 unresolved / 1 mismatch`.
The remaining glyph-switch debt is a real table-layout mismatch, not an
unknown local-label relocation.

2026-06-21 receiver cleanup: the scratch now defines
`cRSubGame::BuildLevel` directly and
removes the duplicate local `Game` field window. Focused Wibo remains `28.25%`,
1190/1245 candidate instructions, prefix 0/1245, with the same `57 ok / 1
mismatch` masked audit. `uv run snail match types --paths` now reports
`partial-compatible Game: 3`, with this scratch removed from the remaining
generic owner list.

## 2026-07-10 pair-bank alias

The raw `+0xff2914/+0xff29bc + index*0x150` spelling remains in this large
scratch because the natural typed pair expression changes VC6 branch/address
formation and globally reshuffles locals. The shared `cRSubGame` header
now owns the exact `PathPair[63]` field; retaining the native
arithmetic here is source-shape preservation, not an unresolved owner.

## 2026-07-10 runtime slab ownership pass

- `cRSubGame` owns a fixed `cRSubLoc[3200][8]` slab at `+0x3bfac8`.
  Its exact `0x20d000` extent lands at `+0x5ccac8`, where a fixed
  `SubRow[3200]` slab begins; the row slab's exact
  `0xbea00` extent lands at the embedded `SubHighScore` at `+0x68b4c8`.
- Each runtime row embeds a `RowModel` at `+0x04` and a `BodBase` at `+0xb0`.
  The first is the authored row actor removed by
  `remove_subgame_bods`; the second is the attachment/fringe row actor built
  by the `P`/`p` path. Intrusive list membership does not transfer ownership
  of either body away from the row slab.
- The row's embedded `RowModel` owns the copied velocity at outer `+0x84`.
  The outer `SubRow` owns `installed_heading_delta +0xac` and
  `ring_speed +0xe8`. Its
  `primary_attachment_cell`, `secondary_attachment_cell`, and
  `source_segment +0xec` fields are borrowed pointers into the sibling runtime
  cell slab and the embedded level-segment bank.
- A fully typed row-writing spelling regressed focused Wibo to `26.40%`,
  shortened the candidate to `1179/1245`, and introduced two call-alignment
  audit mismatches. The scratch therefore keeps its native-shape byte cursor;
  the shared owner layout is exercised by the exact row/cell lookup helpers
  instead of forcing typed expressions into this large switch.

## 2026-07-12 build-session ownership pass

- The selected replay/high-score source is now read through
  `selected_level_record_active` and the borrowed `selected_level_record`.
  Modes 0, 1, and 4 reset the embedded
  `cRSubGame::current_high_score_record` directly; the scratch-local
  `HighScoreEntry` lookalike was not a separate owner.
- The setup reset now names `replay_update_cursor` and the embedded `Player`
  fields it actually mutates: `total_score`, `stopwatch`, `score_tail`,
  `shooting_tier`, and `visible_life_stock`. The score-bucket reset is
  likewise invoked on that same `Player` owner.
- The high-score argument at runtime `+0x30` is the `level_arg_tail` view of
  the base-rate union, and the initial mirror reset now uses
  `track_mirror_enabled` / `track_mirror_repeat_count`.
- All changes are codegen-neutral: focused Wibo remains the honest 28.25%,
  1190/1245 instructions, with 57 clean masked operands and the known glyph
  jump-table layout mismatch. This slice removes fake setup owners without
  perturbing the still-incomplete glyph-builder source shape.

## 2026-07-13 segment-session ownership pass

- `SubSegment +0x08` is a byte-sized random-selection `visited` latch, not an
  integer. Native code clears exactly one byte for every eligible segment and
  sets exactly one byte after a random pick; the shared matcher and analysis
  layouts now preserve the following three padding bytes explicitly.
- Setup and selection now read the owned `SubTracks` First/Last row counts,
  random length/enable state, level display name, and segment-row counts
  directly. The rebuild gate and player follow latch likewise use their shared
  `cRSubGame`/`Player` owners. These substitutions preserve the honest
  28.25%, 1190/1245 frontier and its 57 clean operands plus the known glyph
  table-layout mismatch.
- The mode-3 raw addresses `+0x1b4410`, `+0x1bc850`, and `+0x1c0a70` are
  `level_definition_scratch.segment_slots[1]`, `[3]`, and `[4]`. A fully typed
  active-segment pointer spelling moved the score to 28.17%, so the byte-shaped
  address formation stays visible. Recasting the authored-row copy repeated
  the previously measured 26.40% regression and was also reverted; neither
  residual is hidden with dummy source or masked proof.

## 2026-07-14 path render-body ownership

- The `P`/`p` entry installer no longer reads opaque `Path +0x24/+0x84`
  pointers. The exact `initialize_path_template_record_pair` constructor proves
  that each `Path` owns an inherited `BodBase` at `+0x00` and a second
  `fringe_mesh_bod` at `+0x60`; the two lanes are therefore
  `Path::object` and `Path::fringe_mesh_bod.object` respectively.
- The runtime entry cell borrows the public strip mesh, while the row's
  embedded attachment body borrows the generated fringe mesh. The raw
  primary/secondary pair-bank address formation remains deliberate because its
  typed equivalent changes the large function's register and branch layout.

## Build sequence

1. runtime_build_seed: replay -> recorded seed; modes 4/7 -> 0; else
   `_ftol(random_float_below(32768.0))` (one pre-seed draw — matches the
   port's nextInt15 gate for postal/challenge).
2. initialize_high_score_entry with mode-mapped archive kind (0 postal,
   1 challenge, 2 time-trial via mode 4... mode switch on 0/1/4).
3. lives-to-3 reset when the subgame state lane was 3, zero timers,
   `set_math_random_seed(seed)`, texture set select.
4. Row-count seeding: modes 0/7/4/1 take first_block_row_count +
   authored Length (mode 1 scales by `rate*c1 + c2` then fimul), or when
   the random flag byte (+1293082) is clear: first + last + sum of all
   segment row counts. completion_row_start = rows - last_block_rows.
   Mode 3: first + last + 16 * segment[0] rows. Cap 3100 rows
   ("Track (%s) too long").
5. Grid clear: 3200 rows x 8 cells; row records (244 stride) zeroed
   field-by-field; cells (84-byte stride, 672/row — the golb scratch's
   cell-672 = previous row) get flags &= 0x5F / &= 0xFFFFAFA7 masks,
   color white, vec4 zero at +0x40.
6. Authored copy per selected segment: segment cursor walk with the mode-1
   random segment pick. Crossing a segment boundary clears the first/last-row latch,
   resets `base_subgame_rate` to `1.0f`, then picks
   `random_float_below(mode==1 ? rate*c3+c4 scaled count :
   (float)segment_count)` -> 16928-stride segment, marks +8 visited;
   start rows use the Start block, completion rows the Last block (and
   mode 3 the special block at +1786896). `track_mirror_enabled` (game+2)
   ORs row flag 0x20 and flips authored lanes and mirrored attachment-template
   banks. `switch_track_mirror` runs once on the common selected-segment tail;
   the `'@'` glyph invokes it again from dispatch
   (`track_mirror_repeat_count` at game+4 guards long runs).
7. Authored row flags map: bit2 -> bod row (object id from authored
   +522, matrix identity, position vec from +523..525 with z += row;
   bit8 nested -> aux vec at +526..528), bit1 -> parcel row (flags |=
   0x4001, payload vec +519..521, aux dword from authored row +37),
   bit8 -> 0x08 + extra dword +529, bit4 -> 0x04, 0x200/0x400/0x800/
   0x1000/0x2000 pass through, 0x100 -> 0x100 (the no-drag bit),
   0x8000 -> 0x8000. Per-row int at game+4*(row+60*...)+... = authored
   +530 (the row event id lane).

## Glyph -> runtime tile table (the authoritative mapping)

  ' ' 0 (hidden)        '#' 32               '$' 23
  '&' 34                '(' 22 — every 15th resets the cadence counter,
                        the 8th gets the VISIBLE bod + white color
  '+' 24                ',' 28 (y -= c)      '-' 21
  '.' 1 (floor)         '0'-'9' -> attachment rows: 0 hidden; else
                        tile 15 + bod (parcel digits become slide
                        family!); mode-1 '0' also writes the row parcel
                        payload directly (x = lane-4.0+0.5, mirrored *-1)
  '<' 6                 '='/'|' 14 (wall2)   '>' 3, after prior-row 3:
                        9 + prior cell retagged 12
  '@' 0 + `cRSubGame::SwitchMirror()` (the mirror toggle glyph)
  'F' 19                'G' 17               'J' 25
  'M' 18                'P' 30 / 'p' 29 (attachment entry pair; first
                        cell of the row arms the install: template from
                        336-stride bank (mirror picks +980 vs +812
                        column), span rows get 0x40, OVERLAPPED rows
                        0x80 (the dual-owner bits the swept entry
                        consumes), cell+0x38-style template ptr written)
  'R' 35                '[' 5                '_' 15
  'o' 16                's' 33
  '{' 2, after prior 3: 8 + prior retag 11
  '}' 4, after prior 3: 10 + prior retag 13
  default -> normalize + report (sub_449C00)

## Cell anchor math (grid-audit ground truth)

- non-entry tiles: anchor.x = (float)(runtime lane) - 4.0 + 0.5
  (lane CENTER, [-3.5 .. 3.5]); anchor.y = 0 except ramp-tops 8/9/10
  (= 0.5), rows < 4 non-mode-2 (start platform global), tile 28
  (y -= c), tile 22 keeps y = -1.5-ish const (-1069547520 = -1.5)
  outside mode 3 unless flags & 0x400; anchor.z = row + 0.5.
- entry tiles 29/30: anchor.x = 0.0 (CENTERED — the whole row is the
  attachment), anchor.z = row + 0.0; the row projection/skirt branch also uses
  row + 0.0. The local row + 0.5 value is not the entry cell anchor.
  Skirt-color object variant under byte_4DF934 & 0x20.
- floor family checkerboard uvs: tiles {1,15..27,33,34} get
  (8-runtime-lane)*c and (row%8)*c uv scalars.
- tile 31 anchor.x *= c (497434).
- 4 sub-object slots at cell+0x4c..: position row copied, vec zeroed.

## Replay record analysis ownership (2026-07-13)

The path-template analysis header formerly called the borrowed runtime pointer
target `SelectedLevelRecord` and stopped after one replay sample. That prefix is
not an independent owner: its fields align exactly with `SubSolution`, and the
21,600 six-byte `ReplayRunRecord` entries plus four tail dwords prove the full
0x1fac0-byte authored `cRSubSolution` stride.

The Binary Ninja and IDA-facing campaign now exposes the exact `SubSolution`
and types `cRSubGame::selected_level_record +0xff25d4` accordingly. A
Binary Ninja declaration preview verifies `ReplayRunRecord == 0x06`,
`SubSolution == 0x1fac0`, and the borrowed runtime field without mutating the
database. This is an analysis ownership correction only; focused Wibo remains
the honest 28.25%, 1190/1245-instruction baseline with 57 clean operands and
the existing glyph-table mismatch.

## Runtime storage closure (2026-07-13)

The same analysis owner now replaces the anonymous `+0x3bfac8..+0xff25d0`
range with the three independently measured embedded stores:

- `cRSubLoc runtime_cells[3200][8]` at `+0x3bfac8`, ending at `+0x5ccac8`;
- `TrackAttachmentRuntimeRow runtime_rows[3200]` at `+0x5ccac8`, ending at
  `+0x68b4c8`; and
- the working `SubSolution current_high_score_record` at `+0xfd2b10`, ending
  exactly at the replay-launch flags at `+0xff25d0`.

Binary Ninja preview keeps the enclosing `cRSubGame` size at 0x1272838
while exposing those owned arrays and record, then reverts. No matcher source
was reshaped, so the focused 28.25% baseline and honest glyph-table mismatch
remain unchanged.

## Root BOD catalog consumer pass (2026-07-13)

Every root-owned track object selected by the glyph switch now resolves through
`GameRoot::root_bod_catalog`: floor/slide slice 0, trampoline, universe hole,
three ramp edges, and pillar 0. The spelling retains the byte-shaped switch and
runtime-cell cursors that VC6 needs for the established source shape. Focused
Wibo remains 28.25% (1,190/1,245), with 57 clean operands and the single known
glyph jump-table layout mismatch.

## Completed-segment event ownership (2026-07-13)

The builder stamps each runtime `SubRow::row_event_id +0xf0` from a local
completed-segment event-definition index. That index advances after the last
row of each segment. Mode 3 is the sole exception: its synthetic Start and Last
blocks set a `first_or_last_row` latch and suppress the advance, while ordinary
mode-3 segments still advance it.

The scratch previously recovered the latch assignments but then cleared the
latch before every lane pass and never advanced the event owner. Keeping the
latch for the selected segment and restoring the native tail condition recovers
the 0x44-byte native frame and improves focused Wibo from 28.25% (1,190/1,245)
to 29.27% (1,208/1,245). The only masked-operand mismatch remains the visible
glyph jump-table layout difference.

## Runtime BOD ownership (2026-07-14)

The scratch-local `TrackRowBodSlot` did not own any storage. The exact
`initialize_sub_loc` constructor runs the shared `cRBod` initializer over each
0x54-byte `cRSubLoc`; that owner now directly inherits `BodBase`, so glyph-selected
object writes call `BodBase::set_bod_object` through the real base while
retaining the raw cell cursor needed by the large VC6 switch.

The other two receivers are complete embedded owners, not prefix views:

- `SubRow::row_model +0x04` receives authored 3D row objects;
- `SubRow::attachment_body +0xb0` receives the installed path strip body.

The row field casts and attachment-span cursor now use canonical `SubRow`
instead of its historical `TrackAttachmentRuntimeRow` alias. No distinct
`cRSubLoc::set_bod_object` symbol or replacement shell was introduced. The
ownership consolidation is codegen neutral at `29.27%`, `1,208/1,245`, prefix
`2/1,245`, with `60` clean masked operands and the one known glyph jump-table
layout mismatch.

The skirt-color query now names `GameRoot::subgame` while retaining the root
pointer form needed by the large switch source shape. Focused metrics remain
unchanged.

The remaining root services in the builder now name their complete owners:
`GameRoot::track` chooses the level texture pair, and authored
row object ids index `GameRoot::directx_loader.cached_x_mesh_slots[].object`.
The root byte pointer remains only as the established source-shape carrier for
the large switch; no absolute root-plus-offset expression remains here.

The inherited-base promotion is byte-stable at the same 29.27%, 1,208/1,245
instructions, with 60 clean operands and the one known glyph jump-table
layout mismatch.

## Runtime clear-cursor ownership (2026-07-14)

The native clear pass still advances an interior cursor rooted at
`cRSubLoc::fringe_front` and another rooted at `SubRow::projection_payload.y`.
Those lifetimes are useful compiler evidence, but their former
`+0x3bfb0c/+0x5ccb5c`, 84-byte, 61-dword, and numbered negative/positive lane
constants no longer carry the layout themselves:

- cursor bases derive from `runtime_cells[0][0]` and `runtime_rows[0]`;
- row and lane counts derive from the owned 3200-by-8 arrays;
- cursor strides derive from `sizeof(cRSubLoc)` and `sizeof(SubRow)`; and
- every cleared row lane derives from `offsetof(SubRow, ...)`, covering flags,
  projection payload, parcel/template state, borrowed attachment/source links,
  heading/ring values, and the row-event id.

The adjacent cell deltas likewise derive `lane_and_flags`, `open_edge_mask`,
the inherited list flags, and inherited color from their real owners. The
track-texture selector and mode-3 repeated row count now read the embedded
`SubTracks` fields directly. Focused Wibo retains the existing 29.27%,
1,208/1,245 frontier with 60 clean operands and the sole documented glyph
jump-table mismatch; no typed whole-row rewrite or register-forcing alias was
introduced.

## Builder address ownership (2026-07-14)

The native byte cursors remain because earlier typed rewrites measurably changed
VC6 scheduling, but their large address constants no longer stand alone:

- ordinary, first, last, and mode-3 scratch segment addresses derive from the
  two embedded `SubTracks` owners, `SubSegment` stride, and slot indices;
- the row cursor derives from `cRSubGame::runtime_rows` and `sizeof(SubRow)`;
- the cell index cursor derives from `sizeof(cRSubLoc)`, while the mirror-byte
  lookup derives from `cRSubGame::track_mirror_enabled`;
- primary/secondary template selection derives from `path_pairs`, `PathPair`
  stride, and `PathPair::secondary`; and
- the early-row height seed resolves to path pair 36's borrowed
  `Path::primary_samples` pointer and `AttachmentSample::transform.position.y`.

A separately compiled pre-change scratch and this source produce identical
normalized candidate listings (SHA-256
`4b3b94f2fa2ea974a196c05e9d42f3c2ad75b0a0cc4f47739471d1996e5aa444`).
Focused matching therefore remains exactly 29.27%, 1,208/1,245 instructions,
60 clean operands, and the one documented glyph jump-table mismatch without
using a typed-expression regression or any match-only forcing.

## Authored/runtime row lanes (2026-07-14)

The row-copy phase now derives both sides of its byte-shaped transfer:

- the glyph grid, authored-row array, row stride, object id, local position,
  object position/velocity, path index, ring speed, and segment angle come from
  `SubSegment` and `AuthoredSegmentRow`;
- the destination model transform/position/velocity come from
  `SubRow::row_model` and its `RowModel`/`RenderableBod` bases;
- parcel projection lanes come from `SubRow::projection_payload`; and
- the installed attachment body's flags, position, render object, and color,
  plus the row's heading, ring speed, source-segment link, and event id, all
  derive from the complete `SubRow` owner.

This deliberately does not replace the established row pointers with aggregate
assignments: that spelling already has a measured codegen regression. Hashing
the normalized listing before and after this lane derivation again yields
`4b3b94f2fa2ea974a196c05e9d42f3c2ad75b0a0cc4f47739471d1996e5aa444`,
with focused metrics unchanged at 29.27%, 1,208/1,245 instructions, 60 clean
operands, and only the documented glyph jump-table mismatch.

## Runtime cell lanes (2026-07-14)

The glyph switch and placement tail no longer carry absolute
`+0x3bfa.../+0x3bfb...` layout facts. Their established base-relative cursor
now derives:

- the slab base and eight-lane row extent from
  `cRSubGame::runtime_cells`;
- object list flags, position, render arguments, and color from the inherited
  `BodBase` prefix;
- tile id, lane flags, and all four fringe links from `cRSubLoc`;
- the previous-row tile address from one owned eight-cell row stride; and
- the fringe propagation loop's count/step and destination positions from the
  four-pointer `cRSubLoc` tail and `BodBase::position`.

The unusual trampoline color address remains in its native index-bias form,
but that bias is now derived from the slab base plus `BodBase::color` divided
by `sizeof(cRSubLoc)`. The pre/post normalized listing hash is still
`4b3b94f2fa2ea974a196c05e9d42f3c2ad75b0a0cc4f47739471d1996e5aa444`;
focused Wibo therefore remains honestly unchanged at 29.27%, 1,208/1,245,
60 clean operands, and the known glyph jump-table mismatch.

## Authored BuildLevel and ramp branches (2026-07-14)

Cross-port symbol and full-body evidence identifies this Windows function as
authored `cRSubGame::BuildLevel()`. Android preserves the same seed and
selected-record setup, row-count construction, runtime-grid clear, `Segdif`
and `Negative Segment Length` diagnostics, segment selection, row copy, and
glyph construction. The exact wrapper at `0x437de0` is authored
`GenerateLevel(int)`, while the outer level lifecycle at `0x437eb0` is
`StartLevel(int)`.

That Android body also preserves the original branch-local shape for ramp
glyphs `>`, `{`, and `}`: each prior-row/non-prior-row arm repeats the
`set_bod_object`, render-argument clears, tile assignment, and list-flag update.
Restoring those duplicated operations instead of keeping a refactored common
tail raises focused Wibo from 29.27% to 29.67%, candidate instructions from
1,208 to 1,229 of 1,245, and clean operands from 60 to 66. The remaining two
reported operand mismatches are alignment artifacts (the glyph jump-table
label and a shifted call correspondence), not masked or fabricated matches.

`SubSegment::visited` is the byte at `+0x08`. Both Windows and Android clear it
for every eligible slot and set it after choosing a random segment, but neither
builder reads it during that selection loop. It is therefore owned selection
bookkeeping in this method, not evidence for a no-repeat rule here.

## Build-level service ownership (2026-07-14)

The remaining root-service accesses now use the recovered `GameRoot* g_game`
owner directly: level texture selection, cached DirectX mesh lookup, the root
BOD catalog, and track-skirt color resolution. Cached meshes and installed row
attachments are carried as their real `Object*` type through
`set_object_color`, rather than being weakened to `void*` at this call site.

The authored row-model reset likewise resolves through
`SubRow::row_model.transform.set_matrix_identity()`, and the skirt object
through `SubRow::attachment_body.object`. These two promotions remove local
service and offset aliases without converting the surrounding byte cursor that
VC6 schedules differently. Tested independently and together, the focused
result remains 29.67%, 1,229/1,245 candidate instructions, 66 clean operands,
and the same two documented alignment mismatches.

## 2026-07-14 authored-to-runtime row flags

The builder now names both sides of the copy: `AuthoredSegmentRowFlag` owns
parser metadata and `SubRowFlag` owns generated state. It preserves the shared
path/model-velocity lane, copies the model, render-suppression, NoFall, ring,
and jetpack lanes, and adds only runtime-owned mirror, attachment-span, parcel
candidate, and local-z state. The mode-1 digit parcel path explicitly clears
local-z before storing an already absolute row coordinate. Focused output is
byte-identical at 29.67%, 1,229/1,245 instructions, 66 clean operands, and the
same two alignment mismatches.

## 2026-07-14 game-wide feature owner

The mode-3 tile-`0x16` branch now consumes the shared game-wide
`SUBGAME_RUNTIME_FLAG_ALLOW_FALLING` bit instead of a raw `0x400`. This is not
the per-row `SUBROW_FLAG_NO_FALL` lane. Focused output is byte-identical at
29.67%, 1,229/1,245 instructions, 66 clean operands, and the same two
documented mismatches.

## 2026-07-16 follow-state tail reset

The initialization write at `Player::follow_state +0x3c` now resolves through
the durable `FollowState::flag_3c` owner in both analysis lanes. This function
is the only recovered writer and clears the byte before constructing runtime
rows; `update_subgoldy` is the only recovered reader. Because no nonzero
producer is proved, the field remains neutrally named. The matching source and
its 29.67%, 1,229/1,245-instruction result are unchanged.

Reanalysis also corrected the pre-biased EDI row-reset cursor from a historical
`float*` inference to `int32_t*`, matching the matcher source's intentional
mixed-field word cursor. That costs some incidental HLIL field folding in this
one loop, but pinning the old float view would falsely type integer flags,
indices, and pointers as scalar floats. The honest integer cursor is retained;
the surrounding `SubRow` layout remains proved by its declarations and later
typed consumers.

## 2026-07-16 containing-owner stride cursors

VC6 does not materialize final element pointers in the central construction
loop. It keeps three containing-owner bases and advances them at the exact
native strides: `SubSegment + row * 0x38`, `cRSubGame + row * 0xf4`, and
`cRSubGame + cell * 0x54`. Analysis-only overlapping views now preserve
that real source ownership while exposing the consumed `AuthoredSegmentRow`,
`SubRow`, and `cRSubLoc` members at `+0x814`, `+0x5ccac8`, and `+0x3bfac8`.
The cell view also names the guarded same-lane tile one eight-cell row behind
the current cell instead of rendering it as an unrelated prefix byte.

The compiler-reused stack lifetime at the authored-row ordinal is now the
integer `segment_row_index` in both decompilers; it is no longer tainted as a
`cRSubGame*`. Binary Ninja's exact SSA identities and IDA's exact lvar
definition addresses replay idempotently. This removes 39 raw owner
displacements from Binary Ninja and recovers the same owner chain in IDA.
Matcher source is unchanged at the honest 29.67%, 1,229/1,245-instruction
frontier with the two documented alignment mismatches; no score-shaped source
or operand fakematch was introduced.

## 2026-07-18 attachment-span row cursor

The `P`/`p` installer has one further exact element lifetime inside the broader
containing-owner loop. Its cursor starts at `&runtime_row_anchor->row`, writes
`SubRow::flags`, `primary_attachment_cell`, or
`secondary_attachment_cell`, and advances by exactly `sizeof(SubRow) == 0xf4`
for `Path::row_span_count` rows. Binary Ninja identifies that lifetime as
`RegisterVariableSourceType(3857, 67)`; IDA identifies the same local at
definition address `0x436dc2`.

Both replay lanes now preserve it as borrowed `SubRow* stamped_row`. Binary
Ninja emits direct field writes and `stamped_row = &stamped_row[1]`; IDA emits
the same fields and `++stamped_row`. A second replay is idempotent in both
databases (779 BN operations skipped; IDA reports the local unchanged, zero
parse errors, and no failures). Matcher source remains untouched at the honest
29.67%, 1,229/1,245-instruction frontier with the same two alignment
mismatches; this is ownership recovery, not match shaping.

The resulting BN reanalysis also corrects two prefix-equivalent
`set_bod_object` receivers from the embedded `vtable` word to the enclosing
`cRSubLoc`/`BodBase` prefix. Those are accepted type-propagation
improvements in the same function; they do not alter matcher source or bytes.

## 2026-07-18 fringe position propagation

The placement tail iterates the four contiguous borrowed fringe links at
`cRSubLoc::fringe_front` through `fringe_back`. The native ECX lifetime is
therefore an exact `FringeObject**` slot cursor. Its two EAX reloads are the
borrowed `FringeObject*` in that slot, and their derived `+0x10` address is
exactly `&FringeObject::bod.position`, a `Vec3*`; it is not an integer buffer
or a separately owned position.

The BN replay pins those identities at `(4697, 67)`, `(4697, 66)`,
`(4714, 66)`, and `(4718, 66)`, plus the exact four-slot counter at
`(4692, 68)`. IDA pins the corresponding locals at `0x437101`, `0x437105`,
`0x43710a`, and `0x43711f`. Both second replays are idempotent. The resulting
decompiles directly expose `FringeObject::bod.position` in both lanes, and IDA
replaces its former integer position casts with `fringe_position->x/y/z`.
Matcher source remains untouched at 29.67%, 1,229/1,245 instructions, 66 clean
operands, and the same two documented mismatches; no fakematch was introduced.

## 2026-07-18 builder-loop state ownership

The restored Binary Ninja session closes eight single-role stack lifetimes
shared by the segment and cell construction loops: `segment_cursor`,
`trampoline_counter`, `first_or_last_row`, `row_event_owner`, `build_row`,
`active_segment`, `attachment_entry_installed`, and `lane`. IDA identifies the
same source variables at their exact stack definitions. In particular,
`row_event_owner` is stored into every completed `SubRow::row_event_id`, while
`first_or_last_row` suppresses that advance only for the synthetic mode-3
Start/Last blocks. The random-length/edge-row stack reuse remains neutrally
named because it has two distinct roles and is not a safe ownership claim.

The matcher tail now carries the four contiguous borrowed fringe links as
`Fringe**` and each pointee as the complete inherited `Fringe` owner. Position
clears and copies therefore resolve through `Fringe::position` rather than
integer address arithmetic. VC6 emits the same normalized candidate listing:
29.67%, 1,229/1,245 instructions, 66 clean operands, and the same two honest
alignment mismatches. No table alias, forced register, or dummy dependency was
added.

## 2026-07-18 visited-cursor register ownership

The runtime clear pass reuses ECX for four unrelated source lifetimes: the
eight-cell fringe-link countdown, `SubTracks::segment_count`, a borrowed
cursor beginning at `SubSegment::visited`, and the final `cRSubGame*`
loop owner. Treating that physical register as one `cRSubGame*` produced
the false `segment_count->scan_reset` expression and also tainted helper-call
results and integer loop conditions.

Binary Ninja exposes separate definition identities at `0x436165`,
`0x4361a1`, `0x4361ad`, and `0x43714d`. The countdown and byte cursor also
cross loop phis and update definitions at `0x43616a`/`0x436171` and
`0x4361b3`/`0x4361bd`; replaying only their entry definitions lets HLIL
coalesce them again. The durable replay therefore splits and merges each
complete SSA lifetime before typing the four roles as `int32_t`, `int32_t`,
`uint8_t*`, and `cRSubGame*`, respectively.

IDA independently recovers the same byte cursor and now names it
`visited_cursor` at its Hex-Rays definition locator `0x4361ae`. Its `+16928`
step is exactly `sizeof(SubSegment) == 0x4220`,
so the cursor remains a borrowed field address rather than being falsely
promoted to an owning `SubSegment*`. The incidental random-helper spill at
stack `-0x5c` remains without user-authored metadata because its source role
is not proved.

The focused replay is idempotent in both databases: Binary Ninja skips all
four complete lifetime groups as already current, while IDA reports 279 type
operations and 108 names unchanged with no missing or failed operations. The
strict focused export passes both decompilers and all 768 health checks.

Matcher source and operands are untouched; the normalized candidate remains
at the honest 29.67%, 1,229/1,245-instruction frontier with 66 clean operands
and the same two documented alignment mismatches. This pass only corrects
durable analysis ownership and adds checks rejecting the former false runtime
owner; no score-shaped source or operand fakematch was introduced.

## 2026-07-19 runtime tile identity ownership

The authored glyph switch now writes the shared byte-sized `SubLocTileId`
vocabulary instead of anonymous integers. The names preserve exact producer
evidence: glyph-derived floor/slide/ramp variants, the Wall2 projectile tile,
pickup and hazard markers, path-entry case, and the ring marker. The same
constants are consumed by `cRSubLoc::IsFloor/IsRamp/IsEmpty/IsSlide`, the floor
height sampler, edge/fringe passes, runtime dispatcher, player movement, Golb,
and SubLazer paths.

The field remains an unsigned byte; the value enum is deliberately separate
because VC6 ordinary enums are four bytes. Rebuilding the broad scratch leaves
the honest result unchanged at 29.67%, 1,229/1,245 instructions, 66 clean
operands, and the same two jump-table operand mismatches. No branch, table,
register, or source dependency was changed for score.

## 2026-07-19 runtime grid clear lifetimes

The non-random length pass borrows `SubSegment::row_count` from each of the
authored segment slots. Binary Ninja's exact EAX/ECX/EDX identities now expose
that loop as `segment_slot_index`, `segment_row_count_cursor`, and
`segment_row_count`; the cursor advances by `0x4220`, exactly
`sizeof(SubSegment)`. It remains an `int32_t*` field cursor rather than being
promoted to a fabricated, negatively biased `SubSegment*` owner.

The following 3,200-row reset carries two more physical field cursors. The
row cursor starts at `SubRow::projection_payload.y` and advances by `0xf4`,
while the cell cursor starts at `cRSubLoc::fringe_front`, derives the
neighboring `lane_and_flags` word at `-4`, and advances each lane by `0x54`.
The replay names both outer countdowns, the lane-and-flags and list-flags
values, and the current/next fringe-link cursors. It deliberately leaves the
compiler's old-value loop temporaries anonymous and does not pretend either
field cursor is a complete record owner.

All 12 annotations survive reanalysis and a second guarded replay skips all 12
as already current. The strict focused export passes both decompilers and all
898 pre-existing health checks; the new owner-graph check pins the exact
stride/cursor result. Matcher source and operands remain untouched at the
honest 29.67%, 1,229/1,245-instruction frontier with 66 clean operands and the
same two documented mismatches. No score-shaped source or operand fakematch
was introduced.

## 2026-07-24 authored glyph lane ownership

The eight-lane materialization loop now keeps its two lane identities
separate. `runtime_lane` selects the physical `cRSubLoc` written in
`runtime_cells`, while `authored_lane` is either that lane or `7 - lane` and
indexes the borrowed active `SubSegment::glyph_rows`. Their two branch
definitions and SSA joins are replayed as complete lifetimes; naming only the
branch writes left anonymous join values and was rejected before export.

The stack slot used for `SubTracks::random_length` during setup is reused much
later as the byte `edge_row` normalizer argument. Its first/last-block writes
and SSA join are split away from the earlier integer lifetime, so HLIL now
passes `edge_row` to `normalize_segment_glyph_for_track_flags` instead of
falsely displaying the low byte of the authored random length. The active
segment register is likewise split from the byte glyph loaded through it.
Together these recover the direct producer chain
`active_segment->glyph_rows[authored_lane][segment_row_index]` to
`normalized_glyph` without inventing a new owner.

IDA independently preserves the same `lane`/mirrored-lane distinction, names
the stack byte `edge_rowa`, and carries a `char*` glyph cursor into the same
normalizer call. The following anchor and UV lane now retain `cell_anchor_z`
and `uv_row_index`; Binary Ninja also recovers the correct
`set_bod_object(&runtime_cell_anchor->cell, ...)` receiver on several switch
arms instead of the former interior `bod.vtable` display.

Matcher source and operands remain untouched. This is durable analysis
ownership only: no branch, table, dummy dependency, or masked operand was
changed to improve the score. The focused matcher remains at the honest
29.67%, 1,229/1,245-instruction frontier with 66 clean operands and the same
two documented jump-table/call-alignment mismatches.

## 2026-07-24 IDA runtime-row materialization ownership

IDA now preserves the same borrowed `SubRow` owner that Binary Ninja already
recovered for the authored-row copy. The physical `RuntimeRowStrideAnchor*`
still points into `cRSubGame::runtime_rows`; exact numeric-operand
normalization only prevents the large `+0x5ccac8..+0x5ccba0` displacements
from colliding with IDA's auto-created `byte_5CCAC8` / `unk_5CCBxx` symbols.
The refreshed pseudocode therefore resolves `source_segment`, `row_event_id`,
row flags, `row_model`, projection/parcel payload, attachment template and
heading fields, and the embedded `attachment_body` through the borrowed row
instead of inventing process-global owners.

The clear loop is likewise pinned to its physical field cursors:
`segment_row_count_cursor`, `parcel_spawn_y_cursor`,
`lane_and_flags_cursor`, and the current/next fringe-link cursors. These are
borrowed interior addresses with exact `0x4220`, `0xf4`, and `0x54` strides;
none was promoted to a complete-record owner. IDA's x87 instructions expose
implicit `st0` as operand zero, so their row displacements are guarded at
operand one and verified by readback.

The replay is idempotent, the strengthened cross-decompiler health suite passes
all 930 checks, and matcher source and operands remain untouched at the honest
29.67%, 1,229/1,245-instruction frontier with 66 clean operands and the same
two documented mismatches. No score-shaped source, register coercion, dummy
dependency, or masked-operand fakematch was added.

## 2026-07-24 authored render-suppression handoff

The builder now names authored bit `0x04` by its proved downstream contract:
`AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER` is copied directly to
`SUBROW_FLAG_SUPPRESS_TRACK_RENDER`. The parser supplies it from the post-row
`*` syntax, while `merge_track_tile_runs` and `build_track_fringe_objects`
independently consume the runtime bit to remove row-owned body/list and
directional-fringe rendering. The complete producer/handoff/consumer chain
supports the semantic name; it is not inferred from punctuation alone.

This ownership-only rename leaves focused matching unchanged at 29.67%,
1,229/1,245 instructions, with 66 clean operands and the same two documented
jump-table/call-alignment mismatches.

## 2026-07-24 parcel spawn-position producer

The parcel-row path now names `SubRow +0x90` as
`parcel_spawn_position`. It copies the authored row's local x/y/z only when
the parcel-candidate bit is present. The two parcel placers subsequently
convert that same vector to world space, and `update_subgame` hands it directly
to `spawn_track_parcel`. This complete lifecycle proves a parcel-owned spawn
position rather than a generic projection payload.

The field rename preserves its exact 0x90 offset, the physical y-lane reset
cursor, and all codegen. Focused matching remains 29.67%, 1,229/1,245
instructions, with 66 clean operands and the same two documented mismatches.

## 2026-07-24 runtime clear field-stride ownership

The 3,200-row reset does not carry whole-record owners. It carries three
borrowed interior addresses: `SubRow::parcel_spawn_position.y`, advancing by
the complete `0xf4` row stride; `cRSubLoc::lane_and_flags`, advancing by
the complete `0x54` cell stride; and `cRSubLoc::fringe_front`, likewise
advancing by `0x54`. `cRSubGame::runtime_rows` and `runtime_cells` remain
the sole owners. The analysis-only `SubRowParcelSpawnYStrideCursor`,
`TrackRowCellLaneAndFlagsStrideCursor`, and
`TrackRowCellFringeFrontStrideCursor` views are exactly those owner-record
widths; their tails only model induction into the next record and own neither
records nor fringe pointers.

Binary Ninja pins the five physical lifetimes at
`StackVariableSourceType(569, -40)` and
`RegisterVariableSourceType(573, 73)`, `(633, 72)`, `(689, 66)`, and
`(698, 72)`. Its refreshed HLIL exposes the positive row fields, the
`lane_and_flags` word, all four fringe links, and unit cursor advances. The
HLIL printer still spells two backward byte offsets with C-like pointer
subtraction; MLIL confirms the actual arithmetic remains byte-exact at `-4`
and `-0x18`, followed by `+0x54` cell and `+0xf4` row advances. These are
display quirks, not scaled typed-pointer operations.

IDA independently pins the same locals at `0x4360ea`, `0x4360ee`,
`0x43612a`, `0x436162`, and `0x43616b`. Hex-Rays renders the backward accesses
through the preceding view tail, the positive fields by name, and the advances
as `++lane_and_flags_cursor`, `next_row_fringe_front_cursor++`, and
`++parcel_spawn_y_cursor`. The canonical BN replay and focused replay verify
all widths and identities, with the focused lane entirely already current;
the second IDA replay likewise reports all five locals unchanged with no parse
errors or failures. BN and IDA therefore agree, so no Ghidra tie-break was
needed.

Matcher source and operands remain untouched. Focused matching stays at the
honest 29.67%, 1,229/1,245-instruction frontier with 66 clean operands and the
same jump-table and call-alignment mismatches. This slice recovers durable
borrowed-cursor ownership only; it adds no branch shaping, dummy dependency,
register coercion, or masked-operand fakematch.

## 2026-07-25 runtime segment-selection owner chain

The row builder now exposes the complete segment-selection ownership chain.
`SubTracks` remains the sole owner of its embedded `SubSegment` records.
`selected_segment` borrows the chosen first, last, random, or sequential
record; the active-segment stack slot carries that same borrowed pointer; and
`source_segment` may replace it with the last segment or the mode-3 scratch
segment before authored rows are copied into the runtime slab. Each resulting
runtime row retains the final borrowed provenance pointer in
`row.source_segment`.

Binary Ninja pins the eight physical identities at user-variable indices 759,
810, 814, 822, 971, 1012, 1052, and 1147: the visited-segment index, runtime
row index, build-runtime owner, selected segment, random and sequential
segment indices, selected row count, and final source segment. IDA independently
pins the corresponding six recoverable Hex-Rays locals at `0x4361a8`,
`0x4361db`, `0x4361df`, `0x4361e7`, `0x4362cd`, and `0x43632c`. Its two
compiler-copy indices remain unnamed because neither alone owns the sequential
selection lifetime.

Both focused replay lanes are idempotent, and the paired export agrees with
zero mismatches while all 1,039 strict cross-decompiler health checks pass.
Binary Ninja and IDA agree, so no Ghidra tie-break was needed. Matcher source
and operands remain untouched at the honest 29.67%, 1,229/1,245-instruction
frontier with 66 clean operands and the same two documented mismatches. No
score-shaped source, register coercion, dummy dependency, masked operand, or
other fakematch was added.

## 2026-07-25 runtime attachment-path borrows

The `P`/`p` glyph arm now exposes the complete attachment borrow chain.
`cRSubGame::path_pairs` owns 63 `PathPair` records. The mirror branch
selects one complete `Path`, either `primary` or `secondary`, and the current
`cRSubLoc` retains that borrowed path in `attachment_template_record`.
The selected path's `row_span_count` then stamps borrowed links to that same
cell across consecutive `SubRow` records. The pair, selected path, cell, and
rows all keep their existing owners.

Binary Ninja pins `selected_attachment_path` at
`RegisterVariableSourceType(3686, 67)` and `attachment_span_index` at
`RegisterVariableSourceType(3844, 68)`. Its transient EDI cell alias was
explicitly rejected: persisting it adds no visible owner and weakens unrelated
`set_bod_object` arguments to `BodVtable**`, so the replay removes that user
variable and leaves the already typed alias automatic. IDA independently pins
`runtime_cell`, `selected_attachment_path`, and `attachment_span_index` at
`0x4366c5`, `0x436d17`, and `0x436db5`. Hex-Rays now selects
`&path_pairs[index].primary` or `.secondary` directly instead of widening the
secondary branch to a containing `PathPair*`.

Both decompilers therefore agree on the selected record and the span-stamped
cell links; no Ghidra tie-break was needed. Matcher source and operands remain
untouched at the honest 29.67%, 1,229/1,245-instruction frontier with 66 clean
operands and the same two documented mismatches. No score-shaped source,
register coercion, dummy dependency, masked operand, or other fakematch was
added.

## 2026-07-27 mobile-authored glyph producer chain

Android `cRSubGame::BuildLevel()` at `0x0007e88c`, iOS
`cRSubGame::BuildLevel()` at `0x00021090`, and Windows at `0x00435eb0` agree
that the two indices into the selected segment glyph slab have different
owners: the first is the possibly mirrored authored lane, while the second is
the row within the selected `SubSegment`. The scratch incorrectly used the
runtime lane for both dimensions. It now reads
`glyph_rows[authored_lane][segment_row]`.

The same three builds agree on the byte producer chain. The raw byte remains
borrowed through `glyph_ptr`; `LevelConvert` /
`normalize_segment_glyph_for_track_flags` produces the switch value; the
`P`/`p` arm tests that normalized value; and only the diagnostic path reads
the raw byte again for a second conversion. Expressing those lifetimes
directly raises focused matching from 29.67% (1,229/1,245 instructions, 77
clean operands, 117 unaudited) to 31.70% (1,228/1,245, 78 clean, 115
unaudited), with the one existing jump-table mismatch retained.

The mobile bodies also prove that `SwitchMirror()` belongs to the common
new-segment join, not to every generated row or only the sequential picker.
The first authored nested-loop, per-row-test, and flattened common-join probes
reached 26.58%, 27.38%, and 27.42% respectively because they disturbed the
then-unresolved VC6 lifetime schedule, so none was retained at that point.

## 2026-07-28 cross-port segment transition and Windows fringe-slot lifetime

Android and iOS settle the authored control flow: selecting the first, last,
random, or sequential segment all reaches the same `SwitchMirror()` call
before row construction. Windows remains authoritative for ABI and layout.
Its `BuildLevel` computes the address of the current cell's four borrowed
fringe links at `0x00436695`, stores that `Fringe**` in stack slot `+0x40` at
`0x0043669b`, clears the four links, carries the pointer across the glyph
switch, and reloads it at `0x00437100` for the four-object position-copy loop.
Expressing `subobject_slot` once at cell initialization and retaining it
through that consumer restores the target's exact `sub esp, 0x44` frame and
raises focused matching from 31.70% to 32.40%.

With that real Windows lifetime recovered, retaining the mobile-authored
common `SwitchMirror()` join produces 32.32% (1,230/1,245 instructions,
2-instruction prefix, 78 clean operands, 115 unaudited, and only the existing
jump-table mismatch). A fresh authored nested-loop probe reached 31.23%, so it
was rejected rather than score-shaped. The source now records both the real
borrowed fringe ownership and the cross-port transition semantics without a
compiler barrier, dummy dependency, register coercion, or other fakematch.

## 2026-07-29 runtime clear owner-offset views

The Windows clear loop carries two interior-field cursors: EDI points at
`SubRow::parcel_spawn_position.y` (`SubRow + 0x94`), while ESI points at
`cRSubLoc::lane_and_flags` (`cRSubLoc + 0x40`). The stores at `0x436102`,
`0x436133`, and `0x43614d` therefore reach the owning row `flags`, cell
`open_edge_mask`, and inherited `bod.list_flags` fields. Binary Ninja's
offset-pointer views now encode those two physical bases directly. IDA keeps
the equivalent field-first stride cursors because its parser does not support
the Binary Ninja pointer-offset annotations.

The runtime-grid replay now verifies the pointer offsets and exact inherited
base metadata before touching user variables. The refreshed Binary Ninja
artifact names all three owner fields and forbids the former raw
`__offset(...)` expressions. The independent fringe cursor remains
field-first so its four borrowed pointer clears stay explicit rather than
collapsing into an analysis-generated `memset`.

This is an analysis-fidelity improvement, not a matcher-source change. Focused
matching remains at 32.32% (1,230/1,245 instructions, two-instruction prefix,
78 clean operands, 115 unaudited, and the existing jump-table mismatch).
Guarded replay is idempotent, and the strict paired export reports zero
Binary Ninja or IDA mismatches with all 1,149 decompile-health checks passing.

## 2026-07-30 native glyph dispatch order

The target jump table and its physical case blocks settle the authored switch
order as:

`' '`, `'R'`, `'#'`, `'@'`, `'G'`, `'_'`, `'$'`, `'o'`, `'M'`, `'F'`,
`'.'`, `'s'`, `'&'`, `','`, `'+'`, `'J'`, `'-'`, `'='`/`'|'`, `'('`,
`'>'`, `'}'`, `'{'`, `'<'`, `'['`, `'P'`/`'p'`, `'0'`, `'1'` through
`'9'`, and `default`.

Reordering the source cases to that native block order raises focused matching
from 32.43% to 40.84%. The candidate retains the real switch and its one known
table-layout mismatch; the table was not padded, reordered with dummy code, or
masked as proof.

The surrounding segment selection now leaves `SwitchMirror()`, the selected
segment's runtime `row_base`, and its negative-length check on the common
new-segment tail. Redundant entry initializers for `segment_row` and
`active_segment` are gone. Removing the unconditional `segment_cursor`
initializer was independently retested at the later register frontier and
regressed weighted matching by 11.20 bytes, so it remains in source.

## 2026-07-30 attachment and post-switch owners

The `P`/`p` cases now install the borrowed template directly in
`runtime_cell->attachment_template_record`; every later object and span
consumer reloads that cell-owned field. This raises matching from 40.84% to
41.81%. The target's physical branch order tests an already-primary row first
and installs the secondary link on that path, raising the result again to
41.97%.

A typed `Vector3* cell_position` now owns the complete post-switch position
lifetime rather than only the initial zero stores. That measured owner raises
the result to 42.36% and remains visible through anchor placement, ramp
adjustment, trampoline placement, and the borrowed fringe-object copies. A
zero-store-only position alias was byte-neutral and was not retained as a
partial explanation.

## 2026-07-30 authored-row lifetime recovery

The first mirrored/no-fall/jetpack-off flag stores form their row addresses
directly; the reusable `row_record` owner begins only after those stores. That
native lifetime raises focused matching from 42.36% to 43.18%, extends the
exact prefix from 2 to 9 instructions, fixes the receiver register for the
whole function, and leaves only the known glyph jump-table mismatch.

The row model position, row model velocity, and parcel projection are three
whole `Vector3` copies in the authored source. Keeping all three independently
improving assignments raises the result to 44.07%. The selected authored row
is then retained as the indexed `AuthoredSegmentRow` owner while each flag
test reloads its leading word, matching the target's repeated loads and
raising the result to 44.96%.

## 2026-07-30 runtime clear flag update

The runtime-cell clear pass updates byte 1 of `lane_and_flags` directly:
`((unsigned char*)cell_flags)[1] &= 0x5f`. Removing the temporary whole-word
round trip cuts 15 candidate instructions and raises focused matching to the
then-current 45.47% frontier: 1240/1245 instructions, a 9-instruction exact prefix,
108 clean references, 0 unresolved, 1 mismatch, and 60 unaudited. The sole
audited mismatch remains
`populate_runtime_track_cells_glyph_jump_table@0x437194` versus the candidate
local switch table.

A fresh inner-lane countdown `do` loop compiles byte-for-byte identically to
the retained `for` loop. Earlier whole-clear countdown spelling was likewise
neutral, while cursor-first payload advancement regressed. Those variants are
recorded in `experiments.jsonl`; no loop-shape coercion, volatile dependency,
register forcing, or jump-table fakematch was retained.

## 2026-07-30 segment-scoped row builder

Windows, Android, and iOS all select one first, last, random, or sequential
segment and then consume its authored rows in an inner loop. The Windows
control flow at `0x4361ca..0x437183` resets `segment_row`, advances both
`segment_row` and `build_row` at the row tail, and returns to segment selection
only when the selected segment is exhausted. The mobile `BuildLevel` bodies
preserve the same two-loop ownership.

Replacing the flattened per-runtime-row selection test with that
segment-scoped builder raises focused matching from 45.47% to 52.19%
(`1240/1245 -> 1238/1245`). `SwitchMirror()`, `row_base`, and the
negative-length check now execute on the common selected-segment tail, while
the inner loop owns authored-row consumption and runtime-row advancement.

The native mode-1 `'0'` glyph path keeps the x87 expression
`lane - 4.0f + 0.5f`; folding it to `lane - 3.5f` removes one instruction and
loses two clean constant references. Retaining the authored expression moves
the final frontier to 52.25% (`0.5225442834`), 1239/1245 instructions,
2 prefix instructions, and 111 clean / 0 unresolved / 1 mismatch /
55 unaudited operands.

An explicit second `selected_segment` local regressed to 50.78% and enlarged
the frame from `0x44` to `0x48`; the decompiler's selected/active distinction
does not require a second source variable at this optimization frontier. An
outer `do` loop reached 51.89%, and a separately prechecked inner `do` loop
reached 51.91%. Split inner guards, declaration order, and loop-local
`build_row` scope were byte-neutral. None of those variants was retained as a
score-shaped dependency.

The sole audited mismatch remains the real
`populate_runtime_track_cells_glyph_jump_table@0x437194` layout versus the
compiler-generated local switch table. It is not masked or replaced with a
hand-authored table.

## 2026-07-30 runtime clear word owner

The Windows lane clear at `0x43612c..0x436131` loads the complete
`lane_and_flags` word, clears byte 1 through `and ch, 0x5f`, and stores the
complete word. Retaining that real value owner as
`lane_and_flags &= 0xffff5fff` raises focused matching from 52.25% to 55.64%
(`2805/5042` weighted bytes), restores the 9-instruction exact prefix, and
keeps the candidate at 1239/1245 instructions. The masked audit remains
111 clean / 0 unresolved / 1 mismatch / 55 unaudited; the only mismatch is
still the physical glyph jump-table layout.

This source shape also restores the target's EBX receiver and initial EBP zero
carrier across the function. Byte-addressed signed and unsigned temporary
variants reached only 54.82% and added audit/count debt, so the exact
whole-word mask is the retained explanation.

The improved allocator frontier was followed by bounded replays rather than
register coercion:

- lane countdown, mode-3 countdown, segment-row-count cursor, main-builder
  lifetime/order, receiver-alias, runtime-row owner, and representative glyph
  owner variants were byte-neutral;
- a fully target-shaped countdown clear reached 55.53%, so its outer and
  payload loop changes were rejected;
- widening the setup-owner scopes or removing the unconditional segment
  cursor initializer reached at most 55.34%;
- a separately scoped `selected_segment` enlarged the frame from `0x44` to
  `0x48` and regressed to 50.84%.

The remaining first mismatch is the saved receiver at stack slot `-0x3c`
instead of native `-0x38`; native uses the adjacent slot for
`active_segment`. Declaration-order, typed-owner, alias-elision, and honest
scope-interaction probes did not move those slots without a broader
regression, so no dummy local, padding, volatile dependency, or forced
register was retained.

## 2026-07-30 segment accumulators and shared random tail

The mode-3 accumulator now retains borrowed `SubSegment` owners for the first,
last, and repeated segment records. The repeated-segment owner prevents VC6
from hoisting the row count and recovers the native load/add/store countdown;
the last-segment owner recovers both native completion-row stores, and the
first-segment owner restores the native initial register order. These changes
move the focused frontier from 55.64% to 57.62%. The one remaining instruction
in that block is an honest compiler-value-forwarding residual:
`mov ecx, edx` instead of reloading the first-segment row count.

The ordinary authored-segment sum now keeps first/last segment borrows, a
borrowed `segment_count` field, and a guarded `row_count` cursor. The
`segment_count` owner prevents the loop from collapsing into a cached
countdown, while the positive guard delays cursor formation until after the
empty check. The resulting initial sum and complete cursor/index loop match
the native instruction sequence; focused matching reaches 59.45%.

Random segment selection now branches only around the two direct RNG
expressions and merges through a shared float result. This reproduces the
native branch-specific `"Segdif"`/`"Segtra"` pushes and the single shared
`_ftol`, rate scale, second `_ftol`, and segment-address tail. It removes 21
candidate instructions, preserves all 111 aligned references, and reduces
unaudited references from 56 to 53. Binary Ninja also proves that
`first_or_last_row` is initialized once and set for first/last selections but
is not cleared in the general-segment branch; removing that disproven reset
sets the current frontier to 60.19%, 1237/1245 instructions, with a
9-instruction prefix and 111 clean / 0 unresolved / 1 mismatch /
53 unaudited operands.

Recorded bounded sweeps close the local alternatives: initial-sum operand and
accumulator spellings, mode-3 loop forms, cursor-initializer removal,
function-scope setup owners, runtime-clear counter and complete-cell owners,
main-builder declaration/order/receiver aliases, random-enabled byte owners,
and shared tag variables were neutral or regressive. The shared-tag form
correctly shortened the duplicated path but spilled the tag/range and lost
reference alignment; the retained shared-result form explains the native
tail without that debt. The sole audited mismatch remains the physical glyph
jump table at `0x437194` versus VC6's candidate-local switch table.

## 2026-07-31 intrinsic fringe reset

The four consecutive fringe handles at each runtime cell are one 16-byte reset
operation. Expressing that operation as intrinsic `memset` raises focused
matching from **60.19%** to **62.59%** (`3034.95 -> 3155.57` weighted bytes)
and moves the candidate from 1237 to 1238 instructions against native's 1245.
The 9-instruction exact prefix and audit remain 111 clean / 0 unresolved /
1 mismatch / 53 unaudited.

VC6 inlines the reset into the native payload loop exactly: `EAX` advances by
`0x54`, `ESI` owns the current payload, `EDX` is the fresh zero value, and
`ECX` counts eight lanes. It also recovers native's preceding row-clear
transition from the `EAX` zero owner to the `EBP` lane countdown. The same
intrinsic 16-byte fringe reset is independently retained in the exact
`initialize_subgame` scratch, so this is shared field-level behavior rather
than a register-shaped shim.

Declaration through `<string.h>`, an explicit `memset` prototype, and
`#pragma intrinsic(memset)` all emit the same winning bytes; the scratch keeps
the explicit intrinsic form already used by the exact sibling. Index and
countdown payload loops are likewise byte-identical. Cursor-first advancement
reaches only 61.70%. Explicit row/payload zero locals, lane countdown
spellings, complete-cell/list owners, and semantically equivalent tile/list
operation schedules are neutral or regressive, so none is retained.

## 2026-07-31 post-reset owner interaction bound

The first post-intrinsic mismatch remains the saved receiver at candidate
stack slot `-0x3c` instead of native `-0x38`. A dependency-complete replay
tested the real values whose lifetimes could honestly exchange the adjacent
setup slots:

- complete function-entry `row_event_owner` and `active_segment` lifetimes
  are byte-neutral;
- retaining the early runtime base and consuming it at the main loop is
  byte-neutral;
- all three declaration orders for `segment_row`, `active_segment`, and
  `base` are byte-neutral;
- moving the complete segment cursor lifetime to function entry loses
  49.99 weighted bytes;
- the valid combined native-setup lifetime arrangements lose 112.49 weighted
  bytes;
- four representative glyph-cell owner forms are neutral or lose 8.12
  weighted bytes.

The target's five consecutive ring-flag transfers visibly reuse a full-width
mask for both the authored-row test and runtime-row publication. Replaying
that ownership as one reassigned local, five branch-local values, and
dependency-complete value- and pointer-parameter `__forceinline` helpers is
byte-neutral in every valid case. VC6 folds all of those source forms back to
the retained direct expressions, so the register pattern does not distinguish
a recoverable source owner at this frontier.

The focused baseline therefore remains **62.59%** (`3155.57/5042` weighted
bytes), 1238/1245 instructions, a 9-instruction exact prefix, and 111 clean /
0 unresolved / 1 mismatch / 53 unaudited references. No dummy stack owner,
padding, volatile dependency, asymmetric flag rewrite, or register coercion
was retained.

## 2026-07-31 direct runtime-row ownership

Native keeps the scaled runtime-row offset in `EBX` and applies each
`SubRow` field displacement at the use site. The former scratch instead
materialized one absolute `row_record` pointer, which collapsed those field
references into small offsets and displaced the complete row-publication
block.

Using `runtime_rows[build_row]` directly for the complete row lifetime raises
focused matching from **62.59%** to **69.46%**
(`3155.57 -> 3502.01/5042` weighted bytes). The candidate now has 1240
instructions against native's 1245, retains the 9-instruction exact prefix,
and improves the operand audit from 111 clean / 0 unresolved / 1 mismatch /
53 unaudited to **162 clean / 0 unresolved / 1 mismatch / 4 unaudited**.
The five ring-flag transfers now reproduce native's full-width mask sequence
without any source-level mask owner.

The retained source uses typed aggregate copies for model position, model
velocity, and parcel position, and typed float copies for `ring_speed` and
`installed_heading_delta`; each is byte-identical to the corresponding
bit-preserving raw expression. A macro expansion was used only to test the
whole ownership hypothesis and is not retained.

Bounded alternatives close the local score temptations:

- recomputing the parcel-set source through `active_segment[segment_row]`
  clears all four unaudited references but regresses to 66.21% and collapses
  the exact prefix from 9 to 2 instructions;
- splitting the parcel vector into three component copies gains 14 weighted
  bytes but loses one clean reference, adds three unaudited references, and
  moves the instruction count farther from native;
- component model-velocity copies lose 7 weighted bytes, while component
  model-position copies lose 267 and collapse the prefix to 2.

The sole audited mismatch remains the real physical glyph jump table at
`0x437194`; no pointer macro, component-copy tradeoff, manual jump table, or
allocator coercion is retained.

## 2026-07-31 segment extension control flow

The native row loop separates two operations that the former scratch nested:

1. at or beyond `completion_row_start`, modes 0, 1, 3, 4, and 7 select the
   last segment while other non-mode-2 paths select scratch slot 1;
2. on every non-mode-2 row, the selected segment's projected end is checked
   against `completion_row_start`, excluding scratch slots 1, 3, and 4 and
   the last segment before extending both runtime bounds.

Binary Ninja confirms that split at `0x436306..0x4363c0`. In particular, mode
3 first passes through the scratch fallback and is then overwritten with the
last segment; the former `else if (level_mode == 3)` retained scratch slot 1
and incorrectly kept the extension test inside the completion-range branch.

Restoring the two checks raises focused matching from **69.46%** to
**70.99%** (`3502.01 -> 3579.50/5042` weighted bytes) and extends the exact
prefix from **9 to 76 instructions**. The candidate has 1251 instructions
against native's 1245; the audit remains 162 clean / 0 unresolved /
1 mismatch / 4 unaudited.

The selected segment's `segment_row` lifetime is now scoped to that segment;
moving the declaration from the function setup is byte-neutral. Equivalent
condition spellings do not improve the result:

- one `if/else` loses 49 weighted bytes and collapses the prefix to 9;
- scratch-default and last-default override forms each lose 59 weighted
  bytes and likewise collapse the prefix;
- a typed conditional owner loses 75 weighted bytes;
- caching `level_mode` loses 8 weighted bytes;
- removing the unconditional segment-cursor initializer extends the prefix
  by one instruction but loses 128 weighted bytes overall.

No duplicated side effect, dummy owner, or forced branch was introduced; the
retained two source checks are the behavior proven by the native control
flow.

## 2026-07-31 ring, lane, and glyph list ownership

Binary Ninja exposes the native ring-speed publication at
`0x436624..0x436648` as a bit-preserving GPR copy whose source value remains
live across initialization of the per-row attachment latch and lane counter.
Keeping that integer value owner and delaying its destination store until
after both initializers raises focused matching from **72.28%** to **72.68%**
(`3644.48 -> 3664.70/5042` weighted bytes). Equivalent destination-pointer
and union spellings produce the same or older bytes; six additional split,
union-member, and float-owner forms are neutral or lose 20-74 weighted bytes.
The remaining source-load/address order is therefore a bounded scheduling
residual, not a reason to coerce a register.

The runtime cell lane index is published through the complete
`lane_and_flags` word. Replacing the former address-taken low-byte temporary
with the equivalent full-word `0xffffffe0` mask removes four candidate
instructions and raises matching by another 38.15 weighted bytes. Signed,
unsigned, XOR, and OR spellings are byte-identical. Union, reference, pointer,
and reconstructed-low-byte attempts to force the target's `and al, 0xe0`
sequence all regress by 83-93 weighted bytes and are not retained.

The switch cases share one pointer to the current cell's list-flags word.
Declaring that owner before dispatch is byte-neutral; consuming it prevents
VC6 from hoisting each list-flags load ahead of the preceding tile-id store.
The empty case proves the interaction locally (+4 weighted bytes), the next
three non-object cases add 16, and the object, ramp, attachment, trampoline,
and digit cases repeat the same native ordering. Applying the owner to the
complete dispatch raises the frontier from **72.68%** to **75.33%**
(`3664.70 -> 3798.19/5042`) without changing the 1248/1245 instruction shape,
76-instruction prefix, or 162 clean / 0 unresolved / 1 mismatch / 4 unaudited
operand audit.

The remaining mismatch is still the physical glyph jump table. The four
unaudited references straddle the row-model/parcel block. Native-looking
alternatives were replayed together rather than judged in isolation:
removing the early segment-cursor initializer, a guarded `do` row loop, and
the directly indexed parcel-set source all regress when combined. The guarded
loop alone gains 11 weighted bytes and clears the four unaudited references,
but collapses the exact prefix from 76 to 9 and moves the instruction count
farther from native, so it is recorded as a tradeoff rather than retained.

## 2026-07-31 attachment and post-switch ownership

Binary Ninja's attachment dispatch at `0x436d99..0x436de7` tests the mirror
flag as the positive branch and selects the secondary path there. Reversing
the equivalent source branch to the native layout gains 16 weighted bytes.
The ramp cases also share the two render-argument field owners across the
switch; consuming those owners in every ramp arm gains another 8 weighted
bytes without changing behavior or reference quality.

After dispatch, native retains separate source- and destination-position
owners while copying the current cell position to each non-null fringe.
Expressing those two real owners explicitly gains 11 weighted bytes. An
aggregate assignment loses 25 weighted bytes and adds five instructions,
while post-increment and cursor variants lose 2; those alternatives are
recorded but not retained.

The trampoline tail exposed one semantic error in the former scratch.
Native's `0x4370d5..0x4370fa` control flow always restores
`cell_position->z = row_anchor_z` for trampoline tiles. Only the
`cell_position->y = -3.0f` write is conditional on mode 3 and runtime flag
`0x400`. Moving the Z write outside that nested condition gains another
4 weighted bytes and restores the observed behavior.

Together these changes raise focused matching from **75.33%** to **76.10%**
and move the candidate from 1248 to 1249 instructions against native's 1245.
The 76-instruction exact prefix and 162 clean / 0 unresolved / 1 mismatch /
4 unaudited operand audit remain intact. The sole audited mismatch is still
the physical glyph jump table.

The surrounding ownership space is bounded by recorded dependency-complete
mutations: parcel-source owner lifetimes lose 298 weighted bytes; raw
attachment-template slot lifetimes lose 61-77; stamped-row scoping loses
576-599; stamped-flags and lane-UV value owners are neutral or regressive;
post-switch zero owners are neutral or lose 92; and trampoline `else-if`
spellings are neutral or gain only while degrading the reference audit.
None is retained.

## 2026-07-31 post-ownership loop initialization

The latest row, glyph-list, attachment, and trampoline owners changed the
enclosing allocation enough to justify replaying the setup and segment-loop
frontiers against the current source.

Windows' mode-3 accumulator at `0x435fd9..0x435ff2` is a post-tested
16-iteration countdown. It computes the next row total in a register, publishes
that total, and only then decrements the counter. Retaining the corresponding
`rows_remaining` and `next_runtime_row_count` owners adds **4.04 weighted
bytes** without changing instruction count, exact prefix, or reference
quality. A preincrement index loop compiles to the same bytes, but the retained
countdown follows the native control and value flow.

The outer builder likewise initializes `build_row` at `0x4361ca` before the
`runtime_row_count <= 0` exit at `0x4361d4`. Moving that real initialization
before the guard and expressing the post-selection traversal as a `while`
loop adds another **4.04 weighted bytes**. The resulting retained frontier is:

```text
match: 76.26%
target: 1245 insns, candidate: 1249 insns
prefix: 76/1245 target insns
masked operands: 162 ok, 0 unresolved, 1 mismatch, 4 unaudited
```

The one mismatch remains the physical glyph jump table, and the four
unaudited references remain the displaced row-model/parcel transfers.

Current-state dependency checks bound the adjacent apparent owners. Of the 31
selected-segment declaration/publication combinations, 8 complete forms are
byte-identical, 8 complete forms lose four weighted bytes, and the 15 forms
that use the owner without declaring it are intentionally invalid. No complete
form improves the retained baseline. Eight receiver/loop forms show that a
named `build_runtime_owner` does not recover the target's long-lived `EBX`;
only the independently proved early `build_row` initialization contributes.

Four pointer, reference, and `SubTracks` aliases for `random_enabled` add four
more weighted bytes by preventing VC6 from hoisting its load above the
`base_subgame_rate` store. They are rejected as score-only aliases: both
mobile `BuildLevel` bodies preserve the direct member read after that store,
and Windows exposes no distinct borrowed owner. The ledger now contains 134
records, 128 mutation sweeps, and 531 unique variants; no alias, dummy
dependency, or register-shaped lifetime is retained.

## 2026-07-31 runtime clear field ownership

The native lane clear at `0x43612c..0x436156` publishes three distinct field
owners in source order: the complete lane word, the tile byte, and the
list-flags word. Naming those actual destinations prevents VC6 from hoisting
the list-flags load and delaying the tile-byte store across the two lane-word
updates. All three complete pointer forms compile identically and recover the
native clear schedule; a typed `cRSubLoc` spelling is rejected because the
current class definition does not expose the byte field with the required
type.

The retained split-owner form raises focused matching from **76.26%** to
**76.58%** (`3845.18 -> 3861.36/5042` weighted bytes, +16.17) without changing
the 1249/1245 instruction shape, 76-instruction exact prefix, or 162 clean /
0 unresolved / 1 mismatch / 4 unaudited operand audit. The sole mismatch
remains the physical glyph jump table.

The improved allocation also reopens the early setup dependency cleanly.
Removing the eager segment-cursor initialization alone loses 233 weighted
bytes. Pairing that native-looking lifetime with pointer or reference
publication of `first_block_row_count` extends the exact prefix from 76 to
101 instructions, but still loses 35 weighted bytes overall; retaining the
field owner without the lifetime change loses 198. All nine complete
single- and two-site combinations were recorded, so the extra setup spill is
still a bounded allocation residual rather than a reason to keep an alias.

The ledger now contains 136 records, 130 mutation sweeps, 6 probes, 584
evaluated variants, and 544 unique variants.

## 2026-07-31 post-clear row-transfer ownership bound

The four unaudited relocations remain concentrated in the native model and
parcel transfer at `0x4364b5..0x436581`. That block visibly forms the authored
velocity source before the runtime-row destination, and recomputes the parcel
set through the selected segment plus its logical row index. Both dependencies
were replayed after the clear-field owner changed the whole-function
allocation.

Pointer and reference owners for the model-velocity source are all
byte-identical, alone and beside the parcel source. Recomputing the parcel set
does clear all four unaudited relocations and adds two clean references, but it
loses 306 weighted bytes, collapses the exact prefix from 76 to 2
instructions, and falls to **70.52%**. The proof-quality improvement is not
retained at that whole-function cost.

The target also loads `g_game` between the authored object-id load and cached
mesh-slot index formation. Four real singleton owners—the game root, DirectX
loader, slot bank, and selected object—compile byte-identically to the direct
member expression. That instruction order is therefore allocator-derived, not
evidence for a distinct source owner.

At this historical snapshot the ledger contained 138 records, 132 mutation
sweeps, 6 probes, 595 evaluated variants, and 555 unique variants. The tested
owner forms did not improve the **76.58%**, 1249/1245 frontier, whose audit had
162 clean references, one physical jump-table mismatch, and four unaudited
references. That result records those specific forms; the later producer-backed
pass below resolves the jump-table mismatch.

## 2026-08-09 producer-backed trampoline cadence

The remaining physical jump-table mismatch was traced to the `'('` producer,
not to case order. Android `BuildLevel` dispatches the result of `LevelConvert`
and labels ASCII `0x28` as the trampoline arm. Its case caches the old list
flags, increments the cadence counter, resets at 15, executes the object/color
path only on the non-15 count of 8, and repeats the render-bit clear on the
other non-15 path. Windows exposes the same shape at
`0x436a13..0x436ab3`: the equal-15 path writes tile `0x16` and exits, while the
non-15 fallback performs the second low-byte clear before writing tile `0x16`.

At the cadence acceptance receipt, the retained source expressed that producer control directly as
`if (counter == 15) ... else if (counter == 8) ... else ...`. This expands the
candidate by five instructions and lowers the whole-function fuzzy score from
**76.58%** to **75.79%** (`3861.36 -> 3821.35/5042` weighted bytes), while
preserving the 76-instruction exact prefix. The reference result improves from
162 clean / 1 mismatch / 4 unaudited to **163 clean / 0 mismatch / 4
unaudited**. In dependency-chain terms, correcting the producer arm restores
the missing branch extent consumed by the glyph jump table, so all 28 table
destinations can be paired; the four independent row-model/parcel references
remain unchanged.

The exact probe receipt is recorded as `trampoline-mobile-cadence-shape`
(source SHA-256 `bf686f00753c5f454011d121aa64f0187af85ba8736a201062b75cc6b664cece`).
The later 2026-08-09 primary `cRSubRow` / `cRRowModel` owner replay compiles
that unchanged scratch SHA at **75.79%**, **1254/1245** instructions, with the
same 76-instruction prefix and 163 clean / 0 mismatch / 4 unaudited references.
This restores the cadence receipt's instruction count after a transient
one-instruction type-vocabulary drift; the producer-backed audit correction and
append-only historical probe receipt remain unchanged.
Explicit cached-flag and duplicated early-tile spellings were discarded: they
either lost the native full-word `EBP` mask flow or collapsed the exact prefix.
The ledger now contains 139 records: 132 mutation sweeps and 7 focused probes.

## 2026-08-09 stale mutation-plan retirement

`fringe-position-copy-owner-mutations.json` is retired. The append-only
experiment ledger already preserves the explored position-copy lane and its
best recorded variant, while the plan's anchor no longer matches the current
authored fringe source.

## 2026-09-09 post-cadence transfer and setup replay

The older row-transfer experiment predates the trampoline producer correction.
A fresh seven-case replay starts at 75.7406%, 1,253/1,245 instructions, prefix
76, and 163 clean / 0 mismatch / 4 unaudited references. The velocity-source
pointer/reference owners are byte-neutral. Recomputing the parcel set from
the selected segment and logical row now reaches 77.7555%, 1,250 instructions
and 165 clean / no audit debt, but collapses the exact prefix to 9. It is not
retained despite the score and reference improvements.

The eleven-case `post-cadence-parcel-setup-lifetimes-20260909.json` then pairs
that producer with late segment-cursor initialization and pointer/reference
publication of the first-block count. The count owners do not restore the
parcel variant's prefix; removing eager cursor initialization yields 74.6592%
and still prefix 9. Without the parcel change, the cursor variants only extend
the prefix to 77 at a substantial whole-function regression. No source change
is retained. The tracked path-context receipt preserves both complete grids
and their current baseline identities. These outcomes replace the older score
expectations for these particular forms, without closing the ownership lane.
