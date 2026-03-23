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
- `+0x42c`: `attachment_exit_value_a`
  - neutral placeholder label; the native meaning of this exit-side lane is still unresolved
- `+0x430`: `attachment_exit_value_b`
  - neutral placeholder label; the native meaning of this exit-side lane is still unresolved
- `+0x434`: `attachment_exit_progress`
- `+0x438`: `attachment_exit_progress_step`
- `+0x43c`: `current_cell`
- `+0x440`: `completion_handoff_active`
- `+0x444`: `completion_handoff_timer`
- `+0x448`: `completion_handoff_timer_step`
- `+0x44c`: `attachment_exit_gate_a`
- `+0x44d`: `attachment_exit_gate_b`
- `+0x44e`: `completion_handoff_voice_gate`
- `+0x16cc`: `snail_hotspots_local`
  - `19`-entry `Vec3` array
- `+0x17b0`: `snail_hotspots_world`
  - `19`-entry `Vec3` array
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

Current practical read for the hotspot bank:

- `build_snail_hotspots` seeds `snail_hotspots_local` from the snail model's named hotpoint textures
- the recovered authored hotspot names include:
  - index `12`: `X/CameraSkidStop.tga`
  - index `17`: `X/CameraSlugDeath`
  - index `18`: `X/CameraIntroTalk`
- `update_snail_skin` transforms that `19`-entry local bank into `snail_hotspots_world`
  - slots `0..10` use the cached matrix at `player + 0x1684`
  - slots `11..18` use the cached matrix at `player + 0x1604`
- the earlier standalone cutscene-anchor reads at `+0x1840` and `+0x1888` are `snail_hotspots_world[12]` (`CameraSkidStop`) and `snail_hotspots_world[18]` (`CameraIntroTalk`)
- `update_cutscene` keeps reorienting the live intro camera around hotspot `18`, uses the `12 -> 18` lerp with the recovered sinusoidal x-offset in completion state `6`, and keeps the fixed completion/death look-at legs on hotspot `18`
- hotspot `17` (`CameraSlugDeath`) is a real transformed hotspot, but no direct runtime consumer for it was recovered in this pass
- the exact gameplay roles of the two source matrices, and the reason later cutscene legs keep reusing the authored `CameraIntroTalk` hotspot, are still unresolved

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
- `+0x04`: `pulse_progress`
- `+0x08`: `pulse_step`
- `+0x0c`: unknown byte gate
- `+0x10`: `warning_transition_progress`
- `+0x14`: `warning_transition_step`
- `+0x18`: `skin_hold_ticks`
- `+0x1c`: `fill`
- `+0x20`: `display_fill`
- `+0x24`: `hit_flash_progress`
- `+0x28`: `hit_flash_step`

Current practical read:

- `handle_subgoldy_collisions` feeds this controller through `apply_damage_gauge_delta(&player->damage_gauge, delta, force)`
- `update_subgoldy` ticks it every frame through `update_damage_gauge(&player->damage_gauge)`
- the controller owns a separate warning actor through `start_warning` / `update_warning` / `stop_warning`
- the currently recovered deltas line up with collision branches:
  - ambient hazard path `+0.02`
  - salt contact `+0.02`
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
- `update_jetpack_gauge` advances `progress`, emits the near-expiry warning curve around `0.94`, shuts off the `JETPACKTHRUST` visual lane once the warning band begins, and forces shutoff when the current runtime cell carries flag `0x80`
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
- that separate jetpack-side controller keeps its selected state at `player + 0x12e4`
  - `0` = no thrust presentation
  - `4` = active thrust presentation
  - activation uses `set_weapon_animation(..., 1, ..., 4)` followed by a queued `0`
  - deactivation at the `0.94` warning edge uses `set_weapon_animation(..., 1, 1, 8)` followed by a queued `-1`
