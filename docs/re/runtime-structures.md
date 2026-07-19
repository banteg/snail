# Runtime Structures

This page collects the high-confidence runtime layouts that currently matter most for the movement, attachment, and row-event work.

The goal is not to freeze a final class hierarchy. It is to keep the recovered offsets in one place so Binary Ninja typing, Frida captures, and the Zig rewrite can all refer to the same names.

## Player

The current high-confidence `Player` fields are:

- `+0x38`: `live_matrix`
  - `+0x68`: `live_matrix.position`
- `+0x80`: `resurrect_final_loss`
- `+0x84`: `resurrect_active`
- `+0x8c`: `resurrect_progress`
- `+0x90`: `resurrect_progress_step`
- `+0x98`: `ghost_sprite_a`
- `+0x9c`: `ghost_sprite_b`
- `+0xa0`: exact 0xac-byte `click_start` child (`cRClickStart`)
  - child `+0x80` / Player `+0x120`: `state`, the complete observed
    `ClickStartState` graph: `INACTIVE (0)`, deliberately unresolved
    `UNKNOWN_1 (1)`, `WAITING_FOR_START (2)`, `START_PENDING (3)`, and
    `TEARDOWN (4)`
  - `WAITING_FOR_START` is the suspended-drive/start-gate state consumed by both `update_subgoldy` and `update_subgame`: it leaves the player actor active, but suppresses selected-record replay sample application, lateral steering interpolation, forward velocity, movement-fire/slow-commentary gates, timer advance, and generated garbage/salt hazard spawns
  - the current Zig port maps this shape to the post-attachment launch envelope (`LaunchState.active`) rather than treating it as a standalone hazard flag
  - child `+0x84`: prompt widget
  - child `+0x88/+0x8c`: teardown progress and step
  - child `+0x98`: borrowed containing `Player*`
  - child `+0xa8` / Player `+0x148`: `hide_prompt`, cleared by the intro cutscene handoff
- `+0x14c`: `row_event_cutscene_started`
- `+0x150`: `nuke`
  - exact 0x7c-byte authored `cRNuke` collision-ring owner
- `+0x1cc`: `movement_sound_variant_sample`
- `+0x1d0`: exact empty one-byte `firework` child (`cRFireWork`)
  - `firework_shoot` does not read instance state, but Windows callers still pass this embedded receiver through `ecx`
- `+0x1d4`: `damage_retrigger_timer`
- `+0x1d8`: `damage_retrigger_step`
- `+0x1dc`: `surface_reaction_timer`
- `+0x1e0`: `surface_reaction_step`
- `+0x1e8`: `row_event`
  - inline `PlayerRowEventState`
- `+0x2d8`: `control_override_active`
- `+0x2dc`: `cutscene_pitch_cycle`
- `+0x2e0`: `cutscene_pitch_cycle_step`
- `+0x308`: `movement_flag_selector`
- `+0x338`: `movement_flags`
- `+0x33c`: `previous_movement_flags`
- `+0x374`: `nuke_effect_progress`
- `+0x378`: `nuke_effect_progress_step`
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
- `+0x42c`: `post_follow_exit_roll`
  - runtime-confirmed camera carryover input during the pending post-follow window
- `+0x430`: `post_follow_heading_carryover`
  - raw installed-heading bits copied from the follow template; downstream consumer still unresolved
- `+0x434`: `attachment_exit_progress`
- `+0x438`: `attachment_exit_progress_step`
- `+0x43c`: `control_source`
- `+0x440`: `completion_handoff_active`
- `+0x444`: `completion_handoff_timer`
- `+0x448`: `completion_handoff_timer_step`
- `+0x44c`: `attachment_exit_gate_a`
- `+0x44d`: `attachment_exit_gate_b`
- `+0x44e`: `completion_handoff_voice_gate`
- `+0x2730`: `movement_fire_progress`
- `+0x2734`: `movement_fire_progress_step`
- `+0x273c`: `track_z_offset`
- `+0x2740`: `track_z_anchor`
- `+0x2744`: `completion_handoff_cycle_progress`
- `+0x2748`: `completion_handoff_cycle_step`
- `+0x2750`: exact 0x214-byte `sub_hover` child (`cRSubHover`)
- `+0x2980`: `interaction_max_z`
  - per-player collision and pickup ceiling
- `+0x2984`: `presentation`
  - inline exact 0x19b4-byte `Snail` (`cRSnail`)
- `+0x29a8`: `presentation.visual_root`
  - current live snail visual root
- `+0x2964`: `cached_camera_target_world`
  - world-space camera anchor consumed by `update_cameraman`
- `+0x42dc`: `presentation.cutscene` (authored `cRCutScene`)
- `+0x4340`: `visible_life_stock`
  - seeded to `3` by `populate_runtime_track_cells_from_segments` before `initialize_subgoldy`
  - incremented by `add_subgoldy_score` on each `50,000` score bucket, capped at `9`
  - decremented by `update_subgoldy_resurrect` on the respawn branch

`add_subgoldy_score` writes six per-event score buckets at `+0x310..+0x324`
before updating total score at `+0x2e4`:

| Event | Offset | Native label | Points |
| --- | --- | --- | --- |
| `0` | `+0x310` | `Garbage` | `10` |
| `1` | `+0x314` | `Slug` | `500` |
| `2` | `+0x318` | `Ring` | `100` |
| `3` | `+0x31c` | `Parcel Collect` | `100` |
| `4` | `+0x320` | `Parcel Deliver` | `100` |
| `5` | `+0x324` | `Bonus` | caller-supplied |

Current practical read for the hotspot bank:

- `build_snail_hotspots` seeds `snail_hotspots_local` from the snail model's named hotpoint textures
- the recovered authored hotspot names include:
  - index `12`: `X/CameraSkidStop.tga`
  - index `17`: `X/CameraSlugDeath`
  - index `18`: `X/CameraIntroTalk`
- `update_snail_skin` transforms that `19`-entry local bank into `snail_hotspots_world`
  - slots `0..10` use `presentation + 0x1684` (`snail_hotspot_source_matrix_b`)
  - slots `11..18` use `presentation + 0x1604` (`snail_hotspot_source_matrix_a`)
- the earlier standalone cutscene-anchor reads at `+0x1840` and `+0x1888` are `snail_hotspots_world[12]` (`CameraSkidStop`) and `snail_hotspots_world[18]` (`CameraIntroTalk`)
- `update_cutscene` keeps reorienting the live intro camera around hotspot `18`, uses the `12 -> 18` lerp with the recovered sinusoidal x-offset in completion state `6`, and keeps the fixed completion/death look-at legs on hotspot `18`
- hotspot `17` (`CameraSlugDeath`) is a real transformed hotspot, but no direct runtime consumer for it was recovered in this pass
- the exact gameplay roles of the two source matrices, and the reason later cutscene legs keep reusing the authored `CameraIntroTalk` hotspot, are still unresolved

Two `update_subgoldy` corrections from the latest static audit:

- `player + 0x43c` is not the current runtime track cell. The live cell remains a transient local from `get_track_grid_cell_at_world_position(...)`; the persistent player field is a per-player `control_source` pointer used by the uncaptured-cursor and transition lanes.
- the currently safe `control_source` sub-slice is:
  - `+0x04`: `control_flags_a`
  - `+0x0c`: `control_flags_b`
  - `+0x28`: `steering_x`
  - the recovered shared bit on both flag dwords is `0x4000` (`PLAYER_CONTROL_FLAG_CONFIRM`)
- `player + 0x2970` is now the current safe `steering_mode_selector`
  - `update_subgoldy` uses it to index the uncaptured-cursor sensitivity table
  - when the selector is `1`, the same block copies `control_source->steering_x` directly into the live `track_z_offset` lane instead of preserving the anchored delta
- `player + 0x2984` is the inline exact 0x19b4-byte `Snail` (`cRSnail`)
  - `+0x04`: inherited BOD `list_flags`
  - `+0x24`: borrowed animated `Object* object`
  - `+0x38`: `live_matrix`
  - `+0x78`: borrowed `render_animation_manager` pointing to the owned manager
    at `+0x104` while the linked Object has generated animation
  - `+0x80`: `previous_live_matrix`
  - `+0x100`: `owner_player`
  - `+0x104`: inline `anim_manager`
    - `+0x00`: `state`
    - `+0x04`: `progress`
    - `+0x08`: `progress_step`
    - `+0x0c`: borrowed `ObjectAnimation* active_animation`
    - `+0x10`: completion latch
    - `+0x14`: `queued_animations[10]`
    - `+0x3c`: `queue_count`
    - `+0x40`: borrowed `RenderableBod* target_model` backlink
    - `+0x44`: borrowed `PresentationAnimationSlot* animation_slots`
  - `+0x14c`: ten owned 0x80-byte cutscene animation donor slots
  - `+0x64c`: `weapon_channels[3]`, three consecutive exact `0x3dc`-byte
    authored `cRWeapon` owners at `+0x64c/+0xa28/+0xe04`
    - `+0x04`: inherited BOD `list_flags`
    - `+0x24`: borrowed animated `Object* object`
    - `+0x38`: `live_matrix`
    - `+0x78`: borrowed `render_animation_manager` pointing to the owned
      manager at `+0x108`
    - `+0x104`: `selected_state`
    - `+0x108`: inline `anim_manager`
    - `+0x150`: five owned 0x80-byte animation donor slots
    - `+0x3d0`: `release_step`
  - `+0x11e0`: `jetpack_channel`, a fourth exact `cRWeapon` owner used for
    the jetpack base/draw animation slots
  - `+0x15bc`: `wobble`
    - `+0x00`: `roll_phase`
    - `+0x04`: `roll_phase_step`
    - `+0x08`: `lift_phase`
    - `+0x0c`: `lift_phase_step`
    - `initialize_cutscene` seeds the two phase-step pairs before the intro wobble branches
  - `+0x15cc`: owned `snail_hotspot_source_body`
    - inherited transform at `+0x1604` (`snail_hotspot_source_matrix_a`)
  - `+0x164c`: owned `snail_hotspot_body`
    - inherited transform at `+0x1684` (`snail_hotspot_source_matrix_b`)
  - `+0x16cc`: `snail_hotspots_local`
    - `19`-entry `Vec3` array
  - `+0x17b0`: `snail_hotspots_world`
    - `19`-entry `Vec3` array
  - `+0x1894`: `invincible_shell`
    - exact 0xa4-byte authored `cRInvincible` visual owner
    - `+0x28`: shell color
    - `+0x38`: live shell transform
    - `+0x80`: `state`, a complete `InvincibleState` graph:
      `INACTIVE (0) -> FADING_IN (1) -> ACTIVE (2) -> FADING_OUT (3)`;
      reactivation while fading out returns directly to `FADING_IN`
    - `+0x84`: `spin_phase`
    - `+0x88`: `spin_phase_step`
    - `+0x8c`: `fade_progress`
    - `+0x90`: `fade_step`
    - `+0x98/+0x9c`: cutscene roll progress/step
    - `+0xa0`: animation-channel release-step gate
    - `initialize_invincible_shell`, `start_invincible_shell`, and `update_invincible_shell` all operate on this same embedded controller
  - `+0x1938`: exact 0x20-byte `snail_skin` (`cRSnailSkin`)
    - `+0x00`: `selected_slot`
    - `+0x04`: `slot_ids[3]`
    - `+0x10`: borrowed `Snail* owner_snail` parent backlink
    - `+0x14`: `active`
    - `+0x18`: `progress`
    - `+0x1c`: `progress_step`
    - `initialize_snail_skin` seeds the parent backlink and clears the timed skin-swap state
    - `update_snail_skin_transition` follows `owner_snail->object`, raises
      object flag `0x8`, writes the selected material index, and advances the
      timer lanes
    - raw code at `0x4428ef` confirms `initialize_cutscene` passes `presentation + 0x1938` directly to `update_snail_skin_transition`; there is no separate `weapon_release_active` byte ahead of this state
  - `+0x1958`: exact 0x5c-byte `cutscene` (`cRCutScene`)
    - `+0x00/+0x04`: presentation and Player backlinks
    - `+0x08`: `camera_mode`; Windows only writes `1` or `-1`, so the value
      semantics remain intentionally unnamed
    - `+0x0c`: complete observed `CutSceneState` graph:
      - intro: `INTRO_PENDING (1) -> INTRO_ACTIVE (2) ->
        INTRO_RETURN_BLEND (8) -> INTRO_FINISH (9) -> INACTIVE (0)`
      - completion: `COMPLETION_PENDING (5) -> COMPLETION_BLEND (6) ->
        COMPLETION_HOLD (7)`
      - death: `DEATH_PENDING (10) -> DEATH_BLEND (11) -> DEATH_HOLD (12)`
      - states `3` and `4` have no producer or handler in the Windows image and
        are deliberately left unassigned
    - `+0x10`: live camera matrix
    - `+0x50/+0x54`: progress and progress step
    - `+0x58`: force-camera-update gate
    - the owner ends at `+0x5c`; the following `Player +0x4338` word is
      `parcels_collected`, not CutScene tail storage
    - `initialize_cutscene_ai` and `update_cutscene` own this controller;
      `initialize_subgoldy`, `update_subgoldy`, and collision handling enter its
      intro, completion, and death families through the same embedded field
- `player + 0x435c/+0x4360` is the current safe slow-commentary timer pair
  - `slow_commentary_timer`
  - `slow_commentary_step`
  - `initialize_subgoldy` seeds the step to `1/60`
  - `update_subgoldy` resets the timer outside the narrow slow-movement band and triggers the native slow commentary once the timer exceeds `1.0`
