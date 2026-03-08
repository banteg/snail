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

pub const MovementMode = enum {
    track,
    attachment,

    pub fn label(self: MovementMode) []const u8 {
        return switch (self) {
            .track => "track",
            .attachment => "attachment",
        };
    }
};

pub const RecentEvent = union(enum) {
    none,
    attachment_probe,
    attachment_begin,
    attachment_end,
    parcel: i32,
    trampoline,
    health_pickup,
    jetpack_pickup,
    garbage_hit,
    salt_hit,
    slug_hit,
    no_fall,
    jetpack_off,
    ring: segment.RingKind,

    pub fn label(self: RecentEvent) []const u8 {
        return switch (self) {
            .none => "none",
            .attachment_probe => "attachment_probe",
            .attachment_begin => "attachment_begin",
            .attachment_end => "attachment_end",
            .parcel => "parcel",
            .trampoline => "trampoline",
            .health_pickup => "health_pickup",
            .jetpack_pickup => "jetpack_pickup",
            .garbage_hit => "garbage_hit",
            .salt_hit => "salt_hit",
            .slug_hit => "slug_hit",
            .no_fall => "no_fall",
            .jetpack_off => "jetpack_off",
            .ring => |ring_kind| switch (ring_kind) {
                .none => "ring_none",
                .normal => "ring_normal",
                .powerup => "ring_powerup",
                .explode => "ring_explode",
                .slow => "ring_slow",
            },
        };
    }
};

pub const EncounterCounters = struct {
    attachments_begun: u32 = 0,
    attachments_completed: u32 = 0,
    parcels: u32 = 0,
    trampoline_rows: u32 = 0,
    health_pickups: u32 = 0,
    jetpack_pickups: u32 = 0,
    garbage_hits: u32 = 0,
    salt_hits: u32 = 0,
    slug_hits: u32 = 0,
    no_fall_rows: u32 = 0,
    jetpack_off_rows: u32 = 0,
    ring_normal: u32 = 0,
    ring_powerup: u32 = 0,
    ring_explode: u32 = 0,
    ring_slow: u32 = 0,
};

const RowSample = struct {
    global_row: usize,
    traversable_bounds: track.LaneBounds,
    resolved_lane_index: usize,
    cell: u8,
    gameplay_cell: ?track.GameplayCellKind,
    runtime_tile_hint: ?u8,
    annotation: ?segment.Annotation,
    path_center_lane: ?f32,
    path_name: ?[]const u8,
};

