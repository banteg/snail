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

pub const max_active = 128;
pub const jet_particle_trail_count = 15;
pub const jet_particle_side_count = 2;
pub const jet_particle_count = jet_particle_trail_count * jet_particle_side_count;
pub const nuke_particle_count = gameplay.native_nuke_sprite_count;
const slug_goo_particle_count: usize = 70;
const slug_goo_width_scale: f32 = 0.30000001;
const slug_goo_height_scale: f32 = 1.2;
const slug_goo_gravity_scale: f32 = -0.0099999998 * 2.2;
const slug_goo_lifetime_base: f32 = 0.60000002;
const slug_goo_lifetime_random_scale: f32 = 0.000015258789;
const slug_goo_spread_base: f32 = 0.2;
const slug_goo_spread_random_scale: f32 = 0.0000061035157;
const slug_goo_size_base: f32 = 0.25;
const slug_goo_size_random_scale: f32 = 0.000030517578 * 0.75;
const slug_goo_vertical_random_base: f32 = 0.30000001;
const slug_goo_signed_velocity_scale: f32 = 0.000061035156;
const slug_goo_positive_velocity_scale: f32 = 0.000030517578;
const slug_goo_spawn_velocity_offset_scale: f32 = 0.00030517578;
const slug_goo_tint_base: f32 = 0.69999999;
const slug_goo_tint_random_scale: f32 = 0.0000091552738;
const jet_particle_trail_step: f32 = 0.071428575;
const jet_particle_width_random_base: f32 = 0.12;
const jet_particle_back_random_base: f32 = 0.40000001;
const jet_particle_random_scale: f32 = 0.0000015258789;
const jet_particle_detached_random_scale: f32 = 0.000030517578;
const jet_particle_detached_chance_threshold: f32 = 0.89999998;
const jet_particle_detached_velocity_scale: f32 = 0.85000002;
const jet_particle_detached_width: f32 = 0.100000001;
const jet_particle_detached_height: f32 = 0.300000012;
const jet_particle_detached_acceleration_y: f32 = 0.00100000005;
const jet_particle_detached_ticks: u16 = 18;
const rocket_smoke_width: f32 = 0.1;
const rocket_smoke_height: f32 = 0.5;
const rocket_smoke_ticks: u16 = 12;

pub const Kind = enum {
    explode_big,
    explode_small,
    slug_goo,
    garbage_smoke,
    smoke,
};

pub const Effect = struct {
    active: bool = false,
    kind: Kind = .explode_small,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    acceleration: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    scale_start: f32 = 0.8,
    scale_end: f32 = 0.8,
    tint: rl.Color = .white,
    ticks_remaining: u16 = 0,
    total_ticks: u16 = 0,
};

pub const JetParticle = struct {
    active: bool = false,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    width: f32 = 0.0,
    height: f32 = 0.0,
    tint: rl.Color = .white,
};

pub const NukeParticle = struct {
    active: bool = false,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    width: f32 = 0.0,
    height: f32 = 0.0,
    tint: rl.Color = .white,
};

