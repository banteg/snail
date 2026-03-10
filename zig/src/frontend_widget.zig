const std = @import("std");
const rl = @import("raylib");
const app_ui = @import("app_ui.zig");
const game_font = @import("game_font.zig");

pub const WidgetType = enum(u8) {
    menu_button = 20,
    slider_value = 21,
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

pub const SliderDirection = enum {
    less,
    more,
};

pub const SliderTextures = struct {
    less: ?rl.Texture2D = null,
    less_hover: ?rl.Texture2D = null,
    more: ?rl.Texture2D = null,
    more_hover: ?rl.Texture2D = null,
    bar: ?rl.Texture2D = null,
    bar_full: ?rl.Texture2D = null,
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
// PORT(verified): the `0x100000` slider-widget path lays out its child sprites at these
// authored offsets during `layout_frontend_widget`, overriding the constructor's temporary
// `+40` seed. The track itself is drawn by `draw_frontend_widget` as a 256x32 strip at
// `row_top + 50`.
pub const slider_arrow_size: f32 = 64.0;
pub const slider_bar_width: f32 = 256.0;
pub const slider_bar_height: f32 = 32.0;
pub const slider_bar_y_offset: f32 = 50.0;
pub const slider_arrow_y_offset: f32 = 33.0;
pub const slider_value_y_offset: f32 = 49.0;
pub const slider_left_arrow_left: f32 = 118.0;
pub const slider_right_arrow_left: f32 = 458.0;
// PORT(partial): Windows stacks the next options row using the previous widget's computed
// `+588` height after the slider children are attached. The exact stored height is not
// surfaced as a literal in the recovered snippets; `86` still matches the live screen
// spacing and reference captures.
pub const slider_stack_height: f32 = 86.0;

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
        .slider_value => .{
            // PORT(verified): `sub_401D30(..., widget_type=21, ...)` is the slider readout
            // child path. It keeps the type-20 shell border metrics but drops text scale to 1.0.
            .text_scale = 1.0,
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
    return stackBelowWithGap(rect, type20_stack_gap);
}

pub fn stackBelowWithGap(rect: Rect, child_gap: f32) f32 {
    // PORT(verified): `stack_widget_below` copies the previous widget's authored-space
    // X anchor, then places the child at `prev_y + prev_height + child_gap`.
    return rect.top + rect.height + child_gap;
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
    // PORT(partial): the recovered `draw_frontend_widget` path does not show an explicit
    // second text draw, but removing this offset dark pass made the menu captures diverge
    // materially from the shipped reference frames. Keep the current shell-font treatment
    // until the lower-level text flush path is recovered more precisely.
    font.drawText(text, shadow_point.x, shadow_point.y, scaled_font_size, colors.shadow);
    font.drawText(text, text_point.x, text_point.y, scaled_font_size, colors.text);
}

pub fn sliderStackBelow(rect: Rect) f32 {
    return rect.top + slider_stack_height + type20_stack_gap;
}

pub fn sliderBarRect(text_rect: Rect) Rect {
    return .{
        .left = text_rect.centerX() - slider_bar_width * 0.5,
        .top = text_rect.top + slider_bar_y_offset,
        .width = slider_bar_width,
        .height = slider_bar_height,
    };
}

pub fn sliderArrowRect(text_rect: Rect, direction: SliderDirection) Rect {
    return .{
        .left = switch (direction) {
            .less => slider_left_arrow_left,
            .more => slider_right_arrow_left,
        },
        .top = text_rect.top + slider_arrow_y_offset,
        .width = slider_arrow_size,
        .height = slider_arrow_size,
    };
}

pub fn sliderValueTextRect(font: *const game_font.Loaded, text_rect: Rect, text: []const u8) Rect {
    return widgetTextRect(font, .slider_value, .center, text, text_rect.top + slider_value_y_offset, 0.0);
}

pub fn sliderFrameRect(
    font: *const game_font.Loaded,
    text_rect: Rect,
    row_state: TextButtonState,
    value_text: []const u8,
) Rect {
    const base_rect = pillRect(text_rect, row_state);
    const bar_rect = sliderBarRect(text_rect);
    const less_rect = sliderArrowRect(text_rect, .less);
    const more_rect = sliderArrowRect(text_rect, .more);
    const value_rect = pillRect(sliderValueTextRect(font, text_rect, value_text), row_state);
    const bottom = @max(
        value_rect.top + value_rect.height,
        @max(
            bar_rect.top + bar_rect.height + row_state.current_padding,
            @max(less_rect.top + less_rect.height, more_rect.top + more_rect.height),
        ),
    );
    return .{
        .left = base_rect.left,
        .top = base_rect.top,
        .width = base_rect.width,
        .height = bottom - base_rect.top,
    };
}

pub fn drawSliderMenuRow(
    layout: app_ui.VirtualLayout,
    art: Art,
    slider_textures: SliderTextures,
    font: *const game_font.Loaded,
    title_text: []const u8,
    text_rect: Rect,
    value_text: []const u8,
    normalized_value: f32,
    displayed_value: f32,
    row_state: TextButtonState,
    less_hovered: bool,
    more_hovered: bool,
) void {
    const clamped_value = std.math.clamp(normalized_value, 0.0, 1.0);
    const displayed_clamped_value = std.math.clamp(displayed_value, 0.0, 1.0);
    const colors = colorsForState(row_state, false);
    const frame_rect = sliderFrameRect(font, text_rect, row_state, value_text);
    const bar_rect = sliderBarRect(text_rect);
    const less_rect = sliderArrowRect(text_rect, .less);
    const more_rect = sliderArrowRect(text_rect, .more);
    const value_rect = sliderValueTextRect(font, text_rect, value_text);
    const title_metrics = metricsForType(.menu_button);

    drawNineSliceFrame(layout, art.border, frame_rect, type20_border_edge, type20_border_edge / 128.0, colors.fill);

    const shadow_point = layout.mapPoint(text_rect.left + 2.0, text_rect.top + 2.0);
    const text_point = layout.mapPoint(text_rect.left, text_rect.top);
    const scaled_font_size = layout.scaleFloat(title_metrics.fontSize(font));
    font.drawText(title_text, shadow_point.x, shadow_point.y, scaled_font_size, colors.shadow);
    font.drawText(title_text, text_point.x, text_point.y, scaled_font_size, colors.text);

    if (slider_textures.bar) |texture| {
        drawTextureLocalRect(layout, texture, bar_rect.left, bar_rect.top, bar_rect.width, bar_rect.height, .white);
    } else {
        rl.drawRectangleRounded(layout.mapRect(bar_rect.left, bar_rect.top, bar_rect.width, bar_rect.height), 0.45, 8, .{ .r = 188, .g = 94, .b = 44, .a = 232 });
    }
    if (slider_textures.bar_full) |texture| {
        drawTextureLocalRectSource(
            layout,
            texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @as(f32, @floatFromInt(texture.width)) * displayed_clamped_value,
                .height = @as(f32, @floatFromInt(texture.height)),
            },
            bar_rect.left,
            bar_rect.top,
            bar_rect.width * displayed_clamped_value,
            bar_rect.height,
            .white,
        );
    } else {
        rl.drawRectangleRounded(
            .{
                .x = layout.mapPoint(bar_rect.left, bar_rect.top).x,
                .y = layout.mapPoint(bar_rect.left, bar_rect.top).y,
                .width = layout.scaleFloat(bar_rect.width * displayed_clamped_value),
                .height = layout.scaleFloat(bar_rect.height),
            },
            0.45,
            8,
            .{ .r = 252, .g = 198, .b = 40, .a = 255 },
        );
    }

    const less_disabled = clamped_value <= 0.001;
    const more_disabled = clamped_value >= 0.999;
    const less_texture = if (less_hovered and !less_disabled)
        slider_textures.less_hover orelse slider_textures.less
    else
        slider_textures.less;
    const more_texture = if (more_hovered and !more_disabled)
        slider_textures.more_hover orelse slider_textures.more
    else
        slider_textures.more;
    if (less_texture) |texture| {
        drawTextureLocalRect(layout, texture, less_rect.left, less_rect.top, less_rect.width, less_rect.height, if (less_disabled) .{ .r = 255, .g = 255, .b = 255, .a = 128 } else .white);
    }
    if (more_texture) |texture| {
        drawTextureLocalRect(layout, texture, more_rect.left, more_rect.top, more_rect.width, more_rect.height, if (more_disabled) .{ .r = 255, .g = 255, .b = 255, .a = 128 } else .white);
    }

    drawTextButton(layout, art, font, .slider_value, value_text, value_rect, row_state, false);
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

fn drawTextureLocalRectSource(
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

fn drawTextureLocalRect(
    layout: app_ui.VirtualLayout,
    texture: rl.Texture2D,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRectSource(
        layout,
        texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(texture.width)),
            .height = @as(f32, @floatFromInt(texture.height)),
        },
        local_x,
        local_y,
        local_width,
        local_height,
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

test "slider arrow rect uses the recovered authored offsets" {
    const text_rect = Rect{ .left = 260.0, .top = 153.0, .width = 120.0, .height = 44.2 };
    const less_rect = sliderArrowRect(text_rect, .less);
    const more_rect = sliderArrowRect(text_rect, .more);
    try std.testing.expectEqual(@as(f32, 118.0), less_rect.left);
    try std.testing.expectEqual(@as(f32, 458.0), more_rect.left);
    try std.testing.expectEqual(@as(f32, 186.0), less_rect.top);
    try std.testing.expectEqual(@as(f32, 186.0), more_rect.top);
}
