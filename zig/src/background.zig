const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const assets = @import("assets.zig");
const archive = @import("archive.zig");
const render_blend = @import("render_blend.zig");
const resource_store = @import("resource_store.zig");

const original_screen_width: f32 = 640.0;
const original_screen_height: f32 = 480.0;
const warp_grid_width = 8;
const warp_grid_height = 8;
const warp_vertex_count = warp_grid_width * warp_grid_height;
const warp_cell_width = original_screen_width / @as(f32, @floatFromInt(warp_grid_width - 1));
const warp_cell_height = original_screen_height / @as(f32, @floatFromInt(warp_grid_height - 1));
const warp_u_span: f32 = 0.625;
const warp_v_span: f32 = 0.9375;
const tau: f32 = std.math.pi * 2.0;
const frontend_random_range: u32 = 0x8000;
const frontend_random_center: f32 = 16384.0;
const frontend_random_unit_scale: f32 = 1.0 / frontend_random_center;
const warp_min_cycle_seconds: f32 = 3.0;
const warp_max_cycle_seconds: f32 = 5.0;
const light_streak_count = 36;
const light_streak_fade_step: f32 = 1.0 / 12.0;
const light_streak_max_progress: f32 = 35.0;
const light_streak_progress_bias: f32 = 2.0;
const light_streak_reset_distance: f32 = 10.0;
const light_streak_length_scale: f32 = 0.0114285713;
const light_streak_sprite_half_size: f32 = 0.8;
const light_streak_projection_near: f32 = 0.3;
const light_streak_projection_distance: f32 = 50.0;
const light_streak_base_color = rl.Color{ .r = 204, .g = 204, .b = 255, .a = 102 };
const light_streak_random_seed: u64 = 0x534d5f5354415253;
const default_light_streak_camera = LightStreakCamera{
    .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    .right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    .forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    .fov_degrees = 38.0,
};
pub const light_streak_sprite_path = "SPRITES/STARTAIL.TGA";

pub const Rgb = struct {
    r: u8,
    g: u8,
    b: u8,
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    id: i32,
    fog: Rgb,
    picture: []const u8,
    landscape: ?[]const u8,
    distort: f32,

    pub fn deinit(self: *Definition) void {
        self.arena.deinit();
    }

    pub fn fogColor(self: *const Definition) rl.Color {
        return .{
            .r = self.fog.r,
            .g = self.fog.g,
            .b = self.fog.b,
            .a = 255,
        };
    }
};

pub const Layout = struct {
    x: f32,
    y: f32,
    width: f32,
    height: f32,
    scale: f32,

    pub fn mapPoint(self: Layout, local_x: f32, local_y: f32) rl.Vector2 {
        return .{
            .x = self.x + local_x * self.scale,
            .y = self.y + local_y * self.scale,
        };
    }

    pub fn mapRect(self: Layout, local_x: f32, local_y: f32, local_width: f32, local_height: f32) rl.Rectangle {
        return .{
            .x = self.x + local_x * self.scale,
            .y = self.y + local_y * self.scale,
            .width = local_width * self.scale,
            .height = local_height * self.scale,
        };
    }
};

pub const Loaded = struct {
    definition: Definition,
    primary_texture: assets.LoadedTexture,
    secondary_texture: ?assets.LoadedTexture = null,

    pub fn loadByPath(
        allocator: std.mem.Allocator,
        store: *resource_store.Store,
        script_path: []const u8,
    ) !Loaded {
        const entry = store.catalog.dat.entryByPath(script_path) orelse return error.EntryNotFound;
        return loadFromEntry(allocator, store, entry);
    }

    pub fn loadFromEntry(
        allocator: std.mem.Allocator,
        store: *resource_store.Store,
        entry: archive.Entry,
    ) !Loaded {
        const decoded = try store.catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        var definition = try parseText(allocator, decoded, entry.path);
        errdefer definition.deinit();

        var textures = try loadTexturesForPicture(store, definition.source_path, definition.picture);
        errdefer textures.deinit();

        return .{
            .definition = definition,
            .primary_texture = textures.primary_texture,
            .secondary_texture = textures.secondary_texture,
        };
    }

    pub fn deinit(self: *Loaded) void {
        if (self.secondary_texture) |*texture| {
            texture.unload();
            self.secondary_texture = null;
        }
        self.primary_texture.unload();
        self.definition.deinit();
    }

    pub fn fogColor(self: *const Loaded) rl.Color {
        return self.definition.fogColor();
    }

    pub fn baseWidth(self: *const Loaded) f32 {
        const secondary_width = if (self.secondary_texture) |texture|
            @as(f32, @floatFromInt(texture.texture.width))
        else
            0.0;
        return @as(f32, @floatFromInt(self.primary_texture.texture.width)) + secondary_width;
    }

    pub fn baseHeight(self: *const Loaded) f32 {
        const primary_height = @as(f32, @floatFromInt(self.primary_texture.texture.height));
        const secondary_height = if (self.secondary_texture) |texture|
            @as(f32, @floatFromInt(texture.texture.height))
        else
            0.0;
        return @max(primary_height, secondary_height);
    }

    pub fn fittedLayout(self: *const Loaded, bounds: rl.Rectangle) Layout {
        const base_width = self.baseWidth();
        const base_height = self.baseHeight();
        const scale = @min(bounds.width / base_width, bounds.height / base_height);
        const width = base_width * scale;
        const height = base_height * scale;
        return .{
            .x = bounds.x + (bounds.width - width) * 0.5,
            .y = bounds.y + (bounds.height - height) * 0.5,
            .width = width,
            .height = height,
            .scale = scale,
        };
    }

    pub fn draw(self: *const Loaded, bounds: rl.Rectangle) Layout {
        rl.drawRectangleRec(bounds, self.fogColor());

        const layout = self.fittedLayout(bounds);
        const primary_width = @as(f32, @floatFromInt(self.primary_texture.texture.width));
        const primary_height = @as(f32, @floatFromInt(self.primary_texture.texture.height));
        drawTextureScaled(self.primary_texture.texture, layout.x, layout.y, primary_width * layout.scale, primary_height * layout.scale);

        if (self.secondary_texture) |texture| {
            const secondary_width = @as(f32, @floatFromInt(texture.texture.width));
            const secondary_height = @as(f32, @floatFromInt(texture.texture.height));
            drawTextureScaled(texture.texture, layout.x + primary_width * layout.scale, layout.y, secondary_width * layout.scale, secondary_height * layout.scale);
        }

        return layout;
    }

    pub fn drawAuthored(self: *const Loaded, bounds: rl.Rectangle) Layout {
        rl.drawRectangleRec(bounds, self.fogColor());

        const layout = authoredViewportLayout(bounds);
        const primary_width = @as(f32, @floatFromInt(self.primary_texture.texture.width));
        const primary_height = @as(f32, @floatFromInt(self.primary_texture.texture.height));
        drawTextureScaled(self.primary_texture.texture, layout.x, layout.y, primary_width * layout.scale, primary_height * layout.scale);

        if (self.secondary_texture) |texture| {
            const secondary_width = @as(f32, @floatFromInt(texture.texture.width));
            const secondary_height = @as(f32, @floatFromInt(texture.texture.height));
            drawTextureScaled(texture.texture, layout.x + primary_width * layout.scale, layout.y, secondary_width * layout.scale, secondary_height * layout.scale);
        }

        return layout;
    }

    pub fn drawStretched(self: *const Loaded, bounds: rl.Rectangle) void {
        rl.drawRectangleRec(bounds, self.fogColor());

        const base_width = self.baseWidth();
        const base_height = self.baseHeight();
        if (base_width <= 0.0 or base_height <= 0.0) return;

        const scale_x = bounds.width / base_width;
        const scale_y = bounds.height / base_height;
        const primary_width = @as(f32, @floatFromInt(self.primary_texture.texture.width));
        const primary_height = @as(f32, @floatFromInt(self.primary_texture.texture.height));
        drawTextureScaled(self.primary_texture.texture, bounds.x, bounds.y, primary_width * scale_x, primary_height * scale_y);

        if (self.secondary_texture) |texture| {
            const secondary_width = @as(f32, @floatFromInt(texture.texture.width));
            const secondary_height = @as(f32, @floatFromInt(texture.texture.height));
            drawTextureScaled(texture.texture, bounds.x + primary_width * scale_x, bounds.y, secondary_width * scale_x, secondary_height * scale_y);
        }
    }
};

