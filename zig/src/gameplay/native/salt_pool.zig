//! Mirror of the native salt hazard pool (cRSalt).
//!
//! Transcribed from the matched/pinned quartet in tools/match/scratches/
//! (initialize @ 0x441540 100%, spawn @ 0x441560 74%, update @ 0x4417d0 48%,
//! deactivate @ 0x441740 41% — residuals are layout-only, semantics pinned;
//! see each scratch's NOTES.md and the 2026-06-12 invalidation-ledger entry).
//!
//! RULE: do not refactor this module for taste, and do not fix the native
//! quirks — they are observable behavior:
//! - spawn corrupts velocity.z with a single byte write, leaving it a
//!   denormal ~0; mirrored here as literal zero
//! - the native progress/step fields overlap the next slot's header and are
//!   never initialized, so the progress-driven state-2 transition almost
//!   never fires; mirrored here as fields that stay zero
//! - salt lifetime is therefore governed by collision, y < 0, the kill
//!   plane, and the tile-14 low-altitude floor exit
//!
//! Zig seams: the live list / free stack anchors live in the pool instead
//! of game globals; the grid/runtime cell lookups and the containment probe
//! arrive through UpdateDeps; report_errorf becomes std.log.

const std = @import("std");

pub const slot_count = 40;

pub const Vec3 = struct {
    x: f32 = 0.0,
    y: f32 = 0.0,
    z: f32 = 0.0,
};

pub const SaltHazardSlot = struct {
    list_flags: u32 = 0, // 0x200 linked, 0x40 iteration guard
    list_prev: ?*SaltHazardSlot = null,
    list_next: ?*SaltHazardSlot = null,
    position: Vec3 = .{}, // live-matrix position row (+0x68)
    heading_angle: f32 = 0.0, // world-y rotation applied at spawn
    state: i32 = 0, // +0x80: 0 free, 1 live, 2 remove
    velocity: Vec3 = .{}, // +0x8c; z stays 0 (native byte-poke bug)
    armed_byte_poke: bool = false, // the spawn write that lands in velocity.z
    progress: f32 = 0.0, // +0x98, native: uninitialized overlap, never fires
    progress_step: f32 = 0.0, // +0x9c, native: uninitialized overlap
};

