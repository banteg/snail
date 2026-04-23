const ui = @import("../ui.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

// PORT(verified): `initialize_main_menu` seeds the first button at `y = 90`, then chains
// High Scores, Options, Credits, and Exit with `sub_4027B0`. Windows seeds Exit with
// `y = 390` first, but immediately overrides it by chaining from Credits.
pub const start_y: f32 = 90.0;

pub fn textRect(font: *const game_font.Loaded, item: frontend.MainMenuItem) frontend_widget.Rect {
    return switch (item) {
        .new_game => frontend_widget.menuButtonTextRect(font, item.label(), start_y, frontend_widget.menu_button_center_offset_x),
        .high_scores => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .new_game)), frontend_widget.menu_button_center_offset_x),
        .options => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .high_scores)), frontend_widget.menu_button_center_offset_x),
        .credits => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .options)), frontend_widget.menu_button_center_offset_x),
        .exit => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .credits)), frontend_widget.menu_button_center_offset_x),
    };
}

pub fn drawMenuUi(state: anytype, layout: VirtualLayout) void {
    for (frontend.main_menu_items, 0..) |item, index| {
        frontend_widget.drawMenuButton(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            textRect(&state.ui_font, item),
            state.main_menu_button_states[index],
            false,
        );
    }
}
