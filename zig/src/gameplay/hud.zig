const std = @import("std");
const rl = @import("raylib");
const app_ui = @import("../app_ui.zig");
const assets = @import("../assets.zig");
const frontend_widget = @import("../frontend/widget.zig");
const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");

const VirtualLayout = app_ui.VirtualLayout;

const row_event_widget_frame_width: f32 = 88.0;
const row_event_widget_frame_height: f32 = 30.0;
const row_event_widget_frame_offset_x: f32 = -18.0;
const row_event_widget_frame_offset_y: f32 = -15.0;
const row_event_widget_icon_x: f32 = -12.0;
const row_event_widget_icon_y: f32 = -10.0;
const row_event_widget_icon_size: f32 = 20.0;
const row_event_widget_text_x: f32 = 14.0;
const row_event_widget_text_y: f32 = -9.0;
const row_event_widget_bonus_y: f32 = 18.0;

pub fn drawTutorialHud(state: anytype, layout: VirtualLayout, runner: gameplay.Runner) !void {
    const parcel_target = currentParcelTarget(state);
    const parcel_count = runner.counters.parcels;

    var parcel_buffer: [32]u8 = undefined;
    const parcel_text = if (parcel_target > 0)
        try std.fmt.bufPrint(&parcel_buffer, "{d}/{d}", .{ parcel_count, parcel_target })
    else
        try std.fmt.bufPrint(&parcel_buffer, "{d}", .{parcel_count});
    drawIconCounter(state, layout, .package, parcel_text, 12.0, 10.0, 22, .white);

    if (state.tutorial_reference_score > 0) {
        var best_buffer: [32]u8 = undefined;
        const best_text = try formatScoreWithCommas(&best_buffer, state.tutorial_reference_score);
        drawCenteredHudTextShadowed(state, layout, 320.0, 10.0, best_text, 22, .white);
    }

    var score_buffer: [32]u8 = undefined;
    const score_text = try formatScoreWithCommas(&score_buffer, runner.score.total);
    drawRightAlignedHudTextShadowed(state, layout, 628.0, 10.0, score_text, 22, .white);
}

pub fn drawStandardHud(state: anytype, layout: VirtualLayout, runner: gameplay.Runner) !void {
    const parcel_target = currentParcelTarget(state);
    const parcel_count = runner.counters.parcels;

    if (parcel_target > 0) {
        var parcel_buffer: [32]u8 = undefined;
        const parcel_text = try std.fmt.bufPrint(&parcel_buffer, "{d}/{d}", .{ parcel_count, parcel_target });
        drawIconCounter(state, layout, .package, parcel_text, 12.0, 10.0, 22, .white);
    }

    var score_buffer: [32]u8 = undefined;
    const score_text = try formatScoreWithCommas(&score_buffer, runner.score.total);
    drawCenteredHudTextShadowed(state, layout, 320.0, 10.0, score_text, 22, .white);

    var elapsed_buffer: [32]u8 = undefined;
    const elapsed_text = try formatElapsedMillis(&elapsed_buffer, runner.stopwatch.elapsedMillis());
    drawRightAlignedHudTextShadowed(state, layout, 628.0, 10.0, elapsed_text, 22, .white);
}

pub fn drawProgressBar(state: anytype, layout: VirtualLayout, runner: gameplay.Runner) void {
    const preview = state.current_track_preview orelse return;
    const total_rows = @max(preview.total_rows, 1);
    const progress = std.math.clamp(runner.row_position / @as(f32, @floatFromInt(total_rows)), 0.0, 1.0);
    const remaining_height = (1.0 - progress) * 232.0 + 12.0;
    if (state.current_gameplay_sprites.progress_bar_lit) |loaded_texture| {
        drawTextureLocalRectSource(
            layout,
            loaded_texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @floatFromInt(loaded_texture.texture.width),
                .height = remaining_height,
            },
            13.0,
            150.0,
            64.0,
            remaining_height,
            .white,
        );
    }
    if (state.current_gameplay_sprites.progress_bar) |loaded_texture| {
        drawTextureLocalRectSource(
            layout,
            loaded_texture,
            .{
                .x = 0.0,
                .y = remaining_height,
                .width = @floatFromInt(loaded_texture.texture.width),
                .height = 256.0 - remaining_height,
            },
            13.0,
            150.0 + remaining_height,
            64.0,
            256.0 - remaining_height,
            .white,
        );
    }
    if (state.current_gameplay_sprites.progress_cursor) |loaded_texture| {
        drawTextureLocalRect(layout, loaded_texture, 12.0, remaining_height + 111.0, 64.0, 64.0, .white);
    }
}

