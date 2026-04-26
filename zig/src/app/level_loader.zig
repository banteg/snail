const std = @import("std");

const audio_volume = @import("audio_volume.zig");
const run_tuning = @import("run_tuning.zig");
const track_build_seed = @import("track_build_seed.zig");
const voice_audio = @import("voice_audio.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_resources = @import("../gameplay/resources.zig");
const level = @import("../level.zig");
const level_prompt = @import("../level_prompt.zig");
const segment = @import("../segment.zig");
const track = @import("../track.zig");
const track_render = @import("../track_render.zig");

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
    const forced_empty_prompt = replay_sample_on_match and state.level_prompt_queue.active() == null;
    if (segment_changed or token_changed or forced_empty_prompt) {
        queueLevelSegmentPrompt(state, segment_entry);
    }
    if (segment_changed or token_changed or replay_sample_on_match) {
        try voice_audio.playLevelSegmentSample(voice_audio.context(state), segment_entry);
    }
}

fn startupGameplayBlockActive(state: anytype) bool {
    if (state.gameplay_click_start_active) return true;
    const runner = state.level_runner orelse return false;
    return runner.introCutsceneBlocksGameplay();
}

pub fn loadGameLevel(state: anytype, level_path: []const u8) !void {
    state.level_index = state.resources.catalog.findLevelIndex(level_path) orelse return error.EntryNotFound;
    track_build_seed.invalidate(trackBuildSeedContext(state));
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
    gameplay_resources.unloadTurbo(&state.gameplay_resources);
    state.gameplay_jetpack_visual_state = .{};
    state.gameplay_weapon_visual_state = .{};
    state.gameplay_effects.clear();
    voice_audio.stopPlayback(voice_audio.context(state));
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
        const runtime_build_seed = track_build_seed.seedForCurrentLoad(trackBuildSeedContext(state));
        state.current_track_preview = try track.LoadedLevelPreview.loadWithOptions(
            state.allocator,
            &state.resources.catalog,
            loaded_level,
            .{
                .runtime_build_flags = run_tuning.currentRunRuntimeBuildFlags(runTuningContext(state)),
                .runtime_build_seed = runtime_build_seed,
                .random_length_scalar_override = switch (state.active_frontend_mode orelse .tutorial) {
                    .challenge => run_tuning.currentRunChallengeDifficultyScalar(runTuningContext(state)),
                    .postal, .time_trial, .tutorial => null,
                },
                .garbage_scalar_override = run_tuning.currentRunGarbageScalar(runTuningContext(state)),
                .salt_scalar_override = run_tuning.currentRunSaltScalar(runTuningContext(state)),
            },
        );
        if (state.current_track_preview) |*loaded_track_preview| {
            state.math_random_state = loaded_track_preview.runtime_build_final_random_state;
            try run_tuning.configureRuntimeParcels(runTuningContext(state), &state.math_random_state, loaded_track_preview);
            if (gameTrackSetIndexForLevel(loaded_level.track)) |track_set_index| {
                state.current_game_track_scene = try track_render.Scene.buildStandaloneSegmentScene(
                    state.allocator,
                    &state.resources,
                    track_set_index,
                );
            }
            if (state.command == .game) {
                try gameplay_resources.reloadTurbo(
                    &state.gameplay_resources,
                    state.allocator,
                    &state.resources,
                    &state.animation_catalog,
                );
                audio_volume.applyConfigVolumes(audio_volume.context(state));
            }
            state.level_runner = gameplay.Runner.init(loaded_track_preview);
            state.level_runner.?.configureCompletionBonus(
                run_tuning.currentParcelTarget(runTuningContext(state)),
                run_tuning.completionBonusAppliesForMode(state.active_frontend_mode),
            );
            state.level_runner.?.configureSessionMode(run_tuning.runnerSessionModeForFrontendMode(state.active_frontend_mode));
            state.level_runner.?.configureBaseSubgameRate(run_tuning.currentRunReplaySpeedScalar(runTuningContext(state)));
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

pub fn gameTrackSetIndexForLevel(level_track: level.Track) ?u8 {
    return switch (level_track) {
        .index => |index| switch (index) {
            0, 1, 2, 3 => @intCast(index),
            else => null,
        },
        .random => null,
    };
}

fn runTuningContext(state: anytype) run_tuning.Context {
    const loaded_level = if (state.current_level) |*current_level|
        current_level
    else
        null;
    const loaded_track_preview = if (state.current_track_preview) |*current_track_preview|
        current_track_preview
    else
        null;
    return .{
        .active_frontend_mode = state.active_frontend_mode,
        .selected_level_record_override = state.selected_level_record_override,
        .runtime_config = &state.runtime_config,
        .current_level = loaded_level,
        .current_track_preview = loaded_track_preview,
        .active_frontend_level_index = state.active_frontend_level_index,
        .current_runtime_build_seed = state.current_runtime_build_seed,
    };
}

fn trackBuildSeedContext(state: anytype) track_build_seed.Context {
    return .{
        .command = state.command,
        .active_frontend_mode = state.active_frontend_mode,
        .active_frontend_level_index = state.active_frontend_level_index,
        .level_index = state.level_index,
        .selected_level_record_override = state.selected_level_record_override,
        .math_random_state = &state.math_random_state,
        .current_runtime_build_seed = &state.current_runtime_build_seed,
        .current_runtime_build_seed_level_index = &state.current_runtime_build_seed_level_index,
        .current_runtime_build_seed_mode = &state.current_runtime_build_seed_mode,
    };
}
