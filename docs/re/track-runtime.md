# Track Runtime

This page covers the runtime data path between authored segment metadata and the generated gameplay grid.

## Segment Metadata Layout

Verified parser behavior:

- segment files are enumerated from `SEGMENTS/*.TXT`
- hard cap: `150` segment files
- each row keeps `8` interior cell characters between the leading and trailing `@` guards
- the Zig text parser currently retains the two guard columns for editor/debug
  visibility, but the runtime builder mirrors native by treating them as parser
  fences: they map to empty cells and do not advance `switch_track_mirror`
- `switch_track_mirror` increments its latch counter when the random mirror
  decision repeats the current state; the fourth repeat flips the decision and
  clears the counter
- a literal `*` immediately after the row body is stored as a real per-row flag
- metadata matching is case-insensitive and prefix-friendly rather than exact
- recognized metadata includes `Path`, `Ring`, `RingSpeed`, `Parcel`, `3DModel`, `Velocity`, `JetPack=Off`, and `NoFall`

Observed field offsets from the segment slot base in `load_segment_definitions`:

- row flags: `+0x88c`
- parcel id: `+0x890`
- parcel offset: `+0x894`, `+0x898`, `+0x89c`
- 3D model handle: `+0x8a0`
- model offset: `+0x8a4`, `+0x8a8`, `+0x8ac`
- velocity: `+0x8b0`, `+0x8b4`, `+0x8b8`
- path index: `+0x8bc`
- ring speed: `+0x8c0`

Current Zig port note:

- the segment parser and preview pipeline now preserve per-row `RingSpeed` metadata as a first-class row/runtime field instead of dropping it during text import

`AuthoredSegmentRowFlag` owns the packed row-flags dword at `+0x88c`:

- low byte:
  - `Parcel` sets `0x01`
  - `3DModel` sets `0x02`
  - the post-row `*` marker sets `0x04`
  - `Path` and `Velocity` set `0x08`
- second byte:
  - `NoFall` sets `0x01`
  - `Ring=None` sets `0x02`
  - `Ring=Normal` sets `0x04`
  - `Ring=Explode` sets `0x08`
  - `Ring=Slow` sets `0x10`
  - `Ring=PowerUp` sets `0x20`
  - `JetPack=Off` sets `0x80`

## Track Runtime Pipeline

Known stages:

- `select_track_tile_edge_variants`
- `promote_track_tiles_to_fringe_variants`
- `harmonize_center_lane_floor_slide_variants`
- `merge_track_tile_runs`
- `mark_track_warning_zones`
- `build_track_fringe_objects`
- `build_track_render_caches`
- `place_parcels_on_track`
- `place_challenge_parcels_on_track`
- `get_track_grid_cell_at_world_position`
- `sample_track_floor_height_at_position`
- `get_track_cell_row_index`

The practical read is that the game does not play directly on the authored text grid. It first builds and normalizes a runtime grid, then applies gameplay and render passes on top of that generated state.

The cross-port symbols also recover the authored builder hierarchy:

- Windows `populate_runtime_track_cells_from_segments` is `cRSubGame::BuildLevel()`; it chooses segments and materializes their rows and glyphs into the runtime slabs
- exact Windows `rebuild_track_runtime_from_segments` is the void `cRSubGame::GenerateLevel(int)`; it wraps `BuildLevel()` with feature, colour, parcel, normalization, warning, fringe, and cache passes
- outer Windows `build_subgame_level` is `cRSubGame::StartLevel(int)`; it loads the level and managers, calls `GenerateLevel(int)`, and then establishes landscape, player, HUD, music, and active-list state

Current high-confidence render-normalization read:

- `select_track_tile_edge_variants` is the main edge/corner swap pass
- `promote_track_tiles_to_fringe_variants` upgrades selected open-below cells before fringe emission
- `harmonize_center_lane_floor_slide_variants` applies the center-seam floor/slide override bit after BOD-object table matches
- `merge_track_tile_runs` suppresses follower cells so long horizontal strips render as one run head
- `mark_track_warning_zones` expands warning footprints around hazard-bearing tiles before cache build
- `build_track_fringe_objects` allocates directional fringe objects from the post-normalized strip
  - it begins by calling `initialize_fringe_manager`
  - then uses `allocate_fringe_object` to draw from a 7000-entry pool of 0x38-byte fringe objects
  - each emitted fringe object takes its RGBA skirt colour from `get_track_skirt_color`
