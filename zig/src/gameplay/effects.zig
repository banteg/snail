const std = @import("std");
const rl = @import("raylib");

const app = @import("../app.zig");
const assets = @import("../assets.zig");
const gameplay = @import("../gameplay.zig");
const level = @import("../level.zig");
const track = @import("../track.zig");

const default_archive_path = app.default_archive_path;
const default_level_path = app.default_level_path;
const simulation_step_seconds = 1.0 / 60.0;

pub const max_active = 64;

pub const Kind = enum {
    explode_big,
    explode_small,
    slug_goo,
    smoke,
};

pub const Effect = struct {
    active: bool = false,
    kind: Kind = .explode_small,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    acceleration: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    width: f32 = 0.8,
    height: f32 = 0.8,
    tint: rl.Color = .white,
    ticks_remaining: u16 = 0,
};

pub const Controller = struct {
    items: [max_active]Effect = [_]Effect{.{}} ** max_active,
    count: usize = 0,

    pub fn clear(self: *Controller) void {
        self.count = 0;
        for (&self.items) |*effect| {
            effect.active = false;
        }
    }

    pub fn update(self: *Controller) void {
        var write_index: usize = 0;
        for (0..self.count) |read_index| {
            var effect = self.items[read_index];
            if (!effect.active or effect.ticks_remaining == 0) continue;
            effect.position = .{
                .x = effect.position.x + effect.velocity.x,
                .y = effect.position.y + effect.velocity.y,
                .z = effect.position.z + effect.velocity.z,
            };
            effect.velocity = .{
                .x = effect.velocity.x + effect.acceleration.x,
                .y = effect.velocity.y + effect.acceleration.y,
                .z = effect.velocity.z + effect.acceleration.z,
            };
            effect.ticks_remaining -= 1;
            if (effect.ticks_remaining == 0) continue;
            self.items[write_index] = effect;
            write_index += 1;
        }
        self.count = write_index;
        for (write_index..max_active) |index| {
            self.items[index].active = false;
        }
    }

    pub fn spawn(
        self: *Controller,
        kind: Kind,
        position: rl.Vector3,
        width: f32,
        height: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        self.spawnWithPhysics(
            kind,
            position,
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            width,
            height,
            ticks_remaining,
            tint,
        );
    }

    pub fn spawnWithVelocity(
        self: *Controller,
        kind: Kind,
        position: rl.Vector3,
        velocity: rl.Vector3,
        width: f32,
        height: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        self.spawnWithPhysics(
            kind,
            position,
            velocity,
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            width,
            height,
            ticks_remaining,
            tint,
        );
    }

    pub fn spawnWithPhysics(
        self: *Controller,
        kind: Kind,
        position: rl.Vector3,
        velocity: rl.Vector3,
        acceleration: rl.Vector3,
        width: f32,
        height: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        if (self.count >= max_active) return;
        self.items[self.count] = .{
            .active = true,
            .kind = kind,
            .position = position,
            .velocity = velocity,
            .acceleration = acceleration,
            .width = width,
            .height = height,
            .tint = tint,
            .ticks_remaining = ticks_remaining,
        };
        self.count += 1;
    }

    pub fn spawnRunnerEffects(
        self: *Controller,
        previous: gameplay.Runner,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const forward = current.worldForward(preview);
        if (current.counters.ring_explode > previous.counters.ring_explode) {
            self.spawn(
                .explode_big,
                current.worldPosition(preview, 0.52),
                1.8,
                1.8,
                28,
                .{ .r = 255, .g = 228, .b = 168, .a = 244 },
            );
        }
        if (current.counters.health_pickups > previous.counters.health_pickups) {
            self.spawnHealthPickupEffects(previous, current, preview);
        }
        if (current.jetpack.jet_particles_active) {
            self.spawnJetParticleEffects(current, preview);
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits or current.counters.salt_hits > previous.counters.salt_hits or current.counters.turret_hits > previous.counters.turret_hits) {
            const impact_origin = current.last_garbage_hit_position orelse current.last_salt_hit_position orelse current.worldPosition(preview, 0.44);
            self.spawn(
                .explode_small,
                impact_origin,
                0.9,
                0.9,
                18,
                .{ .r = 255, .g = 220, .b = 180, .a = 236 },
            );
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits) {
            const smoke_origin = current.last_garbage_hit_position orelse current.worldPosition(preview, 0.34);
            self.spawnWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x - 0.18,
                    .y = smoke_origin.y + 0.22,
                    .z = smoke_origin.z,
                },
                .{
                    .x = forward.x * 0.02,
                    .y = 0.012,
                    .z = forward.z * 0.02,
                },
                0.56,
                0.56,
                22,
                .{ .r = 255, .g = 255, .b = 255, .a = 208 },
            );
            self.spawnWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x + 0.14,
                    .y = smoke_origin.y + 0.36,
                    .z = smoke_origin.z - 0.08,
                },
                .{
                    .x = forward.x * 0.014,
                    .y = 0.018,
                    .z = (forward.z * 0.014) - 0.004,
                },
                0.72,
                0.72,
                28,
                .{ .r = 255, .g = 255, .b = 255, .a = 176 },
            );
        }
        if (current.counters.salt_hits > previous.counters.salt_hits) {
            const smoke_origin = current.last_salt_hit_position orelse current.worldPosition(preview, 0.52);
            self.spawnWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x,
                    .y = smoke_origin.y + 0.6,
                    .z = smoke_origin.z,
                },
                .{
                    .x = 0.0,
                    .y = 0.02,
                    .z = forward.z * 0.01,
                },
                0.68,
                0.82,
                24,
                .{ .r = 255, .g = 255, .b = 255, .a = 192 },
            );
        }
        if (current.defeated_slug_cell_count > previous.defeated_slug_cell_count) {
            for (previous.defeated_slug_cell_count..current.defeated_slug_cell_count) |index| {
                const defeated = current.defeated_slug_cells[index];
                const position = laneWorldPosition(preview, defeated.row, defeated.lane, 0.38);
                self.spawn(
                    .slug_goo,
                    position,
                    0.82,
                    0.82,
                    24,
                    .white,
                );
            }
        }
    }

    // PORT(partial): native `update_jet_particles` drives a 15x2 persistent SMOKE.TGA
    // sprite bank from the player's live matrix while the jet particle owner is armed.
    // The port feeds the same lifecycle into the generic smoke effect system until the
    // dedicated nozzle sprite owner is represented directly.
    pub fn spawnJetParticleEffects(
        self: *Controller,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const forward = normalizeVector3(current.worldForward(preview));
        const up = normalizeVector3(current.worldUp(preview));
        var right = crossVector3(up, forward);
        if (vectorLength(right) <= 0.0001) {
            right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
        } else {
            right = normalizeVector3(right);
        }

        const origin = current.worldPosition(preview, 0.18);
        const alpha = std.math.clamp(current.jetpack.warning_intensity, 0.0, 1.0);
        const size = std.math.lerp(@as(f32, 0.16), @as(f32, 0.42), alpha);
        const tint_alpha: u8 = @intFromFloat(std.math.lerp(@as(f32, 96.0), @as(f32, 224.0), alpha));
        const backward = -0.10 - (0.18 * alpha);
        const upward = 0.03 + (0.05 * alpha);

        for ([_]f32{ -0.16, 0.16 }) |side| {
            self.spawnWithVelocity(
                .smoke,
                offsetPosition(origin, right, up, forward, side, -0.03, -0.24),
                .{
                    .x = (forward.x * backward) + (up.x * upward) + (right.x * side * 0.04),
                    .y = (forward.y * backward) + (up.y * upward) + (right.y * side * 0.04),
                    .z = (forward.z * backward) + (up.z * upward) + (right.z * side * 0.04),
                },
                size,
                size,
                10,
                .{ .r = 255, .g = 255, .b = 255, .a = tint_alpha },
            );
        }
    }

    // PORT(partial): native `health_collect_particles` emits 8 `SMOKE.TGA` sprites from the
    // picked-up runtime slot using world-axis radial velocity, the player's live motion
    // packet, and a small downward acceleration. The port now matches that packet shape
    // through the gameplay-effect system, while still approximating the native motion lanes
    // from consecutive runner world transforms instead of the original inline fields.
    pub fn spawnHealthPickupEffects(
        self: *Controller,
        previous: gameplay.Runner,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const pickup_origin = current.last_health_pickup_position orelse current.worldPosition(preview, 0.34);
        const previous_position = previous.worldPosition(preview, 0.0);
        const current_position = current.worldPosition(preview, 0.0);
        const player_motion = rl.Vector3{
            .x = current_position.x - previous_position.x,
            .y = current_position.y - previous_position.y,
            .z = current_position.z - previous_position.z,
        };
        var particle_index: usize = 0;
        while (particle_index < 8) : (particle_index += 1) {
            const angle = @as(f32, @floatFromInt(particle_index)) * 0.78539819;
            self.spawnWithPhysics(
                .smoke,
                pickup_origin,
                .{
                    .x = (std.math.sin(angle) * 0.015) + (player_motion.x * 3.0),
                    .y = (std.math.cos(angle) * 0.015) + (player_motion.y * 3.0),
                    .z = (player_motion.z * 0.4) + (player_motion.z * 3.0),
                },
                .{
                    .x = 0.0,
                    .y = -0.0002,
                    .z = 0.0,
                },
                0.1,
                0.5,
                16,
                .{ .r = 255, .g = 191, .b = 191, .a = 255 },
            );
        }
    }
};

