const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");
const x2 = @import("x2.zig");

pub const Mode = enum {
    loop,
    once,
    pingpong,
};

pub const FrameRef = struct {
    entry_index: usize,
    frame_number: usize,
};

pub const Clip = struct {
    name: []const u8,
    family_key: []const u8,
    duration_seconds: f32,
    mode: Mode,
    trigger_steps: []const []const u8,
    frames: []const FrameRef,
};

pub const Catalog = struct {
    arena: std.heap.ArenaAllocator,
    test_anim: ?[]const u8,
    clips: []const Clip,
    clip_index_by_family: archive.CaseInsensitiveStringHashMap(usize),

    pub fn deinit(self: *Catalog) void {
        self.arena.deinit();
    }

    pub fn load(allocator: std.mem.Allocator, asset_catalog: *const assets.Catalog) !Catalog {
        const entry = asset_catalog.dat.entryByPath("X/_ANIMATION.TXT") orelse return error.AnimationScriptMissing;
        const bytes = try asset_catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(bytes);

        var arena = std.heap.ArenaAllocator.init(allocator);
        errdefer arena.deinit();
        const arena_allocator = arena.allocator();

        var clips: std.ArrayList(Clip) = .empty;
        defer clips.deinit(arena_allocator);
        var clip_index_by_family = archive.CaseInsensitiveStringHashMap(usize).init(arena_allocator);

        var builder: ?ClipBuilder = null;
        var test_anim: ?[]const u8 = null;
        var in_block_comment = false;

        var lines = std.mem.splitScalar(u8, bytes, '\n');
        while (lines.next()) |raw_line| {
            const line = std.mem.trim(u8, raw_line, " \t\r");
            if (line.len == 0) continue;
            if (in_block_comment) {
                if (std.mem.indexOf(u8, line, "*/") != null) {
                    in_block_comment = false;
                }
                continue;
            }
            if (std.mem.startsWith(u8, line, "/*")) {
                if (std.mem.indexOf(u8, line, "*/") == null) {
                    in_block_comment = true;
                }
                continue;
            }
            if (isCommentLine(line)) {
                continue;
            }

            const line_key = parseLineKey(line) orelse return error.UnsupportedAnimationDirective;
            if (line_key == .test_directive) {
                if (builder != null) return error.AnimationDirectiveOutOfPlace;
                test_anim = try arena_allocator.dupe(u8, valueAfterColon(line));
            } else if (line_key == .anim_directive) {
                if (builder != null) return error.MissingAnimationEnd;
                builder = .{
                    .name = try arena_allocator.dupe(u8, valueAfterColon(line)),
                };
            } else if (line_key == .duration_directive) {
                if (builder == null) return error.AnimationDirectiveOutOfPlace;
                builder.?.duration_seconds = try std.fmt.parseFloat(f32, valueAfterColon(line));
            } else if (line_key == .mode_directive) {
                if (builder == null) return error.AnimationDirectiveOutOfPlace;
                builder.?.mode = try parseMode(valueAfterColon(line));
            } else if (line_key == .trigger_directive) {
                if (builder == null) return error.AnimationDirectiveOutOfPlace;
                builder.?.trigger_steps = try parseTriggerBlock(arena_allocator, &lines);
            } else {
                if (builder == null) return error.AnimationDirectiveOutOfPlace;
                const built = try finalizeClip(arena_allocator, asset_catalog, builder.?);
                try clip_index_by_family.put(built.family_key, clips.items.len);
                try clips.append(arena_allocator, built);
                builder = null;
            }
        }
        if (builder != null) return error.MissingAnimationEnd;

        return .{
            .arena = arena,
            .test_anim = test_anim,
            .clips = try clips.toOwnedSlice(arena_allocator),
            .clip_index_by_family = clip_index_by_family,
        };
    }

    pub fn findClipIndexForModelPath(self: *const Catalog, model_path: []const u8) ?usize {
        return self.clip_index_by_family.get(familyKeyFromPath(model_path));
    }
};

pub fn frameNumberFromPath(path: []const u8) usize {
    return parseFrameNumber(path);
}