- `data_4df904 + 0x432700` is the embedded `Snail` itself, not a separate
  global jetpack controller
  - that Snail owns `Weapon jetpack_channel` at `+0x11e0`
  - `set_snail_jetpack` mutates `jetpack_channel.selected_state` and routes
    the visible thrust lane through the authored
    `cRWeapon::SetAnimation(int, bool, int)` member
- `player + 0x29a8` is `player->presentation.visual_root`, not a standalone sibling field
  - the currently safe `SnailVisual` sub-slice is:
    - `+0x10`: `flags`
    - `+0x80`: `follow_lateral_response`
    - `+0x84`: `squidge_primary`
    - `+0x88`: `squidge_secondary`
- `player + 0x4344` is the real inline 0x18-byte `Squidge` (`cRSquidge`) consumed by `update_subgoldy` and copied into `player->presentation.visual_root`
  - the stable Windows harness name `initialize_score_stats` is actually `cRSquidge::Init`; the real score buckets are independently stored at `player + 0x310`
- `start_squidge_z` is a `void` helper, like `start_squidge_y`
  - the old float-return prototype was a decompiler artifact
  - forcing that float return into IDA was the direct cause of the `update_subgoldy` inline-asm regression; reverting it to `void` restores a normal high-level decompile
  - `+0x00`: `y_output`
  - `+0x04`: `y_velocity`
  - `+0x08`: `y_phase`
  - `+0x0c`: `z_output`
  - `+0x10`: `z_velocity`
  - `+0x14`: `z_phase`
  - helper constants recovered from `update_squidge`: phase spring `0.15000001`,
    damping `0.81999999`, and terminal epsilon `0.001`
- `player + 0x150` is the exact 0x7c-byte authored `cRNuke` owner
  - `+0x00`: `state`, the complete `NukeState` graph:
    `INACTIVE (0) -> ACTIVE (1) -> INACTIVE`
  - `+0x04`: `owner_player`
  - `+0x08`: `orbit_center_z_step`
  - `+0x0c`: `orbit_center_z`
  - `+0x10`: `orbit_phase`
  - `+0x14`: `orbit_phase_step`
  - `+0x18`: `sprite_slots[25]`
  - `handle_subgoldy_collisions` arms it through `initialize_nuke`
  - `update_subgoldy` either advances it through `update_nuke` or tears it down through `uninit_nuke`
  - `initialize_nuke` seeds `orbit_center_z = owner_player->position.z - 5.0`, `orbit_center_z_step = subgame_rate * 2`, `orbit_phase = 0`, and `orbit_phase_step = 0.10471976`
  - `update_nuke` advances 25 sprites around the active axis with `sin/cos(index * 0.04 * tau + orbit_phase) * 7.0`; each sprite uses the native `3.0 x 3.0` size lanes
  - `update_subgoldy` owns the lifetime gate through `player + 0x374/+0x378`, refreshing the step as `subgame_rate * 0.022222223` and tearing the controller down once progress exceeds `1.0`
- `player + 0x14c` is the one-shot `row_event_cutscene_started` latch
  - `initialize_subgoldy` clears it on run start
  - `update_subgoldy` flips it the first time the row-event tip path dispatches the one-shot cutscene animation
- `player + 0x1cc..+0x1e0` is a non-row-event movement and reaction slice
  - `+0x00`: `movement_sound_variant_sample`
    - `play_movement_state_sound` stores the sampled movement-sound variant here before deriving the emitted sound id
  - `+0x08`: `damage_retrigger_timer`
  - `+0x0c`: `damage_retrigger_step`
    - `handle_subgoldy_collisions` seeds the timer from the step, and `update_subgoldy` advances and clears it past the terminal threshold
  - `+0x10`: `surface_reaction_timer`
  - `+0x14`: `surface_reaction_step`
    - `update_subgoldy` uses this second pair for a separate terrain or surface reaction cadence
  - `+0x04` and `+0x18` remain intentionally unresolved in this pass
- `player + 0x1e8` is a real inline `PlayerRowEventState`
  - `+0x00`: `id`
  - `+0x04`: inline `tip_definition.flags`
  - `+0x08`: `tip_definition.layout_y`
  - `+0x0c`: `tip_definition.text_scale`
  - `+0x10`: `tip_definition.dismiss_seconds`
  - `+0x14`: `tip_definition.text`
  - `update_subgoldy` seeds that tail as a small tip payload and passes `&player->row_event.tip_definition` to `enqueue_tip_message`; it is not a standalone row-event controller suffix
- `player + 0x2d8` is a broader `control_override_active` gate than the earlier cutscene-only guess
  - it suppresses several normal control and attachment branches in `update_subgoldy`
  - `initialize_cutscene` also reads it to decide whether to auto-dispatch the default idle animation
- `player + 0x2dc/+0x2e0` form the current safe cutscene-side cycle pair
  - `cutscene_pitch_cycle`
  - `cutscene_pitch_cycle_step`
  - `initialize_cutscene` advances them before rotating the player-owned cutscene frame around world X
- `player + 0x328/+0x32c` is the current safe barrier-hold timer pair
  - `barrier_hold_progress`
  - `barrier_hold_step`
  - `initialize_subgoldy` seeds the step to `1/60`
  - `update_subgoldy` advances it only while the sampled runtime tile is `0x0e`
    and `live_matrix.position.y < 6.5`; that branch zeroes forward velocity,
    snaps z to `floor(z + 0.49) - 0.5`, and calls `begin_post_follow_carryover`
    once progress crosses `1.0`
- `player + 0x330/+0x334` is the current safe startup-voice timer pair
  - `startup_voice_timer`
  - `startup_voice_step`
  - `initialize_subgoldy` seeds both lanes to `0.055555552`; the broader caller-side voice gating is still unresolved, so only the timer pair is named here
- `player + 0x350..+0x370` is now a typed camera-presentation slice
  - `+0x00`: `lane_lean_state`
  - `+0x04`: `lane_lean_amplitude`
  - `+0x08`: `lane_lean_progress`
  - `+0x0c`: `lane_lean_progress_step`
  - `+0x10`: `timer_360_state`
  - `+0x14`: unresolved dword
  - `+0x18`: `timer_360_progress`
  - `+0x1c`: `timer_360_step`
  - `+0x20`: `heading_roll`
  - `update_subgoldy` arms the `lane_lean_*` triplet on specific tile families, advances `lane_lean_progress` by `lane_lean_progress_step`, and clears the state once the progress lane exceeds `1.0`
  - it independently advances the offset-named `timer_360_*` window and clears
    its state once progress exceeds `1.0`; no stronger role name is asserted yet
  - `update_cameraman` consumes `lane_lean_amplitude`, `lane_lean_progress`, and `heading_roll` directly when building the live camera roll
  - `update_track_attachment_follow_state` also accumulates `installed_heading_delta` into `heading_roll`, matching the same live lane the port already mirrors

Important caveat:

- the real `Player` object is larger than the currently typed prefix
- the movement-emitter and visual-state blocks around `player + 0x2984` and beyond are still only partially named
- the Windows build keeps contact damage and jetpack countdown as two separate inline controllers:
  - `player + 0x3c4` is the contact or hazard accumulator
  - `player + 0x2750` is the jetpack warning or auto-shutoff controller

## Cameraman State

The current high-confidence `Cameraman` owner is:

- `+0x00`: `live_matrix`
- `+0x40`: `desired_matrix`
- `+0x80`: `previous_desired_matrix`
- `+0xc0`: `player`
- `+0xc4`: `game`
- `+0xc8`: `fov_degrees`
- `+0xcc`: `force_camera_update`
- `+0xd0`: `attachment_lift_envelope`
- `+0xd4`: `smoothed_attachment_lift_envelope`

Current practical read:

- `initialize_cameraman` wires the shared `player` and `game` pointers, clears the three live matrices, zeroes the attachment lift envelopes, and seeds `fov_degrees` to `110.0`
- `update_cameraman` builds `desired_matrix` from `player->cached_camera_target_world`, attachment and movement-side lift inputs, then interpolates `live_matrix` between `previous_desired_matrix` and `desired_matrix`
- the current tracked IDA camera slice is now typed from the checked-in header, so the decompile uses `live_matrix`, `desired_matrix`, and `cached_camera_target_world` directly instead of raw matrix blocks and `player + 0x2964` float indexing

The outer `cRSubGame::CameraAI()` path copies `force_camera_update` into
`SubgameRuntime::camera_snap_requested`, matching the parallel
`CutScene::force_camera_update` handoff. Several player-side attachment and
presentation inputs consumed by `update_cameraman` are still only partially
typed.

## Damage Gauge Controller

The inline exact `0x2c`-byte controller at `player + 0x3c4` is the authored
`cRDamageGuage` owner; the shipped class and texture names preserve that
spelling.

High-confidence current fields:

- `+0x00`: `state`, a complete `DamageGuageState` graph:
  `MONITORING (0) -> WARNING_TRANSITION (1) -> DRAINING (2) -> MONITORING`
- `+0x04`: `pulse_progress`
- `+0x08`: `pulse_step`
- `+0x0c`: unresolved write-only byte; Windows and Android `Init` clear it,
  but no live consumer currently proves a semantic name
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
- the adjacent authored `cRProgressBar` is an empty one-byte owner at
  `player + 0x3f0`; its exact `AI` ignores `this`, but typed callsites and the
  mobile class names preserve ownership while both decompilers now expose its
  player-z and subgame-row inputs through `GameRoot`
- the controller drives the exact `0x10`-byte authored `cRWarning` at
  `player + 0x3f4` through `start_warning` / `update_warning` / `stop_warning`
  - `WarningState` is a complete three-state graph: `INACTIVE (0)`,
    `OPAQUE (1)`, and `FADING (2)`
  - `start_warning` seeds the fading phase at `1.0`, forcing the next update to
    wrap into opaque and play sample 50; opaque then advances back into the
    fading/zero-hold half-cycle until `stop_warning` returns it to inactive
  - the paired narrow replay guards this exact owner in both databases: all six
    lifecycle methods are `void __thiscall(Warning*)`, IDA now renders the
    state/phase/border fields directly, and the receiver-free Windows
    `StopSample` body remains a member because the mobile ports retain that edge
- `apply_damage_gauge_delta` ignores unforced positive damage while
  `state == DAMAGE_GUAGE_STATE_DRAINING`; the draining auto-decay path is the
  forced caller
- `apply_damage_gauge_delta` also ignores all unforced deltas while the sign bit
  of `Game+0x4300b4` is set, and ignores unforced negative draining deltas while
  `Game+0x42ff60 == 1`
- `update_damage_gauge` reads several game-global gates:
  - `Game+0x74621` is the global `pause_gate` consumed by controller math and `update_warning`
  - `Game+0x430199` and `Game+0x4301bc` block fresh full-gauge startup from
    `MONITORING`
  - `Game+0x4301bc` also fast-forwards `WARNING_TRANSITION` and applies an
    extra unforced `-0.0066666668` drain while `DRAINING`
  - `Game+0x42fde8 == 0.49f` gates entry into `DRAINING` and its fill-zero exit
  - `Game+0x4301c0 > 0`, `Game+0x42fe08 > 0`, or `Game+0x434064 != 0` also
    return `DRAINING` to `MONITORING`
- the currently recovered deltas line up with collision branches:
  - ambient hazard path `+0.02`
  - salt contact `+0.15`
  - garbage `+0.04`
  - slug `+1.0`
  - health pickup `-0.5`

## SubHover

The exact 0x214-byte authored `cRSubHover` child at `Player +0x2750` is now
typed as `SubHover`, distinct from both the `cRJetPack` pickup singleton and
the `cRDamageGuage` contact-damage owner.

High-confidence current fields:

- `+0x00`: `progress`
- `+0x04`: `progress_step`
- `+0x08`: unresolved padding
- `+0x0c`: `state`, the complete `SubHoverState` graph:
  `INACTIVE (0) -> ACTIVE (1) -> INACTIVE`
- `+0x10`: `player`
- `+0x14`: `wobble_x`
- `+0x18`: `wobble_y`
- `+0x1c`: `wobble_alpha`
- `+0x20`: `particle_slots[30]`
- `+0x200`: `game`
- `+0x20c`: `warning_intensity_latch`
- `+0x210`: `warning_intensity`

Current practical read:

- `initialize_jetpack_gauge` zeros the controller, sets the progress step to `1/600`, and seeds the runtime and owning-player pointers
- `arm_jetpack_gauge` transitions `state` from `INACTIVE` to `ACTIVE` and clears the wobble outputs
- `update_jetpack_gauge` advances `progress`, emits the near-expiry warning curve around `0.94`, shuts off the `JETPACKTHRUST` visual lane once the warning band begins, and forces shutoff when the current runtime cell carries flag `0x80`
- `initialize_jet_particles`, `update_jet_particles`, and `uninit_jet_particles` operate on the same controller; the `+0x20` block is a fixed `30`-entry sprite-slot bank used by the hover thrust particles
  - cross-port authored names are `cRSubHover::JetInit`, `Jets`, and `JetUnInit`
  - the Zig port now mirrors this as a persistent `15 x 2` nozzle bank instead of respawning generic smoke every frame
  - `update_jet_particles` rolls `random_back_seed = next_math_random_value() * 0.0000015258789 + 0.40000001` and `random_width_seed = next_math_random_value() * 0.0000015258789 + 0.12` once per bank update
  - at trail index `14`, each side rolls `next_math_random_value() * 0.000030517578 > 0.89999998`; success allocates one detached smoke sprite at that trail-tip position, size `0.1 x 0.3`, carrying `Player.velocity * 0.85` and the sprite `+0x78` lane `0.001`
  - the Zig port maps that detached smoke sprite into the generic effect pool, so the native sprite-manager lifetime is still approximated rather than owned by a literal sprite slot
