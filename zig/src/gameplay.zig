const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const track = @import("track.zig");

pub const RunnerInput = struct {
    lane_delta: i8 = 0,
    speed_delta_rows_per_second: f32 = 0.0,
    toggle_pause: bool = false,
    reset: bool = false,
};

pub const AttachmentHint = enum {
    none,
    probe,
    entry,

    pub fn label(self: AttachmentHint) []const u8 {
        return switch (self) {
            .none => "none",
            .probe => "probe",
            .entry => "entry",
        };
    }
};

pub const Runner = struct {
    lane_index: usize = 0,
    lane_center: f32 = 0.5,
    row_position: f32 = 0.0,
    speed_rows_per_second: f32 = 12.0,
    paused: bool = false,
    finished: bool = false,
    tick_count: u64 = 0,
    current_global_row: usize = 0,
    current_cell: u8 = ' ',
    current_annotation: ?segment.Annotation.Tag = null,
    attachment_hint: AttachmentHint = .none,
    path_center_lane: ?f32 = null,
    traversable_bounds: track.LaneBounds = .{ .min = 0, .max = 0 },

    pub fn init(preview: *const track.LoadedLevelPreview) Runner {
        var runner = Runner{};
        runner.reset(preview);
        return runner;
    }

    pub fn reset(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.* = .{
            .speed_rows_per_second = 12.0,
        };
        self.refreshSample(preview);
    }

    pub fn step(self: *Runner, preview: *const track.LoadedLevelPreview, input: RunnerInput, delta_seconds: f32) void {
        if (input.reset) {
            self.reset(preview);
            return;
        }

        if (input.toggle_pause) {
            self.paused = !self.paused;
        }

        self.speed_rows_per_second = std.math.clamp(
            self.speed_rows_per_second + input.speed_delta_rows_per_second,
            2.0,
            48.0,
        );

        if (preview.total_rows == 0) {
            self.finished = true;
            return;
        }

        self.applyLaneDelta(input.lane_delta);

        if (!self.paused and !self.finished) {
            const track_end = @as(f32, @floatFromInt(preview.total_rows - 1)) + 0.999;
            self.row_position = @min(self.row_position + (self.speed_rows_per_second * delta_seconds), track_end);
            self.finished = self.row_position >= track_end;
            self.tick_count += 1;
        }

        self.refreshSample(preview);
    }

    pub fn worldPosition(self: *const Runner, preview: *const track.LoadedLevelPreview, y: f32) rl.Vector3 {
        return preview.worldPositionForLane(self.lane_center, self.row_position, y);
    }

    pub fn annotationLabel(self: *const Runner) ?[]const u8 {
        const tag = self.current_annotation orelse return null;
        return switch (tag) {
            .path => "path",
            .ring => "ring",
            .parcel => "parcel",
            .model => "model",
            .jetpack_off => "jetpack_off",
            .no_fall => "no_fall",
        };
    }

    fn applyLaneDelta(self: *Runner, lane_delta: i8) void {
        if (lane_delta == 0) return;
        if (lane_delta < 0) {
            const amount: usize = @intCast(-lane_delta);
            self.lane_index = if (amount > self.lane_index) 0 else self.lane_index - amount;
            return;
        }
        self.lane_index += @intCast(lane_delta);
    }

    fn refreshSample(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.traversable_bounds = .{ .min = 0, .max = 0 };
            self.lane_center = 0.5;
            return;
        }

        const clamped_row_float = std.math.clamp(
            self.row_position,
            0.0,
            @as(f32, @floatFromInt(preview.total_rows - 1)),
        );
        const global_row: usize = @intFromFloat(@floor(clamped_row_float));
        self.current_global_row = global_row;

        const row_location = preview.locateRow(global_row) orelse {
            self.current_cell = ' ';
            self.current_annotation = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            return;
        };

        const traversable = preview.laneBoundsForRow(row_location);
        self.traversable_bounds = traversable;
        self.lane_index = std.math.clamp(self.lane_index, traversable.min, traversable.max);
        self.current_cell = preview.cellAt(global_row, self.lane_index) orelse ' ';
        self.current_annotation = if (row_location.row.annotation) |annotation| annotation.tag() else null;

        if (preview.pathBoundsForRow(row_location)) |path_bounds| {
            self.attachment_hint = switch (self.current_cell) {
                'P' => .entry,
                'p' => .probe,
                else => .probe,
            };
            self.path_center_lane = (@as(f32, @floatFromInt(path_bounds.min + path_bounds.max)) * 0.5) + 0.5;
            self.lane_center = self.path_center_lane.?;
        } else {
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.lane_center = @as(f32, @floatFromInt(self.lane_index)) + 0.5;
        }
    }
};

test "runner advances deterministically over fixed time" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    for (0..120) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectApproxEqAbs(@as(f32, 24.0), runner.row_position, 0.001);
    try std.testing.expectEqual(@as(u64, 120), runner.tick_count);
}

test "runner discovers attachment hint rows in shipped corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/ARCADE000.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    var found_attachment_hint = false;
    for (0..1024) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
        if (runner.attachment_hint != .none) {
            found_attachment_hint = true;
            break;
        }
    }

    try std.testing.expect(found_attachment_hint);
}
