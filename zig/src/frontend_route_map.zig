const rl = @import("raylib");
const frontend_bridge = @import("frontend_bridge.zig");
const frontend_widget = @import("frontend_widget.zig");
const galaxy = @import("galaxy.zig");
const game_font = @import("game_font.zig");

// PORT(verified): `initialize_galaxy` places the Star Map title at `(15,15)` with shell-font
// scale `0.83`, the bottom Back/Exit control at `(20,420)` with absolute alignment, and
// `open_galaxy_route` seeds the selected route card from `(route_x + 60, route_y - 130)`.
pub const title_x: f32 = 15.0;
pub const title_y: f32 = 15.0;
pub const title_scale: f32 = 0.83;
// PORT(verified): `initialize_galaxy` seeds sprite `138` at `(300,10)`. The shipped
// `SPACEMAPLOGO.TGA` art is `256x64`, and the Windows sprite path uses that authored size.
pub const logo_x: f32 = 300.0;
pub const logo_y: f32 = 10.0;
pub const logo_width: f32 = 256.0;
pub const logo_height: f32 = 64.0;
pub const back_x: f32 = 20.0;
pub const back_y: f32 = 420.0;
pub const card_title_scale: f32 = 0.9;
pub const card_subtitle_scale: f32 = 0.9;
pub const card_body_scale: f32 = 0.7;
// PORT(verified): `open_galaxy_route` expands the selected card bounds by `8` on the
// left/right and bottom edges only. The top edge stays anchored to the title widget.
pub const card_horizontal_padding: f32 = 8.0;
pub const card_bottom_padding: f32 = 8.0;
pub const card_horizontal_pointer_gap: f32 = 6.0;
pub const card_star_gap: f32 = 16.0;
pub const card_right_limit: f32 = 631.0;
pub const card_min_top: f32 = 49.0;
pub const card_bottom_y: f32 = 450.0;
pub const card_text_gap: f32 = 0.0;
pub const primary_button_gap: f32 = 20.0;
pub const replay_button_gap: f32 = 10.0;
// PORT(verified): `sub_401130` renders the selected route card (`69516`) as a type-20 style
// 9-slice frame with a recovered authored edge size of `26.0`, not as a stretched quad.
pub const card_frame_edge: f32 = 26.0;
// PORT(verified): `update_galaxy` draws galaxy sprites `139..148` as `256x256` quads
// centered on the transformed `sub_4088E0` points, and the inter-route connector uses
// `LINE.TGA` at width `4.0`.
pub const galaxy_size: f32 = 256.0;
pub const path_line_width: f32 = 4.0;

pub const CardLayout = struct {
    card_rect: frontend_widget.Rect,
    title_rect: frontend_widget.Rect,
    subtitle_rect: frontend_widget.Rect,
    body_rect: frontend_widget.Rect,
    primary_text_rect: frontend_widget.Rect,
    replay_text_rect: ?frontend_widget.Rect,
    pointer_start: galaxy.Point,
    pointer_end: galaxy.Point,
};

pub fn backLabel(screen_mode: frontend_bridge.RouteMapScreenMode) []const u8 {
    return frontend_bridge.routeMapBackLabelForScreenMode(screen_mode);
}

pub fn backTextRect(font: *const game_font.Loaded, screen_mode: frontend_bridge.RouteMapScreenMode) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(font, .menu_button, .absolute, backLabel(screen_mode), back_y, back_x);
}

pub fn bodyText(maybe_text: ?[]const u8) []const u8 {
    // PORT(verified): `open_galaxy_route` copies the route body from the per-route record
    // once when the card opens. `update_galaxy` does not swap that body text based on
    // hover state or selected action.
    return maybe_text orelse "";
}

pub fn pointForRouteIndex(maybe_names: ?*const galaxy.Definition, route_index: usize) ?galaxy.Point {
    if (maybe_names) |names| {
        if (names.routePointForRouteIndex(route_index)) |point| return point;
    }
    return galaxy.routePointForRouteIndex(route_index);
}

pub fn hoveredRouteIndex(maybe_names: ?*const galaxy.Definition, local_mouse: rl.Vector2, route_limit: usize) ?usize {
    if (route_limit == 0) return null;

    const selection_radius_squared = 17.0 * 17.0;
    for (1..@min(route_limit, galaxy.map_route_count) + 1) |route_index| {
        const point = pointForRouteIndex(maybe_names, route_index) orelse continue;
        const dx = point.x - local_mouse.x;
        const dy = point.y - local_mouse.y;
        if (dx * dx + dy * dy < selection_radius_squared) {
            return route_index;
        }
    }
    return null;
}

