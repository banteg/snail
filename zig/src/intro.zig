const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const archive = @import("archive.zig");
const game_font = @import("game_font.zig");

const text_world_height: f32 = 1.0;
const text_world_width_scale: f32 = 0.8;
const scroll_start_z: f32 = 0.2;
const scroll_end_z: f32 = 3.0;
const world_y: f32 = -4.0;
const rotation_cos: f32 = @bitCast(@as(u32, 0x3f226794));
const rotation_sin: f32 = @bitCast(@as(u32, 0x3f45e3fc));
const projection_focal_ratio: f32 = 0.3125;
const near_clip_depth: f32 = 0.05;
const text_color: rl.Color = .{ .r = 0xf1, .g = 0xc5, .b = 0x4a, .a = 0xff };

pub const ImageEntry = struct {
    archive_path: []const u8,
    width: f32,
    height: f32,
};

pub const Entry = union(enum) {
    text: []const u8,
    image: ImageEntry,
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    source_path: []const u8,
    duration: f32,
    entries: []Entry,

    pub fn deinit(self: *Definition) void {
        self.arena.deinit();
    }
};

pub const LoadedImage = struct {
    archive_path: []const u8,
    width: f32,
    height: f32,
    texture: assets.LoadedTexture,
};

pub const LoadedEntry = union(enum) {
    text: []const u8,
    image: LoadedImage,
};

pub const Loaded = struct {
    definition: Definition,
    entries: []LoadedEntry,

    pub fn deinit(self: *Loaded, allocator: std.mem.Allocator) void {
        for (self.entries) |*entry| {
            switch (entry.*) {
                .text => {},
                .image => |*image| image.texture.unload(),
            }
        }
        allocator.free(self.entries);
        self.definition.deinit();
    }

    pub fn duration(self: *const Loaded) f32 {
        return self.definition.duration;
    }

    pub fn durationTicks(self: *const Loaded) u64 {
        return @as(u64, @intFromFloat(@max(self.duration() * 60.0, 1.0)));
    }

    pub fn progressForTicks(self: *const Loaded, elapsed_ticks: u64) f32 {
        const total_ticks = self.durationTicks();
        if (total_ticks == 0) return 1.0;
        return std.math.clamp(
            @as(f32, @floatFromInt(elapsed_ticks)) / @as(f32, @floatFromInt(total_ticks)),
            0.0,
            1.0,
        );
    }

    // PORT(partial): this crawl renderer now follows the recovered intro plane (`y = -4`),
    // X-axis rotation, centered world-space text and image quads, per-line/image heights,
    // and shared duration-driven z scroll from `initialize_intro_text_screen`. Remaining
    // gaps are exact transition semantics and any original renderer-side batching quirks.
    pub fn drawCrawl(self: *const Loaded, ui_font: *const game_font.Loaded, progress: f32, viewport: rl.Rectangle) void {
        const layout = crawlLayout(totalLoadedWorldHeight(self.entries));
        const scroll_offset = std.math.clamp(progress, 0.0, 1.0) * layout.scroll_distance;
        var cursor_z = scroll_start_z;

        for (self.entries) |entry| {
            switch (entry) {
                .text => |line| drawProjectedTextLine(ui_font, line, cursor_z + scroll_offset, viewport),
                .image => |image| drawProjectedImage(image, cursor_z + scroll_offset, viewport),
            }
            cursor_z -= loadedEntryWorldHeight(entry);
        }
    }
};

pub fn loadFromArchive(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    entry: archive.Entry,
) !Loaded {
    const decoded = try catalog.readEntryAlloc(allocator, entry);
    defer allocator.free(decoded);

    var definition = try parseText(allocator, decoded, entry.path);
    errdefer definition.deinit();
    return loadResolvedEntries(allocator, catalog, definition);
}

pub fn loadByPath(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    path: []const u8,
) !Loaded {
    const entry = catalog.dat.entryByPath(path) orelse return error.EntryNotFound;
    return loadFromArchive(allocator, catalog, entry);
}

