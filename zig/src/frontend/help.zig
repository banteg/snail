const app_ui = @import("../app_ui.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = app_ui.VirtualLayout;

pub const Action = enum {
    back,
};

pub const button_count: usize = 1;
pub const back_anchor_y: f32 = 420.0;

pub fn backTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.menuButtonTextRect(font, "Back", back_anchor_y, 0.0);
}

pub fn drawMenuUi(state: anytype, layout: VirtualLayout) void {
    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        backTextRect(&state.ui_font),
        state.help_button_states[0],
        false,
    );
}
