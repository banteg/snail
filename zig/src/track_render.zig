const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const attachment_builders = @import("attachment_builders.zig");
const assets = @import("assets.zig");
const gameplay_billboard = @import("gameplay/billboard.zig");
const level = @import("level.zig");
const render_blend = @import("render_blend.zig");
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
        preview.drawPlacedModelsOnly(null);
        drawSegmentSelectionOutline(preview, selected_segment_index);
    }

    pub fn drawGameplay(
        self: *const Scene,
        preview: *const track.LoadedLevelPreview,
        batch_shader: ?rl.Shader,
        model_shader: ?rl.Shader,
    ) void {
        // PORT(partial): native draws the whole world pass with the camera's
        // fog render state active. The batch shader carries the ported fog
        // lanes for world-space geometry; the surfaces themselves are opaque,
        // so only the soft cutoff applies.
        if (batch_shader) |shader| {
            gameplay_billboard.setAlphaCutoff(shader, gameplay_billboard.soft_alpha_cutoff);
            rl.beginShaderMode(shader);
        }
        drawAllAttachmentGeometryForFamily(self, preview, .start);
        drawRenderCacheCells(self, preview);
        drawAllAttachmentGeometryExceptFamily(self, preview, .start);
        if (batch_shader != null) rl.endShaderMode();
        preview.drawPlacedModelsOnly(model_shader);
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

const TexturedQuad = struct {
    a: TexturedVertex,
    b: TexturedVertex,
    c: TexturedVertex,
    d: TexturedVertex,
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
    setSceneSurfaceTextureSampling(&textures.track.texture, .repeat);
    setSceneSurfaceTextureSampling(&textures.slide.texture, .repeat);
    setSceneSurfaceTextureSampling(&textures.warn.texture, .repeat);
    setSceneSurfaceTextureSampling(&textures.ramp.texture, .repeat);
    // FRINGE.TGA is a tiny edge alpha ramp; repeating wraps the opposite edge into the falloff.
    rl.setTextureWrap(textures.fringe.texture, .clamp);
    setSceneSurfaceTextureSampling(&textures.back.texture, .repeat);
}

fn setSceneSurfaceTextureSampling(texture: *rl.Texture2D, wrap: rl.TextureWrap) void {
    rl.genTextureMipmaps(texture);
    rl.setTextureWrap(texture.*, wrap);
    rl.setTextureFilter(texture.*, .anisotropic_16x);
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

    drawRenderCacheSurfaces(scene, preview);
    drawRenderCacheFringe(scene, preview);
}

fn drawRenderCacheSurfaces(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
    drawRenderCacheSurfacePass(scene, preview, .floor, true);
    drawRenderCacheSurfacePass(scene, preview, .slide, false);
    drawRenderCacheSurfacePass(scene, preview, .warn, false);
    drawRenderCacheSurfacePass(scene, preview, .ramp, false);
}

fn drawRenderCacheSurfacePass(
    scene: *const Scene,
    preview: *const track.LoadedLevelPreview,
    target_family: RenderCacheFamily,
    include_ramp_backing: bool,
) void {
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;

    var surface_batch = TexturedQuadBatch.begin(textureForRenderCacheFamily(scene, target_family));
    defer surface_batch.end();

    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const lane_bounds = renderLaneBounds(row_location.row.cells) orelse continue;
        const max_lane_index = @min(lane_bounds.max, preview.max_width - 1);
        if (lane_bounds.min > max_lane_index) continue;

        var lane_index = lane_bounds.min;
        while (lane_index <= max_lane_index) : (lane_index += 1) {
            const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
            const family = renderCacheFamilyForRuntimeCell(preview, global_row, lane_index) orelse continue;
            const backing_surface_tile = renderBackingSurfaceTileForRuntimeCell(preview, global_row, lane_index, tile_type);
            if (!preview.renderCacheHeadAt(global_row, lane_index) and backing_surface_tile == null) continue;
            const run_length = mergedRenderCacheRunLength(preview, global_row, lane_index, max_lane_index, family);
            const draw_ramp_backing = include_ramp_backing and family == .ramp;
            if (family != target_family and !draw_ramp_backing) {
                lane_index += run_length - 1;
                continue;
            }

            const left = @as(f32, @floatFromInt(lane_index)) - width_offset;
            const right = left + @as(f32, @floatFromInt(run_length));
            const front = @as(f32, @floatFromInt(global_row));
            const back = front + 1.0;
            const surface_tile = backing_surface_tile orelse tile_type;
            const front_height = surfaceHeightAtTileFraction(surface_tile, front, 0.0);
            const back_height = surfaceHeightAtTileFraction(surface_tile, front, 0.999);

            const top_left = rl.Vector3{ .x = left, .y = front_height, .z = front };
            const bottom_left = rl.Vector3{ .x = left, .y = back_height, .z = back };
            const bottom_right = rl.Vector3{ .x = right, .y = back_height, .z = back };
            const top_right = rl.Vector3{ .x = right, .y = front_height, .z = front };

            if (draw_ramp_backing) {
                surface_batch.emitQuad(
                    top_left,
                    bottom_left,
                    bottom_right,
                    top_right,
                    renderCacheSurfaceUv(.floor, left, right, front, back),
                    .white,
                );
            } else {
                surface_batch.emitQuad(
                    top_left,
                    bottom_left,
                    bottom_right,
                    top_right,
                    renderCacheSurfaceUv(family, left, right, front, back),
                    .white,
                );
            }

            lane_index += run_length - 1;
        }
    }
}