- the recovered asset family for that controller is `JETPACKTHRUST`; the still-missing piece is the separate `cRSubHover::Jets` nozzle-particle owner

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
- `+0x125e480`: `track_parcels`
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
  - `attachment_exit_value_a` from `follow_state.orientation_b`
  - `attachment_exit_value_b` from `follow_state.template_record->row_scalar_a` or zero
  - `attachment_exit_pending = 1`
  - `attachment_exit_progress = 0`
  - `attachment_exit_gate_a = 0`
  - `attachment_exit_gate_b = 0`
- `update_subgoldy` uses those exit-side latches as threshold gates inside fall handling, not as the final death selector:
  - once `attachment_exit_progress > 0.7`, `attachment_exit_gate_a` gates a one-shot voice trigger and, when `player + 0x2d8 == 0`, a cutscene animation at `world_y < -6`
  - `attachment_exit_gate_b` gates a later one-shot voice trigger at `world_y < -7`
  - the separate death handoff remains the older `world_y < -7 && death_active == 0` path that calls `initialize_subgoldy_death`
- `update_subgoldy` also owns a separate completion handoff block:
  - once the player reaches the course-end threshold at `game + 0x58` and no attachment-exit handoff is pending, it arms `completion_handoff_active = 1`
  - it seeds `completion_handoff_timer = 0`, `completion_handoff_timer_step = 1/60`, and `completion_handoff_voice_gate = 0`
  - cutscene state `6` initializes the completion screen almost immediately, on the first handoff tick after arming
  - while active, it clamps the forward presentation offsets (`track_z_offset` / `track_z_anchor`) to the fixed completion lane and advances the timer every tick
  - after `2.0` seconds, `completion_handoff_voice_gate` gates a one-shot voice event `8`
  - after `5.0` seconds, the same block begins the frontend fade, flushes `row_event_display` if needed, and routes through `complete_subgame`
  - when `level_mode == 0` and `level_mode_arg == *(data_4df904 + 0x12d4644) - 1`, that completion block calls `complete_subgame(game, 1)`, writes `app + 0x1bc = 0x1d`, and sets `app + 0x1b8 = 0x1a`
  - the other completion exits write `game + 0x1270fc8 = 1`, then:
    - force `app + 0x1b8 = 0x1a` and `app + 0x1bc = 2` when `level_mode == 7`
    - otherwise copy the current outer owner into `app + 0x1bc` and set `app + 0x1b8 = 0x1a` when `selected_level_record_persistent != 0`
    - otherwise copy the current outer owner into `app + 0x1bc` and set `app + 0x1b8 = 0x1b`
- `update_subgoldy_resurrect` now has one stronger bridge-side read:
  - the respawn branch copies the current outer owner from `app + 0x1b8` into `app + 0x1bc`, then writes `app + 0x1b8 = 0x1c`
  - respawn therefore uses the same outer `26/27/28` rebuild slot as the other handoffs instead of a special gameplay-only reload lane
  - the final-loss branch first writes `game + 0x1270fc8 = 2`, then calls `complete_subgame(game, 1)`
  - when `selected_level_record_persistent != 0`, that final-loss leg copies the current outer owner into `app + 0x1bc` and sets `app + 0x1b8 = 0x1a`
  - when `selected_level_record_persistent == 0`, the same leg still copies the current owner into `app + 0x1bc`, then:
    - sets `app + 0x1b8 = 0x1b` for non-postal modes
    - sets `app + 0x1b8 = 0x1b` for postal mode when app byte `+0x30d` is non-zero
    - otherwise forces `app + 0x1b8 = 0x1a` and overwrites `app + 0x1bc = 2`
- the app byte at `+0x30d` is now narrowed:
  - `add_arcade_high_score` and `add_survival_high_score` both set it to `1` while arming active state `20`
  - `destroy_high_score_screen` clears it back to `0`
  - `update_completion_screen` also branches on it before tearing down the completion screen
  - current best read: it is a high-score-entry / high-score-screen continuation flag, not a generic gameplay mode byte
