# Track quad tables (BOD banks) and the post-build render passes

Recovered 2026-06-10 from `initialize_game_assets_and_world` @ 0x40acf0 plus the
four post-build passes. This unblocks the three deliberately-empty port lanes in
`zig/src/track.zig` / `track_render.zig` (fringe promotion, seam harmonize,
corner edge variants).

## Root-owned BOD catalog

The constructor and the asset initializer jointly prove that `GameRoot+0x44100`
is one contiguous array of 352 56-byte `BodBase` records. It ends exactly at
the root-owned `DirectXLoader` at `GameRoot+0x48E00`.

| record indices | `GameRoot` range | recovered owner/role |
|---|---|---|
| 0 | `+0x44100` | universe hole quad |
| 1..4 | `+0x44138..+0x44217` | unknown; no role assigned yet |
| 5..8 | `+0x44218..+0x442F7` | floor corner bank |
| 9..12 | `+0x442F8..+0x443D7` | warning corner bank |
| 13..16 | `+0x443D8..+0x444B7` | slide corner bank |
| 17 | `+0x444B8` | trampoline mesh |
| 18..21 | `+0x444F0..+0x445CF` | unknown; no role assigned yet |
| 22..29 | `+0x445D0..+0x4478F` | eight pillar meshes |
| 30..37 | `+0x44790..+0x4494F` | floor slice bank |
| 38..45 | `+0x44950..+0x44B0F` | warning slice bank |
| 46..53 | `+0x44B10..+0x44CCF` | slide slice bank |
| 54..56 | `+0x44CD0..+0x44D77` | ramp edge quads (-1, 0, +1) |
| 57 | `+0x44D78` | lazer object model |
| 58..345 | `+0x44DB0..+0x48CAF` | complete 8x4x3x3 track-fringe catalog |
| 346..350 | `+0x48CB0..+0x48DC7` | unknown; no role assigned yet |
| 351 | `+0x48DC8` | salt hazard mesh (`salt.x`) |

The source projection is `RootBodCatalog`; unknown ranges stay opaque until a
producer or consumer establishes their ownership.

## The three quad banks

`initialize_game_assets_and_world` builds three parallel banks of 56-byte BOD
slots inside `Game` (slot base; the inner object pointer lives at slot+36):

| bank | texture | corner slots (4) | slice slots (8) |
|---|---|---|---|
| floor | `Objects/World00/Track0.tga` | `game+0x44218` (ptrs @ +0x4423C) | `game+0x44790` (ptrs @ +0x447B4) |
| warn | `Objects/World00/TrackWarn.tga` | `game+0x442F8` (ptrs @ +0x4431C) | `game+0x44950` (ptrs @ +0x44974) |
| slide | `Objects/World00/Slide0.tga` | `game+0x443D8` (ptrs @ +0x443FC) | `game+0x44B10` (ptrs @ +0x44B34) |

- The initializer calls authored corner ids 0, 1, 2, 3 in that order, but
  stores them at physical indices 0, 1, **3, 2**. Consumers therefore use the
  explicit authored-id-to-storage-index mapping in `RootBodCatalog`.
- Slice slots are `initialize_backdrop_slice_quad(ptr, texture, i)` for
  `i = 0..7`. `populate` only ever assigns slice 0; slices 1..7 are the
  longer run-strip variants installed later by `merge_track_tile_runs`.
- The `World00` texture names are rewritten per world by the level texture-set
  selector; bank addresses are stable.

## Initial cell quads (populate, glyph switch)

Every runtime cell's quad slot is `cell+36`. Per glyph family `populate`
assigns a fixed object (game dword index × 4 = byte offset):

- floor family → Track0 slice 0 (`dword 70125` = +0x447B4)
- slide family → Slide0 slice 0 (`dword 70349` = +0x44B34)
- trampoline → `Tramp.x` mesh (`BodBase` @ +0x444B8, object @ +0x444DC)
- pillar family → first pillar mesh (`BodBase` @ +0x445D0, object @ +0x445F4)
- hole → universe hole quad (`BodBase` @ +0x44100, object @ +0x44124)
- ramp edges → raised-edge -1 / 0 / +1 quads (objects @ +0x44CF4,
  +0x44D2C, and +0x44D64)