- `update_subgoldy` also reads `state` from `player + 0x275c`; when that lane is `1`, the late `0x43ce23 -> 0x43ce75` branch retires `attachment_exit_pending` before the `attachment_exit_progress` / gate-A block
- `update_subgoldy` consumes the wobble outputs and active state from this controller immediately after the per-frame update
- the final no-op call from `update_jetpack_gauge` uses the same Windows address
  as `spawn_track_speedup`, but its receiver/arguments are
  `SubHover*`, `Vector3*`, and `float`; Android's separate literal no-op
  `cRSubHover::Hover(tVector&, float)` proves the folded authored alias

## Weapon Presentation Owners

The block rooted at `player + 0x2984` is the exact authored `cRSnail` owner.
Its weapon presentation is not a flat state controller: the Snail owns three
consecutive `cRWeapon` instances plus a fourth jetpack instance.

High-confidence current read:

- `update_player_movement_flags` feeds the authored
  `cRSnail::SetWeapon(int)` member (`set_snail_weapon` at `0x445920`)
- `SetWeapon` resolves one `movement_flags` mask into three Weapon states
- the three `Weapon` owners live at Snail offsets:
  - `+0x64c`
  - `+0xa28`
  - `+0xe04`
- each Weapon keeps its current selected state at:
  - `+0x750`
  - `+0xb2c`
  - `+0xf08`

The paired queue/start helpers operate at two different ownership levels:

- `dispatch_cutscene_animation` (`0x444600`) is
  `cRSnail::SetAnimation(int, bool, int)` over the Snail root, its root
  `AnimManager`, and ten owned animation slots
- `set_weapon_animation` (`0x4446e0`) is
  `cRWeapon::SetAnimation(int, bool, int)` over one Weapon, its inline
  `AnimManager`, and five owned animation slots

- when their third argument is non-zero, they immediately begin a selected state
- when their third argument is zero, they append the requested state id to a small queued-transition list
- both helpers select `0x80`-byte owned renderable slots with
  `state_id << 7`, then borrow each slot's linked `Object::animation`

Practical interpretation:

- this is not the same system as the 12 movement-flag emitter slots updated at `player + 0x450`
- the `+0x2984` block is one embedded Snail, not a second anonymous visual
  controller
- the jetpack lane is `Snail::jetpack_channel` at `+0x11e0`; it is not a
  separate global controller
- that Weapon keeps its selected state at Snail `+0x12e4`
  - `0` = no thrust presentation
  - `4` = active thrust presentation
  - activation uses `set_weapon_animation(..., 1, ..., 4)` followed by a queued `0`
  - deactivation at the `0.94` warning edge uses `set_weapon_animation(..., 1, 1, 8)` followed by a queued `-1`
- the recovered asset family for that controller is `JETPACKTHRUST`; the separate `cRSubHover::Jets` nozzle-particle owner is now represented in Zig as the persistent bank above, including native-scaled width/back-offset jitter and the recovered trail-tip detached puff allocation branch

## SubgameRuntime

The current high-confidence `SubgameRuntime` fields are:

`initialize_subgame @ 0x4374b0` closes the receiver identity: Windows, the
exact matcher, and the cross-port `cRSubGame::Init()` symbol all describe the
same `0x1272838`-byte gameplay aggregate. The older Binary Ninja `Game` type
was a separate named-type identity with the same extent, not a second owner.
Once the receiver is bound to `SubgameRuntime`, the initializer exposes the
embedded runtime-cell grid, high-score banks, HUD handles, player backlink,
GUI, galaxy, completion, and times-up owners directly. `Game` remains useful
only as historical decompiler spelling in older evidence.

- `+0x34`: `challenge_difficulty_scalar`
- `+0x38`: `track_center_x`
- `+0x40`: `level_mode`
- `+0x44`: `level_mode_arg`
- `+0x48`: `base_subgame_rate`
- `+0x4c`: `runtime_flags`, the game-wide `SubgameRuntimeFlag` course-feature
  word; it is distinct from authored/runtime row flags, and its proved bit
  consumers and native mode presets are cataloged in `track-runtime.md`
- `+0xa854`: `track_state_latch`
- `+0xa858`: `tutorial`
  - inline `TutorialController`
- `+0xa874..+0x1b01ec`: `level_definition`
  - complete `0x1a5978` active `SubTracks` owner, cross-port `cRSubTracks`
  - `+0x1b0138`: `level_length`
  - `+0x1b013c`: `level_random`
  - `+0x1b01e0`: `parcel_target_count`
- `+0x1b01ec..+0x355b64`: `level_definition_scratch`
  - second complete `SubTracks` owner used for startup enumeration and built-ins
  - second complete `0x1a5978` owner used for startup level enumeration and
    then reseeded from the built-in segment table
  - the built-in handoff is the void `cRSubTracks::Init(cRSubSegmentRaw**)`
    family: Windows consumes a pointer table of static `0x48` `SubSegmentRaw`
    records and copies their eight glyph rows into inline `SubSegment`s; the
    raw `+0x24` lane is a separate marker-row pointer whose 31 live strings
    each contain one `*`, while the preceding six metadata dwords remain
    semantically unassigned because this Windows member never reads them
- `+0x355b64..+0x355d94`: ten embedded `BodBase` group heads
  - `+0x355b64`: fringe objects and row attachment bodies
  - `+0x355b9c`: ordinary track bodies plus start/completion banners
  - `+0x355bd4`: tutorial barrier plus live sub-lazers
  - `+0x355c0c`: live salt hazards
  - `+0x355cb4`: tile 29/30 special track bodies
  - the other five constructed group roles remain unknown on Windows
- `+0x355db0`: `speedup_pickup`
  - exact `0xb4`-byte authored `cRSubSpeedUp` singleton
- `+0x355e64`: `jetpack_pickup`
  - exact `0x19c`-byte `cRJetPack` singleton
  - two complete embedded `0x94`-byte `cRVapour` children at `+0x74` and
    `+0x108`; each retains the real output `cRObject*` at child `+0x24`
- `+0x356000`: `health_pickups`
  - eight inline exact `0x74`-byte authored `cRSubHealth` slots
  - `cRSubSpeedUp`, `cRJetPack`, and `cRSubHealth` share the recovered
    `TrackPickupState` protocol: `INACTIVE (0)`, `ACTIVE (1)`, and
    `TEARDOWN_PENDING (2)`
  - the live spawners claim only `INACTIVE` slots, collision moves a collected
    `ACTIVE` pickup to `TEARDOWN_PENDING`, and the exact class AI removes its
    inherited BOD and sprite before returning the owner to `INACTIVE`
- `+0x3563a0`: `slug_hazards`
  - eight inline exact `0xec`-byte authored `Slug` (`cRSlug`) slots
  - `SlugPool` owns the complete `0x760`-byte Windows extent
- `+0x356b00`: `sub_lazers`
  - exact `0xdc0`-byte authored `SubLazerManager` with 20 inline `0xb0`-byte
    `SubLazer` (`cRSubLazer`) records
  - each record owns its inherited `RenderableBod` and borrows the containing
    subgame at slot `+0x88`
  - collision borrows slots while the subgame is live
- `+0x3578c0`: `salt_hazards`
  - exact `0x17c0`-byte authored `SaltManager` with 40 inline `0x98`-byte
    `Salt` (`cRSalt`) records
  - each record owns its inherited `RenderableBod` and borrows the containing
    subgame at slot `+0x88`
  - each slot owns a one-byte `collision_armed` latch at `+0x94`
- `+0x359080`: `banners`
  - two inline `0x60`-byte `Banner` records ending exactly at `+0x359140`
  - banner `+0x48` borrows the subgame while `+0x54` separately borrows the
    row-source player
- `+0x359140`: `garbage_hazards`
  - exact `0x264c`-byte `SubGarbagePool` wrapper
  - borrowed active-chain head at pool `+0x00`, followed by 50 inline
    `0xc4`-byte authored `SubGarbage` (`cRSubGarbage`) records at pool `+0x04`
- `+0xff7c00`: `landscape_manager`
  - exact `0x97a4`-byte `cRLandscapeManager` owner ending at `+0x10013a4`
  - ten `0x90`-byte active entries at `+0x00`, script count at `+0x5a0`, and
    128 `0x124`-byte parsed script records at `+0x5a4`
- `+0x10013a4`: `smtrack_heightfield`
  - exact `0x128`-byte animated BOD ending at `+0x10014cc`
  - `BodBase` at `+0x00` borrows the live mesh; an Object-derived
    `FrameSequence` at `+0x38` selects `TextureRef` frames and drives heightmap
    resampling
- `+0x10014cc`: `sm_tracks`
  - exact `0x25cfb4`-byte owner with a leading count and 150 `0x4088`-byte
    authored-segment records beginning at `+0x10014d0`
  - symbol-preserving iOS builds name this owner `cRSMTracks`, with
    `Import()` and `OpenLevels()` members matching the two Windows loaders
  - the aggregate ends exactly at the parcel pool, so the count does not alias
    entry 0 and there is no terminal padding word
- `+0x125e480`: `parcel_manager`
  - exact `0x1b58`-byte `cRParcelManager` owner with 50 inline `0x8c`-byte
    `Parcel` records
  - each `Parcel` owns its inherited `BodBase` and borrows the enclosing
    `SubgameRuntime`, embedded `Player`, and SpriteManager sprite handle
- `+0x1260020`: `galaxy`
  - exact `0x10fa8`-byte `Galaxy` controller ending at `+0x1270fc8`
  - `load_galaxy_layout` borrows the external `GalaxyPoint[10]` group-anchor
    bank at `0x4a1c4c` and `GalaxyPoint[101]` route bank at `0x4a1d14`
  - 101 `0x2a0` slots at controller `+0x10`; each slot owns a four-byte tick
    prefix and a `0x29c` route record
  - `load_level_definition_file` maps each `ArcadeN` definition to slot `N`,
    writing the level display name to record `detail_text` and `GalaxyText:`
    to record `description_text`
  - ten `0xa0` route-name records at controller `+0x10930`, ending exactly at
    the progress-base field at `+0x10f70`
- `+0x12727d8`: `completion`
  - exact `0x50`-byte authored `cRCompletion` owner shared by parcel delivery
    and the final result screen
- `+0x1272828`: `times_up`
  - exact adjacent `0x10`-byte authored `cRTimesUp` tail owner
  - `show_times_up_message` moves `INACTIVE -> DISPLAYING` and seeds its
    progress pair; AI advances to `EXPIRED`, tears down the borrowed widget,
    kills the embedded player on the following tick, and returns to `INACTIVE`
  - the maintained BN/IDA runtime replay now applies all three
    `void __thiscall(TimesUp*)` ABIs, so both tracked decompilers preserve the
    state/progress/border owner instead of raw receiver arithmetic
- `+0xff25d0`: `selected_level_record_active`
- `+0xff25d1`: `selected_level_record_persistent`
- `+0xff25d4`: `selected_level_record`
  - pointer to the expanded in-memory selected replay/high-score entry, not the compact on-disk `0x88 + 5*n` record
  - closed gameplay slice:
    - `+0x28`: `replay_level_index`
    - `+0x38`: `runtime_build_flags`
    - `+0x48`: `replay_speed_scalar`
    - `+0x68`: `runtime_build_seed`
    - `+0x6c`: `replay_sample_count`
    - `+0x70 + i*6`: replay sample `lateral_x`
    - `+0x72 + i*6`: replay sample `delta_z`
    - `+0x74 + i*6`: replay sample 16-bit `flags` (compact persistence stores
      only the low byte)

The `+0x72` sample lane is not a steering lane. `update_subgoldy` uses it on the non-selected
Time Trial replay/ghost path by accumulating `convert_math_type16_to_32(sample, 32.0)` into
`data_643190`; selected replay playback reads `+0x70` lateral X and `+0x74` flags directly.
That Time Trial ghost path marks the two `SPRITES/GHOST.TGA` sprite slots visible, writes the
accumulated ghost `z` into their payload lane, and clamps it to no more than 20 rows ahead of
Turbo. Selected-record playback instead forces that payload to Turbo's live `z`.
The same `update_subgoldy` slice also writes live replay samples: first sample stores absolute
world `z` in the ghost-Z lane, later samples store decoded-relative `z` deltas, and flags use
bits `0x1/0x2` for fire state, `0x4` for the replay latch, and `0x8` for the marked replay tail.
- `+0xff25d8`: `selected_level_record_saved_return_owner`
- `+0xff25dc`: `replay_update_cursor`
- `+0xff25e4`: `runtime_track_index`

Current practical read:

- `build_subgame_level` embeds the live `SubGoldy` actor at `game + 0x3bb7a4`, and `initialize_subgoldy` writes the back-pointer from `player + 0x408` into that owning gameplay object
- `initialize_tutorial` owns only the small `Game + 0xa858` tutorial controller:
  - `+0x00`: `state`
  - `+0x0c`: stored `Game` back-pointer
  - it sets runtime flags `0x600000` and clears the low `0x02` runtime bit while wiring that back-pointer
