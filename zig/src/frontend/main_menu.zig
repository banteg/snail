const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

// PORT(verified): `initialize_main_menu` seeds the first button at `y = 90`, then chains
// High Scores, Options, Credits, and Exit with `sub_4027B0`. Windows seeds Exit with
// `y = 390` first, but immediately overrides it by chaining from Credits.
pub const start_y: f32 = 90.0;

pub fn textRect(font: *const game_font.Loaded, item: frontend.MainMenuItem) frontend_widget.Rect {
    return switch (item) {
        .new_game => frontend_widget.type20TextRect(font, item.label(), start_y, frontend_widget.type20_center_offset_x),
        .high_scores => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .new_game)), frontend_widget.type20_center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .high_scores)), frontend_widget.type20_center_offset_x),
        .credits => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .options)), frontend_widget.type20_center_offset_x),
        .exit => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(textRect(font, .credits)), frontend_widget.type20_center_offset_x),
    };
}
