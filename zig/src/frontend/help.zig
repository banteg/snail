const ui = @import("../ui.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

pub const Action = enum {
    back,
};

pub const button_count: usize = 1;
pub const back_anchor_y: f32 = 420.0;

pub fn backTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, "Back", back_anchor_y, 0.0);
}

pub const Context = struct {
    font: *const game_font.Loaded,
    widget_art: frontend_widget.Art,
    button_states: *const [button_count]frontend_widget.TextButtonState,
};

pub fn drawMenuUi(context: Context, layout: VirtualLayout) void {
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        "Back",
        backTextRect(context.font),
        context.button_states[0],
        false,
    );
}
