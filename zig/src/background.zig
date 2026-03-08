const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const archive = @import("archive.zig");

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