pub const Controller = struct {
    items: [max_active]Effect = [_]Effect{.{}} ** max_active,
    jet_particles: [jet_particle_count]JetParticle = [_]JetParticle{.{}} ** jet_particle_count,
    nuke_particles: [nuke_particle_count]NukeParticle = [_]NukeParticle{.{}} ** nuke_particle_count,
    count: usize = 0,
    visual_random_state: u32 = 0x4df904,

    pub fn clear(self: *Controller) void {
        self.count = 0;
        for (&self.items) |*effect| {
            effect.active = false;
        }
        self.clearJetParticles();
        self.clearNukeParticles();
    }

    pub fn clearJetParticles(self: *Controller) void {
        for (&self.jet_particles) |*particle| {
            particle.* = .{};
        }
    }

    pub fn clearNukeParticles(self: *Controller) void {
        for (&self.nuke_particles) |*particle| {
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

    pub fn activeNukeParticleCount(self: *const Controller) usize {
        var active: usize = 0;
        for (self.nuke_particles) |particle| {
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
        scale_start: f32,
        scale_end: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        self.spawnWithPhysics(
            kind,
            position,
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            scale_start,
            scale_end,
            ticks_remaining,
            tint,
        );
    }

    pub fn spawnWithVelocity(
        self: *Controller,
        kind: Kind,
        position: rl.Vector3,
        velocity: rl.Vector3,
        scale_start: f32,
        scale_end: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        self.spawnWithPhysics(
            kind,
            position,
            velocity,
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            scale_start,
            scale_end,
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
        scale_start: f32,
        scale_end: f32,
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
            .scale_start = scale_start,
            .scale_end = scale_end,
            .tint = tint,
            .ticks_remaining = ticks_remaining,
            .total_ticks = ticks_remaining,
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
        if (current.nuke.active) {
            self.updateNukeParticleBank(current, preview);
        } else if (previous.nuke.active) {
            self.clearNukeParticles();
        }
        if (current.counters.health_pickups > previous.counters.health_pickups) {
            self.spawnHealthPickupEffects(current, preview);
        }
        if (current.jetpack.jet_particles_active) {
            self.updateJetParticleBank(current, preview);
        } else if (previous.jetpack.jet_particles_active) {
            self.clearJetParticles();
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits or current.counters.salt_hits > previous.counters.salt_hits) {
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
        if (current.counters.rocket_smoke_particles > previous.counters.rocket_smoke_particles) {
            self.spawnRocketSmokeParticles(current);
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
                self.spawnSlugGooBurst(current, preview, defeated);
            }
        }
    }

    // PORT(verified): native `initialize_nuke` allocates 25 sprites, sets each
    // size lane to 3.0, and `update_nuke` places them at
    // `(sin(i * 0.04 * tau + phase) * 7, cos(...) * 7, orbit_axis)` while the
    // player-side controller remains active.
    pub fn updateNukeParticleBank(
        self: *Controller,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        if (!current.nuke.active) {
            self.clearNukeParticles();
            return;
        }

        const origin = current.worldPosition(preview, 0.52);
        for (0..nuke_particle_count) |index| {
            const phase = (@as(f32, @floatFromInt(index)) * 0.039999999 * std.math.tau) + current.nuke.phase;
            self.nuke_particles[index] = .{
                .active = true,
                .position = .{
                    .x = origin.x + (@sin(phase) * gameplay.native_nuke_orbit_radius),
                    .y = origin.y + (@cos(phase) * gameplay.native_nuke_orbit_radius),
                    .z = current.nuke.orbit_axis,
                },
                .width = 3.0,
                .height = 3.0,
                .tint = .white,
            };
        }
    }

    // PORT(verified): native `spawn_garbage_smoke_particle` allocates sprite
    // ref 33 (`SPRITES/JET.TGA`) from the live garbage object's current
    // position, copies `garbage.velocity * 0.2`, and seeds the sprite scale
    // interpolation lanes to `0.3 -> 1.3`.
    pub fn spawnGarbageSmokeParticle(self: *Controller, current: gameplay.Runner) void {
        const smoke_origin = current.last_garbage_smoke_position orelse current.last_garbage_hit_position orelse return;
        self.spawnWithVelocity(
            .garbage_smoke,
            smoke_origin,
            current.last_garbage_smoke_velocity,
            0.3,
            1.3,
            8,
            .white,
        );
    }

    // PORT(verified): native `spawn_golb_smoke` emits `SMOKE.TGA` from a
    // rocket-family Golb shot at the current body position and a half-step
    // trailing position, with sprite scale lanes seeded to `0.1 -> 0.5` and
    // velocity copied from `projectile_velocity * 0.4`.
    pub fn spawnRocketSmokeParticles(self: *Controller, current: gameplay.Runner) void {
        for (current.last_rocket_smoke_positions) |position| {
            self.spawnWithVelocity(
                .smoke,
                position,
                current.last_rocket_smoke_velocity,
                rocket_smoke_width,
                rocket_smoke_height,
                rocket_smoke_ticks,
                .white,
            );
        }
    }

    // PORT(verified): native `explode_slug_hazard` allocates 70 SLUGGOO
    // sprites from the live slug center, randomizes each size/color/velocity,
    // and applies a shared downward acceleration of `run_rate^2 * -0.022`.
    pub fn spawnSlugGooBurst(
        self: *Controller,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
        defeated: gameplay.RowTarget,
    ) void {
        const origin = laneWorldPosition(preview, defeated.row, defeated.lane, 1.7);
        const run_rate = @max(current.track_center_x, 0.001);
        for (0..slug_goo_particle_count) |_| {
            const spread = self.nextNativeVisualRandomFloatScaled(slug_goo_spread_random_scale) + slug_goo_spread_base;
            const size_seed = self.nextNativeVisualRandomFloatScaled(slug_goo_size_random_scale) + slug_goo_size_base;
            const lifetime_factor = self.nextNativeVisualRandomFloatScaled(slug_goo_lifetime_random_scale) + slug_goo_lifetime_base;
            const tint_factor = self.nextNativeVisualRandomFloatScaled(slug_goo_tint_random_scale) + slug_goo_tint_base;
            const velocity = rl.Vector3{
                .x = self.nextNativeVisualRandomSignedFloatScaled(spread * slug_goo_signed_velocity_scale) * run_rate,
                .y = self.nextNativeVisualRandomFloatScaled((spread + slug_goo_vertical_random_base) * slug_goo_positive_velocity_scale) * run_rate,
                .z = self.nextNativeVisualRandomFloatScaled(spread * slug_goo_positive_velocity_scale) * run_rate,
            };
            const spawn_fraction = self.nextNativeVisualRandomFloatScaled(slug_goo_spawn_velocity_offset_scale);
            const position = rl.Vector3{
                .x = origin.x + (velocity.x * spawn_fraction),
                .y = origin.y + (velocity.y * spawn_fraction),
                .z = origin.z + (velocity.z * spawn_fraction),
            };
            const lifetime_ticks: u16 = @intFromFloat(@max(1.0, @ceil((lifetime_factor * 60.0) / run_rate)));
            const tint_channel: u8 = @intFromFloat(@min(255.0, @max(0.0, tint_factor * 255.0)));
            self.spawnWithPhysics(
                .slug_goo,
                position,
                velocity,
                .{
                    .x = 0.0,
                    .y = (run_rate * run_rate) * slug_goo_gravity_scale,
                    .z = 0.0,
                },
                size_seed * slug_goo_width_scale,
                size_seed * slug_goo_height_scale,
                lifetime_ticks,
                .{ .r = tint_channel, .g = tint_channel, .b = tint_channel, .a = 255 },
            );
        }
    }

    // PORT(partial): native `update_jet_particles` drives a 15x2 persistent
    // SMOKE.TGA sprite bank from the two jet nozzles, then occasionally
    // allocates one detached smoke sprite from the trail tip. The native sprite
    // manager's owner-side retirement is represented here by the generic effect
    // lifetime.
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
        const back_seed = self.nextJetParticleRandomSeed(jet_particle_back_random_base);
        const width_seed = self.nextJetParticleRandomSeed(jet_particle_width_random_base);

        for (0..jet_particle_trail_count) |trail_index| {
            const progress = @as(f32, @floatFromInt(trail_index)) * jet_particle_trail_step;
            const size = (1.0 - progress) * width_seed * intensity;
            const back_offset = -(progress * back_seed * intensity);

            for (0..jet_particle_side_count) |side_index| {
                const side: f32 = if (side_index == 0) -0.16 else 0.16;
                const nozzle = offsetPosition(origin, right, up, forward, side, -0.03, -0.24);
                const bank_index = (trail_index * jet_particle_side_count) + side_index;
                const particle_position = rl.Vector3{
                    .x = nozzle.x + (forward.x * back_offset),
                    .y = nozzle.y + (forward.y * back_offset),
                    .z = nozzle.z + (forward.z * back_offset),
                };
                self.jet_particles[bank_index] = .{
                    .active = true,
                    .position = particle_position,
                    .width = size,
                    .height = size,
                    .tint = .white,
                };

                if (trail_index + 1 == jet_particle_trail_count and self.nextJetParticleRandom01() > jet_particle_detached_chance_threshold) {
                    self.spawnJetParticleDetachedPuff(particle_position, current);
                }
            }
        }
    }

    fn nextJetParticleRandomSeed(self: *Controller, base: f32) f32 {
        self.visual_random_state = self.visual_random_state *% 1103515245 +% 12345;
        const raw: u32 = (self.visual_random_state >> 16) & 0x7FFF;
        return (@as(f32, @floatFromInt(raw)) * jet_particle_random_scale) + base;
    }

    fn nextJetParticleRandom01(self: *Controller) f32 {
        self.visual_random_state = self.visual_random_state *% 1103515245 +% 12345;
        const raw: u32 = (self.visual_random_state >> 16) & 0x7FFF;
        return @as(f32, @floatFromInt(raw)) * jet_particle_detached_random_scale;
    }

    fn nextNativeVisualRandomInt15(self: *Controller) u32 {
        self.visual_random_state = (self.visual_random_state *% 0x343fd) +% 0x269ec3;
        return (self.visual_random_state >> 16) & 0x7fff;
    }

    fn nextNativeVisualRandomFloatScaled(self: *Controller, scale: f32) f32 {
        return @as(f32, @floatFromInt(self.nextNativeVisualRandomInt15())) * scale;
    }

    fn nextNativeVisualRandomSignedFloatScaled(self: *Controller, scale: f32) f32 {
        return (@as(f32, @floatFromInt(self.nextNativeVisualRandomInt15())) - 16384.0) * scale;
    }

    fn spawnJetParticleDetachedPuff(self: *Controller, position: rl.Vector3, current: gameplay.Runner) void {
        const player_velocity = current.nativeVelocityPerTick();
        self.spawnWithPhysics(
            .smoke,
            position,
            .{
                .x = player_velocity.x * jet_particle_detached_velocity_scale,
                .y = player_velocity.y * jet_particle_detached_velocity_scale,
                .z = player_velocity.z * jet_particle_detached_velocity_scale,
            },
            .{
                .x = 0.0,
                .y = jet_particle_detached_acceleration_y,
                .z = 0.0,
            },
            jet_particle_detached_width,
            jet_particle_detached_height,
            jet_particle_detached_ticks,
            .white,
        );
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
    try std.testing.expectApproxEqAbs(@as(f32, 0.1), effect.scale_start, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), effect.scale_end, 0.0001);
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

test "garbage smoke uses native jet sprite packet" {
    var controller = Controller{};
    var current = gameplay.Runner{};
    current.last_garbage_smoke_position = .{ .x = 1.25, .y = 2.5, .z = 3.75 };
    current.last_garbage_smoke_velocity = .{ .x = 0.1, .y = 0.2, .z = 0.3 };

    controller.spawnGarbageSmokeParticle(current);

    try std.testing.expectEqual(@as(usize, 1), controller.count);
    const effect = controller.items[0];
    try std.testing.expectEqual(Kind.garbage_smoke, effect.kind);
    try std.testing.expectApproxEqAbs(@as(f32, 1.25), effect.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), effect.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.75), effect.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.1), effect.velocity.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), effect.velocity.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.3), effect.velocity.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.3), effect.scale_start, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.3), effect.scale_end, 0.0001);
    try std.testing.expectEqual(@as(u16, 8), effect.ticks_remaining);
}

