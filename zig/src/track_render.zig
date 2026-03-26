const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const attachment_builders = @import("attachment_builders.zig");
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
const track_skirt_tint = rl.Color{ .r = 255, .g = 255, .b = 255, .a = 102 };

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
        drawAttachmentGeometry(self, preview, selected_segment_index);
        preview.drawPlacedModelsOnly();
        drawSegmentSelectionOutline(preview, selected_segment_index);
    }

    pub fn drawGameplay(self: *const Scene, preview: *const track.LoadedLevelPreview, selected_segment_index: usize) void {
        drawRuntimeCells(self, preview);
        drawAttachmentGeometry(self, preview, selected_segment_index);
        preview.drawPlacedModelsOnly();
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
        .white,
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
            const family = surfaceFamilyForRuntimeCell(preview, global_row, lane_index) orelse continue;
            if (!preview.runtimeFlagB40At(global_row, lane_index)) continue;
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
                .white,
            );

            for (lane_index..lane_index + run_length) |edge_lane_index| {
                const edge_left = @as(f32, @floatFromInt(edge_lane_index)) - width_offset;
                const edge_right = edge_left + 1.0;
                const fringe_edge_mask = fringeEdgeMaskForRuntimeTiles(
                    preview.runtime_tiles,
                    preview.total_rows,
                    preview.max_width,
                    global_row,
                    edge_lane_index,
                    row_location.row.marked,
                );
                if (fringe_edge_mask != 0) {
                    drawFringeSides(scene, edge_left, edge_right, front, back, front_height, back_height, fringe_edge_mask);
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
            track_skirt_tint,
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
            track_skirt_tint,
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
            track_skirt_tint,
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
            track_skirt_tint,
        );
    }
}

fn fringeObjectsEnabledForRuntimeCell(row_marked: bool, tile_type: u8) bool {
    if (row_marked) return false;
    return tile_type != 0x20;
}

fn runtimeTileIsFringeSolid(tile_type: u8) bool {
    return !track.isOpenNeighborRuntimeTileFamily(tile_type) and tile_type != 0x16;
}

fn fringeNeighborIsSolid(
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
) bool {
    if (global_row >= total_rows or lane_index >= max_width) return false;
    return runtimeTileIsFringeSolid(runtime_tiles[(global_row * max_width) + lane_index]);
}

fn fringeEdgeMaskForRuntimeTiles(
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
    row_marked: bool,
) u8 {
    if (global_row >= total_rows or max_width == 0 or lane_index >= max_width) return 0;
    const tile_type = runtime_tiles[(global_row * max_width) + lane_index];
    if (!fringeObjectsEnabledForRuntimeCell(row_marked, tile_type)) return 0;
    if (!runtimeTileIsFringeSolid(tile_type)) return 0;

    var mask: u8 = 0;
    if (lane_index == 0 or !fringeNeighborIsSolid(runtime_tiles, total_rows, max_width, global_row, lane_index - 1)) {
        mask |= 0x08;
    }
    if (lane_index + 1 >= max_width or !fringeNeighborIsSolid(runtime_tiles, total_rows, max_width, global_row, lane_index + 1)) {
        mask |= 0x04;
    }
    if (global_row == 0 or !fringeNeighborIsSolid(runtime_tiles, total_rows, max_width, global_row - 1, lane_index)) {
        mask |= 0x01;
    }
    if (global_row + 1 >= total_rows or !fringeNeighborIsSolid(runtime_tiles, total_rows, max_width, global_row + 1, lane_index)) {
        mask |= 0x02;
    }
    return mask;
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

fn drawAttachmentGeometry(scene: *const Scene, preview: *const track.LoadedLevelPreview, selected_segment_index: usize) void {
    if (preview.attachment_scaffold.built_attachments.len == 0) return;

    for (preview.attachment_scaffold.built_attachments) |*built| {
        if (built.row.segment_index != selected_segment_index) continue;
        switch (built.template.spec.family) {
            .nonlinear_42 => drawNonlinear42Attachment(scene, built),
            else => drawOrdinaryAttachment(scene, built),
        }
    }
}

fn drawOrdinaryAttachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    const half_width = @as(f32, @floatFromInt(template.width_cells)) * 0.5;
    const subdivisions = template.width_cells;
    const base_row = @as(f32, @floatFromInt(built.row.global_row));

    for (0..template.samples.len - 1) |sample_index| {
        const front_pose = attachment_builders.samplePoseAtProgress(template, @floatFromInt(sample_index));
        const back_pose = attachment_builders.samplePoseAtProgress(template, @floatFromInt(sample_index + 1));
        const front_world_z = base_row + front_pose.position.z;
        const back_world_z = base_row + back_pose.position.z;

        for (0..subdivisions) |subdivision| {
            const left_offset = -half_width + @as(f32, @floatFromInt(subdivision));
            const right_offset = left_offset + 1.0;

            drawDoubleSidedTexturedQuad(
                scene.textures.track.texture,
                scene.textures.track.texture,
                attachmentVertex(front_pose, left_offset, base_row),
                attachmentVertex(back_pose, left_offset, base_row),
                attachmentVertex(back_pose, right_offset, base_row),
                attachmentVertex(front_pose, right_offset, base_row),
                topSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z),
            );
        }
    }
}

