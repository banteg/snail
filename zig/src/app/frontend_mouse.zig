const rl = @import("raylib");

const frontend_audio = @import("frontend_audio.zig");
const frontend = @import("../frontend.zig");
const frontend_activation = @import("../frontend/activation.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const frontend_challenge_setup_menu = @import("../frontend/challenge_setup_menu.zig");
const frontend_completion_screen = @import("../frontend/completion_screen.zig");
const frontend_exit_prompt = @import("../frontend/exit_prompt.zig");
const frontend_flow = @import("frontend_flow.zig");
const frontend_high_score_screen = @import("../frontend/high_score_screen.zig");
const frontend_input = @import("frontend_input.zig");
const frontend_main_menu = @import("../frontend/main_menu.zig");
const frontend_new_game_menu = @import("../frontend/new_game_menu.zig");
const frontend_options_menu = @import("../frontend/options_menu.zig");
const frontend_pause_menu = @import("../frontend/pause_menu.zig");
const frontend_route_map = @import("../frontend/route_map.zig");
const frontend_widget = @import("../frontend/widget.zig");
const route_map_state = @import("route_map_state.zig");
const run_result = @import("run_result.zig");

pub fn updateMainMenuSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };
    var hovered_index: ?usize = null;

    for (frontend.main_menu_items, 0..) |item, index| {
        const text_rect = frontend_main_menu.textRect(&state.ui_font, item);
        if (frontend_widget.hitRect(text_rect, state.main_menu_button_states[index]).contains(local_mouse)) {
            hovered_index = index;
        }
    }

    if (hovered_index) |index| {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForMainMenu(index));
        state.menu_index = index;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .main_menu = frontend.main_menu_items[index] });
        }
    } else {
        frontend_input.setHoverTarget(state, null);
    }
}

pub fn updateNewGameSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };
    var hovered_index: ?usize = null;

    for (frontend.new_game_menu_items[0..4], 0..) |item, index| {
        if (!frontend_flow.newGameMenuItemVisible(state, item)) continue;
        const text_rect = frontend_new_game_menu.textRect(&state.ui_font, item);
        if (frontend_widget.hitRect(text_rect, state.new_game_button_states[index]).contains(local_mouse)) {
            hovered_index = index;
        }
    }

    const help_rect = frontend_new_game_menu.helpTextRect(&state.ui_font);
    if (frontend_widget.hitRect(help_rect, state.new_game_button_states[4]).contains(local_mouse)) {
        hovered_index = 4;
    }

    const back_rect = frontend_new_game_menu.backTextRect(&state.ui_font);
    if (frontend_widget.hitRect(back_rect, state.new_game_button_states[5]).contains(local_mouse)) {
        hovered_index = 5;
    }

    if (hovered_index) |index| {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForNewGame(index));
        state.new_game_menu_index = index;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .new_game_menu = frontend.new_game_menu_items[index] });
        }
    } else {
        frontend_input.setHoverTarget(state, null);
    }
}