- void `build_track_render_caches` consumes the resulting ownership/flag state into the Floor/Slide/Warn/Ramp/Fringe caches; its final debug-report value is incidental, just as the initializer's final allocation pointer is incidental

Current Zig port status for this slice:

- static asset-init recovery confirms the promoted floor and promoted slide replacement tables both route into the shared `TRACKWARN` asset family, but native only promotes after matching the current BOD object against those tables; the port no longer guesses from open-below runtime tiles alone
- `harmonize_center_lane_floor_slide_variants` is likewise table-driven: row phase and neighbour families are only candidate filters, so the port no longer guesses center-seam floor/slide flips from tile ids alone
- the horizontal ownership lane now also follows the recovered floor-vs-slide split more closely: floor condensation uses the native subset (`0x01/0x15/0x1b/0x21/0x22`, excluding floor-family tile `0x14`), the separate slide-family path uses `IsSlide`, and warn-promoted or corner-marked heads no longer collapse into a single quad
- the runtime edge-mask lane now also carries the native corner bit on `5/6/9/10` masks
- the simple fringe renderer now honors two recovered `build_track_fringe_objects` suppressors: marked rows and explicit runtime warn tile `0x20`
- the simple fringe renderer now uses the recovered `is_neighbor_cell_solid` predicate directly for fringe-neighbour solidity; render-backed marker cells like `0x0e`, `0x1d`, and `0x23` remain open, while attachment-entry tile `0x1e` is solid as a neighbour but does not emit its own fringe because `select_track_tile_edge_variants` excludes it from edge-mask assignment
- the simple fringe renderer now also uses the recovered shared skirt tint shape from `get_track_skirt_color`: white RGB with fixed `0.4` alpha
- the runtime preview and debug path now also mirror the recovered `mark_track_warning_zones` footprint grid
- the warning-footprint lane now also feeds one recovered gameplay consumer: it suppresses generic ambient garbage/salt fallback spawns on `0x01/0x15/0x0f` cells, matching the native `update_subgame` gate
- `mark_track_warning_zones` operates on the native 8 playable lanes. In Zig's
  retained 10-column parser grid, the first and last `@` guard columns are not
  eligible warning seed or footprint lanes.
- the remaining static gap is exact BOD-table matching for `promote_track_tiles_to_fringe_variants` and `harmonize_center_lane_floor_slide_variants`, the final render/cache consumer for `mark_track_warning_zones` beyond that fallback-hazard suppressor, directional fringe objects, and the last marked-row / low-bit ownership details in `merge_track_tile_runs`

Related shared color helper:

- `get_track_skirt_color` packages the current track skirt RGB scalars plus a fixed alpha into one RGBA tuple
- the currently recovered initializer path (`build_track_colours` -> `sub_44dc50` -> `sub_44db90(..., 1.0)`) leaves those skirt RGB scalars at white unless another later owner mutates them
- the same helper is used while populating runtime track rows and while emitting fringe objects

## Game-Wide Runtime Feature Flags

`SubgameRuntime::runtime_flags` at `+0x4c` is a game-wide course-feature word.
It is a separate owner from both `AuthoredSegmentRow::flags` and the copied
`SubRow::flags` word. `set_subgame_features` writes the mode preset before
track population, while selected replay/high-score records can restore the
complete persisted word.

Windows producer/consumer evidence currently proves these individual bits:

| Bit | Recovered owner meaning | Native consumer |
|---:|---|---|
| `0x000001` | preserve the space glyph variant | glyph normalizer; also selects disabled `=`/`|` fallbacks |
| `0x000002` | ambient garbage spawning | random garbage fallback in `update_subgame` |
| `0x000004` | preserve authored `o` | glyph normalizer |
| `0x000008` | default ramp rings | unauthored kind-4 ramp-ring path in `update_subgame` |
| `0x000010` | ring life reward | kind-4/5 ring collision adds one life below ten outside mode 3 |
| `0x000020` | preserve brace/bracket orientation | glyph normalizer keeps `{}`/`[]` variants instead of collapsing them |
| `0x000040` | preserve authored `_` | glyph normalizer; also the disabled `o`/`$` fallback |
| `0x000080` | slug hazards | runtime tile `0x12` slug spawn path |
| `0x000100` | preserve authored `=` and `|` | glyph normalizer |
| `0x000200` | preserve ramp punctuation | glyph normalizer gates `<>[]{}` |
| `0x000400` | allow falling | player update skips its blanket floor clamp; builder preserves gap behavior |
| `0x000800` | health pickups | runtime tile `0x17` health spawn path |
| `0x004000` | preserve authored `-` | glyph normalizer |
| `0x010000` | ambient salt spawning | random salt fallback in `update_subgame` |
| `0x400000` | movement-fire emitters | late `update_subgoldy` presentation/audio path |
| `0x800000` | parcel spawns | selected `SubRow` parcel request in `update_subgame` |