- `update_tutorial` is not a hidden tutorial event runner; it dereferences the stored `Game` pointer and returns the current row cell from `get_track_grid_cell_at_world_position`
- row-message/tutorial text dispatch continues through the normal `PlayerRowEventState -> TipMessageDefinition -> enqueue_tip_message -> TipManager` path
- the embedded level-definition slice is firmer now:
  - `load_level_definition_file` stores the middle-segment count at `game + 0xa874`, the authored `Length:` dword at `game + 0x1b0138`, and the `Random:yes` byte at `game + 0x1b013c`
  - `copy_segment_definition_to_level_slot` seeds each `0x4220` middle-segment slot from `game + 0xa878`, with the first slot's row count at `game + 0xa87c`
  - `populate_runtime_track_cells_from_segments` consumes those lanes so non-random courses sum first + middle + last block rows, while random courses pick middle segments from the shared math RNG until the `Length:` target is filled; the mode-1 random branch scales that target by challenge difficulty before subtracting the final `Last:` block row count into `game + 0x58`
  - current best read: the scalar at `game + 0x34` is the normalized challenge-difficulty lane, because `build_subgame_level` restores it from selected-record compact field `+0x50`, which matches the recovered `challenge_difficulty_value` offset in the compact high-score record
  - `build_subgame_level` seeds `game + 0x48` from the live course mode or from selected-record compact field `+0x48`, and `calc_subgame_rate` uses that lane as the base rate before completion and damage modifiers
  - `game + 0x125ffd8/+0x125ffdc` are the normalized `Garbage:`/`Salt:` frequencies: course build seeds or replay-restores them, `update_subgame` consumes them as hazard spawn controls, and `complete_subgame` persists them back into the high-score/replay record
- `build_subgame_level -> rebuild_track_runtime_from_segments -> populate_runtime_track_cells_from_segments` seeds `player + 0x4340` to `3` before `initialize_subgoldy` runs
- the same course-build path also seeds the row bounds consumed by `update_subgoldy`:
  - `game + 0x50` = first-block row count
  - `game + 0x54` = generated runtime row count
  - `game + 0x58` = `game + 0x54 - final Last-block row count`
  - current best read: on non-random shipped levels, completion arms at the start of the final `Last:` block rather than on the last populated row
- `begin_post_follow_carryover` seeds the attachment-exit handoff:
  - `post_follow_exit_roll` from `follow_state.orientation_b`
  - `post_follow_heading_carryover` from `follow_state.template_record->installed_heading_bits` or zero
  - `attachment_exit_pending = 1`
  - `attachment_exit_progress = 0`
  - `attachment_exit_gate_a = 0`
  - `attachment_exit_gate_b = 0`
- `update_subgoldy` uses those exit-side latches as threshold gates inside fall handling, not as the final death selector:
  - once `attachment_exit_progress > 0.7`, `attachment_exit_gate_a` gates a one-shot voice trigger and, when `player + 0x2d8 == 0`, a cutscene animation at `world_y < -6`
  - `attachment_exit_gate_b` gates a later one-shot voice trigger at `world_y < -7`
  - the bounded March 26 static sweep keeps `post_follow_heading_carryover` unresolved but narrows where it is not used:
    - `begin_post_follow_carryover` is still only the carryover writer
    - `update_subgoldy` does not directly read `player + 0x430` in the bounded retirement families
    - `update_cameraman` only consumes `player + 0x42c`, not `player + 0x430`
  - the separate death handoff remains the older `world_y < -7 && death_active == 0` path that calls `initialize_subgoldy_death`
  - direct disassembly corrects one field-xref omission while retaining the
    progress finding:
    - accepted `try_enter_track_attachment_from_swept_motion` clears `attachment_exit_pending` at `0x42c98a`; the relocatable Game-base access was absent from the earlier field-xref result
    - `attachment_exit_progress` does not have its own separate progress-expiry clear
  - current BN xrefs show `attachment_exit_progress` is only written by `begin_post_follow_carryover` and the single `update_subgoldy` store at `0x43ce96`
  - outside successful swept re-entry, later retirement of `attachment_exit_pending` is limited to five clear sites inside `update_subgoldy`: `0x43bcb3`, `0x43bf6f`, `0x43c06d`, `0x43c3ea`, and `0x43ce75`
    - the special `0x43bcb3` late clear is now statically tied to the non-follow floor-cache/slide motion block: the branch first checks runtime tiles `0x0f`, `0x10`, `0x12`, and `0x13`, then reaches the same block for slide-family cells only when `damage_gauge.state == 2`
    - the grounded snap branch at `0x43bf6f`, the trampoline landing branch at `0x43c3ea`, and one separate floor-snap branch at `0x43c06d` are also statically identifiable
    - the `0x43ce75` late clear is now narrowed too: it sits behind `sub_hover.state == 1` at `0x43ce23`, so it is not the generic/common retirement lane
    - the common post-swept-re-entry retirement path among those late clears still needs runtime confirmation
  - Zig now follows that narrowing more honestly:
    - the old `attachment_exit_progress >= 1.0` timeout clear is gone
    - active-phase retirement only uses the confirmed jetpack clear plus a conservative grounded/trampoline settle proxy until the missing carryover owner is recovered
- `update_subgoldy` also owns a separate completion handoff block:
  - once the player reaches the course-end threshold at `game + 0x58` and no attachment-exit handoff is pending, it arms `completion_handoff_active = 1`
  - it seeds `completion_handoff_timer = 0`, `completion_handoff_timer_step = 1/60`, and `completion_handoff_voice_gate = 0`
  - cutscene state `6` initializes the completion screen almost immediately, on the first handoff tick after arming
  - while active, it clamps the forward presentation offsets (`track_z_offset` / `track_z_anchor`) to the fixed completion lane and advances the timer every tick
  - after `2.0` seconds, `completion_handoff_voice_gate` gates a one-shot voice event `8`
  - after `5.0` seconds, the same block begins the frontend fade, flushes `completion` if needed, and routes through `complete_subgame`
  - when `level_mode == 0` and `level_mode_arg == *(data_4df904 + 0x12d4644) - 1`, that completion block calls `complete_subgame(game, 1)`, writes `app + 0x1bc = 0x1d`, and sets `app + 0x1b8 = 0x1a`
  - the other completion exits write `game + 0x1270fc8 = 1`, then:
    - force `app + 0x1b8 = 0x1a` and `app + 0x1bc = 2` when `level_mode == 7`
      - `initialize_subgame` and `update_subgame` both treat `level_mode == 7` as tutorial mode, so this is the tutorial-completion `26 -> 2` return-to-New-Game override rather than a separate unknown owner
    - otherwise copy the current outer owner into `app + 0x1bc` and set `app + 0x1b8 = 0x1a` when `selected_level_record_persistent != 0`
    - otherwise copy the current outer owner into `app + 0x1bc` and set `app + 0x1b8 = 0x1b`
- `update_subgoldy_resurrect` now has one stronger bridge-side read:
  - `player + 0x84` is the `resurrect_active` gate checked by `update_subgoldy` before it either advances `update_subgoldy_resurrect` or allows a fresh `initialize_subgoldy_death` dispatch
  - `initialize_subgoldy_resurrect` sets `resurrect_active`, stores `resurrect_final_loss`, and seeds the `resurrect_progress` pair; its apparent integer return is dead at both `initialize_subgoldy_death` call sites
  - the respawn branch copies the current outer owner from `app + 0x1b8` into `app + 0x1bc`, then writes `app + 0x1b8 = 0x1c`
  - respawn therefore uses a direct outer owner selector (`0x1c`) rather than the saved-owner `26/27/28` bridge family
  - the final-loss branch first writes `game + 0x1270fc8 = 2`, then calls `complete_subgame(game, 1)`
  - when `selected_level_record_persistent != 0`, that final-loss leg copies the current outer owner into `app + 0x1bc` and sets `app + 0x1b8 = 0x1a`
  - when `selected_level_record_persistent == 0`, the same leg still copies the current owner into `app + 0x1bc`, then:
    - sets `app + 0x1b8 = 0x1b` for non-postal modes
    - sets `app + 0x1b8 = 0x1b` for postal mode when app byte `+0x30d` is non-zero
      - on qualifying postal/challenge failures, `complete_subgame -> add_arcade_high_score` / `add_survival_high_score` has already armed `app + 0x1b8 = 0x14`, so this branch preserves the post-level high-score owner itself in `app + 0x1bc` before the `0x1b` rebuild-return handoff
    - otherwise forces `app + 0x1b8 = 0x1a` and overwrites `app + 0x1bc = 2`
  - `update_frontend_state_machine` state `0x1b` then destroys and reinitializes subgame, and `initialize_subgame` consumes that nonzero continuation selector by mode:
    - `level_mode == 1` rebuilds the challenge-setup owner through `initialize_challenge_setup_screen`
    - `level_mode == 4` rebuilds the Time Trial galaxy owner through `initialize_galaxy`
    - the current port now rebuilds that `level_mode == 1` lane into a literal challenge-setup controller instead of collapsing it onto `New Game -> Challenge Mode`
  - current best read for `game + 0x1270fc8` / app dword `+0x12e55e0` is now narrower than "not replay-only":
    - selector `1` is the postal post-completion rebuild lane
      - ordinary non-final completion writes `game + 0x1270fc8 = 1`
      - `initialize_subgame` then treats postal mode specially under selector `1`: increments the visible route progression lane, saves `SnailMail.cfg`, opens the postal galaxy owner, and resets subgame
      - this matches the current Zig `RouteMapScreenMode.post_completion_exit` lane rather than a generic route-map reopen
    - selector `2` is the ordinary rebuild/start lane used by other front-end owners
      - `update_subgoldy_resurrect` writes `game + 0x1270fc8 = 2` before ordinary final-loss teardown
      - `update_new_game_menu` direct `Postal Mode` also writes app `+0x12e55e0 = 2` before frontend state `10`
      - `exit_high_score_screen` and transient pause-abandon flow also write `2` on their rebuild path
      - `initialize_subgame` then uses selector `2` plus `level_mode` to rebuild the normal postal galaxy (`0`), challenge setup (`1`), or Time Trial galaxy (`4`) without the selector-`1` postal-completion side effects
- the app byte at `+0x30d` is now narrowed:
  - `add_arcade_high_score` and `add_survival_high_score` both set it to `1` while arming active state `20`
  - `destroy_high_score_screen` clears it back to `0`
  - `update_completion_screen` also branches on it before tearing down the completion screen
  - `update_high_score_screen` uses the same high-score-entry lane on post-level commit, then exits through `exit_high_score_screen`, which branches on the surviving run mode at `app + 0x74658`:
    - `0` (`postal`) -> frontend state `2`
    - `1` (`challenge`) -> frontend state `10`
  - current best read: it is a high-score-entry / high-score-screen continuation flag, not a generic gameplay mode byte
  - on ordinary postal/challenge failures, it is also the bridge-side split that decides whether `update_subgoldy_resurrect` preserves saved owner `0x14` (post-level high-score entry) for the later `0x1b` rebuild-return lane or forces the direct `0x1a -> owner 2` New Game override instead
  - `complete_subgame` only calls `add_arcade_high_score` / `add_survival_high_score` when `selected_level_record_active == 0`, so transient selected-record postal final-loss runs keep `app + 0x30d == 0` and therefore take the native `0x1a -> owner 2` New Game override instead of the `0x1b` return
- `update_galaxy` and `update_challenge_setup_screen` both seed `selected_level_record_active = 1` and populate `selected_level_record` before returning to `update_subgame` state `1`
  - the current static launchers do not show a matching write to `selected_level_record_persistent`
  - the challenge setup `Watch Replay` pointer targets the game-local mirror at `game + 0xfb3050`, not the visible challenge score table
  - the port now mirrors that split directly: challenge-setup `Watch Replay` launches stay on a transient selected-record source backed by that separate mirror and rebuild back into the same challenge-setup owner on return
