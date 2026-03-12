const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Vec3 = struct {
    x: f32,
    y: f32,
    z: f32,
};

pub const RingKind = enum {
    none,
    normal,
    powerup,
    explode,
    slow,
};

pub const ParcelAnnotation = struct {
    id: i32,
    offset: Vec3,
};

pub const ModelAnnotation = struct {
    name: []const u8,
    offset: Vec3,
};

pub const Annotation = union(enum) {
    path: []const u8,
    ring: RingKind,
    parcel: ParcelAnnotation,
    model: ModelAnnotation,
    jetpack_off,
    no_fall,

    pub const Tag = std.meta.Tag(Annotation);

    pub fn tag(self: Annotation) Tag {
        return std.meta.activeTag(self);
    }
};

const AnnotationKey = enum {
    path,
    ring,
    parcel,
    model,
    jetpack,
};

pub const Row = struct {
    cells: []const u8,
    marked: bool = false,
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
    var saw_data_guard = false;
    var width: usize = 0;

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |raw_line| {
        if (in_data) {
            const line = std.mem.trimRight(u8, raw_line, "\r");
            if (line.len == 0) continue;
            // Windows treats the full-@ guard rows as segment data fences, not as real rows.
            if (!saw_data_guard) {
                if (isSegmentDataFence(line)) {
                    saw_data_guard = true;
                    continue;
                }
            } else if (isSegmentDataFence(line)) {
                break;
            }

            const cell_end = @min(@as(usize, 10), line.len);
            const cells = try arena_allocator.dupe(u8, line[0..cell_end]);
            width = @max(width, cells.len);

            var marked = false;
            var suffix_slice: []const u8 = "";
            if (line.len > 10) {
                suffix_slice = line[10..];
                if (suffix_slice.len > 0 and suffix_slice[0] == '*') {
                    marked = true;
                    suffix_slice = suffix_slice[1..];
                }
                suffix_slice = std.mem.trim(u8, suffix_slice, " \t\r");
            }
            try rows.append(arena_allocator, .{
                .cells = cells,
                .marked = marked,
                .annotation = if (suffix_slice.len > 0) try parseAnnotation(arena_allocator, suffix_slice) else null,
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

fn isSegmentDataFence(line: []const u8) bool {
    return line.len >= 3 and line[0] == '@' and line[1] == '@' and line[2] == '@';
}

fn parseAnnotation(allocator: std.mem.Allocator, raw: []const u8) !Annotation {
    const trimmed = std.mem.trim(u8, raw, " \t");
    if (trimmed.len == 0) {
        return error.EmptySegmentAnnotation;
    }

    if (std.ascii.eqlIgnoreCase(trimmed, "NoFall") or std.ascii.eqlIgnoreCase(trimmed, "No Fall")) {
        return .no_fall;
    }

    if (std.mem.indexOfScalar(u8, trimmed, '=')) |equals_index| {
        const key = std.mem.trim(u8, trimmed[0..equals_index], " \t");
        const value = std.mem.trim(u8, trimmed[equals_index + 1 ..], " \t");

        if (parseAnnotationKey(key)) |annotation_key| {
            return switch (annotation_key) {
                .path => .{ .path = try allocator.dupe(u8, value) },
                .ring => .{ .ring = parseRingKind(value) orelse return error.UnsupportedSegmentRingKind },
                .parcel => blk: {
                    const parsed = try parseParcelValue(value);
                    break :blk .{ .parcel = .{
                        .id = parsed.parcel_id,
                        .offset = parsed.offset,
                    } };
                },
                .model => blk: {
                    const parsed = try parseNamedOffsetValue(allocator, value);
                    break :blk .{ .model = .{
                        .name = parsed.name,
                        .offset = parsed.offset,
                    } };
                },
                .jetpack => if (std.ascii.eqlIgnoreCase(value, "Off")) .jetpack_off else error.UnsupportedSegmentJetpackValue,
            };
        }

        return error.UnsupportedSegmentAnnotation;
    }

    return error.UnsupportedSegmentAnnotation;
}

fn parseSingleQuotedValue(allocator: std.mem.Allocator, line: []const u8) ![]const u8 {
    const first_quote = std.mem.indexOfScalar(u8, line, '\'') orelse return error.InvalidQuotedValue;
    const second_quote_relative = std.mem.indexOfScalar(u8, line[first_quote + 1 ..], '\'') orelse return error.InvalidQuotedValue;
    return allocator.dupe(u8, line[first_quote + 1 .. first_quote + 1 + second_quote_relative]);
}

const ParcelValue = struct {
    parcel_id: i32,
    offset: Vec3,
};

const NamedOffsetValue = struct {
    name: []const u8,
    offset: Vec3,
};

fn parseParcelValue(value: []const u8) !ParcelValue {
    const comma_index = std.mem.indexOfScalar(u8, value, ',') orelse return error.InvalidParcelAnnotation;
    const id_text = std.mem.trim(u8, value[0..comma_index], " \t");
    const offset_text = std.mem.trim(u8, value[comma_index + 1 ..], " \t");
    return .{
        .parcel_id = try std.fmt.parseInt(i32, id_text, 10),
        .offset = try parseVec3Value(offset_text),
    };
}

fn parseNamedOffsetValue(allocator: std.mem.Allocator, value: []const u8) !NamedOffsetValue {
    const paren_index = std.mem.indexOfScalar(u8, value, '(') orelse return error.InvalidNamedOffsetAnnotation;
    const name_text = std.mem.trim(u8, value[0..paren_index], " \t");
    const offset_text = std.mem.trim(u8, value[paren_index..], " \t");
    return .{
        .name = try allocator.dupe(u8, name_text),
        .offset = try parseVec3Value(offset_text),
    };
}

fn parseVec3Value(value: []const u8) !Vec3 {
    const trimmed = std.mem.trim(u8, value, " \t()");
    var parts = std.mem.splitScalar(u8, trimmed, ',');
    const x_text = std.mem.trim(u8, parts.next() orelse return error.InvalidVec3Annotation, " \t");
    const y_text = std.mem.trim(u8, parts.next() orelse return error.InvalidVec3Annotation, " \t");
    const z_text = std.mem.trim(u8, parts.next() orelse return error.InvalidVec3Annotation, " \t");
    if (parts.next() != null) return error.InvalidVec3Annotation;

    return .{
        .x = try std.fmt.parseFloat(f32, x_text),
        .y = try std.fmt.parseFloat(f32, y_text),
        .z = try std.fmt.parseFloat(f32, z_text),
    };
}

fn parseRingKind(value: []const u8) ?RingKind {
    if (std.ascii.eqlIgnoreCase(value, "None")) return .none;
    if (std.ascii.eqlIgnoreCase(value, "Normal")) return .normal;
    if (std.ascii.eqlIgnoreCase(value, "PowerUp") or std.ascii.eqlIgnoreCase(value, "Powerup")) return .powerup;
    if (std.ascii.eqlIgnoreCase(value, "Explode") or std.ascii.eqlIgnoreCase(value, "Explosive")) return .explode;
    if (std.ascii.eqlIgnoreCase(value, "Slow")) return .slow;
    return null;
}

fn parseAnnotationKey(key: []const u8) ?AnnotationKey {
    if (std.ascii.eqlIgnoreCase(key, "Path")) return .path;
    if (std.ascii.eqlIgnoreCase(key, "Ring")) return .ring;
    if (std.ascii.eqlIgnoreCase(key, "Parcel")) return .parcel;
    if (std.ascii.eqlIgnoreCase(key, "3DModel")) return .model;
    if (std.ascii.eqlIgnoreCase(key, "JetPack")) return .jetpack;
    return null;
}

test "parse start segment" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/START.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var segment = try parseText(std.testing.allocator, data, "SEGMENTS/START.TXT");
    defer segment.deinit();

    try std.testing.expectEqual(@as(usize, 1), segment.segment_id);
    try std.testing.expectEqualStrings("Start", segment.name);
    try std.testing.expectEqual(@as(usize, 10), segment.width);
    try std.testing.expectEqual(@as(usize, 31), segment.height);
    try std.testing.expectEqualStrings("@PPPPPPPP@", segment.rows[4].cells);
    try std.testing.expectEqual(false, segment.rows[4].marked);
    switch (segment.rows[4].annotation.?) {
        .path => |path_name| try std.testing.expectEqualStrings("Start", path_name),
        else => return error.ExpectedPathAnnotation,
    }
}

test "parse big jump segment annotation" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/BIG JUMP.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var segment = try parseText(std.testing.allocator, data, "SEGMENTS/BIG JUMP.TXT");
    defer segment.deinit();

    try std.testing.expectEqualStrings("@  {}{}  @", segment.rows[8].cells);
    switch (segment.rows[8].annotation.?) {
        .ring => |ring| try std.testing.expectEqual(.explode, ring),
        else => return error.ExpectedRingAnnotation,
    }
}

test "parse parcel, no fall, and row mark semantics" {
    const hump_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/HUMP.TXT", 1 << 16);
    defer std.testing.allocator.free(hump_data);

    var hump = try parseText(std.testing.allocator, hump_data, "SEGMENTS/HUMP.TXT");
    defer hump.deinit();

    const parcel = hump.rows[23].annotation.?;
    switch (parcel) {
        .parcel => |parcel_annotation| {
            try std.testing.expectEqual(@as(i32, 0), parcel_annotation.id);
            try std.testing.expectEqual(@as(f32, 0.0), parcel_annotation.offset.x);
            try std.testing.expectEqual(@as(f32, 0.0), parcel_annotation.offset.y);
            try std.testing.expectEqual(@as(f32, 0.0), parcel_annotation.offset.z);
        },
        else => return error.ExpectedParcelAnnotation,
    }

    const supertramp_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/SUPERTRAMP2.TXT", 1 << 16);
    defer std.testing.allocator.free(supertramp_data);

    var supertramp = try parseText(std.testing.allocator, supertramp_data, "SEGMENTS/SUPERTRAMP2.TXT");
    defer supertramp.deinit();

    try std.testing.expectEqual(Annotation.Tag.no_fall, supertramp.rows[10].annotation.?.tag());

    const gap_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/EASY GAP.TXT", 1 << 16);
    defer std.testing.allocator.free(gap_data);

    var gap = try parseText(std.testing.allocator, gap_data, "SEGMENTS/EASY GAP.TXT");
    defer gap.deinit();

    try std.testing.expect(gap.rows[6].marked);
}

test "normalize explosive and jetpack annotations" {
    const tutorial_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/TUTORIAL 11.TXT", 1 << 16);
    defer std.testing.allocator.free(tutorial_data);

    var tutorial = try parseText(std.testing.allocator, tutorial_data, "SEGMENTS/TUTORIAL 11.TXT");
    defer tutorial.deinit();

    switch (tutorial.rows[27].annotation.?) {
        .ring => |ring| try std.testing.expectEqual(.explode, ring),
        else => return error.ExpectedRingAnnotation,
    }

    const jetpack_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/JETPACKOFF.TXT", 1 << 16);
    defer std.testing.allocator.free(jetpack_data);

    var jetpack = try parseText(std.testing.allocator, jetpack_data, "SEGMENTS/JETPACKOFF.TXT");
    defer jetpack.deinit();

    try std.testing.expectEqual(Annotation.Tag.jetpack_off, jetpack.rows[0].annotation.?.tag());
}

test "parse shipped segment corpus" {
    var dir = try std.fs.cwd().openDir("artifacts/extracted/SnailMail.dat/SEGMENTS", .{ .iterate = true });
    defer dir.close();

    var iterator = dir.iterate();
    var parsed_count: usize = 0;
    while (try iterator.next()) |entry| {
        if (entry.kind != .file) continue;
        if (!std.ascii.endsWithIgnoreCase(entry.name, ".TXT")) continue;

        var path_buffer: [512]u8 = undefined;
        const path = try std.fmt.bufPrint(&path_buffer, "artifacts/extracted/SnailMail.dat/SEGMENTS/{s}", .{entry.name});
        const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, path, 1 << 16);
        defer std.testing.allocator.free(data);

        var parsed = try parseText(std.testing.allocator, data, path);
        defer parsed.deinit();

        try std.testing.expect(parsed.segment_id >= 0);
        try std.testing.expect(parsed.name.len > 0);
        try std.testing.expectEqual(@as(usize, 10), parsed.width);
        parsed_count += 1;
    }

    try std.testing.expectEqual(@as(usize, 133), parsed_count);
}
