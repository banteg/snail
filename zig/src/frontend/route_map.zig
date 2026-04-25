const std = @import("std");
const rl = @import("raylib");
const ui = @import("../ui.zig");
const assets = @import("../assets.zig");
const frontend = @import("../frontend.zig");
const frontend_bridge = @import("bridge.zig");
const frontend_widget = @import("widget.zig");
const galaxy = @import("../galaxy.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

pub const actions_without_replay = [_]frontend.RouteMenuAction{
    .play,
    .back,
};

pub const actions_with_replay = [_]frontend.RouteMenuAction{
    .play,
    .watch_best_trial,
    .back,
};

pub const actions_closed = [_]frontend.RouteMenuAction{
    .back,
};
pub const button_count: usize = 3;
pub const primary_button_index: usize = 0;
pub const replay_button_index: usize = 1;
pub const back_button_index: usize = 2;

pub const HoverState = enum(u8) {
    none = 0,
    card = 1,
    route = 2,
};

// PORT(verified): `initialize_galaxy` places the Star Map title at `(15,15)` with shell-font
// scale `0.83`, the bottom Back/Exit control at `(20,420)` with absolute alignment, and
// `open_galaxy_route` seeds the selected route card from `(route_x + 60, route_y - 130)`.
pub const title_x: f32 = 15.0;
pub const title_y: f32 = 15.0;
pub const title_scale: f32 = 0.83;
// PORT(verified): `initialize_galaxy` seeds sprite `138` at `(370,10)`. The generic
// widget layout then clamps it by the 15px sprite hot padding to authored x=369 because
// `SPACEMAPLOGO.TGA` is `256x64`.
pub const logo_x: f32 = 369.0;
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
// PORT(verified): `sub_401130` renders the selected route card (`69516`) as a menu-button-style
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

pub fn drawMenuUi(state: anytype, layout: VirtualLayout) void {
    const mode = state.frontend_route_mode orelse return;
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    drawStars(state, layout, mode);
    drawUiFontTextAbsolute(state, layout, "Intergalactic Delivery Route", title_x, title_y, title_scale, .ray_white);
    drawLogo(state, layout);
    if (state.currentRouteMapOpenIndex()) |route_index| {
        const route_galaxy_name = state.currentFrontendGalaxyName() orelse frontend.frontendRouteModeLabel(mode);
        const route_level_name = if (state.frontend_route_level) |loaded_level| loaded_level.name else "Route";
        const route_body = bodyText(if (state.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
        const primary_label = frontend.routeMenuActionLabel(mode, .play);
        const replay_label = if (state.routeMapShowsReplay()) frontend.routeMenuActionLabel(mode, .watch_best_trial) else null;
        const maybe_names = if (state.galaxy_names) |*names| names else null;
        if (pointForRouteIndex(maybe_names, route_index)) |route_point| {
            const layout_state = cardLayout(
                &state.ui_font,
                route_point,
                route_galaxy_name,
                route_level_name,
                route_body,
                primary_label,
                replay_label,
            );
            drawConnection(layout, layout_state.pointer_start, layout_state.pointer_end, state.route_map_art.line_star, 4.0, .white);
            drawCard(state, layout, layout_state, route_galaxy_name, route_level_name, route_body, primary_label, replay_label);
        }
    }

    frontend_widget.drawMenuButton(
        layout,
        widget_art,
        &state.ui_font,
        backLabel(state.route_map_screen_mode),
        backTextRect(&state.ui_font, state.route_map_screen_mode),
        state.route_map_button_states[back_button_index],
        false,
    );
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

fn drawUiFontTextAbsolute(
    state: anytype,
    layout: VirtualLayout,
    text: []const u8,
    left: f32,
    top: f32,
    text_scale: f32,
    color: rl.Color,
) void {
    const point = layout.mapPoint(left, top);
    state.ui_font.drawText(text, point.x, point.y, layout.scaleFloat(scaledUiFontSize(&state.ui_font, text_scale)), color);
}

fn drawUiFontTextRect(
    state: anytype,
    layout: VirtualLayout,
    text: []const u8,
    rect: frontend_widget.Rect,
    text_scale: f32,
    color: rl.Color,
) void {
    drawUiFontTextAbsolute(state, layout, text, rect.left, rect.top, text_scale, color);
}

fn drawTextureLocalRectSource(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    source: rl.Rectangle,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    if (local_width <= 0.0 or local_height <= 0.0) return;
    rl.drawTexturePro(
        loaded_texture.texture,
        source,
        layout.mapRect(local_x, local_y, local_width, local_height),
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        tint,
    );
}

fn drawTextureLocalRect(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRectSource(
        layout,
        loaded_texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        local_x,
        local_y,
        local_width,
        local_height,
        tint,
    );
}

fn drawTextureCenteredLocal(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    center_x: f32,
    center_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRect(
        layout,
        loaded_texture,
        center_x - local_width * 0.5,
        center_y - local_height * 0.5,
        local_width,
        local_height,
        tint,
    );
}

fn drawConnection(
    layout: VirtualLayout,
    start_point: galaxy.Point,
    end_point: galaxy.Point,
    line_texture: ?assets.LoadedTexture,
    authored_width: f32,
    tint: rl.Color,
) void {
    const start = layout.mapPoint(start_point.x, start_point.y);
    const end = layout.mapPoint(end_point.x, end_point.y);
    const dx = end.x - start.x;
    const dy = end.y - start.y;
    const length = std.math.sqrt(dx * dx + dy * dy);
    if (length <= 0.01) return;

    if (line_texture) |loaded_texture| {
        const scaled_width = layout.scaleFloat(authored_width);
        rl.drawTexturePro(
            loaded_texture.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
                .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
            },
            .{
                .x = start.x,
                .y = start.y,
                .width = length,
                .height = scaled_width,
            },
            .{ .x = 0.0, .y = scaled_width * 0.5 },
            @as(f32, @floatCast(std.math.atan2(dy, dx) * 180.0 / std.math.pi)),
            tint,
        );
    } else {
        rl.drawLineEx(start, end, layout.scaleFloat(authored_width), tint);
    }
}

fn drawStars(state: anytype, layout: VirtualLayout, mode: frontend.FrontendLevelMode) void {
    const available_limit = state.availableFrontendRouteLimit(mode);
    const active_route_index = state.currentRouteMapOpenIndex() orelse state.frontend_route_index;
    const selected_galaxy_index = if (state.galaxy_names) |names|
        names.galaxyIndexForRouteIndex(state.frontend_route_index)
    else
        null;
    for (0..galaxy.map_galaxy_count) |galaxy_index| {
        const center = galaxy.galaxyCenter(galaxy_index);
        if (state.route_map_art.galaxies[galaxy_index]) |loaded_texture| {
            drawTextureCenteredLocal(layout, loaded_texture, center.x, center.y, galaxy_size, galaxy_size, .white);
        }
    }

    if (state.galaxy_names) |names| {
        if (selected_galaxy_index) |galaxy_index| {
            var route_cursor: usize = 0;
            for (0..galaxy_index) |prior_index| {
                route_cursor += names.starCountForGalaxyIndex(prior_index) orelse 0;
            }
            const star_count = names.starCountForGalaxyIndex(galaxy_index) orelse 0;
            var visible_star_count = if (available_limit > route_cursor)
                @min(star_count, available_limit - route_cursor)
            else
                0;
            if (state.route_map_screen_mode == .post_completion_exit and active_route_index > route_cursor) {
                visible_star_count = @min(visible_star_count, active_route_index - route_cursor);
            }

            if (visible_star_count >= 2) {
                for (0..visible_star_count - 1) |local_index| {
                    const start_route_index = route_cursor + local_index + 1;
                    const end_route_index = start_route_index + 1;
                    if (state.route_map_screen_mode == .post_completion_exit and start_route_index >= active_route_index) continue;
                    const line_tint: rl.Color = if (start_route_index < active_route_index)
                        .{ .r = 255, .g = 255, .b = 255, .a = 204 }
                    else
                        .{ .r = 255, .g = 255, .b = 255, .a = 51 };
                    drawConnection(
                        layout,
                        names.routePointForRouteIndex(start_route_index).?,
                        names.routePointForRouteIndex(end_route_index).?,
                        state.route_map_art.line,
                        path_line_width,
                        line_tint,
                    );
                }
            }

            for (0..visible_star_count) |local_index| {
                const route_index = route_cursor + local_index + 1;
                const point = names.routePointForRouteIndex(route_index).?;
                if (state.route_map_art.level_star) |loaded_texture| {
                    drawTextureCenteredLocal(layout, loaded_texture, point.x, point.y, 32.0, 32.0, .white);
                }
            }
        }
    }

    for (1..@min(available_limit, galaxy.map_route_count) + 1) |route_index| {
        const highlight_alpha = state.route_map_route_highlight_alpha[route_index];
        if (highlight_alpha <= 0.001) continue;
        const maybe_names = if (state.galaxy_names) |*names| names else null;
        if (pointForRouteIndex(maybe_names, route_index)) |selected_point| {
            if (state.route_map_art.level_select) |loaded_texture| {
                drawTextureCenteredLocal(
                    layout,
                    loaded_texture,
                    selected_point.x,
                    selected_point.y,
                    64.0,
                    64.0,
                    .{
                        .r = 255,
                        .g = 255,
                        .b = 255,
                        .a = @intFromFloat(std.math.clamp(highlight_alpha * 255.0, 0.0, 255.0)),
                    },
                );
            }
        }
    }
}

fn drawCard(
    state: anytype,
    layout: VirtualLayout,
    layout_state: CardLayout,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) void {
    if (state.route_map_art.border) |loaded_texture| {
        frontend_widget.drawNineSliceFrame(
            layout,
            loaded_texture.texture,
            layout_state.card_rect,
            card_frame_edge,
            card_frame_edge / 128.0,
            .white,
        );
    }

    drawUiFontTextRect(state, layout, route_galaxy_name, layout_state.title_rect, card_title_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_level_name, layout_state.subtitle_rect, card_subtitle_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_body, layout_state.body_rect, card_body_scale, .ray_white);

    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    frontend_widget.drawMenuButton(
        layout,
        widget_art,
        &state.ui_font,
        primary_action,
        layout_state.primary_text_rect,
        state.route_map_button_states[primary_button_index],
        false,
    );
    if (replay_action) |label| {
        if (layout_state.replay_text_rect) |replay_text_rect| {
            frontend_widget.drawTextButton(
                layout,
                widget_art,
                &state.ui_font,
                .route_map_secondary_action,
                label,
                replay_text_rect,
                state.route_map_button_states[replay_button_index],
                false,
            );
        }
    }
}

fn drawLogo(state: anytype, layout: VirtualLayout) void {
    const loaded_texture = state.route_map_art.logo orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        logo_x,
        logo_y,
        logo_width,
        logo_height,
        .white,
    );
}
