//! Plain data types used by the gameplay `Runner`. Kept separate so the Runner
//! implementation in `gameplay.zig` does not have to re-declare them.
//!
//! No function here may reference `gameplay.Runner` or any runtime entity
//! module. Moving pure types only.

const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("../attachment_builders.zig");
const segment = @import("../segment.zig");

pub const RunnerInput = struct {
    lane_delta: i8 = 0,
    target_lane_center: ?f32 = null,
    steering_authored_x: ?f32 = null,
    speed_delta_rows_per_second: f32 = 0.0,
    fire_pressed: bool = false,
    fire_down: bool = false,
    toggle_pause: bool = false,
    reset: bool = false,
};

pub const ReplayDirective = struct {
    active: bool = false,
    lateral_world_x: ?f32 = null,
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
    trampoline_bounces: u32 = 0,
    health_pickups: u32 = 0,
    jetpack_pickups: u32 = 0,
    garbage_hits: u32 = 0,
    garbage_smoke_particles: u32 = 0,
    rocket_smoke_particles: u32 = 0,
    salt_hits: u32 = 0,
    slug_hits: u32 = 0,
    no_fall_rows: u32 = 0,
    jetpack_off_rows: u32 = 0,
    ring_normal: u32 = 0,
    ring_powerup: u32 = 0,
    ring_explode: u32 = 0,
    ring_slow: u32 = 0,
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

pub fn formatTimeTrialString(buffer: []u8, elapsed_millis: u32) ![]const u8 {
    // PORT(verified): `format_time_trial_string` (0x448960) returns the
    // zero-time sentinel verbatim, otherwise formats the cRTime minutes,
    // seconds, and centiseconds lanes as `%1i:%02i:%02i`.
    if (elapsed_millis == 0) return std.fmt.bufPrint(buffer, "-:--:--", .{});

    const total_seconds = @divTrunc(elapsed_millis, 1000);
    const minutes = @divTrunc(total_seconds, 60);
    const seconds = @mod(total_seconds, 60);
    const centiseconds = @divTrunc(@mod(elapsed_millis, 1000), 10);
    return std.fmt.bufPrint(buffer, "{d}:{d:0>2}:{d:0>2}", .{ minutes, seconds, centiseconds });
}

test "time trial string mirrors native format helper" {
    var buffer: [32]u8 = undefined;

    try std.testing.expectEqualStrings("-:--:--", try formatTimeTrialString(&buffer, 0));
    try std.testing.expectEqualStrings("0:01:50", try formatTimeTrialString(&buffer, 1500));
    try std.testing.expectEqualStrings("1:31:23", try formatTimeTrialString(&buffer, 91_230));
}

// Damage gauge / warning-actor types live in `gameplay/damage.zig`.
// Snail skin and weapon-presentation types live in `gameplay/presentation.zig`.

// PORT(verified): native cutscene/presentation animation ids consumed by
// `dispatch_cutscene_animation`
// (`artifacts/ida/functions/00444600-dispatch_cutscene_animation.c`). Native
// passes these as the `a2` argument and uses them to index the
// presentation controller's 128-byte-stride `animation_slot_table` at
// `presentation + 0x170`. The family keys map 1:1 to the shipped
// `X/_ANIMATION.TXT` `Anim:turbo-*-000.x` entries. Native callsites recover
// ids 1/3/4/5/6/7/8/9 directly; id 2 is conservative from the shipped load
// and animation-file order (`turbo-move` before `turbo-bobalong`).
pub const AnimClipId = enum(u8) {
    none = 0,
    base = 1,
    move = 2,
    lookback_l = 3,
    lookback_r = 4,
    skidstop = 5,
    damaged = 6,
    intoshell = 7,
    fall = 8,
    talk = 9,

    pub fn familyKey(self: AnimClipId) ?[]const u8 {
        return switch (self) {
            .none => null,
            .base => "TURBO-BASE",
            .move => "TURBO-MOVE",
            .lookback_l => "TURBO-LOOKBACKLEFT",
            .lookback_r => "TURBO-LOOKBACKRIGHT",
            .skidstop => "TURBO-SKIDSTOP",
            .damaged => "TURBO-DAMAGED",
            .intoshell => "TURBO-INTOSHELL",
            .fall => "TURBO-FALL",
            .talk => "TURBO-TALK",
        };
    }

    pub fn label(self: AnimClipId) []const u8 {
        return switch (self) {
            .none => "none",
            .base => "base",
            .move => "move",
            .lookback_l => "lookback_l",
            .lookback_r => "lookback_r",
            .skidstop => "skidstop",
            .damaged => "damaged",
            .intoshell => "intoshell",
            .fall => "fall",
            .talk => "talk",
        };
    }
};

// PORT(verified): mirror of the per-player presentation controller slice that
// `dispatch_cutscene_animation` writes (`+0x108` progress, `+0x10c`
// progress_step, `+0x110` current slot pointer, `+0x118..0x13f` queued
// animation ids, `+0x140` queued count). The port keeps just the logical
// `AnimClipId` values the renderer needs to pick the right turbo clip; the
// 128-byte animation-slot metadata lives in the shared xanim catalog.
pub const max_queued_cutscene_animations: usize = 10;

pub const AnimDispatchState = struct {
    // Native's `initialize_cutscene_ai` queues base, while the live gameplay
    // runner presents id 2 as the steady movement loop. Keep id 2 mapped to
    // the shipped `turbo-move` family rather than the previously inferred
    // `turbo-bobalong` family.
    active: AnimClipId = .move,
    initial_frame: ?u16 = null,
    active_edge_latched: bool = false,
    queued_ids: [max_queued_cutscene_animations]AnimClipId =
        [_]AnimClipId{.none} ** max_queued_cutscene_animations,
    queued_count: u8 = 0,
    token: u32 = 0,

    // Mirrors native `dispatch_cutscene_animation`
    // (`artifacts/ida/functions/00444600-dispatch_cutscene_animation.c:6`):
    // when `immediate` is true, clear the queue, latch the new id, and
    // optionally seed the initial frame; otherwise append to the queue.
    pub fn dispatch(
        self: *AnimDispatchState,
        anim_id: AnimClipId,
        immediate: bool,
        initial_frame: ?u16,
    ) void {
        if (immediate) {
            self.active = anim_id;
            self.initial_frame = initial_frame;
            self.queued_count = 0;
            self.token +%= 1;
        } else if (self.queued_count < max_queued_cutscene_animations) {
            self.queued_ids[self.queued_count] = anim_id;
            self.queued_count += 1;
        }
    }

    // Mirrors the queue-pop tail of native `update_anim_manager`
    // (`artifacts/ida/functions/004447d0-update_anim_manager.c:84-116`): when
    // the current clip finishes, pop the head of the queue and reseed the
    // active slot.
    pub fn onCurrentClipFinished(self: *AnimDispatchState) void {
        if (self.queued_count == 0) return;
        self.active = self.queued_ids[0];
        self.initial_frame = null;
        self.token +%= 1;
        var i: usize = 1;
        while (i < self.queued_count) : (i += 1) {
            self.queued_ids[i - 1] = self.queued_ids[i];
        }
        self.queued_count -= 1;
        self.queued_ids[self.queued_count] = .none;
    }
};

// `JetpackWarningBand` and `JetpackGauge` live in `gameplay/jetpack.zig`.

pub const FallState = struct {
    cause: DeathCause,
    world_x: f32,
    world_y: f32,
    world_z: f32,
    vertical_velocity: f32 = 0.0,
    resurrect_ticks: u16 = 0,
    basis_forward: attachment_builders.Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    basis_up: attachment_builders.Vec3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
};

pub const RunnerPhase = union(enum) {
    active,
    fall: FallState,
    completion_handoff,
};

// PORT(partial): Windows attachment-follow is driven by installed runtime attachment
// records plus sampled template geometry. The current port uses built templates and
// the recovered swept-entry/local-distance lanes, but this struct remains the Zig-side
// owner for values Windows stores across the player follow block and installed
// runtime row-cell record.
pub const AttachmentFollowState = struct {
    active: bool = false,
    source_cell_row: usize = 0,
    // Native follow state keeps a segment index plus a raw local-distance progress inside
    // that segment. Keep both, then derive a builder-facing template progress for the
    // shared Zig attachment helpers.
    sample_index: usize = 0,
    local_progress: f32 = 0.0,
    // Mirrors the native local-distance lane, including raw negative/overflow seeds on entry.
    progress: f32 = 0.0,
    // Zig-side convenience cache in sample-index-plus-fraction space.
    template_progress: f32 = 0.0,
    exit_overshoot: f32 = 0.0,
    lateral_offset: f32 = 0.0,
    cached_output_lane_center: f32 = 0.5,
    vertical_offset: f32 = 0.0,
    // Native writes this from the source row-cell scalar during begin. The port still seeds
    // it from the built template until that runtime row-cell scalar is surfaced in preview data.
    installed_heading_delta: f32 = 0.0,
    camera_orientation_a: f32 = 0.0,
    camera_orientation_b: f32 = 0.0,
    exit_carryover_a: f32 = 0.0,
    exit_carryover_b: f32 = 0.0,
    cached_output_position: attachment_builders.Vec3 = .{},
};

pub const AttachmentExitCarryover = struct {
    // `carryover_a` is the confirmed common carryover lane copied into `post_follow_value_a`.
    carryover_a: f32 = 0.0,
    // `carryover_b` is still preserved because Windows writes `player + 0x430`, but bounded
    // static RE has not yet closed a common consumer for it.
    carryover_b: f32 = 0.0,
};

pub const InstalledAttachmentEntry = struct {
    sample_index: usize,
    local_progress: f32,
    lateral_offset: f32,
    vertical_offset: f32,
};

pub const InstalledAttachmentSlot = enum {
    primary,
    secondary,
};

pub const LaunchState = struct {
    active: bool = false,
    world_x: f32 = 0.0,
    height: f32 = 0.0,
    vertical_velocity: f32 = 0.0,
    camera_progress: f32 = 0.0,
    camera_progress_step: f32 = 0.0,
    basis_forward: attachment_builders.Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    basis_up: attachment_builders.Vec3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
};

pub const WorldFrame = struct {
    position: rl.Vector3,
    forward: rl.Vector3,
    up: rl.Vector3,
};

pub const AttachmentCameraProgress = struct {
    template_kind: u8,
    template_progress: f32,
};
