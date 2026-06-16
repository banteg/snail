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
primary/secondary cell pointers over `AttachmentPathTemplate::row_span_count`
rows. `AttachmentPathTemplate +0x48` is therefore a runtime row-span count,
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
`AttachmentPathTemplate::row_span_count`, and stamps
`TrackAttachmentRuntimeRow::primary_attachment_cell` /
`secondary_attachment_cell` over the template span. Focused Wibo remains
`28.25%`, `1190/1245`, with `57 ok / 1 unresolved / 0 mismatch`. This is
relationship evidence rather than a score slice: the builder produces the same
fields consumed by `begin_track_attachment_follow_state`,
`project_position_onto_track_attachment`, `place_parcels_on_track`, and the
player attachment-entry path.

2026-06-16 layout assertion pass: `AttachmentPathTemplate` now carries
explicit tail padding and asserts `sizeof(AttachmentPathTemplate) == 0x150`.
The builder's `P`/`p` path selects from both template banks with that stride,
while earlier fields through `+0xa8` remain the shared path-follow template
view consumed by attachment entry/projection/follow scratches.

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
   mode 3 the special block at +1786896). Mirror byte (game+2) ORs row
   flag 0x20 and `switch_track_mirror` runs PER ROW (mirror state
   toggles on '@').
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
