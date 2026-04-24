const std = @import("std");
const rl = @import("raylib");

const audio_volume = @import("audio_volume.zig");
const frontend_audio = @import("frontend_audio.zig");
const frontend = @import("../frontend.zig");
const frontend_activation = @import("../frontend/activation.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const frontend_challenge_setup_menu = @import("../frontend/challenge_setup_menu.zig");
const frontend_exit_prompt = @import("../frontend/exit_prompt.zig");
const frontend_flow = @import("frontend_flow.zig");
const frontend_high_score_screen = @import("../frontend/high_score_screen.zig");
const frontend_options_menu = @import("../frontend/options_menu.zig");
const frontend_pause_menu = @import("../frontend/pause_menu.zig");
const frontend_route_map = @import("../frontend/route_map.zig");
const run_result = @import("run_result.zig");

const frontend_activation_delay_step: f32 = 1.0 / 12.0;

pub fn setHoverTarget(state: anytype, target: ?frontend_activation.HoverTarget) void {
    if (state.hovered_frontend_target == target) return;
    state.hovered_frontend_target = target;
    if (target != null) {
        state.keyboard_frontend_focus_visible = false;
        frontend_audio.playHoverSound(frontend_audio.context(state));
    }
}

pub fn noteKeyboardNavigation(state: anytype) void {
    state.keyboard_frontend_focus_visible = true;
}

pub fn activeButtonTarget(state: anytype) ?frontend_activation.HoverTarget {
    if (state.pending_frontend_activation) |pending| {
        return pending.target;
    }
    return state.hovered_frontend_target;
}

pub fn buttonHot(state: anytype, target: frontend_activation.HoverTarget, fallback_selected: bool) bool {
    if (activeButtonTarget(state)) |active_target| {
        return active_target == target;
    }
    return state.keyboard_frontend_focus_visible and fallback_selected;
}

pub fn queueActivation(state: anytype, action: frontend_activation.QueuedAction) void {
    if (state.pending_frontend_activation != null) return;
    frontend_audio.playSelectSound(frontend_audio.context(state));
    const requires_fade = frontend_activation.queuedActivationRequiresFade(action);
    if (requires_fade) {
        state.frontend_transition.beginOverlayFadeOut();
    }
    state.pending_frontend_activation = .{
        .action = action,
        .target = frontend_activation.queuedActivationTarget(action),
        .requires_fade = requires_fade,
    };
}

pub fn dispatchActivation(state: anytype, action: frontend_activation.QueuedAction) !void {
    switch (action) {
        .main_menu => |item| try frontend_flow.performMainMenuItem(state, item),
        .new_game_menu => |item| try frontend_flow.performNewGameMenuItem(state, item),
        .challenge_setup_menu => |item| try frontend_flow.performChallengeSetupMenuItem(state, item),
        .options_menu => |item| try frontend_flow.performOptionsMenuItem(state, item),
        .pause_menu => |item| try frontend_flow.performPauseMenuItem(state, item),
        .route_map_menu => |item| try frontend_flow.performRouteMenuAction(state, item),
        .help_menu => |item| try frontend_flow.performHelpMenuItem(state, item),
        .high_scores_menu => |item| try frontend_flow.performHighScoreMenuAction(state, item),
        .high_score_replay => |index| try frontend_flow.performHighScoreReplay(state, index),
        .post_level_high_scores => |item| try frontend_flow.performPostLevelHighScoreAction(state, item),
        .completion_screen => |item| try frontend_flow.performCompletionAction(state, item),
        .exit_prompt => |choice| try frontend_flow.performExitPromptChoice(state, choice),
    }
}

pub fn updatePendingActivation(state: anytype) !bool {
    if (state.pending_frontend_activation) |*pending| {
        pending.progress = @min(pending.progress + frontend_activation_delay_step, 1.0);
        const fade_ready = !pending.requires_fade or state.frontend_transition.state == .black_idle;
        if (pending.progress >= 0.999 and fade_ready) {
            const action = pending.action;
            const should_fade_in = pending.requires_fade and state.frontend_transition.state == .black_idle;
            state.pending_frontend_activation = null;
            try dispatchActivation(state, action);
            if (should_fade_in) {
                state.frontend_transition.completeHandoff();
            }
            return true;
        }
    }
    return false;
}

pub fn readPressedWidgetShortcutCode() ?u8 {
    // PORT(partial): this currently implements only the native text-input codes that
    // recovered widget shortcuts actually use in the shipped front-end: Escape (`11`),
    // Enter (`5` / `6`), and lowercase `o` (`111`).
    if (rl.isKeyPressed(.escape)) return 11;
    if (rl.isKeyPressed(.enter)) {
        return if (rl.isKeyDown(.left_control) or rl.isKeyDown(.right_control)) 6 else 5;
    }
    if (rl.isKeyPressed(.o)) return 111;
    return null;
}

pub fn shortcutActivationForCode(state: anytype, code: u8) ?frontend_activation.QueuedAction {
    return switch (state.game_phase) {
        .pause_menu => switch (code) {
            11 => .{ .pause_menu = .end_game },
            111 => .{ .pause_menu = .options },
            5, 6 => .{ .pause_menu = .@"resume" },
            else => null,
        },
        .high_scores_menu => if (state.high_score_screen_owner == .post_level_entry) switch (code) {
            11 => .{ .post_level_high_scores = .cancel },
            5, 6 => .{ .post_level_high_scores = .submit },
            else => null,
        } else null,
        else => null,
    };
}

pub fn handleWidgetShortcutInput(state: anytype) !bool {
    if (state.frontend_transition.blocksInput()) return false;
    if (state.pending_frontend_activation != null) return false;
    const code = readPressedWidgetShortcutCode() orelse return false;
    const action = shortcutActivationForCode(state, code) orelse return false;
    noteKeyboardNavigation(state);
    queueActivation(state, action);
    return true;
}

pub fn stepOptionsMenuValue(state: anytype, item: frontend.OptionsMenuItem, delta: f32) !void {
    switch (item) {
        .fullscreen => {
            if (delta != 0.0) {
                frontend_audio.playSelectSound(frontend_audio.context(state));
                state.toggleFullscreenPreference();
            }
        },
        .sound_volume => {
            const previous = state.runtime_config.soundVolume();
            state.runtime_config.setSoundVolume(state.runtime_config.soundVolume() + delta);
            audio_volume.applyConfigVolumes(audio_volume.context(state));
            if (state.runtime_config.soundVolume() != previous) {
                frontend_audio.playSelectSound(frontend_audio.context(state));
            }
        },
        .music_volume => {
            state.runtime_config.setMusicVolume(state.runtime_config.musicVolume() + delta);
            audio_volume.applyConfigVolumes(audio_volume.context(state));
        },
        .back => if (delta != 0.0) {
            frontend_audio.playSelectSound(frontend_audio.context(state));
            try frontend_flow.leaveOptionsMenu(state);
        },
    }
}

pub fn stepChallengeSetupMenuValue(state: anytype, item: frontend_challenge_setup_menu.Item, delta_raw: i32) void {
    if (delta_raw == 0) return;

    switch (item) {
        .difficulty => {
            const previous = state.runtime_config.challengeReplayDifficultyValue();
            const next = std.math.clamp(
                @as(i32, @intCast(previous)) + delta_raw,
                0,
                100,
            );
            state.runtime_config.setChallengeReplayDifficultyValue(@intCast(next));
            if (state.runtime_config.challengeReplayDifficultyValue() != previous) {
                frontend_audio.playSelectSound(frontend_audio.context(state));
            }
        },
        .speed => {
            const previous = state.runtime_config.challengeReplaySpeedValue();
            const next = std.math.clamp(
                @as(i32, @intCast(previous)) + delta_raw,
                0,
                100,
            );
            state.runtime_config.setChallengeReplaySpeedValue(@intCast(next));
            if (state.runtime_config.challengeReplaySpeedValue() != previous) {
                frontend_audio.playSelectSound(frontend_audio.context(state));
            }
        },
        .play, .watch_replay, .back => {},
    }
}

pub fn handleMainMenuKeyboard(state: anytype) void {
    if (rl.isKeyPressed(.up)) {
        state.menu_index = wrappedIndex(frontend.main_menu_items.len, state.menu_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        state.menu_index = wrappedIndex(frontend.main_menu_items.len, state.menu_index, 1);
        noteKeyboardNavigation(state);
    }
    if (confirmPressed()) {
        queueActivation(state, .{ .main_menu = frontend.main_menu_items[state.menu_index] });
    }
}

pub fn handleNewGameKeyboard(state: anytype) void {
    frontend_flow.normalizeNewGameMenuSelection(state);
    if (rl.isKeyPressed(.up)) {
        frontend_flow.stepNewGameMenuSelection(state, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        frontend_flow.stepNewGameMenuSelection(state, 1);
        noteKeyboardNavigation(state);
    }
    if (confirmPressed()) {
        const item = frontend.new_game_menu_items[state.new_game_menu_index];
        if (frontend_flow.newGameMenuItemVisible(state, item)) {
            queueActivation(state, .{ .new_game_menu = item });
        }
    }
}

pub fn handleChallengeSetupKeyboard(state: anytype) void {
    frontend_flow.normalizeChallengeSetupSelection(state);
    const visible_items = frontend_flow.challengeSetupVisibleItems(state);
    if (rl.isKeyPressed(.up)) {
        state.challenge_setup_index = wrappedIndex(visible_items.len, state.challenge_setup_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        state.challenge_setup_index = wrappedIndex(visible_items.len, state.challenge_setup_index, 1);
        noteKeyboardNavigation(state);
    }

    const selected = frontend_flow.currentChallengeSetupSelectedItem(state);
    if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
        noteKeyboardNavigation(state);
        stepChallengeSetupMenuValue(state, selected, -frontend_challenge_setup_menu.slider_adjust_step);
    }
    if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
        noteKeyboardNavigation(state);
        stepChallengeSetupMenuValue(state, selected, frontend_challenge_setup_menu.slider_adjust_step);
    }
    if (confirmPressed()) {
        switch (selected) {
            .play, .watch_replay, .back => queueActivation(state, .{ .challenge_setup_menu = selected }),
            .difficulty, .speed => {},
        }
    }
}

pub fn handleOptionsKeyboard(state: anytype) !void {
    if (rl.isKeyPressed(.up)) {
        state.options_menu_index = wrappedIndex(frontend.options_menu_items.len, state.options_menu_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        state.options_menu_index = wrappedIndex(frontend.options_menu_items.len, state.options_menu_index, 1);
        noteKeyboardNavigation(state);
    }

    const selected = frontend.options_menu_items[state.options_menu_index];
    if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
        noteKeyboardNavigation(state);
        try stepOptionsMenuValue(state, selected, -frontend_options_menu.slider_adjust_step);
    }
    if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
        noteKeyboardNavigation(state);
        try stepOptionsMenuValue(state, selected, frontend_options_menu.slider_adjust_step);
    }
    if (confirmPressed()) {
        switch (selected) {
            .fullscreen, .back => queueActivation(state, .{ .options_menu = selected }),
            .sound_volume, .music_volume => {},
        }
    }
}

pub fn handlePauseKeyboard(state: anytype) void {
    if (rl.isKeyPressed(.up)) {
        state.pause_menu_index = wrappedIndex(frontend_pause_menu.items.len, state.pause_menu_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        state.pause_menu_index = wrappedIndex(frontend_pause_menu.items.len, state.pause_menu_index, 1);
        noteKeyboardNavigation(state);
    }
    if (confirmPressed()) {
        queueActivation(state, .{ .pause_menu = frontend_pause_menu.items[state.pause_menu_index] });
    }
}

pub fn handleRouteMapKeyboard(state: anytype) !void {
    const route_actions = frontend_flow.activeRouteMenuActions(state);
    if (rl.isKeyPressed(.up)) {
        state.route_menu_action_index = wrappedIndex(route_actions.len, state.route_menu_action_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down)) {
        state.route_menu_action_index = wrappedIndex(route_actions.len, state.route_menu_action_index, 1);
        noteKeyboardNavigation(state);
    }
    if (frontend_bridge.routeMapAllowsRouteSwitching(state.route_map_screen_mode) and rl.isKeyPressed(.left)) {
        noteKeyboardNavigation(state);
        try frontend_flow.stepFrontendRouteSelection(state, -1);
    }
    if (frontend_bridge.routeMapAllowsRouteSwitching(state.route_map_screen_mode) and rl.isKeyPressed(.right)) {
        noteKeyboardNavigation(state);
        try frontend_flow.stepFrontendRouteSelection(state, 1);
    }
    if (confirmPressed()) {
        queueActivation(state, .{ .route_map_menu = route_actions[state.route_menu_action_index] });
    }
}

pub fn handleHighScoresKeyboard(state: anytype) void {
    if (state.high_score_screen_owner == .post_level_entry) {
        if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
            state.post_level_high_score_action_index = wrappedIndex(frontend_high_score_screen.post_level_actions.len, state.post_level_high_score_action_index, -1);
            noteKeyboardNavigation(state);
        }
        if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
            state.post_level_high_score_action_index = wrappedIndex(frontend_high_score_screen.post_level_actions.len, state.post_level_high_score_action_index, 1);
            noteKeyboardNavigation(state);
        }
        if (confirmPressed()) {
            queueActivation(state, .{ .post_level_high_scores = frontend_high_score_screen.post_level_actions[state.post_level_high_score_action_index] });
        }
    } else {
        if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
            state.high_scores_action_index = wrappedIndex(frontend_high_score_screen.menu_actions.len, state.high_scores_action_index, -1);
            noteKeyboardNavigation(state);
        }
        if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
            state.high_scores_action_index = wrappedIndex(frontend_high_score_screen.menu_actions.len, state.high_scores_action_index, 1);
            noteKeyboardNavigation(state);
        }
        if (confirmPressed()) {
            queueActivation(state, .{ .high_scores_menu = frontend_high_score_screen.menu_actions[state.high_scores_action_index] });
        }
    }
}