pub const Player = struct {
    allocator: std.mem.Allocator,
    clip: *const Clip,
    keyframes: []KeyframeModel,
    rendered: x2.Uploaded,
    paused: bool = false,
    elapsed_seconds: f64 = 0.0,
    current_from_index: usize = 0,
    current_to_index: usize = 0,
    current_blend: f32 = 0.0,
    current_sample_number: f32 = 0.0,

    pub fn load(
        allocator: std.mem.Allocator,
        asset_catalog: *const assets.Catalog,
        clip: *const Clip,
        flip_v: bool,
        initial_frame_number: usize,
    ) !Player {
        if (clip.frames.len == 0) return error.EmptyAnimationClip;

        const keyframes = try allocator.alloc(KeyframeModel, clip.frames.len);
        var loaded_count: usize = 0;
        errdefer {
            for (keyframes[0..loaded_count]) |*frame| {
                frame.deinit();
            }
            allocator.free(keyframes);
        }

        for (clip.frames, 0..) |frame_ref, index| {
            keyframes[index] = try KeyframeModel.load(allocator, asset_catalog, frame_ref);
            loaded_count = index + 1;
        }

        for (keyframes[1..]) |*frame| {
            if (!x2.sameTopology(&keyframes[0].parsed, &frame.parsed)) {
                return error.AnimationTopologyMismatch;
            }
        }

        const initial_entry = asset_catalog.model_entries[clip.frames[0].entry_index];
        var rendered = try x2.Uploaded.loadFromArchive(allocator, asset_catalog, initial_entry, flip_v);
        errdefer rendered.deinit();

        var player = Player{
            .allocator = allocator,
            .clip = clip,
            .keyframes = keyframes,
            .rendered = rendered,
        };

        player.seekToFrame(initial_frame_number);
        try player.refreshPose();
        return player;
    }

    pub fn deinit(self: *Player) void {
        self.rendered.deinit();
        for (self.keyframes) |*frame| {
            frame.deinit();
        }
        self.allocator.free(self.keyframes);
    }

    pub fn step(self: *Player, delta_seconds: f64) !void {
        if (!self.paused) {
            self.elapsed_seconds += delta_seconds;
        }
        try self.refreshPose();
    }

    pub fn refreshPose(self: *Player) !void {
        if (self.keyframes.len == 1) {
            self.current_from_index = 0;
            self.current_to_index = 0;
            self.current_blend = 0.0;
            self.current_sample_number = @floatFromInt(self.keyframes[0].frame_number);
            return;
        }

        const frame_sample = self.sample();
        self.current_from_index = frame_sample.from_index;
        self.current_to_index = frame_sample.to_index;
        self.current_blend = frame_sample.blend;
        self.current_sample_number = frame_sample.sample_number;
        try self.rendered.applyInterpolatedVertices(
            &self.keyframes[frame_sample.from_index].parsed,
            &self.keyframes[frame_sample.to_index].parsed,
            frame_sample.blend,
        );
    }

    pub fn restart(self: *Player) !void {
        self.paused = false;
        self.elapsed_seconds = 0.0;
        try self.refreshPose();
    }

    pub fn togglePause(self: *Player) void {
        self.paused = !self.paused;
    }

    fn seekToFrame(self: *Player, frame_number: usize) void {
        const last = @as(f64, @floatFromInt(self.keyframes[self.keyframes.len - 1].frame_number));
        if (last <= 0.0 or self.clip.duration_seconds <= 0.0) {
            self.elapsed_seconds = 0.0;
            return;
        }

        const clamped = @min(@as(f64, @floatFromInt(frame_number)), last);
        const phase = clamped / last;
        self.elapsed_seconds = phase * self.clip.duration_seconds;
    }

    fn sample(self: *const Player) Sample {
        const elapsed = @max(self.elapsed_seconds, 0.0);
        const duration = @max(@as(f64, self.clip.duration_seconds), 0.0001);
        const last_frame_number = @as(f64, @floatFromInt(self.keyframes[self.keyframes.len - 1].frame_number));

        const phase = switch (self.clip.mode) {
            .once => @min(elapsed / duration, 1.0),
            .loop => normalizedLoop(elapsed, duration),
            .pingpong => normalizedPingpong(elapsed, duration),
        };
        const sample_number = @as(f32, @floatCast(phase * last_frame_number));

        if (sample_number <= @as(f32, @floatFromInt(self.keyframes[0].frame_number))) {
            return .{
                .from_index = 0,
                .to_index = 0,
                .blend = 0.0,
                .sample_number = sample_number,
            };
        }

        for (self.keyframes[1..], 1..) |frame, index| {
            const upper = @as(f32, @floatFromInt(frame.frame_number));
            if (sample_number <= upper) {
                const lower = @as(f32, @floatFromInt(self.keyframes[index - 1].frame_number));
                const denom = @max(upper - lower, 0.0001);
                return .{
                    .from_index = index - 1,
                    .to_index = index,
                    .blend = (sample_number - lower) / denom,
                    .sample_number = sample_number,
                };
            }
        }

        const last_index = self.keyframes.len - 1;
        return .{
            .from_index = last_index,
            .to_index = last_index,
            .blend = 0.0,
            .sample_number = sample_number,
        };
    }
};

