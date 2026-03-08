const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");

pub const LoadedLevelPreview = struct {
    allocator: std.mem.Allocator,
    segments: []segment.Definition,
    row_offsets: []usize,
    total_rows: usize,
    max_width: usize,

    pub fn load(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        level_definition: *const level.Definition,
    ) !LoadedLevelPreview {
        const segment_count = level_definition.segments.len;
        const segments = try allocator.alloc(segment.Definition, segment_count);
        errdefer allocator.free(segments);

        const row_offsets = try allocator.alloc(usize, segment_count);
        errdefer allocator.free(row_offsets);

        var loaded_count: usize = 0;
        errdefer {
            for (segments[0..loaded_count]) |*loaded_segment| {
                loaded_segment.deinit();
            }
        }

        var total_rows: usize = 0;
        var max_width: usize = 0;
        for (level_definition.segments, 0..) |segment_entry, index| {
            row_offsets[index] = total_rows;

            var path_buffer: [512]u8 = undefined;
            const archive_path = try std.fmt.bufPrint(&path_buffer, "SEGMENTS/{s}", .{segment_entry.path});
            const entry = catalog.dat.entryByPath(archive_path) orelse return error.SegmentEntryMissing;
            segments[index] = try segment.loadFromArchive(allocator, catalog, entry);
            loaded_count = index + 1;

            total_rows += segments[index].height;
            max_width = @max(max_width, segments[index].width);
        }

        return .{
            .allocator = allocator,
            .segments = segments,
            .row_offsets = row_offsets,
            .total_rows = total_rows,
            .max_width = max_width,
        };
    }

    pub fn deinit(self: *LoadedLevelPreview) void {
        for (self.segments) |*loaded_segment| {
            loaded_segment.deinit();
        }
        self.allocator.free(self.row_offsets);
        self.allocator.free(self.segments);
    }

    pub fn previewCamera(self: *const LoadedLevelPreview, time_seconds: f32, selected_segment_index: usize) rl.Camera3D {
        const target = self.segmentCenter(selected_segment_index);
        const distance = @max(@as(f32, @floatFromInt(self.total_rows)) * 0.45, 18.0);
        return .{
            .position = .{
                .x = target.x + std.math.cos(time_seconds * 0.18) * distance,
                .y = target.y + distance * 0.6,
                .z = target.z + std.math.sin(time_seconds * 0.18) * distance,
            },
            .target = target,
            .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .fovy = 45.0,
            .projection = .perspective,
        };
    }

    pub fn draw(self: *const LoadedLevelPreview, selected_segment_index: usize) void {
        const cell_size: f32 = 1.0;
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;

        for (self.segments, 0..) |loaded_segment, segment_index| {
            const is_selected = segment_index == selected_segment_index;
            const segment_start_z = @as(f32, @floatFromInt(self.row_offsets[segment_index])) * cell_size;

            drawSegmentBoundary(width_offset, segment_start_z, loaded_segment.height, is_selected);
            drawSegmentCells(loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentCenterline(loaded_segment, width_offset, segment_start_z, cell_size, if (is_selected) .orange else .sky_blue);
            drawSegmentAnnotations(loaded_segment, width_offset, segment_start_z, cell_size, is_selected);
        }
    }

    pub fn activeSegment(self: *const LoadedLevelPreview, selected_segment_index: usize) ?*const segment.Definition {
        if (selected_segment_index >= self.segments.len) return null;
        return &self.segments[selected_segment_index];
    }

    fn segmentCenter(self: *const LoadedLevelPreview, selected_segment_index: usize) rl.Vector3 {
        const safe_index = @min(selected_segment_index, self.segments.len - 1);
        const loaded_segment = self.segments[safe_index];
        const start_z = @as(f32, @floatFromInt(self.row_offsets[safe_index]));
        return .{
            .x = 0.0,
            .y = 0.0,
            .z = start_z + @as(f32, @floatFromInt(loaded_segment.height)) * 0.5,
        };
    }
};

fn drawSegmentCells(
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    is_selected: bool,
    cell_size: f32,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        for (row.cells, 0..) |cell, col_index| {
            const position = rl.Vector3{
                .x = (@as(f32, @floatFromInt(col_index)) - width_offset + 0.5) * cell_size,
                .y = if (cell == '@') 0.35 else -0.05,
                .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
            };
            const size = rl.Vector3{
                .x = cell_size,
                .y = if (cell == '@') 0.7 else 0.1,
                .z = cell_size,
            };

            const color = tintForSelection(colorForCell(cell), is_selected);
            rl.drawCubeV(position, size, color);
        }
    }
}