- a second replay-launch lane now has stronger static shape on the app side:
  - `update_high_score_screen` replay-row clicks and the New Game menu's random replay branch both seed `app + 0x1066bec` with a replay-bearing record pointer, set app bytes `+0x1066be8` / `+0x1066be9` to `1`, and populate `app + 0x1066bf0` with the later saved replay return owner (`0x12` from high-score rows, `2` from the menu replay path)
  - `update_frontend_state_machine` initializes subgame at `data_4df904 + 0x74618`, so those app offsets alias the subgame-local selected-record fields exactly:
    - `app + 0x1066be8` = `game + 0xff25d0` (`selected_level_record_active`)
    - `app + 0x1066be9` = `game + 0xff25d1` (`selected_level_record_persistent`)
    - `app + 0x1066bec` = `game + 0xff25d4` (`selected_level_record`)
    - `app + 0x1066bf0` = `game + 0xff25d8` (`selected_level_record_saved_return_owner`) during that prelaunch window
  - `initialize_game_assets_and_world` clears app bytes `+0x1066be8` / `+0x1066be9` back to `0` during startup, so persistent replay-backed launches are not inheriting stale selected-record flags from an earlier app lifetime
  - high-score replay rows and the menu random replay path therefore arm the persistent selected-record lane directly, not through a later constructor-side copy helper
  - the menu replay branch is more specific than a generic replay picker:
    - the direct menu buttons stay on the ordinary owner path:
      - `Postal Mode` destroys the menu, sets frontend state `10`, writes `app + 0x74658 = 0`, writes app `+0x12e55e0 = 2`, and does not touch the selected-record scratch
      - `Challenge Mode` and `Time Trial` also jump to frontend state `10` with `app + 0x74658 = 1/4` respectively, but likewise do not touch the selected-record scratch
      - `Tutorial` jumps to frontend state `10`, writes `app + 0x74658 = 7`, and initializes the tutorial helper directly
    - `update_new_game_menu` rotates a menu-local dword cursor at `data_4df904 + 0x4f2dc` through `0..4` and wraps `5 -> 0`
    - only cursor values `0`, `1`, and `3` probe replay-bearing banks, so the loop skips the tutorial / back lanes instead of treating every menu item as a replay source
    - those three probe lanes map to postal (`app + 0x6ffae8`, `app + 0x74658 = 0`), challenge (`app + 0x85c128`, `app + 0x74658 = 1`), and completion / Time Trial (`app + 0x9b8768`, `app + 0x74658 = 4`)
    - each bank search reuses the same `0x1fac0` record stride and RNG-derived record index, and the branch gives up after `1000` attempts
    - the launcher is gated by menu-local float fields at `+0x10` / `+0x14`: `update_new_game_menu` adds the float at `+0x14` into the float at `+0x10`, enters the replay search only once that accumulator exceeds `1.0`, and clears `+0x10` back to `0.0` before the bank probe loop
    - the same menu-local object now has a firmer partial layout:
      - `+0x0`: rotating replay-bank cursor
      - `+0x4`: likely replay-attract hide latch; any input clears it after unhiding all six menu widgets, while a successful replay launch sets it to `1` immediately before `destroy_main_menu`
      - `+0x8`: post-probe hide-release accumulator; `update_subgame` later compares it against `1.0` before clearing the hide latch
      - `+0xc`: post-probe hide-release step; `update_new_game_menu` resets it to `1/3600` after either a replay-attract launch or a `1000`-attempt miss
      - `+0x10`: replay-attract launch accumulator
      - `+0x14`: replay-attract launch addend; the shipped Windows image initializes this dword to zero, the current tracked decompile only recovers it as a read operand inside `update_new_game_menu`, and BN reports no direct code/data xrefs to the absolute slot
    - when all `1000` attempts miss, the branch does not launch; it writes menu locals `+0x8 = 0` and `+0xc = 0x3991a2b4` (`0.00027777778f`) and returns
    - the remaining unknown is not the launch scratch itself but the remaining lane producers:
      - current best read: the replay-attract branch is real code, but dormant in the shipped image unless an unrecovered runtime mutation seeds the zero addend
      - the tracked full-HLIL snapshot does not show any out-of-line absolute references to `data_4df904 + 0x4f2e8/+0x4f2ec/+0x4f2f0`, and outside `update_new_game_menu` the only confirmed global consumers are `initialize_subgame` reading the likely hide latch at `+0x4`, `update_subgame` reading `+0x4/+0x8`, and `update_completion_screen` tail-calling back into `update_new_game_menu`
      - `update_subgame` later consumes `data_4df904 + 0x4f2e4` (`menu-local +0x8`) and clears the likely hide latch at `data_4df904 + 0x4f2e0` once that accumulator exceeds `1.0`
      - if another producer exists, it is not surfacing as a normal out-of-line global-field writer in the current image; the remaining possibilities are a pointer-relative write through some other holder of the reused menu object or a dormant build/data-controlled lane
  - those same launch helpers also update `app + 119190` from the selected record's mode or owner bank before jumping to frontend state `10`
  - `initialize_subgoldy` unconditionally calls `initialize_click_start`, and `initialize_click_start` hides its `Click to Start` widget when `app + 0x1066be8 != 0`, so the same app-side replay scratch also suppresses the normal click-start gate on persistent replay launches
  - `update_subgame` state `2` now closes one startup-side bridge write too:
    - when `selected_level_record_active != 0` and either the live click-start owner at `game + 0x3bbba0` raises flag `0x4000` while `game + 0xc == 0`, or the New Game replay-attract hide latch at `data_4df904 + 0x4f2e0` is still armed, it copies the current outer owner from `app + 0x1b8` into `app + 0x1bc`
    - it then sets `app + 0x1b8 = 0x1a` when `selected_level_record_persistent != 0`, otherwise `app + 0x1b8 = 0x1b`
    - the saved-owner slot is therefore no longer globally unresolved: selected-record startup uses the same "save current owner, then choose bridge opcode by persistent lane" pattern as the later completion and failure helpers
- `update_pause_menu` uses `app + 0x1066be9` directly on the pause `End Game` branch: it copies the current owner into the completion-screen saved-owner slot, then picks completion state `3` when the persistent byte is `1` (`7` for tutorial mode, `2` otherwise)
  - `update_completion_screen` state `3` destroys subgame and restores the state saved at `app + 0x1066bf0`, so the persistent replay-backed abandon or overlay lane uses the same saved-owner destroy-return path as persistent result exits rather than frontend state `0x1c`
  - when that persistent byte is `0`, the same pause branch falls through to completion state `2`; `update_completion_screen` state `2` then calls `complete_subgame(game, 1)`, skips the app `+0x30d` score-entry branch because transient selected-record runs keep `selected_level_record_active != 0`, destroys subgame, and on `level_mode == 4` reinitializes subgame directly instead of using frontend state `0x1c`
  - `update_subgame` seeds `game + 0x1270fc8 = 2` on the route-map best-trial launch path, and `initialize_subgame` later uses that nonzero continuation selector plus `level_mode == 4` to rebuild the galaxy owner through `initialize_galaxy` / `reset_subgame`
  - transient route-map replay pause abandon therefore uses the non-clear rebuild lane (`0x1b` / opcode `27`-shaped semantics), not the respawn-only clear-replay lane (`0x1c` / opcode `28`)
  - `update_subgoldy` also consumes the selected-record replay payload directly while `selected_level_record_active != 0`, `replay_update_cursor < record->replay_sample_count`, and `click_start.state != 2`:
    - `record->replay_samples[replay_update_cursor].lateral_x` becomes live replay `x`
    - `record->replay_samples[replay_update_cursor].flags & 0x4` feeds `track_state_latch`
    - that same `flags` byte bit `0x8` writes `app + 0x1b8 = 0x1a`, `app + 0x1bc = 10`, sets app byte `+0x30c = 1`, and calls `begin_frontend_fade_in(app + 0x24)`
  - selected replay marker bit `0x8` therefore loops back through frontend state `10 -> initialize_subgame -> update_subgame`, not directly to the route-map or high-score launch surface
  - `update_frontend_state_machine` state `0x1c` also clears app dword `+0x12e55e0` before the rebuild handoff
- `set_subgame_features`, `populate_runtime_track_cells_from_segments`, and `build_subgame_level` all consume `selected_level_record_active` or `selected_level_record_persistent` to override the live course metadata from that record
- `initialize_subgame` also reads `selected_level_record_persistent` to restore the saved replay-speed scalar before the first mode controller reset
- `destroy_subgame` clears `selected_level_record_persistent` and writes `app + 0x1bc = 0x12` on that teardown path
- `update_subgame` clears `selected_level_record_active` when the persistent lane is absent on state `0`, and later re-arms `selected_level_record_active = (selected_level_record_persistent == 1)` on rebuild state `7`
- the selected-record launch split is now tighter:
  - `update_galaxy` and `update_challenge_setup_screen` only expose the transient game-side `selected_level_record_active` lane
  - high-score replay rows and the menu random replay path write the persistent lane through the aliasing app-side replay scratch at `app + 0x1066be9 == game + 0xff25d1`
  - whole-image static disassembly still shows no direct nonzero store to `game + 0xff25d1`; the only literal store to that byte is the teardown clear in `destroy_subgame` at `0x438b13` because the nonzero writer arrives through the overlapping app-base address instead
  - `build_subgame_level` only tests `selected_level_record_active || selected_level_record_persistent` before copying selected-record mode, level, replay-speed, and scalar fields, so the remaining bridge-side questions are no longer "where is the persistent writer?" or "is there any saved-owner writer at all?" but which launch families should be treated as transient versus persistent, and which non-startup helpers still seed distinct saved owners before `26/27/28`
  - app dword `+0x12e55e0` is therefore not a persistent-bit source:
    - current best read is the same rebuild selector seen at `game + 0x1270fc8`, with selector `1` owning the postal post-completion reopen and selector `2` owning the ordinary rebuild/start lane
    - state `0x1c` only clears that selector during the rebuild-clear-replay bridge
- `game + 0x12727d8` is the authored `Completion` controller, not a loose flag cluster:
  - `initialize_subgoldy` clears `completion.state` to `COMPLETION_STATE_INACTIVE`
  - `destroy_subgame` and the completion leg in `update_subgoldy` both flush it through `flush_row_event_display`
  - `register_parcel_delivery`, `update_row_event_display`, and `flush_row_event_display` recover the controller's parcel-count, bonus, and state fields
  - `update_subgoldy` waits for `COMPLETION_STATE_CONTINUE_ACCEPTED` before allowing the completion handoff timer to finish
  - the old `game + 0x12727f0` byte is `Completion +0x18` and remains a conservative controller gate: when it is `1` and the control source carries the `0x4000` accept/fire flag, `update_subgoldy` fast-forwards `completion_handoff_timer` to `5.1`
- the main gameplay collision consumers now line up with the spawn helpers:
  - `initialize_track_parcel_slots`, `spawn_track_parcel`, `place_parcels_on_track`, `place_challenge_parcels_on_track`, and `handle_subgoldy_collisions` all share `parcel_target_count` and `ParcelManager::slots`
  - `spawn_track_health_pickup` and `handle_subgoldy_collisions` use the `health_pickups` array
  - `spawn_track_jetpack_pickup` uses the separate `jetpack_pickup` slot
  - `spawn_track_garbage_hazard` pushes slots into the `active_garbage_hazards` list over the `garbage_hazards` pool
    - when `movement_flags & 0x80` is clear, the garbage-hit branch subtracts `normalized_contact.x * velocity.z * 0.18` from `player->velocity.x` and `normalized_contact.z * velocity.z * 0.10` from `player->velocity.z`
    - the grounded track leg in `update_subgoldy` then applies `position += velocity` and damps `velocity.x` by `1 - track_center_x * 0.1` each tick
  - `spawn_slug_hazard` and `handle_subgoldy_collisions` use the `slug_hazards` array
- the embedded `ParcelManager::slots` are the same runtime family allocated by the Windows `cRSubGame::AddParcel` path and remain separate only from the garbage runtime seeded at `game + 0x359144`
- native `replay_update_cursor` is the per-update cursor advanced by `update_subgoldy`
- the same cursor also drives selected replay-sample reads and the Time Trial terminal threshold
- native `runtime_track_index` at `+0xff25e4` is separate and still names the rendered/current row index
- the Zig runner keeps the replay lane as `replay_sample_index` because its `runtime_track_index`
  name is already used for the rendered row index consumed by track sampling
- the dword at `+0xff25d8` remains separate from `selected_level_record`, `replay_update_cursor`, and `runtime_track_index`
  - current best read: it is the saved replay return owner seeded by persistent replay launchers (`0x12` from high-score replay rows, `2` from the menu replay path) and later restored by `update_completion_screen` state `3`
  - the Zig bridge now mirrors that lane more literally too: persistent selected-replay context stores the raw saved owner-state separately and only derives a higher-level target from it when it needs to rebuild an owner shell
  - remaining gap: the full lifetime of that field after subgame init is still not traced end-to-end
- the remaining New Game replay-attract gap is now narrower too:
  - the persistent replay scratch, bank rotation, saved replay return-owner writes, startup clear, and click-start suppressor are confirmed statically
  - BN static inspection now shows `data_4df904 + 0x4f2dc + 0x14` starts as zero and has no direct absolute xrefs outside the `update_new_game_menu` read, so the port keeps the replay-attract branch modeled but dormant instead of inventing a timer
  - the hide-release lane is now modeled as the recovered `+0x8` accumulator and `+0xc = 1/3600` step reset after each probe pass; the remaining static gap is the dormant launch-step producer at `+0x14`
- the former single-slot pickup-like window around `game + 0x355e08` lies
  inside the exact `0xb4`-byte `SubSpeedUp` owner at `+0x355db0`; it is not a
  second pickup and must not be merged with the adjacent `JetPack` at
  `+0x355e64`

## Runtime Configuration

The process-global storage at `0x4df918` is one exact 0xc4-byte
`RuntimeConfig`, persisted wholesale as `SnailMail.cfg`. The checked-in analysis
owner now spans the complete range instead of leaving its first field and
interior consumers as unrelated globals.

High-confidence regions are:

- `+0x00/+0x04`: sample and stream volume;
- `+0x08`: fullscreen selection;
- `+0x1c`: the dword `RuntimeRenderFlag` word;
- `+0x20..+0x33`: validation tail, validity latch, and alignment;
- `+0x34`: display-mode index;
- `+0x38`: two steering-sensitivity scalars;
- `+0x40/+0x44/+0x48`: challenge score/speed defaults;
- `+0x60`: 64-byte last-entered player name;
- `+0xa0..+0xac`: route limit, landscape selector, selected score bank, and
  loading budget; and
- `+0xc0`: new-game tutorial latch.

The initializer and every load/save site independently prove the full 0xc4
extent. Reserved fields keep offset-based names because no current consumer
justifies stronger semantics.

## Voice Manager

The process-global voice bank at `0x751498` is one exact `0x188`-byte
`cRVoiceManager` owner, now named `g_voice_manager` in both analysis lanes. It
contains 16 inline `0x18`-byte `cRVoiceSet` records followed by the shared
progress and frequency fields at `+0x180/+0x184`.

Each `VoiceSet` owns:

- `+0x00/+0x04`: sample count and shuffled-playlist cursor;
- `+0x08/+0x0c`: allocated playlist and registered-sample arrays; and
- `+0x10/+0x14`: cooldown progress and step.