pub const Runner = struct {
    lane_index: usize = 0,
    resolved_lane_index: usize = 0,
    lane_center: f32 = 0.5,
    runtime_track_index: usize = 0,
    movement_progress: f32 = 0.0,
    movement_rate_scalar: f32 = 0.0,
    row_position: f32 = 0.0,
    speed_rows_per_second: f32 = 12.0,
    paused: bool = false,
    finished: bool = false,
    tick_count: u64 = 0,
    movement_mode: MovementMode = .track,
    current_global_row: usize = 0,
    current_cell: u8 = ' ',
    current_annotation: ?segment.Annotation.Tag = null,
    current_gameplay_cell: ?track.GameplayCellKind = null,
    current_runtime_tile_hint: ?u8 = null,
    current_path_name: ?[]const u8 = null,
    attachment_hint: AttachmentHint = .none,
    attachment_path_name: ?[]const u8 = null,
    attachment_ticks: u64 = 0,
    path_center_lane: ?f32 = null,
    traversable_bounds: track.LaneBounds = .{ .min = 0, .max = 0 },
    recent_event: RecentEvent = .none,
    counters: EncounterCounters = .{},
    last_processed_row: ?usize = null,

    pub fn init(preview: *const track.LoadedLevelPreview) Runner {
        var runner = Runner{};
        runner.reset(preview);
        return runner;
    }

    pub fn reset(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        self.* = .{
            .speed_rows_per_second = 12.0,
        };
        self.syncRowPosition(preview);
        self.refreshSample(preview);
        self.last_processed_row = self.current_global_row;
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

        if (self.movement_mode != .attachment) {
            self.applyLaneDelta(input.lane_delta);
        }

        if (!self.paused and !self.finished) {
            self.movement_rate_scalar = self.speed_rows_per_second * delta_seconds;
            self.advanceMovement(preview);
            self.tick_count += 1;
        }

        self.processVisitedRows(preview);
        self.endAttachmentIfNeeded(preview);
        self.refreshSample(preview);
        if (self.movement_mode == .attachment) {
            self.attachment_ticks += 1;
        }
    }

    pub fn worldPosition(self: *const Runner, preview: *const track.LoadedLevelPreview, y: f32) rl.Vector3 {
        const floor_y = preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) orelse 0.0;
        return preview.worldPositionForLane(self.lane_center, self.row_position, floor_y + y);
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

    pub fn gameplayCellLabel(self: *const Runner) ?[]const u8 {
        const kind = self.current_gameplay_cell orelse return null;
        return kind.label();
    }

    pub fn recentEventLabel(self: *const Runner) []const u8 {
        return self.recent_event.label();
    }

    pub fn activePathName(self: *const Runner) ?[]const u8 {
        return self.attachment_path_name orelse self.current_path_name;
    }

    pub fn runtimeTileHint(self: *const Runner) ?u8 {
        return self.current_runtime_tile_hint;
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
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.traversable_bounds = .{ .min = 0, .max = 0 };
            self.resolved_lane_index = 0;
            self.lane_center = 0.5;
            self.runtime_track_index = 0;
            self.movement_progress = 0.0;
            self.row_position = 0.0;
            return;
        }

        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.resolved_lane_index = 0;
            return;
        };

        self.current_global_row = sample.global_row;
        self.traversable_bounds = sample.traversable_bounds;
        self.resolved_lane_index = sample.resolved_lane_index;
        self.current_cell = sample.cell;
        self.current_annotation = if (sample.annotation) |annotation| annotation.tag() else null;
        self.current_gameplay_cell = sample.gameplay_cell;
        self.current_runtime_tile_hint = sample.runtime_tile_hint;
        self.current_path_name = sample.path_name;
        self.path_center_lane = sample.path_center_lane;
        self.attachment_hint = if (sample.gameplay_cell) |kind|
            switch (kind) {
                .attachment_entry => .entry,
                .attachment_probe => .probe,
                else => returnAttachmentHint(sample.path_center_lane),
            }
        else
            returnAttachmentHint(sample.path_center_lane);
        self.lane_center = if (self.movement_mode == .attachment and sample.path_center_lane != null)
            sample.path_center_lane.?
        else
            @as(f32, @floatFromInt(sample.resolved_lane_index)) + 0.5;
    }

    fn advanceMovement(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or self.finished) return;

        const last_row = preview.total_rows - 1;
        const max_progress: f32 = 0.999;
        var remaining = self.movement_rate_scalar;

        while (remaining > 0.0) {
            const progress_limit: f32 = if (self.runtime_track_index >= last_row) max_progress else 1.0;
            const available_progress = progress_limit - self.movement_progress;
            if (available_progress <= 0.0) {
                break;
            }

            if (remaining < available_progress) {
                self.movement_progress += remaining;
                remaining = 0.0;
                break;
            }

            remaining -= available_progress;
            if (self.runtime_track_index >= last_row) {
                self.movement_progress = max_progress;
                self.finished = true;
                remaining = 0.0;
                break;
            }

            self.runtime_track_index += 1;
            self.movement_progress = 0.0;
        }

        self.syncRowPosition(preview);
    }

    fn syncRowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.row_position = 0.0;
            return;
        }

        const last_row = preview.total_rows - 1;
        if (self.runtime_track_index > last_row) {
            self.runtime_track_index = last_row;
            self.movement_progress = 0.999;
        }
        self.row_position = @as(f32, @floatFromInt(self.runtime_track_index)) + self.movement_progress;
    }

    fn sampleRow(self: *const Runner, preview: *const track.LoadedLevelPreview, global_row: usize) ?RowSample {
        const row_location = preview.locateRow(global_row) orelse return null;
        const traversable = preview.laneBoundsForRow(row_location);
        const desired_lane = std.math.clamp(self.lane_index, traversable.min, traversable.max);

        var resolved_lane_index = desired_lane;
        var path_center_lane: ?f32 = null;
        if (preview.pathBoundsForRow(row_location)) |path_bounds| {
            path_center_lane = (@as(f32, @floatFromInt(path_bounds.min + path_bounds.max)) * 0.5) + 0.5;
            if (self.movement_mode == .attachment) {
                resolved_lane_index = (path_bounds.min + path_bounds.max) / 2;
            }
        }

        const cell = row_location.row.cells[resolved_lane_index];
        const annotation = row_location.row.annotation;
        const runtime_tile_hint = preview.runtimeTileAt(global_row, resolved_lane_index) orelse track.confirmedRuntimeTileHint(cell);
        const gameplay_cell = if (runtime_tile_hint) |tile_type|
            track.runtimeGameplayCellKindForTile(tile_type, preview.runtime_build_flags) orelse track.gameplayCellKind(cell)
        else
            track.gameplayCellKind(cell);
        return .{
            .global_row = global_row,
            .traversable_bounds = traversable,
            .resolved_lane_index = resolved_lane_index,
            .cell = cell,
            .gameplay_cell = gameplay_cell,
            .runtime_tile_hint = runtime_tile_hint,
            .annotation = annotation,
            .path_center_lane = path_center_lane,
            .path_name = pathNameFromAnnotation(annotation),
        };
    }

    fn processVisitedRows(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;
        const current_row = currentRowIndex(preview, self.row_position);
        const last_row = self.last_processed_row orelse {
            self.last_processed_row = current_row;
            return;
        };
        if (current_row < last_row) {
            self.last_processed_row = current_row;
            return;
        }

        var row = last_row + 1;
        while (row <= current_row) : (row += 1) {
            self.processRow(preview, row);
        }
        self.last_processed_row = current_row;
    }

    fn processRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const sample = self.sampleRow(preview, global_row) orelse return;

        if (sample.annotation) |annotation| {
            switch (annotation) {
                .path => |path_name| {
                    if (self.movement_mode == .attachment) {
                        self.attachment_path_name = path_name;
                    }
                },
                .ring => |ring_kind| {
                    if (sample.gameplay_cell) |kind| {
                        if (kind == .ring) {
                            self.recordRing(ring_kind);
                        }
                    }
                },
                .parcel => |parcel| {
                    self.counters.parcels += 1;
                    self.recent_event = .{ .parcel = parcel.id };
                },
                .jetpack_off => {
                    self.counters.jetpack_off_rows += 1;
                    self.recent_event = .jetpack_off;
                },
                .no_fall => {
                    self.counters.no_fall_rows += 1;
                    self.recent_event = .no_fall;
                },
                .model => {},
            }
        }

        const gameplay_cell = sample.gameplay_cell orelse return;
        switch (gameplay_cell) {
            .attachment_probe => {
                if (self.movement_mode == .track) {
                    self.recent_event = .attachment_probe;
                }
            },
            .attachment_entry => {
                if (self.movement_mode != .attachment) {
                    self.movement_mode = .attachment;
                    self.attachment_path_name = sample.path_name;
                    self.counters.attachments_begun += 1;
                    self.recent_event = .attachment_begin;
                }
            },
            .ring => {},
            .trampoline => {
                self.counters.trampoline_rows += 1;
                self.recent_event = .trampoline;
            },
            .health => {
                self.counters.health_pickups += 1;
                self.recent_event = .health_pickup;
            },
            .jetpack => {
                self.counters.jetpack_pickups += 1;
                self.recent_event = .jetpack_pickup;
            },
            .garbage => {
                self.counters.garbage_hits += 1;
                self.recent_event = .garbage_hit;
            },
            .salt => {
                self.counters.salt_hits += 1;
                self.recent_event = .salt_hit;
            },
            .slug => {
                self.counters.slug_hits += 1;
                self.recent_event = .slug_hit;
            },
        }
    }

    fn endAttachmentIfNeeded(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode != .attachment or preview.total_rows == 0) return;
        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse return;
        if (sample.path_center_lane != null) return;

        self.movement_mode = .track;
        self.attachment_path_name = null;
        self.counters.attachments_completed += 1;
        self.recent_event = .attachment_end;
    }

    fn recordRing(self: *Runner, ring_kind: segment.RingKind) void {
        switch (ring_kind) {
            .none => {},
            .normal => self.counters.ring_normal += 1,
            .powerup => self.counters.ring_powerup += 1,
            .explode => self.counters.ring_explode += 1,
            .slow => self.counters.ring_slow += 1,
        }
        if (ring_kind != .none) {
            self.recent_event = .{ .ring = ring_kind };
        }
    }
};

