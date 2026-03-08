# Track Path RE Notes

This page captures the current static understanding of the `SEGMENTS` path system and the segment-to-track runtime pipeline inside [`SnailMail.RWG`](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail.RWG).

Primary sources used for these notes:

- the Binary Ninja database in [`SnailMail.RWG.bndb`](/Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail.RWG.bndb)
- the exported HLIL snapshot in [`SnailMail.RWG.bndb_hlil.txt`](/Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail.RWG.bndb_hlil.txt)
- the IDA decompile dump in [`SnailMail.RWG.c`](/Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail.RWG.c)
- Ghidra as a second-opinion decompiler for ambiguous functions

## Current Function Map

High-confidence renamed functions in the current Binary Ninja database:

- `find_segment_path_index_by_name` at `0x429ae0`
- `initialize_path_template_record_pair` at `0x4085c0`
- `mirror_path_template_pair_x` at `0x421dc0`
- `load_segment_definitions` at `0x448160`
- `load_level_definitions` at `0x448900`
- `load_level_definition_file` at `0x447480`
- `copy_segment_definition_to_level_slot` at `0x447300`
- `begin_track_attachment_follow_state` at `0x420c40`
- `update_track_attachment_follow_state` at `0x420cb0`
- `try_enter_track_attachment_from_swept_motion` at `0x42c770`
- `is_point_inside_track_attachment` at `0x42ca90`
- `is_neighbor_cell_solid` at `0x434b60`
- `populate_runtime_track_cells_from_segments` at `0x435eb0`
- `select_track_tile_edge_variants` at `0x435a80`
- `merge_track_tile_runs` at `0x435180`
- `normalize_segment_glyph_for_track_flags` at `0x437270`
- `rebuild_track_runtime_from_segments` at `0x437de0`
- `select_level_track_texture_set` at `0x410730`
- `populate_track_runtime_entities` at `0x438b90`
- `spawn_track_garbage_hazard` at `0x43da80`
- `update_player_track_movement_and_triggers` at `0x43b120`
- `end_track_attachment_follow_state` at `0x43af60`
- `allocate_parcels_on_track` at `0x4438e0`
- `allocate_challenge_parcels_on_track` at `0x444240`
- `project_position_onto_track_attachment` at `0x4444b0`
- `get_track_grid_cell_at_world_position` at `0x43d410`
- `get_track_cell_row_index` at `0x447040`
- `sample_track_floor_height_at_position` at `0x43d4d0`

The current track-runtime pipeline is:

1. `load_segment_definitions` parses `SEGMENTS/*.TXT` into an internal segment catalog.
2. `load_level_definitions` composes segment sequences and level rules from `LEVELS/*.TXT`.
3. `rebuild_track_runtime_from_segments` normalizes the loaded cells into a runtime track:
   - `select_track_tile_edge_variants`
   - `merge_track_tile_runs`
   - `allocate_parcels_on_track`
4. Later game code consumes the rebuilt track runtime for parcel placement and gameplay.

## Hardcoded Path Table

`Path=<name>` in `SEGMENTS/*.TXT` does not resolve through an archive file.

Instead, `find_segment_path_index_by_name` linearly searches a hardcoded string-pointer table at `g_segment_path_name_table` (`0x4a3d6c`) and returns the matching index or `-1`.

Recovered table order:

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
- the extra names were easy to miss in HLIL because a few short entries were rendered as generic pointers instead of obvious string-typed symbols
- short names like `DIP`, `P0`, `P1`, and `P2` are especially easy to miss in the exported HLIL for that reason

One useful corpus fact from the extracted archive:

- no shipped `SEGMENTS/*.TXT` or `LEVELS/*.TXT` currently references `WARP` by name

## Path Template Slot Layout

The current static read is that named `Path=` ids index into a prebuilt bank of paired sampled path-template records.

Observed facts:

- the runtime path-template bank is rooted at `arg1 + 0xff2914`
- the second half of each pair is rooted at `arg1 + 0xff29bc`, exactly `0xa8` bytes after the first
- the init pass zeroes `126` records of size `0xa8`, which is enough space for `63` path-template pairs
- one named path id therefore steps by `0x150`, which is `0xa8 + 0xa8`
- the first record of pair `n` lives at `base + n * 0x150`
- the second record of pair `n` lives at `base + n * 0x150 + 0xa8`

Two generic helpers now make that layout clearer:

- `initialize_path_template_record_pair`
  - constructs the two `0x18`-byte record halves for one paired path object and installs the shared vtable at `data_497334`
- `mirror_path_template_pair_x`
  - clones one path-template pair from source to destination
  - negates X-space sample positions and basis vectors
  - swaps copied strip winding and index order so the mirrored path still renders and samples correctly

The important practical rule is:

- most named path slots build the first `0xa8` record with a constructor family, then build the second `0xa8` record by calling `mirror_path_template_pair_x(dst = base + 0xa8, src = base)`
- `SUPERTRAMP` and `START` are the clear exceptions: both halves are built explicitly instead of through the mirror helper

One caution:

- the path-generation init block constructs aligned pairs beyond the `51` public names, so the constructor bank is larger than the public `Path=` name table

## Path Template Constructor Families

The constructor-family mapping below is the current high-confidence read for the `51` named slots. It is based on the init block between the `"path generation start"` and `"path generation end"` markers, filtered to aligned `0x150` pair starts.

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
| 24 | `WORM` | `sub_420170` | also does extra per-half object setup outside the generic `sub_4246a0` visual pass |
| 25-27 | `LOOPOUT*` | `sub_41c5f0` | `LOOPOUT`, `LOOPOUT3`, `LOOPOUTBIG` |
| 28 | `SWEEP` | `sub_422c00` | |
| 29 | `SNAKE` | `sub_423580` | |
| 30 | `WARP` | unresolved | no clean aligned constructor site recovered yet; no shipped extracted text currently references `WARP` |
| 31 | `SUPERTRAMP` | `sub_423f10` | both halves are built explicitly, not via `mirror_path_template_pair_x` |
| 32 | `SLALOMDOUBLE` | `sub_425050` | |
| 33-35 | `P0`, `P1`, `P2` | `sub_425a40` | |
| 36 | `START` | `sub_426400` | both halves are built explicitly, not via `mirror_path_template_pair_x` |
| 37 | `TURNOVER` | `sub_426cb0` | |
| 38 | `TURNOVERDOUBLE` | `sub_427640` | |
| 39 | `TURNUNDER` | `sub_427fe0` | |
| 40 | `WIBBLE` | `sub_4289a0` | |
| 41 | `INVERT` | `sub_429250` | |
| 42 | `HALFPIPE` | `sub_429b20` | |
| 43-44 | `TWISTERA`, `TWISTERB` | `sub_42a540` | |
| 45-46 | `TWISTER2A`, `TWISTER2B` | `sub_42af30` | |
| 47-50 | `TOAD*` | `sub_42cbf0` | `TOAD0`, `TOAD1`, `TOADPAIR0`, `TOADPAIR1` |

## Segment Metadata Layout

`load_segment_definitions` confirms the text grammar already implemented in the repo parser, and also shows how the RWG runtime stores per-row metadata.

Verified parser behavior:

- segment files are enumerated from `SEGMENTS/*.TXT`
- hard cap: `150` segment files
- each row keeps `8` interior cell characters between the leading and trailing `@` guards
- a literal `*` immediately after the row body is stored as a real per-row flag
- metadata matching is done through `find_case_insensitive_substring`, so matching is case-insensitive and prefix-friendly rather than exact
- recognized metadata includes:
  - `Path=<name>`
  - `Ring=<name>`
  - `RingSpeed=<float>`
  - `Parcel=<id>,(<x>,<y>,<z>)`
  - `3DModel=<mesh> (<x>,<y>,<z>)`
  - `Velocity=(<x>,<y>,<z>)`
  - `JetPack=Off`
  - `No Fall` / `NoFall`

Key storage facts from the decompile:

