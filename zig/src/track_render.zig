const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const assets = @import("assets.zig");
const track = @import("track.zig");

const track_texture_path_fmt = "OBJECTS/WORLD00/TRACK{d}.TGA";
const slide_texture_path_fmt = "OBJECTS/WORLD00/SLIDE{d}.TGA";
const warn_texture_path = "OBJECTS/WORLD00/TRACKWARN.TGA";
const back_texture_path = "OBJECTS/WORLD00/BACK.TGA";
const ramp_texture_path = "OBJECTS/UNIVERSE/RAMP.TGA";
const fringe_texture_path = "OBJECTS/UNIVERSE/FRINGE.TGA";

const skirt_depth: f32 = 0.65;
const back_plane_margin: f32 = 4.0;
const back_plane_y: f32 = -0.66;

pub const Scene = struct {
    allocator: std.mem.Allocator,
    track_set_index: u8,
    textures: Textures,

    pub fn buildStandaloneSegmentScene(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        track_set_index: u8,
    ) !Scene {
        const resolved_track_set = try resolveTrackSetIndex(track_set_index);
        var textures = try Textures.load(allocator, catalog, resolved_track_set);
        errdefer textures.unload();

        return .{
            .allocator = allocator,
            .track_set_index = resolved_track_set,
            .textures = textures,
        };
    }

    pub fn deinit(self: *Scene) void {
        self.textures.unload();
    }

    pub fn draw(self: *const Scene, preview: *const track.LoadedLevelPreview, selected_segment_index: usize) void {
        drawBackPlane(self, preview);
        drawRuntimeCells(self, preview);
        preview.drawPlacedModelsOnly();
        drawSegmentSelectionOutline(preview, selected_segment_index);
    }
};

const Textures = struct {
    track: assets.LoadedTexture,
    slide: assets.LoadedTexture,
    warn: assets.LoadedTexture,
    ramp: assets.LoadedTexture,
    fringe: assets.LoadedTexture,
    back: assets.LoadedTexture,

    fn load(allocator: std.mem.Allocator, catalog: *const assets.Catalog, track_set_index: u8) !Textures {
        var track_path_buffer: [64]u8 = undefined;
        var slide_path_buffer: [64]u8 = undefined;

        var textures = Textures{
            .track = try catalog.loadTextureByPath(allocator, try std.fmt.bufPrint(&track_path_buffer, track_texture_path_fmt, .{track_set_index})),
            .slide = try catalog.loadTextureByPath(allocator, try std.fmt.bufPrint(&slide_path_buffer, slide_texture_path_fmt, .{track_set_index})),
            .warn = try catalog.loadTextureByPath(allocator, warn_texture_path),
            .ramp = try catalog.loadTextureByPath(allocator, ramp_texture_path),
            .fringe = try catalog.loadTextureByPath(allocator, fringe_texture_path),
            .back = try catalog.loadTextureByPath(allocator, back_texture_path),
        };
        setSceneTextureWrap(&textures);
        return textures;
    }

    fn unload(self: *Textures) void {
        self.track.unload();
        self.slide.unload();
        self.warn.unload();
        self.ramp.unload();
        self.fringe.unload();
        self.back.unload();
    }
};

const SurfaceFamily = enum {
    floor,
    slide,
    warn,
    ramp,
};

const QuadUv = struct {
    left: f32,
    right: f32,
    top: f32,
    bottom: f32,
};

const LaneBounds = struct {
    min: usize,
    max: usize,
};

const gameplay_half_width: f32 = 4.0;
const gameplay_uv_scale: f32 = 0.125;
const render_cache_row_chunk: f32 = 24.0;

fn resolveTrackSetIndex(track_set_index: u8) !u8 {
    return switch (track_set_index) {
        0, 1, 2, 3 => track_set_index,
        else => error.UnsupportedTrackSetIndex,
    };
}

fn setSceneTextureWrap(textures: *Textures) void {
    rl.setTextureWrap(textures.track.texture, .repeat);
    rl.setTextureWrap(textures.slide.texture, .repeat);
    rl.setTextureWrap(textures.warn.texture, .repeat);
    rl.setTextureWrap(textures.ramp.texture, .repeat);
    rl.setTextureWrap(textures.fringe.texture, .repeat);
    rl.setTextureWrap(textures.back.texture, .repeat);
}