The exact native composite words are:

| Producer path | Mask |
|---|---:|
| pre-switch seed | `0x000484` |
| transitional/default engine modes | `0x600484` |
| Postal and Challenge | `0xf5cfff` |
| Time Trial | `0x75cfff` |
| Tutorial from `set_subgame_features` | `0xe4cfff` |
| `initialize_tutorial` OR mask | `0x600000` |

Bits `0x040000`, `0x100000`, and `0x200000` remain present only through those
composite presets in the recovered Windows paths. They deliberately remain
unnamed until a native consumer establishes their behavior; in particular,
the tutorial `0x600000` OR must not be flattened into two guessed feature
names. Tutorial then clears only the proved ambient-garbage bit `0x000002`.

## Level Runtime Field Mapping

High-confidence downstream behavior:

- `Random:yes` and `Length:` feed `populate_runtime_track_cells_from_segments`
- random levels choose a seeded middle segment strip at runtime; challenge mode scales both the target `Length:` and the candidate-pool upper bound from the normalized difficulty lane
- that same runtime-population pass seeds Goldy's visible life stock to `3` before `initialize_subgoldy`
- `Track:` feeds `select_level_track_texture_set`
- `Track:r` randomizes across the non-random track sets and changes backdrop handling
- `Garbage:` becomes a normalized `0..1` runtime scalar used by the gameplay-side spawn path inside `update_subgame`
- `Salt:` follows the same normalization pattern and feeds the salt hazard path

## Confirmed Glyph Dispatch

High-confidence normalized-glyph-to-runtime cases:

- `$` -> health pickup
- `J` -> jetpack pickup
- `s` -> garbage hazard
- `&` -> salt hazard
- `M` -> slug hazard
- `P` and `p` -> path attachment tiles
- `+` dispatches to runtime tile `0x18` with the same floor-family BOD as the pickup/slug floor rows
- `F` dispatches to runtime tile `0x13` with the same floor-family BOD
- `G` dispatches to runtime tile `0x11` with the same floor-family BOD, even though that tile id is outside the recovered floor-cache predicate

Useful follow-on facts:

- ramp-like tile families drive the floor-height sampler
- some normalized tile ids carry extra vertical bias
- the text alphabet goes through a normalization pass before runtime tile ids are assigned

Recovered normalized glyph classes used by the shipped segment corpus:

- ` ` -> class `0x00`
- `#` -> class `0x01`
- `$` -> class `0x02`
- `&` -> class `0x03`
- `-` -> class `0x07`
- `.` -> class `0x08`
- `0..9` -> classes `0x09` and `0x0a` (`0..3` are the only decimal bodies used by the shipped segment corpus)
- `<` -> class `0x0b`
- `=` and `|` -> class `0x0c`
- `>` -> class `0x0d`
- `@` -> class `0x0e`
- `J` -> class `0x11`
- `M` -> class `0x12`
- `P` and `p` -> class `0x13`
- `R` -> class `0x14`
- `[` -> class `0x15`
- `_` -> class `0x16`
- `s` -> class `0x18`
- `{` -> class `0x19`
- `}` -> class `0x1a`

For the common gameplay build preset `0x00f5cfff` used by postal and challenge play, the shipped punctuation glyphs are effectively already in their enabled forms. One easy-to-misread split is `-`: native gates it on build flag `0x4000`, not on the nearby floor-family bit `0x40`. The main remaining builder work is not the flag rewrite itself, but the row-to-row backpatching for the ramp families.

Recovered flat gameplay and hazard anchors:

