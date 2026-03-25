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

// PORT(verified): the shared centered exit prompt path in `initialize_exit_prompt`
// seeds the Yes/No buttons at `330`, but then stacks both beneath the title at
// `y = stack_widget_below(title)` while keeping their `x = -80/+80` offsets.
pub const title_y: f32 = 200.0;
pub const yes_x: f32 = -80.0;
pub const no_x: f32 = 80.0;
