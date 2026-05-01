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
//! score, presentation.snail_skin, preview) still live on Runner and reach in through
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
const SubLazerSlot = gameplay_runtime_entities.SubLazerSlot;
const SubLazerSlotState = gameplay_runtime_entities.SubLazerSlotState;

// PORT(verified): `spawn_salt_hazard`
// (`artifacts/ida/functions/00441560-spawn_salt_hazard.c:29`) seeds the
// salt slot's Y velocity (`+0x90`) as `track_center_x * 0.033333335`.
// `+0x9c`, the lifetime-step field consumed by `update_salt_hazard`, is not
// initialized by spawn and remains zero in the reset pool. Salt therefore
// rises from its anchor instead of timing out after a few frames.
pub const native_salt_vertical_velocity_factor: f32 = 0.033333335;
// PORT(verified): native writes only byte `1` at `+0x94`, even though
// `update_salt_hazard` later reads the same address as the z-velocity float.
// Preserve that odd lane exactly: it is effectively stationary in z.
pub const native_salt_z_velocity_bit_pattern: u32 = 1;
// PORT(partial): native `spawn_salt_hazard` draws from shared
// `next_math_random_value`, which returns `[-16384, 16384]`, then multiplies
// by `0.0001917476` for the initial Y-rotation angle. The port keeps the same
// scale but advances a runner-local RNG so salt spawn does not perturb the
// broader gameplay random stream.
pub const native_salt_yaw_random_scale: f32 = 0.0001917476;
// PORT(partial): native `update_salt_hazard` feeds the lifted slot through
// track-attachment tests and deactivates it once that attachment no longer
// accepts the next position. The port does not yet carry those native
// attachment objects for salt, so cap the visible lift near the spawn anchor
// instead of letting authored salt drift upward for the whole live window.
pub const port_salt_visible_lift_cap: f32 = 0.08;
// PORT(verified): `spawn_sub_lazer_projectile` seeds the nested-sprite bob
// phase step as
// `track_center_x * 0.0055555557`
// (`analysis/decompile/ida/functions/00441670-spawn_sub_lazer_projectile.c:29`). At
// the port's fixed `track_center_x = 4.0`, this is `0.0222` per tick, so one
// full sine cycle takes ~45 ticks (~0.75s).
pub const native_sub_lazer_phase_step_factor: f32 = 0.0055555557;
// PORT(verified): `update_sub_lazer_projectile` writes the nested sprite Y
// offset as `sin(phase * 2*pi) * 0.3 + base_y`
// (`analysis/decompile/ida/functions/0043efb0-update_sub_lazer_projectile.c:93-98`).
// It is not the live body position sampled by `handle_subgoldy_collisions`.
pub const native_sub_lazer_bob_amplitude: f32 = 0.30000001;
// PORT(verified): `shoot_subgoldy` adjusts each successive slot's spawn Y by
// `-0.01 * slot_index` so stacked lazers vertically separate
// (`artifacts/ida/functions/00441ad0-shoot_subgoldy.c:22`).
pub const native_sub_lazer_stack_y_step: f32 = -0.0099999998;

pub const max_active_health_pickups: usize = 8;
pub const max_active_jetpack_pickups: usize = 1;
pub const max_active_runtime_pickups: usize = max_active_health_pickups + max_active_jetpack_pickups;
pub const max_active_runtime_hazards: usize = 128;
pub const max_active_runtime_ring_effects: usize = 2;
// PORT(verified): native `cRSalt @ game + 0x3578c0` has 40 slots with stride
// 0x98 (152 bytes per slot) per
// `artifacts/ida/functions/00441540-initialize_salt_hazard_pool.c`.
pub const max_active_salt_slots: usize = 40;
// PORT(verified): native `cRSubLazerManager @ game + 0x356b00` has 20 slots
// with stride 0xb0 (176 bytes per slot) per
// `analysis/decompile/ida/functions/00441650-initialize_sub_lazer_pool.c`.
pub const max_active_sub_lazer_slots: usize = 20;

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