The symbol-preserving mobile builds retain the authored
`cRVoiceSet::{Init, Shuffle, AI, Play}` and
`cRVoiceManager::{ReSet, Init, AI, Play, IsPlaying}` families. Windows callers
and the mobile implementations also close the two ambiguous mutator ABIs:
`VoiceSet::Init(int)` and `VoiceSet::Shuffle()` are `void`. Their different
platform-specific return-register residue is incidental, and every caller
discards it.

`VoiceManager::Init()` parses all 16 named `Voice/_Voice.txt` banks, registers
their samples, applies the three normalization scalars, reads the global
frequency interval, and resets the inline cooldowns. `VoiceManager::Play()`
then selects a bank and applies one of the three recovered policies: idle-only,
global-cooldown, or interrupt. The checked-in matcher enums name those proved
bank IDs and policies without strengthening the native integer formals.

## Sound Effect Manager

Windows uses `g_sound_effect_manager @ 0x78ff88` as an exact one-byte empty
`cRSound` facade. Its six recovered methods never read receiver fields, but 36
native ECX loads across startup, frontend, gameplay, cutscene, and warning
callers prove the shared member owner. Android's later `gRSound` diverges by
storing a borrowed sound-bank pointer; that platform-specific field is not
projected back onto the empty Windows object.

The shipped `g_sound_bank_entries @ 0x4a2140` is one exact `0x270`-byte table:
51 live `0x0c`-byte `cRSoundBank` records followed by the empty-string sentinel.
Each record owns a path pointer, the registered sample index written at `+0x04`,
and its normalization class at `+0x08`. Both decompiler databases now claim the
full 52-record extent rather than retaining a pointer-sized item at its head.

`cRSound::Init(cRSoundBank*)` is `void`. Windows naturally leaves the sentinel
path in EAX while Android leaves a record offset, and both startup callers
discard it. The positional `Play(int, tVector&)` overload additionally recovers
the borrowed source vector and the listener at
`GameRoot::players[0].camera.body.transform.position`; its 25-unit attenuation
and pan calculation remain exact in the matcher.

## Backdrop

The Windows root owns one exact `0x6cc`-byte `cRBackdrop`-compatible object at
`GameRoot +0x4ec10`.

- `BackdropDistortCell distort_grid[8][8]` owns the full `+0x58..+0x657`
  animated warp grid.
- `+0x67c` and `+0x69c` begin two parallel 0x20-byte
  `BackdropWorldBlend` records. Each owns a constructed `tColour`, blend
  fraction, blend step, previous world, and current world.
- Android's symbolized `cRBackdrop::SetWorld(int)` performs the same state
  transition as Windows `0x410f40`: invert both blend fractions, shift current
  to previous, and install the new world in both records.
- Windows' only two callers discard EAX, and the 14-instruction exact scratch
  remains byte-identical with a `void` contract. The old
  `set_backdrop_texture_target` spelling remains only as the stable Windows
  harness identity.

## Frontend Widget

The shared front-end widget runtime now has a checked-in conservative type lane.

High-confidence current fields:

- `+0x04`: `list_flags`
- `+0x08`: `list_prev`
- `+0x0c`: `list_next`
- `+0x4c`: `authored_left`
- `+0x50`: `authored_top`
- `+0x54`: `authored_width`
- `+0x58`: `authored_height`
- `+0x5c`: `texture_hit_test_enabled` / `sprite_extend_enabled`
- `+0x5d`: `sprite_wobble_positive`
- `+0x60`: `background_texture_id`
- `+0x64`: `texture_hit_test_sprite` / `sprite_hit_mask_texture_id`
- `+0x68`: `sprite_extend_texture_c`
- `+0x7c`: `widget_type`
- `+0x17c`: `slider_position_target`
- `+0x180`: `slider_position_current`
- `+0x184`: `slider_hit_left`
- `+0x188`: `slider_hit_right`
- `+0x18c`: `slider_hit_top`
- `+0x190`: `slider_hit_bottom`
- `+0x194`: `shortcut_key_code`
- `+0x1a0`: `widget_flags`
- `+0x1a4`: `previous_widget_flags`
- `+0x1ac`: `current_fill_color`
- `+0x1bc`: `idle_fill_color`
- `+0x1cc`: `hot_fill_color`
- `+0x1dc`: `current_text_color`
- `+0x1ec`: `idle_text_color`
- `+0x1fc`: `hot_text_color`
- `+0x20c`: `hover_blend_target`
- `+0x210`: `hover_blend_current`
- `+0x214`: `idle_padding`
- `+0x218`: `hot_padding`
- `+0x21c`: `target_padding`
- `+0x220`: `current_padding`
- `+0x224`: `text_effect_target`
- `+0x228`: `text_effect_current`
- `+0x22c`: `render_inset_delta`
- `+0x230`: `render_inset_base`
- `+0x234`: `render_inset_dynamic`
- `+0x238`: `layout_left`
- `+0x23c`: `layout_top`
- `+0x240`: `texture_hit_x`
- `+0x244`: `texture_hit_y`
- `+0x248`: `layout_width`
- `+0x24c`: `layout_height`
- `+0x250`: `texture_hit_width`
- `+0x254`: `texture_hit_height`
- `+0x258`: `border_edge`
- `+0x25c`: `text_alignment`
- `+0x260`: `anchor_x`
- `+0x264`: `teardown_progress`
- `+0x268`: `teardown_progress_step`
- `+0x26c`: `stack_gap`
- `+0x270`: `texture_id`
- `+0x274`: `texture_layer`
- `+0x278`: `mouse_history_warmup_frames`
- `+0x27c`: `previous_mouse_x`
- `+0x280`: `previous_mouse_y`
- `+0x28c`: `tooltip`
- `+0x2cc`: `text_buffer`
- `+0x6ec`: `font_id`
- `+0x6f0`: `font_scale`
- `+0x6f4`: `layout_anchor_x`
- `+0x6f8`: `layout_anchor_y`
- `+0x6fc`: `input_cursor`
- `+0x700`: `input_cursor_visible`
- `+0x704`: `input_cursor_blink_progress`
- `+0x708`: `input_cursor_blink_step`
- `+0x70c`: `input_flags`
- `+0x710`: `input_length`
- `+0x714`: `input_capacity`
- `+0x718`: `slider_less_widget`
- `+0x71c`: `slider_more_widget`
- `+0x720`: `slider_value_widget`

The adjacent `+0x1a0/+0x1a4` words now share the proven
`FrontendWidgetFlag` ownership in every checked-in analysis lane and in the
narrow Binary Ninja replay. Only bits with independent writers and readers are
named; the remaining interaction/style bits stay unresolved rather than being
inferred from nearby behavior.

Conservative current read:

- `layout_frontend_widget` owns the authored/live/clamped rect lane plus slider hit bounds
- `update_frontend_widget_interaction` is the authored `cRBorder::AI()` slot-zero
  callback and owns the hover blend, padding interpolation, shortcut dispatch,
  tooltip updates, and slider child propagation
- `initialize_frontend_widget` seeds the shared color/style banks, render inset controls, font/layout anchors, and slider child widgets
- exact `border_input_text_init` initializes the seven-field editor tail at `+0x6fc..+0x714`; `border_input_text` consumes the same cursor, blink, filter, length, and capacity state
- `text_buffer` should stay opaque for now; the full `0x420` block is consumed by widget text/layout helpers and text-input init, not just by plain C-string calls

The unstripped Android `cRBorder::AI()` body and the iOS `Border.o` function at
`0x3c410` independently preserve the same field offsets and call sequence as
Windows: active-list removal, `MouseTest`, delayed clicks, sound IDs 8/9,
tooltip and twinkle updates, `RePosition`, `Draw`, `InputText`, and slider-child
propagation. Windows installs `0x402820` in the border callback table and the
active-BOD loop invokes slot zero through its shared void AI contract. This is
class and ABI provenance; it does not inflate the still-partial byte match.

Android preserves the adjacent authored API as `cRBorder::HideInit()`,
`UnHideInit()`, `Highlight()`, `UnHighlight()`, and
`SpriteExtend(int, int, int, bool)`. Their complete mobile bodies match the
Windows state transitions, and every Windows callsite discards EAX. The shared
members therefore use the real `void` contracts; values left in EAX by the
Windows store schedules are incidental, not ownership-bearing returns.
The transactional Binary Ninja replay now persists and verifies all five
visibility/highlight/sprite-extension members directly, including the three
texture IDs and wobble byte owned by `SpriteExtend(...)`.

Android also preserves the exact `cRBorder::InputTextInit(int, char*, int)`
body. Both Windows callers discard EAX, while each platform exits with the
incidental result of `RePosition()` or `cRInputOK::Init()`. The shared member
therefore uses the authored `void` contract and names the final `+0x714` lane
as input capacity. The transactional Binary Ninja replay now persists and
verifies that typed receiver, its three arguments, and the void result
directly.

The adjacent Windows `border_input_text` body is authored
`cRBorder::InputText()` in both mobile symbol sets (`0x3b97c` on iOS and
`0x52a7c` on Android). Both ports preserve the complete editor state machine:
autorepeat key dispatch, the inline cursor marker, insertion/deletion,
separator-aware vertical movement, numeric/space filtering, blink and
`RePosition()`, and optional `cRInputOK`/`cRBorderManager` teardown. Mobile's
editor lanes are eight bytes earlier because its `cRBorder` prefix is shorter,
but their order matches Windows `+0x6fc..+0x714`. The sole Windows caller at
`0x402e48` immediately tests `widget_flags`, so EAX is not consumed; the float
shown by the Android decompiler is only the incidental result of the final
callee. The replayed Windows member therefore has the authored `void`
contract while the 64.64% scratch remains an honest partial match.

The broader cRBorder construction/layout surface is also authored `void`:

- `initialize_frontend_widget` is Android
  `cRBorder::Init(int, char*, int, float, float, tColour, int, float)`; all 83
  Windows callers discard EAX
- `layout_frontend_widget` is `cRBorder::RePosition()`; all 24 callers discard
  EAX, and Android exits without establishing a result
- `set_frontend_widget_shortcut_key` is `cRBorder::SetKeyLeft(int)`; all five
  callers discard the flags word left incidentally in EAX
- `stack_widget_below` is `cRBorder::SetBelow(cRBorder*)`; Android tail-calls
  void `RePosition()`, and all 36 Windows callers discard EAX

The exact small setters remain 6/6 and 9/9 instructions, and the constructor
remains 429/429 at 99.30%. `RePosition()` falls honestly to 84.18% at 177/177
because removing the synthetic result changes register allocation. The
transactional Binary Ninja replay now persists and verifies the authored void
`Init(...)`, `RePosition()`, `SetKeyLeft(int)`, and `SetBelow(cRBorder*)`
contracts, including the typed previous-widget receiver for the below-link.

### Frontend lifecycle return contracts

The same audit closes three controller families without widening every `AI()`
member indiscriminately:

- root-owned 0x1c-byte `Exit::initialize_exit_prompt` is the exact void
  `cRExit::Init()`; Android reaches a common side-effect-only epilogue and the
  sole Windows caller discards EAX
- embedded 0x28-byte `GUI::initialize_challenge_setup_screen` is void
  `cRGUI::Init()`; Binary Ninja applied and read back this prototype, while
  `GUI::update_challenge_setup_screen` remains result-bearing `cRGUI::AI()`
  because `update_subgame` consumes its semantic 0/1/3 result
- the four `HighScore` methods are the void `cRHighScore::Init(int, int)`,
  `AI()`, `UnInit()`, and `Exit()` lifecycle; Android AI directly tail-branches
  to the other three, and every external Windows caller discards EAX

Exit Init and HighScore UnInit/Exit remain exact. GUI Init is honestly 96.41%
at 167/167 instructions, and HighScore AI is honestly 98.05% at 205/205; both
lost only register allocation formerly constrained by synthetic return values.
The cRBorder, Exit, and HighScore void prototypes remain explicitly deferred
in Binary Ninja after live verification restored scalar inference, rather than
being forced or reported as applied.

### Frontend Widget Tooltip

The iOS `Border.o` symbol set identifies this embedded owner as authored
`cRToolTip`; the shared Windows analysis spelling is `FrontendWidgetTooltip`.
Each `FrontendWidget` owns the exact `0x40`-byte subobject at `+0x28c`.

High-confidence current fields:

- `+0x04`: `state`
- `+0x08`: `mode_flags`
- `+0x0c`: `owner_widget`
- `+0x10`: `delay_progress`
- `+0x14`: `delay_step`
- `+0x18`: `tooltip_widget`
- `+0x38`: `owner_widget_38`

Current practical read:

- exact `reset_tooltip` / authored `cRToolTip::ReSet()` and `update_tooltip` /
  `cRToolTip::AI()` now replay as void members directly against
  `FrontendWidgetTooltip*`; their EAX values were incidental nested-call or
  state-dispatch residue
- `owner_widget` and `owner_widget_38` are borrowed backlinks; `tooltip_widget` is the live handle to a `BorderManager`-owned widget whose lifetime this controller releases
- `state == 2` owns the `delay_progress += delay_step` leg before tooltip creation
- `state == 3` owns the live tooltip widget and kills it when the owner loses the active hover flag

## Row Event Display Controller

The inline controller at `game + 0x12727d8` is the exact `Completion` /
cross-port `cRCompletion` owner.

High-confidence current fields:

- `+0x00`: `widget_a`
- `+0x04`: `widget_b`
- `+0x08`: `widget_c`
- `+0x0c`: `widget_d`
- `+0x10`: `widget_e`
- `+0x14`: `state` (`CompletionState`)
- `+0x18`: `completion_fast_forward_gate`
- `+0x1c`: `parcel_target_count`
- `+0x20`: `bonus_enabled`
- `+0x24`: `staged_parcel_count`
- `+0x28`: `delivered_parcel_count`
- `+0x2c`: `progress`
- `+0x30`: `progress_step`
- `+0x34..+0x3f`: `widget_world` (`Vector3` parcel-delivery destination)
- `+0x40`: `bonus_blink_progress`
- `+0x44`: `bonus_blink_step`
- `+0x48`: `bonus_score`
- `+0x4c`: `display_token`

Current practical read:

- `initialize_completion_screen` enters `STAGING_PARCELS`
- `update_row_event_display` owns the complete display lifecycle:
  - `STAGING_PARCELS` creates one HUD-bound delivery parcel at a time
  - after the last staged parcel, nonempty runs enter `WAITING_FOR_DELIVERIES`; the zero-parcel path uses `EMPTY_DELIVERY_DELAY` before joining the summary lane
  - the final registered delivery or empty-delay expiry enters `SUMMARY_PENDING`, which reveals the summary and advances immediately to `SUMMARY_ACTIVE`
  - the accept input moves `SUMMARY_ACTIVE` to `CONTINUE_ACCEPTED`
- `register_parcel_delivery` increments `delivered_parcel_count`, awards the parcel score tier, applies the optional final bonus, and moves the final parcel to `SUMMARY_PENDING`
- `flush_row_event_display` fast-forwards the remaining parcel payout, destroys the owned widgets, copies `display_token` into the global presentation slot, and returns the controller to `INACTIVE`
- the byte at `+0x18` still contains the old `game + 0x12727f0` gate; it is now tracked as `completion_fast_forward_gate` because one recovered completion-handoff read uses it, but the nonzero writer is still unresolved

## Track Parcel Runtime

The placed parcel pickups now line up on a dedicated embedded runtime slot shape rooted at `game + 0x125e480`.

High-confidence current fields:

- `+0x10`: `world_position`
- `+0x38`: `state` (`ParcelState`)
- `+0x3c`: `owner_subgame`
- `+0x54`: `sprite`
- `+0x5c`: `bob_phase`
- `+0x60`: `bob_phase_step`
- `+0x64`: `owner_player`
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
- `spawn_track_parcel` is the Windows `cRSubGame::AddParcel` path: it allocates one free slot from `game->parcel_manager`, seeds the spawn position, installs the sprite, stores the borrowed player pointer, and enters `TRACK_ACTIVE`
- `update_track_parcel` owns the recovered lifecycle:
  - `TRACK_ACTIVE` bobs on the track and retires behind the player
  - collision moves the slot to `COLLECT_PENDING`; the updater advances it to `COLLECTING` and homes it into the player's parcel anchor
  - `update_row_event_display` reuses a spawned slot as `DELIVERY_PENDING`; the updater advances it to `DELIVERING`, flies it into `Completion::widget_world`, and calls `register_parcel_delivery`
  - every completed or discarded lane returns the manager-owned slot to `INACTIVE`
  - values `2` and `3` remain `UNKNOWN_2` and `UNKNOWN_3`: the exact updater treats both as inert, but no recovered live Windows producer writes either value
- `place_parcels_on_track` and `place_challenge_parcels_on_track` decide how many authored parcel rows stay live and feed the HUD-facing `parcel_target_count`
  - the survival/challenge path first builds the full candidate list in the
    global 4096-entry `g_parcel_group_survival_0` bank (cross-port original
    symbol `gParcelGroupSurvival0`), then keeps `target_count` entries with one
    random draw and in-place compaction per kept parcel; it is not an
    `N - target` random-removal pass
- `handle_subgoldy_collisions` reads the same slots back, awards the parcel score tier, and moves collected slots from `TRACK_ACTIVE` to `COLLECT_PENDING`
- these slots are the gameplay parcel runtime behind `cRSubGame::AddParcel`, not a separate manager path from it

## Track Pickup Runtime

The health and jetpack pickup spawners share the same leading pickup fields,
but their complete owners differ: health ends after that compact prefix while
the `0x19c`-byte `JetPack` continues with two embedded `Vapour` renderers.

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
  - forward velocity `player->velocity.z * 0.4`
  - spawn-position carry `player->velocity.xyz * 3.0`
  - sprite size `0.1 x 0.5`, tint `(1.0, 0.75, 0.75, 1.0)`, and a small downward acceleration `-0.0002`
- Android `cRSubGame::AddHealth` and `cRSubGame::AddJetPack` confirm the same field meanings even though later ports rearrange surrounding storage

## Track Ring / Special-Effect Runtime

The authored ring and special-effect pickups line up on a dedicated `2`-slot runtime bank rooted at `game + 0x35b78c`.

High-confidence current fields:

- `+0x68`: `effect_position`
- `+0x80`: `state` (`SubRingState`)
- `+0x84`: `owner`
- `+0x88`: `kind` (`SubRingKind`)
- `+0x8c`: `owner_snapshot`
- `+0x90`: `halo_particles[10]`
- `+0x1d4`: `effect_progress`
- `+0x1d8`: `effect_progress_step`
- `+0x1dc`: `active_x_oscillation_enabled`
  - conservative gate name; the writer is still unresolved
- `+0x1e0`: `active_phase`
- `+0x1e4`: `active_phase_step`
- `+0x1e8`: `child_update_cadence`

Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds both slots through `initialize_track_ring_or_special_effect_runtime`
- `update_subgame` dispatches authored `0x23` ring rows plus the ramp families `0x02..0x0a` into `spawn_track_ring_or_special_effect`
- `spawn_track_ring_or_special_effect` seeds the slot kind, owner selector snapshot, world position, and the child particle family (`ParticleRing`, `ParticleExplode`, `ParticleSlow`)
  - explicit authored ring rows use `SUB_RING_KIND_NORMAL_AUTHORED` (`5`), `POWER_UP_AUTHORED` (`8`), `EXPLODE_AUTHORED` (`6`), or `SLOW_AUTHORED` (`7`) and consume `RingSpeed` from the runtime row record at `game + 0x5ccac8 + row * 0xf4 + 0xe8`:
    - `phase_step = 1 / (ring_speed * 60) * track_center_x * tau`
  - the default ramp family uses `EXPLODE_RAMP` (`2`), randomized `SLOW_DEFAULT` (`3`), or `NORMAL_DEFAULT` (`4`) and the shared base-rate path instead:
    - `phase_step = 1 / ((2 - base_subgame_rate * 0.3) * 60) * movement_flag_selector * 0.125 * track_center_x * tau`
  - values `0` and `1` remain explicit `UNKNOWN_0`/`UNKNOWN_1` tokens because no live Windows producer is recovered; the spawner still preserves their distinct placement/RNG paths and the collision consumer preserves kind `1`'s score + `PW1` behavior
  - after a `NORMAL_DEFAULT` (`4`) ramp spawn, `update_subgame` advances the spacing cursor to the source row during early startup movement modes, otherwise to `source + 35`; the live Zig scanner mirrors the non-startup `source + 35` branch
  - the active slot position is the mutable vector at `+0x68/+0x6c/+0x70`
  - default ramp families `0/1/2/3/4` randomize `x` directly into that live slot vector at spawn
  - child particles orbit around the same live slot vector instead of around an independent hidden anchor
- `handle_subgoldy_collisions` reads the same runtime slots back with the shared ring gate:
  - `delta_z < 1.0`
  - normalized distance `< 0.98`
- on hit, the slot does not die immediately: `handle_subgoldy_collisions` moves `ACTIVE -> COLLECT_PENDING`, and the slot's `update_ring_or_special_effect_parent` vtable advances `COLLECT_PENDING -> COLLECTING` before teardown
- the collect transition (`2 -> 3`) and expand transition (`4 -> 5`) seed `effect_progress_step` from `Game.track_center_x * 0.0694444478`, not from the live subgame speed scalar
- the same vtable owns the `EXPAND_PENDING -> EXPANDING` teardown lane keyed from `movement_flag_selector_snapshot`
- the collision switch owns the ring-kind ladder:
  - `UNKNOWN_1` (`1`) -> score + `PW1`
  - `EXPLODE_RAMP`/`EXPLODE_AUTHORED` (`2/6`) -> score + `EXPLODERING` + `initialize_nuke`
  - `SLOW_DEFAULT`/`SLOW_AUTHORED` (`3/7`) -> negative motion-lane impulse + `SLOWRING`
  - `NORMAL_DEFAULT`/`NORMAL_AUTHORED` (`4/5`) -> optional voice + weapon-selector increment + `PW1..PW7`
  - `POWER_UP_AUTHORED` (`8`) -> weapon-selector increment + `PW1..PW7`
- the same pre-ladder collision block writes the live forward-motion lane:
  - `SLOW_DEFAULT`/`SLOW_AUTHORED`: `velocity.z = -0.1`
  - other live ring-effect kinds: `velocity.z = track_center_x * 0.5`
- the current Zig runner now mirrors the live runtime-slot collision owner and that ring-kind ladder, preserves per-row `RingSpeed` metadata in the preview pipeline, seeds the native presentation anchor for the ring slot, carries the recovered `base_subgame_rate` lane into the default-family `0/1/2/3/4` phase-step formula, seeds the post-hit progress step from `track_center_x` instead of from runner speed, and writes both the negative and positive live-ring `velocity.z` impulses into the runner motion lane
- the remaining Zig gap is that collisions still use the older lower proxy anchor while the player-height parity gap remains open, and the active `+0x1dc` oscillation gate is still conservative because its writer is still unresolved

## cRSubGarbage Runtime

The Windows garbage hazard pool is typed through the exact authored
`SubGarbage` (`cRSubGarbage`) owner. `GarbageHazardSlot` and
`GarbageHazardPool` remain compatibility aliases only; the earlier parcel and
flattened `GarbageHazardRuntime` labels on `0x408550`, `0x43f130`, and
`0x43f200` were a bad read of this same family.

High-confidence current fields:

- `+0x00..+0x7f`: inherited `RenderableBod body`
- `+0x68`: inherited `body.transform.position`
- `+0x80`: `next_active`
- `+0x84`: `SubGarbageState state`
  - `INACTIVE = 0`, `ACTIVE = 1`, `BURST_PENDING = 2`, `BURST = 3`
- `+0x88`: `SubGarbageCollisionSide collision_side`
  - `RIGHT = 1`, `LEFT = 2`
- `+0x8c`: `owner_game`
- `+0x90`: `velocity`
- `+0x9c`: `radius`
- `+0xa0`: `attachment_facing_angle`
- `+0xa4`: unresolved scalar
- `+0xa8`: `burst_rate_step`
- `+0xac`: `smoke_timer`
- `+0xb0`: `smoke_timer_step`
- `+0xb4`: `sprite`
- `+0xb8`: `source_cell`
- `+0xbc`: `hidden`
- `+0xc0`: `owner_player`

Current practical read:

- `initialize_runtime_pools_and_path_template_bank` seeds the 50 inline slots
  with `initialize_garbage_hazard`; the exact `50 * 0xc4 == 0x2648` record
  extent plus the four-byte active head closes `SubGarbagePool` at `0x264c`
- `spawn_track_garbage_hazard` allocates from that pool and threads the slot
  into `garbage_hazards.active_head`
- `handle_subgoldy_collisions` walks that active list directly
- `update_golb_ai` borrows the same `SubGarbagePool::active_head` chain twice:
  direct projectile contact uses the slot radius, while kind-2 impact splash
  marks every nearby live slot through the same state and collision-side fields
- on collision, the slot flips from `SUB_GARBAGE_STATE_ACTIVE` to
  `SUB_GARBAGE_STATE_BURST_PENDING`, records
  `SUB_GARBAGE_COLLISION_SIDE_RIGHT` or
  `SUB_GARBAGE_COLLISION_SIDE_LEFT`, and contributes the recovered `+0.04`
  gauge delta
- `update_garbage_hazard` matches Android and iOS `cRSubGarbage::AI()`: after collision, the slot bursts outward with randomized velocity, emits periodic smoke, and self-destructs when it falls below the track or behind the player
  - the Zig port now emits the smoke through a native-shaped burst event (`SMOKE.TGA`, position from the live garbage slot, `velocity * 0.2`, size `0.3 x 1.3`, and an ~8-tick lifetime) instead of hand-placing two collision puffs
- `destroy_garbage_hazard` matches Android `cRSubGarbage::Kill()` and unlinks
  the same `next_active` chain rooted at
  `owner_game->garbage_hazards.active_head`
- Android `cRSubGame::AddGarbage` confirms the same random scale and active-list
  pattern, while Windows fixes the exact storage layout and wrapper boundary
- the exact constructor, allocator, reset, teardown, and AI paths plus both
  partial high-fanout consumers (`update_golb_ai` and
  `handle_subgoldy_collisions`) independently agree on those four lifecycle
  values and two impact-side values; the enum names are analysis ownership,
  not a matching workaround

## cRSlug Runtime

The Windows slug hazard pool is typed as the exact authored `Slug` (`cRSlug`)
owner. `SlugHazardRuntime` remains only a matcher compatibility alias for older
scratch vocabulary.

High-confidence current fields:

- `+0x00..+0x7f`: inherited `RenderableBod body`
- `+0x68`: inherited `body.transform.position`
- `+0x80`: `state`
- `+0x84`: `death_toss_direction`
- `+0x88`: `owner_game`
- `+0x8c`: `velocity`
- `+0x98`: `attachment_facing_angle`
- `+0x9c..+0xab`: unnamed state-two teardown scratch; writes are proved but no
  reader is identified