pub const Runtime = struct {
    use_split_draw: bool,
    distort_amount: f32,
    flipped_uvs: bool = false,
    warp_vertices: [warp_vertex_count]WarpVertex,

    pub fn init(loaded: *const Loaded) Runtime {
        var runtime = Runtime{
            .use_split_draw = loaded.secondary_texture != null,
            .distort_amount = loaded.definition.distort,
            .warp_vertices = undefined,
        };
        runtime.reset(loaded);
        return runtime;
    }

    pub fn reset(self: *Runtime, loaded: *const Loaded) void {
        self.use_split_draw = loaded.secondary_texture != null;
        self.distort_amount = loaded.definition.distort;
        self.flipped_uvs = false;
        initializeWarpVertices(&self.warp_vertices, runtimeSeedForSourcePath(loaded.definition.source_path), self.distort_amount);
    }

    pub fn update(self: *Runtime) void {
        if (self.use_split_draw) return;

        for (&self.warp_vertices) |*vertex| {
            vertex.phase += vertex.phase_step;
            if (vertex.phase >= tau) {
                vertex.phase -= tau;
            }
            vertex.offset_x = @sin(vertex.phase) * vertex.amplitude_x;
            vertex.offset_y = @cos(vertex.phase) * vertex.amplitude_y;
        }
    }

    pub fn draw(self: *const Runtime, loaded: *const Loaded, bounds: rl.Rectangle) Layout {
        if (self.use_split_draw) {
            return loaded.drawAuthored(bounds);
        }

        rl.drawRectangleRec(bounds, loaded.fogColor());
        const layout = authoredViewportLayout(bounds);
        drawWarpedTexture(loaded.primary_texture.texture, layout, &self.warp_vertices, self.flipped_uvs);
        return layout;
    }

    pub fn drawStretched(self: *const Runtime, loaded: *const Loaded, bounds: rl.Rectangle) void {
        if (self.use_split_draw) {
            loaded.drawStretched(bounds);
            return;
        }

        rl.drawRectangleRec(bounds, loaded.fogColor());
        drawWarpedTexture(loaded.primary_texture.texture, authoredViewportLayout(bounds), &self.warp_vertices, self.flipped_uvs);
    }
};

pub const LightStreakCamera = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    fov_degrees: f32,
};

pub const LightStreakDrawMode = enum {
    automatic,
    textured,
    lines,
};

pub const LightStreakDrawOptions = struct {
    mode: LightStreakDrawMode = .automatic,
    alpha_multiplier: f32 = 1.0,
    size_multiplier: f32 = 1.0,
    stretch_multiplier: f32 = 1.0,
    draw_debug_centers: bool = false,
    draw_debug_quads: bool = false,
};

pub const LightStreakDrawStats = struct {
    total_entries: usize = 0,
    alpha_visible_entries: usize = 0,
    center_projected_entries: usize = 0,
    drawn_entries: usize = 0,
    average_alpha: f32 = 0.0,
    max_alpha: f32 = 0.0,
    average_stretch: f32 = 0.0,
};

const LightStreakState = enum {
    dormant,
    visible,
    fade_in,
    fade_out,
};

const LightStreakEntry = struct {
    sprite_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    direction: rl.Vector3 = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    speed: f32 = 0.0,
    progress: f32 = 0.0,
    size: f32 = 0.4,
};

const LightStreakScenePacket = struct {
    current: rl.Vector3,
    motion_delta: rl.Vector3,
};

