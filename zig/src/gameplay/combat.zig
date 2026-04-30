//! Projectile runtime pools.
//!
//! Native references:
//! - Subgoldy weapon lanes fire projectiles from `movement_flags` selectors
//!   (`update_player_movement_flags` / `play_movement_state_sound`).
//! The manager here holds the 12 native Golb emitter slots; Runner still owns
//! the spawn + step methods because they cross-read motion / attachment state.

const std = @import("std");

pub const max_active_projectiles: usize = 12;

pub const Projectile = struct {
    pub const Kind = enum {
        turbo,
        laser,
        rocket,
        sub_lazer,
    };

    pub const TrailPoint = struct {
        x: f32 = 0.0,
        y: f32 = 0.0,
        z: f32 = 0.0,
    };

    pub const max_trail_points: usize = 4;

    active: bool = false,
    kind: Kind = .turbo,
    world_x: f32 = 0.0,
    world_y: f32 = 0.0,
    world_z: f32 = 0.0,
    dir_x: f32 = 0.0,
    dir_y: f32 = 0.0,
    dir_z: f32 = 1.0,
    speed_rows_per_second: f32 = 0.0,
    bounced_off_slug: bool = false,
    trail_points: [max_trail_points]TrailPoint = [_]TrailPoint{.{}} ** max_trail_points,
    trail_count: u8 = 0,

    pub fn resetTrail(self: *Projectile) void {
        self.trail_points = [_]TrailPoint{.{}} ** max_trail_points;
        self.trail_count = 0;
        self.appendTrailPoint();
    }

    pub fn appendTrailPoint(self: *Projectile) void {
        const point = TrailPoint{
            .x = self.world_x,
            .y = self.world_y,
            .z = self.world_z,
        };
        if (self.trail_count < max_trail_points) {
            self.trail_points[self.trail_count] = point;
            self.trail_count += 1;
            return;
        }
        for (0..max_trail_points - 1) |index| {
            self.trail_points[index] = self.trail_points[index + 1];
        }
        self.trail_points[max_trail_points - 1] = point;
    }
};

pub const ProjectilePool = struct {
    slots: [max_active_projectiles]Projectile = [_]Projectile{.{}} ** max_active_projectiles,
    count: usize = 0,

    pub fn reset(self: *ProjectilePool) void {
        self.* = .{};
    }

    pub fn active(self: *const ProjectilePool) []const Projectile {
        return self.slots[0..self.count];
    }
};

pub const Combat = struct {
    projectiles: ProjectilePool = .{},

    pub fn reset(self: *Combat) void {
        self.* = .{};
    }
};

test "projectile trail keeps the native vapour point window" {
    var projectile = Projectile{
        .world_x = 1.0,
        .world_y = 2.0,
        .world_z = 3.0,
    };
    projectile.resetTrail();
    try std.testing.expectEqual(@as(u8, 1), projectile.trail_count);
    try std.testing.expectEqual(@as(f32, 3.0), projectile.trail_points[0].z);

    inline for (0..Projectile.max_trail_points) |index| {
        projectile.world_z = @floatFromInt(4 + index);
        projectile.appendTrailPoint();
    }

    try std.testing.expectEqual(@as(u8, Projectile.max_trail_points), projectile.trail_count);
    try std.testing.expectEqual(@as(f32, 4.0), projectile.trail_points[0].z);
    try std.testing.expectEqual(@as(f32, 7.0), projectile.trail_points[Projectile.max_trail_points - 1].z);
}
