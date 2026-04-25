const app = @import("../app.zig");
const boot_assets = @import("boot_assets.zig");
const music_audio = @import("music_audio.zig");
const voice_audio = @import("voice_audio.zig");

const credits_script_path = app.credits_script_path;
const default_audio_path = app.default_audio_path;
const help_background_path = app.help_background_path;
const intro_background_path = app.intro_background_path;
const intro_music_path = app.intro_music_path;
const intro_script_path = app.intro_script_path;
const main_menu_background_path = app.main_menu_background_path;
const route_map_background_path = app.route_map_background_path;
const thanks_screen_background_path = app.thanks_screen_background_path;

pub fn sync(state: anytype) !void {
    switch (state.game_phase) {
        .level, .pause_menu => {},
        else => voice_audio.stopPlayback(voice_audio.context(state)),
    }
    switch (state.game_phase) {
        .boot => {
            music_audio.stopPreview(music_audio.context(state));
            clearLevelSelectionState(state);
            state.boot_task_index = 0;
            boot_assets.unload(boot_assets.context(state));
            state.unloadTextScript();
            state.unloadGameBackground();
            try state.loadLoadingScreen();
        },
        .intro => {
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, intro_background_path, intro_music_path);
            try state.loadTextScript(intro_script_path);
        },
        .main_menu, .new_game_menu, .high_scores_menu => {
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, main_menu_background_path, default_audio_path);
        },
        .challenge_setup_menu => {
            clearLevelSelectionState(state);
            state.challenge_setup_speed_display_value = @as(f32, @floatFromInt(state.runtime_config.challengeReplaySpeedValue())) * 0.01;
            state.challenge_setup_difficulty_display_value = @as(f32, @floatFromInt(state.runtime_config.challengeReplayDifficultyValue())) * 0.01;
            try loadBackgroundMusicPhase(state, main_menu_background_path, default_audio_path);
        },
        .options_menu => {
            state.options_sound_display_value = state.runtime_config.soundVolume();
            state.options_music_display_value = state.runtime_config.musicVolume();
            if (state.options_return_phase == .pause_menu) {
                try loadCurrentGameplayBackdrop(state);
            } else {
                clearLevelSelectionState(state);
                try loadBackgroundMusicPhase(state, main_menu_background_path, default_audio_path);
            }
        },
        .pause_menu => {
            try loadCurrentGameplayBackdrop(state);
        },
        .route_map_menu => {
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, route_map_background_path, default_audio_path);
        },
        .credits => {
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, intro_background_path, intro_music_path);
            try state.loadTextScript(credits_script_path);
        },
        .help => {
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, help_background_path, default_audio_path);
        },
        .exit_prompt => {
            if (state.exit_prompt_return_phase == .pause_menu) {
                try loadCurrentGameplayBackdrop(state);
            } else if (state.exit_prompt_return_phase == .route_map_menu) {
                clearLevelSelectionState(state);
                try loadBackgroundMusicPhase(state, route_map_background_path, default_audio_path);
            } else {
                clearLevelSelectionState(state);
                try loadBackgroundMusicPhase(state, main_menu_background_path, default_audio_path);
            }
        },
        .completion_screen => {
            if (state.preserve_completion_screen_reveal_on_enter) {
                state.preserve_completion_screen_reveal_on_enter = false;
            } else {
                state.resetCompletionScreenReveal();
            }
            clearLevelTransientUi(state);
            try loadCurrentGameplayBackdrop(state);
        },
        .thanks_screen => {
            state.thanks_screen_controller.reset();
            clearLevelSelectionState(state);
            try loadBackgroundMusicPhase(state, thanks_screen_background_path, intro_music_path);
        },
        .level => {
            music_audio.stopPreview(music_audio.context(state));
            clearLevelTransientUi(state);
            try loadCurrentGameplayBackdrop(state);
            const previous_active_level_segment_index = state.active_level_segment_index;
            try state.syncActiveLevelSegment();
            try state.dispatchCurrentRunnerRowMessage(previous_active_level_segment_index, null, true);
        },
    }
}

fn clearLevelSelectionState(state: anytype) void {
    state.active_level_segment_index = null;
    clearLevelTransientUi(state);
}

fn clearLevelTransientUi(state: anytype) void {
    state.clearLevelPromptQueue();
    state.mouse_level_lane_target = null;
}

fn unloadFrontendScreens(state: anytype) void {
    state.unloadTextScript();
    state.unloadLoadingScreen();
}

fn loadBackgroundMusicPhase(state: anytype, background_path: []const u8, music_path: []const u8) !void {
    unloadFrontendScreens(state);
    try state.loadGameBackground(background_path);
    try music_audio.playByPath(music_audio.context(state), music_path);
}

fn loadCurrentGameplayBackdrop(state: anytype) !void {
    unloadFrontendScreens(state);
    try state.loadCurrentLevelBackground();
}