fn drawBackPlane(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;
    const left = -width_offset - back_plane_margin;
    const right = width_offset + back_plane_margin;
    const front = -back_plane_margin;
    const back = @as(f32, @floatFromInt(preview.total_rows)) + back_plane_margin;

    drawTexturedQuad(
        scene.textures.back.texture,
        .{ .x = left, .y = back_plane_y, .z = front },
        .{ .x = left, .y = back_plane_y, .z = back },
        .{ .x = right, .y = back_plane_y, .z = back },
        .{ .x = right, .y = back_plane_y, .z = front },
        .{ .left = 0.0, .right = 1.0, .top = 0.0, .bottom = 1.0 },
    );
}

fn drawRuntimeCells(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
    if (preview.max_width == 0) return;
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;

    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const lane_bounds = renderLaneBounds(row_location.row.cells) orelse continue;
        const max_lane_index = @min(lane_bounds.max, preview.max_width - 1);
        if (lane_bounds.min > max_lane_index) continue;

        var lane_index = lane_bounds.min;
        while (lane_index <= max_lane_index) : (lane_index += 1) {
            const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
            const family = surfaceFamilyForTile(tile_type) orelse continue;
            const run_length = mergedSurfaceRunLength(preview, global_row, lane_index, max_lane_index, family);

            const left = @as(f32, @floatFromInt(lane_index)) - width_offset;
            const right = left + @as(f32, @floatFromInt(run_length));
            const front = @as(f32, @floatFromInt(global_row));
            const back = front + 1.0;
            const front_height = surfaceHeightAtTileFraction(tile_type, front, 0.0);
            const back_height = surfaceHeightAtTileFraction(tile_type, front, 0.999);

            drawTexturedQuad(
                textureForFamily(scene, family),
                .{ .x = left, .y = front_height, .z = front },
                .{ .x = left, .y = back_height, .z = back },
                .{ .x = right, .y = back_height, .z = back },
                .{ .x = right, .y = front_height, .z = front },
                topSurfaceUv(family, left, right, front, back),
            );

            for (lane_index..lane_index + run_length) |edge_lane_index| {
                const edge_left = @as(f32, @floatFromInt(edge_lane_index)) - width_offset;
                const edge_right = edge_left + 1.0;
                const edge_mask = preview.runtimeEdgeMaskAt(global_row, edge_lane_index) orelse 0;
                if (edge_mask != 0) {
                    drawFringeSides(scene, edge_left, edge_right, front, back, front_height, back_height, edge_mask);
                }
            }

            lane_index += run_length - 1;
        }
    }
}

fn drawFringeSides(
    scene: *const Scene,
    left: f32,
    right: f32,
    front: f32,
    back: f32,
    front_height: f32,
    back_height: f32,
    edge_mask: u8,
) void {
    const bottom_front = @min(front_height, back_height) - skirt_depth;
    const bottom_back = bottom_front;

    if ((edge_mask & 0x08) != 0) {
        drawTexturedQuad(
            scene.textures.fringe.texture,
            .{ .x = left, .y = bottom_front, .z = front },
            .{ .x = left, .y = bottom_back, .z = back },
            .{ .x = left, .y = back_height, .z = back },
            .{ .x = left, .y = front_height, .z = front },
            .{ .left = 0.0, .right = 1.0, .top = 1.0, .bottom = 0.0 },
        );
    }
    if ((edge_mask & 0x04) != 0) {
        drawTexturedQuad(
            scene.textures.fringe.texture,
            .{ .x = right, .y = front_height, .z = front },
            .{ .x = right, .y = back_height, .z = back },
            .{ .x = right, .y = bottom_back, .z = back },
            .{ .x = right, .y = bottom_front, .z = front },
            .{ .left = 0.0, .right = 1.0, .top = 0.0, .bottom = 1.0 },
        );
    }
    if ((edge_mask & 0x01) != 0) {
        drawTexturedQuad(
            scene.textures.fringe.texture,
            .{ .x = left, .y = bottom_front, .z = front },
            .{ .x = right, .y = bottom_front, .z = front },
            .{ .x = right, .y = front_height, .z = front },
            .{ .x = left, .y = front_height, .z = front },
            .{ .left = 0.0, .right = 1.0, .top = 1.0, .bottom = 0.0 },
        );
    }
    if ((edge_mask & 0x02) != 0) {
        drawTexturedQuad(
            scene.textures.fringe.texture,
            .{ .x = left, .y = back_height, .z = back },
            .{ .x = right, .y = back_height, .z = back },
            .{ .x = right, .y = bottom_back, .z = back },
            .{ .x = left, .y = bottom_back, .z = back },
            .{ .left = 0.0, .right = 1.0, .top = 0.0, .bottom = 1.0 },
        );
    }
}

