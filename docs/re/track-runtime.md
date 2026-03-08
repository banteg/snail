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
- `merge_track_tile_runs`
- `allocate_parcels_on_track`
- `allocate_challenge_parcels_on_track`
- `get_track_cell_row_index`

The practical read is that the game does not play directly on the authored text grid. It first builds and normalizes a runtime grid, then applies gameplay and render passes on top of that generated state.

## Level Runtime Field Mapping

High-confidence downstream behavior:

- `Random:yes` and `Length:` feed `populate_runtime_track_cells_from_segments`
- `Track:` feeds `select_level_track_texture_set`
- `Track:r` randomizes across the non-random track sets and changes backdrop handling
- `Garbage:` becomes a normalized `0..1` runtime scalar used by `populate_track_runtime_entities`
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

## Salt, Slug, and Ring Dispatch

High-confidence findings:

- `salt.x` is cloned into a `40`-slot runtime array and managed separately from slugs
- slugs use an `8`-slot pool and a different runtime path
- authored `R` rows map onto ring-effect helpers through the packed ring bits
- `Ring=None` suppresses the helper
- `Ring=Normal` and `Ring=PowerUp` land on the ring particle family
- `Ring=Explode` lands on the explode particle family
- `Ring=Slow` lands on the slow particle family

## Runtime Flags

Confirmed authored-to-runtime lanes:

- `Parcel` -> runtime low-byte `0x01` plus `0x4000`
- `NoFall` -> runtime `0x100`
- `JetPack=Off` -> runtime `0x8000`

Important caveat:

- `0x8000` is seeded by authored `JetPack=Off`, but later visual normalization also reuses that lane
- path attachments use different low-byte lanes, so they should not be flattened together with `JetPack=Off`
- the rewrite should keep `Parcel`, `NoFall`, `JetPack=Off`, and path attachments as distinct authored concepts

## Render Pipeline

The post-build renderer uses explicit cache buckets:

- `Floor`
- `Slide`
- `Warn`
- `Ramp`
- `Fringe`

Those passes reuse runtime flags and helper families, so not every runtime bit should be interpreted as pure authored gameplay metadata.