pub const LightStreakController = struct {
    entries: [light_streak_count]LightStreakEntry = [_]LightStreakEntry{.{}} ** light_streak_count,
    state: LightStreakState = .dormant,
    fade: f32 = 0.0,
    fade_step: f32 = light_streak_fade_step,
    random_state: u64 = light_streak_random_seed,

    pub fn init() LightStreakController {
        return .{};
    }

    pub fn update(self: *LightStreakController, camera: LightStreakCamera, visible_requested: bool) void {
        switch (self.state) {
            .dormant => {
                if (!visible_requested) return;
                self.initialize(camera);
                self.state = .fade_in;
                self.fade = 0.0;
                self.fade_step = light_streak_fade_step;
                self.updatePositions(camera, 0.0);
            },
            .visible => {
                self.updatePositions(camera, 1.0);
                if (!visible_requested) {
                    self.fade = 1.0;
                    self.fade_step = light_streak_fade_step;
                    self.state = .fade_out;
                }
            },
            .fade_in => {
                self.updatePositions(camera, self.fade);
                if (!visible_requested) {
                    self.state = .fade_out;
                }
                self.fade += self.fade_step;
                if (self.fade >= 1.0) {
                    self.fade = 1.0;
                    self.state = .visible;
                }
            },
            .fade_out => {
                self.updatePositions(camera, self.fade);
                if (visible_requested) {
                    self.state = .fade_in;
                    return;
                }
                self.fade -= self.fade_step;
                if (self.fade < 0.0) {
                    self.fade = 0.0;
                    self.state = .dormant;
                }
            },
        }
    }

    pub fn draw(self: *const LightStreakController, bounds: rl.Rectangle, camera: LightStreakCamera, texture: ?rl.Texture2D) void {
        _ = self.drawWithOptions(bounds, camera, texture, .{});
    }

    pub fn drawWithOptions(
        self: *const LightStreakController,
        bounds: rl.Rectangle,
        camera: LightStreakCamera,
        texture: ?rl.Texture2D,
        options: LightStreakDrawOptions,
    ) LightStreakDrawStats {
        if (self.state == .dormant) return .{};
        const layout = authoredViewportLayout(bounds);
        return self.drawInViewport(layout, camera, texture, options);
    }

    pub fn debugFade(self: *const LightStreakController) f32 {
        return self.fade;
    }

    pub fn debugStateLabel(self: *const LightStreakController) []const u8 {
        return switch (self.state) {
            .dormant => "dormant",
            .fade_in => "fade_in",
            .visible => "visible",
            .fade_out => "fade_out",
        };
    }

    fn drawInViewport(
        self: *const LightStreakController,
        layout: Layout,
        camera: LightStreakCamera,
        texture: ?rl.Texture2D,
        options: LightStreakDrawOptions,
    ) LightStreakDrawStats {
        var alpha_sum: f32 = 0.0;
        var stretch_sum: f32 = 0.0;
        var stats: LightStreakDrawStats = .{};
        const viewport = rectFromLayout(layout);
        if (viewport.width <= 0.0 or viewport.height <= 0.0) return stats;

        render_blend.beginAlphaPreservingFramebufferAlpha();
        defer rl.endBlendMode();

        for (self.entries) |entry| {
            stats.total_entries += 1;
            const scene_packet = lightStreakScenePacket(camera, entry.sprite_position, entry.direction);

            const alpha_scale = std.math.clamp(
                lightStreakAlphaScale(entry, self.fade) * @max(options.alpha_multiplier, 0.0),
                0.0,
                1.0,
            );
            if (alpha_scale <= 0.0) continue;
            stats.alpha_visible_entries += 1;
            alpha_sum += alpha_scale;
            stats.max_alpha = @max(stats.max_alpha, alpha_scale);

            const sprite_screen = projectScenePointToViewport(viewport, camera, scene_packet.current) orelse continue;
            stats.center_projected_entries += 1;
            if (options.draw_debug_centers) {
                drawLightStreakDebugMarker(sprite_screen);
            }
            const color = lightStreakTint(alpha_scale);
            if (color.a == 0) continue;

            const authored_half_size = light_streak_sprite_half_size * @max(options.size_multiplier, 0.0);
            const stretch = lightStreakSpriteStretch(entry) * @max(options.stretch_multiplier, 0.0);
            if (authored_half_size <= 0.0 or stretch <= 0.0) continue;
            stretch_sum += stretch;

            const draw_mode = switch (options.mode) {
                .automatic => if (texture != null) LightStreakDrawMode.textured else .lines,
                else => options.mode,
            };

            const drew = switch (draw_mode) {
                .textured => if (texture) |sprite_texture|
                    drawLightStreakSprite(
                        sprite_texture,
                        viewport,
                        camera,
                        scene_packet,
                        authored_half_size,
                        stretch,
                        color,
                        options.draw_debug_quads,
                    )
                else
                    false,
                .lines => drawLightStreakLine(
                    viewport,
                    camera,
                    scene_packet,
                    authored_half_size,
                    stretch,
                    color,
                ),
                .automatic => unreachable,
            };
            if (drew) {
                stats.drawn_entries += 1;
            }
        }

        if (stats.alpha_visible_entries > 0) {
            stats.average_alpha = alpha_sum / @as(f32, @floatFromInt(stats.alpha_visible_entries));
            stats.average_stretch = stretch_sum / @as(f32, @floatFromInt(stats.alpha_visible_entries));
        }
        return stats;
    }

    fn initialize(self: *LightStreakController, camera: LightStreakCamera) void {
        for (&self.entries, 0..) |*entry, index| {
            self.seedEntry(entry, camera, index == 0);
        }
    }

    fn seedEntry(self: *LightStreakController, entry: *LightStreakEntry, camera: LightStreakCamera, first: bool) void {
        const size = if (first)
            0.40000001
        else
            ((@as(f32, @floatFromInt(self.nextRandom15())) - frontend_random_center) * 0.0000061035157) + 0.40000001;
        const initial_progress = @as(f32, @floatFromInt(self.nextRandom15())) * 0.0010681152;
        self.resetEntry(entry, camera, size, initial_progress);
    }

    fn resetEntry(self: *LightStreakController, entry: *LightStreakEntry, camera: LightStreakCamera, size: f32, progress: f32) void {
        const random_x = (@as(f32, @floatFromInt(self.nextRandom15())) - frontend_random_center) * frontend_random_unit_scale;
        const random_y = (@as(f32, @floatFromInt(self.nextRandom15())) - frontend_random_center) * frontend_random_unit_scale;
        const speed = @as(f32, @floatFromInt(self.nextRandom15())) * 0.000018310548 + 0.30000001;
        const plane_direction = normalizeVector3(addVector3(
            scaleVector3(camera.right, random_x),
            scaleVector3(camera.up, random_y),
        ));

        entry.* = .{
            .sprite_position = addVector3(cameraOrigin(camera), scaleVector3(plane_direction, progress)),
            .direction = scaleVector3(plane_direction, speed),
            .speed = speed,
            .progress = progress,
            .size = size,
        };
    }

    fn updatePositions(self: *LightStreakController, camera: LightStreakCamera, fade: f32) void {
        _ = fade;
        for (&self.entries) |*entry| {
            entry.sprite_position = addVector3(entry.sprite_position, entry.direction);
            entry.progress += entry.speed;
            if (entry.progress > light_streak_max_progress) {
                const size = entry.size;
                const reset_progress = entry.speed * light_streak_reset_distance;
                self.resetEntry(entry, camera, size, reset_progress);
            }
        }
    }

    fn nextRandom15(self: *LightStreakController) u32 {
        self.random_state = (self.random_state *% 1103515245) +% 12345;
        return @intCast((self.random_state >> 16) & 0x7fff);
    }
};

