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
- `+0x44c`: `attachment_exit_gate_a`
- `+0x44d`: `attachment_exit_gate_b`
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
- `+0x1b01e0`: `parcel_target_count`
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
- `+0x125e430`: `track_parcels`
  - `50`-slot `TrackParcelRuntime` array
- `+0x12727d8`: `row_event_display`
  - inline `RowEventDisplayController`
- `+0xff25d0`: `selected_level_record_active`
- `+0xff25d1`: `selected_level_record_persistent`
- `+0xff25d4`: `selected_level_record`
- `+0xff25d8`: `replay_track_index`
- `+0xff25dc`: `runtime_track_index`

Current practical read:

- `build_subgame_level` embeds the live `SubGoldy` actor at `game + 0x3bb7a4`, and `initialize_subgoldy` writes the back-pointer from `player + 0x408` into that owning gameplay object
- `build_subgame_level -> rebuild_track_runtime_from_segments -> populate_runtime_track_cells_from_segments` seeds `player + 0x4340` to `3` before `initialize_subgoldy` runs
- `initialize_subgoldy_fall_state` seeds the attachment-exit handoff:
  - `post_follow_value_a` from `follow_state.orientation_b`
  - `post_follow_value_b` from `follow_state.template_record->row_scalar_a` or zero
  - `attachment_exit_pending = 1`
  - `attachment_exit_progress = 0`
  - `attachment_exit_gate_a = 0`
  - `attachment_exit_gate_b = 0`
- `update_subgoldy` uses those exit-side latches as threshold gates inside fall handling, not as the final death selector:
  - once `attachment_exit_progress > 0.7`, `attachment_exit_gate_a` gates a one-shot voice trigger and, when `player + 0x2d8 == 0`, a cutscene animation at `world_y < -6`
  - `attachment_exit_gate_b` gates a later one-shot voice trigger at `world_y < -7`
  - the separate death handoff remains the older `world_y < -7 && death_active == 0` path that calls `initialize_subgoldy_death`
- `update_galaxy` and `update_challenge_setup_screen` both seed `selected_level_record_active = 1` and populate `selected_level_record` before returning to `update_subgame` state `1`
- `set_subgame_features`, `populate_runtime_track_cells_from_segments`, and `build_subgame_level` all consume `selected_level_record_active` or `selected_level_record_persistent` to override the live course metadata from that record
- `update_subgame` clears `selected_level_record_persistent` on front-end entry and later re-arms `selected_level_record_active = (selected_level_record_persistent == 1)` on rebuild state `7`
- `game + 0x12727d8` is the gameplay row-event display controller, not a loose flag cluster:
  - `initialize_subgoldy` clears `row_event_display.state`
  - `destroy_subgame` and the completion leg in `update_subgoldy` both flush it through `flush_row_event_display`
  - `register_parcel_delivery`, `update_row_event_display`, and `flush_row_event_display` recover the controller's parcel-count, bonus, and state fields
  - the old `game + 0x12727f0` byte now sits inside `row_event_display + 0x18` and remains an unresolved controller gate
- the main gameplay collision consumers now line up with the spawn helpers:
  - `place_parcels_on_track`, `place_challenge_parcels_on_track`, and `handle_subgoldy_collisions` share `parcel_target_count` and the `track_parcels` array
  - `spawn_track_health_pickup` and `handle_subgoldy_collisions` use the `health_pickups` array
  - `spawn_track_jetpack_pickup` uses the separate `jetpack_pickup` slot
  - `spawn_track_garbage_hazard` pushes slots into the `active_garbage_hazards` list over the `garbage_hazards` pool
  - `spawn_slug_hazard` and `handle_subgoldy_collisions` use the `slug_hazards` array
- the embedded `track_parcels` slots are not the same object family as either the parcel-manager path behind `cRSubGame::AddParcel` or the separate garbage runtime seeded at `game + 0x359144`
- `runtime_track_index` is the per-tick cursor advanced by `update_subgoldy`
- the same cursor also drives the replay-track reads in that function
- the scalar at `+0xff25d8` remains separate from `selected_level_record` and should not be merged with the live cursor without more evidence
- one nearby single-slot pickup-like block around `game + 0x355e08` is still unresolved and should not be merged with `jetpack_pickup` yet

## Row Event Display Controller

The inline controller at `game + 0x12727d8` is now typed as `RowEventDisplayController`.

High-confidence current fields:

- `+0x14`: `state`
- `+0x1c`: `parcel_target_count`
- `+0x20`: `bonus_enabled`
- `+0x24`: `staged_parcel_count`
- `+0x28`: `delivered_parcel_count`
- `+0x2c`: `progress`
- `+0x30`: `progress_step`
- `+0x34`: `widget_world_x`
- `+0x38`: `widget_world_y`
- `+0x3c`: `widget_world_z`
- `+0x40`: `bonus_blink_progress`
- `+0x44`: `bonus_blink_step`
- `+0x48`: `bonus_score`
- `+0x4c`: `display_token`

Current practical read:

- `update_row_event_display` drives the controller state machine and the staged parcel-widget reveal path
- `register_parcel_delivery` increments `delivered_parcel_count`, awards the parcel score tier, applies the optional final bonus, and sets `state = 3`
- `flush_row_event_display` fast-forwards the remaining parcel payout, destroys the owned widgets, copies `display_token` into the global presentation slot, and clears `state`
- the byte at `+0x18` still contains the old `game + 0x12727f0` gate and should stay unnamed until its exact gameplay meaning is recovered

