# Path Templates

`Path=<name>` in `SEGMENTS/*.TXT` does not resolve through an archive file.

Instead, `find_segment_path_index_by_name` linearly searches a hardcoded string-pointer table at `g_segment_path_name_table` (`0x4a3d6c`) and returns the matching index or `-1`.

## Hardcoded Path Table

| Index | Name |
|---:|---|
| 0 | `LOOPTHELOOP` |
| 1 | `LOOPTHELOOP2` |
| 2 | `LOOPTHELOOP4` |
| 3 | `LOOPTHELOOPT2` |
| 4 | `LOOPTHELOOPT3` |
| 5 | `LOOPTHELOOPT4` |
| 6 | `LOOPTHELOOPW` |
| 7 | `LOOPBOW` |
| 8 | `HILL` |
| 9 | `HILL4C` |
| 10 | `HILL4` |
| 11 | `VALLEY` |
| 12 | `VALLEY4C` |
| 13 | `VALLEY4` |
| 14 | `SBEND` |
| 15 | `CAGE2` |
| 16 | `HUMP` |
| 17 | `DUMP` |
| 18 | `HUMPSMALL` |
| 19 | `DUMPSMALL` |
| 20 | `DIP` |
| 21 | `SCREW` |
| 22 | `SLALOM` |
| 23 | `SLALOMBIG` |
| 24 | `WORM` |
| 25 | `LOOPOUT` |
| 26 | `LOOPOUT3` |
| 27 | `LOOPOUTBIG` |
| 28 | `SWEEP` |
| 29 | `SNAKE` |
| 30 | `WARP` |
| 31 | `SUPERTRAMP` |
| 32 | `SLALOMDOUBLE` |
| 33 | `P0` |
| 34 | `P1` |
| 35 | `P2` |
| 36 | `START` |
| 37 | `TURNOVER` |
| 38 | `TURNOVERDOUBLE` |
| 39 | `TURNUNDER` |
| 40 | `WIBBLE` |
| 41 | `INVERT` |
| 42 | `HALFPIPE` |
| 43 | `TWISTERA` |
| 44 | `TWISTERB` |
| 45 | `TWISTER2A` |
| 46 | `TWISTER2B` |
| 47 | `TOAD0` |
| 48 | `TOAD1` |
| 49 | `TOADPAIR0` |
| 50 | `TOADPAIR1` |

Important correction:

- the shipped table has `51` names, not `47`
- no shipped `SEGMENTS/*.TXT` or `LEVELS/*.TXT` currently references `WARP` by name

## Path Template Slot Layout

Observed facts:

- the runtime path-template bank is rooted at `arg1 + 0xff2914`
- the second half of each pair is rooted at `arg1 + 0xff29bc`, exactly `0xa8` bytes after the first
- the init pass zeroes `126` records of size `0xa8`, which is enough space for `63` path-template pairs
- one named path id therefore steps by `0x150`, which is `0xa8 + 0xa8`
- the first record of pair `n` lives at `base + n * 0x150`
- the second record of pair `n` lives at `base + n * 0x150 + 0xa8`

Two generic helpers now make that layout clearer:

- `initialize_path_template_record_pair`
- `mirror_path_template_pair_x`

The important practical rule is:

- most named path slots build the first `0xa8` record with a constructor family, then build the second `0xa8` record by calling `mirror_path_template_pair_x(dst = base + 0xa8, src = base)`
- `SUPERTRAMP` and `START` are the clear exceptions: both halves are built explicitly instead of through the mirror helper

## Constructor Families

| Index | Name | Constructor | Notes |
|---:|---|---|---|
| 0-5 | `LOOPTHELOOP*` | `sub_41b0f0` | `LOOPTHELOOP`, `2`, `4`, `T2`, `T3`, `T4` |
| 6 | `LOOPTHELOOPW` | `sub_41bb40` | |
| 7 | `LOOPBOW` | `sub_42ba80` | |
| 8-13 | `HILL*` / `VALLEY*` | `sub_42d570` | `HILL`, `HILL4C`, `HILL4`, `VALLEY`, `VALLEY4C`, `VALLEY4` |
| 14 | `SBEND` | `sub_42df00` | |
| 15 | `CAGE2` | `sub_42e720` | |
| 16, 18 | `HUMP`, `HUMPSMALL` | `sub_41d030` | |
| 17, 19 | `DUMP`, `DUMPSMALL` | `sub_41da30` | |
| 20 | `DIP` | `sub_41e440` | |
| 21 | `SCREW` | `sub_41eda0` | |
| 22 | `SLALOM` | `sub_41f760` | |
| 23 | `SLALOMBIG` | `sub_4221f0` | |
| 24 | `WORM` | `sub_420170` | |
| 25-27 | `LOOPOUT*` | `sub_41c5f0` | `LOOPOUT`, `LOOPOUT3`, `LOOPOUTBIG` |
| 28 | `SWEEP` | `sub_422c00` | |
| 29 | `SNAKE` | `sub_423580` | |
| 30 | `WARP` | unresolved | no clean aligned constructor site recovered yet |
| 31 | `SUPERTRAMP` | `sub_423f10` | both halves are built explicitly |
| 32 | `SLALOMDOUBLE` | `sub_425050` | |
| 33-35 | `P0`, `P1`, `P2` | `sub_425a40` | |
| 36 | `START` | `sub_426400` | both halves are built explicitly |
| 37 | `TURNOVER` | `sub_426cb0` | |
| 38 | `TURNOVERDOUBLE` | `sub_427640` | |
| 39 | `TURNUNDER` | `sub_427fe0` | |
| 40 | `WIBBLE` | `sub_4289a0` | |
| 41 | `INVERT` | `sub_429250` | |
| 42 | `HALFPIPE` | `sub_429b20` | |
| 43-44 | `TWISTERA`, `TWISTERB` | `sub_42a540` | |
| 45-46 | `TWISTER2A`, `TWISTER2B` | `sub_42af30` | |
| 47-50 | `TOAD*` | `sub_42cbf0` | `TOAD0`, `TOAD1`, `TOADPAIR0`, `TOADPAIR1` |

## Practical Read

- named `Path=` rows choose hardcoded template pairs rather than archive-defined path files
- most names are family variants built from one constructor plus an X-mirror pass
- `WARP` remains the one public slot without a clean recovered constructor path
