# Runtime Structures

This page collects the high-confidence runtime layouts that currently matter most for the movement, attachment, and row-event work.

The goal is not to freeze a final class hierarchy. It is to keep the recovered offsets in one place so Binary Ninja typing, Frida captures, and the Zig rewrite can all refer to the same names.

## Player

The current high-confidence `Player` fields are:

- `+0x68`: `position`
- `+0x98`: `cached_track_pair_cell_a`
- `+0x9c`: `cached_track_pair_cell_b`
- `+0x120`: `movement_state`
- `+0x1e8`: `row_event_id`
- `+0x1ec`: `row_event_state`
- `+0x1f0`: `row_event_timer`
- `+0x1f8`: `row_event_data_a`
- `+0x1fc`: `row_event_data_b`
- `+0x308`: `movement_flag_selector`
- `+0x338`: `movement_flags`
- `+0x33c`: `previous_movement_flags`
- `+0x380`: `player_slot`
  - used as the player index passed to hit-effect dispatch in `handle_subgoldy_collisions`
  - not the visible life counter
- `+0x384`: `follow_state`
- `+0x3c4`: `damage_gauge`
  - inline `DamageGaugeController`
- `+0x408`: `game`
- `+0x40c`: `movement_mode_selector`
- `+0x410`: `velocity`
- `+0x41d`: `attachment_exit_pending`
- `+0x424`: `attachment_exit_anchor_z`
- `+0x42c`: `post_follow_value_a`
- `+0x430`: `post_follow_value_b`
- `+0x434`: `attachment_exit_progress`
- `+0x438`: `attachment_exit_progress_step`
- `+0x43c`: `current_cell`
- `+0x44c`: `follow_effect_gate_a`
- `+0x44d`: `follow_effect_gate_b`
- `+0x2730`: `movement_progress`
- `+0x2734`: `movement_rate_scalar`
- `+0x273c`: `track_z_offset`
- `+0x2740`: `track_z_anchor`
- `+0x2750`: `jetpack_gauge`
  - inline `JetpackGaugeController`
- `+0x4340`: `visible_life_stock`
  - seeded to `3` by `populate_runtime_track_cells_from_segments` before `initialize_subgoldy`
  - incremented by `add_subgoldy_score` on each `50,000` score bucket, capped at `9`
  - decremented by `update_subgoldy_resurrect` on the respawn branch

Important caveat:

- the real `Player` object is larger than the currently typed prefix
- the movement-emitter and visual-state blocks around `player + 0x2984` and beyond are still only partially named
- the Windows build keeps contact damage and jetpack countdown as two separate inline controllers:
  - `player + 0x3c4` is the contact or hazard accumulator
  - `player + 0x2750` is the jetpack warning or auto-shutoff controller

## Damage Gauge Controller

The inline controller at `player + 0x3c4` is now typed as `DamageGaugeController`.

High-confidence current fields:

- `+0x00`: `state`
- `+0x10`: `transition_progress`
- `+0x14`: `transition_step`
- `+0x18`: `transition_counter`
- `+0x1c`: `fill`
- `+0x20`: `display_fill`
- `+0x24`: `hold_progress`
- `+0x28`: `hold_step`

Current practical read:

- `handle_subgoldy_collisions` feeds this controller through `apply_damage_gauge_delta(&player->damage_gauge, delta, force)`
- `update_subgoldy` ticks it every frame through `update_damage_gauge(&player->damage_gauge)`
- the currently recovered deltas line up with collision branches:
  - salt or hazard contact `+0.15`
  - ambient hazard path `+0.02`
  - garbage `+0.04`
  - slug `+1.0`
  - health pickup `-0.5`

## Jetpack Gauge Controller

The inline controller at `player + 0x2750` is now typed as `JetpackGaugeController`.

High-confidence current fields:

- `+0x00`: `progress`
- `+0x04`: `cycle_phase`
- `+0x08`: `cycle_phase_step`
- `+0x0c`: `state`
- `+0x10`: `warning_anchor`
- `+0x14`: `wobble_x`
- `+0x18`: `wobble_y`
- `+0x1c`: `wobble_alpha`
- `+0x200`: `game`
- `+0x210`: `warning_intensity`

