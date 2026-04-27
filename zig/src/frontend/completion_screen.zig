const std = @import("std");
const rl = @import("raylib");
const ui = @import("../ui.zig");
const assets = @import("../assets.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");

const VirtualLayout = ui.VirtualLayout;

pub const title_y: f32 = 80.0;
pub const package_y: f32 = 160.0;
pub const parcel_icon_x: f32 = 100.0;
pub const parcel_icon_y: f32 = 144.0;
pub const parcel_icon_width: f32 = 32.0;
pub const parcel_icon_height: f32 = 64.0;
pub const bonus_y: f32 = 302.0;
pub const continue_y: f32 = 320.0;
pub const continue_y_with_bonus: f32 = 400.0;
pub const reveal_step: f32 = 1.0 / 24.0;
pub const reveal_bonus_threshold: f32 = 1.0;
pub const reveal_continue_threshold: f32 = 2.0;
// PORT(verified): completion is initialized from subgame without resetting the front-end
// center justify, so it inherits the `25` authored-pixel center offset.
pub const center_offset_x: f32 = frontend_widget.menu_button_center_offset_x;

pub const Action = enum {
    continue_flow,
};

pub const Outcome = enum {
    completed,
    failed,
};

pub const Summary = struct {
    outcome: Outcome = .completed,
    level_name: []const u8,
    mode: ?frontend.FrontendLevelMode,
    elapsed_millis: u32,
    parcel_count: u32,
    parcel_target: usize,
    score: u32,
    score_is_partial: bool,
    score_totals: gameplay.ScoreTotals = .{},
    visible_life_stock: u32 = 0,
    damage_gauge: f32 = 0.0,
    high_score_rank: ?usize = null,
    time_trial_record_improved: bool = false,
    unlocked_next_route: bool = false,
};

pub fn title(summary: Summary) []const u8 {
    return switch (summary.outcome) {
        .completed => if (summary.mode) |mode|
            switch (mode) {
                .postal => "Delivery Complete!",
                .time_trial => "Route Complete",
                .challenge => "Challenge Complete",
                .tutorial => "Tutorial Complete",
            }
        else
            "Level Complete",
        .failed => if (summary.mode) |mode|
            switch (mode) {
                .postal => "Game Over",
                .time_trial => "Route Failed",
                .challenge => "Challenge Failed",
                .tutorial => "Tutorial Failed",
            }
        else
            "Run Failed",
    };
}

pub fn hasBonusLine(summary: Summary) bool {
    return summary.outcome == .completed and summary.score_totals.completion_bonus > 0;
}

pub fn revealTarget(summary: Summary) f32 {
    if (summary.outcome != .completed) return reveal_bonus_threshold;
    return if (hasBonusLine(summary))
        reveal_continue_threshold
    else
        reveal_bonus_threshold;
}

pub fn bonusVisibleAtProgress(summary: Summary, progress: f32) bool {
    return hasBonusLine(summary) and progress >= reveal_bonus_threshold;
}

pub fn continueVisibleAtProgress(summary: Summary, progress: f32) bool {
    return progress >= if (hasBonusLine(summary))
        reveal_continue_threshold
    else
        reveal_bonus_threshold;
}

pub fn packageLine(buffer: []u8, summary: Summary) ![]const u8 {
    return if (summary.parcel_count == 1)
        std.fmt.bufPrint(buffer, "1 Package Delivered", .{})
    else
        std.fmt.bufPrint(buffer, "{d:0>2} Packages Delivered", .{summary.parcel_count});
}

pub fn bonusLine(buffer: []u8, summary: Summary) !?[]const u8 {
    if (!hasBonusLine(summary)) return null;
    if (summary.score_totals.completion_bonus == 50_000 and summary.parcel_count == summary.parcel_target) {
        return try std.fmt.bufPrint(buffer, "Perfect Score! 50,000 Bonus Points!", .{});
    }
    return try std.fmt.bufPrint(buffer, "{d} Bonus Points!", .{summary.score_totals.completion_bonus});
}

pub fn continueAnchorY(summary: Summary) f32 {
    return if (hasBonusLine(summary)) continue_y_with_bonus else continue_y;
}

pub fn titleTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, text, title_y, center_offset_x);
}

pub fn packageTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, text, package_y, center_offset_x);
}

pub fn bonusTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, text, bonus_y, center_offset_x);
}

pub fn continueTextRect(font: *const game_font.Loaded, summary: Summary) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, "Click to Continue", continueAnchorY(summary), center_offset_x);
}

