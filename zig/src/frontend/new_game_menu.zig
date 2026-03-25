const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

// PORT(verified): `initialize_new_game_menu` seeds Tutorial at `y = 80`, chains Postal,
// Time Trial, and Challenge Mode with `stack_widget_below`, places Help explicitly at
// `(center - 220, y = 350)`, then seeds Back at `y = 350` but immediately stacks it below
// Challenge Mode. The explicit `350` for Back is only a constructor seed.
pub const start_y: f32 = 80.0;
pub const help_anchor_y: f32 = 350.0;
pub const help_center_offset_x: f32 = -220.0;
pub const back_center_offset_x: f32 = 0.0;

pub fn textRect(font: *const game_font.Loaded, item: frontend.NewGameMenuItem) frontend_widget.Rect {
    return switch (item) {
        .tutorial => frontend_widget.type20TextRect(font, item.label(), start_y, frontend_widget.type20_center_offset_x),
        .postal_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .tutorial)), frontend_widget.type20_center_offset_x),
        .time_trial => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .postal_mode)), frontend_widget.type20_center_offset_x),
        .challenge_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .time_trial)), frontend_widget.type20_center_offset_x),
        .help => helpTextRect(font),
        .back => backTextRect(font),
    };
}

pub fn helpTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Help", help_anchor_y, help_center_offset_x);
}

pub fn backTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(
        font,
        "Back",
        frontend_widget.stackBelow(textRect(font, .challenge_mode)),
        back_center_offset_x,
    );
}
