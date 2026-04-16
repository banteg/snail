//! Projectile + turret runtime pools.
//!
//! Native references:
//! - Subgoldy weapon lanes fire projectiles from `movement_flags` selectors
//!   (`update_player_movement_flags` / `play_movement_state_sound`).
//! - Turret rows (`=` glyph / runtime tile 0x1e) spawn their own projectile
//!   flashes per row via `update_subgame`.
//!
//! The manager here holds the active pools; Runner still owns the spawn +
//! step methods because they cross-read the motion / attachment / damage
//! state.

const gameplay_runtime_entities = @import("runtime_entities.zig");
const runner_state = @import("runner_state.zig");

const Projectile = runner_state.Projectile;
const TurretState = gameplay_runtime_entities.TurretState;

pub const max_active_projectiles: usize = 16;
pub const max_active_turret_states: usize = 64;

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

pub const TurretPool = struct {
    slots: [max_active_turret_states]TurretState = [_]TurretState{
        .{ .row = 0, .lane = 0 },
    } ** max_active_turret_states,
    count: usize = 0,

    pub fn reset(self: *TurretPool) void {
        self.* = .{};
    }

    pub fn active(self: *const TurretPool) []const TurretState {
        return self.slots[0..self.count];
    }
};

pub const Combat = struct {
    projectiles: ProjectilePool = .{},
    turrets: TurretPool = .{},

    pub fn reset(self: *Combat) void {
        self.* = .{};
    }
};
