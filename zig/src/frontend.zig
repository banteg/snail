const std = @import("std");
const rl = @import("raylib");

const frontend_transition_fade_step: f32 = 0.0555555522;
const frontend_transition_hold_step: f32 = 0.33333334;

pub const BootTask = enum {
    load_high_scores,
    load_intro_background,
    load_main_menu_background,
    load_route_map_background,
    load_help_background,
    load_intro_script,
    load_credits_script,
    load_intro_music,
    load_menu_music,
};

pub const boot_tasks = [_]BootTask{
    .load_high_scores,
    .load_intro_background,
    .load_main_menu_background,
    .load_route_map_background,
    .load_help_background,
    .load_intro_script,
    .load_credits_script,
    .load_intro_music,
    .load_menu_music,
};

// PORT(scaffold): the default `snail` path is now a forward-pass boot and menu shell.
// Replace this with the real menu flow once original assets, transitions, and actions are ported.
pub const GamePhase = enum {
    boot,
    intro,
    main_menu,
    new_game_menu,
    options_menu,
    route_map_menu,
    high_scores_menu,
    cutscene,
    completion_screen,
    post_level_high_score,
    credits,
    help,
    level,
};

pub const FrontendTransitionState = enum {
    idle,
    fading_in,
    fading_out,
    holding_black,
    handoff,
};

// PORT(partial): intro and credits now reuse the recovered front-end black overlay transition:
// fade in from alpha 1.0 to 0.0 over 18 ticks, fade out over 18 ticks, then hold black for 3 ticks
// before the next screen swaps in and starts its own fade-in. Other front-end overlay users remain unresolved.
pub const FrontendTransition = struct {
    state: FrontendTransitionState = .idle,
    alpha: f32 = 0.0,
    progress: f32 = 0.0,
    pending_phase: ?GamePhase = null,

    pub fn beginFadeIn(self: *FrontendTransition) void {
        self.state = .fading_in;
        self.alpha = 1.0;
        self.progress = 0.0;
        self.pending_phase = null;
    }

    pub fn beginFadeOut(self: *FrontendTransition, next_phase: GamePhase) void {
        if (self.state != .idle) return;
        self.state = .fading_out;
        self.alpha = 0.0;
        self.progress = 0.0;
        self.pending_phase = next_phase;
    }

    pub fn update(self: *FrontendTransition) ?GamePhase {
        switch (self.state) {
            .idle => return null,
            .fading_in => {
                self.alpha = @max(self.alpha - frontend_transition_fade_step, 0.0);
                if (self.alpha <= 0.01) {
                    self.alpha = 0.0;
                    self.state = .idle;
                }
            },
            .fading_out => {
                self.alpha = @min(self.alpha + frontend_transition_fade_step, 1.0);
                if (self.alpha >= 0.99) {
                    self.alpha = 1.0;
                    self.progress = 0.0;
                    self.state = .holding_black;
                }
            },
            .holding_black => {
                self.progress = @min(self.progress + frontend_transition_hold_step, 1.0);
                if (self.progress >= 0.99) {
                    self.state = .handoff;
                    return self.pending_phase;
                }
            },
            .handoff => return self.pending_phase,
        }
        return null;
    }

    pub fn completeHandoff(self: *FrontendTransition) void {
        self.beginFadeIn();
    }

    pub fn blocksInput(self: *const FrontendTransition) bool {
        return self.state != .idle;
    }

    pub fn draw(self: *const FrontendTransition, bounds: rl.Rectangle) void {
        if (self.alpha <= 0.01) return;
        rl.drawRectangleRec(bounds, .{
            .r = 0,
            .g = 0,
            .b = 0,
            .a = @intFromFloat(std.math.clamp(self.alpha, 0.0, 1.0) * 255.0),
        });
    }
};

// PORT(partial): these top-level labels match the recovered front-end constructor at
// `initialize_main_menu`.
// Actions for `Options` and deeper score routing are still scaffolded until their handlers are ported.
pub const MainMenuItem = enum {
    new_game,
    high_scores,
    options,
    credits,
    exit,

    pub fn label(self: MainMenuItem) [:0]const u8 {
        return switch (self) {
            .new_game => "New Game",
            .high_scores => "High Scores",
            .options => "Options",
            .credits => "Credits",
            .exit => "Exit",
        };
    }
};

pub const main_menu_items = [_]MainMenuItem{ .new_game, .high_scores, .options, .credits, .exit };