pub fn drawCompleted(
    state: anytype,
    layout: VirtualLayout,
    summary: Summary,
    bonus_visible: bool,
    continue_button_state: frontend_widget.TextButtonState,
    continue_visible: bool,
) !void {
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    const completion_text_only: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_completion_screen` builds the title,
        // package line, bonus line, and continue prompt with flags
        // `0x20400002`, which suppress the pill background while keeping the
        // menu-button shell-font metrics.
        .flags = 0x20400002,
    };

    const title_text = title(summary);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        title_text,
        titleTextRect(&state.ui_font, title_text),
        idle_state,
        false,
        completion_text_only,
    );

    var package_buffer: [64]u8 = undefined;
    const package_text = switch (summary.mode orelse .tutorial) {
        .postal => try packageLine(&package_buffer, summary),
        .time_trial, .challenge, .tutorial => summary.level_name,
    };
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        package_text,
        packageTextRect(&state.ui_font, package_text),
        idle_state,
        false,
        completion_text_only,
    );

    if ((summary.mode orelse .tutorial) == .postal) {
        drawParcelIcon(state, layout);
    }

    if (bonus_visible) {
        if (try bonusLine(&package_buffer, summary)) |bonus_text| {
            frontend_widget.drawTextButtonWithOptions(
                layout,
                widget_art,
                &state.ui_font,
                .menu_button,
                bonus_text,
                bonusTextRect(&state.ui_font, bonus_text),
                idle_state,
                false,
                completion_text_only,
            );
        }
    }

    if (continue_visible) {
        frontend_widget.drawTextButtonWithOptions(
            layout,
            widget_art,
            &state.ui_font,
            .menu_button,
            "Click to Continue",
            continueTextRect(&state.ui_font, summary),
            continue_button_state,
            false,
            completion_text_only,
        );
    }
}

pub fn drawFailed(
    state: anytype,
    layout: VirtualLayout,
    summary: Summary,
    continue_button_state: frontend_widget.TextButtonState,
) !void {
    const overlay_panel = layout.mapRect(120.0, 132.0, 400.0, 204.0);
    const title_point = layout.mapPoint(144.0, 156.0);
    const body_point = layout.mapPoint(144.0, 196.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_pos_y: i32 = @intFromFloat(title_point.y);
    const body_x: i32 = @intFromFloat(body_point.x);
    const body_pos_y: i32 = @intFromFloat(body_point.y);
    const title_text = title(summary);
    var elapsed_buffer: [32]u8 = undefined;
    const elapsed_text = try gameplay.formatTimeTrialString(&elapsed_buffer, summary.elapsed_millis);

    rl.drawRectangleRounded(overlay_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 214 });
    drawAppText(state, title_text, title_x, title_pos_y, layout.fontSize(28), .gold);

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrint(
        &summary_buffer,
        "{s}>Time {s}>Packages {d}/{d}",
        .{
            if (summary.outcome == .completed) summary.level_name else "Run ended before route completion",
            elapsed_text,
            summary.parcel_count,
            summary.parcel_target,
        },
    );
    try drawWrappedText(
        state,
        summary_text,
        body_x,
        body_pos_y,
        layout.scaleInt(332),
        layout.fontSize(20),
        .ray_white,
    );

    const score_y = body_pos_y + layout.scaleInt(70);
    if (summary.mode == .time_trial) {
        var time_buffer: [128]u8 = undefined;
        const time_text = try std.fmt.bufPrint(&time_buffer, "Route time {s}", .{elapsed_text});
        drawAppText(state, time_text, body_x, score_y, layout.fontSize(18), .sky_blue);
    } else {
        var score_buffer: [128]u8 = undefined;
        const score_text = try std.fmt.bufPrint(&score_buffer, "Score {d}{s}", .{
            summary.score,
            if (summary.score_is_partial) " (partial)" else "",
        });
        drawAppText(state, score_text, body_x, score_y, layout.fontSize(18), .sky_blue);

        var breakdown_buffer: [224]u8 = undefined;
        const breakdown_text = try std.fmt.bufPrint(
            &breakdown_buffer,
            "Rings {d}  Garbage {d}  Health {d}  Pickup {d}  Register {d}  Bonus {d}  Lives {d}  Damage {d:.2}",
            .{
                summary.score_totals.ring_collect,
                summary.score_totals.garbage_collision,
                summary.score_totals.health_collect,
                summary.score_totals.parcel_pickup,
                summary.score_totals.parcel_register,
                summary.score_totals.completion_bonus,
                summary.visible_life_stock,
                summary.damage_gauge,
            },
        );
        try drawWrappedText(
            state,
            breakdown_text,
            body_x,
            score_y + layout.scaleInt(22),
            layout.scaleInt(332),
            layout.fontSize(16),
            .light_gray,
        );
    }

    if (summary.unlocked_next_route) {
        drawAppText(state, "Unlocked the next delivery route.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (summary.time_trial_record_improved) {
        drawAppText(state, "Saved a new best route time.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (summary.high_score_rank) |rank| {
        var rank_buffer: [96]u8 = undefined;
        const rank_text = try std.fmt.bufPrint(&rank_buffer, "New high score rank: {d}", .{rank + 1});
        drawAppText(state, rank_text, body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    }

    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Click to Continue",
        continueTextRect(&state.ui_font, summary),
        continue_button_state,
        false,
    );
}

fn drawParcelIcon(state: anytype, layout: VirtualLayout) void {
    const loaded_texture = state.frontend_widget_art.parcel_icon orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        parcel_icon_x,
        parcel_icon_y,
        parcel_icon_width,
        parcel_icon_height,
        .white,
    );
}

fn drawAppText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    ui.drawText(.{ .font = &state.ui_font }, text, x, y, font_size, color);
}

fn drawWrappedText(state: anytype, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    return ui.drawWrappedText(.{ .font = &state.ui_font }, text, x, y, max_width, line_height, color);
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