fn currentRowIndex(preview: *const track.LoadedLevelPreview, row_position: f32) usize {
    return @intFromFloat(@floor(std.math.clamp(
        row_position,
        0.0,
        @as(f32, @floatFromInt(preview.total_rows - 1)),
    )));
}

fn returnAttachmentHint(path_center_lane: ?f32) AttachmentHint {
    return if (path_center_lane != null) .probe else .none;
}

fn pathNameFromAnnotation(annotation: ?segment.Annotation) ?[]const u8 {
    const value = annotation orelse return null;
    return switch (value) {
        .path => |path_name| path_name,
        else => null,
    };
}

const TestFixture = struct {
    catalog: assets.Catalog,
    level_definition: level.Definition,
    preview: track.LoadedLevelPreview,

    fn load(level_path: []const u8) !TestFixture {
        var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
        errdefer catalog.deinit();

        const level_entry = catalog.level_entries[catalog.findLevelIndex(level_path).?];
        var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
        errdefer level_definition.deinit();

        var preview = try track.LoadedLevelPreview.loadWithOptions(
            std.testing.allocator,
            &catalog,
            &level_definition,
            .{ .load_models = false },
        );
        errdefer preview.deinit();

        return .{
            .catalog = catalog,
            .level_definition = level_definition,
            .preview = preview,
        };
    }

    fn deinit(self: *TestFixture) void {
        self.preview.deinit();
        self.level_definition.deinit();
        self.catalog.deinit();
    }
};