fn drawLightStreakLine(
    viewport: rl.Rectangle,
    camera: LightStreakCamera,
    scene_packet: LightStreakScenePacket,
    authored_half_size: f32,
    stretch: f32,
    tint: rl.Color,
) bool {
    const current_screen = projectScenePointToViewport(viewport, camera, scene_packet.current) orelse return false;
    const local_points = lightStreakQuadLocalPoints(scene_packet.motion_delta, authored_half_size, stretch);
    const tail_scene = addVector3(scene_packet.current, .{
        .x = local_points[3].x,
        .y = local_points[3].y,
        .z = 0.0,
    });
    const tail_screen = projectScenePointToViewport(viewport, camera, tail_scene) orelse return false;
    rl.drawLineEx(current_screen, tail_screen, authored_half_size * 2.0, tint);
    return true;
}

fn projectLightStreakSpriteQuad(
    viewport: rl.Rectangle,
    camera: LightStreakCamera,
    scene_packet: LightStreakScenePacket,
    authored_half_size: f32,
    stretch: f32,
) ?[4]rl.Vector2 {
    const local_points = lightStreakQuadLocalPoints(scene_packet.motion_delta, authored_half_size, stretch);
    const v0_scene = addVector3(scene_packet.current, .{ .x = local_points[0].x, .y = local_points[0].y, .z = 0.0 });
    const v1_scene = addVector3(scene_packet.current, .{ .x = local_points[1].x, .y = local_points[1].y, .z = 0.0 });
    const v2_scene = addVector3(scene_packet.current, .{ .x = local_points[2].x, .y = local_points[2].y, .z = 0.0 });
    const v3_scene = addVector3(scene_packet.current, .{ .x = local_points[3].x, .y = local_points[3].y, .z = 0.0 });
    return .{
        projectScenePointToViewport(viewport, camera, v0_scene) orelse return null,
        projectScenePointToViewport(viewport, camera, v1_scene) orelse return null,
        projectScenePointToViewport(viewport, camera, v2_scene) orelse return null,
        projectScenePointToViewport(viewport, camera, v3_scene) orelse return null,
    };
}

fn drawLightStreakSprite(
    texture: rl.Texture2D,
    viewport: rl.Rectangle,
    camera: LightStreakCamera,
    scene_packet: LightStreakScenePacket,
    authored_half_size: f32,
    stretch: f32,
    tint: rl.Color,
    draw_debug_quad: bool,
) bool {
    const quad = projectLightStreakSpriteQuad(
        viewport,
        camera,
        scene_packet,
        authored_half_size,
        stretch,
    ) orelse return false;

    const v0 = quad[0];
    const v1 = quad[1];
    const v2 = quad[2];
    const v3 = quad[3];

    rlgl.rlDrawRenderBatchActive();
    rlgl.rlSetTexture(texture.id);
    defer rlgl.rlSetTexture(0);

    rlgl.rlBegin(rlgl.rl_quads);

    // Native `draw_sprite_quad` builds the four corners in scene space and hands
    // them to D3D with the native winding. In the raylib 2D path that same visual
    // quad needs the reversed point order to survive the active front-face state,
    // while still preserving the original per-corner UVs.
    rlgl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    inline for (&[_]struct { uv: rl.Vector2, point: rl.Vector2 }{
        .{ .uv = .{ .x = 0.0, .y = 1.0 }, .point = v3 },
        .{ .uv = .{ .x = 1.0, .y = 1.0 }, .point = v2 },
        .{ .uv = .{ .x = 1.0, .y = 0.0 }, .point = v1 },
        .{ .uv = .{ .x = 0.0, .y = 0.0 }, .point = v0 },
    }) |vertex| {
        rlgl.rlTexCoord2f(vertex.uv.x, vertex.uv.y);
        rlgl.rlVertex3f(vertex.point.x, vertex.point.y, 0.0);
    }
    rlgl.rlEnd();
    rlgl.rlDrawRenderBatchActive();

    if (draw_debug_quad) {
        drawLightStreakDebugQuad(v0, v1, v2, v3);
    }
    return true;
}

fn drawLightStreakDebugMarker(center: rl.Vector2) void {
    const marker_color = rl.Color{ .r = 255, .g = 160, .b = 32, .a = 220 };
    rl.drawCircleV(center, 2.5, marker_color);
    rl.drawLineEx(
        .{ .x = center.x - 5.0, .y = center.y },
        .{ .x = center.x + 5.0, .y = center.y },
        1.0,
        marker_color,
    );
    rl.drawLineEx(
        .{ .x = center.x, .y = center.y - 5.0 },
        .{ .x = center.x, .y = center.y + 5.0 },
        1.0,
        marker_color,
    );
}

fn drawLightStreakDebugQuad(v0: rl.Vector2, v1: rl.Vector2, v2: rl.Vector2, v3: rl.Vector2) void {
    const outline_color = rl.Color{ .r = 64, .g = 220, .b = 255, .a = 220 };
    rl.drawLineEx(v0, v1, 1.0, outline_color);
    rl.drawLineEx(v1, v2, 1.0, outline_color);
    rl.drawLineEx(v2, v3, 1.0, outline_color);
    rl.drawLineEx(v3, v0, 1.0, outline_color);
}

