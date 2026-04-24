const std = @import("std");

const app = @import("../app.zig");
const frontend_audio = @import("frontend_audio.zig");
const frontend = @import("../frontend.zig");
const frontend_activation = @import("../frontend/activation.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const frontend_challenge_setup_menu = @import("../frontend/challenge_setup_menu.zig");
const frontend_completion_screen = @import("../frontend/completion_screen.zig");
const frontend_exit_prompt = @import("../frontend/exit_prompt.zig");
const frontend_help = @import("../frontend/help.zig");
const frontend_high_score_screen = @import("../frontend/high_score_screen.zig");
const frontend_route_map = @import("../frontend/route_map.zig");
const high_score = @import("../high_score.zig");
const level_loader = @import("level_loader.zig");
const selected_replay = @import("selected_replay.zig");

const default_level_path = app.default_level_path;
const GamePhase = frontend.GamePhase;
const FrontendLevelMode = frontend.FrontendLevelMode;
const MainMenuItem = frontend.MainMenuItem;
const NewGameMenuItem = frontend.NewGameMenuItem;
const OptionsMenuItem = frontend.OptionsMenuItem;
const PauseMenuItem = frontend.PauseMenuItem;
const RouteMenuAction = frontend.RouteMenuAction;

pub fn enterGamePhase(state: anytype, phase: GamePhase) !void {
    state.game_phase = phase;
    state.game_phase_ticks = 0;
    state.hovered_frontend_target = null;
    state.keyboard_frontend_focus_visible = false;
    state.pending_frontend_activation = null;
    if (phase == .new_game_menu) {
        normalizeNewGameMenuSelection(state);
    }
    switch (phase) {
        .main_menu => state.current_outer_owner = frontend_bridge.outerOwnerStateMainMenu(),
        .new_game_menu => state.current_outer_owner = frontend_bridge.outerOwnerStateNewGameMenu(frontend.new_game_menu_items[state.new_game_menu_index]),
        .thanks_screen => state.current_outer_owner = frontend_bridge.outerOwnerStateThanksScreen(),
        else => {},
    }
    try state.syncGamePhaseResources();
    state.snapFrontendWidgetStates();
}

pub fn enterStartPhase(state: anytype, phase: GamePhase) !void {
    try state.high_score_tables.loadFromRuntimeRoot(state.allocator, state.runtime_root_path);

    switch (phase) {
        .boot => try enterGamePhase(state, .boot),
        .intro,
        .main_menu,
        .new_game_menu,
        .challenge_setup_menu,
        .help,
        .credits,
        .thanks_screen,
        => try enterGamePhase(state, phase),
        .high_scores_menu => try enterHighScoreBrowseScreen(state, .postal),
        .options_menu => {
            if (state.start_pause_context) {
                try level_loader.loadGameLevel(state, default_level_path);
                state.options_return_phase = .pause_menu;
            } else {
                state.options_return_phase = .main_menu;
            }
            try enterGamePhase(state, .options_menu);
        },
        .pause_menu => {
            try enterGameplayShell(state, default_level_path);
            try enterPauseMenu(state);
        },
        .exit_prompt => {
            if (state.start_pause_context) {
                try level_loader.loadGameLevel(state, default_level_path);
                try beginEndGamePrompt(state, .pause_menu);
            } else {
                try beginExitPrompt(state, .main_menu);
            }
        },
        .route_map_menu => try enterRouteMapMenu(state, .postal),
        .level => try enterGameplayShell(state, default_level_path),
        .completion_screen => {
            try level_loader.loadGameLevel(state, default_level_path);
            state.active_frontend_mode = .postal;
            state.active_frontend_level_index = 1;
            state.pending_run_result = .{
                .outcome = .completed,
                .level_name = "Snail Mail 101",
                .mode = .postal,
                .elapsed_millis = 62_340,
                .parcel_count = 1,
                .parcel_target = 1,
                .score = 50_210,
                .score_is_partial = true,
                .score_totals = .{
                    .parcel_pickup = 100,
                    .parcel_register = 10,
                    .completion_bonus = 50_000,
                    .total = 50_210,
                },
                .visible_life_stock = 3,
                .completion_owner = .postal_route_map,
                .outer_return_target = .postal_route_map,
            };
            try enterGamePhase(state, .completion_screen);
        },
    }
}

pub fn performMainMenuItem(state: anytype, item: MainMenuItem) !void {
    switch (item) {
        .new_game => try enterGamePhase(state, .new_game_menu),
        .high_scores => {
            state.high_scores_action_index = 1;
            try enterHighScoreBrowseScreen(state, .postal);
        },
        .options => {
            state.options_return_phase = .main_menu;
            try enterGamePhase(state, .options_menu);
        },
        .credits => try enterGamePhase(state, .credits),
        .exit => try beginExitPrompt(state, .main_menu),
    }
}

pub fn activateMainMenuItem(state: anytype, item: MainMenuItem) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performMainMenuItem(state, item);
}