test "rocket smoke uses recovered golb smoke packet" {
    var controller = Controller{};
    var current = gameplay.Runner{};
    current.counters.rocket_smoke_particles = 2;
    current.last_rocket_smoke_positions = .{
        .{ .x = 1.0, .y = 2.0, .z = 3.0 },
        .{ .x = 1.0, .y = 2.0, .z = 2.8 },
    };
    current.last_rocket_smoke_velocity = .{ .x = 0.01, .y = 0.02, .z = 0.03 };

    controller.spawnRocketSmokeParticles(current);

    try std.testing.expectEqual(@as(usize, 2), controller.count);
    for (controller.items[0..2], current.last_rocket_smoke_positions) |effect, position| {
        try std.testing.expectEqual(Kind.smoke, effect.kind);
        try std.testing.expectApproxEqAbs(position.x, effect.position.x, 0.0001);
        try std.testing.expectApproxEqAbs(position.y, effect.position.y, 0.0001);
        try std.testing.expectApproxEqAbs(position.z, effect.position.z, 0.0001);
        try std.testing.expectApproxEqAbs(rocket_smoke_width, effect.scale_start, 0.0001);
        try std.testing.expectApproxEqAbs(rocket_smoke_height, effect.scale_end, 0.0001);
        try std.testing.expectApproxEqAbs(current.last_rocket_smoke_velocity.x, effect.velocity.x, 0.0001);
        try std.testing.expectApproxEqAbs(current.last_rocket_smoke_velocity.y, effect.velocity.y, 0.0001);
        try std.testing.expectApproxEqAbs(current.last_rocket_smoke_velocity.z, effect.velocity.z, 0.0001);
        try std.testing.expectEqual(rocket_smoke_ticks, effect.ticks_remaining);
    }
}

