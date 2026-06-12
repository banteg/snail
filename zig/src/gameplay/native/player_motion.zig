//! Mirror of the native player motion core and attachment-exit lanes
//! (update_subgoldy @ 0x43b120, consumer/exit regions).
//!
//! Transcribed from the dossier in tools/match/scratches/update_subgoldy/
//! (motion core + exit-lane cluster reads, 2026-06-12) and the matched
//! begin_post_follow_carryover (100%). RULE: do not refactor for taste;
//! quirks and exact constants are the point.
//!
//! Zig seams: tile/cell queries, squidge, sound, death, and the carryover
//! arm arrive through deps; the live matrix y/z are the position fields.

const std = @import("std");

pub const gravity_coefficient: f32 = -0.0099999998; // vy += rate^2 * this
pub const drag_z_coefficient: f32 = 0.003; // vz *= 1 - rate*this (gated on bounce byte)
pub const drag_y_coefficient: f32 = 0.003;
pub const drag_x_coefficient: f32 = 0.1;
pub const acceleration_quantum_coefficient: f32 = 0.0040000002; // 2 * rate^2 * this per application
pub const lateral_clamp: f32 = 4.0;
pub const rest_height: f32 = 0.49000001;
pub const grounded_snap_min_y: f32 = -0.16333334;
pub const squidge_velocity_threshold: f32 = -0.029999999;
pub const trampoline_bounce_rate_scale: f32 = 0.30000001;
pub const death_plane_y: f32 = -7.0;
pub const trampoline_tile: u8 = 22;

pub const MotionState = struct {
    position: Vec3 = .{},
    velocity: Vec3 = .{},
    /// byte +0x1e4: set by trampoline bounce, cleared by grounding lanes,
    /// gates the vz drag
    trampoline_bounce: bool = false,
    attachment_exit_pending: bool = false,
};

pub const Vec3 = struct { x: f32 = 0, y: f32 = 0, z: f32 = 0 };

/// the shared integration block (LABEL_101 / free-flight twin):
/// position += velocity, drag triple, gravity, +/-4 lateral clamp.
pub fn integrateAndDrag(state: *MotionState, rate: f32) void {
    state.position.x += state.velocity.x;
    state.position.y += state.velocity.y;
    state.position.z += state.velocity.z;
    if (!state.trampoline_bounce) {
        state.velocity.z *= 1.0 - rate * drag_z_coefficient;
    }
    state.velocity.y *= 1.0 - rate * drag_y_coefficient;
    state.velocity.x *= 1.0 - rate * drag_x_coefficient;
    state.velocity.y += rate * rate * gravity_coefficient;
    if (state.position.x < -lateral_clamp) {
        state.position.x = -lateral_clamp;
        state.velocity.x = 0.0;
    }
    if (state.position.x > lateral_clamp) {
        state.position.x = lateral_clamp;
        state.velocity.x = 0.0;
    }
}

/// the shared acceleration quantum: 2 * rate^2 * 0.004, applied by the
/// following non-DETOUR lane, slide tiles, jetpack state 1, and the
/// +0x41c one-tick boost
pub fn accelerationQuantum(rate: f32) f32 {
    const q = rate * rate * acceleration_quantum_coefficient;
    return q + q;
}

pub const GroundingDeps = struct {
    open_neighbor: bool,
    tile_id: u8,
    context: *anyopaque,
    squidge_fn: *const fn (context: *anyopaque, amount: f32) void,
};

/// the grounded-snap lane (0x43bf6f region): corrected predicates —
/// pending clears unconditionally inside the block, only the snap
/// requires vy <= 0. Returns true when the lane fired.
pub fn groundedSnapLane(state: *MotionState, deps: GroundingDeps) bool {
    if (!(state.position.y < rest_height and state.position.y > grounded_snap_min_y))
        return false;
    if (deps.open_neighbor or deps.tile_id == trampoline_tile)
        return false;
    // native also resets the live-matrix rotation and clears the bounce byte
    state.trampoline_bounce = false;
    if (state.velocity.y < squidge_velocity_threshold) {
        deps.squidge_fn(deps.context, state.velocity.y - 0.029999999);
    }
    if (state.velocity.y <= 0.0) {
        state.position.y = rest_height;
        state.velocity.y = 0.0;
    }
    state.attachment_exit_pending = false;
    return true;
}

pub const TrampolineDeps = struct {
    tile_id: u8,
    cell_anchor_y: f32,
    context: *anyopaque,
    squidge_fn: *const fn (context: *anyopaque, amount: f32) void,
    play_sound_fn: *const fn (context: *anyopaque, sound: u8) void,
};