pub fn activeHighScoreScreenMode(state: anytype) high_score.Mode {
    return state.high_score_screen_owner.activeMode();
}

pub fn setHighScoreBrowseOwner(state: anytype, mode: high_score.Mode) void {
    state.high_scores_menu_index = frontend_high_score_screen.modeIndex(mode);
    state.high_score_screen_owner = .{ .main_menu_browse = mode };
    state.clearPostLevelHighScoreEntry();
    state.current_outer_owner = frontend_bridge.outerOwnerStateHighScores(mode);
}

pub fn enterHighScoreBrowseScreen(state: anytype, mode: high_score.Mode) !void {
    setHighScoreBrowseOwner(state, mode);
    try enterGamePhase(state, .high_scores_menu);
}

pub fn enterPostLevelHighScoreScreen(state: anytype, context: frontend_high_score_screen.PendingEntry) !void {
    try enterPostLevelHighScoreScreenWithReturn(state, context, null, null);
}

pub fn enterPostLevelHighScoreScreenWithReturn(
    state: anytype,
    context: frontend_high_score_screen.PendingEntry,
    return_owner: ?frontend_bridge.OuterOwnerState,
    return_opcode: ?frontend_bridge.OuterBridgeOpcode,
) !void {
    state.high_score_screen_owner = .{ .post_level_entry = context };
    state.high_scores_menu_index = frontend_high_score_screen.modeIndex(context.mode);
    state.preparePostLevelHighScoreEntry(context);
    state.post_level_high_score_return_owner = return_owner;
    state.post_level_high_score_return_opcode = return_opcode orelse .destroy_return;
    state.current_outer_owner = frontend_bridge.outerOwnerStateHighScores(context.mode);
    try enterGamePhase(state, .high_scores_menu);
}

pub fn performNewGameMenuItem(state: anytype, item: NewGameMenuItem) !void {
    switch (item) {
        .tutorial => {
            state.runtime_config.setNewGameExtraModesVisible(true);
            try enterFrontendLevelMode(state, .tutorial);
        },
        .postal_mode => try enterFrontendLevelMode(state, .postal),
        .time_trial => try enterFrontendLevelMode(state, .time_trial),
        .challenge_mode => try enterChallengeSetupMenu(state),
        .help => try enterGamePhase(state, .help),
        .back => try enterGamePhase(state, .main_menu),
    }
}

pub fn activateNewGameMenuItem(state: anytype, item: NewGameMenuItem) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performNewGameMenuItem(state, item);
}

pub fn newGameMenuItemVisible(state: anytype, item: NewGameMenuItem) bool {
    return switch (item) {
        .postal_mode, .time_trial, .challenge_mode => state.runtime_config.newGameExtraModesVisible(),
        .tutorial, .help, .back => true,
    };
}

pub fn newGameMenuIndexVisible(state: anytype, index: usize) bool {
    if (index >= frontend.new_game_menu_items.len) return false;
    return newGameMenuItemVisible(state, frontend.new_game_menu_items[index]);
}

pub fn normalizeNewGameMenuSelection(state: anytype) void {
    if (newGameMenuIndexVisible(state, state.new_game_menu_index)) return;
    state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.tutorial);
}

pub fn stepNewGameMenuSelection(state: anytype, delta: isize) void {
    var remaining = frontend.new_game_menu_items.len;
    while (remaining > 0) : (remaining -= 1) {
        state.new_game_menu_index = wrappedIndex(frontend.new_game_menu_items.len, state.new_game_menu_index, delta);
        if (newGameMenuIndexVisible(state, state.new_game_menu_index)) return;
    }
    state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.tutorial);
}

pub fn challengeSetupReplayAvailable(state: anytype) bool {
    return state.high_score_tables.challenge[0].has_replay;
}

pub fn challengeSetupVisibleItems(state: anytype) []const frontend_challenge_setup_menu.Item {
    return if (challengeSetupReplayAvailable(state))
        frontend_challenge_setup_menu.items[0..]
    else
        frontend_challenge_setup_menu.items_without_replay[0..];
}

pub fn currentChallengeSetupSelectedItem(state: anytype) frontend_challenge_setup_menu.Item {
    const items = challengeSetupVisibleItems(state);
    return items[@min(state.challenge_setup_index, items.len - 1)];
}

