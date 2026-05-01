const std = @import("std");
const rl = @import("raylib");
const ui = @import("../ui.zig");
const assets = @import("../assets.zig");
const frontend_art = @import("../frontend/art.zig");
const frontend_widget = @import("../frontend/widget.zig");
const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_art = @import("../gameplay_art.zig");
const level = @import("../level.zig");
const row_event = @import("row_event.zig");
const track = @import("../track.zig");

const VirtualLayout = ui.VirtualLayout;

const row_event_widget_frame_width: f32 = 88.0;
const row_event_widget_frame_height: f32 = 30.0;
const row_event_widget_frame_offset_x: f32 = -18.0;
const row_event_widget_frame_offset_y: f32 = -15.0;
const row_event_widget_text_y: f32 = -9.0;
const row_event_widget_bonus_y: f32 = 18.0;

pub const Context = struct {
    font: *const game_font.Loaded,
    frontend_widget_art: *const frontend_art.FrontendWidgetArt,
    sprites: *const gameplay_art.SpriteArt,
    current_track_preview: ?*const track.LoadedLevelPreview,
    current_level: ?*const level.Definition,
    tutorial_reference_score: u32,
};

pub fn modeShowsGameplayScores(session_mode: gameplay.SessionMode) bool {
    // PORT(verified): tutorial mode hides score widgets A/D in
    // `initialize_subgame` (0x4374b0) and `build_subgame_level` (0x437eb0).
    return session_mode != .tutorial;
}

pub fn modeShowsParcelCounter(session_mode: gameplay.SessionMode) bool {
    // PORT(verified): parcel widgets B/C are allocated only for native
    // `level_mode == 0` (Postal) in `initialize_subgame` 0x437610..0x437733.
    return session_mode == .postal;
}

pub fn modeShowsLifeSlots(session_mode: gameplay.SessionMode) bool {
    // PORT(verified): life slots are allocated only for native `level_mode == 0`,
    // and `show_subgoldy_lives` is gated to that mode in `update_subgoldy`.
    return session_mode == .postal;
}

test "native gameplay widget hud visibility is mode gated" {
    try std.testing.expect(modeShowsGameplayScores(.postal));
    try std.testing.expect(modeShowsGameplayScores(.challenge));
    try std.testing.expect(modeShowsGameplayScores(.time_trial));
    try std.testing.expect(!modeShowsGameplayScores(.tutorial));

    try std.testing.expect(modeShowsParcelCounter(.postal));
    try std.testing.expect(!modeShowsParcelCounter(.challenge));
    try std.testing.expect(!modeShowsParcelCounter(.time_trial));
    try std.testing.expect(!modeShowsParcelCounter(.tutorial));

    try std.testing.expect(modeShowsLifeSlots(.postal));
    try std.testing.expect(!modeShowsLifeSlots(.challenge));
    try std.testing.expect(!modeShowsLifeSlots(.time_trial));
    try std.testing.expect(!modeShowsLifeSlots(.tutorial));
}

pub fn drawStandardHud(context: Context, layout: VirtualLayout, runner: gameplay.Runner) !void {
    // PORT(verified): `initialize_subgame` (0x4374b0) allocates the widget-backed
    // gameplay HUD. Widget A (`game+0x35bb88`) is the top-right score, widget D
    // (`game+0x35bb8c`) the top-left reference best, widgets B/C the Postal
    // parcel icon + count, and widgets 0..9 the Postal life row. See
    // docs/re/hud-pipeline.md.

    if (!modeShowsGameplayScores(runner.session_mode)) return;

    // Widget A: score, top-right.
    var score_buffer: [32]u8 = undefined;
    const score_text = try formatScoreWithCommas(&score_buffer, runner.score.total);
    drawRightAlignedHudTextShadowed(context, layout, 628.0, 14.0, score_text, 22, .white);

    // Widget D: reference best score / best time (mode-dependent). The native
    // widget lives at (40, 14) right-aligned with anchor -71; rendering as a
    // left-aligned string at x=12 gives the same visual position without the
    // widget's shell.
    if (runner.session_mode == .postal or runner.session_mode == .challenge) {
        if (context.tutorial_reference_score > 0) {
            var best_buffer: [32]u8 = undefined;
            const best_text = try formatScoreWithCommas(&best_buffer, context.tutorial_reference_score);
            drawHudTextShadowed(context, layout, 12.0, 14.0, best_text, 22, .white);
        }
    } else if (runner.session_mode == .time_trial) {
        // Time Trial: widget D holds the running elapsed time (the native
        // `format_time_trial_string` output).
        var elapsed_buffer: [32]u8 = undefined;
        const elapsed_text = try gameplay.formatTimeTrialString(&elapsed_buffer, runner.stopwatch.elapsedMillis());
        drawHudTextShadowed(context, layout, 12.0, 14.0, elapsed_text, 22, .white);
    }

    // Widgets B + C: Postal parcel icon + count. Mode-gated to Postal.
    if (modeShowsParcelCounter(runner.session_mode)) {
        const parcel_target = currentParcelTarget(context);
        const parcel_count = runner.counters.parcels;
        // PORT(verified): `initialize_subgame` 0x4376bb: sprite 0x7a at (0, 58).
        drawTextureLocalRect(layout, context.frontend_widget_art.parcel_icon, 0.0, 58.0, 32.0, 64.0, .white);
        var parcel_buffer: [32]u8 = undefined;
        const parcel_text = if (parcel_target > 0)
            try std.fmt.bufPrint(&parcel_buffer, "{d}/{d}", .{ parcel_count, parcel_target })
        else
            try std.fmt.bufPrint(&parcel_buffer, "{d}", .{parcel_count});
        // PORT(verified): widget C at (47, 80), absolute alignment.
        drawHudTextShadowed(context, layout, 47.0, 80.0, parcel_text, 22, .white);
    }
}

