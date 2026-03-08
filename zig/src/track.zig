const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const x2 = @import("x2.zig");

const LoadedModelAsset = struct {
    path: []const u8,
    loaded: x2.LoadedModel,

    fn deinit(self: *LoadedModelAsset, allocator: std.mem.Allocator) void {
        self.loaded.deinit();
        allocator.free(self.path);
    }
};

const PlacedModel = struct {
    asset_index: usize,
    segment_index: usize,
    row_index: usize,
    offset: segment.Vec3,
};

pub const LoadedLevelPreview = struct {
    allocator: std.mem.Allocator,
    segments: []segment.Definition,
    row_offsets: []usize,
    model_assets: []LoadedModelAsset,
    placed_models: []PlacedModel,
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

        var model_assets_list: std.ArrayList(LoadedModelAsset) = .empty;
        defer model_assets_list.deinit(allocator);
        errdefer {
            for (model_assets_list.items) |*asset| {
                asset.deinit(allocator);
            }
        }

        var placed_models_list: std.ArrayList(PlacedModel) = .empty;
        defer placed_models_list.deinit(allocator);

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

            for (segments[index].rows, 0..) |row, row_index| {
                const annotation = row.annotation orelse continue;
                if (annotation.kind != .model or annotation.model_name == null) continue;

                const archive_model_path = try resolveSegmentModelArchivePath(allocator, annotation.model_name.?);
                errdefer allocator.free(archive_model_path);

                var asset_index: ?usize = null;
                for (model_assets_list.items, 0..) |asset, existing_index| {
                    if (std.mem.eql(u8, asset.path, archive_model_path)) {
                        asset_index = existing_index;
                        break;
                    }
                }

                if (asset_index == null) {
                    const model_entry = catalog.dat.entryByPath(archive_model_path) orelse {
                        allocator.free(archive_model_path);
                        continue;
                    };

                    const loaded_model = try x2.LoadedModel.loadFromArchive(allocator, catalog, model_entry, true);
                    try model_assets_list.append(allocator, .{
                        .path = archive_model_path,
                        .loaded = loaded_model,
                    });
                    asset_index = model_assets_list.items.len - 1;
                } else {
                    allocator.free(archive_model_path);
                }

                try placed_models_list.append(allocator, .{
                    .asset_index = asset_index.?,
                    .segment_index = index,
                    .row_index = row_index,
                    .offset = annotation.offset orelse .{ .x = 0.0, .y = 0.0, .z = 0.0 },
                });
            }
        }

        return .{
            .allocator = allocator,
            .segments = segments,
            .row_offsets = row_offsets,
            .model_assets = try model_assets_list.toOwnedSlice(allocator),
            .placed_models = try placed_models_list.toOwnedSlice(allocator),
            .total_rows = total_rows,
            .max_width = max_width,
        };
    }

    pub fn deinit(self: *LoadedLevelPreview) void {
        for (self.model_assets) |*asset| {
            asset.deinit(self.allocator);
        }
        self.allocator.free(self.placed_models);
        self.allocator.free(self.model_assets);
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
            drawSegmentGameplayMarkers(loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentCenterline(loaded_segment, width_offset, segment_start_z, cell_size, if (is_selected) .orange else .sky_blue);
            drawSegmentAnnotations(loaded_segment, width_offset, segment_start_z, cell_size, is_selected);
        }

        self.drawPlacedModels(width_offset, cell_size);
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

    fn drawPlacedModels(self: *const LoadedLevelPreview, width_offset: f32, cell_size: f32) void {
        for (self.placed_models) |instance| {
            if (instance.asset_index >= self.model_assets.len) continue;
            if (instance.segment_index >= self.segments.len) continue;

            const loaded_segment = self.segments[instance.segment_index];
            if (instance.row_index >= loaded_segment.rows.len) continue;

            const row = loaded_segment.rows[instance.row_index];
            const segment_start_z = @as(f32, @floatFromInt(self.row_offsets[instance.segment_index])) * cell_size;
            const base = rowAnchorPosition(row, instance.row_index, width_offset, segment_start_z, cell_size, 0.02);
            const position = applyAnnotationOffset(base, instance.offset);
            const asset = &self.model_assets[instance.asset_index].loaded;

            const transform = rl.Matrix.translate(
                position.x - asset.center.x,
                position.y - asset.bounds_min.y,
                position.z - asset.center.z,
            );
            for (asset.submeshes) |submesh| {
                rl.drawMesh(submesh.mesh, submesh.material, transform);
            }
        }
    }
};