fn drawSegmentCenterline(
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    color: rl.Color,
) void {
    var previous: ?rl.Vector3 = null;

    for (loaded_segment.rows, 0..) |row, row_index| {
        const bounds = traversableBounds(row.cells) orelse {
            previous = null;
            continue;
        };

        const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
        const point = rl.Vector3{
            .x = (center_col - width_offset) * cell_size,
            .y = 0.35,
            .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
        };

        rl.drawSphere(point, 0.08, color);
        if (previous) |prev| {
            rl.drawLine3D(prev, point, color);
        }
        previous = point;
    }
}

fn drawSegmentAnnotations(
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        const annotation = row.annotation orelse continue;
        const bounds = traversableBounds(row.cells) orelse continue;

        const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
        const position = rl.Vector3{
            .x = (center_col - width_offset) * cell_size,
            .y = 0.75,
            .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
        };

        const color = tintForSelection(colorForAnnotation(annotation.key), is_selected);
        switch (annotationKind(annotation.key)) {
            .ring => rl.drawSphere(position, 0.22, color),
            .parcel => rl.drawCubeV(position, .{ .x = 0.32, .y = 0.32, .z = 0.32 }, color),
            .jetpack => rl.drawSphere(position, 0.18, color),
            .model => rl.drawCubeV(position, .{ .x = 0.28, .y = 0.5, .z = 0.28 }, color),
            .path => rl.drawSphere(position, 0.12, color),
            .flag => rl.drawCubeV(position, .{ .x = 0.18, .y = 0.18, .z = 0.18 }, color),
        }
    }
}

fn drawSegmentBoundary(width_offset: f32, segment_start_z: f32, height: usize, is_selected: bool) void {
    const left = rl.Vector3{ .x = -width_offset, .y = 0.02, .z = segment_start_z };
    const right = rl.Vector3{ .x = width_offset, .y = 0.02, .z = segment_start_z };
    rl.drawLine3D(left, right, if (is_selected) .orange else .dark_gray);

    const end_z = segment_start_z + @as(f32, @floatFromInt(height));
    rl.drawLine3D(
        .{ .x = -width_offset, .y = 0.02, .z = end_z },
        .{ .x = width_offset, .y = 0.02, .z = end_z },
        if (is_selected) .orange else .dark_gray,
    );
}

const TraversableBounds = struct {
    min: usize,
    max: usize,
};

fn traversableBounds(cells: []const u8) ?TraversableBounds {
    var min_index: ?usize = null;
    var max_index: usize = 0;
    for (cells, 0..) |cell, index| {
        if (!isTraversable(cell)) continue;
        if (min_index == null) min_index = index;
        max_index = index;
    }

    if (min_index == null) return null;
    return .{ .min = min_index.?, .max = max_index };
}

fn isTraversable(cell: u8) bool {
    return cell != '@';
}

const AnnotationKind = enum {
    ring,
    parcel,
    jetpack,
    model,
    path,
    flag,
};

fn annotationKind(key: []const u8) AnnotationKind {
    if (std.ascii.eqlIgnoreCase(key, "Ring")) return .ring;
    if (std.ascii.eqlIgnoreCase(key, "Parcel")) return .parcel;
    if (std.ascii.eqlIgnoreCase(key, "JetPack")) return .jetpack;
    if (std.ascii.eqlIgnoreCase(key, "3DModel")) return .model;
    if (std.ascii.eqlIgnoreCase(key, "Path")) return .path;
    return .flag;
}

fn colorForAnnotation(key: []const u8) rl.Color {
    return switch (annotationKind(key)) {
        .ring => .yellow,
        .parcel => .green,
        .jetpack => .sky_blue,
        .model => .purple,
        .path => .gold,
        .flag => .white,
    };
}

fn colorForCell(cell: u8) rl.Color {
    return switch (cell) {
        '@' => .dark_blue,
        '_' => .gray,
        '.' => .light_gray,
        'P' => .sky_blue,
        '#' => .orange,
        's' => .white,
        '>' => .gold,
        '{', '}', ';' => .yellow,
        '[', 'M', 'R', 'J' => .red,
        '~' => .green,
        '$', '&', '(', ')', '-', '<', '=', '0', '1', '2', '3', '|', 'p' => .purple,
        ' ' => .dark_gray,
        else => .dark_purple,
    };
}

fn tintForSelection(base: rl.Color, is_selected: bool) rl.Color {
    if (!is_selected) return base;
    return .{
        .r = @intCast(@min(@as(u16, base.r) + 30, 255)),
        .g = @intCast(@min(@as(u16, base.g) + 20, 255)),
        .b = @intCast(@min(@as(u16, base.b) + 10, 255)),
        .a = base.a,
    };
}

test "load tutorial level preview" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    try std.testing.expectEqual(@as(usize, level_definition.segments.len), preview.segments.len);
    try std.testing.expectEqualStrings("Start", preview.segments[0].name);
    try std.testing.expect(preview.total_rows > 0);
}
