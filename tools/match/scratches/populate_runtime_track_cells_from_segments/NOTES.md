# Dossier — scratch not yet written (5056 bytes, the runtime grid build)

populate_runtime_track_cells_from_segments @ 0x435eb0. The function that
DEFINES the grid conventions the 2026-06-13 grid-alignment audit hinges
on. Read complete 2026-06-13; scratch deferred (the glyph switch makes
it large but mechanical).

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
   segment pick: `random_float_below(mode==1 ? rate*c3+c4 scaled count :
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

- non-entry tiles: anchor.x = (float)(mirrored lane) - 4.0 + 0.5
  (lane CENTER, [-3.5 .. 3.5]); anchor.y = 0 except ramp-tops 8/9/10
  (= 0.5), rows < 4 non-mode-2 (start platform global), tile 28
  (y -= c), tile 22 keeps y = -1.5-ish const (-1069547520 = -1.5)
  outside mode 3 unless flags & 0x400; anchor.z = row + 0.5.
- entry tiles 29/30: anchor.x = 0.0 (CENTERED — the whole row is the
  attachment), anchor.z = row + 0.5 with a second field at row + 0.0;
  skirt-color object variant under byte_4DF934 & 0x20.
- floor family checkerboard uvs: tiles {1,15..27,33,34} get
  (8-lane)*c and (row%8)*c uv scalars.
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
