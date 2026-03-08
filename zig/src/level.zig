const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Rgb = struct {
    r: i32,
    g: i32,
    b: i32,
};

pub const SegmentAttribute = struct {
    key: []const u8,
    value: []const u8,
};

pub const SegmentEntry = struct {
    path: []const u8,
    duration: ?f32 = null,
    sample: ?[]const u8 = null,
    message: ?[]const u8 = null,
    angle: ?f32 = null,
    attributes: []const SegmentAttribute = &.{},
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    name: []const u8,
    mode: []const u8,
    track: ?i32 = null,
    galaxy_text: ?[]const u8 = null,
    background: ?[]const u8 = null,
    fringe: ?Rgb = null,
    parcels: ?usize = null,
    quota: ?usize = null,
    speed: ?usize = null,
    garbage: ?usize = null,
    salt: ?usize = null,
    flags: []const []const u8 = &.{},
    random: ?bool = null,
    length_value: ?usize = null,
    length_raw: ?[]const u8 = null,
    segments: []const SegmentEntry = &.{},
    first_segments: []const []const u8 = &.{},
    last_segments: []const []const u8 = &.{},

    pub fn deinit(self: *Definition) void {
        self.arena.deinit();
    }
};

pub fn loadFromArchive(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    entry: archive.Entry,
) !Definition {
    const decoded = try catalog.readEntryAlloc(allocator, entry);
    defer allocator.free(decoded);
    return parseText(allocator, decoded, entry.path);
}