## Track Parcel Runtime

The placed parcel pickups now line up on a dedicated embedded runtime slot shape rather than a raw offset block.
 
 High-confidence current fields:
 
 - `+0x60`: `world_position`
 - `+0x88`: `state`
 
Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds a `50`-slot Windows array with `sub_408860`
- `place_parcels_on_track` and `place_challenge_parcels_on_track` decide how many authored parcel rows stay live and feed the HUD-facing `parcel_target_count`
- `handle_subgoldy_collisions` reads the same slots back, awards the parcel score tier, and flips collected slots from state `1` to state `4`
- Android and iOS confirm the gameplay semantics through `cRSubGame::AddParcel`, and that parcel-manager family should not be merged with the separate garbage-object runtime at `game + 0x359144`

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

The Windows garbage hazard pool is now typed as `GarbageHazardRuntime`, and the earlier parcel labels on `0x408550`, `0x43f130`, and `0x43f200` were a bad read of this same family.

High-confidence current fields:

- `+0x50`: `scale`
- `+0x68`: `world_position`
- `+0x80`: `next_active`
- `+0x84`: `state`
- `+0x88`: `collision_side`
- `+0x8c`: `game`
- `+0x90`: `velocity`
- `+0xa0`: `sprite_y_offset`
- `+0xac`: `smoke_timer`
- `+0xb0`: `smoke_timer_step`
- `+0xb4`: `sprite`
- `+0xb8`: `source_cell`
- `+0xc0`: `owner`

Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds the `50`-slot pool with `initialize_garbage_hazard`
- `spawn_track_garbage_hazard` allocates from that pool and threads the slot into `active_garbage_hazards`
- `handle_subgoldy_collisions` walks that active list directly
- on collision, the slot flips to state `2`, records the left or right impact side in `collision_side`, and contributes the recovered `+0.04` gauge delta
- `update_garbage_hazard` matches Android and iOS `cRSubGarbage::AI()`: after collision, the slot bursts outward with randomized velocity, emits periodic smoke, and self-destructs when it falls below the track or behind the player
- `destroy_garbage_hazard` matches Android `cRSubGarbage::Kill()` and unlinks the same `next_active` chain rooted at `game + 0x359140`
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

- `+0x38`: `kind`
- `+0x3c`: `is_mirrored_x`
- `+0x40`: `side_exit_mode`
- `+0x44`: `segment_count`
- `+0x4c`: `segment_count_f`
- `+0x54`: `width_cells`
- `+0x58`: `primary_points`
- `+0x5c`: `secondary_points`
- `+0x98`: `installed_heading_delta`
- `+0x9c`: `special_runtime_cell_swaps`

Still unresolved from the current Windows package:

- whether `+0xa0/+0xa4` are template fields at all in the special live-update branch
- the exact producer that sets `special_runtime_cell_swaps`

High-confidence `PathTemplateSample` fields:

- `+0x00`: `basis_right`
- `+0x10`: `basis_up`
- `+0x20`: `basis_forward`
- `+0x30`: `position`
- `+0x80`: `delta_dir_to_next`
- `+0x8c`: `delta_length`
- `+0x90`: `center_x`
- `+0x94`: `rotation_scalar_94`
- `+0x98`: `rotation_scalar_98`
- `+0x9c`: `lateral_scale`
- `+0xa0`: `warp_phase`

This matches the recovered follow-state update behavior:

- `segment_count` bounds the active sample index
- the current sample `delta_length` scales the per-tick path factor
- `position` and `delta_dir_to_next` feed the interpolated output pose
- `warp_phase` is the field consumed by the special nonlinear kind-`42` / `WARP`-like branch

## Current Zig Port Attachment Types

The Zig port now has its own attachment-side types that are worth keeping distinct from the Windows layouts above.

These are implementation shapes, not recovered Windows structs:

- [`attachment_builders.TemplateSample`](../../zig/src/attachment_builders.zig)
  - Zig-side sampled point record used by the builder scaffold
- [`attachment_builders.Template`](../../zig/src/attachment_builders.zig)
  - Zig-side public-family template with width, sample count, exit-tail extra, and the sample array
- [`attachment_builders.BuiltAttachment`](../../zig/src/attachment_builders.zig)
  - one authored row plus its built Zig-side template
- [`attachment_builders.Scaffold`](../../zig/src/attachment_builders.zig)
  - current preview-owned authored-row registry, built templates, and first installed-row map
- `AttachmentFollowState` in [`gameplay.zig`](../../zig/src/gameplay.zig)
  - current gameplay-side follow state carrying source row, progress, exit overshoot, lateral offset, cached output lane center, vertical offset, and cached output position
- `LaunchState` in [`gameplay.zig`](../../zig/src/gameplay.zig)
  - current gameplay-side post-attachment launch state used by `SUPERTRAMP` and elevated exits

Current practical split:

- the RE docs above describe the Windows runtime structures
- the Zig types above describe the current port-side scaffold that now builds, renders, and follows public attachment families without yet claiming the exact Windows installed-bank layout

## Binary Ninja Note

These names are now safe to use when reading or extending the current Binary Ninja database.

One local tooling caveat remains:

- the current `bn decompile` output does not always rewrite post-hoc struct-growth sites away from raw `__offset(...)` expressions, even after a manual analysis refresh
- `bn types show Player`, `bn types show Game`, and `bn types show PathTemplate` are therefore the authoritative typed layouts for now
