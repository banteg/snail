const ui = @import("../ui.zig");
const frontend_widget = @import("widget.zig");

const VirtualLayout = ui.VirtualLayout;

pub const message_y: f32 = 435.0;

const hold_step: f32 = 1.0 / 240.0;
const hide_step: f32 = 1.0 / 30.0;

pub const Stage = enum(u8) {
    title_visible = 0,
    title_hidden = 1,
    challenge_visible = 2,
    challenge_hidden = 3,
    time_trial_visible = 4,
    time_trial_hidden = 5,
    continue_visible = 6,
    continue_hold = 7,
};

pub const Controller = struct {
    stage: Stage = .title_visible,
    progress: f32 = 0.0,
    progress_step: f32 = hold_step,

    pub fn reset(self: *Controller) void {
        self.* = .{};
    }

    pub fn step(self: *Controller) void {
        if (self.progress_step <= 0.0) return;

        self.progress += self.progress_step;
        if (self.progress <= 1.0) return;

        self.progress = 0.0;
        switch (self.stage) {
            .title_visible => {
                self.stage = .title_hidden;
                self.progress_step = hide_step;
            },
            .title_hidden => {
                self.stage = .challenge_visible;
                self.progress_step = hold_step;
            },
            .challenge_visible => {
                self.stage = .challenge_hidden;
                self.progress_step = hide_step;
            },
            .challenge_hidden => {
                self.stage = .time_trial_visible;
                self.progress_step = hold_step;
            },
            .time_trial_visible => {
                self.stage = .time_trial_hidden;
                self.progress_step = hide_step;
            },
            .time_trial_hidden => {
                self.stage = .continue_visible;
                self.progress_step = hold_step;
            },
            .continue_visible => {
                self.stage = .continue_hold;
                self.progress_step = 0.0;
            },
            .continue_hold => {},
        }
    }

    pub fn allowsContinue(self: *const Controller) bool {
        return @intFromEnum(self.stage) >= @intFromEnum(Stage.challenge_visible);
    }

    pub fn currentText(self: *const Controller) ?[]const u8 {
        return switch (self.stage) {
            .title_visible => "Thanks For Playing!",
            .title_hidden => null,
            .challenge_visible => "Test your reflexes in Challenge Mode!",
            .challenge_hidden => null,
            .time_trial_visible => "Improve your skills in Time Trial!",
            .time_trial_hidden => null,
            .continue_visible, .continue_hold => "Click to Continue",
        };
    }
};

pub fn drawMenuUi(state: anytype, layout: VirtualLayout) void {
    const text = state.thanks_screen_controller.currentText() orelse return;
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        text,
        frontend_widget.menuButtonTextRect(&state.ui_font, text, message_y, 0.0),
        idle_state,
        false,
        .{ .flags = 0x20400002 },
    );
}
