const std = @import("std");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");

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
    return frontend_widget.type20TextRect(font, text, title_y, 0.0);
}

pub fn packageTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, package_y, 0.0);
}

pub fn bonusTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, bonus_y, 0.0);
}

pub fn continueTextRect(font: *const game_font.Loaded, summary: Summary) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Click to Continue", continueAnchorY(summary), 0.0);
}
