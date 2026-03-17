const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("attachment_builders.zig");
const assets = @import("assets.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const track = @import("track.zig");

pub const RunnerInput = struct {
    lane_delta: i8 = 0,
    target_lane_center: ?f32 = null,
    speed_delta_rows_per_second: f32 = 0.0,
    fire: bool = false,
    toggle_pause: bool = false,
    reset: bool = false,
};

pub const ReplayDirective = struct {
    active: bool = false,
    lateral_world_x: ?f32 = null,
    secondary_lane: ?i32 = null,
    raw_flag_bits: u8 = 0,
};

pub const AttachmentHint = enum {
    none,
    probe,
    entry,

    pub fn label(self: AttachmentHint) []const u8 {
        return switch (self) {
            .none => "none",
            .probe => "probe",
            .entry => "entry",
        };
    }
};

pub const MovementMode = enum {
    track,
    attachment,

    pub fn label(self: MovementMode) []const u8 {
        return switch (self) {
            .track => "track",
            .attachment => "attachment",
        };
    }
};

pub const SessionMode = enum {
    debug,
    postal,
    challenge,
    time_trial,
    tutorial,

    pub fn label(self: SessionMode) []const u8 {
        return switch (self) {
            .debug => "debug",
            .postal => "postal",
            .challenge => "challenge",
            .time_trial => "time_trial",
            .tutorial => "tutorial",
        };
    }
};

pub const DeathCause = enum {
    damage,
    hazard,
    fall,

    pub fn label(self: DeathCause) []const u8 {
        return switch (self) {
            .damage => "damage",
            .hazard => "hazard",
            .fall => "fall",
        };
    }
};

pub const cutscene_none_id: u8 = 0;
pub const cutscene_intro_id: u8 = 1;
pub const cutscene_completion_id: u8 = 5;
pub const cutscene_death_id: u8 = 10;

pub const RunnerHandoff = union(enum) {
    none,
    completion_screen_init,
    completion_finalize,
    respawn: DeathCause,
    final_loss: DeathCause,
};

const FallState = struct {
    cause: DeathCause,
    world_x: f32,
    world_y: f32,
    world_z: f32,
    vertical_velocity: f32 = 0.0,
    basis_forward: attachment_builders.Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    basis_up: attachment_builders.Vec3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
};

pub const RuntimeHazardKind = enum {
    garbage,
    salt,
};

pub const RuntimeHazard = struct {
    row: usize,
    lane: usize,
    kind: RuntimeHazardKind,
    presentation_scale: f32 = 1.0,
    presentation_phase: f32 = 0.0,
};

pub const TrackParcelRuntime = struct {
    state: u32 = 0,
    row: usize = 0,
    parcel_id: i32 = 0,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    flight_anchor: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_scale: f32 = 1.0,
    bob_phase: f32 = 0.0,
    bob_phase_step: f32 = track_parcel_bob_phase_step,
    progress: f32 = 0.0,
    progress_step: f32 = 0.0,
    target_distance: f32 = 0.0,
    travel_dir: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    delivery_offset: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },

    pub fn active(self: TrackParcelRuntime) bool {
        return self.state != 0;
    }

    pub fn presentationPosition(self: TrackParcelRuntime) rl.Vector3 {
        return switch (self.state) {
            1 => blk: {
                var position = self.world_position;
                position.y += std.math.sin(self.bob_phase * std.math.tau) * track_parcel_bob_amplitude;
                break :blk position;
            },
            5, 7 => self.presentation_position,
            else => self.world_position,
        };
    }

    pub fn presentationScale(self: TrackParcelRuntime) f32 {
        return switch (self.state) {
            5, 7 => self.presentation_scale,
            else => 1.0,
        };
    }
};

const TrackParcelHomeAnchor = struct {
    active: bool = false,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

const TurretState = struct {
    row: usize,
    lane: usize,
    seconds: f32 = 0.0,
    flash_ticks: u8 = 0,
};

pub const Projectile = struct {
    pub const Kind = enum {
        turbo,
        laser,
        rocket,
        enemy_laser,
    };

    active: bool = false,
    kind: Kind = .turbo,
    world_x: f32 = 0.0,
    world_y: f32 = 0.0,
    world_z: f32 = 0.0,
    dir_x: f32 = 0.0,
    dir_y: f32 = 0.0,
    dir_z: f32 = 1.0,
    speed_rows_per_second: f32 = 0.0,
};

const RunnerPhase = union(enum) {
    active,
    fall: FallState,
    completion_handoff,
};

const completion_handoff_timer_step: f32 = 1.0 / 60.0;
const completion_handoff_voice_delay_seconds: f32 = 2.5;
const completion_handoff_release_seconds: f32 = 5.0;
const completion_handoff_release_force_seconds: f32 = 5.1;
const replay_world_x_min: f32 = -4.0;
const replay_world_x_max: f32 = 4.0;
const row_event_display_stage_progress_step: f32 = 1.0 / 24.0;
const row_event_display_hold_progress_step: f32 = 1.0 / 60.0;
const row_event_display_final_delay_progress_step: f32 = 1.0 / 60.0;
const row_event_widget_local_x: f32 = 7.30000019;
const row_event_widget_local_y: f32 = 2.0;
const row_event_widget_local_z: f32 = 6.0;

pub const RecentEvent = union(enum) {
    none,
    attachment_probe,
    attachment_begin,
    attachment_end,
    parcel: i32,
    trampoline,
    health_pickup,
    jetpack_pickup,
    garbage_hit,
    salt_hit,
    slug_hit,
    turret_hit,
    no_fall,
    jetpack_off,
    ring: segment.RingKind,

    pub fn label(self: RecentEvent) []const u8 {
        return switch (self) {
            .none => "none",
            .attachment_probe => "attachment_probe",
            .attachment_begin => "attachment_begin",
            .attachment_end => "attachment_end",
            .parcel => "parcel",
            .trampoline => "trampoline",
            .health_pickup => "health_pickup",
            .jetpack_pickup => "jetpack_pickup",
            .garbage_hit => "garbage_hit",
            .salt_hit => "salt_hit",
            .slug_hit => "slug_hit",
            .turret_hit => "turret_hit",
            .no_fall => "no_fall",
            .jetpack_off => "jetpack_off",
            .ring => |ring_kind| switch (ring_kind) {
                .none => "ring_none",
                .normal => "ring_normal",
                .powerup => "ring_powerup",
                .explode => "ring_explode",
                .slow => "ring_slow",
            },
        };
    }
};

pub const EncounterCounters = struct {
    attachments_begun: u32 = 0,
    attachments_completed: u32 = 0,
    parcels: u32 = 0,
    trampoline_rows: u32 = 0,
    health_pickups: u32 = 0,
    jetpack_pickups: u32 = 0,
    garbage_hits: u32 = 0,
    salt_hits: u32 = 0,
    slug_hits: u32 = 0,
    turret_hits: u32 = 0,
    no_fall_rows: u32 = 0,
    jetpack_off_rows: u32 = 0,
    ring_normal: u32 = 0,
    ring_powerup: u32 = 0,
    ring_explode: u32 = 0,
    ring_slow: u32 = 0,
};

pub const ScoreTotals = struct {
    total: u32 = 0,
    ring_collect: u32 = 0,
    garbage_collision: u32 = 0,
    health_collect: u32 = 0,
    parcel_pickup: u32 = 0,
    parcel_register: u32 = 0,
    completion_bonus: u32 = 0,
};

const RowEventDisplayState = enum(u32) {
    inactive = 0,
    staging = 1,
    hold = 2,
    final_delivery = 3,
    bonus_prompt = 4,
    complete = 5,
    final_delivery_delay = 6,
};

const RowEventDisplayController = struct {
    state: RowEventDisplayState = .inactive,
    gate_18: u8 = 0,
    parcel_target_count: u32 = 0,
    bonus_enabled: bool = false,
    staged_parcel_count: u32 = 0,
    delivered_parcel_count: u32 = 0,
    progress: f32 = 0.0,
    progress_step: f32 = 0.0,
    widget_world_x: f32 = 0.0,
    widget_world_y: f32 = 0.0,
    widget_world_z: f32 = 0.0,
    bonus_blink_progress: f32 = 0.0,
    bonus_blink_step: f32 = 0.0,
    bonus_score: u32 = postal_completion_bonus_score,
    display_token: u32 = 0,

    fn configureForRun(self: *RowEventDisplayController, parcel_target: usize, bonus_enabled: bool) void {
        const delivered_parcel_count = self.delivered_parcel_count;
        const staged_parcel_count = self.staged_parcel_count;
        self.* = .{
            .parcel_target_count = @intCast(parcel_target),
            .bonus_enabled = bonus_enabled,
            .staged_parcel_count = staged_parcel_count,
            .delivered_parcel_count = delivered_parcel_count,
            .bonus_score = postal_completion_bonus_score,
            .bonus_blink_step = 1.0,
        };
    }

    fn reconfigureCompletion(self: *RowEventDisplayController, parcel_target: usize, bonus_enabled: bool) void {
        self.parcel_target_count = @intCast(parcel_target);
        self.bonus_enabled = bonus_enabled;
        self.bonus_score = postal_completion_bonus_score;
    }
};

pub const Stopwatch = struct {
    total_seconds: f32 = 0.0,
    minutes: u32 = 0,
    seconds: u32 = 0,
    centiseconds: u32 = 0,
    milliseconds: u32 = 0,
    fractional_seconds: f32 = 0.0,

    pub fn advance(self: *Stopwatch, tick_count: f32) void {
        const delta_seconds = tick_count * (1.0 / 60.0);
        self.total_seconds += delta_seconds;

        var fractional_seconds = self.fractional_seconds + delta_seconds;
        while (fractional_seconds >= 1.0) {
            fractional_seconds -= 1.0;
            self.seconds += 1;
            if (self.seconds >= 60) {
                self.seconds -= 60;
                self.minutes += 1;
            }
        }

        self.fractional_seconds = fractional_seconds;
        self.centiseconds = @intFromFloat(@floor(fractional_seconds * 100.0));
        self.milliseconds = @intFromFloat(@floor(fractional_seconds * 1000.0));
    }

    pub fn elapsedMillis(self: Stopwatch) u32 {
        return @intFromFloat(@round(self.total_seconds * 1000.0));
    }
};

pub const DamageWarningState = enum {
    idle,
    filling,
    draining,

    pub fn label(self: DamageWarningState) []const u8 {
        return switch (self) {
            .idle => "idle",
            .filling => "fill",
            .draining => "drain",
        };
    }
};

pub const JetpackWarningBand = enum {
    idle,
    steady,
    near_empty,

    pub fn label(self: JetpackWarningBand) []const u8 {
        return switch (self) {
            .idle => "idle",
            .steady => "steady",
            .near_empty => "near_empty",
        };
    }
};

pub const JetpackGauge = struct {
    active: bool = false,
    progress: f32 = 0.0,
    warning_intensity: f32 = 0.0,
    pulse_envelope: f32 = 0.0,
    warning_band: JetpackWarningBand = .idle,
    wobble_x: f32 = 0.0,
    wobble_y: f32 = 0.0,
    wobble_alpha: f32 = 0.0,

    pub fn fuelRemaining(self: JetpackGauge) f32 {
        if (!self.active) return 0.0;
        return std.math.clamp(1.0 - self.progress, 0.0, 1.0);
    }
};

// PORT(partial): Windows now confirms the contact-damage controller is the separate
// player +0x3c4 block behind `apply_damage_gauge_delta` / `update_damage_gauge`,
// not the jetpack gauge at +0x2750. A separate +0.02 damage path from another pool
// is still unresolved, so only the identified gameplay hazards are modeled here.
//
// PORT(partial): Windows spawns garbage/salt from a forward row scan over an 8-row
// live strip rather than treating matching runtime tiles as immediate contacts. The
// runner now mirrors that with a spawned-hazard window and the recovered scalar-based
// ambient thresholds, but still omits the original suppressor bits, mode gates, and
// the separate Wall2 ambient pool because the preview does not expose those flags yet.
const health_recover_delta: f32 = -0.5;
const garbage_damage_delta: f32 = 0.04;
const salt_damage_delta: f32 = 0.15;
const slug_damage_delta: f32 = 1.0;
const garbage_speed_scale: f32 = 0.9;
const garbage_lateral_push: f32 = 0.35;
const garbage_collision_distance_threshold: f32 = 0.98;
const salt_collision_distance_threshold: f32 = 0.49;
const runtime_hazard_collision_z_tolerance: f32 = 1.0;
const damage_warning_fill_step: f32 = 0.16666667;
const damage_warning_drain_delta: f32 = -0.0016666667;
const jetpack_gauge_tick_step: f32 = 0.0016666667;
const jetpack_warning_threshold: f32 = 0.94;
const jetpack_auto_shutoff_margin_rows: f32 = 5.0;
const runtime_track_parcel_spawn_ahead_rows: usize = 46;
const runtime_track_parcel_expiry_margin_rows: f32 = 10.0;
const jetpack_warning_phase_scale: f32 = 16.666668;
const runtime_hazard_live_window_rows: usize = 8;
const max_active_track_parcels: usize = 50;
const max_active_runtime_hazards: usize = 128;
const max_active_projectiles: usize = 16;
const max_defeated_slug_cells: usize = 64;
const max_collected_parcel_rows: usize = 1024;
const score_life_threshold: u32 = 50_000;
const postal_completion_bonus_score: u32 = 50_000;
const starting_visible_life_stock: u32 = 3;
const starting_runtime_track_index: usize = 4;
const maximum_visible_life_stock: u32 = 9;
pub const intro_cutscene_duration_ticks: u16 = 240;
pub const completion_cutscene_duration_ticks: u16 = 72;
pub const death_cutscene_duration_ticks: u16 = 72;
const intro_cutscene_hold_ticks: u16 = intro_cutscene_duration_ticks / 2;
const intro_cutscene_blend_ticks: u16 = intro_cutscene_duration_ticks - intro_cutscene_hold_ticks;
const completion_cutscene_blend_ticks: u16 = completion_cutscene_duration_ticks / 2;
const death_cutscene_blend_ticks: u16 = death_cutscene_duration_ticks / 2;
const fall_gravity: f32 = 10.0;
// PORT(partial): bundle 14 only ties the recovered `-7` window to in-fall transition logic,
// not to the final respawn/game-over rule. Keep this as a provisional handoff gate until the
// death/resurrect path is recovered more fully.
const fall_world_y_threshold: f32 = -7.0;
const attachment_exit_progress_step_default: f32 = 1.0 / 60.0;
const attachment_exit_gate_a_progress_threshold: f32 = 0.7;
const attachment_side_exit_margin: f32 = 0.3;
const attachment_entry_start_y_tolerance: f32 = -0.2;
const attachment_entry_end_y_tolerance: f32 = 0.001;
const attachment_entry_rider_height: f32 = 0.49;
const supertramp_launch_velocity_scale: f32 = 12.0;
const supertramp_launch_gravity: f32 = 18.0;
const mouse_steer_lerp_scale: f32 = 12.0;
const lane_lean_duration_seconds: f32 = 0.25;
const lane_lean_amplitude_scale: f32 = 0.05;
const lane_lean_max_amplitude: f32 = 0.08;
const attachment_pre_roll_scale: f32 = 0.35;
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
const completion_cutscene_x_offset: f32 = 0.5;
const death_cutscene_x_offset: f32 = 2.0;
const death_cutscene_y_floor: f32 = 0.0;
const cutscene_target_body_height: f32 = 0.18;
const cutscene_anchor_b_height: f32 = 0.82;
const base_fire_cooldown_ticks: u8 = 10;
const projectile_speed_rows_per_second: f32 = 48.0;
const turret_projectile_speed_rows_per_second: f32 = 20.0;
const turret_fire_interval_seconds: f32 = 1.0;
const turret_projectile_spawn_rows_ahead: usize = 24;
const turret_projectile_hit_z_tolerance: f32 = 0.5;
const turret_projectile_hit_x_tolerance: f32 = 0.6;
const turret_flash_duration_ticks: u8 = 6;
const max_active_turret_states: usize = 64;
const slow_ring_duration_ticks: u16 = 240;
const invincible_duration_ticks: u16 = 480;
const max_weapon_level: u8 = 2;
const slug_projectile_kill_score: u32 = 100;
const cameraman_base_right = rl.Vector3{ .x = 1.0, .y = 0.0, .z = 0.0 };
const cameraman_base_up = rl.Vector3{ .x = 0.0, .y = 0.946145, .z = 0.323752 };
const cameraman_base_forward = rl.Vector3{ .x = 0.0, .y = -0.323752, .z = 0.946145 };
const cameraman_identity_matrix = rl.Matrix{
    .m0 = 1.0,
    .m4 = 0.0,
    .m8 = 0.0,
    .m12 = 0.0,
    .m1 = 0.0,
    .m5 = 1.0,
    .m9 = 0.0,
    .m13 = 0.0,
    .m2 = 0.0,
    .m6 = 0.0,
    .m10 = 1.0,
    .m14 = 0.0,
    .m3 = 0.0,
    .m7 = 0.0,
    .m11 = 0.0,
    .m15 = 1.0,
};
const camera_anchor_local_y: f32 = 0.82;
const camera_anchor_local_z: f32 = 0.4;
const cameraman_base_translation_y: f32 = 1.8;
const cameraman_base_translation_z: f32 = -0.5;
const cameraman_forward_distance: f32 = 3.3;
const cameraman_vertical_lift_early_weight: f32 = 1.15;
const cameraman_vertical_lift_late_weight: f32 = 0.35;
const cameraman_deadzone_min_z_delta: f32 = 1.70000005;
const cameraman_deadzone_max_z_delta: f32 = 3.0;
const cameraman_fov_blend: f32 = 0.3;
const cameraman_attachment_lift_blend: f32 = 0.18;
const cameraman_launch_lift_blend: f32 = 0.18;
const completion_cutscene_start_blend: f32 = 0.5;
const death_cutscene_start_blend: f32 = 0.85;
const native_hotspot_camera_skid_stop_index: u8 = 12;
const native_hotspot_camera_slug_death_index: u8 = 17;
const native_hotspot_camera_intro_talk_index: u8 = 18;
const hotspot_camera_skid_stop_local = rl.Vector3{ .x = -0.54505, .y = 0.0, .z = 1.8749 };
const hotspot_camera_slug_death_local = rl.Vector3{ .x = -0.0088, .y = 0.7189, .z = -5.4915 };
const hotspot_camera_intro_talk_local = rl.Vector3{ .x = 0.862, .y = -0.13765, .z = 1.87215 };

fn shotCooldownTicksForWeaponLevel(weapon_level: u8) u8 {
    return switch (weapon_level) {
        0 => 4,
        1 => 7,
        else => 4,
    };
}

fn projectileSpeedForKind(kind: Projectile.Kind) f32 {
    return switch (kind) {
        .turbo => projectile_speed_rows_per_second,
        .laser => projectile_speed_rows_per_second * 1.15,
        .rocket => projectile_speed_rows_per_second * 0.8,
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

// PORT(partial): Windows attachment-follow is driven by installed runtime attachment
// records plus sampled template geometry. The current port now uses built templates,
// a preview-side installed-row map, and a first geometric entry test, but this state
// is still a Zig-side implementation shape rather than the recovered Windows layout.
const AttachmentFollowState = struct {
    active: bool = false,
    source_row: usize = 0,
    progress: f32 = 0.0,
    exit_overshoot: f32 = 0.0,
    lateral_offset: f32 = 0.0,
    cached_output_lane_center: f32 = 0.5,
    vertical_offset: f32 = 0.0,
    exit_carryover_orientation: f32 = 0.0,
    exit_carryover_scalar: f32 = 0.0,
    cached_output_position: attachment_builders.Vec3 = .{},
};

const AttachmentExitCarryover = struct {
    value_a: f32 = 0.0,
    value_b: f32 = 0.0,
};

const InstalledAttachmentEntry = struct {
    progress: f32,
    lateral_offset: f32,
    vertical_offset: f32,
};

const LaunchState = struct {
    active: bool = false,
    world_x: f32 = 0.0,
    height: f32 = 0.0,
    vertical_velocity: f32 = 0.0,
    basis_forward: attachment_builders.Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    basis_up: attachment_builders.Vec3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
};

const WorldFrame = struct {
    position: rl.Vector3,
    forward: rl.Vector3,
    up: rl.Vector3,
};

const CameraAnchorState = struct {
    world: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

const SnailHotspotState = struct {
    camera_skid_stop: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    camera_slug_death: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    camera_intro_talk: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

const CutsceneCameraController = struct {
    state: u8 = 0,
    matrix: rl.Matrix = cameraman_identity_matrix,
    snap_next: bool = false,
    ticks: u16 = 0,
};

const CameramanState = struct {
    out_matrix: rl.Matrix = cameraman_identity_matrix,
    current_desired_matrix: rl.Matrix = cameraman_identity_matrix,
    previous_desired_matrix: rl.Matrix = cameraman_identity_matrix,
    snap_next: bool = true,
    fov_degrees: f32 = 110.0,
    attachment_lift_accumulator: f32 = 0.0,
    launch_lift_accumulator: f32 = 0.0,
};

fn lerpVector3(a: rl.Vector3, b: rl.Vector3, t: f32) rl.Vector3 {
    return .{
        .x = std.math.lerp(a.x, b.x, t),
        .y = std.math.lerp(a.y, b.y, t),
        .z = std.math.lerp(a.z, b.z, t),
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const length_squared = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    if (length_squared <= 0.000001) {
        return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    }
    const inv_length = @as(f32, 1.0) / @sqrt(length_squared);
    return .{
        .x = v.x * inv_length,
        .y = v.y * inv_length,
        .z = v.z * inv_length,
    };
}

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

fn rotateVectorWorldX(v: rl.Vector3, radians: f32) rl.Vector3 {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return .{
        .x = v.x,
        .y = (v.y * cos_theta) + (v.z * sin_theta),
        .z = (v.z * cos_theta) - (v.y * sin_theta),
    };
}

fn rotateVectorWorldZ(v: rl.Vector3, radians: f32) rl.Vector3 {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return .{
        .x = (v.x * cos_theta) - (v.y * sin_theta),
        .y = (v.x * sin_theta) + (v.y * cos_theta),
        .z = v.z,
    };
}

const CameraTransform = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
};

fn cameraMatrixFromTransform(transform: CameraTransform) rl.Matrix {
    return .{
        .m0 = transform.right.x,
        .m4 = transform.up.x,
        .m8 = transform.forward.x,
        .m12 = transform.position.x,
        .m1 = transform.right.y,
        .m5 = transform.up.y,
        .m9 = transform.forward.y,
        .m13 = transform.position.y,
        .m2 = transform.right.z,
        .m6 = transform.up.z,
        .m10 = transform.forward.z,
        .m14 = transform.position.z,
        .m3 = 0.0,
        .m7 = 0.0,
        .m11 = 0.0,
        .m15 = 1.0,
    };
}

fn cameraTransformFromMatrix(matrix: rl.Matrix) CameraTransform {
    return .{
        .position = .{ .x = matrix.m12, .y = matrix.m13, .z = matrix.m14 },
        .right = .{ .x = matrix.m0, .y = matrix.m1, .z = matrix.m2 },
        .up = .{ .x = matrix.m4, .y = matrix.m5, .z = matrix.m6 },
        .forward = .{ .x = matrix.m8, .y = matrix.m9, .z = matrix.m10 },
    };
}

fn normalizeCameraTransform(transform: CameraTransform) CameraTransform {
    const forward = normalizeVector3(transform.forward);
    var right = crossVector3(transform.up, forward);
    if ((right.x * right.x) + (right.y * right.y) + (right.z * right.z) <= 0.000001) {
        right = normalizeVector3(transform.right);
    } else {
        right = normalizeVector3(right);
    }
    const up = normalizeVector3(crossVector3(forward, right));
    return .{
        .position = transform.position,
        .right = right,
        .up = up,
        .forward = forward,
    };
}

fn rotateCameraTransformWorldX(transform: CameraTransform, radians: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = rotateVectorWorldX(transform.right, radians),
        .up = rotateVectorWorldX(transform.up, radians),
        .forward = rotateVectorWorldX(transform.forward, radians),
    });
}

fn rotateCameraTransformWorldZ(transform: CameraTransform, radians: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = rotateVectorWorldZ(transform.right, radians),
        .up = rotateVectorWorldZ(transform.up, radians),
        .forward = rotateVectorWorldZ(transform.forward, radians),
    });
}

fn rotateCameraTransformLocalZ(transform: CameraTransform, radians: f32) CameraTransform {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = .{
            .x = (transform.right.x * cos_theta) + (transform.up.x * sin_theta),
            .y = (transform.right.y * cos_theta) + (transform.up.y * sin_theta),
            .z = (transform.right.z * cos_theta) + (transform.up.z * sin_theta),
        },
        .up = .{
            .x = (transform.up.x * cos_theta) - (transform.right.x * sin_theta),
            .y = (transform.up.y * cos_theta) - (transform.right.y * sin_theta),
            .z = (transform.up.z * cos_theta) - (transform.right.z * sin_theta),
        },
        .forward = transform.forward,
    });
}