pub fn parseText(
    allocator: std.mem.Allocator,
    data: []const u8,
    source_path: []const u8,
) !Definition {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var duration: ?f32 = null;
    var text_block: ?[]const u8 = null;

    const start_marker = "Text Start:";
    const end_marker = "Text End:";
    var lines = std.mem.splitScalar(u8, data, '\n');
    var scratch: [4096]u8 = undefined;
    while (lines.next()) |raw_line| {
        const line = stripLine(raw_line, &scratch);
        if (line.len == 0) continue;

        if (std.mem.startsWith(u8, line, "Duration:")) {
            duration = try std.fmt.parseFloat(f32, std.mem.trim(u8, line["Duration:".len..], " \t"));
            continue;
        }

        if (std.mem.eql(u8, line, start_marker)) {
            const text_start_offset = @intFromPtr(raw_line.ptr) - @intFromPtr(data.ptr) + raw_line.len + 1;
            const end_index = std.mem.indexOf(u8, data[text_start_offset..], end_marker) orelse return error.MissingIntroTextEnd;
            text_block = std.mem.trim(u8, data[text_start_offset .. text_start_offset + end_index], "\r\n");
            break;
        }
    }

    const resolved_text_block = text_block orelse return error.MissingIntroText;
    const entries = try parseEntries(arena_allocator, resolved_text_block, source_path);

    return .{
        .arena = arena,
        .source_path = try arena_allocator.dupe(u8, source_path),
        .duration = duration orelse return error.MissingIntroDuration,
        .entries = entries,
    };
}

fn loadResolvedEntries(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    definition: Definition,
) !Loaded {
    const resolved_entries = try allocator.alloc(LoadedEntry, definition.entries.len);
    var initialized_count: usize = 0;
    errdefer allocator.free(resolved_entries);
    errdefer {
        for (resolved_entries[0..initialized_count]) |*entry| {
            switch (entry.*) {
                .text => {},
                .image => |*image| image.texture.unload(),
            }
        }
    }

    for (definition.entries, 0..) |entry, index| {
        resolved_entries[index] = switch (entry) {
            .text => |text| .{ .text = text },
            .image => |image| .{
                .image = .{
                    .archive_path = image.archive_path,
                    .width = image.width,
                    .height = image.height,
                    .texture = try catalog.loadTextureByPath(allocator, image.archive_path),
                },
            },
        };
        initialized_count = index + 1;
    }

    return .{
        .definition = definition,
        .entries = resolved_entries,
    };
}

fn parseEntries(
    allocator: std.mem.Allocator,
    text_block: []const u8,
    source_path: []const u8,
) ![]Entry {
    var entries: std.ArrayList(Entry) = .empty;
    defer entries.deinit(allocator);

    var lines = std.mem.splitScalar(u8, text_block, '\n');
    while (lines.next()) |raw_line| {
        const line = std.mem.trimRight(u8, raw_line, "\r");
        const stripped = std.mem.trim(u8, line, " \t");
        if (stripped.len > 0 and stripped[0] == '*') {
            try entries.append(allocator, .{ .image = try parseImageDirective(allocator, stripped, source_path) });
            continue;
        }

        const normalized_text = if (stripped.len == 0) "" else try allocator.dupe(u8, stripped);
        try entries.append(allocator, .{ .text = normalized_text });
    }

    return try entries.toOwnedSlice(allocator);
}

fn parseImageDirective(
    allocator: std.mem.Allocator,
    line: []const u8,
    source_path: []const u8,
) !ImageEntry {
    const open_paren = std.mem.indexOfScalar(u8, line, '(') orelse return error.InvalidIntroImageDirective;
    const close_paren = std.mem.lastIndexOfScalar(u8, line, ')') orelse return error.InvalidIntroImageDirective;
    if (close_paren <= open_paren + 1) return error.InvalidIntroImageDirective;

    const image_name = std.mem.trim(u8, line[1..open_paren], " \t");
    if (image_name.len == 0) return error.InvalidIntroImageDirective;

    const inner = line[open_paren + 1 .. close_paren];
    var parts = std.mem.splitScalar(u8, inner, ',');
    const width_text = std.mem.trim(u8, parts.next() orelse return error.InvalidIntroImageDirective, " \t");
    const height_text = std.mem.trim(u8, parts.next() orelse return error.InvalidIntroImageDirective, " \t");
    if (parts.next() != null) return error.InvalidIntroImageDirective;

    const archive_path = try buildImageArchivePath(allocator, source_path, image_name);
    return .{
        .archive_path = archive_path,
        .width = try std.fmt.parseFloat(f32, width_text),
        .height = try std.fmt.parseFloat(f32, height_text),
    };
}