- `.` -> runtime tile `0x01`
- `_` -> runtime tile `0x0f`
- `|` -> runtime tile `0x0e`
- `(` -> runtime tile `0x16`
- `-` -> runtime tile `0x15`
- `+` -> runtime tile `0x18`
- `F` -> runtime tile `0x13`
- `G` -> runtime tile `0x11`
- `P` participates in the attachment-install path as runtime tile `0x1e`
- `p` participates in the attachment-install path as runtime tile `0x1d`
- `$` -> runtime tile `0x17`
- `J` -> runtime tile `0x19`
- `M` -> runtime tile `0x12`
- explicit `R` rows land on runtime tile `0x23`
- explicit `s` rows land on runtime tile `0x21`
- explicit `&` rows land on runtime tile `0x22`
- `#` rows land on runtime tile `0x20`
- `@` guard rows normalize to runtime tile `0x00`
- parcel digits `0..9` normalize into the parcel floor tile family rooted at runtime tile `0x0f`; the native case table accepts the full decimal range even though the shipped rows only use `0..3`

Recovered special floor-height slot use:

- runtime cell `+0x14` is the per-cell floor-height slot sampled by `sample_track_floor_height_at_position`
- runtime tile `0x16` returns that stored slot directly instead of using a generic slope formula
- in the shipped track-builder branch recovered so far, the `0x16` builder case seeds that slot to `-3.0`
- player update also treats tile `0x16` specially when comparing player `y` against that stored floor height

Recovered row-wise ramp and connector rewrites:

- `>`:
  - first row in a run becomes runtime tile `0x03`
  - when the previous row in the same lane is runtime tile `0x03`, the current row becomes `0x09` and that previous row is backpatched to `0x0c`
- `{`:
  - first row in a run becomes runtime tile `0x02`
  - when the previous row in the same lane is runtime tile `0x03`, the current row becomes `0x08` and that previous row is backpatched to `0x0b`
- `}`:
  - first row in a run becomes runtime tile `0x04`
  - when the previous row in the same lane is runtime tile `0x03`, the current row becomes `0x0a` and that previous row is backpatched to `0x0d`

## Salt, Slug, and Ring Dispatch

High-confidence findings:

- startup loads `salt.x` into the root salt donor and clones that object into
  the `40` inline `0x98`-byte salt slots at `SubgameRuntime +0x3578c0`
- startup likewise clones the root lazer donor into the `20` inline
  `0xb0`-byte sub-lazer slots at `SubgameRuntime +0x356b00`
- both slot families borrow their owning subgame through slot `+0x88`
- `SubLazerState` is the 32-bit slot owner at `+0x80`: inactive `0`, active
  `1`, and recycle-pending `2`
- `cRSubLazerManager::Init()` clears every slot to inactive; the manager Shoot
  scan selects an inactive actor, actor Shoot marks it active, collision or bob
  expiry marks it recycle-pending, and actor AI returns that state through the
  root active-BOD list
- salt is managed separately from slugs
- slugs use an `8`-slot pool and a different runtime path: tile `0x12` scans
  for `SUB_SLUG_STATE_INACTIVE`, activates the selected slot, and later
  collision accepts only `ACTIVE` or `LATERAL_ACTIVE`; kill advances an active
  slot through `DEATH_TOSS_PENDING` and `TEARDOWN_PENDING` before recycle
- authored `R` rows map onto ring-effect helpers through the packed ring bits
- runtime tile `0x18` exists in the track builder but the later entity-population path calls a stubbed `nullsub`, not a live pickup or hazard spawner
- `Ring=None` suppresses the helper
- `Ring=Normal` and `Ring=PowerUp` land on the ring particle family
- `Ring=Explode` lands on the explode particle family
- `Ring=Slow` lands on the slow particle family
- ramp-tile ring placement is split:
  - default `SUB_RING_KIND_NORMAL_DEFAULT` (`4`) ramp rings are spawned from the current cell and receive the native `+6` row z offset inside `spawn_track_ring_or_special_effect`; the spawner may randomize them to `SLOW_DEFAULT` (`3`)
  - ramp `Ring=PowerUp`/`Ring=Explode`/`Ring=Slow` calls pass the cell `48` rows ahead (`0xfc0 / 0x54`) and use that target cell directly
  - explosive ramp tiles `0x08..0x0a` still use the current cell and receive the native `+17` row z offset in the `SUB_RING_KIND_EXPLODE_RAMP` (`2`) branch
