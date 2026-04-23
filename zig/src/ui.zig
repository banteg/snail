const std = @import("std");
const rl = @import("raylib");
const game_font = @import("game_font.zig");

pub const authored_width: f32 = 640.0;
pub const authored_height: f32 = 480.0;

pub const Context = struct {
    font: *const game_font.Loaded,
};

pub const VirtualLayout = struct {
    x: f32,
    y: f32,
    width: f32,
    height: f32,
    scale: f32,

    pub fn mapPoint(self: VirtualLayout, local_x: f32, local_y: f32) rl.Vector2 {
        return .{
            .x = self.x + local_x * self.scale,
            .y = self.y + local_y * self.scale,
        };
    }

    pub fn unmapPoint(self: VirtualLayout, screen_x: f32, screen_y: f32) rl.Vector2 {
        return .{
            .x = (screen_x - self.x) / self.scale,
            .y = (screen_y - self.y) / self.scale,
        };
    }

    pub fn containsScreenPoint(self: VirtualLayout, screen_x: f32, screen_y: f32) bool {
        return screen_x >= self.x and screen_x <= self.x + self.width and screen_y >= self.y and screen_y <= self.y + self.height;
    }

    pub fn mapRect(self: VirtualLayout, local_x: f32, local_y: f32, local_width: f32, local_height: f32) rl.Rectangle {
        return .{
            .x = self.x + local_x * self.scale,
            .y = self.y + local_y * self.scale,
            .width = local_width * self.scale,
            .height = local_height * self.scale,
        };
    }

    pub fn scaleFloat(self: VirtualLayout, value: f32) f32 {
        return value * self.scale;
    }

    pub fn scaleInt(self: VirtualLayout, value: i32) i32 {
        return @intFromFloat(@round(@as(f32, @floatFromInt(value)) * self.scale));
    }

    pub fn fontSize(self: VirtualLayout, authored_size: i32) i32 {
        return @max(self.scaleInt(authored_size), 1);
    }
};

pub fn virtualLayout(bounds: rl.Rectangle) VirtualLayout {
    const scale = @min(bounds.width / authored_width, bounds.height / authored_height);
    const width = authored_width * scale;
    const height = authored_height * scale;
    return .{
        .x = bounds.x + (bounds.width - width) * 0.5,
        .y = bounds.y + (bounds.height - height) * 0.5,
        .width = width,
        .height = height,
        .scale = scale,
    };
}

pub const MenuPanels = struct {
    menu_panel: rl.Rectangle,
    detail_panel: rl.Rectangle,
    footer_panel: rl.Rectangle,
    title_x: i32,
    title_y: i32,
    detail_title_x: i32,
    detail_title_y: i32,
    detail_body_x: i32,
    detail_body_y: i32,
    detail_width: i32,
    control_x: i32,
    control_y: i32,
};

pub fn menuPanels(layout: VirtualLayout) MenuPanels {
    return .{
        .menu_panel = layout.mapRect(56.0, 104.0, 220.0, 250.0),
        .detail_panel = layout.mapRect(292.0, 104.0, 248.0, 250.0),
        .footer_panel = layout.mapRect(56.0, 370.0, 484.0, 38.0),
        .title_x = @intFromFloat(layout.mapPoint(72.0, 78.0).x),
        .title_y = @intFromFloat(layout.mapPoint(72.0, 78.0).y),
        .detail_title_x = @intFromFloat(layout.mapPoint(312.0, 126.0).x),
        .detail_title_y = @intFromFloat(layout.mapPoint(312.0, 126.0).y),
        .detail_body_x = @intFromFloat(layout.mapPoint(312.0, 168.0).x),
        .detail_body_y = @intFromFloat(layout.mapPoint(312.0, 168.0).y),
        .detail_width = @intFromFloat(layout.mapRect(292.0, 104.0, 248.0, 250.0).width - layout.scaleFloat(36.0)),
        .control_x = @intFromFloat(layout.mapPoint(312.0, 250.0).x),
        .control_y = @intFromFloat(layout.mapPoint(312.0, 250.0).y),
    };
}

pub fn drawText(context: Context, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    context.font.drawText(text, @floatFromInt(x), @floatFromInt(y), @floatFromInt(font_size), color);
}

