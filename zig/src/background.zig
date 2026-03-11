const std = @import("std");
const rl = @import("raylib");
const rlgl = rl.gl;
const assets = @import("assets.zig");
const archive = @import("archive.zig");

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
        catalog: *const assets.Catalog,
        script_path: []const u8,
    ) !Loaded {
        const entry = catalog.dat.entryByPath(script_path) orelse return error.EntryNotFound;
        return loadFromEntry(allocator, catalog, entry);
    }

    pub fn loadFromEntry(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
    ) !Loaded {
        const decoded = try catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        var definition = try parseText(allocator, decoded, entry.path);
        errdefer definition.deinit();

        var textures = try loadTexturesForPicture(allocator, catalog, definition.source_path, definition.picture);
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
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    source_path: []const u8,
    picture: []const u8,
) !LoadedTextures {
    const directory = directoryPrefix(source_path);
    const stem = pictureStem(picture);

    var split_a_buffer: [std.fs.max_path_bytes]u8 = undefined;
    var split_b_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const split_a_path = try std.fmt.bufPrint(&split_a_buffer, "{s}{s}_A.TGA", .{ directory, stem });
    const split_b_path = try std.fmt.bufPrint(&split_b_buffer, "{s}{s}_B.TGA", .{ directory, stem });

    if (catalog.findTextureEntry(split_a_path) != null and catalog.findTextureEntry(split_b_path) != null) {
        var primary_texture = try catalog.loadTextureByPath(allocator, split_a_path);
        errdefer primary_texture.unload();
        const secondary_texture = try catalog.loadTextureByPath(allocator, split_b_path);
        return .{
            .primary_texture = primary_texture,
            .secondary_texture = secondary_texture,
        };
    }

    var picture_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const picture_path = try std.fmt.bufPrint(&picture_buffer, "{s}{s}", .{ directory, picture });
    if (catalog.findTextureEntry(picture_path) != null) {
        return .{
            .primary_texture = try catalog.loadTextureByPath(allocator, picture_path),
        };
    }

    if (catalog.findTextureEntry(split_a_path) != null) {
        return .{
            .primary_texture = try catalog.loadTextureByPath(allocator, split_a_path),
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
    defer rlgl.rlEnd();
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

test "warped backdrop flips vertical crop only" {
    const normal = warpCellUvBounds(2, 3, false);
    const flipped = warpCellUvBounds(2, 3, true);

    try std.testing.expectApproxEqAbs(@as(f32, 0.8) - normal.right, flipped.left, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.8) - normal.left, flipped.right, 0.0001);
    try std.testing.expectApproxEqAbs(normal.top, flipped.top, 0.0001);
    try std.testing.expectApproxEqAbs(normal.bottom, flipped.bottom, 0.0001);
}