fn blendCameraTransforms(lhs: CameraTransform, rhs: CameraTransform, t: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = lerpVector3(lhs.position, rhs.position, t),
        .right = lerpVector3(lhs.right, rhs.right, t),
        .up = lerpVector3(lhs.up, rhs.up, t),
        .forward = lerpVector3(lhs.forward, rhs.forward, t),
    });
}

fn orthonormalFrameFromForwardUp(forward: rl.Vector3, up_hint: rl.Vector3) CameraTransform {
    const normalized_forward = normalizeVector3(forward);
    var right = crossVector3(up_hint, normalized_forward);
    if ((right.x * right.x) + (right.y * right.y) + (right.z * right.z) <= 0.000001) {
        right = cameraman_base_right;
    } else {
        right = normalizeVector3(right);
    }
    const up = normalizeVector3(crossVector3(normalized_forward, right));
    return .{
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .right = right,
        .up = up,
        .forward = normalized_forward,
    };
}

fn pointCameraTransformAt(position: rl.Vector3, target: rl.Vector3, up_hint: rl.Vector3) CameraTransform {
    var transform = orthonormalFrameFromForwardUp(.{
        .x = target.x - position.x,
        .y = target.y - position.y,
        .z = target.z - position.z,
    }, up_hint);
    transform.position = position;
    return transform;
}

fn cameraMatrixWithPosition(matrix: rl.Matrix, position: rl.Vector3) rl.Matrix {
    var result = matrix;
    result.m12 = position.x;
    result.m13 = position.y;
    result.m14 = position.z;
    return result;
}

fn lookAtPoint(matrix: rl.Matrix, target: rl.Vector3, up_hint: rl.Vector3) rl.Matrix {
    const position = rl.Vector3{
        .x = matrix.m12,
        .y = matrix.m13,
        .z = matrix.m14,
    };
    return cameraMatrixFromTransform(pointCameraTransformAt(position, target, up_hint));
}

fn linearInterpolateCameraMatrices(lhs: rl.Matrix, rhs: rl.Matrix, t: f32) rl.Matrix {
    var lhs_translation: rl.Vector3 = undefined;
    var lhs_rotation: rl.Quaternion = undefined;
    var lhs_scale: rl.Vector3 = undefined;
    rl.math.matrixDecompose(lhs, &lhs_translation, &lhs_rotation, &lhs_scale);

    var rhs_translation: rl.Vector3 = undefined;
    var rhs_rotation: rl.Quaternion = undefined;
    var rhs_scale: rl.Vector3 = undefined;
    rl.math.matrixDecompose(rhs, &rhs_translation, &rhs_rotation, &rhs_scale);

    var result = rl.math.quaternionToMatrix(rl.math.quaternionSlerp(lhs_rotation, rhs_rotation, t));
    result.m12 = std.math.lerp(lhs_translation.x, rhs_translation.x, t);
    result.m13 = std.math.lerp(lhs_translation.y, rhs_translation.y, t);
    result.m14 = std.math.lerp(lhs_translation.z, rhs_translation.z, t);
    return cameraMatrixFromTransform(normalizeCameraTransform(cameraTransformFromMatrix(result)));
}

fn normalizeRadians(radians: f32) f32 {
    var angle = radians;
    while (angle > std.math.pi) angle -= std.math.tau;
    while (angle < -std.math.pi) angle += std.math.tau;
    return angle;
}

fn rollRadiansFromForwardUp(forward: rl.Vector3, up: rl.Vector3) f32 {
    const normalized_forward = normalizeVector3(forward);
    var reference_right = crossVector3(.{ .x = 0.0, .y = 1.0, .z = 0.0 }, normalized_forward);
    if (dotVector3(reference_right, reference_right) <= 0.000001) {
        reference_right = crossVector3(.{ .x = 1.0, .y = 0.0, .z = 0.0 }, normalized_forward);
    }
    reference_right = normalizeVector3(reference_right);
    const reference_up = normalizeVector3(crossVector3(normalized_forward, reference_right));
    const normalized_up = normalizeVector3(up);
    return std.math.atan2(
        dotVector3(normalized_up, reference_right),
        dotVector3(normalized_up, reference_up),
    );
}

fn buildNormalCameramanTransform(translation_x: f32, translation_y: f32, translation_z: f32, intro_pitch_radians: f32, speed_pitch_radians: f32) CameraTransform {
    var transform: CameraTransform = .{
        .position = .{
            .x = translation_x,
            .y = translation_y,
            .z = translation_z,
        },
        .right = cameraman_base_right,
        .up = cameraman_base_up,
        .forward = cameraman_base_forward,
    };
    transform = rotateCameraTransformWorldX(transform, intro_pitch_radians);
    transform = rotateCameraTransformWorldX(transform, speed_pitch_radians);
    return transform;
}

fn cameramanVerticalLift(anchor_y: f32, progress_blend: f32) f32 {
    return std.math.lerp(
        anchor_y * cameraman_vertical_lift_early_weight,
        anchor_y * cameraman_vertical_lift_late_weight,
        progress_blend,
    );
}

fn cameramanPitchRadiansFromAnchorY(anchor_y: f32) f32 {
    return std.math.clamp(
        (-2.0 - ((anchor_y - 0.49) * 5.0)) * 0.0174499992,
        -1.22149992,
        1.22149992,
    );
}

fn clampedPreviousDesiredCameraZ(anchor_z: f32, previous_z: f32) f32 {
    const previous_delta_z = anchor_z - previous_z;
    if (previous_delta_z > cameraman_deadzone_max_z_delta) {
        return anchor_z - cameraman_deadzone_max_z_delta;
    }
    if (previous_delta_z < cameraman_deadzone_min_z_delta) {
        return anchor_z - cameraman_deadzone_min_z_delta;
    }
    return previous_z;
}