fn drawRenderCacheFringe(scene: *const Scene, preview: *const track.LoadedLevelPreview) void {
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;

    // PORT(verified): `build_track_fringe_supertramp_mesh` seeds blend preset 5,
    // and `set_blend_mode(5)` maps to D3DBLEND_SRCALPHA/D3DBLEND_ONE.
    render_blend.beginAdditivePreservingFramebufferAlpha();
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();

    var fringe_batch = TexturedQuadBatch.begin(scene.textures.fringe.texture);
    defer fringe_batch.end();

    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const lane_bounds = renderLaneBounds(row_location.row.cells) orelse continue;
        const max_lane_index = @min(lane_bounds.max, preview.max_width - 1);
        if (lane_bounds.min > max_lane_index) continue;

        for (lane_bounds.min..max_lane_index + 1) |lane_index| {
            const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse continue;
            _ = renderCacheFamilyForRuntimeCell(preview, global_row, lane_index) orelse continue;

            const fringe_edge_mask = fringeEdgeMaskForRuntimeTiles(
                preview.runtime_tiles,
                preview.total_rows,
                preview.max_width,
                global_row,
                lane_index,
                row_location.row.marked,
            );
            if (fringe_edge_mask == 0) continue;

            const left = @as(f32, @floatFromInt(lane_index)) - width_offset;
            const right = left + 1.0;
            const front = @as(f32, @floatFromInt(global_row));
            const back = front + 1.0;
            const backing_surface_tile = renderBackingSurfaceTileForRuntimeCell(preview, global_row, lane_index, tile_type);
            const surface_tile = backing_surface_tile orelse tile_type;
            const front_height = surfaceHeightAtTileFraction(surface_tile, front, 0.0);
            const back_height = surfaceHeightAtTileFraction(surface_tile, front, 0.999);

            drawFringeSides(&fringe_batch, left, right, front, back, front_height, back_height, fringe_edge_mask);
        }
    }
}

fn drawFringeSides(
    fringe_batch: *TexturedQuadBatch,
    left: f32,
    right: f32,
    front: f32,
    back: f32,
    front_height: f32,
    back_height: f32,
    edge_mask: u8,
) void {
    const outer_z = fringeSideOuterZSpan(front, back);
    if ((edge_mask & 0x08) != 0) {
        drawFringeRamp(
            fringe_batch,
            .{ .x = left, .y = back_height, .z = back },
            .{ .x = left - attachment_fringe_outset, .y = back_height, .z = outer_z.back },
            .{ .x = left - attachment_fringe_outset, .y = front_height, .z = outer_z.front },
            .{ .x = left, .y = front_height, .z = front },
        );
    }
    if ((edge_mask & 0x04) != 0) {
        drawFringeRamp(
            fringe_batch,
            .{ .x = right, .y = front_height, .z = front },
            .{ .x = right + attachment_fringe_outset, .y = front_height, .z = outer_z.front },
            .{ .x = right + attachment_fringe_outset, .y = back_height, .z = outer_z.back },
            .{ .x = right, .y = back_height, .z = back },
        );
    }
    if ((edge_mask & 0x01) != 0) {
        drawFringeRamp(
            fringe_batch,
            .{ .x = left, .y = front_height, .z = front },
            .{ .x = left, .y = front_height, .z = front - attachment_fringe_outset },
            .{ .x = right, .y = front_height, .z = front - attachment_fringe_outset },
            .{ .x = right, .y = front_height, .z = front },
        );
    }
    if ((edge_mask & 0x02) != 0) {
        drawFringeRamp(
            fringe_batch,
            .{ .x = right, .y = back_height, .z = back },
            .{ .x = right, .y = back_height, .z = back + attachment_fringe_outset },
            .{ .x = left, .y = back_height, .z = back + attachment_fringe_outset },
            .{ .x = left, .y = back_height, .z = back },
        );
    }
}

