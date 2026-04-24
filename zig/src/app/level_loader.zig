const std = @import("std");

const audio = @import("audio.zig");
const frontend = @import("../frontend.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_resources = @import("../gameplay/resources.zig");
const high_score = @import("../high_score.zig");
const level = @import("../level.zig");
const level_prompt = @import("../level_prompt.zig");
const segment = @import("../segment.zig");
const track = @import("../track.zig");
const track_render = @import("../track_render.zig");

const FrontendLevelMode = frontend.FrontendLevelMode;

pub fn isTutorialGameplay(state: anytype) bool {
    if (isTutorialFlow(state)) return true;
    return isTutorialLevel(state);
}

pub fn isTutorialFlow(state: anytype) bool {
    if (state.active_frontend_mode == .tutorial) return true;
    if (state.level_runner) |runner| {
        if (runner.session_mode == .tutorial) return true;
    }
    return false;
}

pub fn isTutorialLevel(state: anytype) bool {
    const loaded_level = state.current_level orelse return false;
    return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
}

pub fn resetSubgameCamera(state: anytype) void {
    state.subgame_camera = .{};
}

pub fn queueLevelSegmentPrompt(state: anytype, segment_entry: *const level.SegmentEntry) void {
    const message = segment_entry.message orelse return;
    const duration_ticks = level_prompt.durationTicks(segment_entry.duration);
    if (isTutorialGameplay(state)) {
        state.level_prompt_queue.replaceSingle(message, duration_ticks);
        return;
    }
    state.level_prompt_queue.enqueue(message, duration_ticks);
}

pub fn currentRunnerRowMessageSegmentIndex(state: anytype) ?usize {
    const loaded_level = state.current_level orelse return null;
    const runner = state.level_runner orelse return null;
    const logical_segment_index = runner.currentRowMessageLogicalSegmentIndex() orelse return null;
    if (logical_segment_index >= loaded_level.segments.len) return null;
    return logical_segment_index;
}

pub fn dispatchCurrentRunnerRowMessage(
    state: anytype,
    previous_segment_index: ?usize,
    previous_token: ?u32,
    replay_sample_on_match: bool,
) !void {
    const logical_segment_index = currentRunnerRowMessageSegmentIndex(state) orelse return;
    if (startupGameplayBlockActive(state)) return;

    const loaded_level = state.current_level orelse return;
    const runner = state.level_runner orelse return;
    const segment_changed = previous_segment_index == null or previous_segment_index.? != logical_segment_index;
    const token_changed = if (previous_token) |token|
        runner.currentRowMessageToken() != token
    else
        false;
    if (!segment_changed and !token_changed and !replay_sample_on_match) return;

    const segment_entry = &loaded_level.segments[logical_segment_index];
    if (segment_changed or token_changed) {
        queueLevelSegmentPrompt(state, segment_entry);
    }
    if (segment_changed or token_changed or replay_sample_on_match) {
        try audio.playLevelSegmentSample(state, segment_entry);
    }
}

pub fn replaySpeedScalarForSliderValue(value: u32) f32 {
    const normalized = @as(f32, @floatFromInt(value)) * 0.01;
    return if (normalized >= 1.0)
        1.1
    else
        (normalized * 0.9) + 0.2;
}

pub fn currentRunReplaySpeedScalar(state: anytype) f32 {
    if (state.selected_level_record_override) |record| return record.replay_speed_scalar;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => replaySpeedScalarForSliderValue(state.runtime_config.challengeReplaySpeedValue()),
        .postal, .time_trial, .tutorial => replaySpeedScalarForSliderValue(if (state.current_level) |loaded_level|
            @as(u32, @intCast(loaded_level.speed orelse 0))
        else
            0),
    };
}

pub fn currentRunChallengeDifficultyValue(state: anytype) u32 {
    if (state.selected_level_record_override) |record| return record.challenge_difficulty_value;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => state.runtime_config.challengeReplayDifficultyValue(),
        .postal, .time_trial, .tutorial => 0,
    };
}

