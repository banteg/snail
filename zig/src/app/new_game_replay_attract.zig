const std = @import("std");

const frontend_bridge = @import("../frontend/bridge.zig");
const high_score = @import("../high_score.zig");
const math_random = @import("math_random.zig");

pub const release_step_after_probe: f32 = 1.0 / 3600.0;
const max_probe_attempts = 1000;
const main_bank_random_count = 4;
const completion_bank_random_count = 0x33;

pub const Controller = struct {
    cursor: u8 = 0,
    hide_latch: bool = false,
    hide_release_accumulator: f32 = 0.0,
    hide_release_step: f32 = 0.0,
    launch_accumulator: f32 = 0.0,
    // Native menu-local +0x14 is read by `update_new_game_menu`, but the shipped
    // Windows image initializes it to 0 and static xrefs do not expose a writer.
    // Keep the branch present but dormant rather than inventing an attract timer.
    launch_step: f32 = 0.0,

    pub fn noteInput(self: *Controller) void {
        self.hide_latch = false;
    }

    pub fn resetReleaseTimer(self: *Controller) void {
        self.hide_release_accumulator = 0.0;
        self.hide_release_step = release_step_after_probe;
    }

    pub fn tickReleaseTimer(self: *Controller) void {
        if (!self.hide_latch) return;
        self.hide_release_accumulator += self.hide_release_step;
        if (self.hide_release_accumulator > 1.0) {
            self.hide_latch = false;
        }
    }

    pub fn stepLaunchTimer(self: *Controller) bool {
        if (self.launch_step == 0.0) return false;
        self.launch_accumulator += self.launch_step;
        if (self.launch_accumulator <= 1.0) return false;
        self.launch_accumulator = 0.0;
        return true;
    }
};

pub fn probeSource(
    controller: *Controller,
    tables: *const high_score.Tables,
    random_state: *u32,
) ?frontend_bridge.SelectedLevelRecordSource {
    var attempts: usize = 0;
    while (attempts < max_probe_attempts) : (attempts += 1) {
        const source = sourceForCursor(controller.cursor, tables, random_state);
        advanceCursor(controller);
        if (source) |selected| return selected;
    }
    return null;
}

fn sourceForCursor(
    cursor: u8,
    tables: *const high_score.Tables,
    random_state: *u32,
) ?frontend_bridge.SelectedLevelRecordSource {
    return switch (cursor) {
        0 => blk: {
            const index = randomIndex(random_state, main_bank_random_count);
            if (!entryCanAttract(&tables.postal[index])) break :blk null;
            break :blk .{ .postal = index };
        },
        1 => blk: {
            const index = randomIndex(random_state, main_bank_random_count);
            if (!entryCanAttract(&tables.challenge[index])) break :blk null;
            break :blk .{ .challenge = index };
        },
        3 => blk: {
            const index = randomIndex(random_state, completion_bank_random_count);
            if (!entryCanAttract(&tables.completion[index])) break :blk null;
            break :blk .{ .completion = index };
        },
        else => null,
    };
}

fn entryCanAttract(entry: *const high_score.Entry) bool {
    return entry.has_replay and entry.replaySampleCount() != 0;
}

fn advanceCursor(controller: *Controller) void {
    controller.cursor += 1;
    if (controller.cursor == 5) {
        controller.cursor = 0;
    }
}

fn randomIndex(random_state: *u32, comptime count: usize) usize {
    const value = math_random.nextInt15(random_state);
    return @intCast((value * count) >> 15);
}

test "new game replay attract probes native cursor banks only" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    var raw_record = [_]u8{0} ** 0x8d;
    writeU32(raw_record[0x74..0x78], 1);

    tables.completion[0].raw_record = try std.testing.allocator.dupe(u8, &raw_record);
    tables.completion[0].has_replay = true;

    var controller = Controller{ .cursor = 2 };
    var random_state: u32 = 0;

    const source = probeSource(&controller, &tables, &random_state) orelse return error.ExpectedReplaySource;
    try std.testing.expectEqual(frontend_bridge.SelectedLevelRecordSource{ .completion = 0 }, source);
    try std.testing.expectEqual(@as(u8, 4), controller.cursor);
}

test "new game replay attract ignores active scores without replay payloads" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    tables.postal[0].score = 123;
    tables.challenge[0].has_replay = true;

    var controller = Controller{};
    var random_state: u32 = 0;

    try std.testing.expectEqual(@as(?frontend_bridge.SelectedLevelRecordSource, null), probeSource(&controller, &tables, &random_state));
    try std.testing.expectEqual(@as(u8, 0), controller.cursor);
}

test "new game replay attract timer stays dormant without native launch step" {
    var controller = Controller{ .launch_accumulator = 2.0 };

    try std.testing.expect(!controller.stepLaunchTimer());
    try std.testing.expectEqual(@as(f32, 2.0), controller.launch_accumulator);
}

test "new game replay attract launch uses persistent new-game return owner" {
    const launch = frontend_bridge.SelectedLevelRecordLaunch{
        .source = .{ .postal = 0 },
        .persistent = true,
        .outer_return_target = .new_game_menu,
    };

    try std.testing.expectEqual(
        @as(?frontend_bridge.SavedReplayReturnOuterOwner, .new_game_menu),
        frontend_bridge.savedReplayReturnOuterOwnerForLaunch(launch),
    );
}

fn writeU32(out: *[4]u8, value: u32) void {
    out[0] = @intCast(value & 0xff);
    out[1] = @intCast((value >> 8) & 0xff);
    out[2] = @intCast((value >> 16) & 0xff);
    out[3] = @intCast((value >> 24) & 0xff);
}
