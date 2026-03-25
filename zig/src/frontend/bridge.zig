const std = @import("std");
const frontend = @import("../frontend.zig");
const high_score = @import("../high_score.zig");

pub const ResultReturnTarget = enum {
    main_menu,
    new_game_menu,
    challenge_setup_menu,
    postal_route_map,
    time_trial_route_map,
    high_scores_menu,
    replay_current_level,
    thanks_screen,
};

pub const OuterBridgeOpcode = enum(u8) {
    destroy_return = 26,
    rebuild_return = 27,
    rebuild_clear_replay_return = 28,
    init_thanks_screen = 29,
    update_thanks_screen = 30,
};

pub const RouteMapScreenMode = enum(u8) {
    normal = 0,
    post_completion_exit = 1,
    replay = 2,
};

pub const SelectedLevelRecordSource = union(enum) {
    postal: usize,
    challenge: usize,
    challenge_setup: usize,
    completion: usize,
};

pub const SavedReplayReturnOwner = enum(u32) {
    new_game_menu = 2,
    high_scores_menu = 18,
};

pub const SelectedLevelRecordLaunch = struct {
    source: SelectedLevelRecordSource,
    persistent: bool,
    return_target: ResultReturnTarget,

    pub fn defaultForSource(source: SelectedLevelRecordSource) SelectedLevelRecordLaunch {
        return .{
            .source = source,
            .persistent = defaultSelectedLevelRecordLaunchPersistent(source),
            .return_target = defaultSelectedLevelRecordLaunchReturnTarget(source),
        };
    }
};

pub const SelectedLevelRecordOverride = struct {
    mode: frontend.FrontendLevelMode,
    level_index: usize,
    runtime_build_flags: u32,
    replay_speed_scalar: f32,
    challenge_speed_value: u32,
    challenge_difficulty_value: u32,
    challenge_difficulty_scalar: f32,
    runtime_build_seed: u32,
    garbage_scalar: f32,
    salt_scalar: f32,

    pub fn fromHighScoreEntry(entry: *const high_score.Entry) ?SelectedLevelRecordOverride {
        const raw_mode = std.math.cast(i32, entry.replay_mode_id) orelse return null;
        const mode = std.meta.intToEnum(frontend.FrontendLevelMode, raw_mode) catch return null;
        return .{
            .mode = mode,
            .level_index = @intCast(entry.replay_level_index),
            .runtime_build_flags = entry.runtime_build_flags,
            .replay_speed_scalar = entry.replay_speed_scalar,
            .challenge_speed_value = entry.challenge_speed_value,
            .challenge_difficulty_value = entry.challenge_difficulty_value,
            .challenge_difficulty_scalar = entry.challenge_difficulty_scalar,
            .runtime_build_seed = entry.runtime_build_seed,
            .garbage_scalar = entry.garbage_scalar,
            .salt_scalar = entry.salt_scalar,
        };
    }
};

pub const RouteMapTarget = struct {
    mode: frontend.FrontendLevelMode,
    screen_mode: RouteMapScreenMode,
    start_route_override: ?usize = null,
};

pub const ReplayLevelTarget = struct {
    mode: frontend.FrontendLevelMode,
    level_index: usize,
    selected_level_record_override: ?SelectedLevelRecordOverride = null,
    selected_level_record_launch: ?SelectedLevelRecordLaunch = null,
};

pub const OuterOwner = enum {
    main_menu,
    challenge_setup_menu,
    new_game_menu,
    route_map,
    high_scores_menu,
    replay_current_level,
    thanks_screen,
    resume_active_run,
};

pub const OuterOwnerState = struct {
    owner: OuterOwner = .main_menu,
    new_game_menu_item: frontend.NewGameMenuItem = .tutorial,
    route_map: RouteMapTarget = .{
        .mode = .postal,
        .screen_mode = .normal,
    },
    high_score_mode: high_score.Mode = .postal,
    replay: ReplayLevelTarget = .{
        .mode = .postal,
        .level_index = 0,
    },
};

// PORT(verified): `initialize_galaxy` uses internal mode `2` for the Time Trial / replay
// Star Map path, while normal Postal entry starts in mode `0`.
pub fn defaultRouteMapScreenMode(mode: frontend.FrontendLevelMode) RouteMapScreenMode {
    return switch (mode) {
        .postal => .normal,
        .time_trial => .replay,
        .challenge, .tutorial => unreachable,
    };
}

pub fn newGameMenuItemForBridgeMode(mode: ?frontend.FrontendLevelMode) frontend.NewGameMenuItem {
    return switch (mode orelse .postal) {
        .tutorial => .tutorial,
        .postal => .postal_mode,
        .time_trial => .time_trial,
        .challenge => .challenge_mode,
    };
}

pub fn defaultSelectedLevelRecordLaunchPersistent(source: SelectedLevelRecordSource) bool {
    // PORT(verified): `update_frontend_state_machine` initializes subgame at
    // `data_4df904 + 0x74618`, so the app replay-launch scratch that
    // `update_high_score_screen` / `update_new_game_menu` seed at
    // `+0x1066be8/+0x1066be9/+0x1066bec` aliases
    // `game + 0xff25d0/+0xff25d1/+0xff25d4` exactly. Route-map best-trial launchers
    // still seed only the transient game-side active lane.
    return switch (source) {
        .postal, .challenge => true,
        .challenge_setup, .completion => false,
    };
}