// PORT(partial): these labels and mode actions match the recovered `initialize_new_game_menu`
// and `launch_frontend_level_mode` new-game flow.
// `Help` is still only a partial screen port, and later progression beyond the first level remains unresolved.
pub const NewGameMenuItem = enum {
    tutorial,
    postal_mode,
    time_trial,
    challenge_mode,
    help,
    back,

    pub fn label(self: NewGameMenuItem) [:0]const u8 {
        return switch (self) {
            .tutorial => "Tutorial",
            .postal_mode => "Postal Mode",
            .time_trial => "Time Trial",
            .challenge_mode => "Challenge Mode",
            .help => "Help",
            .back => "Back",
        };
    }
};

pub const new_game_menu_items = [_]NewGameMenuItem{
    .tutorial,
    .postal_mode,
    .time_trial,
    .challenge_mode,
    .help,
    .back,
};

// PORT(partial): these mode ids match the recovered `sub_417eb0` launcher and `sub_443650` level-name switch.
// We only port the initial level handoff here, not the original front-end's level-select or progression flow yet.
pub const FrontendLevelMode = enum(i32) {
    postal = 0,
    challenge = 1,
    time_trial = 4,
    tutorial = 7,
};

pub const HighScoresMenuItem = enum {
    postal_high_scores,
    challenge_high_scores,
    back,

    pub fn label(self: HighScoresMenuItem) [:0]const u8 {
        return switch (self) {
            .postal_high_scores => "Postal High Scores",
            .challenge_high_scores => "Challenge High Scores",
            .back => "Back",
        };
    }
};

pub const high_scores_menu_items = [_]HighScoresMenuItem{
    .postal_high_scores,
    .challenge_high_scores,
    .back,
};

// PORT(partial): the original options screen is a richer widget tree with sliders and text objects.
// This port keeps the recovered fields, labels, and save/apply behavior on a simpler list UI for now.
pub const OptionsMenuItem = enum {
    fullscreen,
    sound_volume,
    music_volume,
    back,
};

pub const options_menu_items = [_]OptionsMenuItem{
    .fullscreen,
    .sound_volume,
    .music_volume,
    .back,
};

pub const RouteMenuAction = enum {
    play,
    watch_best_trial,
    back,
};

pub const route_menu_actions = [_]RouteMenuAction{
    .play,
    .watch_best_trial,
    .back,
};

pub fn newGameMenuHint(item: NewGameMenuItem) ?[]const u8 {
    return switch (item) {
        .postal_mode => "Start the postal-mode level flow.",
        .time_trial => "Start the time-trial level flow.",
        .challenge_mode => "Start the challenge-mode level flow.",
        .help => "Open the help screen.",
        else => null,
    };
}

pub fn mainMenuItemHint(item: MainMenuItem) ?[]const u8 {
    return switch (item) {
        .new_game => "Open the recovered New Game flow.",
        .high_scores => "Open postal and challenge score tables.",
        .options => "Adjust the recovered fullscreen, sounds, and music config fields.",
        .credits => "Play the shipped archive-backed credits crawl.",
        .exit => "Leave the runtime.",
    };
}

pub fn optionsMenuTitle(item: OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => "Full-screen",
        .sound_volume => "Sounds Volume",
        .music_volume => "Music Volume",
        .back => "Back",
    };
}

pub fn optionsMenuHint(runtime_config_loaded_from_file: bool, item: OptionsMenuItem) ?[]const u8 {
    return switch (item) {
        .fullscreen => if (runtime_config_loaded_from_file)
            "Recovered fullscreen preference from SnailMail.cfg. The development default only stays windowed when no runtime config exists."
        else
            "Recovered fullscreen preference from the options flow. Until a runtime config exists, development startup stays windowed by default.",
        .sound_volume => "Recovered sound-effects scalar from SnailMail.cfg and the original options menu apply path.",
        .music_volume => "Recovered music scalar from SnailMail.cfg and the original options menu apply path.",
        .back => "Save the current config blob and return to the main menu.",
    };
}

pub fn optionsMenuLabel(item: OptionsMenuItem, fullscreen_enabled: bool, sound_volume: f32, music_volume: f32, buffer: []u8) ![]const u8 {
    return switch (item) {
        .fullscreen => std.fmt.bufPrint(buffer, "Full-screen {s}", .{if (fullscreen_enabled) "On" else "Off"}),
        .sound_volume => std.fmt.bufPrint(buffer, "Sounds {d:>3.0}%", .{sound_volume * 100.0}),
        .music_volume => std.fmt.bufPrint(buffer, "Music {d:>3.0}%", .{music_volume * 100.0}),
        .back => "Back",
    };
}