pub fn normalizeChallengeSetupSelection(state: anytype) void {
    const items = challengeSetupVisibleItems(state);
    if (state.challenge_setup_index < items.len) return;
    state.challenge_setup_index = items.len - 1;
}

pub fn enterChallengeSetupMenu(state: anytype) !void {
    try state.setSelectedLevelRecordContext(null, null);
    state.challenge_setup_index = 0;
    state.current_outer_owner = frontend_bridge.outerOwnerStateChallengeSetupMenu();
    try enterGamePhase(state, .challenge_setup_menu);
}

pub fn performChallengeSetupMenuItem(state: anytype, item: frontend_challenge_setup_menu.Item) !void {
    switch (item) {
        .difficulty, .speed => {},
        .play => try enterFrontendLevelPath(state, .challenge, 0),
        .watch_replay => {
            if (!challengeSetupReplayAvailable(state)) return;
            try enterSelectedLevelRecordSource(state, frontend_bridge.SelectedLevelRecordLaunch.defaultForSource(.{ .challenge_setup = 0 }));
        },
        .back => try returnToNewGameMenu(state, .challenge_setup_menu),
    }
}

pub fn performOptionsMenuItem(state: anytype, item: OptionsMenuItem) !void {
    switch (item) {
        .fullscreen => state.toggleFullscreenPreference(),
        .sound_volume, .music_volume => {},
        .back => try leaveOptionsMenu(state),
    }
}

pub fn performPauseMenuItem(state: anytype, item: PauseMenuItem) !void {
    switch (item) {
        .end_game => try beginEndGamePrompt(state, .pause_menu),
        .options => {
            state.options_return_phase = .pause_menu;
            try enterGamePhase(state, .options_menu);
        },
        .@"resume" => try resumeFromPauseMenu(state),
    }
}

pub fn performHelpMenuItem(state: anytype, item: frontend_help.Action) !void {
    switch (item) {
        .back => try returnToNewGameMenu(state, .help),
    }
}

pub fn activateOptionsMenuItem(state: anytype, item: OptionsMenuItem) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performOptionsMenuItem(state, item);
}

pub fn beginExitPrompt(state: anytype, return_phase: GamePhase) !void {
    state.exit_prompt_choice_index = 1;
    state.exit_prompt_return_phase = return_phase;
    state.exit_prompt_mode = .quit_app;
    try enterGamePhase(state, .exit_prompt);
}

pub fn beginEndGamePrompt(state: anytype, return_phase: GamePhase) !void {
    state.exit_prompt_choice_index = 1;
    state.exit_prompt_return_phase = return_phase;
    state.exit_prompt_mode = .abandon_run;
    try enterGamePhase(state, .exit_prompt);
}

pub fn beginRouteMapExitPrompt(state: anytype) !void {
    state.exit_prompt_choice_index = 1;
    state.exit_prompt_return_phase = .route_map_menu;
    state.exit_prompt_mode = .leave_route_map;
    try enterGamePhase(state, .exit_prompt);
}

pub fn performExitPromptChoice(state: anytype, choice: frontend_exit_prompt.Choice) !void {
    switch (choice) {
        .no => try enterGamePhase(state, state.exit_prompt_return_phase),
        .yes => switch (state.exit_prompt_mode) {
            .quit_app => state.should_exit = true,
            .abandon_run => try state.abandonActiveRun(),
            .leave_route_map => try returnToNewGameMenu(state, .route_map_menu),
        },
    }
}

pub fn activateExitPromptChoice(state: anytype, choice: frontend_exit_prompt.Choice) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performExitPromptChoice(state, choice);
}

pub fn performRouteMenuAction(state: anytype, action: RouteMenuAction) !void {
    switch (action) {
        .play => try enterSelectedFrontendRoute(state),
        .watch_best_trial => {
            const route_index = state.currentRouteMapOpenIndex() orelse return;
            const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return;
            try enterSelectedLevelRecordSource(state, frontend_bridge.SelectedLevelRecordLaunch.defaultForSource(.{ .completion = completion_index }));
        },
        .back => if (state.route_map_screen_mode == .post_completion_exit)
            try beginRouteMapExitPrompt(state)
        else
            try returnToNewGameMenu(state, .route_map_menu),
    }
}

pub fn performCompletionAction(state: anytype, action: frontend_completion_screen.Action) !void {
    switch (action) {
        .continue_flow => try state.continueCompletionScreen(),
    }
}

