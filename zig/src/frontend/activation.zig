const frontend = @import("../frontend.zig");
const frontend_challenge_setup_menu = @import("challenge_setup_menu.zig");
const frontend_completion_screen = @import("completion_screen.zig");
const frontend_exit_prompt = @import("exit_prompt.zig");
const frontend_help = @import("help.zig");
const frontend_high_score_screen = @import("high_score_screen.zig");
const frontend_widget = @import("widget.zig");

pub const HoverTarget = enum(u8) {
    main_menu_new_game,
    main_menu_high_scores,
    main_menu_options,
    main_menu_credits,
    main_menu_exit,
    new_game_tutorial,
    new_game_postal_mode,
    new_game_time_trial,
    new_game_challenge_mode,
    new_game_help,
    new_game_back,
    challenge_setup_difficulty,
    challenge_setup_difficulty_less,
    challenge_setup_difficulty_more,
    challenge_setup_speed,
    challenge_setup_speed_less,
    challenge_setup_speed_more,
    challenge_setup_play,
    challenge_setup_watch_replay,
    challenge_setup_back,
    options_fullscreen,
    options_sound_volume,
    options_sound_less,
    options_sound_more,
    options_music_volume,
    options_music_less,
    options_music_more,
    options_back,
    pause_menu_end_game,
    pause_menu_options,
    pause_menu_resume,
    route_map_play,
    route_map_watch_best_trial,
    route_map_back,
    help_back,
    high_scores_back,
    high_scores_switch_table,
    high_scores_replay_0,
    high_scores_replay_1,
    high_scores_replay_2,
    high_scores_replay_3,
    high_scores_replay_4,
    high_scores_replay_5,
    high_scores_replay_6,
    high_scores_replay_7,
    high_scores_replay_8,
    high_scores_replay_9,
    post_level_high_scores_cancel,
    post_level_high_scores_submit,
    completion_continue,
    exit_prompt_yes,
    exit_prompt_no,
};

pub const QueuedAction = union(enum) {
    main_menu: frontend.MainMenuItem,
    new_game_menu: frontend.NewGameMenuItem,
    challenge_setup_menu: frontend_challenge_setup_menu.Item,
    options_menu: frontend.OptionsMenuItem,
    pause_menu: frontend.PauseMenuItem,
    route_map_menu: frontend.RouteMenuAction,
    help_menu: frontend_help.Action,
    high_scores_menu: frontend_high_score_screen.MenuAction,
    high_score_replay: usize,
    post_level_high_scores: frontend_high_score_screen.PostLevelAction,
    completion_screen: frontend_completion_screen.Action,
    exit_prompt: frontend_exit_prompt.Choice,
};

pub const QueuedActivation = struct {
    action: QueuedAction,
    target: HoverTarget,
    requires_fade: bool,
    progress: f32 = 0.0,
};

pub fn hoverTargetForMainMenu(index: usize) HoverTarget {
    return switch (index) {
        0 => .main_menu_new_game,
        1 => .main_menu_high_scores,
        2 => .main_menu_options,
        3 => .main_menu_credits,
        4 => .main_menu_exit,
        else => unreachable,
    };
}

pub fn hoverTargetForNewGame(index: usize) HoverTarget {
    return switch (index) {
        0 => .new_game_tutorial,
        1 => .new_game_postal_mode,
        2 => .new_game_time_trial,
        3 => .new_game_challenge_mode,
        4 => .new_game_help,
        5 => .new_game_back,
        else => unreachable,
    };
}

pub fn hoverTargetForChallengeSetupItem(item: frontend_challenge_setup_menu.Item) HoverTarget {
    return switch (item) {
        .difficulty => .challenge_setup_difficulty,
        .speed => .challenge_setup_speed,
        .play => .challenge_setup_play,
        .watch_replay => .challenge_setup_watch_replay,
        .back => .challenge_setup_back,
    };
}

pub fn hoverTargetForChallengeSetupSliderArrow(
    item: frontend_challenge_setup_menu.Item,
    direction: frontend_widget.SliderDirection,
) HoverTarget {
    return switch (item) {
        .difficulty => switch (direction) {
            .less => .challenge_setup_difficulty_less,
            .more => .challenge_setup_difficulty_more,
        },
        .speed => switch (direction) {
            .less => .challenge_setup_speed_less,
            .more => .challenge_setup_speed_more,
        },
        .play, .watch_replay, .back => unreachable,
    };
}

pub fn sliderHoverTargetBelongsToChallengeSetupRow(target: HoverTarget, item: frontend_challenge_setup_menu.Item) bool {
    return switch (item) {
        .difficulty => switch (target) {
            .challenge_setup_difficulty,
            .challenge_setup_difficulty_less,
            .challenge_setup_difficulty_more,
            => true,
            else => false,
        },
        .speed => switch (target) {
            .challenge_setup_speed,
            .challenge_setup_speed_less,
            .challenge_setup_speed_more,
            => true,
            else => false,
        },
        .play, .watch_replay, .back => false,
    };
}

pub fn hoverTargetForOptions(index: usize) HoverTarget {
    return switch (index) {
        0 => .options_fullscreen,
        1 => .options_sound_volume,
        2 => .options_music_volume,
        3 => .options_back,
        else => unreachable,
    };
}