pub const Runner = struct {
    session_mode: SessionMode = .debug,
    lane_index: usize = 0,
    resolved_lane_index: usize = 0,
    lane_center: f32 = 0.5,
    runtime_track_index: usize = 0,
    movement_progress: f32 = 0.0,
    movement_rate_scalar: f32 = 0.0,
    row_position: f32 = 0.0,
    previous_row_position: f32 = 0.0,
    speed_rows_per_second: f32 = 12.0,
    paused: bool = false,
    finished: bool = false,
    phase: RunnerPhase = .active,
    cutscene_id: u8 = cutscene_none_id,
    cutscene_ticks: u16 = 0,
    cutscene_camera: CutsceneCameraController = .{},
    pending_handoff: RunnerHandoff = .none,
    completion_handoff_timer: f32 = 0.0,
    completion_handoff_timer_step: f32 = completion_handoff_timer_step,
    completion_handoff_voice_gate: bool = false,
    completion_screen_init_sent: bool = false,
    tick_count: u64 = 0,
    stopwatch: Stopwatch = .{},
    movement_mode: MovementMode = .track,
    current_global_row: usize = 0,
    current_cell: u8 = ' ',
    current_annotation: ?segment.Annotation.Tag = null,
    current_gameplay_cell: ?track.GameplayCellKind = null,
    current_runtime_tile_hint: ?u8 = null,
    current_path_name: ?[]const u8 = null,
    replay_world_x_override: ?f32 = null,
    replay_secondary_lane: ?i32 = null,
    replay_raw_flag_bits: u8 = 0,
    replay_track_state_latch: bool = false,
    replay_fade_requested: bool = false,
    attachment_hint: AttachmentHint = .none,
    attachment_path_name: ?[]const u8 = null,
    attachment_follow: AttachmentFollowState = .{},
    launch: LaunchState = .{},
    attachment_exit_pending: bool = false,
    attachment_exit_anchor_z: f32 = 0.0,
    post_follow_value_a: f32 = 0.0,
    post_follow_value_b: f32 = 0.0,
    attachment_exit_carryover_a: f32 = 0.0,
    attachment_exit_carryover_b: f32 = 0.0,
    attachment_exit_progress: f32 = 0.0,
    attachment_exit_progress_step: f32 = 0.0,
    attachment_exit_gate_a: bool = false,
    attachment_exit_gate_b: bool = false,
    lane_lean_amplitude: f32 = 0.0,
    lane_lean_progress: f32 = 1.0,
    attachment_pre_roll: f32 = 0.0,
    attachment_post_roll: f32 = 0.0,
    heading_roll: f32 = 0.0,
    previous_heading_roll_sample: f32 = 0.0,
    snail_hotspots: SnailHotspotState = .{},
    camera_anchor: CameraAnchorState = .{},
    cameraman: CameramanState = .{},
    attachment_ticks: u64 = 0,
    jetpack: JetpackGauge = .{},
    track_parcel_home_anchor: TrackParcelHomeAnchor = .{},
    path_center_lane: ?f32 = null,
    previous_lane_center: f32 = 0.5,
    traversable_bounds: track.LaneBounds = .{ .min = 0, .max = 0 },
    recent_event: RecentEvent = .none,
    counters: EncounterCounters = .{},
    score: ScoreTotals = .{},
    recent_score_award: u32 = 0,
    recent_score_award_ticks: u8 = 0,
    row_event_display: RowEventDisplayController = .{},
    last_garbage_hit_position: ?rl.Vector3 = null,
    last_salt_hit_position: ?rl.Vector3 = null,
    visible_life_stock: u32 = starting_visible_life_stock,
    weapon_level: u8 = 0,
    slow_ticks: u16 = 0,
    invincible_ticks: u16 = 0,
    shot_cooldown_ticks: u8 = 0,
    damage_gauge: f32 = 0.0,
    slug_hit_active: bool = false,
    damage_warning_state: DamageWarningState = .idle,
    damage_warning_fill: f32 = 0.0,
    last_processed_row: ?usize = null,
    active_track_parcels: [max_active_track_parcels]TrackParcelRuntime = [_]TrackParcelRuntime{.{}} ** max_active_track_parcels,
    last_runtime_parcel_scan_end: usize = 0,
    active_runtime_hazards: [max_active_runtime_hazards]RuntimeHazard = [_]RuntimeHazard{undefined} ** max_active_runtime_hazards,
    active_runtime_hazard_count: usize = 0,
    last_runtime_hazard_scan_end: usize = 0,
    active_projectiles: [max_active_projectiles]Projectile = [_]Projectile{.{}} ** max_active_projectiles,
    active_projectile_count: usize = 0,
    active_turret_states: [max_active_turret_states]TurretState = [_]TurretState{.{ .row = 0, .lane = 0 }} ** max_active_turret_states,
    active_turret_state_count: usize = 0,
    defeated_slug_cells: [max_defeated_slug_cells]RowTarget = [_]RowTarget{.{ .row = 0, .lane = 0 }} ** max_defeated_slug_cells,
    defeated_slug_cell_count: usize = 0,
    collected_parcel_rows: [max_collected_parcel_rows]usize = [_]usize{0} ** max_collected_parcel_rows,
    collected_parcel_row_count: usize = 0,
    math_random_state: u32 = 0,

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
        self.* = .{
            .session_mode = session_mode,
            .speed_rows_per_second = 12.0,
            .row_event_display = .{
                .parcel_target_count = row_event_config.parcel_target_count,
                .bonus_enabled = row_event_config.bonus_enabled,
                .bonus_score = row_event_config.bonus_score,
                .bonus_blink_step = 1.0,
            },
            .visible_life_stock = starting_visible_life_stock,
            .math_random_state = preview.runtime_build_final_random_state,
        };
        if (preview.total_rows > 0) {
            self.runtime_track_index = @min(starting_runtime_track_index, preview.total_rows - 1);
            self.movement_progress = 0.0;
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
        self.last_processed_row = self.current_global_row;
        self.refreshCameraState(preview);
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
            self.pending_handoff = .completion_finalize;
            return;
        }

        if (self.acceptsGameplayInput()) {
            self.previous_row_position = self.row_position;
            self.previous_lane_center = self.lane_center;
            self.applyLaneDelta(input.lane_delta);
            if (input.target_lane_center) |target_lane_center| {
                self.applyTargetLaneCenter(preview, target_lane_center, delta_seconds);
            }
        }

        if (!self.paused and self.acceptsGameplayInput()) {
            self.handleFireInput(preview, input.fire);
            self.movement_rate_scalar = self.effectiveSpeedRowsPerSecond() * delta_seconds;
            self.advanceMovement(preview);
            if (replay.active) {
                self.applyReplayDirective(preview, replay);
                self.applyReplayMovementFlagProgress(preview);
            }
            self.tick_count += 1;
            self.stopwatch.advance(1.0);
        }

        if (!self.paused and self.phase == .active) {
            self.refreshLiveTrackParcels(preview);
        }
        if (!self.paused) {
            self.updateTrackParcels(preview);
            self.updateRowEventDisplay(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.processTrackParcelCollisions(preview);
            self.updateTurretFire(preview, delta_seconds);
            self.updateProjectiles(preview, delta_seconds);
            self.refreshLiveRuntimeHazards(preview);
            self.processRuntimeHazardCollisions(preview);
            self.processVisitedRows(preview);
            self.updateJetpackGauge(preview);
            self.updateDamageWarning();
            self.stepTemporaryStates();
        } else if (!self.paused) {
            self.updatePhaseController(preview, delta_seconds);
        }
        self.endAttachmentIfNeeded(preview);
        if (!self.paused and self.phase == .active) {
            self.stepAttachmentExitState();
        }
        if (!self.paused and self.phase == .active) {
            self.maybeBeginCompletionCutscene(preview);
        }
        if (!self.paused and self.phase == .active) {
            self.updateLaunch(preview, delta_seconds);
        }
        if (!self.paused) {
            self.stepLaneLean(delta_seconds);
        }
        self.refreshSample(preview);
        if (!self.paused and self.phase == .active) {
            self.updateFallEntry(preview);
        }
        if (self.movement_mode == .attachment and self.phase == .active) {
            self.attachment_ticks += 1;
        }
        self.refreshCameraState(preview);
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
        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const position = attachment_builders.worldPositionForTemplate(
                    &built.template,
                    self.attachment_follow.progress,
                    self.attachment_follow.source_row,
                    self.attachment_follow.lateral_offset,
                    self.attachment_follow.vertical_offset + y,
                );
                return .{ .x = position.x, .y = position.y, .z = position.z };
            }
        }
        if (self.launch.active) {
            const floor_y = preview.sampleFloorHeightAtGridPosition(
                self.current_global_row,
                self.resolved_lane_index,
                self.row_position,
            ) orelse 0.0;
            return .{
                .x = self.launch.world_x,
                .y = floor_y + self.launch.height + y,
                .z = self.row_position,
            };
        }
        const floor_y = preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) orelse 0.0;
        var world = preview.worldPositionForLane(self.lane_center, self.row_position, floor_y + y);
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
        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment_follow.progress,
                    self.attachment_follow.source_row,
                    self.attachment_follow.lateral_offset,
                    self.attachment_follow.vertical_offset,
                );
                return .{
                    .x = pose.basis_forward.x,
                    .y = pose.basis_forward.y,
                    .z = pose.basis_forward.z,
                };
            }
        }
        if (self.launch.active) {
            return .{
                .x = self.launch.basis_forward.x,
                .y = self.launch.basis_forward.y,
                .z = self.launch.basis_forward.z,
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
        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const pose = attachment_builders.worldPoseForTemplate(
                    &built.template,
                    self.attachment_follow.progress,
                    self.attachment_follow.source_row,
                    self.attachment_follow.lateral_offset,
                    self.attachment_follow.vertical_offset,
                );
                return .{
                    .x = pose.basis_up.x,
                    .y = pose.basis_up.y,
                    .z = pose.basis_up.z,
                };
            }
        }
        if (self.launch.active) {
            return .{
                .x = self.launch.basis_up.x,
                .y = self.launch.basis_up.y,
                .z = self.launch.basis_up.z,
            };
        }
        return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    }

    pub fn cameramanFovDegrees(self: *const Runner) f32 {
        return self.cameraman.fov_degrees;
    }

    pub fn cameramanMatrix(self: *const Runner) rl.Matrix {
        return self.cameraman.out_matrix;
    }

    pub fn takeCameramanSnap(self: *Runner) bool {
        const snap_next = self.cameraman.snap_next;
        self.cameraman.snap_next = false;
        return snap_next;
    }

    pub fn cutsceneCameraActive(self: *const Runner) bool {
        return self.cutscene_camera.state != 0;
    }

    pub fn cutsceneCameraMatrix(self: *const Runner) rl.Matrix {
        return self.cutscene_camera.matrix;
    }

    pub fn takeCutsceneCameraSnap(self: *Runner) bool {
        const snap_next = self.cutscene_camera.snap_next;
        self.cutscene_camera.snap_next = false;
        return snap_next;
    }

    pub fn replayTrackStateLatched(self: *const Runner) bool {
        return self.replay_track_state_latch;
    }

    pub fn replayRawFlagBits(self: *const Runner) u8 {
        return self.replay_raw_flag_bits;
    }

    pub fn replaySecondaryLane(self: *const Runner) ?i32 {
        return self.replay_secondary_lane;
    }

    pub fn replayFadeRequested(self: *const Runner) bool {
        return self.replay_fade_requested;
    }

    pub fn consumeReplayFadeRequest(self: *Runner) bool {
        const requested = self.replay_fade_requested;
        self.replay_fade_requested = false;
        return requested;
    }

    pub fn introCutsceneBlocksGameplay(self: *const Runner) bool {
        return self.cutscene_id == cutscene_intro_id and self.cutsceneCameraActive();
    }

    pub fn refreshCameraState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.refreshCameraAnchor(preview);
        self.refreshSnailHotspots(preview);
        self.refreshCameraRollState(preview);
        self.updateCameraman(preview);
        self.updateCutsceneCamera(preview);
    }

    pub fn cameramanProgressBlend(self: *const Runner, preview: *const track.LoadedLevelPreview) f32 {
        if (preview.total_rows == 0) return 1.0;
        const total_rows = @as(f32, @floatFromInt(preview.total_rows));
        return std.math.clamp(((self.camera_anchor.world.z / total_rows) * 1.4) - 0.4, 0.0, 1.0);
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
        return self.active_runtime_hazards[0..self.active_runtime_hazard_count];
    }

    pub fn activeTrackParcels(self: *const Runner) []const TrackParcelRuntime {
        return self.active_track_parcels[0..];
    }

    fn nextMathRandomInt15(self: *Runner) u32 {
        self.math_random_state = (self.math_random_state *% 0x343fd) +% 0x269ec3;
        return (self.math_random_state >> 16) & 0x7fff;
    }

    pub fn activeProjectiles(self: *const Runner) []const Projectile {
        return self.active_projectiles[0..self.active_projectile_count];
    }

    pub fn gameplayCellLabel(self: *const Runner) ?[]const u8 {
        const kind = self.current_gameplay_cell orelse return null;
        return kind.label();
    }

    pub fn recentEventLabel(self: *const Runner) []const u8 {
        return self.recent_event.label();
    }

    pub fn activePathName(self: *const Runner) ?[]const u8 {
        return self.attachment_path_name orelse self.current_path_name;
    }

    pub fn runtimeTileHint(self: *const Runner) ?u8 {
        return self.current_runtime_tile_hint;
    }

    pub fn damageWarningLabel(self: *const Runner) []const u8 {
        return self.damage_warning_state.label();
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
        const handoff = self.pending_handoff;
        self.pending_handoff = .none;
        return handoff;
    }

    pub fn configureCompletionBonus(self: *Runner, parcel_target: usize, enabled: bool) void {
        self.row_event_display.configureForRun(parcel_target, enabled);
    }

    pub fn configureSessionMode(self: *Runner, session_mode: SessionMode) void {
        self.session_mode = session_mode;
    }

    pub fn registeredParcelCount(self: *const Runner) u32 {
        return self.row_event_display.delivered_parcel_count;
    }

    pub fn setCutscene(self: *Runner, cutscene_id: u8) void {
        self.cutscene_id = cutscene_id;
        self.cutscene_ticks = 0;
        self.cutscene_camera.ticks = 0;
        self.cutscene_camera.snap_next = cutscene_id != cutscene_none_id;
        self.cutscene_camera.state = switch (cutscene_id) {
            cutscene_intro_id => 1,
            cutscene_completion_id => 5,
            cutscene_death_id => 10,
            else => 0,
        };
    }

    pub fn clearCutscene(self: *Runner) void {
        self.cutscene_id = cutscene_none_id;
        self.cutscene_ticks = 0;
        self.cutscene_camera = .{};
    }

    fn armLaneLean(self: *Runner, lateral_delta: f32) void {
        const scaled_delta = std.math.clamp(
            lateral_delta * lane_lean_amplitude_scale,
            -lane_lean_max_amplitude,
            lane_lean_max_amplitude,
        );
        if (@abs(scaled_delta) <= 0.0001) return;
        self.lane_lean_amplitude = scaled_delta;
        self.lane_lean_progress = 0.0;
    }

    fn stepLaneLean(self: *Runner, delta_seconds: f32) void {
        self.lane_lean_progress = std.math.clamp(
            self.lane_lean_progress + (delta_seconds / lane_lean_duration_seconds),
            0.0,
            1.0,
        );
        if (self.lane_lean_progress >= 0.999) {
            self.lane_lean_amplitude *= 0.8;
            if (@abs(self.lane_lean_amplitude) <= 0.0001) {
                self.lane_lean_amplitude = 0.0;
            }
        }
    }

    fn applyLaneDelta(self: *Runner, lane_delta: i8) void {
        if (lane_delta == 0) return;
        if (self.launch.active) return;
        self.armLaneLean(@floatFromInt(lane_delta));
        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            self.attachment_follow.lateral_offset += @floatFromInt(lane_delta);
            return;
        }
        self.lane_center += @floatFromInt(lane_delta);
        self.lane_index = @as(usize, @intFromFloat(@max(0.0, @floor(self.lane_center - 0.5))));
    }

    fn applyTargetLaneCenter(self: *Runner, preview: *const track.LoadedLevelPreview, raw_target_lane_center: f32, delta_seconds: f32) void {
        if (preview.total_rows == 0 or self.launch.active) return;

        const alpha = std.math.clamp(delta_seconds * mouse_steer_lerp_scale, 0.0, 1.0);
        const min_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.min)) + 0.5;
        const max_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.max)) + 0.5;
        const target_lane_center = std.math.clamp(raw_target_lane_center, min_lane_center, max_lane_center);

        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            if (self.currentAttachmentBuilt(preview)) |built| {
                const centered_position = attachment_builders.worldPositionForTemplate(
                    &built.template,
                    self.attachment_follow.progress,
                    self.attachment_follow.source_row,
                    0.0,
                    self.attachment_follow.vertical_offset,
                );
                const centered_lane_center = laneCenterFromWorldX(preview, centered_position.x);
                const target_lateral_offset = target_lane_center - centered_lane_center;
                const previous_offset = self.attachment_follow.lateral_offset;
                self.attachment_follow.lateral_offset += (target_lateral_offset - self.attachment_follow.lateral_offset) * alpha;
                self.armLaneLean(self.attachment_follow.lateral_offset - previous_offset);
                return;
            }
        }

        const previous_lane_center = self.lane_center;
        self.lane_center += (target_lane_center - self.lane_center) * alpha;
        self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
        self.armLaneLean(self.lane_center - previous_lane_center);
    }

    fn refreshSample(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.traversable_bounds = .{ .min = 0, .max = 0 };
            self.resolved_lane_index = 0;
            self.lane_center = 0.5;
            self.runtime_track_index = 0;
            self.movement_progress = 0.0;
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
            self.attachment_hint = .none;
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
        self.attachment_hint = if (sample.gameplay_cell) |kind|
            switch (kind) {
                .attachment_entry => .entry,
                .attachment_probe => .probe,
                else => returnAttachmentHint(sample.path_center_lane),
            }
        else
            returnAttachmentHint(sample.path_center_lane);
        if (self.attachment_follow.active and self.movement_mode == .attachment) {
            self.lane_center = self.attachment_follow.cached_output_lane_center;
            self.attachment_follow.cached_output_lane_center = self.lane_center;
            self.lane_index = sample.resolved_lane_index;
        } else if (self.replay_world_x_override) |world_x| {
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
            if (self.phase != .active or self.movement_mode != .track or self.launch.active) return;
            const world_x = std.math.clamp(raw_world_x, replay_world_x_min, replay_world_x_max);
            self.replay_world_x_override = world_x;
            self.lane_center = laneCenterFromWorldX(preview, world_x);
            const lane_index = preview.laneIndexAtWorldX(world_x);
            self.lane_index = lane_index;
            self.resolved_lane_index = lane_index;
        }

        self.replay_secondary_lane = replay.secondary_lane;
        self.replay_raw_flag_bits = replay.raw_flag_bits;
        self.replay_track_state_latch = (replay.raw_flag_bits & 0x04) != 0;
        if ((replay.raw_flag_bits & 0x08) != 0) {
            self.replay_fade_requested = true;
        }
    }

    fn applyReplayMovementFlagProgress(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (!self.replay_track_state_latch) return;
        if ((self.replay_raw_flag_bits & 0x01) != 0) {
            self.advanceTrackMovementByRows(preview, 0.3);
        }
        if ((self.replay_raw_flag_bits & 0x02) != 0) {
            self.movement_progress = std.math.clamp(self.movement_rate_scalar, 0.0, 0.999);
            self.syncRowPosition(preview);
        }
    }

    fn currentReplayWorldX(self: *const Runner) ?f32 {
        if (self.phase != .active) return null;
        if (self.movement_mode != .track) return null;
        if (self.launch.active) return null;
        return self.replay_world_x_override;
    }

    fn advanceMovement(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or self.finished) return;

        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            self.advanceAttachmentFollow(preview);
            return;
        }

        self.advanceTrackMovementByRows(preview, self.movement_rate_scalar);
    }

    fn advanceTrackMovementByRows(self: *Runner, preview: *const track.LoadedLevelPreview, step_rows: f32) void {
        if (preview.total_rows == 0 or self.finished) return;
        if (self.movement_mode != .track) return;

        const last_row = preview.total_rows - 1;
        const max_progress: f32 = 0.999;
        var remaining = step_rows;

        while (remaining > 0.0) {
            const progress_limit: f32 = if (self.runtime_track_index >= last_row) max_progress else 1.0;
            const available_progress = progress_limit - self.movement_progress;
            if (available_progress <= 0.0) {
                break;
            }

            if (remaining < available_progress) {
                self.movement_progress += remaining;
                remaining = 0.0;
                break;
            }

            remaining -= available_progress;
            if (self.runtime_track_index >= last_row) {
                self.movement_progress = max_progress;
                remaining = 0.0;
                break;
            }

            self.runtime_track_index += 1;
            self.movement_progress = 0.0;
        }

        self.syncRowPosition(preview);
    }

    fn syncRowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.row_position = 0.0;
            return;
        }

        const last_row = preview.total_rows - 1;
        if (self.runtime_track_index > last_row) {
            self.runtime_track_index = last_row;
            self.movement_progress = 0.999;
        }
        self.row_position = @as(f32, @floatFromInt(self.runtime_track_index)) + self.movement_progress;
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

        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            const target_lane_center = std.math.clamp(
                self.attachment_follow.cached_output_lane_center,
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
        var began_installed_attachment = false;

        if (self.movement_mode != .attachment) {
            began_installed_attachment = self.tryBeginInstalledAttachmentFollow(preview, global_row, sample);
        }

        if (sample.annotation) |annotation| {
            switch (annotation) {
                .path => |path_name| {
                    if (self.movement_mode == .attachment) {
                        self.attachment_path_name = path_name;
                    }
                },
                .ring => |ring_kind| {
                    if (sample.gameplay_cell) |kind| {
                        if (kind == .ring) {
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
        if (self.movement_mode == .attachment or self.launch.active) return;

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
            .attachment_entry => {
                if (self.movement_mode != .attachment and
                    !began_installed_attachment and
                    !preview.installedBuiltAttachmentsAtRow(global_row).any())
                {
                    self.beginAttachmentFollow(preview, sample);
                }
            },
            .ring => {},
            .trampoline => {
                self.counters.trampoline_rows += 1;
                self.recent_event = .trampoline;
            },
            .health => {
                self.counters.health_pickups += 1;
                self.applyDamageGaugeDelta(health_recover_delta);
                self.recent_event = .health_pickup;
            },
            .jetpack => {
                self.counters.jetpack_pickups += 1;
                self.armJetpackGauge();
                self.recent_event = .jetpack_pickup;
            },
            .garbage => {},
            .salt => {},
            .slug => {
                if (self.isSlugDefeated(global_row, sample.resolved_lane_index)) return;
                if (self.invincible_ticks > 0) {
                    self.defeatSlug(global_row, sample.resolved_lane_index);
                    return;
                }
                self.counters.slug_hits += 1;
                self.recent_event = .slug_hit;
                // PORT(partial): Windows first sends slug contact through a dedicated hit/fall
                // branch that clears attachment-follow and enters the death cutscene state; the
                // +1.0 damage-gauge delta appears only on repeated slug contact while already in
                // that state. The runner mirrors that split locally: first hit arms the slug-hit
                // latch and enters the scripted handoff, later contacts add the recovered damage.
                if (self.slug_hit_active) {
                    self.applyDamageGaugeDelta(1.0);
                    return;
                }
                self.slug_hit_active = true;
                self.beginFallState(preview, .hazard, cutscene_death_id);
            },
        }
    }

    fn endAttachmentIfNeeded(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode != .attachment or !self.attachment_follow.active or preview.total_rows == 0) return;
        if (self.currentAttachmentBuilt(preview)) |built| {
            if (self.attachmentShouldSideExit(built)) {
                self.commitAttachmentSideExit(preview, built);
                self.finishAttachmentFollowWithExitHandoff(preview);
                return;
            }
            if (self.attachment_follow.progress >= @as(f32, @floatFromInt(built.template.sample_count))) {
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
                self.slow_ticks = slow_ring_duration_ticks;
            },
        }
        if (ring_kind == .normal or ring_kind == .powerup or ring_kind == .explode) {
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
        for (&self.active_track_parcels) |*parcel| {
            if (!parcel.active() or parcel.state == 1) continue;
            parcel.state = 0;
        }
        while (self.row_event_display.delivered_parcel_count < self.counters.parcels) {
            self.registerParcelDelivery();
        }
        self.row_event_display.state = .inactive;
        self.row_event_display.progress = 0.0;
        self.row_event_display.progress_step = 0.0;
        self.row_event_display.gate_18 = 0;
        self.row_event_display.display_token = 0;
        self.row_event_display.bonus_blink_progress = 0.0;
        self.track_parcel_home_anchor = .{};
    }

    fn recordScore(self: *Runner, slot: *u32, points: u32) void {
        const previous_total = self.score.total;
        slot.* = std.math.add(u32, slot.*, points) catch std.math.maxInt(u32);
        self.score.total = std.math.add(u32, self.score.total, points) catch std.math.maxInt(u32);
        self.recent_score_award = points;
        self.recent_score_award_ticks = 45;
        self.updateVisibleLifeStockFromScore(previous_total, self.score.total);
    }

    fn registerParcelDelivery(self: *Runner) void {
        if (self.row_event_display.delivered_parcel_count == self.row_event_display.parcel_target_count) return;
        self.row_event_display.delivered_parcel_count += 1;
        self.row_event_display.display_token +%= 1;
        self.recordScore(&self.score.parcel_register, 100);
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
        for (&self.active_track_parcels) |*parcel| {
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
            self.track_parcel_home_anchor = .{
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
        for (self.active_track_parcels) |parcel| {
            if (parcel.state == 6 or parcel.state == 7) return true;
        }
        return false;
    }

    fn armRowEventStagingIfNeeded(self: *Runner) void {
        if (!self.hasPendingRowEventParcelStage()) return;
        if (self.hasActiveRowEventDeliveryParcel()) return;
        switch (self.row_event_display.state) {
            .inactive => {
                self.row_event_display.state = .staging;
                self.row_event_display.progress = 0.0;
                self.row_event_display.progress_step = row_event_display_stage_progress_step;
            },
            .staging, .hold, .final_delivery, .bonus_prompt, .complete, .final_delivery_delay => {},
        }
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
        var index: usize = 0;
        while (index < self.active_runtime_hazard_count) {
            const hazard = self.active_runtime_hazards[index];
            const y_offset: f32 = switch (hazard.kind) {
                .garbage => 0.28,
                .salt => 0.18,
            };
            const hazard_position = runtimeCellWorldPosition(preview, hazard.row, hazard.lane, y_offset);
            const delta_x = player_position.x - hazard_position.x;
            const delta_y = player_position.y - hazard_position.y;
            const delta_z = player_position.z - hazard_position.z;
            if (@abs(delta_z) > runtime_hazard_collision_z_tolerance) {
                index += 1;
                continue;
            }
            const distance = @sqrt((delta_x * delta_x) + (delta_y * delta_y) + (delta_z * delta_z));
            const threshold = switch (hazard.kind) {
                .garbage => garbage_collision_distance_threshold,
                .salt => salt_collision_distance_threshold,
            };
            if (distance > threshold) {
                index += 1;
                continue;
            }
            _ = self.consumeRuntimeHazard(hazard.row, hazard.lane, hazard.kind);
            switch (hazard.kind) {
                .garbage => {
                    self.counters.garbage_hits += 1;
                    self.last_garbage_hit_position = hazard_position;
                    self.recordScore(&self.score.garbage_collision, 10);
                    self.applyGarbageImpact(preview, hazard_position);
                    self.applyDamageGaugeDelta(garbage_damage_delta);
                    self.recent_event = .garbage_hit;
                },
                .salt => {
                    self.counters.salt_hits += 1;
                    self.last_salt_hit_position = hazard_position;
                    self.applyDamageGaugeDelta(salt_damage_delta);
                    self.recent_event = .salt_hit;
                },
            }
            return;
        }
    }

    // PORT(partial): Windows garbage collisions do more than apply the +0.04 damage
    // delta. They also knock Goldy sideways and shave current forward speed. The exact
    // velocity fields are still not fully modeled, so the runner applies a conservative
    // equivalent: a one-shot 10% forward-speed loss plus a lateral push away from the
    // impacted lane, with the same effect applied to attachment lateral offset when
    // attached instead of snapping back to lane steps.
    fn applyGarbageImpact(self: *Runner, preview: *const track.LoadedLevelPreview, impact_position: rl.Vector3) void {
        const player_position = self.worldPosition(preview, 0.4);
        const delta_x = player_position.x - impact_position.x;
        const delta_z = player_position.z - impact_position.z;
        const planar_distance = @max(@sqrt((delta_x * delta_x) + (delta_z * delta_z)), 0.0001);
        const delta_x_normalized = delta_x / planar_distance;
        const delta_z_normalized = delta_z / planar_distance;
        const speed_before = self.speed_rows_per_second;

        self.speed_rows_per_second = std.math.clamp(
            speed_before - (@abs(delta_z_normalized) * speed_before * 0.10),
            2.0,
            48.0,
        );

        const lateral_push = (-delta_x_normalized) * garbage_lateral_push *
            std.math.clamp(speed_before / 12.0, 0.5, 2.0);

        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            self.attachment_follow.lateral_offset += lateral_push;
            return;
        }

        const min_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.min)) + 0.5;
        const max_lane_center = @as(f32, @floatFromInt(self.traversable_bounds.max)) + 0.5;
        self.lane_center = std.math.clamp(
            self.lane_center + lateral_push,
            min_lane_center,
            max_lane_center,
        );
        self.lane_index = laneIndexForLaneCenter(preview, self.lane_center);
    }

    fn applyDamageGaugeDelta(self: *Runner, delta: f32) void {
        self.damage_gauge = std.math.clamp(self.damage_gauge + delta, 0.0, 1.0);
        if (self.damage_gauge <= 0.0) {
            self.damage_warning_state = .idle;
            self.damage_warning_fill = 0.0;
        }
    }

    fn maybeAwardRowEventCompletionBonus(self: *Runner) void {
        if (self.score.completion_bonus != 0 or !self.row_event_display.bonus_enabled) return;
        if (self.row_event_display.parcel_target_count == 0 or
            self.row_event_display.delivered_parcel_count < self.row_event_display.parcel_target_count) return;

        self.recordScore(&self.score.completion_bonus, postal_completion_bonus_score);
    }

    // PORT(partial): recovered from Android `cRDamageGuage::AI()`. Filling the gauge enters a
    // warning/fill phase, then a slow auto-drain phase, instead of killing the player directly.
    // This still omits the original game-flag gates, warning actor, and the separate fall-side path.
    fn updateDamageWarning(self: *Runner) void {
        switch (self.damage_warning_state) {
            .idle => {
                if (self.damage_gauge >= 1.0) {
                    self.damage_warning_state = .filling;
                    self.damage_warning_fill = 0.0;
                }
            },
            .filling => {
                self.damage_warning_fill = std.math.clamp(self.damage_warning_fill + damage_warning_fill_step, 0.0, 1.0);
                if (self.damage_warning_fill >= 0.999) {
                    self.damage_warning_state = .draining;
                }
            },
            .draining => {
                self.applyDamageGaugeDelta(damage_warning_drain_delta);
            },
        }
    }

    fn effectiveSpeedRowsPerSecond(self: *const Runner) f32 {
        if (self.slow_ticks > 0) return self.speed_rows_per_second * 0.5;
        return self.speed_rows_per_second;
    }

    fn refreshCameraAnchor(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.camera_anchor = .{};
            return;
        }

        const base_position = self.worldPosition(preview, 0.0);
        const frame = orthonormalFrameFromForwardUp(self.worldForward(preview), self.worldUp(preview));
        self.camera_anchor.world = .{
            .x = base_position.x + (frame.up.x * camera_anchor_local_y) + (frame.forward.x * camera_anchor_local_z),
            .y = base_position.y + (frame.up.y * camera_anchor_local_y) + (frame.forward.y * camera_anchor_local_z),
            .z = base_position.z + (frame.up.z * camera_anchor_local_y) + (frame.forward.z * camera_anchor_local_z),
        };
    }

    fn wantsKind24CameraFovBoost(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        const built = self.currentAttachmentBuilt(preview) orelse return false;
        const runtime_kind = built.template.spec.runtime_kind orelse return false;
        return runtime_kind == 24;
    }

    fn refreshCameraRollState(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.attachment_pre_roll = 0.0;
        self.attachment_post_roll = 0.0;
        self.attachment_follow.exit_carryover_orientation = 0.0;
        self.attachment_follow.exit_carryover_scalar = 0.0;

        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            const surface_roll = rollRadiansFromForwardUp(self.worldForward(preview), self.worldUp(preview));
            const delta_roll = normalizeRadians(surface_roll - self.previous_heading_roll_sample);
            self.previous_heading_roll_sample = surface_roll;
            self.heading_roll = normalizeRadians(self.heading_roll + delta_roll);
            self.attachment_pre_roll = surface_roll * attachment_pre_roll_scale;
            self.attachment_post_roll = surface_roll;
            const carryover = self.attachmentExitCarryoverFromFollow(preview);
            self.attachment_follow.exit_carryover_orientation = carryover.value_a;
            // PORT(partial): Windows latches an attachment-row scalar for exit carryover. Use
            // the live template pose delta here so the exit controller is driven by attachment
            // geometry rather than the old cameraman roll approximation.
            self.attachment_follow.exit_carryover_scalar = carryover.value_b;
            self.attachment_exit_carryover_a = carryover.value_a;
            self.attachment_exit_carryover_b = carryover.value_b;
            return;
        }

        if (self.launch.active) {
            self.previous_heading_roll_sample = rollRadiansFromForwardUp(self.worldForward(preview), self.worldUp(preview));
            return;
        }

        if (self.phase == .fall) return;
        self.previous_heading_roll_sample = 0.0;
    }

    fn bodyFrame(self: *const Runner, preview: *const track.LoadedLevelPreview) CameraTransform {
        var frame = orthonormalFrameFromForwardUp(self.worldForward(preview), self.worldUp(preview));
        frame.position = self.worldPosition(preview, 0.0);
        return frame;
    }

    fn refreshSnailHotspots(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.snail_hotspots = .{};
            return;
        }

        const frame = self.bodyFrame(preview);
        self.snail_hotspots.camera_skid_stop = offsetPosition(
            frame.position,
            frame.right,
            frame.up,
            frame.forward,
            hotspot_camera_skid_stop_local.x,
            hotspot_camera_skid_stop_local.y,
            hotspot_camera_skid_stop_local.z,
        );
        self.snail_hotspots.camera_slug_death = offsetPosition(
            frame.position,
            frame.right,
            frame.up,
            frame.forward,
            hotspot_camera_slug_death_local.x,
            hotspot_camera_slug_death_local.y,
            hotspot_camera_slug_death_local.z,
        );
        self.snail_hotspots.camera_intro_talk = offsetPosition(
            frame.position,
            frame.right,
            frame.up,
            frame.forward,
            hotspot_camera_intro_talk_local.x,
            hotspot_camera_intro_talk_local.y,
            hotspot_camera_intro_talk_local.z,
        );
    }

    fn cutsceneTargetPoint(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Vector3 {
        return self.worldPosition(preview, cutscene_target_body_height);
    }

    fn cutsceneMatrixAtPosition(self: *const Runner, preview: *const track.LoadedLevelPreview, position: rl.Vector3) rl.Matrix {
        return lookAtPoint(
            cameraMatrixWithPosition(self.cameraman.out_matrix, position),
            self.cutsceneTargetPoint(preview),
            self.bodyFrame(preview).up,
        );
    }

    fn introCutsceneMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview) rl.Matrix {
        return self.cutsceneMatrixAtPosition(preview, self.snail_hotspots.camera_intro_talk);
    }

    fn completionCutsceneMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, t: f32) rl.Matrix {
        const start_position = lerpVector3(
            self.snail_hotspots.camera_skid_stop,
            self.snail_hotspots.camera_intro_talk,
            completion_cutscene_start_blend,
        );
        return self.cutsceneMatrixAtPosition(
            preview,
            lerpVector3(start_position, self.snail_hotspots.camera_intro_talk, t),
        );
    }

    fn deathCutsceneMatrix(self: *const Runner, preview: *const track.LoadedLevelPreview, t: f32) rl.Matrix {
        const start_position = lerpVector3(
            self.snail_hotspots.camera_slug_death,
            self.snail_hotspots.camera_intro_talk,
            death_cutscene_start_blend,
        );
        return self.cutsceneMatrixAtPosition(
            preview,
            lerpVector3(start_position, self.snail_hotspots.camera_intro_talk, t),
        );
    }

    fn updateCutsceneCamera(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or self.cutscene_camera.state == 0) return;

        switch (self.cutscene_camera.state) {
            1 => {
                self.cutscene_camera.matrix = self.introCutsceneMatrix(preview);
                self.cutscene_camera.snap_next = true;
                self.cutscene_camera.ticks = 0;
                self.cutscene_ticks = 0;
                self.cutscene_camera.state = 2;
            },
            2 => {
                self.cutscene_camera.matrix = self.introCutsceneMatrix(preview);
                self.cutscene_camera.ticks +|= 1;
                self.cutscene_ticks = @min(self.cutscene_ticks +| 1, intro_cutscene_duration_ticks);
                if (self.cutscene_camera.ticks >= intro_cutscene_hold_ticks) {
                    self.cutscene_camera.state = 8;
                    self.cutscene_camera.ticks = 0;
                }
            },
            8 => {
                const progress = progressForTicks(self.cutscene_camera.ticks, intro_cutscene_blend_ticks);
                const eased = std.math.sin(progress * (std.math.pi / 2.0));
                self.cutscene_camera.matrix = linearInterpolateCameraMatrices(
                    self.introCutsceneMatrix(preview),
                    self.cameraman.out_matrix,
                    eased,
                );
                self.cutscene_camera.ticks +|= 1;
                self.cutscene_ticks = @min(self.cutscene_ticks +| 1, intro_cutscene_duration_ticks);
                if (self.cutscene_camera.ticks >= intro_cutscene_blend_ticks) {
                    self.cutscene_camera.state = 9;
                }
            },
            9 => {
                self.cutscene_camera.matrix = self.cameraman.out_matrix;
                self.clearCutscene();
            },
            5 => {
                self.cutscene_camera.matrix = self.completionCutsceneMatrix(preview, 0.0);
                self.cutscene_camera.snap_next = true;
                self.cutscene_camera.ticks = 0;
                self.cutscene_camera.state = 6;
            },
            6 => {
                const progress = progressForTicks(self.cutscene_camera.ticks, completion_cutscene_blend_ticks);
                const eased = std.math.sin(progress * (std.math.pi / 2.0));
                self.cutscene_camera.matrix = self.completionCutsceneMatrix(preview, eased);
                self.cutscene_camera.ticks +|= 1;
                if (self.cutscene_camera.ticks >= completion_cutscene_blend_ticks) {
                    self.cutscene_camera.state = 7;
                }
            },
            7 => {
                self.cutscene_camera.matrix = self.completionCutsceneMatrix(preview, 1.0);
            },
            10 => {
                self.cutscene_camera.matrix = self.deathCutsceneMatrix(preview, 0.0);
                self.cutscene_camera.snap_next = true;
                self.cutscene_camera.ticks = 0;
                self.cutscene_camera.state = 11;
            },
            11 => {
                const progress = progressForTicks(self.cutscene_camera.ticks, death_cutscene_blend_ticks);
                const eased = std.math.sin(progress * (std.math.pi / 2.0));
                self.cutscene_camera.matrix = self.deathCutsceneMatrix(preview, eased);
                self.cutscene_camera.ticks +|= 1;
                if (self.cutscene_camera.ticks >= death_cutscene_blend_ticks) {
                    self.cutscene_camera.state = 12;
                }
            },
            12 => {
                self.cutscene_camera.matrix = self.deathCutsceneMatrix(preview, 1.0);
            },
            else => {
                self.cutscene_camera.state = 0;
            },
        }
    }

    fn updateCameraman(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.cameraman = .{};
            return;
        }

        const desired_fov: f32 = if (self.wantsKind24CameraFovBoost(preview)) 160.0 else 110.0;
        self.cameraman.fov_degrees += (desired_fov - self.cameraman.fov_degrees) * cameraman_fov_blend;

        const anchor_x = self.camera_anchor.world.x;
        const anchor_y = self.camera_anchor.world.y;
        const anchor_z = self.camera_anchor.world.z;
        const progress_blend = self.cameramanProgressBlend(preview);
        const vertical_lift = cameramanVerticalLift(anchor_y, progress_blend);
        const anchor_pitch_radians = cameramanPitchRadiansFromAnchorY(anchor_y);
        const intro_pitch_radians = (1.0 - progress_blend) * 0.8725;
        const lateral_roll_radians = anchor_x * (-8.0 * 0.0174499992 * 0.170000002);
        const lane_lean_roll_radians =
            (0.5 - (std.math.cos(self.lane_lean_progress * std.math.pi) * 0.5)) *
            self.lane_lean_amplitude *
            std.math.tau;
        const floor_height = preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) orelse 0.0;
        const extra_vertical = @max(self.camera_anchor.world.y - (floor_height + camera_anchor_local_y), 0.0);
        const desired_attachment_lift = if (self.movement_mode == .attachment and self.attachment_follow.active)
            extra_vertical
        else
            0.0;
        const desired_launch_lift = if (self.launch.active) extra_vertical else 0.0;
        self.cameraman.attachment_lift_accumulator +=
            (desired_attachment_lift - self.cameraman.attachment_lift_accumulator) * cameraman_attachment_lift_blend;
        self.cameraman.launch_lift_accumulator +=
            (desired_launch_lift - self.cameraman.launch_lift_accumulator) * cameraman_launch_lift_blend;

        var desired_transform = buildNormalCameramanTransform(
            anchor_x * 0.40000001,
            cameraman_base_translation_y,
            cameraman_base_translation_z,
            intro_pitch_radians,
            anchor_pitch_radians,
        );
        desired_transform.position.x += anchor_x * 0.33333334;
        desired_transform.position.y += vertical_lift +
            self.cameraman.attachment_lift_accumulator +
            self.cameraman.launch_lift_accumulator;
        desired_transform.position.z += anchor_z + 0.4;

        desired_transform = rotateCameraTransformLocalZ(desired_transform, lane_lean_roll_radians + lateral_roll_radians);
        if (self.movement_mode == .attachment and self.attachment_follow.active) {
            desired_transform = rotateCameraTransformLocalZ(desired_transform, self.attachment_pre_roll);
            desired_transform = rotateCameraTransformLocalZ(desired_transform, self.attachment_post_roll);
        }
        if (self.attachment_exit_pending) {
            desired_transform = rotateCameraTransformWorldZ(desired_transform, self.post_follow_value_a);
        }
        desired_transform = rotateCameraTransformLocalZ(desired_transform, self.heading_roll);

        if (self.cameraman.current_desired_matrix.m15 == 1.0 and
            self.cameraman.current_desired_matrix.m0 == 1.0 and
            self.cameraman.current_desired_matrix.m5 == 1.0 and
            self.cameraman.current_desired_matrix.m10 == 1.0 and
            self.cameraman.current_desired_matrix.m12 == 0.0 and
            self.cameraman.current_desired_matrix.m13 == 0.0 and
            self.cameraman.current_desired_matrix.m14 == 0.0 and
            self.tick_count == 0)
        {
            const desired_matrix = cameraMatrixFromTransform(desired_transform);
            self.cameraman.out_matrix = desired_matrix;
            self.cameraman.current_desired_matrix = desired_matrix;
            self.cameraman.previous_desired_matrix = desired_matrix;
            self.cameraman.snap_next = true;
            return;
        }

        var previous_desired_transform = cameraTransformFromMatrix(self.cameraman.previous_desired_matrix);
        previous_desired_transform.position.z = clampedPreviousDesiredCameraZ(anchor_z, previous_desired_transform.position.z);

        const out_transform = blendCameraTransforms(previous_desired_transform, desired_transform, 0.3);
        self.cameraman.out_matrix = cameraMatrixFromTransform(out_transform);
        self.cameraman.current_desired_matrix = cameraMatrixFromTransform(desired_transform);
        self.cameraman.previous_desired_matrix = self.cameraman.current_desired_matrix;
    }

    fn stepTemporaryStates(self: *Runner) void {
        if (self.slow_ticks > 0) self.slow_ticks -= 1;
        if (self.invincible_ticks > 0) self.invincible_ticks -= 1;
        if (self.shot_cooldown_ticks > 0) self.shot_cooldown_ticks -= 1;
        if (self.recent_score_award_ticks > 0) self.recent_score_award_ticks -= 1;
    }

    fn recordPowerupRing(self: *Runner) void {
        if (self.weapon_level < max_weapon_level) {
            self.weapon_level += 1;
            return;
        }
        self.invincible_ticks = invincible_duration_ticks;
    }

    fn triggerExplodeRing(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        var write_index: usize = 0;
        for (0..self.active_runtime_hazard_count) |read_index| {
            const hazard = self.active_runtime_hazards[read_index];
            const row_delta = @abs(@as(i32, @intCast(hazard.row)) - @as(i32, @intCast(self.current_global_row)));
            const lane_delta = @abs(@as(i32, @intCast(hazard.lane)) - @as(i32, @intCast(self.resolved_lane_index)));
            if (hazard.kind == .garbage and row_delta <= 6 and lane_delta <= 2) continue;
            self.active_runtime_hazards[write_index] = hazard;
            write_index += 1;
        }
        self.active_runtime_hazard_count = write_index;

        const start_row = self.current_global_row -| 6;
        const end_row = @min(preview.total_rows, self.current_global_row + 7);
        const gameplay_width = @min(preview.max_width, 8);
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

    fn handleFireInput(self: *Runner, preview: *const track.LoadedLevelPreview, fire: bool) void {
        if (!fire or self.shot_cooldown_ticks != 0) return;
        self.spawnProjectiles(preview);
        self.shot_cooldown_ticks = shotCooldownTicksForWeaponLevel(self.weapon_level);
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
        switch (self.weapon_level) {
            0 => {
                self.spawnProjectile(.turbo, origin.x, origin.y, origin.z, forward.x, forward.y, forward.z);
            },
            1 => {
                self.spawnProjectile(
                    .laser,
                    origin.x - (right.x * 0.35),
                    origin.y - (right.y * 0.35),
                    origin.z - (right.z * 0.35),
                    forward.x,
                    forward.y,
                    forward.z,
                );
                self.spawnProjectile(
                    .laser,
                    origin.x + (right.x * 0.35),
                    origin.y + (right.y * 0.35),
                    origin.z + (right.z * 0.35),
                    forward.x,
                    forward.y,
                    forward.z,
                );
            },
            else => {
                self.spawnProjectile(
                    .rocket,
                    origin.x + (up.x * 0.16) + (forward.x * 0.12),
                    origin.y + (up.y * 0.16) + (forward.y * 0.12),
                    origin.z + (up.z * 0.16) + (forward.z * 0.12),
                    forward.x,
                    forward.y,
                    forward.z,
                );
            },
        }
    }

    fn spawnProjectile(self: *Runner, kind: Projectile.Kind, world_x: f32, world_y: f32, world_z: f32, dir_x: f32, dir_y: f32, dir_z: f32) void {
        var slot_index: ?usize = null;
        for (0..max_active_projectiles) |index| {
            if (!self.active_projectiles[index].active) {
                slot_index = index;
                break;
            }
        }
        const index = slot_index orelse return;
        self.active_projectiles[index] = .{
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
        if (index >= self.active_projectile_count) {
            self.active_projectile_count = index + 1;
        }
    }

    fn updateProjectiles(self: *Runner, preview: *const track.LoadedLevelPreview, delta_seconds: f32) void {
        var write_index: usize = 0;
        for (0..self.active_projectile_count) |read_index| {
            var projectile = self.active_projectiles[read_index];
            if (!projectile.active) continue;
            projectile.world_x += projectile.dir_x * projectile.speed_rows_per_second * delta_seconds;
            projectile.world_y += projectile.dir_y * projectile.speed_rows_per_second * delta_seconds;
            projectile.world_z += projectile.dir_z * projectile.speed_rows_per_second * delta_seconds;
            if (self.resolveProjectileHit(preview, &projectile)) continue;
            if (projectile.kind == .enemy_laser) {
                if (projectile.world_z < self.row_position - 8.0) continue;
            } else if (projectile.world_z > @as(f32, @floatFromInt(preview.total_rows + 8))) continue;
            self.active_projectiles[write_index] = projectile;
            write_index += 1;
        }
        self.active_projectile_count = write_index;
        for (write_index..max_active_projectiles) |index| {
            self.active_projectiles[index].active = false;
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

        if (self.hasRuntimeHazard(global_row, lane_index, .salt)) {
            return true;
        }

        if (self.consumeRuntimeHazard(global_row, lane_index, .garbage)) {
            self.last_garbage_hit_position = runtimeCellWorldPosition(preview, global_row, lane_index, 0.28);
            return true;
        }

        if (self.gameplayCellAt(preview, global_row, lane_index)) |kind| switch (kind) {
            .slug => {
                if (!self.isSlugDefeated(global_row, lane_index) and self.weapon_level > 0) {
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
        const gameplay_width = @min(preview.max_width, 8);
        const width_offset = @as(f32, @floatFromInt(gameplay_width)) * 0.5;
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
                    self.spawnProjectile(
                        .enemy_laser,
                        (@as(f32, @floatFromInt(lane_index)) + 0.5) - width_offset,
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
        self.active_turret_states = next_states;
        self.active_turret_state_count = next_state_count;
    }

    fn findTurretState(self: *const Runner, row: usize, lane: usize) ?TurretState {
        for (0..self.active_turret_state_count) |index| {
            const state = self.active_turret_states[index];
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
        for (0..self.collected_parcel_row_count) |index| {
            if (self.collected_parcel_rows[index] == global_row) return true;
        }
        return false;
    }

    pub fn liveTrackParcelAt(self: *const Runner, global_row: usize) ?TrackParcelRuntime {
        const index = self.findTrackParcelSlotIndex(global_row) orelse return null;
        return self.active_track_parcels[index];
    }

    fn collectParcelRow(self: *Runner, global_row: usize) bool {
        if (self.isParcelCollected(global_row)) return false;
        if (self.collected_parcel_row_count < max_collected_parcel_rows) {
            self.collected_parcel_rows[self.collected_parcel_row_count] = global_row;
            self.collected_parcel_row_count += 1;
        }
        return true;
    }

    fn defeatSlug(self: *Runner, global_row: usize, lane_index: usize) void {
        if (self.isSlugDefeated(global_row, lane_index)) return;
        if (self.defeated_slug_cell_count < max_defeated_slug_cells) {
            self.defeated_slug_cells[self.defeated_slug_cell_count] = .{ .row = global_row, .lane = lane_index };
            self.defeated_slug_cell_count += 1;
        }
        self.recordScore(&self.score.garbage_collision, slug_projectile_kill_score);
    }

    fn findTrackParcelSlotIndex(self: *const Runner, global_row: usize) ?usize {
        for (0..self.active_track_parcels.len) |index| {
            const parcel = self.active_track_parcels[index];
            if (parcel.active() and parcel.row == global_row) return index;
        }
        return null;
    }

    fn allocateTrackParcelSlot(self: *Runner) ?*TrackParcelRuntime {
        for (&self.active_track_parcels) |*parcel| {
            if (!parcel.active()) return parcel;
        }
        return null;
    }

    fn collectLiveTrackParcel(self: *Runner, global_row: usize) void {
        const index = self.findTrackParcelSlotIndex(global_row) orelse return;
        self.active_track_parcels[index].state = 0;
    }

    fn refreshLiveTrackParcels(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;

        const current_row = currentRowIndex(preview, self.row_position);
        const window_start = current_row;
        const window_end = @min(window_start + runtime_track_parcel_spawn_ahead_rows, preview.total_rows);
        if (self.last_runtime_parcel_scan_end < window_start or self.last_runtime_parcel_scan_end > window_end) {
            self.last_runtime_parcel_scan_end = window_start;
        }

        for (self.last_runtime_parcel_scan_end..window_end) |global_row| {
            if (self.isParcelCollected(global_row)) continue;
            const row_location = preview.locateRow(global_row) orelse continue;
            const annotation = row_location.row.annotation orelse continue;
            switch (annotation) {
                .parcel => |parcel| self.spawnLiveTrackParcel(preview, row_location, parcel),
                else => {},
            }
        }
        self.last_runtime_parcel_scan_end = window_end;
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
        for (&self.active_track_parcels) |*parcel| {
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
        return self.track_parcel_home_anchor.world_position;
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

    fn currentRowEventCompletionCellActive(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        const current_sample = self.currentRuntimeSample(preview) orelse return false;
        return preview.runtimeFlagB40At(current_sample.global_row, current_sample.resolved_lane_index);
    }

    // PORT(partial): Windows `update_row_event_display` owns the parcel-delivery widget
    // controller and the post-delivery completion state. The port now mirrors the proven
    // `3 -> 4 -> 5` state path on the gameplay side and uses the rebuilt current-cell
    // completion bit instead of the older authored `'_'` proxy, but it still omits the
    // unresolved widget owner and staged parcel visuals.
    fn stepRowEventBonusPrompt(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.row_event_display.bonus_blink_progress += self.row_event_display.bonus_blink_step;
        if (self.row_event_display.bonus_blink_progress > 1.0) {
            self.row_event_display.bonus_blink_progress = 0.0;
        }
        if (self.currentRowEventCompletionCellActive(preview)) {
            self.row_event_display.state = .complete;
        }
    }

    fn stepRowEventProgress(self: *Runner) bool {
        self.row_event_display.progress = std.math.clamp(
            self.row_event_display.progress + self.row_event_display.progress_step,
            0.0,
            1.0,
        );
        return self.row_event_display.progress >= 1.0;
    }

    fn updateRowEventDisplay(self: *Runner, preview: *const track.LoadedLevelPreview) void {
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
                self.stepRowEventBonusPrompt(preview);
            },
            .bonus_prompt => self.stepRowEventBonusPrompt(preview),
            .final_delivery_delay => {
                if (!self.stepRowEventProgress()) return;
                self.row_event_display.progress = 0.0;
                self.row_event_display.state = .final_delivery;
            },
        }
    }

    fn updateRowEventWidgetWorld(self: *Runner) void {
        const camera_transform = normalizeCameraTransform(cameraTransformFromMatrix(self.cameraman.out_matrix));
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

        var scan_start = @max(window_start, self.last_runtime_hazard_scan_end);
        if (scan_start > window_end) scan_start = window_end;

        var global_row = scan_start;
        while (global_row < window_end) : (global_row += 1) {
            self.scanRuntimeHazardRow(preview, global_row);
        }
        self.last_runtime_hazard_scan_end = window_end;
    }

    fn pruneRuntimeHazards(self: *Runner, window_start: usize, window_end: usize) void {
        var write_index: usize = 0;
        for (0..self.active_runtime_hazard_count) |read_index| {
            const hazard = self.active_runtime_hazards[read_index];
            if (hazard.row < window_start or hazard.row >= window_end) continue;
            self.active_runtime_hazards[write_index] = hazard;
            write_index += 1;
        }
        self.active_runtime_hazard_count = write_index;
    }

    fn scanRuntimeHazardRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const row_location = preview.locateRow(global_row) orelse return;

        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                switch (sample.kind) {
                    .garbage => self.addRuntimeHazard(global_row, lane, .garbage),
                    .salt => self.addRuntimeHazard(global_row, lane, .salt),
                    else => {},
                }
            }

            if (preview.hasGarbageSpawnHintAt(global_row, lane) and shouldSpawnAmbientHazard(global_row, lane, preview.garbage_scalar, .garbage)) {
                self.addRuntimeHazard(global_row, lane, .garbage);
            }
            if (preview.hasSaltSpawnHintAt(global_row, lane) and shouldSpawnAmbientHazard(global_row, lane, preview.salt_scalar, .salt)) {
                self.addRuntimeHazard(global_row, lane, .salt);
            }
        }
    }

    fn addRuntimeHazard(self: *Runner, row: usize, lane: usize, kind: RuntimeHazardKind) void {
        for (0..self.active_runtime_hazard_count) |index| {
            const hazard = self.active_runtime_hazards[index];
            if (hazard.row == row and hazard.lane == lane and hazard.kind == kind) return;
        }
        if (self.active_runtime_hazard_count >= self.active_runtime_hazards.len) return;

        self.active_runtime_hazards[self.active_runtime_hazard_count] = .{
            .row = row,
            .lane = lane,
            .kind = kind,
            .presentation_scale = runtimeHazardPresentationScale(row, lane, kind),
            .presentation_phase = runtimeHazardPresentationPhase(row, lane, kind),
        };
        self.active_runtime_hazard_count += 1;
    }

    fn runtimeHazardPresentationScale(row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
        const seed = runtimeHazardSeed(row, lane, kind);
        const normalized = @as(f32, @floatFromInt(@as(u16, @truncate(seed >> 16)))) / 65535.0;
        return switch (kind) {
            // Android `cRSubGame::AddGarbage` scales garbage with `(RAND(0.4) + 1.0) * 0.6`.
            .garbage => (1.0 + normalized * 0.4) * 0.6,
            .salt => 1.0,
        };
    }

    fn runtimeHazardPresentationPhase(row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
        const seed = runtimeHazardSeed(row, lane, kind);
        const normalized = @as(f32, @floatFromInt(@as(u16, @truncate(seed)))) / 65535.0;
        return normalized * std.math.tau;
    }

    fn runtimeHazardSeed(row: usize, lane: usize, kind: RuntimeHazardKind) u64 {
        var seed: u64 = 0x517cc1b727220a95;
        seed ^= @as(u64, @intCast(row + 1)) *% 0x9e3779b97f4a7c15;
        seed ^= @as(u64, @intCast(lane + 3)) *% 0xbf58476d1ce4e5b9;
        seed ^= (@as(u64, @intFromEnum(kind)) + 1) *% 0x94d049bb133111eb;
        return seed;
    }

    fn hasRuntimeHazard(self: *const Runner, row: usize, lane: usize, kind: RuntimeHazardKind) bool {
        for (0..self.active_runtime_hazard_count) |index| {
            const hazard = self.active_runtime_hazards[index];
            if (hazard.row == row and hazard.lane == lane and hazard.kind == kind) return true;
        }
        return false;
    }

    fn consumeRuntimeHazard(self: *Runner, row: usize, lane: usize, kind: RuntimeHazardKind) bool {
        for (0..self.active_runtime_hazard_count) |index| {
            const hazard = self.active_runtime_hazards[index];
            if (hazard.row != row or hazard.lane != lane or hazard.kind != kind) continue;

            var shift_index = index;
            while (shift_index + 1 < self.active_runtime_hazard_count) : (shift_index += 1) {
                self.active_runtime_hazards[shift_index] = self.active_runtime_hazards[shift_index + 1];
            }
            self.active_runtime_hazard_count -= 1;
            return true;
        }
        return false;
    }

    fn runtimeCellWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
        const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
        return preview.worldPositionForLane(
            @as(f32, @floatFromInt(lane_index)) + 0.5,
            @as(f32, @floatFromInt(global_row)),
            floor_height + y_offset,
        );
    }

    // PORT(partial): Windows `update_jetpack_gauge` at player +0x2750 is a separate
    // timer/warning/shutoff controller from the contact-damage gauge. The runner mirrors
    // the 1/600 countdown, the 0.94 near-empty band, the runtime-cell `flags_b & 0x80`
    // warning snap seeded from `JetPack=Off`, the recovered warning-intensity/wobble fields,
    // and the route-end auto-shutoff, but it still omits lift/fall suppression and the
    // separate weapon-animation side effects behind `set_snail_jetpack`.
    fn updateJetpackGauge(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (!self.jetpack.active) return;

        self.jetpack.progress += jetpack_gauge_tick_step;
        if (self.jetpack.progress > 1.0 or self.rowPositionNearRouteEnd(preview)) {
            self.disarmJetpackGauge();
            return;
        }

        const current_sample = self.currentRuntimeSample(preview);
        const forced_warning = if (current_sample) |sample|
            preview.runtimeFlagB80At(sample.global_row, sample.resolved_lane_index)
        else
            false;

        var warning_phase: f32 = 1.0;
        self.jetpack.warning_band = .steady;

        if (self.jetpack.progress < 0.1) {
            warning_phase = self.jetpack.progress * 10.0;
        } else if (self.jetpack.progress <= jetpack_warning_threshold) {
            if (forced_warning) {
                self.jetpack.progress = jetpack_warning_threshold;
                self.jetpack.warning_band = .near_empty;
            }
            warning_phase = 1.0;
        } else {
            self.jetpack.warning_band = .near_empty;
            warning_phase = std.math.clamp(
                (1.0 - self.jetpack.progress) * jetpack_warning_phase_scale,
                0.0,
                1.0,
            );
        }

        const warning_intensity = 1.0 - ((@cos(warning_phase * std.math.pi) + 1.0) * 0.5);
        self.jetpack.warning_intensity = warning_intensity;
        self.jetpack.pulse_envelope = warning_intensity;
        self.jetpack.wobble_x = @sin(self.jetpack.progress * 25.1327419) * warning_intensity * 0.25;
        self.jetpack.wobble_y = ((@sin(self.jetpack.progress * 37.6991119) * 0.25) + 1.0) * warning_intensity;
        self.jetpack.wobble_alpha = 0.0;
    }

    fn armJetpackGauge(self: *Runner) void {
        self.jetpack = .{
            .active = true,
            .warning_band = .steady,
            .pulse_envelope = 1.0,
        };
    }

    fn disarmJetpackGauge(self: *Runner) void {
        self.jetpack = .{};
    }

    // PORT(partial): Windows enters the death selector once Goldy's world Y falls below -7.0.
    // The runner still does not simulate vertical motion, so it uses a conservative proxy:
    // no sampled floor at the current lane, outside attachment-follow, without an active
    // jetpack, and without the recovered runtime `NoFall` lane set triggers the same direct
    // fall-side death-resolution path. The separate scripted death cutscene remains reserved
    // for hit-side hazards like slug contact.
    fn updateFallEntry(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode == .attachment) return;
        if (self.launch.active) return;
        if (self.jetpack.active) return;
        if (preview.runtimeFlagB01At(self.current_global_row, self.resolved_lane_index)) return;
        if (!rowHasAnyFloor(preview, self.current_global_row)) return;
        if (preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) != null) return;

        self.beginFallState(preview, .fall, cutscene_none_id);
    }

    // PORT(partial): Windows `populate_runtime_track_cells_from_segments` seeds Goldy's
    // visible life stock to 3, and `cRSubGoldy::ScoreAdd` awards one more whenever total
    // score crosses another 50,000-point bucket, capped at 9. Postal respawn consumption is
    // now committed by the runner's death/resurrect handoff, not the app reload path.
    fn updateVisibleLifeStockFromScore(self: *Runner, previous_total: u32, current_total: u32) void {
        const previous_bucket = @divTrunc(previous_total, score_life_threshold);
        const current_bucket = @divTrunc(current_total, score_life_threshold);
        if (current_bucket <= previous_bucket) return;
        const crossed_buckets = current_bucket - previous_bucket;
        const updated_lives = std.math.add(u32, self.visible_life_stock, crossed_buckets) catch std.math.maxInt(u32);
        self.visible_life_stock = @min(maximum_visible_life_stock, updated_lives);
    }

    fn beginCompletionCutscene(self: *Runner) void {
        if (self.phase != .active) return;
        self.finished = true;
        self.phase = .completion_handoff;
        self.completion_handoff_timer = 0.0;
        self.completion_handoff_timer_step = completion_handoff_timer_step;
        self.completion_handoff_voice_gate = false;
        self.completion_screen_init_sent = false;
        self.setCutscene(cutscene_completion_id);
    }

    fn routeEndReached(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (preview.total_rows == 0) return false;
        return self.row_position >= preview.course_end_threshold;
    }

    fn maybeBeginCompletionCutscene(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.attachment_exit_pending) return;
        if (self.movement_mode == .attachment and self.attachment_follow.active) return;
        if (!self.routeEndReached(preview)) return;
        self.beginCompletionCutscene();
    }

    fn completionHandoffRequiresRowEventResolution(self: *const Runner) bool {
        return switch (self.session_mode) {
            .postal, .time_trial => self.row_event_display.parcel_target_count != 0,
            .challenge, .tutorial, .debug => false,
        };
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

        const max_row = @max(@as(f32, @floatFromInt(preview.total_rows)) - 0.001, 0.0);
        const clamped_row_position = std.math.clamp(world_z, 0.0, max_row);
        const runtime_track_index = preview.rowIndexAtWorldZ(clamped_row_position);
        self.runtime_track_index = runtime_track_index;
        self.movement_progress = std.math.clamp(
            clamped_row_position - @as(f32, @floatFromInt(runtime_track_index)),
            0.0,
            0.999,
        );
        self.row_position = clamped_row_position;
        self.lane_center = laneCenterFromWorldX(preview, world_x);
        self.lane_index = preview.laneIndexAtWorldX(world_x);
        self.resolved_lane_index = self.lane_index;
    }

    fn beginFallState(self: *Runner, preview: *const track.LoadedLevelPreview, cause: DeathCause, cutscene_id: u8) void {
        if (self.phase != .active or self.finished) return;
        const frame = self.captureWorldFrame(preview);
        const initial_vertical_velocity = if (self.launch.active) self.launch.vertical_velocity else 0.0;
        if (self.movement_mode == .attachment) {
            self.seedAttachmentExitStateFromCarryover(preview, frame.position.z);
        } else if (self.attachment_exit_pending) {
            self.seedAttachmentExitStateFromCurrentExit(frame.position.z);
        } else if (cause == .fall) {
            self.seedAttachmentExitStateZeroed(frame.position.z);
        }
        self.paused = false;
        self.launch = .{};
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
                _ = self.advanceCutsceneTicks();
                self.completion_handoff_timer += self.completion_handoff_timer_step;
                if (!self.completion_handoff_voice_gate and
                    self.completion_handoff_timer >= completion_handoff_voice_delay_seconds)
                {
                    self.completion_handoff_voice_gate = true;
                }
                if (!self.completion_screen_init_sent and
                    (self.cutscene_camera.state == 5 or self.cutscene_camera.state == 6) and
                    self.completion_handoff_timer >= completion_handoff_timer_step)
                {
                    self.completion_screen_init_sent = true;
                    self.pending_handoff = .completion_screen_init;
                }
                if (self.row_event_display.gate_18 != 0 and
                    self.currentRowEventCompletionCellActive(preview))
                {
                    self.completion_handoff_timer = @max(
                        self.completion_handoff_timer,
                        completion_handoff_release_force_seconds,
                    );
                }
                if (self.row_event_display.state == .complete) {
                    self.completion_handoff_timer = @max(
                        self.completion_handoff_timer,
                        completion_handoff_release_force_seconds,
                    );
                }
                if (self.completion_handoff_timer < completion_handoff_release_seconds) return;
                if (self.completionHandoffRequiresRowEventResolution() and
                    self.row_event_display.state != .complete)
                {
                    self.completion_handoff_timer = @max(
                        0.0,
                        self.completion_handoff_timer - self.completion_handoff_timer_step,
                    );
                    return;
                }
                if (self.pending_handoff != .none) return;
                self.pending_handoff = .completion_finalize;
            },
            .fall => |state| {
                var next_state = state;
                next_state.world_z = self.attachment_exit_anchor_z;
                self.phase = .{ .fall = next_state };
                const cutscene_finished = self.advanceCutsceneTicks();
                self.stepAttachmentExitState();
                switch (next_state.cause) {
                    .fall => {
                        next_state.world_y += next_state.vertical_velocity * delta_seconds;
                        next_state.vertical_velocity -= fall_gravity * delta_seconds;
                        self.phase = .{ .fall = next_state };
                        if (!self.attachment_exit_gate_b and next_state.world_y < fall_world_y_threshold) {
                            self.attachment_exit_gate_b = true;
                        }
                        if (next_state.world_y > fall_world_y_threshold) return;
                    },
                    .hazard, .damage => {
                        if (!cutscene_finished) return;
                    },
                }

                if (self.deathUsesFinalLoss()) {
                    self.pending_handoff = .{ .final_loss = next_state.cause };
                    return;
                }
                if (self.session_mode == .postal and self.visible_life_stock > 0) {
                    self.visible_life_stock -= 1;
                }
                self.pending_handoff = .{ .respawn = next_state.cause };
            },
        }
    }

    fn advanceCutsceneTicks(self: *Runner) bool {
        const duration_ticks = cutsceneDurationTicks(self.cutscene_id) orelse return false;
        if (self.cutscene_ticks >= duration_ticks) return true;
        self.cutscene_ticks +|= 1;
        if (self.cutscene_ticks > duration_ticks) {
            self.cutscene_ticks = duration_ticks;
        }
        return self.cutscene_ticks >= duration_ticks;
    }

    fn stepAttachmentExitState(self: *Runner) void {
        if (!self.attachment_exit_pending) return;
        const progress_step = self.attachment_exit_progress_step;
        self.attachment_exit_progress = std.math.clamp(
            self.attachment_exit_progress + progress_step,
            0.0,
            1.0,
        );
        if (!self.attachment_exit_gate_a and self.attachment_exit_progress > attachment_exit_gate_a_progress_threshold) {
            self.attachment_exit_gate_a = true;
        }
        self.post_follow_value_a = normalizeRadians(self.post_follow_value_a + (self.post_follow_value_b * progress_step));
        if (self.attachment_exit_progress >= 1.0) {
            self.attachment_exit_pending = false;
        }
    }

    fn deathUsesFinalLoss(self: *const Runner) bool {
        return switch (self.session_mode) {
            .postal => self.visible_life_stock == 0,
            .challenge, .time_trial => true,
            .tutorial, .debug => false,
        };
    }

    fn currentAttachmentBuilt(self: *const Runner, preview: *const track.LoadedLevelPreview) ?*const attachment_builders.BuiltAttachment {
        if (!self.attachment_follow.active) return null;
        return preview.builtAttachmentForSourceRow(self.attachment_follow.source_row);
    }

    fn laneCenterFromWorldX(preview: *const track.LoadedLevelPreview, world_x: f32) f32 {
        const gameplay_width = @min(preview.max_width, 8);
        const width_offset = @as(f32, @floatFromInt(gameplay_width)) * 0.5;
        return world_x + width_offset;
    }

    fn laneIndexForLaneCenter(preview: *const track.LoadedLevelPreview, lane_center: f32) usize {
        if (preview.max_width == 0) return 0;
        const centered_lane = std.math.clamp(
            lane_center,
            0.5,
            @as(f32, @floatFromInt(preview.max_width)) - 0.5,
        );
        return @min(
            preview.max_width - 1,
            @as(usize, @intFromFloat(@floor(centered_lane - 0.5))),
        );
    }

    fn trackEntryWorldPosition(preview: *const track.LoadedLevelPreview, row_position: f32, lane_center: f32) attachment_builders.Vec3 {
        const lane_index = laneIndexForLaneCenter(preview, lane_center);
        const global_row = currentRowIndex(preview, row_position);
        const floor_y = preview.sampleFloorHeightAtGridPosition(global_row, lane_index, row_position) orelse 0.0;
        const world_position = preview.worldPositionForLane(lane_center, row_position, floor_y + attachment_entry_rider_height);
        return .{
            .x = world_position.x,
            .y = world_position.y,
            .z = world_position.z,
        };
    }

    fn attachmentLocalPosition(pose: attachment_builders.WorldPose, world_position: attachment_builders.Vec3) attachment_builders.Vec3 {
        const delta = attachment_builders.Vec3.sub(world_position, pose.position);
        return .{
            .x = (delta.x * pose.basis_right.x) + (delta.y * pose.basis_right.y) + (delta.z * pose.basis_right.z),
            .y = (delta.x * pose.basis_up.x) + (delta.y * pose.basis_up.y) + (delta.z * pose.basis_up.z),
            .z = (delta.x * pose.basis_forward.x) + (delta.y * pose.basis_forward.y) + (delta.z * pose.basis_forward.z),
        };
    }

    fn attachmentEntryVerticalOffset(family: attachment_builders.BuilderFamily, local_y: f32) f32 {
        return switch (family) {
            // Windows seeds nonlinear kind-42 follow height from the raw local rider offset.
            // That path legitimately reaches `-0.49` once Goldy is riding the trough floor.
            .kind42 => local_y,
            else => @max(0.0, local_y - attachment_entry_rider_height),
        };
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
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        self.row_position = exit_world_position.z + built.template.exit_tail_extra;
        self.row_position += self.attachment_follow.exit_overshoot;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.movement_progress = self.row_position - @floor(self.row_position);
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
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        const end_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            sample_count_f,
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        const last_delta_length = attachment_builders.deltaLengthAtProgress(&built.template, final_progress);
        const launch_factor = std.math.clamp(self.movement_rate_scalar * last_delta_length, 0.0, 1.0);
        const exit_world_x = self.attachment_follow.cached_output_position.x;
        const exit_lane = preview.laneIndexAtWorldX(exit_world_x);
        const exit_floor_y = preview.sampleFloorHeightAtGridPosition(
            currentRowIndex(preview, end_position.z),
            exit_lane,
            end_position.z,
        ) orelse 0.0;

        self.row_position = end_position.z + built.template.exit_tail_extra + self.attachment_follow.exit_overshoot;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.movement_progress = self.row_position - @floor(self.row_position);
        self.lane_index = exit_lane;
        self.resolved_lane_index = exit_lane;
        self.lane_center = laneCenterFromWorldX(preview, exit_world_x);
        self.launch = .{
            .active = true,
            .world_x = exit_world_x,
            .height = @max(0.6, end_position.y - exit_floor_y),
            .vertical_velocity = @max(0.15, launch_factor) * supertramp_launch_velocity_scale,
            .basis_forward = end_pose.basis_forward,
            .basis_up = end_pose.basis_up,
        };
    }

    fn attachmentShouldSideExit(self: *const Runner, built: *const attachment_builders.BuiltAttachment) bool {
        if (self.attachment_follow.vertical_offset > 0.0) return false;

        const pose = attachment_builders.samplePoseAtProgress(&built.template, self.attachment_follow.progress);
        const local_lateral = @abs(self.attachment_follow.lateral_offset * pose.lateral_scale);
        const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
        return local_lateral > half_width + attachment_side_exit_margin;
    }

    fn commitAttachmentSideExit(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
    ) void {
        const world_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            self.attachment_follow.progress,
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        const clamped_world_x = std.math.clamp(world_pose.position.x, -4.0, 4.0);
        self.row_position = world_pose.position.z;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.movement_progress = self.row_position - @floor(self.row_position);
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
            self.launch = .{
                .active = true,
                .world_x = clamped_world_x,
                .height = exit_height,
                .vertical_velocity = 0.0,
                .basis_forward = world_pose.basis_forward,
                .basis_up = world_pose.basis_up,
            };
        }
    }

    fn updateAttachmentFollowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const built = self.currentAttachmentBuilt(preview) orelse return;
        const position = attachment_builders.worldPositionForTemplate(
            &built.template,
            self.attachment_follow.progress,
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        self.attachment_follow.cached_output_position = position;
        self.row_position = position.z;
        self.runtime_track_index = currentRowIndex(preview, self.row_position);
        self.movement_progress = self.row_position - @floor(self.row_position);
        self.attachment_follow.cached_output_lane_center = laneCenterFromWorldX(preview, position.x);
        self.lane_center = self.attachment_follow.cached_output_lane_center;
        self.resolved_lane_index = preview.laneIndexAtWorldX(position.x);
    }

    fn advanceAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const built = self.currentAttachmentBuilt(preview) orelse {
            self.syncRowPosition(preview);
            return;
        };
        const sample_count: f32 = @floatFromInt(built.template.sample_count);
        const delta_length = attachment_builders.deltaLengthAtProgress(&built.template, self.attachment_follow.progress);
        const advanced_progress = self.attachment_follow.progress + (self.movement_rate_scalar * delta_length);
        self.attachment_follow.exit_overshoot = @max(0.0, advanced_progress - sample_count);
        self.attachment_follow.progress = std.math.clamp(advanced_progress, 0.0, sample_count);
        self.updateAttachmentFollowPosition(preview);
    }

    fn beginAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview, sample: RowSample) void {
        self.launch = .{};
        self.movement_mode = .attachment;
        self.attachment_path_name = sample.path_name;
        self.attachment_follow = .{
            .active = true,
            .source_row = sample.global_row,
            .progress = self.row_position - @floor(self.row_position),
            .exit_overshoot = 0.0,
            .lateral_offset = if (sample.path_center_lane) |path_center_lane|
                self.lane_center - path_center_lane
            else
                0.0,
            .cached_output_lane_center = self.lane_center,
            .vertical_offset = 0.0,
        };
        self.updateAttachmentFollowPosition(preview);
        self.counters.attachments_begun += 1;
        self.recent_event = .attachment_begin;
    }

    fn beginInstalledAttachmentFollow(self: *Runner, preview: *const track.LoadedLevelPreview, built: *const attachment_builders.BuiltAttachment, entry: InstalledAttachmentEntry) void {
        self.launch = .{};
        self.movement_mode = .attachment;
        self.attachment_path_name = built.row.raw_name;

        self.attachment_follow = .{
            .active = true,
            .source_row = built.row.global_row,
            .progress = entry.progress,
            .exit_overshoot = 0.0,
            .lateral_offset = entry.lateral_offset,
            .cached_output_lane_center = self.lane_center,
            .vertical_offset = entry.vertical_offset,
        };
        self.updateAttachmentFollowPosition(preview);
        self.counters.attachments_begun += 1;
        self.recent_event = .attachment_begin;
    }

    fn tryBeginInstalledAttachmentFollow(
        self: *Runner,
        preview: *const track.LoadedLevelPreview,
        global_row: usize,
        sample: RowSample,
    ) bool {
        const installed = preview.installedBuiltAttachmentsAtRow(global_row);
        const candidates = [_]?*const attachment_builders.BuiltAttachment{
            installed.primary,
            installed.secondary,
        };
        for (candidates) |maybe_built| {
            const built = maybe_built orelse continue;
            if (self.installedAttachmentEntry(preview, built, global_row, sample)) |entry| {
                self.beginInstalledAttachmentFollow(preview, built, entry);
                return true;
            }
        }
        return false;
    }

    fn installedAttachmentEntry(
        self: *const Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
        global_row: usize,
        sample: RowSample,
    ) ?InstalledAttachmentEntry {
        if (self.geometricInstalledAttachmentEntry(preview, built, sample)) |entry| {
            return entry;
        }

        if (global_row == built.row.global_row) {
            return self.sourceRowInstalledAttachmentEntry(preview, built, global_row);
        }

        return null;
    }

    fn sourceRowInstalledAttachmentEntry(
        self: *const Runner,
        preview: *const track.LoadedLevelPreview,
        built: *const attachment_builders.BuiltAttachment,
        global_row: usize,
    ) ?InstalledAttachmentEntry {
        const row_progress: f32 = @floatFromInt(global_row - built.row.global_row);
        const row_fraction = std.math.clamp(
            self.row_position - @as(f32, @floatFromInt(global_row)),
            0.0,
            1.0,
        );
        const progress = std.math.clamp(
            row_progress + row_fraction,
            0.0,
            @as(f32, @floatFromInt(built.template.sample_count)),
        );
        const centered_world_position = attachment_builders.worldPositionForTemplate(
            &built.template,
            progress,
            built.row.global_row,
            0.0,
            0.0,
        );
        const centered_lane_center = laneCenterFromWorldX(preview, centered_world_position.x);
        const lateral_offset = self.lane_center - centered_lane_center;
        const entry_world_position = trackEntryWorldPosition(preview, self.row_position, self.lane_center);
        const entry_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            progress,
            built.row.global_row,
            0.0,
            0.0,
        );
        const entry_local = attachmentLocalPosition(entry_pose, entry_world_position);
        const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
        if (@abs(lateral_offset) > half_width + attachment_side_exit_margin) return null;
        return .{
            .progress = progress,
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
        const start_progress = std.math.clamp(
            self.previous_row_position - @as(f32, @floatFromInt(built.row.global_row)),
            0.0,
            @as(f32, @floatFromInt(built.template.sample_count)),
        );
        const end_progress = std.math.clamp(
            self.row_position - @as(f32, @floatFromInt(built.row.global_row)),
            0.0,
            @as(f32, @floatFromInt(built.template.sample_count)),
        );
        if (end_progress <= start_progress) return null;

        const current_lane_center = std.math.clamp(
            self.lane_center,
            @as(f32, @floatFromInt(sample.traversable_bounds.min)) + 0.5,
            @as(f32, @floatFromInt(sample.traversable_bounds.max)) + 0.5,
        );
        const start_world_position = trackEntryWorldPosition(preview, self.previous_row_position, self.previous_lane_center);
        const end_world_position = trackEntryWorldPosition(preview, self.row_position, current_lane_center);
        const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
        const end_index = @min(
            @as(usize, @intFromFloat(@floor(end_progress))),
            @as(usize, built.template.sample_count - 1),
        );
        const start_index = @min(
            @as(usize, @intFromFloat(@floor(start_progress))),
            end_index,
        );

        var candidate_index = end_index;
        while (true) {
            const candidate_progress: f32 = @floatFromInt(candidate_index);
            const candidate_pose = attachment_builders.worldPoseForTemplate(
                &built.template,
                candidate_progress,
                built.row.global_row,
                0.0,
                0.0,
            );
            const start_local = attachmentLocalPosition(candidate_pose, start_world_position);
            const sample_length = attachment_builders.deltaLengthAtProgress(&built.template, candidate_progress);

            if (@abs(start_local.x) <= half_width + attachment_side_exit_margin and
                start_local.y >= attachment_entry_start_y_tolerance and
                start_local.z >= 0.0 and
                start_local.z <= sample_length)
            {
                const end_local = attachmentLocalPosition(candidate_pose, end_world_position);
                if (end_local.y <= attachment_entry_end_y_tolerance) {
                    const sample_fraction = if (sample_length <= 0.0001)
                        0.0
                    else
                        std.math.clamp(start_local.z / sample_length, 0.0, 1.0);
                    const progress = std.math.clamp(
                        candidate_progress + sample_fraction,
                        0.0,
                        @as(f32, @floatFromInt(built.template.sample_count)),
                    );
                    const pose = attachment_builders.samplePoseAtProgress(&built.template, progress);
                    const lateral_offset = if (@abs(pose.lateral_scale) > 0.0001)
                        start_local.x / pose.lateral_scale
                    else
                        start_local.x;
                    return .{
                        .progress = progress,
                        .lateral_offset = lateral_offset,
                        .vertical_offset = attachmentEntryVerticalOffset(built.template.spec.family, start_local.y),
                    };
                }
            }

            if (candidate_index == start_index) break;
            candidate_index -= 1;
        }

        return null;
    }

    fn clearAttachmentFollow(self: *Runner) void {
        self.movement_mode = .track;
        self.attachment_path_name = null;
        self.attachment_follow = .{};
    }

    fn attachmentExitCarryoverFromFollow(self: *const Runner, preview: *const track.LoadedLevelPreview) AttachmentExitCarryover {
        const built = self.currentAttachmentBuilt(preview) orelse {
            return .{
                .value_a = self.attachment_post_roll,
                .value_b = 0.0,
            };
        };

        const current_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            self.attachment_follow.progress,
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );
        const next_progress = @min(
            self.attachment_follow.progress + 1.0,
            @as(f32, @floatFromInt(built.template.sample_count)),
        );
        const next_pose = attachment_builders.worldPoseForTemplate(
            &built.template,
            next_progress,
            self.attachment_follow.source_row,
            self.attachment_follow.lateral_offset,
            self.attachment_follow.vertical_offset,
        );

        const current_roll = rollRadiansFromForwardUp(
            attachmentVec3ToVector3(current_pose.basis_forward),
            attachmentVec3ToVector3(current_pose.basis_up),
        );
        const next_roll = rollRadiansFromForwardUp(
            attachmentVec3ToVector3(next_pose.basis_forward),
            attachmentVec3ToVector3(next_pose.basis_up),
        );
        return .{
            .value_a = current_roll,
            .value_b = normalizeRadians(next_roll - current_roll),
        };
    }

    fn currentAttachmentExitCarryover(self: *const Runner, preview: *const track.LoadedLevelPreview) AttachmentExitCarryover {
        if (self.attachment_follow.active) {
            if (self.attachment_follow.exit_carryover_orientation != 0.0 or
                self.attachment_follow.exit_carryover_scalar != 0.0)
            {
                return .{
                    .value_a = self.attachment_follow.exit_carryover_orientation,
                    .value_b = self.attachment_follow.exit_carryover_scalar,
                };
            }
            return self.attachmentExitCarryoverFromFollow(preview);
        }

        return .{
            .value_a = self.attachment_exit_carryover_a,
            .value_b = self.attachment_exit_carryover_b,
        };
    }

    fn beginAttachmentExitState(self: *Runner, anchor_z: f32) void {
        self.attachment_exit_pending = true;
        self.attachment_exit_anchor_z = anchor_z;
        self.attachment_exit_progress = 0.0;
        self.attachment_exit_progress_step = attachment_exit_progress_step_default;
        self.attachment_exit_gate_a = false;
        self.attachment_exit_gate_b = false;
    }

    fn seedAttachmentExitStateFromCarryover(self: *Runner, preview: *const track.LoadedLevelPreview, anchor_z: f32) void {
        const carryover = if (self.movement_mode == .attachment and self.attachment_follow.active)
            self.currentAttachmentExitCarryover(preview)
        else
            AttachmentExitCarryover{
                .value_a = self.attachment_exit_carryover_a,
                .value_b = self.attachment_exit_carryover_b,
            };
        self.beginAttachmentExitState(anchor_z);
        self.post_follow_value_a = carryover.value_a;
        self.post_follow_value_b = carryover.value_b;
        self.attachment_exit_carryover_a = carryover.value_a;
        self.attachment_exit_carryover_b = carryover.value_b;
        self.previous_heading_roll_sample = rollRadiansFromForwardUp(self.worldForward(preview), self.worldUp(preview));
    }

    fn seedAttachmentExitStateFromCurrentExit(self: *Runner, anchor_z: f32) void {
        const post_follow_value_a = self.post_follow_value_a;
        const post_follow_value_b = self.post_follow_value_b;
        self.beginAttachmentExitState(anchor_z);
        self.post_follow_value_a = post_follow_value_a;
        self.post_follow_value_b = post_follow_value_b;
    }

    fn seedAttachmentExitStateZeroed(self: *Runner, anchor_z: f32) void {
        self.beginAttachmentExitState(anchor_z);
        self.post_follow_value_a = 0.0;
        self.post_follow_value_b = 0.0;
    }

    fn shouldRetireAttachmentDirectlyForCompletion(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (self.launch.active) return false;
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
        if (!self.launch.active) return;

        self.launch.height = @max(0.0, self.launch.height + (self.launch.vertical_velocity * delta_seconds));
        self.launch.vertical_velocity -= supertramp_launch_gravity * delta_seconds;
        self.lane_center = laneCenterFromWorldX(preview, self.launch.world_x);
        self.lane_index = preview.laneIndexAtWorldX(self.launch.world_x);
        self.resolved_lane_index = self.lane_index;

        if (self.launch.height > 0.0 or self.launch.vertical_velocity > 0.0) return;
        self.launch = .{};
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
        const collected_parcel_rows = self.collected_parcel_rows;
        const collected_parcel_row_count = self.collected_parcel_row_count;
        self.reset(preview);
        self.session_mode = session_mode;
        self.score = score;
        self.visible_life_stock = visible_life_stock;
        self.tick_count = tick_count;
        self.stopwatch = stopwatch;
        self.counters.parcels = parcel_count;
        self.row_event_display = row_event_display;
        self.collected_parcel_rows = collected_parcel_rows;
        self.collected_parcel_row_count = collected_parcel_row_count;
    }

    fn rowPositionNearRouteEnd(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (preview.total_rows == 0) return false;
        return self.row_position > preview.course_end_threshold - jetpack_auto_shutoff_margin_rows;
    }
};