pub fn updateChallengeSetupSelection(state: anytype) void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };

    const difficulty_slider = challengeSetupSliderLayout(state, .difficulty);
    if (difficulty_slider.less_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForChallengeSetupSliderArrow(.difficulty, .less));
        state.challenge_setup_index = 0;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.stepChallengeSetupMenuValue(state, .difficulty, -frontend_challenge_setup_menu.slider_adjust_step);
        }
        return;
    }
    if (difficulty_slider.more_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForChallengeSetupSliderArrow(.difficulty, .more));
        state.challenge_setup_index = 0;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.stepChallengeSetupMenuValue(state, .difficulty, frontend_challenge_setup_menu.slider_adjust_step);
        }
        return;
    }
    if (difficulty_slider.frame_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, .challenge_setup_difficulty);
        state.challenge_setup_index = 0;
        return;
    }

    const speed_slider = challengeSetupSliderLayout(state, .speed);
    if (speed_slider.less_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForChallengeSetupSliderArrow(.speed, .less));
        state.challenge_setup_index = 1;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.stepChallengeSetupMenuValue(state, .speed, -frontend_challenge_setup_menu.slider_adjust_step);
        }
        return;
    }
    if (speed_slider.more_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForChallengeSetupSliderArrow(.speed, .more));
        state.challenge_setup_index = 1;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.stepChallengeSetupMenuValue(state, .speed, frontend_challenge_setup_menu.slider_adjust_step);
        }
        return;
    }
    if (speed_slider.frame_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, .challenge_setup_speed);
        state.challenge_setup_index = 1;
        return;
    }

    const visible_items = frontend_flow.challengeSetupVisibleItems(state);
    for (visible_items, 0..) |item, visible_index| {
        switch (item) {
            .difficulty, .speed => continue,
            .play, .watch_replay, .back => {
                const text_rect = challengeSetupTextRect(state, item);
                const button_index = switch (item) {
                    .play => frontend_challenge_setup_menu.play_button_index,
                    .watch_replay => frontend_challenge_setup_menu.watch_replay_button_index,
                    .back => frontend_challenge_setup_menu.back_button_index,
                    .difficulty, .speed => unreachable,
                };
                if (frontend_widget.hitRect(text_rect, state.challenge_setup_button_states[button_index]).contains(local_mouse)) {
                    frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForChallengeSetupItem(item));
                    state.challenge_setup_index = visible_index;
                    if (rl.isMouseButtonPressed(.left)) {
                        frontend_input.queueActivation(state, .{ .challenge_setup_menu = item });
                    }
                    return;
                }
            },
        }
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn updateOptionsSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };

    const layout_state = optionsMenuLayoutState(state);
    const fullscreen_rect = frontend_options_menu.textRect(&state.ui_font, layout_state, .fullscreen);
    if (frontend_widget.hitRect(fullscreen_rect, state.options_button_states[frontend_options_menu.fullscreen_button_index]).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptions(0));
        state.options_menu_index = 0;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .options_menu = .fullscreen });
        }
        return;
    }

    const sound_slider = frontend_options_menu.sliderLayout(&state.ui_font, layout_state, .sound_volume);
    if (sound_slider.less_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptionsSliderArrow(.sound_volume, .less));
        state.options_menu_index = 1;
        if (rl.isMouseButtonPressed(.left)) {
            try frontend_input.stepOptionsMenuValue(state, .sound_volume, -frontend_options_menu.slider_adjust_step);
        }
        return;
    }
    if (sound_slider.more_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptionsSliderArrow(.sound_volume, .more));
        state.options_menu_index = 1;
        if (rl.isMouseButtonPressed(.left)) {
            try frontend_input.stepOptionsMenuValue(state, .sound_volume, frontend_options_menu.slider_adjust_step);
        }
        return;
    }
    if (sound_slider.frame_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptions(1));
        state.options_menu_index = 1;
        return;
    }

    const music_slider = frontend_options_menu.sliderLayout(&state.ui_font, layout_state, .music_volume);
    if (music_slider.less_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptionsSliderArrow(.music_volume, .less));
        state.options_menu_index = 2;
        if (rl.isMouseButtonPressed(.left)) {
            try frontend_input.stepOptionsMenuValue(state, .music_volume, -frontend_options_menu.slider_adjust_step);
        }
        return;
    }
    if (music_slider.more_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptionsSliderArrow(.music_volume, .more));
        state.options_menu_index = 2;
        if (rl.isMouseButtonPressed(.left)) {
            try frontend_input.stepOptionsMenuValue(state, .music_volume, frontend_options_menu.slider_adjust_step);
        }
        return;
    }
    if (music_slider.frame_rect.contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptions(2));
        state.options_menu_index = 2;
        return;
    }

    const back_rect = frontend_options_menu.textRect(&state.ui_font, layout_state, .back);
    if (frontend_widget.hitRect(back_rect, state.options_button_states[frontend_options_menu.back_button_index]).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForOptions(3));
        state.options_menu_index = 3;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .options_menu = .back });
        }
        return;
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn updatePauseSelection(state: anytype) void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };
    var hovered_index: ?usize = null;

    for (frontend_pause_menu.items, 0..) |item, index| {
        const text_rect = frontend_pause_menu.textRect(&state.ui_font, item);
        if (frontend_widget.hitRect(text_rect, state.pause_menu_button_states[index]).contains(local_mouse)) {
            hovered_index = index;
        }
    }

    if (hovered_index) |index| {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForPauseMenu(index));
        state.pause_menu_index = index;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .pause_menu = frontend_pause_menu.items[index] });
        }
    } else {
        frontend_input.setHoverTarget(state, null);
    }
}