fn laneWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    return preview.worldPositionForLane(@as(f32, @floatFromInt(lane_index)) + 0.5, @as(f32, @floatFromInt(global_row)), floor_height + y_offset);
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

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

test "health pickup burst uses the recovered smoke packet and downward drift" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var previous = gameplay.Runner.init(&loaded_track_preview);
    var current = previous;
    current.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    current.last_health_pickup_position = .{ .x = 1.25, .y = 2.5, .z = 3.75 };

    var controller = Controller{};
    controller.spawnHealthPickupEffects(previous, current, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, 8), controller.count);
    const effect = controller.items[0];
    const previous_position = previous.worldPosition(&loaded_track_preview, 0.0);
    const current_position = current.worldPosition(&loaded_track_preview, 0.0);
    const player_motion = rl.Vector3{
        .x = current_position.x - previous_position.x,
        .y = current_position.y - previous_position.y,
        .z = current_position.z - previous_position.z,
    };

    try std.testing.expectEqual(Kind.smoke, effect.kind);
    try std.testing.expectApproxEqAbs(@as(f32, 1.25), effect.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), effect.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.75), effect.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.1), effect.width, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), effect.height, 0.0001);
    try std.testing.expectEqual(@as(u8, 255), effect.tint.r);
    try std.testing.expectEqual(@as(u8, 191), effect.tint.g);
    try std.testing.expectEqual(@as(u8, 191), effect.tint.b);
    try std.testing.expectEqual(@as(u8, 255), effect.tint.a);
    try std.testing.expectApproxEqAbs(player_motion.x * 3.0, effect.velocity.x, 0.0001);
    try std.testing.expectApproxEqAbs(0.015 + (player_motion.y * 3.0), effect.velocity.y, 0.0001);
    try std.testing.expectApproxEqAbs((player_motion.z * 0.4) + (player_motion.z * 3.0), effect.velocity.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), effect.acceleration.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.0002), effect.acceleration.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), effect.acceleration.z, 0.0001);

    controller.update();
    const updated = controller.items[0];
    try std.testing.expectApproxEqAbs(effect.position.x + effect.velocity.x, updated.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(effect.position.y + effect.velocity.y, updated.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(effect.position.z + effect.velocity.z, updated.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(effect.velocity.x, updated.velocity.x, 0.0001);
    try std.testing.expectApproxEqAbs(effect.velocity.y - 0.0002, updated.velocity.y, 0.0001);
    try std.testing.expectApproxEqAbs(effect.velocity.z, updated.velocity.z, 0.0001);
}

test "jetpack particles use recovered armed lifecycle smoke packets" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.jetpack.arm();
    runner.jetpack.warning_intensity = 0.5;

    var controller = Controller{};
    controller.spawnJetParticleEffects(runner, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, 2), controller.count);
    const left = controller.items[0];
    const right = controller.items[1];

    try std.testing.expectEqual(Kind.smoke, left.kind);
    try std.testing.expectEqual(Kind.smoke, right.kind);
    try std.testing.expectApproxEqAbs(@as(f32, 0.29), left.width, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.29), left.height, 0.0001);
    try std.testing.expectEqual(@as(u16, 10), left.ticks_remaining);
    try std.testing.expectEqual(@as(u8, 160), left.tint.a);
    try std.testing.expect(left.position.x != right.position.x or left.position.z != right.position.z);
    try std.testing.expect(left.velocity.x != right.velocity.x or left.velocity.z != right.velocity.z);
}
