const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const attachment_builders = @import("attachment_builders.zig");
const assets = @import("assets.zig");
const resource_store = @import("resource_store.zig");
const track = @import("track.zig");

const track_texture_path_fmt = "OBJECTS/WORLD00/TRACK{d}.TGA";
const slide_texture_path_fmt = "OBJECTS/WORLD00/SLIDE{d}.TGA";
const warn_texture_path = "OBJECTS/WORLD00/TRACKWARN.TGA";
const back_texture_path = "OBJECTS/WORLD00/BACK.TGA";
const ramp_texture_path = "OBJECTS/UNIVERSE/RAMP.TGA";
const fringe_texture_path = "OBJECTS/UNIVERSE/FRINGE.TGA";

const back_plane_margin: f32 = 4.0;
const back_plane_y: f32 = -0.66;
const track_skirt_tint = rl.Color{ .r = 255, .g = 255, .b = 255, .a = 102 };
const attachment_fringe_outset: f32 = 0.4;
const fringe_texture_u: f32 = 0.5;
const fringe_edge_v: f32 = 1.0;
const fringe_outset_v: f32 = 0.0;

pub const Scene = struct {
    allocator: std.mem.Allocator,
    track_set_index: u8,
    textures: Textures,

    pub fn buildStandaloneSegmentScene(
        allocator: std.mem.Allocator,
        store: *resource_store.Store,
        track_set_index: u8,
    ) !Scene {
        const resolved_track_set = try resolveTrackSetIndex(track_set_index);
        var textures = try Textures.load(store, resolved_track_set);
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
        drawRenderCacheCells(self, preview);
        drawAttachmentGeometry(self, preview, selected_segment_index);
        preview.drawPlacedModelsOnly();
        drawSegmentSelectionOutline(preview, selected_segment_index);
    }

    pub fn drawGameplay(self: *const Scene, preview: *const track.LoadedLevelPreview) void {
        drawRenderCacheCells(self, preview);
        drawAllAttachmentGeometry(self, preview);
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

    fn load(store: *resource_store.Store, track_set_index: u8) !Textures {
        var track_path_buffer: [64]u8 = undefined;
        var slide_path_buffer: [64]u8 = undefined;

        var textures = Textures{
            .track = try store.texture(try std.fmt.bufPrint(&track_path_buffer, track_texture_path_fmt, .{track_set_index})),
            .slide = try store.texture(try std.fmt.bufPrint(&slide_path_buffer, slide_texture_path_fmt, .{track_set_index})),
            .warn = try store.texture(warn_texture_path),
            .ramp = try store.texture(ramp_texture_path),
            .fringe = try store.texture(fringe_texture_path),
            .back = try store.texture(back_texture_path),
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

const RenderCacheFamily = enum {
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

const TexturedVertex = struct {
    position: rl.Vector3,
    u: f32,
    v: f32,
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
    // FRINGE.TGA is a tiny edge alpha ramp; repeating wraps the opposite edge into the falloff.
    rl.setTextureWrap(textures.fringe.texture, .clamp);
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

fn drawRenderCacheCells(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
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
            const family = renderCacheFamilyForRuntimeCell(preview, global_row, lane_index) orelse continue;
            if (!preview.renderCacheHeadAt(global_row, lane_index) and track.renderBackingSurfaceTileForRuntimeTile(tile_type) == null) continue;
            const run_length = mergedRenderCacheRunLength(preview, global_row, lane_index, max_lane_index, family);

            const left = @as(f32, @floatFromInt(lane_index)) - width_offset;
            const right = left + @as(f32, @floatFromInt(run_length));
            const front = @as(f32, @floatFromInt(global_row));
            const back = front + 1.0;
            const surface_tile = track.renderSurfaceTileForRuntimeTile(tile_type);
            const front_height = surfaceHeightAtTileFraction(surface_tile, front, 0.0);
            const back_height = surfaceHeightAtTileFraction(surface_tile, front, 0.999);

            const top_left = rl.Vector3{ .x = left, .y = front_height, .z = front };
            const bottom_left = rl.Vector3{ .x = left, .y = back_height, .z = back };
            const bottom_right = rl.Vector3{ .x = right, .y = back_height, .z = back };
            const top_right = rl.Vector3{ .x = right, .y = front_height, .z = front };

            if (family == .ramp) {
                drawTexturedQuad(
                    scene.textures.track.texture,
                    top_left,
                    bottom_left,
                    bottom_right,
                    top_right,
                    renderCacheSurfaceUv(.floor, left, right, front, back),
                    .white,
                );
            }

            drawTexturedQuad(
                textureForRenderCacheFamily(scene, family),
                top_left,
                bottom_left,
                bottom_right,
                top_right,
                renderCacheSurfaceUv(family, left, right, front, back),
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
    if ((edge_mask & 0x08) != 0) {
        drawFringeRamp(
            scene,
            .{ .x = left, .y = back_height, .z = back },
            .{ .x = left - attachment_fringe_outset, .y = back_height, .z = back },
            .{ .x = left - attachment_fringe_outset, .y = front_height, .z = front },
            .{ .x = left, .y = front_height, .z = front },
        );
    }
    if ((edge_mask & 0x04) != 0) {
        drawFringeRamp(
            scene,
            .{ .x = right, .y = front_height, .z = front },
            .{ .x = right + attachment_fringe_outset, .y = front_height, .z = front },
            .{ .x = right + attachment_fringe_outset, .y = back_height, .z = back },
            .{ .x = right, .y = back_height, .z = back },
        );
    }
    if ((edge_mask & 0x01) != 0) {
        drawFringeRamp(
            scene,
            .{ .x = left, .y = front_height, .z = front },
            .{ .x = left, .y = front_height, .z = front - attachment_fringe_outset },
            .{ .x = right, .y = front_height, .z = front - attachment_fringe_outset },
            .{ .x = right, .y = front_height, .z = front },
        );
    }
    if ((edge_mask & 0x02) != 0) {
        drawFringeRamp(
            scene,
            .{ .x = right, .y = back_height, .z = back },
            .{ .x = right, .y = back_height, .z = back + attachment_fringe_outset },
            .{ .x = left, .y = back_height, .z = back + attachment_fringe_outset },
            .{ .x = left, .y = back_height, .z = back },
        );
    }
}

fn drawFringeRamp(
    scene: *const Scene,
    edge_a: rl.Vector3,
    outer_a: rl.Vector3,
    outer_b: rl.Vector3,
    edge_b: rl.Vector3,
) void {
    drawDoubleSidedTexturedVertexQuad(
        scene.textures.fringe.texture,
        .{ .position = edge_a, .u = fringe_texture_u, .v = fringe_edge_v },
        .{ .position = outer_a, .u = fringe_texture_u, .v = fringe_outset_v },
        .{ .position = outer_b, .u = fringe_texture_u, .v = fringe_outset_v },
        .{ .position = edge_b, .u = fringe_texture_u, .v = fringe_edge_v },
        track_skirt_tint,
    );
}

fn fringeObjectsEnabledForRuntimeCell(row_marked: bool, tile_type: u8) bool {
    if (row_marked) return false;
    return tile_type != 0x20;
}

fn runtimeTileIsFringeSolid(tile_type: u8) bool {
    if (track.renderBackingSurfaceTileForRuntimeTile(tile_type) != null) return true;
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
        drawBuiltAttachment(scene, built);
    }
}

fn drawAllAttachmentGeometry(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
    if (preview.attachment_scaffold.built_attachments.len == 0) return;

    for (preview.attachment_scaffold.built_attachments) |*built| {
        drawBuiltAttachment(scene, built);
    }
}

fn drawBuiltAttachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    drawAttachmentFringe(scene, built);
    switch (built.template.spec.family) {
        .nonlinear_42 => drawNonlinear42Attachment(scene, built),
        else => drawOrdinaryAttachment(scene, built),
    }
}

fn drawAttachmentFringe(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2 or template.width_cells == 0) return;

    const half_width = @as(f32, @floatFromInt(template.width_cells)) * 0.5;
    const left_edge_offset = -half_width;
    const left_inner_offset = @min(left_edge_offset + 1.0, half_width);
    const right_edge_offset = half_width;
    const right_inner_offset = @max(right_edge_offset - 1.0, -half_width);

    for (0..template.samples.len - 1) |sample_index| {
        const front_progress: f32 = @floatFromInt(sample_index);
        const back_progress: f32 = @floatFromInt(sample_index + 1);

        const front_left_edge = attachmentPathVertex(built, front_progress, left_edge_offset);
        const back_left_edge = attachmentPathVertex(built, back_progress, left_edge_offset);
        const front_left_outer = extendAttachmentEdge(front_left_edge, attachmentPathVertex(built, front_progress, left_inner_offset));
        const back_left_outer = extendAttachmentEdge(back_left_edge, attachmentPathVertex(built, back_progress, left_inner_offset));

        const front_right_edge = attachmentPathVertex(built, front_progress, right_edge_offset);
        const back_right_edge = attachmentPathVertex(built, back_progress, right_edge_offset);
        const front_right_outer = extendAttachmentEdge(front_right_edge, attachmentPathVertex(built, front_progress, right_inner_offset));
        const back_right_outer = extendAttachmentEdge(back_right_edge, attachmentPathVertex(built, back_progress, right_inner_offset));

        // Native keeps U pinned at the middle of FRINGE.TGA and uses V across the edge/outset span.
        // The raylib upload path samples V inverted relative to the recovered object facequads.
        drawFringeRamp(scene, back_left_edge, back_left_outer, front_left_outer, front_left_edge);
        drawFringeRamp(scene, back_right_edge, back_right_outer, front_right_outer, front_right_edge);
    }
}

fn drawOrdinaryAttachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    const surface_texture = attachmentSurfaceTexture(scene, template);
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
                surface_texture,
                surface_texture,
                attachmentVertex(front_pose, left_offset, base_row),
                attachmentVertex(back_pose, left_offset, base_row),
                attachmentVertex(back_pose, right_offset, base_row),
                attachmentVertex(front_pose, right_offset, base_row),
                renderCacheSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z),
            );
        }
    }
}