fn currentRowIndex(preview: *const track.LoadedLevelPreview, row_position: f32) usize {
    return @intFromFloat(@floor(std.math.clamp(
        row_position,
        0.0,
        @as(f32, @floatFromInt(preview.total_rows - 1)),
    )));
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

fn cutsceneDurationTicks(cutscene_id: u8) ?u16 {
    return switch (cutscene_id) {
        cutscene_intro_id => intro_cutscene_duration_ticks,
        cutscene_completion_id => completion_cutscene_duration_ticks,
        cutscene_death_id => death_cutscene_duration_ticks,
        else => null,
    };
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

fn shouldSpawnAmbientHazard(global_row: usize, lane: usize, scalar: f32, kind: RuntimeHazardKind) bool {
    if (scalar <= 0.0) return false;

    const roll = deterministicRuntimeSpawnRoll(global_row, lane, kind);
    const threshold = switch (kind) {
        .garbage => 0.8 + (0.2 * (1.0 - scalar)),
        .salt => 0.98 + (0.02 * (1.0 - scalar)),
    };
    return roll > threshold;
}

fn deterministicRuntimeSpawnRoll(global_row: usize, lane: usize, kind: RuntimeHazardKind) f32 {
    const kind_bias: u64 = switch (kind) {
        .garbage => 0x9e3779b97f4a7c15,
        .salt => 0xc2b2ae3d27d4eb4f,
    };
    var value = (@as(u64, global_row) << 32) ^ (@as(u64, lane) * 0x9e3779b1) ^ kind_bias;
    value ^= value >> 33;
    value *%= 0xff51afd7ed558ccd;
    value ^= value >> 33;
    value *%= 0xc4ceb9fe1a85ec53;
    value ^= value >> 33;
    const bucket: u32 = @truncate(value & 0xffff);
    return @as(f32, @floatFromInt(bucket)) / 65535.0;
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
    runner.lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    runner.runtime_track_index = target.row - 1;
    runner.movement_progress = 0.99;
    runner.syncRowPosition(preview);
    runner.refreshSample(preview);
    runner.last_processed_row = target.row - 1;
}

fn setRunnerLiveRowTarget(runner: *Runner, target: RowTarget) void {
    runner.lane_index = target.lane;
    runner.lane_center = @as(f32, @floatFromInt(target.lane)) + 0.5;
    runner.row_position = @as(f32, @floatFromInt(target.row)) + 0.01;
}

fn stepUntilHandoff(runner: *Runner, preview: *const track.LoadedLevelPreview, max_steps: usize) usize {
    var steps: usize = 0;
    while (steps < max_steps and runner.pending_handoff == .none) : (steps += 1) {
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

fn laneOutsideAttachmentWidth(
    preview: *const track.LoadedLevelPreview,
    built: *const attachment_builders.BuiltAttachment,
    global_row: usize,
) ?usize {
    const progress: f32 = @floatFromInt(global_row - built.row.global_row);
    const centered = attachment_builders.worldPositionForTemplate(
        &built.template,
        progress,
        built.row.global_row,
        0.0,
        0.0,
    );
    const centered_lane_center = Runner.laneCenterFromWorldX(preview, centered.x);
    const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
    const minimum_offset = half_width + attachment_side_exit_margin + 0.2;

    for (0..preview.max_width) |lane| {
        const lane_center = @as(f32, @floatFromInt(lane)) + 0.5;
        if (@abs(lane_center - centered_lane_center) > minimum_offset) return lane;
    }
    return null;
}

test "cameraman vertical lift weights anchor height early and late" {
    try std.testing.expectApproxEqAbs(@as(f32, 1.15), cameramanVerticalLift(1.0, 0.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.35), cameramanVerticalLift(1.0, 1.0), 0.0001);
    try std.testing.expect(cameramanVerticalLift(1.0, 0.0) > cameramanVerticalLift(1.0, 1.0));
}

test "cameraman deadzone clamps previous desired z around the anchor" {
    try std.testing.expectApproxEqAbs(@as(f32, 9.0), clampedPreviousDesiredCameraZ(12.0, 2.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 10.29999995), clampedPreviousDesiredCameraZ(12.0, 11.5), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 10.0), clampedPreviousDesiredCameraZ(12.0, 10.0), 0.0001);
}

test "template kind 24 alone boosts cameraman fov" {
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

test "runner advances deterministically over fixed time" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    for (0..120) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectApproxEqAbs(@as(f32, 28.0), runner.row_position, 0.001);
    try std.testing.expectEqual(@as(usize, 28), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_rate_scalar, 0.0001);
    try std.testing.expectEqual(@as(u64, 120), runner.tick_count);
}

test "runner keeps discrete track cursor and fractional movement progress" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.step(&preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(usize, 4), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 4.2), runner.row_position, 0.0001);

    for (0..4) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(@as(usize, 5), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.row_position, 0.0001);
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
        if (runner.attachment_hint != .none) {
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
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("health_pickup", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, salt);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.salt_hits);
    try std.testing.expectApproxEqAbs(salt_damage_delta, runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("salt_hit", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.slug_hits);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("slug_hit", runner.recentEventLabel());
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);

    runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, garbage);
    const speed_before_garbage = runner.speed_rows_per_second;
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqual(@as(u32, 10), runner.score.total);
    try std.testing.expectEqual(@as(u32, 10), runner.score.garbage_collision);
    try std.testing.expectApproxEqAbs(garbage_damage_delta, runner.damage_gauge, 0.0001);
    try std.testing.expect(runner.speed_rows_per_second < speed_before_garbage);
    try std.testing.expect(runner.last_garbage_hit_position != null);
    try std.testing.expectEqualStrings("garbage_hit", runner.recentEventLabel());
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
    runner.movement_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(garbage.row, garbage.lane, .garbage);

    try std.testing.expectEqual(@as(usize, 1), runner.activeRuntimeHazards().len);
    runner.processRuntimeHazardCollisions(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 0), runner.activeRuntimeHazards().len);
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
    runner.movement_progress = 0.6;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.addRuntimeHazard(garbage.row, garbage.lane, .garbage);

    const lane_before = runner.lane_center;
    runner.processRuntimeHazardCollisions(&fixture.preview);
    try std.testing.expect(runner.lane_center != lane_before);
}