const FringeSideOuterZSpan = struct {
    front: f32,
    back: f32,
};

fn fringeSideOuterZSpan(front: f32, back: f32) FringeSideOuterZSpan {
    return .{ .front = front, .back = back };
}

fn drawFringeRamp(
    fringe_batch: *TexturedQuadBatch,
    edge_a: rl.Vector3,
    outer_a: rl.Vector3,
    outer_b: rl.Vector3,
    edge_b: rl.Vector3,
) void {
    fringe_batch.emitDoubleSidedVertexQuad(
        .{ .position = edge_a, .u = fringe_texture_u, .v = fringe_edge_v },
        .{ .position = outer_a, .u = fringe_texture_u, .v = fringe_outset_v },
        .{ .position = outer_b, .u = fringe_texture_u, .v = fringe_outset_v },
        .{ .position = edge_b, .u = fringe_texture_u, .v = fringe_edge_v },
        track_skirt_tint,
    );
}

fn fringeObjectsEnabledForRuntimeCell(row_marked: bool, tile_type: u8) bool {
    if (row_marked) return false;
    return tile_type != 0x20 and tile_type != 0x1e and tile_type != 0x21 and tile_type != 0x22;
}

fn runtimeTileIsFringeSolid(tile_type: u8) bool {
    // PORT(verified): `is_neighbor_cell_solid` works from the native runtime
    // tile family, not from our render-backing floor substitution. Ring/open
    // marker cells stay open for fringe objects even when the port draws floor
    // underneath them in the main surface pass.
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

fn drawAllAttachmentGeometryForFamily(
    scene: *const Scene,
    preview: *const track.LoadedLevelPreview,
    family: attachment_builders.BuilderFamily,
) void {
    if (preview.attachment_scaffold.built_attachments.len == 0) return;

    for (preview.attachment_scaffold.built_attachments) |*built| {
        if (built.template.spec.family != family) continue;
        drawBuiltAttachment(scene, built);
    }
}

fn drawAllAttachmentGeometryExceptFamily(
    scene: *const Scene,
    preview: *const track.LoadedLevelPreview,
    family: attachment_builders.BuilderFamily,
) void {
    if (preview.attachment_scaffold.built_attachments.len == 0) return;

    for (preview.attachment_scaffold.built_attachments) |*built| {
        if (built.template.spec.family == family) continue;
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

    render_blend.beginAdditivePreservingFramebufferAlpha();
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();

    var fringe_batch = TexturedQuadBatch.begin(scene.textures.fringe.texture);
    defer fringe_batch.end();

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
        drawFringeRamp(&fringe_batch, back_left_edge, back_left_outer, front_left_outer, front_left_edge);
        drawFringeRamp(&fringe_batch, back_right_edge, back_right_outer, front_right_outer, front_right_edge);
    }
}

fn drawOrdinaryAttachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    enableAttachmentSurfaceCulling();

    const surface_texture = attachmentSurfaceTexture(scene, template);
    const half_width = @as(f32, @floatFromInt(template.width_cells)) * 0.5;
    const subdivisions = template.width_cells;
    const base_row = @as(f32, @floatFromInt(built.row.global_row));

    var surface_batch = TexturedQuadBatch.begin(surface_texture);
    defer surface_batch.end();

    for (0..template.samples.len - 1) |sample_index| {
        const front_pose = attachment_builders.samplePoseAtProgress(template, @floatFromInt(sample_index));
        const back_pose = attachment_builders.samplePoseAtProgress(template, @floatFromInt(sample_index + 1));
        if (startAttachmentFinalFlatSpanSuppressed(template, sample_index, front_pose, back_pose)) continue;
        const front_world_z = base_row + front_pose.position.z;
        const back_world_z = base_row + back_pose.position.z;

        for (0..subdivisions) |subdivision| {
            const left_offset = -half_width + @as(f32, @floatFromInt(subdivision));
            const right_offset = left_offset + 1.0;

            const front_left = attachmentVertex(front_pose, left_offset, base_row);
            const back_left = attachmentVertex(back_pose, left_offset, base_row);
            const back_right = attachmentVertex(back_pose, right_offset, base_row);
            const front_right = attachmentVertex(front_pose, right_offset, base_row);
            const uv = attachmentSurfaceUv(template, sample_index, subdivision, left_offset, right_offset, front_world_z, back_world_z);
            if (template.spec.family == .start) {
                drawStartAttachmentQuad(&surface_batch, front_left, back_left, back_right, front_right, uv);
            } else {
                surface_batch.emitDoubleSidedQuad(
                    front_left,
                    back_left,
                    back_right,
                    front_right,
                    uv,
                    .white,
                );
            }
        }
    }
}

