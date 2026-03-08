const std = @import("std");
const assets = @import("assets.zig");
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
    title: ?[]const u8,
    name: []const u8,
    family_key: []const u8,
    duration_seconds: f32,
    mode: Mode,
    frames: []const FrameRef,
};

pub const Catalog = struct {
    arena: std.heap.ArenaAllocator,
    test_anim: ?[]const u8,
    clips: []const Clip,

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

        var current_title: ?[]const u8 = null;
        var in_comment = false;
        var comment_buffer: std.ArrayList(u8) = .empty;
        defer comment_buffer.deinit(allocator);

        var builder: ?ClipBuilder = null;
        var test_anim: ?[]const u8 = null;

        var lines = std.mem.splitScalar(u8, bytes, '\n');
        while (lines.next()) |raw_line| {
            const line = std.mem.trim(u8, raw_line, " \t\r");
            if (line.len == 0) continue;

            if (in_comment) {
                if (std.mem.indexOf(u8, line, "*/")) |end_index| {
                    const prefix = std.mem.trim(u8, line[0..end_index], " \t\r*");
                    if (prefix.len > 0) {
                        if (comment_buffer.items.len > 0) {
                            try comment_buffer.append(allocator, ' ');
                        }
                        try comment_buffer.appendSlice(allocator, prefix);
                    }
                    current_title = if (comment_buffer.items.len > 0) try arena_allocator.dupe(u8, comment_buffer.items) else null;
                    comment_buffer.clearRetainingCapacity();
                    in_comment = false;
                } else {
                    const content = std.mem.trim(u8, line, " \t\r*");
                    if (content.len > 0) {
                        if (comment_buffer.items.len > 0) {
                            try comment_buffer.append(allocator, ' ');
                        }
                        try comment_buffer.appendSlice(allocator, content);
                    }
                }
                continue;
            }

            if (std.mem.startsWith(u8, line, "/*")) {
                const after = line[2..];
                if (std.mem.indexOf(u8, after, "*/")) |end_index| {
                    const content = std.mem.trim(u8, after[0..end_index], " \t\r*");
                    current_title = if (content.len > 0) try arena_allocator.dupe(u8, content) else null;
                } else {
                    in_comment = true;
                    const content = std.mem.trim(u8, after, " \t\r*");
                    if (content.len > 0) {
                        try comment_buffer.appendSlice(allocator, content);
                    }
                }
                continue;
            }

            if (std.mem.startsWith(u8, line, "Test:")) {
                test_anim = try arena_allocator.dupe(u8, valueAfterColon(line));
                continue;
            }

            if (std.mem.startsWith(u8, line, "Anim:")) {
                builder = .{
                    .title = current_title,
                    .name = try arena_allocator.dupe(u8, valueAfterColon(line)),
                };
                current_title = null;
                continue;
            }

            if (builder == null) continue;

            if (std.mem.startsWith(u8, line, "Duration:")) {
                builder.?.duration_seconds = try std.fmt.parseFloat(f32, valueAfterColon(line));
                continue;
            }

            if (std.mem.startsWith(u8, line, "Mode:")) {
                builder.?.mode = parseMode(valueAfterColon(line));
                continue;
            }

            if (std.mem.startsWith(u8, line, "AnimEnd:")) {
                const built = try finalizeClip(arena_allocator, asset_catalog, builder.?);
                if (built.frames.len > 0) {
                    try clips.append(arena_allocator, built);
                }
                builder = null;
                continue;
            }
        }

        return .{
            .arena = arena,
            .test_anim = test_anim,
            .clips = try clips.toOwnedSlice(arena_allocator),
        };
    }

    pub fn findClipIndexForModelPath(self: *const Catalog, model_path: []const u8) ?usize {
        const family_key = familyKeyFromPath(model_path);
        for (self.clips, 0..) |clip, index| {
            if (std.ascii.eqlIgnoreCase(clip.family_key, family_key)) {
                return index;
            }
        }
        return null;
    }
};

pub fn frameNumberFromPath(path: []const u8) usize {
    return parseFrameNumber(path);
}