const LoadedTextures = struct {
    primary_texture: assets.LoadedTexture,
    secondary_texture: ?assets.LoadedTexture = null,

    fn deinit(self: *@This()) void {
        if (self.secondary_texture) |*texture| {
            texture.unload();
            self.secondary_texture = null;
        }
        self.primary_texture.unload();
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

    var id: ?i32 = null;
    var fog: ?Rgb = null;
    var picture: ?[]const u8 = null;
    var landscape: ?[]const u8 = null;
    var distort: ?f32 = null;

    var lines = std.mem.splitScalar(u8, data, '\n');
    var scratch: [4096]u8 = undefined;
    while (lines.next()) |raw_line| {
        const line = try stripInlineComments(raw_line, &scratch);
        if (line.len == 0) continue;

        const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse continue;
        const key = std.mem.trim(u8, line[0..colon_index], " \t");
        const value = std.mem.trim(u8, line[colon_index + 1 ..], " \t");

        const field = parseField(key) orelse return error.UnsupportedBackgroundField;
        switch (field) {
            .id => id = try std.fmt.parseInt(i32, value, 10),
            .fog => fog = try parseRgb(value),
            .picture => picture = try arena_allocator.dupe(u8, value),
            .landscape => landscape = if (value.len == 0) null else try arena_allocator.dupe(u8, value),
            .distort => distort = try std.fmt.parseFloat(f32, value),
        }
    }

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .id = id orelse return error.MissingBackgroundId,
        .fog = fog orelse return error.MissingBackgroundFog,
        .picture = picture orelse return error.MissingBackgroundPicture,
        .landscape = landscape,
        .distort = distort orelse return error.MissingBackgroundDistort,
    };
}

const Field = enum {
    id,
    fog,
    picture,
    landscape,
    distort,
};

fn loadTexturesForPicture(
    store: *resource_store.Store,
    source_path: []const u8,
    picture: []const u8,
) !LoadedTextures {
    const directory = directoryPrefix(source_path);
    const stem = pictureStem(picture);

    var split_a_buffer: [std.fs.max_path_bytes]u8 = undefined;
    var split_b_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const split_a_path = try std.fmt.bufPrint(&split_a_buffer, "{s}{s}_A.TGA", .{ directory, stem });
    const split_b_path = try std.fmt.bufPrint(&split_b_buffer, "{s}{s}_B.TGA", .{ directory, stem });

    if (store.catalog.findTextureEntry(split_a_path) != null and store.catalog.findTextureEntry(split_b_path) != null) {
        var primary_texture = try store.texture(split_a_path);
        errdefer primary_texture.unload();
        const secondary_texture = try store.texture(split_b_path);
        return .{
            .primary_texture = primary_texture,
            .secondary_texture = secondary_texture,
        };
    }

    var picture_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const picture_path = try std.fmt.bufPrint(&picture_buffer, "{s}{s}", .{ directory, picture });
    if (store.catalog.findTextureEntry(picture_path) != null) {
        return .{
            .primary_texture = try store.texture(picture_path),
        };
    }

    if (store.catalog.findTextureEntry(split_a_path) != null) {
        return .{
            .primary_texture = try store.texture(split_a_path),
        };
    }

    return error.EntryNotFound;
}

fn drawTextureScaled(texture: rl.Texture2D, x: f32, y: f32, width: f32, height: f32) void {
    rl.drawTexturePro(
        texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(texture.width),
            .height = @floatFromInt(texture.height),
        },
        .{
            .x = x,
            .y = y,
            .width = width,
            .height = height,
        },
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        .white,
    );
}

const WarpVertex = struct {
    phase: f32,
    phase_step: f32,
    amplitude_x: f32,
    amplitude_y: f32,
    offset_x: f32,
    offset_y: f32,
};

fn authoredViewportLayout(bounds: rl.Rectangle) Layout {
    const scale = @min(bounds.width / original_screen_width, bounds.height / original_screen_height);
    const width = original_screen_width * scale;
    const height = original_screen_height * scale;
    return .{
        .x = bounds.x + (bounds.width - width) * 0.5,
        .y = bounds.y + (bounds.height - height) * 0.5,
        .width = width,
        .height = height,
        .scale = scale,
    };
}

fn runtimeSeedForSourcePath(source_path: []const u8) u64 {
    // PORT(partial): the original backdrop grid pulls fresh random phases and amplitudes
    // from the shared frontend RNG. The port now matches the recovered integer-to-float
    // distortion math, but still seeds deterministically by source path so captures stay
    // stable across runs.
    var hasher = std.hash.Wyhash.init(0);
    hasher.update(source_path);
    return hasher.final();
}

fn initializeWarpVertices(vertices: *[warp_vertex_count]WarpVertex, seed: u64, distort_amount: f32) void {
    var prng = std.Random.DefaultPrng.init(seed);
    const random = prng.random();

    for (0..warp_grid_height) |row| {
        for (0..warp_grid_width) |col| {
            const vertex = &vertices[row * warp_grid_width + col];
            if (row == 0 or col == 0 or row == warp_grid_height - 1 or col == warp_grid_width - 1) {
                vertex.* = .{
                    .phase = 0.0,
                    .phase_step = 0.0,
                    .amplitude_x = 0.0,
                    .amplitude_y = 0.0,
                    .offset_x = 0.0,
                    .offset_y = 0.0,
                };
                continue;
            }

            const phase_sample = @as(f32, @floatFromInt(random.intRangeLessThan(u32, 0, frontend_random_range)));
            const step_sample = @as(f32, @floatFromInt(random.intRangeLessThan(u32, 0, frontend_random_range)));
            const amplitude_x_sample = @as(f32, @floatFromInt(random.intRangeLessThan(u32, 0, frontend_random_range)));
            const amplitude_y_sample = @as(f32, @floatFromInt(random.intRangeLessThan(u32, 0, frontend_random_range)));

            const phase = phase_sample * (tau / @as(f32, @floatFromInt(frontend_random_range)));
            const phase_step = tau / (((step_sample * frontend_random_unit_scale) + warp_min_cycle_seconds) * 60.0);
            const amplitude_x = (amplitude_x_sample - frontend_random_center) * distort_amount * frontend_random_unit_scale;
            const amplitude_y = (amplitude_y_sample - frontend_random_center) * distort_amount * frontend_random_unit_scale;
            vertex.* = .{
                .phase = phase,
                .phase_step = phase_step,
                .amplitude_x = amplitude_x,
                .amplitude_y = amplitude_y,
                .offset_x = @sin(phase) * amplitude_x,
                .offset_y = @cos(phase) * amplitude_y,
            };
        }
    }
}