fn drawSegmentSelectionOutline(preview: *const track.LoadedLevelPreview, selected_segment_index: usize) void {
    if (preview.segments.len == 0) return;
    const safe_index = @min(selected_segment_index, preview.segments.len - 1);
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;
    const left = -width_offset;
    const right = width_offset;
    const front = @as(f32, @floatFromInt(preview.row_offsets[safe_index]));
    const back = front + @as(f32, @floatFromInt(preview.segments[safe_index].height));
    const y = 0.02;

    rl.drawLine3D(.{ .x = left, .y = y, .z = front }, .{ .x = right, .y = y, .z = front }, .orange);
    rl.drawLine3D(.{ .x = right, .y = y, .z = front }, .{ .x = right, .y = y, .z = back }, .orange);
    rl.drawLine3D(.{ .x = right, .y = y, .z = back }, .{ .x = left, .y = y, .z = back }, .orange);
    rl.drawLine3D(.{ .x = left, .y = y, .z = back }, .{ .x = left, .y = y, .z = front }, .orange);
}

fn textureForFamily(scene: *const Scene, family: SurfaceFamily) rl.Texture2D {
    return switch (family) {
        .floor => scene.textures.track.texture,
        .slide => scene.textures.slide.texture,
        .warn => scene.textures.warn.texture,
        .ramp => scene.textures.ramp.texture,
    };
}

fn surfaceFamilyForTile(tile_type: u8) ?SurfaceFamily {
    if (track.isFloorCacheRuntimeTileFamily(tile_type)) return .floor;
    if (track.isSlideRuntimeTileFamily(tile_type)) return .slide;
    if (track.isRampRuntimeTileFamily(tile_type)) return .ramp;
    return switch (tile_type) {
        0x20 => .warn,
        else => null,
    };
}

fn surfaceHeightAtTileFraction(tile_type: u8, row_origin: f32, row_fraction: f32) f32 {
    return track.sampleFloorHeightForRuntimeTile(
        tile_type,
        row_origin + row_fraction,
        track.specialFloorHeightForShippedRuntimeTile(tile_type),
    ) orelse 0.0;
}

fn renderLaneBounds(cells: []const u8) ?LaneBounds {
    var min_index: ?usize = null;
    var max_index: usize = 0;
    for (cells, 0..) |cell, index| {
        if (cell == '@') continue;
        if (min_index == null) min_index = index;
        max_index = index;
    }

    if (min_index == null) return null;
    return .{ .min = min_index.?, .max = max_index };
}

fn mergedSurfaceRunLength(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
    max_lane_index: usize,
    family: SurfaceFamily,
) usize {
    if (family == .ramp or family == .warn) return 1;

    var run_length: usize = 1;
    var scan_lane = lane_index + 1;
    while (scan_lane <= max_lane_index) : (scan_lane += 1) {
        const next_tile_type = preview.runtimeTileAt(global_row, scan_lane) orelse break;
        const extend = switch (family) {
            .floor => track.isFloorCacheRuntimeTileFamily(next_tile_type),
            .slide => isSlideRunMergeTile(next_tile_type),
            .warn, .ramp => false,
        };
        if (!extend) break;
        run_length += 1;
    }
    return run_length;
}

fn isSlideRunMergeTile(tile_type: u8) bool {
    return switch (tile_type) {
        0x01, 0x15, 0x1b, 0x21, 0x22 => true,
        else => false,
    };
}