fn resolveSegmentModelArchivePath(allocator: std.mem.Allocator, model_name: []const u8) ![]const u8 {
    const stem = if (std.mem.lastIndexOfScalar(u8, model_name, '.')) |dot_index| model_name[0..dot_index] else model_name;
    var upper = try allocator.alloc(u8, stem.len);
    errdefer allocator.free(upper);
    for (stem, 0..) |ch, index| {
        upper[index] = std.ascii.toUpper(ch);
    }

    const archive_path = try std.fmt.allocPrint(allocator, "X/{s}.X2", .{upper});
    allocator.free(upper);
    return archive_path;
}

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
            if (row.marked and cell != '@') {
                rl.drawCubeWiresV(position, size, .gold);
            }
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
        const bounds = guidanceBounds(row) orelse {
            previous = null;
            continue;
        };

        const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
        const point = worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, 0.35);

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
        switch (annotation.kind) {
            .path => drawPathMarkers(row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .ring => drawRingMarkers(row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .parcel => drawParcelMarker(row, row_index, width_offset, segment_start_z, cell_size, annotation, is_selected),
            .model => drawModelMarker(row, row_index, width_offset, segment_start_z, cell_size, annotation, is_selected),
            .velocity => drawVelocityMarker(row, row_index, width_offset, segment_start_z, cell_size, annotation, is_selected),
            .jetpack_off => drawJetpackOffMarker(row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .no_fall => drawNoFallMarker(row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .ring_speed => drawRingSpeedMarker(row, row_index, width_offset, segment_start_z, cell_size, annotation, is_selected),
            .unknown => drawGenericAnnotationMarker(row, row_index, width_offset, segment_start_z, cell_size, is_selected),
        }
    }
}

fn drawSegmentGameplayMarkers(
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    is_selected: bool,
    cell_size: f32,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        for (row.cells, 0..) |cell, col_index| {
            const marker = gameplayMarkerForCell(cell) orelse continue;
            const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, markerY(marker));
            const color = tintForSelection(markerColor(marker), is_selected);

            switch (marker) {
                .parcel => rl.drawCubeV(position, .{ .x = 0.24, .y = 0.24, .z = 0.24 }, color),
                .enemy => rl.drawCubeV(position, .{ .x = 0.26, .y = 0.48, .z = 0.26 }, color),
                .asteroid => rl.drawSphere(position, 0.16, color),
                .salt => {
                    rl.drawSphere(position, 0.14, color);
                    rl.drawLine3D(
                        .{ .x = position.x, .y = position.y - 0.1, .z = position.z },
                        .{ .x = position.x, .y = position.y + 0.14, .z = position.z },
                        color,
                    );
                },
                .health => rl.drawCubeV(position, .{ .x = 0.22, .y = 0.22, .z = 0.22 }, color),
                .turret => rl.drawCubeV(position, .{ .x = 0.24, .y = 0.6, .z = 0.24 }, color),
                .trampoline => rl.drawCubeV(position, .{ .x = 0.28, .y = 0.12, .z = 0.28 }, color),
            }
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

fn drawPathMarkers(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    var found = false;
    var first: ?rl.Vector3 = null;
    var last: ?rl.Vector3 = null;

    for (row.cells, 0..) |cell, col_index| {
        if (!isPathCell(cell)) continue;
        found = true;

        const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, 0.62);
        const color = tintForSelection(if (cell == 'P') .sky_blue else .blue, is_selected);
        rl.drawSphere(position, if (cell == 'P') 0.17 else 0.13, color);
        if (first == null) first = position;
        last = position;
    }

    if (first) |start| {
        if (last) |finish| {
            if (start.x != finish.x or start.z != finish.z) {
                rl.drawLine3D(start, finish, tintForSelection(.gold, is_selected));
            }
        }
        return;
    }

    drawGenericAnnotationMarker(row, row_index, width_offset, segment_start_z, cell_size, is_selected);
}

fn drawRingMarkers(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const annotation = row.annotation orelse return;
    const color = tintForSelection(colorForAnnotation(annotation), is_selected);
    var found = false;

    for (row.cells, 0..) |cell, col_index| {
        if (!isRingCell(cell)) continue;
        found = true;

        const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, 0.85);
        switch (annotation.ring_kind orelse .normal) {
            .none => rl.drawCubeWiresV(position, .{ .x = 0.28, .y = 0.28, .z = 0.28 }, color),
            .normal => rl.drawSphere(position, 0.2, color),
            .powerup => rl.drawCubeV(position, .{ .x = 0.28, .y = 0.28, .z = 0.28 }, color),
            .explode => {
                rl.drawSphere(position, 0.22, color);
                rl.drawSphere(.{ .x = position.x, .y = position.y + 0.05, .z = position.z }, 0.08, .red);
            },
            .slow => rl.drawSphere(position, 0.18, color),
        }
    }

    if (!found) {
        drawGenericAnnotationMarker(row, row_index, width_offset, segment_start_z, cell_size, is_selected);
    }
}

fn drawParcelMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    annotation: segment.Annotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(row, row_index, width_offset, segment_start_z, cell_size, 0.6);
    const offset = annotation.offset orelse segment.Vec3{ .x = 0.0, .y = 0.0, .z = 0.0 };
    const position = applyAnnotationOffset(base, offset);
    const color = tintForSelection(if (annotation.parcel_id == 0) .gold else .green, is_selected);

    rl.drawLine3D(base, position, tintForSelection(.dark_green, is_selected));
    rl.drawCubeV(position, .{ .x = 0.32, .y = 0.32, .z = 0.32 }, color);
}