fn drawWarpedTexture(
    texture: rl.Texture2D,
    layout: Layout,
    vertices: *const [warp_vertex_count]WarpVertex,
    flipped_uvs: bool,
) void {
    if (texture.width <= 0 or texture.height <= 0) return;

    rlgl.rlSetTexture(texture.id);
    defer rlgl.rlSetTexture(0);

    rlgl.rlBegin(rlgl.rl_quads);
    rlgl.rlColor4ub(255, 255, 255, 255);

    for (0..warp_grid_height - 1) |row| {
        for (0..warp_grid_width - 1) |col| {
            const top_left = warpVertexPoint(layout, vertices, row, col);
            const top_right = warpVertexPoint(layout, vertices, row + 1, col);
            const bottom_right = warpVertexPoint(layout, vertices, row + 1, col + 1);
            const bottom_left = warpVertexPoint(layout, vertices, row, col + 1);

            const uvs = warpCellUvBounds(row, col, flipped_uvs);

            rlgl.rlTexCoord2f(uvs.left, uvs.top);
            rlgl.rlVertex2f(top_left.x, top_left.y);

            rlgl.rlTexCoord2f(uvs.left, uvs.bottom);
            rlgl.rlVertex2f(bottom_left.x, bottom_left.y);

            rlgl.rlTexCoord2f(uvs.right, uvs.bottom);
            rlgl.rlVertex2f(bottom_right.x, bottom_right.y);

            rlgl.rlTexCoord2f(uvs.right, uvs.top);
            rlgl.rlVertex2f(top_right.x, top_right.y);
        }
    }
    rlgl.rlEnd();
    rlgl.rlDrawRenderBatchActive();
}

const WarpCellUvBounds = struct {
    left: f32,
    right: f32,
    top: f32,
    bottom: f32,
};

fn warpVertexPoint(
    layout: Layout,
    vertices: *const [warp_vertex_count]WarpVertex,
    row: usize,
    col: usize,
) rl.Vector2 {
    const vertex = vertices[row * warp_grid_width + col];
    return .{
        .x = layout.x + (@as(f32, @floatFromInt(row)) * warp_cell_width + vertex.offset_x) * layout.scale,
        .y = layout.y + (@as(f32, @floatFromInt(col)) * warp_cell_height + vertex.offset_y) * layout.scale,
    };
}

fn warpCellUvBounds(row: usize, col: usize, flipped_uvs: bool) WarpCellUvBounds {
    const u_step = warp_u_span / @as(f32, @floatFromInt(warp_grid_width - 1));
    const v_step = warp_v_span / @as(f32, @floatFromInt(warp_grid_height - 1));
    const left_u = @as(f32, @floatFromInt(row)) * u_step;
    const right_u = @as(f32, @floatFromInt(row + 1)) * u_step;
    const top_v = @as(f32, @floatFromInt(col)) * v_step;
    const bottom_v = @as(f32, @floatFromInt(col + 1)) * v_step;
    if (!flipped_uvs) {
        return .{
            .left = left_u,
            .right = right_u,
            .top = top_v,
            .bottom = bottom_v,
        };
    }

    return .{
        .left = 0.8 - right_u,
        .right = 0.8 - left_u,
        .top = top_v,
        .bottom = bottom_v,
    };
}

fn directoryPrefix(path: []const u8) []const u8 {
    const slash_index = std.mem.lastIndexOfScalar(u8, path, '/') orelse return "";
    return path[0 .. slash_index + 1];
}

fn pictureStem(path: []const u8) []const u8 {
    const dot_index = std.mem.lastIndexOfScalar(u8, path, '.') orelse return path;
    return path[0..dot_index];
}

fn parseField(key: []const u8) ?Field {
    if (std.ascii.eqlIgnoreCase(key, "ID")) return .id;
    if (std.ascii.eqlIgnoreCase(key, "Fog")) return .fog;
    if (std.ascii.eqlIgnoreCase(key, "Picture")) return .picture;
    if (std.ascii.eqlIgnoreCase(key, "Landscape")) return .landscape;
    if (std.ascii.eqlIgnoreCase(key, "Distort")) return .distort;
    return null;
}

fn stripInlineComments(line: []const u8, scratch: []u8) ![]const u8 {
    var out_index: usize = 0;
    var index: usize = 0;
    while (index < line.len) {
        if (index + 1 < line.len and line[index] == '/' and line[index + 1] == '*') {
            index += 2;
            while (index + 1 < line.len and !(line[index] == '*' and line[index + 1] == '/')) : (index += 1) {}
            if (index + 1 < line.len) {
                index += 2;
            } else {
                break;
            }
            continue;
        }

        if (out_index >= scratch.len) return error.LineTooLong;
        scratch[out_index] = line[index];
        out_index += 1;
        index += 1;
    }

    return std.mem.trim(u8, scratch[0..out_index], " \t\r");
}

fn parseRgb(value: []const u8) !Rgb {
    if (value.len < 7 or value[0] != '(' or value[value.len - 1] != ')') {
        return error.InvalidBackgroundRgb;
    }

    var parts = std.mem.splitScalar(u8, value[1 .. value.len - 1], ',');
    const r = try parseRgbComponent(parts.next() orelse return error.InvalidBackgroundRgb);
    const g = try parseRgbComponent(parts.next() orelse return error.InvalidBackgroundRgb);
    const b = try parseRgbComponent(parts.next() orelse return error.InvalidBackgroundRgb);
    if (parts.next() != null) return error.InvalidBackgroundRgb;

    return .{ .r = r, .g = g, .b = b };
}

fn parseRgbComponent(value: []const u8) !u8 {
    const parsed = try std.fmt.parseInt(i32, std.mem.trim(u8, value, " \t"), 10);
    if (parsed < 0 or parsed > 255) return error.InvalidBackgroundRgb;
    return @intCast(parsed);
}

fn rectFromLayout(layout: Layout) rl.Rectangle {
    return .{
        .x = layout.x,
        .y = layout.y,
        .width = layout.width,
        .height = layout.height,
    };
}

fn addVector3(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
    };
}

fn subVector3(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
    };
}

fn scaleVector3(value: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{
        .x = value.x * scalar,
        .y = value.y * scalar,
        .z = value.z * scalar,
    };
}