fn buildImageArchivePath(
    allocator: std.mem.Allocator,
    source_path: []const u8,
    image_name: []const u8,
) ![]const u8 {
    const directory = directoryPrefix(source_path);
    const texture_name = if (std.ascii.endsWithIgnoreCase(image_name, ".tga"))
        image_name
    else
        try std.fmt.allocPrint(allocator, "{s}.TGA", .{image_name});
    if (!std.ascii.endsWithIgnoreCase(image_name, ".tga")) {
        return try std.fmt.allocPrint(allocator, "{s}{s}", .{ directory, texture_name });
    }
    return try std.fmt.allocPrint(allocator, "{s}{s}", .{ directory, image_name });
}

fn directoryPrefix(source_path: []const u8) []const u8 {
    const slash_index = std.mem.lastIndexOfScalar(u8, source_path, '/') orelse return "";
    return source_path[0 .. slash_index + 1];
}

fn stripLine(raw_line: []const u8, scratch: []u8) []const u8 {
    const clipped = if (raw_line.len > scratch.len) raw_line[0..scratch.len] else raw_line;
    @memcpy(scratch[0..clipped.len], clipped);
    return std.mem.trim(u8, scratch[0..clipped.len], " \t\r");
}

const Projection = struct {
    center_x: f32,
    center_y: f32,
    focal: f32,
};

const CrawlLayout = struct {
    final_cursor_z: f32,
    scroll_distance: f32,
};

const ProjectedPoint = struct {
    x: f32,
    y: f32,
};

const ProjectedQuad = struct {
    top_left: ProjectedPoint,
    top_right: ProjectedPoint,
    bottom_right: ProjectedPoint,
    bottom_left: ProjectedPoint,
};

fn projectionForViewport(viewport: rl.Rectangle) Projection {
    return .{
        .center_x = viewport.x + viewport.width * 0.5,
        .center_y = viewport.y + viewport.height * 0.5,
        .focal = @min(viewport.width, viewport.height) * projection_focal_ratio,
    };
}

fn projectPoint(projection: Projection, world_x: f32, world_z: f32) ?ProjectedPoint {
    const rotated_y = world_y * rotation_cos + world_z * rotation_sin;
    const depth = -world_y * rotation_sin + world_z * rotation_cos;
    if (depth <= near_clip_depth) return null;

    const perspective = projection.focal / depth;
    return .{
        .x = projection.center_x + world_x * perspective,
        .y = projection.center_y - rotated_y * perspective,
    };
}