pub fn handleExitPromptKeyboard(state: anytype) void {
    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
        state.exit_prompt_choice_index = wrappedIndex(frontend_exit_prompt.choices.len, state.exit_prompt_choice_index, -1);
        noteKeyboardNavigation(state);
    }
    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
        state.exit_prompt_choice_index = wrappedIndex(frontend_exit_prompt.choices.len, state.exit_prompt_choice_index, 1);
        noteKeyboardNavigation(state);
    }
    if (confirmPressed()) {
        queueActivation(state, .{ .exit_prompt = frontend_exit_prompt.choices[state.exit_prompt_choice_index] });
    }
}

pub fn handleCompletionKeyboard(state: anytype) void {
    if (run_result.completionContinueVisible(state) and confirmPressed()) {
        noteKeyboardNavigation(state);
        queueActivation(state, .{ .completion_screen = .continue_flow });
    }
}

pub fn handleHelpKeyboard(state: anytype) void {
    if (confirmPressed()) {
        queueActivation(state, .{ .help_menu = .back });
    }
}

pub fn updateWidgetAnimations(state: anytype) void {
    const main_menu_active = state.game_phase == .main_menu and !state.frontend_transition.blocksInput();
    for (&state.main_menu_button_states, 0..) |*button_state, index| {
        button_state.stepFor(.menu_button, main_menu_active and buttonHot(state, frontend_activation.hoverTargetForMainMenu(index), state.menu_index == index));
    }

    const new_game_active = state.game_phase == .new_game_menu and !state.frontend_transition.blocksInput();
    for (&state.new_game_button_states, 0..) |*button_state, index| {
        button_state.stepFor(
            .menu_button,
            new_game_active and
                frontend_flow.newGameMenuIndexVisible(state, index) and
                buttonHot(state, frontend_activation.hoverTargetForNewGame(index), state.new_game_menu_index == index),
        );
    }

    const challenge_setup_active = state.game_phase == .challenge_setup_menu and !state.frontend_transition.blocksInput();
    const selected_challenge_item = frontend_flow.currentChallengeSetupSelectedItem(state);
    for (&state.challenge_setup_button_states, 0..) |*button_state, index| {
        const item = frontend_challenge_setup_menu.items[index];
        const hot = switch (item) {
            .difficulty, .speed => blk: {
                const active_target = activeButtonTarget(state);
                break :blk challenge_setup_active and
                    ((active_target != null and frontend_activation.sliderHoverTargetBelongsToChallengeSetupRow(active_target.?, item)) or
                        (state.keyboard_frontend_focus_visible and selected_challenge_item == item));
            },
            .watch_replay => challenge_setup_active and frontend_flow.challengeSetupReplayAvailable(state) and buttonHot(
                state,
                frontend_activation.hoverTargetForChallengeSetupItem(item),
                selected_challenge_item == item,
            ),
            .play, .back => challenge_setup_active and buttonHot(
                state,
                frontend_activation.hoverTargetForChallengeSetupItem(item),
                selected_challenge_item == item,
            ),
        };
        button_state.stepFor(.menu_button, hot);
    }
    state.challenge_setup_speed_display_value = stepSliderDisplay(
        state.challenge_setup_speed_display_value,
        @as(f32, @floatFromInt(state.runtime_config.challengeReplaySpeedValue())) * 0.01,
    );
    state.challenge_setup_difficulty_display_value = stepSliderDisplay(
        state.challenge_setup_difficulty_display_value,
        @as(f32, @floatFromInt(state.runtime_config.challengeReplayDifficultyValue())) * 0.01,
    );

    const options_active = state.game_phase == .options_menu and !state.frontend_transition.blocksInput();
    for (&state.options_button_states, 0..) |*button_state, index| {
        const item = frontend.options_menu_items[index];
        const hot = switch (item) {
            .sound_volume, .music_volume => blk: {
                const active_target = activeButtonTarget(state);
                break :blk options_active and ((active_target != null and frontend_activation.sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (state.keyboard_frontend_focus_visible and state.options_menu_index == index));
            },
            else => options_active and buttonHot(state, frontend_activation.hoverTargetForOptions(index), state.options_menu_index == index),
        };
        button_state.stepFor(.menu_button, hot);
    }
    state.options_sound_display_value = stepSliderDisplay(state.options_sound_display_value, state.runtime_config.soundVolume());
    state.options_music_display_value = stepSliderDisplay(state.options_music_display_value, state.runtime_config.musicVolume());

    const pause_menu_active = state.game_phase == .pause_menu and !state.frontend_transition.blocksInput();
    for (&state.pause_menu_button_states, 0..) |*button_state, index| {
        button_state.stepFor(.menu_button, pause_menu_active and buttonHot(state, frontend_activation.hoverTargetForPauseMenu(index), state.pause_menu_index == index));
    }

    const route_map_active = state.game_phase == .route_map_menu and !state.frontend_transition.blocksInput();
    const route_map_card_open = state.routeMapCardIsOpen();
    state.route_map_button_states[frontend_route_map.primary_button_index].stepFor(
        .menu_button,
        route_map_active and route_map_card_open and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.play), activeRouteMenuHotAction(state) == .play),
    );
    state.route_map_button_states[frontend_route_map.replay_button_index].stepFor(
        .route_map_secondary_action,
        route_map_active and route_map_card_open and state.routeMapShowsReplay() and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.watch_best_trial), activeRouteMenuHotAction(state) == .watch_best_trial),
    );
    state.route_map_button_states[frontend_route_map.back_button_index].stepFor(
        .menu_button,
        route_map_active and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.back), activeRouteMenuHotAction(state) == .back),
    );

    const help_active = state.game_phase == .help and !state.frontend_transition.blocksInput();
    state.help_button_states[0].stepFor(.menu_button, help_active and buttonHot(state, .help_back, true));

    const high_scores_active = state.game_phase == .high_scores_menu and !state.frontend_transition.blocksInput();
    const post_level_active = state.high_score_screen_owner == .post_level_entry;
    for (&state.high_score_button_states, 0..) |*button_state, index| {
        button_state.stepFor(.footer_button, high_scores_active and !post_level_active and buttonHot(state, frontend_activation.hoverTargetForHighScores(index), state.high_scores_action_index == index));
    }
    for (&state.high_score_replay_button_states, 0..) |*button_state, index| {
        button_state.stepFor(
            .compact_score_row,
            high_scores_active and !post_level_active and state.highScoreReplayAvailable(index) and buttonHot(state, frontend_activation.hoverTargetForHighScoreReplay(index), false),
        );
    }
    for (&state.post_level_high_score_button_states, 0..) |*button_state, index| {
        button_state.stepFor(.footer_button, high_scores_active and post_level_active and buttonHot(state, frontend_activation.hoverTargetForPostLevelHighScores(index), state.post_level_high_score_action_index == index));
    }

    const completion_active = run_result.completionScreenInteractive(state);
    state.completion_continue_button_state.stepFor(
        .menu_button,
        completion_active and run_result.completionContinueVisible(state) and buttonHot(state, .completion_continue, true),
    );

    const exit_prompt_active = state.game_phase == .exit_prompt and !state.frontend_transition.blocksInput();
    for (&state.exit_prompt_button_states, 0..) |*button_state, index| {
        button_state.stepFor(.menu_button, exit_prompt_active and buttonHot(state, frontend_activation.hoverTargetForExitPrompt(index), state.exit_prompt_choice_index == index));
    }
}