- kinds `0` and `1` remain named `UNKNOWN_0` and `UNKNOWN_1`: their distinct native spawn/consumer paths are preserved, but no live Windows producer has been recovered

Recovered salt-slot lifecycle:

- `initialize_salt_hazard_pool` is the exact void `cRSaltManager::Init()` and
  clears all 40 inline slots to `SALT_STATE_INACTIVE`
- `spawn_salt_hazard` scans a `40`-slot pool with stride `0x98`
- `SaltState` lives at `slot + 0x80`: inactive `0`, active `1`, and
  recycle-pending `2`
- a free slot is one with state `SALT_STATE_INACTIVE`
- spawn initializes:
  - `state = SALT_STATE_ACTIVE`
  - `fade_alpha +0x8c = 0`
  - `spawn_velocity_y +0x90 = game_dt * 0.0333333351`
  - `collision_armed +0x94 = 1`
  - `slot + 0x68/+0x6c/+0x70 = spawn xyz`
- the slot also enters a linked list and sets runtime flag `0x200`
- the Windows Add caller discards EAX, but the exact function has
  return-sensitive exit shapes; its analysis ABI remains conservatively
  `int32_t` and no slot-index result is claimed

2026-06-16 correction:

- the integrating/attachment-probe updater at `0x4417d0` belongs to the
  sub-lazer vtable, not the salt vtable
- `0x441740` is the paired sub-lazer deactivate helper
- the salt vtable installed by `initialize_salt_hazard_runtime` points at
  `0x441c10`; that updater computes a fade fraction at `slot + 0x8c`,
  updates alpha, and moves the slot to `SALT_STATE_RECYCLE_PENDING` after the
  z cutoff

The older claim that salt update integrates `slot +0x8c/+0x90/+0x94` as
velocity came from the shifted `0x4417d0` label.

Recovered deactivation conditions:

- `y < 0`
- `z` past the current track maximum
- runtime tile `0x0e` with `y < 7`
- entering an attachment corridor carried by runtime flags `0x40` or `0x80`

Wall2 / runtime tile `0x0e` render ownership:

- `merge_track_tile_runs` condenses horizontal `0x0e` runs into a single BOD owner on the first cell
- the merged run width is stored in that owner cell as `TrackRowCell.render_flags >> 8`
- follower cells have their object-owner bits cleared and should not independently draw `PILLAR1.X2`
- `update_golb_ai` only uses runtime tile `0x0e` for the fallback track-grid projectile stop after live-object collision checks; authored floor and parcel digit cells are not projectile blockers

## Runtime Flags

`SubRowFlag` owns the generated `SubRow::flags` dword. Confirmed
authored-to-runtime lanes:

- `Parcel` (`0x0001`) becomes `SUBROW_FLAG_PARCEL_CANDIDATE` plus
  `SUBROW_FLAG_PARCEL_Z_IS_LOCAL` (`0x4000`); the latter tells challenge
  placement to add the selected absolute row to the authored local z
- `3DModel` (`0x0002`) becomes `SUBROW_FLAG_ROW_MODEL_PRESENT`, consumed when
  `update_subgame` activates the embedded `RowModel`
- the authored `*` marker (`0x0004`) becomes
  `SUBROW_FLAG_SUPPRESS_TRACK_RENDER`; both fringe construction and merged-run
  cleanup suppress the row's cells and attachment body
- authored `Path` and model `Velocity` deliberately share `0x0008`; the
  runtime lane remains named `SUBROW_FLAG_PATH_OR_MODEL_VELOCITY` rather than
  pretending those two parser concepts are separable
- `NoFall` becomes `SUBROW_FLAG_NO_FALL` (`0x0100`); the proved player-side
  consumer skips the post-attachment forward-velocity drag on that row
- `Ring=None`, `Normal`, `Explode`, `Slow`, and `PowerUp` preserve their
  `0x0200`, `0x0400`, `0x0800`, `0x1000`, and `0x2000` lanes for the ring and
  special-effect dispatcher
- `JetPack=Off` becomes `SUBROW_FLAG_JETPACK_OFF` (`0x8000`) and snaps the
  active jetpack gauge to its `0.94` shutoff band

Runtime-only lanes add state that does not belong to the authored record:

- `0x0010`: a selected parcel spawn request
- `0x0020`: mirrored-row parcel coordinates
- `0x0040` / `0x0080`: primary and overlapping secondary attachment spans

The identical numeric `0x8000` in `SubLoc::lane_and_flags` belongs to the
separate per-cell owner (`SUBLOC_FLAG_CORNER_OBJECT`). It is not a reuse of the
`SubRow` jetpack bit.

## Runtime Cell Quantization

Recovered from `get_track_grid_cell_at_world_position` and `get_track_runtime_cell_at_world_z`:

- world `x` is quantized with `floor(x + 4.0)` and clamped to lane `0..7`
- world `z` is quantized with `floor(z)` and clamped to row `0..0xc7f`
- runtime track rows are stored at `game + 0x5ccac8 + row * 0xf4`
  - the canonical checked-in owner is `SubRow` (`cRSubRow` in symbol-preserving builds)
  - the shared analysis header and both live databases use that same identity;
    the retired descriptive `TrackAttachmentRuntimeRow` name is no longer an
    active consumer type
  - `+0x00`: `flags`
  - `+0x04`: embedded `RowModel`, including the authored 3D row body
  - `+0xb0`: embedded `BodBase attachment_body` used by path strips and fringe
  - `+0xe8`: `ring_speed`
- gameplay grid cells are stored at `game + 0x3bfac8 + (lane + row * 8) * 0x54`
- the canonical cell owner is `SubLoc` (`cRSubLoc`); its constructor runs the
  shared `cRBod` initializer over the `+0x00..+0x37` body prefix, and the grid
  builder routes object selection through the shared `BodBase::set_bod_object`
  method rather than a separate cell-only object slot
- the checked-in typed slice for one gameplay/render cell also exposes:
  - `anchor_position`
  - `attachment_template_record`
  - byte-sized `SubLocTileId tile_id`
  - `open_edge_mask`
  - `lane_and_flags`
  - four fringe/cache object slots at `+0x44..+0x50`
- `+0x3e..+0x3f` is proved alignment padding: the live Binary Ninja database
  has no field xrefs there, unlike `tile_id`, `open_edge_mask`, and
  `lane_and_flags` on either side.
- `open_edge_mask` is produced from the four adjacent cells:
  - `0x01` previous row/back
  - `0x02` next row/front
  - `0x04` next lane/right
  - `0x08` previous lane/left
- the independently proved `lane_and_flags` lanes are:
  - `0x0007` lane index
  - `0x0008/0x0010` suppress random salt/garbage spawns; warning footprints
    stamp both as `0x0018`
  - `0x0020` warning-cache family and `0x0040` swapped floor/slide cache family
  - `0x0f00` merged-run width, shifted by 8
  - `0x2000` AI enabled
  - `0x4000` uncached standalone body; render-cache aggregation clears it
  - `0x8000` corner object
- runtime row `+0xe8` carries the per-row `RingSpeed` float copied from segment metadata

That is the sampling path used both by player movement and by the floor-height helper.

## Runtime Tile Families

The shared `SubLocTileId` vocabulary now connects the glyph builder to every
typed consumer. Names are limited to behavior proved in Windows or preserved
cross-port predicates:

- `SUBLOC_TILE_EMPTY` (`0x00`) and `SUBLOC_TILE_FLOOR_DOT` (`0x01`)
- the twelve ramp identities `0x02..0x0d`, named by their authored
  brace/bracket/angle producer and raised/backpatch role
- `SUBLOC_TILE_WALL2` (`0x0e`), the pillar-bodied tile whose `cRSubLoc::AI`
  path emits SubLazer projectiles
- slide/floor glyph variants `0x0f..0x15`, including the exact `_`, `o`, `F`,
  `G`, and `-` producers plus the predicate-only variants
- `SUBLOC_TILE_TRAMPOLINE` (`0x16`), health/speedup/jetpack markers
  (`0x17..0x19`), and the remaining predicate-only slide/floor variants
  (`0x1a..0x1b`)
- `SUBLOC_TILE_UNIVERSE_HOLE` (`0x1c`), lowercase/uppercase path entries
  (`0x1d/0x1e`), and the width-only variant (`0x1f`)
- hash, garbage, salt, and ring markers (`0x20..0x23`)

