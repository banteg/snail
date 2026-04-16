//! Plain data types used by the gameplay `Runner`. Kept separate so the Runner
//! implementation in `gameplay.zig` does not have to re-declare them.
//!
//! No function here may reference `gameplay.Runner` or any runtime entity
//! module. Moving pure types only.

const std = @import("std");
const segment = @import("../segment.zig");

pub const damage_gauge_pulse_step: f32 = 0.020833334;
pub const damage_gauge_hit_flash_step: f32 = 0.033333335;
pub const damage_warning_transition_step: f32 = 0.16666667;
pub const damage_warning_actor_step: f32 = 0.083333336;
pub const postal_completion_bonus_score: u32 = 50_000;

pub const RunnerInput = struct {
    lane_delta: i8 = 0,
    target_lane_center: ?f32 = null,
    speed_delta_rows_per_second: f32 = 0.0,
    fire_pressed: bool = false,
    fire_down: bool = false,
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

pub const RowEventDisplayState = enum(u32) {
    inactive = 0,
    staging = 1,
    hold = 2,
    final_delivery = 3,
    bonus_prompt = 4,
    complete = 5,
    final_delivery_delay = 6,
};

pub const RowEventDisplayController = struct {
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

    pub fn configureForRun(self: *RowEventDisplayController, parcel_target: usize, bonus_enabled: bool) void {
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

    pub fn reconfigureCompletion(self: *RowEventDisplayController, parcel_target: usize, bonus_enabled: bool) void {
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

pub const DamageWarningActorState = enum(u8) {
    hidden = 0,
    solid = 1,
    fade_cycle = 2,
};

pub const DamageGaugeRuntime = struct {
    display_fill: f32 = 0.0,
    pulse_progress: f32 = 0.0,
    pulse_step: f32 = damage_gauge_pulse_step,
    hit_flash_progress: f32 = 0.0,
    hit_flash_step: f32 = damage_gauge_hit_flash_step,
    warning_transition_progress: f32 = 0.0,
    warning_transition_step: f32 = damage_warning_transition_step,
    skin_hold_ticks: u8 = 0,
};

pub const DamageWarningActor = struct {
    state: DamageWarningActorState = .hidden,
    progress: f32 = 0.0,
    step: f32 = damage_warning_actor_step,
    alpha: f32 = 0.0,
    sample_generation: u8 = 0,
};

// PORT(verified): native `SnailSkinTransitionState` from `change_snail_skin` @ 0x445fd0
// and `update_snail_skin_transition` @ 0x445f80. Slots: 0 = default, 1 = damage-red,
// 2 = invincible. `progress_step = 1 / (duration_s * 60)` when duration > 0, else 0
// (instant swap). When active and progress crosses 1.0, the native transition resets to
// slot 0 (default).
pub const SnailSkinSlot = enum(u8) {
    default = 0,
    damage = 1,
    invincible = 2,
};

pub const SnailSkinTransition = struct {
    selected_slot: SnailSkinSlot = .default,
    active: bool = false,
    progress: f32 = 0.0,
    progress_step: f32 = 0.0,

    pub fn change(self: *SnailSkinTransition, slot: SnailSkinSlot, duration_seconds: f32) void {
        self.active = true;
        self.progress = 0.0;
        self.selected_slot = slot;
        self.progress_step = if (duration_seconds > 0.0)
            1.0 / (duration_seconds * 60.0)
        else
            0.0;
    }

    pub fn tick(self: *SnailSkinTransition) void {
        if (!self.active) return;
        self.progress += self.progress_step;
        if (self.progress <= 1.0) return;
        self.progress = 0.0;
        self.active = false;
        self.selected_slot = .default;
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

pub const WeaponChannelStates = struct {
    left: u8 = 0,
    right: u8 = 0,
    center: u8 = 0,
};

pub fn nativeWeaponChannelStates(movement_flags: u32) WeaponChannelStates {
    return switch (movement_flags) {
        1, 129 => .{ .center = 1 },
        2 => .{ .left = 1, .right = 1 },
        4 => .{ .left = 1, .right = 1, .center = 1 },
        8 => .{ .right = 2 },
        16, 144 => .{ .left = 2, .right = 2 },
        32, 64, 192 => .{ .center = 3 },
        else => .{ .center = 1 },
    };
}