fn drawNonlinear42Attachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    const surface_texture = attachmentSurfaceTexture(scene, template);
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
                surface_texture,
                surface_texture,
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, right_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, right_offset),
                renderCacheSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z),
            );
        }
    }
}

fn attachmentSurfaceTexture(scene: *const Scene, template: *const attachment_builders.Template) rl.Texture2D {
    return switch (template.spec.family) {
        // START's native template receives Objects/World00/Slide0.tga as the visible strip.
        .start => scene.textures.slide.texture,
        else => scene.textures.track.texture,
    };
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

fn attachmentPathVertex(
    built: *const attachment_builders.BuiltAttachment,
    progress: f32,
    lateral_offset: f32,
) rl.Vector3 {
    if (built.template.spec.family == .nonlinear_42) {
        return nonlinear42AttachmentVertex(&built.template, built.row.global_row, progress, lateral_offset);
    }

    return attachmentVertex(
        attachment_builders.samplePoseAtProgress(&built.template, progress),
        lateral_offset,
        @floatFromInt(built.row.global_row),
    );
}

fn extendAttachmentEdge(edge: rl.Vector3, inner: rl.Vector3) rl.Vector3 {
    const delta = vector3Sub(edge, inner);
    const len = vector3Length(delta);
    if (len <= 0.0001) return edge;
    return vector3Add(edge, vector3Scale(delta, attachment_fringe_outset / len));
}

fn vector3Add(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

fn vector3Sub(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}

fn vector3Scale(v: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{ .x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar };
}

fn vector3Length(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn textureForRenderCacheFamily(scene: *const Scene, family: RenderCacheFamily) rl.Texture2D {
    return switch (family) {
        .floor => scene.textures.track.texture,
        .slide => scene.textures.slide.texture,
        .warn => scene.textures.warn.texture,
        .ramp => scene.textures.ramp.texture,
    };
}

fn renderCacheFamilyForTile(tile_type: u8) ?RenderCacheFamily {
    const surface_tile = track.renderSurfaceTileForRuntimeTile(tile_type);
    if (track.isFloorCacheRuntimeTileFamily(surface_tile)) return .floor;
    if (track.isSlideRuntimeTileFamily(surface_tile)) return .slide;
    if (track.isRampRuntimeTileFamily(surface_tile)) return .ramp;
    return switch (surface_tile) {
        0x20 => .warn,
        else => null,
    };
}

fn renderCacheFamilyForRuntimeCell(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
) ?RenderCacheFamily {
    const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse return null;
    if (preview.renderCacheWarnSurfaceAt(global_row, lane_index)) return .warn;

    var family = renderCacheFamilyForTile(tile_type) orelse return null;
    if (preview.renderCacheSurfaceSwapAt(global_row, lane_index)) {
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

fn mergedRenderCacheRunLength(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
    max_lane_index: usize,
    family: RenderCacheFamily,
) usize {
    if (family == .ramp or family == .warn) return 1;

    var run_length: usize = 1;
    var scan_lane = lane_index + 1;
    while (scan_lane <= max_lane_index) : (scan_lane += 1) {
        if (preview.renderCacheHeadAt(global_row, scan_lane)) break;
        const next_family = renderCacheFamilyForRuntimeCell(preview, global_row, scan_lane) orelse break;
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

test "fringe edge mask keeps render-backed object cells solid" {
    const tiles = [_]u8{
        0x01, 0x16,
        0x00, 0x01,
    };
    try std.testing.expect(runtimeTileIsFringeSolid(0x1d));
    try std.testing.expect(runtimeTileIsFringeSolid(0x23));
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

test "attachment fringe extends beyond the path edge by the native outset" {
    const edge = rl.Vector3{ .x = -4.0, .y = 2.0, .z = 6.0 };
    const inner = rl.Vector3{ .x = -3.0, .y = 2.0, .z = 6.0 };
    const extended = extendAttachmentEdge(edge, inner);

    try std.testing.expectApproxEqAbs(@as(f32, -4.4), extended.x, 0.0001);
    try std.testing.expectApproxEqAbs(edge.y, extended.y, 0.0001);
    try std.testing.expectApproxEqAbs(edge.z, extended.z, 0.0001);
}

test "fringe uv keeps native mid-u and flips v for raylib sampling" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), fringe_texture_u, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), fringe_edge_v, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), fringe_outset_v, 0.0001);
}

fn renderCacheSurfaceUv(family: RenderCacheFamily, left: f32, right: f32, front: f32, back: f32) QuadUv {
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

fn drawDoubleSidedTexturedVertexQuad(
    texture: rl.Texture2D,
    a: TexturedVertex,
    b: TexturedVertex,
    c: TexturedVertex,
    d: TexturedVertex,
    tint: rl.Color,
) void {
    drawTexturedVertexQuad(texture, a, b, c, d, tint);
    drawTexturedVertexQuad(texture, d, c, b, a, tint);
}

fn drawTexturedVertexQuad(
    texture: rl.Texture2D,
    a: TexturedVertex,
    b: TexturedVertex,
    c: TexturedVertex,
    d: TexturedVertex,
    tint: rl.Color,
) void {
    rlgl.rlSetTexture(texture.id);
    defer rlgl.rlSetTexture(0);

    rlgl.rlBegin(rlgl.rl_quads);
    defer rlgl.rlEnd();
    rlgl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    drawTexturedVertex(a);
    drawTexturedVertex(b);
    drawTexturedVertex(c);
    drawTexturedVertex(d);
}

fn drawTexturedVertex(vertex: TexturedVertex) void {
    rlgl.rlTexCoord2f(vertex.u, vertex.v);
    rlgl.rlVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
}

test "resolve track set index rejects unresolved windows values" {
    try std.testing.expectEqual(@as(u8, 0), try resolveTrackSetIndex(0));
    try std.testing.expectEqual(@as(u8, 3), try resolveTrackSetIndex(3));
    try std.testing.expectError(error.UnsupportedTrackSetIndex, resolveTrackSetIndex(4));
    try std.testing.expectError(error.UnsupportedTrackSetIndex, resolveTrackSetIndex(5));
}

test "surface family maps recovered runtime tile families" {
    try std.testing.expectEqual(@as(?RenderCacheFamily, .floor), renderCacheFamilyForTile(0x0f));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x15));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .ramp), renderCacheFamilyForTile(0x03));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x1d));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x1e));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x23));
}

test "top surface uv follows recovered world mapping" {
    const uv = renderCacheSurfaceUv(.floor, -4.0, -3.0, 0.0, 1.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), uv.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), uv.right, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.875), uv.bottom, 0.0001);
}

test "top surface uv resets on 24-row cache chunk boundaries" {
    const uv = renderCacheSurfaceUv(.slide, -4.0, -3.0, 24.0, 25.0);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), uv.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.875), uv.bottom, 0.0001);
}

test "ramp surface uv keeps per-cell mapping" {
    const uv = renderCacheSurfaceUv(.ramp, -4.0, -3.0, 0.0, 1.0);
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
