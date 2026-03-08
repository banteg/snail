const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    duration: f32,
    text: []const u8,

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

pub fn loadByPath(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    path: []const u8,
) !Definition {
    const entry = catalog.dat.entryByPath(path) orelse return error.EntryNotFound;
    return loadFromArchive(allocator, catalog, entry);
}

pub fn parseText(
    allocator: std.mem.Allocator,
    data: []const u8,
    source_path: []const u8,
) !Definition {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var duration: ?f32 = null;
    var text: ?[]const u8 = null;

    const start_marker = "Text Start:";
    const end_marker = "Text End:";
    var lines = std.mem.splitScalar(u8, data, '\n');
    var scratch: [4096]u8 = undefined;
    while (lines.next()) |raw_line| {
        const line = stripLine(raw_line, &scratch);
        if (line.len == 0) continue;

        if (std.mem.startsWith(u8, line, "Duration:")) {
            duration = try std.fmt.parseFloat(f32, std.mem.trim(u8, line["Duration:".len..], " \t"));
            continue;
        }

        if (std.mem.eql(u8, line, start_marker)) {
            const text_start_offset = @intFromPtr(raw_line.ptr) - @intFromPtr(data.ptr) + raw_line.len + 1;
            const end_index = std.mem.indexOf(u8, data[text_start_offset..], end_marker) orelse return error.MissingIntroTextEnd;
            text = try arena_allocator.dupe(u8, std.mem.trim(u8, data[text_start_offset .. text_start_offset + end_index], "\r\n"));
            break;
        }
    }

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .duration = duration orelse return error.MissingIntroDuration,
        .text = text orelse return error.MissingIntroText,
    };
}

fn stripLine(raw_line: []const u8, scratch: []u8) []const u8 {
    const clipped = if (raw_line.len > scratch.len) raw_line[0..scratch.len] else raw_line;
    @memcpy(scratch[0..clipped.len], clipped);
    return std.mem.trim(u8, scratch[0..clipped.len], " \t\r");
}

test "parse intro script body" {
    const source =
        \\/* Intro script */
        \\
        \\Duration:35
        \\
        \\Text Start:
        \\Credits
        \\
        \\Programming
        \\Text End:
    ;
    var definition = try parseText(std.testing.allocator, source, "INTRO/CREDITS.TXT");
    defer definition.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 35.0), definition.duration, 0.001);
    try std.testing.expectEqualStrings("Credits\n\nProgramming", definition.text);
}
