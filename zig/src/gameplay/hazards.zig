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

const std = @import("std");
const rl = @import("raylib");

const gameplay_runtime_entities = @import("runtime_entities.zig");

const RuntimeHazard = gameplay_runtime_entities.Hazard;
const RuntimeHazardKind = gameplay_runtime_entities.HazardKind;
const RuntimePickup = gameplay_runtime_entities.Pickup;
const RuntimePickupKind = gameplay_runtime_entities.PickupKind;
const RuntimeRingEffect = gameplay_runtime_entities.RingEffect;
const SaltSlot = gameplay_runtime_entities.SaltSlot;
const SaltSlotState = gameplay_runtime_entities.SaltSlotState;

// PORT(verified): `spawn_salt_hazard`
// (`artifacts/ida/functions/00441560-spawn_salt_hazard.c:29`) seeds the
// lifetime step as `track_center_x * 0.033333335`. With the port's fixed
// `track_center_x = 4.0` this gives `0.133333` per tick, matching the ~7.5
// tick (~0.125s) lifetime ceiling native's `update_salt_hazard` expects.
pub const native_salt_lifetime_step_factor: f32 = 0.033333335;
// PORT(verified): `next_math_random_value` returns `[-16384, 16384]`;
// `spawn_salt_hazard` multiplies the centered value by `0.0001917476` to get
// the initial Y-rotation angle (`0.0001917476 ≈ tau / 32768`).
pub const native_salt_yaw_random_scale: f32 = 0.0001917476;

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

    // PORT(verified): mirror of `spawn_salt_hazard`
    // (`artifacts/ida/functions/00441560-spawn_salt_hazard.c`). Allocates
    // the first inactive slot, marks it active, seeds position + velocity
    // from the caller's Vec3 inputs, initializes the lifetime step from
    // `track_center_x * 0.033333335`, and rolls a random Y-rotation on the
    // spawn frame.
    pub fn spawn(
        self: *SaltHazardPool,
        row: usize,
        lane: usize,
        world_position: rl.Vector3,
        velocity: rl.Vector3,
        track_center_x: f32,
        random_state: *u32,
    ) ?*SaltSlot {
        const slot = self.allocate() orelse return null;
        slot.* = .{
            .state = .active,
            .row = row,
            .lane = lane,
            .world_position = world_position,
            .velocity = velocity,
            .lifetime_progress = 0.0,
            .lifetime_step = track_center_x * native_salt_lifetime_step_factor,
            .yaw_radians = nextSaltYawRadians(random_state),
        };
        return slot;
    }

    // PORT(verified): mirror of `update_salt_hazard`
    // (`artifacts/ida/functions/004417d0-update_salt_hazard.c`). Each active
    // slot advances its lifetime counter by `lifetime_step` per tick; once
    // the counter crosses `1.0` the slot transitions to `removing` for
    // cleanup on the next tick. While active, position integrates by
    // velocity.  The track-attachment collision + screen-bounds check in
    // native lines 45-91 lives on the Runner side (it has to reach into
    // the preview's installed attachment slots).
    pub fn tickActiveSlots(self: *SaltHazardPool) void {
        for (&self.slots) |*slot| {
            switch (slot.state) {
                .inactive => {},
                .active => {
                    slot.lifetime_progress += slot.lifetime_step;
                    if (slot.lifetime_progress > 1.0) {
                        slot.state = .removing;
                        continue;
                    }
                    slot.world_position.x += slot.velocity.x;
                    slot.world_position.y += slot.velocity.y;
                    slot.world_position.z += slot.velocity.z;
                },
                .removing => {
                    // PORT(verified): native `update_salt_hazard` state-2
                    // branch (lines 94-128) unlinks the slot from the
                    // intrusive list and flips the active byte back to 0.
                    // The port's pool is a plain array (no intrusive list
                    // machinery), so removing just marks the slot inactive
                    // so `allocate` can reuse it.
                    slot.state = .inactive;
                },
            }
        }
    }

    // PORT(verified): mirror of `deactivate_salt_hazard`
    // (`artifacts/ida/functions/00441740-deactivate_salt_hazard.c`) — called
    // by the collision/attachment-exit paths to retire a slot immediately
    // rather than waiting for the lifetime counter. Native unlinks from the
    // live list and clears the list-flag bit; the port just flips the
    // state byte.
    pub fn deactivate(_: *SaltHazardPool, slot: *SaltSlot) void {
        slot.state = .inactive;
    }
};

// `next_math_random_value()` returns a signed value in `[-16384, 16384]`
// (native `random()` shifted to zero-center). `spawn_salt_hazard` centers
// the output by subtracting `16384.0` from the raw `0..32768` value, then
// scales by `0.0001917476` (≈ `tau / 32768`) to get the Y-rotation angle.
// The port keeps its own LCG state per-Runner, so the helper just wraps
// `random_state` advancement + native-style centering + scale.
fn nextSaltYawRadians(random_state: *u32) f32 {
    random_state.* = random_state.* *% 1103515245 +% 12345;
    const raw: u32 = (random_state.* >> 16) & 0x7FFF;
    const centered = @as(f32, @floatFromInt(@as(i32, @intCast(raw)))) - 16384.0;
    return centered * native_salt_yaw_random_scale;
}

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
