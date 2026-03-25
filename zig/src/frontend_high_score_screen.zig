const high_score = @import("high_score.zig");

pub const PendingEntry = struct {
    mode: high_score.Mode,
    rank: usize,
};

pub const Owner = union(enum) {
    main_menu_browse: high_score.Mode,
    post_level_entry: PendingEntry,

    pub fn activeMode(self: Owner) high_score.Mode {
        return switch (self) {
            .main_menu_browse => |mode| mode,
            .post_level_entry => |context| context.mode,
        };
    }
};

pub const PostLevelAction = enum {
    cancel,
    submit,

    pub fn label(self: PostLevelAction) []const u8 {
        return switch (self) {
            .cancel => "Cancel",
            .submit => "Submit",
        };
    }
};

pub const post_level_actions = [_]PostLevelAction{
    .cancel,
    .submit,
};

pub const MenuAction = enum {
    back,
    switch_table,
};

pub const menu_actions = [_]MenuAction{
    .back,
    .switch_table,
};

pub const screen_modes = [_]high_score.Mode{
    .postal,
    .challenge,
};

pub fn modeIndex(mode: high_score.Mode) usize {
    for (screen_modes, 0..) |candidate, index| {
        if (candidate == mode) return index;
    }
    return 0;
}
