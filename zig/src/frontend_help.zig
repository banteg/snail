const frontend_widget = @import("frontend_widget.zig");
const game_font = @import("game_font.zig");

pub const back_anchor_y: f32 = 420.0;

pub fn backTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Back", back_anchor_y, 0.0);
}
