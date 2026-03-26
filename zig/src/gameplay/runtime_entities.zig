const std = @import("std");
const rl = @import("raylib");

const track_parcel_bob_amplitude: f32 = 0.3;
const track_parcel_bob_phase_step: f32 = 0.012820513;

pub const HazardKind = enum {
    garbage,
    salt,
};

pub const HazardState = enum(u8) {
    inactive = 0,
    active = 1,
    burst_setup = 2,
    burst = 3,
};

pub const Hazard = struct {
    row: usize,
    lane: usize,
    kind: HazardKind,
    state: HazardState = .active,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_scale: f32 = 1.0,
    presentation_phase: f32 = 0.0,
    yaw_radians: f32 = 0.0,
    arming_progress: f32 = 1.0,
    arming_step: f32 = 0.0,
    collision_side: i8 = 0,
};

pub const PickupKind = enum {
    health,
    jetpack,
};

pub const Pickup = struct {
    row: usize,
    lane: usize,
    kind: PickupKind,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    bob_phase: f32 = 0.0,
    bob_phase_step: f32 = 0.0,
};

pub const RingEffectState = enum(u8) {
    active,
    collect_setup,
    collect_follow,
    miss_setup,
    miss_expand,
};

pub const RingEffect = struct {
    source_row: usize,
    row: usize,
    lane: usize,
    kind: u8,
    state: RingEffectState = .active,
    collision_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    presentation_scale: f32 = 1.0,
    movement_flag_selector_snapshot: u8 = 0,
    active_x_oscillation_enabled: bool = false,
    child_update_cadence: u8 = 0,
    active_phase: f32 = 0.0,
    active_phase_step: f32 = 0.0,
    effect_progress: f32 = 0.0,
    effect_progress_step: f32 = 0.0,
};

pub const TrackParcel = struct {
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

    pub fn active(self: TrackParcel) bool {
        return self.state != 0;
    }

    pub fn presentationPosition(self: TrackParcel) rl.Vector3 {
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

    pub fn presentationScale(self: TrackParcel) f32 {
        return switch (self.state) {
            5, 7 => self.presentation_scale,
            else => 1.0,
        };
    }
};

pub const TrackParcelHomeAnchor = struct {
    active: bool = false,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

pub const TurretState = struct {
    row: usize,
    lane: usize,
    seconds: f32 = 0.0,
    flash_ticks: u8 = 0,
};