Current practical read:

- `initialize_jetpack_gauge` zeros the controller, sets the cycle phase to `1/600`, and seeds the runtime and warning-anchor pointers
- `arm_jetpack_gauge` transitions `state` from idle to active and clears the wobble outputs
- `update_jetpack_gauge` advances `progress`, emits the near-expiry warning curve around `0.94`, and forces shutoff when the current runtime cell carries flag `0x80`
- `update_subgoldy` consumes the wobble outputs and active state from this controller immediately after the per-frame update

## Movement Visual State Controller

The block rooted at `player + 0x2984` now has a stable enough behavioral shape to document, even though the full struct layout is still incomplete.

High-confidence current read:

- `update_player_movement_flags` feeds this block through `update_movement_visual_state_controller` at `0x445920`
- the controller resolves one `movement_flags` mask into three channel states
- those three channels live at offsets:
  - `+0x64c`
  - `+0xa28`
  - `+0xe04`
- each channel keeps its current selected state at:
  - `+0x750`
  - `+0xb2c`
  - `+0xf08`

The transition helpers at `dispatch_cutscene_animation` (`0x444600`) and `0x4446e0` appear to be near-identical queue or start routines over adjacent channel structs:

- when their third argument is non-zero, they immediately begin a selected state
- when their third argument is zero, they append the requested state id to a small queued-transition list
- both helpers read per-state records from pointer tables whose entries are selected by `state_id << 7`

Practical interpretation:

- this is not the same system as the 12 movement-flag emitter slots updated at `player + 0x450`
- the `+0x2984` block is a second layer that looks more like a queued visual-state or presentation controller
- the same queue or start pattern also appears in the global jetpack-related controller rooted at `data_4df904 + 0x432700`, via helper `0x445860`

## Game

The current high-confidence `Game` fields are:

- `+0x38`: `track_center_x`
- `+0x40`: `level_mode`
- `+0x44`: `level_mode_arg`
- `+0x4c`: `runtime_flags`
- `+0xa854`: `track_state_latch`
- `+0xa874`: `row_event_limit`
- `+0x355e64`: `jetpack_pickup`
  - one-slot `TrackPickupRuntime`
- `+0x356000`: `health_pickups`
  - `8`-slot `TrackPickupRuntime` array
- `+0x3563a0`: `slug_hazards`
  - `8`-slot `SlugHazardRuntime` array in Windows
- `+0x359140`: `active_garbage_hazards`
  - head pointer for the active garbage list
- `+0x359144`: `garbage_hazards`
  - `50`-slot `GarbageHazardRuntime` array
- `+0xff25d0`: `replay_active`
- `+0xff25d4`: `replay_track`
- `+0xff25d8`: `replay_track_index`
- `+0xff25dc`: `runtime_track_index`

Current practical read:

- `build_subgame_level` embeds the live `SubGoldy` actor at `game + 0x3bb7a4`, and `initialize_subgoldy` writes the back-pointer from `player + 0x408` into that owning gameplay object
- `build_subgame_level -> rebuild_track_runtime_from_segments -> populate_runtime_track_cells_from_segments` seeds `player + 0x4340` to `3` before `initialize_subgoldy` runs
- the main gameplay collision consumers now line up with the spawn helpers:
  - `spawn_track_health_pickup` and `handle_subgoldy_collisions` use the `health_pickups` array
  - `spawn_track_jetpack_pickup` uses the separate `jetpack_pickup` slot
  - `spawn_track_garbage_hazard` pushes slots into the `active_garbage_hazards` list over the `garbage_hazards` pool
  - `spawn_slug_hazard` and `handle_subgoldy_collisions` use the `slug_hazards` array
- `runtime_track_index` is the per-tick cursor advanced by `update_subgoldy`
- the same cursor also drives the replay-track reads in that function
- `replay_track_index` remains a separate tracked scalar and should not be merged with the live cursor without more evidence
- one nearby single-slot pickup-like block around `game + 0x355e08` is still unresolved and should not be merged with `jetpack_pickup` yet

