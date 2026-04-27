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
pub const jet_particle_trail_count = 15;
pub const jet_particle_side_count = 2;
pub const jet_particle_count = jet_particle_trail_count * jet_particle_side_count;
const jet_particle_trail_step: f32 = 0.071428575;
const jet_particle_native_width_seed: f32 = 0.145;
const jet_particle_native_back_seed: f32 = 0.425;

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

pub const JetParticle = struct {
    active: bool = false,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    width: f32 = 0.0,
    height: f32 = 0.0,
    tint: rl.Color = .white,
};

pub const Controller = struct {
    items: [max_active]Effect = [_]Effect{.{}} ** max_active,
    jet_particles: [jet_particle_count]JetParticle = [_]JetParticle{.{}} ** jet_particle_count,
    count: usize = 0,

    pub fn clear(self: *Controller) void {
        self.count = 0;
        for (&self.items) |*effect| {
            effect.active = false;
        }
        self.clearJetParticles();
    }

    pub fn clearJetParticles(self: *Controller) void {
        for (&self.jet_particles) |*particle| {
            particle.* = .{};
        }
    }

    pub fn activeJetParticleCount(self: *const Controller) usize {
        var active: usize = 0;
        for (self.jet_particles) |particle| {
            if (particle.active) active += 1;
        }
        return active;
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
            self.spawnHealthPickupEffects(current, preview);
        }
        if (current.jetpack.jet_particles_active) {
            self.updateJetParticleBank(current, preview);
        } else if (previous.jetpack.jet_particles_active) {
            self.clearJetParticles();
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
        if (current.counters.garbage_smoke_particles > previous.counters.garbage_smoke_particles) {
            self.spawnGarbageSmokeParticle(current);
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

    // PORT(verified): native `spawn_garbage_smoke_particle` allocates one
    // `SMOKE.TGA` sprite from the live garbage object's current position,
    // copies `garbage.velocity * 0.2`, and seeds size lanes to `0.3 x 1.3`.
    pub fn spawnGarbageSmokeParticle(self: *Controller, current: gameplay.Runner) void {
        const smoke_origin = current.last_garbage_smoke_position orelse current.last_garbage_hit_position orelse return;
        self.spawnWithVelocity(
            .smoke,
            smoke_origin,
            current.last_garbage_smoke_velocity,
            0.3,
            1.3,
            8,
            .white,
        );
    }

    // PORT(partial): native `update_jet_particles` drives a 15x2 persistent
    // SMOKE.TGA sprite bank from the two jet nozzles. The port now models the
    // persistent bank directly; native per-frame RNG jitter and the occasional
    // detached puff from the trail tip are still pending.
    pub fn updateJetParticleBank(
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
        const intensity = std.math.clamp(current.jetpack.warning_intensity, 0.0, 1.0);

        for (0..jet_particle_trail_count) |trail_index| {
            const progress = @as(f32, @floatFromInt(trail_index)) * jet_particle_trail_step;
            const size = (1.0 - progress) * jet_particle_native_width_seed * intensity;
            const back_offset = -(progress * jet_particle_native_back_seed * intensity);

            for (0..jet_particle_side_count) |side_index| {
                const side: f32 = if (side_index == 0) -0.16 else 0.16;
                const nozzle = offsetPosition(origin, right, up, forward, side, -0.03, -0.24);
                const bank_index = (trail_index * jet_particle_side_count) + side_index;
                self.jet_particles[bank_index] = .{
                    .active = true,
                    .position = .{
                        .x = nozzle.x + (forward.x * back_offset),
                        .y = nozzle.y + (forward.y * back_offset),
                        .z = nozzle.z + (forward.z * back_offset),
                    },
                    .width = size,
                    .height = size,
                    .tint = .white,
                };
            }
        }
    }

    // PORT(verified): native `health_collect_particles` emits 8 `SMOKE.TGA`
    // sprites from the picked-up runtime slot. It offsets their spawn position
    // by `Player.velocity * 3`, then gives them only the radial sin/cos burst
    // plus `velocity.z * 0.4`.
    pub fn spawnHealthPickupEffects(
        self: *Controller,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const pickup_origin = current.last_health_pickup_position orelse current.worldPosition(preview, 0.34);
        const player_velocity = current.nativeVelocityPerTick();
        const particle_origin = rl.Vector3{
            .x = pickup_origin.x + (player_velocity.x * 3.0),
            .y = pickup_origin.y + (player_velocity.y * 3.0),
            .z = pickup_origin.z + (player_velocity.z * 3.0),
        };
        var particle_index: usize = 0;
        while (particle_index < 8) : (particle_index += 1) {
            const angle = @as(f32, @floatFromInt(particle_index)) * 0.78539819;
            self.spawnWithPhysics(
                .smoke,
                particle_origin,
                .{
                    .x = std.math.sin(angle) * 0.015,
                    .y = std.math.cos(angle) * 0.015,
                    .z = player_velocity.z * 0.4,
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

    const previous = gameplay.Runner.init(&loaded_track_preview);
    var current = previous;
    current.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    current.last_health_pickup_position = .{ .x = 1.25, .y = 2.5, .z = 3.75 };
    current.native_velocity_x_per_tick = 0.025;
    current.velocity_y = 0.05;
    current.native_velocity_z_override_per_tick = -0.1;

    var controller = Controller{};
    controller.spawnHealthPickupEffects(current, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, 8), controller.count);
    const effect = controller.items[0];
    const player_velocity = current.nativeVelocityPerTick();

    try std.testing.expectEqual(Kind.smoke, effect.kind);
    try std.testing.expectApproxEqAbs(@as(f32, 1.25) + (player_velocity.x * 3.0), effect.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5) + (player_velocity.y * 3.0), effect.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.75) + (player_velocity.z * 3.0), effect.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.1), effect.width, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), effect.height, 0.0001);
    try std.testing.expectEqual(@as(u8, 255), effect.tint.r);
    try std.testing.expectEqual(@as(u8, 191), effect.tint.g);
    try std.testing.expectEqual(@as(u8, 191), effect.tint.b);
    try std.testing.expectEqual(@as(u8, 255), effect.tint.a);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), effect.velocity.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.015), effect.velocity.y, 0.0001);
    try std.testing.expectApproxEqAbs(player_velocity.z * 0.4, effect.velocity.z, 0.0001);
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

test "jetpack particles use recovered persistent nozzle bank" {
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
    controller.updateJetParticleBank(runner, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, 0), controller.count);
    try std.testing.expectEqual(@as(usize, jet_particle_count), controller.activeJetParticleCount());
    const left = controller.jet_particles[0];
    const right = controller.jet_particles[1];
    const trail_tip = controller.jet_particles[jet_particle_count - 1];

    try std.testing.expect(left.active);
    try std.testing.expect(right.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0725), left.width, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0725), left.height, 0.0001);
    try std.testing.expectEqual(@as(u8, 255), left.tint.a);
    try std.testing.expect(left.position.x != right.position.x or left.position.z != right.position.z);
    try std.testing.expect(trail_tip.width < left.width);
    try std.testing.expect(trail_tip.position.x != right.position.x or trail_tip.position.z != right.position.z);

    runner.jetpack.jet_particles_active = false;
    controller.spawnRunnerEffects(
        blk: {
            var previous = runner;
            previous.jetpack.jet_particles_active = true;
            break :blk previous;
        },
        runner,
        &loaded_track_preview,
    );
    try std.testing.expectEqual(@as(usize, 0), controller.activeJetParticleCount());
}