const Sample = struct {
    from_index: usize,
    to_index: usize,
    blend: f32,
    sample_number: f32,
};

const KeyframeModel = struct {
    frame_number: usize,
    parsed: x2.Document,

    fn load(allocator: std.mem.Allocator, asset_catalog: *const assets.Catalog, frame_ref: FrameRef) !KeyframeModel {
        const entry = asset_catalog.model_entries[frame_ref.entry_index];
        const decoded = try asset_catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        return .{
            .frame_number = frame_ref.frame_number,
            .parsed = try x2.parse(allocator, decoded),
        };
    }

    fn deinit(self: *KeyframeModel) void {
        self.parsed.deinit();
    }
};

const ClipBuilder = struct {
    name: []const u8,
    duration_seconds: ?f32 = null,
    mode: Mode = .once,
    trigger_steps: ?[]const []const u8 = null,
};

fn finalizeClip(
    allocator: std.mem.Allocator,
    asset_catalog: *const assets.Catalog,
    builder: ClipBuilder,
) !Clip {
    const family_key = try allocator.dupe(u8, familyKeyFromPath(builder.name));
    const frames = try resolveFramesForFamily(allocator, asset_catalog, family_key);
    return .{
        .name = builder.name,
        .family_key = family_key,
        .duration_seconds = builder.duration_seconds orelse return error.MissingAnimationDuration,
        .mode = builder.mode,
        .trigger_steps = builder.trigger_steps orelse return error.MissingAnimationTrigger,
        .frames = frames,
    };
}

fn resolveFramesForFamily(
    allocator: std.mem.Allocator,
    asset_catalog: *const assets.Catalog,
    family_key: []const u8,
) ![]const FrameRef {
    var frames: std.ArrayList(FrameRef) = .empty;
    defer frames.deinit(allocator);

    for (asset_catalog.model_entries, 0..) |entry, entry_index| {
        if (std.ascii.eqlIgnoreCase(familyKeyFromPath(entry.path), family_key)) {
            try frames.append(allocator, .{
                .entry_index = entry_index,
                .frame_number = parseFrameNumber(entry.path),
            });
        }
    }

    std.sort.insertion(FrameRef, frames.items, {}, lessThanFrameRef);
    return frames.toOwnedSlice(allocator);
}

fn lessThanFrameRef(_: void, lhs: FrameRef, rhs: FrameRef) bool {
    return lhs.frame_number < rhs.frame_number;
}

fn familyKeyFromPath(path: []const u8) []const u8 {
    const basename = std.fs.path.basename(path);
    const stem = basename[0 .. std.mem.lastIndexOfScalar(u8, basename, '.') orelse basename.len];
    const dash_index = std.mem.lastIndexOfScalar(u8, stem, '-') orelse return stem;
    return stem[0..dash_index];
}

fn parseFrameNumber(path: []const u8) usize {
    const basename = std.fs.path.basename(path);
    const stem = basename[0 .. std.mem.lastIndexOfScalar(u8, basename, '.') orelse basename.len];
    const dash_index = std.mem.lastIndexOfScalar(u8, stem, '-') orelse return 0;
    return std.fmt.parseUnsigned(usize, stem[dash_index + 1 ..], 10) catch 0;
}

const LineKey = enum {
    test_directive,
    anim_directive,
    duration_directive,
    mode_directive,
    trigger_directive,
    anim_end_directive,
};