test "slug hit latches the shared fall path" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);
    try std.testing.expect(runner.slug_hit_active);
}

test "powerup rings upgrade weapon level then grant invincible state" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 1), runner.weapon_level);
    try std.testing.expectEqual(@as(u16, 0), runner.invincible_ticks);

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 2), runner.weapon_level);
    try std.testing.expectEqual(@as(u16, 0), runner.invincible_ticks);

    runner.recordRing(&fixture.preview, .powerup);
    try std.testing.expectEqual(@as(u8, 2), runner.weapon_level);
    try std.testing.expectEqual(invincible_duration_ticks, runner.invincible_ticks);
}

test "slow rings reduce effective speed while active" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner{};
    runner.speed_rows_per_second = 18.0;

    runner.recordRing(&fixture.preview, .slow);
    try std.testing.expectEqual(slow_ring_duration_ticks, runner.slow_ticks);
    try std.testing.expectEqual(@as(u32, 0), runner.score.total);
    try std.testing.expectEqual(@as(u32, 0), runner.score.ring_collect);
    try std.testing.expectApproxEqAbs(@as(f32, 9.0), runner.effectiveSpeedRowsPerSecond(), 0.0001);

    runner.stepTemporaryStates();
    try std.testing.expectEqual(@as(u16, slow_ring_duration_ticks - 1), runner.slow_ticks);
}

