const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const archive = @import("archive.zig");
const game_font = @import("game_font.zig");

const text_line_advance_world: f32 = 1.0;
const text_glyph_height_world: f32 = 1.0;
const text_glyph_advance_scale: f32 = 0.8;
const scroll_start_z: f32 = 0.2;
const scroll_end_z: f32 = 3.0;
const world_y: f32 = -4.0;
const rotation_cos: f32 = @bitCast(@as(u32, 0x3f226794));
const rotation_sin: f32 = @bitCast(@as(u32, 0x3f45e3fc));
const original_intro_viewport_width: f32 = 640.0;
const original_intro_viewport_height: f32 = 480.0;
const projection_focal_original: f32 = 100.0;
const near_clip_depth: f32 = 0.05;
const text_color: rl.Color = .white;

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
    // X-axis rotation, Font3D unit quad geometry, right-to-left centered glyph placement,
    // image sizing, and duration-driven shared z scroll from `initialize_intro_screen`.
    // Remaining gaps are the exact object/material batching path and backdrop RNG seeding.
    pub fn drawCrawl(self: *const Loaded, ui_font: *const game_font.Loaded, progress: f32, viewport: rl.Rectangle) void {
        const layout = crawlLayout(totalLoadedWorldHeight(self.entries));
        const scroll_offset = std.math.clamp(progress, 0.0, 1.0) * layout.scroll_distance;
        const viewport_scale = introViewportScale(viewport);
        const camera = introCameraForViewport(viewport);
        camera.begin();
        defer rl.endMode3D();
        var cursor_z = scroll_start_z;

        for (self.entries) |entry| {
            switch (entry) {
                .text => |line| drawWorldTextLine(ui_font, line, cursor_z + scroll_offset, viewport_scale),
                .image => |image| drawWorldImage(image, cursor_z + scroll_offset, viewport_scale),
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

const WorldQuad = struct {
    top_left: rl.Vector3,
    top_right: rl.Vector3,
    bottom_right: rl.Vector3,
    bottom_left: rl.Vector3,
};

fn projectionForViewport(viewport: rl.Rectangle) Projection {
    const scale = viewport.height / original_intro_viewport_height;
    return .{
        .center_x = viewport.x + viewport.width * 0.5,
        .center_y = viewport.y + viewport.height * 0.5,
        .focal = projection_focal_original * scale,
    };
}

fn introViewportScale(viewport: rl.Rectangle) f32 {
    return @min(
        viewport.width / original_intro_viewport_width,
        viewport.height / original_intro_viewport_height,
    );
}

fn introCameraForViewport(viewport: rl.Rectangle) rl.Camera3D {
    const projection = projectionForViewport(viewport);
    const half_height = @max(viewport.height * 0.5, 1.0);
    const fovy_radians = 2.0 * std.math.atan(half_height / projection.focal);
    return .{
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .target = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .fovy = std.math.radiansToDegrees(fovy_radians),
        .projection = .perspective,
    };
}

fn worldPoint(world_x: f32, world_z: f32, viewport_scale: f32) rl.Vector3 {
    return .{
        .x = world_x * viewport_scale,
        .y = (world_y * rotation_cos + world_z * rotation_sin) * viewport_scale,
        .z = -world_y * rotation_sin + world_z * rotation_cos,
    };
}

fn worldQuad(left_x: f32, right_x: f32, top_z: f32, bottom_z: f32, viewport_scale: f32) ?WorldQuad {
    const top_left = worldPoint(left_x, top_z, viewport_scale);
    const top_right = worldPoint(right_x, top_z, viewport_scale);
    const bottom_right = worldPoint(right_x, bottom_z, viewport_scale);
    const bottom_left = worldPoint(left_x, bottom_z, viewport_scale);
    if (top_left.z <= near_clip_depth or top_right.z <= near_clip_depth or bottom_right.z <= near_clip_depth or bottom_left.z <= near_clip_depth) {
        return null;
    }
    return .{
        .top_left = top_left,
        .top_right = top_right,
        .bottom_right = bottom_right,
        .bottom_left = bottom_left,
    };
}

const LineMetrics = struct {
    render_width: f32,
    first_right_edge_x: f32,
};

fn drawWorldTextLine(ui_font: *const game_font.Loaded, line: []const u8, center_z: f32, viewport_scale: f32) void {
    if (line.len == 0 or ui_font.nominal_height <= 0.0) return;

    const metrics = measureLineMetrics(ui_font, line);
    var pen_right_x = metrics.first_right_edge_x;

    for (line) |byte| {
        if (byte == '\r' or byte == '\n') continue;

        const slot_index = game_font.slotIndexForByte(byte) orelse game_font.fallback_slot_index;
        const glyph_width_world = glyphRenderWidthWorld(ui_font, slot_index);
        const glyph_advance_world = glyphAdvanceWorld(ui_font, slot_index);
        defer pen_right_x -= glyph_advance_world;

        if (byte == ' ') continue;

        const quad = worldQuad(
            pen_right_x - glyph_width_world,
            pen_right_x,
            center_z + text_glyph_height_world * 0.5,
            center_z - text_glyph_height_world * 0.5,
            viewport_scale,
        ) orelse continue;
        drawTexturedQuad(
            ui_font.texture,
            glyphSourceRect(ui_font.slots[slot_index]),
            quad,
            text_color,
            true,
            true,
        );
    }
}

fn drawWorldImage(image: LoadedImage, center_z: f32, viewport_scale: f32) void {
    const world_width = clampedImageWorldWidth(image);
    const world_height = clampedImageWorldHeight(image);
    if (worldQuad(
        -world_width * 0.5,
        world_width * 0.5,
        center_z + world_height * 0.5,
        center_z - world_height * 0.5,
        viewport_scale,
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
            false,
            false,
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

fn measureLineMetrics(ui_font: *const game_font.Loaded, line: []const u8) LineMetrics {
    var advance_width: f32 = 0.0;
    var last_render_width: f32 = 0.0;
    var saw_glyph = false;

    for (line) |byte| {
        if (byte == '\r' or byte == '\n') continue;
        const slot_index = game_font.slotIndexForByte(byte) orelse game_font.fallback_slot_index;
        advance_width += glyphAdvanceWorld(ui_font, slot_index);
        last_render_width = glyphRenderWidthWorld(ui_font, slot_index);
        saw_glyph = true;
    }

    if (!saw_glyph) {
        return .{
            .render_width = 0.0,
            .first_right_edge_x = 0.0,
        };
    }

    const last_advance_width = last_render_width * text_glyph_advance_scale;
    const render_width = advance_width - last_advance_width + last_render_width;
    return .{
        .render_width = render_width,
        .first_right_edge_x = render_width * 0.5,
    };
}

fn glyphRenderWidthWorld(ui_font: *const game_font.Loaded, slot_index: usize) f32 {
    if (slot_index >= ui_font.slots.len or ui_font.nominal_height <= 0.0) return 0.0;
    return ui_font.slots[slot_index].source_width / ui_font.nominal_height;
}

fn glyphAdvanceWorld(ui_font: *const game_font.Loaded, slot_index: usize) f32 {
    return glyphRenderWidthWorld(ui_font, slot_index) * text_glyph_advance_scale;
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
        .text => text_line_advance_world,
        .image => |image| clampedImageWorldHeight(image),
    };
}

fn clampedImageWorldWidth(image: LoadedImage) f32 {
    return @max(image.width, 0.01);
}

fn clampedImageWorldHeight(image: LoadedImage) f32 {
    return @max(image.height, 0.01);
}

fn glyphSourceRect(slot: anytype) rl.Rectangle {
    return .{
        .x = slot.source_x,
        .y = slot.source_y,
        .width = slot.source_width,
        .height = slot.source_height,
    };
}

fn drawTexturedQuad(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    quad: WorldQuad,
    tint: rl.Color,
    use_half_texel_inset: bool,
    flip_horizontal: bool,
) void {
    if (source.width <= 0.0 or source.height <= 0.0) return;

    const texture_width: f32 = @floatFromInt(texture.width);
    const texture_height: f32 = @floatFromInt(texture.height);
    if (texture_width <= 0.0 or texture_height <= 0.0) return;

    const inset_x: f32 = if (use_half_texel_inset and source.width > 1.0) 0.5 else 0.0;
    const inset_y: f32 = if (use_half_texel_inset and source.height > 1.0) 0.5 else 0.0;
    const unclamped_left_u = (source.x + inset_x) / texture_width;
    const unclamped_right_u = (source.x + source.width - inset_x) / texture_width;
    const left_u = if (flip_horizontal) unclamped_right_u else unclamped_left_u;
    const right_u = if (flip_horizontal) unclamped_left_u else unclamped_right_u;
    const top_v = (source.y + inset_y) / texture_height;
    const bottom_v = (source.y + source.height - inset_y) / texture_height;

    rl.gl.rlDrawRenderBatchActive();
    rl.gl.rlSetTexture(texture.id);
    defer {
        rl.gl.rlSetTexture(0);
        rl.gl.rlDrawRenderBatchActive();
    }
    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();

    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    rl.gl.rlTexCoord2f(left_u, top_v);
    rl.gl.rlVertex3f(quad.top_left.x, quad.top_left.y, quad.top_left.z);
    rl.gl.rlTexCoord2f(right_u, top_v);
    rl.gl.rlVertex3f(quad.top_right.x, quad.top_right.y, quad.top_right.z);
    rl.gl.rlTexCoord2f(right_u, bottom_v);
    rl.gl.rlVertex3f(quad.bottom_right.x, quad.bottom_right.y, quad.bottom_right.z);
    rl.gl.rlTexCoord2f(left_u, bottom_v);
    rl.gl.rlVertex3f(quad.bottom_left.x, quad.bottom_left.y, quad.bottom_left.z);
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

test "projection focal uses the recovered 100-unit intro scalar" {
    const projection = projectionForViewport(.{ .x = 0.0, .y = 0.0, .width = 1024.0, .height = 768.0 });
    try std.testing.expectApproxEqAbs(@as(f32, 512.0), projection.center_x, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 384.0), projection.center_y, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 160.0), projection.focal, 0.001);
}

test "intro viewport scale tracks 640x480 upscaling" {
    const scale = introViewportScale(.{
        .x = 0.0,
        .y = 0.0,
        .width = 1024.0,
        .height = 768.0,
    });
    try std.testing.expectApproxEqAbs(@as(f32, 1.6), scale, 0.001);
}

test "viewport scale expands intro plane coordinates without changing depth" {
    const scaled = worldPoint(1.0, 0.2, 1.6);
    const unscaled = worldPoint(1.0, 0.2, 1.0);
    try std.testing.expectApproxEqAbs(@as(f32, 1.6), scaled.x, 0.001);
    try std.testing.expectApproxEqAbs(unscaled.z, scaled.z, 0.001);
    try std.testing.expect(@abs(scaled.y) > @abs(unscaled.y));
}

test "line metrics use Font3D render width with 0.8 advance" {
    var slots = [_]game_font.GlyphSlot{game_font.GlyphSlot.invisible()} ** 95;
    slots[game_font.slotIndexForByte('A').?] = .{
        .source_x = 0.0,
        .source_y = 0.0,
        .source_width = 12.0,
        .source_height = 16.0,
        .advance_width = 9.0,
    };
    slots[game_font.slotIndexForByte('B').?] = .{
        .source_x = 12.0,
        .source_y = 0.0,
        .source_width = 8.0,
        .source_height = 16.0,
        .advance_width = 6.0,
    };
    const font = game_font.Loaded{
        .texture = undefined,
        .slots = slots,
        .nominal_height = 10.0,
    };

    const metrics = measureLineMetrics(&font, "AB");
    try std.testing.expectApproxEqAbs(@as(f32, 1.76), metrics.render_width, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.88), metrics.first_right_edge_x, 0.001);
}

test "textured quad uv inset trims font marker columns" {
    const texture = rl.Texture2D{
        .id = 1,
        .width = 256,
        .height = 128,
        .mipmaps = 1,
        .format = .uncompressed_r8g8b8a8,
    };
    const source = rl.Rectangle{
        .x = 32.0,
        .y = 1.0,
        .width = 10.0,
        .height = 12.0,
    };
    const inset_x = if (true and source.width > 1.0) 0.5 else 0.0;
    const inset_y = if (true and source.height > 1.0) 0.5 else 0.0;

    try std.testing.expectApproxEqAbs(@as(f32, 32.5 / 256.0), (source.x + inset_x) / @as(f32, @floatFromInt(texture.width)), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 41.5 / 256.0), (source.x + source.width - inset_x) / @as(f32, @floatFromInt(texture.width)), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.5 / 128.0), (source.y + inset_y) / @as(f32, @floatFromInt(texture.height)), 0.0001);
}