fn drawStartAttachmentQuad(
    surface_batch: *TexturedQuadBatch,
    front_left: rl.Vector3,
    back_left: rl.Vector3,
    back_right: rl.Vector3,
    front_right: rl.Vector3,
    uv: QuadUv,
) void {
    const quads = startAttachmentFaceQuads(front_left, back_left, back_right, front_right, uv);
    surface_batch.emitVertexQuad(quads[0], .white);
    surface_batch.emitVertexQuad(quads[1], .white);
}

fn startAttachmentFinalFlatSpanSuppressed(
    template: *const attachment_builders.Template,
    sample_index: usize,
    front_pose: attachment_builders.AttachmentPose,
    back_pose: attachment_builders.AttachmentPose,
) bool {
    if (template.spec.family != .start) return false;
    if (sample_index + 2 != template.samples.len) return false;
    return @abs(front_pose.position.y) <= 0.0001 and @abs(back_pose.position.y) <= 0.0001;
}

fn enableAttachmentSurfaceCulling() void {
    // Native path meshes render with D3D culling enabled; without it the paired
    // front/back facequads fight because they use opposite quad diagonals.
    rl.gl.rlEnableBackfaceCulling();
}

fn startAttachmentFaceQuads(
    front_left: rl.Vector3,
    back_left: rl.Vector3,
    back_right: rl.Vector3,
    front_right: rl.Vector3,
    uv: QuadUv,
) [2]TexturedQuad {
    return .{
        .{
            .a = .{ .position = front_left, .u = uv.left, .v = uv.top },
            .b = .{ .position = front_right, .u = uv.right, .v = uv.top },
            .c = .{ .position = back_right, .u = uv.right, .v = uv.bottom },
            .d = .{ .position = back_left, .u = uv.left, .v = uv.bottom },
        },
        .{
            .a = .{ .position = front_right, .u = uv.right, .v = uv.top },
            .b = .{ .position = front_left, .u = uv.left, .v = uv.top },
            .c = .{ .position = back_left, .u = uv.left, .v = uv.bottom },
            .d = .{ .position = back_right, .u = uv.right, .v = uv.bottom },
        },
    };
}

fn drawNonlinear42Attachment(scene: *const Scene, built: *const attachment_builders.BuiltAttachment) void {
    const template = &built.template;
    if (template.samples.len < 2) return;

    enableAttachmentSurfaceCulling();

    const surface_texture = attachmentSurfaceTexture(scene, template);
    const half_width = @as(f32, @floatFromInt(template.width_cells)) * 0.5;
    const subdivisions = template.width_cells;

    var surface_batch = TexturedQuadBatch.begin(surface_texture);
    defer surface_batch.end();

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

            surface_batch.emitDoubleSidedQuad(
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, left_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, back_progress, right_offset),
                nonlinear42AttachmentVertex(template, built.row.global_row, front_progress, right_offset),
                renderCacheSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z),
                .white,
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

