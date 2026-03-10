const std = @import("std");
const rl = @import("raylib");
const app_ui = @import("app_ui.zig");
const game_font = @import("game_font.zig");

pub const WidgetType = enum(u8) {
    menu_button = 20,
    compact_score_row = 22,
    footer_button = 23,
    route_map_secondary_action = 24,
};

pub const WidgetAlignment = enum(u8) {
    absolute = 0,
    left = 1,
    center = 2,
    right = 3,
};

pub const type20_idle_padding: f32 = 9.0;
// PORT(verified): `sub_401D30(..., widget_type=20, ...)` seeds `+536 = 13.0` for the
// shell-font menu widget hot padding, and `sub_402820` animates toward that target.
pub const type20_hot_padding: f32 = 13.0;
// PORT(verified): `sub_401D30(..., widget_type=20, ...)` seeds `+620 = 26.0` for the
// shell-font menu widget, and `sub_4027B0` chains the next button by adding that recovered
// gap to the previous widget's measured text height.
pub const type20_stack_gap: f32 = 26.0;
// PORT(verified): the standard centered shell-font menu constructors pass `x = 20.0`
// with alignment `2`, matching the authored-space offset used by the Windows main/new game
// menu button stack.
pub const type20_center_offset_x: f32 = 20.0;
// PORT(verified): `sub_401130` renders the type-20 shell border with a fixed authored
// corner size of `+560 = 20.0`, while the compact/footer variants use a 4px edge path.
pub const type20_border_edge: f32 = 20.0;
pub const compact_border_edge: f32 = 4.0;
pub const cursor_hotspot_x: f32 = 8.0;
pub const cursor_hotspot_y: f32 = 7.0;
pub const cursor_size: f32 = 64.0;

const hover_lerp: f32 = 0.1;
const idle_fill = colorFromBytes(84, 57, 128, 179);
const hot_fill = colorFromBytes(155, 79, 177, 255);
const idle_text = colorFromBytes(255, 133, 0, 179);
const hot_text = rl.Color.ray_white;
const text_shadow = colorFromBytes(30, 10, 28, 224);

pub const Rect = struct {
    left: f32,
    top: f32,
    width: f32,
    height: f32,

    pub fn contains(self: Rect, point: rl.Vector2) bool {
        return point.x >= self.left and point.x <= self.left + self.width and point.y >= self.top and point.y <= self.top + self.height;
    }

    pub fn centerX(self: Rect) f32 {
        return self.left + self.width * 0.5;
    }

    pub fn centerY(self: Rect) f32 {
        return self.top + self.height * 0.5;
    }
};

pub const Art = struct {
    border: rl.Texture2D,
};

pub const Metrics = struct {
    text_scale: f32,
    idle_padding: f32,
    hot_padding: f32,
    border_edge: f32,
    source_edge_fraction: f32,

    pub fn fontSize(self: Metrics, font: *const game_font.Loaded) f32 {
        return font.nominal_height * self.text_scale;
    }

    pub fn textHeight(self: Metrics, font: *const game_font.Loaded) f32 {
        return font.nominal_height * self.text_scale;
    }
};

pub const TextButtonState = struct {
    hot_blend: f32 = 0.0,
    current_padding: f32 = type20_idle_padding,

    pub fn snapFor(self: *TextButtonState, widget_type: WidgetType, hot: bool) void {
        const metrics = metricsForType(widget_type);
        self.hot_blend = if (hot) 1.0 else 0.0;
        self.current_padding = if (hot) metrics.hot_padding else metrics.idle_padding;
    }

    pub fn stepFor(self: *TextButtonState, widget_type: WidgetType, hot: bool) void {
        const metrics = metricsForType(widget_type);
        const hot_target: f32 = if (hot) 1.0 else 0.0;
        const padding_target = if (hot) metrics.hot_padding else metrics.idle_padding;
        self.hot_blend = stepValue(self.hot_blend, hot_target);
        self.current_padding = stepValue(self.current_padding, padding_target);
    }
};

pub const ButtonColors = struct {
    fill: rl.Color,
    text: rl.Color,
    shadow: rl.Color,
};

