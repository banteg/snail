const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const ImageEntry = struct {
    archive_path: []const u8,
    width: f32,
    height: f32,
};

pub const Entry = union(enum) {
    text: []const u8,
    image: ImageEntry,
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    duration: f32,
    entries: []Entry,

    pub fn deinit(self: *Definition) void {
        self.arena.deinit();
    }
};

pub const LoadedImage = struct {
    archive_path: []const u8,
    width: f32,
    height: f32,
    texture: assets.LoadedTexture,
};

pub const LoadedEntry = union(enum) {
    text: []const u8,
    image: LoadedImage,
};

pub const Loaded = struct {
    definition: Definition,
    entries: []LoadedEntry,

    pub fn deinit(self: *Loaded, allocator: std.mem.Allocator) void {
        for (self.entries) |*entry| {
            switch (entry.*) {
                .text => {},
                .image => |*image| image.texture.unload(),
            }
        }
        allocator.free(self.entries);
        self.definition.deinit();
    }

    pub fn duration(self: *const Loaded) f32 {
        return self.definition.duration;
    }
};

pub fn loadFromArchive(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    entry: archive.Entry,
) !Loaded {
    const decoded = try catalog.readEntryAlloc(allocator, entry);
    defer allocator.free(decoded);

    var definition = try parseText(allocator, decoded, entry.path);
    errdefer definition.deinit();
    return loadResolvedEntries(allocator, catalog, definition);
}

pub fn loadByPath(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    path: []const u8,
) !Loaded {
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
    var text_block: ?[]const u8 = null;

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
            text_block = std.mem.trim(u8, data[text_start_offset .. text_start_offset + end_index], "\r\n");
            break;
        }
    }

    const resolved_text_block = text_block orelse return error.MissingIntroText;
    const entries = try parseEntries(arena_allocator, resolved_text_block, source_path);

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .duration = duration orelse return error.MissingIntroDuration,
        .entries = entries,
    };
}

fn loadResolvedEntries(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    definition: Definition,
) !Loaded {
    const resolved_entries = try allocator.alloc(LoadedEntry, definition.entries.len);
    var initialized_count: usize = 0;
    errdefer allocator.free(resolved_entries);
    errdefer {
        for (resolved_entries[0..initialized_count]) |*entry| {
            switch (entry.*) {
                .text => {},
                .image => |*image| image.texture.unload(),
            }
        }
    }

    for (definition.entries, 0..) |entry, index| {
        resolved_entries[index] = switch (entry) {
            .text => |text| .{ .text = text },
            .image => |image| .{
                .image = .{
                    .archive_path = image.archive_path,
                    .width = image.width,
                    .height = image.height,
                    .texture = try catalog.loadTextureByPath(allocator, image.archive_path),
                },
            },
        };
        initialized_count = index + 1;
    }

    return .{
        .definition = definition,
        .entries = resolved_entries,
    };
}

fn parseEntries(
    allocator: std.mem.Allocator,
    text_block: []const u8,
    source_path: []const u8,
) ![]Entry {
    var entries: std.ArrayList(Entry) = .empty;
    defer entries.deinit(allocator);

    var lines = std.mem.splitScalar(u8, text_block, '\n');
    while (lines.next()) |raw_line| {
        const line = std.mem.trimRight(u8, raw_line, "\r");
        const stripped = std.mem.trim(u8, line, " \t");
        if (stripped.len > 0 and stripped[0] == '*') {
            try entries.append(allocator, .{ .image = try parseImageDirective(allocator, stripped, source_path) });
            continue;
        }

        const normalized_text = if (stripped.len == 0) "" else try allocator.dupe(u8, stripped);
        try entries.append(allocator, .{ .text = normalized_text });
    }

    return try entries.toOwnedSlice(allocator);
}