- row metadata uses a stride of `14` dwords per row
- each segment slot reserves metadata for `295` rows
- the path index field is written after `Path=` lookup through `find_segment_path_index_by_name`
- the ring-speed field is stored beside the path index in the same row-metadata array

Observed field offsets from the segment slot base in `load_segment_definitions`:

- row flags: `+0x88c`
- parcel id: `+0x890`
- parcel offset: `+0x894`, `+0x898`, `+0x89c`
- 3D model handle: `+0x8a0`
- model offset: `+0x8a4`, `+0x8a8`, `+0x8ac`
- velocity: `+0x8b0`, `+0x8b4`, `+0x8b8`
- path index: `+0x8bc`

Observed uses of the generic row-flags dword at `+0x88c`:

- `Parcel` and `NoFall` both set `0x01`
- `3DModel` and `Ring=None` both set `0x02`
- the post-row `*` marker and `Ring=Normal` both set `0x04`
- `Path`, `Velocity`, and `Ring=Explode` all set `0x08`
- `Ring=Slow` sets `0x10`
- `Ring=PowerUp` sets `0x20`
- `JetPack=Off` sets `0x80`

That means `+0x88c` is a generic metadata-flag byte, not a clean ring-only enum.

One useful parser detail:

- the case-insensitive substring matcher explains why shipped spellings like `Ring=Powerup` and `Ring=Explosive` still match the RWG parser's canonical probes `Ring=PowerUp` and `Ring=Explode`

The segment-to-runtime builder copies these row fields into the per-cell runtime record during `rebuild_track_runtime_from_segments`.

High-confidence runtime mapping:

- runtime `+0x5ccb58`, `+0x5ccb5c`, `+0x5ccb60`: copied parcel offset
- runtime `+0x5ccb64`: copied parcel id
- runtime `+0x5ccb68`: copied row `Path=` index
- runtime `+0x5ccb34`, `+0x5ccb38`, `+0x5ccb3c`: copied `3DModel` offset
- runtime `+0x5ccb4c`, `+0x5ccb50`, `+0x5ccb54`: copied `Velocity`

## Track Runtime Pipeline

The text segment grid is not used directly during play.

The current static read is that the game first builds a normalized runtime grid, then applies visual and gameplay passes on top of it.

Known stages:

- `select_track_tile_edge_variants`
  - computes neighbor masks for each track cell
  - chooses edge and corner variants for special tile classes
- `merge_track_tile_runs`
  - scans the normalized `8`-wide grid
  - collapses repeated horizontal runs into longer strip variants where allowed
- `allocate_parcels_on_track`
  - allocates parcel placements for the current course
  - also projects some flagged cells or items onto the generated track rows
- `allocate_challenge_parcels_on_track`
  - scans the rebuilt runtime cells for parcel-capable rows whose copied parcel id is `0`
  - randomly activates challenge parcels from that filtered set
- `get_track_cell_row_index`
  - converts a runtime cell pointer back into a row index inside the generated track

One useful clue from `allocate_parcels_on_track`:

- after parcel allocation, it calls helper math at `0x42b920` and `0x42b9c0` using runtime-cell pointers and the derived row index
- this strongly suggests those helpers sample a generated track basis or transform and then convert local offsets into world-space positions

One useful clue from `allocate_challenge_parcels_on_track`:

- the copied runtime field at `+0x5ccb64` is parcel id, not path index
- challenge-mode parcel selection explicitly filters for runtime cells whose parcel id equals `0`

## Level Runtime Field Mapping

The current static read is that `load_level_definition_file` only parses text into a level descriptor, and `sub_437eb0` later normalizes the selected descriptor into runtime fields before the track build begins.

High-confidence downstream behavior:

- `Random:yes` and `Length:` feed `populate_runtime_track_cells_from_segments`
  - a runtime flag toggles between authored sequential assembly and randomized segment selection
  - a runtime length value is used as the target generated track length
- `Track:` feeds `select_level_track_texture_set`
  - values `0..3` pick the matching track texture set
  - value `5` is the `Track:r` / random case and randomizes across `0..3`