pub fn defaultSelectedLevelRecordLaunchReturnTarget(source: SelectedLevelRecordSource) ResultReturnTarget {
    return switch (source) {
        .completion => .time_trial_route_map,
        .postal, .challenge => .high_scores_menu,
        .challenge_setup => .challenge_setup_menu,
    };
}

pub fn savedReplayReturnOwnerForLaunch(launch: SelectedLevelRecordLaunch) ?SavedReplayReturnOwner {
    if (!launch.persistent) return null;
    return switch (launch.return_target) {
        .new_game_menu => .new_game_menu,
        .high_scores_menu => .high_scores_menu,
        else => null,
    };
}

pub fn resultReturnTargetForSavedReplayReturnOwner(state: SavedReplayReturnOwner) ResultReturnTarget {
    return switch (state) {
        .new_game_menu => .new_game_menu,
        .high_scores_menu => .high_scores_menu,
    };
}

pub fn outerOwnerStateMainMenu() OuterOwnerState {
    return .{ .owner = .main_menu };
}

pub fn outerOwnerStateChallengeSetupMenu() OuterOwnerState {
    return .{ .owner = .challenge_setup_menu };
}

pub fn outerOwnerStateThanksScreen() OuterOwnerState {
    return .{ .owner = .thanks_screen };
}

pub fn outerOwnerStateResumeActiveRun() OuterOwnerState {
    return .{ .owner = .resume_active_run };
}

pub fn outerOwnerStateNewGameMenu(item: frontend.NewGameMenuItem) OuterOwnerState {
    return .{
        .owner = .new_game_menu,
        .new_game_menu_item = item,
    };
}

pub fn outerOwnerStateRouteMap(target: RouteMapTarget) OuterOwnerState {
    return .{
        .owner = .route_map,
        .route_map = target,
    };
}

pub fn outerOwnerStateHighScores(mode: high_score.Mode) OuterOwnerState {
    return .{
        .owner = .high_scores_menu,
        .high_score_mode = mode,
    };
}

pub fn outerOwnerStateReplay(target: ReplayLevelTarget) OuterOwnerState {
    return .{
        .owner = .replay_current_level,
        .replay = target,
    };
}

pub fn outerOwnerStateForSelectedReplayLaunch(
    mode: frontend.FrontendLevelMode,
    source: SelectedLevelRecordSource,
    return_target: ResultReturnTarget,
    active_level_index: usize,
) OuterOwnerState {
    return switch (return_target) {
        .main_menu => outerOwnerStateMainMenu(),
        .new_game_menu => outerOwnerStateNewGameMenu(newGameMenuItemForBridgeMode(mode)),
        .challenge_setup_menu => outerOwnerStateChallengeSetupMenu(),
        .postal_route_map => outerOwnerStateRouteMap(.{
            .mode = .postal,
            .screen_mode = .post_completion_exit,
        }),
        .time_trial_route_map => outerOwnerStateRouteMap(.{
            .mode = .time_trial,
            .screen_mode = defaultRouteMapScreenMode(.time_trial),
            .start_route_override = active_level_index,
        }),
        .high_scores_menu => outerOwnerStateHighScores(switch (source) {
            .challenge => .challenge,
            else => .postal,
        }),
        .replay_current_level => outerOwnerStateReplay(.{
            .mode = mode,
            .level_index = active_level_index,
        }),
        .thanks_screen => outerOwnerStateThanksScreen(),
    };
}

pub fn savedOuterOwnerForLevelLaunch(
    mode: frontend.FrontendLevelMode,
    level_index: usize,
    selected_level_record_launch: ?SelectedLevelRecordLaunch,
) OuterOwnerState {
    if (selected_level_record_launch) |launch| {
        return outerOwnerStateForSelectedReplayLaunch(mode, launch.source, launch.return_target, level_index);
    }

    return switch (mode) {
        .postal => outerOwnerStateRouteMap(.{
            .mode = .postal,
            .screen_mode = defaultRouteMapScreenMode(.postal),
        }),
        .time_trial => outerOwnerStateRouteMap(.{
            .mode = .time_trial,
            .screen_mode = defaultRouteMapScreenMode(.time_trial),
        }),
        .challenge => outerOwnerStateChallengeSetupMenu(),
        .tutorial => outerOwnerStateNewGameMenu(.tutorial),
    };
}

pub fn highScoreBrowseBackOwner(mode: high_score.Mode) OuterOwnerState {
    return switch (mode) {
        .postal => outerOwnerStateNewGameMenu(.postal_mode),
        .challenge => outerOwnerStateChallengeSetupMenu(),
    };
}

pub fn routeMapBackLabelForScreenMode(screen_mode: RouteMapScreenMode) []const u8 {
    return switch (screen_mode) {
        .post_completion_exit => "Exit",
        .normal, .replay => "Back",
    };
}

pub fn routeMapAllowsRouteSwitching(screen_mode: RouteMapScreenMode) bool {
    // PORT(verified): `update_galaxy` skips the open/switch/close route branch entirely
    // for internal mode `1`, keeping the postal-return Star Map locked on its current
    // route card while still allowing Play/Exit.
    return screen_mode != .post_completion_exit;
}