pub fn parseText(
    allocator: std.mem.Allocator,
    data: []const u8,
    source_path: []const u8,
) !Definition {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var segments: std.ArrayList(SegmentEntry) = .empty;
    defer segments.deinit(arena_allocator);
    var first_segments: std.ArrayList([]const u8) = .empty;
    defer first_segments.deinit(arena_allocator);
    var last_segments: std.ArrayList([]const u8) = .empty;
    defer last_segments.deinit(arena_allocator);

    var name: []const u8 = "";
    var mode: []const u8 = "";
    var track: ?i32 = null;
    var galaxy_text: ?[]const u8 = null;
    var background: ?[]const u8 = null;
    var fringe: ?Rgb = null;
    var parcels: ?usize = null;
    var quota: ?usize = null;
    var speed: ?usize = null;
    var garbage: ?usize = null;
    var salt: ?usize = null;
    var flags: []const []const u8 = &.{};
    var random: ?bool = null;
    var length_value: ?usize = null;
    var length_raw: ?[]const u8 = null;

    var lines = std.mem.splitScalar(u8, data, '\n');
    var scratch: [4096]u8 = undefined;
    while (lines.next()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (line.len == 0) continue;

        if (std.mem.eql(u8, line, "GalaxyText:")) {
            galaxy_text = try parseBracedBlock(arena_allocator, &lines);
            continue;
        }
        if (std.mem.startsWith(u8, line, "Segments Begin:")) {
            const inline_value = std.mem.trim(u8, line["Segments Begin:".len..], " \t");
            try parseSegmentBlock(arena_allocator, &lines, &segments, inline_value);
            continue;
        }
        if (std.mem.startsWith(u8, line, "First:")) {
            const inline_value = std.mem.trim(u8, line["First:".len..], " \t");
            try parsePathBlock(arena_allocator, &lines, &first_segments, inline_value);
            continue;
        }
        if (std.mem.startsWith(u8, line, "Last:")) {
            const inline_value = std.mem.trim(u8, line["Last:".len..], " \t");
            try parsePathBlock(arena_allocator, &lines, &last_segments, inline_value);
            continue;
        }

        const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse continue;
        const key = std.mem.trim(u8, line[0..colon_index], " \t");
        const value = std.mem.trim(u8, line[colon_index + 1 ..], " \t");

        if (std.ascii.eqlIgnoreCase(key, "Name")) {
            name = try parseSingleQuotedValue(arena_allocator, line);
        } else if (std.ascii.eqlIgnoreCase(key, "Mode")) {
            mode = try arena_allocator.dupe(u8, value);
        } else if (std.ascii.eqlIgnoreCase(key, "Track")) {
            track = try std.fmt.parseInt(i32, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Background")) {
            background = try arena_allocator.dupe(u8, value);
        } else if (std.ascii.eqlIgnoreCase(key, "Fringe")) {
            fringe = try parseRgb(value);
        } else if (std.ascii.eqlIgnoreCase(key, "Parcels")) {
            parcels = try std.fmt.parseUnsigned(usize, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Quota")) {
            quota = try std.fmt.parseUnsigned(usize, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Speed")) {
            speed = try std.fmt.parseUnsigned(usize, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Slug") or std.ascii.eqlIgnoreCase(key, "Garbage")) {
            garbage = try std.fmt.parseUnsigned(usize, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Salt")) {
            salt = try std.fmt.parseUnsigned(usize, value, 10);
        } else if (std.ascii.eqlIgnoreCase(key, "Flags")) {
            flags = try parseFlags(arena_allocator, value);
        } else if (std.ascii.eqlIgnoreCase(key, "Random")) {
            random = std.ascii.eqlIgnoreCase(value, "yes");
        } else if (std.ascii.eqlIgnoreCase(key, "Length")) {
            if (std.ascii.eqlIgnoreCase(value, "auto")) {
                length_raw = try arena_allocator.dupe(u8, value);
            } else {
                length_value = std.fmt.parseUnsigned(usize, value, 10) catch null;
                if (length_value == null) {
                    length_raw = try arena_allocator.dupe(u8, value);
                }
            }
        }
    }

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .name = name,
        .mode = mode,
        .track = track,
        .galaxy_text = galaxy_text,
        .background = background,
        .fringe = fringe,
        .parcels = parcels,
        .quota = quota,
        .speed = speed,
        .garbage = garbage,
        .salt = salt,
        .flags = flags,
        .random = random,
        .length_value = length_value,
        .length_raw = length_raw,
        .segments = try segments.toOwnedSlice(arena_allocator),
        .first_segments = try first_segments.toOwnedSlice(arena_allocator),
        .last_segments = try last_segments.toOwnedSlice(arena_allocator),
    };
}

fn stripInlineComments(line: []const u8, scratch: []u8) ![]const u8 {
    var out_index: usize = 0;
    var index: usize = 0;
    while (index < line.len) {
        if (index + 1 < line.len and line[index] == '/' and line[index + 1] == '*') {
            index += 2;
            while (index + 1 < line.len and !(line[index] == '*' and line[index + 1] == '/')) : (index += 1) {}
            if (index + 1 < line.len) {
                index += 2;
            } else {
                break;
            }
            continue;
        }

        if (out_index >= scratch.len) return error.LineTooLong;
        scratch[out_index] = line[index];
        out_index += 1;
        index += 1;
    }

    return std.mem.trim(u8, scratch[0..out_index], " \t\r");
}

fn parseBracedBlock(
    allocator: std.mem.Allocator,
    lines: *std.mem.SplitIterator(u8, .scalar),
) !?[]const u8 {
    var scratch: [4096]u8 = undefined;
    while (lines.peek()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (line.len == 0) {
            _ = lines.next();
            continue;
        }
        if (std.mem.eql(u8, line, "{")) {
            _ = lines.next();
            break;
        }
        return null;
    }

    var block: std.ArrayList(u8) = .empty;
    defer block.deinit(allocator);
    while (lines.next()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (std.mem.eql(u8, line, "}")) break;
        const trimmed_right = std.mem.trimRight(u8, raw_line, "\r");
        if (trimmed_right.len > 0) {
            if (block.items.len > 0) try block.append(allocator, '\n');
            try block.appendSlice(allocator, std.mem.trimRight(u8, trimmed_right, " \t"));
        }
    }

    if (block.items.len == 0) return null;
    return try block.toOwnedSlice(allocator);
}

fn parseSegmentBlock(
    allocator: std.mem.Allocator,
    lines: *std.mem.SplitIterator(u8, .scalar),
    output: *std.ArrayList(SegmentEntry),
    inline_value: []const u8,
) !void {
    if (inline_value.len > 0) {
        try output.append(allocator, try parseSegmentEntry(allocator, inline_value));
    }

    var scratch: [4096]u8 = undefined;
    while (lines.next()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (line.len == 0) continue;
        if (std.mem.startsWith(u8, line, "Segments End:")) break;
        try output.append(allocator, try parseSegmentEntry(allocator, line));
    }
}

fn parsePathBlock(
    allocator: std.mem.Allocator,
    lines: *std.mem.SplitIterator(u8, .scalar),
    output: *std.ArrayList([]const u8),
    inline_value: []const u8,
) !void {
    if (inline_value.len > 0) {
        try output.append(allocator, try allocator.dupe(u8, inline_value));
    }

    var scratch: [4096]u8 = undefined;
    while (lines.peek()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (line.len == 0) {
            _ = lines.next();
            if (output.items.len > 0) break;
            continue;
        }
        if (looksLikeField(line)) break;
        _ = lines.next();
        try output.append(allocator, try allocator.dupe(u8, line));
    }
}

fn parseSegmentEntry(allocator: std.mem.Allocator, line: []const u8) !SegmentEntry {
    const path_end = findTxtPathEnd(line) orelse return error.InvalidLevelSegmentEntry;
    const path = try allocator.dupe(u8, std.mem.trim(u8, line[0..path_end], " \t"));
    const remainder = std.mem.trim(u8, line[path_end..], " \t");

    var attributes: std.ArrayList(SegmentAttribute) = .empty;
    defer attributes.deinit(allocator);

    var entry = SegmentEntry{
        .path = path,
    };

    var index: usize = 0;
    while (index < remainder.len) {
        while (index < remainder.len and std.ascii.isWhitespace(remainder[index])) : (index += 1) {}
        if (index >= remainder.len) break;

        const key_start = index;
        while (index < remainder.len and remainder[index] != '=' and !std.ascii.isWhitespace(remainder[index])) : (index += 1) {}
        if (index >= remainder.len or remainder[index] != '=') break;
        const key_text = remainder[key_start..index];
        index += 1;

        const value_text = if (index < remainder.len and remainder[index] == '"') blk: {
            index += 1;
            const value_start = index;
            while (index < remainder.len and remainder[index] != '"') : (index += 1) {}
            const value = remainder[value_start..@min(index, remainder.len)];
            if (index < remainder.len and remainder[index] == '"') index += 1;
            break :blk value;
        } else blk: {
            const value_start = index;
            while (index < remainder.len and !std.ascii.isWhitespace(remainder[index])) : (index += 1) {}
            break :blk remainder[value_start..index];
        };

        const key = try allocator.dupe(u8, key_text);
        const value = try allocator.dupe(u8, value_text);
        try attributes.append(allocator, .{ .key = key, .value = value });

        if (std.ascii.eqlIgnoreCase(key, "Duration")) {
            entry.duration = try std.fmt.parseFloat(f32, value);
        } else if (std.ascii.eqlIgnoreCase(key, "Sample")) {
            entry.sample = value;
        } else if (std.ascii.eqlIgnoreCase(key, "Message")) {
            entry.message = value;
        } else if (std.ascii.eqlIgnoreCase(key, "Angle")) {
            entry.angle = try std.fmt.parseFloat(f32, value);
        }
    }

    entry.attributes = try attributes.toOwnedSlice(allocator);
    return entry;
}

fn findTxtPathEnd(line: []const u8) ?usize {
    if (line.len < 4) return null;
    var index: usize = 0;
    while (index + 4 <= line.len) : (index += 1) {
        const slice = line[index .. index + 4];
        if (std.ascii.eqlIgnoreCase(slice, ".txt")) return index + 4;
    }
    return null;
}

fn looksLikeField(line: []const u8) bool {
    const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse return false;
    if (colon_index == 0) return false;
    for (line[0..colon_index]) |char| {
        if (!(std.ascii.isAlphabetic(char) or std.ascii.isDigit(char) or char == ' ')) return false;
    }
    return true;
}

fn parseFlags(allocator: std.mem.Allocator, value: []const u8) ![]const []const u8 {
    var flags: std.ArrayList([]const u8) = .empty;
    defer flags.deinit(allocator);

    var parts = std.mem.tokenizeAny(u8, value, ", \t");
    while (parts.next()) |part| {
        try flags.append(allocator, try allocator.dupe(u8, part));
    }

    return try flags.toOwnedSlice(allocator);
}

fn parseRgb(value: []const u8) !Rgb {
    var parts = std.mem.tokenizeAny(u8, value, "(,)");
    const r = parts.next() orelse return error.InvalidRgb;
    const g = parts.next() orelse return error.InvalidRgb;
    const b = parts.next() orelse return error.InvalidRgb;
    return .{
        .r = try std.fmt.parseInt(i32, std.mem.trim(u8, r, " \t"), 10),
        .g = try std.fmt.parseInt(i32, std.mem.trim(u8, g, " \t"), 10),
        .b = try std.fmt.parseInt(i32, std.mem.trim(u8, b, " \t"), 10),
    };
}

fn parseSingleQuotedValue(allocator: std.mem.Allocator, line: []const u8) ![]const u8 {
    const first_quote = std.mem.indexOfScalar(u8, line, '\'') orelse return error.InvalidQuotedValue;
    const second_quote_relative = std.mem.indexOfScalar(u8, line[first_quote + 1 ..], '\'') orelse return error.InvalidQuotedValue;
    return allocator.dupe(u8, line[first_quote + 1 .. first_quote + 1 + second_quote_relative]);
}

test "parse arcade000 level" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/LEVELS/ARCADE000.TXT", 1 << 20);
    defer std.testing.allocator.free(data);

    var level = try parseText(std.testing.allocator, data, "LEVELS/ARCADE000.TXT");
    defer level.deinit();

    try std.testing.expectEqualStrings("Test", level.name);
    try std.testing.expectEqualStrings("arcade", level.mode);
    try std.testing.expectEqual(@as(?usize, 65), level.garbage);
    try std.testing.expectEqual(@as(?usize, 500), level.length_value);
    try std.testing.expectEqual(@as(usize, 4), level.segments.len);
    try std.testing.expectEqualStrings("Wibble.txt", level.segments[0].path);
    try std.testing.expectEqualStrings("Start.txt", level.first_segments[0]);
    try std.testing.expectEqualStrings("Finish.txt", level.last_segments[0]);
}

test "parse tutorial level metadata" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/LEVELS/TUTORIAL.TXT", 1 << 20);
    defer std.testing.allocator.free(data);

    var level = try parseText(std.testing.allocator, data, "LEVELS/TUTORIAL.TXT");
    defer level.deinit();

    try std.testing.expectEqualStrings("tutorial", level.mode);
    try std.testing.expectEqual(@as(?i32, 0), level.track);
    try std.testing.expectEqual(@as(usize, 23), level.segments.len);
    try std.testing.expectApproxEqAbs(@as(f32, 5.5), level.segments[0].duration.?, 0.0001);
    try std.testing.expectEqualStrings("Voice/tut1.ogg", level.segments[0].sample.?);
    try std.testing.expect(std.mem.indexOf(u8, level.segments[0].message.?, "Turbo the Snail") != null);
}

test "parse level segment angle and galaxy text" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/LEVELS/ARCADE038.TXT", 1 << 20);
    defer std.testing.allocator.free(data);

    var level = try parseText(std.testing.allocator, data, "LEVELS/ARCADE038.TXT");
    defer level.deinit();

    try std.testing.expect(std.mem.indexOf(u8, level.galaxy_text.?, "jetpack") != null);
    const worm = level.segments[10];
    try std.testing.expectEqualStrings("Worm.txt", worm.path);
    try std.testing.expectEqual(@as(f32, 360.0), worm.angle.?);
}
