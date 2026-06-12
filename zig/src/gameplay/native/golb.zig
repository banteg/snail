//! Mirror of update_golb_ai @ 0x414820 (cGolb::Update) — one live Golb
//! shot per tick.
//!
//! Transcribed from tools/match/scratches/update_golb_ai (20.79%,
//! structure complete, full semantics extracted 2026-06-13). RULE: do not
//! refactor for taste; quirks and exact constants are the point.
//!
//! Zig seams: the path-follow riding lane (calc_path_length_z — a
//! template-stamped sibling of update_track_attachment_follow_state),
//! grid-cell tile probes, the garbage/slug pools, and sprite/smoke/vapour
//! emission arrive through GolbDeps. The pure lanes (band gravity, rocket
//! homing, trail offsets, spin wrap, slug deflection, lifetime) are
//! standalone functions with transcription tests.

const std = @import("std");

pub const Vec3 = struct { x: f32 = 0, y: f32 = 0, z: f32 = 0 };

pub const GolbKind = enum(i32) {
    /// kind 0: the turbo shot — track-band gravity, slug bounce byte
    golb = 0,
    /// kind 1: the laser — vapour trail, pierces garbage
    lazer = 1,
    /// kind 2: the rocket — homing blend, smoke pair, spin
    rocket = 2,
};

pub const band_floor_y: f32 = 0.0;
pub const band_ceiling_y: f32 = 0.49000001; // +0x14-style rest height reused
pub const band_gravity_coefficient: f32 = 0.017000001; // vy -= rate * this
pub const homing_impact_distance: f32 = 0.40000001;
pub const homing_stall_speed: f32 = 0.1;
pub const homing_keep_coefficient: f32 = 1.5; // keep = 1 - blend*1.5
pub const trail_step_fraction: f32 = 0.30000001; // kind 0: out, -0.3*dir, -0.6*dir
pub const smoke_step_fraction: f32 = 0.5; // kind 2: out, -0.5*dir
pub const spin_wrap: f32 = 6.2831855; // 2*pi
pub const lifetime_expiry: f32 = 1.0;
pub const forward_band_rows: f32 = 46.0; // player z + 46 alive window
pub const garbage_probe_half_depth: f32 = 3.0;
pub const garbage_contact_pad: f32 = 0.49000001; // radius + this
pub const rocket_splash_radius: f32 = 3.0;
pub const slug_probe_half_depth: f32 = 2.5;
pub const slug_contact_distance: f32 = 2.5;
pub const path_entry_tile: u8 = 30;
pub const wall_tile: u8 = 14;
pub const fast_entry_min_vz: f32 = 1.0;

/// cGolb runtime state, mirror-relevant fields at their native offsets.
pub const GolbShot = struct {
    homing_target_active: bool = false, // +0x198
    homing_target: Vec3 = .{}, // +0x19c
    homing_blend: f32 = 0.0, // +0x1ac
    homing_blend_step: f32 = 0.0, // +0x1b0
    spin: f32 = 0.0, // +0x1b4
    spin_step: f32 = 0.0, // +0x1b8
    skip_one_tick: bool = false, // +0x1bc
    slug_bounce_armed: bool = false, // +0x1bd
    kind: GolbKind = .golb, // +0x1c0
    position: Vec3 = .{}, // +0x1f4 (the integrated position)
    previous_output: Vec3 = .{}, // +0x234
    state: i32 = 0, // +0x244: 1 = live
    velocity: Vec3 = .{}, // +0x24c (per tick)
    direction: Vec3 = .{}, // +0x258 (output delta, drives trails)
    path_factor: f32 = 0.0, // +0x264
    lifetime: f32 = 0.0, // +0x268
    lifetime_step: f32 = 0.0, // +0x26c
    output_position: Vec3 = .{}, // +0x2ac (the matrix position row)
    path_follow_active: bool = false, // +0x2bc (.active)
    path_entry_z_latch: f32 = 0.0, // +0x2e4
};

fn normalize(vector: *Vec3) f32 {
    const length = @sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    if (length > 0.0) {
        vector.x /= length;
        vector.y /= length;
        vector.z /= length;
    }
    return length;
}