pub fn hoverTargetForOptionsSliderArrow(item: frontend.OptionsMenuItem, direction: frontend_widget.SliderDirection) HoverTarget {
    return switch (item) {
        .sound_volume => switch (direction) {
            .less => .options_sound_less,
            .more => .options_sound_more,
        },
        .music_volume => switch (direction) {
            .less => .options_music_less,
            .more => .options_music_more,
        },
        else => unreachable,
    };
}

pub fn sliderHoverTargetBelongsToOptionsRow(target: HoverTarget, item: frontend.OptionsMenuItem) bool {
    return switch (item) {
        .sound_volume => switch (target) {
            .options_sound_volume, .options_sound_less, .options_sound_more => true,
            else => false,
        },
        .music_volume => switch (target) {
            .options_music_volume, .options_music_less, .options_music_more => true,
            else => false,
        },
        else => false,
    };
}

pub fn hoverTargetForPauseMenu(index: usize) HoverTarget {
    return switch (index) {
        0 => .pause_menu_end_game,
        1 => .pause_menu_options,
        2 => .pause_menu_resume,
        else => unreachable,
    };
}

pub fn hoverTargetForRouteMenuAction(action: frontend.RouteMenuAction) HoverTarget {
    return switch (action) {
        .play => .route_map_play,
        .watch_best_trial => .route_map_watch_best_trial,
        .back => .route_map_back,
    };
}

pub fn newGameMenuItemForFrontendMode(mode: frontend.FrontendLevelMode) frontend.NewGameMenuItem {
    return switch (mode) {
        .tutorial => .tutorial,
        .postal => .postal_mode,
        .time_trial => .time_trial,
        .challenge => .challenge_mode,
    };
}

pub fn newGameMenuIndexForItem(target: frontend.NewGameMenuItem) usize {
    for (frontend.new_game_menu_items, 0..) |item, index| {
        if (item == target) return index;
    }
    return 0;
}

pub fn hoverTargetForHighScores(index: usize) HoverTarget {
    return switch (index) {
        0 => .high_scores_back,
        1 => .high_scores_switch_table,
        else => unreachable,
    };
}

pub fn hoverTargetForHighScoreReplay(index: usize) HoverTarget {
    return switch (index) {
        0 => .high_scores_replay_0,
        1 => .high_scores_replay_1,
        2 => .high_scores_replay_2,
        3 => .high_scores_replay_3,
        4 => .high_scores_replay_4,
        5 => .high_scores_replay_5,
        6 => .high_scores_replay_6,
        7 => .high_scores_replay_7,
        8 => .high_scores_replay_8,
        9 => .high_scores_replay_9,
        else => unreachable,
    };
}

pub fn hoverTargetForPostLevelHighScores(index: usize) HoverTarget {
    return switch (index) {
        0 => .post_level_high_scores_cancel,
        1 => .post_level_high_scores_submit,
        else => unreachable,
    };
}

pub fn hoverTargetForExitPrompt(index: usize) HoverTarget {
    return switch (index) {
        0 => .exit_prompt_yes,
        1 => .exit_prompt_no,
        else => unreachable,
    };
}

pub fn queuedActivationTarget(action: QueuedAction) HoverTarget {
    return switch (action) {
        .main_menu => |item| switch (item) {
            .new_game => .main_menu_new_game,
            .high_scores => .main_menu_high_scores,
            .options => .main_menu_options,
            .credits => .main_menu_credits,
            .exit => .main_menu_exit,
        },
        .new_game_menu => |item| switch (item) {
            .tutorial => .new_game_tutorial,
            .postal_mode => .new_game_postal_mode,
            .time_trial => .new_game_time_trial,
            .challenge_mode => .new_game_challenge_mode,
            .help => .new_game_help,
            .back => .new_game_back,
        },
        .challenge_setup_menu => |item| hoverTargetForChallengeSetupItem(item),
        .options_menu => |item| switch (item) {
            .fullscreen => .options_fullscreen,
            .back => .options_back,
            .sound_volume, .music_volume => unreachable,
        },
        .pause_menu => |item| switch (item) {
            .end_game => .pause_menu_end_game,
            .options => .pause_menu_options,
            .@"resume" => .pause_menu_resume,
        },
        .route_map_menu => |item| switch (item) {
            .play => .route_map_play,
            .watch_best_trial => .route_map_watch_best_trial,
            .back => .route_map_back,
        },
        .help_menu => .help_back,
        .high_scores_menu => |item| switch (item) {
            .back => .high_scores_back,
            .switch_table => .high_scores_switch_table,
        },
        .high_score_replay => |index| hoverTargetForHighScoreReplay(index),
        .post_level_high_scores => |item| switch (item) {
            .cancel => .post_level_high_scores_cancel,
            .submit => .post_level_high_scores_submit,
        },
        .completion_screen => .completion_continue,
        .exit_prompt => |choice| switch (choice) {
            .yes => .exit_prompt_yes,
            .no => .exit_prompt_no,
        },
    };
}

pub fn queuedActivationRequiresFade(action: QueuedAction) bool {
    return switch (action) {
        .exit_prompt => |choice| switch (choice) {
            .yes => true,
            .no => false,
        },
        else => false,
    };
}