test "projectile fire defeats slug after powerup" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.weapon_level = 1;
    const gameplay_width = @min(fixture.preview.max_width, 8);
    const width_offset = @as(f32, @floatFromInt(gameplay_width)) * 0.5;
    const lane_center = @as(f32, @floatFromInt(slug.lane)) + 0.5;
    var projectile: Projectile = .{
        .active = true,
        .world_x = lane_center - width_offset,
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

test "weapon tiers spawn expected projectile families" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 4.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.tutorial);
    runner.reset(&fixture.preview);

    runner.weapon_level = 0;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.active_projectile_count);
    try std.testing.expectEqual(Projectile.Kind.turbo, runner.active_projectiles[0].kind);

    runner.active_projectile_count = 0;
    for (&runner.active_projectiles) |*projectile| projectile.active = false;
    runner.weapon_level = 1;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 2), runner.active_projectile_count);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.active_projectiles[0].kind);
    try std.testing.expectEqual(Projectile.Kind.laser, runner.active_projectiles[1].kind);

    runner.active_projectile_count = 0;
    for (&runner.active_projectiles) |*projectile| projectile.active = false;
    runner.weapon_level = 2;
    runner.spawnProjectiles(&fixture.preview);
    try std.testing.expectEqual(@as(usize, 1), runner.active_projectile_count);
    try std.testing.expectEqual(Projectile.Kind.rocket, runner.active_projectiles[0].kind);
}