pub fn updateRouteMapSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        clearRouteMapHover(state);
        frontend_input.setHoverTarget(state, null);
        return;
    };
    const mode = state.frontend_route_mode orelse {
        clearRouteMapHover(state);
        frontend_input.setHoverTarget(state, null);
        return;
    };

    const back_rect = frontend_route_map.backTextRect(&state.ui_font, state.route_map_screen_mode);
    if (frontend_widget.hitRect(back_rect, state.route_map_button_states[frontend_route_map.back_button_index]).contains(local_mouse)) {
        clearRouteMapHover(state);
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForRouteMenuAction(.back));
        if (frontend_flow.routeMenuActionIndexForAction(state, .back)) |index| {
            state.route_menu_action_index = index;
        }
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .route_map_menu = .back });
        }
        return;
    }

    const maybe_names = if (state.galaxy_names) |*names| names else null;
    const hovered_route_index = if (frontend_bridge.routeMapAllowsRouteSwitching(state.route_map_screen_mode))
        frontend_route_map.hoveredRouteIndex(maybe_names, local_mouse, state.availableFrontendRouteLimit(mode))
    else
        null;
    state.route_map_hover_state = if (hovered_route_index != null) .route else .none;
    state.route_map_hovered_index = hovered_route_index;

    if (route_map_state.currentOpenIndex(state)) |route_index| {
        const route_galaxy_name = state.currentFrontendGalaxyName() orelse frontend.frontendRouteModeLabel(mode);
        const route_level_name = if (state.frontend_route_level) |loaded_level| loaded_level.name else "Route";
        const route_body = frontend_route_map.bodyText(if (state.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
        if (frontend_route_map.pointForRouteIndex(maybe_names, route_index)) |route_point| {
            const card_layout = frontend_route_map.cardLayout(
                &state.ui_font,
                route_point,
                route_galaxy_name,
                route_level_name,
                route_body,
                frontend.routeMenuActionLabel(mode, .play),
                if (state.routeMapShowsReplay()) frontend.routeMenuActionLabel(mode, .watch_best_trial) else null,
            );

            if (frontend_widget.hitRect(card_layout.primary_text_rect, state.route_map_button_states[frontend_route_map.primary_button_index]).contains(local_mouse)) {
                state.route_map_hover_state = .card;
                state.route_map_hovered_index = null;
                frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForRouteMenuAction(.play));
                if (frontend_flow.routeMenuActionIndexForAction(state, .play)) |index| {
                    state.route_menu_action_index = index;
                }
                if (rl.isMouseButtonPressed(.left)) {
                    frontend_input.queueActivation(state, .{ .route_map_menu = .play });
                }
                return;
            }

            if (card_layout.replay_text_rect) |replay_rect| {
                if (frontend_widget.hitRect(replay_rect, state.route_map_button_states[frontend_route_map.replay_button_index]).contains(local_mouse)) {
                    state.route_map_hover_state = .card;
                    state.route_map_hovered_index = null;
                    frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForRouteMenuAction(.watch_best_trial));
                    if (frontend_flow.routeMenuActionIndexForAction(state, .watch_best_trial)) |index| {
                        state.route_menu_action_index = index;
                    }
                    if (rl.isMouseButtonPressed(.left)) {
                        frontend_input.queueActivation(state, .{ .route_map_menu = .watch_best_trial });
                    }
                    return;
                }
            }

            if (card_layout.card_rect.contains(local_mouse)) {
                state.route_map_hover_state = .card;
                state.route_map_hovered_index = null;
                frontend_input.setHoverTarget(state, null);
                return;
            }
        }
    }

    if (hovered_route_index) |route_index| {
        frontend_input.setHoverTarget(state, null);
        if (rl.isMouseButtonPressed(.left) and route_map_state.currentOpenIndex(state) != route_index) {
            try route_map_state.openCard(state, route_index);
            frontend_audio.playSelectSound(frontend_audio.context(state));
        }
        return;
    }

    if (route_map_state.canCloseCard(state) and rl.isMouseButtonPressed(.left)) {
        route_map_state.closeCard(state);
        frontend_audio.playSelectSound(frontend_audio.context(state));
        frontend_input.setHoverTarget(state, null);
        return;
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn updateHelpSelection(state: anytype) void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };

    const back_rect = @import("../frontend/help.zig").backTextRect(&state.ui_font);
    if (frontend_widget.hitRect(back_rect, state.help_button_states[0]).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, .help_back);
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .help_menu = .back });
        }
        return;
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn updateHighScoresSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };

    if (state.high_score_screen_owner == .post_level_entry) {
        const cancel_rect = frontend_high_score_screen.footerTextRect(&state.ui_font, frontend_high_score_screen.post_level_actions[0].label(), frontend_high_score_screen.entry_cancel_x);
        if (frontend_widget.hitRect(cancel_rect, state.post_level_high_score_button_states[0]).contains(local_mouse)) {
            frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForPostLevelHighScores(0));
            state.post_level_high_score_action_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                frontend_input.queueActivation(state, .{ .post_level_high_scores = .cancel });
            }
            return;
        }

        const submit_rect = frontend_high_score_screen.footerTextRect(&state.ui_font, frontend_high_score_screen.post_level_actions[1].label(), frontend_high_score_screen.entry_submit_x);
        if (frontend_widget.hitRect(submit_rect, state.post_level_high_score_button_states[1]).contains(local_mouse)) {
            frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForPostLevelHighScores(1));
            state.post_level_high_score_action_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                frontend_input.queueActivation(state, .{ .post_level_high_scores = .submit });
            }
            return;
        }
    } else {
        const selected_mode = frontend_flow.activeHighScoreScreenMode(state);
        const entries = state.high_score_tables.visibleEntries(selected_mode);
        if (frontend_high_score_screen.rowsShowReplay(selected_mode, false)) {
            for (entries, 0..) |entry, entry_index| {
                if (!entry.has_replay) continue;
                const replay_rect = frontend_high_score_screen.replayTextRect(&state.ui_font, selected_mode, frontend_high_score_screen.row_start_y + @as(f32, @floatFromInt(entry_index)) * frontend_high_score_screen.row_pitch);
                if (frontend_widget.hitRect(replay_rect, state.high_score_replay_button_states[entry_index]).contains(local_mouse)) {
                    frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForHighScoreReplay(entry_index));
                    if (rl.isMouseButtonPressed(.left)) {
                        frontend_input.queueActivation(state, .{ .high_score_replay = entry_index });
                    }
                    return;
                }
            }
        }

        const back_rect = frontend_high_score_screen.footerTextRect(&state.ui_font, "Back", frontend_high_score_screen.back_x);
        if (frontend_widget.hitRect(back_rect, state.high_score_button_states[0]).contains(local_mouse)) {
            frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForHighScores(0));
            state.high_scores_action_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                frontend_input.queueActivation(state, .{ .high_scores_menu = .back });
            }
            return;
        }

        const toggle_label = frontend_high_score_screen.tableToggleLabel(frontend_flow.activeHighScoreScreenMode(state));
        const toggle_rect = frontend_high_score_screen.footerTextRect(&state.ui_font, toggle_label, frontend_high_score_screen.toggle_x);
        if (frontend_widget.hitRect(toggle_rect, state.high_score_button_states[1]).contains(local_mouse)) {
            frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForHighScores(1));
            state.high_scores_action_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                frontend_input.queueActivation(state, .{ .high_scores_menu = .switch_table });
            }
            return;
        }
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn updateCompletionSelection(state: anytype) void {
    const result = state.pending_run_result orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };
    if (!run_result.completionContinueVisible(state)) {
        frontend_input.setHoverTarget(state, null);
        return;
    }
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };
    const continue_rect = frontend_completion_screen.continueTextRect(&state.ui_font, run_result.summary(result));
    if (frontend_widget.hitRect(continue_rect, state.completion_continue_button_state).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, .completion_continue);
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .completion_screen = .continue_flow });
        }
        return;
    }
    frontend_input.setHoverTarget(state, null);
}