fn attachmentSurfaceUv(
    template: *const attachment_builders.Template,
    sample_index: usize,
    subdivision: usize,
    left_offset: f32,
    right_offset: f32,
    front_world_z: f32,
    back_world_z: f32,
) QuadUv {
    if (template.spec.family == .start) {
        const row_phase = @as(f32, @floatFromInt(sample_index & 7)) * 0.125;
        return .{
            .left = @as(f32, @floatFromInt(subdivision)) * 0.125,
            .right = @as(f32, @floatFromInt(subdivision + 1)) * 0.125,
            .top = row_phase,
            .bottom = row_phase + 0.125,
        };
    }

    return renderCacheSurfaceUv(.floor, left_offset, right_offset, front_world_z, back_world_z);
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

fn renderCacheFamilyForSurfaceTile(surface_tile: u8) ?RenderCacheFamily {
    if (track.isFloorCacheRuntimeTileFamily(surface_tile)) return .floor;
    if (track.isSlideRuntimeTileFamily(surface_tile)) return .slide;
    if (track.isRampRuntimeTileFamily(surface_tile)) return .ramp;
    return switch (surface_tile) {
        0x20 => .warn,
        else => null,
    };
}

fn renderCacheFamilyForTile(tile_type: u8) ?RenderCacheFamily {
    return renderCacheFamilyForSurfaceTile(track.renderSurfaceTileForRuntimeTile(tile_type));
}

fn renderCacheFamilyForRuntimeCell(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
) ?RenderCacheFamily {
    const tile_type = preview.runtimeTileAt(global_row, lane_index) orelse return null;
    if (tile_type == 0x20 and runtimeCellIsFullWidthCapRow(preview, global_row)) return .floor;
    if (preview.renderCacheWarnSurfaceAt(global_row, lane_index)) return .warn;

    const surface_tile = renderBackingSurfaceTileForRuntimeCell(preview, global_row, lane_index, tile_type) orelse tile_type;
    var family = renderCacheFamilyForSurfaceTile(surface_tile) orelse return null;
    if (preview.renderCacheSurfaceSwapAt(global_row, lane_index)) {
        family = switch (family) {
            .floor => .slide,
            .slide => .floor,
            .warn, .ramp => family,
        };
    }
    return family;
}

fn runtimeCellIsFullWidthCapRow(preview: *const track.LoadedLevelPreview, global_row: usize) bool {
    const row_location = preview.locateRow(global_row) orelse return false;
    var saw_cap_cell = false;
    for (row_location.row.cells) |cell| {
        if (cell == '@') continue;
        if (cell != '#') return false;
        saw_cap_cell = true;
    }
    return saw_cap_cell;
}

fn renderBackingSurfaceTileForRuntimeCell(
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
    tile_type: u8,
) ?u8 {
    _ = preview;
    _ = global_row;
    _ = lane_index;
    return track.renderBackingSurfaceTileForRuntimeTile(tile_type);
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
    try std.testing.expect(!fringeObjectsEnabledForRuntimeCell(false, 0x1e));
    try std.testing.expect(!fringeObjectsEnabledForRuntimeCell(false, 0x21));
    try std.testing.expect(!fringeObjectsEnabledForRuntimeCell(false, 0x22));
    try std.testing.expect(fringeObjectsEnabledForRuntimeCell(false, 0x01));
}

test "object runtime tiles keep their native slide-cache surface" {
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x21));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x22));
}

test "fringe edge mask follows native solid-neighbor tile family" {
    const tiles = [_]u8{
        0x01, 0x16,
        0x00, 0x01,
    };
    try std.testing.expect(!runtimeTileIsFringeSolid(0x0e));
    try std.testing.expect(!runtimeTileIsFringeSolid(0x1d));
    try std.testing.expect(runtimeTileIsFringeSolid(0x1e));
    try std.testing.expect(!runtimeTileIsFringeSolid(0x23));
    try std.testing.expect(!runtimeTileIsFringeSolid(0x16));
    try std.testing.expectEqual(@as(u8, 0x0f), fringeEdgeMaskForRuntimeTiles(&tiles, 2, 2, 0, 0, false));
    try std.testing.expectEqual(@as(u8, 0x00), fringeEdgeMaskForRuntimeTiles(&tiles, 2, 2, 0, 1, false));
    try std.testing.expectEqual(@as(u8, 0x00), fringeEdgeMaskForRuntimeTiles(&[_]u8{0x1e}, 1, 1, 0, 0, false));
}

test "track skirt tint follows the recovered shared skirt alpha" {
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.r);
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.g);
    try std.testing.expectEqual(@as(u8, 255), track_skirt_tint.b);
    try std.testing.expectEqual(@as(u8, 102), track_skirt_tint.a);
}