pub const SaltHazardPool = struct {
    slots: [slot_count]SaltHazardSlot = @splat(.{}),
    live_first: ?*SaltHazardSlot = null, // anchor at game+0x3ca224
    free_top: ?*SaltHazardSlot = null, // anchor at game+0x5a8

    /// initialize_salt_hazard_pool @ 0x441540 (matched 100%)
    pub fn initializeSaltHazardPool(self: *SaltHazardPool) void {
        for (&self.slots) |*slot| slot.state = 0;
    }

    /// spawn_salt_hazard @ 0x441560 (pinned). Returns the slot index used,
    /// or slot_count when the pool is exhausted. speed_base mirrors
    /// game[+0x74650]; random_value mirrors next_math_random_value().
    pub fn spawnSaltHazard(
        self: *SaltHazardPool,
        position: Vec3,
        speed_base: f32,
        random_value: i32,
    ) usize {
        var index: usize = 0;
        while (self.slots[index].state != 0) {
            index += 1;
            if (index >= slot_count) return index;
        }
        const slot = &self.slots[index];
        slot.state = 1;
        slot.velocity.x = 0.0;
        slot.velocity.y = speed_base * 0.033333335;
        slot.position = position;
        // native: set_matrix_rotation_identity then rotate_matrix_world_y by
        // (rand - 16384) * 0.0001917476 (+/- pi)
        slot.heading_angle = (@as(f32, @floatFromInt(random_value)) - 16384.0) * 0.0001917476;
        // native: mov byte [slot+0x94], 1 — pokes velocity.z's low byte;
        // the resulting denormal behaves as zero everywhere downstream
        slot.velocity.z = 0.0;
        slot.armed_byte_poke = true;
        if (slot.list_flags & 0x200 != 0) {
            std.log.err("salt list ADDafter on linked slot", .{});
            return index;
        }
        slot.list_next = self.live_first;
        if (slot.list_next) |next| next.list_prev = slot;
        self.live_first = slot;
        slot.list_flags |= 0x200;
        return index;
    }

    /// deactivate_salt_hazard @ 0x441740 (pinned): unlink from the live
    /// list, push onto the free stack, clear state either way.
    pub fn deactivateSaltHazard(self: *SaltHazardPool, slot: *SaltHazardSlot) void {
        const flags = slot.list_flags;
        if (flags & 0x200 == 0) {
            std.log.err("salt list REMOVE on unlinked slot", .{});
            slot.state = 0;
            return;
        }
        if (flags & 0x40 != 0) {
            std.log.err("salt list REMOVEnext under iteration guard", .{});
            slot.state = 0;
            return;
        }
        if (slot.list_next) |next| next.list_prev = slot.list_prev;
        if (slot.list_prev) |prev|
            prev.list_next = slot.list_next
        else
            self.live_first = slot.list_next;
        slot.list_next = self.free_top;
        self.free_top = slot;
        slot.state = 0;
        slot.list_flags = flags & ~@as(u32, 0x200);
    }

    /// update_salt_hazard @ 0x4417d0 (pinned). Containment and track lookups
    /// arrive through deps; returns what the caller must do for effects.
    pub fn updateSaltHazard(
        self: *SaltHazardPool,
        slot: *SaltHazardSlot,
        deps: UpdateDeps,
    ) UpdateResult {
        if (deps.paused) return .none;
        switch (slot.state) {
            2 => {
                self.deactivateSaltHazard(slot);
                return .none;
            },
            1 => {
                slot.progress = slot.progress_step + slot.progress;
                if (slot.progress > 1.0) {
                    slot.state = 2;
                    return .none;
                }
                slot.position.x = slot.velocity.x + slot.position.x;
                slot.position.y = slot.velocity.y + slot.position.y;
                slot.position.z = slot.velocity.z + slot.position.z;
                if (slot.position.y >= 0.0 and slot.position.z >= deps.kill_plane_z) {
                    const tile = deps.gridTile(slot.position);
                    const cell = deps.runtimeCell(slot.position);
                    if (tile != 14 or slot.position.y >= 7.0) {
                        const probe = Vec3{
                            .x = slot.velocity.x + slot.position.x,
                            .y = slot.velocity.y + slot.position.y,
                            .z = slot.velocity.z + slot.position.z,
                        };
                        const sweep = Vec3{
                            .x = slot.velocity.x * 1.05,
                            .y = slot.velocity.y * 1.05,
                            .z = slot.velocity.z * 1.05,
                        };
                        const primary_hit = cell.flags & 0x40 != 0 and
                            deps.insideAttachment(.primary, probe, sweep);
                        if (!primary_hit) {
                            if (cell.flags & 0x80 == 0) return .none;
                            if (!deps.insideAttachment(.secondary, probe, sweep)) return .none;
                        }
                        self.deactivateSaltHazard(slot);
                        return .collision_effect;
                    }
                }
                self.deactivateSaltHazard(slot);
                return .none;
            },
            else => return .none,
        }
    }
};

pub const UpdateResult = enum { none, collision_effect };

pub const AttachmentLane = enum { primary, secondary };

pub const RuntimeCellView = struct {
    flags: u8, // 0x40 primary attachment present, 0x80 secondary
};

pub const UpdateDeps = struct {
    paused: bool,
    kill_plane_z: f32, // game[+0x3be0e4]
    context: *anyopaque,
    grid_tile_fn: *const fn (context: *anyopaque, position: Vec3) u8,
    runtime_cell_fn: *const fn (context: *anyopaque, position: Vec3) RuntimeCellView,
    inside_attachment_fn: *const fn (
        context: *anyopaque,
        lane: AttachmentLane,
        probe: Vec3,
        sweep: Vec3,
    ) bool,

    fn gridTile(self: UpdateDeps, position: Vec3) u8 {
        return self.grid_tile_fn(self.context, position);
    }

    fn runtimeCell(self: UpdateDeps, position: Vec3) RuntimeCellView {
        return self.runtime_cell_fn(self.context, position);
    }

    fn insideAttachment(self: UpdateDeps, lane: AttachmentLane, probe: Vec3, sweep: Vec3) bool {
        return self.inside_attachment_fn(self.context, lane, probe, sweep);
    }
};