/// the trampoline lane (0x43c3ea region): runs while exit is pending,
/// applies gravity first, bounces on tile 22 inside the +/-0.49 window:
/// vy is SET to rate*0.3 (not flipped), the bounce byte arms, sound 41.
pub fn pendingExitTrampolineLane(state: *MotionState, rate: f32, deps: TrampolineDeps) bool {
    if (!state.attachment_exit_pending) return false;
    state.velocity.y += rate * rate * gravity_coefficient;
    if (deps.tile_id != trampoline_tile) return false;
    if (!(deps.cell_anchor_y + rest_height > state.position.y and
        deps.cell_anchor_y - rest_height < state.position.y)) return false;
    deps.squidge_fn(deps.context, state.velocity.y);
    state.velocity.y = rate * trampoline_bounce_rate_scale;
    state.position.y = deps.cell_anchor_y + rest_height;
    state.attachment_exit_pending = false;
    state.trampoline_bounce = true;
    deps.play_sound_fn(deps.context, 41);
    return true;
}

const TestMotionDeps = struct {
    squidges: u32 = 0,
    last_squidge: f32 = 0,
    sounds: u32 = 0,

    fn squidge(context: *anyopaque, amount: f32) void {
        const self: *TestMotionDeps = @ptrCast(@alignCast(context));
        self.squidges += 1;
        self.last_squidge = amount;
    }
    fn sound(context: *anyopaque, s: u8) void {
        _ = s;
        const self: *TestMotionDeps = @ptrCast(@alignCast(context));
        self.sounds += 1;
    }
};

test "integration applies the native drag triple, gravity, and clamp" {
    var state = MotionState{ .velocity = .{ .x = 5.0, .y = 0.1, .z = 1.0 }, .position = .{ .x = 3.9 } };
    integrateAndDrag(&state, 2.0);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0 * (1.0 - 2.0 * 0.003)), state.velocity.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.1 * (1.0 - 2.0 * 0.003) + 4.0 * gravity_coefficient), state.velocity.y, 0.0001);
    // walked past the wall: clamped with vx zeroed
    try std.testing.expectEqual(@as(f32, 4.0), state.position.x);
    try std.testing.expectEqual(@as(f32, 0.0), state.velocity.x);
}

test "trampoline bounce sets vy to rate*0.3 and arms the bounce byte" {
    var state = MotionState{
        .position = .{ .y = 1.2 },
        .velocity = .{ .y = -0.5 },
        .attachment_exit_pending = true,
    };
    var deps = TestMotionDeps{};
    const fired = pendingExitTrampolineLane(&state, 2.0, .{
        .tile_id = trampoline_tile,
        .cell_anchor_y = 1.0,
        .context = &deps,
        .squidge_fn = TestMotionDeps.squidge,
        .play_sound_fn = TestMotionDeps.sound,
    });
    try std.testing.expect(fired);
    try std.testing.expectApproxEqAbs(@as(f32, 0.6), state.velocity.y, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.49), state.position.y, 0.001);
    try std.testing.expect(state.trampoline_bounce);
    try std.testing.expect(!state.attachment_exit_pending);
    try std.testing.expectEqual(@as(u32, 1), deps.sounds);
    // the bounce byte now gates the vz drag
    state.velocity.z = 1.0;
    integrateAndDrag(&state, 2.0);
    try std.testing.expectEqual(@as(f32, 1.0), state.velocity.z);
}

test "grounded snap clears pending unconditionally but only snaps when falling" {
    var state = MotionState{
        .position = .{ .y = 0.3 },
        .velocity = .{ .y = 0.02 }, // rising: no snap
        .attachment_exit_pending = true,
        .trampoline_bounce = true,
    };
    var deps = TestMotionDeps{};
    const fired = groundedSnapLane(&state, .{
        .open_neighbor = false,
        .tile_id = 0,
        .context = &deps,
        .squidge_fn = TestMotionDeps.squidge,
    });
    try std.testing.expect(fired);
    try std.testing.expect(!state.attachment_exit_pending); // unconditional clear
    try std.testing.expect(!state.trampoline_bounce);
    try std.testing.expectApproxEqAbs(@as(f32, 0.3), state.position.y, 0.0001); // no snap while rising
    try std.testing.expectEqual(@as(u32, 0), deps.squidges);

    // falling fast: squidge with vy - 0.03, snap, zero vy
    var falling = MotionState{ .position = .{ .y = 0.3 }, .velocity = .{ .y = -0.2 }, .attachment_exit_pending = true };
    _ = groundedSnapLane(&falling, .{
        .open_neighbor = false,
        .tile_id = 0,
        .context = &deps,
        .squidge_fn = TestMotionDeps.squidge,
    });
    try std.testing.expectEqual(@as(u32, 1), deps.squidges);
    try std.testing.expectApproxEqAbs(@as(f32, -0.23), deps.last_squidge, 0.001);
    try std.testing.expectEqual(@as(f32, rest_height), falling.position.y);
    try std.testing.expectEqual(@as(f32, 0.0), falling.velocity.y);
}