test "slug death spawns the native goo burst instead of one static sprite" {
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

    var controller = Controller{};
    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.track_center_x = 1.0;
    controller.spawnSlugGooBurst(runner, &loaded_track_preview, .{ .row = 12, .lane = 1 });

    try std.testing.expectEqual(slug_goo_particle_count, controller.count);

    const origin = laneWorldPosition(&loaded_track_preview, 12, 1, 1.7);
    const first = controller.items[0];
    try std.testing.expectEqual(Kind.slug_goo, first.kind);
    try std.testing.expect(first.position.y >= origin.y);
    try std.testing.expect(first.scale_start >= slug_goo_size_base * slug_goo_width_scale);
    try std.testing.expect(first.scale_start <= (slug_goo_size_base + 0.75) * slug_goo_width_scale);
    try std.testing.expect(first.scale_end >= slug_goo_size_base * slug_goo_height_scale);
    try std.testing.expect(first.scale_end <= (slug_goo_size_base + 0.75) * slug_goo_height_scale);
    try std.testing.expectApproxEqAbs(slug_goo_gravity_scale, first.acceleration.y, 0.0001);
    try std.testing.expect(first.ticks_remaining >= 36);
    try std.testing.expect(first.ticks_remaining <= 66);
    try std.testing.expect(first.tint.r >= 178);
    try std.testing.expectEqual(first.tint.r, first.tint.g);
    try std.testing.expectEqual(first.tint.r, first.tint.b);
    try std.testing.expectEqual(@as(u8, 255), first.tint.a);
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
    const initial_visual_random_state = controller.visual_random_state;
    controller.updateJetParticleBank(runner, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, 0), controller.count);
    try std.testing.expectEqual(@as(usize, jet_particle_count), controller.activeJetParticleCount());
    try std.testing.expect(controller.visual_random_state != initial_visual_random_state);
    const left = controller.jet_particles[0];
    const right = controller.jet_particles[1];
    const trail_tip = controller.jet_particles[jet_particle_count - 1];

    try std.testing.expect(left.active);
    try std.testing.expect(right.active);
    try std.testing.expect(left.width >= 0.06);
    try std.testing.expect(left.width <= 0.085);
    try std.testing.expectApproxEqAbs(left.width, left.height, 0.0001);
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