/// PORT(partial): 40-slot `cRSalt` projectile pool. Matches the recovered slot
/// count and runtime fields the port consumes (`game + 0x3578c0`: lifetime
/// progress + step, world position, motion lane, and yaw), but keeps those fields
/// in a plain Zig slot instead of the native body/list object graph.
/// `initialize_salt_hazard_pool` at
/// `artifacts/ida/functions/00441540-initialize_salt_hazard_pool.c` zeros the
/// state byte on every slot; `spawn_salt_hazard`
/// (`artifacts/ida/functions/00441560-spawn_salt_hazard.c`) allocates the
/// first inactive slot, seeds position, writes `0` to x velocity, writes
/// `track_center_x * 0.033333335` to y velocity, writes byte `1` at the
/// z-velocity address, and installs a randomized Y rotation.
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

    // PORT(partial): mirror of `spawn_salt_hazard`
    // (`artifacts/ida/functions/00441560-spawn_salt_hazard.c`). Allocates
    // the first inactive slot, marks it active, seeds position from the
    // caller's Vec3 input, seeds the native motion lane, and rolls a random
    // Y-rotation on the spawn frame.
    pub fn spawn(
        self: *SaltHazardPool,
        row: usize,
        lane: usize,
        world_position: rl.Vector3,
        track_center_x: f32,
        random_state: *u32,
    ) ?*SaltSlot {
        const slot = self.allocate() orelse return null;
        slot.* = .{
            .state = .active,
            .row = row,
            .lane = lane,
            .world_position = world_position,
            .spawn_y = world_position.y,
            .velocity = .{
                .x = 0.0,
                .y = track_center_x * native_salt_vertical_velocity_factor,
                .z = @as(f32, @bitCast(native_salt_z_velocity_bit_pattern)),
            },
            .lifetime_progress = 0.0,
            .lifetime_step = 0.0,
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
                    slot.world_position.y = @min(
                        slot.world_position.y + slot.velocity.y,
                        slot.spawn_y + port_salt_visible_lift_cap,
                    );
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
// (native `random()` shifted to zero-center). `spawn_salt_hazard` centers the
// output by subtracting `16384.0` from the raw `0..32768` value, then scales by
// `0.0001917476` (≈ `tau / 32768`) to get the Y-rotation angle. The port keeps
// its own LCG state per-Runner, so the helper wraps `random_state` advancement
// plus native-scaled centering.
fn nextSaltYawRadians(random_state: *u32) f32 {
    random_state.* = random_state.* *% 1103515245 +% 12345;
    const raw: u32 = (random_state.* >> 16) & 0x7FFF;
    const centered = @as(f32, @floatFromInt(@as(i32, @intCast(raw)))) - 16384.0;
    return centered * native_salt_yaw_random_scale;
}

test "salt spawn seeds native lift velocity instead of lifetime expiry" {
    var pool = SaltHazardPool{};
    var random_state: u32 = 0;
    const track_center_x: f32 = 4.0;
    const slot = pool.spawn(
        12,
        3,
        .{ .x = 2.5, .y = 0.18, .z = 12.0 },
        track_center_x,
        &random_state,
    ).?;

    try std.testing.expectApproxEqAbs(
        track_center_x * native_salt_vertical_velocity_factor,
        slot.velocity.y,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), slot.lifetime_step, 0.0001);

    pool.tickActiveSlots();

    try std.testing.expectEqual(SaltSlotState.active, slot.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.18) + port_salt_visible_lift_cap, slot.world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), slot.lifetime_progress, 0.0001);
}

