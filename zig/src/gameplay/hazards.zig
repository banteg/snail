//! Hazard / pickup / ring-effect runtime pools.
//!
//! Mirrors the native pools the subgame maintains:
//! - `cRGarbageHazardPool` @ `game + 0x359140` — 50 slots (garbage)
//! - `cRSalt` @ `game + 0x3578c0` — 40 slots (authored/ambient salt)
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
const SaltSlot = gameplay_runtime_entities.SaltSlot;
const SaltSlotState = gameplay_runtime_entities.SaltSlotState;

pub const max_active_health_pickups: usize = 8;
pub const max_active_jetpack_pickups: usize = 1;
pub const max_active_runtime_pickups: usize = max_active_health_pickups + max_active_jetpack_pickups;
pub const max_active_runtime_hazards: usize = 128;
pub const max_active_runtime_ring_effects: usize = 2;
// PORT(verified): native `cRSalt @ game + 0x3578c0` has 40 slots with stride
// 0x98 (152 bytes per slot) per
// `artifacts/ida/functions/00441540-initialize_salt_hazard_pool.c`.
pub const max_active_salt_slots: usize = 40;

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

/// PORT(verified): 40-slot `cRSalt` projectile pool. Matches the layout at
/// `game + 0x3578c0` with per-slot lifetime progress + step, world position,
/// velocity, and yaw. `initialize_salt_hazard_pool` at
/// `artifacts/ida/functions/00441540-initialize_salt_hazard_pool.c` zeros the
/// state byte on every slot; `spawn_salt_hazard`
/// (`artifacts/ida/functions/00441560-spawn_salt_hazard.c`) allocates the
/// first inactive slot, seeds position, velocity, lifetime step from
/// `track_center_x * 0.033333335`, and a randomized Y rotation.
pub const SaltHazardPool = struct {
    slots: [max_active_salt_slots]SaltSlot = [_]SaltSlot{.{}} ** max_active_salt_slots,
    last_scan_end: usize = 0,

    pub fn reset(self: *SaltHazardPool) void {
        self.* = .{};
    }

    pub fn active(self: *const SaltHazardPool) []const SaltSlot {
        // The native pool does not keep a contiguous live prefix — slots are
        // reused in place. Callers should iterate all 40 and test state.
        return self.slots[0..];
    }

    pub fn allocate(self: *SaltHazardPool) ?*SaltSlot {
        for (&self.slots) |*slot| {
            if (slot.state == .inactive) return slot;
        }
        return null;
    }

    pub fn contains(self: *const SaltHazardPool, row: usize, lane: usize) bool {
        for (self.slots) |slot| {
            if (slot.state == .inactive) continue;
            if (slot.row == row and slot.lane == lane) return true;
        }
        return false;
    }

    pub fn countActive(self: *const SaltHazardPool) usize {
        var total: usize = 0;
        for (self.slots) |slot| {
            if (slot.state != .inactive) total += 1;
        }
        return total;
    }
};

/// All hazard-family pools grouped. Mirrors the native subgame memory layout:
/// separate garbage, salt, pickup, and ring pools.
pub const Runtime = struct {
    hazards: HazardPool = .{},
    salts: SaltHazardPool = .{},
    pickups: PickupPool = .{},
    rings: RingPool = .{},

    pub fn reset(self: *Runtime) void {
        self.* = .{};
    }
};
