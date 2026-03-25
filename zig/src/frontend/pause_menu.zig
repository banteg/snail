const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

// PORT(verified): `cRSubPause::Init()` creates the centered pause stack with `End Game`
// at `y = 145`, then chains `Options` and `Resume` below it with the shared shell-font
// widget stack helper.
pub const start_y: f32 = 145.0;
pub const center_offset_x: f32 = 0.0;
pub const items = frontend.pause_menu_items;

pub fn textRect(font: *const game_font.Loaded, item: frontend.PauseMenuItem) frontend_widget.Rect {
    return switch (item) {
        .end_game => frontend_widget.type20TextRect(font, item.label(), start_y, center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .end_game)), center_offset_x),
        .@"resume" => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .options)), center_offset_x),
    };
}