pub fn updateExitPromptSelection(state: anytype) !void {
    const local_mouse = currentMouse(state) orelse {
        frontend_input.setHoverTarget(state, null);
        return;
    };

    const yes_rect = frontend_exit_prompt.textRect(
        &state.ui_font,
        state.exit_prompt_mode,
        frontend_exit_prompt.choices[0].label(),
        frontend_exit_prompt.yes_x,
    );
    if (frontend_widget.hitRect(yes_rect, state.exit_prompt_button_states[0]).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForExitPrompt(0));
        state.exit_prompt_choice_index = 0;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .exit_prompt = .yes });
        }
        return;
    }

    const no_rect = frontend_exit_prompt.textRect(
        &state.ui_font,
        state.exit_prompt_mode,
        frontend_exit_prompt.choices[1].label(),
        frontend_exit_prompt.no_x,
    );
    if (frontend_widget.hitRect(no_rect, state.exit_prompt_button_states[1]).contains(local_mouse)) {
        frontend_input.setHoverTarget(state, frontend_activation.hoverTargetForExitPrompt(1));
        state.exit_prompt_choice_index = 1;
        if (rl.isMouseButtonPressed(.left)) {
            frontend_input.queueActivation(state, .{ .exit_prompt = .no });
        }
        return;
    }

    frontend_input.setHoverTarget(state, null);
}