/// kind-0 vertical band: gravity above the band or below the floor,
/// hard zero inside [0, 0.49] so the shot skims the track.
pub fn applyGolbBandGravity(shot: *GolbShot, subgame_rate: f32) void {
    if (shot.position.y > band_ceiling_y or shot.position.y < band_floor_y) {
        shot.velocity.y -= subgame_rate * band_gravity_coefficient;
    } else {
        shot.velocity.y = 0.0;
    }
}

pub const HomingResult = enum { flying, impact, stalled };

/// kind-2 homing lane: blend ramps to 1.0 by its step; velocity becomes
/// renormalize((1 - blend*1.5) * velocity + blend * to_target) scaled
/// back to the previous speed. Impact under 0.4 distance; stall when the
/// speed drops below 0.1.
pub fn stepRocketHoming(shot: *GolbShot) HomingResult {
    const blend_advanced = shot.homing_blend_step + shot.homing_blend;
    shot.homing_blend = blend_advanced;
    if (blend_advanced > 1.0)
        shot.homing_blend = 1.0;
    const speed = normalize(&shot.velocity);
    var delta = Vec3{
        .x = shot.homing_target.x - shot.position.x,
        .y = shot.homing_target.y - shot.position.y,
        .z = shot.homing_target.z - shot.position.z,
    };
    if (normalize(&delta) < homing_impact_distance)
        return .impact;
    const pull = shot.homing_blend;
    const keep = 1.0 - shot.homing_blend * homing_keep_coefficient;
    shot.velocity.x = keep * shot.velocity.x + delta.x * pull;
    shot.velocity.y = keep * shot.velocity.y + delta.y * pull;
    shot.velocity.z = keep * shot.velocity.z + pull * delta.z;
    _ = normalize(&shot.velocity);
    shot.velocity.x = speed * shot.velocity.x;
    shot.velocity.y = speed * shot.velocity.y;
    shot.velocity.z = speed * shot.velocity.z;
    if (speed < homing_stall_speed)
        return .stalled;
    return .flying;
}

/// the kind-0 trail triple: output, output - 0.3*direction,
/// output - 0.6*direction.
pub fn golbTrailPositions(shot: *const GolbShot) [3]Vec3 {
    const out = shot.output_position;
    const dir = shot.direction;
    return .{
        out,
        .{
            .x = out.x - dir.x * trail_step_fraction,
            .y = out.y - dir.y * trail_step_fraction,
            .z = out.z - dir.z * trail_step_fraction,
        },
        .{
            .x = out.x - dir.x * (trail_step_fraction + trail_step_fraction),
            .y = out.y - dir.y * (trail_step_fraction + trail_step_fraction),
            .z = out.z - dir.z * (trail_step_fraction + trail_step_fraction),
        },
    };
}

/// the kind-2 smoke pair: output and output - 0.5*direction; the spin
/// accumulates by its step and wraps past 2*pi.
pub fn rocketSmokePositions(shot: *GolbShot) [2]Vec3 {
    const spun = shot.spin_step + shot.spin;
    shot.spin = spun;
    if (spun > spin_wrap)
        shot.spin = spun - spin_wrap;
    const out = shot.output_position;
    const dir = shot.direction;
    return .{
        out,
        .{
            .x = out.x - dir.x * smoke_step_fraction,
            .y = out.y - dir.y * smoke_step_fraction,
            .z = out.z - dir.z * smoke_step_fraction,
        },
    };
}

/// slug contact deflection: the velocity flattens to the reflected
/// horizontal lane — (-speed*nx, 0, -speed*nz) off the contact normal —
/// and the path follow drops.
pub fn deflectVelocityFromSlug(shot: *GolbShot, contact_delta: Vec3) void {
    shot.path_follow_active = false;
    const speed = normalize(&shot.velocity);
    var probe = contact_delta;
    _ = normalize(&probe);
    shot.velocity.x = -(speed * probe.x);
    shot.velocity.y = 0.0;
    shot.velocity.z = -(speed * probe.z);
}