pub fn cardLayout(
    font: *const game_font.Loaded,
    route_point: galaxy.Point,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) CardLayout {
    var title_left = route_point.x + 60.0;
    var title_top = route_point.y - 130.0;

    while (true) {
        const title_rect = uiFontTextRectAbsolute(font, route_galaxy_name, title_left, title_top, card_title_scale);
        const subtitle_rect = uiFontTextRectAbsolute(
            font,
            route_level_name,
            title_left,
            frontend_widget.stackBelowWithGap(title_rect, card_text_gap),
            card_subtitle_scale,
        );
        const body_rect = uiFontTextRectAbsolute(
            font,
            route_body,
            title_left,
            frontend_widget.stackBelowWithGap(subtitle_rect, card_text_gap),
            card_body_scale,
        );
        const title_center_offset = title_rect.left + title_rect.width * 0.5 - 320.0;

        var primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            frontend_widget.stackBelowWithGap(body_rect, primary_button_gap),
            title_center_offset,
        );
        var replay_text_rect: ?frontend_widget.Rect = null;
        if (replay_action) |label| {
            replay_text_rect = frontend_widget.widgetTextRect(
                font,
                .route_map_secondary_action,
                .center,
                label,
                frontend_widget.stackBelowWithGap(body_rect, replay_button_gap),
                title_center_offset,
            );
            primary_text_rect = frontend_widget.widgetTextRect(
                font,
                .menu_button,
                .center,
                primary_action,
                frontend_widget.stackBelowWithGap(replay_text_rect.?, primary_button_gap),
                title_center_offset,
            );
        }

        var left = @min(title_rect.left, @min(subtitle_rect.left, @min(body_rect.left, primary_text_rect.left)));
        const top = @min(title_rect.top, @min(subtitle_rect.top, @min(body_rect.top, primary_text_rect.top)));
        var right = @max(
            title_rect.left + title_rect.width,
            @max(
                subtitle_rect.left + subtitle_rect.width,
                @max(body_rect.left + body_rect.width, primary_text_rect.left + primary_text_rect.width),
            ),
        );
        var bottom = @max(
            title_rect.top + title_rect.height,
            @max(
                subtitle_rect.top + subtitle_rect.height,
                @max(body_rect.top + body_rect.height, primary_text_rect.top + primary_text_rect.height),
            ),
        );
        left -= card_horizontal_padding;
        right += card_horizontal_padding;
        bottom += card_bottom_padding;

        var adjusted = false;
        if (right > card_right_limit) {
            title_left = route_point.x - (right - left) - 40.0;
            adjusted = true;
        }
        if (top < card_min_top) {
            title_top = 50.0;
            adjusted = true;
        }
        if (bottom > card_bottom_y) {
            title_top = card_bottom_y - (bottom - top);
            adjusted = true;
        }
        if (adjusted) continue;

        const card_rect: frontend_widget.Rect = .{
            .left = left,
            .top = top,
            .width = right - left,
            .height = bottom - top,
        };
        const card_center_offset = card_rect.left + card_rect.width * 0.5 - 320.0;
        primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            primary_text_rect.top,
            card_center_offset,
        );
        if (replay_action) |label| {
            if (replay_text_rect) |replay_rect| {
                replay_text_rect = frontend_widget.widgetTextRect(
                    font,
                    .route_map_secondary_action,
                    .center,
                    label,
                    replay_rect.top,
                    card_center_offset,
                );
            }
        }
        const pointer_start_x = if (card_rect.left <= route_point.x)
            route_point.x - card_star_gap
        else
            route_point.x + card_star_gap;
        const pointer_end_x = if (card_rect.left <= route_point.x)
            card_rect.left + card_rect.width + card_horizontal_pointer_gap
        else
            card_rect.left - card_horizontal_pointer_gap;
        return .{
            .card_rect = card_rect,
            .title_rect = title_rect,
            .subtitle_rect = subtitle_rect,
            .body_rect = body_rect,
            .primary_text_rect = primary_text_rect,
            .replay_text_rect = replay_text_rect,
            .pointer_start = .{ .x = pointer_start_x, .y = route_point.y },
            .pointer_end = .{ .x = pointer_end_x, .y = route_point.y },
        };
    }
}

fn scaledUiFontSize(font: *const game_font.Loaded, text_scale: f32) f32 {
    return font.nominal_height * text_scale;
}

fn multilineUiTextHeight(font: *const game_font.Loaded, text: []const u8, text_scale: f32) f32 {
    if (text.len == 0) return 0.0;
    var line_count: usize = 1;
    for (text) |byte| {
        if (byte == '\n') line_count += 1;
    }
    return @as(f32, @floatFromInt(line_count)) * scaledUiFontSize(font, text_scale);
}

fn uiFontTextRectAbsolute(font: *const game_font.Loaded, text: []const u8, left: f32, top: f32, text_scale: f32) frontend_widget.Rect {
    const font_size = scaledUiFontSize(font, text_scale);
    return .{
        .left = left,
        .top = top,
        .width = font.measureText(text, font_size),
        .height = multilineUiTextHeight(font, text, text_scale),
    };
}
