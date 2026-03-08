const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Annotation = struct {
    raw: []const u8,
    key: []const u8,
    value: ?[]const u8 = null,
};

pub const Row = struct {
    cells: []const u8,
    annotation: ?Annotation = null,
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    segment_id: usize,
    name: []const u8,
    width: usize,
    height: usize,
    rows: []const Row,

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

    var rows: std.ArrayList(Row) = .empty;
    defer rows.deinit(arena_allocator);

    var segment_id: ?usize = null;
    var name: ?[]const u8 = null;
    var in_data = false;
    var width: usize = 0;

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |raw_line| {
        if (in_data) {
            const line = std.mem.trimRight(u8, raw_line, "\r");
            if (line.len == 0) continue;

            const cell_end = @min(@as(usize, 10), line.len);
            const cells = try arena_allocator.dupe(u8, line[0..cell_end]);
            width = @max(width, cells.len);

            const suffix = if (line.len > 10) std.mem.trim(u8, line[10..], " \t\r") else "";
            try rows.append(arena_allocator, .{
                .cells = cells,
                .annotation = if (suffix.len > 0) try parseAnnotation(arena_allocator, suffix) else null,
            });
            continue;
        }

        const line = std.mem.trim(u8, raw_line, " \t\r");
        if (line.len == 0 or std.mem.startsWith(u8, line, "//")) continue;

        if (std.mem.startsWith(u8, line, "ID:")) {
            segment_id = try std.fmt.parseUnsigned(usize, std.mem.trim(u8, line["ID:".len..], " \t"), 10);
            continue;
        }
        if (std.mem.startsWith(u8, line, "Name:")) {
            name = try parseSingleQuotedValue(arena_allocator, line);
            continue;
        }
        if (std.mem.startsWith(u8, line, "Data:")) {
            in_data = true;
            continue;
        }
    }

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .segment_id = segment_id orelse return error.MissingSegmentId,
        .name = name orelse return error.MissingSegmentName,
        .width = width,
        .height = rows.items.len,
        .rows = try rows.toOwnedSlice(arena_allocator),
    };
}

fn parseAnnotation(allocator: std.mem.Allocator, raw: []const u8) !Annotation {
    if (std.mem.indexOfScalar(u8, raw, '=')) |equals_index| {
        return .{
            .raw = try allocator.dupe(u8, raw),
            .key = try allocator.dupe(u8, std.mem.trim(u8, raw[0..equals_index], " \t")),
            .value = try allocator.dupe(u8, std.mem.trim(u8, raw[equals_index + 1 ..], " \t")),
        };
    }

    const trimmed = std.mem.trim(u8, raw, " \t");
    return .{
        .raw = try allocator.dupe(u8, trimmed),
        .key = try allocator.dupe(u8, trimmed),
        .value = null,
    };
}

fn parseSingleQuotedValue(allocator: std.mem.Allocator, line: []const u8) ![]const u8 {
    const first_quote = std.mem.indexOfScalar(u8, line, '\'') orelse return error.InvalidQuotedValue;
    const second_quote_relative = std.mem.indexOfScalar(u8, line[first_quote + 1 ..], '\'') orelse return error.InvalidQuotedValue;
    return allocator.dupe(u8, line[first_quote + 1 .. first_quote + 1 + second_quote_relative]);
}

test "parse start segment" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var segment = try parseText(std.testing.allocator, data, "SEGMENTS/START.TXT");
    defer segment.deinit();

    try std.testing.expectEqual(@as(usize, 1), segment.segment_id);
    try std.testing.expectEqualStrings("Start", segment.name);
    try std.testing.expectEqual(@as(usize, 10), segment.width);
    try std.testing.expectEqual(@as(usize, 33), segment.height);
    try std.testing.expectEqualStrings("@PPPPPPPP@", segment.rows[5].cells);
    try std.testing.expectEqualStrings("Path", segment.rows[5].annotation.?.key);
    try std.testing.expectEqualStrings("Start", segment.rows[5].annotation.?.value.?);
}

test "parse big jump segment annotation" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/BIG JUMP.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var segment = try parseText(std.testing.allocator, data, "SEGMENTS/BIG JUMP.TXT");
    defer segment.deinit();

    try std.testing.expectEqualStrings("@  {}{}  @", segment.rows[9].cells);
    try std.testing.expectEqualStrings("Ring", segment.rows[9].annotation.?.key);
    try std.testing.expectEqualStrings("Explode", segment.rows[9].annotation.?.value.?);
}