test "fringe side ramps stay row-local at exposed row corners" {
    // PORT(verified): Windows chooses separate directional fringe-object variants
    // in `build_track_fringe_objects`; side meshes do not stretch through the
    // front/back corner cells.
    const span = fringeSideOuterZSpan(12.0, 13.0);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), span.front, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 13.0), span.back, 0.0001);
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
    rlgl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rlgl.rlTexCoord2f(uv.left, uv.top);
    rlgl.rlVertex3f(top_left.x, top_left.y, top_left.z);

    rlgl.rlTexCoord2f(uv.left, uv.bottom);
    rlgl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);

    rlgl.rlTexCoord2f(uv.right, uv.bottom);
    rlgl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);

    rlgl.rlTexCoord2f(uv.right, uv.top);
    rlgl.rlVertex3f(top_right.x, top_right.y, top_right.z);

    rlgl.rlEnd();
    rlgl.rlDrawRenderBatchActive();
}

const TexturedQuadBatch = struct {
    texture: ?rl.Texture2D = null,

    fn init() TexturedQuadBatch {
        return .{};
    }

    fn begin(texture: rl.Texture2D) TexturedQuadBatch {
        var batch = TexturedQuadBatch.init();
        batch.useTexture(texture);
        return batch;
    }

    fn useTexture(self: *TexturedQuadBatch, texture: rl.Texture2D) void {
        if (self.texture) |active_texture| {
            if (active_texture.id == texture.id) return;
            self.end();
        }

        rlgl.rlDrawRenderBatchActive();
        rlgl.rlSetTexture(texture.id);
        rlgl.rlBegin(rlgl.rl_quads);
        self.texture = texture;
    }

    fn end(self: *TexturedQuadBatch) void {
        if (self.texture == null) return;

        rlgl.rlEnd();
        rlgl.rlDrawRenderBatchActive();
        rlgl.rlSetTexture(0);
        self.texture = null;
    }

    fn emitQuad(
        self: *TexturedQuadBatch,
        top_left: rl.Vector3,
        bottom_left: rl.Vector3,
        bottom_right: rl.Vector3,
        top_right: rl.Vector3,
        uv: QuadUv,
        tint: rl.Color,
    ) void {
        std.debug.assert(self.texture != null);
        emitTexturedQuad(top_left, bottom_left, bottom_right, top_right, uv, tint);
    }

    fn emitDoubleSidedQuad(
        self: *TexturedQuadBatch,
        top_left: rl.Vector3,
        bottom_left: rl.Vector3,
        bottom_right: rl.Vector3,
        top_right: rl.Vector3,
        uv: QuadUv,
        tint: rl.Color,
    ) void {
        self.emitQuad(top_left, bottom_left, bottom_right, top_right, uv, tint);
        self.emitQuad(top_right, bottom_right, bottom_left, top_left, uv, tint);
    }

    fn emitVertexQuad(
        self: *TexturedQuadBatch,
        quad: TexturedQuad,
        tint: rl.Color,
    ) void {
        std.debug.assert(self.texture != null);
        emitTexturedVertexQuad(quad.a, quad.b, quad.c, quad.d, tint);
    }

    fn emitDoubleSidedVertexQuad(
        self: *TexturedQuadBatch,
        a: TexturedVertex,
        b: TexturedVertex,
        c: TexturedVertex,
        d: TexturedVertex,
        tint: rl.Color,
    ) void {
        std.debug.assert(self.texture != null);
        emitTexturedVertexQuad(a, b, c, d, tint);
        emitTexturedVertexQuad(d, c, b, a, tint);
    }
};

fn emitTexturedQuad(
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: QuadUv,
    tint: rl.Color,
) void {
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

fn emitTexturedVertexQuad(
    a: TexturedVertex,
    b: TexturedVertex,
    c: TexturedVertex,
    d: TexturedVertex,
    tint: rl.Color,
) void {
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
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x0e));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x1d));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x1e));
    try std.testing.expectEqual(@as(?RenderCacheFamily, .slide), renderCacheFamilyForTile(0x23));
}

