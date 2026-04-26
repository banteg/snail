const std = @import("std");
const ui = @import("../ui.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");
const frontend_bridge = @import("bridge.zig");
const high_score = @import("../high_score.zig");

const VirtualLayout = ui.VirtualLayout;

// PORT(verified): `initialize_high_score_screen` sets center justify to `25`, uses title
// `y = 64`, row start `111`, row pitch `27`, and footer row `111 + 10*27 = 381`. Each
// visible row is a separate compact-score-row widget bundle whose per-widget anchors are
// added to that global center justify.
pub const title_y: f32 = 64.0;
pub const row_start_y: f32 = 111.0;
pub const row_pitch: f32 = 27.0;
pub const footer_y: f32 = 381.0;
pub const rank_marker_x: f32 = frontend_widget.menu_button_center_offset_x - 228.0;
pub const rank_number_x: f32 = frontend_widget.menu_button_center_offset_x - 222.0;
pub const name_x: f32 = frontend_widget.menu_button_center_offset_x - 180.0;
pub const postal_score_x: f32 = frontend_widget.menu_button_center_offset_x + 160.0;
pub const postal_replay_x: f32 = frontend_widget.menu_button_center_offset_x + 125.0;
pub const challenge_score_x: f32 = frontend_widget.menu_button_center_offset_x + 125.0;
pub const challenge_replay_x: f32 = frontend_widget.menu_button_center_offset_x + 170.0;
pub const entry_cancel_x: f32 = frontend_widget.menu_button_center_offset_x - 110.0;
pub const entry_submit_x: f32 = frontend_widget.menu_button_center_offset_x + 55.0;
pub const back_x: f32 = frontend_widget.menu_button_center_offset_x - 132.0;
pub const toggle_x: f32 = frontend_widget.menu_button_center_offset_x + 33.0;
pub const button_count: usize = 2;
pub const replay_button_count: usize = high_score.visible_entry_count;

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
    // PORT(verified): `initialize_high_score_screen` allocates per-row Replay widgets for
    // both postal and challenge score banks. Inline name entry uses the same row space for
    // text input, so replay activation is suppressed while that owner is active.
    _ = mode;
    return !in_name_entry;
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

pub fn drawMenuUi(
    state: anytype,
    layout: VirtualLayout,
    owner: Owner,
    selected_mode: high_score.Mode,
    pending_entry: ?PendingEntry,
    pending_draft_name: ?[]const u8,
) !void {
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var title_state = frontend_widget.TextButtonState{};
    title_state.snapFor(.footer_button, false);
    const title_text = title(owner);
    frontend_widget.drawTextButton(
        layout,
        art,
        &state.ui_font,
        .footer_button,
        title_text,
        frontend_widget.widgetTextRect(
            &state.ui_font,
            .footer_button,
            .center,
            title_text,
            title_y,
            frontend_widget.menu_button_center_offset_x,
        ),
        title_state,
        false,
    );

    if (pending_entry) |context| {
        const draft_name = pending_draft_name orelse "_";
        drawTable(state, layout, context.rank, draft_name, true, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_actions[0].label(),
            footerTextRect(&state.ui_font, post_level_actions[0].label(), entry_cancel_x),
            state.post_level_high_score_button_states[0],
            false,
        );
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_actions[1].label(),
            footerTextRect(&state.ui_font, post_level_actions[1].label(), entry_submit_x),
            state.post_level_high_score_button_states[1],
            false,
        );
    } else {
        drawTable(state, layout, null, null, false, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            "Back",
            footerTextRect(&state.ui_font, "Back", back_x),
            state.high_score_button_states[0],
            false,
        );
        const toggle_label = tableToggleLabel(selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            toggle_label,
            footerTextRect(&state.ui_font, toggle_label, toggle_x),
            state.high_score_button_states[1],
            false,
        );
    }
}

fn drawTable(
    state: anytype,
    layout: VirtualLayout,
    highlight_index: ?usize,
    editing_name: ?[]const u8,
    hide_replay: bool,
    mode: high_score.Mode,
) void {
    const entries = state.high_score_tables.visibleEntries(mode);
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    const row_background_text = rowBackgroundText(mode);
    const text_only_score_cell: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_high_score_screen` gives the rank, name,
        // and numeric score cells flags `0x20400000`, so those compact-score-row widgets
        // render as text-only entries on top of the shared row background.
        .flags = 0x20400000,
    };

    for (entries, 0..) |table_entry, entry_index| {
        const row_highlighted = highlight_index != null and highlight_index.? == entry_index;
        if (!table_entry.isActive() and !row_highlighted) continue;

        const row_y = row_start_y + @as(f32, @floatFromInt(entry_index)) * row_pitch;
        var row_state = frontend_widget.TextButtonState{};
        row_state.snapFor(.compact_score_row, row_highlighted);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            row_background_text,
            rowBackgroundTextRect(&state.ui_font, mode, row_y),
            row_state,
            false,
        );

        var rank_buffer: [8]u8 = undefined;
        const rank_text = std.fmt.bufPrint(&rank_buffer, "{d}", .{entry_index + 1}) catch "";
        const display_name = if (row_highlighted and editing_name != null)
            editing_name.?
        else
            displayName(&table_entry);

        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            rank_text,
            rankTextRect(&state.ui_font, row_y, rank_text),
            row_state,
            false,
            text_only_score_cell,
        );
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            display_name,
            nameTextRect(&state.ui_font, row_y, display_name),
            row_state,
            false,
            text_only_score_cell,
        );

        var score_buffer: [32]u8 = undefined;
        const score_text = if (table_entry.isActive())
            (std.fmt.bufPrint(&score_buffer, "{d}", .{table_entry.score}) catch "0")
        else
            "";
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            score_text,
            scoreTextRect(&state.ui_font, mode, row_y, score_text),
            row_state,
            false,
            text_only_score_cell,
        );
        if (rowsShowReplay(mode, hide_replay) and table_entry.has_replay) {
            frontend_widget.drawTextButton(
                layout,
                art,
                &state.ui_font,
                .compact_score_row,
                "Replay",
                replayTextRect(&state.ui_font, mode, row_y),
                state.high_score_replay_button_states[entry_index],
                false,
            );
        }
    }
}