/// direction update + lifetime accumulation shared by every live tick:
/// direction = output - previous_output, lifetime += step, previous =
/// output. Returns true while the shot stays alive (lifetime <= 1.0).
pub fn advanceDirectionAndLifetime(shot: *GolbShot) bool {
    shot.direction.x = shot.output_position.x - shot.previous_output.x;
    shot.direction.y = shot.output_position.y - shot.previous_output.y;
    shot.direction.z = shot.output_position.z - shot.previous_output.z;
    const lived = shot.lifetime_step + shot.lifetime;
    shot.lifetime = lived;
    shot.previous_output = shot.output_position;
    return lived <= lifetime_expiry;
}

pub const PathEntryProbe = struct {
    /// tile under the output position
    tile_id: u8,
    /// tile one row earlier (native cell - 672 = 8 cells = previous row)
    previous_row_tile_id: u8,
};

pub const PathEntryDecision = enum { none, enter_here, enter_previous_row };

/// the tile-30 path entry lanes: only while y is inside (0, 1) and the
/// output z has passed the latch. Fast shots (vz > 1) pre-enter via the
/// previous row, latching z + 1.
pub fn decidePathEntry(shot: *GolbShot, probe: PathEntryProbe) PathEntryDecision {
    if (!(shot.path_entry_z_latch < shot.output_position.z and
        shot.position.y < 1.0 and shot.position.y > 0.0)) return .none;
    if (probe.tile_id == path_entry_tile) {
        shot.path_entry_z_latch = shot.output_position.z;
        return .enter_here;
    }
    if (shot.velocity.z > fast_entry_min_vz and probe.previous_row_tile_id == path_entry_tile) {
        shot.path_entry_z_latch = shot.output_position.z + 1.0;
        return .enter_previous_row;
    }
    return .none;
}

/// the alive band: golb_band_min_z (player interaction_max_z, +0x2980)
/// <= shot z <= player z + 46. Outside the band the contact sweeps are
/// skipped entirely (the shot still flies).
pub fn insideContactBand(shot_z: f32, band_min_z: f32, player_z: f32) bool {
    return shot_z >= band_min_z and player_z + forward_band_rows >= shot_z;
}

test "band gravity zeroes vy inside the track band and pulls above it" {
    var shot = GolbShot{ .position = .{ .y = 0.25 }, .velocity = .{ .y = 0.5 } };
    applyGolbBandGravity(&shot, 1.0);
    try std.testing.expectEqual(@as(f32, 0.0), shot.velocity.y);
    shot.position.y = 0.5;
    applyGolbBandGravity(&shot, 2.0);
    try std.testing.expectApproxEqAbs(@as(f32, -2.0 * 0.017000001), shot.velocity.y, 1e-7);
    shot.position.y = -0.01;
    shot.velocity.y = 0.0;
    applyGolbBandGravity(&shot, 1.0);
    try std.testing.expect(shot.velocity.y < 0.0);
}

test "rocket homing blends toward the target and keeps the old speed" {
    var shot = GolbShot{
        .kind = .rocket,
        .homing_target_active = true,
        .homing_target = .{ .x = 0.0, .y = 0.0, .z = 10.0 },
        .homing_blend = 0.5,
        .homing_blend_step = 0.75,
        .position = .{},
        .velocity = .{ .x = 2.0, .y = 0.0, .z = 0.0 },
    };
    const result = stepRocketHoming(&shot);
    try std.testing.expectEqual(HomingResult.flying, result);
    // blend capped at 1.0
    try std.testing.expectEqual(@as(f32, 1.0), shot.homing_blend);
    // speed preserved through the renormalize
    const speed = @sqrt(shot.velocity.x * shot.velocity.x +
        shot.velocity.y * shot.velocity.y + shot.velocity.z * shot.velocity.z);
    try std.testing.expectApproxEqAbs(@as(f32, 2.0), speed, 1e-5);
    // keep = 1 - 1.5 at full blend turns the old heading negative; the
    // target pull dominates so the shot now travels toward +z
    try std.testing.expect(shot.velocity.z > 0.0);
    try std.testing.expect(shot.velocity.x < 0.0);
}

test "rocket homing impacts under 0.4 distance and stalls under 0.1 speed" {
    var close = GolbShot{
        .homing_target = .{ .z = 0.3 },
        .velocity = .{ .z = 1.0 },
    };
    try std.testing.expectEqual(HomingResult.impact, stepRocketHoming(&close));
    var slow = GolbShot{
        .homing_target = .{ .z = 10.0 },
        .velocity = .{ .z = 0.05 },
    };
    try std.testing.expectEqual(HomingResult.stalled, stepRocketHoming(&slow));
}