fn dotVector3(lhs: rl.Vector3, rhs: rl.Vector3) f32 {
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

fn vectorLengthSquared(value: rl.Vector3) f32 {
    return dotVector3(value, value);
}

fn vectorLength(value: rl.Vector3) f32 {
    return @sqrt(vectorLengthSquared(value));
}

fn normalizeVector3(value: rl.Vector3) rl.Vector3 {
    const length = vectorLength(value);
    if (length <= 0.000001) {
        return .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    }
    return scaleVector3(value, 1.0 / length);
}

fn cameraOrigin(camera: LightStreakCamera) rl.Vector3 {
    return addVector3(camera.position, scaleVector3(camera.forward, light_streak_projection_distance));
}

fn worldPointToLightStreakScene(camera: LightStreakCamera, point: rl.Vector3) rl.Vector3 {
    const relative = subVector3(point, camera.position);
    return .{
        .x = -dotVector3(relative, camera.right),
        .y = dotVector3(relative, camera.up),
        .z = -dotVector3(relative, camera.forward),
    };
}

fn rotateWorldVectorToLightStreakCamera(camera: LightStreakCamera, vector: rl.Vector3) rl.Vector3 {
    return .{
        .x = dotVector3(vector, camera.right),
        .y = dotVector3(vector, camera.up),
        .z = dotVector3(vector, camera.forward),
    };
}

fn lightStreakScenePacket(camera: LightStreakCamera, current_world: rl.Vector3, velocity_world: rl.Vector3) LightStreakScenePacket {
    return .{
        .current = worldPointToLightStreakScene(camera, current_world),
        .motion_delta = rotateWorldVectorToLightStreakCamera(camera, velocity_world),
    };
}

fn projectScenePointToViewport(viewport: rl.Rectangle, camera: LightStreakCamera, point: rl.Vector3) ?rl.Vector2 {
    const depth = -point.z;
    if (depth <= light_streak_projection_near) return null;

    const focal = (original_screen_height * 0.5) / @tan((camera.fov_degrees * std.math.pi / 180.0) * 0.5);
    const screen_x = (original_screen_width * 0.5) + ((point.x / depth) * focal);
    const screen_y = (original_screen_height * 0.5) - ((point.y / depth) * focal);
    return .{
        .x = viewport.x + (screen_x / original_screen_width) * viewport.width,
        .y = viewport.y + (screen_y / original_screen_height) * viewport.height,
    };
}

fn lightStreakAlphaScale(entry: LightStreakEntry, fade: f32) f32 {
    return @max(0.0, (entry.progress - light_streak_progress_bias) * entry.size * light_streak_length_scale * fade);
}

fn lightStreakSpriteStretch(entry: LightStreakEntry) f32 {
    return (entry.speed + 1.0) * 4.0;
}

fn lightStreakTint(alpha_scale: f32) rl.Color {
    var color = light_streak_base_color;
    color.a = @intFromFloat(std.math.clamp(alpha_scale, 0.0, 1.0) * 255.0);
    return color;
}

fn lightStreakQuadLocalPoints(
    motion_delta_scene: rl.Vector3,
    size: f32,
    stretch: f32,
) [4]rl.Vector2 {
    // `render_game_frame` transforms sprite current and previous positions into
    // scene space, negates scene x/z, then `update_sprite_facing_angle` derives
    // the draw angle from that scene-space motion delta.
    const scene_x = motion_delta_scene.x;
    const scene_y = motion_delta_scene.y;
    const length = @sqrt((scene_x * scene_x) + (scene_y * scene_y));
    if (length <= 0.000001) {
        return .{
            .{ .x = -size, .y = size },
            .{ .x = size, .y = size },
            .{ .x = size, .y = -size },
            .{ .x = -size * stretch, .y = -size * stretch },
        };
    }

    const direction_angle = std.math.atan2(scene_x, scene_y) + (std.math.pi * 0.5);
    const base = size * 1.41400003;
    const cos_term = @cos(direction_angle) * base;
    const sin_term = @sin(direction_angle) * base;
    return .{
        .{ .x = -sin_term, .y = cos_term },
        .{ .x = cos_term, .y = sin_term },
        .{ .x = sin_term, .y = -cos_term },
        .{ .x = -(cos_term * stretch), .y = -(sin_term * stretch) },
    };
}

test "parse background script fields" {
    const text =
        \\/* Background script */
        \\ID:7
        \\Fog:(128,0,128)
        \\Picture:Menubg.tga
        \\Landscape:
        \\Distort:0.3
        \\
    ;
    var definition = try parseText(std.testing.allocator, text, "BACKGROUNDS/MENUBG.TXT");
    defer definition.deinit();

    try std.testing.expectEqual(@as(i32, 7), definition.id);
    try std.testing.expectEqual(@as(u8, 128), definition.fog.r);
    try std.testing.expectEqual(@as(u8, 0), definition.fog.g);
    try std.testing.expectEqual(@as(u8, 128), definition.fog.b);
    try std.testing.expectEqualStrings("Menubg.tga", definition.picture);
    try std.testing.expectEqual(@as(?[]const u8, null), definition.landscape);
    try std.testing.expectApproxEqAbs(@as(f32, 0.3), definition.distort, 0.0001);
}

test "picture helpers preserve directory and extensionless stem" {
    try std.testing.expectEqualStrings("BACKGROUNDS/", directoryPrefix("BACKGROUNDS/MENUBG.TXT"));
    try std.testing.expectEqualStrings("Menubg", pictureStem("Menubg.tga"));
    try std.testing.expectEqualStrings("SpaceRed", pictureStem("SpaceRed"));
}

test "runtime picks warp path for single picture backgrounds" {
    var definition = Definition{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "BACKGROUNDS/SPACERED.TXT",
        .id = 0,
        .fog = .{ .r = 0, .g = 0, .b = 0 },
        .picture = "SpaceRed.tga",
        .landscape = null,
        .distort = 10.0,
    };
    defer definition.deinit();

    const loaded = Loaded{
        .definition = definition,
        .primary_texture = undefined,
        .secondary_texture = null,
    };
    var runtime = Runtime.init(&loaded);
    try std.testing.expect(!runtime.use_split_draw);
    runtime.update();
}

test "runtime keeps split textures on the static draw path" {
    var definition = Definition{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "BACKGROUNDS/MENUBG.TXT",
        .id = 0,
        .fog = .{ .r = 0, .g = 0, .b = 0 },
        .picture = "Menubg.tga",
        .landscape = null,
        .distort = 0.0,
    };
    defer definition.deinit();

    const loaded = Loaded{
        .definition = definition,
        .primary_texture = undefined,
        .secondary_texture = .{
            .path = "",
            .texture = undefined,
        },
    };
    const runtime = Runtime.init(&loaded);
    try std.testing.expect(runtime.use_split_draw);
}

test "distortion grid uses recovered 3-to-5 second timing and bounded amplitudes" {
    var vertices: [warp_vertex_count]WarpVertex = undefined;
    initializeWarpVertices(&vertices, 1234, 0.75);

    const min_phase_step = tau / (warp_max_cycle_seconds * 60.0);
    const max_phase_step = tau / (warp_min_cycle_seconds * 60.0);

    for (0..warp_grid_height) |row| {
        for (0..warp_grid_width) |col| {
            const vertex = vertices[row * warp_grid_width + col];
            const is_border = row == 0 or col == 0 or row == warp_grid_height - 1 or col == warp_grid_width - 1;
            if (is_border) {
                try std.testing.expectEqual(@as(f32, 0.0), vertex.phase);
                try std.testing.expectEqual(@as(f32, 0.0), vertex.phase_step);
                try std.testing.expectEqual(@as(f32, 0.0), vertex.amplitude_x);
                try std.testing.expectEqual(@as(f32, 0.0), vertex.amplitude_y);
                continue;
            }

            try std.testing.expect(vertex.phase >= 0.0 and vertex.phase < tau);
            try std.testing.expect(vertex.phase_step >= min_phase_step);
            try std.testing.expect(vertex.phase_step <= max_phase_step);
            try std.testing.expect(vertex.amplitude_x >= -0.75 and vertex.amplitude_x < 0.75);
            try std.testing.expect(vertex.amplitude_y >= -0.75 and vertex.amplitude_y < 0.75);
        }
    }
}

test "warped backdrop flips horizontal crop only" {
    const normal = warpCellUvBounds(2, 3, false);
    const flipped = warpCellUvBounds(2, 3, true);

    try std.testing.expectApproxEqAbs(@as(f32, 0.8) - normal.right, flipped.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.8) - normal.left, flipped.right, 0.0001);
    try std.testing.expectApproxEqAbs(normal.top, flipped.top, 0.0001);
    try std.testing.expectApproxEqAbs(normal.bottom, flipped.bottom, 0.0001);
}

