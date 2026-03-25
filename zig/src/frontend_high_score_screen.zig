const frontend_widget = @import("frontend_widget.zig");
const game_font = @import("game_font.zig");
const frontend_bridge = @import("frontend_bridge.zig");
const high_score = @import("high_score.zig");

// PORT(verified): `initialize_high_score_screen` uses title `y = 64`, row start `111`,
// row pitch `27`, and footer row `111 + 10*27 = 381`. Each visible row is a separate
// type-22 widget bundle anchored at `x = -228/-222/-180/+160/+125` for postal or
// `x = -228/-222/-180/+125/+170` for challenge, rather than a single freehand text strip.
pub const title_y: f32 = 64.0;
pub const row_start_y: f32 = 111.0;
pub const row_pitch: f32 = 27.0;
pub const footer_y: f32 = 381.0;
pub const rank_marker_x: f32 = -228.0;
pub const rank_number_x: f32 = -222.0;
pub const name_x: f32 = -180.0;
pub const postal_score_x: f32 = 160.0;
pub const postal_replay_x: f32 = 125.0;
pub const challenge_score_x: f32 = 125.0;
pub const challenge_replay_x: f32 = 170.0;
pub const entry_cancel_x: f32 = -110.0;
pub const entry_submit_x: f32 = 55.0;
pub const back_x: f32 = -132.0;
pub const toggle_x: f32 = 33.0;

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

pub fn title(owner: Owner) []const u8 {
    return switch (owner) {
        .post_level_entry => "Enter your name here!",
        .main_menu_browse => |mode| switch (mode) {
            .postal => "Postal High Scores",
            .challenge => "Challenge High Scores",
        },
    };
}

pub fn tableToggleLabel(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "Challenge Score",
        .challenge => "Postal Scores",
    };
}

pub fn nextBrowseMode(owner: Owner) ?high_score.Mode {
    return switch (owner) {
        .post_level_entry => null,
        .main_menu_browse => |mode| switch (mode) {
            .postal => .challenge,
            .challenge => .postal,
        },
    };
}

pub fn replaySource(owner: Owner, entry_index: usize) ?frontend_bridge.SelectedLevelRecordSource {
    return switch (owner) {
        .post_level_entry => null,
        .main_menu_browse => |mode| switch (mode) {
            .postal => .{ .postal = entry_index },
            .challenge => .{ .challenge = entry_index },
        },
    };
}

pub fn displayName(entry: *const high_score.Entry) []const u8 {
    const name = entry.name();
    if (name.len == 0) return "---";
    return name;
}

pub fn rowsShowReplay(mode: high_score.Mode, in_name_entry: bool) bool {
    // PORT(verified): `initialize_high_score_screen` only enables the row Replay widgets for the
    // Challenge table, and `update_high_score_screen` suppresses them while inline name-entry is active.
    return mode == .challenge and !in_name_entry;
}

pub fn footerTextRect(font: *const game_font.Loaded, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(font, .footer_button, .center, text, footer_y, center_offset_x);
}

pub fn rowBackgroundText(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "                                               ",
        .challenge => "                                           ",
    };
}

pub fn rowBackgroundTextRect(font: *const game_font.Loaded, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(font, .compact_score_row, .left, rowBackgroundText(mode), row_y, rank_marker_x);
}

pub fn rankTextRect(font: *const game_font.Loaded, row_y: f32, rank_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(font, .compact_score_row, .left, rank_text, row_y, rank_number_x);
}

pub fn nameTextRect(font: *const game_font.Loaded, row_y: f32, display_name: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(font, .compact_score_row, .left, display_name, row_y, name_x);
}

pub fn scoreTextRect(font: *const game_font.Loaded, mode: high_score.Mode, row_y: f32, score_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        font,
        .compact_score_row,
        .right,
        score_text,
        row_y,
        switch (mode) {
            .postal => postal_score_x,
            .challenge => challenge_score_x,
        },
    );
}

pub fn replayTextRect(font: *const game_font.Loaded, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        font,
        .compact_score_row,
        .center,
        "Replay",
        row_y,
        switch (mode) {
            .postal => postal_replay_x,
            .challenge => challenge_replay_x,
        },
    );
}