pub fn measureText(context: Context, text: []const u8, font_size: i32) i32 {
    return @intFromFloat(@ceil(context.font.measureText(text, @floatFromInt(font_size))));
}

pub fn drawWrappedText(context: Context, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;

    var parts = std.mem.splitScalar(u8, text, '>');
    while (parts.next()) |part| {
        const clipped = if (part.len > line_buffer.len - 1) part[0 .. line_buffer.len - 1] else part;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        _ = max_width;
        drawText(context, line_buffer[0..clipped.len], x, y + line_index * line_height, line_height, color);
        line_index += 1;
    }
}

pub fn drawMenuItem(context: Context, layout: VirtualLayout, index: usize, selected_index: usize, label: []const u8) void {
    const active = index == selected_index;
    const row_rect = layout.mapRect(68.0, 128.0 + @as(f32, @floatFromInt(index)) * 42.0, 196.0, 32.0);
    const label_point = layout.mapPoint(84.0, 136.0 + @as(f32, @floatFromInt(index)) * 42.0);

    if (active) {
        rl.drawRectangleRounded(row_rect, 0.25, 8, .orange);
    }
    drawText(context, label, @intFromFloat(label_point.x), @intFromFloat(label_point.y), layout.fontSize(24), if (active) .black else .ray_white);
}

pub fn drawOptionsSliderRow(context: Context, layout: VirtualLayout, label: []const u8, value: f32, panels: MenuPanels) !void {
    var value_buffer: [64]u8 = undefined;
    const value_text = try std.fmt.bufPrint(&value_buffer, "{s}: {d:.2}", .{ label, value });
    drawText(context, value_text, panels.detail_body_x, panels.detail_body_y + layout.scaleInt(64), layout.fontSize(20), .sky_blue);

    const bar_rect = rl.Rectangle{
        .x = @floatFromInt(panels.detail_body_x),
        .y = @floatFromInt(panels.detail_body_y + layout.scaleInt(96)),
        .width = @floatFromInt(@min(panels.detail_width, layout.scaleInt(240))),
        .height = layout.scaleFloat(18.0),
    };
    rl.drawRectangleRounded(bar_rect, 0.24, 8, .{ .r = 255, .g = 255, .b = 255, .a = 26 });
    rl.drawRectangleRounded(
        .{
            .x = bar_rect.x + layout.scaleFloat(2.0),
            .y = bar_rect.y + layout.scaleFloat(2.0),
            .width = (bar_rect.width - layout.scaleFloat(4.0)) * std.math.clamp(value, 0.0, 1.0),
            .height = bar_rect.height - layout.scaleFloat(4.0),
        },
        0.24,
        8,
        .gold,
    );
}

pub fn drawRouteSelectionDots(context: Context, layout: VirtualLayout, panels: MenuPanels, current_index: usize, max_index: usize) void {
    const visible_count: usize = @min(max_index, 8);
    if (visible_count == 0) return;

    const start_index = if (current_index > 4 and max_index > visible_count)
        @min(current_index - 3, max_index - visible_count + 1)
    else
        1;
    const center_y = @as(f32, @floatFromInt(panels.detail_body_y + layout.scaleInt(146)));
    const start_x = @as(f32, @floatFromInt(panels.detail_body_x + layout.scaleInt(10)));
    const spacing = layout.scaleFloat(30.0);

    for (0..visible_count) |visible_offset| {
        const route_index = start_index + visible_offset;
        const active = route_index == current_index;
        const unlocked = route_index <= max_index;
        const center_x = start_x + @as(f32, @floatFromInt(visible_offset)) * spacing;
        rl.drawCircleV(
            .{ .x = center_x, .y = center_y },
            if (active) layout.scaleFloat(8.0) else layout.scaleFloat(6.0),
            if (active)
                .gold
            else if (unlocked)
                .sky_blue
            else
                .dark_gray,
        );

        var label_buffer: [8]u8 = undefined;
        const label = std.fmt.bufPrint(&label_buffer, "{d}", .{route_index}) catch "?";
        drawText(context, label, @intFromFloat(center_x - layout.scaleFloat(4.0)), @intFromFloat(center_y + layout.scaleFloat(14.0)), layout.fontSize(14), .ray_white);
    }
}