pub fn drawProgressBar(context: Context, layout: VirtualLayout, runner: gameplay.Runner) void {
    // PORT(verified): `update_progress_bar` (0x437c40) queues three quads on the
    // left column at authored x=13 with `var_1c = (1 - progress) * 232 + 12`.
    // Empty bar (0x9b `Progress-Bar.tga`) fills the top `var_1c` rows, lit bar
    // (0x9c `Progress-Bar-lit.tga`) fills the remaining `256 - var_1c` below,
    // and the cursor (0x9d) sits at y = var_1c + 111. Native progress is
    // `(current_row - track_row_start) / (track_row_end - track_row_start)`,
    // not absolute row / total rows. See docs/re/hud-pipeline.md.
    const preview = context.current_track_preview orelse return;
    const remaining_height = progressBarRemainingHeight(
        runner.row_position,
        preview.runtime_active_row_start,
        preview.runtime_active_row_end,
    );
    const progress_bar_texture = context.sprites.progress_bar;
    drawTextureLocalRectSource(
        layout,
        progress_bar_texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(progress_bar_texture.texture.width),
            .height = remaining_height,
        },
        13.0,
        150.0,
        64.0,
        remaining_height,
        .white,
    );
    const progress_bar_lit_texture = context.sprites.progress_bar_lit;
    drawTextureLocalRectSource(
        layout,
        progress_bar_lit_texture,
        .{
            .x = 0.0,
            .y = remaining_height,
            .width = @floatFromInt(progress_bar_lit_texture.texture.width),
            .height = 256.0 - remaining_height,
        },
        13.0,
        150.0 + remaining_height,
        64.0,
        256.0 - remaining_height,
        .white,
    );
    drawTextureLocalRect(layout, context.sprites.progress_cursor, 12.0, remaining_height + 111.0, 64.0, 64.0, .white);
}

fn progressBarProgress(row_position: f32, active_row_start: usize, active_row_end: usize) f32 {
    const start: f32 = @floatFromInt(active_row_start);
    const end: f32 = @floatFromInt(@max(active_row_end, active_row_start + 1));
    return std.math.clamp((row_position - start) / (end - start), 0.0, 1.0);
}

fn progressBarRemainingHeight(row_position: f32, active_row_start: usize, active_row_end: usize) f32 {
    return (1.0 - progressBarProgress(row_position, active_row_start, active_row_end)) * 232.0 + 12.0;
}

test "progress bar follows native active row window" {
    try std.testing.expectApproxEqAbs(@as(f32, 244.0), progressBarRemainingHeight(0.0, 31, 131), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 244.0), progressBarRemainingHeight(31.0, 31, 131), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 128.0), progressBarRemainingHeight(81.0, 31, 131), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), progressBarRemainingHeight(131.0, 31, 131), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), progressBarRemainingHeight(200.0, 31, 131), 0.0001);
}

pub fn drawLifeSlots(context: Context, layout: VirtualLayout, visible_life_stock: u32) void {
    // PORT(verified): `initialize_subgame` (0x4377ab) allocates nine life slots via
    // `initialize_frontend_sprite_button(..., sprite=0x7b /Sprites/Life.tga,
    // x=13 + i*24, y=430, ...)` and `show_subgoldy_lives` (0x43af10) toggles the
    // hidden bit on the first `visible_life_stock` slots. The allocation and
    // update gate are Postal-only. See docs/re/hud-pipeline.md.
    const count = @min(visible_life_stock, 9);
    const loaded_texture = context.sprites.life;
    for (0..count) |slot_index| {
        drawTextureLocalRect(
            layout,
            loaded_texture,
            13.0 + @as(f32, @floatFromInt(slot_index)) * 24.0,
            430.0,
            32.0,
            32.0,
            .white,
        );
    }
}

