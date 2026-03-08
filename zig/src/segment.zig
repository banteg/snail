const std = @import("std");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

pub const Vec3 = struct {
    x: f32,
    y: f32,
    z: f32,
};

pub const AnnotationKind = enum {
    unknown,
    path,
    ring,
    ring_speed,
    parcel,
    model,
    velocity,
    jetpack_off,
    no_fall,
};

pub const RingKind = enum {
    none,
    normal,
    powerup,
    explode,
    slow,
};

pub const Annotation = struct {
    raw: []const u8,
    key: []const u8,
    value: ?[]const u8 = null,
    kind: AnnotationKind = .unknown,
    ring_kind: ?RingKind = null,
    ring_speed: ?f32 = null,
    path_name: ?[]const u8 = null,
    parcel_id: ?i32 = null,
    model_name: ?[]const u8 = null,
    offset: ?Vec3 = null,
    velocity: ?Vec3 = null,
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
    var width: usize = 0;

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |raw_line| {
        if (in_data) {
            const line = std.mem.trimRight(u8, raw_line, "\r");
            if (line.len == 0) continue;

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

fn parseAnnotation(allocator: std.mem.Allocator, raw: []const u8) !Annotation {
    const trimmed = std.mem.trim(u8, raw, " \t");

    if (std.ascii.eqlIgnoreCase(trimmed, "NoFall") or std.ascii.eqlIgnoreCase(trimmed, "No Fall")) {
        return .{
            .raw = try allocator.dupe(u8, trimmed),
            .key = try allocator.dupe(u8, "NoFall"),
            .value = null,
            .kind = .no_fall,
        };
    }

    if (std.mem.indexOfScalar(u8, trimmed, '=')) |equals_index| {
        const key = std.mem.trim(u8, trimmed[0..equals_index], " \t");
        const value = std.mem.trim(u8, trimmed[equals_index + 1 ..], " \t");

        var annotation = Annotation{
            .raw = try allocator.dupe(u8, trimmed),
            .key = try allocator.dupe(u8, key),
            .value = try allocator.dupe(u8, value),
        };

        if (std.ascii.eqlIgnoreCase(key, "Path")) {
            annotation.kind = .path;
            annotation.path_name = annotation.value.?;
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "Ring")) {
            annotation.kind = .ring;
            annotation.ring_kind = parseRingKind(value);
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "RingSpeed")) {
            annotation.kind = .ring_speed;
            annotation.ring_speed = try std.fmt.parseFloat(f32, value);
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "Parcel")) {
            annotation.kind = .parcel;
            const parsed = try parseParcelValue(value);
            annotation.parcel_id = parsed.parcel_id;
            annotation.offset = parsed.offset;
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "3DModel")) {
            annotation.kind = .model;
            const parsed = try parseNamedOffsetValue(allocator, value);
            annotation.model_name = parsed.name;
            annotation.offset = parsed.offset;
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "Velocity")) {
            annotation.kind = .velocity;
            annotation.velocity = try parseVec3Value(value);
            return annotation;
        }
        if (std.ascii.eqlIgnoreCase(key, "JetPack") and std.ascii.eqlIgnoreCase(value, "Off")) {
            annotation.kind = .jetpack_off;
            return annotation;
        }

        return annotation;
    }

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
    try std.testing.expectEqual(false, segment.rows[5].marked);
    try std.testing.expectEqualStrings("Path", segment.rows[5].annotation.?.key);
    try std.testing.expectEqualStrings("Start", segment.rows[5].annotation.?.value.?);
    try std.testing.expectEqual(.path, segment.rows[5].annotation.?.kind);
    try std.testing.expectEqualStrings("Start", segment.rows[5].annotation.?.path_name.?);
}

test "parse big jump segment annotation" {
    const data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/BIG JUMP.TXT", 1 << 16);
    defer std.testing.allocator.free(data);

    var segment = try parseText(std.testing.allocator, data, "SEGMENTS/BIG JUMP.TXT");
    defer segment.deinit();

    try std.testing.expectEqualStrings("@  {}{}  @", segment.rows[9].cells);
    try std.testing.expectEqualStrings("Ring", segment.rows[9].annotation.?.key);
    try std.testing.expectEqualStrings("Explode", segment.rows[9].annotation.?.value.?);
    try std.testing.expectEqual(.ring, segment.rows[9].annotation.?.kind);
    try std.testing.expectEqual(.explode, segment.rows[9].annotation.?.ring_kind.?);
}

test "parse parcel, no fall, and row mark semantics" {
    const hump_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/HUMP.TXT", 1 << 16);
    defer std.testing.allocator.free(hump_data);

    var hump = try parseText(std.testing.allocator, hump_data, "SEGMENTS/HUMP.TXT");
    defer hump.deinit();

    const parcel = hump.rows[25].annotation.?;
    try std.testing.expectEqual(.parcel, parcel.kind);
    try std.testing.expectEqual(@as(i32, 0), parcel.parcel_id.?);
    try std.testing.expectEqual(@as(f32, 0.0), parcel.offset.?.x);
    try std.testing.expectEqual(@as(f32, 0.0), parcel.offset.?.y);
    try std.testing.expectEqual(@as(f32, 0.0), parcel.offset.?.z);

    const supertramp_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/SUPERTRAMP2.TXT", 1 << 16);
    defer std.testing.allocator.free(supertramp_data);

    var supertramp = try parseText(std.testing.allocator, supertramp_data, "SEGMENTS/SUPERTRAMP2.TXT");
    defer supertramp.deinit();

    try std.testing.expectEqual(.no_fall, supertramp.rows[11].annotation.?.kind);

    const gap_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/EASY GAP.TXT", 1 << 16);
    defer std.testing.allocator.free(gap_data);

    var gap = try parseText(std.testing.allocator, gap_data, "SEGMENTS/EASY GAP.TXT");
    defer gap.deinit();

    try std.testing.expect(gap.rows[7].marked);
}

test "normalize explosive and jetpack annotations" {
    const tutorial_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/TUTORIAL 11.TXT", 1 << 16);
    defer std.testing.allocator.free(tutorial_data);

    var tutorial = try parseText(std.testing.allocator, tutorial_data, "SEGMENTS/TUTORIAL 11.TXT");
    defer tutorial.deinit();

    try std.testing.expectEqual(.explode, tutorial.rows[28].annotation.?.ring_kind.?);

    const jetpack_data = try std.fs.cwd().readFileAlloc(std.testing.allocator, "artifacts/extracted/SnailMail.dat/SEGMENTS/JETPACKOFF.TXT", 1 << 16);
    defer std.testing.allocator.free(jetpack_data);

    var jetpack = try parseText(std.testing.allocator, jetpack_data, "SEGMENTS/JETPACKOFF.TXT");
    defer jetpack.deinit();

    try std.testing.expectEqual(.jetpack_off, jetpack.rows[1].annotation.?.kind);
}