pub fn snapWidgetStates(state: anytype) void {
    for (&state.main_menu_button_states, 0..) |*button_state, index| {
        button_state.snapFor(.menu_button, state.game_phase == .main_menu and buttonHot(state, frontend_activation.hoverTargetForMainMenu(index), state.menu_index == index));
    }
    for (&state.new_game_button_states, 0..) |*button_state, index| {
        button_state.snapFor(
            .menu_button,
            state.game_phase == .new_game_menu and
                frontend_flow.newGameMenuIndexVisible(state, index) and
                buttonHot(state, frontend_activation.hoverTargetForNewGame(index), state.new_game_menu_index == index),
        );
    }
    const selected_challenge_item = frontend_flow.currentChallengeSetupSelectedItem(state);
    for (&state.challenge_setup_button_states, 0..) |*button_state, index| {
        const item = frontend_challenge_setup_menu.items[index];
        const hot = switch (item) {
            .difficulty, .speed => blk: {
                const active_target = activeButtonTarget(state);
                break :blk state.game_phase == .challenge_setup_menu and
                    ((active_target != null and frontend_activation.sliderHoverTargetBelongsToChallengeSetupRow(active_target.?, item)) or
                        (state.keyboard_frontend_focus_visible and selected_challenge_item == item));
            },
            .watch_replay => state.game_phase == .challenge_setup_menu and frontend_flow.challengeSetupReplayAvailable(state) and buttonHot(
                state,
                frontend_activation.hoverTargetForChallengeSetupItem(item),
                selected_challenge_item == item,
            ),
            .play, .back => state.game_phase == .challenge_setup_menu and buttonHot(
                state,
                frontend_activation.hoverTargetForChallengeSetupItem(item),
                selected_challenge_item == item,
            ),
        };
        button_state.snapFor(.menu_button, hot);
    }
    for (&state.options_button_states, 0..) |*button_state, index| {
        const item = frontend.options_menu_items[index];
        const hot = switch (item) {
            .sound_volume, .music_volume => blk: {
                const active_target = activeButtonTarget(state);
                break :blk state.game_phase == .options_menu and ((active_target != null and frontend_activation.sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (state.keyboard_frontend_focus_visible and state.options_menu_index == index));
            },
            else => state.game_phase == .options_menu and buttonHot(state, frontend_activation.hoverTargetForOptions(index), state.options_menu_index == index),
        };
        button_state.snapFor(.menu_button, hot);
    }
    for (&state.pause_menu_button_states, 0..) |*button_state, index| {
        button_state.snapFor(.menu_button, state.game_phase == .pause_menu and buttonHot(state, frontend_activation.hoverTargetForPauseMenu(index), state.pause_menu_index == index));
    }

    const route_map_card_open = state.routeMapCardIsOpen();
    state.route_map_button_states[frontend_route_map.primary_button_index].snapFor(
        .menu_button,
        state.game_phase == .route_map_menu and route_map_card_open and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.play), activeRouteMenuHotAction(state) == .play),
    );
    state.route_map_button_states[frontend_route_map.replay_button_index].snapFor(
        .route_map_secondary_action,
        state.game_phase == .route_map_menu and route_map_card_open and state.routeMapShowsReplay() and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.watch_best_trial), activeRouteMenuHotAction(state) == .watch_best_trial),
    );
    state.route_map_button_states[frontend_route_map.back_button_index].snapFor(
        .menu_button,
        state.game_phase == .route_map_menu and buttonHot(state, frontend_activation.hoverTargetForRouteMenuAction(.back), activeRouteMenuHotAction(state) == .back),
    );
    state.help_button_states[0].snapFor(.menu_button, state.game_phase == .help and buttonHot(state, .help_back, true));

    const post_level_active = state.high_score_screen_owner == .post_level_entry;
    for (&state.high_score_button_states, 0..) |*button_state, index| {
        button_state.snapFor(.footer_button, state.game_phase == .high_scores_menu and !post_level_active and buttonHot(state, frontend_activation.hoverTargetForHighScores(index), state.high_scores_action_index == index));
    }
    for (&state.high_score_replay_button_states, 0..) |*button_state, index| {
        button_state.snapFor(
            .compact_score_row,
            state.game_phase == .high_scores_menu and !post_level_active and state.highScoreReplayAvailable(index) and buttonHot(state, frontend_activation.hoverTargetForHighScoreReplay(index), false),
        );
    }
    for (&state.post_level_high_score_button_states, 0..) |*button_state, index| {
        button_state.snapFor(.footer_button, state.game_phase == .high_scores_menu and post_level_active and buttonHot(state, frontend_activation.hoverTargetForPostLevelHighScores(index), state.post_level_high_score_action_index == index));
    }
    state.completion_continue_button_state.snapFor(
        .menu_button,
        run_result.completionScreenInteractive(state) and run_result.completionContinueVisible(state) and buttonHot(state, .completion_continue, true),
    );
    for (&state.exit_prompt_button_states, 0..) |*button_state, index| {
        button_state.snapFor(.menu_button, state.game_phase == .exit_prompt and buttonHot(state, frontend_activation.hoverTargetForExitPrompt(index), state.exit_prompt_choice_index == index));
    }
}

fn activeRouteMenuHotAction(state: anytype) frontend.RouteMenuAction {
    return frontend_flow.activeRouteMenuHotAction(state);
}

fn confirmPressed() bool {
    return rl.isKeyPressed(.enter) or rl.isKeyPressed(.space);
}

fn wrappedIndex(count: usize, current: usize, delta: isize) usize {
    if (count == 0) return 0;
    const count_signed: isize = @intCast(count);
    var next = @as(isize, @intCast(current)) + delta;
    next = @mod(next, count_signed);
    return @intCast(next);
}

fn stepSliderDisplay(current: f32, target: f32) f32 {
    return current + (target - current) * 0.35;
}
