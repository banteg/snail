const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("attachment_builders.zig");
const assets = @import("assets.zig");
const gameplay_assets = @import("gameplay/assets.zig");
const attachment_module = @import("gameplay/attachment.zig");
const gameplay_camera = @import("gameplay/camera.zig");
const gameplay_runtime_entities = @import("gameplay/runtime_entities.zig");
const combat_module = @import("gameplay/combat.zig");
const damage_module = @import("gameplay/damage.zig");
const hazards_module = @import("gameplay/hazards.zig");
const jetpack_module = @import("gameplay/jetpack.zig");
const motion_module = @import("gameplay/motion.zig");
const parcel_module = @import("gameplay/parcel.zig");
const phase_module = @import("gameplay/phase.zig");
const presentation_module = @import("gameplay/presentation.zig");
const row_event_module = @import("gameplay/row_event.zig");
const runner_state = @import("gameplay/runner_state.zig");
const score_module = @import("gameplay/score.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const track = @import("track.zig");

const RuntimeHazardKind = gameplay_runtime_entities.HazardKind;
const RuntimeHazardState = gameplay_runtime_entities.HazardState;
const RuntimeHazard = gameplay_runtime_entities.Hazard;
const RuntimePickupKind = gameplay_runtime_entities.PickupKind;
const RuntimePickup = gameplay_runtime_entities.Pickup;
const RuntimeRingEffectState = gameplay_runtime_entities.RingEffectState;
const RuntimeRingEffect = gameplay_runtime_entities.RingEffect;
const TrackParcelRuntime = gameplay_runtime_entities.TrackParcel;
const TrackParcelHomeAnchor = gameplay_runtime_entities.TrackParcelHomeAnchor;
const TurretState = gameplay_runtime_entities.TurretState;

pub const RunnerInput = runner_state.RunnerInput;

pub const ReplayDirective = runner_state.ReplayDirective;

pub const AttachmentHint = runner_state.AttachmentHint;

pub const MovementMode = runner_state.MovementMode;

pub const SessionMode = runner_state.SessionMode;
pub const DeathCause = runner_state.DeathCause;
pub const cutscene_none_id = runner_state.cutscene_none_id;
pub const cutscene_intro_id = runner_state.cutscene_intro_id;
pub const cutscene_completion_id = runner_state.cutscene_completion_id;
pub const cutscene_death_id = runner_state.cutscene_death_id;
pub const RunnerHandoff = runner_state.RunnerHandoff;

const FallState = runner_state.FallState;

pub const Projectile = combat_module.Projectile;

const RunnerPhase = runner_state.RunnerPhase;

const completion_handoff_voice_delay_seconds = phase_module.completion_handoff_voice_delay_seconds;
const completion_handoff_release_seconds = phase_module.completion_handoff_release_seconds;
const completion_handoff_release_force_seconds = phase_module.completion_handoff_release_force_seconds;
const replay_world_x_min: f32 = -4.0;
const replay_world_x_max: f32 = 4.0;
const row_event_display_stage_progress_step = row_event_module.display_stage_progress_step;
const row_event_display_hold_progress_step = row_event_module.display_hold_progress_step;
const row_event_display_final_delay_progress_step = row_event_module.display_final_delay_progress_step;
const row_event_widget_local_x = row_event_module.widget_local_x;
const row_event_widget_local_y = row_event_module.widget_local_y;
const row_event_widget_local_z = row_event_module.widget_local_z;

pub const RecentEvent = runner_state.RecentEvent;
pub const EncounterCounters = runner_state.EncounterCounters;
pub const ScoreTotals = score_module.Totals;
const RowEventDisplayState = row_event_module.DisplayState;
const RowEventDisplayController = row_event_module.DisplayController;
pub const Stopwatch = runner_state.Stopwatch;
pub const DamageWarningState = damage_module.WarningState;
pub const DamageWarningActorState = damage_module.WarningActorState;
pub const DamageGaugeRuntime = damage_module.Runtime;
pub const DamageWarningActor = damage_module.WarningActor;
pub const DamageController = damage_module.Controller;
pub const SnailSkinSlot = presentation_module.SnailSkinSlot;
pub const SnailSkinTransition = presentation_module.SnailSkinTransition;
pub const AnimClipId = runner_state.AnimClipId;
pub const AnimDispatchState = runner_state.AnimDispatchState;
pub const JetpackWarningBand = jetpack_module.WarningBand;
pub const JetpackGauge = jetpack_module.Gauge;

// PORT(partial): Windows now confirms the contact-damage controller is the separate
// player +0x3c4 block behind `apply_damage_gauge_delta` / `update_damage_gauge`,
// not the jetpack gauge at +0x2750. Salt contact uses the `cRSalt`-native
// `+0.15f / dist < 0.98` gate; SubLazer projectiles use the separate
// `cRSubLazerManager @ game + 0x356b00` `+0.02f / dist < 0.49` lane.
//
// PORT(partial): Windows spawns garbage/salt from a forward row scan over an 8-row
// live strip rather than treating matching runtime tiles as immediate contacts. The
// runner now mirrors that with a spawned-hazard window and the recovered scalar-based
// ambient thresholds, but still omits the original suppressor bits and some mode gates
// because the preview does not expose those flags yet.
const health_recover_delta: f32 = -0.5;
const garbage_damage_delta: f32 = 0.04;
// PORT(verified): native `cRSalt` / `handle_subgoldy_collisions` feeds
// `apply_damage_gauge_delta` with `+0.15f` on salt contact
// (`artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c` via the
// `cRSalt @ game+0x3578c0` pool's collision branch). The previous `0.02`
// value was a port conflation with the `cRSubLazerManager @ game+0x356b00`
// SubLazer projectile pool which applies its own separate `+0.02f` damage
// delta when the Wall2 AI fires a sublazer via `shoot_subgoldy`.
const salt_damage_delta: f32 = 0.15;
const slug_damage_delta: f32 = 1.0;
const garbage_collision_distance_threshold: f32 = 0.98;
// PORT(verified): `cRSalt` collision uses the `0.98f` distance gate for
// authored tile-0x22 salt contact, not the `0.49f` gate that the SubLazer
// projectile pool uses. Aligning to the `cRSalt` side of the split.
const salt_collision_distance_threshold: f32 = 0.98;
// PORT(verified): `cRSubLazerManager` projectile collision uses
// `+0.02f` damage and a `0.49f` distance gate per
// `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:122-126`.
const native_sub_lazer_damage_delta: f32 = 0.02;
const native_sub_lazer_collision_distance_threshold: f32 = 0.49;
const runtime_health_collision_distance_threshold: f32 = 0.98;
const runtime_jetpack_collision_distance_threshold: f32 = 3.0;
const runtime_health_collision_y_tolerance: f32 = 0.4;
const runtime_hazard_collision_z_tolerance: f32 = 1.0;
const runtime_pickup_phase_step: f32 = 0.016666668;
const runtime_health_pickup_bob_height: f32 = 0.3;
const garbage_burst_side_bias_scale: f32 = 0.2;
const garbage_burst_gravity_scale: f32 = -0.01;
const garbage_burst_teardown_y: f32 = -10.0;
const garbage_burst_trailing_rows: f32 = 2.0;
const damage_warning_transition_step = damage_module.warning_transition_step;
const damage_warning_drain_delta = damage_module.warning_drain_delta;
const damage_warning_actor_step = damage_module.warning_actor_step;
const damage_warning_actor_solid_alpha = damage_module.warning_actor_solid_alpha;
const damage_gauge_display_lerp = damage_module.gauge_display_lerp;
const damage_gauge_pulse_step = damage_module.gauge_pulse_step;
const damage_gauge_hit_flash_step = damage_module.gauge_hit_flash_step;
const jetpack_warning_threshold = jetpack_module.warning_threshold;
const jetpack_auto_shutoff_margin_rows = jetpack_module.auto_shutoff_margin_rows;
const native_runtime_row_scan_ahead_rows: usize = 46;
const runtime_track_parcel_spawn_ahead_rows: usize = native_runtime_row_scan_ahead_rows;
const runtime_track_parcel_expiry_margin_rows: f32 = 10.0;
const jetpack_warning_phase_scale = jetpack_module.warning_phase_scale;
const runtime_pickup_live_window_rows: usize = native_runtime_row_scan_ahead_rows;
const runtime_hazard_live_window_rows: usize = native_runtime_row_scan_ahead_rows;
const runtime_wall2_emitter_window_rows: usize = 32;
const runtime_ring_live_window_rows: usize = 47;
const runtime_ring_spacing_rows: f32 = 10.0;
const runtime_ring_default_gate_threshold: f32 = 0.7;
const runtime_ring_kind4_to3_threshold: f32 = 0.93;
const runtime_ring_time_trial_kind3_threshold: f32 = 0.5;
const runtime_ring_effect_progress_scale: f32 = 0.069444448;
const runtime_ring_effect_collect_lerp: f32 = 0.94;
const runtime_ring_effect_collect_z_offset: f32 = 0.2;
const runtime_ring_effect_miss_expand_scale: f32 = 1.1;
const runtime_ring_spawn_y_offset_default: f32 = 2.5;
const runtime_ring_spawn_y_offset_explode_ramp: f32 = 3.5;
const runtime_ring_spawn_random_x_amplitude: f32 = 3.0;
const max_active_health_pickups = hazards_module.max_active_health_pickups;
const max_active_jetpack_pickups = hazards_module.max_active_jetpack_pickups;
const max_active_runtime_pickups = hazards_module.max_active_runtime_pickups;
const max_active_track_parcels = parcel_module.max_active_track_parcels;
const max_active_runtime_hazards = hazards_module.max_active_runtime_hazards;
const max_active_runtime_ring_effects = hazards_module.max_active_runtime_ring_effects;
const max_active_projectiles = combat_module.max_active_projectiles;
const max_defeated_slug_cells: usize = 64;
const max_collected_parcel_rows = parcel_module.max_collected_parcel_rows;
const postal_completion_bonus_score = row_event_module.postal_completion_bonus_score;
const starting_visible_life_stock = score_module.starting_visible_life_stock;
const starting_runtime_track_index: usize = 4;
const times_up_trigger_sample_index: usize = 21_000;
const times_up_progress_step: f32 = 0.0055555557;
pub const intro_cutscene_duration_ticks: u16 = gameplay_camera.intro_cutscene_duration_ticks;
pub const completion_cutscene_duration_ticks: u16 = gameplay_camera.completion_cutscene_duration_ticks;
pub const death_cutscene_duration_ticks: u16 = gameplay_camera.death_cutscene_duration_ticks;
const intro_cutscene_hold_ticks: u16 = gameplay_camera.intro_cutscene_hold_ticks;
const intro_cutscene_blend_ticks: u16 = gameplay_camera.intro_cutscene_blend_ticks;
const completion_cutscene_blend_ticks: u16 = gameplay_camera.completion_cutscene_blend_ticks;
const death_cutscene_blend_ticks: u16 = gameplay_camera.death_cutscene_blend_ticks;
const fall_gravity: f32 = 10.0;
// PORT(verified): native `initialize_subgoldy_resurrect` seeds progress at 0
// with a 1/120 step, and `update_subgoldy_resurrect` waits for progress >= 1
// before starting the respawn/final-loss handoff.
const fall_resurrect_delay_ticks: u16 = 120;
// PORT(verified): identical to `native_position_y_death_threshold` above. Native
// `update_subgoldy` at `artifacts/ida/functions/0043b120-update_subgoldy.c:504`
// calls `initialize_subgoldy_death` once `live_matrix.position.y < -7.0`; the
// fall phase (used by the post-death cutscene camera) keeps the same threshold
// for the `attachment.exit.gate_b` latch.
const fall_world_y_threshold: f32 = native_position_y_death_threshold;
const attachment_exit_progress_step_default = attachment_module.exit_progress_step_default;
const attachment_side_exit_margin = attachment_module.side_exit_margin;
const attachment_entry_start_y_tolerance = attachment_module.entry_start_y_tolerance;
const attachment_entry_end_y_tolerance = attachment_module.entry_end_y_tolerance;
const attachment_entry_rider_height = attachment_module.entry_rider_height;
const supertramp_launch_velocity_scale: f32 = 12.0;
const supertramp_launch_gravity: f32 = 18.0;
const launch_camera_progress_step_default: f32 = 1.0 / 72.0;
// Native `update_subgoldy` corrects X by `track_center_x * 0.2` each 60 Hz tick.
const mouse_steer_lerp_scale: f32 = 48.0;
const native_steering_center_x: f32 = 320.0;
const native_steering_max_x: f32 = 639.0;
const native_steering_world_scale: f32 = 0.0125;
const lane_lean_progress_step_scale: f32 = 1.0 / 27.0;
const lane_lean_grounded_max_y: f32 = 0.98000002;
const track_parcel_bob_amplitude: f32 = 0.3;
const track_parcel_bob_phase_step: f32 = 0.012820513;
const track_parcel_home_progress_step: f32 = 0.0416666679;
const track_parcel_delivery_progress_step: f32 = 0.0166666675;
const track_parcel_presentation_min_scale: f32 = 0.4;
const track_parcel_presentation_scale_delta: f32 = 0.6;
const math_random_center: f32 = 16384.0;
const math_random_inv_center: f32 = 1.0 / math_random_center;
const track_parcel_delivery_random_y_scale: f32 = 1.5 * math_random_inv_center;
const track_parcel_home_arc_height: f32 = 0.5;
const completion_cutscene_x_offset: f32 = gameplay_camera.completion_cutscene_x_offset;
const death_cutscene_x_offset: f32 = gameplay_camera.death_cutscene_x_offset;
const death_cutscene_y_floor: f32 = gameplay_camera.death_cutscene_y_floor;
const base_fire_cooldown_ticks: u8 = 10;
const projectile_speed_rows_per_second: f32 = 48.0;
const turret_projectile_speed_rows_per_second: f32 = 20.0;
const turret_fire_interval_seconds: f32 = 1.0;
const turret_projectile_spawn_rows_ahead: usize = 24;
const turret_projectile_hit_z_tolerance: f32 = 0.5;
const turret_projectile_hit_x_tolerance: f32 = 0.6;
const turret_flash_duration_ticks: u8 = 6;
const max_active_turret_states = combat_module.max_active_turret_states;
const native_ticks_per_second: f32 = 60.0;
// Windows quantizes runtime gameplay world X with `floor(x + 4.0)` and clamps the player
// between `-4.0` and `4.0`, so the live `Game.track_center_x` lane is the fixed `4.0`.
const native_track_center_x: f32 = 4.0;
const native_wall2_tile_id: u8 = 0x0e;
const native_wall2_spawn_gate_threshold: f32 = 4.0;
const native_wall2_spawn_y_offset: f32 = 8.0;
const native_wall2_target_z_offset: f32 = 8.0;
const native_wall2_target_random_z_span: f32 = 3.0;
const native_wall2_fire_delta_z_threshold: f32 = -4.0;
const native_sub_lazer_speed: f32 = 0.40000001;
const native_velocity_x_decay_per_tick: f32 = 1.0 - (native_track_center_x * 0.100000001);
// PORT(verified): native `update_subgoldy` snaps `live_matrix.position.y` to
// `sample_track_floor_height_at_position(...) + 0.49` when grounded
// (`artifacts/ida/functions/0043b120-update_subgoldy.c:535`).
const native_grounded_rider_height: f32 = 0.49000001;
// PORT(verified): native damping factors from `update_subgoldy` (0x43bac4). `velocity.y`
// and `velocity.z` decay by `1 - track_center_x * 0.003` per tick; `velocity.x` decays by
// `1 - track_center_x * 0.1` (matches `native_velocity_x_decay_per_tick`).
const native_velocity_yz_decay_per_tick: f32 = 1.0 - (native_track_center_x * 0.003);
// PORT(verified): native gravity coupling `velocity.y += -0.01 * track_center_x^2` per tick
// (`artifacts/ida/functions/0043b120-update_subgoldy.c:332,517,539`). With
// `track_center_x = 4.0`, this is `-0.16` per tick.
const native_gravity_velocity_y_delta: f32 = -0.0099999998 * native_track_center_x * native_track_center_x;
// PORT(verified): `update_subgoldy` at
// `artifacts/ida/functions/0043b120-update_subgoldy.c:504` calls
// `initialize_subgoldy_death` once `live_matrix.position.y < -7.0` and the death
// cutscene gate is still clear.
const native_position_y_death_threshold: f32 = -7.0;
// PORT(verified): native grounded-snap lane `0x43bf6f` reads `position.y < 0.49 && y > -0.163`
// (`artifacts/ida/functions/0043b120-update_subgoldy.c:458-459`). The lower bound
// is `-0.16333334` in the IDA export.
const native_grounded_snap_position_y_upper: f32 = 0.49000001;
const native_grounded_snap_position_y_lower: f32 = -0.16333334;
const native_grounded_snap_velocity_y_squidge_threshold: f32 = -0.029999999;
const native_barrier_hold_max_y: f32 = 6.5;

const TimesUpState = enum {
    inactive,
    message,
    kill_pending,
};

const TimesUpController = struct {
    state: TimesUpState = .inactive,
    progress: f32 = 0.0,
    progress_step: f32 = times_up_progress_step,

    fn show(self: *TimesUpController) void {
        if (self.state != .inactive) return;
        self.progress = 0.0;
        self.progress_step = times_up_progress_step;
        self.state = .message;
    }

    fn update(self: *TimesUpController) bool {
        switch (self.state) {
            .inactive => return false,
            .message => {
                self.progress += self.progress_step;
                if (self.progress > 1.0) {
                    self.state = .kill_pending;
                }
                return false;
            },
            .kill_pending => {
                self.* = .{};
                return true;
            },
        }
    }

    fn visible(self: TimesUpController) bool {
        return self.state == .message;
    }
};

const native_negative_ring_velocity_z_per_tick: f32 = -0.1;
const native_negative_ring_velocity_recovery_z_per_tick: f32 =
    native_track_center_x * native_track_center_x * 0.00400000019 * 0.25;
const native_start_block_velocity_z_delta_per_tick: f32 =
    native_track_center_x * native_track_center_x * 0.0040000002;
const native_floor_cache_velocity_z_delta_per_tick: f32 =
    native_start_block_velocity_z_delta_per_tick * 2.0;
const native_start_block_velocity_z_max_per_tick: f32 = 1.0;
const native_attachment_exit_z_damping_per_tick: f32 = 1.0 - (native_track_center_x * 0.2);
const slow_ring_duration_ticks: u16 = 240;
const turbo_projectile_spread_lateral: f32 = 0.1;
const invincible_duration_ticks: u16 = 480;
const max_weapon_level = presentation_module.max_weapon_level;
const slug_projectile_kill_score: u32 = 100;
const parcel_delivery_register_score: u32 = 10;
const cameraman_identity_matrix = gameplay_camera.cameraman_identity_matrix;
const CameraHotspotWorldState = gameplay_camera.CameraHotspotWorldState;
const CutsceneCameraState = gameplay_camera.CutsceneCameraState;
const CameramanState = gameplay_camera.CameramanState;
const CameraTransform = gameplay_camera.CameraTransform;
const lerpVector3 = gameplay_camera.lerpVector3;
const crossVector3 = gameplay_camera.crossVector3;
const dotVector3 = gameplay_camera.dotVector3;
const normalizeVector3 = gameplay_camera.normalizeVector3;
const cameraMatrixFromTransform = gameplay_camera.cameraMatrixFromTransform;
const cameraTransformFromMatrix = gameplay_camera.cameraTransformFromMatrix;
const normalizeCameraTransform = gameplay_camera.normalizeCameraTransform;
const rotateCameraTransformLocalZ = gameplay_camera.rotateCameraTransformLocalZ;
const rotateCameraTransformWorldZ = gameplay_camera.rotateCameraTransformWorldZ;
const orthonormalFrameFromForwardUp = gameplay_camera.orthonormalFrameFromForwardUp;
const lookAtPoint = gameplay_camera.lookAtPoint;
pub const linearInterpolateCameraMatrices = gameplay_camera.linearInterpolateCameraMatrices;
const rollRadiansFromForwardUp = gameplay_camera.rollRadiansFromForwardUp;
const interpolateWrappedRadians = gameplay_camera.interpolateWrappedRadians;
const attachmentSampleOrientationA = gameplay_camera.attachmentSampleOrientationA;
const buildNormalCameramanTransform = gameplay_camera.buildNormalCameramanTransform;
const cameramanVerticalLiftFromCachedTarget = gameplay_camera.cameramanVerticalLiftFromCachedTarget;
const cameramanPitchRadiansFromCachedTarget = gameplay_camera.cameramanPitchRadiansFromCachedTarget;
const clampedPreviousDesiredCameraZ = gameplay_camera.clampedPreviousDesiredCameraZ;

pub const WeaponChannelStates = presentation_module.WeaponChannelStates;
pub const nativeWeaponChannelStates = presentation_module.nativeWeaponChannelStates;
const movementFlagsForSelector = presentation_module.movementFlagsForSelector;
const movementFireCooldownStepForSelector = presentation_module.movementFireCooldownStepForSelector;

const MovementFireInputState = enum {
    none,
    fresh,
    repeat,
};

fn projectileSpeedForKind(kind: Projectile.Kind) f32 {
    return switch (kind) {
        .turbo => projectile_speed_rows_per_second,
        .laser => projectile_speed_rows_per_second * 2.0,
        .rocket => projectile_speed_rows_per_second * 0.48,
        .enemy_laser => turret_projectile_speed_rows_per_second,
    };
}

const RowSample = struct {
    global_row: usize,
    traversable_bounds: track.LaneBounds,
    path_bounds: ?track.LaneBounds,
    resolved_lane_index: usize,
    cell: u8,
    gameplay_cell: ?track.GameplayCellKind,
    runtime_tile_hint: ?u8,
    annotation: ?segment.Annotation,
    path_center_lane: ?f32,
    path_name: ?[]const u8,
};

fn nativeRingEventLabel(effect_kind: u8) ?segment.RingKind {
    return switch (effect_kind) {
        1 => .normal,
        3, 7 => .slow,
        2, 6 => .explode,
        4, 5, 8 => .powerup,
        else => null,
    };
}

pub fn nativeRuntimeRingKindLabel(effect_kind: u8) ?segment.RingKind {
    return nativeRingEventLabel(effect_kind);
}

fn nativeRingEventScores(effect_kind: u8) bool {
    return switch (effect_kind) {
        1, 2, 4, 5, 6 => true,
        3, 7, 8 => false,
        else => false,
    };
}

fn nativeRingAnnotationHandledByRuntime(tile_type: ?u8, row_flags: u32) bool {
    const resolved_tile = tile_type orelse return false;
    if ((row_flags & track.runtime_row_flag_ring_none) != 0 and track.runtimeGameplayCellKindForTile(resolved_tile, track.defaultRuntimeBuildFlags) == .ring) {
        return true;
    }
    return switch (resolved_tile) {
        0x23 => (row_flags & (track.runtime_row_flag_ring_normal | track.runtime_row_flag_ring_powerup | track.runtime_row_flag_ring_explode | track.runtime_row_flag_ring_slow)) != 0,
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07 => (row_flags & (track.runtime_row_flag_ring_powerup | track.runtime_row_flag_ring_explode | track.runtime_row_flag_ring_slow)) != 0,
        0x08, 0x09, 0x0a => (row_flags & track.runtime_row_flag_ring_explode) != 0,
        else => false,
    };
}

pub fn runtimeHandledRingAnnotation(tile_type: ?u8, row_flags: u32) bool {
    return nativeRingAnnotationHandledByRuntime(tile_type, row_flags);
}

fn requestedExplicitRuntimeRingKind(row_flags: u32) ?u8 {
    if ((row_flags & track.runtime_row_flag_ring_normal) != 0) return 5;
    if ((row_flags & track.runtime_row_flag_ring_powerup) != 0) return 8;
    if ((row_flags & track.runtime_row_flag_ring_explode) != 0) return 6;
    if ((row_flags & track.runtime_row_flag_ring_slow) != 0) return 7;
    return null;
}

fn requestedRampSpecialRuntimeRingKind(row_flags: u32) ?u8 {
    if ((row_flags & track.runtime_row_flag_ring_powerup) != 0) return 8;
    if ((row_flags & track.runtime_row_flag_ring_explode) != 0) return 6;
    if ((row_flags & track.runtime_row_flag_ring_slow) != 0) return 7;
    return null;
}

fn runtimeRingDefaultKind4Eligible(tile_type: u8, runtime_build_flags: u32) bool {
    if ((runtime_build_flags & 0x08) == 0) return false;
    return tile_type == 0x02 or tile_type == 0x03 or tile_type == 0x04;
}

const AttachmentExitCarryover = runner_state.AttachmentExitCarryover;
const InstalledAttachmentEntry = runner_state.InstalledAttachmentEntry;
const InstalledAttachmentSlot = runner_state.InstalledAttachmentSlot;
const WorldFrame = runner_state.WorldFrame;

fn offsetPosition(
    origin: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    local_x: f32,
    local_y: f32,
    local_z: f32,
) rl.Vector3 {
    return .{
        .x = origin.x + (right.x * local_x) + (up.x * local_y) + (forward.x * local_z),
        .y = origin.y + (right.y * local_x) + (up.y * local_y) + (forward.y * local_z),
        .z = origin.z + (right.z * local_x) + (up.z * local_y) + (forward.z * local_z),
    };
}

const AttachmentCameraProgress = runner_state.AttachmentCameraProgress;

pub const Runner = struct {
    session_mode: SessionMode = .debug,
    base_subgame_rate: f32 = 1.1,
    lane_index: usize = 0,
    resolved_lane_index: usize = 0,
    lane_center: f32 = 0.5,
    runtime_track_index: usize = 0,
    // PORT(verified): Windows `Game+0xff25dc` is the replay/update cursor incremented
    // once at the tail of `update_subgoldy`, while the Zig `runtime_track_index`
    // remains the current rendered row. Keep this separate so selected-record playback
    // and future saveback consume the native per-tick stream instead of row indices.
    replay_sample_index: usize = 0,
    track_row_progress: f32 = 0.0,
    track_step_rows: f32 = 0.0,
    row_position: f32 = 0.0,
    previous_row_position: f32 = 0.0,
    speed_rows_per_second: f32 = 12.0,
    native_velocity_x_per_tick: f32 = 0.0,
    native_velocity_z_override_per_tick: ?f32 = null,
    steering_initialized: bool = false,
    steering_anchor_authored_x: f32 = 0.0,
    steering_offset_authored_x: f32 = 0.0,
    paused: bool = false,
    finished: bool = false,
    phase: RunnerPhase = .active,
    cutscene: phase_module.CutsceneState = .{},
    handoff: phase_module.HandoffState = .{},
    tick_count: u64 = 0,
    stopwatch: Stopwatch = .{},
    movement_mode: MovementMode = .track,
    current_global_row: usize = 0,
    current_cell: u8 = ' ',
    current_annotation: ?segment.Annotation.Tag = null,
    current_gameplay_cell: ?track.GameplayCellKind = null,
    current_runtime_tile_hint: ?u8 = null,
    current_path_name: ?[]const u8 = null,
    replay_state: motion_module.ReplayState = .{},
    attachment: attachment_module.State = .{},
    camera_hotspots_world: CameraHotspotWorldState = .{},
    cached_camera_target_world: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    cameraman: CameramanState = .{},
    jetpack: JetpackGauge = .{},
    parcel: parcel_module.Pool = .{},
    path_center_lane: ?f32 = null,
    previous_lane_center: f32 = 0.5,
    traversable_bounds: track.LaneBounds = .{ .min = 0, .max = 0 },
    row_message_logical_segment_index: ?usize = null,
    row_message_token: u32 = 0,
    last_native_ring_effect_kind: ?u8 = null,
    native_ring_effect_token: u32 = 0,
    recent_event: RecentEvent = .none,
    counters: EncounterCounters = .{},
    score: ScoreTotals = .{},
    recent_score_award: u32 = 0,
    recent_score_award_ticks: u8 = 0,
    row_event_display: RowEventDisplayController = .{},
    last_health_pickup_position: ?rl.Vector3 = null,
    last_garbage_hit_position: ?rl.Vector3 = null,
    last_salt_hit_position: ?rl.Vector3 = null,
    visible_life_stock: u32 = starting_visible_life_stock,
    presentation: presentation_module.State = .{},
    damage: DamageController = .{},
    last_processed_row: ?usize = null,
    runtime: hazards_module.Runtime = .{},
    combat: combat_module.Combat = .{},
    times_up: TimesUpController = .{},
    time_trial_ghost_active: bool = false,
    time_trial_ghost_z: f32 = 0.0,
    defeated_slug_cells: [max_defeated_slug_cells]RowTarget = [_]RowTarget{.{ .row = 0, .lane = 0 }} ** max_defeated_slug_cells,
    defeated_slug_cell_count: usize = 0,
    math_random_state: u32 = 0,
    // PORT(verified): `update_subgoldy` owns a live vertical motion lane at `Player+0x6c`
    // (`live_matrix.position.y`) and `Player+0x414` (`velocity.y`). The non-follow grounded
    // state is `position_y = floor_y + 0.49`, with gravity `velocity.y += -0.01 * track_center_x^2`
    // each tick. Tile-family reactions at ramps (2..7) and slides (8..13) seed distinct
    // velocity.y values; `position.y < -7.0` triggers `initialize_subgoldy_death`.
    position_y: f32 = native_grounded_rider_height,
    velocity_y: f32 = 0.0,
    // PORT(verified): mirror of `Player+0x1e4` (`_pad_1e4[0]`). Set to `1` on the trampoline
    // landing lane (`artifacts/ida/functions/0043b120-update_subgoldy.c:529`), cleared
    // by the swept-reentry snap (line 464) and the tile-family "other" reaction (line 577).
    // While `true`, native skips the `velocity.z` damping at line 388 to preserve
    // forward speed immediately after a bounce.
    post_trampoline_airborne: bool = false,
    pub fn init(preview: *const track.LoadedLevelPreview) Runner {
        var runner = Runner{};
        runner.reset(preview);
        return runner;
    }

    pub fn reset(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const configured_parcel_target_count = if (self.row_event_display.parcel_target_count != 0)
            self.row_event_display.parcel_target_count
        else
            @as(u32, @intCast(preview.parcel_target_count));
        const row_event_config = .{
            .parcel_target_count = configured_parcel_target_count,
            .bonus_enabled = self.row_event_display.bonus_enabled,
            .bonus_score = self.row_event_display.bonus_score,
        };
        const session_mode = self.session_mode;
        const base_subgame_rate = self.base_subgame_rate;
        self.* = .{
            .session_mode = session_mode,
            .base_subgame_rate = base_subgame_rate,
            .speed_rows_per_second = 12.0,
            .row_event_display = .{
                .parcel_target_count = row_event_config.parcel_target_count,
                .bonus_enabled = row_event_config.bonus_enabled,
                .bonus_score = row_event_config.bonus_score,
                .bonus_blink_step = 1.0,
            },
            .visible_life_stock = starting_visible_life_stock,
            .math_random_state = preview.runtime_build_final_random_state,
            .position_y = native_grounded_rider_height,
            .velocity_y = 0.0,
            .post_trampoline_airborne = false,
        };
        if (preview.total_rows > 0) {
            self.runtime_track_index = @min(starting_runtime_track_index, preview.total_rows - 1);
            self.track_row_progress = 0.0;
        }
        self.syncRowPosition(preview);
        self.refreshSample(preview);
        if (preview.total_rows > 0) {
            const centered_lane_center =
                (@as(f32, @floatFromInt(self.traversable_bounds.min + self.traversable_bounds.max)) * 0.5) + 0.5;
            self.lane_center = centered_lane_center;
            self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
            self.resolved_lane_index = self.lane_index;
            self.refreshSample(preview);
        }
        self.previous_row_position = self.row_position;
        self.previous_lane_center = self.lane_center;
        self.steering_initialized = false;
        self.steering_anchor_authored_x = 0.0;
        self.steering_offset_authored_x = 0.0;
        self.last_processed_row = self.current_global_row;
        self.syncCurrentRowMessageSegment(preview, false);
        self.refreshCameraState(preview);
    }

    pub fn debugWarpToTrackRow(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        requested_row_position: f32,
        lane_center_override: ?f32,
    ) void {
        if (preview.total_rows == 0) {
            self.reset(preview);
            return;
        }

        self.paused = false;
        self.finished = false;
        self.phase = .active;
        self.clearCutscene();
        self.handoff = .{};
        self.movement_mode = .track;
        self.replay_state = .{};
        self.attachment = .{};
        self.runtime = .{};
        self.combat = .{};
        self.times_up = .{};
        self.time_trial_ghost_active = false;
        self.time_trial_ghost_z = 0.0;
        self.native_velocity_x_per_tick = 0.0;
        self.native_velocity_z_override_per_tick = null;
        self.steering_initialized = false;
        self.steering_anchor_authored_x = 0.0;
        self.steering_offset_authored_x = 0.0;
        self.replay_sample_index = 0;
        self.track_step_rows = 0.0;
        self.position_y = native_grounded_rider_height;
        self.velocity_y = 0.0;
        self.post_trampoline_airborne = false;

        const max_row_position = @as(f32, @floatFromInt(preview.total_rows - 1));
        self.row_position = std.math.clamp(requested_row_position, 0.0, max_row_position);
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.track_row_progress = self.row_position - @floor(self.row_position);
        if (lane_center_override) |lane_center| {
            self.lane_center = lane_center;
        }
        self.syncRowPosition(preview);
        self.refreshSample(preview);
        self.previous_row_position = self.row_position;
        self.previous_lane_center = self.lane_center;
        self.last_processed_row = self.current_global_row;
        self.syncCurrentRowMessageSegment(preview, false);
        self.refreshLiveTrackParcels(preview);
        self.refreshLiveRuntimePickups(preview);
        self.refreshLiveRuntimeHazards(preview);
        self.refreshLiveRuntimeRingEffects(preview);
        self.refreshCameraState(preview);
    }

    pub fn clearTimeTrialGhost(self: *Runner) void {
        self.time_trial_ghost_active = false;
        self.time_trial_ghost_z = 0.0;
    }

    pub fn markTimeTrialGhost(self: *Runner, ghost_z: f32) void {
        self.time_trial_ghost_active = true;
        self.time_trial_ghost_z = @min(ghost_z, self.row_position + 20.0);
    }

    pub fn step(self: *Runner, preview: *const track.LoadedLevelPreview, input: RunnerInput, delta_seconds: f32) void {
        self.stepWithReplay(preview, input, .{}, delta_seconds);
    }

    pub fn stepWithReplay(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        input: RunnerInput,
        replay: ReplayDirective,
        delta_seconds: f32,
    ) void {
        if (input.reset) {
            self.reset(preview);
            return;
        }

        if (input.toggle_pause and self.acceptsGameplayInput()) {
            self.paused = !self.paused;
        }

        if (self.acceptsGameplayInput()) {
            self.speed_rows_per_second = std.math.clamp(
                self.speed_rows_per_second + input.speed_delta_rows_per_second,
                2.0,
                48.0,
            );
        }

        if (preview.total_rows == 0) {
            self.finished = true;
            self.handoff.pending = .completion_finalize;
            return;
        }

        const replay_controls_track_x = replay.active and replay.lateral_world_x != null;
        if (!self.paused and self.acceptsGameplayInput() and replay.active) {
            // PORT(verified): native selected-record playback writes the recorded
            // lateral position and latch bits before steering, movement, and
            // row/collision processing run for the frame.
            self.applyReplayDirective(preview, replay);
        }

        if (self.acceptsGameplayInput()) {
            self.previous_row_position = self.row_position;
            self.previous_lane_center = self.lane_center;
            if (!self.paused) {
                self.stepNativeVelocityX(preview);
            }
            if (!replay_controls_track_x) {
                self.applyLaneDelta(input.lane_delta);
                if (input.steering_authored_x) |steering_authored_x| {
                    self.applyMouseSteeringAuthoredX(preview, steering_authored_x, delta_seconds);
                } else if (input.target_lane_center) |target_lane_center| {
                    self.applyTargetLaneCenter(preview, target_lane_center, delta_seconds);
                }
            }
        }

        if (!self.paused and self.acceptsGameplayInput()) {
            self.stepMovementFireCooldown();
            // PORT(verified): native `update_subgoldy` reseeds the movement-fire cooldown
            // lane from `presentation.movement_fire_cooldown_step` for the first 10 gameplay ticks
            // before the fire gate runs, which suppresses all movement-state shots during
            // that startup window.
            if (self.tick_count < 10) {
                self.presentation.movement_fire_cooldown = self.presentation.movement_fire_cooldown_step;
            }
            self.handleFireInput(preview, self.movementFireInputState(input, replay));
            self.updateNativeVelocityZOverride(preview, delta_seconds);
            self.track_step_rows = self.effectiveSpeedRowsPerSecond() * delta_seconds;
            self.advanceMovement(preview);
            self.tick_count += 1;
            self.replay_sample_index += 1;
            self.stopwatch.advance(1.0);
        }

        if (!self.paused and self.phase == .active) {
            self.tryPrimeCurrentRowAttachmentEntry(preview);
            self.refreshLiveTrackParcels(preview);
        }
        if (!self.paused) {
            self.updateTrackParcels(preview);
            self.updateRowEventDisplay(preview, input.fire_pressed);
        }
        if (!self.paused and self.phase == .active) {
            self.processTrackParcelCollisions(preview);
            self.refreshLiveRuntimePickups(preview);
            self.updateTurretFire(preview, delta_seconds);
            self.updateProjectiles(preview, delta_seconds);
            self.refreshLiveRuntimeHazards(preview);
            self.updateRuntimeHazards(preview);
            self.refreshLiveRuntimeRingEffects(preview);
            self.updateRuntimeRingEffects(preview);
            self.updateRuntimePickups();
            self.processRuntimePickupCollisions(preview);
            self.processRuntimeHazardCollisions(preview);
            self.processRuntimeRingEffectCollisions(preview);
            self.processVisitedRows(preview);
            self.updateJetpackGauge(preview);
            self.updateDamageWarning();
            self.stepTemporaryStates();
            self.updateSlowCommentaryTimer();
        } else if (!self.paused) {
            self.updatePhaseController(preview, delta_seconds);
        }
        self.endAttachmentIfNeeded(preview);
        if (!self.paused and self.phase == .active) {
            self.stepAttachmentExitState(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.maybeBeginCompletionCutscene(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.updateLaunch(preview, delta_seconds);
        }
        self.refreshSample(preview);
        if (!self.paused) {
            self.stepLaneLean(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.stepActivePhaseVerticalMotion(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.updateTimesUpController(preview);
        }
        if (self.movement_mode == .attachment and self.phase == .active) {
            self.attachment.ticks += 1;
        }
        self.syncCurrentRowMessageSegment(preview, true);
        self.refreshCameraState(preview);
    }

    fn inNativeSlowCommentaryBand(self: *const Runner) bool {
        if (self.phase != .active) return false;
        if (self.movement_mode != .track) return false;
        if (self.attachment.exit.pending) return false;
        if (self.track_step_rows <= 0.0001) return false;

        const actual_forward_step = @max(0.0, self.row_position - self.previous_row_position);
        const lower_bound = self.track_step_rows * 0.17;
        const upper_bound = lower_bound + ((self.track_step_rows * 0.5) - lower_bound) * 0.1;
        return actual_forward_step > lower_bound and actual_forward_step < upper_bound;
    }

    fn updateSlowCommentaryTimer(self: *Runner) void {
        if (!self.inNativeSlowCommentaryBand()) {
            self.presentation.slow_commentary_timer = 0.0;
            return;
        }

        self.presentation.slow_commentary_timer += self.presentation.slow_commentary_step;
        if (self.presentation.slow_commentary_timer > 1.0) {
            self.presentation.slow_commentary_timer = 0.0;
            self.presentation.slow_commentary_voice_token +%= 1;
        }
    }

    pub fn worldPosition(self: *const Runner, preview: *const track.LoadedLevelPreview, y: f32) rl.Vector3 {
        if (self.phase == .fall) {
            const state = self.phase.fall;
            return .{
                .x = state.world_x,
                .y = state.world_y + y,
                .z = state.world_z,
            };
        }
        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const position = self.attachmentFollowOutputPosition(built);
                const pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment.follow.template_progress,
                    self.attachment.follow.source_cell_row,
                    self.attachment.follow.lateral_offset,
                    self.attachment.follow.vertical_offset,
                );
                return .{
                    .x = position.x + (pose.basis_up.x * y),
                    .y = position.y + (pose.basis_up.y * y),
                    .z = position.z + (pose.basis_up.z * y),
                };
            }
        }
        if (self.attachment.launch.active) {
            const floor_y = preview.sampleFloorHeightAtGridPosition(
                self.current_global_row,
                self.resolved_lane_index,
                self.row_position,
            ) orelse 0.0;
            return .{
                .x = self.attachment.launch.world_x,
                .y = floor_y + self.attachment.launch.height + y,
                .z = self.row_position,
            };
        }
        // PORT(verified): native `worldPosition` equivalent samples `live_matrix.position.y`
        // directly instead of deriving it from the current floor tile. The port's
        // `native_grounded_rider_height` offset keeps the downstream `y` parameter semantics
        // unchanged — `y=0.0` still means "at floor level" when grounded.
        const base_y = self.position_y - native_grounded_rider_height;
        var world = preview.worldPositionForLane(self.lane_center, self.row_position, base_y + y);
        if (self.currentReplayWorldX()) |world_x| {
            world.x = world_x;
        }
        return world;
    }

    pub fn worldForward(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        if (self.phase == .fall) {
            const state = self.phase.fall;
            return .{
                .x = state.basis_forward.x,
                .y = state.basis_forward.y,
                .z = state.basis_forward.z,
            };
        }
        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment.follow.template_progress,
                    self.attachment.follow.source_cell_row,
                    self.attachment.follow.lateral_offset,
                    self.attachment.follow.vertical_offset,
                );
                return .{
                    .x = pose.basis_forward.x,
                    .y = pose.basis_forward.y,
                    .z = pose.basis_forward.z,
                };
            }
        }
        if (self.attachment.launch.active) {
            return .{
                .x = self.attachment.launch.basis_forward.x,
                .y = self.attachment.launch.basis_forward.y,
                .z = self.attachment.launch.basis_forward.z,
            };
        }
        return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    }

    pub fn worldUp(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        if (self.phase == .fall) {
            const state = self.phase.fall;
            return .{
                .x = state.basis_up.x,
                .y = state.basis_up.y,
                .z = state.basis_up.z,
            };
        }
        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment.follow.template_progress,
                    self.attachment.follow.source_cell_row,
                    self.attachment.follow.lateral_offset,
                    self.attachment.follow.vertical_offset,
                );
                return .{
                    .x = pose.basis_up.x,
                    .y = pose.basis_up.y,
                    .z = pose.basis_up.z,
                };
            }
        }
        if (self.attachment.launch.active) {
            return .{
                .x = self.attachment.launch.basis_up.x,
                .y = self.attachment.launch.basis_up.y,
                .z = self.attachment.launch.basis_up.z,
            };
        }
        return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    }

    pub fn cameramanFovDegrees(self: *const Runner) f32 {
        return self.cameraman.fov_degrees;
    }

    pub fn cameramanMatrix(self: *const Runner) rl.Matrix {
        return self.cameraman.live_matrix;
    }

    pub fn takeCameramanSnap(self: *Runner) bool {
        const snap_next = self.cameraman.snap_next;
        self.cameraman.snap_next = false;
        return snap_next;
    }

    pub fn cutsceneCameraActive(self: *const Runner) bool {
        return self.cutscene.camera.state != .none;
    }

    pub fn cutsceneCameraMatrix(self: *const Runner) rl.Matrix {
        return self.cutscene.camera.matrix;
    }

    pub fn takeCutsceneCameraSnap(self: *Runner) bool {
        const snap_next = self.cutscene.camera.snap_next;
        self.cutscene.camera.snap_next = false;
        return snap_next;
    }

    pub fn replayTrackStateLatched(self: *const Runner) bool {
        return self.replay_state.track_state_latch;
    }

    pub fn replayRawFlagBits(self: *const Runner) u8 {
        return self.replay_state.raw_flag_bits;
    }

    pub fn replayFadeRequested(self: *const Runner) bool {
        return self.replay_state.fade_requested;
    }

    pub fn consumeReplayFadeRequest(self: *Runner) bool {
        const requested = self.replay_state.fade_requested;
        self.replay_state.fade_requested = false;
        return requested;
    }

    pub fn introCutsceneBlocksGameplay(self: *const Runner) bool {
        return self.cutscene.id == cutscene_intro_id and self.cutsceneCameraActive();
    }

    fn tryPrimeCurrentRowAttachmentEntry(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;
        if (self.phase != .active) return;
        if (self.movement_mode != .track) return;
        if (self.attachment.launch.active) return;

        const current_row = currentRowIndex(preview, self.row_position);
        const sample = self.sampleRow(preview, current_row) orelse return;
        if (self.attachment.exit.pending) {
            // PORT(verified): native `update_subgoldy` only reaches
            // `try_enter_track_attachment_from_swept_motion` from the live current cell
            // while `attachment.exit.pending` is still armed; it does not reuse the later
            // visited-row event pass as a broader installed-entry trigger. BN/IDA also show
            // those swept probes are keyed from the live row's `flags_b & 0x40` slot first,
            // then `flags_b & 0x80` only if the first call leaves the gate armed. Raw
            // disassembly does not show a direct helper-side clear before that second
            // gate check, so keep `attachment.exit.pending` live across a successful
            // primary re-entry attempt.
            if (preview.runtimeFlagB40At(current_row, sample.resolved_lane_index)) {
                _ = self.tryBeginInstalledAttachmentFollowForSlot(preview, current_row, sample, .primary);
            }
            if (self.attachment.exit.pending and preview.runtimeFlagB80At(current_row, sample.resolved_lane_index)) {
                _ = self.tryBeginInstalledAttachmentFollowForSlot(preview, current_row, sample, .secondary);
            }
            return;
        }
        const gameplay_cell = sample.gameplay_cell orelse return;
        if (gameplay_cell != .attachment_entry and gameplay_cell != .attachment_probe) return;

        if (self.tryBeginCurrentRowInstalledAttachmentFollow(preview, current_row)) return;
    }

    // PORT(verified): before the tutorial click-start dismissal, native keeps Goldy
    // pinned on the START attachment crest and only refreshes the live camera from that
    // zero-progress state. Once click-start is dismissed, Windows returns to the normal
    // runner step even while the intro cutscene still owns the shared camera.
    pub fn refreshBlockedStartupState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.track_step_rows = 0.0;
        if (!self.paused) {
            self.tryPrimeCurrentRowAttachmentEntry(preview);
            if (self.movement_mode == .attachment and self.attachment.follow.active) {
                self.stepAttachmentFollowAtRate(preview, 0.0);
            }
            self.refreshSample(preview);
        }
        self.refreshCameraState(preview);
    }

    pub fn stepIntroStartupBlock(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        self.step(preview, .{}, delta_seconds);
    }

    pub fn refreshCameraState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.refreshRunnerCameraState(self, preview);
    }

    pub fn cameramanProgressBlend(self: *const Runner, preview: *const track.LoadedLevelPreview) f32 {
        return gameplay_camera.cameramanProgressBlend(self, preview);
    }

    fn cameramanMatrixBlendFactor(self: *const Runner) f32 {
        return gameplay_camera.cameramanMatrixBlendFactor(self);
    }

    pub fn annotationLabel(self: *const Runner) ?[]const u8 {
        const tag = self.current_annotation orelse return null;
        return switch (tag) {
            .path => "path",
            .ring => "ring",
            .parcel => "parcel",
            .model => "model",
            .jetpack_off => "jetpack_off",
            .no_fall => "no_fall",
        };
    }

    pub fn activeRuntimeHazards(self: *const Runner) []const RuntimeHazard {
        return self.runtime.hazards.slots[0..self.runtime.hazards.count];
    }

    pub fn activeRuntimeSalts(self: *const Runner) []const gameplay_runtime_entities.SaltSlot {
        return &self.runtime.salts.slots;
    }

    pub fn activeRuntimeSubLazers(self: *const Runner) []const gameplay_runtime_entities.SubLazerSlot {
        return &self.runtime.sub_lazers.slots;
    }

    pub fn activeRuntimePickups(self: *const Runner) []const RuntimePickup {
        return self.runtime.pickups.slots[0..self.runtime.pickups.count];
    }

    pub fn activeRuntimeRingEffects(self: *const Runner) []const RuntimeRingEffect {
        return self.runtime.rings.slots[0..self.runtime.rings.count];
    }

    pub fn activeTrackParcels(self: *const Runner) []const TrackParcelRuntime {
        return self.parcel.slots[0..];
    }

    fn nextMathRandomInt15(self: *Runner) u32 {
        self.math_random_state = (self.math_random_state *% 0x343fd) +% 0x269ec3;
        return (self.math_random_state >> 16) & 0x7fff;
    }

    fn nextMathRandomFloat01(self: *Runner) f32 {
        return @as(f32, @floatFromInt(self.nextMathRandomInt15())) / 32767.0;
    }

    fn nextMathRandomFloatBelow(self: *Runner, upper_bound: f32) f32 {
        return @as(f32, @floatFromInt(self.nextMathRandomInt15())) * upper_bound * 0.000030517578;
    }

    fn nextMathRandomSignedFloatBelow(self: *Runner, scale: f32) f32 {
        return (@as(f32, @floatFromInt(self.nextMathRandomInt15())) - 16384.0) * scale * 0.000061035156;
    }

    pub fn activeProjectiles(self: *const Runner) []const Projectile {
        return self.combat.projectiles.slots[0..self.combat.projectiles.count];
    }

    pub fn gameplayCellLabel(self: *const Runner) ?[]const u8 {
        const kind = self.current_gameplay_cell orelse return null;
        return kind.label();
    }

    pub fn recentEventLabel(self: *const Runner) []const u8 {
        return self.recent_event.label();
    }

    // PORT(verified): mirror of `dispatch_cutscene_animation`
    // (`artifacts/ida/functions/00444600-dispatch_cutscene_animation.c:6`).
    // Native passes `(presentation, anim_id, immediate, initial_frame)`; the
    // port folds the presentation-controller state onto the `Runner.cutscene.anim`
    // slot and lets the renderer pick the active clip from `AnimClipId.familyKey`.
    pub fn dispatchCutsceneAnimation(
        self: *Runner,
        anim_id: AnimClipId,
        immediate: bool,
        initial_frame: ?u16,
    ) void {
        self.cutscene.anim.dispatch(anim_id, immediate, initial_frame);
    }

    pub fn cutsceneAnimClipLabel(self: *const Runner) []const u8 {
        return self.cutscene.anim.active.label();
    }

    pub fn activePathName(self: *const Runner) ?[]const u8 {
        return self.attachment.path_name orelse self.current_path_name;
    }

    pub fn runtimeTileHint(self: *const Runner) ?u8 {
        return self.current_runtime_tile_hint;
    }

    pub fn damageWarningLabel(self: *const Runner) []const u8 {
        return self.damage.warning_state.label();
    }

    pub fn jetpackWarningLabel(self: *const Runner) []const u8 {
        return self.jetpack.warning_band.label();
    }

    pub fn jetpackFuelRemaining(self: *const Runner) f32 {
        return self.jetpack.fuelRemaining();
    }

    pub fn phaseLabel(self: *const Runner) []const u8 {
        return switch (self.phase) {
            .active => "active",
            .fall => "fall",
            .completion_handoff => "completion_handoff",
        };
    }

    pub fn deathCause(self: *const Runner) ?DeathCause {
        return switch (self.phase) {
            .fall => |state| state.cause,
            else => null,
        };
    }

    pub fn acceptsGameplayInput(self: *const Runner) bool {
        return self.phase == .active and !self.finished;
    }

    pub fn consumeHandoff(self: *Runner) RunnerHandoff {
        const handoff = self.handoff.pending;
        self.handoff.pending = .none;
        return handoff;
    }

    pub fn configureCompletionBonus(self: *Runner, parcel_target: usize, enabled: bool) void {
        self.row_event_display.configureForRun(parcel_target, enabled);
    }

    pub fn configureSessionMode(self: *Runner, session_mode: SessionMode) void {
        self.session_mode = session_mode;
    }

    pub fn configureBaseSubgameRate(self: *Runner, base_subgame_rate: f32) void {
        self.base_subgame_rate = base_subgame_rate;
    }

    pub fn registeredParcelCount(self: *const Runner) u32 {
        return self.row_event_display.registeredParcelCount();
    }

    pub fn rowEventCounterVisible(self: *const Runner) bool {
        return self.row_event_display.counterVisible(self.session_mode == .tutorial);
    }

    pub fn timesUpVisible(self: *const Runner) bool {
        return self.times_up.visible();
    }

    pub fn rowEventParcelTargetCount(self: *const Runner) u32 {
        return self.row_event_display.parcel_target_count;
    }

    pub fn rowEventWidgetWorldPosition(self: *const Runner) rl.Vector3 {
        return self.row_event_display.widgetWorldPosition();
    }

    pub fn rowEventBonusVisible(self: *const Runner) bool {
        return self.row_event_display.bonusVisible();
    }

    pub fn rowEventBonusBlinkAlpha(self: *const Runner) f32 {
        return self.row_event_display.bonusBlinkAlpha();
    }

    pub fn rowEventBonusScore(self: *const Runner) u32 {
        return self.row_event_display.bonus_score;
    }

    pub fn currentRowMessageLogicalSegmentIndex(self: *const Runner) ?usize {
        return self.row_message_logical_segment_index;
    }

    pub fn currentRowMessageToken(self: *const Runner) u32 {
        return self.row_message_token;
    }

    pub fn setCutscene(self: *Runner, cutscene_id: u8) void {
        self.cutscene.set(cutscene_id);
    }

    pub fn clearCutscene(self: *Runner) void {
        self.cutscene.clear();
    }

    fn laneLeanDirectionForRuntimeTile(tile_type: u8) f32 {
        return switch (tile_type) {
            2, 5, 8, 11 => 1.0,
            4, 7, 10, 13 => -1.0,
            else => 0.0,
        };
    }

    fn syncCurrentRowMessageSegment(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        emit_token: bool,
    ) void {
        const row_location = preview.locateRow(self.current_global_row) orelse {
            self.row_message_logical_segment_index = null;
            return;
        };
        const logical_segment_index = preview.segment_logical_indices[row_location.segment_index] orelse {
            self.row_message_logical_segment_index = null;
            return;
        };
        if (self.row_message_logical_segment_index == logical_segment_index) return;
        self.row_message_logical_segment_index = logical_segment_index;
        if (emit_token) {
            self.row_message_token +%= 1;
        }
    }

    fn maybeArmLaneLean(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;
        if (@abs(self.attachment.lane_lean.amplitude) > 0.0001) return;
        if (self.attachment.exit.pending) return;

        const world_position = self.worldPosition(preview, 0.0);
        if (world_position.y > lane_lean_grounded_max_y) return;

        const global_row = preview.rowIndexAtWorldZ(world_position.z);
        const lane_index = preview.laneIndexAtWorldX(world_position.x);
        const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse return;
        const direction = laneLeanDirectionForRuntimeTile(tile_type);
        if (direction == 0.0) return;

        self.attachment.lane_lean.amplitude = direction;
        self.attachment.lane_lean.progress = 0.0;
        self.attachment.lane_lean.progress_step = self.track_step_rows * lane_lean_progress_step_scale;
    }

    fn stepLaneLean(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.maybeArmLaneLean(preview);
        self.attachment.lane_lean.progress_step = self.track_step_rows * lane_lean_progress_step_scale;
        if (@abs(self.attachment.lane_lean.amplitude) <= 0.0001) return;

        self.attachment.lane_lean.progress += self.attachment.lane_lean.progress_step;
        if (self.attachment.lane_lean.progress > 1.0) {
            self.attachment.lane_lean.amplitude = 0.0;
            self.attachment.lane_lean.progress = 0.0;
            self.attachment.lane_lean.progress_step = 0.0;
        }
    }

    fn applyLaneDelta(self: *Runner, lane_delta: i8) void {
        if (lane_delta == 0) return;
        if (self.attachment.launch.active) return;
        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            self.attachment.follow.lateral_offset += @floatFromInt(lane_delta);
            return;
        }
        self.lane_center += @floatFromInt(lane_delta);
        self.lane_index = @as(usize, @intFromFloat(@max(0.0, @floor(self.lane_center - 0.5))));
    }

    fn applyTargetLaneCenter(self: *Runner, preview: *const track.LoadedLevelPreview, raw_target_lane_center: f32, delta_seconds: f32) void {
        if (preview.total_rows == 0 or self.attachment.launch.active) return;

        const alpha = std.math.clamp(delta_seconds * mouse_steer_lerp_scale, 0.0, 1.0);
        const min_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.min)) + 0.5;
        const max_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.max)) + 0.5;
        const target_lane_center = std.math.clamp(raw_target_lane_center, min_lane_center, max_lane_center);

        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const target_world_position = trackEntryWorldPosition(preview, self.row_position, target_lane_center);
                const centered_pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment.follow.template_progress,
                    self.attachment.follow.source_cell_row,
                    0.0,
                    self.attachment.follow.vertical_offset,
                );
                const target_local = attachmentLocalPosition(centered_pose, target_world_position);
                const target_lateral_offset = attachmentLateralOffsetFromLocalX(
                    &built.template,
                    self.attachment.follow.template_progress,
                    target_local.x,
                );
                self.attachment.follow.lateral_offset += (target_lateral_offset - self.attachment.follow.lateral_offset) * alpha;
                return;
            }
        }

        self.lane_center += (target_lane_center - self.lane_center) * alpha;
        self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
    }

    fn applyMouseSteeringAuthoredX(self: *Runner, preview: *const track.LoadedLevelPreview, authored_x: f32, delta_seconds: f32) void {
        if (!self.steering_initialized) {
            // Native click-start recenters the input pointer to `(320, 240)`.
            // Seed the relative accumulator so an off-center OS cursor does not
            // produce an artificial first-frame lane jump in the port.
            self.steering_initialized = true;
            self.steering_anchor_authored_x = authored_x;
            self.steering_offset_authored_x = native_steering_center_x;
        } else {
            const next_offset = authored_x - self.steering_anchor_authored_x + self.steering_offset_authored_x;
            self.steering_offset_authored_x = std.math.clamp(next_offset, 0.0, native_steering_max_x);
            self.steering_anchor_authored_x = authored_x;
        }

        // PORT(verified): native default steering mode accumulates authored mouse
        // deltas into `track_z_offset`, then steers toward
        // `(320 - track_z_offset) * 0.0125`. Selector 1 is the absolute cursor path.
        const target_world_x = std.math.clamp(
            (native_steering_center_x - self.steering_offset_authored_x) * native_steering_world_scale,
            -3.7,
            3.7,
        );
        const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;
        self.applyTargetLaneCenter(preview, width_offset + target_world_x, delta_seconds);
    }

    fn refreshSample(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment.hint = .none;
            self.path_center_lane = null;
            self.traversable_bounds = .{ .min = 0, .max = 0 };
            self.resolved_lane_index = 0;
            self.lane_center = 0.5;
            self.runtime_track_index = 0;
            self.replay_sample_index = 0;
            self.track_row_progress = 0.0;
            self.row_position = 0.0;
            return;
        }

        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment.hint = .none;
            self.path_center_lane = null;
            self.resolved_lane_index = 0;
            return;
        };

        self.current_global_row = sample.global_row;
        self.traversable_bounds = sample.traversable_bounds;
        self.resolved_lane_index = sample.resolved_lane_index;
        self.current_cell = sample.cell;
        self.current_annotation = if (sample.annotation) |annotation| annotation.tag() else null;
        self.current_gameplay_cell = sample.gameplay_cell;
        self.current_runtime_tile_hint = sample.runtime_tile_hint;
        self.current_path_name = sample.path_name;
        self.path_center_lane = sample.path_center_lane;
        self.attachment.hint = if (sample.gameplay_cell) |kind|
            switch (kind) {
                .attachment_entry => .entry,
                .attachment_probe => .probe,
                else => returnAttachmentHint(sample.path_center_lane),
            }
        else
            returnAttachmentHint(sample.path_center_lane);
        if (self.attachment.follow.active and self.movement_mode == .attachment) {
            self.lane_center = self.attachment.follow.cached_output_lane_center;
            self.attachment.follow.cached_output_lane_center = self.lane_center;
            self.lane_index = sample.resolved_lane_index;
        } else if (self.replay_state.world_x_override) |world_x| {
            self.lane_center = laneCenterFromWorldX(preview, world_x);
            self.lane_index = sample.resolved_lane_index;
            self.resolved_lane_index = sample.resolved_lane_index;
        } else if (self.currentReplayWorldX()) |world_x| {
            self.lane_center = laneCenterFromWorldX(preview, world_x);
            self.lane_index = sample.resolved_lane_index;
            self.resolved_lane_index = sample.resolved_lane_index;
        } else {
            const min_lane_center = @as(f32, @floatFromInt(sample.traversable_bounds.min)) + 0.5;
            const max_lane_center = @as(f32, @floatFromInt(sample.traversable_bounds.max)) + 0.5;
            self.lane_center = std.math.clamp(self.lane_center, min_lane_center, max_lane_center);
            self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
            self.resolved_lane_index = self.lane_index;
        }
    }

    fn applyReplayDirective(self: *Runner, preview: *const track.LoadedLevelPreview, replay: ReplayDirective) void {
        if (!replay.active) return;
        if (replay.lateral_world_x) |raw_world_x| {
            if (self.phase != .active or self.movement_mode != .track or self.attachment.launch.active) return;
            const world_x = std.math.clamp(raw_world_x, replay_world_x_min, replay_world_x_max);
            self.replay_state.world_x_override = world_x;
            self.lane_center = laneCenterFromWorldX(preview, world_x);
            const lane_index = preview.laneIndexAtWorldX(world_x);
            self.lane_index = lane_index;
            self.resolved_lane_index = lane_index;
        }

        self.replay_state.raw_flag_bits = replay.raw_flag_bits;
        self.replay_state.track_state_latch = (replay.raw_flag_bits & 0x04) != 0;
        if ((replay.raw_flag_bits & 0x08) != 0) {
            self.replay_state.fade_requested = true;
        }
    }

    fn currentReplayWorldX(self: *const Runner) ?f32 {
        if (self.phase != .active) return null;
        if (self.movement_mode != .track) return null;
        if (self.attachment.launch.active) return null;
        return self.replay_state.world_x_override;
    }

    fn advanceMovement(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or self.finished) return;

        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            self.advanceAttachmentFollow(preview);
            return;
        }

        self.advanceTrackMovementByRows(preview, self.track_step_rows);
    }

    fn advanceTrackMovementByRows(self: *Runner, preview: *const track.LoadedLevelPreview, step_rows: f32) void {
        if (preview.total_rows == 0 or self.finished) return;
        if (self.movement_mode != .track) return;

        self.applyTrackPosition(motion_module.advanceTrackPosition(
            preview,
            self.runtime_track_index,
            self.track_row_progress,
            step_rows,
        ));
    }

    fn syncRowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.applyTrackPosition(motion_module.syncTrackPosition(
            preview,
            self.runtime_track_index,
            self.track_row_progress,
        ));
    }

    fn applyTrackPosition(self: *Runner, position: motion_module.TrackPosition) void {
        self.runtime_track_index = position.runtime_track_index;
        self.track_row_progress = position.row_progress;
        self.row_position = position.row_position;
    }

    fn sampleRow(self: *const Runner, preview: *const track.LoadedLevelPreview, global_row: usize) ?RowSample {
        const row_location = preview.locateRow(global_row) orelse return null;
        const traversable = preview.laneBoundsForRow(row_location);
        const row_width = @min(row_location.row.cells.len, preview.max_width);
        if (row_width == 0) return null;
        const desired_lane = if (self.currentReplayWorldX()) |world_x|
            @min(preview.laneIndexAtWorldX(world_x), row_width - 1)
        else
            std.math.clamp(
                laneIndexForLaneCenter(preview, self.lane_center),
                traversable.min,
                traversable.max,
            );

        var resolved_lane_index = desired_lane;
        var path_center_lane: ?f32 = null;
        const path_bounds = preview.pathBoundsForRow(row_location);
        if (path_bounds) |bounds| {
            path_center_lane = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
        }

        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            const target_lane_center = std.math.clamp(
                self.attachment.follow.cached_output_lane_center,
                @as(f32, @floatFromInt(traversable.min)) + 0.5,
                @as(f32, @floatFromInt(traversable.max)) + 0.5,
            );
            const target_lane = @as(usize, @intFromFloat(@floor(target_lane_center - 0.5)));
            resolved_lane_index = std.math.clamp(target_lane, traversable.min, traversable.max);
        }

        const cell = row_location.row.cells[resolved_lane_index];
        const annotation = row_location.row.annotation;
        const runtime_tile_hint = preview.runtimeTileAt(global_row, resolved_lane_index) orelse track.confirmedRuntimeTileHint(cell);
        const gameplay_cell = if (runtime_tile_hint) |tile_type|
            track.runtimeGameplayCellKindForTile(tile_type, preview.runtime_build_flags) orelse track.gameplayCellKind(cell)
        else
            track.gameplayCellKind(cell);
        return .{
            .global_row = global_row,
            .traversable_bounds = traversable,
            .path_bounds = path_bounds,
            .resolved_lane_index = resolved_lane_index,
            .cell = cell,
            .gameplay_cell = gameplay_cell,
            .runtime_tile_hint = runtime_tile_hint,
            .annotation = annotation,
            .path_center_lane = path_center_lane,
            .path_name = preview.activePathNameAtRow(global_row),
        };
    }

    fn currentRuntimeSample(self: *const Runner, preview: *const track.LoadedLevelPreview) ?RowSample {
        if (preview.total_rows == 0) return null;
        return self.sampleRow(preview, currentRowIndex(preview, self.row_position));
    }

    fn processVisitedRows(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;
        const current_row = currentRowIndex(preview, self.row_position);
        const last_row = self.last_processed_row orelse {
            self.last_processed_row = current_row;
            return;
        };
        if (current_row < last_row) {
            self.last_processed_row = current_row;
            return;
        }

        var row = last_row + 1;
        while (row <= current_row) : (row += 1) {
            self.processRow(preview, row);
        }
        self.last_processed_row = current_row;
    }

    fn processRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const sample = self.sampleRow(preview, global_row) orelse return;
        const runtime_row_flags = preview.runtimeRowFlagsAt(global_row);

        if (sample.annotation) |annotation| {
            switch (annotation) {
                .path => |path_name| {
                    if (self.movement_mode == .attachment) {
                        self.attachment.path_name = path_name;
                    }
                },
                .ring => |ring_kind| {
                    if (sample.gameplay_cell) |kind| {
                        if (kind == .ring and !self.hasRuntimeRingEffect(global_row, sample.resolved_lane_index) and !nativeRingAnnotationHandledByRuntime(sample.runtime_tile_hint, runtime_row_flags)) {
                            self.recordRing(preview, ring_kind);
                        }
                    }
                },
                .parcel => {},
                .jetpack_off => {
                    self.counters.jetpack_off_rows += 1;
                    self.recent_event = .jetpack_off;
                },
                .no_fall => {
                    self.counters.no_fall_rows += 1;
                    self.recent_event = .no_fall;
                },
                .model => {},
            }
        }

        // PORT(partial): attached travel and supertramp-style launch are still driven from the
        // built attachment surface, not the original installed collision volumes. Until the
        // remaining local-frame collision ownership is ported, do not consume floor-level
        // gameplay cells beneath the rider while attached or airborne off an attachment.
        if (self.movement_mode == .attachment or self.attachment.launch.active) return;

        if (sample.cell == '=') {
            self.counters.turret_hits += 1;
            self.recent_event = .turret_hit;
            self.beginFallState(preview, .hazard, cutscene_death_id);
            return;
        }

        const gameplay_cell = sample.gameplay_cell orelse return;
        switch (gameplay_cell) {
            .attachment_probe => {
                if (self.movement_mode == .track) {
                    self.recent_event = .attachment_probe;
                }
            },
            .attachment_entry => {},
            .ring => {},
            .trampoline => {
                self.counters.trampoline_rows += 1;
                self.recent_event = .trampoline;
            },
            .health => {},
            .jetpack => {},
            .garbage => {},
            .salt => {},
            .slug => {
                if (self.isSlugDefeated(global_row, sample.resolved_lane_index)) return;
                if (self.presentation.invincible_ticks > 0) {
                    // PORT(verified):
                    // `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:179-182`
                    // takes the invincible-path slug contact through `kill_slug_hazard`
                    // without `add_subgoldy_score`.
                    self.defeatSlugSilent(global_row, sample.resolved_lane_index);
                    return;
                }
                self.counters.slug_hits += 1;
                self.recent_event = .slug_hit;
                if (self.damage.slug_hit_active) {
                    // PORT(verified): repeat-hit branch at
                    // `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:183-188`.
                    // Native writes `velocity.z = track_center_x^2 * 0.004 * -8` into the
                    // player's `+0x418` lane (`-0.512` with the fixed `track_center_x = 4`)
                    // and immediately calls `apply_damage_gauge_delta(+1.0, 0)`. The
                    // port folds `velocity.z` into the one-shot
                    // `native_velocity_z_override_per_tick` lane that the existing
                    // ring-hit knockback already uses.
                    self.native_velocity_z_override_per_tick =
                        native_track_center_x * native_track_center_x * 0.0040000002 * -8.0;
                    self.applyDamageGaugeDelta(1.0);
                    return;
                }
                // PORT(verified): first-hit branch at
                // `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:190-221`.
                // Native stamps the player velocity triplet before arming
                // `begin_post_follow_carryover` and entering cutscene state `10`:
                //   velocity.x = 0 (player + 0x410)
                //   velocity.y = track_center_x * 0.2 (player + 0x414, = 0.8)
                //   velocity.z = track_center_x * -0.2 (player + 0x418, = -0.8)
                // and clears `follow_state.active`. `clearAttachmentFollow` inside
                // `beginFallState` mirrors the follow clear; the velocity writes
                // need to happen before that transition so the fall phase picks up
                // a non-zero vertical velocity as its initial knockback impulse.
                // Side effects not yet ported: the slug slot's `+0x85 = 1` flag, the
                // randomized `play_slug_voice(34 - rand())` call, and the
                // `firework_shoot(...)` burst land with the slug pool and
                // firework/sfx ports.
                self.native_velocity_x_per_tick = 0.0;
                self.velocity_y = native_track_center_x * 0.2;
                self.native_velocity_z_override_per_tick = native_track_center_x * -0.2;
                self.damage.slug_hit_active = true;
                self.beginFallState(preview, .hazard, cutscene_death_id);
            },
        }
    }

    fn endAttachmentIfNeeded(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode != .attachment or !self.attachment.follow.active or preview.total_rows == 0) return;
        if (self.currentAttachmentBuilt(preview)) |built| {
            if (self.attachmentShouldSideExit(built)) {
                self.beginFallState(preview, .fall, cutscene_none_id);
                return;
            }
            if (self.attachment.follow.sample_index >= built.template.sample_count) {
                self.commitAttachmentNaturalExit(preview, built);
                if (self.shouldRetireAttachmentDirectlyForCompletion(preview)) {
                    self.finishAttachmentFollowDirect();
                } else {
                    self.finishAttachmentFollowWithExitHandoff(preview);
                }
            }
            return;
        }
        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse return;
        if (sample.path_center_lane != null) return;

        if (self.shouldRetireAttachmentDirectlyForCompletion(preview)) {
            self.finishAttachmentFollowDirect();
            return;
        }
        self.finishAttachmentFollowWithExitHandoff(preview);
    }

    fn recordRing(self: *Runner, preview: *const track.LoadedLevelPreview, ring_kind: segment.RingKind) void {
        self.applyRingEffect(preview, ring_kind, switch (ring_kind) {
            .none, .slow => false,
            .normal, .powerup, .explode => true,
        });
    }

    fn recordNativeRingEffect(self: *Runner, preview: *const track.LoadedLevelPreview, effect_kind: u8) void {
        const ring_kind = nativeRingEventLabel(effect_kind) orelse return;
        self.last_native_ring_effect_kind = effect_kind;
        self.native_ring_effect_token +%= 1;
        if (effect_kind == 3 or effect_kind == 7) {
            self.applyNativeNegativeVelocityRing();
            return;
        }
        self.applyRingEffect(preview, ring_kind, nativeRingEventScores(effect_kind));
    }

    // PORT(verified): `handle_subgoldy_collisions` writes `-0.1` directly into
    // `player->velocity.z` for native ring kinds `3/7`, and `update_subgoldy` then recovers
    // that negative lane by `track_center_x^2 * 0.004 * 0.25` each tick until it crosses 0.
    // Positive `velocity.z` carry now shares this lane for first-block and floor-cache
    // acceleration; the fixed rows-per-second scalar remains the lower bound until the
    // remaining native speed owner is fully retired.
    fn applyNativeNegativeVelocityRing(self: *Runner) void {
        self.counters.ring_slow += 1;
        self.native_velocity_z_override_per_tick = native_negative_ring_velocity_z_per_tick;
        self.recent_event = .{ .ring = .slow };
    }

    fn applyRingEffect(self: *Runner, preview: *const track.LoadedLevelPreview, ring_kind: segment.RingKind, award_score: bool) void {
        switch (ring_kind) {
            .none => {},
            .normal => self.counters.ring_normal += 1,
            .powerup => {
                self.counters.ring_powerup += 1;
                self.recordPowerupRing();
            },
            .explode => {
                self.counters.ring_explode += 1;
                self.triggerExplodeRing(preview);
            },
            .slow => {
                self.counters.ring_slow += 1;
                self.presentation.slow_ticks = slow_ring_duration_ticks;
            },
        }
        if (award_score) {
            self.recordScore(&self.score.ring_collect, 100);
        }
        if (ring_kind != .none) {
            self.recent_event = .{ .ring = ring_kind };
        }
    }

    pub fn applyCompletionBonus(self: *Runner, parcel_target: usize) void {
        self.row_event_display.reconfigureCompletion(parcel_target, true);
        self.maybeAwardRowEventCompletionBonus();
    }

    pub fn flushPendingParcelDeliveries(self: *Runner) void {
        for (&self.parcel.slots) |*parcel| {
            if (!parcel.active() or parcel.state == 1) continue;
            parcel.state = 0;
        }
        while (self.row_event_display.delivered_parcel_count < self.counters.parcels) {
            self.registerParcelDelivery();
        }
        self.row_event_display.resetTransient();
        self.parcel.home_anchor = .{};
    }

    fn recordScore(self: *Runner, slot: *u32, points: u32) void {
        const previous_total = self.score.total;
        score_module.add(&self.score, slot, points);
        self.recent_score_award = points;
        self.recent_score_award_ticks = 45;
        self.updateVisibleLifeStockFromScore(previous_total, self.score.total);
    }

    fn registerParcelDelivery(self: *Runner) void {
        if (self.row_event_display.delivered_parcel_count == self.row_event_display.parcel_target_count) return;
        self.row_event_display.delivered_parcel_count += 1;
        self.row_event_display.display_token +%= 1;
        self.recordScore(&self.score.parcel_register, parcel_delivery_register_score);
        if (self.row_event_display.delivered_parcel_count == self.row_event_display.parcel_target_count) {
            self.maybeAwardRowEventCompletionBonus();
            self.row_event_display.staged_parcel_count = self.row_event_display.delivered_parcel_count;
            self.row_event_display.state = .final_delivery_delay;
            self.row_event_display.progress = 0.0;
            self.row_event_display.progress_step = row_event_display_final_delay_progress_step;
            return;
        }

        self.armRowEventStagingIfNeeded();
        if (self.row_event_display.state != .staging) {
            self.row_event_display.state = .hold;
            self.row_event_display.progress = 0.0;
            self.row_event_display.progress_step = row_event_display_hold_progress_step;
        }
    }

    fn processTrackParcelCollisions(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const player_position = self.trackParcelPlayerAnchor(preview);
        for (&self.parcel.slots) |*parcel| {
            if (parcel.state != 1) continue;

            const delta_x = parcel.world_position.x - player_position.x;
            const delta_y = parcel.world_position.y - player_position.y;
            const delta_z = parcel.world_position.z - player_position.z;
            if (delta_z >= 1.0) continue;

            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            if (distance >= 1.24) continue;

            if (!self.collectParcelRow(parcel.row)) {
                parcel.state = 0;
                continue;
            }

            self.counters.parcels += 1;
            self.recordScore(&self.score.parcel_pickup, 100);
            self.recent_event = .{ .parcel = parcel.parcel_id };
            self.parcel.home_anchor = .{
                .active = true,
                .world_position = player_position,
            };
            parcel.state = 4;
            return;
        }
    }

    fn hasPendingRowEventParcelStage(self: *const Runner) bool {
        return self.counters.parcels > self.row_event_display.staged_parcel_count;
    }

    fn hasActiveRowEventDeliveryParcel(self: *const Runner) bool {
        for (self.parcel.slots) |parcel| {
            if (parcel.state == 6 or parcel.state == 7) return true;
        }
        return false;
    }

    fn armRowEventStagingIfNeeded(self: *Runner) void {
        self.row_event_display.armStagingIfNeeded(
            self.hasPendingRowEventParcelStage(),
            self.hasActiveRowEventDeliveryParcel(),
        );
    }

    fn spawnRowEventDeliveryParcel(self: *Runner) bool {
        const slot = self.allocateTrackParcelSlot() orelse return false;
        const home_anchor = self.currentTrackParcelHomeAnchor();
        slot.* = .{
            .state = 6,
            .row = std.math.maxInt(usize),
            .world_position = home_anchor,
            .presentation_position = home_anchor,
            .flight_anchor = home_anchor,
        };
        return true;
    }

    fn processRuntimeHazardCollisions(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const player_position = self.worldPosition(preview, 0.4);

        // PORT(verified): salt collisions resolve against the dedicated
        // `cRSalt`-shaped pool first. Native `handle_subgoldy_collisions`
        // iterates the 40-slot pool with `dist < 0.98` + `z < 1.0` gates
        // and consumes the slot via `deactivate_salt_hazard`.
        for (&self.runtime.salts.slots) |*slot| {
            if (slot.state != .active) continue;
            const delta_x = player_position.x - slot.world_position.x;
            const delta_y = player_position.y - slot.world_position.y;
            const delta_z = player_position.z - slot.world_position.z;
            if (@abs(delta_z) > runtime_hazard_collision_z_tolerance) continue;
            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            if (distance > salt_collision_distance_threshold) continue;

            self.counters.salt_hits += 1;
            self.last_salt_hit_position = slot.world_position;
            self.applyDamageGaugeDelta(salt_damage_delta);
            self.recent_event = .salt_hit;
            self.runtime.salts.deactivate(slot);
            return;
        }

        // PORT(verified): SubLazer projectile collisions follow
        // `handle_subgoldy_collisions`
        // (`artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:122-126`):
        // `z < 1.0 && dist < 0.49`, slot transitions to `removing` state
        // (native writes `state = 2`), and the damage gauge takes
        // `+0.02f`. No attachment/invincible gate — SubLazer shots are
        // the only damage source that pierces those gates in native.
        for (&self.runtime.sub_lazers.slots) |*slot| {
            if (slot.state != .active) continue;
            const delta_x = player_position.x - slot.world_position.x;
            const delta_y = player_position.y - slot.world_position.y;
            const delta_z = player_position.z - slot.world_position.z;
            if (@abs(delta_z) > runtime_hazard_collision_z_tolerance) continue;
            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            if (distance > native_sub_lazer_collision_distance_threshold) continue;

            self.applyDamageGaugeDelta(native_sub_lazer_damage_delta);
            slot.state = .removing;
            return;
        }

        var index: usize = 0;
        while (index < self.runtime.hazards.count) {
            const hazard = &self.runtime.hazards.slots[index];
            if (hazard.state != .active) {
                index += 1;
                continue;
            }
            const hazard_position = hazard.world_position;
            const delta_x = player_position.x - hazard_position.x;
            const delta_y = player_position.y - hazard_position.y;
            const delta_z = player_position.z - hazard_position.z;
            if (@abs(delta_z) > runtime_hazard_collision_z_tolerance) {
                index += 1;
                continue;
            }
            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            if (distance > garbage_collision_distance_threshold) {
                index += 1;
                continue;
            }
            self.counters.garbage_hits += 1;
            self.last_garbage_hit_position = hazard_position;
            self.recordScore(&self.score.garbage_collision, 10);
            self.applyGarbageImpact(preview, hazard_position);
            self.applyDamageGaugeDelta(garbage_damage_delta);
            self.recent_event = .garbage_hit;
            self.beginGarbageBurst(hazard, player_position);
            return;
        }
    }

    // PORT(partial): Windows resolves health and jetpack against their live runtime pickup
    // slots in `handle_subgoldy_collisions`, not by consuming authored rows on crossing.
    // The runner now mirrors the recovered distance and height gates from those runtime
    // slots, the health pickup bob lane, and the jetpack pickup's ramp-side spawn bias,
    // but it still omits the dedicated health particle bod owner and the broader hover
    // presentation/runtime around `cRSubHover`.
    fn processRuntimePickupCollisions(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const player_position = self.playerWorldPosition(preview);
        if (player_position.y < attachment_entry_rider_height) return;

        var index: usize = 0;
        while (index < self.runtime.pickups.count) {
            const pickup = self.runtime.pickups.slots[index];
            const delta_x = pickup.world_position.x - player_position.x;
            const delta_y = pickup.world_position.y - player_position.y;
            const delta_z = pickup.world_position.z - player_position.z;
            if (delta_z >= runtime_hazard_collision_z_tolerance) {
                index += 1;
                continue;
            }

            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            const collided = switch (pickup.kind) {
                .health => @abs(delta_y) < runtime_health_collision_y_tolerance and
                    distance < runtime_health_collision_distance_threshold,
                .jetpack => distance < runtime_jetpack_collision_distance_threshold,
            };
            if (!collided) {
                index += 1;
                continue;
            }

            switch (pickup.kind) {
                .health => {
                    self.counters.health_pickups += 1;
                    self.last_health_pickup_position = pickup.world_position;
                    self.applyDamageGaugeDelta(health_recover_delta);
                    self.recent_event = .health_pickup;
                },
                .jetpack => {
                    self.counters.jetpack_pickups += 1;
                    self.armJetpackGauge();
                    self.recent_event = .jetpack_pickup;
                },
            }
            self.removeRuntimePickupAt(index);
        }
    }

    // PORT(partial): native ring and special-effect pickups resolve from the live 2-slot
    // runtime pool inside `handle_subgoldy_collisions`, not from row traversal. The runner
    // now mirrors that ownership, the recovered `delta_z < 1.0 && distance < 0.98`
    // collision gate, and the post-hit `state 2 -> 3` follow animation instead of removing
    // the slot immediately. The current evidence-capped split is deliberate: presentation
    // now follows the native slot spawn anchor from `spawn_track_ring_or_special_effect`,
    // while collisions still use the earlier lower proxy anchor until the player-height
    // parity gap closes.
    fn processRuntimeRingEffectCollisions(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const player_position = self.playerWorldPosition(preview);
        var index: usize = 0;
        while (index < self.runtime.rings.count) {
            const effect = self.runtime.rings.slots[index];
            if (effect.state != .active) {
                index += 1;
                continue;
            }
            const delta_x = effect.collision_position.x - player_position.x;
            const delta_y = effect.collision_position.y - player_position.y;
            const delta_z = effect.collision_position.z - player_position.z;
            if (delta_z >= runtime_hazard_collision_z_tolerance) {
                index += 1;
                continue;
            }

            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            if (distance >= runtime_health_collision_distance_threshold) {
                index += 1;
                continue;
            }

            if (self.currentRuntimeSample(preview)) |sample| {
                self.current_global_row = sample.global_row;
                self.resolved_lane_index = sample.resolved_lane_index;
            }

            self.recordNativeRingEffect(preview, effect.kind);
            self.runtime.rings.slots[index].state = .collect_setup;
            return;
        }
    }

    // PORT(partial): Windows only writes garbage-hit motion when Goldy is not invincible.
    // The contact branch uses the normalized hazard-to-player vector, seeds
    // `velocity.x -= contact.x * velocity.z * 0.18`, and then lets `update_subgoldy`
    // apply and damp that lane once per grounded track tick. The port now mirrors that
    // lateral owner in track mode and reads the current fixed scalar as the velocity-z
    // floor while the recovered native positive lane is still being widened.
    fn applyGarbageImpact(self: *Runner, preview: *const track.LoadedLevelPreview, impact_position: rl.Vector3) void {
        const player_position = self.worldPosition(preview, 0.4);
        const delta_x = impact_position.x - player_position.x;
        const delta_y = impact_position.y - player_position.y;
        const delta_z = impact_position.z - player_position.z;
        const distance = @max(@sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z)), 0.0001);
        const delta_x_normalized = delta_x / distance;
        const delta_z_normalized = delta_z / distance;
        const speed_before = self.speed_rows_per_second;

        if (self.presentation.invincible_ticks > 0) return;

        self.speed_rows_per_second = std.math.clamp(
            speed_before - (delta_z_normalized * speed_before * 0.10),
            2.0,
            48.0,
        );

        if (self.movement_mode == .attachment and self.attachment.follow.active) {
            self.attachment.follow.lateral_offset -= delta_x_normalized * speed_before * 0.18;
            return;
        }

        const velocity_z_per_tick = speed_before / native_ticks_per_second;
        self.native_velocity_x_per_tick -= delta_x_normalized * velocity_z_per_tick * 0.18;
    }

    fn beginGarbageBurst(self: *Runner, hazard: *RuntimeHazard, player_position: rl.Vector3) void {
        _ = self;
        if (hazard.kind != .garbage or hazard.state != .active) return;
        hazard.state = .burst_setup;
        hazard.collision_side = if (hazard.world_position.x >= player_position.x) 1 else -1;
    }

    fn applyDamageGaugeDelta(self: *Runner, delta: f32) void {
        self.damage.applyDelta(delta, &self.presentation.snail_skin);
    }

    fn maybeAwardRowEventCompletionBonus(self: *Runner) void {
        if (self.score.completion_bonus != 0 or !self.row_event_display.bonus_enabled) return;
        if (self.row_event_display.parcel_target_count == 0 or
            self.row_event_display.delivered_parcel_count < self.row_event_display.parcel_target_count) return;

        self.recordScore(&self.score.completion_bonus, postal_completion_bonus_score);
    }

    fn startDamageWarningActor(self: *Runner) void {
        self.damage.warning_actor.start();
    }

    fn stopDamageWarningActor(self: *Runner) void {
        self.damage.warning_actor.stop();
    }

    fn updateDamageWarningActor(self: *Runner) void {
        self.damage.warning_actor.tick();
    }

    fn updateDamageGaugeController(self: *Runner) void {
        self.damage.updateController(&self.presentation.snail_skin);
    }

    fn updateDamageWarning(self: *Runner) void {
        self.damage.update(&self.presentation.snail_skin);
    }

    pub fn damageGaugeWarningOverlayAlpha(self: *const Runner) f32 {
        return self.damage.overlayAlpha();
    }

    pub fn damageWarningActorAlpha(self: *const Runner) f32 {
        return self.damage.actorAlpha();
    }

    pub fn damageGaugeDisplayFill(self: *const Runner) f32 {
        return self.damage.displayFill();
    }

    fn effectiveSpeedRowsPerSecond(self: *const Runner) f32 {
        if (self.native_velocity_z_override_per_tick) |velocity_z| {
            const native_rows_per_second = velocity_z * native_ticks_per_second;
            if (native_rows_per_second < 0.0) return native_rows_per_second;
            return @max(self.baseEffectiveSpeedRowsPerSecond(), native_rows_per_second);
        }
        return self.baseEffectiveSpeedRowsPerSecond();
    }

    fn baseEffectiveSpeedRowsPerSecond(self: *const Runner) f32 {
        if (self.presentation.slow_ticks > 0) return self.speed_rows_per_second * 0.5;
        return self.speed_rows_per_second;
    }

    fn updateNativeVelocityZOverride(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        var velocity_z = self.native_velocity_z_override_per_tick orelse 0.0;
        const had_velocity = self.native_velocity_z_override_per_tick != null;
        const started_negative = velocity_z < 0.0;
        var accelerated = false;

        const tick_scale = delta_seconds * native_ticks_per_second;

        if (velocity_z < 0.0) {
            velocity_z += native_negative_ring_velocity_recovery_z_per_tick * tick_scale;
            if (velocity_z >= 0.0) velocity_z = 0.0;
        }

        if (!started_negative and self.phase == .active and self.movement_mode == .track) {
            if (self.row_position < @as(f32, @floatFromInt(preview.runtime_active_row_start))) {
                velocity_z += native_start_block_velocity_z_delta_per_tick * tick_scale;
                if (velocity_z > native_start_block_velocity_z_max_per_tick) {
                    velocity_z = native_start_block_velocity_z_max_per_tick;
                }
                accelerated = true;
            }

            if (self.currentTileAddsNativeForwardVelocity(preview) or self.jetpack.active) {
                velocity_z += native_floor_cache_velocity_z_delta_per_tick * tick_scale;
                accelerated = true;
            }
        }

        if (velocity_z >= 0.0) {
            if (velocity_z > 0.0 and self.attachment.exit.pending and !self.currentRowHasRuntimeFlag(preview, track.runtime_row_flag_no_fall) and !self.jetpack.active) {
                velocity_z *= native_attachment_exit_z_damping_per_tick;
            }
            if (velocity_z > 0.0 and !self.post_trampoline_airborne) {
                velocity_z *= native_velocity_yz_decay_per_tick;
            }
            const native_rows_per_second = velocity_z * native_ticks_per_second;
            if (velocity_z <= 0.000001 or (!accelerated and !self.attachment.exit.pending and native_rows_per_second <= self.baseEffectiveSpeedRowsPerSecond())) {
                self.native_velocity_z_override_per_tick = null;
                return;
            }
            self.native_velocity_z_override_per_tick = velocity_z;
            return;
        }

        if (!had_velocity and !accelerated) {
            self.native_velocity_z_override_per_tick = null;
            return;
        }
        self.native_velocity_z_override_per_tick = velocity_z;
    }

    fn currentTileAddsNativeForwardVelocity(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        const tile = preview.runtimeTileAt(self.current_global_row, self.resolved_lane_index) orelse return false;
        return switch (tile) {
            0x0f, 0x10, 0x12, 0x13 => true,
            else => false,
        };
    }

    fn currentRowHasRuntimeFlag(self: *const Runner, preview: *const track.LoadedLevelPreview, flag: u32) bool {
        return (preview.runtimeRowFlagsAt(self.current_global_row) & flag) != 0;
    }

    fn stepNativeVelocityX(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (@abs(self.native_velocity_x_per_tick) <= 0.000001) {
            self.native_velocity_x_per_tick = 0.0;
            return;
        }

        if (self.phase == .active and self.movement_mode == .track and !self.attachment.launch.active and preview.max_width != 0) {
            const unclamped_lane_center = self.lane_center + self.native_velocity_x_per_tick;
            self.lane_center = std.math.clamp(
                unclamped_lane_center,
                0.5,
                @as(f32, @floatFromInt(preview.max_width)) - 0.5,
            );
            self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
            if (self.lane_center != unclamped_lane_center) {
                self.native_velocity_x_per_tick = 0.0;
                return;
            }
        }

        self.native_velocity_x_per_tick *= native_velocity_x_decay_per_tick;
        if (@abs(self.native_velocity_x_per_tick) < 0.0001) {
            self.native_velocity_x_per_tick = 0.0;
        }
    }

    fn refreshCachedCameraTarget(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.refreshRunnerCachedCameraTarget(self, preview);
    }

    // PORT(partial): Windows drives the attachment-side camera lift/FOV envelopes from the
    // player's overall attachment progress, `((player.z - source_cell_row_z) / sample_count_f32)`.
    pub fn currentAttachmentCameraProgress(self: *const Runner, preview: *const track.LoadedLevelPreview) ?AttachmentCameraProgress {
        if (self.movement_mode != .attachment or !self.attachment.follow.active) return null;

        const built = self.currentAttachmentBuilt(preview) orelse return null;
        const template_kind = built.template.spec.template_kind orelse return null;
        const sample_count: f32 = @floatFromInt(built.template.sample_count);
        const template_progress = if (sample_count <= 0.0001)
            0.0
        else
            std.math.clamp(
                (self.playerWorldPosition(preview).z - @as(f32, @floatFromInt(self.attachment.follow.source_cell_row))) / sample_count,
                0.0,
                1.0,
            );

        return .{
            .template_kind = template_kind,
            .template_progress = template_progress,
        };
    }

    fn cameramanAttachmentLiftEnvelope(self: *const Runner, preview: *const track.LoadedLevelPreview) f32 {
        return gameplay_camera.cameramanAttachmentLiftEnvelope(self, preview);
    }

    fn cameramanDesiredFovDegrees(self: *const Runner, preview: *const track.LoadedLevelPreview) f32 {
        return gameplay_camera.cameramanDesiredFovDegrees(self, preview);
    }

    fn refreshCameraRollState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.refreshRunnerCameraRollState(self, preview);
    }

    fn playerWorldPosition(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        return gameplay_camera.playerWorldPosition(self, preview);
    }

    fn cameraHotspotSourceFrameA(self: *const Runner, preview: *const track.LoadedLevelPreview) CameraTransform {
        return gameplay_camera.cameraHotspotSourceFrameA(self, preview);
    }

    fn cameraHotspotSourceFrameB(self: *const Runner, preview: *const track.LoadedLevelPreview) CameraTransform {
        return gameplay_camera.cameraHotspotSourceFrameB(self, preview);
    }

    fn refreshCameraHotspots(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.refreshRunnerCameraHotspots(self, preview);
    }

    fn cutsceneTargetPoint(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        return gameplay_camera.cutsceneTargetPoint(self, preview);
    }

    fn cutsceneLookAtMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, position: rl.Vector3) rl.Matrix {
        return gameplay_camera.cutsceneLookAtMatrix(self, preview, position);
    }

    fn introCutsceneHoldMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Matrix {
        return gameplay_camera.introCutsceneHoldMatrix(self, preview);
    }

    fn introCutsceneBlendMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
        return gameplay_camera.introCutsceneBlendMatrix(self, preview, progress);
    }

    fn completionCutsceneBlendPosition(self: *const Runner, progress: f32) rl.Vector3 {
        return gameplay_camera.completionCutsceneBlendPosition(self, progress);
    }

    fn completionCutsceneBlendMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
        return gameplay_camera.completionCutsceneBlendMatrix(self, preview, progress);
    }

    fn completionCutsceneFixedMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Matrix {
        return gameplay_camera.completionCutsceneFixedMatrix(self, preview);
    }

    fn deathCutsceneBlendPosition(self: *const Runner, progress: f32) rl.Vector3 {
        return gameplay_camera.deathCutsceneBlendPosition(self, progress);
    }

    fn deathCutsceneBlendMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
        return gameplay_camera.deathCutsceneBlendMatrix(self, preview, progress);
    }

    fn deathCutsceneFixedMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Matrix {
        return gameplay_camera.deathCutsceneFixedMatrix(self, preview);
    }

    fn updateCutsceneCamera(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.updateRunnerCutsceneCamera(self, preview);
    }

    fn updateCameraman(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        gameplay_camera.updateRunnerCameraman(self, preview);
    }

    fn stepTemporaryStates(self: *Runner) void {
        if (self.presentation.slow_ticks > 0) self.presentation.slow_ticks -= 1;
        if (self.presentation.invincible_ticks > 0) {
            self.presentation.invincible_ticks -= 1;
            // PORT(verified): native `update_invincible_shell` @ 0x444b70 re-selects
            // `change_snail_skin(..+0x434038, 2, 0f)` every active tick (instant swap to
            // the invincible material slot). The transition snaps to slot 0 on the
            // frame the shell expires.
            self.presentation.snail_skin.change(.invincible, 0.0);
            if (self.presentation.invincible_ticks == 0) {
                self.presentation.snail_skin.change(.default, 0.0);
            }
        }
        if (self.presentation.shot_cooldown_ticks > 0) self.presentation.shot_cooldown_ticks -= 1;
        if (self.recent_score_award_ticks > 0) self.recent_score_award_ticks -= 1;
        if (self.damage.runtime.skin_hold_ticks > 0) self.damage.runtime.skin_hold_ticks -= 1;
        self.presentation.snail_skin.tick();
    }

    fn recordPowerupRing(self: *Runner) void {
        self.advanceMovementFlagSelector();
        if (self.presentation.weapon_level < max_weapon_level) {
            self.presentation.weapon_level += 1;
            return;
        }
        self.presentation.invincible_ticks = invincible_duration_ticks;
    }

    fn advanceMovementFlagSelector(self: *Runner) void {
        if (self.presentation.movement_flag_selector < 8) {
            self.presentation.movement_flag_selector += 1;
        } else if (self.presentation.movement_flag_selector == 8) {
            self.presentation.movement_flag_selector = 7;
        }
        self.presentation.movement_flags = movementFlagsForSelector(self.presentation.movement_flag_selector);
        self.presentation.movement_fire_cooldown_step = movementFireCooldownStepForSelector(self.presentation.movement_flag_selector);
    }

    fn triggerExplodeRing(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        var write_index: usize = 0;
        for (0..self.runtime.hazards.count) |read_index| {
            const hazard = self.runtime.hazards.slots[read_index];
            const row_delta = @abs(@as(i32, @intCast(hazard.row)) - @as(i32, @intCast(self.current_global_row)));
            const lane_delta = @abs(@as(i32, @intCast(hazard.lane)) - @as(i32, @intCast(self.resolved_lane_index)));
            if (hazard.kind == .garbage and row_delta <= 6 and lane_delta <= 2) continue;
            self.runtime.hazards.slots[write_index] = hazard;
            write_index += 1;
        }
        self.runtime.hazards.count = write_index;

        const start_row = self.current_global_row -| 6;
        const end_row = @min(preview.total_rows, self.current_global_row + 7);
        const gameplay_width = preview.max_width;
        const start_lane = self.resolved_lane_index -| 2;
        const end_lane = @min(gameplay_width, self.resolved_lane_index + 3);
        for (start_row..end_row) |global_row| {
            for (start_lane..end_lane) |lane_index| {
                if (self.gameplayCellAt(preview, global_row, lane_index)) |kind| {
                    if (kind == .slug) {
                        self.defeatSlug(global_row, lane_index);
                    }
                }
            }
        }
    }

    fn stepMovementFireCooldown(self: *Runner) void {
        if (self.presentation.movement_fire_cooldown <= 0.0) return;
        self.presentation.movement_fire_cooldown += self.presentation.movement_fire_cooldown_step;
        if (self.presentation.movement_fire_cooldown > 1.0) {
            self.presentation.movement_fire_cooldown = 0.0;
        }
    }

    fn movementFireInputState(self: *const Runner, input: RunnerInput, replay: ReplayDirective) MovementFireInputState {
        _ = self;
        if (replay.active) {
            if ((replay.raw_flag_bits & 0x01) != 0) return .fresh;
            if ((replay.raw_flag_bits & 0x02) != 0) return .repeat;
            return .none;
        }
        if (input.fire_pressed) return .fresh;
        if (input.fire_down) return .repeat;
        return .none;
    }

    fn handleFireInput(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        fire_input_state: MovementFireInputState,
    ) void {
        if ((preview.runtime_build_flags & track.runtime_build_flag_movement_fire) == 0) return;
        if (fire_input_state == .none or self.attachment.exit.pending or self.presentation.movement_fire_cooldown > 0.0) return;
        self.spawnProjectiles(preview);
        self.presentation.shot_cooldown_ticks = 2;
        self.presentation.movement_fire_cooldown = motion_module.movementFlagFireStartProgress(
            self.presentation.movement_fire_cooldown_step,
            fire_input_state == .fresh,
        );
    }

    fn spawnProjectiles(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const origin = self.worldPosition(preview, 0.86);
        const forward = self.worldForward(preview);
        const up = self.worldUp(preview);
        var right = crossVector3(forward, up);
        const right_length = std.math.sqrt((right.x * right.x) + (right.y * right.y) + (right.z * right.z));
        if (right_length > 0.0001) {
            right = .{ .x = right.x / right_length, .y = right.y / right_length, .z = right.z / right_length };
        } else {
            right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
        }
        switch (self.presentation.movement_flags) {
            1, 129 => self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, 0.0, 0.23, 0.12, 0.0),
            2 => {
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, -0.24, 0.11, 0.08, 0.0);
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, 0.24, 0.11, 0.08, 0.0);
            },
            4 => {
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, -0.24, 0.11, 0.08, -turbo_projectile_spread_lateral);
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, 0.24, 0.11, 0.08, turbo_projectile_spread_lateral);
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .turbo, 0.0, 0.23, 0.12, 0.0);
            },
            8 => self.spawnWeaponChannelProjectile(origin, right, up, forward, .laser, 0.24, 0.11, 0.08, 0.0),
            16, 144 => {
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .laser, -0.24, 0.11, 0.08, 0.0);
                self.spawnWeaponChannelProjectile(origin, right, up, forward, .laser, 0.24, 0.11, 0.08, 0.0);
            },
            32, 64, 192 => self.spawnWeaponChannelProjectile(origin, right, up, forward, .rocket, 0.0, 0.23, 0.12, 0.0),
            else => {
                const channel_states = nativeWeaponChannelStates(self.presentation.movement_flags);
                if (channelKindForState(channel_states.left)) |kind| {
                    self.spawnWeaponChannelProjectile(origin, right, up, forward, kind, -0.24, 0.11, 0.08, 0.0);
                }
                if (channelKindForState(channel_states.right)) |kind| {
                    self.spawnWeaponChannelProjectile(origin, right, up, forward, kind, 0.24, 0.11, 0.08, 0.0);
                }
                if (channelKindForState(channel_states.center)) |kind| {
                    self.spawnWeaponChannelProjectile(origin, right, up, forward, kind, 0.0, 0.23, 0.12, 0.0);
                }
            },
        }
    }

    fn channelKindForState(channel_state: u8) ?Projectile.Kind {
        return switch (channel_state) {
            1 => .turbo,
            2 => .laser,
            3 => .rocket,
            else => null,
        };
    }

    fn spawnWeaponChannelProjectile(
        self: *Runner,
        origin: rl.Vector3,
        right: rl.Vector3,
        up: rl.Vector3,
        forward: rl.Vector3,
        kind: Projectile.Kind,
        local_x: f32,
        local_y: f32,
        local_z: f32,
        direction_lateral: f32,
    ) void {
        const spawn_position = offsetPosition(origin, right, up, forward, local_x, local_y, local_z);
        const direction = rl.Vector3{
            .x = forward.x + (right.x * direction_lateral),
            .y = forward.y + (right.y * direction_lateral),
            .z = forward.z + (right.z * direction_lateral),
        };
        self.spawnProjectile(
            kind,
            spawn_position.x,
            spawn_position.y,
            spawn_position.z,
            direction.x,
            direction.y,
            direction.z,
        );
    }

    fn spawnProjectile(self: *Runner, kind: Projectile.Kind, world_x: f32, world_y: f32, world_z: f32, dir_x: f32, dir_y: f32, dir_z: f32) void {
        var slot_index: ?usize = null;
        for (0..max_active_projectiles) |index| {
            if (!self.combat.projectiles.slots[index].active) {
                slot_index = index;
                break;
            }
        }
        const index = slot_index orelse return;
        self.combat.projectiles.slots[index] = .{
            .active = true,
            .kind = kind,
            .world_x = world_x,
            .world_y = world_y,
            .world_z = world_z,
            .dir_x = dir_x,
            .dir_y = dir_y,
            .dir_z = dir_z,
            .speed_rows_per_second = projectileSpeedForKind(kind),
        };
        self.combat.projectiles.slots[index].resetTrail();
        if (index >= self.combat.projectiles.count) {
            self.combat.projectiles.count = index + 1;
        }
    }

    fn updateProjectiles(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        var write_index: usize = 0;
        for (0..self.combat.projectiles.count) |read_index| {
            var projectile = self.combat.projectiles.slots[read_index];
            if (!projectile.active) continue;
            projectile.world_x += projectile.dir_x * projectile.speed_rows_per_second * delta_seconds;
            projectile.world_y += projectile.dir_y * projectile.speed_rows_per_second * delta_seconds;
            projectile.world_z += projectile.dir_z * projectile.speed_rows_per_second * delta_seconds;
            if (self.resolveProjectileHit(preview, &projectile)) continue;
            if (projectile.kind == .enemy_laser) {
                if (projectile.world_z < self.row_position - 8.0) continue;
            } else if (projectile.world_z > @as(f32, @floatFromInt(preview.total_rows + 8))) continue;
            projectile.appendTrailPoint();
            self.combat.projectiles.slots[write_index] = projectile;
            write_index += 1;
        }
        self.combat.projectiles.count = write_index;
        for (write_index..max_active_projectiles) |index| {
            self.combat.projectiles.slots[index].active = false;
        }
    }

    fn resolveProjectileHit(self: *Runner, preview: *const track.LoadedLevelPreview, projectile: *Projectile) bool {
        if (preview.total_rows == 0) return true;
        if (projectile.kind == .enemy_laser) {
            const player_position = self.worldPosition(preview, 0.4);
            if (@abs(projectile.world_z - player_position.z) <= turret_projectile_hit_z_tolerance and
                @abs(projectile.world_x - player_position.x) <= turret_projectile_hit_x_tolerance)
            {
                self.counters.turret_hits += 1;
                self.recent_event = .turret_hit;
                self.beginFallState(preview, .hazard, cutscene_death_id);
                return true;
            }
        }
        const global_row = preview.rowIndexAtWorldZ(projectile.world_z);
        const lane_index = preview.laneIndexAtWorldX(projectile.world_x);
        if (global_row >= preview.total_rows or lane_index >= preview.max_width) return false;

        const row_location = preview.locateRow(global_row) orelse return false;
        const cell = if (lane_index < row_location.row.cells.len) row_location.row.cells[lane_index] else ' ';
        if (isProjectileBlockingCell(cell)) return true;

        // PORT(verified): native `cRSalt` slots block projectiles without
        // being consumed — the port now resolves that against the dedicated
        // `SaltHazardPool` instead of the shared hazard pool.
        if (self.runtime.salts.contains(global_row, lane_index)) {
            return true;
        }

        if (self.consumeRuntimeHazard(global_row, lane_index, .garbage)) {
            self.last_garbage_hit_position = runtimeCellWorldPosition(preview, global_row, lane_index, 0.28);
            return true;
        }

        if (self.gameplayCellAt(preview, global_row, lane_index)) |kind| switch (kind) {
            .slug => {
                if (!self.isSlugDefeated(global_row, lane_index) and self.presentation.weapon_level > 0) {
                    self.defeatSlug(global_row, lane_index);
                    return true;
                }
            },
            else => {},
        };
        return false;
    }

    fn updateTurretFire(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        if (preview.total_rows == 0) return;
        const start_row = currentRowIndex(preview, self.row_position);
        const end_row = @min(start_row + turret_projectile_spawn_rows_ahead, preview.total_rows);
        var next_states: [max_active_turret_states]TurretState = [_]TurretState{.{ .row = 0, .lane = 0 }} ** max_active_turret_states;
        var next_state_count: usize = 0;

        var global_row = start_row;
        while (global_row < end_row) : (global_row += 1) {
            const row_location = preview.locateRow(global_row) orelse continue;
            const width = @min(row_location.row.cells.len, preview.max_width);
            for (0..width) |lane_index| {
                if (row_location.row.cells[lane_index] != '=') continue;
                if (next_state_count >= max_active_turret_states) continue;
                var state = self.findTurretState(global_row, lane_index) orelse TurretState{
                    .row = global_row,
                    .lane = lane_index,
                };
                if (state.flash_ticks > 0) state.flash_ticks -= 1;
                state.seconds += delta_seconds;
                while (state.seconds >= turret_fire_interval_seconds) {
                    state.seconds -= turret_fire_interval_seconds;
                    state.flash_ticks = turret_flash_duration_ticks;
                    const world_x = preview.worldPositionForLane(
                        @as(f32, @floatFromInt(lane_index)) + 0.5,
                        @as(f32, @floatFromInt(global_row)),
                        0.0,
                    ).x;
                    self.spawnProjectile(
                        .enemy_laser,
                        world_x,
                        0.4,
                        @as(f32, @floatFromInt(global_row)),
                        0.0,
                        0.0,
                        -1.0,
                    );
                }
                next_states[next_state_count] = state;
                next_state_count += 1;
            }
        }
        self.combat.turrets.slots = next_states;
        self.combat.turrets.count = next_state_count;
    }

    fn findTurretState(self: *const Runner, row: usize, lane: usize) ?TurretState {
        for (0..self.combat.turrets.count) |index| {
            const state = self.combat.turrets.slots[index];
            if (state.row == row and state.lane == lane) return state;
        }
        return null;
    }

    pub fn turretFlashTicksAt(self: *const Runner, row: usize, lane: usize) u8 {
        if (self.findTurretState(row, lane)) |state| return state.flash_ticks;
        return 0;
    }

    fn gameplayCellAt(self: *const Runner, preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize) ?track.GameplayCellKind {
        _ = self;
        return if (preview.gameplayCellSampleAt(global_row, lane_index)) |sample| sample.kind else null;
    }

    pub fn isSlugDefeated(self: *const Runner, global_row: usize, lane_index: usize) bool {
        for (0..self.defeated_slug_cell_count) |index| {
            const defeated = self.defeated_slug_cells[index];
            if (defeated.row == global_row and defeated.lane == lane_index) return true;
        }
        return false;
    }

    pub fn isParcelCollected(self: *const Runner, global_row: usize) bool {
        return self.parcel.isCollected(global_row);
    }

    pub fn liveTrackParcelAt(self: *const Runner, global_row: usize) ?TrackParcelRuntime {
        const index = self.parcel.findSlotIndex(global_row) orelse return null;
        return self.parcel.slots[index];
    }

    fn collectParcelRow(self: *Runner, global_row: usize) bool {
        return self.parcel.markCollected(global_row);
    }

    fn defeatSlug(self: *Runner, global_row: usize, lane_index: usize) void {
        self.markSlugDefeated(global_row, lane_index, true);
    }

    // PORT(verified): native `handle_subgoldy_collisions` @ 0x44523a takes an invincible
    // slug contact through `kill_slug_hazard` without calling `add_subgoldy_score`. The
    // score-awarding `defeatSlug` is only used by projectile kills and explosive-ring
    // shockwaves; the invincible contact lane marks the slug defeated without score.
    fn defeatSlugSilent(self: *Runner, global_row: usize, lane_index: usize) void {
        self.markSlugDefeated(global_row, lane_index, false);
    }

    fn markSlugDefeated(self: *Runner, global_row: usize, lane_index: usize, award_score: bool) void {
        if (self.isSlugDefeated(global_row, lane_index)) return;
        if (self.defeated_slug_cell_count < max_defeated_slug_cells) {
            self.defeated_slug_cells[self.defeated_slug_cell_count] = .{ .row = global_row, .lane = lane_index };
            self.defeated_slug_cell_count += 1;
        }
        if (award_score) {
            self.recordScore(&self.score.garbage_collision, slug_projectile_kill_score);
        }
    }

    fn findTrackParcelSlotIndex(self: *const Runner, global_row: usize) ?usize {
        return self.parcel.findSlotIndex(global_row);
    }

    fn allocateTrackParcelSlot(self: *Runner) ?*TrackParcelRuntime {
        return self.parcel.allocateSlot();
    }

    fn collectLiveTrackParcel(self: *Runner, global_row: usize) void {
        const index = self.findTrackParcelSlotIndex(global_row) orelse return;
        self.parcel.slots[index].state = 0;
    }

    fn refreshLiveTrackParcels(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;

        const current_row = currentRowIndex(preview, self.row_position);
        const window_start = current_row;
        const window_end = @min(window_start + runtime_track_parcel_spawn_ahead_rows, preview.total_rows);
        if (self.parcel.last_scan_end < window_start or self.parcel.last_scan_end > window_end) {
            self.parcel.last_scan_end = window_start;
        }

        for (self.parcel.last_scan_end..window_end) |global_row| {
            if (self.isParcelCollected(global_row)) continue;
            const row_location = preview.locateRow(global_row) orelse continue;
            const annotation = row_location.row.annotation orelse continue;
            switch (annotation) {
                .parcel => |parcel| self.spawnLiveTrackParcel(preview, row_location, parcel),
                else => {},
            }
        }
        self.parcel.last_scan_end = window_end;
    }

    fn spawnLiveTrackParcel(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        row_location: track.RowLocation,
        parcel: segment.ParcelAnnotation,
    ) void {
        if (self.findTrackParcelSlotIndex(row_location.global_row) != null) return;
        const slot = self.allocateTrackParcelSlot() orelse return;
        const world_position = trackParcelWorldPosition(preview, row_location, parcel.offset);
        const world_row: usize = @intFromFloat(@floor(@max(world_position.z, 0.0)));
        slot.* = .{
            .state = 1,
            .row = row_location.global_row,
            .parcel_id = parcel.id,
            .world_position = world_position,
            .bob_phase = if ((world_row & 1) == 0) 0.5 else 0.0,
            .bob_phase_step = track_parcel_bob_phase_step,
        };
    }

    fn updateTrackParcels(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        for (&self.parcel.slots) |*parcel| {
            if (!parcel.active()) continue;
            switch (parcel.state) {
                1 => {
                    if ((self.row_position - runtime_track_parcel_expiry_margin_rows) >= parcel.world_position.z) {
                        parcel.state = 0;
                        continue;
                    }
                    parcel.bob_phase += parcel.bob_phase_step;
                    if (parcel.bob_phase >= 1.0) {
                        parcel.bob_phase -= 1.0;
                    }
                },
                4 => {
                    self.beginTrackParcelHome(parcel);
                    self.stepTrackParcelHome(preview, parcel);
                },
                5 => self.stepTrackParcelHome(preview, parcel),
                6 => {
                    self.beginTrackParcelDelivery(parcel);
                    self.stepTrackParcelDelivery(preview, parcel);
                },
                7 => self.stepTrackParcelDelivery(preview, parcel),
                else => {},
            }
        }
    }

    fn trackParcelPlayerAnchor(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        const current_row = currentRowIndex(preview, self.row_position);
        const lane_index = laneIndexForLaneCenter(preview, self.lane_center);
        const floor_height = preview.sampleFloorHeightAtGridPosition(
            current_row,
            lane_index,
            self.row_position,
        ) orelse 0.0;
        return preview.worldPositionForLane(self.lane_center, self.row_position, floor_height + 0.4);
    }

    fn currentTrackParcelHomeAnchor(self: *const Runner) rl.Vector3 {
        return self.parcel.home_anchor.world_position;
    }

    fn trackParcelDeliveryTarget(self: *const Runner) rl.Vector3 {
        return .{
            .x = self.row_event_display.widget_world_x,
            .y = self.row_event_display.widget_world_y,
            .z = self.row_event_display.widget_world_z,
        };
    }

    fn beginTrackParcelHome(self: *Runner, parcel: *TrackParcelRuntime) void {
        const bob_offset = std.math.sin(parcel.bob_phase * std.math.tau) * track_parcel_bob_amplitude;
        parcel.world_position.y += bob_offset;
        const home_anchor = self.currentTrackParcelHomeAnchor();
        parcel.flight_anchor = home_anchor;
        const delta = rl.Vector3{
            .x = home_anchor.x - parcel.world_position.x,
            .y = home_anchor.y - parcel.world_position.y,
            .z = home_anchor.z - parcel.world_position.z,
        };
        parcel.progress = 0.0;
        parcel.progress_step = track_parcel_home_progress_step;
        parcel.target_distance = @sqrt((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
        parcel.travel_dir = normalizeVector3(.{
            .x = parcel.world_position.x - home_anchor.x,
            .y = parcel.world_position.y - home_anchor.y,
            .z = parcel.world_position.z - home_anchor.z,
        });
        parcel.state = 5;
    }

    fn trackParcelHomePresentationScale(progress: f32) f32 {
        return track_parcel_presentation_min_scale +
            ((1.0 - progress) * track_parcel_presentation_scale_delta);
    }

    fn stepTrackParcelHome(self: *Runner, preview: *const track.LoadedLevelPreview, parcel: *TrackParcelRuntime) void {
        const home_anchor = parcel.flight_anchor;
        const progress = std.math.clamp(parcel.progress, 0.0, 1.0);
        const remaining_distance = (1.0 - progress) * parcel.target_distance;
        parcel.world_position = .{
            .x = home_anchor.x + (remaining_distance * parcel.travel_dir.x),
            .y = home_anchor.y + (remaining_distance * parcel.travel_dir.y),
            .z = home_anchor.z + (remaining_distance * parcel.travel_dir.z),
        };
        parcel.presentation_position = parcel.world_position;
        const arc = std.math.sin(progress * std.math.pi) * track_parcel_home_arc_height;
        const basis_up = normalizeVector3(self.worldUp(preview));
        parcel.presentation_position.x += basis_up.x * arc;
        parcel.presentation_position.y += basis_up.y * arc;
        parcel.presentation_position.z += basis_up.z * arc;
        parcel.presentation_scale = trackParcelHomePresentationScale(progress);
        parcel.progress += parcel.progress_step;
        if (parcel.progress < 1.0) return;
        parcel.state = 0;
        self.armRowEventStagingIfNeeded();
    }

    fn beginTrackParcelDelivery(self: *Runner, parcel: *TrackParcelRuntime) void {
        const home_anchor = self.currentTrackParcelHomeAnchor();
        parcel.world_position = home_anchor;
        parcel.presentation_position = home_anchor;
        parcel.flight_anchor = home_anchor;
        parcel.progress = 0.0;
        parcel.progress_step = track_parcel_delivery_progress_step;
        const random_x = @as(f32, @floatFromInt(self.nextMathRandomInt15()));
        const random_y = @as(f32, @floatFromInt(self.nextMathRandomInt15()));
        parcel.delivery_offset = .{
            .x = (random_x - math_random_center) * math_random_inv_center,
            .y = 1.0 + ((random_y - math_random_center) * track_parcel_delivery_random_y_scale),
            .z = 0.0,
        };
        parcel.state = 7;
    }

    fn trackParcelDeliveryPresentationScale(progress: f32) f32 {
        return track_parcel_presentation_min_scale + (progress * track_parcel_presentation_scale_delta);
    }

    fn stepTrackParcelDelivery(self: *Runner, preview: *const track.LoadedLevelPreview, parcel: *TrackParcelRuntime) void {
        _ = preview;
        const home_anchor = parcel.flight_anchor;
        const delivery_target = self.trackParcelDeliveryTarget();
        const progress = std.math.clamp(parcel.progress, 0.0, 1.0);
        parcel.world_position = lerpVector3(home_anchor, delivery_target, progress);
        parcel.presentation_position = parcel.world_position;
        parcel.presentation_scale = trackParcelDeliveryPresentationScale(progress);
        const arc = std.math.sin(progress * std.math.pi);
        parcel.presentation_position.x += parcel.delivery_offset.x * arc;
        parcel.presentation_position.y += parcel.delivery_offset.y * arc;
        parcel.presentation_position.z += parcel.delivery_offset.z * arc;
        parcel.progress += parcel.progress_step;
        if (parcel.progress < 1.0) return;
        self.registerParcelDelivery();
        parcel.state = 0;
    }

    pub fn currentRowEventCompletionCellActive(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        const current_sample = self.currentRuntimeSample(preview) orelse return false;
        return preview.runtimeFlagB40At(current_sample.global_row, current_sample.resolved_lane_index);
    }

    // PORT(partial): Windows `update_row_event_display` owns the parcel-delivery widget
    // controller and the post-delivery completion state. The port now mirrors the proven
    // `3 -> 4 -> 5` state path on the gameplay side and uses the rebuilt current-cell
    // completion bit instead of the older authored `'_'` proxy, but it still omits the
    // unresolved widget owner and staged parcel visuals.
    fn stepRowEventBonusPrompt(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.row_event_display.stepBonusPrompt(self.currentRowEventCompletionCellActive(preview));
    }

    fn armRowEventPromptGate(self: *Runner, accept_pressed: bool) void {
        self.row_event_display.armPromptGate(accept_pressed);
    }

    fn stepRowEventProgress(self: *Runner) bool {
        return self.row_event_display.stepProgress();
    }

    fn updateRowEventDisplay(self: *Runner, preview: *const track.LoadedLevelPreview, accept_pressed: bool) void {
        self.updateRowEventWidgetWorld();
        switch (self.row_event_display.state) {
            .inactive, .complete => {},
            .staging => {
                if (!self.stepRowEventProgress()) return;
                if (self.row_event_display.staged_parcel_count >= self.counters.parcels) {
                    self.row_event_display.progress = 0.0;
                    self.row_event_display.state = .hold;
                    self.row_event_display.progress_step = row_event_display_hold_progress_step;
                    return;
                }
                if (!self.spawnRowEventDeliveryParcel()) return;
                self.row_event_display.progress = 0.0;
                self.row_event_display.staged_parcel_count += 1;
                self.row_event_display.state = .hold;
                self.row_event_display.progress_step = row_event_display_hold_progress_step;
            },
            .hold => {
                if (!self.stepRowEventProgress()) return;
                self.row_event_display.progress = 0.0;
                if (self.hasPendingRowEventParcelStage() and !self.hasActiveRowEventDeliveryParcel()) {
                    self.row_event_display.state = .staging;
                    self.row_event_display.progress_step = row_event_display_stage_progress_step;
                }
            },
            .final_delivery => {
                self.row_event_display.gate_18 = 0;
                self.row_event_display.state = .bonus_prompt;
                self.armRowEventPromptGate(accept_pressed);
                self.stepRowEventBonusPrompt(preview);
            },
            .bonus_prompt => {
                self.armRowEventPromptGate(accept_pressed);
                self.stepRowEventBonusPrompt(preview);
            },
            .final_delivery_delay => {
                if (!self.stepRowEventProgress()) return;
                self.row_event_display.progress = 0.0;
                self.row_event_display.state = .final_delivery;
            },
        }
    }

    fn updateRowEventWidgetWorld(self: *Runner) void {
        const camera_transform = normalizeCameraTransform(cameraTransformFromMatrix(self.cameraman.live_matrix));
        const widget_world = offsetPosition(
            camera_transform.position,
            camera_transform.right,
            camera_transform.up,
            camera_transform.forward,
            row_event_widget_local_x,
            row_event_widget_local_y,
            row_event_widget_local_z,
        );
        self.row_event_display.widget_world_x = widget_world.x;
        self.row_event_display.widget_world_y = widget_world.y;
        self.row_event_display.widget_world_z = widget_world.z;
    }

    fn refreshLiveRuntimeHazards(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;

        const window_start = currentRowIndex(preview, self.row_position);
        const window_end = @min(window_start + runtime_hazard_live_window_rows, preview.total_rows);

        self.pruneRuntimeHazards(window_start, window_end);

        var scan_start = @max(window_start, self.runtime.hazards.last_scan_end);
        if (scan_start > window_end) scan_start = window_end;

        var global_row = scan_start;
        while (global_row < window_end) : (global_row += 1) {
            self.scanRuntimeHazardRow(preview, global_row);
        }
        self.runtime.hazards.last_scan_end = window_end;
    }

    fn refreshLiveRuntimePickups(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;

        const window_start = currentRowIndex(preview, self.row_position);
        const window_end = @min(window_start + runtime_pickup_live_window_rows, preview.total_rows);

        self.pruneRuntimePickups(window_start, window_end);

        var scan_start = @max(window_start, self.runtime.pickups.last_scan_end);
        if (scan_start > window_end) scan_start = window_end;

        var global_row = scan_start;
        while (global_row < window_end) : (global_row += 1) {
            self.scanRuntimePickupRow(preview, global_row);
        }
        self.runtime.pickups.last_scan_end = window_end;
    }

    fn updateRuntimeHazards(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        var write_index: usize = 0;
        for (0..self.runtime.hazards.count) |read_index| {
            var hazard = self.runtime.hazards.slots[read_index];
            if (!self.stepRuntimeHazard(preview, &hazard)) continue;
            self.runtime.hazards.slots[write_index] = hazard;
            write_index += 1;
        }
        self.runtime.hazards.count = write_index;

        // PORT(verified): `update_salt_hazard`
        // (`artifacts/ida/functions/004417d0-update_salt_hazard.c`) runs per
        // active slot each tick, advancing lifetime progress and integrating
        // position by velocity. The pool-side `tickActiveSlots` handles that;
        // the attachment-collision/off-track check at native lines 45-91 is
        // not yet wired here (the port already resolves salt contact in
        // `processRuntimeHazardCollisions` against the damage gauge).
        self.runtime.salts.tickActiveSlots();

        // PORT(verified): `update_wall2_ambient_hazard`
        // (`artifacts/ida/functions/0043efb0-update_wall2_ambient_hazard.c`)
        // advances each SubLazer slot's phase + position, then retires the
        // slot when the emitter cell passes behind the player
        // (`get_track_runtime_cell_at_world_z` comparison at native line 47)
        // or the projectile exits the track window. The per-slot physics
        // tick lives on the pool; the emitter-gate retirement fires here
        // where the current runtime row is known.
        self.runtime.sub_lazers.tickActiveSlots();
        self.retireSubLazersBehindPlayer();
        self.maybeFireWall2SubLazersInWindow(preview);
    }

    // PORT(partial): mirrors the recovered Wall2 tile branch inside
    // `wall2_emitter_maybe_fire_sub_lazer` @ 0x439d50. Native runs this from
    // each live runtime row-cell object. The port still discovers candidate
    // emitters from the preview window, but the gate, RNG source, origin,
    // target-z scramble, `delta_z < -4`, and normalized `0.4` velocity now
    // follow the decompile instead of the previous row/lane hash shortcut.
    // The native `cell->flags & 0x2000` owner bit is not exposed in the preview;
    // candidate `0x0e` Wall2 cells stand in for that object-local gate.
    fn maybeFireWall2SubLazersInWindow(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or preview.max_width == 0) return;

        const window_start = currentRowIndex(preview, self.row_position);
        const window_end = @min(window_start + runtime_wall2_emitter_window_rows, preview.total_rows);

        for (window_start..window_end) |global_row| {
            for (0..preview.max_width) |lane_index| {
                const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
                if (tile_type != native_wall2_tile_id) continue;
                if (lane_index > 0 and (preview.runtimeTileAt(global_row, lane_index - 1) orelse 0) == native_wall2_tile_id) {
                    continue;
                }

                if (self.nextMathRandomFloatBelow(100.0) >= native_wall2_spawn_gate_threshold) continue;

                const spawn_position = wall2EmitterSubLazerOrigin(preview, global_row, lane_index);
                const player_position = self.worldPosition(preview, 0.4);
                const target_z = player_position.z +
                    native_wall2_target_z_offset +
                    self.nextMathRandomSignedFloatBelow(native_wall2_target_random_z_span);
                const delta_x = player_position.x - spawn_position.x;
                const delta_y = player_position.y - spawn_position.y;
                const delta_z = target_z - spawn_position.z;
                if (delta_z >= native_wall2_fire_delta_z_threshold) continue;

                const length = @max(@sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z)), 0.0001);
                const inv = native_sub_lazer_speed / length;
                const velocity: rl.Vector3 = .{
                    .x = delta_x * inv,
                    .y = delta_y * inv,
                    .z = delta_z * inv,
                };
                _ = self.runtime.sub_lazers.shoot(global_row, lane_index, spawn_position, velocity, native_track_center_x);
            }
        }
    }

    fn retireSubLazersBehindPlayer(self: *Runner) void {
        for (&self.runtime.sub_lazers.slots) |*slot| {
            if (slot.state != .active) continue;
            // Native native line 47 reads the emitter's runtime cell z and
            // compares to the slot's world position. When the emitter has
            // scrolled off-screen (`emitter_row + trailing_window <
            // row_position`), the slot is destroyed.
            const trailing_window: f32 = 8.0;
            if (@as(f32, @floatFromInt(slot.emitter_row)) + trailing_window < self.row_position) {
                self.runtime.sub_lazers.destroy(slot);
            }
        }
    }

    fn stepRuntimeHazard(self: *Runner, preview: *const track.LoadedLevelPreview, hazard: *RuntimeHazard) bool {
        return switch (hazard.kind) {
            .garbage => self.updateGarbageHazard(preview, hazard),
        };
    }

    fn updateGarbageHazard(self: *Runner, preview: *const track.LoadedLevelPreview, hazard: *RuntimeHazard) bool {
        _ = preview;
        switch (hazard.state) {
            .inactive => return false,
            .active => return true,
            .burst_setup => {
                const speed = @max(self.speed_rows_per_second, 0.0001);
                hazard.state = .burst;
                hazard.velocity = .{
                    .x = ((self.nextMathRandomFloat01() * 0.2) - 0.1) * speed,
                    .y = (0.1 + (self.nextMathRandomFloat01() * 0.2)) * speed,
                    .z = self.nextMathRandomFloat01() * 0.3 * speed,
                };
                if (hazard.collision_side > 0) {
                    hazard.velocity.x = @abs(hazard.velocity.x);
                } else if (hazard.collision_side < 0) {
                    hazard.velocity.x = -@abs(hazard.velocity.x);
                }
                hazard.velocity.x += @as(f32, @floatFromInt(hazard.collision_side)) * speed * garbage_burst_side_bias_scale;
            },
            .burst => {},
        }

        const speed = @max(self.speed_rows_per_second, 0.0001);
        hazard.world_position.x += hazard.velocity.x;
        hazard.world_position.y += hazard.velocity.y;
        hazard.world_position.z += hazard.velocity.z;
        hazard.velocity.y += (speed * speed) * garbage_burst_gravity_scale;
        if (hazard.world_position.y < garbage_burst_teardown_y) return false;
        if (hazard.world_position.z < self.row_position - garbage_burst_trailing_rows) return false;
        return true;
    }

    fn refreshLiveRuntimeRingEffects(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;

        const window_start = currentRowIndex(preview, self.row_position);
        const window_end = @min(window_start + runtime_ring_live_window_rows, preview.total_rows);

        self.pruneRuntimeRingEffects(window_start, window_end);

        var scan_start = @max(window_start, self.runtime.rings.last_scan_end);
        if (scan_start > window_end) scan_start = window_end;

        var global_row = scan_start;
        while (global_row < window_end) : (global_row += 1) {
            self.scanRuntimeRingEffectRow(preview, global_row);
        }
        self.runtime.rings.last_scan_end = window_end;
    }

    fn pruneRuntimeHazards(self: *Runner, window_start: usize, window_end: usize) void {
        var write_index: usize = 0;
        const min_z = @as(f32, @floatFromInt(window_start)) - 8.0;
        const max_z = @as(f32, @floatFromInt(window_end)) + 8.0;
        for (0..self.runtime.hazards.count) |read_index| {
            const hazard = self.runtime.hazards.slots[read_index];
            switch (hazard.state) {
                .active => {
                    if (hazard.row < window_start or hazard.row >= window_end) continue;
                },
                .inactive => continue,
                .burst_setup, .burst => {
                    if (hazard.world_position.z < min_z or hazard.world_position.z > max_z) continue;
                },
            }
            self.runtime.hazards.slots[write_index] = hazard;
            write_index += 1;
        }
        self.runtime.hazards.count = write_index;
    }

    fn pruneRuntimePickups(self: *Runner, window_start: usize, window_end: usize) void {
        var write_index: usize = 0;
        for (0..self.runtime.pickups.count) |read_index| {
            const pickup = self.runtime.pickups.slots[read_index];
            if (pickup.row < window_start or pickup.row >= window_end) continue;
            self.runtime.pickups.slots[write_index] = pickup;
            write_index += 1;
        }
        self.runtime.pickups.count = write_index;
    }

    fn pruneRuntimeRingEffects(self: *Runner, window_start: usize, window_end: usize) void {
        var write_index: usize = 0;
        const min_z = @as(f32, @floatFromInt(window_start)) - 8.0;
        const max_z = @as(f32, @floatFromInt(window_end)) + 8.0;
        for (0..self.runtime.rings.count) |read_index| {
            const effect = self.runtime.rings.slots[read_index];
            switch (effect.state) {
                .active => {
                    if (effect.row < window_start or effect.row >= window_end) continue;
                },
                .collect_setup, .collect_follow, .miss_setup, .miss_expand => {
                    if (effect.presentation_position.z < min_z or effect.presentation_position.z > max_z) continue;
                },
            }
            self.runtime.rings.slots[write_index] = effect;
            write_index += 1;
        }
        self.runtime.rings.count = write_index;
    }

    fn scanRuntimeHazardRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const row_location = preview.locateRow(global_row) orelse return;
        const row_inside_native_spawn_window = runtimeRowInsideNativeSpawnWindow(preview, global_row);

        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                switch (sample.kind) {
                    .garbage => self.addRuntimeHazard(preview, global_row, lane, .garbage),
                    .salt => if (row_inside_native_spawn_window) {
                        self.spawnSaltFromAuthoredCell(preview, global_row, lane);
                    },
                    else => {},
                }
            }

            if (row_inside_native_spawn_window and
                preview.hasGarbageSpawnHintAt(global_row, lane) and
                preview.garbageFallbackNeighborsAllowedAt(global_row, lane) and
                shouldSpawnAmbientHazard(self, preview.garbage_scalar, .garbage))
            {
                self.addRuntimeHazard(preview, global_row, lane, .garbage);
            }
            if (row_inside_native_spawn_window and
                preview.hasSaltSpawnHintAt(global_row, lane) and
                shouldSpawnAmbientHazard(self, preview.salt_scalar, .salt))
            {
                self.spawnSaltFromAmbientHint(preview, global_row, lane);
            }
        }
    }

    fn spawnSaltFromAuthoredCell(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        lane: usize,
    ) void {
        if (self.runtime.salts.contains(global_row, lane)) return;
        self.spawnSaltSlot(preview, global_row, lane);
    }

    fn spawnSaltFromAmbientHint(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        lane: usize,
    ) void {
        if (self.runtime.salts.contains(global_row, lane)) return;
        self.spawnSaltSlot(preview, global_row, lane);
    }

    fn spawnSaltSlot(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        lane: usize,
    ) void {
        // PORT(verified): `spawn_salt_hazard` takes only a Vec3 position.
        // Native reads the cell's anchor position (`cell + 0x10..0x18`) as the
        // spawn anchor; the port mirrors that via `runtimeCellWorldPosition`.
        // Native does not seed velocity at the call site (the slot velocity is
        // whatever the pool init left at 0); authored salt in the shipped
        // tutorial is stationary after spawn apart from the Y oscillation
        // that the renderer samples from `yaw_radians`.
        const position = runtimeCellWorldPosition(preview, global_row, lane, 0.18);
        _ = self.runtime.salts.spawn(
            global_row,
            lane,
            position,
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            native_track_center_x,
            &self.math_random_state,
        );
    }

    fn scanRuntimePickupRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const row_location = preview.locateRow(global_row) orelse return;
        if (!runtimeRowInsideNativeSpawnWindow(preview, global_row)) return;

        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                switch (sample.kind) {
                    .health => self.addRuntimePickup(preview, global_row, lane, .health),
                    .jetpack => self.addRuntimePickup(preview, global_row, lane, .jetpack),
                    else => {},
                }
            }
        }
    }

    fn scanRuntimeRingEffectRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const row_location = preview.locateRow(global_row) orelse return;
        const row_flags = preview.runtimeRowFlagsAt(global_row);
        if ((row_flags & track.runtime_row_flag_ring_none) != 0) return;

        for (row_location.row.cells, 0..) |_, lane_index| {
            const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
            switch (tile_type) {
                0x23 => {
                    const requested_kind = requestedExplicitRuntimeRingKind(row_flags) orelse continue;
                    const target_row = global_row;
                    if (!self.runtimeRingEffectSpawnPositionAllowed(preview, target_row, lane_index)) continue;
                    self.addRuntimeRingEffect(preview, global_row, target_row, lane_index, self.spawnedRuntimeRingKind(requested_kind));
                    self.runtime.rings.last_spawn_z = @floatFromInt(global_row);
                },
                0x02, 0x03, 0x04, 0x05, 0x06, 0x07 => {
                    if (global_row >= preview.runtime_active_row_end) continue;
                    const source_z = @as(f32, @floatFromInt(global_row));
                    if (self.runtime.rings.last_spawn_z + runtime_ring_spacing_rows >= source_z) continue;

                    if (requestedRampSpecialRuntimeRingKind(row_flags)) |requested_kind| {
                        const target_row = global_row + track.ramp_special_ring_forward_row_offset;
                        if (!self.runtimeRingEffectSpawnPositionAllowed(preview, target_row, lane_index)) continue;
                        self.addRuntimeRingEffect(preview, global_row, target_row, lane_index, requested_kind);
                        self.runtime.rings.last_spawn_z = @floatFromInt(target_row);
                        continue;
                    }

                    if (!runtimeRingDefaultKind4Eligible(tile_type, preview.runtime_build_flags)) continue;
                    if (!self.runtimeRingDefaultPassesGate(preview.runtime_build_flags)) continue;

                    const target_row = global_row + track.ramp_default_ring_forward_row_offset;
                    if (!self.runtimeRingEffectSpawnPositionAllowed(preview, target_row, lane_index)) continue;
                    self.addRuntimeRingEffect(preview, global_row, target_row, lane_index, self.spawnedRuntimeRingKind(4));
                    self.runtime.rings.last_spawn_z = source_z;
                },
                0x08, 0x09, 0x0a => {
                    if (global_row >= preview.runtime_active_row_end) continue;
                    const source_z = @as(f32, @floatFromInt(global_row));
                    if (self.runtime.rings.last_spawn_z + runtime_ring_spacing_rows >= source_z) continue;
                    if ((row_flags & track.runtime_row_flag_ring_explode) == 0 and !self.runtimeRingDefaultPassesGate(preview.runtime_build_flags)) {
                        continue;
                    }

                    const target_row = global_row + track.ramp_explode_ring_forward_row_offset;
                    if (!self.runtimeRingEffectSpawnPositionAllowed(preview, target_row, lane_index)) continue;
                    self.addRuntimeRingEffect(preview, global_row, target_row, lane_index, 2);
                    self.runtime.rings.last_spawn_z = source_z;
                },
                else => {},
            }
        }
    }

    fn addRuntimeHazard(self: *Runner, preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: RuntimeHazardKind) void {
        for (0..self.runtime.hazards.count) |index| {
            const hazard = self.runtime.hazards.slots[index];
            if (hazard.row == row and hazard.lane == lane and hazard.kind == kind) return;
        }
        if (self.runtime.hazards.count >= self.runtime.hazards.slots.len) return;

        self.runtime.hazards.slots[self.runtime.hazards.count] = .{
            .row = row,
            .lane = lane,
            .kind = kind,
            .state = .active,
            .world_position = initialRuntimeHazardWorldPosition(preview, row, lane, kind),
            .velocity = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .presentation_scale = runtimeHazardPresentationScale(row, lane, kind),
            .presentation_phase = runtimeHazardPresentationPhase(row, lane, kind),
            .yaw_radians = runtimeHazardYawRadians(row, lane, kind),
            .arming_progress = 1.0,
            .arming_step = 0.0,
            .collision_side = 0,
        };
        self.runtime.hazards.count += 1;
    }

    fn addRuntimePickup(self: *Runner, preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: RuntimePickupKind) void {
        for (0..self.runtime.pickups.count) |index| {
            const pickup = self.runtime.pickups.slots[index];
            if (pickup.row == row and pickup.lane == lane and pickup.kind == kind) return;
        }
        if (self.runtime.pickups.count >= self.runtime.pickups.slots.len) return;
        if (self.activeRuntimePickupCountForKind(kind) >= runtimePickupCapacity(kind)) return;
        const world_position = initialRuntimePickupWorldPosition(preview, row, lane, kind);

        self.runtime.pickups.slots[self.runtime.pickups.count] = .{
            .row = row,
            .lane = lane,
            .kind = kind,
            .world_position = world_position,
            .presentation_position = world_position,
            .bob_phase = initialRuntimePickupBobPhase(row, kind),
            .bob_phase_step = initialRuntimePickupBobPhaseStep(kind),
        };
        self.runtime.pickups.count += 1;
    }

    fn addRuntimeRingEffect(self: *Runner, preview: *const track.LoadedLevelPreview, source_row: usize, row: usize, lane: usize, kind: u8) void {
        if (kind == 0) return;
        for (0..self.runtime.rings.count) |index| {
            const effect = self.runtime.rings.slots[index];
            if (effect.row == row and effect.lane == lane) return;
        }
        if (self.runtime.rings.count >= self.runtime.rings.slots.len) return;

        self.runtime.rings.slots[self.runtime.rings.count] = self.spawnRuntimeRingEffect(
            preview,
            source_row,
            row,
            lane,
            kind,
        );
        self.runtime.rings.count += 1;
    }

    fn spawnRuntimeRingEffect(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        source_row: usize,
        row: usize,
        lane: usize,
        kind: u8,
    ) RuntimeRingEffect {
        const collision_position = collisionRuntimeRingEffectWorldPosition(preview, row, lane, kind);
        var world_position = nativeRuntimeRingEffectWorldPosition(preview, row, lane, kind);
        if (runtimeRingKindUsesRandomizedSpawnX(kind)) {
            world_position.x = (self.nextMathRandomFloat01() - 0.5) * 2.0 * runtime_ring_spawn_random_x_amplitude;
        }
        const active_phase = self.nextMathRandomFloat01() * std.math.tau;
        const seeded_phase_step = self.runtimeRingActivePhaseStep(preview, source_row, kind);
        const active_phase_step = if (self.nextMathRandomFloat01() > 0.5)
            -seeded_phase_step
        else
            seeded_phase_step;
        return .{
            .source_row = source_row,
            .row = row,
            .lane = lane,
            .kind = kind,
            .collision_position = collision_position,
            .world_position = world_position,
            .presentation_position = world_position,
            .presentation_scale = 1.0,
            .movement_flag_selector_snapshot = self.presentation.movement_flag_selector,
            .active_x_oscillation_enabled = runtimeRingKindUsesRandomizedSpawnX(kind),
            .active_phase = active_phase,
            .active_phase_step = active_phase_step,
        };
    }

    fn runtimeHazardPresentationScale(row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
        const seed = runtimeHazardSeed(row, lane, kind);
        const normalized = @as(f32, @floatFromInt(@as(u16, @truncate(seed >> 16)))) / 65535.0;
        return switch (kind) {
            // Android `cRSubGame::AddGarbage` scales garbage with `(RAND(0.4) + 1.0) * 0.6`.
            .garbage => (1.0 + normalized * 0.4) * 0.6,
        };
    }

    fn runtimeHazardPresentationPhase(row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
        const seed = runtimeHazardSeed(row, lane, kind);
        const normalized = @as(f32, @floatFromInt(@as(u16, @truncate(seed)))) / 65535.0;
        return normalized * std.math.tau;
    }

    fn runtimeHazardYawRadians(row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
        return runtimeHazardPresentationPhase(row, lane, kind) - std.math.pi;
    }

    fn initialRuntimeHazardWorldPosition(preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: RuntimeHazardKind) rl.Vector3 {
        return switch (kind) {
            .garbage => runtimeCellWorldPosition(preview, row, lane, runtimeHazardPresentationScale(row, lane, kind)),
        };
    }

    fn initialRuntimePickupWorldPosition(preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: RuntimePickupKind) rl.Vector3 {
        return switch (kind) {
            .health => runtimeCellWorldPosition(preview, row, lane, 0.6),
            .jetpack => runtimeJetpackPickupWorldPosition(preview, row, lane),
        };
    }

    fn runtimeJetpackPickupWorldPosition(preview: *const track.LoadedLevelPreview, row: usize, lane: usize) rl.Vector3 {
        var position = runtimeCellWorldPosition(preview, row, lane, 1.5);
        position.x += runtimeJetpackPickupLateralBias(preview, row, lane);
        return position;
    }

    fn runtimeJetpackPickupLateralBias(preview: *const track.LoadedLevelPreview, row: usize, lane: usize) f32 {
        const edge_mask = preview.runtimeEdgeMaskAt(row, lane) orelse 0;
        return runtimeJetpackPickupLateralBiasFromContext(
            edge_mask & 0x07,
            runtimeTileOrZero(preview, row, lane, -2),
            runtimeTileOrZero(preview, row, lane, -1),
            runtimeTileOrZero(preview, row, lane, 1),
            runtimeTileOrZero(preview, row, lane, 2),
        );
    }

    fn runtimeJetpackPickupLateralBiasFromContext(
        edge_mask_low_bits: u8,
        lane_minus_2_tile: u8,
        lane_minus_1_tile: u8,
        lane_plus_1_tile: u8,
        lane_plus_2_tile: u8,
    ) f32 {
        if (edge_mask_low_bits == 3 and lane_minus_1_tile == 0x0e and lane_plus_2_tile == 0x0e) {
            return 0.5;
        }
        if (edge_mask_low_bits == 4 and lane_minus_2_tile == 0x0e and lane_plus_1_tile == 0x0e) {
            return -0.5;
        }
        return 0.0;
    }

    fn runtimeTileOrZero(preview: *const track.LoadedLevelPreview, row: usize, lane: usize, lane_offset: i32) u8 {
        const source_lane = @as(i32, @intCast(lane));
        const target_lane = source_lane + lane_offset;
        if (target_lane < 0) return 0;
        const lane_index: usize = @intCast(target_lane);
        return preview.runtimeTileAt(row, lane_index) orelse 0;
    }

    fn initialRuntimePickupBobPhase(row: usize, kind: RuntimePickupKind) f32 {
        return switch (kind) {
            .health => if ((row & 1) == 0) 0.5 else 0.0,
            .jetpack => 0.0,
        };
    }

    fn initialRuntimePickupBobPhaseStep(kind: RuntimePickupKind) f32 {
        return switch (kind) {
            .health => runtime_pickup_phase_step,
            .jetpack => 0.0,
        };
    }

    fn updateRuntimePickups(self: *Runner) void {
        for (0..self.runtime.pickups.count) |index| {
            var pickup = &self.runtime.pickups.slots[index];
            pickup.presentation_position = pickup.world_position;
            switch (pickup.kind) {
                .health => {
                    pickup.bob_phase = @mod(pickup.bob_phase + pickup.bob_phase_step, 1.0);
                    pickup.presentation_position.y = pickup.world_position.y +
                        (@sin(pickup.bob_phase * std.math.tau) + 1.0) * runtime_health_pickup_bob_height;
                },
                .jetpack => {},
            }
        }
    }

    fn updateRuntimeRingEffects(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        var index: usize = 0;
        while (index < self.runtime.rings.count) {
            if (!self.updateRuntimeRingEffect(preview, &self.runtime.rings.slots[index])) {
                self.removeRuntimeRingEffectAt(index);
                continue;
            }
            index += 1;
        }
    }

    fn updateRuntimeRingEffect(self: *Runner, preview: *const track.LoadedLevelPreview, effect: *RuntimeRingEffect) bool {
        switch (effect.state) {
            .active => {
                effect.child_update_cadence +%= 1;
                if (effect.child_update_cadence == 3) effect.child_update_cadence = 0;
                if (effect.kind != 3) {
                    effect.active_phase = @mod(effect.active_phase + effect.active_phase_step, std.math.tau);
                    if (effect.active_phase < 0.0) effect.active_phase += std.math.tau;
                }
                if (effect.active_x_oscillation_enabled) {
                    effect.world_position.x = @sin(effect.active_phase) * runtime_ring_spawn_random_x_amplitude;
                }
                effect.presentation_position = effect.world_position;
                effect.presentation_scale = 1.0;

                const player_position = self.playerWorldPosition(preview);
                if (effect.world_position.z >= player_position.z) {
                    if (self.presentation.movement_flag_selector < effect.movement_flag_selector_snapshot) {
                        effect.state = .miss_setup;
                    }
                    return true;
                }
                return false;
            },
            .collect_setup => {
                effect.state = .collect_follow;
                effect.effect_progress = 0.0;
                effect.effect_progress_step = runtimeRingEffectProgressStep();
                return true;
            },
            .collect_follow => {
                effect.effect_progress += effect.effect_progress_step;
                if (effect.effect_progress > 1.0) return false;

                const player_position = self.playerWorldPosition(preview);
                effect.presentation_position.x = ((player_position.x - effect.presentation_position.x) * runtime_ring_effect_collect_lerp) + effect.presentation_position.x;
                effect.presentation_position.y = ((player_position.y - effect.presentation_position.y) * runtime_ring_effect_collect_lerp) + effect.presentation_position.y;
                effect.presentation_position.z = (((player_position.z + runtime_ring_effect_collect_z_offset) - effect.presentation_position.z) * runtime_ring_effect_collect_lerp) + effect.presentation_position.z;
                effect.presentation_scale *= runtime_ring_effect_collect_lerp;
                return true;
            },
            .miss_setup => {
                effect.state = .miss_expand;
                effect.effect_progress = 0.0;
                effect.effect_progress_step = runtimeRingEffectProgressStep();
                return true;
            },
            .miss_expand => {
                effect.effect_progress += effect.effect_progress_step;
                if (effect.effect_progress > 1.0) return false;
                effect.presentation_scale *= runtime_ring_effect_miss_expand_scale;
                return true;
            },
        }
    }

    fn collisionRuntimeRingEffectWorldPosition(preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: u8) rl.Vector3 {
        return runtimeCellWorldPosition(preview, row, lane, runtimeRingCollisionYOffset(kind));
    }

    fn nativeRuntimeRingEffectWorldPosition(preview: *const track.LoadedLevelPreview, row: usize, lane: usize, kind: u8) rl.Vector3 {
        return runtimeCellWorldPosition(preview, row, lane, runtimeRingSpawnYOffset(kind));
    }

    fn runtimeRingCollisionYOffset(kind: u8) f32 {
        return switch (nativeRingEventLabel(kind) orelse .normal) {
            .normal => 0.72,
            .powerup => 0.64,
            .explode => 0.72,
            .slow => 0.5,
            .none => 0.72,
        };
    }

    fn runtimeRingSpawnYOffset(kind: u8) f32 {
        return switch (kind) {
            2 => runtime_ring_spawn_y_offset_explode_ramp,
            0, 1, 3, 4, 5, 6, 7, 8 => runtime_ring_spawn_y_offset_default,
            else => runtime_ring_spawn_y_offset_default,
        };
    }

    fn runtimeRingKindUsesRandomizedSpawnX(kind: u8) bool {
        return switch (kind) {
            0, 1, 2, 3, 4 => true,
            else => false,
        };
    }

    fn runtimeRingActivePhaseStep(self: *const Runner, preview: *const track.LoadedLevelPreview, source_row: usize, kind: u8) f32 {
        switch (kind) {
            5, 6, 7, 8 => {
                const ring_speed = preview.runtimeRowRingSpeedAt(source_row);
                if (ring_speed > 0.0) {
                    return (1.0 / (ring_speed * native_ticks_per_second)) * native_track_center_x * std.math.tau;
                }
            },
            0, 1, 2, 3, 4 => {
                const cycle_seconds = (2.0 - (self.base_subgame_rate * 0.3)) * native_ticks_per_second;
                if (cycle_seconds > 0.0) {
                    return (1.0 / cycle_seconds) *
                        (@as(f32, @floatFromInt(self.presentation.movement_flag_selector)) * 0.125) *
                        native_track_center_x *
                        std.math.tau;
                }
            },
            else => {},
        }
        return 0.0;
    }

    fn runtimeRingEffectProgressStep() f32 {
        return native_track_center_x * runtime_ring_effect_progress_scale;
    }

    fn runtimeHazardSeed(row: usize, lane: usize, kind: RuntimeHazardKind) u64 {
        var seed: u64 = 0x517cc1b727220a95;
        seed ^= @as(u64, @intCast(row + 1)) *% 0x9e3779b97f4a7c15;
        seed ^= @as(u64, @intCast(lane + 3)) *% 0xbf58476d1ce4e5b9;
        seed ^= (@as(u64, @intFromEnum(kind)) + 1) *% 0x94d049bb133111eb;
        return seed;
    }

    fn hasRuntimeHazard(self: *const Runner, row: usize, lane: usize, kind: RuntimeHazardKind) bool {
        for (0..self.runtime.hazards.count) |index| {
            const hazard = self.runtime.hazards.slots[index];
            if (hazard.row == row and hazard.lane == lane and hazard.kind == kind) return true;
        }
        return false;
    }

    fn activeRuntimePickupCountForKind(self: *const Runner, kind: RuntimePickupKind) usize {
        var count: usize = 0;
        for (0..self.runtime.pickups.count) |index| {
            if (self.runtime.pickups.slots[index].kind == kind) count += 1;
        }
        return count;
    }

    fn hasRuntimeRingEffect(self: *const Runner, row: usize, lane: usize) bool {
        for (0..self.runtime.rings.count) |index| {
            const effect = self.runtime.rings.slots[index];
            if (effect.row == row and effect.lane == lane) return true;
        }
        return false;
    }

    fn consumeRuntimeHazard(self: *Runner, row: usize, lane: usize, kind: RuntimeHazardKind) bool {
        for (0..self.runtime.hazards.count) |index| {
            const hazard = self.runtime.hazards.slots[index];
            if (hazard.row != row or hazard.lane != lane or hazard.kind != kind) continue;

            self.removeRuntimeHazardAt(index);
            return true;
        }
        return false;
    }

    fn removeRuntimeHazardAt(self: *Runner, index: usize) void {
        var shift_index = index;
        while (shift_index + 1 < self.runtime.hazards.count) : (shift_index += 1) {
            self.runtime.hazards.slots[shift_index] = self.runtime.hazards.slots[shift_index + 1];
        }
        self.runtime.hazards.count -= 1;
    }

    fn removeRuntimePickupAt(self: *Runner, index: usize) void {
        var shift_index = index;
        while (shift_index + 1 < self.runtime.pickups.count) : (shift_index += 1) {
            self.runtime.pickups.slots[shift_index] = self.runtime.pickups.slots[shift_index + 1];
        }
        self.runtime.pickups.count -= 1;
    }

    fn removeRuntimeRingEffectAt(self: *Runner, index: usize) void {
        var shift_index = index;
        while (shift_index + 1 < self.runtime.rings.count) : (shift_index += 1) {
            self.runtime.rings.slots[shift_index] = self.runtime.rings.slots[shift_index + 1];
        }
        self.runtime.rings.count -= 1;
    }

    fn runtimeRingDefaultPassesGate(self: *Runner, runtime_build_flags: u32) bool {
        if ((runtime_build_flags & 0x08) == 0) return false;
        if (runtime_build_flags == track.tutorialRuntimeBuildFlags) return true;
        return self.nextMathRandomFloat01() > runtime_ring_default_gate_threshold;
    }

    fn runtimePickupCapacity(kind: RuntimePickupKind) usize {
        return switch (kind) {
            .health => max_active_health_pickups,
            .jetpack => max_active_jetpack_pickups,
        };
    }

    fn spawnedRuntimeRingKind(self: *Runner, requested_kind: u8) u8 {
        if (requested_kind != 4) return requested_kind;
        if (self.nextMathRandomFloat01() > runtime_ring_kind4_to3_threshold) return 3;
        if (self.session_mode == .time_trial and self.nextMathRandomFloat01() > runtime_ring_time_trial_kind3_threshold) {
            return 3;
        }
        return 4;
    }

    fn runtimeRingEffectSpawnPositionAllowed(self: *const Runner, preview: *const track.LoadedLevelPreview, target_row: usize, lane_index: usize) bool {
        _ = self;
        return target_row < preview.total_rows and (preview.runtimeTileAt(target_row, lane_index) orelse 0) != 0x0e;
    }

    fn runtimeCellWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
        const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
        return preview.worldPositionForLane(
            @as(f32, @floatFromInt(lane_index)) + 0.5,
            @as(f32, @floatFromInt(global_row)),
            floor_height + y_offset,
        );
    }

    fn wall2EmitterSubLazerOrigin(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize) rl.Vector3 {
        var run_len: usize = 1;
        while (lane_index + run_len < preview.max_width) : (run_len += 1) {
            if ((preview.runtimeTileAt(global_row, lane_index + run_len) orelse 0) != native_wall2_tile_id) break;
        }
        const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
        const lane_center = @as(f32, @floatFromInt(lane_index)) + (@as(f32, @floatFromInt(run_len)) * 0.5);
        return preview.worldPositionForLane(
            lane_center,
            @as(f32, @floatFromInt(global_row)),
            floor_height + native_wall2_spawn_y_offset,
        );
    }

    fn updateJetpackGauge(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (!self.jetpack.active) return;
        const forced_warning = if (self.currentRuntimeSample(preview)) |sample|
            preview.runtimeFlagB80At(sample.global_row, sample.resolved_lane_index)
        else
            false;
        self.jetpack.update(forced_warning, self.rowPositionNearRouteEnd(preview));
    }

    fn armJetpackGauge(self: *Runner) void {
        self.jetpack.arm();
    }

    fn disarmJetpackGauge(self: *Runner) void {
        self.jetpack.disarm();
    }

    // PORT(verified): mirror of `update_subgoldy` non-follow vertical motion from
    // `artifacts/ida/functions/0043b120-update_subgoldy.c:352` (position integrate)
    // through line 584 (floor snap + `y<-7` death trigger + post-follow carryover
    // arm). The slide/floor-cache `_pad_41c` branch and the swept re-entry probes
    // land in follow-up commits.
    fn stepActivePhaseVerticalMotion(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.phase != .active) return;
        if (self.movement_mode == .attachment) return;
        if (self.attachment.launch.active) return;

        // Integrate (`0043b120-update_subgoldy.c:352`). Runs unconditionally in the
        // non-follow branch.
        self.position_y += self.velocity_y;

        // Damping (`0043b120-update_subgoldy.c:390`). `velocity.y *= 1 - track_center_x * 0.003`
        // each tick.
        self.velocity_y *= native_velocity_yz_decay_per_tick;

        const tile_at_position = preview.runtimeTileAt(self.current_global_row, self.resolved_lane_index);

        // 0x43bf6f swept-reentry grounded-snap lane
        // (`0043b120-update_subgoldy.c:458-476`). Fires only when
        // `!follow_state.active` (always true here because the attachment guard
        // above already returned). If `position.y` has drifted into the
        // `[-0.163, 0.49)` band over a tile that is neither open-neighbor family
        // (`{0x00, 0x0e, 0x1c, 0x1d, 0x23}`) nor the trampoline tile (`0x16`), native
        // snaps the rider back up to `0.49` when the velocity is non-positive, zeroes
        // the post-trampoline-airborne flag, and clears `attachment.exit.pending`.
        // The squidge burst at line 468 lands when the squidge controller is ported.
        if (!self.attachment.follow.active and
            self.position_y < native_grounded_snap_position_y_upper and
            self.position_y > native_grounded_snap_position_y_lower)
        {
            const snap_tile_allows = if (tile_at_position) |tile|
                !track.isOpenNeighborRuntimeTileFamily(tile) and tile != 0x16
            else
                false;
            if (snap_tile_allows) {
                self.post_trampoline_airborne = false;
                if (self.velocity_y <= 0.0) {
                    self.position_y = native_grounded_rider_height;
                    self.velocity_y = 0.0;
                }
                self.attachment.exit.pending = false;
            }
        }

        // Death trigger (`0043b120-update_subgoldy.c:504`). Native keeps the check
        // inside the grounded-state block; the port routes `.fall` through the
        // existing `beginFallState` path, which hands off to `updatePhaseController`
        // for respawn/final-loss.
        if (self.position_y < native_position_y_death_threshold) {
            self.beginFallState(preview, .fall, cutscene_none_id);
            return;
        }

        if (self.attachment.exit.pending) {
            // Pending-exit airborne branch (`0043b120-update_subgoldy.c:515-532`).
            // Native applies gravity once each tick while pending, then lets the
            // trampoline envelope bounce the rider off tile `0x16` when the
            // absolute distance to the cell's custom floor is within `0.49`.
            // Other tiles do not feed the floor-sample path while pending, so the
            // rider keeps falling until either the grounded-snap lane above
            // clears the gate or `position.y < -7` triggers death.
            self.velocity_y += native_gravity_velocity_y_delta;
            if (tile_at_position) |tile| {
                if (tile == 0x16) {
                    if (track.specialFloorHeightForShippedRuntimeTile(tile)) |cell_y| {
                        const envelope = native_grounded_rider_height;
                        if (cell_y + envelope > self.position_y and
                            cell_y - envelope < self.position_y)
                        {
                            self.velocity_y = native_track_center_x * 0.30000001;
                            self.position_y = cell_y + native_grounded_rider_height;
                            self.attachment.exit.pending = false;
                            self.post_trampoline_airborne = true;
                            self.counters.trampoline_bounces += 1;
                            self.recent_event = .trampoline;
                            // The squidge burst at `0043b120-update_subgoldy.c:525`
                            // lands with the surrounding squidge-controller port.
                        }
                    }
                }
            }
            return;
        }

        // Floor sampling + snap (`0043b120-update_subgoldy.c:535-579`, within the
        // non-attachment-exit-pending else branch). `sample_track_floor_height_at_position + 0.49`
        // is the grounded rider height; if it is not above `position.y`, continue
        // gravity; otherwise snap and let the tile-family reaction set the
        // outgoing `velocity.y`.
        const floor_y_opt = if (tile_at_position) |tile|
            track.sampleFloorHeightForRuntimeTile(tile, self.row_position, track.specialFloorHeightForShippedRuntimeTile(tile))
        else
            null;
        if (floor_y_opt) |floor_y| {
            const floor_plus_rider = floor_y + native_grounded_rider_height;
            if (floor_plus_rider <= self.position_y) {
                // Airborne above floor (`0043b120-update_subgoldy.c:538-539`):
                // keep applying gravity.
                self.velocity_y += native_gravity_velocity_y_delta;
            } else {
                // At or below floor (`0043b120-update_subgoldy.c:541-579`): snap
                // when the velocity is non-positive, then apply the tile-family
                // velocity.y reaction.
                if (self.velocity_y <= 0.0) {
                    self.position_y = floor_plus_rider;
                }
                self.applyTileFamilyFloorReaction(preview, tile_at_position);
            }
        } else {
            // No sampled floor under the current lane (void, 'M', path/probe cells,
            // or anything outside the native floor-sampler switch). Native returns
            // `-100.0` in this case
            // (`artifacts/ida/functions/0043d4d0-sample_track_floor_height_at_position.c:36`),
            // so `v51 < position.y` stays true every tick and gravity keeps pulling
            // the rider down.
            self.velocity_y += native_gravity_velocity_y_delta;
        }

        self.stepNativeBarrierHoldController(preview, tile_at_position);

        // Post-follow carryover arm at the tail of the else branch
        // (`artifacts/ida/functions/0043b120-update_subgoldy.c:581-583`): once
        // `position.y` has dipped below `0.0` with non-positive velocity, native
        // calls `begin_post_follow_carryover` which arms `attachment.exit.pending`,
        // latches `attachment.exit.anchor_z`, and resets the exit progress/gate
        // bytes. The next tick then flows through the pending-branch gravity +
        // trampoline envelope path above until the rider either dies at `y<-7`
        // or lands on a trampoline.
        if (!self.attachment.exit.pending and
            self.position_y < 0.0 and
            self.velocity_y <= 0.0)
        {
            self.seedAttachmentExitStateZeroed(self.row_position);
        }
    }

    fn stepNativeBarrierHoldController(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        tile_opt: ?u8,
    ) void {
        if (tile_opt != native_wall2_tile_id or self.position_y >= native_barrier_hold_max_y) {
            self.presentation.barrier_hold_progress = 0.0;
            return;
        }

        self.native_velocity_z_override_per_tick = null;
        const snapped_row_position = @floor(self.row_position + native_grounded_rider_height) - 0.5;
        self.applyTrackPosition(motion_module.trackPositionFromWorldZ(preview, snapped_row_position));

        // PORT(verified): `update_subgoldy` advances `player + 0x328` by the
        // seeded `1/60` step while Turbo is held by runtime tile `0x0e`, then
        // calls `begin_post_follow_carryover` once the timer crosses one second.
        self.presentation.barrier_hold_progress += self.presentation.barrier_hold_step;
        if (self.presentation.barrier_hold_progress > 1.0) {
            self.presentation.barrier_hold_progress = 0.0;
            if (!self.attachment.exit.pending) {
                self.seedAttachmentExitStateZeroed(self.row_position);
            }
        }
    }

    // PORT(verified): mirror of the tile-family velocity.y reactions at
    // `artifacts/ida/functions/0043b120-update_subgoldy.c:545-579`. Fires only
    // inside the "below floor" branch where `floor_y + 0.49 > position.y` just
    // snapped the rider up to the floor.
    //
    // - Tiles `0x08..0x0d` (up-slides and ramp-up mirrors) drive `velocity.y = 1.2`
    //   so the rider climbs the slope each tick.
    // - Tiles `0x02..0x07` (down-ramps) set `velocity.y = 0.8` and seed the
    //   surface-reaction animation lane; the `dispatch_cutscene_animation` calls
    //   land when that clip-dispatch layer is ported (plan §4 / task #5).
    // - Any other tile that is not empty (`0x00`), open-neighbor (`0x23`), or
    //   trampoline (`0x16`) clears the post-trampoline-airborne flag and zeroes
    //   `velocity.y`, producing the stable grounded rest state on flat floor.
    fn applyTileFamilyFloorReaction(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        tile_opt: ?u8,
    ) void {
        const tile = tile_opt orelse return;
        switch (tile) {
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d => {
                self.velocity_y = native_track_center_x * 0.30000001;
            },
            0x02, 0x03, 0x04, 0x05, 0x06, 0x07 => {
                self.velocity_y = native_track_center_x * 0.2;
                // PORT(verified): down-ramp reaction dispatches a lookback
                // animation based on lateral sign, then queues the base clip
                // (`0043b120-update_subgoldy.c:564-571`). Native tests
                // `position.x <= 0` where x is in `[-4, 4]`; the port derives
                // the same sign from `lane_center - max_width * 0.5`.
                const lane_mid = @as(f32, @floatFromInt(preview.max_width)) * 0.5;
                const world_x_signed = self.lane_center - lane_mid;
                const lookback: AnimClipId = if (world_x_signed <= 0.0) .lookback_l else .lookback_r;
                self.cutscene.anim.dispatch(lookback, true, null);
                self.cutscene.anim.dispatch(.base, false, null);
            },
            0x00, 0x23, 0x16 => {},
            else => {
                self.post_trampoline_airborne = false;
                self.velocity_y = 0.0;
            },
        }
    }

    fn updateVisibleLifeStockFromScore(self: *Runner, previous_total: u32, current_total: u32) void {
        self.visible_life_stock = score_module.visibleLifeStockAfterScore(
            self.visible_life_stock,
            previous_total,
            current_total,
        );
    }

    fn beginCompletionCutscene(self: *Runner) void {
        phase_module.beginCompletionCutscene(self);
    }

    fn routeEndReached(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        return phase_module.routeEndReached(self, preview);
    }

    fn maybeBeginCompletionCutscene(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        phase_module.maybeBeginCompletionCutscene(self, preview);
    }

    fn captureWorldFrame(self: *const Runner, preview: *const track.LoadedLevelPreview) WorldFrame {
        return .{
            .position = self.worldPosition(preview, 0.0),
            .forward = normalizeVector3(self.worldForward(preview)),
            .up = normalizeVector3(self.worldUp(preview)),
        };
    }

    fn syncTrackPositionFromWorld(self: *Runner, preview: *const track.LoadedLevelPreview, world_x: f32, world_z: f32) void {
        if (preview.total_rows == 0) return;

        self.applyTrackPosition(motion_module.trackPositionFromWorldZ(preview, world_z));
        self.lane_center = laneCenterFromWorldX(preview, world_x);
        self.lane_index = preview.laneIndexAtWorldX(world_x);
        self.resolved_lane_index = self.lane_index;
    }

    fn beginFallState(self: *Runner, preview: *const track.LoadedLevelPreview, cause: DeathCause, cutscene_id: u8) void {
        if (self.phase != .active or self.finished) return;
        const frame = self.captureWorldFrame(preview);
        // PORT(verified): the slug first-hit path
        // (`artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:197-200`)
        // stamps `velocity.y = track_center_x * 0.2` before entering cutscene
        // state 10. The port reads that same lane as the fall phase's initial
        // vertical velocity so the rider's knockback arc picks up the hit
        // impulse instead of starting from rest. The launch branch still wins
        // when a launch is in progress.
        const initial_vertical_velocity = if (self.attachment.launch.active)
            self.attachment.launch.vertical_velocity
        else
            self.velocity_y;

        // PORT(verified): native `update_cutscene` drives the visual clip
        // from the cutscene-state lane. Without the full state-machine port,
        // dispatch the matching clip on phase transition so the renderer
        // reflects the fall/hit immediately:
        //   - `.fall` cause (y<-7 or floor gap) → `turbo-fall` clip.
        //   - `.hazard` cause (slug contact) → `turbo-intoshell`; the
        //     slug-hit path at
        //     `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:203`
        //     writes `cutscene_ai.state = 10` which drives the same clip
        //     family in native.
        //   - `.damage` cause (state-2 drain death) reuses the
        //     `turbo-damaged` clip that the hit-flash already dispatched.
        switch (cause) {
            .fall => self.cutscene.anim.dispatch(.fall, true, null),
            .hazard => self.cutscene.anim.dispatch(.intoshell, true, null),
            .damage => {},
        }
        if (self.movement_mode == .attachment) {
            self.seedAttachmentExitStateFromCarryover(preview, frame.position.z);
        } else if (self.attachment.exit.pending) {
            self.seedAttachmentExitStateFromCurrentExit(frame.position.z);
        } else if (cause == .fall) {
            self.seedAttachmentExitStateZeroed(frame.position.z);
        }
        self.paused = false;
        self.attachment.launch = .{};
        self.clearAttachmentFollow();
        self.syncTrackPositionFromWorld(preview, frame.position.x, frame.position.z);
        self.setCutscene(cutscene_id);
        self.phase = .{
            .fall = .{
                .cause = cause,
                .world_x = frame.position.x,
                .world_y = frame.position.y,
                .world_z = frame.position.z,
                .vertical_velocity = initial_vertical_velocity,
                .basis_forward = vector3ToAttachmentVec3(frame.forward),
                .basis_up = vector3ToAttachmentVec3(frame.up),
            },
        };
    }

    fn updatePhaseController(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        switch (self.phase) {
            .active => {},
            .completion_handoff => {
                phase_module.updateCompletionHandoff(self, preview);
            },
            .fall => |state| {
                var next_state = state;
                next_state.world_z = self.attachment.exit.anchor_z;
                self.phase = .{ .fall = next_state };
                const cutscene_finished = self.advanceCutsceneTicks();
                self.stepAttachmentExitState(preview);
                switch (next_state.cause) {
                    .fall => {
                        next_state.world_y += next_state.vertical_velocity * delta_seconds;
                        next_state.vertical_velocity -= fall_gravity * delta_seconds;
                        self.phase = .{ .fall = next_state };
                        if (!self.attachment.exit.gate_b and next_state.world_y < fall_world_y_threshold) {
                            self.attachment.exit.gate_b = true;
                        }
                        if (next_state.world_y > fall_world_y_threshold) return;
                        next_state.resurrect_ticks = @min(next_state.resurrect_ticks + 1, fall_resurrect_delay_ticks);
                        self.phase = .{ .fall = next_state };
                        if (next_state.resurrect_ticks < fall_resurrect_delay_ticks) return;
                    },
                    .hazard, .damage => {
                        if (!cutscene_finished) return;
                    },
                }

                if (self.deathUsesFinalLoss()) {
                    self.handoff.pending = .{ .final_loss = next_state.cause };
                    return;
                }
                if (self.session_mode == .postal and self.visible_life_stock > 0) {
                    self.visible_life_stock -= 1;
                }
                self.handoff.pending = .{ .respawn = next_state.cause };
            },
        }
    }

    fn advanceCutsceneTicks(self: *Runner) bool {
        return phase_module.advanceCutsceneTicks(self);
    }

    fn stepAttachmentExitState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        _ = preview;
        attachment_module.stepExitState(self);
        // The common pending-exit path only has a confirmed direct consumer for
        // `attachment.exit.post_follow_value_a`. Preserve the carryover angle here instead of synthesizing a
        // shared `attachment.exit.post_follow_value_b`-driven update that static RE has not closed yet.
    }

    fn deathUsesFinalLoss(self: *const Runner) bool {
        return switch (self.session_mode) {
            .postal => self.visible_life_stock == 0,
            .challenge, .time_trial => true,
            .tutorial, .debug => false,
        };
    }

    fn updateTimesUpController(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        // PORT(verified): `update_subgoldy` increments the replay/update cursor
        // once per live tick and calls `show_times_up_message` exactly when it
        // reaches 21000. `update_times_up` then advances a tiny controller by
        // 0.0055555557 each tick; once it enters state 2, it uninitializes the
        // widget and calls `kill_subgoldy`.
        if (self.replay_sample_index == times_up_trigger_sample_index) {
            self.times_up.show();
        }
        if (!self.times_up.update()) return;

        // `kill_subgoldy` is not a separate death cause: it first runs
        // `begin_post_follow_carryover` (which clears the active follow byte),
        // then writes `live_matrix.position.y = -8.0`. The existing native
        // vertical-motion port sees the same `y < -7` condition on the following
        // tick and enters the shared fall/death path.
        self.seedAttachmentExitStateFromCarryover(preview, self.row_position);
        self.clearAttachmentFollow();
        self.position_y = -8.0;
    }

    fn currentAttachmentBuilt(self: *const Runner, preview: *const track.LoadedLevelPreview) ?*const attachment_builders.BuiltAttachment {
        if (!self.attachment.follow.active) return null;
        return preview.builtAttachmentForSourceRow(self.attachment.follow.source_cell_row);
    }

    pub fn currentAttachmentTemplateKind(self: *const Runner, preview: *const track.LoadedLevelPreview) ?u8 {
        const built = self.currentAttachmentBuilt(preview) orelse return null;
        return built.template.spec.template_kind;
    }

    fn laneCenterFromWorldX(preview: *const track.LoadedLevelPreview, world_x: f32) f32 {
        return motion_module.laneCenterFromWorldX(preview, world_x);
    }

    fn laneIndexForLaneCenter(preview: *const track.LoadedLevelPreview, lane_center: f32) usize {
        return motion_module.laneIndexForLaneCenter(preview, lane_center);
    }

    fn trackEntryWorldPosition(preview: *const track.LoadedLevelPreview, row_position: f32, lane_center: f32) attachment_builders.Vec3 {
        return attachment_module.trackEntryWorldPosition(preview, row_position, lane_center);
    }

    fn attachmentWorldPositionFromLocal(
        pose: attachment_builders.WorldPose,
        local_position: attachment_builders.Vec3,
    ) attachment_builders.Vec3 {
        return attachment_module.worldPositionFromLocal(pose, local_position);
    }

    fn attachmentLocalPosition(pose: attachment_builders.WorldPose, world_position: attachment_builders.Vec3) attachment_builders.Vec3 {
        return attachment_module.localPosition(pose, world_position);
    }

    fn attachmentEntryVerticalOffset(family: attachment_builders.BuilderFamily, local_y: f32) f32 {
        return attachment_module.entryVerticalOffset(family, local_y);
    }

    fn commitAttachmentNaturalExit(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        if (built.template.spec.family == .supertramp) {
            self.commitSupertrampNaturalExit(preview, built);
            return;
        }
        const exit_world_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            @floatFromInt(built.template.sample_count),
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
            self.attachment.follow.vertical_offset,
        );
        self.row_position = exit_world_position.z + built.template.exit_tail_extra;
        self.row_position += self.attachment.follow.exit_overshoot;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.track_row_progress = self.row_position - @floor(self.row_position);
        self.lane_index = preview.laneIndexAtWorldX(exit_world_position.x);
        self.resolved_lane_index = self.lane_index;
        self.lane_center = laneCenterFromWorldX(preview, exit_world_position.x);
    }

    fn commitSupertrampNaturalExit(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        const sample_count_f: f32 = @floatFromInt(built.template.sample_count);
        const final_progress = @max(0.0, sample_count_f - 0.001);
        const end_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            final_progress,
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
            self.attachment.follow.vertical_offset,
        );
        const end_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            sample_count_f,
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
            self.attachment.follow.vertical_offset,
        );
        const last_delta_length = attachment_builders.deltaLengthAtProgress(&built.template, final_progress);
        const launch_factor = std.math.clamp(self.track_step_rows * last_delta_length, 0.0, 1.0);
        const exit_world_x = self.attachment.follow.cached_output_position.x;
        const exit_lane = preview.laneIndexAtWorldX(exit_world_x);
        const exit_floor_y = preview.sampleFloorHeightAtGridPosition(
            currentRowIndex(preview, end_position.z),
            exit_lane,
            end_position.z,
        ) orelse 0.0;

        self.row_position = end_position.z + built.template.exit_tail_extra + self.attachment.follow.exit_overshoot;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.track_row_progress = self.row_position - @floor(self.row_position);
        self.lane_index = exit_lane;
        self.resolved_lane_index = exit_lane;
        self.lane_center = laneCenterFromWorldX(preview, exit_world_x);
        self.attachment.launch = .{
            .active = true,
            .world_x = exit_world_x,
            .height = @max(0.6, end_position.y - exit_floor_y),
            .vertical_velocity = @max(0.15, launch_factor) * supertramp_launch_velocity_scale,
            .camera_progress = launch_camera_progress_step_default,
            .camera_progress_step = launch_camera_progress_step_default,
            .basis_forward = end_pose.basis_forward,
            .basis_up = end_pose.basis_up,
        };
    }

    fn attachmentShouldSideExit(self: *const Runner, built: *const attachment_builders.BuiltAttachment) bool {
        return attachment_module.shouldSideExit(
            built,
            self.jetpack.active,
            self.attachment.follow.vertical_offset,
            self.attachment.follow.template_progress,
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
        );
    }

    fn attachmentTemplateHalfSpan(built: *const attachment_builders.BuiltAttachment) f32 {
        return attachment_module.templateHalfSpan(built);
    }

    fn commitAttachmentSideExit(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            self.attachment.follow.template_progress,
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
            self.attachment.follow.vertical_offset,
        );
        const clamped_world_x = std.math.clamp(world_pose.position.x, -4.0, 4.0);
        self.row_position = world_pose.position.z;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.track_row_progress = self.row_position - @floor(self.row_position);
        self.lane_index = preview.laneIndexAtWorldX(clamped_world_x);
        self.resolved_lane_index = self.lane_index;
        self.lane_center = laneCenterFromWorldX(preview, clamped_world_x);

        const floor_y = preview.sampleFloorHeightAtGridPosition(
            self.runtime_track_index,
            self.resolved_lane_index,
            self.row_position,
        ) orelse 0.0;
        const exit_height = @max(0.0, world_pose.position.y - floor_y);
        if (exit_height > 0.001) {
            self.attachment.launch = .{
                .active = true,
                .world_x = clamped_world_x,
                .height = exit_height,
                .vertical_velocity = 0.0,
                .camera_progress = launch_camera_progress_step_default,
                .camera_progress_step = launch_camera_progress_step_default,
                .basis_forward = world_pose.basis_forward,
                .basis_up = world_pose.basis_up,
            };
        }
    }

    fn updateAttachmentFollowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const built = self.currentAttachmentBuilt(preview) orelse return;
        self.syncAttachmentFollowNativeProgressFromTemplateProgress(built);
        self.syncAttachmentFollowTemplateProgress(built);
        const position = self.attachmentFollowOutputPosition(built);
        self.updateAttachmentFollowCameraOrientations(built);
        self.attachment.follow.cached_output_position = position;
        self.row_position = position.z;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.track_row_progress = self.row_position - @floor(self.row_position);
        self.attachment.follow.cached_output_lane_center = laneCenterFromWorldX(preview, position.x);
        self.lane_center = self.attachment.follow.cached_output_lane_center;
        self.resolved_lane_index = preview.laneIndexAtWorldX(position.x);
    }

    fn syncAttachmentFollowNativeProgressFromTemplateProgress(
        self: *Runner,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        if (self.attachment.follow.sample_index != 0 or self.attachment.follow.local_progress != 0.0) return;
        if (self.attachment.follow.template_progress <= 0.0) return;

        const sample_count = built.template.sample_count;
        const sample_count_f: f32 = @floatFromInt(sample_count);
        const clamped_progress = std.math.clamp(self.attachment.follow.template_progress, 0.0, sample_count_f);
        if (clamped_progress >= sample_count_f) {
            self.attachment.follow.sample_index = sample_count;
            self.attachment.follow.local_progress = 0.0;
            self.attachment.follow.progress = 0.0;
            self.attachment.follow.template_progress = sample_count_f;
            return;
        }

        const sample_index = @as(usize, @intFromFloat(@floor(clamped_progress)));
        const sample_index_f: f32 = @floatFromInt(sample_index);
        const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, sample_index_f);
        self.attachment.follow.sample_index = sample_index;
        self.attachment.follow.local_progress = (clamped_progress - sample_index_f) * delta_length;
        self.attachment.follow.progress = self.attachment.follow.local_progress;
    }

    fn syncAttachmentFollowTemplateProgress(
        self: *Runner,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        const sample_count = built.template.sample_count;
        const sample_count_f: f32 = @floatFromInt(sample_count);
        if (self.attachment.follow.sample_index >= sample_count) {
            self.attachment.follow.progress = self.attachment.follow.local_progress;
            self.attachment.follow.template_progress = sample_count_f;
            return;
        }

        const sample_index_f: f32 = @floatFromInt(self.attachment.follow.sample_index);
        const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, sample_index_f);
        const normalized_local_progress = if (delta_length <= 0.0001)
            0.0
        else
            self.attachment.follow.local_progress / delta_length;
        self.attachment.follow.progress = self.attachment.follow.local_progress;
        self.attachment.follow.template_progress = sample_index_f + normalized_local_progress;
    }

    fn stepAttachmentFollowAtRate(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        path_factor: f32,
    ) void {
        // PORT(verified): native `update_track_attachment_follow_state` advances a raw
        // local-distance lane inside the current sample, carries any remainder across sample
        // boundaries, and still publishes the camera phase / heading-roll lanes on zero-rate
        // updates.
        const built = self.currentAttachmentBuilt(preview) orelse {
            self.syncRowPosition(preview);
            return;
        };
        self.syncAttachmentFollowNativeProgressFromTemplateProgress(built);

        const sample_count = built.template.sample_count;
        self.attachment.follow.exit_overshoot = 0.0;
        if (sample_count > 0 and self.attachment.follow.sample_index < sample_count) {
            const current_sample_index_f: f32 = @floatFromInt(self.attachment.follow.sample_index);
            var remaining_local_progress =
                @max(path_factor, 0.0) *
                attachment_builders.deltaLengthAtProgress(&built.template, current_sample_index_f);

            while (remaining_local_progress > 0.0 and self.attachment.follow.sample_index < sample_count) {
                const sample_index_f: f32 = @floatFromInt(self.attachment.follow.sample_index);
                const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, sample_index_f);
                const segment_remaining = @max(0.0, delta_length - self.attachment.follow.local_progress);
                if (remaining_local_progress <= segment_remaining) {
                    self.attachment.follow.local_progress = std.math.clamp(
                        self.attachment.follow.local_progress + remaining_local_progress,
                        0.0,
                        delta_length,
                    );
                    remaining_local_progress = 0.0;
                    break;
                }

                remaining_local_progress -= segment_remaining;
                self.attachment.follow.sample_index += 1;
                self.attachment.follow.local_progress = 0.0;
            }

            if (self.attachment.follow.sample_index >= sample_count) {
                self.attachment.follow.exit_overshoot = std.math.clamp(remaining_local_progress, 0.0, 0.999000013);
            }
        }

        self.attachment.camera.heading_roll += self.attachment.follow.installed_heading_delta;
        self.syncAttachmentFollowTemplateProgress(built);
        self.updateAttachmentFollowPosition(preview);
        if (self.attachment.follow.vertical_offset < 0.0) {
            self.attachment.follow.vertical_offset = 0.0;
        }
    }

    fn updateAttachmentFollowCameraOrientations(
        self: *Runner,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        // PORT(partial): native `update_track_attachment_follow_state` publishes live
        // cameraman rotations through `follow_state.orientation_a/orientation_b`.
        // `orientation_a` is a wrapped interpolation of a per-sample local-roll scalar,
        // while `orientation_b` is the template phase lane
        // (`(sample_index + (local_progress / delta_length)) * installed_heading_delta / sample_count`).
        // The Zig scaffold still does not store the raw Windows per-sample scalar, so derive
        // the same local-roll lane from the built sample basis before applying the native
        // wrapped interpolation.
        const sample_count: f32 = @floatFromInt(built.template.sample_count);
        if (sample_count <= 0.0 or built.template.samples.len == 0) {
            self.attachment.follow.camera_orientation_a = 0.0;
            self.attachment.follow.camera_orientation_b = 0.0;
            return;
        }

        const clamped_progress = std.math.clamp(self.attachment.follow.template_progress, 0.0, sample_count);
        const segment_base_index = @min(
            @as(usize, @intFromFloat(@floor(clamped_progress))),
            @as(usize, built.template.sample_count - 1),
        );
        const segment_base_progress: f32 = @floatFromInt(segment_base_index);
        const segment_local_progress = clamped_progress - segment_base_progress;
        const segment_delta_length = attachment_builders.deltaLengthAtProgress(&built.template, segment_base_progress);
        const normalized_segment_progress = if (segment_delta_length <= 0.0001)
            0.0
        else
            std.math.clamp(segment_local_progress / segment_delta_length, 0.0, 1.0);

        const sample_orientation_a = attachmentSampleOrientationA(&built.template.samples[segment_base_index]);
        if (segment_base_index + 1 >= built.template.samples.len or segment_base_index + 1 >= built.template.sample_count) {
            self.attachment.follow.camera_orientation_a = sample_orientation_a;
        } else {
            const next_sample_orientation_a = attachmentSampleOrientationA(&built.template.samples[segment_base_index + 1]);
            self.attachment.follow.camera_orientation_a =
                interpolateWrappedRadians(sample_orientation_a, next_sample_orientation_a, normalized_segment_progress);
        }

        if (self.attachment.follow.installed_heading_delta == 0.0) {
            self.attachment.follow.camera_orientation_b = 0.0;
            return;
        }
        self.attachment.follow.camera_orientation_b =
            ((segment_base_progress + normalized_segment_progress) * self.attachment.follow.installed_heading_delta) / sample_count;
    }

    fn attachmentFollowOutputPosition(
        self: *const Runner,
        built: *const attachment_builders.BuiltAttachment,
    ) attachment_builders.Vec3 {
        const raw_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            self.attachment.follow.template_progress,
            self.attachment.follow.source_cell_row,
            self.attachment.follow.lateral_offset,
            self.attachment.follow.vertical_offset,
        );
        const position = raw_position;
        return .{
            .x = std.math.clamp(position.x, -4.0, 4.0),
            .y = position.y,
            .z = position.z,
        };
    }

    fn advanceAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.stepAttachmentFollowAtRate(preview, self.track_step_rows);
    }

    fn finalizeAttachmentBegin(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        // PORT(verified): both the direct begin path and the swept installed-entry path
        // immediately run one follow update in the same tick after seeding the live state.
        if (self.currentAttachmentBuilt(preview) != null) {
            self.stepAttachmentFollowAtRate(preview, self.track_step_rows);
        } else {
            self.updateAttachmentFollowPosition(preview);
        }
    }

    fn beginAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview, sample: RowSample) void {
        const source_cell_row: f32 = @floatFromInt(sample.global_row);
        const player_position = self.playerWorldPosition(preview);
        const vertical_offset = player_position.y - attachment_entry_rider_height;
        var lateral_offset: f32 = if (sample.path_center_lane) |path_center_lane|
            self.lane_center - path_center_lane
        else
            0.0;
        if (preview.builtAttachmentForSourceRow(sample.global_row)) |built| {
            const entry_pose = attachment_builders.worldPoseForTemplate(
                &built.template,
                self.row_position - source_cell_row,
                sample.global_row,
                0.0,
                vertical_offset,
            );
            lateral_offset = attachmentLateralOffsetFromLocalX(
                &built.template,
                self.row_position - source_cell_row,
                attachmentLocalPosition(entry_pose, .{
                    .x = player_position.x,
                    .y = player_position.y,
                    .z = player_position.z,
                }).x,
            );
        }
        self.attachment.launch = .{};
        self.movement_mode = .attachment;
        self.attachment.path_name = sample.path_name;
        const installed_heading_delta = if (preview.builtAttachmentForSourceRow(sample.global_row)) |built|
            built.template.installed_heading_delta
        else
            0.0;
        const local_progress = self.row_position - source_cell_row;
        self.attachment.follow = .{
            .active = true,
            .source_cell_row = sample.global_row,
            .sample_index = 0,
            // PORT(verified): native generic entry seeds the follow state's local progress
            // from the current player Z relative to the source-row anchor.
            .local_progress = local_progress,
            .progress = local_progress,
            .exit_overshoot = 0.0,
            .lateral_offset = lateral_offset,
            .cached_output_lane_center = self.lane_center,
            .vertical_offset = vertical_offset,
            .installed_heading_delta = installed_heading_delta,
        };
        self.finalizeAttachmentBegin(preview);
        self.counters.attachments_begun += 1;
        self.recent_event = .attachment_begin;
    }

    fn beginInstalledAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview, built: *const attachment_builders.BuiltAttachment, entry: InstalledAttachmentEntry) void {
        self.attachment.launch = .{};
        self.movement_mode = .attachment;
        self.attachment.path_name = built.row.raw_name;

        self.attachment.follow = .{
            .active = true,
            .source_cell_row = built.row.global_row,
            .sample_index = entry.sample_index,
            .local_progress = entry.local_progress,
            .progress = entry.local_progress,
            .exit_overshoot = 0.0,
            .lateral_offset = entry.lateral_offset,
            .cached_output_lane_center = self.lane_center,
            .vertical_offset = entry.vertical_offset,
            .installed_heading_delta = built.template.installed_heading_delta,
        };
        self.finalizeAttachmentBegin(preview);
        self.counters.attachments_begun += 1;
        self.recent_event = .attachment_begin;
    }

    fn installedBuiltAttachmentForSlot(
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        slot: InstalledAttachmentSlot,
    ) ?*const attachment_builders.BuiltAttachment {
        const installed = preview.installedBuiltAttachmentsAtRow(global_row);
        return switch (slot) {
            .primary => installed.primary,
            .secondary => installed.secondary,
        };
    }

    fn tryBeginInstalledAttachmentFollowForSlot(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        sample: RowSample,
        slot: InstalledAttachmentSlot,
    ) bool {
        const built = installedBuiltAttachmentForSlot(preview, global_row, slot) orelse return false;
        if (self.geometricInstalledAttachmentEntry(preview, built, sample)) |entry| {
            self.beginInstalledAttachmentFollow(preview, built, entry);
            return true;
        }
        return false;
    }

    fn tryBeginCurrentRowInstalledAttachmentFollow(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
    ) bool {
        const installed = preview.installedBuiltAttachmentsAtRow(global_row);
        const candidates = [_]?*const attachment_builders.BuiltAttachment{
            installed.primary,
            installed.secondary,
        };
        for (candidates) |maybe_built| {
            const built = maybe_built orelse continue;
            if (self.currentRowInstalledAttachmentEntry(preview, built, global_row)) |entry| {
                self.beginInstalledAttachmentFollow(preview, built, entry);
                return true;
            }
        }
        return false;
    }

    fn currentRowInstalledAttachmentEntry(
        self: *const Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
        global_row: usize,
    ) ?InstalledAttachmentEntry {
        // PORT(verified): `update_subgoldy` calls `begin_track_attachment_follow_state`
        // directly from the current runtime attachment cell when `attachment.exit.pending`
        // is clear. That begin path seeds progress from the current row cell, not only from
        // the attachment source row, so use the current installed row span here.
        const sample_index = global_row - built.row.global_row;
        const sample_index_f: f32 = @floatFromInt(sample_index);
        const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, sample_index_f);
        const local_progress = std.math.clamp(
            self.row_position - @as(f32, @floatFromInt(global_row)),
            0.0,
            delta_length,
        );
        const template_progress = if (delta_length <= 0.0001)
            sample_index_f
        else
            sample_index_f + (local_progress / delta_length);
        const entry_world_position = trackEntryWorldPosition(preview, self.row_position, self.lane_center);
        const entry_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            template_progress,
            built.row.global_row,
            0.0,
            0.0,
        );
        const entry_local = attachmentLocalPosition(entry_pose, entry_world_position);
        const lateral_offset = attachmentLateralOffsetFromLocalX(&built.template, template_progress, entry_local.x);
        if (@abs(entry_local.x) > attachmentTemplateHalfSpan(built) + attachment_side_exit_margin) return null;
        return .{
            .sample_index = sample_index,
            .local_progress = local_progress,
            .lateral_offset = lateral_offset,
            .vertical_offset = attachmentEntryVerticalOffset(built.template.spec.family, entry_local.y),
        };
    }

    fn geometricInstalledAttachmentEntry(
        self: *const Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
        sample: RowSample,
    ) ?InstalledAttachmentEntry {
        const current_lane_center = std.math.clamp(
            self.lane_center,
            @as(f32, @floatFromInt(sample.traversable_bounds.min)) + 0.5,
            @as(f32, @floatFromInt(sample.traversable_bounds.max)) + 0.5,
        );
        const start_world_position = trackEntryWorldPosition(preview, self.previous_row_position, self.previous_lane_center);
        const end_world_position = trackEntryWorldPosition(preview, self.row_position, current_lane_center);
        return installedAttachmentEntryForSweep(built, start_world_position, end_world_position);
    }

    fn installedAttachmentEntryForSweep(
        built: *const attachment_builders.BuiltAttachment,
        start_world_position: attachment_builders.Vec3,
        end_world_position: attachment_builders.Vec3,
    ) ?InstalledAttachmentEntry {
        // PORT(verified): Windows `try_enter_track_attachment_from_swept_motion` walks the
        // installed sample array from tail to head, skips samples whose world-up Y component
        // is negative, and applies the raw local sweep thresholds against each sample pose.
        const sample_count = @min(@as(usize, built.template.sample_count), built.template.samples.len);
        if (sample_count == 0) return null;

        var candidate_index = sample_count;
        while (candidate_index > 0) {
            candidate_index -= 1;

            const sample = built.template.samples[candidate_index];
            if (sample.basis_up.y < 0.0) continue;

            const candidate_progress: f32 = @floatFromInt(candidate_index);
            const candidate_pose = attachment_builders.worldPoseForTemplate(
                &built.template,
                candidate_progress,
                built.row.global_row,
                0.0,
                0.0,
            );
            const start_local = attachmentLocalPosition(candidate_pose, start_world_position);
            const sample_length = sample.delta_length;

            if (@abs(start_local.x) > attachmentTemplateHalfSpan(built) + attachment_side_exit_margin) continue;
            if (start_local.y < attachment_entry_start_y_tolerance) continue;
            if (start_local.z < 0.0 or start_local.z > sample_length) continue;

            const end_local = attachmentLocalPosition(candidate_pose, end_world_position);
            if (end_local.y > attachment_entry_end_y_tolerance) continue;

            const sample_fraction = if (sample_length <= 0.0001)
                0.0
            else
                std.math.clamp(start_local.z / sample_length, 0.0, 1.0);
            const progress = candidate_progress + sample_fraction;
            const lateral_offset = attachmentLateralOffsetFromLocalX(&built.template, progress, start_local.x);
            return .{
                .sample_index = candidate_index,
                .local_progress = start_local.z,
                .lateral_offset = lateral_offset,
                .vertical_offset = attachmentEntryVerticalOffset(built.template.spec.family, start_local.y),
            };
        }

        return null;
    }

    fn clearAttachmentFollow(self: *Runner) void {
        self.movement_mode = .track;
        self.attachment.path_name = null;
        self.attachment.follow = .{};
    }

    fn attachmentLateralOffsetFromLocalX(
        built_template: *const attachment_builders.Template,
        progress: f32,
        local_x: f32,
    ) f32 {
        return attachment_module.lateralOffsetFromLocalX(built_template, progress, local_x);
    }

    pub fn attachmentExitCarryoverFromFollow(self: *const Runner, preview: *const track.LoadedLevelPreview) AttachmentExitCarryover {
        _ = self.currentAttachmentBuilt(preview) orelse {
            return .{
                .carryover_a = self.attachment.camera.orientation_b,
                .carryover_b = 0.0,
            };
        };

        return .{
            // Native fall-state init copies `follow_state.orientation_b`, which is the
            // attachment phase lane rather than a sampled roll proxy.
            .carryover_a = self.attachment.follow.camera_orientation_b,
            // Native fall-state init copies the live follow record's install-time scalar into
            // `attachment.exit.post_follow_value_b`, including zero. Keep that carryover value, but do not
            // assign a common runtime consumer beyond the write itself until RE closes one.
            .carryover_b = self.attachment.follow.installed_heading_delta,
        };
    }

    fn currentAttachmentExitCarryover(self: *const Runner, preview: *const track.LoadedLevelPreview) AttachmentExitCarryover {
        if (self.attachment.follow.active) {
            if (self.attachment.follow.exit_carryover_a != 0.0 or
                self.attachment.follow.exit_carryover_b != 0.0)
            {
                return .{
                    .carryover_a = self.attachment.follow.exit_carryover_a,
                    .carryover_b = self.attachment.follow.exit_carryover_b,
                };
            }
            return self.attachmentExitCarryoverFromFollow(preview);
        }

        return .{
            .carryover_a = self.attachment.exit.carryover_a,
            .carryover_b = self.attachment.exit.carryover_b,
        };
    }

    fn beginAttachmentExitState(self: *Runner, anchor_z: f32) void {
        attachment_module.beginExitState(self, anchor_z);
    }

    fn seedAttachmentExitStateFromCarryover(self: *Runner, preview: *const track.LoadedLevelPreview, anchor_z: f32) void {
        const exit_carryover = if (self.movement_mode == .attachment and self.attachment.follow.active)
            self.currentAttachmentExitCarryover(preview)
        else
            AttachmentExitCarryover{
                .carryover_a = self.attachment.exit.carryover_a,
                .carryover_b = self.attachment.exit.carryover_b,
            };
        self.beginAttachmentExitState(anchor_z);
        self.attachment.exit.post_follow_value_a = exit_carryover.carryover_a;
        self.attachment.exit.post_follow_value_b = exit_carryover.carryover_b;
        self.attachment.exit.carryover_a = exit_carryover.carryover_a;
        self.attachment.exit.carryover_b = exit_carryover.carryover_b;
        self.attachment.camera.previous_heading_roll_sample = rollRadiansFromForwardUp(self.worldForward(preview), self.worldUp(preview));
    }

    fn seedAttachmentExitStateFromCurrentExit(self: *Runner, anchor_z: f32) void {
        attachment_module.seedExitStateFromCurrentExit(self, anchor_z);
    }

    fn seedAttachmentExitStateZeroed(self: *Runner, anchor_z: f32) void {
        attachment_module.seedExitStateZeroed(self, anchor_z);
    }

    fn shouldRetireAttachmentDirectlyForCompletion(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (self.attachment.launch.active) return false;
        return self.routeEndReached(preview);
    }

    fn finishAttachmentFollowDirect(self: *Runner) void {
        self.clearAttachmentFollow();
        self.counters.attachments_completed += 1;
        self.recent_event = .attachment_end;
    }

    fn finishAttachmentFollowWithExitHandoff(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.seedAttachmentExitStateFromCarryover(preview, self.row_position);
        self.finishAttachmentFollowDirect();
    }

    fn updateLaunch(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        if (!self.attachment.launch.active) return;

        if (self.attachment.launch.camera_progress_step > 0.0) {
            self.attachment.launch.camera_progress = std.math.clamp(
                self.attachment.launch.camera_progress + self.attachment.launch.camera_progress_step,
                0.0,
                1.0,
            );
        }
        self.attachment.launch.height = @max(0.0, self.attachment.launch.height + (self.attachment.launch.vertical_velocity * delta_seconds));
        self.attachment.launch.vertical_velocity -= supertramp_launch_gravity * delta_seconds;
        self.lane_center = laneCenterFromWorldX(preview, self.attachment.launch.world_x);
        self.lane_index = preview.laneIndexAtWorldX(self.attachment.launch.world_x);
        self.resolved_lane_index = self.lane_index;

        if (self.attachment.launch.height > 0.0 or self.attachment.launch.vertical_velocity > 0.0) return;
        self.attachment.launch = .{};
    }

    pub fn applyRespawn(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.flushPendingParcelDeliveries();
        const session_mode = self.session_mode;
        const score = self.score;
        const visible_life_stock = self.visible_life_stock;
        const tick_count = self.tick_count;
        const stopwatch = self.stopwatch;
        const parcel_count = self.counters.parcels;
        const row_event_display = self.row_event_display;
        const collected_parcel_rows = self.parcel.collected_rows;
        const collected_parcel_row_count = self.parcel.collected_row_count;
        self.reset(preview);
        self.session_mode = session_mode;
        self.score = score;
        self.visible_life_stock = visible_life_stock;
        self.tick_count = tick_count;
        self.stopwatch = stopwatch;
        self.counters.parcels = parcel_count;
        self.row_event_display = row_event_display;
        self.parcel.collected_rows = collected_parcel_rows;
        self.parcel.collected_row_count = collected_parcel_row_count;
    }

    fn rowPositionNearRouteEnd(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (preview.total_rows == 0) return false;
        return self.row_position > preview.course_end_threshold - jetpack_auto_shutoff_margin_rows;
    }
};

fn currentRowIndex(preview: *const track.LoadedLevelPreview, row_position: f32) usize {
    return motion_module.currentRowIndex(preview, row_position);
}

fn trackParcelWorldPosition(
    preview: *const track.LoadedLevelPreview,
    row_location: track.RowLocation,
    offset: segment.Vec3,
) rl.Vector3 {
    const bounds = preview.laneBoundsForRow(row_location);
    const center_lane = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
    const floor_height = preview.floorHeightAtCellCenter(row_location.global_row, (bounds.min + bounds.max) / 2) orelse 0.0;
    const base = preview.worldPositionForLane(center_lane, @as(f32, @floatFromInt(row_location.global_row)), floor_height + 0.48);
    return .{
        .x = base.x + offset.x,
        .y = base.y + offset.y,
        .z = base.z + offset.z,
    };
}

fn returnAttachmentHint(path_center_lane: ?f32) AttachmentHint {
    return if (path_center_lane != null) .probe else .none;
}

fn progressForTicks(ticks: u16, total_ticks: u16) f32 {
    return std.math.clamp(
        @as(f32, @floatFromInt(ticks)) / @as(f32, @floatFromInt(total_ticks)),
        0.0,
        1.0,
    );
}

fn vector3ToAttachmentVec3(vector: rl.Vector3) attachment_builders.Vec3 {
    return .{
        .x = vector.x,
        .y = vector.y,
        .z = vector.z,
    };
}

fn attachmentVec3ToVector3(vector: attachment_builders.Vec3) rl.Vector3 {
    return .{
        .x = vector.x,
        .y = vector.y,
        .z = vector.z,
    };
}

const AmbientHazardSource = enum { garbage, salt };

fn runtimeRowInsideNativeSpawnWindow(preview: *const track.LoadedLevelPreview, global_row: usize) bool {
    if (global_row < preview.runtime_active_row_start) return false;
    if (global_row >= preview.runtime_active_row_end) return false;
    return @as(f32, @floatFromInt(global_row)) < preview.course_end_threshold;
}

fn shouldSpawnAmbientHazard(self: *Runner, scalar: f32, source: AmbientHazardSource) bool {
    if (scalar <= 0.0) return false;

    const roll = self.nextMathRandomFloatBelow(1.0);
    // PORT(verified): thresholds come from `update_subgame`
    // (`artifacts/ida/functions/00438b90-update_subgame.c`): garbage uses
    // `(1 - scalar) * 0.2 + 0.8` (lines 432-439) and salt uses
    // `(1 - scalar) * 0.02 + 0.98` (line 453).
    const threshold = switch (source) {
        .garbage => 0.8 + (0.2 * (1.0 - scalar)),
        .salt => 0.98 + (0.02 * (1.0 - scalar)),
    };
    return roll > threshold;
}

fn isProjectileBlockingCell(cell: u8) bool {
    return switch (cell) {
        '@', '0', '1', '2', '=' => true,
        else => false,
    };
}

const TestFixture = struct {
    catalog: assets.Catalog,
    level_definition: ?level.Definition,
    preview: track.LoadedLevelPreview,

    fn load(level_path: []const u8) !TestFixture {
        var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
        errdefer catalog.deinit();

        const level_entry = catalog.level_entries[catalog.findLevelIndex(level_path).?];
        var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
        errdefer level_definition.deinit();

        var preview = try track.LoadedLevelPreview.loadWithOptions(
            std.testing.allocator,
            &catalog,
            &level_definition,
            .{ .load_models = false },
        );
        errdefer preview.deinit();

        return .{
            .catalog = catalog,
            .level_definition = level_definition,
            .preview = preview,
        };
    }

    fn loadSegment(segment_path: []const u8) !TestFixture {
        var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
        errdefer catalog.deinit();

        const segment_entry = catalog.segment_entries[catalog.findSegmentIndex(segment_path).?];
        var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
            std.testing.allocator,
            &catalog,
            segment_entry,
            .{ .load_models = false },
        );
        errdefer preview.deinit();

        return .{
            .catalog = catalog,
            .level_definition = null,
            .preview = preview,
        };
    }

    fn deinit(self: *TestFixture) void {
        self.preview.deinit();
        if (self.level_definition) |*level_definition| {
            level_definition.deinit();
        }
        self.catalog.deinit();
    }
};

pub const RowTarget = struct {
    row: usize,
    lane: usize,
};

const AttachmentEntryTarget = struct {
    row: usize,
    lane: usize,
    path_center_lane: f32,
};

const SweptInstalledEntrySetup = struct {
    row: usize,
    previous_row_position: f32,
    row_position: f32,
    lane_center: f32,
};

test "debug warp starts a runner at an arbitrary level row" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.setCutscene(cutscene_intro_id);
    runner.debugWarpToTrackRow(&fixture.preview, 320.5, 99.0);

    try std.testing.expect(switch (runner.phase) {
        .active => true,
        else => false,
    });
    try std.testing.expect(!runner.finished);
    try std.testing.expect(!runner.introCutsceneBlocksGameplay());
    try std.testing.expectApproxEqAbs(@as(f32, 320.5), runner.row_position, 0.001);
    try std.testing.expectEqual(@as(usize, 320), runner.current_global_row);
    try std.testing.expectEqual(runner.current_global_row, runner.last_processed_row.?);
    try std.testing.expect(runner.lane_center <= @as(f32, @floatFromInt(runner.traversable_bounds.max)) + 0.5);
    try std.testing.expect(runner.currentRowMessageLogicalSegmentIndex() != null);

    runner.debugWarpToTrackRow(&fixture.preview, -10.0, null);
    try std.testing.expectEqual(@as(usize, 0), runner.current_global_row);
}

fn findFirstGameplayCell(preview: *const track.LoadedLevelPreview, kind: track.GameplayCellKind) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                if (sample.kind == kind) {
                    return .{
                        .row = global_row,
                        .lane = lane,
                    };
                }
            }
        }
    }
    return null;
}

fn findFirstRuntimeTile(preview: *const track.LoadedLevelPreview, tile_type: u8) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        for (0..preview.max_width) |lane| {
            if ((preview.runtimeTileAt(global_row, lane) orelse 0) == tile_type) {
                return .{ .row = global_row, .lane = lane };
            }
        }
    }
    return null;
}

fn findFirstRuntimeTileAtOrAfter(preview: *const track.LoadedLevelPreview, tile_type: u8, min_row: usize) ?RowTarget {
    if (min_row >= preview.total_rows) return null;
    for (min_row..preview.total_rows) |global_row| {
        for (0..preview.max_width) |lane| {
            if ((preview.runtimeTileAt(global_row, lane) orelse 0) == tile_type) {
                return .{ .row = global_row, .lane = lane };
            }
        }
    }
    return null;
}

fn findFirstRuntimeFlagB40Cell(preview: *const track.LoadedLevelPreview, expected: bool) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const bounds = preview.laneBoundsForRow(row_location);
        for (bounds.min..bounds.max + 1) |lane| {
            if (preview.runtimeFlagB40At(global_row, lane) == expected) {
                return .{ .row = global_row, .lane = lane };
            }
        }
    }
    return null;
}

fn findFirstOffCenterAttachmentEntry(preview: *const track.LoadedLevelPreview) ?AttachmentEntryTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        if (preview.segment_logical_indices[row_location.segment_index] == null) continue;
        const path_bounds = preview.pathBoundsForRow(row_location) orelse continue;
        const path_center_lane = (@as(f32, @floatFromInt(path_bounds.min + path_bounds.max)) * 0.5) + 0.5;

        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                if (sample.kind != .attachment_entry) continue;
                const lane_center = @as(f32, @floatFromInt(lane)) + 0.5;
                if (@abs(lane_center - path_center_lane) < 0.001) continue;
                return .{
                    .row = global_row,
                    .lane = lane,
                    .path_center_lane = path_center_lane,
                };
            }
        }
    }
    return null;
}

fn findSweptInstalledEntrySetup(
    runner: *Runner,
    preview: *const track.LoadedLevelPreview,
    built: *const attachment_builders.BuiltAttachment,
) !SweptInstalledEntrySetup {
    var candidate_row = built.row.global_row;
    while (candidate_row < built.row.global_row + built.template.sample_count) : (candidate_row += 1) {
        if (preview.installedBuiltAttachmentAtRow(candidate_row) != built) continue;
        const candidate_sample = runner.sampleRow(preview, candidate_row) orelse continue;
        const row_base: f32 = @floatFromInt(candidate_row);
        var lane: usize = 0;
        while (lane < preview.max_width) : (lane += 1) {
            const lane_center = @as(f32, @floatFromInt(lane)) + 0.5;
            var start_step: i32 = -4;
            while (start_step <= 10) : (start_step += 1) {
                var end_step = start_step + 1;
                while (end_step <= 12) : (end_step += 1) {
                    runner.lane_center = lane_center;
                    runner.previous_lane_center = lane_center;
                    runner.previous_row_position = row_base + (@as(f32, @floatFromInt(start_step)) * 0.05);
                    runner.row_position = row_base + (@as(f32, @floatFromInt(end_step)) * 0.05);
                    if (runner.geometricInstalledAttachmentEntry(preview, built, candidate_sample) != null) {
                        return .{
                            .row = candidate_row,
                            .previous_row_position = runner.previous_row_position,
                            .row_position = runner.row_position,
                            .lane_center = lane_center,
                        };
                    }
                }
            }
        }
    }
    return error.TestUnexpectedResult;
}

fn findFirstAnnotationTag(preview: *const track.LoadedLevelPreview, tag: segment.Annotation.Tag) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const annotation = row_location.row.annotation orelse continue;
        if (annotation.tag() != tag) continue;
        const bounds = preview.laneBoundsForRow(row_location);
        const center_lane = (bounds.min + bounds.max) / 2;
        return .{
            .row = global_row,
            .lane = center_lane,
        };
    }
    return null;
}

fn findFirstRawCell(preview: *const track.LoadedLevelPreview, cell: u8) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        for (row_location.row.cells, 0..) |row_cell, lane| {
            if (row_cell == cell) {
                return .{ .row = global_row, .lane = lane };
            }
        }
    }
    return null;
}

fn findFirstFloorGap(preview: *const track.LoadedLevelPreview, require_no_fall: bool) ?RowTarget {
    for (1..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const annotation_tag = if (row_location.row.annotation) |annotation| annotation.tag() else null;
        const wants_no_fall = annotation_tag == .no_fall;
        if (wants_no_fall != require_no_fall) continue;
        if (!rowHasAnyFloor(preview, global_row)) continue;

        const bounds = preview.laneBoundsForRow(row_location);
        for (bounds.min..bounds.max + 1) |lane| {
            const gameplay_kind = if (preview.gameplayCellSampleAt(global_row, lane)) |sample| sample.kind else null;
            if (gameplay_kind == .attachment_entry or gameplay_kind == .attachment_probe) continue;
            if (preview.sampleFloorHeightAtGridPosition(
                global_row,
                lane,
                @as(f32, @floatFromInt(global_row)) + 0.5,
            ) != null) continue;
            return .{
                .row = global_row,
                .lane = lane,
            };
        }
    }
    return null;
}

fn rowHasAnyFloor(preview: *const track.LoadedLevelPreview, global_row: usize) bool {
    const row_location = preview.locateRow(global_row) orelse return false;
    for (row_location.row.cells, 0..) |_, lane| {
        if (preview.sampleFloorHeightAtGridPosition(
            global_row,
            lane,
            @as(f32, @floatFromInt(global_row)) + 0.5,
        ) != null) return true;
    }
    return false;
}

fn primeRunnerBeforeRow(runner: *Runner, preview: *const track.LoadedLevelPreview, target: RowTarget) void {
    std.debug.assert(target.row > 0);
    runner.reset(preview);

    // When `target.row` sits inside an installed attachment span, naïve priming at
    // `target.row - 1` leaves the runner in `.track` mode over a no-floor tile, and
    // the native-faithful `stepActivePhaseVerticalMotion` pulls `position_y` below
    // `-7` via real gravity within a dozen ticks. Native gameplay never reaches
    // these rows outside attachment follow, so instead seed the runner on the
    // grounded row immediately before the attachment's entry and step naturally
    // through the entry/follow flow until it arrives.
    if (preview.installedBuiltAttachmentAtRow(target.row)) |built| {
        const entry_row = built.row.global_row;
        if (entry_row > 0 and target.row > entry_row) {
            runner.runtime_track_index = entry_row - 1;
            runner.track_row_progress = 0.99;
            runner.syncRowPosition(preview);
            runner.refreshSample(preview);
            runner.last_processed_row = entry_row - 1;

            const max_attachment_prime_ticks: u32 = 2048;
            var ticks: u32 = 0;
            while (ticks < max_attachment_prime_ticks) : (ticks += 1) {
                if (runner.phase != .active) break;
                if (runner.current_global_row + 1 >= target.row) break;
                runner.step(preview, .{}, 1.0 / 60.0);
            }
            runner.last_processed_row = runner.current_global_row;
            return;
        }
    }

    runner.lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    runner.runtime_track_index = target.row - 1;
    runner.track_row_progress = 0.99;
    runner.syncRowPosition(preview);
    runner.refreshSample(preview);
    runner.last_processed_row = target.row - 1;
}

fn primeRunnerAfterFirstInstalledAttachment(runner: *Runner, preview: *const track.LoadedLevelPreview) void {
    const target = findFirstGameplayCell(preview, .attachment_entry).?;
    const built = preview.installedBuiltAttachmentAtRow(target.row).?;
    const start_row = target.row + built.template.sample_count + 2;

    runner.reset(preview);
    runner.runtime_track_index = start_row;
    runner.track_row_progress = 0.0;
    runner.syncRowPosition(preview);
    runner.refreshSample(preview);
    runner.last_processed_row = start_row;
}

fn setRunnerLiveRowTarget(runner: *Runner, target: RowTarget) void {
    runner.lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.01;
}

fn stepUntilHandoff(runner: *Runner, preview: *const track.LoadedLevelPreview, max_steps: usize) usize {
    var steps: usize = 0;
    while (steps < max_steps and runner.handoff.pending == .none) : (steps += 1) {
        runner.step(preview, .{}, 1.0 / 60.0);
    }
    return steps;
}

fn stepUntilParcelPickup(runner: *Runner, preview: *const track.LoadedLevelPreview, max_steps: usize) usize {
    var steps: usize = 0;
    while (steps < max_steps and runner.counters.parcels == 0) : (steps += 1) {
        runner.step(preview, .{}, 1.0 / 60.0);
    }
    return steps;
}

fn stepUntilParcelRegistered(runner: *Runner, preview: *const track.LoadedLevelPreview, max_steps: usize) usize {
    var steps: usize = 0;
    while (steps < max_steps and runner.registeredParcelCount() == 0) : (steps += 1) {
        runner.step(preview, .{}, 1.0 / 60.0);
    }
    return steps;
}

fn expectVector3ApproxEq(expected: rl.Vector3, actual: rl.Vector3, tolerance: f32) !void {
    try std.testing.expectApproxEqAbs(expected.x, actual.x, tolerance);
    try std.testing.expectApproxEqAbs(expected.y, actual.y, tolerance);
    try std.testing.expectApproxEqAbs(expected.z, actual.z, tolerance);
}

fn expectCameraMatrixApproxEq(expected: rl.Matrix, actual: rl.Matrix, tolerance: f32) !void {
    const expected_transform = normalizeCameraTransform(cameraTransformFromMatrix(expected));
    const actual_transform = normalizeCameraTransform(cameraTransformFromMatrix(actual));

    try expectVector3ApproxEq(expected_transform.position, actual_transform.position, tolerance);
    try expectVector3ApproxEq(expected_transform.right, actual_transform.right, tolerance);
    try expectVector3ApproxEq(expected_transform.up, actual_transform.up, tolerance);
    try expectVector3ApproxEq(expected_transform.forward, actual_transform.forward, tolerance);
}

fn vector3DistanceSquared(a: rl.Vector3, b: rl.Vector3) f32 {
    const delta_x = a.x - b.x;
    const delta_y = a.y - b.y;
    const delta_z = a.z - b.z;
    return (delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z);
}

fn laneOutsideAttachmentWidth(
    preview: *const track.LoadedLevelPreview,
    built: *const attachment_builders.BuiltAttachment,
    global_row: usize,
) ?usize {
    const progress: f32 = @floatFromInt(global_row - built.row.global_row);
    const centered_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        progress,
        built.row.global_row,
        0.0,
        0.0,
    );
    const half_width = Runner.attachmentTemplateHalfSpan(built);

    for (0..preview.max_width) |lane| {
        const lane_center = @as(f32, @floatFromInt(lane)) + 0.5;
        const entry_world_position = Runner.trackEntryWorldPosition(
            preview,
            @as(f32, @floatFromInt(global_row)),
            lane_center,
        );
        const local_x = Runner.attachmentLocalPosition(centered_pose, entry_world_position).x;
        if (@abs(local_x) > half_width + attachment_side_exit_margin) return lane;
    }
    return null;
}

test "cameraman vertical lift weights cached target y early and late" {
    try std.testing.expectApproxEqAbs(@as(f32, 1.15), cameramanVerticalLiftFromCachedTarget(1.0, 0.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.35), cameramanVerticalLiftFromCachedTarget(1.0, 1.0), 0.0001);
    try std.testing.expect(cameramanVerticalLiftFromCachedTarget(1.0, 0.0) > cameramanVerticalLiftFromCachedTarget(1.0, 1.0));
}

test "cameraman cached-target pitch matches the recovered register formula" {
    try std.testing.expectApproxEqAbs(@as(f32, -0.0348999984), cameramanPitchRadiansFromCachedTarget(0.49), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -1.22149992), cameramanPitchRadiansFromCachedTarget(48.0), 0.0001);
}

test "cameraman deadzone clamps previous desired z around the desired camera z" {
    try std.testing.expectApproxEqAbs(@as(f32, 9.0), clampedPreviousDesiredCameraZ(12.0, 2.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 10.29999995), clampedPreviousDesiredCameraZ(12.0, 11.5), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 10.0), clampedPreviousDesiredCameraZ(12.0, 10.0), 0.0001);
}

test "worm template kind alone boosts cameraman fov" {
    var worm_fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer worm_fixture.deinit();

    var worm_runner = Runner.init(&worm_fixture.preview);
    const worm_target = findFirstGameplayCell(&worm_fixture.preview, .attachment_entry).?;
    const worm_built = worm_fixture.preview.installedBuiltAttachmentAtRow(worm_target.row).?;
    const worm_centered = attachment_builders.worldPositionForTemplate(
        &worm_built.template,
        0.0,
        worm_built.row.global_row,
        0.0,
        0.0,
    );
    const worm_center_lane = Runner.laneCenterFromWorldX(&worm_fixture.preview, worm_centered.x);
    primeRunnerBeforeRow(&worm_runner, &worm_fixture.preview, worm_target);
    worm_runner.lane_center = worm_center_lane;
    worm_runner.lane_index = Runner.laneIndexForLaneCenter(&worm_fixture.preview, worm_center_lane);
    worm_runner.resolved_lane_index = worm_runner.lane_index;
    worm_runner.refreshSample(&worm_fixture.preview);
    worm_runner.step(&worm_fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, worm_runner.movement_mode);
    try std.testing.expect(worm_runner.cameramanFovDegrees() > 110.0);

    var start_fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer start_fixture.deinit();

    var start_runner = Runner.init(&start_fixture.preview);
    const start_target = findFirstGameplayCell(&start_fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&start_runner, &start_fixture.preview, start_target);
    start_runner.step(&start_fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, start_runner.movement_mode);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), start_runner.cameramanFovDegrees(), 0.001);
}

test "rolled attachments publish camera orientation a from sample roll" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/INVERT.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "INVERT";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 8.5,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);
    runner.refreshCameraRollState(&fixture.preview);

    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const clamped_progress = std.math.clamp(
        runner.attachment.follow.template_progress,
        0.0,
        @as(f32, @floatFromInt(built.template.sample_count)),
    );
    const segment_base_index = @min(
        @as(usize, @intFromFloat(@floor(clamped_progress))),
        @as(usize, built.template.sample_count - 1),
    );
    const segment_base_progress: f32 = @floatFromInt(segment_base_index);
    const segment_delta_length = attachment_builders.deltaLengthAtProgress(&built.template, segment_base_progress);
    const normalized_segment_progress = if (segment_delta_length <= 0.0001)
        0.0
    else
        std.math.clamp((clamped_progress - segment_base_progress) / segment_delta_length, 0.0, 1.0);
    const expected = interpolateWrappedRadians(
        attachmentSampleOrientationA(&built.template.samples[segment_base_index]),
        attachmentSampleOrientationA(&built.template.samples[segment_base_index + 1]),
        normalized_segment_progress,
    );

    try std.testing.expect(@abs(expected) > 0.0001);
    try std.testing.expectApproxEqAbs(expected, runner.attachment.follow.camera_orientation_a, 0.0001);
    try std.testing.expectApproxEqAbs(expected, runner.attachment.camera.orientation_a, 0.0001);
}

test "rolled attachments use world x for side-exit threshold" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/INVERT.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const template_progress = 17.0;
    const lateral_offset = 8.0;
    const pose = attachment_builders.samplePoseAtProgress(&built.template, template_progress);
    const world_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        template_progress,
        target.row,
        lateral_offset,
        0.0,
    );
    const subdivision_count = built.template.spec.subdivision_count orelse built.template.width_cells;
    const half_width = @as(f32, @floatFromInt(subdivision_count)) * 0.5;
    const local_delta = @abs(lateral_offset * pose.lateral_scale);
    const world_delta_x = @abs(world_pose.position.x - pose.center_x);

    try std.testing.expect(local_delta > half_width + attachment_side_exit_margin);
    try std.testing.expect(world_delta_x <= half_width + attachment_side_exit_margin);

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "INVERT";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = template_progress,
        .lateral_offset = lateral_offset,
    };

    try std.testing.expect(!runner.attachmentShouldSideExit(built));
}

test "attachment side exit uses subdivision count rather than template width" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const width_threshold = (@as(f32, @floatFromInt(built.template.width_cells)) * 0.5) + attachment_side_exit_margin;
    const subdivision_count = built.template.spec.subdivision_count orelse built.template.width_cells;
    const subdivision_threshold = (@as(f32, @floatFromInt(subdivision_count)) * 0.5) + attachment_side_exit_margin;

    var matching_lateral_offset: ?f32 = null;
    var lateral_offset = width_threshold + 0.25;
    while (lateral_offset < subdivision_threshold + 0.5) : (lateral_offset += 0.25) {
        const pose = attachment_builders.samplePoseAtProgress(&built.template, 12.0);
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            12.0,
            target.row,
            lateral_offset,
            0.0,
        );
        const world_delta_x = @abs(world_pose.position.x - pose.center_x);
        if (world_delta_x > width_threshold and world_delta_x <= subdivision_threshold) {
            matching_lateral_offset = lateral_offset;
            break;
        }
    }
    try std.testing.expect(matching_lateral_offset != null);

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "WORM";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 12.0,
        .lateral_offset = matching_lateral_offset.?,
    };

    try std.testing.expect(!runner.attachmentShouldSideExit(built));
}

test "attachment follow advances template progress by path factor" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "WORM";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.0,
        .installed_heading_delta = built.template.installed_heading_delta,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);

    const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, 5.0);
    try std.testing.expect(@abs(delta_length - 1.0) > 0.0001);

    runner.track_step_rows = 0.25;
    runner.advanceAttachmentFollow(&fixture.preview);

    try std.testing.expectApproxEqAbs(@as(f32, 5.25), runner.attachment.follow.template_progress, 0.0001);
}

test "installed attachment begin preserves raw local progress and advances once immediately" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    var runner = Runner.init(&fixture.preview);
    primeRunnerBeforeRow(&runner, &fixture.preview, target);
    runner.track_step_rows = 0.25;

    const entry = runner.currentRowInstalledAttachmentEntry(&fixture.preview, built, target.row).?;
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), entry.local_progress, 0.0001);

    runner.beginInstalledAttachmentFollow(&fixture.preview, built, entry);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment.follow.active);
    try std.testing.expectEqual(@as(usize, 0), runner.attachment.follow.sample_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), runner.attachment.follow.template_progress, 0.0001);
}

test "attachment follow updates heading roll from the live phase scalar" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "WORM";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.0,
        .installed_heading_delta = built.template.installed_heading_delta,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);

    runner.stepAttachmentFollowAtRate(&fixture.preview, 0.0);

    try std.testing.expectApproxEqAbs(built.template.installed_heading_delta, runner.attachment.camera.heading_roll, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.attachment.follow.template_progress, 0.0001);
}

test "attachment follow keeps zero phase scalar on position refresh" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "WORM";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.0,
        .installed_heading_delta = 0.0,
    };

    runner.updateAttachmentFollowPosition(&fixture.preview);

    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.follow.installed_heading_delta, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.follow.camera_orientation_b, 0.0001);
}

test "attachment follow clamps negative vertical offset after live update" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "START";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.0,
        .vertical_offset = -0.25,
    };

    runner.stepAttachmentFollowAtRate(&fixture.preview, 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.follow.vertical_offset, 0.0001);

    runner.stepAttachmentFollowAtRate(&fixture.preview, 0.0);
    const expected_world = attachment_builders.worldPositionForTemplate(
        &built.template,
        runner.attachment.follow.template_progress,
        target.row,
        runner.attachment.follow.lateral_offset,
        0.0,
    );
    try std.testing.expectApproxEqAbs(expected_world.y, runner.attachment.follow.cached_output_position.y, 0.0001);
}

test "attachment follow clamps output x to gameplay bounds" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const raw_position = attachment_builders.worldPositionForTemplate(
        &built.template,
        5.0,
        target.row,
        100.0,
        0.0,
    );
    const expected_clamped_x = std.math.clamp(raw_position.x, -4.0, 4.0);
    try std.testing.expect(@abs(raw_position.x) > 4.0);

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "START";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.0,
        .lateral_offset = 100.0,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);

    try std.testing.expectApproxEqAbs(expected_clamped_x, runner.attachment.follow.cached_output_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(expected_clamped_x, runner.worldPosition(&fixture.preview, 0.0).x, 0.0001);
}

test "attachment camera lift uses overall attachment progress" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "START";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = 5.5,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);

    const attachment_camera = runner.currentAttachmentCameraProgress(&fixture.preview).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const expected_progress =
        (runner.playerWorldPosition(&fixture.preview).z - @as(f32, @floatFromInt(target.row))) /
        @as(f32, @floatFromInt(built.template.sample_count));
    try std.testing.expectEqual(attachment_builders.template_kind_start, attachment_camera.template_kind);
    try std.testing.expectApproxEqAbs(expected_progress, attachment_camera.template_progress, 0.0001);
}

test "runner advances deterministically over fixed time" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    primeRunnerAfterFirstInstalledAttachment(&runner, &fixture.preview);
    const start_row = runner.runtime_track_index;
    for (0..120) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(start_row)) + 24.0, runner.row_position, 0.001);
    try std.testing.expectEqual(start_row + 24, runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.track_row_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.track_step_rows, 0.0001);
    try std.testing.expectEqual(@as(u64, 120), runner.tick_count);
}

test "runner keeps discrete track cursor and fractional movement progress" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    primeRunnerAfterFirstInstalledAttachment(&runner, &fixture.preview);
    const start_row = runner.runtime_track_index;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(start_row, runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.track_row_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(start_row)) + 0.2, runner.row_position, 0.0001);

    for (0..4) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(start_row + 1, runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.track_row_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(start_row + 1)), runner.row_position, 0.0001);
}

test "runner discovers attachment hint rows in shipped corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/ARCADE000.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    var found_attachment_hint = false;
    for (0..1024) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
        if (runner.attachment.hint != .none) {
            found_attachment_hint = true;
            break;
        }
    }

    try std.testing.expect(found_attachment_hint);
}

test "runner records pickup and hazard encounters from shipped tutorial" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const health = findFirstGameplayCell(&fixture.preview, .health).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, health);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.health_pickups);
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
    try std.testing.expectEqual(@as(u32, 0), runner.score.health_collect);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.gauge, 0.0001);
    try std.testing.expectEqualStrings("health_pickup", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, salt);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.salt_hits);
    // Native-literal assertion: `cRSalt` collisions apply `+0.15f` to the
    // contact-damage gauge (task #3). Self-referential checks against
    // `salt_damage_delta` would silently pass if the constant drifts; anchor
    // on the native value directly.
    try std.testing.expectApproxEqAbs(@as(f32, 0.15), runner.damage.gauge, 0.0001);
    try std.testing.expectApproxEqAbs(salt_damage_delta, runner.damage.gauge, 0.0001);
    try std.testing.expectEqualStrings("salt_hit", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.slug_hits);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.gauge, 0.0001);
    try std.testing.expectEqualStrings("slug_hit", runner.recentEventLabel());
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);

    runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, garbage);
    const speed_before_garbage = runner.speed_rows_per_second;
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqual(@as(u32, 10), runner.score.total);
    try std.testing.expectEqual(@as(u32, 10), runner.score.garbage_collision);
    try std.testing.expectApproxEqAbs(garbage_damage_delta, runner.damage.gauge, 0.0001);
    try std.testing.expect(runner.speed_rows_per_second != speed_before_garbage);
    try std.testing.expect(runner.last_garbage_hit_position != null);
    try std.testing.expectEqualStrings("garbage_hit", runner.recentEventLabel());
}

test "runtime health pickup collides by distance before exact row crossing" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const health = findFirstGameplayCell(&fixture.preview, .health).?;
    runner.reset(&fixture.preview);
    runner.lane_index = health.lane;
    runner.lane_center = @as(f32, @floatFromInt(health.lane)) + 0.5;
    runner.runtime_track_index = health.row - 1;
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimePickup(&fixture.preview, health.row, health.lane, .health);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimePickups().len);
    runner.processRuntimePickupCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 0), runner.activeRuntimePickups().len);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.health_pickups);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.gauge, 0.0001);
    try std.testing.expectEqualStrings("health_pickup", runner.recentEventLabel());
}

test "runtime health pickup keeps native bob phase and presentation lift" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const health = findFirstGameplayCell(&fixture.preview, .health).?;
    runner.addRuntimePickup(&fixture.preview, health.row, health.lane, .health);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimePickups().len);
    const base_position = runner.activeRuntimePickups()[0].world_position;
    const initial_phase: f32 = if ((health.row & 1) == 0) 0.5 else 0.0;
    runner.updateRuntimePickups();

    const pickup = runner.activeRuntimePickups()[0];
    const expected_phase = @mod(initial_phase + runtime_pickup_phase_step, 1.0);
    const expected_y = base_position.y + (@sin(expected_phase * std.math.tau) + 1.0) * runtime_health_pickup_bob_height;
    try std.testing.expectApproxEqAbs(expected_phase, pickup.bob_phase, 0.0001);
    try std.testing.expectApproxEqAbs(base_position.x, pickup.presentation_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(expected_y, pickup.presentation_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(base_position.z, pickup.presentation_position.z, 0.0001);
}

test "runtime jetpack pickup lateral bias follows native edge and neighbor checks" {
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        Runner.runtimeJetpackPickupLateralBiasFromContext(3, 0, 0x0e, 0, 0x0e),
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, -0.5),
        Runner.runtimeJetpackPickupLateralBiasFromContext(4, 0x0e, 0, 0x0e, 0),
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.0),
        Runner.runtimeJetpackPickupLateralBiasFromContext(3, 0, 0, 0, 0x0e),
        0.0001,
    );
}

test "runtime jetpack pickup collides by distance before exact row crossing" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const jetpack = findFirstGameplayCell(&fixture.preview, .jetpack).?;
    runner.reset(&fixture.preview);
    runner.lane_index = jetpack.lane;
    runner.lane_center = @as(f32, @floatFromInt(jetpack.lane)) + 0.5;
    runner.runtime_track_index = jetpack.row - 1;
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimePickup(&fixture.preview, jetpack.row, jetpack.lane, .jetpack);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimePickups().len);
    runner.processRuntimePickupCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 0), runner.activeRuntimePickups().len);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_pickups);
    try std.testing.expect(runner.jetpack.active);
    try std.testing.expectEqualStrings("jetpack_pickup", runner.recentEventLabel());
}

test "runtime garbage hazards collide by distance before exact row crossing" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    runner.reset(&fixture.preview);
    runner.lane_index = garbage.lane;
    runner.lane_center = @as(f32, @floatFromInt(garbage.lane)) + 0.5;
    runner.runtime_track_index = garbage.row - 1;
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(&fixture.preview, garbage.row, garbage.lane, .garbage);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeHazards().len);
    runner.processRuntimeHazardCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeHazards().len);
    try std.testing.expectEqual(RuntimeHazardState.burst_setup, runner.activeRuntimeHazards()[0].state);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqualStrings("garbage_hit", runner.recentEventLabel());
}

test "oblique garbage collisions push the runner sideways" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    runner.reset(&fixture.preview);
    runner.lane_index = garbage.lane;
    runner.lane_center = @as(f32, @floatFromInt(garbage.lane)) + 0.8;
    runner.runtime_track_index = garbage.row - 1;
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(&fixture.preview, garbage.row, garbage.lane, .garbage);

    const lane_before = runner.lane_center;
    runner.processRuntimeHazardCollisions(&fixture.preview);
    try std.testing.expectApproxEqAbs(lane_before, runner.lane_center, 0.0001);
    try std.testing.expect(runner.native_velocity_x_per_tick > 0.0);

    runner.stepNativeVelocityX(&fixture.preview);
    try std.testing.expect(runner.lane_center > lane_before);

    const velocity_after_first_tick = runner.native_velocity_x_per_tick;
    runner.stepNativeVelocityX(&fixture.preview);
    try std.testing.expect(runner.native_velocity_x_per_tick < velocity_after_first_tick);
}

test "mouse steering damps carried native lateral velocity in native order" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.reset(&fixture.preview);
    runner.lane_center = 4.5;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);
    runner.refreshSample(&fixture.preview);
    runner.native_velocity_x_per_tick = 0.5;

    runner.step(&fixture.preview, .{ .target_lane_center = 4.5 }, 1.0 / native_ticks_per_second);

    try std.testing.expect(runner.lane_center > 4.5);
    try std.testing.expect(runner.lane_center < 4.75);
    try std.testing.expectApproxEqAbs(@as(f32, 0.3), runner.native_velocity_x_per_tick, 0.0001);
}

test "garbage impact follows the recovered direction-vector formulas" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.reset(&fixture.preview);
    runner.speed_rows_per_second = 12.0;
    runner.lane_center = 4.5;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);
    runner.refreshSample(&fixture.preview);

    const player_position = runner.worldPosition(&fixture.preview, 0.4);
    const impact_position = rl.Vector3{
        .x = player_position.x - 0.2,
        .y = player_position.y,
        .z = player_position.z + 0.8,
    };
    const distance = @sqrt(0.68);
    const expected_speed = 12.0 - (((impact_position.z - player_position.z) / distance) * 12.0 * 0.10);
    const expected_velocity_x =
        -(((impact_position.x - player_position.x) / distance) * (12.0 / native_ticks_per_second) * 0.18);

    runner.applyGarbageImpact(&fixture.preview, impact_position);

    try std.testing.expectApproxEqAbs(expected_speed, runner.speed_rows_per_second, 0.0001);
    try std.testing.expectApproxEqAbs(expected_velocity_x, runner.native_velocity_x_per_tick, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 4.5), runner.lane_center, 0.0001);
}

test "invincible garbage collisions skip native motion writes but still resolve the hit" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    runner.reset(&fixture.preview);
    runner.lane_index = garbage.lane;
    runner.lane_center = @as(f32, @floatFromInt(garbage.lane)) + 0.8;
    runner.runtime_track_index = garbage.row - 1;
    runner.track_row_progress = 0.6;
    runner.presentation.invincible_ticks = 30;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(&fixture.preview, garbage.row, garbage.lane, .garbage);

    const speed_before = runner.speed_rows_per_second;
    runner.processRuntimeHazardCollisions(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqual(@as(u32, 10), runner.score.total);
    try std.testing.expectApproxEqAbs(garbage_damage_delta, runner.damage.gauge, 0.0001);
    try std.testing.expectApproxEqAbs(speed_before, runner.speed_rows_per_second, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.native_velocity_x_per_tick, 0.0001);
}

test "garbage burst hazards keep live world motion after contact" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    runner.reset(&fixture.preview);
    runner.lane_index = garbage.lane;
    runner.lane_center = @as(f32, @floatFromInt(garbage.lane)) + 0.5;
    runner.runtime_track_index = garbage.row - 1;
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(&fixture.preview, garbage.row, garbage.lane, .garbage);

    runner.processRuntimeHazardCollisions(&fixture.preview);
    const before = runner.activeRuntimeHazards()[0].world_position;
    runner.updateRuntimeHazards(&fixture.preview);
    const after = runner.activeRuntimeHazards()[0].world_position;

    try std.testing.expectEqual(RuntimeHazardState.burst, runner.activeRuntimeHazards()[0].state);
    try std.testing.expect(after.x != before.x or after.y != before.y or after.z != before.z);
}

test "slug hit latches the shared fall path" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.gauge, 0.0001);
    try std.testing.expect(runner.damage.slug_hit_active);
    // PORT(verified): first-hit velocity triplet from
    // `artifacts/ida/functions/00444cf0-handle_subgoldy_collisions.c:197-200`.
    // The fall state captures `velocity_y` before `beginFallState` clears it,
    // so the initial knockback velocity should equal `track_center_x * 0.2`.
    try std.testing.expectApproxEqAbs(
        native_track_center_x * 0.2,
        runner.phase.fall.vertical_velocity,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        native_track_center_x * -0.2,
        runner.native_velocity_z_override_per_tick.?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.native_velocity_x_per_tick, 0.0001);
}

test "repeat slug hit applies the native velocity.z knockback and damage delta" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    // First hit transitions the runner to the fall phase; recover back into a
    // simulated "already latched" state to exercise the repeat path that
    // native takes when Goldy re-contacts a slug from inside the hit/fall
    // block (`handle_subgoldy_collisions.c:183-188`).
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.damage.slug_hit_active = true;
    runner.processRow(&fixture.preview, slug.row);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage.gauge, 0.0001);
    try std.testing.expectApproxEqAbs(
        native_track_center_x * native_track_center_x * 0.0040000002 * -8.0,
        runner.native_velocity_z_override_per_tick.?,
        0.0001,
    );
}

test "powerup rings upgrade weapon level then grant invincible state" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 1), runner.presentation.weapon_level);
    try std.testing.expectEqual(@as(u8, 1), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 2), runner.presentation.movement_flags);
    try std.testing.expectEqual(@as(u16, 0), runner.presentation.invincible_ticks);

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 2), runner.presentation.weapon_level);
    try std.testing.expectEqual(@as(u8, 2), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 4), runner.presentation.movement_flags);
    try std.testing.expectEqual(@as(u16, 0), runner.presentation.invincible_ticks);

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 2), runner.presentation.weapon_level);
    try std.testing.expectEqual(@as(u8, 3), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 8), runner.presentation.movement_flags);
    try std.testing.expectEqual(invincible_duration_ticks, runner.presentation.invincible_ticks);
}

test "powerup ladder bounces between native top selector states" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};
    for (0..8) |_| {
        runner.recordRing(&fixture.preview, .powerup);
    }
    try std.testing.expectEqual(@as(u8, 8), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 144), runner.presentation.movement_flags);

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 7), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 192), runner.presentation.movement_flags);
}

test "slow rings reduce effective speed while active" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};
    runner.speed_rows_per_second = 18.0;

    runner.recordRing(&fixture.preview, .slow);
    try std.testing.expectEqual(slow_ring_duration_ticks, runner.presentation.slow_ticks);
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
    try std.testing.expectEqual(@as(u32, 0), runner.score.ring_collect);
    try std.testing.expectApproxEqAbs(@as(f32, 9.0), runner.effectiveSpeedRowsPerSecond(), 0.0001);

    runner.stepTemporaryStates();
    try std.testing.expectEqual(@as(u16, slow_ring_duration_ticks - 1), runner.presentation.slow_ticks);
}

test "native ring kind 3 seeds the recovered negative-velocity shove" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};
    runner.speed_rows_per_second = 18.0;

    runner.recordNativeRingEffect(&fixture.preview, 3);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.ring_slow);
    try std.testing.expectEqual(@as(u16, 0), runner.presentation.slow_ticks);
    try std.testing.expectApproxEqAbs(
        native_negative_ring_velocity_z_per_tick * native_ticks_per_second,
        runner.effectiveSpeedRowsPerSecond(),
        0.0001,
    );
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
    try std.testing.expectEqualStrings("ring_slow", runner.recentEventLabel());
}

test "native negative-velocity ring recovery moves backward before handing back to base speed" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.speed_rows_per_second = 12.0;
    runner.runtime_track_index = 40;
    runner.track_row_progress = 0.0;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);

    const row_before = runner.row_position;
    runner.recordNativeRingEffect(&fixture.preview, 3);
    runner.step(&fixture.preview, .{}, 1.0 / native_ticks_per_second);
    try std.testing.expect(runner.row_position < row_before);
    try std.testing.expectApproxEqAbs(@as(f32, 39.916), runner.row_position, 0.0001);

    for (0..6) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / native_ticks_per_second);
    }
    try std.testing.expectEqual(@as(?f32, null), runner.native_velocity_z_override_per_tick);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), runner.effectiveSpeedRowsPerSecond(), 0.0001);
}

test "tutorial powerup ramps consume the recovered forward runtime ring event" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 7.0;
    runner.refreshLiveRuntimeRingEffects(&fixture.preview);

    runner.processRuntimeRingEffectCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.ring_powerup);
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);

    runner.row_position = 13.0;
    runner.processRuntimeRingEffectCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.ring_powerup);
    try std.testing.expectEqual(@as(u8, 1), runner.presentation.movement_flag_selector);
    try std.testing.expectEqual(@as(u32, 2), runner.presentation.movement_flags);
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
    try std.testing.expectEqualStrings("ring_powerup", runner.recentEventLabel());
    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeRingEffects().len);
    try std.testing.expectEqual(RuntimeRingEffectState.collect_setup, runner.activeRuntimeRingEffects()[0].state);
}

test "explicit tutorial ring rows still consume their native same-row effects" {
    var powerup_fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer powerup_fixture.deinit();

    var powerup_runner = Runner.init(&powerup_fixture.preview);
    powerup_runner.lane_index = 1;
    powerup_runner.lane_center = 1.5;
    powerup_runner.row_position = 51.0;
    powerup_runner.refreshLiveRuntimeRingEffects(&powerup_fixture.preview);
    powerup_runner.processRuntimeRingEffectCollisions(&powerup_fixture.preview);
    try std.testing.expectEqual(@as(u32, 1), powerup_runner.counters.ring_powerup);
    try std.testing.expectEqual(@as(u32, 0), powerup_runner.score.total);

    var slow_fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 7.TXT");
    defer slow_fixture.deinit();

    var slow_runner = Runner.init(&slow_fixture.preview);
    slow_runner.lane_index = 4;
    slow_runner.lane_center = 4.5;
    slow_runner.row_position = 27.0;
    slow_runner.refreshLiveRuntimeRingEffects(&slow_fixture.preview);
    slow_runner.processRuntimeRingEffectCollisions(&slow_fixture.preview);
    try std.testing.expectEqual(@as(u32, 1), slow_runner.counters.ring_slow);
    try std.testing.expectEqual(@as(u16, 0), slow_runner.presentation.slow_ticks);
    try std.testing.expectApproxEqAbs(
        native_negative_ring_velocity_z_per_tick * native_ticks_per_second,
        slow_runner.effectiveSpeedRowsPerSecond(),
        0.0001,
    );
    try std.testing.expectEqual(@as(u32, 0), slow_runner.score.total);
}

test "tutorial default ramp rings consume the native runtime event lane" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial11_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 11.TXT") orelse return error.EntryNotFound;
    var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial11_entry,
        .{
            .load_models = false,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
        },
    );
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 22.0;
    runner.refreshLiveRuntimeRingEffects(&preview);
    var found_target_effect = false;
    for (runner.activeRuntimeRingEffects()) |effect| {
        if (effect.row == 39 and effect.lane == 1 and effect.kind == 2) {
            found_target_effect = true;
            break;
        }
    }
    try std.testing.expect(found_target_effect);

    runner.row_position = 39.0;
    runner.processRuntimeRingEffectCollisions(&preview);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.ring_explode);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.ring_collect);
    try std.testing.expectEqual(slug_projectile_kill_score, runner.score.garbage_collision);
    try std.testing.expectEqual(@as(usize, 1), runner.defeated_slug_cell_count);
    try std.testing.expectEqualStrings("ring_explode", runner.recentEventLabel());
    var found_collect_setup = false;
    for (runner.activeRuntimeRingEffects()) |effect| {
        if (effect.state == .collect_setup) {
            found_collect_setup = true;
            break;
        }
    }
    try std.testing.expect(found_collect_setup);
}

test "runtime ring effect keeps source row and native presentation anchor" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 51.0;
    runner.refreshLiveRuntimeRingEffects(&fixture.preview);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeRingEffects().len);
    const effect = runner.activeRuntimeRingEffects()[0];
    try std.testing.expectEqual(@as(usize, 51), effect.source_row);
    try std.testing.expectEqual(@as(usize, 51), effect.row);
    try std.testing.expect(!effect.active_x_oscillation_enabled);
    try std.testing.expectApproxEqAbs(
        Runner.runtimeCellWorldPosition(&fixture.preview, 51, 1, runtime_ring_spawn_y_offset_default).y,
        effect.presentation_position.y,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        Runner.runtimeCellWorldPosition(&fixture.preview, 51, 1, Runner.runtimeRingCollisionYOffset(effect.kind)).y,
        effect.collision_position.y,
        0.0001,
    );
}

test "default ramp ring keeps proxy collision anchor while using native presentation spawn" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial11_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 11.TXT") orelse return error.EntryNotFound;
    var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial11_entry,
        .{
            .load_models = false,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
        },
    );
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.math_random_state = 0;
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 22.0;
    runner.refreshLiveRuntimeRingEffects(&preview);

    for (runner.activeRuntimeRingEffects()) |effect| {
        if (effect.row == 39 and effect.lane == 1 and effect.kind == 2) {
            try std.testing.expectApproxEqAbs(
                Runner.runtimeCellWorldPosition(&preview, 39, 1, runtime_ring_spawn_y_offset_explode_ramp).y,
                effect.presentation_position.y,
                0.0001,
            );
            try std.testing.expectApproxEqAbs(
                Runner.runtimeCellWorldPosition(&preview, 39, 1, Runner.runtimeRingCollisionYOffset(effect.kind)).y,
                effect.collision_position.y,
                0.0001,
            );
            try std.testing.expect(effect.active_x_oscillation_enabled);
            try std.testing.expect(effect.presentation_position.x != effect.collision_position.x);
            return;
        }
    }

    return error.ExpectedRuntimeRingEffect;
}

test "default ramp ring seeds native phase step from base subgame rate" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial11_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 11.TXT") orelse return error.EntryNotFound;
    var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial11_entry,
        .{
            .load_models = false,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
        },
    );
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.math_random_state = 0;
    runner.configureBaseSubgameRate(0.56);
    runner.presentation.movement_flag_selector = 4;
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 22.0;
    runner.refreshLiveRuntimeRingEffects(&preview);

    for (runner.activeRuntimeRingEffects()) |effect| {
        if (effect.row == 39 and effect.lane == 1 and effect.kind == 2) {
            const expected =
                (1.0 / ((2.0 - (runner.base_subgame_rate * 0.3)) * native_ticks_per_second)) *
                (@as(f32, @floatFromInt(runner.presentation.movement_flag_selector)) * 0.125) *
                native_track_center_x *
                std.math.tau;
            try std.testing.expectApproxEqAbs(expected, @abs(effect.active_phase_step), 0.0001);
            const x_before = effect.world_position.x;
            runner.updateRuntimeRingEffects(&preview);
            const updated = runner.activeRuntimeRingEffects()[0];
            try std.testing.expect(updated.world_position.x != x_before);
            return;
        }
    }

    return error.ExpectedRuntimeRingEffect;
}

test "runtime ring effect collision arms the native collect follow state" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 51.0;
    runner.refreshLiveRuntimeRingEffects(&fixture.preview);
    runner.processRuntimeRingEffectCollisions(&fixture.preview);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeRingEffects().len);
    try std.testing.expectEqual(RuntimeRingEffectState.collect_setup, runner.activeRuntimeRingEffects()[0].state);

    const pre_follow_position = runner.activeRuntimeRingEffects()[0].presentation_position;
    runner.updateRuntimeRingEffects(&fixture.preview);
    try std.testing.expectEqual(RuntimeRingEffectState.collect_follow, runner.activeRuntimeRingEffects()[0].state);

    runner.updateRuntimeRingEffects(&fixture.preview);
    const post_follow = runner.activeRuntimeRingEffects()[0];
    try std.testing.expect(post_follow.presentation_scale < 1.0);
    try std.testing.expect(post_follow.presentation_position.z > pre_follow_position.z);
}

test "runtime ring effect post-hit progress step follows native track center" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.speed_rows_per_second = 48.0;
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 51.0;
    runner.refreshLiveRuntimeRingEffects(&fixture.preview);
    runner.processRuntimeRingEffectCollisions(&fixture.preview);

    runner.updateRuntimeRingEffects(&fixture.preview);
    try std.testing.expectApproxEqAbs(
        Runner.runtimeRingEffectProgressStep(),
        runner.activeRuntimeRingEffects()[0].effect_progress_step,
        0.0001,
    );

    runner.runtime.rings.slots[0].state = .miss_setup;
    runner.runtime.rings.slots[0].effect_progress_step = 0.0;
    runner.updateRuntimeRingEffects(&fixture.preview);
    try std.testing.expectApproxEqAbs(
        Runner.runtimeRingEffectProgressStep(),
        runner.activeRuntimeRingEffects()[0].effect_progress_step,
        0.0001,
    );
}

test "runtime ring effect collect follow cleans itself up after native progress window" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.lane_index = 1;
    runner.lane_center = 1.5;
    runner.row_position = 51.0;
    runner.refreshLiveRuntimeRingEffects(&fixture.preview);
    runner.processRuntimeRingEffectCollisions(&fixture.preview);

    var guard: usize = 0;
    while (runner.activeRuntimeRingEffects().len != 0 and guard < 64) : (guard += 1) {
        runner.updateRuntimeRingEffects(&fixture.preview);
    }

    try std.testing.expectEqual(@as(usize, 0), runner.activeRuntimeRingEffects().len);
}

test "runtime ring effect bank stays native two-slot pool" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.addRuntimeRingEffect(&fixture.preview, 8, 8, 0, 1);
    runner.addRuntimeRingEffect(&fixture.preview, 9, 9, 1, 2);
    try std.testing.expectEqual(@as(usize, 2), runner.activeRuntimeRingEffects().len);

    runner.runtime.rings.slots[0].state = .collect_follow;
    runner.addRuntimeRingEffect(&fixture.preview, 10, 10, 2, 3);

    const active_effects = runner.activeRuntimeRingEffects();
    try std.testing.expectEqual(@as(usize, 2), active_effects.len);
    try std.testing.expectEqual(@as(usize, 8), active_effects[0].row);
    try std.testing.expectEqual(@as(usize, 9), active_effects[1].row);
}

test "projectile fire defeats slug after powerup" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.presentation.weapon_level = 1;
    const lane_center = @as(f32, @floatFromInt(slug.lane)) + 0.5;
    var projectile: Projectile = .{
        .active = true,
        .world_x = fixture.preview.worldPositionForLane(
            lane_center,
            @as(f32, @floatFromInt(slug.row)),
            0.0,
        ).x,
        .world_y = 0.5,
        .world_z = @as(f32, @floatFromInt(slug.row)) + 0.25,
        .dir_x = 0.0,
        .dir_y = 0.0,
        .dir_z = 1.0,
        .speed_rows_per_second = projectile_speed_rows_per_second,
    };

    try std.testing.expect(runner.resolveProjectileHit(&fixture.preview, &projectile));
    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
    try std.testing.expectEqual(slug_projectile_kill_score, runner.score.garbage_collision);
}

test "movement flags spawn the recovered projectile channel layouts" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);

    runner.presentation.movement_flags = 1;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[0].kind);

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 2;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 2), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[1].kind);

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 4;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 3), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[1].kind);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.combat.projectiles.slots[2].kind);
    try std.testing.expect(@abs(runner.combat.projectiles.slots[0].dir_x - runner.combat.projectiles.slots[1].dir_x) > 0.05);

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 8;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectApproxEqAbs(
        projectile_speed_rows_per_second * 2.0,
        runner.combat.projectiles.slots[0].speed_rows_per_second,
        0.0001,
    );

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 16;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 2), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.combat.projectiles.slots[1].kind);

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 144;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 2), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.combat.projectiles.slots[1].kind);

    runner.combat.projectiles.count = 0;
    for (&runner.combat.projectiles.slots) |*projectile| projectile.active = false;
    runner.presentation.movement_flags = 32;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectEqual(Projectile.Kind.rocket, runner.combat.projectiles.slots[0].kind);
    try std.testing.expectApproxEqAbs(
        projectile_speed_rows_per_second * 0.48,
        runner.combat.projectiles.slots[0].speed_rows_per_second,
        0.0001,
    );
}

test "movement fire cadence follows the native selector-owned cooldown lane" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);

    runner.handleFireInput(&fixture.preview, .fresh);
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectEqual(@as(u8, 2), runner.presentation.shot_cooldown_ticks);
    try std.testing.expectApproxEqAbs(@as(f32, 0.37407407), runner.presentation.movement_fire_cooldown, 0.0001);

    while (runner.presentation.movement_fire_cooldown > 0.0) {
        runner.stepMovementFireCooldown();
    }
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.presentation.movement_fire_cooldown, 0.0001);

    runner.handleFireInput(&fixture.preview, .repeat);
    try std.testing.expectEqual(@as(usize, 2), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.074074075), runner.presentation.movement_fire_cooldown, 0.0001);
}

test "live fire input keeps native press and held lanes separate" {
    var runner = Runner{};

    try std.testing.expectEqual(MovementFireInputState.none, runner.movementFireInputState(.{}, .{}));
    try std.testing.expectEqual(
        MovementFireInputState.fresh,
        runner.movementFireInputState(.{ .fire_pressed = true, .fire_down = true }, .{}),
    );
    try std.testing.expectEqual(
        MovementFireInputState.repeat,
        runner.movementFireInputState(.{ .fire_down = true }, .{}),
    );
}

test "movement fire is suppressed while attachment exit is pending" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);
    runner.attachment.exit.pending = true;

    runner.handleFireInput(&fixture.preview, .fresh);
    try std.testing.expectEqual(@as(usize, 0), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.presentation.movement_fire_cooldown, 0.0001);
}

test "movement fire respects the native runtime fire feature flag" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    fixture.preview.runtime_build_flags &= ~track.runtime_build_flag_movement_fire;

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);

    runner.handleFireInput(&fixture.preview, .fresh);
    try std.testing.expectEqual(@as(usize, 0), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.presentation.movement_fire_cooldown, 0.0001);
}

test "replay fire bits drive the native movement fire gate" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);
    runner.tick_count = 10;

    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x01,
        },
        1.0 / 60.0,
    );
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.37407407), runner.presentation.movement_fire_cooldown, 0.0001);

    while (runner.presentation.movement_fire_cooldown > 0.0) {
        runner.stepMovementFireCooldown();
    }

    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x02,
        },
        1.0 / 60.0,
    );
    try std.testing.expectEqual(@as(usize, 2), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.074074075), runner.presentation.movement_fire_cooldown, 0.0001);
}

test "movement fire stays suppressed for the first ten gameplay ticks" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);

    var tick: usize = 0;
    while (tick < 10) : (tick += 1) {
        runner.step(
            &fixture.preview,
            .{
                .fire_pressed = tick == 0,
                .fire_down = true,
            },
            1.0 / 60.0,
        );
        try std.testing.expectEqual(@as(usize, 0), runner.combat.projectiles.count);
        try std.testing.expectApproxEqAbs(runner.presentation.movement_fire_cooldown_step, runner.presentation.movement_fire_cooldown, 0.0001);
    }

    var held_ticks: usize = 0;
    while (runner.combat.projectiles.count == 0 and held_ticks < 32) : (held_ticks += 1) {
        runner.step(
            &fixture.preview,
            .{
                .fire_down = true,
            },
            1.0 / 60.0,
        );
    }
    try std.testing.expect(held_ticks > 0);
    try std.testing.expectEqual(@as(usize, 1), runner.combat.projectiles.count);
    try std.testing.expectApproxEqAbs(@as(f32, 0.074074075), runner.presentation.movement_fire_cooldown, 0.0001);
}

test "projectiles stop on salt without consuming the hazard" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 13.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    runner.spawnSaltFromAuthoredCell(&fixture.preview, salt.row, salt.lane);

    const lane_center = @as(f32, @floatFromInt(salt.lane)) + 0.5;
    var projectile: Projectile = .{
        .active = true,
        .world_x = fixture.preview.worldPositionForLane(
            lane_center,
            @as(f32, @floatFromInt(salt.row)),
            0.0,
        ).x,
        .world_y = 0.5,
        .world_z = @as(f32, @floatFromInt(salt.row)) + 0.25,
        .dir_x = 0.0,
        .dir_y = 0.0,
        .dir_z = 1.0,
        .speed_rows_per_second = projectile_speed_rows_per_second,
    };

    try std.testing.expect(runner.resolveProjectileHit(&fixture.preview, &projectile));
    try std.testing.expect(runner.runtime.salts.contains(salt.row, salt.lane));
}

test "explode rings defeat nearby slugs and clear nearby garbage only" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 11.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    runner.current_global_row = slug.row;
    runner.resolved_lane_index = slug.lane;
    runner.addRuntimeHazard(&fixture.preview, slug.row, @min(slug.lane + 1, fixture.preview.max_width - 1), .garbage);
    runner.spawnSaltFromAuthoredCell(&fixture.preview, slug.row, slug.lane);

    runner.triggerExplodeRing(&fixture.preview);

    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
    try std.testing.expect(!runner.hasRuntimeHazard(slug.row, @min(slug.lane + 1, fixture.preview.max_width - 1), .garbage));
    try std.testing.expect(runner.runtime.salts.contains(slug.row, slug.lane));
}

test "explode rings still reach right-edge authored lanes" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TIGHT ROPES 2.TXT");
    defer fixture.deinit();

    var right_edge_slug: ?RowTarget = null;
    for (0..fixture.preview.total_rows) |global_row| {
        const row_location = fixture.preview.locateRow(global_row) orelse continue;
        var lane_index = row_location.row.cells.len;
        while (lane_index > 0) {
            lane_index -= 1;
            if (fixture.preview.gameplayCellSampleAt(global_row, lane_index)) |sample| {
                if (sample.kind == .slug and lane_index == fixture.preview.max_width - 2) {
                    right_edge_slug = .{ .row = global_row, .lane = lane_index };
                    break;
                }
            }
        }
        if (right_edge_slug != null) break;
    }
    const slug = right_edge_slug orelse return error.TestUnexpectedResult;

    try std.testing.expectEqual(@as(usize, 8), slug.lane);

    var runner = Runner.init(&fixture.preview);
    runner.current_global_row = slug.row;
    runner.resolved_lane_index = slug.lane;
    runner.triggerExplodeRing(&fixture.preview);

    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
}

test "turret contact enters the shared fall state with the hazard cutscene id" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const turret = findFirstRawCell(&fixture.preview, '=').?;
    primeRunnerBeforeRow(&runner, &fixture.preview, turret);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.turret_hits);
    try std.testing.expectEqualStrings("turret_hit", runner.recentEventLabel());
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);
}

test "turret rows spawn enemy laser projectiles" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const turret = findFirstRawCell(&fixture.preview, '=').?;
    primeRunnerBeforeRow(&runner, &fixture.preview, turret);
    runner.updateTurretFire(&fixture.preview, turret_fire_interval_seconds);

    try std.testing.expect(runner.combat.projectiles.count > 0);
    try std.testing.expectEqual(Projectile.Kind.enemy_laser, runner.combat.projectiles.slots[0].kind);
    try std.testing.expect(runner.combat.turrets.count > 0);
    try std.testing.expect(runner.turretFlashTicksAt(turret.row, turret.lane) > 0);
}

test "multiple visible turrets keep independent controller state" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_position = 20.0;
    runner.refreshSample(&fixture.preview);
    runner.previous_row_position = runner.row_position;
    runner.previous_lane_center = runner.lane_center;

    runner.updateTurretFire(&fixture.preview, 0.5);
    try std.testing.expect(runner.combat.turrets.count >= 2);
    for (0..runner.combat.turrets.count) |index| {
        try std.testing.expectEqual(@as(u8, 0), runner.combat.turrets.slots[index].flash_ticks);
    }

    runner.updateTurretFire(&fixture.preview, 0.5);
    var flashing_count: usize = 0;
    for (0..runner.combat.turrets.count) |index| {
        if (runner.combat.turrets.slots[index].flash_ticks > 0) flashing_count += 1;
    }
    try std.testing.expect(flashing_count >= 2);
}

test "enemy laser projectile hits player and enters the shared fall state" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const player_position = runner.worldPosition(&fixture.preview, 0.4);
    var projectile: Projectile = .{
        .active = true,
        .kind = .enemy_laser,
        .world_x = player_position.x,
        .world_y = player_position.y,
        .world_z = player_position.z,
        .dir_x = 0.0,
        .dir_y = 0.0,
        .dir_z = -1.0,
        .speed_rows_per_second = projectileSpeedForKind(.enemy_laser),
    };

    try std.testing.expect(runner.resolveProjectileHit(&fixture.preview, &projectile));
    try std.testing.expectEqual(@as(u32, 1), runner.counters.turret_hits);
    try std.testing.expectEqualStrings("turret_hit", runner.recentEventLabel());
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);
}

test "runtime hazards preserve recovered presentation scalars" {
    var runner = Runner{};
    var preview = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer preview.deinit();

    runner.addRuntimeHazard(&preview.preview, 32, 4, .garbage);
    runner.spawnSaltFromAuthoredCell(&preview.preview, 48, 1);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeHazards().len);
    const garbage = runner.activeRuntimeHazards()[0];
    try std.testing.expect(garbage.presentation_scale >= 0.6);
    try std.testing.expect(garbage.presentation_scale <= 0.84);
    try std.testing.expect(garbage.world_position.y >= garbage.presentation_scale - 0.1);

    // Salt spawns into its dedicated `SaltHazardPool` and carries the native
    // `runtimeCellWorldPosition(..., 0.18)` Y anchor directly on the slot.
    try std.testing.expect(runner.runtime.salts.contains(48, 1));
    var salt_slot: ?gameplay_runtime_entities.SaltSlot = null;
    for (runner.runtime.salts.slots) |slot| {
        if (slot.state != .inactive and slot.row == 48 and slot.lane == 1) {
            salt_slot = slot;
            break;
        }
    }
    try std.testing.expect(salt_slot != null);
    try std.testing.expectApproxEqAbs(@as(f32, 0.18), salt_slot.?.world_position.y, 0.5);
}

test "tutorial asteroids spawn from the native runtime row scan window" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    try std.testing.expect(garbage.row >= native_runtime_row_scan_ahead_rows);

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = garbage.row - (native_runtime_row_scan_ahead_rows - 1);
    runner.track_row_progress = 0.0;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshLiveRuntimeHazards(&fixture.preview);

    var found = false;
    for (runner.activeRuntimeHazards()) |hazard| {
        if (hazard.kind == .garbage and hazard.row == garbage.row and hazard.lane == garbage.lane) {
            found = true;
            break;
        }
    }
    try std.testing.expect(found);
}

test "runtime pickups and salt respect the native first-block spawn gate" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    const active_row = fixture.preview.runtime_active_row_start;
    try std.testing.expect(active_row > 0);
    const blocked_row = active_row - 1;
    const lane = @min(@as(usize, 4), fixture.preview.max_width - 1);

    var pickup_runner = Runner.init(&fixture.preview);
    fixture.preview.runtime_tiles[(blocked_row * fixture.preview.max_width) + lane] = 0x17;
    pickup_runner.scanRuntimePickupRow(&fixture.preview, blocked_row);
    try std.testing.expectEqual(@as(usize, 0), pickup_runner.activeRuntimePickups().len);

    fixture.preview.runtime_tiles[(active_row * fixture.preview.max_width) + lane] = 0x17;
    pickup_runner.scanRuntimePickupRow(&fixture.preview, active_row);
    try std.testing.expectEqual(@as(usize, 1), pickup_runner.activeRuntimePickups().len);

    var salt_runner = Runner.init(&fixture.preview);
    fixture.preview.runtime_tiles[(blocked_row * fixture.preview.max_width) + lane] = 0x22;
    salt_runner.scanRuntimeHazardRow(&fixture.preview, blocked_row);
    try std.testing.expect(!salt_runner.runtime.salts.contains(blocked_row, lane));

    fixture.preview.runtime_tiles[(active_row * fixture.preview.max_width) + lane] = 0x22;
    salt_runner.scanRuntimeHazardRow(&fixture.preview, active_row);
    try std.testing.expect(salt_runner.runtime.salts.contains(active_row, lane));
}

test "steady gameplay animation id 2 resolves to shipped turbo move" {
    try std.testing.expectEqual(@as(u8, 2), @intFromEnum(AnimClipId.move));
    try std.testing.expectEqualStrings("TURBO-MOVE", AnimClipId.move.familyKey().?);

    const dispatch_state = AnimDispatchState{};
    try std.testing.expectEqual(AnimClipId.move, dispatch_state.active);
}

test "Wall2 emitter fires SubLazer with native player-relative z gate" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/CAGE.TXT");
    defer fixture.deinit();

    const wall = findFirstRuntimeTileAtOrAfter(&fixture.preview, native_wall2_tile_id, 20) orelse return error.TestUnexpectedResult;
    var runner = Runner.init(&fixture.preview);
    runner.row_position = if (wall.row > 20) @floatFromInt(wall.row - 20) else 0.0;
    runner.math_random_state = 0;

    runner.maybeFireWall2SubLazersInWindow(&fixture.preview);

    try std.testing.expectEqual(@as(usize, 1), runner.runtime.sub_lazers.countActive());
    const slot = runner.runtime.sub_lazers.slots[0];
    try std.testing.expectEqual(gameplay_runtime_entities.SubLazerSlotState.active, slot.state);
    try std.testing.expect(slot.velocity.z < 0.0);
    const speed = @sqrt((slot.velocity.x * slot.velocity.x) + (slot.velocity.y * slot.velocity.y) + (slot.velocity.z * slot.velocity.z));
    try std.testing.expectApproxEqAbs(native_sub_lazer_speed, speed, 0.0001);
    try std.testing.expect(slot.world_position.y > 7.0);
}

test "invincible slug contact defeats slug without score award" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.presentation.invincible_ticks = 30;

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    // PORT(verified): native `handle_subgoldy_collisions` @ 0x44523a goes through
    // `kill_slug_hazard` without `add_subgoldy_score`; the score only applies when the
    // slug is killed by a projectile or explosive-ring shockwave.
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
}

test "snail skin transition follows native change + tick timing" {
    var skin = SnailSkinTransition{};
    try std.testing.expectEqual(SnailSkinSlot.default, skin.selected_slot);
    try std.testing.expect(!skin.active);

    // Instant swap: duration 0 sets progress_step=0, active stays true (progress never
    // crosses 1.0, so the slot persists until a new change() call).
    skin.change(.invincible, 0.0);
    try std.testing.expectEqual(SnailSkinSlot.invincible, skin.selected_slot);
    try std.testing.expect(skin.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), skin.progress_step, 0.0001);

    skin.tick();
    try std.testing.expect(skin.active);
    try std.testing.expectEqual(SnailSkinSlot.invincible, skin.selected_slot);

    // Timed swap: duration 0.2s gives progress_step = 1/12 per tick; 13 ticks to cross 1.0.
    skin.change(.damage, 0.2);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0 / (0.2 * 60.0)), skin.progress_step, 0.0001);
    var i: usize = 0;
    while (i < 20 and skin.active) : (i += 1) skin.tick();
    try std.testing.expect(!skin.active);
    try std.testing.expectEqual(SnailSkinSlot.default, skin.selected_slot);
}

test "warning actor follows the native solid and fade cadence" {
    var runner = Runner{};
    runner.startDamageWarningActor();

    try std.testing.expectEqual(DamageWarningActorState.fade_cycle, runner.damage.warning_actor.state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage.warning_actor.progress, 0.0001);

    const first_generation = runner.damage.warning_actor.sample_generation;
    runner.updateDamageWarningActor();
    try std.testing.expectEqual(DamageWarningActorState.solid, runner.damage.warning_actor.state);
    try std.testing.expectEqual(first_generation +% 1, runner.damage.warning_actor.sample_generation);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.warning_actor.progress, 0.0001);

    runner.updateDamageWarningActor();
    try std.testing.expectApproxEqAbs(damage_warning_actor_solid_alpha, runner.damage.warning_actor.alpha, 0.0001);
}

test "damage gauge warning overlay follows display fill and pulse lanes" {
    var runner = Runner{};
    runner.damage.runtime.display_fill = 0.5;
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damageGaugeWarningOverlayAlpha(), 0.0001);

    runner.damage.runtime.display_fill = 0.95;
    runner.damage.runtime.pulse_progress = 0.0;
    try std.testing.expect(runner.damageGaugeWarningOverlayAlpha() > 0.0);

    runner.damage.warning_state = .draining;
    runner.damage.runtime.display_fill = 0.05;
    try std.testing.expect(runner.damageGaugeWarningOverlayAlpha() > 0.0);
}

test "full damage enters warning fill and auto-drain" {
    var runner = Runner{};
    runner.damage.gauge = 1.0;

    runner.updateDamageWarning();
    try std.testing.expectEqual(DamageWarningState.filling, runner.damage.warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage.runtime.warning_transition_progress, 0.0001);
    try std.testing.expectEqual(DamageWarningActorState.solid, runner.damage.warning_actor.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.damageGaugeDisplayFill(), 0.0001);

    for (0..6) |_| {
        runner.updateDamageWarning();
    }
    try std.testing.expectEqual(DamageWarningState.draining, runner.damage.warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage.runtime.warning_transition_progress, 0.0001);

    const gauge_before_drain = runner.damage.gauge;
    runner.updateDamageWarning();
    try std.testing.expect(runner.damage.gauge < gauge_before_drain);
}

test "runner accumulates ring and parcel score totals from shipped levels" {
    var arcade_fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer arcade_fixture.deinit();

    var runner = Runner{};

    runner.recordRing(&arcade_fixture.preview, .normal);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.ring_collect);

    runner = Runner.init(&arcade_fixture.preview);
    const parcel = findFirstAnnotationTag(&arcade_fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &arcade_fixture.preview, parcel);
    try std.testing.expect(stepUntilParcelPickup(&runner, &arcade_fixture.preview, 32) < 32);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.parcel_pickup);
    try std.testing.expectEqual(@as(u32, 0), runner.score.parcel_register);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);

    runner = Runner.init(&arcade_fixture.preview);
    runner.configureCompletionBonus(1, true);
    primeRunnerBeforeRow(&runner, &arcade_fixture.preview, parcel);
    try std.testing.expect(stepUntilParcelPickup(&runner, &arcade_fixture.preview, 32) < 32);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 0), runner.score.completion_bonus);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    runner.flushPendingParcelDeliveries();
    try std.testing.expectEqual(@as(u32, 50_110), runner.score.total);
    try std.testing.expectEqual(parcel_delivery_register_score, runner.score.parcel_register);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.completion_bonus);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
}

test "runner consumes parcel rows only once" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);
    try std.testing.expect(stepUntilParcelPickup(&runner, &fixture.preview, 32) < 32);
    try std.testing.expect(runner.isParcelCollected(parcel.row));
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 0), runner.registeredParcelCount());
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 0), runner.registeredParcelCount());
}

test "runner spawns live parcel slots ahead of the current row" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);

    runner.refreshLiveTrackParcels(&fixture.preview);
    const live_parcel = runner.liveTrackParcelAt(parcel.row).?;
    const initial_phase = live_parcel.bob_phase;

    runner.updateTrackParcels(&fixture.preview);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row).?.bob_phase != initial_phase);
}

test "runner promotes live parcel slots into flight on pickup" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);

    runner.refreshLiveTrackParcels(&fixture.preview);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);

    try std.testing.expect(stepUntilParcelPickup(&runner, &fixture.preview, 32) < 32);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);
    try std.testing.expectEqual(@as(u32, 4), runner.liveTrackParcelAt(parcel.row).?.state);
}

test "row event display updates the parcel widget world from the cameraman matrix" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshCameraState(&fixture.preview);

    const transform = normalizeCameraTransform(cameraTransformFromMatrix(runner.cameraman.live_matrix));
    const expected = offsetPosition(
        transform.position,
        transform.right,
        transform.up,
        transform.forward,
        row_event_widget_local_x,
        row_event_widget_local_y,
        row_event_widget_local_z,
    );

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectApproxEqAbs(expected.x, runner.row_event_display.widget_world_x, 0.0001);
    try std.testing.expectApproxEqAbs(expected.y, runner.row_event_display.widget_world_y, 0.0001);
    try std.testing.expectApproxEqAbs(expected.z, runner.row_event_display.widget_world_z, 0.0001);
}

test "parcel home flight advances on the pickup frame" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };
    runner.parcel.slots[0] = .{
        .state = 4,
        .world_position = .{ .x = 5.0, .y = 2.0, .z = 9.0 },
    };

    runner.updateTrackParcels(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 5), runner.parcel.slots[0].state);
    try std.testing.expectApproxEqAbs(track_parcel_home_progress_step, runner.parcel.slots[0].progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.parcel.slots[0].presentationScale(), 0.0001);
}

test "parcel delivery advances on the staging frame" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.widget_world_x = 9.0;
    runner.row_event_display.widget_world_y = 3.0;
    runner.row_event_display.widget_world_z = 14.0;
    runner.parcel.slots[0] = .{
        .state = 6,
    };

    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };
    runner.updateTrackParcels(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 7), runner.parcel.slots[0].state);
    try std.testing.expectApproxEqAbs(track_parcel_delivery_progress_step, runner.parcel.slots[0].progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.parcel.slots[0].world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.0), runner.parcel.slots[0].world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), runner.parcel.slots[0].world_position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), runner.parcel.slots[0].presentationScale(), 0.0001);
}

test "parcel home flight retires the home-leg slot and arms row event staging" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.counters.parcels = 1;
    runner.row_event_display.parcel_target_count = 2;
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };

    var parcel = TrackParcelRuntime{
        .state = 5,
        .flight_anchor = runner.parcel.home_anchor.world_position,
        .progress = 1.0,
        .progress_step = 0.0,
    };

    runner.stepTrackParcelHome(&fixture.preview, &parcel);

    try std.testing.expectEqual(@as(u32, 0), parcel.state);
    try std.testing.expectEqual(RowEventDisplayState.staging, runner.row_event_display.state);
}

test "row event staging spawns a fresh delivery parcel slot" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.counters.parcels = 1;
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };
    runner.row_event_display.state = .staging;
    runner.row_event_display.progress = 1.0;
    runner.row_event_display.progress_step = 0.0;

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectEqual(@as(u32, 1), runner.row_event_display.staged_parcel_count);
    try std.testing.expectEqual(RowEventDisplayState.hold, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u32, 6), runner.parcel.slots[0].state);
    try std.testing.expectEqual(std.math.maxInt(usize), runner.parcel.slots[0].row);
    try std.testing.expectApproxEqAbs(@as(f32, 4.0), runner.parcel.slots[0].world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.parcel.slots[0].world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), runner.parcel.slots[0].world_position.z, 0.0001);
}

test "parcel home flight lifts presentation along the live basis up" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/LOOPBOW.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "LOOPBOW";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = @as(f32, @floatFromInt(built.template.sample_count)) * 0.25,
    };
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };
    var parcel = TrackParcelRuntime{
        .state = 5,
        .flight_anchor = runner.parcel.home_anchor.world_position,
        .progress = 0.25,
        .progress_step = 0.0,
        .target_distance = 4.0,
        .travel_dir = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    };

    runner.stepTrackParcelHome(&fixture.preview, &parcel);

    const arc = std.math.sin(@as(f32, 0.25) * std.math.pi) * track_parcel_home_arc_height;
    const basis_up = normalizeVector3(runner.worldUp(&fixture.preview));
    try std.testing.expectApproxEqAbs(@as(f32, 7.0), parcel.world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), parcel.world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), parcel.world_position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 7.0) + (basis_up.x * arc), parcel.presentationPosition().x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0) + (basis_up.y * arc), parcel.presentationPosition().y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0) + (basis_up.z * arc), parcel.presentationPosition().z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.85), parcel.presentationScale(), 0.0001);
}

test "parcel delivery keeps linear world position and curved presentation separate" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.widget_world_x = 9.0;
    runner.row_event_display.widget_world_y = 3.0;
    runner.row_event_display.widget_world_z = 14.0;
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };

    var parcel = TrackParcelRuntime{
        .state = 7,
        .flight_anchor = runner.parcel.home_anchor.world_position,
        .progress = 0.5,
        .progress_step = 0.0,
        .delivery_offset = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };

    const expected = lerpVector3(runner.parcel.home_anchor.world_position, .{ .x = 9.0, .y = 3.0, .z = 14.0 }, 0.5);

    runner.stepTrackParcelDelivery(&fixture.preview, &parcel);

    try std.testing.expectApproxEqAbs(expected.x, parcel.world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(expected.y, parcel.world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(expected.z, parcel.world_position.z, 0.0001);
    try std.testing.expectApproxEqAbs(expected.x + 1.0, parcel.presentationPosition().x, 0.0001);
    try std.testing.expectApproxEqAbs(expected.y + 2.0, parcel.presentationPosition().y, 0.0001);
    try std.testing.expectApproxEqAbs(expected.z + 3.0, parcel.presentationPosition().z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.7), parcel.presentationScale(), 0.0001);
}

test "parcel delivery reuses the cached home anchor after the runner moves" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.parcel.home_anchor = .{
        .active = true,
        .world_position = .{ .x = -2.0, .y = 1.5, .z = 8.0 },
    };
    runner.row_position = 20.0;
    runner.lane_center = 6.5;
    runner.row_event_display.widget_world_x = 9.0;
    runner.row_event_display.widget_world_y = 3.0;
    runner.row_event_display.widget_world_z = 14.0;

    var parcel = TrackParcelRuntime{
        .state = 7,
        .flight_anchor = runner.parcel.home_anchor.world_position,
        .progress = 0.0,
        .progress_step = 0.0,
    };

    runner.stepTrackParcelDelivery(&fixture.preview, &parcel);

    try std.testing.expectApproxEqAbs(@as(f32, -2.0), parcel.world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.5), parcel.world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 8.0), parcel.world_position.z, 0.0001);
}

test "parcel delivery seeds the recovered random arc coefficients" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.math_random_state = 0;

    var parcel = TrackParcelRuntime{};
    runner.beginTrackParcelDelivery(&parcel);

    try std.testing.expectEqual(@as(u32, 7), parcel.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), parcel.progress, 0.0001);
    try std.testing.expectApproxEqAbs(track_parcel_delivery_progress_step, parcel.progress_step, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.99768066), parcel.delivery_offset.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.20669556), parcel.delivery_offset.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), parcel.delivery_offset.z, 0.0001);
}

test "runner registers parcel delivery after the parcel flight finishes" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);

    try std.testing.expect(stepUntilParcelPickup(&runner, &fixture.preview, 32) < 32);
    const register_steps = stepUntilParcelRegistered(&runner, &fixture.preview, 256);
    try std.testing.expect(register_steps < 256);
    try std.testing.expectEqual(@as(u32, 1), runner.registeredParcelCount());
    try std.testing.expectEqual(parcel_delivery_register_score, runner.score.parcel_register);
    try std.testing.expectEqual(RowEventDisplayState.hold, runner.row_event_display.state);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) == null);
}

test "final parcel delivery enters the delayed row event controller path" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureCompletionBonus(1, false);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);

    try std.testing.expect(stepUntilParcelPickup(&runner, &fixture.preview, 32) < 32);
    try std.testing.expect(stepUntilParcelRegistered(&runner, &fixture.preview, 256) < 256);
    try std.testing.expectEqual(@as(u32, 1), runner.registeredParcelCount());
    try std.testing.expectEqual(RowEventDisplayState.final_delivery_delay, runner.row_event_display.state);
}

test "row event staging promotes delivered parcels into the hold state" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.state = .staging;
    runner.counters.parcels = 2;
    runner.row_event_display.staged_parcel_count = 1;
    runner.row_event_display.delivered_parcel_count = 2;
    runner.row_event_display.progress_step = 1.0;

    runner.updateRowEventDisplay(&fixture.preview, true);

    try std.testing.expectEqual(@as(u32, 2), runner.row_event_display.staged_parcel_count);
    try std.testing.expectEqual(RowEventDisplayState.hold, runner.row_event_display.state);
}

test "row event widget helpers expose the recovered counter and bonus lanes" {
    var runner = Runner{};
    runner.session_mode = .postal;
    runner.row_event_display.parcel_target_count = 7;
    runner.row_event_display.delivered_parcel_count = 3;
    runner.row_event_display.widget_world_x = 9.0;
    runner.row_event_display.widget_world_y = 2.5;
    runner.row_event_display.widget_world_z = 14.0;
    runner.row_event_display.bonus_enabled = true;
    runner.row_event_display.state = .bonus_prompt;
    runner.row_event_display.bonus_blink_progress = 0.25;
    runner.row_event_display.bonus_score = postal_completion_bonus_score;

    try std.testing.expect(runner.rowEventCounterVisible());
    try std.testing.expectEqual(@as(u32, 7), runner.rowEventParcelTargetCount());
    try std.testing.expectEqual(@as(u32, 3), runner.registeredParcelCount());
    try std.testing.expect(runner.rowEventBonusVisible());
    try std.testing.expect(runner.rowEventBonusBlinkAlpha() > 0.0);

    const widget_world = runner.rowEventWidgetWorldPosition();
    try std.testing.expectApproxEqAbs(@as(f32, 9.0), widget_world.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), widget_world.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 14.0), widget_world.z, 0.0001);
    try std.testing.expectEqual(@as(u32, postal_completion_bonus_score), runner.rowEventBonusScore());
}

test "final parcel delivery can complete the row event on the same tick" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.row_event_display.state = .final_delivery;
    runner.row_event_display.gate_18 = 1;
    runner.row_event_display.bonus_blink_step = 1.0;

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 0), runner.row_event_display.gate_18);
}

test "final parcel delivery arms the row event confirm gate on the same tick" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, false).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.row_event_display.state = .final_delivery;

    runner.updateRowEventDisplay(&fixture.preview, true);

    try std.testing.expectEqual(RowEventDisplayState.bonus_prompt, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 1), runner.row_event_display.gate_18);
}

test "final delivery delay promotes into the final delivery state" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.state = .final_delivery_delay;
    runner.row_event_display.progress_step = 1.0;

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectEqual(RowEventDisplayState.final_delivery, runner.row_event_display.state);
}

test "flush pending parcel deliveries resets row event transient state" {
    var runner = Runner{};
    runner.counters.parcels = 2;
    runner.row_event_display.parcel_target_count = 2;
    runner.row_event_display.delivered_parcel_count = 0;
    runner.row_event_display.staged_parcel_count = 1;
    runner.row_event_display.state = .hold;
    runner.row_event_display.progress = 0.5;
    runner.row_event_display.progress_step = 0.25;
    runner.row_event_display.gate_18 = 1;
    runner.row_event_display.display_token = 9;
    runner.parcel.home_anchor.active = true;
    runner.parcel.slots[0].state = 5;

    runner.flushPendingParcelDeliveries();

    try std.testing.expectEqual(RowEventDisplayState.inactive, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 0), runner.row_event_display.gate_18);
    try std.testing.expectEqual(@as(u32, 0), runner.row_event_display.display_token);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.row_event_display.progress, 0.0001);
    try std.testing.expect(!runner.parcel.home_anchor.active);
}

test "runner applies the completion bonus once" {
    var runner = Runner{};
    runner.row_event_display.delivered_parcel_count = 3;

    runner.applyCompletionBonus(3);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.total);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.completion_bonus);

    runner.applyCompletionBonus(3);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.total);
}

test "runner seeds visible life stock at 3 and caps score-side awards at 9" {
    var runner = Runner{};

    runner.recordScore(&runner.score.ring_collect, 49_900);
    try std.testing.expectEqual(@as(u32, 49_900), runner.score.total);
    try std.testing.expectEqual(@as(u32, 3), runner.visible_life_stock);

    runner.recordScore(&runner.score.health_collect, 100);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.total);
    try std.testing.expectEqual(@as(u32, 4), runner.visible_life_stock);

    runner.recordScore(&runner.score.health_collect, 400_000);
    try std.testing.expectEqual(@as(u32, 450_000), runner.score.total);
    try std.testing.expectEqual(@as(u32, 9), runner.visible_life_stock);
}

test "stopwatch advances minutes seconds and subsecond counters at 60fps" {
    var stopwatch = Stopwatch{};
    stopwatch.advance(90.0);

    try std.testing.expectApproxEqAbs(@as(f32, 1.5), stopwatch.total_seconds, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), stopwatch.minutes);
    try std.testing.expectEqual(@as(u32, 1), stopwatch.seconds);
    try std.testing.expectEqual(@as(u32, 50), stopwatch.centiseconds);
    try std.testing.expectEqual(@as(u32, 500), stopwatch.milliseconds);
    try std.testing.expectEqual(@as(u32, 1500), stopwatch.elapsedMillis());
}

test "times up message arms at the native replay cursor threshold" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.speed_rows_per_second = 0.0;
    fixture.preview.runtime_tiles[runner.current_global_row * fixture.preview.max_width + runner.resolved_lane_index] = 1;
    runner.replay_sample_index = times_up_trigger_sample_index - 1;

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expect(runner.timesUpVisible());
    try std.testing.expectEqual(TimesUpState.message, runner.times_up.state);
    try std.testing.expectApproxEqAbs(times_up_progress_step, runner.times_up.progress, 0.0001);
    try std.testing.expectEqual(times_up_trigger_sample_index, runner.replay_sample_index);
}

test "times up mirrors kill_subgoldy by forcing the live y lane before fall death" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.time_trial);
    runner.speed_rows_per_second = 0.0;
    fixture.preview.runtime_tiles[runner.current_global_row * fixture.preview.max_width + runner.resolved_lane_index] = 1;
    runner.replay_sample_index = times_up_trigger_sample_index - 1;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    var steps: usize = 0;
    while (runner.position_y > native_position_y_death_threshold and steps < 220) : (steps += 1) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expect(steps < 220);
    try std.testing.expect(!runner.timesUpVisible());
    try std.testing.expectEqual(TimesUpState.inactive, runner.times_up.state);
    try std.testing.expect(runner.attachment.exit.pending);
    try std.testing.expectApproxEqAbs(@as(f32, -8.0), runner.position_y, 0.0001);
    try std.testing.expectEqualStrings("active", runner.phaseLabel());

    steps = 0;
    while (runner.phase == .active and steps < 64) : (steps += 1) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }
    try std.testing.expect(steps < 64);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.fall, runner.deathCause().?);
}

test "postal death hands off respawn after the death controller finishes with runner-owned life consumption" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.recordScore(&runner.score.ring_collect, 200);
    runner.runtime_track_index = 24;
    runner.track_row_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);

    const steps = stepUntilHandoff(&runner, &fixture.preview, 256);
    try std.testing.expect(steps < 256);

    const handoff = runner.consumeHandoff();
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);
    try std.testing.expectEqual(DeathCause.hazard, handoff.respawn);
    try std.testing.expectEqual(@as(u32, 2), runner.visible_life_stock);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectApproxEqAbs(@as(f32, 25.0), runner.row_position, 0.0001);
}

test "hazard death keeps on-track height until the selector handoff" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.runtime_track_index = 24;
    runner.track_row_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);
    const starting_world_y = runner.phase.fall.world_y;

    const steps = stepUntilHandoff(&runner, &fixture.preview, 256);
    try std.testing.expect(steps < 256);
    try std.testing.expectApproxEqAbs(starting_world_y, runner.phase.fall.world_y, 0.0001);
    try std.testing.expect(runner.phase.fall.world_y > fall_world_y_threshold);
}

test "applyRespawn preserves score timer and remaining lives while resetting movement" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.recordScore(&runner.score.ring_collect, 200);
    runner.visible_life_stock = 2;
    runner.tick_count = 90;
    runner.stopwatch.advance(90.0);
    runner.runtime_track_index = 24;
    runner.track_row_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);

    runner.applyRespawn(&fixture.preview);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqual(@as(u32, 2), runner.visible_life_stock);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectEqual(@as(u64, 90), runner.tick_count);
    try std.testing.expectEqual(@as(u32, 1500), runner.stopwatch.elapsedMillis());
    try std.testing.expectApproxEqAbs(@as(f32, 4.0), runner.row_position, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.parcels);
}

test "applyRespawn preserves delivered parcel progress and consumed parcel rows" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureCompletionBonus(1, true);
    const parcel = findFirstAnnotationTag(&fixture.preview, .parcel).?;

    primeRunnerBeforeRow(&runner, &fixture.preview, parcel);
    try std.testing.expect(stepUntilParcelPickup(&runner, &fixture.preview, 32) < 32);
    try std.testing.expect(runner.isParcelCollected(parcel.row));
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 0), runner.registeredParcelCount());
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) != null);

    runner.applyRespawn(&fixture.preview);

    try std.testing.expect(runner.isParcelCollected(parcel.row));
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 1), runner.registeredParcelCount());
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.completion_bonus);
    try std.testing.expectEqual(@as(u32, 50_110), runner.score.total);
    try std.testing.expectEqual(RowEventDisplayState.inactive, runner.row_event_display.state);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) == null);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 50_110), runner.score.total);
}

test "challenge death hands off final loss" {
    var fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.challenge);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);

    const steps = stepUntilHandoff(&runner, &fixture.preview, 256);
    try std.testing.expect(steps < 256);

    const handoff = runner.consumeHandoff();
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene.id);
    try std.testing.expectEqual(DeathCause.hazard, handoff.final_loss);
}

test "local Z roll keeps the forward basis fixed" {
    const transform = CameraTransform{
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    };
    const rolled = rotateCameraTransformLocalZ(transform, std.math.pi / 4.0);

    try std.testing.expectApproxEqAbs(@as(f32, 0.0), rolled.forward.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), rolled.forward.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), rolled.forward.z, 0.0001);
    try std.testing.expect(rolled.right.y > 0.6);
}

test "runtime lane-roll tile families arm cameraman roll without input steering" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    const tile_index = runner.current_global_row * fixture.preview.max_width + runner.resolved_lane_index;
    fixture.preview.runtime_tiles[tile_index] = 2;
    runner.refreshCameraState(&fixture.preview);
    const baseline = cameraTransformFromMatrix(runner.cameramanMatrix());

    var step_count: usize = 0;
    while (step_count < 24) : (step_count += 1) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }
    const leaned = cameraTransformFromMatrix(runner.cameramanMatrix());

    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.attachment.lane_lean.amplitude, 0.0001);
    try std.testing.expect(runner.attachment.lane_lean.progress > 0.0);
    try std.testing.expect(@abs(leaned.right.y - baseline.right.y) > 0.005);
}

test "lane input alone no longer arms cameraman roll on neutral tiles" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    const tile_index = runner.current_global_row * fixture.preview.max_width + runner.resolved_lane_index;
    fixture.preview.runtime_tiles[tile_index] = 1;
    const neighbor_index = runner.current_global_row * fixture.preview.max_width + @min(runner.resolved_lane_index + 1, fixture.preview.max_width - 1);
    fixture.preview.runtime_tiles[neighbor_index] = 1;

    runner.step(&fixture.preview, .{ .lane_delta = 1 }, 1.0 / 60.0);

    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.lane_lean.amplitude, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.lane_lean.progress, 0.0001);
}

test "fall state keeps Z anchored and preserves carried follow roll" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.attachment.exit.post_follow_value_a = 0.25;
    runner.attachment.exit.post_follow_value_b = 0.5;
    const anchor_z = runner.attachment.exit.anchor_z;

    runner.updatePhaseController(&fixture.preview, 1.0 / 60.0);

    try std.testing.expectApproxEqAbs(anchor_z, runner.phase.fall.world_z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), runner.attachment.exit.post_follow_value_a, 0.0001);
}

test "floor fall waits for the native resurrect controller before respawn" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.phase.fall.world_y = fall_world_y_threshold - 0.25;
    runner.phase.fall.vertical_velocity = 0.0;

    var step_count: u16 = 0;
    while (step_count + 1 < fall_resurrect_delay_ticks) : (step_count += 1) {
        runner.updatePhaseController(&fixture.preview, 0.0);
        try std.testing.expectEqual(RunnerHandoff.none, runner.handoff.pending);
    }

    runner.updatePhaseController(&fixture.preview, 0.0);
    const handoff = runner.consumeHandoff();
    try std.testing.expectEqual(DeathCause.fall, handoff.respawn);
    try std.testing.expectEqual(fall_resurrect_delay_ticks, runner.phase.fall.resurrect_ticks);
}

test "active jetpack retires attachment exit before the late progress gates" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.attachment.exit.pending = true;
    runner.attachment.exit.progress = 0.5;
    runner.armJetpackGauge();

    runner.stepAttachmentExitState(&fixture.preview);

    try std.testing.expect(!runner.attachment.exit.pending);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), runner.attachment.exit.progress, 0.0001);
    try std.testing.expect(!runner.attachment.exit.gate_a);
}

test "fall-phase attachment exit progress no longer clears pending at one second" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.attachment.exit.progress = 0.99;
    runner.attachment.exit.progress_step = attachment_exit_progress_step_default;

    runner.stepAttachmentExitState(&fixture.preview);

    try std.testing.expect(runner.attachment.exit.pending);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.attachment.exit.progress, 0.0001);
}

test "runner completion enters the delayed handoff controller" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.track_row_progress = 0.95;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginCompletionCutscene();

    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene.id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
    try std.testing.expectEqual(@as(f32, 0.0), runner.handoff.completion_timer);
}

test "completion handoff arms at the final row threshold" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.track_row_progress = 0.01;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expect(runner.row_position > @as(f32, @floatFromInt(fixture.preview.total_rows - 1)));
    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene.id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
}

test "completion handoff uses the preview course-end threshold" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    fixture.preview.course_end_threshold = 12.5;

    var runner = Runner.init(&fixture.preview);
    runner.row_position = 12.49;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.track_row_progress = runner.row_position - @floor(runner.row_position);
    runner.refreshSample(&fixture.preview);
    runner.maybeBeginCompletionCutscene(&fixture.preview);
    try std.testing.expectEqualStrings("active", runner.phaseLabel());

    runner.row_position = 12.5;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.track_row_progress = runner.row_position - @floor(runner.row_position);
    runner.refreshSample(&fixture.preview);
    runner.maybeBeginCompletionCutscene(&fixture.preview);
    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
}

test "completion does not arm while attachment follow is still active at route end" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    fixture.preview.total_rows = built.row.global_row + built.template.sample_count + 1;

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment.path_name = "START";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = @as(f32, @floatFromInt(built.template.sample_count)) - 0.5,
    };
    runner.row_position = @as(f32, @floatFromInt(fixture.preview.total_rows - 1)) + 0.01;

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
}

test "route-end completion can start while parcel delivery registration is still pending" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.track_row_progress = 0.01;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.counters.parcels = 1;
    runner.row_event_display.delivered_parcel_count = 0;

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene.id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
}

test "row event bonus prompt promotes to complete when live runtime flag b40 is set" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    const stale = findFirstRuntimeFlagB40Cell(&fixture.preview, false).?;
    runner.current_global_row = stale.row;
    runner.resolved_lane_index = stale.lane;
    setRunnerLiveRowTarget(&runner, target);
    runner.row_event_display.state = .bonus_prompt;

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
}

test "row event bonus prompt arms the confirm gate from gameplay input" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, false).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.row_event_display.state = .bonus_prompt;

    runner.updateRowEventDisplay(&fixture.preview, true);

    try std.testing.expectEqual(RowEventDisplayState.bonus_prompt, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 1), runner.row_event_display.gate_18);
}

test "row event bonus prompt waits while runtime flag b40 is clear" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, false).?;
    const stale = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    runner.current_global_row = stale.row;
    runner.resolved_lane_index = stale.lane;
    setRunnerLiveRowTarget(&runner, target);
    runner.row_event_display.state = .bonus_prompt;

    runner.updateRowEventDisplay(&fixture.preview, false);

    try std.testing.expectEqual(RowEventDisplayState.bonus_prompt, runner.row_event_display.state);
}

test "tutorial completion screen init handoff fires before the late finalize handoff" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginCompletionCutscene();
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.handoff.completion_timer < completion_handoff_release_seconds);
    try std.testing.expectEqual(CutsceneCameraState.completion_blend, runner.cutscene.camera.state);
}

test "tutorial completion finalize releases after the recovered timer" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginCompletionCutscene();

    const init_steps = stepUntilHandoff(&runner, &fixture.preview, 32);
    try std.testing.expect(init_steps < 32);
    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());

    const finalize_steps = stepUntilHandoff(&runner, &fixture.preview, 360);

    try std.testing.expect(finalize_steps < 360);
    try std.testing.expect(runner.handoff.completion_timer >= completion_handoff_release_seconds);
    try std.testing.expectEqual(RunnerHandoff.completion_finalize, runner.consumeHandoff());
}

test "completion voice gate trips at the native 2.0 second delay" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginCompletionCutscene();

    while (runner.handoff.completion_timer < completion_handoff_voice_delay_seconds and !runner.handoff.completion_voice_gate) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
        _ = runner.consumeHandoff();
    }

    try std.testing.expect(runner.handoff.completion_voice_gate);
    try std.testing.expect(runner.handoff.completion_timer >= completion_handoff_voice_delay_seconds);
}

test "intro cutscene uses hotspot 18 hold and look-at-to-cameraman blend" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.setCutscene(cutscene_intro_id);
    runner.refreshCameraState(&fixture.preview);

    try std.testing.expectEqual(CutsceneCameraState.intro_hold, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(
        runner.introCutsceneHoldMatrix(&fixture.preview),
        runner.cutsceneCameraMatrix(),
        0.0001,
    );

    runner.cutscene.camera.state = .intro_blend;
    runner.cutscene.camera.ticks = intro_cutscene_blend_ticks / 2;
    runner.refreshCameraState(&fixture.preview);

    const progress = progressForTicks(intro_cutscene_blend_ticks / 2, intro_cutscene_blend_ticks);
    const actual = normalizeCameraTransform(cameraTransformFromMatrix(runner.cutsceneCameraMatrix()));
    const expected = runner.introCutsceneBlendMatrix(&fixture.preview, progress);
    const look_at = normalizeCameraTransform(cameraTransformFromMatrix(runner.introCutsceneHoldMatrix(&fixture.preview)));
    const cameraman = normalizeCameraTransform(cameraTransformFromMatrix(runner.cameraman.live_matrix));

    try std.testing.expectEqual(CutsceneCameraState.intro_blend, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(expected, runner.cutsceneCameraMatrix(), 0.0001);
    try std.testing.expect(
        vector3DistanceSquared(actual.position, cameraman.position) <
            vector3DistanceSquared(look_at.position, cameraman.position),
    );
}

test "intro cutscene keeps the override lane for one terminal live-camera tick" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.setCutscene(cutscene_intro_id);
    runner.cutscene.camera.state = .intro_release;
    runner.cutscene.camera.ticks = 0;
    runner.refreshCameraState(&fixture.preview);

    try std.testing.expect(runner.cutsceneCameraActive());
    try std.testing.expectEqual(CutsceneCameraState.intro_release, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(runner.cameramanMatrix(), runner.cutsceneCameraMatrix(), 0.0001);

    runner.refreshCameraState(&fixture.preview);

    try std.testing.expect(!runner.cutsceneCameraActive());
    try std.testing.expectEqual(cutscene_none_id, runner.cutscene.id);
}

test "completion cutscene blends hotspot 12 toward hotspot 18 before fixing on 18" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.setCutscene(cutscene_completion_id);
    runner.refreshCameraState(&fixture.preview);

    try std.testing.expectEqual(CutsceneCameraState.completion_blend, runner.cutscene.camera.state);

    runner.cutscene.camera.state = .completion_blend;
    runner.cutscene.camera.ticks = completion_cutscene_blend_ticks / 2;
    runner.refreshCameraState(&fixture.preview);

    const progress = progressForTicks(completion_cutscene_blend_ticks / 2, completion_cutscene_blend_ticks);
    const expected_blend = runner.completionCutsceneBlendMatrix(&fixture.preview, progress);
    const actual_blend = normalizeCameraTransform(cameraTransformFromMatrix(runner.cutsceneCameraMatrix()));
    const hotspot_lerp = lerpVector3(
        runner.camera_hotspots_world.camera_skid_stop,
        runner.camera_hotspots_world.camera_intro_talk,
        progress,
    );

    try std.testing.expectEqual(CutsceneCameraState.completion_blend, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(expected_blend, runner.cutsceneCameraMatrix(), 0.0001);
    try std.testing.expect(actual_blend.position.x < hotspot_lerp.x);

    runner.cutscene.camera.state = .completion_hold;
    runner.cutscene.camera.ticks = 0;
    runner.refreshCameraState(&fixture.preview);

    const fixed = normalizeCameraTransform(cameraTransformFromMatrix(runner.cutsceneCameraMatrix()));
    try std.testing.expectEqual(CutsceneCameraState.completion_hold, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(
        runner.completionCutsceneFixedMatrix(&fixture.preview),
        runner.cutsceneCameraMatrix(),
        0.0001,
    );
    try expectVector3ApproxEq(runner.camera_hotspots_world.camera_intro_talk, fixed.position, 0.0001);
}

test "postal completion handoff waits for the row event controller to complete" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.session_mode = .postal;
    runner.row_event_display.parcel_target_count = 1;
    runner.row_event_display.state = .bonus_prompt;
    runner.beginCompletionCutscene();
    runner.handoff.completion_timer = completion_handoff_release_seconds;

    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.handoff.completion_timer < completion_handoff_release_force_seconds);

    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.updateRowEventDisplay(&fixture.preview, false);
    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
    try std.testing.expectEqual(RunnerHandoff.completion_finalize, runner.consumeHandoff());
}

test "challenge completion handoff waits for the row event controller to complete" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.session_mode = .challenge;
    runner.row_event_display.parcel_target_count = 1;
    runner.row_event_display.state = .bonus_prompt;
    runner.beginCompletionCutscene();
    runner.handoff.completion_screen_init_sent = true;
    runner.cutscene.camera.state = .completion_hold;
    runner.handoff.completion_timer = completion_handoff_release_seconds;

    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
    try std.testing.expect(runner.handoff.completion_timer < completion_handoff_release_force_seconds);

    runner.row_event_display.state = .complete;
    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RunnerHandoff.completion_finalize, runner.consumeHandoff());
}

test "time-trial completion handoff does not wait for the row event controller" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.session_mode = .time_trial;
    runner.row_event_display.parcel_target_count = 1;
    runner.row_event_display.state = .bonus_prompt;
    runner.beginCompletionCutscene();
    runner.handoff.completion_screen_init_sent = true;
    runner.cutscene.camera.state = .completion_hold;
    runner.handoff.completion_timer = completion_handoff_release_seconds;

    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RunnerHandoff.completion_finalize, runner.consumeHandoff());
}

test "completion gate fast-forwards the late handoff timer on the live completion cell" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.session_mode = .postal;
    runner.row_event_display.parcel_target_count = 1;
    runner.row_event_display.state = .bonus_prompt;
    runner.row_event_display.gate_18 = 1;
    runner.beginCompletionCutscene();
    runner.handoff.completion_timer = 1.0;

    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.updatePhaseController(&fixture.preview, 0.0);

    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.handoff.completion_timer > completion_handoff_release_seconds);
}

test "runner records attachment entry and jetpack pickup from shipped levels" {
    var challenge_fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer challenge_fixture.deinit();

    var runner = Runner.init(&challenge_fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const attachment = findFirstGameplayCell(&challenge_fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &challenge_fixture.preview, attachment);
    runner.step(&challenge_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.attachments_begun);
    try std.testing.expectEqualStrings("attachment_begin", runner.recentEventLabel());
    try std.testing.expect(runner.activePathName() != null);
    try std.testing.expect(runner.attachment.follow.active);

    var jetpack_fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer jetpack_fixture.deinit();

    runner = Runner.init(&jetpack_fixture.preview);
    const jetpack = findFirstGameplayCell(&jetpack_fixture.preview, .jetpack).?;
    primeRunnerBeforeRow(&runner, &jetpack_fixture.preview, jetpack);
    runner.step(&jetpack_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_pickups);
    try std.testing.expect(runner.jetpack.active);
    try std.testing.expect(runner.jetpackFuelRemaining() > 0.99);
    try std.testing.expectEqual(JetpackWarningBand.steady, runner.jetpack.warning_band);
    try std.testing.expectEqualStrings("jetpack_pickup", runner.recentEventLabel());

    const jetpack_off = findFirstAnnotationTag(&jetpack_fixture.preview, .jetpack_off).?;
    primeRunnerBeforeRow(&runner, &jetpack_fixture.preview, jetpack_off);
    runner.armJetpackGauge();
    runner.jetpack.progress = 0.25;
    runner.step(&jetpack_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_off_rows);
    try std.testing.expect(runner.jetpack.active);
    try std.testing.expectApproxEqAbs(jetpack_warning_threshold, runner.jetpack.progress, 0.0001);
    try std.testing.expectEqual(JetpackWarningBand.near_empty, runner.jetpack.warning_band);
    try std.testing.expectApproxEqAbs(@as(f32, 0.06), runner.jetpackFuelRemaining(), 0.0001);
    try std.testing.expectEqualStrings("jetpack_off", runner.recentEventLabel());
}

test "attachment follow preserves lateral offset instead of snapping to the path midpoint" {
    var fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer fixture.deinit();

    const target = findFirstOffCenterAttachmentEntry(&fixture.preview).?;
    const entry_lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    const entry_lateral_sign: f32 = if (entry_lane_center < target.path_center_lane) -1.0 else 1.0;

    var runner = Runner.init(&fixture.preview);
    primeRunnerBeforeRow(
        &runner,
        &fixture.preview,
        .{
            .row = target.row,
            .lane = target.lane,
        },
    );

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment.follow.active);
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const centered_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        runner.attachment.follow.template_progress,
        built.row.global_row,
        0.0,
        runner.attachment.follow.vertical_offset,
    );
    const entry_world_position = Runner.trackEntryWorldPosition(
        &fixture.preview,
        runner.row_position,
        @as(f32, @floatFromInt(target.lane)) + 0.5,
    );
    const centered_lane_center = Runner.laneCenterFromWorldX(&fixture.preview, centered_pose.position.x);
    try std.testing.expectApproxEqAbs(target.path_center_lane, runner.path_center_lane.?, 0.001);
    try std.testing.expect(@abs(runner.lane_center - target.path_center_lane) > 0.1);
    try std.testing.expect(@abs(runner.attachment.follow.lateral_offset) > 0.1);
    try std.testing.expect(runner.attachment.follow.lateral_offset * entry_lateral_sign > 0.0);
    try std.testing.expect((runner.lane_center - centered_lane_center) * runner.attachment.follow.lateral_offset > 0.0);
    try std.testing.expect(@abs(Runner.attachmentLocalPosition(centered_pose, entry_world_position).x) > 0.1);
}

test "standalone start segment attachment follow seeds generic entry from player-relative row and height" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);
    const sample = runner.sampleRow(&fixture.preview, target.row).?;
    const expected_progress = runner.row_position - @as(f32, @floatFromInt(sample.global_row));
    const expected_vertical_offset = runner.playerWorldPosition(&fixture.preview).y - attachment_entry_rider_height;

    runner.beginAttachmentFollow(&fixture.preview, sample);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment.follow.active);
    try std.testing.expectApproxEqAbs(expected_progress, runner.attachment.follow.progress, 0.0001);
    try std.testing.expectApproxEqAbs(expected_vertical_offset, runner.attachment.follow.vertical_offset, 0.0001);

    const world_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;

    try std.testing.expect(world_position.y > floor_height + 0.5);
    try std.testing.expectApproxEqAbs(world_position.z, runner.row_position, 0.001);
}

test "generic attachment begin preserves the raw row-relative progress seed" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    runner.row_position = @as(f32, @floatFromInt(target.row)) + 1.25;
    const sample = runner.sampleRow(&fixture.preview, target.row).?;

    runner.beginAttachmentFollow(&fixture.preview, sample);

    try std.testing.expectApproxEqAbs(@as(f32, 1.25), runner.attachment.follow.progress, 0.0001);
}

test "blocked startup refresh primes the current-row start attachment at zero rate" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const starting_row = currentRowIndex(&fixture.preview, runner.row_position);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    try std.testing.expectEqual(target.row, starting_row);
    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);

    runner.refreshBlockedStartupState(&fixture.preview);

    const expected_top_height = (@as(f32, @floatFromInt(@as(usize, @intFromFloat(@floor(4.0 * std.math.pi))))) / std.math.pi) * 2.0;

    try std.testing.expectEqual(@as(f32, 0.0), runner.track_step_rows);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment.follow.active);
    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(starting_row)), runner.row_position, 0.001);
    try std.testing.expectApproxEqAbs(expected_top_height, runner.worldPosition(&fixture.preview, 0.0).y, 0.001);
    try expectVector3ApproxEq(
        runner.playerWorldPosition(&fixture.preview),
        runner.cached_camera_target_world,
        0.0001,
    );
}

test "blocked startup start attachment keeps the live cameraman basis unmirrored" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    var refresh_count: usize = 0;
    while (refresh_count < 12) : (refresh_count += 1) {
        runner.refreshBlockedStartupState(&fixture.preview);
    }

    const cameraman = cameraTransformFromMatrix(runner.cameramanMatrix());
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment.follow.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.camera.orientation_a, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.camera.orientation_b, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment.camera.heading_roll, 0.0001);
    try std.testing.expect(cameraman.right.x > 0.0);
}

test "tutorial intro startup exits the start attachment on the authored track center" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.setCutscene(cutscene_intro_id);
    runner.refreshBlockedStartupState(&fixture.preview);

    var tick: usize = 0;
    while (tick < intro_cutscene_duration_ticks + 20) : (tick += 1) {
        if (runner.introCutsceneBlocksGameplay()) {
            runner.stepIntroStartupBlock(&fixture.preview, 1.0 / 60.0);
        } else {
            runner.step(&fixture.preview, .{}, 1.0 / 60.0);
        }
    }

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(!runner.attachment.follow.active);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.lane_center, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.worldPosition(&fixture.preview, 0.0).x, 0.001);
}

test "initial live cameraman update does not queue a stale shared-camera snap" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshCameraState(&fixture.preview);

    try std.testing.expect(!runner.takeCameramanSnap());
}

test "death cutscene keeps converging on hotspot 18 instead of switching to hotspot 17" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);
    runner.phase.fall.world_y = -0.75;
    runner.refreshCameraState(&fixture.preview);

    try std.testing.expectEqual(CutsceneCameraState.death_blend, runner.cutscene.camera.state);

    runner.cutscene.camera.state = .death_blend;
    runner.cutscene.camera.ticks = death_cutscene_blend_ticks / 2;
    runner.refreshCameraState(&fixture.preview);

    const progress = progressForTicks(death_cutscene_blend_ticks / 2, death_cutscene_blend_ticks);
    const expected_blend = runner.deathCutsceneBlendMatrix(&fixture.preview, progress);
    const actual_blend = normalizeCameraTransform(cameraTransformFromMatrix(runner.cutsceneCameraMatrix()));

    try std.testing.expectEqual(CutsceneCameraState.death_blend, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(expected_blend, runner.cutsceneCameraMatrix(), 0.0001);
    try std.testing.expect(actual_blend.position.x > runner.camera_hotspots_world.camera_intro_talk.x);
    try std.testing.expect(actual_blend.position.y >= death_cutscene_y_floor);

    runner.cutscene.camera.state = .death_hold;
    runner.cutscene.camera.ticks = 0;
    runner.refreshCameraState(&fixture.preview);

    const fixed = normalizeCameraTransform(cameraTransformFromMatrix(runner.cutsceneCameraMatrix()));
    try std.testing.expectEqual(CutsceneCameraState.death_hold, runner.cutscene.camera.state);
    try expectCameraMatrixApproxEq(
        runner.deathCutsceneFixedMatrix(&fixture.preview),
        runner.cutsceneCameraMatrix(),
        0.0001,
    );
    try std.testing.expect(fixed.position.y >= death_cutscene_y_floor);
    try std.testing.expect(
        vector3DistanceSquared(fixed.position, runner.camera_hotspots_world.camera_intro_talk) <
            vector3DistanceSquared(fixed.position, runner.camera_hotspots_world.camera_slug_death),
    );
}

test "nonlinear kind-42 entry height preserves the recovered raw local offset" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), Runner.attachmentEntryVerticalOffset(.nonlinear_42, 0.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.49), Runner.attachmentEntryVerticalOffset(.nonlinear_42, -0.49), 0.0001);
}

test "ordinary entry height still subtracts the rider baseline" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), Runner.attachmentEntryVerticalOffset(.start, attachment_entry_rider_height), 0.0001);
}

test "swept installed entry rejects pre-sample positions while current-row begin remains available" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const centered = attachment_builders.worldPositionForTemplate(
        &built.template,
        0.0,
        built.row.global_row,
        0.0,
        0.0,
    );
    const center_lane = Runner.laneCenterFromWorldX(&fixture.preview, centered.x);

    runner.lane_center = center_lane;
    runner.previous_lane_center = center_lane;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, center_lane);
    runner.resolved_lane_index = runner.lane_index;
    runner.previous_row_position = @as(f32, @floatFromInt(target.row)) - 0.01;
    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.2;

    const sample = runner.sampleRow(&fixture.preview, target.row).?;
    try std.testing.expect(runner.geometricInstalledAttachmentEntry(&fixture.preview, built, sample) == null);
    try std.testing.expect(runner.currentRowInstalledAttachmentEntry(&fixture.preview, built, target.row) != null);

    runner.last_processed_row = target.row;
    runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
}

test "current-row installed entry uses the native template span" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/WORM.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const width_threshold = (@as(f32, @floatFromInt(built.template.width_cells)) * 0.5) + attachment_side_exit_margin;
    const native_threshold = Runner.attachmentTemplateHalfSpan(built) + attachment_side_exit_margin;

    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.1;
    runner.lane_center = 7.5;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);
    runner.resolved_lane_index = runner.lane_index;

    const entry_world_position = Runner.trackEntryWorldPosition(&fixture.preview, runner.row_position, runner.lane_center);
    const entry_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        runner.row_position - @as(f32, @floatFromInt(target.row)),
        built.row.global_row,
        0.0,
        0.0,
    );
    const entry_local = Runner.attachmentLocalPosition(entry_pose, entry_world_position);
    const entry = runner.currentRowInstalledAttachmentEntry(&fixture.preview, built, target.row);
    try std.testing.expect(entry != null);
    try std.testing.expect(@abs(entry_local.x) > width_threshold);
    try std.testing.expect(@abs(entry_local.x) <= native_threshold);
}

test "current-row installed entry can begin from a later installed row span" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    try std.testing.expect(built.template.sample_count > 1);

    const later_row = target.row + 1;
    try std.testing.expectEqual(built, fixture.preview.installedBuiltAttachmentAtRow(later_row).?);

    const later_progress: f32 = @floatFromInt(later_row - built.row.global_row);
    const later_world_position = attachment_builders.worldPositionForTemplate(
        &built.template,
        later_progress,
        built.row.global_row,
        0.0,
        0.0,
    );
    runner.row_position = @as(f32, @floatFromInt(later_row)) + 0.2;
    runner.lane_center = Runner.laneCenterFromWorldX(&fixture.preview, later_world_position.x);
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);
    runner.resolved_lane_index = runner.lane_index;

    const entry = runner.currentRowInstalledAttachmentEntry(&fixture.preview, built, later_row).?;
    try std.testing.expectEqual(@as(usize, 1), entry.sample_index);
    try std.testing.expect(entry.local_progress > 0.0);
}

test "current-row prime path does not fabricate begin without an installed owner" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    fixture.preview.attachment_scaffold.installed_attachment_rows[target.row] = .{
        .primary = null,
        .secondary = null,
    };

    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.01;
    runner.lane_index = target.lane;
    runner.resolved_lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    runner.previous_lane_center = runner.lane_center;

    runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.attachments_begun);
}

test "visited attachment-entry rows do not fabricate begin without an installed owner" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    fixture.preview.attachment_scaffold.installed_attachment_rows[target.row] = .{
        .primary = null,
        .secondary = null,
    };

    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.01;
    runner.lane_index = target.lane;
    runner.resolved_lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;

    runner.processRow(&fixture.preview, target.row);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.attachments_begun);
    try std.testing.expectEqual(RecentEvent.none, runner.recent_event);
}

test "swept installed re-entry stays on the current-row prime path and leaves exit pending armed" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const setup = try findSweptInstalledEntrySetup(&runner, &fixture.preview, built);
    runner.lane_center = setup.lane_center;
    runner.previous_lane_center = setup.lane_center;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, setup.lane_center);
    runner.resolved_lane_index = runner.lane_index;
    const grid_index = (setup.row * fixture.preview.max_width) + runner.lane_index;
    fixture.preview.render_cache.flag_b40_grid[grid_index] = true;
    fixture.preview.runtime_flag_b80_grid[grid_index] = false;
    runner.previous_row_position = setup.previous_row_position;
    runner.row_position = setup.row_position;

    runner.processRow(&fixture.preview, setup.row);
    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);

    runner.attachment.exit.pending = true;
    runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.attachments_begun);
    try std.testing.expectEqual(RecentEvent.attachment_begin, runner.recent_event);
    try std.testing.expect(runner.attachment.exit.pending);
}

test "swept installed re-entry ignores rows without live attachment-owner flags" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const setup = try findSweptInstalledEntrySetup(&runner, &fixture.preview, built);
    const lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, setup.lane_center);
    const grid_index = (setup.row * fixture.preview.max_width) + lane_index;
    fixture.preview.render_cache.flag_b40_grid[grid_index] = false;
    fixture.preview.runtime_flag_b80_grid[grid_index] = false;

    runner.lane_center = setup.lane_center;
    runner.previous_lane_center = setup.lane_center;
    runner.lane_index = lane_index;
    runner.resolved_lane_index = lane_index;
    runner.previous_row_position = setup.previous_row_position;
    runner.row_position = setup.row_position;
    runner.attachment.exit.pending = true;

    runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);
    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.attachments_begun);
}

test "swept installed re-entry uses the live secondary owner slot only through B80" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var probe_runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const setup = try findSweptInstalledEntrySetup(&probe_runner, &fixture.preview, built);
    const lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, setup.lane_center);
    const grid_index = (setup.row * fixture.preview.max_width) + lane_index;
    const original_slots = fixture.preview.attachment_scaffold.installed_attachment_rows[setup.row];
    const primary_index = original_slots.primary orelse return error.TestUnexpectedResult;
    fixture.preview.attachment_scaffold.installed_attachment_rows[setup.row] = .{
        .primary = null,
        .secondary = primary_index,
    };

    var b40_runner = Runner.init(&fixture.preview);
    b40_runner.lane_center = setup.lane_center;
    b40_runner.previous_lane_center = setup.lane_center;
    b40_runner.lane_index = lane_index;
    b40_runner.resolved_lane_index = lane_index;
    b40_runner.previous_row_position = setup.previous_row_position;
    b40_runner.row_position = setup.row_position;
    b40_runner.attachment.exit.pending = true;
    fixture.preview.render_cache.flag_b40_grid[grid_index] = true;
    fixture.preview.runtime_flag_b80_grid[grid_index] = false;
    b40_runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);
    try std.testing.expectEqual(MovementMode.track, b40_runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 0), b40_runner.counters.attachments_begun);

    var b80_runner = Runner.init(&fixture.preview);
    b80_runner.lane_center = setup.lane_center;
    b80_runner.previous_lane_center = setup.lane_center;
    b80_runner.lane_index = lane_index;
    b80_runner.resolved_lane_index = lane_index;
    b80_runner.previous_row_position = setup.previous_row_position;
    b80_runner.row_position = setup.row_position;
    b80_runner.attachment.exit.pending = true;
    fixture.preview.render_cache.flag_b40_grid[grid_index] = false;
    fixture.preview.runtime_flag_b80_grid[grid_index] = true;
    b80_runner.tryPrimeCurrentRowAttachmentEntry(&fixture.preview);
    try std.testing.expectEqual(MovementMode.attachment, b80_runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), b80_runner.counters.attachments_begun);
}

test "standalone start segment attachment exits from the template end pose" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const exit_progress: f32 = @floatFromInt(built.template.sample_count);
    while (runner.movement_mode == .attachment and runner.attachment.follow.template_progress < exit_progress) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.row_position >= @as(f32, @floatFromInt(target.row + built.template.sample_count)));
    try std.testing.expect(runner.row_position > exit_progress);
}

test "attachment natural exit carries overshoot past the template end" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const sample_count: f32 = @floatFromInt(built.template.sample_count);
    runner.attachment.follow.sample_index = 0;
    runner.attachment.follow.local_progress = 0.0;
    runner.attachment.follow.progress = 0.0;
    runner.attachment.follow.template_progress = sample_count - 0.1;
    runner.speed_rows_per_second = 48.0;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.row_position > @as(f32, @floatFromInt(target.row)) + sample_count + built.template.exit_tail_extra);
}

test "supertramp natural exit enters a launch state above the floor" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/SUPERTRAMP.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const centered = attachment_builders.worldPositionForTemplate(
        &built.template,
        0.0,
        built.row.global_row,
        0.0,
        0.0,
    );
    const center_lane = Runner.laneCenterFromWorldX(&fixture.preview, centered.x);
    runner.lane_center = center_lane;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, center_lane);
    runner.resolved_lane_index = runner.lane_index;
    runner.refreshSample(&fixture.preview);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    const sample_count: f32 = @floatFromInt(built.template.sample_count);
    runner.attachment.follow.sample_index = 0;
    runner.attachment.follow.local_progress = 0.0;
    runner.attachment.follow.progress = 0.0;
    runner.attachment.follow.template_progress = sample_count - 0.1;
    runner.updateAttachmentFollowPosition(&fixture.preview);
    runner.speed_rows_per_second = 48.0;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.attachment.launch.active);

    const launched_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    try std.testing.expect(launched_position.y > floor_height + 0.5);

    const launch_forward = runner.worldForward(&fixture.preview);
    try std.testing.expect(launch_forward.y > 0.1);
}

test "attachment follow side threshold enters the shared fall state" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const subdivision_count = built.template.spec.subdivision_count orelse built.template.width_cells;
    const threshold = (@as(f32, @floatFromInt(subdivision_count)) * 0.5) + attachment_side_exit_margin + 0.2;
    const lateral_sign: f32 = if (runner.attachment.follow.lateral_offset < 0.0) -1.0 else 1.0;
    var side_exit_lateral = runner.attachment.follow.lateral_offset;
    while (true) {
        const pose = attachment_builders.samplePoseAtProgress(&built.template, runner.attachment.follow.template_progress);
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            runner.attachment.follow.template_progress,
            target.row,
            side_exit_lateral,
            runner.attachment.follow.vertical_offset,
        );
        if (@abs(world_pose.position.x - pose.center_x) > threshold) break;
        side_exit_lateral += 0.25 * lateral_sign;
    }
    runner.attachment.follow.lateral_offset = side_exit_lateral;
    runner.updateAttachmentFollowPosition(&fixture.preview);
    runner.endAttachmentIfNeeded(&fixture.preview);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_none_id, runner.cutscene.id);
    try std.testing.expect(runner.attachment.exit.pending);
    try std.testing.expect(!runner.attachment.follow.active);
    try std.testing.expect(runner.row_position >= @as(f32, @floatFromInt(target.row)));
}

test "attachment side threshold is suppressed while jetpack is active" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const subdivision_count = built.template.spec.subdivision_count orelse built.template.width_cells;
    const threshold = (@as(f32, @floatFromInt(subdivision_count)) * 0.5) + attachment_side_exit_margin + 0.2;
    const lateral_sign: f32 = if (runner.attachment.follow.lateral_offset < 0.0) -1.0 else 1.0;
    var side_exit_lateral = runner.attachment.follow.lateral_offset;
    while (true) {
        const pose = attachment_builders.samplePoseAtProgress(&built.template, runner.attachment.follow.template_progress);
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            runner.attachment.follow.template_progress,
            target.row,
            side_exit_lateral,
            runner.attachment.follow.vertical_offset,
        );
        if (@abs(world_pose.position.x - pose.center_x) > threshold) break;
        side_exit_lateral += 0.25 * lateral_sign;
    }
    runner.attachment.follow.lateral_offset = side_exit_lateral;
    runner.jetpack.active = true;

    try std.testing.expect(!runner.attachmentShouldSideExit(built));
}

test "loop side threshold preserves airborne fall height" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/LOOPBOW.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;

    var airborne_progress: ?f32 = null;
    var sample_progress: f32 = 0.0;
    while (sample_progress < @as(f32, @floatFromInt(built.template.sample_count))) : (sample_progress += 0.25) {
        const world_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            sample_progress,
            target.row,
            0.0,
            0.0,
        );
        const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
            currentRowIndex(&fixture.preview, world_position.z),
            fixture.preview.laneIndexAtWorldX(world_position.x),
            world_position.z,
        ) orelse 0.0;
        if (world_position.y > floor_height + 1.0) {
            airborne_progress = sample_progress;
            break;
        }
    }
    try std.testing.expect(airborne_progress != null);

    runner.movement_mode = .attachment;
    runner.attachment.path_name = "LOOPBOW";
    runner.attachment.follow = .{
        .active = true,
        .source_cell_row = target.row,
        .template_progress = airborne_progress.?,
    };
    runner.updateAttachmentFollowPosition(&fixture.preview);

    const subdivision_count = built.template.spec.subdivision_count orelse built.template.width_cells;
    const threshold = (@as(f32, @floatFromInt(subdivision_count)) * 0.5) + attachment_side_exit_margin + 0.2;
    const lateral_sign: f32 = if (runner.attachment.follow.lateral_offset < 0.0) -1.0 else 1.0;
    var side_exit_lateral = runner.attachment.follow.lateral_offset;
    while (true) {
        const pose = attachment_builders.samplePoseAtProgress(&built.template, runner.attachment.follow.template_progress);
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            runner.attachment.follow.template_progress,
            target.row,
            side_exit_lateral,
            runner.attachment.follow.vertical_offset,
        );
        if (@abs(world_pose.position.x - pose.center_x) > threshold) break;
        side_exit_lateral += 0.25 * lateral_sign;
    }
    runner.attachment.follow.lateral_offset = side_exit_lateral;
    runner.updateAttachmentFollowPosition(&fixture.preview);
    runner.endAttachmentIfNeeded(&fixture.preview);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_none_id, runner.cutscene.id);
    try std.testing.expect(runner.attachment.exit.pending);
    try std.testing.expect(!runner.attachment.launch.active);

    const fallen_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    try std.testing.expect(fallen_position.y > floor_height + 0.5);
}

test "installed attachment sweep scans the full template from tail to head" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;

    var candidate_index: ?usize = null;
    var sample_index = @min(@as(usize, built.template.sample_count), built.template.samples.len);
    while (sample_index > 0) {
        sample_index -= 1;
        const template_sample = built.template.samples[sample_index];
        if (template_sample.basis_up.y >= 0.0 and template_sample.delta_length > 0.1) {
            candidate_index = sample_index;
            break;
        }
    }
    const matched_index = candidate_index orelse return error.TestUnexpectedResult;
    try std.testing.expect(matched_index > 0);

    const sample_length = built.template.samples[matched_index].delta_length;
    const candidate_progress: f32 = @floatFromInt(matched_index);
    const pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        candidate_progress,
        built.row.global_row,
        0.0,
        0.0,
    );
    const start_local = attachment_builders.Vec3{
        .x = 0.0,
        .y = 0.0,
        .z = sample_length * 0.5,
    };
    const start_world_position = Runner.attachmentWorldPositionFromLocal(pose, start_local);
    const end_world_position = Runner.attachmentWorldPositionFromLocal(pose, .{
        .x = 0.0,
        .y = -0.05,
        .z = start_local.z,
    });

    const entry = Runner.installedAttachmentEntryForSweep(built, start_world_position, end_world_position).?;
    try std.testing.expectEqual(matched_index, entry.sample_index);
    try std.testing.expectApproxEqAbs(start_local.z, entry.local_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), entry.lateral_offset, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), entry.vertical_offset, 0.0001);
}

test "installed attachment sweep rejects upside-down samples" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/INVERT.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;

    var inverted_index: ?usize = null;
    for (built.template.samples, 0..) |template_sample, sample_index| {
        if (sample_index >= built.template.sample_count) break;
        if (template_sample.basis_up.y < 0.0 and template_sample.delta_length > 0.1) {
            inverted_index = sample_index;
            break;
        }
    }
    const matched_index = inverted_index orelse return error.TestUnexpectedResult;

    const sample_length = built.template.samples[matched_index].delta_length;
    const candidate_progress: f32 = @floatFromInt(matched_index);
    const pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        candidate_progress,
        built.row.global_row,
        0.0,
        0.0,
    );
    const start_local = attachment_builders.Vec3{
        .x = 0.0,
        .y = 0.0,
        .z = sample_length * 0.5,
    };
    const start_world_position = Runner.attachmentWorldPositionFromLocal(pose, start_local);
    const end_world_position = Runner.attachmentWorldPositionFromLocal(pose, .{
        .x = 0.0,
        .y = -0.05,
        .z = start_local.z,
    });

    try std.testing.expect(
        Runner.installedAttachmentEntryForSweep(built, start_world_position, end_world_position) == null,
    );
}

test "current-row installed entry respects template width" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const outside_lane = laneOutsideAttachmentWidth(&fixture.preview, built, target.row).?;
    runner.lane_center = @as(f32, @floatFromInt(outside_lane)) + 0.5;
    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.2;

    try std.testing.expect(
        runner.currentRowInstalledAttachmentEntry(&fixture.preview, built, target.row) == null,
    );
}

test "continuous target lane center preserves fractional track steering" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    primeRunnerAfterFirstInstalledAttachment(&runner, &fixture.preview);
    runner.step(&fixture.preview, .{ .target_lane_center = 4.5 }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.lane_center > 4.5);
    try std.testing.expect(runner.lane_center < 5.5);
    try std.testing.expect(@abs(runner.lane_center - (@floor(runner.lane_center) + 0.5)) > 0.05);
}

test "relative mouse steering starts centered after click-start" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.debugWarpToTrackRow(&fixture.preview, @as(f32, @floatFromInt(fixture.preview.runtime_active_row_start + 8)), 5.0);
    runner.lane_center = 5.0;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);

    runner.step(&fixture.preview, .{ .steering_authored_x = 500.0 }, 1.0 / native_ticks_per_second);

    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.lane_center, 0.0001);
    try std.testing.expectApproxEqAbs(native_steering_center_x, runner.steering_offset_authored_x, 0.0001);
}

test "relative mouse steering follows pointer deltas rather than absolute position" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.debugWarpToTrackRow(&fixture.preview, @as(f32, @floatFromInt(fixture.preview.runtime_active_row_start + 8)), 5.0);
    runner.lane_center = 5.0;
    runner.lane_index = Runner.laneIndexForLaneCenter(&fixture.preview, runner.lane_center);

    runner.step(&fixture.preview, .{ .steering_authored_x = 500.0 }, 1.0 / native_ticks_per_second);
    runner.step(&fixture.preview, .{ .steering_authored_x = 540.0 }, 1.0 / native_ticks_per_second);

    try std.testing.expectApproxEqAbs(@as(f32, 360.0), runner.steering_offset_authored_x, 0.0001);
    try std.testing.expect(runner.lane_center < 5.0);
    try std.testing.expect(runner.lane_center > 4.0);
}

test "continuous target lane center steers attachment lateral offset" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const before_offset = runner.attachment.follow.lateral_offset;
    const raw_target_lane_center = runner.lane_center + 1.5;
    const built = runner.currentAttachmentBuilt(&fixture.preview).?;
    const target_world_position = Runner.trackEntryWorldPosition(
        &fixture.preview,
        runner.row_position,
        raw_target_lane_center,
    );
    const centered_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        runner.attachment.follow.template_progress,
        runner.attachment.follow.source_cell_row,
        0.0,
        runner.attachment.follow.vertical_offset,
    );
    const target_lateral_offset = Runner.attachmentLateralOffsetFromLocalX(
        &built.template,
        runner.attachment.follow.template_progress,
        Runner.attachmentLocalPosition(centered_pose, target_world_position).x,
    );
    runner.step(&fixture.preview, .{ .target_lane_center = raw_target_lane_center }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(
        @abs(runner.attachment.follow.lateral_offset - target_lateral_offset) <
            @abs(before_offset - target_lateral_offset),
    );
    try std.testing.expect(@abs(runner.attachment.follow.lateral_offset - @round(runner.attachment.follow.lateral_offset)) > 0.05);
}

test "installed attachment probe tiles still allow installed begins" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const row_tile_base = target.row * fixture.preview.max_width;
    for (0..fixture.preview.max_width) |lane| {
        const tile_index = row_tile_base + lane;
        if (fixture.preview.runtime_tiles[tile_index] == 0x1e) {
            fixture.preview.runtime_tiles[tile_index] = 0x1d;
        }
    }
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.attachments_begun);
    try std.testing.expectEqual(RecentEvent.attachment_begin, runner.recent_event);
}

test "halfpipe attachment tilts world up with lateral drift" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/HALFPIPE.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    runner.step(&fixture.preview, .{ .lane_delta = 2 }, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    runner.step(&fixture.preview, .{ .lane_delta = 1 }, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const up = runner.worldUp(&fixture.preview);
    try std.testing.expect(@abs(up.x) > 0.04);
}

test "halfpipe attachment rides above the trough floor" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/HALFPIPE.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const world_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    try std.testing.expect(world_position.y > floor_height + 0.35);
}

test "jetpack gauge enters near-empty warning and skips warning math near route end" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.armJetpackGauge();
    runner.jetpack.progress = 0.94;
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expectEqual(JetpackWarningBand.near_empty, runner.jetpack.warning_band);
    try std.testing.expect(runner.jetpack.pulse_envelope > 0.0);
    try std.testing.expect(runner.jetpack.wobble_y > 0.0);

    // PORT(verified): native `update_jetpack_gauge` @ 0x43a3ee uses the 5-row
    // end-of-course band only to skip warning-math presentation that tick; the gauge
    // stays state 1. Assert the gauge remains active, wobbles are not updated, and
    // the band stays at its pre-call default.
    runner.jetpack.disarm();
    runner.armJetpackGauge();
    fixture.preview.course_end_threshold = 40.0;
    runner.row_position = 35.1;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.track_row_progress = runner.row_position - @floor(runner.row_position);
    runner.refreshSample(&fixture.preview);
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expect(runner.jetpack.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.jetpack.wobble_x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.jetpack.wobble_y, 0.0001);
}

test "cached camera target defaults to the player world position without jetpack offsets" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshCachedCameraTarget(&fixture.preview);

    try expectVector3ApproxEq(
        runner.playerWorldPosition(&fixture.preview),
        runner.cached_camera_target_world,
        0.0001,
    );
}

test "cached camera target uses the native jetpack wobble axes" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.jetpack.wobble_x = 0.25;
    runner.jetpack.wobble_y = 0.5;
    runner.jetpack.wobble_alpha = -0.125;

    const base_position = runner.playerWorldPosition(&fixture.preview);
    const frame = orthonormalFrameFromForwardUp(runner.worldForward(&fixture.preview), runner.worldUp(&fixture.preview));
    const expected = rl.Vector3{
        .x = base_position.x + (frame.right.x * runner.jetpack.wobble_x) + (frame.up.x * runner.jetpack.wobble_y) + (frame.forward.x * runner.jetpack.wobble_alpha),
        .y = base_position.y + (frame.right.y * runner.jetpack.wobble_x) + (frame.up.y * runner.jetpack.wobble_y) + (frame.forward.y * runner.jetpack.wobble_alpha),
        .z = base_position.z + (frame.right.z * runner.jetpack.wobble_x) + (frame.up.z * runner.jetpack.wobble_y) + (frame.forward.z * runner.jetpack.wobble_alpha),
    };

    runner.refreshCachedCameraTarget(&fixture.preview);

    try expectVector3ApproxEq(expected, runner.cached_camera_target_world, 0.0001);
}

test "cameraman progress blend uses cached camera target z" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_position = @as(f32, @floatFromInt(fixture.preview.runtime_active_row_start)) + 32.0;
    runner.cached_camera_target_world.z = 0.0;
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.cameramanProgressBlend(&fixture.preview), 0.0001);

    runner.cached_camera_target_world.z = @floatFromInt(fixture.preview.runtime_active_row_start);

    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.cameramanProgressBlend(&fixture.preview), 0.0001);
}

test "cameraman matrix blend factor follows the live subgame rate" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.track_step_rows = 0.2;
    try std.testing.expectApproxEqAbs(@as(f32, 0.06), runner.cameramanMatrixBlendFactor(), 0.0001);

    runner.track_step_rows = 8.0;
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.cameramanMatrixBlendFactor(), 0.0001);
}

test "cameraman ignores speed when cached camera target is fixed" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var low_runner = Runner.init(&fixture.preview);
    low_runner.cached_camera_target_world = .{ .x = 0.0, .y = 0.6, .z = 100.0 };
    low_runner.updateCameraman(&fixture.preview);
    const low_transform = cameraTransformFromMatrix(low_runner.cameramanMatrix());

    var speed_runner = Runner.init(&fixture.preview);
    speed_runner.speed_rows_per_second = 48.0;
    speed_runner.cached_camera_target_world = low_runner.cached_camera_target_world;
    speed_runner.updateCameraman(&fixture.preview);
    const speed_transform = cameraTransformFromMatrix(speed_runner.cameramanMatrix());

    try std.testing.expectApproxEqAbs(low_transform.forward.y, speed_transform.forward.y, 0.0001);
}

test "cameraman lateral follow uses native one-third cached target x" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.cached_camera_target_world = .{ .x = 3.0, .y = 0.49, .z = 100.0 };

    runner.updateCameraman(&fixture.preview);

    try std.testing.expectApproxEqAbs(@as(f32, 2.2), runner.cameraman.desired_matrix.m12, 0.0001);
}

test "cameraman z deadzone follows the desired camera position after base offset" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.tick_count = 1;
    runner.track_step_rows = 1.0;
    runner.cached_camera_target_world = .{ .x = 0.0, .y = 0.49, .z = 100.0 };

    runner.updateCameraman(&fixture.preview);

    try std.testing.expectApproxEqAbs(@as(f32, 99.9), runner.cameraman.desired_matrix.m14, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 97.8), runner.cameraman.live_matrix.m14, 0.0001);
}

test "jetpack gauge ramps warning intensity during the startup tenth" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.armJetpackGauge();
    runner.jetpack.progress = 0.048333332;

    runner.updateJetpackGauge(&fixture.preview);

    try std.testing.expectEqual(JetpackWarningBand.steady, runner.jetpack.warning_band);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), runner.jetpack.warning_intensity, 0.01);
    try std.testing.expectApproxEqAbs(runner.jetpack.warning_intensity, runner.jetpack.pulse_envelope, 0.0001);
    try std.testing.expect(runner.jetpack.wobble_x != 0.0);
    try std.testing.expect(runner.jetpack.wobble_y > 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.jetpack.wobble_alpha, 0.0001);
}

test "fatal floor gaps enter the shared fall state without a cutscene override" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, false).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    // Native gravity `-0.01 * track_center_x^2 = -0.16` per tick pulls the grounded
    // `0.49` start below the `-7` death threshold inside ~15 ticks. Step a generous
    // window so the test covers speed variance without being flaky.
    var ticks: u32 = 0;
    while (ticks < 64) : (ticks += 1) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
        if (runner.phase != .active) break;
    }

    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.fall, runner.deathCause().?);
    try std.testing.expectEqual(cutscene_none_id, runner.cutscene.id);
}

test "runner descends through an authored gap row instead of halting at the edge" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, true).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    const starting_position_y = runner.position_y;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    // `0043b120-update_subgoldy.c:504` only kills the player once `position.y < -7`,
    // not on first contact with a no-floor tile. One motion tick over an authored gap
    // row should leave the runner active with gravity just beginning to pull
    // `velocity_y` down.
    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqualStrings("no_fall", runner.recentEventLabel());
    try std.testing.expect(runner.velocity_y < 0.0);
    try std.testing.expectApproxEqAbs(starting_position_y, runner.position_y, 0.0001);
}

test "barrier hold tile snaps z and arms post-follow exit after the native timer" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = 12;
    runner.track_row_progress = 0.73;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    fixture.preview.runtime_tiles[(runner.current_global_row * fixture.preview.max_width) + runner.resolved_lane_index] = native_wall2_tile_id;
    runner.native_velocity_z_override_per_tick = 0.8;

    runner.stepActivePhaseVerticalMotion(&fixture.preview);

    try std.testing.expectEqual(@as(?f32, null), runner.native_velocity_z_override_per_tick);
    try std.testing.expectApproxEqAbs(@as(f32, 12.5), runner.row_position, 0.0001);
    try std.testing.expectApproxEqAbs(runner.presentation.barrier_hold_step, runner.presentation.barrier_hold_progress, 0.0001);
    try std.testing.expect(!runner.attachment.exit.pending);

    var ticks: usize = 0;
    while (ticks < 61 and !runner.attachment.exit.pending) : (ticks += 1) {
        runner.refreshSample(&fixture.preview);
        fixture.preview.runtime_tiles[(runner.current_global_row * fixture.preview.max_width) + runner.resolved_lane_index] = native_wall2_tile_id;
        runner.stepActivePhaseVerticalMotion(&fixture.preview);
    }

    try std.testing.expect(runner.attachment.exit.pending);
    try std.testing.expectApproxEqAbs(runner.row_position, runner.attachment.exit.anchor_z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.presentation.barrier_hold_progress, 0.0001);
}

test "floor-cache launch rows preserve enough native forward carry for trampoline gaps" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const segment_entry = catalog.segment_entries[catalog.findSegmentIndex("SEGMENTS/TRAMPOLINES.TXT").?];
    var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        segment_entry,
        .{
            .load_models = false,
            .runtime_active_row_start = 0,
        },
    );
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.lane_index = 2;
    runner.lane_center = 2.5;
    runner.runtime_track_index = 2;
    runner.track_row_progress = 0.0;
    runner.syncRowPosition(&preview);
    runner.refreshSample(&preview);
    runner.last_processed_row = 2;

    var saw_trampoline_bounce = false;
    var ticks: u32 = 0;
    while (ticks < 90) : (ticks += 1) {
        runner.step(&preview, .{}, 1.0 / 60.0);
        if (runner.post_trampoline_airborne) {
            saw_trampoline_bounce = true;
            break;
        }
        if (runner.phase != .active) break;
    }

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expect(saw_trampoline_bounce);
    try std.testing.expect(runner.counters.trampoline_bounces > 0);
    try std.testing.expect(runner.current_global_row >= 24);
}

test "tutorial powerup ramps preserve enough native carry to cross the authored gap" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const segment_entry = catalog.segment_entries[catalog.findSegmentIndex("SEGMENTS/TUTORIAL 4.TXT").?];
    var preview = try track.LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        segment_entry,
        .{
            .load_models = false,
            .runtime_active_row_start = 0,
        },
    );
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.speed_rows_per_second = 10.0;
    runner.lane_index = 4;
    runner.lane_center = 4.5;
    runner.runtime_track_index = 2;
    runner.track_row_progress = 0.0;
    runner.syncRowPosition(&preview);
    runner.refreshSample(&preview);
    runner.last_processed_row = 2;

    var ticks: u32 = 0;
    while (ticks < 120 and runner.current_global_row < 20) : (ticks += 1) {
        runner.step(&preview, .{}, 1.0 / 60.0);
        if (runner.phase != .active) break;
    }

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expect(runner.current_global_row >= 20);
    try std.testing.expect(runner.position_y > native_position_y_death_threshold);
}

test "active jetpack suppresses fall entry over a floor gap" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, false).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    runner.armJetpackGauge();
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expect(runner.jetpack.active);
}

test "runner records trampoline rows from shipped levels" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const trampoline = findFirstGameplayCell(&fixture.preview, .trampoline).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, trampoline);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.trampoline_rows);
    try std.testing.expectEqualStrings("trampoline", runner.recentEventLabel());
    try std.testing.expectEqualStrings("trampoline", runner.gameplayCellLabel().?);
}

test "score awards update transient tutorial hud state" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.recordScore(&runner.score.ring_collect, 100);
    try std.testing.expectEqual(@as(u32, 100), runner.recent_score_award);
    try std.testing.expectEqual(@as(u8, 45), runner.recent_score_award_ticks);

    runner.stepTemporaryStates();
    try std.testing.expectEqual(@as(u8, 44), runner.recent_score_award_ticks);
}

test "row message token increments when the runner enters a new logical segment" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const initial_token = runner.currentRowMessageToken();
    const initial_logical_segment_index = runner.currentRowMessageLogicalSegmentIndex();

    var expected_logical_segment_index: ?usize = null;
    for (0..fixture.preview.total_rows) |global_row| {
        const row_location = fixture.preview.locateRow(global_row) orelse continue;
        const logical_segment_index = fixture.preview.segment_logical_indices[row_location.segment_index] orelse continue;
        if (initial_logical_segment_index) |initial_index| {
            if (logical_segment_index == initial_index) continue;
        }
        expected_logical_segment_index = logical_segment_index;
        break;
    }

    const next_logical_segment_index = expected_logical_segment_index orelse return error.TestExpectedLogicalSegment;
    var tick: usize = 0;
    while (tick < 4096 and runner.currentRowMessageToken() == initial_token) : (tick += 1) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(initial_token +% 1, runner.currentRowMessageToken());
    try std.testing.expectEqual(next_logical_segment_index, runner.currentRowMessageLogicalSegmentIndex().?);
}

test "replay directive overrides world x and latches replay flags" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .lateral_world_x = -3.25,
            .raw_flag_bits = 0x0c,
        },
        1.0 / 60.0,
    );

    const world = runner.worldPosition(&fixture.preview, 0.82);
    try std.testing.expectApproxEqAbs(@as(f32, -3.25), world.x, 0.0001);
    try std.testing.expectEqual(@as(usize, 1), runner.resolved_lane_index);
    try std.testing.expectEqual(@as(u8, 0x0c), runner.replayRawFlagBits());
    try std.testing.expect(runner.replayTrackStateLatched());
    try std.testing.expect(runner.replayFadeRequested());
    try std.testing.expect(runner.consumeReplayFadeRequest());
    try std.testing.expect(!runner.consumeReplayFadeRequest());
}

test "replay directive seeds the tick before live steering and movement" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const replay_world_x: f32 = -3.25;
    const replay_lane_center = Runner.laneCenterFromWorldX(&fixture.preview, replay_world_x);
    runner.stepWithReplay(
        &fixture.preview,
        .{
            .lane_delta = 1,
            .target_lane_center = replay_lane_center + 4.0,
            .steering_authored_x = native_steering_max_x,
        },
        .{
            .active = true,
            .lateral_world_x = replay_world_x,
            .raw_flag_bits = 0x04,
        },
        1.0 / 60.0,
    );

    try std.testing.expectApproxEqAbs(replay_lane_center, runner.previous_lane_center, 0.0001);
    try std.testing.expectApproxEqAbs(replay_lane_center, runner.lane_center, 0.0001);
    try std.testing.expect(runner.replayTrackStateLatched());
}

test "replay sample cursor advances per active update independent of row index" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    try std.testing.expectEqual(starting_runtime_track_index, runner.runtime_track_index);
    try std.testing.expectEqual(@as(usize, 0), runner.replay_sample_index);

    runner.stepWithReplay(&fixture.preview, .{}, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(starting_runtime_track_index, runner.runtime_track_index);
    try std.testing.expectEqual(@as(usize, 1), runner.replay_sample_index);
    try std.testing.expect(runner.track_row_progress > 0.0);
}

test "time-trial ghost marker clamps to twenty rows ahead of Turbo" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_position = 12.0;

    runner.markTimeTrialGhost(40.0);
    try std.testing.expect(runner.time_trial_ghost_active);
    try std.testing.expectApproxEqAbs(@as(f32, 32.0), runner.time_trial_ghost_z, 0.0001);

    runner.markTimeTrialGhost(20.0);
    try std.testing.expectApproxEqAbs(@as(f32, 20.0), runner.time_trial_ghost_z, 0.0001);

    runner.clearTimeTrialGhost();
    try std.testing.expect(!runner.time_trial_ghost_active);
}

test "replay flag bit 0x1 seeds native movement fire progress" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    primeRunnerAfterFirstInstalledAttachment(&runner, &fixture.preview);
    runner.tick_count = 10;
    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x05,
        },
        1.0 / 60.0,
    );

    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.track_row_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.37407407), runner.presentation.movement_fire_cooldown, 0.0001);
    try std.testing.expectApproxEqAbs(
        @as(f32, @floatFromInt(runner.runtime_track_index)) + runner.track_row_progress,
        runner.row_position,
        0.0001,
    );
}

test "replay flag bit 0x2 seeds native movement fire progress from the selector step" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    primeRunnerAfterFirstInstalledAttachment(&runner, &fixture.preview);
    runner.track_row_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.tick_count = 10;

    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x06,
        },
        1.0 / 60.0,
    );

    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.track_step_rows, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.8), runner.track_row_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.074074075), runner.presentation.movement_fire_cooldown, 0.0001);
    try std.testing.expectApproxEqAbs(
        @as(f32, @floatFromInt(runner.runtime_track_index)) + runner.track_row_progress,
        runner.row_position,
        0.0001,
    );
}
