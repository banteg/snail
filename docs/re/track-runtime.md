# Track Runtime

This page covers the runtime data path between authored segment metadata and the generated gameplay grid.

## Segment Metadata Layout

Verified parser behavior:

- segment files are enumerated from `SEGMENTS/*.TXT`
- hard cap: `150` segment files
- each row keeps `8` interior cell characters between the leading and trailing `@` guards
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

Observed uses of the packed row-flags dword at `+0x88c`:

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

Current high-confidence render-normalization read:

- `select_track_tile_edge_variants` is the main edge/corner swap pass
- `promote_track_tiles_to_fringe_variants` upgrades selected open-below cells before fringe emission
- `harmonize_center_lane_floor_slide_variants` applies the center-seam floor/slide override bit
- `merge_track_tile_runs` suppresses follower cells so long horizontal strips render as one run head
- `mark_track_warning_zones` expands warning footprints around hazard-bearing tiles before cache build
- `build_track_fringe_objects` allocates directional fringe objects from the post-normalized strip
  - it begins by calling `initialize_fringe_manager`
  - then uses `allocate_fringe_object` to draw from a 7000-entry pool of 0x38-byte fringe objects
  - each emitted fringe object takes its RGBA skirt colour from `get_track_skirt_color`
- `build_track_render_caches` consumes the resulting ownership/flag state into the Floor/Slide/Warn/Ramp/Fringe caches

Related shared color helper:

- `get_track_skirt_color` packages the current track skirt RGB scalars plus a fixed alpha into one RGBA tuple
- the same helper is used while populating runtime track rows and while emitting fringe objects

## Level Runtime Field Mapping

High-confidence downstream behavior:

- `Random:yes` and `Length:` feed `populate_runtime_track_cells_from_segments`
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
- `+` dispatches, but the current target is a nullsub and no shipped extracted segment currently uses it

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
- `0..3` -> classes `0x09` and `0x0a`
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

For the common gameplay build preset `0x00f5cfff` used by postal and challenge play, the shipped punctuation glyphs are effectively already in their enabled forms. The main remaining builder work is not the flag rewrite itself, but the row-to-row backpatching for the ramp families.

Recovered flat gameplay and hazard anchors:

- `.` -> runtime tile `0x01`
- `_` -> runtime tile `0x0f`
- `|` -> runtime tile `0x0e`
- `(` -> runtime tile `0x16`
- `-` -> runtime tile `0x15`
- `P` / `p` participate in the attachment-install path, but the exact glyph-to-runtime-tile mapping is still not settled from the current Windows package
- `$` -> runtime tile `0x17`
- `J` -> runtime tile `0x19`
- `M` -> runtime tile `0x12`
- explicit `R` rows land on runtime tile `0x23`
- explicit `s` rows land on runtime tile `0x21`
- explicit `&` rows land on runtime tile `0x22`
- `#` rows land on runtime tile `0x20`
- `@` guard rows normalize to runtime tile `0x00`
- parcel digits `0..3` normalize into the parcel floor tile family rooted at runtime tile `0x0f`

Recovered special floor-height slot use:

- runtime cell `+0x14` is the per-cell floor-height slot sampled by `sample_track_floor_height_at_position`
- runtime tile `0x16` returns that stored slot directly instead of using a generic slope formula
- in the shipped track-builder branch recovered so far, the `0x16` builder case seeds that slot to `-3.0`
- player update also treats tile `0x16` specially when comparing player `y` against that stored floor height

Recovered row-wise ramp and connector rewrites:

- `>`:
  - first row in a run becomes runtime tile `0x03`
  - if the previous row in the same lane was not already `0x03`, that previous row is backpatched to `0x0c`
  - subsequent linked rows in the same lane become `0x09`
- `{`:
  - first row in a run becomes runtime tile `0x02`
  - if the previous row in the same lane was not already `0x03`, that previous row is backpatched to `0x0b`
  - subsequent linked rows in the same lane become `0x08`
- `}`:
  - first row in a run becomes runtime tile `0x04`
  - if the previous row in the same lane was not already `0x03`, that previous row is backpatched to `0x0d`
  - subsequent linked rows in the same lane become `0x0a`

## Salt, Slug, and Ring Dispatch

High-confidence findings:

- `salt.x` is cloned into a `40`-slot runtime array and managed separately from slugs
- slugs use an `8`-slot pool and a different runtime path
- authored `R` rows map onto ring-effect helpers through the packed ring bits
- runtime tile `0x18` exists in the track builder but the later entity-population path calls a stubbed `nullsub`, not a live pickup or hazard spawner
- `Ring=None` suppresses the helper
- `Ring=Normal` and `Ring=PowerUp` land on the ring particle family
- `Ring=Explode` lands on the explode particle family
- `Ring=Slow` lands on the slow particle family

Recovered salt-slot lifecycle:

- `spawn_salt_hazard` scans a `40`-slot pool with stride `0x98`
- slot state lives at `slot + 0x80`
- a free slot is one with state `0`
- spawn initializes:
  - `slot + 0x80 = 1`
  - `slot + 0x8c = 0`
  - `slot + 0x90 = game_dt * 0.0333333351`
  - `slot + 0x94 = 1`
  - `slot + 0x68/+0x6c/+0x70 = spawn xyz`
- the slot also enters a linked list and sets runtime flag `0x200`

Recovered update and teardown:

- `update_salt_hazard` advances an arming factor at `slot + 0x98` by `slot + 0x9c`
- once armed, it integrates position by adding velocity at:
  - `slot + 0x8c` -> `x`
  - `slot + 0x90` -> `y`
  - `slot + 0x94` -> `z`
- `deactivate_salt_hazard` removes the slot from the active list and clears state back to `0`

Recovered deactivation conditions:

- `y < 0`
- `z` past the current track maximum
- runtime tile `0x0e` with `y < 7`
- entering an attachment corridor carried by runtime flags `0x40` or `0x80`

## Runtime Flags

Confirmed authored-to-runtime lanes:

- `Parcel` -> runtime low-byte `0x01` plus `0x4000`
- `NoFall` -> runtime `0x100`
- `JetPack=Off` -> runtime `0x8000`

Important caveat:

- `0x8000` is seeded by authored `JetPack=Off`, but later visual normalization also reuses that lane
- path attachments use different low-byte lanes, so they should not be flattened together with `JetPack=Off`
- the rewrite should keep `Parcel`, `NoFall`, `JetPack=Off`, and path attachments as distinct authored concepts

## Runtime Cell Quantization

Recovered from `get_track_grid_cell_at_world_position` and `get_track_runtime_cell_at_world_z`:

- world `x` is quantized with `floor(x + 4.0)` and clamped to lane `0..7`
- world `z` is quantized with `floor(z)` and clamped to row `0..0xc7f`
- runtime track rows are stored at `game + 0x5ccac8 + row * 0xf4`
- gameplay grid cells are stored at `game + 0x3bfac8 + (lane + row * 8) * 0x54`

That is the sampling path used both by player movement and by the floor-height helper.

## Runtime Tile Families

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
- `0x22` -> `spawn_salt_hazard`
- `0x12` -> `spawn_slug_hazard` when `build_flags & 0x80`
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