## Track Pickup Runtime

The health and jetpack pickup spawners now line up on one shared runtime slot shape.

High-confidence current fields:

- `+0x10`: `world_position`
- `+0x38`: `state`
- `+0x3c`: `owner`
- `+0x64`: `sprite`
- `+0x68`: `source_cell`
- `+0x6c`: `parity_offset`

Current practical read:

- `spawn_track_health_pickup` populates `health_pickups[i]`
- `spawn_track_jetpack_pickup` populates the single `jetpack_pickup` slot
- both helpers lift the spawn point above the authored floor height, attach a sprite using `player->player_slot`, and store the source runtime cell
- Android `cRSubGame::AddHealth` and `cRSubGame::AddJetPack` confirm the same field meanings even though later ports rearrange surrounding storage

## Garbage Hazard Runtime

The Windows garbage hazard pool is now typed as `GarbageHazardRuntime`.

High-confidence current fields:

- `+0x50`: `scale`
- `+0x68`: `world_position`
- `+0x80`: `next_active`
- `+0x84`: `state`
- `+0x88`: `collision_side`
- `+0xb4`: `sprite`
- `+0xb8`: `source_cell`
- `+0xc0`: `owner`

Current practical read:

- `spawn_track_garbage_hazard` allocates from the `50`-slot pool and threads the slot into `active_garbage_hazards`
- `handle_subgoldy_collisions` walks that active list directly
- on collision, the slot flips to state `2`, records the left or right impact side in `collision_side`, and contributes the recovered `+0.04` gauge delta
- Android `cRSubGame::AddGarbage` confirms the same random scale and active-list pattern, but Windows remains authoritative on the exact storage layout

## Slug Hazard Runtime

The Windows slug hazard pool is now typed as `SlugHazardRuntime`.

High-confidence current fields:

- `+0x68`: `world_position`
- `+0x80`: `state`
- `+0x8c`: `velocity`
- `+0xac`: `sprite`
- `+0xb0`: `source_cell`

Current practical read:

- `spawn_slug_hazard` allocates from the `8`-slot Windows pool, projects the spawn onto attachments, and seeds forward velocity from `track_center_x`
- `handle_subgoldy_collisions` reads the same slots back through the `slug_hazards` array
- later Android and iOS ports still use the same semantic fields, but at least one later build expands the slug capacity beyond the Windows `8`-slot pool

## Attachment Template Samples

The path-template typing is now firm enough to name the sampled point records explicitly.

High-confidence `PathTemplate` fields:

- `+0x44`: `sample_count`
- `+0x58`: `primary_points`
- `+0x5c`: `secondary_points`
- `+0x98`: `row_scalar_a`
- `+0x9c`: `row_scalar_b`
- `+0xa0`: `row_scalar_c`
- `+0xa4`: `row_scalar_d`

High-confidence `PathTemplateSample` fields:

- `+0x30`: `position`
- `+0x80`: `delta`
- `+0x8c`: `delta_length`
- `+0x90`: `orientation_a`
- `+0x94`: `orientation_b`
- `+0x98`: `orientation_c`
- `+0x9c`: `scalar_9c`
- `+0xa0`: `scalar_a0`

This matches the recovered follow-state update behavior:

- `sample_count` bounds the active sample index
- the current sample `delta_length` scales the per-tick path factor
- `position` and `delta` feed the interpolated output pose
- `scalar_a0` is the field currently consumed by the ride-height smoothing branch in `update_subgoldy`

## Binary Ninja Note

These names are now safe to use when reading or extending the current Binary Ninja database.

One local tooling caveat remains:

- the current `bn decompile` output does not always rewrite post-hoc struct-growth sites away from raw `__offset(...)` expressions, even after a manual analysis refresh
- `bn types show Player`, `bn types show Game`, and `bn types show PathTemplate` are therefore the authoritative typed layouts for now