test "jetpack trail tip can emit recovered detached smoke puff" {
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
    runner.jetpack.warning_intensity = 1.0;
    runner.native_velocity_x_per_tick = 0.02;
    runner.velocity_y = 0.03;
    runner.native_velocity_z_override_per_tick = -0.04;

    var controller = Controller{};
    controller.visual_random_state = 5;
    controller.updateJetParticleBank(runner, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, jet_particle_count), controller.activeJetParticleCount());
    try std.testing.expectEqual(@as(usize, 1), controller.count);
    const effect = controller.items[0];
    const right_tip = controller.jet_particles[jet_particle_count - 1];

    try std.testing.expectEqual(Kind.smoke, effect.kind);
    try std.testing.expectApproxEqAbs(right_tip.position.x, effect.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(right_tip.position.y, effect.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(right_tip.position.z, effect.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(jet_particle_detached_width, effect.scale_start, 0.0001);
    try std.testing.expectApproxEqAbs(jet_particle_detached_height, effect.scale_end, 0.0001);
    try std.testing.expectApproxEqAbs(runner.nativeVelocityPerTick().x * jet_particle_detached_velocity_scale, effect.velocity.x, 0.0001);
    try std.testing.expectApproxEqAbs(runner.nativeVelocityPerTick().y * jet_particle_detached_velocity_scale, effect.velocity.y, 0.0001);
    try std.testing.expectApproxEqAbs(runner.nativeVelocityPerTick().z * jet_particle_detached_velocity_scale, effect.velocity.z, 0.0001);
    try std.testing.expectApproxEqAbs(jet_particle_detached_acceleration_y, effect.acceleration.y, 0.0001);
    try std.testing.expectEqual(jet_particle_detached_ticks, effect.ticks_remaining);
}

test "explode ring nuke uses native 25 sprite orbit bank" {
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
    runner.nuke = .{
        .active = true,
        .orbit_axis = 12.0,
        .phase = 0.0,
    };

    var controller = Controller{};
    controller.updateNukeParticleBank(runner, &loaded_track_preview);

    try std.testing.expectEqual(@as(usize, nuke_particle_count), controller.activeNukeParticleCount());
    const origin = runner.worldPosition(&loaded_track_preview, 0.52);
    const first = controller.nuke_particles[0];
    const opposite = controller.nuke_particles[nuke_particle_count / 2];
    try std.testing.expect(first.active);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), first.width, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), first.height, 0.0001);
    try std.testing.expectApproxEqAbs(origin.x, first.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(origin.y + gameplay.native_nuke_orbit_radius, first.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), first.position.z, 0.0001);
    try std.testing.expect(opposite.position.y < origin.y);

    runner.nuke.active = false;
    controller.spawnRunnerEffects(
        blk: {
            var previous = runner;
            previous.nuke.active = true;
            break :blk previous;
        },
        runner,
        &loaded_track_preview,
    );
    try std.testing.expectEqual(@as(usize, 0), controller.activeNukeParticleCount());
}