pub fn drawTutorialLives(state: anytype, layout: VirtualLayout, visible_life_stock: u32) void {
    const count = @min(visible_life_stock, 9);
    const loaded_texture = state.current_gameplay_sprites.life orelse return;
    for (0..count) |slot_index| {
        drawTextureLocalRect(
            layout,
            loaded_texture,
            12.0 + @as(f32, @floatFromInt(slot_index)) * 20.0,
            438.0,
            32.0,
            32.0,
            .white,
        );
    }
}

pub fn drawStatusWidgets(state: anytype, layout: VirtualLayout, runner: gameplay.Runner) void {
    drawJetpackGauge(state, layout, runner, false);
    drawDamageGauge(state, layout, runner, false);
    if (runner.session_mode == .postal) {
        drawTutorialLives(state, layout, runner.visible_life_stock);
    }
}

pub fn drawRowEventWidget(
    state: anytype,
    layout: VirtualLayout,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) !void {
    if (!runner.rowEventCounterVisible()) return;
    const widget_world = runner.rowEventWidgetWorldPosition();
    const screen_point = rl.getWorldToScreenEx(widget_world, camera, rl.getScreenWidth(), rl.getScreenHeight());
    if (!std.math.isFinite(screen_point.x) or !std.math.isFinite(screen_point.y)) return;
    if (!layout.containsScreenPoint(screen_point.x, screen_point.y)) return;

    const local_point = layout.unmapPoint(screen_point.x, screen_point.y);
    var frame_state = frontend_widget.TextButtonState{};
    frame_state.snapFor(.menu_button, false);
    const colors = frontend_widget.colorsForState(frame_state, false);
    frontend_widget.drawNineSliceFrame(
        layout,
        state.frontend_widget_art.border.?.texture,
        .{
            .left = local_point.x + row_event_widget_frame_offset_x,
            .top = local_point.y + row_event_widget_frame_offset_y,
            .width = row_event_widget_frame_width,
            .height = row_event_widget_frame_height,
        },
        frontend_widget.menu_button_border_edge,
        frontend_widget.menu_button_border_edge / 128.0,
        .{ .r = colors.fill.r, .g = colors.fill.g, .b = colors.fill.b, .a = 176 },
    );

    if (state.frontend_widget_art.parcel_icon) |loaded_texture| {
        drawTextureLocalRect(
            layout,
            loaded_texture,
            local_point.x + row_event_widget_icon_x,
            local_point.y + row_event_widget_icon_y,
            row_event_widget_icon_size,
            row_event_widget_icon_size,
            .white,
        );
    }

    var counter_buffer: [32]u8 = undefined;
    const counter_text = try std.fmt.bufPrint(
        &counter_buffer,
        "{d}/{d}",
        .{ runner.registeredParcelCount(), runner.rowEventParcelTargetCount() },
    );
    drawHudTextShadowed(state, layout, local_point.x + row_event_widget_text_x, local_point.y + row_event_widget_text_y, counter_text, 16, .white);

    if (runner.rowEventBonusVisible()) {
        var bonus_buffer: [32]u8 = undefined;
        const bonus_text = try std.fmt.bufPrint(&bonus_buffer, "+{d}", .{runner.rowEventBonusScore()});
        const alpha: u8 = @intFromFloat(std.math.clamp(runner.rowEventBonusBlinkAlpha(), 0.0, 1.0) * 255.0);
        drawCenteredHudTextShadowed(
            state,
            layout,
            local_point.x + 26.0,
            local_point.y + row_event_widget_bonus_y,
            bonus_text,
            16,
            .{ .r = 255, .g = 224, .b = 112, .a = alpha },
        );
    }
}