const RowTarget = struct {
    row: usize,
    lane: usize,
};

fn findFirstGameplayCell(preview: *const track.LoadedLevelPreview, kind: track.GameplayCellKind) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                if (sample.kind == kind) {
                    return .{
                        .row = global_row,
                        .lane = lane,
                    };
                }
            }
        }
    }
    return null;
}

fn primeRunnerBeforeRow(runner: *Runner, preview: *const track.LoadedLevelPreview, target: RowTarget) void {
    std.debug.assert(target.row > 0);
    runner.reset(preview);
    runner.lane_index = target.lane;
    runner.runtime_track_index = target.row - 1;
    runner.movement_progress = 0.99;
    runner.syncRowPosition(preview);
    runner.refreshSample(preview);
    runner.last_processed_row = target.row - 1;
}

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
    try std.testing.expectEqual(@as(usize, 24), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_rate_scalar, 0.0001);
    try std.testing.expectEqual(@as(u64, 120), runner.tick_count);
}

test "runner keeps discrete track cursor and fractional movement progress" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.step(&preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(usize, 0), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.row_position, 0.0001);

    for (0..4) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(@as(usize, 1), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.row_position, 0.0001);
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

test "runner records pickup and hazard encounters from shipped tutorial" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const health = findFirstGameplayCell(&fixture.preview, .health).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, health);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.health_pickups);
    try std.testing.expectEqualStrings("health_pickup", runner.recentEventLabel());

    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, salt);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.salt_hits);
    try std.testing.expectEqualStrings("salt_hit", runner.recentEventLabel());

    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.slug_hits);
    try std.testing.expectEqualStrings("slug_hit", runner.recentEventLabel());

    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, garbage);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqualStrings("garbage_hit", runner.recentEventLabel());
}

test "runner records attachment entry and jetpack pickup from shipped levels" {
    var challenge_fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer challenge_fixture.deinit();

    var runner = Runner.init(&challenge_fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const attachment = findFirstGameplayCell(&challenge_fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &challenge_fixture.preview, attachment);
    runner.step(&challenge_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.attachments_begun);
    try std.testing.expectEqualStrings("attachment_begin", runner.recentEventLabel());
    try std.testing.expect(runner.activePathName() != null);

    var jetpack_fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer jetpack_fixture.deinit();

    runner = Runner.init(&jetpack_fixture.preview);
    const jetpack = findFirstGameplayCell(&jetpack_fixture.preview, .jetpack).?;
    primeRunnerBeforeRow(&runner, &jetpack_fixture.preview, jetpack);
    runner.step(&jetpack_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_pickups);
    try std.testing.expectEqualStrings("jetpack_pickup", runner.recentEventLabel());
}

test "runner records trampoline rows from shipped levels" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const trampoline = findFirstGameplayCell(&fixture.preview, .trampoline).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, trampoline);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.trampoline_rows);
    try std.testing.expectEqualStrings("trampoline", runner.recentEventLabel());
    try std.testing.expectEqualStrings("trampoline", runner.gameplayCellLabel().?);
}