test "projectiles stop on salt without consuming the hazard" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 13.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    runner.addRuntimeHazard(salt.row, salt.lane, .salt);

    const gameplay_width = @min(fixture.preview.max_width, 8);
    const width_offset = @as(f32, @floatFromInt(gameplay_width)) * 0.5;
    const lane_center = @as(f32, @floatFromInt(salt.lane)) + 0.5;
    var projectile: Projectile = .{
        .active = true,
        .world_x = lane_center - width_offset,
        .world_y = 0.5,
        .world_z = @as(f32, @floatFromInt(salt.row)) + 0.25,
        .dir_x = 0.0,
        .dir_y = 0.0,
        .dir_z = 1.0,
        .speed_rows_per_second = projectile_speed_rows_per_second,
    };

    try std.testing.expect(runner.resolveProjectileHit(&fixture.preview, &projectile));
    try std.testing.expect(runner.hasRuntimeHazard(salt.row, salt.lane, .salt));
}

test "explode rings defeat nearby slugs and clear nearby garbage only" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 11.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    runner.current_global_row = slug.row;
    runner.resolved_lane_index = slug.lane;
    runner.addRuntimeHazard(slug.row, @min(slug.lane + 1, fixture.preview.max_width - 1), .garbage);
    runner.addRuntimeHazard(slug.row, slug.lane, .salt);

    runner.triggerExplodeRing(&fixture.preview);

    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
    try std.testing.expect(!runner.hasRuntimeHazard(slug.row, @min(slug.lane + 1, fixture.preview.max_width - 1), .garbage));
    try std.testing.expect(runner.hasRuntimeHazard(slug.row, slug.lane, .salt));
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
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
}

test "turret rows spawn enemy laser projectiles" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/TUTORIAL 6.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const turret = findFirstRawCell(&fixture.preview, '=').?;
    primeRunnerBeforeRow(&runner, &fixture.preview, turret);
    runner.updateTurretFire(&fixture.preview, turret_fire_interval_seconds);

    try std.testing.expect(runner.active_projectile_count > 0);
    try std.testing.expectEqual(Projectile.Kind.enemy_laser, runner.active_projectiles[0].kind);
    try std.testing.expect(runner.active_turret_state_count > 0);
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
    try std.testing.expect(runner.active_turret_state_count >= 2);
    for (0..runner.active_turret_state_count) |index| {
        try std.testing.expectEqual(@as(u8, 0), runner.active_turret_states[index].flash_ticks);
    }

    runner.updateTurretFire(&fixture.preview, 0.5);
    var flashing_count: usize = 0;
    for (0..runner.active_turret_state_count) |index| {
        if (runner.active_turret_states[index].flash_ticks > 0) flashing_count += 1;
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
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
}

test "runtime hazards preserve recovered presentation scalars" {
    var runner = Runner{};
    runner.addRuntimeHazard(32, 4, .garbage);
    runner.addRuntimeHazard(48, 1, .salt);

    try std.testing.expectEqual(@as(usize, 2), runner.activeRuntimeHazards().len);
    const garbage = runner.activeRuntimeHazards()[0];
    const salt = runner.activeRuntimeHazards()[1];

    try std.testing.expect(garbage.presentation_scale >= 0.6);
    try std.testing.expect(garbage.presentation_scale <= 0.84);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), salt.presentation_scale, 0.0001);
}

test "invincible slug contact defeats slug instead of entering death" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.invincible_ticks = 30;

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expect(runner.isSlugDefeated(slug.row, slug.lane));
    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqual(@as(u32, slug_projectile_kill_score), runner.score.total);
}

test "full damage enters warning fill and auto-drain" {
    var runner = Runner{};
    runner.damage_gauge = 1.0;

    runner.updateDamageWarning();
    try std.testing.expectEqual(DamageWarningState.filling, runner.damage_warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_warning_fill, 0.0001);

    for (0..6) |_| {
        runner.updateDamageWarning();
    }
    try std.testing.expectEqual(DamageWarningState.draining, runner.damage_warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage_warning_fill, 0.0001);

    const gauge_before_drain = runner.damage_gauge;
    runner.updateDamageWarning();
    try std.testing.expect(runner.damage_gauge < gauge_before_drain);
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
    try std.testing.expectEqual(@as(u32, 50_200), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.parcel_register);
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

    const transform = normalizeCameraTransform(cameraTransformFromMatrix(runner.cameraman.out_matrix));
    const expected = offsetPosition(
        transform.position,
        transform.right,
        transform.up,
        transform.forward,
        row_event_widget_local_x,
        row_event_widget_local_y,
        row_event_widget_local_z,
    );

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectApproxEqAbs(expected.x, runner.row_event_display.widget_world_x, 0.0001);
    try std.testing.expectApproxEqAbs(expected.y, runner.row_event_display.widget_world_y, 0.0001);
    try std.testing.expectApproxEqAbs(expected.z, runner.row_event_display.widget_world_z, 0.0001);
}

test "parcel home flight advances on the pickup frame" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };
    runner.active_track_parcels[0] = .{
        .state = 4,
        .world_position = .{ .x = 5.0, .y = 2.0, .z = 9.0 },
    };

    runner.updateTrackParcels(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 5), runner.active_track_parcels[0].state);
    try std.testing.expectApproxEqAbs(track_parcel_home_progress_step, runner.active_track_parcels[0].progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.active_track_parcels[0].presentationScale(), 0.0001);
}

test "parcel delivery advances on the staging frame" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.widget_world_x = 9.0;
    runner.row_event_display.widget_world_y = 3.0;
    runner.row_event_display.widget_world_z = 14.0;
    runner.active_track_parcels[0] = .{
        .state = 6,
    };

    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };
    runner.updateTrackParcels(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 7), runner.active_track_parcels[0].state);
    try std.testing.expectApproxEqAbs(track_parcel_delivery_progress_step, runner.active_track_parcels[0].progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.active_track_parcels[0].world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.0), runner.active_track_parcels[0].world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), runner.active_track_parcels[0].world_position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), runner.active_track_parcels[0].presentationScale(), 0.0001);
}

test "parcel home flight retires the home-leg slot and arms row event staging" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.counters.parcels = 1;
    runner.row_event_display.parcel_target_count = 2;
    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };

    var parcel = TrackParcelRuntime{
        .state = 5,
        .flight_anchor = runner.track_parcel_home_anchor.world_position,
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
    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };
    runner.row_event_display.state = .staging;
    runner.row_event_display.progress = 1.0;
    runner.row_event_display.progress_step = 0.0;

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 1), runner.row_event_display.staged_parcel_count);
    try std.testing.expectEqual(RowEventDisplayState.hold, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u32, 6), runner.active_track_parcels[0].state);
    try std.testing.expectEqual(std.math.maxInt(usize), runner.active_track_parcels[0].row);
    try std.testing.expectApproxEqAbs(@as(f32, 4.0), runner.active_track_parcels[0].world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), runner.active_track_parcels[0].world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), runner.active_track_parcels[0].world_position.z, 0.0001);
}

test "parcel home flight lifts presentation along the live basis up" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/LOOPBOW.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    runner.movement_mode = .attachment;
    runner.attachment_path_name = "LOOPBOW";
    runner.attachment_follow = .{
        .active = true,
        .source_row = target.row,
        .progress = @as(f32, @floatFromInt(built.template.sample_count)) * 0.25,
    };
    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };
    var parcel = TrackParcelRuntime{
        .state = 5,
        .flight_anchor = runner.track_parcel_home_anchor.world_position,
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
    runner.track_parcel_home_anchor = .{
        .active = true,
        .world_position = .{ .x = 4.0, .y = 5.0, .z = 6.0 },
    };

    var parcel = TrackParcelRuntime{
        .state = 7,
        .flight_anchor = runner.track_parcel_home_anchor.world_position,
        .progress = 0.5,
        .progress_step = 0.0,
        .delivery_offset = .{ .x = 1.0, .y = 2.0, .z = 3.0 },
    };

    const expected = lerpVector3(runner.track_parcel_home_anchor.world_position, .{ .x = 9.0, .y = 3.0, .z = 14.0 }, 0.5);

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
    runner.track_parcel_home_anchor = .{
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
        .flight_anchor = runner.track_parcel_home_anchor.world_position,
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
    try std.testing.expectEqual(@as(u32, 100), runner.score.parcel_register);
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

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectEqual(@as(u32, 2), runner.row_event_display.staged_parcel_count);
    try std.testing.expectEqual(RowEventDisplayState.hold, runner.row_event_display.state);
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

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 0), runner.row_event_display.gate_18);
}