pub fn drawJetpackGauge(state: anytype, layout: VirtualLayout, runner: gameplay.Runner, show_label: bool) void {
    if (!runner.jetpack.active) return;

    const panel = layout.mapRect(548.0, 108.0, 28.0, 224.0);
    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const fill_ratio = runner.jetpackFuelRemaining();
    const active_fill_height = fill_height * fill_ratio;
    const pulse = if (runner.jetpack.warning_band == .near_empty) runner.jetpack.pulse_envelope else @as(f32, 0.0);
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const fill_color = jetpackGaugeColor(runner.jetpack.warning_band, pulse);

    if (show_label) {
        drawAppText(state, "Jet", @intFromFloat(panel.x + layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
    }
    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const inner = rl.Rectangle{
        .x = panel.x + fill_margin,
        .y = panel.y + fill_margin,
        .width = fill_width,
        .height = fill_height,
    };
    rl.drawRectangleRounded(inner, 0.12, 6, .{ .r = 255, .g = 255, .b = 255, .a = 20 });

    if (active_fill_height > 0.0) {
        const fill_rect = rl.Rectangle{
            .x = inner.x,
            .y = inner.y + (fill_height - active_fill_height),
            .width = fill_width,
            .height = active_fill_height,
        };
        rl.drawRectangleRounded(fill_rect, 0.12, 6, fill_color);
    }

    rl.drawRectangleRoundedLinesEx(panel, 0.18, 8, layout.scaleFloat(2.0), .{ .r = 255, .g = 255, .b = 255, .a = outline_alpha });
}

pub fn drawDamageGauge(state: anytype, layout: VirtualLayout, runner: gameplay.Runner, show_label: bool) void {
    const panel = layout.mapRect(586.0, 108.0, 28.0, 224.0);
    const fill_ratio = runner.damageGaugeDisplayFill();
    const pulse = (@sin(runner.damage.runtime.pulse_progress * std.math.tau) + 1.0) * 0.5;
    const bright_overlay_alpha = runner.damageGaugeWarningOverlayAlpha();
    const warning_actor_alpha = runner.damageWarningActorAlpha();
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const warning_alpha: u8 = @intFromFloat(std.math.clamp(warning_actor_alpha, 0.0, 1.0) * 255.0);
    const bright_alpha: u8 = @intFromFloat(std.math.clamp(bright_overlay_alpha, 0.0, 1.0) * 255.0);

    if (show_label) {
        drawAppText(state, "Damage", @intFromFloat(panel.x - layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
    }
    if (state.current_gameplay_sprites.damage_gauge_full) |loaded_texture| {
        if (fill_ratio > 0.0) {
            const source_height = @as(f32, @floatFromInt(loaded_texture.texture.height));
            const source_width = @as(f32, @floatFromInt(loaded_texture.texture.width));
            const source = rl.Rectangle{
                .x = 0.0,
                .y = source_height * (1.0 - fill_ratio),
                .width = source_width,
                .height = source_height * fill_ratio,
            };
            drawTextureLocalRectSource(layout, loaded_texture, source, 586.0, 108.0 + (224.0 * (1.0 - fill_ratio)), 28.0, 224.0 * fill_ratio, .white);
        }
    }
    if (bright_alpha > 0) {
        if (state.current_gameplay_sprites.damage_gauge_bright) |loaded_texture| {
            drawTextureLocalRect(layout, loaded_texture, 586.0, 108.0, 28.0, 224.0, .{ .r = 255, .g = 255, .b = 255, .a = bright_alpha });
        }
    }
    if (warning_alpha > 0) {
        if (state.current_gameplay_sprites.warning) |loaded_texture| {
            drawTextureLocalRect(layout, loaded_texture, 288.0, 64.0, 64.0, 64.0, .{ .r = 255, .g = 255, .b = 255, .a = warning_alpha });
        }
    }
    if (state.current_gameplay_sprites.damage_gauge) |loaded_texture| {
        drawTextureLocalRect(layout, loaded_texture, 586.0, 108.0, 28.0, 224.0, .white);
        return;
    }

    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const active_fill_height = fill_height * fill_ratio;
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const fill_color = damageGaugeColor(fill_ratio, runner.damage.warning_state, pulse);
    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });
    const inner = rl.Rectangle{
        .x = panel.x + fill_margin,
        .y = panel.y + fill_margin,
        .width = fill_width,
        .height = fill_height,
    };
    rl.drawRectangleRounded(inner, 0.12, 6, .{ .r = 255, .g = 255, .b = 255, .a = 20 });
    if (active_fill_height > 0.0) {
        const fill_rect = rl.Rectangle{
            .x = inner.x,
            .y = inner.y + (fill_height - active_fill_height),
            .width = fill_width,
            .height = active_fill_height,
        };
        rl.drawRectangleRounded(fill_rect, 0.12, 6, fill_color);
    }
    rl.drawRectangleRoundedLinesEx(panel, 0.18, 8, layout.scaleFloat(2.0), .{ .r = 255, .g = 255, .b = 255, .a = outline_alpha });
}

fn currentParcelTarget(state: anytype) usize {
    if (state.current_track_preview) |preview| return preview.parcel_target_count;
    return if (state.current_level) |loaded_level| loaded_level.parcels orelse 0 else 0;
}

fn formatElapsedMillis(buffer: []u8, elapsed_millis: u32) ![]const u8 {
    const total_seconds = @divTrunc(elapsed_millis, 1000);
    const minutes = @divTrunc(total_seconds, 60);
    const seconds = @mod(total_seconds, 60);
    const centiseconds = @divTrunc(@mod(elapsed_millis, 1000), 10);
    return std.fmt.bufPrint(buffer, "{d:0>2}:{d:0>2}.{d:0>2}", .{ minutes, seconds, centiseconds });
}

fn formatScoreWithCommas(buffer: []u8, score: u32) ![:0]const u8 {
    var digits_buffer: [16]u8 = undefined;
    const digits = try std.fmt.bufPrint(&digits_buffer, "{d}", .{score});

    var write_index: usize = 0;
    const remainder = digits.len % 3;
    for (digits, 0..) |digit, index| {
        if (index != 0 and (index % 3 == remainder or (remainder == 0 and index % 3 == 0))) {
            if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
            buffer[write_index] = ',';
            write_index += 1;
        }
        if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
        buffer[write_index] = digit;
        write_index += 1;
    }
    if (write_index >= buffer.len) return error.NoSpaceLeft;
    buffer[write_index] = 0;
    return buffer[0..write_index :0];
}

fn drawCenteredHudText(state: anytype, layout: VirtualLayout, authored_center_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    const point = layout.mapPoint(authored_center_x, authored_y);
    drawAppText(state, text, @intFromFloat(point.x - @as(f32, @floatFromInt(width)) * 0.5), @intFromFloat(point.y), font_size, color);
}

fn drawHudTextShadowed(state: anytype, layout: VirtualLayout, authored_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    drawAppText(state, text, @intFromFloat(point.x + layout.scaleFloat(2.0)), @intFromFloat(point.y + layout.scaleFloat(2.0)), font_size, .black);
    drawAppText(state, text, @intFromFloat(point.x), @intFromFloat(point.y), font_size, color);
}

fn drawRightAlignedHudTextShadowed(state: anytype, layout: VirtualLayout, authored_right_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    drawHudTextShadowed(state, layout, authored_right_x - @as(f32, @floatFromInt(width)), authored_y, text, authored_size, color);
}

fn drawCenteredHudTextShadowed(state: anytype, layout: VirtualLayout, authored_center_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    drawHudTextShadowed(state, layout, authored_center_x - @as(f32, @floatFromInt(width)) * 0.5, authored_y, text, authored_size, color);
}

fn drawIconCounter(state: anytype, layout: VirtualLayout, glyph: game_font.IconGlyph, text: []const u8, authored_x: f32, authored_y: f32, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    state.ui_font.drawText(&[_]u8{glyph.byte()}, point.x, point.y, @floatFromInt(font_size), .white);
    drawAppText(state, text, @intFromFloat(point.x + layout.scaleFloat(26.0)), @intFromFloat(point.y), font_size, color);
}

fn drawAppText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    app_ui.drawText(.{ .font = &state.ui_font }, text, x, y, font_size, color);
}

fn measureAppText(state: anytype, text: []const u8, font_size: i32) i32 {
    return app_ui.measureText(.{ .font = &state.ui_font }, text, font_size);
}

fn drawTextureLocalRectSource(layout: VirtualLayout, loaded_texture: assets.LoadedTexture, source: rl.Rectangle, local_x: f32, local_y: f32, local_width: f32, local_height: f32, tint: rl.Color) void {
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

fn drawTextureLocalRect(layout: VirtualLayout, loaded_texture: assets.LoadedTexture, local_x: f32, local_y: f32, local_width: f32, local_height: f32, tint: rl.Color) void {
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

fn damageGaugeColor(fill_ratio: f32, warning_state: gameplay.DamageWarningState, pulse: f32) rl.Color {
    if (warning_state != .idle) {
        const green: u8 = @intFromFloat(160.0 + 72.0 * pulse);
        return .{ .r = 255, .g = green, .b = 88, .a = 232 };
    }
    if (fill_ratio >= 0.75) return .{ .r = 232, .g = 78, .b = 72, .a = 224 };
    if (fill_ratio >= 0.35) return .{ .r = 244, .g = 170, .b = 64, .a = 216 };
    return .{ .r = 94, .g = 204, .b = 122, .a = 208 };
}

fn jetpackGaugeColor(warning_band: gameplay.JetpackWarningBand, pulse: f32) rl.Color {
    return switch (warning_band) {
        .idle => .{ .r = 94, .g = 204, .b = 122, .a = 0 },
        .steady => .{ .r = 90, .g = 172, .b = 255, .a = 224 },
        .near_empty => .{
            .r = 255,
            .g = @intFromFloat(164.0 + 72.0 * pulse),
            .b = 84,
            .a = 232,
        },
    };
}