pub fn performPostLevelHighScoreAction(state: anytype, action: frontend_high_score_screen.PostLevelAction) !void {
    switch (action) {
        .cancel => try state.cancelPostLevelHighScoreEntry(),
        .submit => try state.submitPostLevelHighScore(),
    }
}

pub fn activatePostLevelHighScoreAction(state: anytype, action: frontend_high_score_screen.PostLevelAction) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performPostLevelHighScoreAction(state, action);
}

pub fn performHighScoreMenuAction(state: anytype, action: frontend_high_score_screen.MenuAction) !void {
    switch (action) {
        .back => switch (state.high_score_screen_owner) {
            .main_menu_browse => |mode| {
                const owner = frontend_bridge.highScoreBrowseBackOwner(mode);
                // PORT(verified): `exit_high_score_screen` restores owner `2` for postal
                // browse and owner `10` for challenge browse. In the port, those map to
                // the New Game controller with the Postal item selected and the literal
                // challenge-setup controller respectively.
                switch (owner.owner) {
                    .new_game_menu => {
                        state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(owner.new_game_menu_item);
                        try enterGamePhase(state, .new_game_menu);
                    },
                    .challenge_setup_menu => try enterChallengeSetupMenu(state),
                    else => unreachable,
                }
            },
            .post_level_entry => try state.cancelPostLevelHighScoreEntry(),
        },
        .switch_table => switch (state.high_score_screen_owner) {
            .main_menu_browse, .post_level_entry => if (frontend_high_score_screen.nextBrowseMode(state.high_score_screen_owner)) |next_mode| {
                setHighScoreBrowseOwner(state, next_mode);
            },
        },
    }
}

pub fn performHighScoreReplay(state: anytype, entry_index: usize) !void {
    const source = frontend_high_score_screen.replaySource(state.high_score_screen_owner, entry_index) orelse return;
    if (!state.highScoreReplayAvailable(entry_index)) return;
    try enterSelectedLevelRecordSource(state, frontend_bridge.SelectedLevelRecordLaunch.defaultForSource(source));
}

pub fn activateHighScoreMenuAction(state: anytype, action: frontend_high_score_screen.MenuAction) !void {
    frontend_audio.playSelectSound(frontend_audio.context(state));
    try performHighScoreMenuAction(state, action);
}

pub fn enterPauseMenu(state: anytype) !void {
    state.pause_menu_index = 0;
    try enterGamePhase(state, .pause_menu);
}

pub fn resumeFromPauseMenu(state: anytype) !void {
    try enterGamePhase(state, .level);
}

pub fn enterGameplayShell(state: anytype, level_path: []const u8) !void {
    state.active_frontend_mode = null;
    state.active_frontend_level_index = 0;
    state.current_outer_owner = frontend_bridge.outerOwnerStateMainMenu();
    state.saved_outer_owner = frontend_bridge.outerOwnerStateMainMenu();
    try state.setSelectedLevelRecordContext(null, null);
    try level_loader.loadGameLevel(state, level_path);
    try enterGamePhase(state, .level);
}

pub fn enterFrontendLevelPath(state: anytype, mode: FrontendLevelMode, level_index: usize) !void {
    try beginFrontendLevelPath(state, mode, level_index, null, null);
}

pub fn enterSelectedLevelRecordPath(state: anytype, record: frontend_bridge.SelectedLevelRecordOverride) !void {
    const selected_level_record_launch = if (state.selected_level_record_source) |source|
        frontend_bridge.SelectedLevelRecordLaunch{
            .source = source,
            .persistent = state.selected_level_record_persistent,
            .outer_return_target = selected_replay.launchOuterReturnTarget(state) orelse frontend_bridge.defaultSelectedLevelRecordLaunchOuterReturnTarget(source),
        }
    else
        null;
    try beginFrontendLevelPath(state, record.mode, record.level_index, record, selected_level_record_launch);
}

pub fn enterSelectedLevelRecordSource(state: anytype, launch: frontend_bridge.SelectedLevelRecordLaunch) !void {
    const entry = selected_replay.entryForSource(state, launch.source) orelse return;
    const record = frontend_bridge.SelectedLevelRecordOverride.fromHighScoreEntry(entry) orelse return;
    try beginFrontendLevelPath(state, record.mode, record.level_index, record, launch);
}