test "final delivery delay promotes into the final delivery state" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.row_event_display.state = .final_delivery_delay;
    runner.row_event_display.progress_step = 1.0;

    runner.updateRowEventDisplay(&fixture.preview);

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
    runner.track_parcel_home_anchor.active = true;
    runner.active_track_parcels[0].state = 5;

    runner.flushPendingParcelDeliveries();

    try std.testing.expectEqual(RowEventDisplayState.inactive, runner.row_event_display.state);
    try std.testing.expectEqual(@as(u8, 0), runner.row_event_display.gate_18);
    try std.testing.expectEqual(@as(u32, 0), runner.row_event_display.display_token);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.row_event_display.progress, 0.0001);
    try std.testing.expect(!runner.track_parcel_home_anchor.active);
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

test "postal death hands off respawn after the death controller finishes with runner-owned life consumption" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.recordScore(&runner.score.ring_collect, 200);
    runner.runtime_track_index = 24;
    runner.movement_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);

    const steps = stepUntilHandoff(&runner, &fixture.preview, 256);
    try std.testing.expect(steps < 256);

    const handoff = runner.consumeHandoff();
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
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
    runner.movement_progress = 0.5;
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
    runner.movement_progress = 0.5;
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
    try std.testing.expectEqual(@as(u32, 50_200), runner.score.total);
    try std.testing.expectEqual(RowEventDisplayState.inactive, runner.row_event_display.state);
    try std.testing.expect(runner.liveTrackParcelAt(parcel.row) == null);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.parcels);
    try std.testing.expectEqual(@as(u32, 50_200), runner.score.total);
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
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
    try std.testing.expectEqual(DeathCause.hazard, handoff.final_loss);
}

test "fall entry clears attachment-follow state and seeds attachment exit fields" {
    var fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment_path_name = "SUPERTRAMP";
    runner.attachment_follow = .{
        .active = true,
        .exit_carryover_orientation = 0.6,
        .exit_carryover_scalar = 0.4,
    };
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.attachment_path_name == null);
    try std.testing.expect(!runner.attachment_follow.active);
    try std.testing.expect(runner.attachment_exit_pending);
    try std.testing.expect(!runner.attachment_exit_gate_a);
    try std.testing.expect(!runner.attachment_exit_gate_b);
    try std.testing.expectApproxEqAbs(@as(f32, 0.6), runner.post_follow_value_a, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), runner.post_follow_value_b, 0.0001);
    try std.testing.expectEqual(cutscene_death_id, runner.cutscene_id);
    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
}

test "latched attachment carryover can reseed the exit handoff after follow clears" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.attachment_exit_carryover_a = 0.6;
    runner.attachment_exit_carryover_b = 0.4;

    runner.seedAttachmentExitStateFromCarryover(&fixture.preview, 12.0);

    try std.testing.expect(runner.attachment_exit_pending);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), runner.attachment_exit_anchor_z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.6), runner.post_follow_value_a, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), runner.post_follow_value_b, 0.0001);
}

test "fall entry preserves current post-follow carryover when exit handoff is already pending" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.attachment_exit_pending = true;
    runner.attachment_exit_progress = 0.5;
    runner.attachment_exit_gate_a = true;
    runner.post_follow_value_a = 0.25;
    runner.post_follow_value_b = 0.5;

    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);

    try std.testing.expect(runner.attachment_exit_pending);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment_exit_progress, 0.0001);
    try std.testing.expect(!runner.attachment_exit_gate_a);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), runner.post_follow_value_a, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), runner.post_follow_value_b, 0.0001);
}

test "on-track hazard death does not arm the attachment exit handoff" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .hazard, cutscene_death_id);

    try std.testing.expect(!runner.attachment_exit_pending);
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

test "lane change lean and lateral steering both feed cameraman roll" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshCameraState(&fixture.preview);
    const baseline = cameraTransformFromMatrix(runner.cameramanMatrix());

    runner.step(&fixture.preview, .{ .lane_delta = 1 }, 1.0 / 60.0);
    const leaned = cameraTransformFromMatrix(runner.cameramanMatrix());

    try std.testing.expect(runner.lane_lean_amplitude > 0.0);
    try std.testing.expect(@abs(leaned.right.y - baseline.right.y) > 0.005);
}

test "fall state keeps Z anchored and advances carried follow roll" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.post_follow_value_a = 0.25;
    runner.post_follow_value_b = 0.5;
    const anchor_z = runner.attachment_exit_anchor_z;

    runner.updatePhaseController(&fixture.preview, 1.0 / 60.0);

    try std.testing.expectApproxEqAbs(anchor_z, runner.phase.fall.world_z, 0.0001);
    try std.testing.expect(runner.post_follow_value_a > 0.25);
}

test "attachment exit progress arms gate a after the recovered threshold" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.attachment_exit_progress = attachment_exit_gate_a_progress_threshold;

    runner.stepAttachmentExitState();

    try std.testing.expect(runner.attachment_exit_gate_a);
}

test "fall state arms gate b at the deep threshold" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginFallState(&fixture.preview, .fall, cutscene_none_id);
    runner.phase.fall.world_y = fall_world_y_threshold - 0.01;

    runner.updatePhaseController(&fixture.preview, 0.0);

    try std.testing.expect(runner.attachment_exit_gate_b);
}

test "attachment exit pending applies a world-Z camera roll" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.refreshCameraState(&fixture.preview);
    const baseline = cameraTransformFromMatrix(runner.cameramanMatrix());

    runner.attachment_exit_pending = true;
    runner.post_follow_value_a = std.math.pi / 6.0;
    runner.refreshCameraState(&fixture.preview);
    const rotated = cameraTransformFromMatrix(runner.cameramanMatrix());

    try std.testing.expectApproxEqAbs(@as(f32, 0.0), baseline.forward.x, 0.0001);
    try std.testing.expect(@abs(rotated.forward.x) > 0.05);
}

test "runner completion enters the delayed handoff controller" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.movement_progress = 0.95;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginCompletionCutscene();

    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene_id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
    try std.testing.expectEqual(@as(f32, 0.0), runner.completion_handoff_timer);
}

test "completion handoff arms at the final row threshold" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.movement_progress = 0.01;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expect(runner.row_position > @as(f32, @floatFromInt(fixture.preview.total_rows - 1)));
    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene_id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
}

test "completion handoff uses the preview course-end threshold" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    fixture.preview.course_end_threshold = 12.5;

    var runner = Runner.init(&fixture.preview);
    runner.row_position = 12.49;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.movement_progress = runner.row_position - @floor(runner.row_position);
    runner.refreshSample(&fixture.preview);
    runner.maybeBeginCompletionCutscene(&fixture.preview);
    try std.testing.expectEqualStrings("active", runner.phaseLabel());

    runner.row_position = 12.5;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.movement_progress = runner.row_position - @floor(runner.row_position);
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
    runner.attachment_path_name = "START";
    runner.attachment_follow = .{
        .active = true,
        .source_row = target.row,
        .progress = @as(f32, @floatFromInt(built.template.sample_count)) - 0.5,
    };
    runner.row_position = @as(f32, @floatFromInt(fixture.preview.total_rows - 1)) + 0.01;

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
}

test "route-end completion waits for attachment exit handoff to clear" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.movement_progress = 0.01;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.attachment_exit_pending = true;
    runner.attachment_exit_progress = 0.0;
    runner.attachment_exit_progress_step = attachment_exit_progress_step_default;

    runner.maybeBeginCompletionCutscene(&fixture.preview);
    try std.testing.expectEqualStrings("active", runner.phaseLabel());

    runner.attachment_exit_progress = 0.99;
    runner.stepAttachmentExitState();
    runner.maybeBeginCompletionCutscene(&fixture.preview);
    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene_id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
}

test "route-end completion can start while parcel delivery registration is still pending" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.movement_progress = 0.01;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.counters.parcels = 1;
    runner.row_event_display.delivered_parcel_count = 0;

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene_id);
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

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
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

    runner.updateRowEventDisplay(&fixture.preview);

    try std.testing.expectEqual(RowEventDisplayState.bonus_prompt, runner.row_event_display.state);
}

test "route-end natural attachment retirement bypasses the exit handoff" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    fixture.preview.total_rows = built.row.global_row + built.template.sample_count + 1;

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment_path_name = "START";
    runner.attachment_follow = .{
        .active = true,
        .source_row = target.row,
        .progress = @floatFromInt(built.template.sample_count),
        .exit_overshoot = 0.999,
    };

    runner.endAttachmentIfNeeded(&fixture.preview);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(!runner.attachment_exit_pending);
    try std.testing.expectEqualStrings("attachment_end", runner.recentEventLabel());

    runner.maybeBeginCompletionCutscene(&fixture.preview);

    try std.testing.expectEqualStrings("completion_handoff", runner.phaseLabel());
    try std.testing.expectEqual(cutscene_completion_id, runner.cutscene_id);
    try std.testing.expectEqual(RunnerHandoff.none, runner.consumeHandoff());
}

test "tutorial completion screen init handoff fires before the late finalize handoff" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginCompletionCutscene();
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.completion_handoff_timer < completion_handoff_release_seconds);
    try std.testing.expectEqual(@as(u8, 6), runner.cutscene_camera.state);
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
    try std.testing.expect(runner.completion_handoff_timer >= completion_handoff_release_seconds);
    try std.testing.expectEqual(RunnerHandoff.completion_finalize, runner.consumeHandoff());
}

test "completion voice gate trips at the native 2.5 second delay" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.beginCompletionCutscene();

    while (runner.completion_handoff_timer < completion_handoff_voice_delay_seconds and !runner.completion_handoff_voice_gate) {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
        _ = runner.consumeHandoff();
    }

    try std.testing.expect(runner.completion_handoff_voice_gate);
    try std.testing.expect(runner.completion_handoff_timer >= completion_handoff_voice_delay_seconds);
}

test "postal completion handoff waits for the row event controller to complete" {
    var fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.session_mode = .postal;
    runner.row_event_display.parcel_target_count = 1;
    runner.row_event_display.state = .bonus_prompt;
    runner.beginCompletionCutscene();
    runner.completion_handoff_timer = completion_handoff_release_seconds;

    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.completion_handoff_timer < completion_handoff_release_force_seconds);

    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.updateRowEventDisplay(&fixture.preview);
    runner.updatePhaseController(&fixture.preview, 0.0);
    try std.testing.expectEqual(RowEventDisplayState.complete, runner.row_event_display.state);
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
    runner.completion_handoff_timer = 1.0;

    const target = findFirstRuntimeFlagB40Cell(&fixture.preview, true).?;
    setRunnerLiveRowTarget(&runner, target);
    runner.updatePhaseController(&fixture.preview, 0.0);

    try std.testing.expectEqual(RunnerHandoff.completion_screen_init, runner.consumeHandoff());
    try std.testing.expect(runner.completion_handoff_timer > completion_handoff_release_seconds);
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
    try std.testing.expect(runner.attachment_follow.active);

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
    try std.testing.expect(runner.attachment_follow.active);
    const built = fixture.preview.installedBuiltAttachmentAtRow(target.row).?;
    const centered = attachment_builders.worldPositionForTemplate(
        &built.template,
        runner.attachment_follow.progress,
        built.row.global_row,
        0.0,
        runner.attachment_follow.vertical_offset,
    );
    const width_offset = @as(f32, @floatFromInt(@min(fixture.preview.max_width, 8))) * 0.5;
    const centered_lane_center = centered.x + width_offset;
    try std.testing.expectApproxEqAbs((@as(f32, @floatFromInt(target.lane)) + 0.5) - centered_lane_center, runner.attachment_follow.lateral_offset, 0.001);
    try std.testing.expectApproxEqAbs(target.path_center_lane, runner.path_center_lane.?, 0.001);
    try std.testing.expect(@abs(runner.lane_center - target.path_center_lane) > 0.1);
    try std.testing.expect((runner.lane_center - centered_lane_center) * runner.attachment_follow.lateral_offset > 0.0);
}

test "standalone start segment attachment follow uses built template world height" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment_follow.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.attachment_follow.vertical_offset, 0.0001);

    const world_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;

    try std.testing.expect(world_position.y > floor_height + 0.5);
    try std.testing.expectApproxEqAbs(world_position.z, runner.row_position, 0.001);
}

test "kind42 entry height preserves the recovered raw local offset" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), Runner.attachmentEntryVerticalOffset(.kind42, 0.0), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.49), Runner.attachmentEntryVerticalOffset(.kind42, -0.49), 0.0001);
}

test "ordinary entry height still subtracts the rider baseline" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), Runner.attachmentEntryVerticalOffset(.start, attachment_entry_rider_height), 0.0001);
}

test "swept installed entry rejects source-row positions before the sample start" {
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
    try std.testing.expect(runner.sourceRowInstalledAttachmentEntry(&fixture.preview, built, target.row) != null);
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
    while (runner.movement_mode == .attachment and runner.attachment_follow.progress < exit_progress) {
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
    runner.attachment_follow.progress = sample_count - 0.1;
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
    runner.attachment_follow.progress = sample_count - 0.1;
    runner.updateAttachmentFollowPosition(&fixture.preview);
    runner.speed_rows_per_second = 48.0;
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.launch.active);

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

test "attachment follow side-exits when lateral drift exceeds template width" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
    const required_lateral = half_width + attachment_side_exit_margin + 0.2;
    const lateral_sign: i8 = if (runner.attachment_follow.lateral_offset < 0.0) -1 else 1;
    const additional_offset = @max(0.0, required_lateral - @abs(runner.attachment_follow.lateral_offset));
    const delta_steps: i8 = @intFromFloat(@ceil(additional_offset));
    const lane_delta: i8 = delta_steps * lateral_sign;
    runner.step(&fixture.preview, .{ .lane_delta = lane_delta }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqualStrings("attachment_end", runner.recentEventLabel());
    try std.testing.expect(runner.row_position >= @as(f32, @floatFromInt(target.row)));
}

test "loop side-exit preserves airborne launch height" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/LOOPBOW.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    var guard: usize = 0;
    while (runner.movement_mode == .attachment and guard < 256) : (guard += 1) {
        const world_position = runner.worldPosition(&fixture.preview, 0.0);
        const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
            runner.current_global_row,
            runner.resolved_lane_index,
            runner.row_position,
        ) orelse 0.0;
        if (world_position.y > floor_height + 1.0) break;
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
    const required_lateral = half_width + attachment_side_exit_margin + 0.2;
    const lateral_sign: i8 = if (runner.attachment_follow.lateral_offset < 0.0) -1 else 1;
    const additional_offset = @max(0.0, required_lateral - @abs(runner.attachment_follow.lateral_offset));
    const delta_steps: i8 = @intFromFloat(@ceil(additional_offset));
    const lane_delta: i8 = delta_steps * lateral_sign;
    runner.step(&fixture.preview, .{ .lane_delta = lane_delta }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.launch.active);

    const launched_position = runner.worldPosition(&fixture.preview, 0.0);
    const floor_height = fixture.preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    try std.testing.expect(launched_position.y > floor_height + 0.5);
}

test "installed attachment entry respects template width" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    const built = fixture.preview.builtAttachmentForSourceRow(target.row).?;
    const outside_lane = laneOutsideAttachmentWidth(&fixture.preview, built, target.row).?;
    primeRunnerBeforeRow(
        &runner,
        &fixture.preview,
        .{
            .row = target.row,
            .lane = outside_lane,
        },
    );

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.attachments_begun);
}

test "continuous target lane center preserves fractional track steering" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.step(&fixture.preview, .{ .target_lane_center = 4.5 }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.lane_center > 4.5);
    try std.testing.expect(runner.lane_center < 5.5);
    try std.testing.expect(@abs(runner.lane_center - (@floor(runner.lane_center) + 0.5)) > 0.05);
}

test "continuous target lane center steers attachment lateral offset" {
    var fixture = try TestFixture.loadSegment("SEGMENTS/START.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const target = findFirstGameplayCell(&fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, target);

    runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);

    const before_offset = runner.attachment_follow.lateral_offset;
    runner.step(&fixture.preview, .{ .target_lane_center = runner.lane_center + 1.5 }, 1.0 / 60.0);

    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment_follow.lateral_offset > before_offset + 0.05);
    try std.testing.expect(@abs(runner.attachment_follow.lateral_offset - @round(runner.attachment_follow.lateral_offset)) > 0.05);
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

test "jetpack gauge enters near-empty warning and auto-shuts off near route end" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.armJetpackGauge();
    runner.jetpack.progress = 0.94;
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expectEqual(JetpackWarningBand.near_empty, runner.jetpack.warning_band);
    try std.testing.expect(runner.jetpack.pulse_envelope > 0.0);
    try std.testing.expect(runner.jetpack.wobble_y > 0.0);

    runner.armJetpackGauge();
    fixture.preview.course_end_threshold = 40.0;
    runner.row_position = 35.1;
    runner.runtime_track_index = currentRowIndex(&fixture.preview, runner.row_position);
    runner.movement_progress = runner.row_position - @floor(runner.row_position);
    runner.refreshSample(&fixture.preview);
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expect(!runner.jetpack.active);
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
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("fall", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.fall, runner.deathCause().?);
    try std.testing.expectEqual(cutscene_none_id, runner.cutscene_id);
}

test "authored no-fall rows suppress the fall death path" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, true).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqualStrings("no_fall", runner.recentEventLabel());
}

test "runtime no-fall lane suppresses fall entry without current annotation state" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, true).?;
    runner.current_global_row = gap.row;
    runner.resolved_lane_index = gap.lane;
    runner.lane_index = gap.lane;
    runner.lane_center = @as(f32, @floatFromInt(gap.lane)) + 0.5;
    runner.row_position = @as(f32, @floatFromInt(gap.row)) + 0.5;
    runner.current_annotation = null;

    runner.updateFallEntry(&fixture.preview);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
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
            .secondary_lane = 321,
            .raw_flag_bits = 0x0c,
        },
        1.0 / 60.0,
    );

    const world = runner.worldPosition(&fixture.preview, 0.82);
    try std.testing.expectApproxEqAbs(@as(f32, -3.25), world.x, 0.0001);
    try std.testing.expectEqual(@as(usize, 0), runner.resolved_lane_index);
    try std.testing.expectEqual(@as(?i32, 321), runner.replaySecondaryLane());
    try std.testing.expectEqual(@as(u8, 0x0c), runner.replayRawFlagBits());
    try std.testing.expect(runner.replayTrackStateLatched());
    try std.testing.expect(runner.replayFadeRequested());
    try std.testing.expect(runner.consumeReplayFadeRequest());
    try std.testing.expect(!runner.consumeReplayFadeRequest());
}

test "replay flag bit 0x1 advances movement through the replay latch" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x05,
        },
        1.0 / 60.0,
    );

    try std.testing.expectApproxEqAbs(@as(f32, 0.5), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(
        @as(f32, @floatFromInt(runner.runtime_track_index)) + runner.movement_progress,
        runner.row_position,
        0.0001,
    );
}

test "replay flag bit 0x2 snaps movement progress to the movement rate scalar" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.movement_progress = 0.6;
    runner.row_position = 0.6;

    runner.stepWithReplay(
        &fixture.preview,
        .{},
        .{
            .active = true,
            .raw_flag_bits = 0x06,
        },
        1.0 / 60.0,
    );

    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_rate_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(
        @as(f32, @floatFromInt(runner.runtime_track_index)) + runner.movement_progress,
        runner.row_position,
        0.0001,
    );
}
