const std = @import("std");
const ui = @import("../ui.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

// PORT(verified): `initialize_new_game_menu` sets the global center justify to `25`, seeds
// Tutorial at `y = 80`, chains Postal, Time Trial, and Challenge Mode with
// `stack_widget_below`, places Help at `(center + 25 - 220, y = 350)`, then seeds Back at
// `y = 350` but immediately stacks it below Challenge Mode.
pub const start_y: f32 = 80.0;
pub const help_anchor_y: f32 = 350.0;
pub const help_center_offset_x: f32 = frontend_widget.menu_button_center_offset_x - 220.0;
pub const back_center_offset_x: f32 = frontend_widget.menu_button_center_offset_x;

pub fn textRect(font: *const game_font.Loaded, item: frontend.NewGameMenuItem) frontend_widget.Rect {
    return switch (item) {
        .tutorial => frontend_widget.menuButtonTextRect(font, item.label(), start_y, frontend_widget.menu_button_center_offset_x),
        .postal_mode => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .tutorial)), frontend_widget.menu_button_center_offset_x),
        .time_trial => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .postal_mode)), frontend_widget.menu_button_center_offset_x),
        .challenge_mode => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .time_trial)), frontend_widget.menu_button_center_offset_x),
        .help => helpTextRect(font),
        .back => backTextRect(font),
    };
}

pub fn helpTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, "Help", help_anchor_y, help_center_offset_x);
}

pub fn backTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(
        font,
        "Back",
        frontend_widget.stackBelow(textRect(font, .challenge_mode)),
        back_center_offset_x,
    );
}

pub const Context = struct {
    font: *const game_font.Loaded,
    widget_art: frontend_widget.Art,
    button_states: *const [frontend.new_game_menu_items.len]frontend_widget.TextButtonState,
};

pub fn drawMenuUi(context: Context, layout: VirtualLayout, visible_items: [4]bool) void {
    for (frontend.new_game_menu_items[0..4], 0..) |item, index| {
        if (!visible_items[index]) continue;
        frontend_widget.drawMenuButton(
            layout,
            context.widget_art,
            context.font,
            item.label(),
            textRect(context.font, item),
            context.button_states[index],
            false,
        );
    }
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        "Help",
        helpTextRect(context.font),
        context.button_states[4],
        false,
    );
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        "Back",
        backTextRect(context.font),
        context.button_states[5],
        false,
    );
}

test "new game help/back anchors include native center justify" {
    try std.testing.expectApproxEqAbs(frontend_widget.menu_button_center_offset_x - 220.0, help_center_offset_x, 0.001);
    try std.testing.expectApproxEqAbs(frontend_widget.menu_button_center_offset_x, back_center_offset_x, 0.001);
}