- object cells (flag 2) → per-object bank `game dwords 74635 + 47*object_id`

## Pass 1: select_track_tile_edge_variants @ 0x435a80

For tiles not in {0, 35, 28, 29, 30, 14}: build an open-neighbor mask
(left=8, right=4, behind=1, ahead=2 — using `is_sub_loc_empty`
on the 4 neighbors, with grid borders counting as open). On exact corner
masks, set cell flag 0x8000 and install a corner quad:

| mask | open dirs | corner id |
|---|---|---|
| 9 | left+behind | 0 |
| 5 | right+behind | 1 |
| 6 | right+ahead | 2 |
| 0xA | left+ahead | 3 |

Bank choice: tiles {1, 20, 21, 27, 33, 34} take the **Track0** corner; any
other tile except {22, 14, ramp family} takes the **Slide0** corner.

## Pass 2: harmonize_center_lane_floor_slide_variants @ 0x4356f0

Runs only on rows where `row % 8 == 3` (look ahead one row) or `row % 8 == 5`
(look behind one row), every lane, skipping cells with flag 0x20:

- floor-family cell next to a slide-family neighbor (or neighbor tile 30 for
  the ahead case / 32 for the behind case): if the cell quad is Track0
  slice 0, swap to Slide0 slice 0; any Track0 corner swaps to the same-index
  Slide0 corner. Set flag 0x40.
- slide-family cell next to a floor-family neighbor: the mirror swap
  (Slide0 → Track0), flag 0x40.

This is the seam-alignment pass the port stubbed out in
`buildRenderCacheSurfaceSwapGrid`; the "two recovered replacement tables"
are the Track0 and Slide0 corner banks.

## Pass 3: merge_track_tile_runs @ 0x435180

Collapses repeated same-family quad runs into the longer slice variants
(slices 1..7 = strip lengths). Skips cells with flag 0x8000 (corner variant)
or 0x40 (seam-swapped). Pre-pass ORs 0x6000 into every cell's flag dword.
Floor-family runs select `floor_slices[run_length - 1]`; slide-family runs
select `slide_slices[run_length - 1]`. Tile-0x0e runs use the matching
`pillar[run_length - 1]` mesh, while empty/tile-0x23 cells in level mode 2 use
the universe-hole object.

## Pass 4: promote_track_tiles_to_fringe_variants @ 0x4355f0

For every cell whose **next-row** cell is open-neighbor family: if the cell
quad equals Track0 slice i or Slide0 slice i (any i in 0..7), replace it with
**TrackWarn slice i** and set flag 0x20. This is the striped gap-warning
floor; it only fires on cells still carrying a plain floor/slide quad, which
is the eligibility predicate the port was missing
(`buildRenderCacheWarnSurfaceGrid`).

## Port consequences

- The port can model the whole system without BOD pointers: track a per-cell
  `(bank, kind, index)` triple (bank ∈ {floor, warn, slide}, kind ∈
  {slice, corner}, index 0..7 / 0..3) seeded by glyph family, then run the
  four passes in the native `rebuild_track_runtime_from_segments` order
  (0x437de0): edge variants → warn promotion → seam harmonize → run merge,
  followed by warning zones, fringe objects, and the render caches. The
  skip-flag chain depends on this order: promote sets 0x20 which harmonize
  skips; harmonize sets 0x40 which merge skips.
- Flag bits on the cell flag dword: 0x20 = warn-promoted, 0x40 = seam-swap,
  0x8000 = corner variant, 0x6000 = merge pre-pass mark.
- `TrackWarn.tga` (and its per-world siblings) is the texture for the
  promoted quads; the port already loads per-world texture sets.
