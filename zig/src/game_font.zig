const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");

pub const default_archive_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";

const max_slot_index = 94;
const slot_count = max_slot_index + 1;
pub const fallback_slot_index = 74;
const space_slot_index = 53;
const recovered_spacing_scale: f32 = 0.75;

// PORT(partial): these named icon tokens are backed by shipped tutorial `Message=` strings
// plus the recovered FONT-MENU-HOVER byte mapper. A few other special slots still need names.
pub const IconGlyph = enum(u8) {
    package = '{',
    mouse = '}',
    slug = '[',
    asteroid = ']',
    powerup = '~',
    slow_ring = ';',
    health = '_',
    salt = '^',

    pub fn byte(self: IconGlyph) u8 {
        return @intFromEnum(self);
    }

    pub fn slotIndex(self: IconGlyph) usize {
        return slotIndexForByte(self.byte()).?;
    }
};

pub const GlyphSlot = struct {
    source_x: f32,
    source_y: f32,
    source_width: f32,
    source_height: f32,
    advance_width: f32,

    pub fn invisible() GlyphSlot {
        return .{
            .source_x = 0.0,
            .source_y = 0.0,
            .source_width = 0.0,
            .source_height = 0.0,
            .advance_width = 0.0,
        };
    }
};

// PORT(verified): the menu font uses the shipped FONT-MENU-HOVER atlas plus the recovered
// row-0 delimiter scan, column-0 height marker, glyph mapper, and 0.75 advance spacing.
// Evidence: sub_449d20, sub_449e90, and sub_449f50.
pub const Loaded = struct {
    texture: rl.Texture2D,
    slots: [slot_count]GlyphSlot,
    nominal_height: f32,
    spacing_scale: f32 = recovered_spacing_scale,

    pub fn load(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !Loaded {
        return loadByPath(allocator, catalog, default_archive_path);
    }

    pub fn loadByPath(allocator: std.mem.Allocator, catalog: *const assets.Catalog, path: []const u8) !Loaded {
        const entry = catalog.findTextureEntry(path) orelse return error.EntryNotFound;
        const decoded = try catalog.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        const image = try rl.loadImageFromMemory(".tga", decoded);
        defer rl.unloadImage(image);

        const colors = try rl.loadImageColors(image);
        defer rl.unloadImageColors(colors);

        const scan = try scanAtlas(colors, @intCast(image.width), @intCast(image.height));
        const texture = try rl.loadTextureFromImage(image);
        rl.setTextureWrap(texture, .clamp);
        rl.setTextureFilter(texture, .bilinear);

        return .{
            .texture = texture,
            .slots = scan.slots,
            .nominal_height = @floatFromInt(scan.nominal_height),
        };
    }

    pub fn deinit(self: *Loaded) void {
        rl.unloadTexture(self.texture);
    }

    pub fn drawText(self: *const Loaded, text: []const u8, x: f32, y: f32, font_size: f32, color: rl.Color) void {
        if (font_size <= 0.0 or self.nominal_height <= 0.0) return;

        var pen_x = x;
        var pen_y = y;
        const origin_x = x;

        for (text) |byte| {
            switch (byte) {
                '\n' => {
                    pen_x = origin_x;
                    pen_y += font_size;
                    continue;
                },
                '\r' => continue,
                else => {},
            }

            const slot_index = slotIndexForByte(byte) orelse fallback_slot_index;
            if (byte != ' ') {
                self.drawSlot(slot_index, pen_x, pen_y, font_size, color);
            }
            pen_x += self.measureSlot(slot_index, font_size);
        }
    }

    pub fn measureText(self: *const Loaded, text: []const u8, font_size: f32) f32 {
        if (font_size <= 0.0 or self.nominal_height <= 0.0) return 0.0;

        const scale = font_size / self.nominal_height;
        const tail_padding = (1.0 - self.spacing_scale) * self.slots[space_slot_index].advance_width * scale;
        var line_width: f32 = 0.0;
        var max_width: f32 = 0.0;

        for (text) |byte| {
            switch (byte) {
                '\n' => {
                    max_width = @max(max_width, line_width + tail_padding);
                    line_width = 0.0;
                    continue;
                },
                '\r' => continue,
                else => {},
            }

            const slot_index = slotIndexForByte(byte) orelse fallback_slot_index;
            line_width += self.measureSlot(slot_index, font_size);
        }

        return @max(max_width, line_width + tail_padding);
    }

    pub fn drawSlot(self: *const Loaded, slot_index: usize, x: f32, y: f32, font_size: f32, color: rl.Color) void {
        if (slot_index >= self.slots.len or font_size <= 0.0 or self.nominal_height <= 0.0) return;

        const slot = self.slots[slot_index];
        if (slot.source_width <= 0.0) return;

        const scale = font_size / self.nominal_height;
        rl.drawTexturePro(
            self.texture,
            .{
                .x = slot.source_x,
                .y = slot.source_y,
                .width = slot.source_width,
                .height = slot.source_height,
            },
            .{
                .x = x,
                .y = y,
                .width = slot.source_width * scale,
                .height = font_size,
            },
            .{ .x = 0.0, .y = 0.0 },
            0.0,
            color,
        );
    }

    pub fn measureSlot(self: *const Loaded, slot_index: usize, font_size: f32) f32 {
        if (slot_index >= self.slots.len or font_size <= 0.0 or self.nominal_height <= 0.0) return 0.0;

        const scale = font_size / self.nominal_height;
        return self.slots[slot_index].advance_width * scale;
    }
};

const AtlasScan = struct {
    slots: [slot_count]GlyphSlot,
    nominal_height: usize,
};

fn scanAtlas(colors: []const rl.Color, width: usize, height: usize) !AtlasScan {
    if (width == 0 or height < 2 or colors.len != width * height) {
        return error.InvalidFontAtlas;
    }

    const nominal_height = findNominalHeight(colors, width, height) orelse return error.InvalidFontAtlas;
    const source_y, const source_height = biasedVerticalSourceRect(height, nominal_height);
    var slots = [_]GlyphSlot{GlyphSlot.invisible()} ** slot_count;
    var previous_marker: isize = -1;
    var slot_index: usize = 0;

    for (0..width) |x| {
        if (!isWhiteMarker(colors[rowOffset(width, 0) + x])) continue;
        if (slot_index >= slot_count) return error.InvalidFontAtlas;

        const start_x = @as(usize, @intCast(previous_marker + 1));
        const glyph_width = x - start_x;
        slots[slot_index] = .{
            // PORT(verified): register_font_texture_sheet stores biased atlas UVs up front.
            // The Windows path does not apply a second inset at draw time.
            .source_x = @as(f32, @floatFromInt(start_x)) + 0.5,
            .source_y = source_y,
            .source_width = @floatFromInt(glyph_width),
            .source_height = source_height,
            .advance_width = @as(f32, @floatFromInt(glyph_width)) * recovered_spacing_scale,
        };

        previous_marker = @intCast(x);
        slot_index += 1;
    }

    if (slot_index != slot_count) return error.InvalidFontAtlas;
    return .{
        .slots = slots,
        .nominal_height = nominal_height,
    };
}

fn biasedVerticalSourceRect(image_height: usize, nominal_height: usize) struct { f32, f32 } {
    const denominator = @as(f32, @floatFromInt(image_height - 1));
    const image_height_f = @as(f32, @floatFromInt(image_height));
    const top_v = 3.0 / denominator;
    const bottom_v = @as(f32, @floatFromInt(nominal_height)) / denominator;
    return .{
        top_v * image_height_f,
        (bottom_v - top_v) * image_height_f,
    };
}

fn findNominalHeight(colors: []const rl.Color, width: usize, height: usize) ?usize {
    for (1..height) |y| {
        if (isWhiteMarker(colors[rowOffset(width, y)])) {
            return y;
        }
    }
    return null;
}

fn rowOffset(width: usize, y: usize) usize {
    return y * width;
}

fn isWhiteMarker(color: rl.Color) bool {
    return color.r == 255 and color.g == 255 and color.b == 255;
}

pub fn slotIndexForByte(byte: u8) ?usize {
    if (byte >= 'a' and byte <= 'z') return byte - 'a' + 1;
    if (byte >= 'A' and byte <= 'Z') return byte - 'A' + 27;
    if (byte >= '0' and byte <= '9') return byte - '0' + 54;

    // The original front-end reuses some ASCII punctuation bytes as tokens for
    // non-text atlas art, so this stays a byte-to-slot mapper, not a "literal punctuation" table.
    return switch (byte) {
        ' ' => 53,
        '"' => 64,
        ':' => 66,
        '(' => 67,
        ')' => 68,
        '!' => 69,
        '@' => 70,
        '#' => 71,
        '$' => 72,
        '%' => 73,
        '?' => 74,
        '&' => 75,
        '*' => 76,
        '+' => 77,
        '-' => 79,
        '/' => 80,
        '\\' => 81,
        ',' => 82,
        '.' => 83,
        '\'' => 84,
        '|' => 85,
        '{' => 86,
        '}' => 87,
        '[' => 88,
        ']' => 89,
        '~' => 90,
        ';' => 91,
        '_' => 92,
        '^' => 93,
        '=' => 94,
        else => null,
    };
}

test "slot index mapping matches recovered front-end font mapper" {
    try std.testing.expectEqual(@as(?usize, 1), slotIndexForByte('a'));
    try std.testing.expectEqual(@as(?usize, 26), slotIndexForByte('z'));
    try std.testing.expectEqual(@as(?usize, 27), slotIndexForByte('A'));
    try std.testing.expectEqual(@as(?usize, 52), slotIndexForByte('Z'));
    try std.testing.expectEqual(@as(?usize, 53), slotIndexForByte(' '));
    try std.testing.expectEqual(@as(?usize, 54), slotIndexForByte('0'));
    try std.testing.expectEqual(@as(?usize, 63), slotIndexForByte('9'));
    try std.testing.expectEqual(@as(?usize, 64), slotIndexForByte('"'));
    try std.testing.expectEqual(@as(?usize, 69), slotIndexForByte('!'));
    try std.testing.expectEqual(@as(?usize, 74), slotIndexForByte('?'));
    try std.testing.expectEqual(@as(?usize, 81), slotIndexForByte('\\'));
    try std.testing.expectEqual(@as(?usize, 94), slotIndexForByte('='));
    try std.testing.expectEqual(@as(?usize, null), slotIndexForByte('<'));
}

test "named icon glyphs resolve to recovered tutorial slots" {
    try std.testing.expectEqual(@as(usize, 86), IconGlyph.package.slotIndex());
    try std.testing.expectEqual(@as(usize, 87), IconGlyph.mouse.slotIndex());
    try std.testing.expectEqual(@as(usize, 88), IconGlyph.slug.slotIndex());
    try std.testing.expectEqual(@as(usize, 89), IconGlyph.asteroid.slotIndex());
    try std.testing.expectEqual(@as(usize, 90), IconGlyph.powerup.slotIndex());
    try std.testing.expectEqual(@as(usize, 91), IconGlyph.slow_ring.slotIndex());
    try std.testing.expectEqual(@as(usize, 92), IconGlyph.health.slotIndex());
    try std.testing.expectEqual(@as(usize, 93), IconGlyph.salt.slotIndex());
}
