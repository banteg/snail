const ui = @import("../ui.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

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

pub fn drawMenuUi(state: anytype, layout: VirtualLayout, visible_items: [4]bool) void {
    for (frontend.new_game_menu_items[0..4], 0..) |item, index| {
        if (!visible_items[index]) continue;
        frontend_widget.drawMenuButton(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            textRect(&state.ui_font, item),
            state.new_game_button_states[index],
            false,
        );
    }
    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Help",
        helpTextRect(&state.ui_font),
        state.new_game_button_states[4],
        false,
    );
    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        backTextRect(&state.ui_font),
        state.new_game_button_states[5],
        false,
    );
}