pub fn currentRunChallengeDifficultyScalar(state: anytype) f32 {
    if (state.selected_level_record_override) |record| return record.challenge_difficulty_scalar;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => @as(f32, @floatFromInt(currentRunChallengeDifficultyValue(state))) * 0.01,
        .postal, .time_trial, .tutorial => 0.0,
    };
}

pub fn currentRunChallengeSpeedValue(state: anytype) u32 {
    if (state.selected_level_record_override) |record| return record.challenge_speed_value;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => state.runtime_config.challengeReplaySpeedValue(),
        .postal, .time_trial, .tutorial => 0,
    };
}

pub fn challengeParcelTargetCount(speed_value: u32, difficulty_scalar: f32) usize {
    const scaled_target = (@as(f32, @floatFromInt(speed_value)) * 50.0 * 0.01) +
        (difficulty_scalar * 50.0);
    return @as(usize, @intFromFloat(@floor(@max(scaled_target, 0.0)))) + 1;
}

pub fn challengeRuntimeHazardScalar(value: u32) f32 {
    return @as(f32, @floatFromInt(value)) * 0.01 * 0.8;
}

pub fn currentRunGarbageScalar(state: anytype) f32 {
    if (state.selected_level_record_override) |record| return record.garbage_scalar;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => challengeRuntimeHazardScalar(currentRunChallengeDifficultyValue(state)),
        .postal, .time_trial, .tutorial => if (state.current_level) |loaded_level|
            loaded_level.normalizedGarbageScalar() orelse 0.0
        else
            0.0,
    };
}

pub fn currentRunSaltScalar(state: anytype) f32 {
    if (state.selected_level_record_override) |record| return record.salt_scalar;
    return switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => challengeRuntimeHazardScalar(currentRunChallengeDifficultyValue(state)),
        .postal, .time_trial, .tutorial => if (state.current_level) |loaded_level|
            loaded_level.normalizedSaltScalar() orelse 0.0
        else
            0.0,
    };
}

pub fn currentParcelTarget(state: anytype) usize {
    if (state.current_track_preview) |preview| return preview.parcel_target_count;
    return if (state.current_level) |loaded_level|
        loaded_level.parcels orelse 0
    else
        0;
}

pub fn configureRuntimeParcels(state: anytype, loaded_track_preview: *track.LoadedLevelPreview) !void {
    switch (state.active_frontend_mode orelse .tutorial) {
        .challenge => {
            const target_count = challengeParcelTargetCount(
                currentRunChallengeSpeedValue(state),
                currentRunChallengeDifficultyScalar(state),
            );
            _ = try loaded_track_preview.trimParcelAnnotationsToTarget(&state.math_random_state, target_count);
        },
        .postal, .time_trial, .tutorial => {},
    }
}

pub fn currentRunRuntimeBuildFlags(state: anytype) u32 {
    return if (state.current_track_preview) |preview|
        preview.runtime_build_flags
    else if (state.selected_level_record_override) |record|
        record.runtime_build_flags
    else
        runtimeBuildFlagsForFrontendMode(state.active_frontend_mode);
}

pub fn currentRunHighScoreEntry(state: anytype, score: u32) high_score.Entry {
    return .{
        .score = score,
        .replay_level_index = @intCast(state.active_frontend_level_index),
        .replay_mode_id = if (state.active_frontend_mode) |mode|
            @as(u32, @intCast(@intFromEnum(mode)))
        else
            0,
        .challenge_speed_value = currentRunChallengeSpeedValue(state),
        .runtime_build_flags = currentRunRuntimeBuildFlags(state),
        .replay_speed_scalar = currentRunReplaySpeedScalar(state),
        .challenge_difficulty_value = currentRunChallengeDifficultyValue(state),
        .challenge_difficulty_scalar = currentRunChallengeDifficultyScalar(state),
        .runtime_build_seed = state.current_runtime_build_seed,
        .garbage_scalar = currentRunGarbageScalar(state),
        .salt_scalar = currentRunSaltScalar(state),
    };
}

fn startupGameplayBlockActive(state: anytype) bool {
    if (state.gameplay_click_start_active) return true;
    const runner = state.level_runner orelse return false;
    return runner.introCutsceneBlocksGameplay();
}