pub fn drawStatusWidgets(context: Context, layout: VirtualLayout, runner: gameplay.Runner) void {
    drawDamageGauge(context, layout, runner);
    if (modeShowsLifeSlots(runner.session_mode)) {
        drawLifeSlots(context, layout, runner.visible_life_stock);
    }
}

pub fn drawTimesUpWidget(context: Context, layout: VirtualLayout, runner: gameplay.Runner) void {
    if (!runner.timesUpVisible()) return;
    // PORT(verified): `show_times_up_message` creates a centered font-20
    // frontend text widget with authored y=200.
    drawCenteredHudTextShadowed(context, layout, 320.0, 200.0, "Time's Up", 20, .white);
}

pub fn drawRowEventWidget(
    context: Context,
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
        context.frontend_widget_art.border.texture,
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

    var counter_buffer: [2]u8 = undefined;
    const counter_text = row_event.formatDeliveredCount(&counter_buffer, runner.registeredParcelCount());
    drawCenteredHudTextShadowed(context, layout, local_point.x + 26.0, local_point.y + row_event_widget_text_y, counter_text, 16, .white);

    if (runner.rowEventBonusVisible()) {
        var bonus_buffer: [32]u8 = undefined;
        const bonus_text = try std.fmt.bufPrint(&bonus_buffer, "+{d}", .{runner.rowEventBonusScore()});
        const alpha: u8 = @intFromFloat(std.math.clamp(runner.rowEventBonusBlinkAlpha(), 0.0, 1.0) * 255.0);
        drawCenteredHudTextShadowed(
            context,
            layout,
            local_point.x + 26.0,
            local_point.y + row_event_widget_bonus_y,
            bonus_text,
            16,
            .{ .r = 255, .g = 224, .b = 112, .a = alpha },
        );
    }
}

// PORT(verified): `update_damage_gauge` (0x440fd0) queues three quads on the
// right column at authored (560, 70, 64, 396). Bright overlay (0x5b) covers the
// full area, empty (0x59 `DamageGuage.tga`) fills the top `var_14` rows, and
// full (0x5a `DamageGuageFull.tga`) fills the remaining `396 - var_14` below.
// See docs/re/hud-pipeline.md.
const damage_gauge_x: f32 = 560.0;
const damage_gauge_y: f32 = 70.0;
const damage_gauge_w: f32 = 64.0;
const damage_gauge_h: f32 = 396.0;
const damage_gauge_empty_height_base: f32 = 351.0;
const damage_gauge_empty_height_scale: f32 = 308.0;
const damage_gauge_empty_floor_threshold: f32 = 0.0099999998;
const damage_gauge_full_threshold: f32 = 0.99900001;

pub fn drawDamageGauge(context: Context, layout: VirtualLayout, runner: gameplay.Runner) void {
    const empty_texture = context.sprites.damage_gauge;
    const full_texture = context.sprites.damage_gauge_full;
    const bright_texture = context.sprites.damage_gauge_bright;
    const fill_ratio = runner.damageGaugeDisplayFill();
    const bright_overlay_alpha = runner.damageGaugeWarningOverlayAlpha();
    const warning_actor_alpha = runner.damageWarningActorAlpha();
    const warning_alpha: u8 = @intFromFloat(std.math.clamp(warning_actor_alpha, 0.0, 1.0) * 255.0);
    const bright_alpha: u8 = @intFromFloat(std.math.clamp(bright_overlay_alpha, 0.0, 1.0) * 255.0);
    // PORT(verified): native computes `var_14` from display fill with
    // thresholds, not a linear full-height split:
    // `fill >= 0.999 -> 0`, `fill < 0.01 -> 396`, else
    // `351 - fill * 308` (`update_damage_gauge` 0x4411b3..0x4411f6).
    const empty_height = damageGaugeEmptyHeight(fill_ratio);
    const full_height = damage_gauge_h - empty_height;
    const source_width = @as(f32, @floatFromInt(empty_texture.texture.width));

    if (bright_alpha > 0) {
        drawTextureLocalRectSource(
            layout,
            bright_texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = source_width,
                .height = damage_gauge_h,
            },
            damage_gauge_x,
            damage_gauge_y,
            damage_gauge_w,
            damage_gauge_h,
            .{ .r = 255, .g = 255, .b = 255, .a = bright_alpha },
        );
    }
    if (empty_height > 0.0) {
        drawTextureLocalRectSource(
            layout,
            empty_texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = source_width,
                .height = empty_height,
            },
            damage_gauge_x,
            damage_gauge_y,
            damage_gauge_w,
            empty_height,
            .white,
        );
    }
    if (full_height > 0.0) {
        drawTextureLocalRectSource(
            layout,
            full_texture,
            .{
                .x = 0.0,
                .y = empty_height,
                .width = source_width,
                .height = full_height,
            },
            damage_gauge_x,
            damage_gauge_y + empty_height,
            damage_gauge_w,
            full_height,
            .white,
        );
    }
    // PORT(verified): `initialize_warning` (0x446e8a) places sprite 0x5e
    // `Sprites/Warning.tga` at authored (288, 64, 64, 64); `update_warning`
    // (0x446f80) modulates alpha.
    if (warning_alpha > 0) {
        drawTextureLocalRect(layout, context.sprites.warning, 288.0, 64.0, 64.0, 64.0, .{ .r = 255, .g = 255, .b = 255, .a = warning_alpha });
    }
}

