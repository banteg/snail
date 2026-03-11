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
        var textures = try Textures.load(allocator, catalog, track_set_index);
        errdefer textures.unload();

        return .{
            .allocator = allocator,
            .track_set_index = normalizeTrackSetIndex(track_set_index),
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
        const safe_track_set = normalizeTrackSetIndex(track_set_index);

        var track_path_buffer: [64]u8 = undefined;
        var slide_path_buffer: [64]u8 = undefined;

        var textures = Textures{
            .track = try catalog.loadTextureByPath(allocator, try std.fmt.bufPrint(&track_path_buffer, track_texture_path_fmt, .{safe_track_set})),
            .slide = try catalog.loadTextureByPath(allocator, try std.fmt.bufPrint(&slide_path_buffer, slide_texture_path_fmt, .{safe_track_set})),
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

pub fn normalizeTrackSetIndex(track_set_index: u8) u8 {
    return track_set_index % 4;
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
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;

    for (0..preview.total_rows) |global_row| {
        for (0..preview.max_width) |lane_index| {
            const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
            const family = surfaceFamilyForTile(tile_type) orelse continue;

            const left = @as(f32, @floatFromInt(lane_index)) - width_offset;
            const right = left + 1.0;
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
                .{ .left = 0.0, .right = 1.0, .top = 0.0, .bottom = 1.0 },
            );

            const edge_mask = preview.runtimeEdgeMaskAt(global_row, lane_index) orelse 0;
            if (edge_mask != 0) {
                drawFringeSides(scene, left, right, front, back, front_height, back_height, edge_mask);
            }
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

test "normalize track set index wraps into windows range" {
    try std.testing.expectEqual(@as(u8, 0), normalizeTrackSetIndex(0));
    try std.testing.expectEqual(@as(u8, 3), normalizeTrackSetIndex(3));
    try std.testing.expectEqual(@as(u8, 0), normalizeTrackSetIndex(4));
    try std.testing.expectEqual(@as(u8, 1), normalizeTrackSetIndex(5));
}

test "surface family maps recovered runtime tile families" {
    try std.testing.expectEqual(@as(?SurfaceFamily, .floor), surfaceFamilyForTile(0x0f));
    try std.testing.expectEqual(@as(?SurfaceFamily, .slide), surfaceFamilyForTile(0x15));
    try std.testing.expectEqual(@as(?SurfaceFamily, .ramp), surfaceFamilyForTile(0x03));
    try std.testing.expectEqual(@as(?SurfaceFamily, .warn), surfaceFamilyForTile(0x20));
    try std.testing.expectEqual(@as(?SurfaceFamily, null), surfaceFamilyForTile(0x1d));
}