pub const Player = struct {
    allocator: std.mem.Allocator,
    clip: *const Clip,
    keyframes: []KeyframeModel,
    rendered: x2.LoadedModel,
    paused: bool = false,
    paused_elapsed: f64 = 0.0,
    start_time: f64,
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
        start_time: f64,
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
            if (!x2.topologyCompatible(&keyframes[0].parsed, &frame.parsed)) {
                return error.AnimationTopologyMismatch;
            }
        }

        const initial_entry = asset_catalog.model_entries[clip.frames[0].entry_index];
        var rendered = try x2.LoadedModel.loadFromArchive(allocator, asset_catalog, initial_entry, flip_v);
        errdefer rendered.deinit();

        var player = Player{
            .allocator = allocator,
            .clip = clip,
            .keyframes = keyframes,
            .rendered = rendered,
            .start_time = start_time,
        };

        player.seekToFrame(initial_frame_number, start_time) catch {};
        try player.update(start_time);
        return player;
    }

    pub fn deinit(self: *Player) void {
        self.rendered.deinit();
        for (self.keyframes) |*frame| {
            frame.deinit();
        }
        self.allocator.free(self.keyframes);
    }

    pub fn update(self: *Player, now: f64) !void {
        if (self.keyframes.len == 1) {
            self.current_from_index = 0;
            self.current_to_index = 0;
            self.current_blend = 0.0;
            self.current_sample_number = @floatFromInt(self.keyframes[0].frame_number);
            return;
        }

        const frame_sample = self.sample(now);
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

    pub fn restart(self: *Player, now: f64) void {
        self.paused = false;
        self.paused_elapsed = 0.0;
        self.start_time = now;
    }

    pub fn togglePause(self: *Player, now: f64) void {
        if (self.paused) {
            self.start_time = now - self.paused_elapsed;
            self.paused = false;
        } else {
            self.paused_elapsed = elapsedSeconds(self, now);
            self.paused = true;
        }
    }

    fn seekToFrame(self: *Player, frame_number: usize, now: f64) !void {
        const last = @as(f64, @floatFromInt(self.keyframes[self.keyframes.len - 1].frame_number));
        if (last <= 0.0 or self.clip.duration_seconds <= 0.0) {
            self.start_time = now;
            return;
        }

        const clamped = @min(@as(f64, @floatFromInt(frame_number)), last);
        const phase = clamped / last;
        self.start_time = now - phase * self.clip.duration_seconds;
    }

    fn elapsedSeconds(self: *const Player, now: f64) f64 {
        return if (self.paused) self.paused_elapsed else now - self.start_time;
    }

    fn sample(self: *const Player, now: f64) Sample {
        const elapsed = @max(self.elapsedSeconds(now), 0.0);
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
    parsed: x2.ParsedModel,

    fn load(allocator: std.mem.Allocator, asset_catalog: *const assets.Catalog, frame_ref: FrameRef) !KeyframeModel {
        const entry = asset_catalog.model_entries[frame_ref.entry_index];
        const decoded = try asset_catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        return .{
            .frame_number = frame_ref.frame_number,
            .parsed = try x2.parseModel(allocator, decoded),
        };
    }

    fn deinit(self: *KeyframeModel) void {
        self.parsed.deinit();
    }
};

const ClipBuilder = struct {
    title: ?[]const u8 = null,
    name: []const u8,
    duration_seconds: f32 = 1.0,
    mode: Mode = .once,
};

fn finalizeClip(
    allocator: std.mem.Allocator,
    asset_catalog: *const assets.Catalog,
    builder: ClipBuilder,
) !Clip {
    const family_key = try allocator.dupe(u8, familyKeyFromPath(builder.name));
    const frames = try resolveFramesForFamily(allocator, asset_catalog, family_key);
    return .{
        .title = builder.title,
        .name = builder.name,
        .family_key = family_key,
        .duration_seconds = builder.duration_seconds,
        .mode = builder.mode,
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

    insertionSortFrames(frames.items);
    return frames.toOwnedSlice(allocator);
}

fn insertionSortFrames(frames: []FrameRef) void {
    var index: usize = 1;
    while (index < frames.len) : (index += 1) {
        const value = frames[index];
        var position = index;
        while (position > 0 and frames[position - 1].frame_number > value.frame_number) : (position -= 1) {
            frames[position] = frames[position - 1];
        }
        frames[position] = value;
    }
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

fn parseMode(value: []const u8) Mode {
    if (std.ascii.eqlIgnoreCase(value, "Loop")) return .loop;
    if (std.ascii.eqlIgnoreCase(value, "Pingpong")) return .pingpong;
    return .once;
}

fn valueAfterColon(line: []const u8) []const u8 {
    const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse return "";
    return std.mem.trim(u8, line[colon_index + 1 ..], " \t\r");
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
    try std.testing.expectEqual(@as(usize, 5), clip.frames.len);
    try std.testing.expectEqual(@as(usize, 0), clip.frames[0].frame_number);
    try std.testing.expectEqual(@as(usize, 4), clip.frames[4].frame_number);
}

test "load animation player for turbo bobalong" {
    var asset_catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer asset_catalog.deinit();

    var animation_catalog = try Catalog.load(std.testing.allocator, &asset_catalog);
    defer animation_catalog.deinit();

    const clip_index = animation_catalog.findClipIndexForModelPath("X/TURBO-BOBALONG-003.X2") orelse return error.ClipNotFound;
    const clip = &animation_catalog.clips[clip_index];

    var player = try Player.load(
        std.testing.allocator,
        &asset_catalog,
        clip,
        true,
        3,
        0.0,
    );
    defer player.deinit();

    try std.testing.expectEqual(@as(usize, 5), player.keyframes.len);
    try std.testing.expectEqual(@as(usize, 263), player.rendered.parsed.vertices.len);
}