- `Track:r` also changes backdrop handling during level start
  - non-random track ids keep the loaded background asset
  - the random-track path instead picks a random `Space*.txt` background
- `Garbage:` is normalized to a `0..1` runtime scalar and later consumed by `populate_track_runtime_entities`
  - that pass uses the scalar to gate calls to `spawn_track_garbage_hazard`
  - `spawn_track_garbage_hazard` allocates from a `50`-slot pool and chooses sprite ids `0x72..0x75`, which match `Sprites/GarbageA-D.tga`
- `Salt:` follows the same normalization pattern and also feeds `populate_track_runtime_entities`
  - the strongest current read is that it gates calls to `sub_441560`, which manages a `40`-slot pool
  - that likely corresponds to salt-related hazard or effect placement, but the exact asset identity is not fully pinned down yet from static text exports alone

One caution:

- the exact copy from the parsed level-descriptor fields into the later runtime slots is still inferred from the downstream reads above, rather than fully recovered as a typed struct assignment in the exported text dumps

## Confirmed Glyph Dispatch

`populate_runtime_track_cells_from_segments` does not switch directly on raw segment glyphs.

Instead it:

1. calls `normalize_segment_glyph_for_track_flags`
2. lets that helper rewrite some source glyph classes through `lookup_table_43744c[char - 0x20]`
3. normalizes the resulting glyph through `lookup_table_437204[char - 0x20]`
4. dispatches that case id through the switch rooted at `jump_table_437194`
5. assigns the runtime tile type at `cell + 0x3bfb04`

The table below is therefore a high-confidence normalized-glyph-to-runtime map for the shipped segment alphabet after `normalize_segment_glyph_for_track_flags` has done its substitutions.

One useful constraint from `lookup_table_43744c`:

- most printable glyphs bypass the normalizer unchanged
- only these raw glyph classes participate in rewrite logic:
  - space
  - `$`
  - `-`
  - `<` and `>`
  - `=`
  - `[` and `]`
  - `_`
  - `o`
  - `{`, `|`, and `}`

High-confidence rewrite behavior from `normalize_segment_glyph_for_track_flags`:

- space can rewrite to `,` or `.`
- `$` and `o` can rewrite to `.` or `_`
- `-` can collapse to `.`
- `<` and `>` can collapse to `.`
- `[` and `]` can rewrite into `.`, `<`, `{`, or stay as bracket-family glyphs
- `{` and `}` can rewrite into `.`, `>`, `{`, `}`, or stay as brace-family glyphs
- `=` and `|` participate in the flag-driven flat-tile family and can rewrite into `.`, `,`, space, `=`, or `|`

| Glyph | Dispatch Case | Runtime Tile Type | Notes |
|---|---:|---|---|
| space | `0x00` | `0x00` | empty or neutral |
| `#` | `0x01` | `0x20` | special flat tile |
| `$` | `0x02` | `0x17` | special flagged tile |
| `&` | `0x03` | `0x22` | special flagged tile |
| `(` | `0x04` | `0x16` | special height tile |
| `+` | `0x05` | `0x18` | special flagged tile |
| `,` | `0x06` | `0x1c` | special flat tile with a small height offset |
| `-` | `0x07` | `0x15` | special flagged tile |
| `.` | `0x08` | `0x01` | flat visible tile |
| `0` | `0x09` | `0x00` or `0x0f` | depends on existing attachment flags |
| `1` through `9` | `0x0a` | `0x00` or `0x0f` | same branch family as `0`, depends on existing attachment flags |
| `<` | `0x0b` | `0x06` | ramp-family tile |
| `=` | `0x0c` | `0x0e` | neutral or flat tile |
| `>` | `0x0d` | `0x03` or `0x09` | depends on the previous-row tile state |
| `@` | `0x0e` | `0x00` | row guard, not a gameplay tile |
| `F` | `0x0f` | `0x13` | special flagged tile |
| `G` | `0x10` | `0x11` | special flagged tile |
| `J` | `0x11` | `0x19` | special flagged tile |
| `M` | `0x12` | `0x12` | special flagged tile |
| `P` | `0x13` | `0x1e` | path attachment tile |
| `p` | `0x13` | `0x1d` | path attachment tile |
| `R` | `0x14` | `0x23` | special flat tile |
| `[` | `0x15` | `0x05` | ramp-family tile |
| `_` | `0x16` | `0x0f` | special flat tile |
| `o` | `0x17` | `0x10` | special flat tile |
| `s` | `0x18` | `0x21` | special flagged tile |
| `{` | `0x19` | `0x02` or `0x08` | depends on the previous-row tile state |
| `|` | `0x0c` | `0x0e` | aliases `=` |
| `}` | `0x1a` | `0x04` or `0x0a` | depends on the previous-row tile state |

