const ui = @import("../ui.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

pub const Mode = enum {
    quit_app,
    abandon_run,
    leave_route_map,
};

pub const Choice = enum {
    no,
    yes,

    pub fn label(self: Choice) []const u8 {
        return switch (self) {
            .no => "No",
            .yes => "Yes",
        };
    }
};

pub const choices = [_]Choice{
    .yes,
    .no,
};
pub const button_count: usize = choices.len;

// PORT(verified): the shared centered exit prompt path in `initialize_exit_prompt`
// seeds the Yes/No buttons at `330`, but then stacks both beneath the title at
// `y = stack_widget_below(title)` while keeping their `x = -80/+80` offsets.
pub const title_y: f32 = 200.0;
pub const yes_x: f32 = -80.0;
pub const no_x: f32 = 80.0;

pub fn textRect(font: *const game_font.Loaded, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    const title_rect = frontend_widget.widgetTextRect(
        font,
        .menu_button,
        .center,
        "Do you really want to quit?",
        title_y,
        0.0,
    );
    return frontend_widget.widgetTextRect(
        font,
        .menu_button,
        .center,
        text,
        frontend_widget.stackBelow(title_rect),
        center_offset_x,
    );
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
        choices[0].label(),
        textRect(context.font, choices[0].label(), yes_x),
        context.button_states[0],
        false,
    );
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        choices[1].label(),
        textRect(context.font, choices[1].label(), no_x),
        context.button_states[1],
        false,
    );
}