fn drawProjectedTextLine(ui_font: *const game_font.Loaded, line: []const u8, top_z: f32, viewport: rl.Rectangle) void {
    if (line.len == 0) return;

    const projection = projectionForViewport(viewport);
    const line_width_world = measureLineWorldWidth(ui_font, line);
    var pen_x = -line_width_world * 0.5;

    rl.gl.rlSetTexture(ui_font.texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();

    rl.gl.rlColor4ub(text_color.r, text_color.g, text_color.b, text_color.a);

    for (line) |byte| {
        if (byte == '\r' or byte == '\n') continue;

        const slot_index = game_font.slotIndexForByte(byte) orelse game_font.fallback_slot_index;
        const slot = ui_font.slots[slot_index];
        const advance_world = slot.advance_width * text_world_width_scale / ui_font.nominal_height;

        if (byte != ' ' and slot.source_width > 0.0 and slot.source_height > 0.0) {
            const glyph_width_world = slot.source_width * text_world_width_scale / ui_font.nominal_height;
            const glyph_height_world = slot.source_height / ui_font.nominal_height;
            if (projectQuad(
                projection,
                pen_x,
                pen_x + glyph_width_world,
                top_z,
                top_z - glyph_height_world,
            )) |quad| {
                emitTexturedQuad(
                    ui_font.texture,
                    .{
                        .x = slot.source_x,
                        .y = slot.source_y,
                        .width = slot.source_width,
                        .height = slot.source_height,
                    },
                    quad,
                );
            }
        }

        pen_x += advance_world;
    }
}

fn drawProjectedImage(image: LoadedImage, top_z: f32, viewport: rl.Rectangle) void {
    const world_width = clampedImageWorldWidth(image);
    const world_height = clampedImageWorldHeight(image);
    const projection = projectionForViewport(viewport);
    if (projectQuad(
        projection,
        -world_width * 0.5,
        world_width * 0.5,
        top_z,
        top_z - world_height,
    )) |quad| {
        drawTexturedQuad(
            image.texture.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @floatFromInt(image.texture.texture.width),
                .height = @floatFromInt(image.texture.texture.height),
            },
            quad,
            .white,
        );
    }
}

fn crawlLayout(total_world_height: f32) CrawlLayout {
    const final_cursor_z = scroll_start_z - total_world_height;
    return .{
        .final_cursor_z = final_cursor_z,
        .scroll_distance = scroll_end_z - final_cursor_z,
    };
}

fn measureLineWorldWidth(ui_font: *const game_font.Loaded, line: []const u8) f32 {
    var width: f32 = 0.0;
    for (line) |byte| {
        if (byte == '\r' or byte == '\n') continue;
        const slot_index = game_font.slotIndexForByte(byte) orelse game_font.fallback_slot_index;
        width += ui_font.slots[slot_index].advance_width * text_world_width_scale / ui_font.nominal_height;
    }
    return width;
}

fn projectQuad(
    projection: Projection,
    left_x: f32,
    right_x: f32,
    top_z: f32,
    bottom_z: f32,
) ?ProjectedQuad {
    return .{
        .top_left = projectPoint(projection, left_x, top_z) orelse return null,
        .top_right = projectPoint(projection, right_x, top_z) orelse return null,
        .bottom_right = projectPoint(projection, right_x, bottom_z) orelse return null,
        .bottom_left = projectPoint(projection, left_x, bottom_z) orelse return null,
    };
}

fn drawTexturedQuad(texture: rl.Texture2D, source: rl.Rectangle, quad: ProjectedQuad, tint: rl.Color) void {
    if (texture.width <= 0 or texture.height <= 0) return;

    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();

    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    emitTexturedQuad(texture, source, quad);
}

fn emitTexturedQuad(texture: rl.Texture2D, source: rl.Rectangle, quad: ProjectedQuad) void {
    const inv_width = 1.0 / @as(f32, @floatFromInt(texture.width));
    const inv_height = 1.0 / @as(f32, @floatFromInt(texture.height));
    const tex_u0 = source.x * inv_width;
    const tex_v0 = source.y * inv_height;
    const tex_u1 = (source.x + source.width) * inv_width;
    const tex_v1 = (source.y + source.height) * inv_height;

    rl.gl.rlTexCoord2f(tex_u0, tex_v0);
    rl.gl.rlVertex2f(quad.top_left.x, quad.top_left.y);

    rl.gl.rlTexCoord2f(tex_u1, tex_v0);
    rl.gl.rlVertex2f(quad.top_right.x, quad.top_right.y);

    rl.gl.rlTexCoord2f(tex_u1, tex_v1);
    rl.gl.rlVertex2f(quad.bottom_right.x, quad.bottom_right.y);

    rl.gl.rlTexCoord2f(tex_u0, tex_v1);
    rl.gl.rlVertex2f(quad.bottom_left.x, quad.bottom_left.y);
}

fn totalLoadedWorldHeight(entries: []const LoadedEntry) f32 {
    var total_height: f32 = 0.0;
    for (entries) |entry| {
        total_height += loadedEntryWorldHeight(entry);
    }
    return total_height;
}

