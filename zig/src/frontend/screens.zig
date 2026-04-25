const std = @import("std");

const high_score = @import("../high_score.zig");
const challenge_setup_menu = @import("challenge_setup_menu.zig");
const exit_prompt = @import("exit_prompt.zig");
const frontend_widget = @import("widget.zig");
const help = @import("help.zig");
const high_score_screen = @import("high_score_screen.zig");
const main_menu = @import("main_menu.zig");
const new_game_menu = @import("new_game_menu.zig");
const options_menu = @import("options_menu.zig");
const pause_menu = @import("pause_menu.zig");
const render = @import("render.zig");
const route_map = @import("route_map.zig");
const thanks = @import("thanks.zig");

fn widgetArt(state: anytype) frontend_widget.Art {
    return .{
        .border = state.frontend_widget_art.border.?.texture,
    };
}

pub fn drawBoot(state: anytype, layout: anytype) void {
    if (state.current_loading_screen != null) return;

    const font_size = layout.fontSize(30);
    const title_width = render.measureText(state, "Loading...", font_size);
    const title_point = layout.mapPoint(320.0, 240.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    render.drawText(
        state,
        "Loading...",
        title_x - @divTrunc(title_width, 2),
        title_y - layout.scaleInt(18),
        font_size,
        .ray_white,
    );
}

pub fn drawTextScript(state: anytype, layout: anytype) void {
    const script = state.currentTextScript() orelse return;
    const progress = state.currentTextScriptProgress() orelse 0.0;
    script.drawCrawl(&state.ui_font, progress, .{
        .x = layout.x,
        .y = layout.y,
        .width = layout.width,
        .height = layout.height,
    });
}

pub fn drawMainMenu(state: anytype, layout: anytype) !void {
    main_menu.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .button_states = &state.main_menu_button_states,
    }, layout);

    if (state.game_status_message) |message| {
        try render.drawStatusMessage(state, layout, message);
    }
}

pub fn drawNewGameMenu(state: anytype, layout: anytype) !void {
    new_game_menu.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .button_states = &state.new_game_button_states,
    }, layout, .{
        state.newGameMenuItemVisible(.tutorial),
        state.newGameMenuItemVisible(.postal_mode),
        state.newGameMenuItemVisible(.time_trial),
        state.newGameMenuItemVisible(.challenge_mode),
    });

    if (state.game_status_message) |message| {
        try render.drawStatusMessage(state, layout, message);
    }
}

fn challengeSetupLayoutState(
    state: anytype,
    difficulty_buffer: []u8,
    speed_buffer: []u8,
) challenge_setup_menu.LayoutState {
    return .{
        .replay_available = state.challengeSetupReplayAvailable(),
        .difficulty_value_text = options_menu.sliderValueText(@as(f32, @floatFromInt(state.runtime_config.challengeReplayDifficultyValue())) * 0.01, difficulty_buffer),
        .speed_value_text = options_menu.sliderValueText(@as(f32, @floatFromInt(state.runtime_config.challengeReplaySpeedValue())) * 0.01, speed_buffer),
        .difficulty_row_state = state.challenge_setup_button_states[challenge_setup_menu.difficulty_button_index],
        .speed_row_state = state.challenge_setup_button_states[challenge_setup_menu.speed_button_index],
    };
}

pub fn drawChallengeSetupMenu(state: anytype, layout: anytype) !void {
    const active_target = state.activeFrontendButtonTarget();
    var difficulty_buffer: [16]u8 = undefined;
    var speed_buffer: [16]u8 = undefined;
    challenge_setup_menu.drawMenuUi(
        state,
        layout,
        challengeSetupLayoutState(state, &difficulty_buffer, &speed_buffer),
        active_target,
        state.slider_art.textures(),
    );

    if (state.game_status_message) |message| {
        try render.drawStatusMessage(state, layout, message);
    }
}

pub fn drawOptionsMenu(state: anytype, layout: anytype) !void {
    const menu_layout = state.optionsMenuLayoutState();
    const active_target = state.activeFrontendButtonTarget();
    options_menu.drawMenuUi(state, layout, menu_layout, active_target, state.slider_art.textures());

    if (state.game_status_message) |message| {
        try render.drawStatusMessage(state, layout, message);
    }
}

pub fn drawPauseMenu(state: anytype, layout: anytype) void {
    pause_menu.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .button_states = &state.pause_menu_button_states,
    }, layout);
}

pub fn drawRouteMapMenu(state: anytype, layout: anytype) !void {
    route_map.drawMenuUi(state, layout);

    if (state.game_status_message) |message| {
        try render.drawNoticeBlock(state, layout, 320.0, 438.0, message, .ray_white);
    }
}

pub fn drawHighScoresMenu(state: anytype, layout: anytype) !void {
    const pending_entry = state.postLevelHighScoreContext();
    const selected_mode = state.activeHighScoreScreenMode();
    var draft_buffer: [high_score.name_capacity + 1]u8 = undefined;
    const pending_draft_name = if (pending_entry != null)
        if (state.postLevelHighScoreDraft().len == 0)
            "_"
        else
            try std.fmt.bufPrint(&draft_buffer, "{s}_", .{state.postLevelHighScoreDraft()})
    else
        null;
    try high_score_screen.drawMenuUi(
        state,
        layout,
        state.high_score_screen_owner,
        selected_mode,
        pending_entry,
        pending_draft_name,
    );

    if (state.game_status_message) |message| {
        try render.drawStatusMessage(state, layout, message);
    }
}

pub fn drawExitPrompt(state: anytype, layout: anytype) void {
    render.drawHeading(
        state,
        layout,
        exit_prompt.titleCenterX(state.exit_prompt_mode),
        exit_prompt.title_y,
        "Do you really want to quit?",
        26,
        .center,
        .ray_white,
    );
    exit_prompt.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .button_states = &state.exit_prompt_button_states,
        .mode = state.exit_prompt_mode,
    }, layout);
}

pub fn drawHelp(state: anytype, layout: anytype) void {
    help.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .button_states = &state.help_button_states,
    }, layout);
}

pub fn drawThanks(state: anytype, layout: anytype) void {
    thanks.drawMenuUi(.{
        .font = &state.ui_font,
        .widget_art = widgetArt(state),
        .current_text = state.thanks_screen_controller.currentText(),
    }, layout);
}
