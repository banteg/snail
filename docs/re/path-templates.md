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
- shipped authored content does reference `WARP` by name via [`SEGMENTS/WARP.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/WARP.TXT)
- shipped authored content also references `HALFPIPE` by name via [`SEGMENTS/HALFPIPE.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/HALFPIPE.TXT), [`SEGMENTS/HALFPIPE2.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/HALFPIPE2.TXT), and [`SEGMENTS/HALFPIPE3.TXT`](../../artifacts/extracted/SnailMail.dat/SEGMENTS/HALFPIPE3.TXT)
- path-table index `42` is still the authored name `HALFPIPE`
- the recovered **runtime kind** `42` is a different field entirely
- a focused March 12 capture now proves authored `HALFPIPE` installs live into runtime kind `42`
- `sub_429b20` still strongly matches one constructor for the nonlinear kind-`42` family, but kind `42` is no longer safely describable as `WARP`-only
- Android now proves a stronger public split in its own path registry:
  - `HALFPIPE` is public slot `57` and `LoadPaths` builds it directly with `cRPath::BuildHalfPipe`
  - `HALFPOLE` is public slot `58` and `LoadPaths` builds it directly with `cRPath::BuildHalfPole`
  - `WARP` is a separate public slot `37`, and it does not appear as the same builder family in the recovered Android `LoadPaths` body

## Installed Pair Bank Bridge

The parser and runtime installer now close most of the old bridge gap:

- `load_segment_definitions` parses `Path=...`, resolves it through `find_segment_path_index_by_name`, and stores the resulting public-table index on each parsed segment row at `+0x8bc`
- `populate_runtime_track_cells_from_segments` later reads that stored index from the parsed row and selects an installed pair as `path_index * 336 + installed_pair_bank`
- the two installed-pair bank roots used by the `P/p` branch are:
  - `game + 0xff2914`
  - `game + 0xff29bc`
- uppercase `P` becomes runtime tile `30` and lowercase `p` becomes runtime tile `29`, but the choice between those two installed-pair roots comes from a separate builder-state byte at `this + 2`
- those roots differ by exactly one `0xa8`-byte record, so one public path id resolves to a `336`-byte installed pair made of two adjacent template records

What this still does **not** prove:

- that the constructor-generation bank at the higher asset/world offsets is laid out identically to the installed runtime pair bank
- that every constructor family uses the same left/right semantic for the two halves
- the exact meaning of the `this + 2` branch in the `P/p` installer that chooses which half pointer is installed on the row

## Path Template Slot Layout

Observed facts:

- the runtime path-template bank is rooted at `arg1 + 0xff2914`
- the second half of each pair is rooted at `arg1 + 0xff29bc`, exactly `0xa8` bytes after the first
- the init pass zeroes `126` records of size `0xa8`, which is enough space for `63` potential two-record pairings

Two generic helpers now make that layout clearer:

- `initialize_path_template_record_pair`
- `mirror_path_template_pair_x`

What is still **not** proven from this package:

- that the constructor-generation bank universally treats those `126` records as `63` contiguous left/right pairs
- that the first/second record layout is the same for every constructor family

`initialize_path_template_record_pair` proves record initialization at `+0x0` and `+0x18`, and `mirror_path_template_pair_x` proves one record can be mirrored into another, but the actual call sites that establish universal pair layout are still missing.

One more shared helper is now clear from the constructor xrefs:

- `finalize_path_template` (`0x42c600`) is the common post-constructor finalizer used by most concrete path families and by `mirror_path_template_pair_x`
- it is not another family constructor; it recomputes derived per-sample lengths and final strip-mesh state after the primary/secondary sample arrays have been written

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

- `+0x24`: `strip_mesh`
  - pointer to the generated strip-mesh object used by the constructor family
- `+0x30/+0x34`: two leading header floats; these are live in the runtime record but do not yet have a stable semantic name
- `+0x38`: attachment kind or constructor family id
- `+0x3c`: mirror flag
- `+0x40`: terminal or return flag read by `update_track_attachment_follow_state`
- `+0x44`: segment count
- `+0x4c`: float copy of the effective segment count
- `+0x50`: scale or width-like constructor parameter
- `+0x54`: width-cell count used for the generated strip mesh
- `+0x58`: pointer to the primary sampled-point array
- `+0x5c`: pointer to the mirrored or secondary sampled-point array
- `+0x98`: install-time row scalar written during entry/begin
- `+0x9c`: template-side special flag checked by live update

This is the main reason the raw decompile reads so badly:

- `*(_DWORD *)(this + 88)` and `*(_DWORD *)(this + 92)` are not vtables
- they are the two sample-array pointers at `+0x58` and `+0x5c`
- expressions like `*(float *)(*(_DWORD *)(this + 88) + v8 + 144)` are just per-sample field accesses at `sample_offset + 0x90`

Still unresolved from this package:

- whether `+0xa0/+0xa4` belong to the template record at all in the special update path
- the exact semantic names for the mirror-copied header scalars at `+0x30/+0x34`

High-confidence fields on the pointed-to `strip_mesh` object:

- `+0x10`: render or allocation flags
- `+0x2c`: vertex count
- `+0x38`: vertex array
- `+0x48`: optional vertex-colour array
- `+0x54`: live facequad count
- `+0x58`: facequad capacity
- `+0x5c`: `0x30`-byte `ObjectFaceQuad` array

High-confidence facequad record shape:

- `+0x00`: face flags
- `+0x02/+0x04/+0x06/+0x08`: four vertex indices
- `+0x0c`: texture reference pointer
- `+0x10..+0x2c`: four `(u, v)` pairs

High-confidence fields on each sampled point record inside the `+0x58` / `+0x5c` arrays:

- record size: `0xa8`
- `+0x00/+0x10/+0x20`: three `0x10`-byte matrix rows, not three packed `Vec3`s
- `+0x30/+0x34/+0x38`: world position used by the follow-state update
- `+0x80/+0x84/+0x88`: delta vector toward the next sample
- `+0x8c`: delta length, which `update_track_attachment_follow_state` multiplies by the per-tick path factor
- `+0x90`: `center_x`
- `+0x94/+0x98`: family-specific rotation or carryover scalars; these are zeroed in the recovered halfpipe and kind-`42` constructors
- `+0x9c`: scalar used by the ordinary follow path
- `+0xa0`: extra scalar copied verbatim by the mirror helper and consumed by the nonlinear kind-`42` branch

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
| 30 | `WARP` | `sub_429b20`? | no longer safe as a direct public-name mapping; `sub_429b20` is now treated as one nonlinear kind-`42` constructor branch, and Android strongly suggests the same constructor shape as `cRPath::BuildHalfPipe` |
| 31 | `SUPERTRAMP` | `sub_423f10` | both halves are built explicitly |
| 32 | `SLALOMDOUBLE` | `sub_425050` | |
| 33-35 | `P0`, `P1`, `P2` | `sub_425a40` | |
| 36 | `START` | `sub_426400` | both halves are built explicitly |
| 37 | `TURNOVER` | `sub_426cb0` | |
| 38 | `TURNOVERDOUBLE` | `sub_427640` | |
| 39 | `TURNUNDER` | `sub_427fe0` | |
| 40 | `WIBBLE` | `sub_4289a0` | |
| 41 | `INVERT` | `sub_429250` | |
| 42 | `HALFPIPE` | unresolved | live capture now proves it installs as runtime kind `42` with `66` samples, but the exact constructor/install split is still missing |
| 43-44 | `TWISTERA`, `TWISTERB` | `sub_42a540` | |
| 45-46 | `TWISTER2A`, `TWISTER2B` | `sub_42af30` | |
| 47-50 | `TOAD*` | `sub_42cbf0` | `TOAD0`, `TOAD1`, `TOADPAIR0`, `TOADPAIR1` |

The March 10 Windows attachment package independently corroborated a few of these families from the live follow side:

- kind `31` has the dedicated launch-exit branch, matching `SUPERTRAMP`
- kinds `33`, `34`, and `35` are the shared `P`-family constructor variants
- kind `36` is the explicit `START` constructor family
- kind `42` still has its own nonlinear projection or follow branch in both projection and live-update code
- a March 12 path-oracle capture now proves authored `HALFPIPE` also resolves into that live kind-`42` family
- `sub_429b20` remains the strongest current constructor match for one branch of the nonlinear family, but the exact Windows public-name mapping inside that family is still open

## Practical Read

- named `Path=` rows choose hardcoded template pairs rather than archive-defined path files
- most names are family variants built from one constructor plus an X-mirror pass
- `sub_429b20` remains the strongest recovered constructor for one nonlinear kind-`42` family branch
- Android's named `cRPath::BuildHalfPipe` is a strong structural match for that constructor body
- Android's `LoadPaths` also directly maps public slot `57` to `BuildHalfPipe` and slot `58` to `BuildHalfPole`, while keeping `WARP` as a separate public slot `37`
- Android also has a neighboring `cRPath::BuildHalfPole`, and `cRPathFollowGoldy::Traverse` special-cases both `HalfPipePos` and `HalfPolePos`, so the nonlinear attachment family is at least split into those two named siblings on that port
- `HALFPIPE` is no longer a purely static gap: it is now proven live as runtime kind `42`, but it still lacks a directly recovered constructor body
- `WARP` still lacks a directly recovered live family mapping and should not be collapsed into the same public slot as `HALFPIPE`
- the template bank is constructor-generated runtime data, not a ready-made static blob in the executable, so a faithful extractor will need either constructor emulation or a runtime dump step

## Current Zig Port Scaffold

The current Zig port now mirrors the public authored family set directly:

- [`attachment_builders.zig`](../../zig/src/attachment_builders.zig) carries the full `51`-name public path registry
- every public name now builds a Zig-side template through one of the recovered builder families
- the segment viewer renders all public families from those built templates
- gameplay now also uses those built templates for live attachment progression and camera basis

What this does **not** mean:

- the Zig port does **not** yet claim the exact Windows installed bank layout
- it does **not** yet hard-code a universal `63`-pair constructor-bank rule
- it does **not** yet claim the final public-name split inside the nonlinear kind-`42` family

So the current Zig scaffold is the right public-family layer for implementation, while the exact Windows bank/install semantics remain a live RE topic.