test "trail offsets step by 0.3 fractions of the direction" {
    const shot = GolbShot{
        .output_position = .{ .z = 10.0 },
        .direction = .{ .z = 1.0 },
    };
    const trail = golbTrailPositions(&shot);
    try std.testing.expectApproxEqAbs(@as(f32, 10.0), trail[0].z, 1e-6);
    try std.testing.expectApproxEqAbs(@as(f32, 10.0 - 0.30000001), trail[1].z, 1e-6);
    try std.testing.expectApproxEqAbs(@as(f32, 10.0 - 0.60000002), trail[2].z, 1e-6);
}

test "rocket smoke pair wraps the spin past two pi" {
    var shot = GolbShot{
        .spin = 6.2,
        .spin_step = 0.2,
        .output_position = .{ .x = 1.0 },
        .direction = .{ .x = 1.0 },
    };
    const smokes = rocketSmokePositions(&shot);
    try std.testing.expectApproxEqAbs(@as(f32, 6.4 - 6.2831855), shot.spin, 1e-6);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), smokes[1].x, 1e-6);
}

test "slug deflection reflects horizontally and drops the path follow" {
    var shot = GolbShot{
        .path_follow_active = true,
        .velocity = .{ .y = 1.0, .z = 3.0 },
    };
    deflectVelocityFromSlug(&shot, .{ .x = 0.0, .y = 0.0, .z = 1.0 });
    try std.testing.expect(!shot.path_follow_active);
    try std.testing.expectEqual(@as(f32, 0.0), shot.velocity.y);
    const speed = @sqrt(1.0 + 9.0);
    try std.testing.expectApproxEqAbs(-@as(f32, @floatCast(speed)), shot.velocity.z, 1e-5);
}

test "direction and lifetime advance retires past 1.0" {
    var shot = GolbShot{
        .output_position = .{ .z = 5.0 },
        .previous_output = .{ .z = 4.0 },
        .lifetime = 0.95,
        .lifetime_step = 0.1,
    };
    try std.testing.expect(!advanceDirectionAndLifetime(&shot));
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), shot.direction.z, 1e-6);
    try std.testing.expectEqual(@as(f32, 5.0), shot.previous_output.z);
}

test "path entry latches tile 30 and fast shots pre-enter the previous row" {
    var shot = GolbShot{
        .position = .{ .y = 0.25 },
        .output_position = .{ .z = 12.0 },
        .path_entry_z_latch = 10.0,
        .velocity = .{ .z = 1.5 },
    };
    try std.testing.expectEqual(
        PathEntryDecision.enter_here,
        decidePathEntry(&shot, .{ .tile_id = 30, .previous_row_tile_id = 0 }),
    );
    try std.testing.expectEqual(@as(f32, 12.0), shot.path_entry_z_latch);

    shot.path_entry_z_latch = 10.0;
    try std.testing.expectEqual(
        PathEntryDecision.enter_previous_row,
        decidePathEntry(&shot, .{ .tile_id = 0, .previous_row_tile_id = 30 }),
    );
    try std.testing.expectEqual(@as(f32, 13.0), shot.path_entry_z_latch);

    // slow shots do not pre-enter
    shot.velocity.z = 0.5;
    shot.path_entry_z_latch = 10.0;
    try std.testing.expectEqual(
        PathEntryDecision.none,
        decidePathEntry(&shot, .{ .tile_id = 0, .previous_row_tile_id = 30 }),
    );

    // outside the y band nothing latches
    shot.position.y = 1.5;
    try std.testing.expectEqual(
        PathEntryDecision.none,
        decidePathEntry(&shot, .{ .tile_id = 30, .previous_row_tile_id = 30 }),
    );
}

test "contact band spans interaction line to player z plus 46" {
    try std.testing.expect(insideContactBand(10.0, 5.0, 8.0));
    try std.testing.expect(!insideContactBand(4.0, 5.0, 8.0));
    try std.testing.expect(!insideContactBand(60.0, 5.0, 8.0));
    try std.testing.expect(insideContactBand(54.0, 5.0, 8.0));
}