fn parseImageDirective(
    allocator: std.mem.Allocator,
    line: []const u8,
    source_path: []const u8,
) !ImageEntry {
    const open_paren = std.mem.indexOfScalar(u8, line, '(') orelse return error.InvalidIntroImageDirective;
    const close_paren = std.mem.lastIndexOfScalar(u8, line, ')') orelse return error.InvalidIntroImageDirective;
    if (close_paren <= open_paren + 1) return error.InvalidIntroImageDirective;

    const image_name = std.mem.trim(u8, line[1..open_paren], " \t");
    if (image_name.len == 0) return error.InvalidIntroImageDirective;

    const inner = line[open_paren + 1 .. close_paren];
    var parts = std.mem.splitScalar(u8, inner, ',');
    const width_text = std.mem.trim(u8, parts.next() orelse return error.InvalidIntroImageDirective, " \t");
    const height_text = std.mem.trim(u8, parts.next() orelse return error.InvalidIntroImageDirective, " \t");
    if (parts.next() != null) return error.InvalidIntroImageDirective;

    const archive_path = try buildImageArchivePath(allocator, source_path, image_name);
    return .{
        .archive_path = archive_path,
        .width = try std.fmt.parseFloat(f32, width_text),
        .height = try std.fmt.parseFloat(f32, height_text),
    };
}

fn buildImageArchivePath(
    allocator: std.mem.Allocator,
    source_path: []const u8,
    image_name: []const u8,
) ![]const u8 {
    const directory = directoryPrefix(source_path);
    const texture_name = if (std.ascii.endsWithIgnoreCase(image_name, ".tga"))
        image_name
    else
        try std.fmt.allocPrint(allocator, "{s}.TGA", .{image_name});
    if (!std.ascii.endsWithIgnoreCase(image_name, ".tga")) {
        return try std.fmt.allocPrint(allocator, "{s}{s}", .{ directory, texture_name });
    }
    return try std.fmt.allocPrint(allocator, "{s}{s}", .{ directory, image_name });
}

fn directoryPrefix(source_path: []const u8) []const u8 {
    const slash_index = std.mem.lastIndexOfScalar(u8, source_path, '/') orelse return "";
    return source_path[0 .. slash_index + 1];
}

fn stripLine(raw_line: []const u8, scratch: []u8) []const u8 {
    const clipped = if (raw_line.len > scratch.len) raw_line[0..scratch.len] else raw_line;
    @memcpy(scratch[0..clipped.len], clipped);
    return std.mem.trim(u8, scratch[0..clipped.len], " \t\r");
}

test "parse intro script body into ordered text entries" {
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
    try std.testing.expectEqual(@as(usize, 3), definition.entries.len);
    switch (definition.entries[0]) {
        .text => |text| try std.testing.expectEqualStrings("Credits", text),
        .image => return error.UnexpectedIntroEntry,
    }
    switch (definition.entries[1]) {
        .text => |text| try std.testing.expectEqualStrings("", text),
        .image => return error.UnexpectedIntroEntry,
    }
    switch (definition.entries[2]) {
        .text => |text| try std.testing.expectEqualStrings("Programming", text),
        .image => return error.UnexpectedIntroEntry,
    }
}

test "parse intro image directive" {
    const source =
        \\Duration:80
        \\Text Start:
        \\*Turbo.tga(1.5,2.0)
        \\Text End:
    ;
    var definition = try parseText(std.testing.allocator, source, "INTRO/INTRO.TXT");
    defer definition.deinit();

    try std.testing.expectEqual(@as(usize, 1), definition.entries.len);
    switch (definition.entries[0]) {
        .text => return error.UnexpectedIntroEntry,
        .image => |image| {
            try std.testing.expectEqualStrings("INTRO/Turbo.tga", image.archive_path);
            try std.testing.expectApproxEqAbs(@as(f32, 1.5), image.width, 0.001);
            try std.testing.expectApproxEqAbs(@as(f32, 2.0), image.height, 0.001);
        },
    }
}