pub fn beginFrontendLevelPath(
    state: anytype,
    mode: FrontendLevelMode,
    level_index: usize,
    selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride,
    selected_level_record_launch: ?frontend_bridge.SelectedLevelRecordLaunch,
) !void {
    var path_buffer: [64]u8 = undefined;
    const level_path = try frontend.frontendLevelPath(mode, level_index, &path_buffer);
    try state.setSelectedLevelRecordContext(selected_level_record_override, selected_level_record_launch);
    state.active_frontend_mode = mode;
    state.active_frontend_level_index = level_index;
    state.saved_outer_owner = frontend_bridge.savedOuterOwnerForLevelLaunch(mode, level_index, selected_level_record_launch);
    state.current_outer_owner = state.saved_outer_owner;
    state.seed_level_intro_cutscene = true;
    try level_loader.loadGameLevel(state, level_path);
    try enterGamePhase(state, .level);
}

pub fn leaveOptionsMenu(state: anytype) !void {
    try state.saveRuntimeConfig();
    try enterGamePhase(state, state.options_return_phase);
}

pub fn returnToNewGameMenu(state: anytype, from_phase: GamePhase) !void {
    switch (from_phase) {
        .help => state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.help),
        .challenge_setup_menu => state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.challenge_mode),
        .route_map_menu => {
            if (state.frontend_route_mode) |mode| {
                state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(frontend_activation.newGameMenuItemForFrontendMode(mode));
            }
        },
        else => {},
    }
    try enterGamePhase(state, .new_game_menu);
}

pub fn enterFrontendLevelMode(state: anytype, mode: FrontendLevelMode) !void {
    switch (mode) {
        .postal, .time_trial => try enterRouteMapMenu(state, mode),
        .challenge => try enterChallengeSetupMenu(state),
        .tutorial => try enterFrontendLevelPath(state, mode, 0),
    }
}

pub fn enterRouteMapMenu(state: anytype, mode: FrontendLevelMode) !void {
    try enterRouteMapMenuWithScreenMode(state, mode, frontend_bridge.defaultRouteMapScreenMode(mode));
}

pub fn enterRouteMapMenuWithScreenMode(state: anytype, mode: FrontendLevelMode, screen_mode: frontend_bridge.RouteMapScreenMode) !void {
    try state.setSelectedLevelRecordContext(null, null);
    state.frontend_route_mode = mode;
    state.route_map_screen_mode = screen_mode;
    state.current_outer_owner = frontend_bridge.outerOwnerStateRouteMap(.{
        .mode = mode,
        .screen_mode = screen_mode,
        .start_route_override = state.start_route_index_override,
    });
    state.frontend_route_index = state.initialFrontendRouteIndex(mode);
    if (state.start_route_index_override) |override| {
        const highest_available = state.highestAvailableFrontendRouteIndex(mode);
        if (highest_available > 0) {
            state.frontend_route_index = std.math.clamp(override, @as(usize, 1), highest_available);
        }
        state.start_route_index_override = null;
    }
    try state.openFrontendRouteCard(state.frontend_route_index);
    state.resetRouteMapHighlightAnimations();
    state.syncRouteMapHighlightTargets();
    try enterGamePhase(state, .route_map_menu);
}

pub fn enterSelectedFrontendRoute(state: anytype) !void {
    const mode = state.frontend_route_mode orelse return;
    try enterFrontendLevelPath(state, mode, state.currentRouteMapOpenIndex() orelse state.frontend_route_index);
}

pub fn stepFrontendRouteSelection(state: anytype, delta: isize) !void {
    const mode = state.frontend_route_mode orelse return;
    const route_count = state.availableFrontendRouteLimit(mode);
    if (route_count == 0) return;
    const next_route_index = wrappedIndex(route_count, state.frontend_route_index - 1, delta) + 1;
    try state.openFrontendRouteCard(next_route_index);
}

pub fn activeRouteMenuActions(state: anytype) []const RouteMenuAction {
    if (!state.routeMapCardIsOpen()) return &frontend_route_map.actions_closed;
    return if (state.routeMapShowsReplay())
        &frontend_route_map.actions_with_replay
    else
        &frontend_route_map.actions_without_replay;
}

pub fn activeRouteMenuHotAction(state: anytype) RouteMenuAction {
    const actions = activeRouteMenuActions(state);
    return actions[@min(state.route_menu_action_index, actions.len - 1)];
}

pub fn routeMenuActionIndexForAction(state: anytype, action: RouteMenuAction) ?usize {
    for (activeRouteMenuActions(state), 0..) |candidate, index| {
        if (candidate == action) return index;
    }
    return null;
}

fn wrappedIndex(count: usize, current: usize, delta: isize) usize {
    if (count == 0) return 0;
    const count_signed: isize = @intCast(count);
    var next = @as(isize, @intCast(current)) + delta;
    next = @mod(next, count_signed);
    return @intCast(next);
}