/// PORT(partial): 20-slot `cRSubLazerManager` projectile pool. Keeps the
/// recovered slot count and the fields the port uses from `game + 0x356b00`
/// (body position, velocity, and nested-sprite bob phase), but omits the native
/// intrusive list, full renderable-body, and sprite-owner subobjects.
/// `initialize_sub_lazer_pool`
/// (`analysis/decompile/ida/functions/00441650-initialize_sub_lazer_pool.c`)
/// zeros the state byte on every slot; `spawn_sub_lazer_projectile` at
/// `analysis/decompile/ida/functions/00441670-spawn_sub_lazer_projectile.c` seeds the
/// position, velocity, phase step, and render basis that the port currently
/// collapses to explicit slot fields.
pub const SubLazerPool = struct {
    slots: [max_active_sub_lazer_slots]SubLazerSlot =
        [_]SubLazerSlot{.{}} ** max_active_sub_lazer_slots,
    fire_generation: u32 = 0,
    last_fire_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },

    pub fn reset(self: *SubLazerPool) void {
        self.* = .{};
    }

    pub fn active(self: *const SubLazerPool) []const SubLazerSlot {
        return self.slots[0..];
    }

    pub fn allocateAt(self: *SubLazerPool) ?struct { slot: *SubLazerSlot, index: usize } {
        for (&self.slots, 0..) |*slot, index| {
            if (slot.state == .inactive) return .{ .slot = slot, .index = index };
        }
        return null;
    }

    pub fn countActive(self: *const SubLazerPool) usize {
        var total: usize = 0;
        for (self.slots) |slot| {
            if (slot.state != .inactive) total += 1;
        }
        return total;
    }

    // PORT(partial): mirror of `spawn_sub_lazer_projectile`
    // (`analysis/decompile/ida/functions/00441670-spawn_sub_lazer_projectile.c`).
    // Allocates the first inactive slot, stores the port-side emitter cell
    // back-ref, body position, launch velocity, and nested-sprite bob step.
    // The visual bob starts at phase 0 so the slot draws at the spawn height.
    pub fn spawn(
        self: *SubLazerPool,
        emitter_row: usize,
        emitter_lane: usize,
        world_position: rl.Vector3,
        velocity: rl.Vector3,
        track_center_x: f32,
    ) ?*SubLazerSlot {
        const allocation = self.allocateAt() orelse return null;
        allocation.slot.* = .{
            .state = .active,
            .emitter_row = emitter_row,
            .emitter_lane = emitter_lane,
            .world_position = world_position,
            .visual_y = world_position.y,
            .velocity = velocity,
            .phase = 0.0,
            .phase_step = track_center_x * native_sub_lazer_phase_step_factor,
        };
        return allocation.slot;
    }

    // PORT(verified): `shoot_subgoldy`
    // (`artifacts/ida/functions/00441ad0-shoot_subgoldy.c`). Walks the pool
    // for the first inactive slot, adjusts spawn Y by
    // `-0.01 * slot_index` so stacked shots don't co-locate vertically,
    // then delegates to `spawn`. The native `sfx 15` call lives after the
    // successful spawn, so the port increments `fire_generation` only on
    // successful allocation and preserves the original unstacked spawn
    // position for `play_sound_effect_at_position(15, a2)`. Returns null when
    // the pool is exhausted.
    pub fn shoot(
        self: *SubLazerPool,
        emitter_row: usize,
        emitter_lane: usize,
        world_position: rl.Vector3,
        velocity: rl.Vector3,
        track_center_x: f32,
    ) ?*SubLazerSlot {
        const allocation = self.allocateAt() orelse return null;
        const stacked_position: rl.Vector3 = .{
            .x = world_position.x,
            .y = world_position.y + @as(f32, @floatFromInt(allocation.index)) * native_sub_lazer_stack_y_step,
            .z = world_position.z,
        };
        allocation.slot.* = .{
            .state = .active,
            .emitter_row = emitter_row,
            .emitter_lane = emitter_lane,
            .world_position = stacked_position,
            .visual_y = stacked_position.y,
            .velocity = velocity,
            .phase = 0.0,
            .phase_step = track_center_x * native_sub_lazer_phase_step_factor,
        };
        self.fire_generation +%= 1;
        self.last_fire_position = world_position;
        return allocation.slot;
    }

    // PORT(partial): mirror of `update_sub_lazer_projectile`
    // (`analysis/decompile/ida/functions/0043efb0-update_sub_lazer_projectile.c`).
    // Native body motion is owned by the renderable-body/list machinery that
    // `spawn_sub_lazer_projectile` links into; the port approximates that by
    // integrating the explicit launch velocity on the body position. The sine
    // phase drives only the nested-sprite draw Y, matching the native write to
    // `slot->sprite + 0x4c` instead of moving the collision body.
    pub fn tickActiveSlots(self: *SubLazerPool) void {
        for (&self.slots) |*slot| {
            switch (slot.state) {
                .inactive => {},
                .active => {
                    slot.phase += slot.phase_step;
                    if (slot.phase >= 1.0) slot.phase -= 1.0;
                    slot.world_position.x += slot.velocity.x;
                    slot.world_position.y += slot.velocity.y;
                    slot.world_position.z += slot.velocity.z;
                    slot.visual_y = slot.world_position.y +
                        std.math.sin(slot.phase * std.math.tau) * native_sub_lazer_bob_amplitude;
                },
                .removing => {
                    // PORT(verified): native `destroy_sub_lazer_projectile`
                    // (`analysis/decompile/ida/functions/00439bc0-destroy_sub_lazer_projectile.c`)
                    // unlinks the slot and its four nested body objects
                    // from the shared intrusive-list machinery. The port's
                    // plain-array pool just flips state back to inactive.
                    slot.state = .inactive;
                },
            }
        }
    }

    // PORT(verified): mirror of `destroy_sub_lazer_projectile`. Called
    // when the emitter cell passes behind the player or the slot
    // collides. The port simplification drops the intrusive-list unlink
    // and just flips the state byte.
    pub fn destroy(_: *SubLazerPool, slot: *SubLazerSlot) void {
        slot.state = .inactive;
    }
};

test "SubLazer tick keeps collision body separate from sprite bob" {
    var pool = SubLazerPool{};
    const slot = pool.spawn(
        12,
        2,
        .{ .x = 1.0, .y = 9.0, .z = 30.0 },
        .{ .x = 0.1, .y = -0.25, .z = -0.35 },
        4.0,
    ).?;

    pool.tickActiveSlots();

    try std.testing.expectApproxEqAbs(@as(f32, 1.1), slot.world_position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 8.75), slot.world_position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 29.65), slot.world_position.z, 0.0001);
    try std.testing.expect(slot.visual_y > slot.world_position.y);
}

test "SubLazer bob phase wraps at native unit boundary" {
    var pool = SubLazerPool{};
    const slot = pool.spawn(
        4,
        1,
        .{ .x = 0.0, .y = 8.0, .z = 16.0 },
        .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        4.0,
    ).?;
    slot.phase = 0.99;
    slot.phase_step = 0.01;

    pool.tickActiveSlots();

    try std.testing.expectApproxEqAbs(@as(f32, 0.0), slot.phase, 0.0001);
    try std.testing.expectApproxEqAbs(slot.world_position.y, slot.visual_y, 0.0001);
}

/// All hazard-family pools grouped. Mirrors the native subgame memory layout:
/// separate garbage, salt, sub-lazer, pickup, and ring pools.
pub const Runtime = struct {
    hazards: HazardPool = .{},
    salts: SaltHazardPool = .{},
    sub_lazers: SubLazerPool = .{},
    pickups: PickupPool = .{},
    rings: RingPool = .{},

    pub fn reset(self: *Runtime) void {
        self.* = .{};
    }
};