fn drawModelMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    annotation: segment.Annotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(row, row_index, width_offset, segment_start_z, cell_size, 0.5);
    const offset = annotation.offset orelse segment.Vec3{ .x = 0.0, .y = 0.0, .z = 0.0 };
    const position = applyAnnotationOffset(base, offset);
    const color = tintForSelection(.purple, is_selected);

    rl.drawLine3D(base, position, tintForSelection(.light_gray, is_selected));
    rl.drawCubeV(position, .{ .x = 0.36, .y = 0.72, .z = 0.36 }, color);
    rl.drawCubeWiresV(position, .{ .x = 0.36, .y = 0.72, .z = 0.36 }, .ray_white);
}

fn drawVelocityMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    annotation: segment.Annotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(row, row_index, width_offset, segment_start_z, cell_size, 0.8);
    const velocity = annotation.velocity orelse return;
    const tip = rl.Vector3{
        .x = base.x + velocity.x,
        .y = base.y + velocity.y,
        .z = base.z + velocity.z,
    };

    const color = tintForSelection(.lime, is_selected);
    rl.drawLine3D(base, tip, color);
    rl.drawSphere(tip, 0.12, color);
}

fn drawJetpackOffMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const bounds = guidanceBounds(row) orelse return;
    drawRowStrip(bounds, row_index, width_offset, segment_start_z, cell_size, 0.22, tintForSelection(.red, is_selected));
}

fn drawNoFallMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const bounds = guidanceBounds(row) orelse return;
    const left = worldPositionForColumn(@as(f32, @floatFromInt(bounds.min)) + 0.5, row_index, width_offset, segment_start_z, cell_size, 0.95);
    const right = worldPositionForColumn(@as(f32, @floatFromInt(bounds.max)) + 0.5, row_index, width_offset, segment_start_z, cell_size, 0.95);
    const color = tintForSelection(.sky_blue, is_selected);
    rl.drawLine3D(left, right, color);
    rl.drawSphere(left, 0.08, color);
    rl.drawSphere(right, 0.08, color);
}

fn drawRingSpeedMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    annotation: segment.Annotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(row, row_index, width_offset, segment_start_z, cell_size, 0.7);
    const speed = annotation.ring_speed orelse 0.0;
    const height = @max(@abs(speed) * 0.15, 0.15);
    const top = rl.Vector3{ .x = base.x, .y = base.y + height, .z = base.z };
    const color = tintForSelection(.yellow, is_selected);
    rl.drawLine3D(base, top, color);
    rl.drawSphere(top, 0.08, color);
}