pub fn frontendRouteModeLabel(mode: FrontendLevelMode) []const u8 {
    return switch (mode) {
        .postal => "Postal",
        .time_trial => "Time Trial",
        .challenge => "Challenge",
        .tutorial => "Tutorial",
    };
}

pub fn routeMenuActionLabel(mode: FrontendLevelMode, action: RouteMenuAction) []const u8 {
    return switch (action) {
        .play => if (mode == .postal) "Deliver!" else "Play",
        .watch_best_trial => "Watch Best Trial",
        .back => if (mode == .postal) "Exit" else "Back",
    };
}

pub fn routeMenuHint(mode: FrontendLevelMode, action: RouteMenuAction) ?[]const u8 {
    return switch (action) {
        .play => if (mode == .postal)
            "Launch the selected delivery route using the recovered front-end route index."
        else
            "Launch the selected route using the recovered front-end route index.",
        .watch_best_trial => "The original front end can launch saved replay trials from here, but replay playback is not ported yet.",
        .back => "Return to the main menu.",
    };
}

// PORT(verified): the original route selectors pass 1-based postal/time-trial indices into
// `load_frontend_level_by_mode_and_index`, so route 1 is `ARCADE001`, not `ARCADE000`.
pub fn frontendLevelPath(mode: FrontendLevelMode, level_index: usize, path_buffer: []u8) ![]const u8 {
    return switch (mode) {
        .tutorial => "LEVELS/TUTORIAL.TXT",
        .challenge => "LEVELS/CHALLENGE000.TXT",
        .postal => if (level_index == 0)
            error.InvalidRouteIndex
        else if (level_index <= 0x32)
            try std.fmt.bufPrint(path_buffer, "LEVELS/ARCADE{d:0>3}.TXT", .{level_index})
        else
            "LEVELS/ARCADEEXTRA000.TXT",
        .time_trial => if (level_index == 0)
            error.InvalidRouteIndex
        else if (level_index <= 0x32)
            try std.fmt.bufPrint(path_buffer, "LEVELS/ARCADE{d:0>3}.TXT", .{level_index})
        else
            try std.fmt.bufPrint(path_buffer, "LEVELS/TIMETRIALEXTRA{d:0>3}.TXT", .{level_index - 0x32}),
    };
}

test "frontend level mode paths follow recovered launch mapping" {
    var scratch: [64]u8 = undefined;

    try std.testing.expectEqualStrings("LEVELS/TUTORIAL.TXT", try frontendLevelPath(.tutorial, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/CHALLENGE000.TXT", try frontendLevelPath(.challenge, 0, &scratch));
    try std.testing.expectError(error.InvalidRouteIndex, frontendLevelPath(.postal, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE001.TXT", try frontendLevelPath(.postal, 1, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE012.TXT", try frontendLevelPath(.postal, 12, &scratch));
    try std.testing.expectError(error.InvalidRouteIndex, frontendLevelPath(.time_trial, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE001.TXT", try frontendLevelPath(.time_trial, 1, &scratch));
    try std.testing.expectEqualStrings("LEVELS/TIMETRIALEXTRA001.TXT", try frontendLevelPath(.time_trial, 0x33, &scratch));
}

test "route menu labels follow recovered postal wording" {
    try std.testing.expectEqualStrings("Deliver!", routeMenuActionLabel(.postal, .play));
    try std.testing.expectEqualStrings("Exit", routeMenuActionLabel(.postal, .back));
    try std.testing.expectEqualStrings("Play", routeMenuActionLabel(.time_trial, .play));
    try std.testing.expectEqualStrings("Back", routeMenuActionLabel(.time_trial, .back));
}

test "frontend fade-in reaches idle after 18 ticks" {
    var transition: FrontendTransition = .{};
    transition.beginFadeIn();

    for (0..18) |_| {
        try std.testing.expectEqual(@as(?GamePhase, null), transition.update());
    }

    try std.testing.expectEqual(FrontendTransitionState.idle, transition.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), transition.alpha, 0.001);
}

test "frontend fade-out hands off after black hold" {
    var transition: FrontendTransition = .{};
    transition.beginFadeOut(.main_menu);

    var handoff_phase: ?GamePhase = null;
    for (0..21) |_| {
        handoff_phase = transition.update() orelse handoff_phase;
    }

    try std.testing.expectEqual(GamePhase.main_menu, handoff_phase.?);
    try std.testing.expectEqual(FrontendTransitionState.handoff, transition.state);

    transition.completeHandoff();
    try std.testing.expectEqual(FrontendTransitionState.fading_in, transition.state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), transition.alpha, 0.001);
}