- `update_galaxy` and `update_challenge_setup_screen` both seed `selected_level_record_active = 1` and populate `selected_level_record` before returning to `update_subgame` state `1`
  - the current static launchers do not show a matching write to `selected_level_record_persistent`
- `set_subgame_features`, `populate_runtime_track_cells_from_segments`, and `build_subgame_level` all consume `selected_level_record_active` or `selected_level_record_persistent` to override the live course metadata from that record
- `initialize_subgame` also reads `selected_level_record_persistent` to restore the saved replay-speed scalar before the first mode controller reset
- `destroy_subgame` clears `selected_level_record_persistent` and writes `app + 0x1bc = 0x12` on that teardown path
- `update_subgame` clears `selected_level_record_active` when the persistent lane is absent on state `0`, and later re-arms `selected_level_record_active = (selected_level_record_persistent == 1)` on rebuild state `7`
- the writer for `selected_level_record_persistent` is still unresolved; current static evidence only confirms that it is a separate lifecycle lane, not that frontend selected-record launches set it directly
- `game + 0x12727d8` is the gameplay row-event display controller, not a loose flag cluster:
  - `initialize_subgoldy` clears `row_event_display.state`
  - `destroy_subgame` and the completion leg in `update_subgoldy` both flush it through `flush_row_event_display`
  - `register_parcel_delivery`, `update_row_event_display`, and `flush_row_event_display` recover the controller's parcel-count, bonus, and state fields
  - the old `game + 0x12727f0` byte now sits inside `row_event_display + 0x18` and remains an unresolved controller gate, but its one recovered gameplay read is now narrower: when it is `1` and the current runtime cell carries flag `0x40`, `update_subgoldy` fast-forwards `completion_handoff_timer` to `5.1`
- the main gameplay collision consumers now line up with the spawn helpers:
  - `initialize_track_parcel_slots`, `spawn_track_parcel`, `place_parcels_on_track`, `place_challenge_parcels_on_track`, and `handle_subgoldy_collisions` all share `parcel_target_count` and the `track_parcels` array
  - `spawn_track_health_pickup` and `handle_subgoldy_collisions` use the `health_pickups` array
  - `spawn_track_jetpack_pickup` uses the separate `jetpack_pickup` slot
  - `spawn_track_garbage_hazard` pushes slots into the `active_garbage_hazards` list over the `garbage_hazards` pool
  - `spawn_slug_hazard` and `handle_subgoldy_collisions` use the `slug_hazards` array
- the embedded `track_parcels` slots are the same runtime family allocated by the Windows `cRSubGame::AddParcel` path and remain separate only from the garbage runtime seeded at `game + 0x359144`
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

The placed parcel pickups now line up on a dedicated embedded runtime slot shape rooted at `game + 0x125e480`.

High-confidence current fields:

- `+0x10`: `world_position`
- `+0x38`: `state`
- `+0x3c`: `game`
- `+0x54`: `sprite`
- `+0x5c`: `bob_phase`
- `+0x60`: `bob_phase_step`
- `+0x64`: `owner`
- `+0x68`: `progress`
- `+0x6c`: `progress_step`
- `+0x70`: `target_distance`
- `+0x74`: `travel_dir_x`
- `+0x78`: `travel_dir_y`
- `+0x7c`: `travel_dir_z`
- `+0x80`: `delivery_offset_x`
- `+0x84`: `delivery_offset_y`
- `+0x88`: `delivery_offset_z`

Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds the `50`-slot array with `initialize_track_parcel_runtime`
- `build_subgame_level` clears the live array for the current run through `initialize_track_parcel_slots`
- `spawn_track_parcel` is the Windows `cRSubGame::AddParcel` path: it allocates one free slot from `game->track_parcels`, seeds the spawn position, installs the sprite, and stores the parcel-owner pointer
- `update_track_parcel` runs the parcel's bobbing, homing, and final delivery arc, then calls `register_parcel_delivery(&parcel->game->row_event_display)` before killing the sprite and clearing the slot state
- `place_parcels_on_track` and `place_challenge_parcels_on_track` decide how many authored parcel rows stay live and feed the HUD-facing `parcel_target_count`
- `handle_subgoldy_collisions` reads the same slots back, awards the parcel score tier, and flips collected slots from state `1` to state `4`
- these slots are the gameplay parcel runtime behind `cRSubGame::AddParcel`, not a separate manager path from it

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
- health seeds a parity-based `phase_offset` (`0.0` on odd `z`, `0.5` on even `z`) plus a `1/60` phase step, and `update_track_health_pickup` applies the native sprite-only bob `base_y + (sin(phase * tau) + 1.0) * 0.3`
- jetpack seeds the same source-cell/parity lane but also applies the native ramp-side lateral bias at spawn time:
  - `+0.5` when `edge_mask & 7 == 3` and neighbor tiles `(lane - 1, lane + 2)` are both `0x0e`
  - `-0.5` when `edge_mask & 7 == 4` and neighbor tiles `(lane - 2, lane + 1)` are both `0x0e`
