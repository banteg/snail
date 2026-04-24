const std = @import("std");
const rl = @import("raylib");

const frontend_widget = @import("widget.zig");
const ui = @import("../ui.zig");

pub const TextAlign = enum {
    left,
    center,
    right,
};

fn context(state: anytype) ui.Context {
    return .{ .font = &state.ui_font };
}

pub fn drawText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    ui.drawText(context(state), text, x, y, font_size, color);
}

pub fn measureText(state: anytype, text: []const u8, font_size: i32) i32 {
    return ui.measureText(context(state), text, font_size);
}

pub fn drawTextAligned(
    state: anytype,
    layout: ui.VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
    alignment: TextAlign,
) void {
    const point = layout.mapPoint(local_x, local_y);
    const font_size = layout.fontSize(authored_size);
    const width = measureText(state, text, font_size);
    const draw_x = switch (alignment) {
        .left => @as(i32, @intFromFloat(point.x)),
        .center => @as(i32, @intFromFloat(point.x)) - @divTrunc(width, 2),
        .right => @as(i32, @intFromFloat(point.x)) - width,
    };
    drawText(state, text, draw_x, @intFromFloat(point.y), font_size, color);
}

pub fn drawHeading(
    state: anytype,
    layout: ui.VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    alignment: TextAlign,
    color: rl.Color,
) void {
    drawTextAligned(state, layout, local_x + 2.0, local_y + 2.0, text, authored_size, .{ .r = 30, .g = 10, .b = 28, .a = 224 }, alignment);
    drawTextAligned(state, layout, local_x, local_y, text, authored_size, color, alignment);
}

fn phaseShowsCursor(phase: anytype) bool {
    return switch (phase) {
        .main_menu,
        .new_game_menu,
        .challenge_setup_menu,
        .options_menu,
        .pause_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .thanks_screen,
        .help,
        => true,
        .boot, .intro, .credits, .level => false,
    };
}

fn drawCursorRocket(state: anytype, layout: ui.VirtualLayout, local_x: f32, local_y: f32) void {
    const loaded_texture = state.frontend_cursor_texture orelse return;
    const destination = layout.mapRect(
        local_x - frontend_widget.cursor_hotspot_x,
        local_y - frontend_widget.cursor_hotspot_y,
        frontend_widget.cursor_size,
        frontend_widget.cursor_size,
    );
    rl.drawTexturePro(
        loaded_texture.texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        destination,
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        .white,
    );
}

pub fn drawCursorOverlay(state: anytype, layout: ui.VirtualLayout) void {
    if (state.command != .game) return;
    if (!phaseShowsCursor(state.game_phase)) return;
    const local_mouse = state.currentFrontendMouseLocal() orelse return;
    drawCursorRocket(state, layout, local_mouse.x, local_mouse.y);
}

pub fn drawStatusMessage(state: anytype, layout: ui.VirtualLayout, message: []const u8) !void {
    try drawNoticeBlock(state, layout, ui.authored_width * 0.5, 438.0, message, .ray_white);
}

pub fn drawNoticeBlock(
    state: anytype,
    layout: ui.VirtualLayout,
    center_x: f32,
    local_y: f32,
    message: []const u8,
    color: rl.Color,
) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;
    var parts = std.mem.tokenizeAny(u8, message, ">\n");
    while (parts.next()) |part| {
        const trimmed = std.mem.trim(u8, part, " \t\r");
        if (trimmed.len == 0) continue;
        const clipped = if (trimmed.len > line_buffer.len - 1) trimmed[0 .. line_buffer.len - 1] else trimmed;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        drawTextAligned(
            state,
            layout,
            center_x,
            local_y + @as(f32, @floatFromInt(line_index * 20)),
            line_buffer[0..clipped.len],
            20,
            color,
            .center,
        );
        line_index += 1;
    }
}