- `+0xac`: `sprite`
- `+0xb0`: `source_cell`
- `+0xb4`: `passed_player`
- `+0xb8`: `lateral_phase`
- `+0xbc`: `lateral_phase_step`
- `+0xc0`: `owner_player`
- `+0xc4`: `engagement_voice_gate`
- `+0xc8`: `hit_points`
- `+0xcc`: `hit_flash_pending`
- `+0xd0`: `hit_flash_progress`
- `+0xd4`: `hit_flash_progress_step`
- `+0xd8`: `voice_active`
- `+0xd9`: `player_encounter_latched`
- `+0xdc`: `voice_progress`
- `+0xe0`: `voice_progress_step`
- `+0xe4`: `blink_progress`
- `+0xe8`: `blink_step`

Current practical read:

- `spawn_slug_hazard` allocates from the `8`-slot Windows pool, projects the spawn onto attachments, and seeds forward velocity from `track_center_x`
- `handle_subgoldy_collisions` reads the same slots back through the `slug_hazards` array
- `update_slug_hazard_ai` owns the ambient slug alert: state `1` checks `player->live_matrix.position.z + 1.0 > world_position.z`, latches `player_encounter_latched`, rolls the native math RNG, and calls `play_slug_voice(slot, 30 - scaled_random)` only when the first roll is above `0.600000024`
- the same state sets `passed_player` after the slug's world `z` falls behind the player and clears `engagement_voice_gate` before `play_voice_manager(..., 2, 1, -1)` when the player is within `16` rows; this is separate from the direct ambient `play_slug_voice` one-shot
- `hit_slug_hazard` decrements `hit_points`, latches `hit_flash_pending`, and calls `play_slug_voice(slot, 36 - scaled_random)` while the slot remains alive, mapping to `SLUG-HIT1..3`
- `kill_slug_hazard` only acts on live state `1`; it calls `play_slug_voice(slot, 28 - scaled_random)` for `SLUG-DEATH1..2`, switches the slot to explosion state `2`, records the left/right toss selector from `world_position.x`, awards slug score, and then calls `explode_slug_hazard`
- `spawn_slug_hazard` passes `attachment_facing_angle` to the track-attachment projector, and `update_slug_hazard_ai` later adds that projected angle to the player's heading for the sprite; the garbage family has the same producer/consumer contract at its own `attachment_facing_angle`
- `play_slug_voice` and `update_slug_voice_ai` use the per-slot `voice_active`, `voice_progress`, and `voice_progress_step` fields in addition to the global slug voice manager gate
- later Android and iOS ports still use the same semantic fields, but at least one later build expands the slug capacity beyond the Windows `8`-slot pool

## cRSubLazer and cRSalt Runtime

The adjacent projectile managers now use their authored actor owners in both
analysis lanes. `SubLazerSlot` and `SaltHazardSlot` remain compatibility aliases
only; live receivers and manager arrays use `SubLazer` and `Salt`.

- `initialize_sub_lazer_runtime` constructs the inherited `RenderableBod` and
  installs the table at `0x49733c`; its callback is
  `update_sub_lazer_projectile`, preserved as `cRSubLazer::AI()` on Android and
  iOS
- `SubLazerManager` owns 20 inline `0xb0`-byte actors, exactly matching the
  native `0xdc0` size ledger; each actor owns a 32-bit `SubLazerState` at
  `+0x80`, stores its borrowed `owner_game` at `+0x88`, velocity at `+0x8c`,
  and bob phase pair at `+0x98/+0x9c`
- the three proved SubLazer states are inactive `0`, active `1`, and
  recycle-pending `2`: manager initialization and Kill write inactive, Shoot
  writes active, and AI consumes recycle-pending after bob expiry or collision
- `spawn_sub_lazer_projectile` is the slot-level authored `Shoot`, while
  `deactivate_sub_lazer_projectile` is `cRSubLazer::Kill()`; the manager-level
  `shoot_subgoldy` scans the same inline array
- `initialize_salt_hazard_runtime` constructs the same inherited owner and
  installs the table at `0x497340`; its callback is the exact
  `cRSalt::AI()` at `update_salt_hazard`
- `SaltManager` owns 40 inline `0x98`-byte actors, exactly matching the native
  `0x17c0` size ledger; each actor owns a 32-bit `SaltState` at `+0x80` and
  independent fade-alpha, spawn-y, and collision-latch fields at
  `+0x8c/+0x90/+0x94`, proved across spawn, collision, and AI
- `initialize_salt_hazard_pool` is the exact void `cRSaltManager::Init()`;
  `spawn_salt_hazard` keeps a conservative `int32_t` analysis result because
  its Windows exits are return-sensitive even though the sole caller discards
  EAX

No field beyond those observed lanes is inferred: the cRSubLazer tail
`+0xa0..+0xaf` and the padding around both actors' state/backlink fields remain
unnamed.

## Attachment Template Samples

The path-template typing is now firm enough to name the sampled point records explicitly.

High-confidence `PathTemplate` fields:

- `+0x24`: `strip_mesh`
  - pointer to the generated strip-mesh object, not an inline nested blob
- `+0x38`: `kind`
- `+0x3c`: `is_mirrored_x`
- `+0x40`: `side_exit_mode`
- `+0x44`: `segment_count`
- `+0x4c`: `segment_count_f`
- `+0x54`: `width_cells`
- `+0x58`: `primary_samples`
- `+0x5c`: `secondary_samples`
- `+0x98`: `installed_heading_delta`
- `+0x9c`: `has_entry_mesh_transition`
- `+0xa0`: `entry_transition_strip_mesh`
- `+0xa4`: `entry_base_strip_mesh`

Byte-lane clarifications:

- `is_mirrored_x` is a byte flag, not a `uint32_t`
- `has_entry_mesh_transition` is a byte flag, and all current constructor
  scratches use that recovered owner directly

The tail ownership is now closed:

- world init sets `+0xa0` from one of 12 auxiliary template-pair strip meshes
  and `+0xa4` from the public template's own strip mesh
- follow progress swaps the installed entry cell's object to `+0xa0` at `3/7`
  with alpha `0.6`, then restores `+0xa4` at the terminal sample with alpha `1`
- the 12 auxiliary pairs serve public pairs `0..7`, `25..27`, and `41`

High-confidence `PathTemplateSample` fields:

- `+0x00..+0x3f`: `TransformMatrix`
- `+0x00`: `basis_right`
- `+0x10`: `basis_up`
- `+0x20`: `basis_forward`
- `+0x30`: `position`
- `+0x40..+0x7f`: still opaque
- `+0x80`: `delta_dir_to_next`
- `+0x8c`: `delta_length`
- `+0x90`: `center_x`
- `+0x94`: `rotation_scalar_94`
- `+0x98`: `rotation_scalar_98`
- `+0x9c`: `lateral_scale`
- `+0xa0`: `special_scalar`

The shared checked-in reverse-engineering header at
[`analysis/headers/path_template_types.h`](../../analysis/headers/path_template_types.h)
now also mirrors the stable `FollowState` prefix used by the attachment-follow
helpers. Treat that header as the current repo-owned typed source for the
`Path` / shared `Object` / follow-state slice that we actively mirror into
IDA.

The same narrow typed lane now also carries the `TrackRowCell` slice used by
the follow helpers and the render-cache builders:

- `+0x10..+0x18`: `anchor_position`
- `+0x38`: `attachment_template_record`
- `+0x3c`: byte-sized `SubLocTileId tile_id`; the shared value vocabulary now
  names the builder's floor/ramp/Wall2/slide, pickup, hazard, attachment, and
  ring identities without widening the one-byte field
- `+0x3d`: `open_edge_mask`, with previous/next row bits `0x01/0x02` and
  next/previous lane bits `0x04/0x08`
- `+0x3e..+0x3f`: alignment padding. Binary Ninja reports no code or data
  references to this interval, while both adjacent byte fields and the dword at
  `+0x40` have independent producer/consumer xrefs.
- `+0x40`: `lane_and_flags`, carrying the low lane index plus the proved
  hazard-suppression, cache-family, merged-run-width, AI, uncached-body, and
  corner-object lanes
- `+0x44..+0x50`: four fringe/cache object slots

The checked-in header also now mirrors the narrow render-cache owner slice:

- `SegmentCache`, the authored `cRSegmentCache` embedded at
  `SubgameRuntime +0x5c`
- `TrackRenderCacheSlot`
- the borrowed `SegmentCache.owner_subgame` backlink to that enclosing
  `SubgameRuntime`
- `SubgameRuntime.runtime_row_count` and its owned runtime-cell slab
- the generic render-object texture-group tail at `+0xc0..+0xd4`

High-confidence shared `Object` geometry fields:

- `+0x10`: `flags`
- `+0x2c`: `vertex_count`
- `+0x38`: `vertices`
- `+0x48`: `vertex_colours`
- `+0x54`: `facequad_count`
- `+0x58`: `facequad_capacity`
- `+0x5c`: `facequads`

`PathTemplateStripMesh` is retired as an owner name. It was an early partial
view of the first `0x60` bytes of `Object`; the same allocation helpers and
geometry fields are used by path strips, backdrop quads, fringe objects, and
render-cache inputs. The exact backdrop-quad helper family now independently
reads back as `Object*` in both decompilers, so keeping the partial name would
split one real owner by callsite.

The former path-local strip-mesh flags are now owned by the shared `ObjectFlag`
word. In particular, `0x10000` is `OBJECT_FLAG_USE_VERTEX_COLOURS` and
`0x100000` is `OBJECT_FLAG_DISABLE_CULLING`; neither meaning is path-specific.

`PathTemplate.kind` is now also carried as a conservative enum in the checked-in
header. Most constructor values are uniquely named from their builders, while a
few remain explicit family buckets where multiple builders still share one native
kind:

- `PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY = 0x00`
- `PATH_TEMPLATE_KIND_FAMILY_10 = 0x10`
- `PATH_TEMPLATE_KIND_FAMILY_11 = 0x11`
- `PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY = 0x27`

This is intentionally more conservative than the public constructor symbols.
The current Windows caller-table audit supports public-family constructor names
like `initialize_hump_path_template_pair`, `initialize_dump_path_template_pair`,
`initialize_dip_path_template_pair`, `initialize_slalomdouble_path_template_pair`,
and `initialize_cage2_path_template_pair`, but those constructors do not map
1:1 to the runtime `PathTemplate.kind` buckets they write into the record.

High-confidence `ObjectFaceQuad` fields:

- `+0x00`: `flags`
  - 16-bit storage field; do not model this as a C enum-backed struct member or the facequad record stops matching the recovered `0x30` allocation size
  - low-byte `OBJECT_FACEQUAD_FLAG_TRIANGLE` (`0x80`) selects the authored
    three-index form; the fourth vertex and second triangle are omitted
- `+0x02/+0x04/+0x06/+0x08`: four vertex indices
- `+0x0c`: `texture_ref`
- `+0x10..+0x2c`: four `(u, v)` pairs

High-confidence `TextureRef` / `TextureRefList` surface used by facequads:

- `TextureRefList +0x00`: `count`
- `TextureRefList +0x04`: `capacity`
- `TextureRefList +0x08`: first `TextureRef` entry
- `TextureRef` size: `0xa4`
- `TextureRef +0x00`: `flags`
- `TextureRef +0x0c`: `texture_path`
- `TextureRef +0x8c`: `slot_index`
- `TextureRef +0x98`: `arg3_98`
- `TextureRef +0xa0`: `one_a0`

The exact `TextureRef +0x00` word now carries the shared `TextureRefFlags`
ownership in the object-render, path, and star-manager analysis lanes. The
exact 0xb4-byte `Sprite` owner likewise carries `SpriteFlag` at `+0x04` in the
star and garbage-hazard lanes. These names cover only behavior closed by
independent lifecycle, renderer, animation, and loader consumers; unknown bits
remain unnamed.
  - both names stay intentionally offset-based: `get_or_create_texture_ref` writes caller `arg3` into `arg3_98` and constant `1` into `one_a0`, but their gameplay meaning is still open

Binary Ninja typing note:

- the repeated decompile pattern `*(_DWORD *)(this + 88)` / `*(_DWORD *)(this + 92)` is now confirmed as `primary_samples` / `secondary_samples`
- these are struct pointers, not vtables
- the first `0x40` bytes of each sample are a four-row transform block, which is why the old raw output kept surfacing `+0x10`, `+0x20`, and `+0x30` row offsets

This matches the recovered follow-state update behavior:

- `segment_count` bounds the active sample index
- the current sample `delta_length` scales the per-tick path factor
- `position` and `delta_dir_to_next` feed the interpolated output pose
- `special_scalar` is the field consumed by the special nonlinear kind-`42` branch

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
- `bn types show Player`, `bn types show SubgameRuntime`, and the recovered
  path-template types are therefore the authoritative typed layouts for now
- older databases can retain a same-size `Game*` named-type identity on the
  cataloged subgame lifecycle and track-normalization receivers; inspect one
  read-only with
  `uv run tools/binja/repair_subgame_receiver_owner.py --function <name>`, and
  use the explicit `--apply` form only after its guards report the exact known
  stale state
- the recovered path-template surface now also has a narrow mirrored IDA lane through [`analysis/headers/path_template_types.h`](../../analysis/headers/path_template_types.h) and [`tools/ida/sync_path_template_types.py`](../../tools/ida/sync_path_template_types.py)
