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

pub fn centerOffset(mode: Mode) f32 {
    return switch (mode) {
        .quit_app, .abandon_run => frontend_widget.menu_button_center_offset_x,
        // Route-map prompts are entered from screens that reset center justify to zero.
        .leave_route_map => 0.0,
    };
}

pub fn titleCenterX(mode: Mode) f32 {
    return 320.0 + centerOffset(mode);
}

pub fn textRect(font: *const game_font.Loaded, mode: Mode, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    const title_rect = frontend_widget.widgetTextRect(
        font,
        .menu_button,
        .center,
        "Do you really want to quit?",
        title_y,
        centerOffset(mode),
    );
    return frontend_widget.widgetTextRect(
        font,
        .menu_button,
        .center,
        text,
        frontend_widget.stackBelow(title_rect),
        centerOffset(mode) + center_offset_x,
    );
}

pub const Context = struct {
    font: *const game_font.Loaded,
    widget_art: frontend_widget.Art,
    button_states: *const [button_count]frontend_widget.TextButtonState,
    mode: Mode,
};

pub fn drawMenuUi(context: Context, layout: VirtualLayout) void {
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        choices[0].label(),
        textRect(context.font, context.mode, choices[0].label(), yes_x),
        context.button_states[0],
        false,
    );
    frontend_widget.drawMenuButton(
        layout,
        context.widget_art,
        context.font,
        choices[1].label(),
        textRect(context.font, context.mode, choices[1].label(), no_x),
        context.button_states[1],
        false,
    );
}