pub fn metricsForType(widget_type: WidgetType) Metrics {
    return switch (widget_type) {
        .menu_button => .{
            // PORT(verified): `sub_401D30(..., widget_type=20, ...)` seeds `+1776 = 1.3`
            // for the shell-font menu button scale.
            .text_scale = 1.3,
            .idle_padding = type20_idle_padding,
            .hot_padding = type20_hot_padding,
            .border_edge = type20_border_edge,
            .source_edge_fraction = type20_border_edge / 128.0,
        },
        .compact_score_row => .{
            .text_scale = 0.65,
            .idle_padding = 1.0,
            .hot_padding = 3.0,
            .border_edge = compact_border_edge,
            .source_edge_fraction = 0.1,
        },
        .footer_button => .{
            .text_scale = 1.14,
            .idle_padding = 6.0,
            .hot_padding = 7.0,
            .border_edge = compact_border_edge,
            .source_edge_fraction = 0.1,
        },
        .route_map_secondary_action => .{
            // PORT(verified): `initialize_galaxy` / `open_galaxy_route` keep the replay action
            // on the type-20 shell border, but override the text scale to `0.8` and idle pad
            // to `8.0` for the "Watch Best Trial" button.
            .text_scale = 0.8,
            .idle_padding = 8.0,
            .hot_padding = type20_hot_padding,
            .border_edge = type20_border_edge,
            .source_edge_fraction = type20_border_edge / 128.0,
        },
    };
}

pub fn type20TextRect(font: *const game_font.Loaded, text: []const u8, anchor_y: f32, center_offset_x: f32) Rect {
    return widgetTextRect(font, .menu_button, .center, text, anchor_y, center_offset_x);
}

pub fn widgetTextRect(
    font: *const game_font.Loaded,
    widget_type: WidgetType,
    alignment: WidgetAlignment,
    text: []const u8,
    anchor_y: f32,
    anchor_x: f32,
) Rect {
    const metrics = metricsForType(widget_type);
    const width = font.measureText(text, metrics.fontSize(font));
    const base_x = switch (alignment) {
        .absolute => anchor_x,
        .left, .center, .right => 320.0 + anchor_x,
    };
    return .{
        .left = switch (alignment) {
            .absolute, .left => base_x,
            .center => base_x - width * 0.5,
            .right => base_x - width,
        },
        .top = anchor_y,
        .width = width,
        .height = metrics.textHeight(font),
    };
}

pub fn stackBelow(rect: Rect) f32 {
    // PORT(verified): Windows `sub_4027B0` places the next shell-font widget at
    // `prev_y + current_gap(26) + prev_text_height`. In the port, `rect.height`
    // is the authored-space text height for the current widget type.
    return rect.top + rect.height + type20_stack_gap;
}

pub fn hitRect(text_rect: Rect, state: TextButtonState) Rect {
    return pillRect(text_rect, state);
}

pub fn pillRect(text_rect: Rect, state: TextButtonState) Rect {
    return expandRect(text_rect, state.current_padding);
}

pub fn colorsForState(state: TextButtonState, disabled: bool) ButtonColors {
    var fill = lerpColor(idle_fill, hot_fill, state.hot_blend);
    var text = lerpColor(idle_text, hot_text, state.hot_blend);
    var shadow = text_shadow;
    if (disabled) {
        fill = halfColor(fill);
        text = halfColor(text);
        shadow = halfColor(shadow);
    }
    return .{
        .fill = fill,
        .text = text,
        .shadow = shadow,
    };
}

pub fn drawType20Button(
    layout: app_ui.VirtualLayout,
    art: Art,
    font: *const game_font.Loaded,
    text: []const u8,
    text_rect: Rect,
    state: TextButtonState,
    disabled: bool,
) void {
    drawTextButton(layout, art, font, .menu_button, text, text_rect, state, disabled);
}