The invalid dispatch case is `0x1b`, which falls into the builder's `TrackError:%c in Segment %s` path.

Useful follow-on facts from the same switch:

- runtime tile ids `0x1d` and `0x1e` are the only direct outputs of `p` and `P`
- `sample_track_floor_height_at_position` treats tile ids `0x02` through `0x0d` as ramp-like height families
- tile ids `0x08`, `0x09`, and `0x0a` get a built-in `+0.5` vertical bias in the floor-height sampler

## First Confirmed Path Consumer

The first strong static consumer of nonzero `Path=` indices is inside `rebuild_track_runtime_from_segments`.

For `P` and `p` cells in the segment row text:

- the builder copies the parsed row `Path=` index into runtime `+0x5ccb68`
- `P` becomes runtime tile type `0x1e`
- `p` becomes runtime tile type `0x1d`
- later in the same build pass, the `P/p` cell branch indexes hardcoded path-template pairs at:
  - `arg1 + 0xff2914`
  - `arg1 + 0xff29bc`
- each path id advances by `0x150` bytes, which corresponds to two `0xa8`-byte template records per path index
- the selected template record is stored on the track-grid cell and then propagated into runtime-cell attachment pointers for neighboring rows

This is the first point where named `Path=` rows clearly affect generated track attachments rather than just being parsed into metadata.

Practical read:

- `Path=<name>` is not only a parser-time annotation
- `P/p` rows are the bridge between text segments and hardcoded path-template geometry
- the route shape is at least partly driven by hardcoded template objects, not only by the visible text grid

## Hardcoded Path Templates

The path-template arrays appear to hold pairs of sampled path records.

Observed facts:

- the runtime owns a block rooted at `arg1 + 0xff2914`
- a second block at `arg1 + 0xff29bc` is exactly `0xa8` bytes later
- the initialization code zeroes `126` records of size `0xa8`, which is enough space for `63` path-index pairs
- helper constructors such as `sub_4289a0`, `sub_429250`, and `sub_429b20` build sampled path records with the same `0xa8` stride and are called during `initialize_game_assets_and_world`
- most named pairs are initialized as `constructor(base)` followed by `mirror_path_template_pair_x(base + 0xa8, base)`
- `SUPERTRAMP` and `START` instead construct both halves explicitly

High-confidence field usage inside one `0xa8` record:

- `+0x24`: display or visual object pointer used when `P/p` cells assign the runtime cell's primary object
- `+0x38`: sampled path object pointer consumed by the attachment-follow state machine
- `+0x48`: number of neighboring runtime cells that receive `0x40` or `0x80` attachment flags
- `+0x84`: secondary visual object pointer copied into the runtime cell's side object slot

What is not pinned down yet:

- the exact constructor site for the named `WARP` slot
- whether every aligned pair beyond the `51` public names is reachable from gameplay code
- whether all path slots are built eagerly during world init or some later code still patches them from smaller prototypes

## Attachment Follow State

The next major static finding is that the hardcoded path templates are not only visual. They feed a real player-follow state machine.

`update_player_track_movement_and_triggers` is the primary per-frame player or snail track update.

High-confidence behavior from the HLIL and IDA decompile:

- clamps lateral track position to `[-4, 4]`
- samples the current runtime cell from world position through `get_track_grid_cell_at_world_position`
- derives the current row index through `get_track_cell_row_index`
- samples ordinary floor height through `sample_track_floor_height_at_position`
- reacts to many tile ids through `cell->type` at runtime offset `+0x3c`
- enters and exits a separate attachment-follow state through `begin_track_attachment_follow_state`, `update_track_attachment_follow_state`, and `end_track_attachment_follow_state`

`sample_track_floor_height_at_position` makes the ordinary track-height rules explicit:

- flat or neutral cells return `0`
- ramp families return fractional height from the current row position
- tile `0x16` returns a per-cell stored height field
- unrelated cells return `-100`

That split matters because the path system is handled separately from ordinary floor height.

### How `P/p` Attachments Reach The Player

Inside the `P/p` branch of `rebuild_track_runtime_from_segments`:

- the selected hardcoded path-template record is written to the track cell at `+0x3bfb00`
- the record's neighbor count at `+0x48` determines how many runtime cells receive attachment flags
- those runtime cells get flag `0x40` first and then `0x80` for the second attachment lane
- the same pass stores attachment pointers into runtime `+0x5ccb6c` and `+0x5ccb70`

Later, `update_player_track_movement_and_triggers` checks those `0x40` and `0x80` flags on the current runtime cell and, when present, calls `try_enter_track_attachment_from_swept_motion` on the corresponding attachment pointer.

It also explicitly checks runtime tile types `0x1d` and `0x1e` before starting attachment-follow behavior, which ties the text glyphs `p` and `P` directly to the player movement path.

### Attachment Follow Functions

The follow-state chain now looks like this:

1. `begin_track_attachment_follow_state`
   - starts a follow state from the current runtime cell
   - stores the source cell pointer
   - captures the cell's path object pointer from `cell + 0x38`
   - resets progress and some exit-state values
2. `try_enter_track_attachment_from_swept_motion`
   - scans the attachment path object's sampled `0xa8` records backward
   - tests the current and swept player position against the attachment corridor
   - on hit, populates a global follow-state block at `data_4df904 + 0x430100`
   - immediately calls `update_track_attachment_follow_state`
3. `update_track_attachment_follow_state`
   - advances along the sampled path records using per-segment length at `sample + 0x8c`
   - updates world position from the sampled basis and origin fields
   - mutates some ride-state fields and returns `3` when the run finishes
4. `end_track_attachment_follow_state`
   - clears the active ride state and preserves a few exit values for ordinary movement to resume cleanly

`is_point_inside_track_attachment` is a related point-membership predicate over the same sampled path object and is used by movement code as a cheaper attachment test.

### Practical Read

This is the first high-confidence static evidence that:

- `Path=<name>` affects gameplay movement, not only visuals
- `P/p` rows install attachment corridors onto the generated runtime track
- the player update can transition from normal floor-following into a path-follow state backed by hardcoded sampled geometry
- the unresolved part is now mostly name-to-template mapping and exact tile semantics, not whether the paths matter at runtime

## Current Unknowns

The main unresolved issue is not the path-name lookup itself. That part is now clear.

The unresolved part is no longer whether the stored `Path=` row index is used for gameplay movement. It is.

What is still missing:

- the exact initialization path from the hardcoded path-name table to the path-template pair tables
- the detailed semantics of each path-template constructor beyond the current family grouping
- the exact constructor site for the named `WARP` slot
- the exact tile-id semantics around attachment entry, exit, and special-case movement reactions
- whether every named path family feeds the same attachment-follow code or whether some names are visual-only exceptions

## Practical Impact On The Rewrite

What the rewrite can already do confidently:

- parse `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- mirror the text metadata fields and row flags
- build a sequential blockout from segment rows
- attach semantic markers such as parcels, rings, models, and no-fall rows

What still needs more RE before the Zig runtime can match the original course shape:

- how each named `Path=` row maps onto the hardcoded template-pair tables
- how the original runtime samples those templates for player movement, object placement, and camera behavior
- which tile ids and row markers trigger attachment entry and exit versus ordinary floor-following
