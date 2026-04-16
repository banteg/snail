//! Hazard / pickup / ring-effect runtime pools.
//!
//! Mirrors the three per-row windowed pools the native subgame maintains:
//! - garbage/salt/slug hazards (ambient + authored) — 128 slots
//! - health/jetpack pickups — 9 slots
//! - ring effects (slow/explode/powerup bursts) — 2 slots
//!
//! Methods that only touch the pool itself live here (add / count / reset /
//! find / consume). Methods that cross-read other Runner fields (damage,
//! score, snail_skin, preview) still live on Runner and reach in through
//! the pool fields.

const gameplay_runtime_entities = @import("runtime_entities.zig");

const RuntimeHazard = gameplay_runtime_entities.Hazard;
const RuntimeHazardKind = gameplay_runtime_entities.HazardKind;
const RuntimePickup = gameplay_runtime_entities.Pickup;
const RuntimePickupKind = gameplay_runtime_entities.PickupKind;
const RuntimeRingEffect = gameplay_runtime_entities.RingEffect;

pub const max_active_health_pickups: usize = 8;
pub const max_active_jetpack_pickups: usize = 1;
pub const max_active_runtime_pickups: usize = max_active_health_pickups + max_active_jetpack_pickups;
pub const max_active_runtime_hazards: usize = 128;
pub const max_active_runtime_ring_effects: usize = 2;

pub const HazardPool = struct {
    slots: [max_active_runtime_hazards]RuntimeHazard = [_]RuntimeHazard{
        .{ .row = 0, .lane = 0, .kind = .garbage },
    } ** max_active_runtime_hazards,
    count: usize = 0,
    last_scan_end: usize = 0,

    pub fn reset(self: *HazardPool) void {
        self.* = .{};
    }

    pub fn active(self: *const HazardPool) []const RuntimeHazard {
        return self.slots[0..self.count];
    }

    /// Returns true if a hazard at (row, lane, kind) is already in the live
    /// window. Used by the refresh-live pass to dedupe authored + ambient
    /// spawn candidates.
    pub fn contains(self: *const HazardPool, row: usize, lane: usize, kind: RuntimeHazardKind) bool {
        for (0..self.count) |i| {
            const h = self.slots[i];
            if (h.row == row and h.lane == lane and h.kind == kind) return true;
        }
        return false;
    }
};

pub const PickupPool = struct {
    slots: [max_active_runtime_pickups]RuntimePickup = [_]RuntimePickup{
        .{ .row = 0, .lane = 0, .kind = .health },
    } ** max_active_runtime_pickups,
    count: usize = 0,
    last_scan_end: usize = 0,

    pub fn reset(self: *PickupPool) void {
        self.* = .{};
    }

    pub fn active(self: *const PickupPool) []const RuntimePickup {
        return self.slots[0..self.count];
    }

    pub fn countOfKind(self: *const PickupPool, kind: RuntimePickupKind) usize {
        var total: usize = 0;
        for (0..self.count) |i| {
            if (self.slots[i].kind == kind) total += 1;
        }
        return total;
    }
};

pub const RingPool = struct {
    slots: [max_active_runtime_ring_effects]RuntimeRingEffect = [_]RuntimeRingEffect{
        .{ .source_row = 0, .row = 0, .lane = 0, .kind = 0 },
    } ** max_active_runtime_ring_effects,
    count: usize = 0,
    last_scan_end: usize = 0,
    last_spawn_z: f32 = -1000.0,

    pub fn reset(self: *RingPool) void {
        self.* = .{};
    }

    pub fn active(self: *const RingPool) []const RuntimeRingEffect {
        return self.slots[0..self.count];
    }
};

/// All three hazard-family pools grouped. Mirrors the tripartite pool layout
/// in the native subgame memory.
pub const Runtime = struct {
    hazards: HazardPool = .{},
    pickups: PickupPool = .{},
    rings: RingPool = .{},

    pub fn reset(self: *Runtime) void {
        self.* = .{};
    }
};