pub fn drawTextButton(
    layout: app_ui.VirtualLayout,
    art: Art,
    font: *const game_font.Loaded,
    widget_type: WidgetType,
    text: []const u8,
    text_rect: Rect,
    state: TextButtonState,
    disabled: bool,
) void {
    const metrics = metricsForType(widget_type);
    const colors = colorsForState(state, disabled);
    const pill_rect = pillRect(text_rect, state);
    drawNineSlice(layout, art.border, pill_rect, metrics.border_edge, metrics.source_edge_fraction, colors.fill);

    const shadow_point = layout.mapPoint(text_rect.left + 2.0, text_rect.top + 2.0);
    const text_point = layout.mapPoint(text_rect.left, text_rect.top);
    const scaled_font_size = layout.scaleFloat(metrics.fontSize(font));
    font.drawText(text, shadow_point.x, shadow_point.y, scaled_font_size, colors.shadow);
    font.drawText(text, text_point.x, text_point.y, scaled_font_size, colors.text);
}

pub fn drawNineSliceFrame(
    layout: app_ui.VirtualLayout,
    texture: rl.Texture2D,
    rect: Rect,
    edge: f32,
    source_edge_fraction: f32,
    tint: rl.Color,
) void {
    drawNineSlice(layout, texture, rect, edge, source_edge_fraction, tint);
}

fn expandRect(rect: Rect, padding: f32) Rect {
    return .{
        .left = rect.left - padding,
        .top = rect.top - padding,
        .width = rect.width + padding * 2.0,
        .height = rect.height + padding * 2.0,
    };
}

fn drawNineSlice(
    layout: app_ui.VirtualLayout,
    texture: rl.Texture2D,
    rect: Rect,
    edge: f32,
    source_edge_fraction: f32,
    tint: rl.Color,
) void {
    if (rect.width <= 0.0 or rect.height <= 0.0) return;

    const texture_width = @as(f32, @floatFromInt(texture.width));
    const texture_height = @as(f32, @floatFromInt(texture.height));
    const source_edge_x = texture_width * source_edge_fraction;
    const source_edge_y = texture_height * source_edge_fraction;

    const clamped_edge_x = @min(edge, rect.width * 0.5);
    const clamped_edge_y = @min(edge, rect.height * 0.5);
    const center_width = @max(rect.width - clamped_edge_x * 2.0, 0.0);
    const center_height = @max(rect.height - clamped_edge_y * 2.0, 0.0);
    const source_center_width = @max(texture_width - source_edge_x * 2.0, 0.0);
    const source_center_height = @max(texture_height - source_edge_y * 2.0, 0.0);

    const left = rect.left;
    const top = rect.top;
    const right = rect.left + rect.width - clamped_edge_x;
    const bottom = rect.top + rect.height - clamped_edge_y;
    const center_x = rect.left + clamped_edge_x;
    const center_y = rect.top + clamped_edge_y;

    drawSlice(layout, texture, .{ .x = 0.0, .y = 0.0, .width = source_edge_x, .height = source_edge_y }, left, top, clamped_edge_x, clamped_edge_y, tint);
    drawSlice(layout, texture, .{ .x = source_edge_x, .y = 0.0, .width = source_center_width, .height = source_edge_y }, center_x, top, center_width, clamped_edge_y, tint);
    drawSlice(layout, texture, .{ .x = texture_width - source_edge_x, .y = 0.0, .width = source_edge_x, .height = source_edge_y }, right, top, clamped_edge_x, clamped_edge_y, tint);

    drawSlice(layout, texture, .{ .x = 0.0, .y = source_edge_y, .width = source_edge_x, .height = source_center_height }, left, center_y, clamped_edge_x, center_height, tint);
    drawSlice(layout, texture, .{ .x = source_edge_x, .y = source_edge_y, .width = source_center_width, .height = source_center_height }, center_x, center_y, center_width, center_height, tint);
    drawSlice(layout, texture, .{ .x = texture_width - source_edge_x, .y = source_edge_y, .width = source_edge_x, .height = source_center_height }, right, center_y, clamped_edge_x, center_height, tint);

    drawSlice(layout, texture, .{ .x = 0.0, .y = texture_height - source_edge_y, .width = source_edge_x, .height = source_edge_y }, left, bottom, clamped_edge_x, clamped_edge_y, tint);
    drawSlice(layout, texture, .{ .x = source_edge_x, .y = texture_height - source_edge_y, .width = source_center_width, .height = source_edge_y }, center_x, bottom, center_width, clamped_edge_y, tint);
    drawSlice(layout, texture, .{ .x = texture_width - source_edge_x, .y = texture_height - source_edge_y, .width = source_edge_x, .height = source_edge_y }, right, bottom, clamped_edge_x, clamped_edge_y, tint);
}