fn parseLineKey(line: []const u8) ?LineKey {
    if (std.mem.startsWith(u8, line, "Test:")) return .test_directive;
    if (std.mem.startsWith(u8, line, "Anim:")) return .anim_directive;
    if (std.mem.startsWith(u8, line, "Duration:")) return .duration_directive;
    if (std.mem.startsWith(u8, line, "Mode:")) return .mode_directive;
    if (std.mem.startsWith(u8, line, "Trigger:")) return .trigger_directive;
    if (std.mem.startsWith(u8, line, "AnimEnd:")) return .anim_end_directive;
    return null;
}

fn parseMode(value: []const u8) !Mode {
    if (std.ascii.eqlIgnoreCase(value, "Loop")) return .loop;
    if (std.ascii.eqlIgnoreCase(value, "Pingpong")) return .pingpong;
    if (std.ascii.eqlIgnoreCase(value, "Once")) return .once;
    return error.UnsupportedAnimationMode;
}

fn valueAfterColon(line: []const u8) []const u8 {
    const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse return "";
    return std.mem.trim(u8, line[colon_index + 1 ..], " \t\r");
}

fn isCommentLine(line: []const u8) bool {
    return std.mem.startsWith(u8, line, "/*") or std.mem.startsWith(u8, line, "*") or std.mem.startsWith(u8, line, "*/");
}

fn parseTriggerBlock(
    allocator: std.mem.Allocator,
    lines: *std.mem.SplitIterator(u8, .scalar),
) ![]const []const u8 {
    var steps: std.ArrayList([]const u8) = .empty;
    defer steps.deinit(allocator);

    while (lines.peek()) |raw_line| {
        const line = std.mem.trim(u8, raw_line, " \t\r");
        if (line.len == 0 or isCommentLine(line)) {
            _ = lines.next();
            continue;
        }
        if (std.mem.startsWith(u8, line, "AnimEnd:")) break;
        if (!isValidTriggerStep(line)) return error.UnsupportedAnimationTriggerStep;

        _ = lines.next();
        try steps.append(allocator, try allocator.dupe(u8, line));
    }

    if (steps.items.len == 0) return error.EmptyAnimationTrigger;
    return try steps.toOwnedSlice(allocator);
}

fn isValidTriggerStep(line: []const u8) bool {
    if (std.ascii.eqlIgnoreCase(line, "START") or std.ascii.eqlIgnoreCase(line, "LAST")) return true;
    if (line.len != 3) return false;
    for (line) |ch| {
        if (!std.ascii.isDigit(ch)) return false;
    }
    return true;
}

fn normalizedLoop(elapsed: f64, duration: f64) f64 {
    const cycles = elapsed / duration;
    return cycles - @floor(cycles);
}

fn normalizedPingpong(elapsed: f64, duration: f64) f64 {
    const cycles = elapsed / duration;
    const base = cycles - @floor(cycles);
    const whole_cycles = @as(i64, @intFromFloat(@floor(cycles)));
    return if (@mod(whole_cycles, 2) == 0) base else 1.0 - base;
}

test "parse animation catalog and resolve turbo bobalong" {
    var asset_catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer asset_catalog.deinit();

    var animation_catalog = try Catalog.load(std.testing.allocator, &asset_catalog);
    defer animation_catalog.deinit();

    const clip_index = animation_catalog.findClipIndexForModelPath("X/TURBO-BOBALONG-003.X2") orelse return error.ClipNotFound;
    const clip = animation_catalog.clips[clip_index];
    try std.testing.expectEqualStrings("turbo-bobalong-000.x", clip.name);
    try std.testing.expectEqual(Mode.pingpong, clip.mode);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), clip.duration_seconds, 0.0001);
    try std.testing.expectEqual(@as(usize, 7), clip.trigger_steps.len);
    try std.testing.expectEqualStrings("START", clip.trigger_steps[0]);
    try std.testing.expectEqualStrings("LAST", clip.trigger_steps[clip.trigger_steps.len - 1]);
    try std.testing.expectEqual(@as(usize, 5), clip.frames.len);
    try std.testing.expectEqual(@as(usize, 0), clip.frames[0].frame_number);
    try std.testing.expectEqual(@as(usize, 4), clip.frames[4].frame_number);
}

