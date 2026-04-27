const std = @import("std");
const rl = @import("raylib");

const track_parcel_bob_amplitude: f32 = 0.3;
const track_parcel_bob_phase_step: f32 = 0.012820513;

// PORT(verified): after the salt migration, `HazardKind` only covers
// garbage. Salt lives in its own `SaltHazardPool` that mirrors native's
// dedicated `cRSalt @ game + 0x3578c0`. The single-variant enum is kept
// (rather than replaced with a direct type) so `Hazard.kind`-shaped call
// sites retain their existing switch ergonomics, and so any future
// hazard family added to the shared pool has a natural place to land.
pub const HazardKind = enum {
    garbage,
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
    smoke_progress: f32 = 0.0,
};

// PORT(verified): per-slot layout mirrors the `cRSalt` projectile slot at
// `game + 0x3578c0` in `artifacts/ida/functions/00441560-spawn_salt_hazard.c`
// and `artifacts/ida/functions/004417d0-update_salt_hazard.c`. The 40-slot
// native pool's per-slot state is:
//
//   - `+0x80` state (0 = inactive, 1 = active, 2 = queued for removal)
//   - `+0x68..+0x73` world position (Vec3)
//   - `+0x8c..+0x97` world velocity (Vec3)
//   - `+0x98` lifetime progress (f32)
//   - `+0x9c` lifetime step (f32, seeded from `track_center_x * 0.033333335`)
//   - `+0x38..+0x68` 4x4 transform matrix seeded on spawn via identity +
//     random Y rotation (`rotate_matrix_world_y` with a signed random angle)
//
// The port carries the load-bearing fields explicitly. The transform matrix
// is represented as a single yaw scalar because the renderer only needs the
// Y rotation for sprite orientation — native's full matrix is used by the
// track-attachment intersection test, which the port reads back from the
// salt slot directly at collision time.
pub const SaltSlotState = enum(u8) {
    inactive = 0,
    active = 1,
    removing = 2,
};

pub const SaltSlot = struct {
    state: SaltSlotState = .inactive,
    row: usize = 0,
    lane: usize = 0,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    lifetime_progress: f32 = 0.0,
    lifetime_step: f32 = 0.0,
    yaw_radians: f32 = 0.0,
};

// PORT(verified): per-slot layout mirrors the `cRSubLazerManager` projectile
// slot at `game + 0x356b00` in
// `artifacts/ida/functions/00441670-spawn_wall2_ambient_hazard.c` and
// `artifacts/ida/functions/0043efb0-update_wall2_ambient_hazard.c`. The
// 20-slot native pool's per-slot state layout is:
//
//   - `+0x80` state (0 inactive, 1 active, 2 queued for removal)
//   - `+0x14` spawn-position Y anchor (the y-oscillation base)
//   - `+0x68..+0x73` world position (Vec3)
//   - `+0x8c..+0x97` velocity (Vec3)
//   - `+0x6c` phase (accumulates toward the sine oscillation driver)
//   - `+0x70` phase_step (seeded from `track_center_x * 0.0055555557`)
//   - `+0x44` back-pointer to emitter cell
//   - `+0x64` nested render/body object pointer (sprite)
//
// Native uses the Y-position as the sine-wave rest point; the sprite bobs
// around `anchor_y + sin(phase*2*pi) * 0.3` each tick. The emitter cell
// back-pointer gates the slot cleanup — once the emitter is past the
// player, the slot is destroyed.
pub const SubLazerSlotState = enum(u8) {
    inactive = 0,
    active = 1,
    removing = 2,
};

pub const SubLazerSlot = struct {
    state: SubLazerSlotState = .inactive,
    emitter_row: usize = 0,
    emitter_lane: usize = 0,
    world_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    anchor_y: f32 = 0.0,
    phase: f32 = 0.0,
    phase_step: f32 = 0.0,
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