fn damageGaugeEmptyHeight(fill_ratio: f32) f32 {
    if (fill_ratio > damage_gauge_full_threshold) return 0.0;
    if (fill_ratio < damage_gauge_empty_floor_threshold) return damage_gauge_h;
    return damage_gauge_empty_height_base - fill_ratio * damage_gauge_empty_height_scale;
}

test "damage gauge split follows native display-fill curve" {
    try std.testing.expectEqual(@as(f32, damage_gauge_h), damageGaugeEmptyHeight(0.0));
    try std.testing.expectEqual(@as(f32, 0.0), damageGaugeEmptyHeight(1.0));
    try std.testing.expectApproxEqAbs(@as(f32, 197.0), damageGaugeEmptyHeight(0.5), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 73.8), damageGaugeEmptyHeight(0.9), 0.0001);
}

fn currentParcelTarget(context: Context) usize {
    if (context.current_track_preview) |preview| return preview.parcel_target_count;
    return if (context.current_level) |loaded_level| loaded_level.parcels orelse 0 else 0;
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

fn drawCenteredHudText(context: Context, layout: VirtualLayout, authored_center_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(context, text, font_size);
    const point = layout.mapPoint(authored_center_x, authored_y);
    drawAppText(context, text, @intFromFloat(point.x - @as(f32, @floatFromInt(width)) * 0.5), @intFromFloat(point.y), font_size, color);
}

fn drawHudTextShadowed(context: Context, layout: VirtualLayout, authored_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    drawAppText(context, text, @intFromFloat(point.x + layout.scaleFloat(2.0)), @intFromFloat(point.y + layout.scaleFloat(2.0)), font_size, .black);
    drawAppText(context, text, @intFromFloat(point.x), @intFromFloat(point.y), font_size, color);
}

fn drawRightAlignedHudTextShadowed(context: Context, layout: VirtualLayout, authored_right_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    // `measureAppText` returns the text width in screen pixels (the font size
    // passed in is already scaled), while `authored_right_x` is in authored
    // 640x480 space. Divide the measured width by `layout.scale` so the
    // subtraction stays in authored units and `drawHudTextShadowed` can map
    // the final position through `mapPoint` without a scale mismatch.
    const font_size = layout.fontSize(authored_size);
    const scaled_width = measureAppText(context, text, font_size);
    const authored_width = @as(f32, @floatFromInt(scaled_width)) / layout.scale;
    drawHudTextShadowed(context, layout, authored_right_x - authored_width, authored_y, text, authored_size, color);
}

fn drawCenteredHudTextShadowed(context: Context, layout: VirtualLayout, authored_center_x: f32, authored_y: f32, text: []const u8, authored_size: i32, color: rl.Color) void {
    // Same scale-space reconciliation as `drawRightAlignedHudTextShadowed`:
    // the measured text width comes back in screen pixels from a scaled font
    // size, but the centering math needs authored units.
    const font_size = layout.fontSize(authored_size);
    const scaled_width = measureAppText(context, text, font_size);
    const authored_width = @as(f32, @floatFromInt(scaled_width)) / layout.scale;
    drawHudTextShadowed(context, layout, authored_center_x - authored_width * 0.5, authored_y, text, authored_size, color);
}

fn drawIconCounter(context: Context, layout: VirtualLayout, glyph: game_font.IconGlyph, text: []const u8, authored_x: f32, authored_y: f32, authored_size: i32, color: rl.Color) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    context.font.drawText(&[_]u8{glyph.byte()}, point.x, point.y, @floatFromInt(font_size), .white);
    drawAppText(context, text, @intFromFloat(point.x + layout.scaleFloat(26.0)), @intFromFloat(point.y), font_size, color);
}

fn drawAppText(context: Context, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    ui.drawText(.{ .font = context.font }, text, x, y, font_size, color);
}

fn measureAppText(context: Context, text: []const u8, font_size: i32) i32 {
    return ui.measureText(.{ .font = context.font }, text, font_size);
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