test "start attachment span leaves authored empty rows out of the render cache" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/TUTORIAL.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
        },
    );
    defer preview.deinit();

    for (5..30) |empty_start_row| {
        for (1..9) |start_lane| {
            try std.testing.expectEqual(@as(u8, 0x00), preview.runtimeTileAt(empty_start_row, start_lane).?);
            try std.testing.expectEqual(
                @as(?RenderCacheFamily, null),
                renderCacheFamilyForRuntimeCell(&preview, empty_start_row, start_lane),
            );
        }
    }
}

test "start terminal cap renders as floor instead of a warning strip" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/TUTORIAL.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
        },
    );
    defer preview.deinit();

    const terminal_cap_row = 30;
    try std.testing.expectEqual(@as(u8, 0x20), preview.runtimeTileAt(terminal_cap_row, 1).?);
    try std.testing.expect(runtimeCellIsFullWidthCapRow(&preview, terminal_cap_row));
    try std.testing.expectEqual(
        @as(?RenderCacheFamily, .floor),
        renderCacheFamilyForRuntimeCell(&preview, terminal_cap_row, 1),
    );
}

test "start attachment uv follows recovered facequad tiling" {
    const template = attachment_builders.Template{
        .spec = attachment_builders.specForPublicPath(.start),
        .width_cells = 8,
    };

    const first = attachmentSurfaceUv(&template, 0, 0, -4.0, -3.0, 4.0, 5.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), first.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), first.right, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), first.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), first.bottom, 0.0001);

    const wrapped = attachmentSurfaceUv(&template, 9, 7, 3.0, 4.0, 13.0, 14.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.875), wrapped.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), wrapped.right, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), wrapped.top, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), wrapped.bottom, 0.0001);
}

test "start attachment emits recovered facequad vertex order" {
    const front_left = rl.Vector3{ .x = -1.0, .y = 2.0, .z = 3.0 };
    const back_left = rl.Vector3{ .x = -1.0, .y = 1.0, .z = 4.0 };
    const back_right = rl.Vector3{ .x = 0.0, .y = 1.0, .z = 4.0 };
    const front_right = rl.Vector3{ .x = 0.0, .y = 2.0, .z = 3.0 };
    const uv = QuadUv{ .left = 0.25, .right = 0.375, .top = 0.5, .bottom = 0.625 };

    const quads = startAttachmentFaceQuads(front_left, back_left, back_right, front_right, uv);

    try expectTexturedVertex(quads[0].a, front_left, uv.left, uv.top);
    try expectTexturedVertex(quads[0].b, front_right, uv.right, uv.top);
    try expectTexturedVertex(quads[0].c, back_right, uv.right, uv.bottom);
    try expectTexturedVertex(quads[0].d, back_left, uv.left, uv.bottom);

    try expectTexturedVertex(quads[1].a, front_right, uv.right, uv.top);
    try expectTexturedVertex(quads[1].b, front_left, uv.left, uv.top);
    try expectTexturedVertex(quads[1].c, back_left, uv.left, uv.bottom);
    try expectTexturedVertex(quads[1].d, back_right, uv.right, uv.bottom);
}

test "start attachment suppresses only the final flat cap span" {
    var samples = [_]attachment_builders.TemplateSample{.{}} ** 4;
    const template = attachment_builders.Template{
        .spec = attachment_builders.specForPublicPath(.start),
        .samples = &samples,
    };
    const flat = attachment_builders.AttachmentPose{
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .center_x = 0.0,
        .lateral_scale = 1.0,
        .basis_right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .basis_up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .basis_forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .special_scalar = 0.0,
    };
    var raised = flat;
    raised.position.y = 1.0;

    try std.testing.expect(!startAttachmentFinalFlatSpanSuppressed(&template, 1, flat, flat));
    try std.testing.expect(!startAttachmentFinalFlatSpanSuppressed(&template, 2, raised, flat));
    try std.testing.expect(startAttachmentFinalFlatSpanSuppressed(&template, 2, flat, flat));
}

fn expectTexturedVertex(
    actual: TexturedVertex,
    expected_position: rl.Vector3,
    expected_u: f32,
    expected_v: f32,
) !void {
    try std.testing.expectApproxEqAbs(expected_position.x, actual.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(expected_position.y, actual.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(expected_position.z, actual.position.z, 0.0001);
    try std.testing.expectApproxEqAbs(expected_u, actual.u, 0.0001);
    try std.testing.expectApproxEqAbs(expected_v, actual.v, 0.0001);
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
