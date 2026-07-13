# populate_runtime_track_cells_from_segments

populate_runtime_track_cells_from_segments @ 0x435eb0. The function that
DEFINES the grid conventions the 2026-06-13 grid-alignment audit hinges
on.

## Scratch status

Promoted to a matcher scratch on 2026-06-13. Current result after the
runtime-grid high-score and segment-rate slices: 28.25%, 1190/1245 candidate
instructions (`tools/match/match.sh
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
anchor also puts `cell->anchor_position.z` at the row boundary (`row + 0.0`),
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
`TrackRowCell::attachment_template_record`, uses
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
`SubgameRuntime` root and the named `TrackAttachmentRuntimeRow` fields
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
`SubgameRuntime::populate_runtime_track_cells_from_segments` directly and
removes the duplicate local `Game` field window. Focused Wibo remains `28.25%`,
1190/1245 candidate instructions, prefix 0/1245, with the same `57 ok / 1
mismatch` masked audit. `uv run snail match types --paths` now reports
`partial-compatible Game: 3`, with this scratch removed from the remaining
generic owner list.

## 2026-07-10 pair-bank alias

The raw `+0xff2914/+0xff29bc + index*0x150` spelling remains in this large
scratch because the natural typed pair expression changes VC6 branch/address
formation and globally reshuffles locals. The shared `SubgameRuntime` header
now owns the exact `PathPair[63]` field; retaining the native
arithmetic here is source-shape preservation, not an unresolved owner.

## 2026-07-10 runtime slab ownership pass

- `SubgameRuntime` owns a fixed `SubLoc[3200][8]` slab at `+0x3bfac8`.
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
  `SubgameRuntime::current_high_score_record` directly; the scratch-local
  `HighScoreEntry` lookalike was not a separate owner.
- The setup reset now names `replay_update_cursor` and the embedded `Player`
  fields it actually mutates: `total_score`, `stopwatch`, `score_tail`,
  `movement_flag_selector`, and `visible_life_stock`. The score-bucket reset is
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
  `SubgameRuntime`/`Player` owners. These substitutions preserve the honest
  28.25%, 1190/1245 frontier and its 57 clean operands plus the known glyph
  table-layout mismatch.
- The mode-3 raw addresses `+0x1b4410`, `+0x1bc850`, and `+0x1c0a70` are
  `level_definition_scratch.segment_slots[1]`, `[3]`, and `[4]`. A fully typed
  active-segment pointer spelling moved the score to 28.17%, so the byte-shaped
  address formation stays visible. Recasting the authored-row copy repeated
  the previously measured 26.40% regression and was also reverted; neither
  residual is hidden with dummy source or masked proof.

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
6. Authored copy per row: segment cursor walk with the mode-1 random
   segment pick. Crossing a segment boundary clears the first/last-row latch,
   resets `base_subgame_rate` to `1.0f`, then picks
   `random_float_below(mode==1 ? rate*c3+c4 scaled count :
   (float)segment_count)` -> 16928-stride segment, marks +8 visited;
   start rows use the Start block, completion rows the Last block (and
   mode 3 the special block at +1786896). `track_mirror_enabled` (game+2)
   ORs row flag 0x20, flips authored lanes and mirrored attachment-template
   banks, and `switch_track_mirror` runs PER ROW (`track_mirror_repeat_count`
   at game+4 guards long runs; mirror state toggles on '@').
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
                        payload directly (x = lane-3.5, mirrored *-1)
  '<' 6                 '='/'|' 14 (wall2)   '>' 3, after prior-row 3:
                        9 + prior cell retagged 12
  '@' 0 + switch_track_mirror (the mirror toggle glyph)
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

## Verify targets for the port (next pass)

1. the '(' trampoline cadence (8th visible / 15th reset) vs the port's
   track build;
2. the prior-row-3 retag chain ({,>,} -> 8/9/10 with prior 11/12/13);
3. digits -> tile 15 (slide) on non-attachment rows;
4. rows < 4 start-platform anchor y;
5. the mode-1 random segment pick + visited byte (+8) semantics vs
   the port's challenge build.

## Replay record analysis ownership (2026-07-13)

The path-template analysis header formerly called the borrowed runtime pointer
target `SelectedLevelRecord` and stopped after one replay sample. That prefix is
not an independent owner: its fields align exactly with `SubSolution`, and the
21,600 six-byte `ReplayRunRecord` entries plus four tail dwords prove the full
0x1fac0-byte authored `cRSubSolution` stride.

The Binary Ninja and IDA-facing campaign now exposes the exact `SubSolution`
and types `SubgameRuntime::selected_level_record +0xff25d4` accordingly. A
Binary Ninja declaration preview verifies `ReplayRunRecord == 0x06`,
`SubSolution == 0x1fac0`, and the borrowed runtime field without mutating the
database. This is an analysis ownership correction only; focused Wibo remains
the honest 28.25%, 1190/1245-instruction baseline with 57 clean operands and
the existing glyph-table mismatch.

## Runtime storage closure (2026-07-13)

The same analysis owner now replaces the anonymous `+0x3bfac8..+0xff25d0`
range with the three independently measured embedded stores:

- `TrackRowCell runtime_cells[3200][8]` at `+0x3bfac8`, ending at `+0x5ccac8`;
- `TrackAttachmentRuntimeRow runtime_rows[3200]` at `+0x5ccac8`, ending at
  `+0x68b4c8`; and
- the working `SubSolution current_high_score_record` at `+0xfd2b10`, ending
  exactly at the replay-launch flags at `+0xff25d0`.

Binary Ninja preview keeps the enclosing `SubgameRuntime` size at 0x1272838
while exposing those owned arrays and record, then reverts. No matcher source
was reshaped, so the focused 28.25% baseline and honest glyph-table mismatch
remain unchanged.
