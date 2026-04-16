//! Plain data types used by the gameplay `Runner`. Kept separate so the Runner
//! implementation in `gameplay.zig` does not have to re-declare them.
//!
//! No function here may reference `gameplay.Runner` or any runtime entity
//! module. Moving pure types only.

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