fn drawGenericAnnotationMarker(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const position = rowAnchorPosition(row, row_index, width_offset, segment_start_z, cell_size, 0.75);
    rl.drawCubeV(position, .{ .x = 0.18, .y = 0.18, .z = 0.18 }, tintForSelection(.white, is_selected));
}

fn drawRowStrip(
    bounds: TraversableBounds,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
    color: rl.Color,
) void {
    const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
    const width = @as(f32, @floatFromInt(bounds.max - bounds.min + 1)) * cell_size;
    const position = worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, y);
    rl.drawCubeV(position, .{ .x = width, .y = 0.08, .z = 0.2 }, color);
}

fn rowAnchorPosition(
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    const bounds = guidanceBounds(row) orelse blk: {
        const max_index = if (row.cells.len == 0) @as(usize, 0) else row.cells.len - 1;
        break :blk TraversableBounds{ .min = 0, .max = max_index };
    };
    const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
    return worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, y);
}

fn cellWorldPosition(
    col_index: usize,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    return worldPositionForColumn(@as(f32, @floatFromInt(col_index)) + 0.5, row_index, width_offset, segment_start_z, cell_size, y);
}

fn worldPositionForColumn(
    column: f32,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    return .{
        .x = (column - width_offset) * cell_size,
        .y = y,
        .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
    };
}

fn applyAnnotationOffset(base: rl.Vector3, offset: segment.Vec3) rl.Vector3 {
    return .{
        .x = base.x + offset.x,
        .y = base.y + offset.y,
        .z = base.z + offset.z,
    };
}

const TraversableBounds = struct {
    min: usize,
    max: usize,
};

fn guidanceBounds(row: segment.Row) ?TraversableBounds {
    return pathBounds(row.cells) orelse traversableBounds(row.cells);
}

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

fn pathBounds(cells: []const u8) ?TraversableBounds {
    var min_index: ?usize = null;
    var max_index: usize = 0;
    for (cells, 0..) |cell, index| {
        if (!isPathCell(cell)) continue;
        if (min_index == null) min_index = index;
        max_index = index;
    }

    if (min_index == null) return null;
    return .{ .min = min_index.?, .max = max_index };
}

fn isTraversable(cell: u8) bool {
    return cell != '@';
}

fn isPathCell(cell: u8) bool {
    return cell == 'P' or cell == 'p';
}

fn isRingCell(cell: u8) bool {
    return switch (cell) {
        '>', '<', '{', '}', ';', 'R' => true,
        else => false,
    };
}

const GameplayMarker = enum {
    parcel,
    enemy,
    asteroid,
    salt,
    health,
    turret,
    trampoline,
};

fn gameplayMarkerForCell(cell: u8) ?GameplayMarker {
    return switch (cell) {
        '0', '1', '2', '3' => .parcel,
        'M', '[', 'J' => .enemy,
        's' => .asteroid,
        '&' => .salt,
        '$' => .health,
        '=' => .turret,
        '(', ')' => .trampoline,
        else => null,
    };
}

fn markerColor(marker: GameplayMarker) rl.Color {
    return switch (marker) {
        .parcel => .gold,
        .enemy => .red,
        .asteroid => .gray,
        .salt => .sky_blue,
        .health => .green,
        .turret => .purple,
        .trampoline => .orange,
    };
}

fn markerY(marker: GameplayMarker) f32 {
    return switch (marker) {
        .parcel => 0.72,
        .enemy => 0.62,
        .asteroid => 0.56,
        .salt => 0.62,
        .health => 0.7,
        .turret => 0.78,
        .trampoline => 0.12,
    };
}

fn colorForAnnotation(annotation: segment.Annotation) rl.Color {
    return switch (annotation.kind) {
        .path => .gold,
        .ring => switch (annotation.ring_kind orelse .normal) {
            .none => .gray,
            .normal => .yellow,
            .powerup => .green,
            .explode => .orange,
            .slow => .purple,
        },
        .ring_speed => .yellow,
        .parcel => .green,
        .model => .purple,
        .velocity => .lime,
        .jetpack_off => .red,
        .no_fall => .sky_blue,
        .unknown => .white,
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

test "resolve segment x model path" {
    const resolved = try resolveSegmentModelArchivePath(std.testing.allocator, "signBang.x");
    defer std.testing.allocator.free(resolved);

    try std.testing.expectEqualStrings("X/SIGNBANG.X2", resolved);
}
