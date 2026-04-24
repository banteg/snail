const ui = @import("../ui.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

// PORT(verified): `cRSubPause::Init()` creates the centered pause stack with `End Game`
// at `y = 145`, then chains `Options` and `Resume` below it with the shared shell-font
// widget stack helper.
pub const start_y: f32 = 145.0;
pub const center_offset_x: f32 = 0.0;
pub const items = frontend.pause_menu_items;

pub fn textRect(font: *const game_font.Loaded, item: frontend.PauseMenuItem) frontend_widget.Rect {
    return switch (item) {
        .end_game => frontend_widget.menuButtonTextRect(font, item.label(), start_y, center_offset_x),
        .options => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .end_game)), center_offset_x),
        .@"resume" => frontend_widget.menuButtonTextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .options)), center_offset_x),
    };
}

pub const Context = struct {
    font: *const game_font.Loaded,
    widget_art: frontend_widget.Art,
    button_states: *const [items.len]frontend_widget.TextButtonState,
};

pub fn drawMenuUi(context: Context, layout: VirtualLayout) void {
    for (items, 0..) |item, index| {
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
}
