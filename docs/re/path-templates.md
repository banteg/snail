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

Important corrections:

- the shipped table has `51` names, not `47`
- no shipped `SEGMENTS/*.TXT` or `LEVELS/*.TXT` currently references `WARP` by name
- path-table index `42` is still the authored name `HALFPIPE`
- the recovered **runtime kind** `42` is a different field entirely, and is currently the strongest match for the missing `WARP`-family constructor

## Path Template Slot Layout

Observed facts:

- the runtime path-template bank is rooted at `arg1 + 0xff2914`
- the second half of each pair is rooted at `arg1 + 0xff29bc`, exactly `0xa8` bytes after the first
- the init pass zeroes `126` records of size `0xa8`, which is enough space for `63` potential two-record pairings

Two generic helpers now make that layout clearer:

- `initialize_path_template_record_pair`
- `mirror_path_template_pair_x`

What is still **not** proven from this package:

- that the runtime universally treats those `126` records as `63` contiguous left/right pairs
- that one authored path id always steps by `0x150`
- that the first/second record layout is the same for every constructor family

`initialize_path_template_record_pair` proves record initialization at `+0x0` and `+0x18`, and `mirror_path_template_pair_x` proves one record can be mirrored into another, but the actual call sites that establish universal pair layout are still missing.

## Dynamic Family Cross-Check

The evening March 8 capture at [`artifacts/frida/snailmail-trace-20260308-204003-8604.ndjson`](../../artifacts/frida/snailmail-trace-20260308-204003-8604.ndjson) now gives live `template_summary` records during attachment-follow.

Useful dynamic cross-checks against the static constructors:

- kind `36` -> sample count `27`, subdivision count `8`
- kind `35` -> sample count `16`, subdivision count `3`
- kind `34` -> sample count `16`, subdivision count `3`
- kind `33` -> sample count `16`, subdivision count `3`
- kind `32` -> sample count `70`, subdivision count `4`
- kind `42` -> sample count `66`, subdivision count `8`
- kind `39` -> sample count `45`, subdivision count `4`
- kind `45` -> sample count `52`, subdivision count `3`

That dynamic shape is useful because it tells us the constructor output is stable enough to model by family:

- the live runtime is not mutating the sample count or subdivision count per use-site
- the follow-state code is consuming family-shaped records, not ad hoc per-row blobs
- the remaining rewrite problem is therefore constructor semantics and sampled-point reconstruction, not discovering whether path templates are dynamically resized at runtime

## Recovered Record Shape

`mirror_path_template_pair_x` plus the recovered `SUPERTRAMP` constructor (`0x423f10`) now give a much clearer picture of one path-template record.

High-confidence fields on the `0xa8`-byte record:

- `+0x24`: nested render or mesh strip object
- `+0x30/+0x34`: two leading header floats; these are live in the runtime record but do not yet have a stable semantic name
- `+0x38`: attachment kind or constructor family id
- `+0x3c`: mirror flag
- `+0x40`: terminal or return flag read by `update_track_attachment_follow_state`
- `+0x44`: sample count
- `+0x4c`: float copy of the effective sample count
- `+0x50`: scale or width-like constructor parameter
- `+0x54`: subdivision count used for the generated strip mesh
- `+0x58`: pointer to the primary sampled point array
- `+0x5c`: pointer to the mirrored or secondary sampled point array
- `+0x98`: install-time row scalar written during entry/begin
- `+0x9c`: template-side special flag checked by live update

Still unresolved from this package:

- whether `+0xa0/+0xa4` belong to the template record at all in the special update path
- the exact semantic names for the mirror-copied header scalars at `+0x30/+0x34`

High-confidence fields on each sampled point record inside the `+0x58` / `+0x5c` arrays:

- record size: `0xa8`
- `+0x30/+0x34/+0x38`: world position used by the follow-state update
- `+0x80/+0x84/+0x88`: delta vector toward the next sample
- `+0x8c`: delta length, which `update_track_attachment_follow_state` multiplies by the per-tick path factor
- `+0x90/+0x94/+0x98`: orientation-like vector that gets mirrored on X
- `+0x9c`: scalar used by the ordinary follow path
- `+0xa0`: extra scalar copied verbatim by the mirror helper

What the mirror helper actually does:

- copies shared header fields like sample count and constructor parameters
- mirrors X-oriented values in the sampled point arrays
- copies the per-sample delta length at `+0x8c`
- mirrors the generated strip mesh vertices and swaps winding-sensitive fields in the nested mesh object

This matches the follow-state code path:

- the live follow state stores a pointer to one of these records
- `update_track_attachment_follow_state` advances `sample_index` and `progress`
- the current sample's `+0x8c` length scales the incoming path factor
- the sample's positions and delta vectors feed the interpolated output position

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
| 30 | `WARP` | unresolved | most likely the missing constructor for runtime kind `42` |
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

The March 10 Windows attachment package independently corroborated a few of these families from the live follow side:

- kind `31` has the dedicated launch-exit branch, matching `SUPERTRAMP`
- kinds `33`, `34`, and `35` are the shared `P`-family constructor variants
- kind `36` is the explicit `START` constructor family
- kind `42` still has its own nonlinear projection or follow branch in both projection and live-update code, and the newest package strengthens the read that this runtime kind is the missing `WARP`-family constructor output

## Practical Read

- named `Path=` rows choose hardcoded template pairs rather than archive-defined path files
- most names are family variants built from one constructor plus an X-mirror pass
- `WARP` remains the one public slot without a directly recovered constructor body, but runtime kind `42` is now the strongest candidate for that missing family
- the template bank is constructor-generated runtime data, not a ready-made static blob in the executable, so a faithful extractor will need either constructor emulation or a runtime dump step