const TestDeps = struct {
    paused: bool = false,
    kill_plane_z: f32 = -100.0,
    tile: u8 = 0,
    flags: u8 = 0,
    primary_hit: bool = false,
    secondary_hit: bool = false,

    fn deps(self: *TestDeps) UpdateDeps {
        return .{
            .paused = self.paused,
            .kill_plane_z = self.kill_plane_z,
            .context = self,
            .grid_tile_fn = gridTile,
            .runtime_cell_fn = runtimeCell,
            .inside_attachment_fn = insideAttachment,
        };
    }

    fn gridTile(context: *anyopaque, position: Vec3) u8 {
        _ = position;
        const self: *TestDeps = @ptrCast(@alignCast(context));
        return self.tile;
    }

    fn runtimeCell(context: *anyopaque, position: Vec3) RuntimeCellView {
        _ = position;
        const self: *TestDeps = @ptrCast(@alignCast(context));
        return .{ .flags = self.flags };
    }

    fn insideAttachment(context: *anyopaque, lane: AttachmentLane, probe: Vec3, sweep: Vec3) bool {
        _ = probe;
        _ = sweep;
        const self: *TestDeps = @ptrCast(@alignCast(context));
        return switch (lane) {
            .primary => self.primary_hit,
            .secondary => self.secondary_hit,
        };
    }
};

test "spawn seeds the native lanes and preserves the velocity.z quirk" {
    var pool = SaltHazardPool{};
    pool.initializeSaltHazardPool();
    const index = pool.spawnSaltHazard(.{ .x = 1.0, .y = 2.0, .z = 3.0 }, 30.0, 16384 + 8192);
    try std.testing.expectEqual(@as(usize, 0), index);
    const slot = &pool.slots[0];
    try std.testing.expectEqual(@as(i32, 1), slot.state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), slot.velocity.y, 0.0001);
    try std.testing.expectEqual(@as(f32, 0.0), slot.velocity.x);
    try std.testing.expectEqual(@as(f32, 0.0), slot.velocity.z);
    try std.testing.expectApproxEqAbs(@as(f32, 1.5707968), slot.heading_angle, 0.001);
    try std.testing.expect(slot.list_flags & 0x200 != 0);
    try std.testing.expectEqual(slot, pool.live_first.?);
}

test "spawn returns slot_count when the pool is exhausted" {
    var pool = SaltHazardPool{};
    for (&pool.slots) |*slot| slot.state = 1;
    try std.testing.expectEqual(@as(usize, slot_count), pool.spawnSaltHazard(.{}, 30.0, 0));
}

test "live salt persists without collision because progress never fires" {
    var pool = SaltHazardPool{};
    _ = pool.spawnSaltHazard(.{ .y = 5.0, .z = 10.0 }, 30.0, 16384);
    var deps = TestDeps{};
    for (0..100) |_| {
        try std.testing.expectEqual(UpdateResult.none, pool.updateSaltHazard(&pool.slots[0], deps.deps()));
    }
    try std.testing.expectEqual(@as(i32, 1), pool.slots[0].state);
}

test "salt deactivates below the kill plane and on the tile-14 floor" {
    var pool = SaltHazardPool{};
    _ = pool.spawnSaltHazard(.{ .y = 5.0, .z = 10.0 }, 30.0, 16384);
    var deps = TestDeps{ .kill_plane_z = 50.0 };
    _ = pool.updateSaltHazard(&pool.slots[0], deps.deps());
    try std.testing.expectEqual(@as(i32, 0), pool.slots[0].state);

    _ = pool.spawnSaltHazard(.{ .y = 5.0, .z = 10.0 }, 30.0, 16384);
    var floor_deps = TestDeps{ .tile = 14 };
    _ = pool.updateSaltHazard(&pool.slots[0], floor_deps.deps());
    try std.testing.expectEqual(@as(i32, 0), pool.slots[0].state);
}

test "containment hit reports the collision effect and frees the slot" {
    var pool = SaltHazardPool{};
    _ = pool.spawnSaltHazard(.{ .y = 5.0, .z = 10.0 }, 30.0, 16384);
    var deps = TestDeps{ .flags = 0x80, .secondary_hit = true };
    try std.testing.expectEqual(
        UpdateResult.collision_effect,
        pool.updateSaltHazard(&pool.slots[0], deps.deps()),
    );
    try std.testing.expectEqual(@as(i32, 0), pool.slots[0].state);
    try std.testing.expectEqual(&pool.slots[0], pool.free_top.?);

    // miss on both lanes returns without deactivating
    _ = pool.spawnSaltHazard(.{ .y = 5.0, .z = 10.0 }, 30.0, 16384);
    var miss_deps = TestDeps{ .flags = 0xc0 };
    try std.testing.expectEqual(UpdateResult.none, pool.updateSaltHazard(&pool.slots[0], miss_deps.deps()));
    try std.testing.expectEqual(@as(i32, 1), pool.slots[0].state);
}