- `handle_subgoldy_collisions` reads the same runtime slots back with pickup-specific gates:
  - health: `player_world_y >= 0.49`, `delta_z < 1.0`, `abs(delta_y) < 0.4`, normalized distance `< 0.98`
  - jetpack: `player_world_y >= 0.49`, `delta_z < 1.0`, normalized distance `< 3.0`
- health collection also triggers `health_collect_particles`, which allocates `8` `SMOKE.TGA` sprites (`sprite id 128`) with:
  - radial world-axis velocity `sin/cos(i * pi / 4) * 0.015`
  - forward carry `player_motion_z * 0.4`
  - full motion carry `player_motion_xyz * 3.0`
  - sprite size `0.1 x 0.5`, tint `(1.0, 0.75, 0.75, 1.0)`, and a small downward acceleration `-0.0002`
- Android `cRSubGame::AddHealth` and `cRSubGame::AddJetPack` confirm the same field meanings even though later ports rearrange surrounding storage

## Track Ring / Special-Effect Runtime

The authored ring and special-effect pickups line up on a dedicated `2`-slot runtime bank rooted at `game + 0x35b78c`.

High-confidence current fields:

- `+0x10`: `world_position`
- `+0x38`: `state`
- `+0x3c`: `owner`
- `+0x40`: `kind`
- `+0x44`: `movement_flag_selector_snapshot`
- `+0x19c`: `phase`
- `+0x1a0`: `phase_step`

Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds both slots through `initialize_track_ring_or_special_effect_runtime`
- `update_subgame` dispatches authored `0x23` ring rows plus the ramp families `0x02..0x0a` into `spawn_track_ring_or_special_effect`
- `spawn_track_ring_or_special_effect` seeds the slot kind, owner selector snapshot, world position, and the child particle family (`ParticleRing`, `ParticleExplode`, `ParticleSlow`)
- `handle_subgoldy_collisions` reads the same runtime slots back with the shared ring gate:
  - `delta_z < 1.0`
  - normalized distance `< 0.98`
- on hit, the slot does not die immediately: `handle_subgoldy_collisions` flips it into the shared post-hit lane, and the slot's `update_subgoldy_bullet` vtable advances the recovered `2 -> 3` follow/collapse animation before teardown
- the same vtable also owns the missed-pickup `4 -> 5` expand-and-teardown lane keyed from `movement_flag_selector_snapshot`
- the collision switch owns the ring-kind ladder:
  - `1` -> score + `PW1`
  - `2/6` -> score + `EXPLODERING` + `initialize_nuke`
  - `3/7` -> negative motion-lane impulse + `SLOWRING`
  - `4/5` -> optional voice + weapon-selector increment + `PW1..PW7`
  - `8` -> weapon-selector increment + `PW1..PW7`
- the current Zig runner now mirrors the live runtime-slot collision owner and that ring-kind ladder, but the exact original ring bod anchor/layout fields behind `spawn_track_ring_or_special_effect` are still only approximated from the runtime target row/lane

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