fn topSurfaceUv(family: SurfaceFamily, left: f32, right: f32, front: f32, back: f32) QuadUv {
    if (family == .ramp) {
        return .{ .left = 0.0, .right = 1.0, .top = 0.0, .bottom = 1.0 };
    }
    const z_block_base = @floor(front / render_cache_row_chunk) * render_cache_row_chunk;
    return .{
        .left = (left + gameplay_half_width) * gameplay_uv_scale,
        .right = (right + gameplay_half_width) * gameplay_uv_scale,
        .top = 1.0 - ((front - z_block_base) * gameplay_uv_scale),
        .bottom = 1.0 - ((back - z_block_base) * gameplay_uv_scale),
    };
}

fn drawTexturedQuad(
    texture: rl.Texture2D,
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: QuadUv,
) void {
    rlgl.rlSetTexture(texture.id);
    defer rlgl.rlSetTexture(0);

    rlgl.rlBegin(rlgl.rl_quads);
    defer rlgl.rlEnd();
    rlgl.rlColor4ub(255, 255, 255, 255);

    rlgl.rlTexCoord2f(uv.left, uv.top);
    rlgl.rlVertex3f(top_left.x, top_left.y, top_left.z);

    rlgl.rlTexCoord2f(uv.left, uv.bottom);
    rlgl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);

    rlgl.rlTexCoord2f(uv.right, uv.bottom);
    rlgl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);

    rlgl.rlTexCoord2f(uv.right, uv.top);
    rlgl.rlVertex3f(top_right.x, top_right.y, top_right.z);
}

test "resolve track set index rejects unresolved windows values" {
    try std.testing.expectEqual(@as(u8, 0), try resolveTrackSetIndex(0));
    try std.testing.expectEqual(@as(u8, 3), try resolveTrackSetIndex(3));
    try std.testing.expectError(error.UnsupportedTrackSetIndex, resolveTrackSetIndex(4));
    try std.testing.expectError(error.UnsupportedTrackSetIndex, resolveTrackSetIndex(5));
}

test "surface family maps recovered runtime tile families" {
    try std.testing.expectEqual(@as(?SurfaceFamily, .floor), surfaceFamilyForTile(0x0f));
    try std.testing.expectEqual(@as(?SurfaceFamily, .slide), surfaceFamilyForTile(0x15));
    try std.testing.expectEqual(@as(?SurfaceFamily, .ramp), surfaceFamilyForTile(0x03));
    try std.testing.expectEqual(@as(?SurfaceFamily, null), surfaceFamilyForTile(0x1d));
}

test "top surface uv follows recovered world mapping" {
    const uv = topSurfaceUv(.floor, -4.0, -3.0, 0.0, 1.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), uv.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), uv.right, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.875), uv.bottom, 0.0001);
}

test "top surface uv resets on 24-row cache chunk boundaries" {
    const uv = topSurfaceUv(.slide, -4.0, -3.0, 24.0, 25.0);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.875), uv.bottom, 0.0001);
}

test "ramp surface uv keeps per-cell mapping" {
    const uv = topSurfaceUv(.ramp, -4.0, -3.0, 0.0, 1.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), uv.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.right, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), uv.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.bottom, 0.0001);
}

test "render lane bounds keep the traversable strip instead of path-only lanes" {
    const bounds = renderLaneBounds("@__P__p_@").?;
    try std.testing.expectEqual(@as(usize, 1), bounds.min);
    try std.testing.expectEqual(@as(usize, 7), bounds.max);
}

test "slide run merge matches recovered runtime tile subset" {
    try std.testing.expect(isSlideRunMergeTile(0x01));
    try std.testing.expect(isSlideRunMergeTile(0x15));
    try std.testing.expect(isSlideRunMergeTile(0x1b));
    try std.testing.expect(isSlideRunMergeTile(0x21));
    try std.testing.expect(isSlideRunMergeTile(0x22));
    try std.testing.expect(!isSlideRunMergeTile(0x14));
    try std.testing.expect(!isSlideRunMergeTile(0x20));
}