The VC6 matcher lane keeps `SubLocTileId` as a byte typedef and puts the named
constants in `SubLocTileIdValue`, because ordinary VC6 enums are four bytes.
The analysis header instead uses a fixed-width one-byte `SubLocTileId` enum,
which lets Binary Ninja and IDA render the same values without widening the
shipped `cRSubLoc +0x3c` field.

Recovered helper predicates:

- floor-cache family:
  - `0x0f`, `0x10`, `0x12`, `0x13`, `0x17`, `0x18`, `0x19`, `0x1a`
- ramp family:
  - `0x02`, `0x03`, `0x04`, `0x05`, `0x06`, `0x07`, `0x08`, `0x09`, `0x0a`, `0x0b`, `0x0c`, `0x0d`
- slide family:
  - `0x01`, `0x14`, `0x15`, `0x1b`, `0x21`, `0x22`
- open-neighbor family:
  - `0x00`, `0x0e`, `0x1c`, `0x1d`, `0x23`

These helpers feed both the render-cache passes and the movement code, so they are a better porting boundary than the raw authored glyphs.

Recovered gameplay entity-population tile semantics from `update_subgame`:

- `0x17` -> `spawn_track_health_pickup`
- `0x18` -> stubbed `nullsub`
- `0x19` -> `spawn_track_jetpack_pickup`
- `0x21` -> `spawn_track_garbage_hazard`
  - the exact allocator selects `SUB_GARBAGE_STATE_INACTIVE` from the owned
    50-slot pool and activates the slot; collision/Golb consumers transition
    it through `BURST_PENDING` to the exact AI's `BURST` state
- `0x22` -> `spawn_salt_hazard`
- `0x12` -> `spawn_slug_hazard` when `build_flags & 0x80`; the exact allocator
  claims one inactive record from the eight owned `0xec`-byte slots and writes
  `SUB_SLUG_STATE_ACTIVE`
- `0x01` and `0x15` can also produce garbage through the randomized fallback branch when `build_flags & 0x2`
- `0x01` and `0x0f` can also produce salt through the randomized fallback branch when `build_flags & 0x10000`
- `0x23` plus the ramp ring family `0x02..0x0a` feed `spawn_track_ring_or_special_effect`

## Floor Height Sampling

Recovered from `sample_track_floor_height_at_position`:

- sample the current runtime cell through `get_track_grid_cell_at_world_position`
- read the runtime tile id from cell `+0x3c`
- let `fract_z = z - floor(z)`

Returned floor heights:

- `0x01`, `0x0e`, `0x0f` -> `0.0`
- `0x02`, `0x03`, `0x04`, `0x05`, `0x06`, `0x07`, `0x0b`, `0x0c`, `0x0d` -> `fract_z * 0.4`
- `0x08`, `0x09`, `0x0a` -> `(fract_z * 0.4) + 0.5`
- `0x16` -> per-cell stored floor height at `cell + 0x14`
- everything else -> `-100.0`

This is the clearest recovered statement so far that the original game samples movement height from runtime tile ids, not directly from the authored text characters.

## Render Pipeline

The post-build renderer uses explicit cache buckets:

- `Floor`
- `Slide`
- `Warn`
- `Ramp`
- `Fringe`

Those passes reuse runtime flags and helper families, so not every runtime bit should be interpreted as pure authored gameplay metadata.

The checked-in render-cache owner slice now also exposes:

- `SegmentCache.max_vertex_counts[5]`
- `SegmentCache.max_index_counts[5]`
- `SegmentCache.shared_vertex_buffers[5]`
- `SegmentCache.shared_index_buffers[5]`
- `SubgameRuntime.segment_cache` at `+0x5c`
- `SegmentCache.owner_subgame`, a borrowed backlink to the enclosing runtime
- `SegmentCache.slots[143][5]`, owned `BodBase` cache nodes
- `TrackRenderCacheSlot.cache_row_base` at `+0x38`
- the generic render-object texture-group tail at `+0xc0..+0xd4`

The cache mesh code is three functions, not one oversized extent:
`build_track_render_caches @ 0x433220`, `add_track_cache_vertex @ 0x433830`,
and `append_track_cache_object @ 0x433960`. Curating those boundaries raises
the public builder to 99.79% while keeping both helpers independently auditable.
Both helpers borrow the canonical `Object` geometry owner; the previous
`PathTemplateStripMesh` input was only a stale partial view and could not
describe the fringe and runtime-cell objects passed by the builder.