fn drawNonlinear42Attachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    const half_width = @as(f32, @floatFromInt(template.width_cells)) * 0.5;
    const subdivisions = template.width_cells;

    for (0..template.samples.len - 1) |sample_index| {
        const front_progress: f32 = @floatFromInt(sample_index);
        const back_progress: f32 = @floatFromInt(sample_index + 1);
        const front_pose = attachment_builders.samplePoseAtProgress(template, front_progress);
        const back_pose = attachment_builders.samplePoseAtProgress(template, back_progress);
        const front_world_z = @as(f32, @floatFromInt(built.row.global_row)) + front_pose.position.z;
        const back_world_z = @as(f32, @floatFromInt(built.row.global_row)) + back_pose.position.z;

        for (0..subdivisions) |subdivision| {
            const left_offset = -half_width + @as(f32, @floatFromInt(subdivision));
            const right_offset = left_offset + 1.0;

            drawDoubleSidedTexturedQuad(
                scene.textures.track.texture,
                scene.textures.track.texture,
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, right_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, right_offset),
                topSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z),
            );
        }
    }
}

fn attachmentVertex(
    pose: attachment_builders.AttachmentPose,
    lateral_offset: f32,
    base_row: f32,
) rl.Vector3 {
    const local_lateral = pose.center_x + (lateral_offset * pose.lateral_scale);
    return .{
        .x = pose.position.x + (pose.basis_right.x * local_lateral),
        .y = pose.position.y + (pose.basis_right.y * local_lateral),
        .z = base_row + pose.position.z + (pose.basis_right.z * local_lateral),
    };
}

fn nonlinear42AttachmentVertex(
    template: *const attachment_builders.Template,
    source_cell_row: usize,
    progress: f32,
    lateral_offset: f32,
) rl.Vector3 {
    const world = attachment_builders.worldPositionForTemplate(
        template,
        progress,
        source_cell_row,
        lateral_offset,
        -0.49,
    );
    return .{
        .x = world.x,
        .y = world.y,
        .z = world.z,
    };
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

fn surfaceFamilyForRuntimeCell(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
) ?SurfaceFamily {
    const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse return null;
    if (preview.runtimeWarnSurfaceAt(global_row, lane_index)) return .warn;

    var family = surfaceFamilyForTile(tile_type) orelse return null;
    if (preview.runtimeSurfaceSwapAt(global_row, lane_index)) {
        family = switch (family) {
            .floor => .slide,
            .slide => .floor,
            .warn, .ramp => family,
        };
    }
    return family;
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
        if (preview.runtimeFlagB40At(global_row, scan_lane)) break;
        const next_family = surfaceFamilyForRuntimeCell(preview, global_row, scan_lane) orelse break;
        if (next_family != family) break;
        run_length += 1;
    }
    return run_length;
}

test "fringe objects follow the recovered row and tile suppression rules" {
    try std.testing.expect(!fringeObjectsEnabledForRuntimeCell(true, 0x01));
    try std.testing.expect(!fringeObjectsEnabledForRuntimeCell(false, 0x20));
    try std.testing.expect(fringeObjectsEnabledForRuntimeCell(false, 0x01));
}

test "fringe edge mask follows the native solid-neighbor helper" {
    const tiles = [_]u8{
        0x01, 0x16,
        0x00, 0x01,
    };
    try std.testing.expect(!runtimeTileIsFringeSolid(0x16));
    try std.testing.expectEqual(@as(u8, 0x0f), fringeEdgeMaskForRuntimeTiles(&tiles, 2, 2, 0, 0, false));
    try std.testing.expectEqual(@as(u8, 0x00), fringeEdgeMaskForRuntimeTiles(&tiles, 2, 2, 0, 1, false));
}

test "track skirt tint follows the recovered shared skirt alpha" {
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.r);
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.g);
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.b);
    try std.testing.expectEqual(@as(u8, 102), track_skirt_tint.a);
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
    tint: rl.Color,
) void {
    rlgl.rlSetTexture(texture.id);
    defer rlgl.rlSetTexture(0);

    rlgl.rlBegin(rlgl.rl_quads);
    defer rlgl.rlEnd();
    rlgl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rlgl.rlTexCoord2f(uv.left, uv.top);
    rlgl.rlVertex3f(top_left.x, top_left.y, top_left.z);

    rlgl.rlTexCoord2f(uv.left, uv.bottom);
    rlgl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);

    rlgl.rlTexCoord2f(uv.right, uv.bottom);
    rlgl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);

    rlgl.rlTexCoord2f(uv.right, uv.top);
    rlgl.rlVertex3f(top_right.x, top_right.y, top_right.z);
}

fn drawDoubleSidedTexturedQuad(
    front_texture: rl.Texture2D,
    back_texture: rl.Texture2D,
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: QuadUv,
) void {
    drawTexturedQuad(front_texture, top_left, bottom_left, bottom_right, top_right, uv, .white);
    drawTexturedQuad(back_texture, top_right, bottom_right, bottom_left, top_left, uv, .white);
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