test "light streak controller fades in from dormant and seeds camera-plane entries" {
    var controller = LightStreakController.init();
    const camera = default_light_streak_camera;

    controller.update(camera, true);

    try std.testing.expectEqual(LightStreakState.fade_in, controller.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), controller.fade, 0.0001);

    for (controller.entries) |entry| {
        try std.testing.expect(entry.speed >= 0.30000001);
        try std.testing.expect(entry.speed < 0.90000004);
        try std.testing.expectApproxEqAbs(@as(f32, 0.0), dotVector3(entry.direction, camera.forward), 0.0001);
        try std.testing.expect(entry.progress >= 0.0);
        try std.testing.expect(entry.progress < light_streak_max_progress);
        try std.testing.expectApproxEqAbs(entry.progress, vectorLength(subVector3(entry.sprite_position, cameraOrigin(camera))), 0.0002);
    }
}

test "light streak controller reaches visible and fades back to dormant" {
    var controller = LightStreakController.init();
    const camera = default_light_streak_camera;

    controller.update(camera, true);
    for (0..13) |_| {
        controller.update(camera, true);
    }
    try std.testing.expectEqual(LightStreakState.visible, controller.state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), controller.fade, 0.0001);

    controller.update(camera, false);
    try std.testing.expectEqual(LightStreakState.fade_out, controller.state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), controller.fade, 0.0001);

    for (0..13) |_| {
        controller.update(camera, false);
    }
    try std.testing.expectEqual(LightStreakState.dormant, controller.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), controller.fade, 0.0001);
}

test "light streak alpha lane and sprite stretch match native formulas" {
    const entry = LightStreakEntry{
        .speed = 0.5,
        .progress = 10.0,
        .size = 0.4,
    };

    try std.testing.expectApproxEqAbs(@as(f32, 0.036571428), lightStreakAlphaScale(entry, 1.0), 0.00001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), lightStreakSpriteStretch(entry), 0.0001);
}

test "light streak tint uses runtime alpha lane rather than setup alpha" {
    const tint = lightStreakTint(0.5);

    try std.testing.expectEqual(light_streak_base_color.r, tint.r);
    try std.testing.expectEqual(light_streak_base_color.g, tint.g);
    try std.testing.expectEqual(light_streak_base_color.b, tint.b);
    try std.testing.expectEqual(@as(u8, 127), tint.a);
}

test "light streak quad local points match native stretched-corner shape" {
    const quad = lightStreakQuadLocalPoints(
        .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        0.8,
        6.0,
    );

    try std.testing.expectApproxEqAbs(@as(f32, -1.1312), quad[0].x, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quad[0].y, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quad[1].x, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 1.1312), quad[1].y, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 1.1312), quad[2].x, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quad[2].y, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quad[3].x, 0.0002);
    try std.testing.expectApproxEqAbs(@as(f32, -6.7872), quad[3].y, 0.0003);
}

test "light streak scene packet follows native negated x and z scene space" {
    const camera = default_light_streak_camera;
    const current_world = rl.Vector3{ .x = 2.0, .y = 3.0, .z = 54.0 };
    const velocity_world = rl.Vector3{ .x = 0.5, .y = -0.25, .z = 0.0 };
    const packet = lightStreakScenePacket(camera, current_world, velocity_world);

    try std.testing.expectApproxEqAbs(@as(f32, -2.0), packet.current.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), packet.current.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -54.0), packet.current.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), packet.motion_delta.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -0.25), packet.motion_delta.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), packet.motion_delta.z, 0.0001);
}

test "light streak update advances sprite position by velocity" {
    var controller = LightStreakController.init();
    const camera = default_light_streak_camera;
    controller.update(camera, true);

    const before = controller.entries[0].sprite_position;
    const velocity = controller.entries[0].direction;
    controller.update(camera, true);
    const after = controller.entries[0].sprite_position;

    try std.testing.expectApproxEqAbs(before.x + velocity.x, after.x, 0.0001);
    try std.testing.expectApproxEqAbs(before.y + velocity.y, after.y, 0.0001);
    try std.testing.expectApproxEqAbs(before.z + velocity.z, after.z, 0.0001);
}
