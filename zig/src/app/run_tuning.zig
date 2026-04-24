const std = @import("std");

const config = @import("../config.zig");
const frontend = @import("../frontend.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const gameplay = @import("../gameplay.zig");
const high_score = @import("../high_score.zig");
const level = @import("../level.zig");
const track = @import("../track.zig");

const FrontendLevelMode = frontend.FrontendLevelMode;

pub const Context = struct {
    active_frontend_mode: ?FrontendLevelMode,
    selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride,
    runtime_config: *const config.Blob,
    current_level: ?*const level.Definition,
    current_track_preview: ?*const track.LoadedLevelPreview,
    active_frontend_level_index: usize,
    current_runtime_build_seed: u32,
};

pub fn replaySpeedScalarForSliderValue(value: u32) f32 {
    const normalized = @as(f32, @floatFromInt(value)) * 0.01;
    return if (normalized >= 1.0)
        1.1
    else
        (normalized * 0.9) + 0.2;
}

pub fn currentRunReplaySpeedScalar(context: Context) f32 {
    if (context.selected_level_record_override) |record| return record.replay_speed_scalar;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => replaySpeedScalarForSliderValue(context.runtime_config.challengeReplaySpeedValue()),
        .postal, .time_trial, .tutorial => replaySpeedScalarForSliderValue(if (context.current_level) |loaded_level|
            @as(u32, @intCast(loaded_level.speed orelse 0))
        else
            0),
    };
}

pub fn currentRunChallengeDifficultyValue(context: Context) u32 {
    if (context.selected_level_record_override) |record| return record.challenge_difficulty_value;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => context.runtime_config.challengeReplayDifficultyValue(),
        .postal, .time_trial, .tutorial => 0,
    };
}

pub fn currentRunChallengeDifficultyScalar(context: Context) f32 {
    if (context.selected_level_record_override) |record| return record.challenge_difficulty_scalar;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => @as(f32, @floatFromInt(currentRunChallengeDifficultyValue(context))) * 0.01,
        .postal, .time_trial, .tutorial => 0.0,
    };
}

pub fn currentRunChallengeSpeedValue(context: Context) u32 {
    if (context.selected_level_record_override) |record| return record.challenge_speed_value;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => context.runtime_config.challengeReplaySpeedValue(),
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

pub fn currentRunGarbageScalar(context: Context) f32 {
    if (context.selected_level_record_override) |record| return record.garbage_scalar;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => challengeRuntimeHazardScalar(currentRunChallengeDifficultyValue(context)),
        .postal, .time_trial, .tutorial => if (context.current_level) |loaded_level|
            loaded_level.normalizedGarbageScalar() orelse 0.0
        else
            0.0,
    };
}

pub fn currentRunSaltScalar(context: Context) f32 {
    if (context.selected_level_record_override) |record| return record.salt_scalar;
    return switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => challengeRuntimeHazardScalar(currentRunChallengeDifficultyValue(context)),
        .postal, .time_trial, .tutorial => if (context.current_level) |loaded_level|
            loaded_level.normalizedSaltScalar() orelse 0.0
        else
            0.0,
    };
}

pub fn currentParcelTarget(context: Context) usize {
    if (context.current_track_preview) |preview| return preview.parcel_target_count;
    return if (context.current_level) |loaded_level|
        loaded_level.parcels orelse 0
    else
        0;
}

pub fn configureRuntimeParcels(context: Context, random_state: *u32, loaded_track_preview: *track.LoadedLevelPreview) !void {
    switch (context.active_frontend_mode orelse .tutorial) {
        .challenge => {
            const target_count = challengeParcelTargetCount(
                currentRunChallengeSpeedValue(context),
                currentRunChallengeDifficultyScalar(context),
            );
            _ = try loaded_track_preview.trimParcelAnnotationsToTarget(random_state, target_count);
        },
        .postal, .time_trial, .tutorial => {},
    }
}

pub fn currentRunRuntimeBuildFlags(context: Context) u32 {
    return if (context.current_track_preview) |preview|
        preview.runtime_build_flags
    else if (context.selected_level_record_override) |record|
        record.runtime_build_flags
    else
        runtimeBuildFlagsForFrontendMode(context.active_frontend_mode);
}

pub fn currentRunHighScoreEntry(context: Context, score: u32) high_score.Entry {
    return .{
        .score = score,
        .replay_level_index = @intCast(context.active_frontend_level_index),
        .replay_mode_id = if (context.active_frontend_mode) |mode|
            @as(u32, @intCast(@intFromEnum(mode)))
        else
            0,
        .challenge_speed_value = currentRunChallengeSpeedValue(context),
        .runtime_build_flags = currentRunRuntimeBuildFlags(context),
        .replay_speed_scalar = currentRunReplaySpeedScalar(context),
        .challenge_difficulty_value = currentRunChallengeDifficultyValue(context),
        .challenge_difficulty_scalar = currentRunChallengeDifficultyScalar(context),
        .runtime_build_seed = context.current_runtime_build_seed,
        .garbage_scalar = currentRunGarbageScalar(context),
        .salt_scalar = currentRunSaltScalar(context),
    };
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