fn drawSlice(
    layout: app_ui.VirtualLayout,
    texture: rl.Texture2D,
    source: rl.Rectangle,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    if (local_width <= 0.0 or local_height <= 0.0) return;
    rl.drawTexturePro(
        texture,
        source,
        layout.mapRect(local_x, local_y, local_width, local_height),
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        tint,
    );
}

fn alignedTextRect(width: f32, height: f32, anchor_y: f32, alignment: WidgetAlignment, anchor_x: f32) Rect {
    const base_x = switch (alignment) {
        .absolute => anchor_x,
        .left, .center, .right => 320.0 + anchor_x,
    };
    return .{
        .left = switch (alignment) {
            .absolute, .left => base_x,
            .center => base_x - width * 0.5,
            .right => base_x - width,
        },
        .top = anchor_y,
        .width = width,
        .height = height,
    };
}

fn stepValue(current: f32, target: f32) f32 {
    const stepped = current + (target - current) * hover_lerp;
    if (@abs(target - stepped) < 0.001) return target;
    return stepped;
}

fn lerpColor(a: rl.Color, b: rl.Color, t: f32) rl.Color {
    const clamped_t = std.math.clamp(t, 0.0, 1.0);
    return .{
        .r = lerpChannel(a.r, b.r, clamped_t),
        .g = lerpChannel(a.g, b.g, clamped_t),
        .b = lerpChannel(a.b, b.b, clamped_t),
        .a = lerpChannel(a.a, b.a, clamped_t),
    };
}

fn lerpChannel(a: u8, b: u8, t: f32) u8 {
    return @intFromFloat(@round(@as(f32, @floatFromInt(a)) + (@as(f32, @floatFromInt(b)) - @as(f32, @floatFromInt(a))) * t));
}

fn halfColor(color: rl.Color) rl.Color {
    return .{
        .r = color.r / 2,
        .g = color.g / 2,
        .b = color.b / 2,
        .a = color.a / 2,
    };
}

fn colorFromBytes(r: u8, g: u8, b: u8, a: u8) rl.Color {
    return .{ .r = r, .g = g, .b = b, .a = a };
}

test "type20 text rect is centered around 320 plus offset" {
    const rect = alignedTextRect(80.0, 44.2, 90.0, .center, type20_center_offset_x);
    try std.testing.expectEqual(@as(f32, 300.0), rect.left);
    try std.testing.expectEqual(@as(f32, 90.0), rect.top);
    try std.testing.expectEqual(@as(f32, 80.0), rect.width);
    try std.testing.expectApproxEqAbs(@as(f32, 44.2), rect.height, 0.001);
}

test "left aligned text rect uses the authored x anchor directly from center offset space" {
    const rect = alignedTextRect(80.0, 44.2, 111.0, .left, -228.0);
    try std.testing.expectEqual(@as(f32, 92.0), rect.left);
    try std.testing.expectEqual(@as(f32, 111.0), rect.top);
    try std.testing.expectEqual(@as(f32, 80.0), rect.width);
}

test "right aligned text rect ends at the authored anchor" {
    const rect = alignedTextRect(80.0, 44.2, 111.0, .right, 160.0);
    try std.testing.expectEqual(@as(f32, 400.0), rect.left);
    try std.testing.expectEqual(@as(f32, 111.0), rect.top);
    try std.testing.expectEqual(@as(f32, 80.0), rect.width);
}

test "stack below uses the recovered 26 pixel gap" {
    const rect = Rect{ .left = 0.0, .top = 90.0, .width = 80.0, .height = 44.2 };
    try std.testing.expectApproxEqAbs(@as(f32, 160.2), stackBelow(rect), 0.001);
}