pub fn loadGameLevel(state: anytype, level_path: []const u8) !void {
    state.level_index = state.resources.catalog.findLevelIndex(level_path) orelse return error.EntryNotFound;
    invalidateTrackBuildSeed(state);
    try reloadLevel(state);
}

pub fn syncActiveLevelSegment(state: anytype) !void {
    _ = state.current_level orelse {
        state.active_level_segment_index = null;
        state.level_prompt_queue.clear();
        return;
    };
    const logical_segment_index = currentRunnerRowMessageSegmentIndex(state) orelse {
        state.active_level_segment_index = null;
        state.level_prompt_queue.clear();
        return;
    };

    state.level_segment_index = logical_segment_index;
    const previous_segment_index = state.active_level_segment_index;
    const segment_changed = previous_segment_index == null or previous_segment_index.? != logical_segment_index;
    state.active_level_segment_index = logical_segment_index;
    if (segment_changed) {
        if (previous_segment_index) |previous_index| {
            if (logical_segment_index < previous_index) {
                state.level_prompt_queue.clear();
            }
        }
    }
}

pub fn reloadLevel(state: anytype) !void {
    const seed_intro_cutscene = state.command == .game and state.seed_level_intro_cutscene;
    state.seed_level_intro_cutscene = false;
    if (state.current_level) |*loaded_level| {
        loaded_level.deinit();
        state.current_level = null;
    }
    if (state.current_segment) |*loaded_segment| {
        loaded_segment.deinit();
        state.current_segment = null;
    }
    if (state.current_track_preview) |*loaded_track_preview| {
        loaded_track_preview.deinit();
        state.current_track_preview = null;
    }
    if (state.current_game_track_scene) |*scene| {
        scene.deinit();
        state.current_game_track_scene = null;
    }
    gameplay_resources.unloadTurbo(state);
    gameplay_resources.resetPresentationState(state);
    state.gameplay_effects.clear();
    audio.stopVoicePlayback(state);
    state.gameplay_voice_manager.clear();
    state.native_gameplay_voice_manager.clear();
    state.announced_slug_voice_cell_count = 0;
    state.level_runner = null;
    state.gameplay_click_start_active = false;
    resetSubgameCamera(state);
    state.tutorial_reference_score = 0;
    if (state.resources.catalog.level_entries.len == 0) return;

    const entry = state.resources.catalog.level_entries[state.level_index];
    state.current_level = try level.loadFromArchive(state.allocator, &state.resources.catalog, entry);
    if (state.current_level) |*loaded_level| {
        const runtime_build_seed = trackBuildSeedForCurrentLoad(state);
        state.current_track_preview = try track.LoadedLevelPreview.loadWithOptions(
            state.allocator,
            &state.resources.catalog,
            loaded_level,
            .{
                .runtime_build_flags = currentRunRuntimeBuildFlags(state),
                .runtime_build_seed = runtime_build_seed,
                .random_length_scalar_override = switch (state.active_frontend_mode orelse .tutorial) {
                    .challenge => currentRunChallengeDifficultyScalar(state),
                    .postal, .time_trial, .tutorial => null,
                },
                .garbage_scalar_override = currentRunGarbageScalar(state),
                .salt_scalar_override = currentRunSaltScalar(state),
            },
        );
        if (state.current_track_preview) |*loaded_track_preview| {
            state.math_random_state = loaded_track_preview.runtime_build_final_random_state;
            try configureRuntimeParcels(state, loaded_track_preview);
            if (gameTrackSetIndexForLevel(loaded_level.track)) |track_set_index| {
                state.current_game_track_scene = try track_render.Scene.buildStandaloneSegmentScene(
                    state.allocator,
                    &state.resources,
                    track_set_index,
                );
            }
            if (state.command == .game) {
                try gameplay_resources.reloadTurbo(state);
                audio.applyAudioConfigVolumes(state);
            }
            state.level_runner = gameplay.Runner.init(loaded_track_preview);
            state.level_runner.?.configureCompletionBonus(
                currentParcelTarget(state),
                completionBonusAppliesForMode(state.active_frontend_mode),
            );
            state.level_runner.?.configureSessionMode(runnerSessionModeForFrontendMode(state.active_frontend_mode));
            state.level_runner.?.configureBaseSubgameRate(currentRunReplaySpeedScalar(state));
            state.gameplay_click_start_active = seed_intro_cutscene and isTutorialFlow(state);
            if (seed_intro_cutscene) {
                state.level_runner.?.setCutscene(gameplay.cutscene_intro_id);
            } else {
                state.level_runner.?.clearCutscene();
            }
            if (state.level_runner) |*runner| {
                state.updateSubgameCamera(runner);
            }
            if (isTutorialGameplay(state)) {
                state.tutorial_reference_score = state.high_score_tables.postal[0].score;
            }
        }
    }
    state.level_segment_index = 0;
    try reloadLevelSegment(state);
    try syncActiveLevelSegment(state);
}