pub fn optionsMenuLayoutState(state: anytype) frontend_options_menu.LayoutState {
    return .{
        .fullscreen_enabled = state.runtime_config.fullscreenEnabled(),
        .sound_value = state.runtime_config.soundVolume(),
        .music_value = state.runtime_config.musicVolume(),
        .sound_row_state = state.options_button_states[frontend_options_menu.sound_button_index],
        .music_row_state = state.options_button_states[frontend_options_menu.music_button_index],
    };
}

fn currentMouse(state: anytype) ?rl.Vector2 {
    return state.currentUiMouseLocal();
}

fn clearRouteMapHover(state: anytype) void {
    state.route_map_hover_state = .none;
    state.route_map_hovered_index = null;
}

fn challengeSetupLayoutState(
    state: anytype,
    difficulty_buffer: []u8,
    speed_buffer: []u8,
) frontend_challenge_setup_menu.LayoutState {
    return .{
        .replay_available = frontend_flow.challengeSetupReplayAvailable(state),
        .difficulty_value_text = frontend_options_menu.sliderValueText(@as(f32, @floatFromInt(state.runtime_config.challengeReplayDifficultyValue())) * 0.01, difficulty_buffer),
        .speed_value_text = frontend_options_menu.sliderValueText(@as(f32, @floatFromInt(state.runtime_config.challengeReplaySpeedValue())) * 0.01, speed_buffer),
        .difficulty_row_state = state.challenge_setup_button_states[frontend_challenge_setup_menu.difficulty_button_index],
        .speed_row_state = state.challenge_setup_button_states[frontend_challenge_setup_menu.speed_button_index],
    };
}

fn challengeSetupSliderLayout(state: anytype, item: frontend_challenge_setup_menu.Item) frontend_widget.SliderLayout {
    var difficulty_buffer: [16]u8 = undefined;
    var speed_buffer: [16]u8 = undefined;
    return frontend_challenge_setup_menu.sliderLayout(
        &state.ui_font,
        challengeSetupLayoutState(state, &difficulty_buffer, &speed_buffer),
        item,
    );
}

fn challengeSetupTextRect(state: anytype, item: frontend_challenge_setup_menu.Item) frontend_widget.Rect {
    var difficulty_buffer: [16]u8 = undefined;
    var speed_buffer: [16]u8 = undefined;
    return frontend_challenge_setup_menu.textRect(
        &state.ui_font,
        challengeSetupLayoutState(state, &difficulty_buffer, &speed_buffer),
        item,
    );
}