fn loadedEntryWorldHeight(entry: LoadedEntry) f32 {
    return switch (entry) {
        .text => text_world_height,
        .image => |image| clampedImageWorldHeight(image),
    };
}

fn clampedImageWorldWidth(image: LoadedImage) f32 {
    return @max(image.width, 0.01);
}

fn clampedImageWorldHeight(image: LoadedImage) f32 {
    return @max(image.height, 0.01);
}

test "parse intro script body into ordered text entries" {
    const source =
        \\/* Intro script */
        \\
        \\Duration:35
        \\
        \\Text Start:
        \\Credits
        \\
        \\Programming
        \\Text End:
    ;
    var definition = try parseText(std.testing.allocator, source, "INTRO/CREDITS.TXT");
    defer definition.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 35.0), definition.duration, 0.001);
    try std.testing.expectEqual(@as(usize, 3), definition.entries.len);
    switch (definition.entries[0]) {
        .text => |text| try std.testing.expectEqualStrings("Credits", text),
        .image => return error.UnexpectedIntroEntry,
    }
    switch (definition.entries[1]) {
        .text => |text| try std.testing.expectEqualStrings("", text),
        .image => return error.UnexpectedIntroEntry,
    }
    switch (definition.entries[2]) {
        .text => |text| try std.testing.expectEqualStrings("Programming", text),
        .image => return error.UnexpectedIntroEntry,
    }
}

test "parse intro image directive" {
    const source =
        \\Duration:80
        \\Text Start:
        \\*Turbo.tga(1.5,2.0)
        \\Text End:
    ;
    var definition = try parseText(std.testing.allocator, source, "INTRO/INTRO.TXT");
    defer definition.deinit();

    try std.testing.expectEqual(@as(usize, 1), definition.entries.len);
    switch (definition.entries[0]) {
        .text => return error.UnexpectedIntroEntry,
        .image => |image| {
            try std.testing.expectEqualStrings("INTRO/Turbo.tga", image.archive_path);
            try std.testing.expectApproxEqAbs(@as(f32, 1.5), image.width, 0.001);
            try std.testing.expectApproxEqAbs(@as(f32, 2.0), image.height, 0.001);
        },
    }
}

test "intro duration ticks clamp to at least one frame" {
    const definition = Definition{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "",
        .duration = 0.0,
        .entries = &.{},
    };
    var loaded = Loaded{
        .definition = definition,
        .entries = &.{},
    };
    defer loaded.definition.deinit();

    try std.testing.expectEqual(@as(u64, 1), loaded.durationTicks());
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), loaded.progressForTicks(5), 0.001);
}

test "projected crawl uses image world heights and text line height" {
    const entries = [_]LoadedEntry{
        .{ .text = "Credits" },
        .{ .image = .{
            .archive_path = "INTRO/Turbo.tga",
            .width = 1.5,
            .height = 2.25,
            .texture = undefined,
        } },
        .{ .text = "Programming" },
    };

    try std.testing.expectApproxEqAbs(@as(f32, 4.25), totalLoadedWorldHeight(&entries), 0.001);
}

test "crawl layout follows recovered cursor math" {
    const layout = crawlLayout(4.25);
    try std.testing.expectApproxEqAbs(@as(f32, -4.05), layout.final_cursor_z, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 7.05), layout.scroll_distance, 0.001);
}

test "projection moves crawl upward and inward as z advances" {
    const projection = projectionForViewport(.{ .x = 0.0, .y = 0.0, .width = 640.0, .height = 480.0 });
    const near_center = projectPoint(projection, 0.0, 0.2).?;
    const far_center = projectPoint(projection, 0.0, 3.0).?;
    try std.testing.expect(far_center.y < near_center.y);

    const near_quad = projectQuad(projection, -1.0, 1.0, 0.2, -0.8).?;
    const far_quad = projectQuad(projection, -1.0, 1.0, 3.0, 2.0).?;
    const near_width = near_quad.top_right.x - near_quad.top_left.x;
    const far_width = far_quad.top_right.x - far_quad.top_left.x;
    try std.testing.expect(far_width < near_width);
}