pub fn nextMathRandomInt15(state: anytype) u32 {
    state.math_random_state = (state.math_random_state *% 0x343fd) +% 0x269ec3;
    return (state.math_random_state >> 16) & 0x7fff;
}

pub fn trackBuildSeedForCurrentLoad(state: anytype) u32 {
    if (state.command != .game) return 0;

    const mode = state.active_frontend_mode;
    if (state.selected_level_record_override) |record| {
        if (mode == record.mode and state.active_frontend_level_index == record.level_index) {
            state.current_runtime_build_seed = record.runtime_build_seed;
            state.current_runtime_build_seed_level_index = state.level_index;
            state.current_runtime_build_seed_mode = mode;
            return record.runtime_build_seed;
        }
    }
    if (state.current_runtime_build_seed_level_index == state.level_index and state.current_runtime_build_seed_mode == mode) {
        return state.current_runtime_build_seed;
    }

    const seed: u32 = switch (mode orelse return 0) {
        .tutorial, .time_trial => 0,
        .postal, .challenge => nextMathRandomInt15(state),
    };
    state.current_runtime_build_seed = seed;
    state.current_runtime_build_seed_level_index = state.level_index;
    state.current_runtime_build_seed_mode = mode;
    return seed;
}

pub fn invalidateTrackBuildSeed(state: anytype) void {
    state.current_runtime_build_seed_level_index = null;
    state.current_runtime_build_seed_mode = null;
}

pub fn reloadLevelSegment(state: anytype) !void {
    if (state.current_segment) |*loaded_segment| {
        loaded_segment.deinit();
        state.current_segment = null;
    }

    const loaded_level = state.current_level orelse return;
    if (loaded_level.segments.len == 0) return;
    if (state.level_segment_index >= loaded_level.segments.len) {
        state.level_segment_index = loaded_level.segments.len - 1;
    }

    var path_buffer: [512]u8 = undefined;
    const archive_path = try std.fmt.bufPrint(&path_buffer, "SEGMENTS/{s}", .{loaded_level.segments[state.level_segment_index].path});
    const entry = state.resources.catalog.dat.entryByPath(archive_path) orelse return;
    state.current_segment = try segment.loadFromArchive(state.allocator, &state.resources.catalog, entry);
}

pub fn runtimeBuildFlagsForFrontendMode(mode: ?FrontendLevelMode) u32 {
    return switch (mode orelse .postal) {
        .postal, .challenge => track.postalChallengeRuntimeBuildFlags,
        .time_trial => track.timeTrialRuntimeBuildFlags,
        .tutorial => track.tutorialRuntimeBuildFlags,
    };
}

pub fn runnerSessionModeForFrontendMode(mode: ?FrontendLevelMode) gameplay.SessionMode {
    return switch (mode orelse .postal) {
        .postal => .postal,
        .challenge => .challenge,
        .time_trial => .time_trial,
        .tutorial => .tutorial,
    };
}

pub fn completionBonusAppliesForMode(mode: ?FrontendLevelMode) bool {
    return switch (mode orelse .postal) {
        .postal => true,
        .challenge, .time_trial, .tutorial => false,
    };
}

pub fn gameTrackSetIndexForLevel(level_track: level.Track) ?u8 {
    return switch (level_track) {
        .index => |index| switch (index) {
            0, 1, 2, 3 => @intCast(index),
            else => null,
        },
        .random => null,
    };
}