test "resolve animation frame family for turbo bobalong" {
    var asset_catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer asset_catalog.deinit();

    const frames = try resolveFramesForFamily(std.testing.allocator, &asset_catalog, "TURBO-BOBALONG");
    defer std.testing.allocator.free(frames);

    try std.testing.expectEqual(@as(usize, 5), frames.len);
    try std.testing.expectEqual(@as(usize, 0), frames[0].frame_number);
    try std.testing.expectEqual(@as(usize, 4), frames[4].frame_number);
    try std.testing.expectEqualStrings("X/TURBO-BOBALONG-000.X2", asset_catalog.model_entries[frames[0].entry_index].path);
    try std.testing.expectEqualStrings("X/TURBO-BOBALONG-004.X2", asset_catalog.model_entries[frames[4].entry_index].path);
}

test "parse shipped animation catalog" {
    var asset_catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer asset_catalog.deinit();

    var animation_catalog = try Catalog.load(std.testing.allocator, &asset_catalog);
    defer animation_catalog.deinit();

    try std.testing.expectEqual(@as(usize, 29), animation_catalog.clips.len);
    for (animation_catalog.clips) |clip| {
        try std.testing.expect(clip.duration_seconds > 0.0);
        try std.testing.expect(clip.trigger_steps.len >= 2);
        try std.testing.expectEqualStrings("START", clip.trigger_steps[0]);
        try std.testing.expectEqualStrings("LAST", clip.trigger_steps[clip.trigger_steps.len - 1]);
    }
}

test "pingpong sample is stable at fixed elapsed time" {
    const frame_numbers = [_]usize{ 0, 1, 2, 3, 4 };
    const clip = Clip{
        .name = "turbo-bobalong-000.x",
        .family_key = "TURBO-BOBALONG",
        .duration_seconds = 0.5,
        .mode = .pingpong,
        .trigger_steps = &.{ "START", "LAST" },
        .frames = &.{
            .{ .entry_index = 0, .frame_number = 0 },
            .{ .entry_index = 1, .frame_number = 1 },
            .{ .entry_index = 2, .frame_number = 2 },
            .{ .entry_index = 3, .frame_number = 3 },
            .{ .entry_index = 4, .frame_number = 4 },
        },
    };

    const sample_a = sampleFrameNumbers(&clip, &frame_numbers, 0.125);
    const sample_b = sampleFrameNumbers(&clip, &frame_numbers, 0.125);

    try std.testing.expectEqual(sample_a.from_index, sample_b.from_index);
    try std.testing.expectEqual(sample_a.to_index, sample_b.to_index);
    try std.testing.expectApproxEqAbs(sample_a.blend, sample_b.blend, 0.000001);
}

fn sampleFrameNumbers(clip: *const Clip, frame_numbers: []const usize, elapsed_seconds: f64) Sample {
    const duration = @max(@as(f64, clip.duration_seconds), 0.0001);
    const last_frame_number = @as(f64, @floatFromInt(frame_numbers[frame_numbers.len - 1]));
    const phase = switch (clip.mode) {
        .once => @min(elapsed_seconds / duration, 1.0),
        .loop => normalizedLoop(elapsed_seconds, duration),
        .pingpong => normalizedPingpong(elapsed_seconds, duration),
    };
    const sample_number = @as(f32, @floatCast(phase * last_frame_number));

    if (sample_number <= @as(f32, @floatFromInt(frame_numbers[0]))) {
        return .{
            .from_index = 0,
            .to_index = 0,
            .blend = 0.0,
            .sample_number = sample_number,
        };
    }

    for (frame_numbers[1..], 1..) |frame_number, index| {
        const upper = @as(f32, @floatFromInt(frame_number));
        if (sample_number <= upper) {
            const lower = @as(f32, @floatFromInt(frame_numbers[index - 1]));
            const denom = @max(upper - lower, 0.0001);
            return .{
                .from_index = index - 1,
                .to_index = index,
                .blend = (sample_number - lower) / denom,
                .sample_number = sample_number,
            };
        }
    }

    const last_index = frame_numbers.len - 1;
    return .{
        .from_index = last_index,
        .to_index = last_index,
        .blend = 0.0,
        .sample_number = sample_number,
    };
}
