const std = @import("std");

const track = @import("../track.zig");

pub const ReplayState = struct {
    world_x_override: ?f32 = null,
    secondary_lane: ?i32 = null,
    raw_flag_bits: u8 = 0,
    track_state_latch: bool = false,
    fade_requested: bool = false,
};

const movement_flag_startup_ticks: u64 = 10;
const fresh_replay_movement_flag_offset: f32 = 0.30000001;

pub fn replayMovementFlagSeedProgress(rate_scalar: f32, raw_flag_bits: u8) ?f32 {
    if ((raw_flag_bits & 0x01) != 0) return rate_scalar + fresh_replay_movement_flag_offset;
    if ((raw_flag_bits & 0x02) != 0) return rate_scalar;
    return null;
}

pub fn stepReplayMovementFlagProgress(
    current_progress: f32,
    rate_scalar: f32,
    tick_count: u64,
    replay: ReplayState,
) f32 {
    var progress = current_progress;
    if (tick_count < movement_flag_startup_ticks) {
        progress = rate_scalar;
    }
    if (progress > 0.0) {
        const advanced = progress + rate_scalar;
        return if (advanced > 1.0) 0.0 else advanced;
    }
    if (!replay.track_state_latch) return progress;
    return replayMovementFlagSeedProgress(rate_scalar, replay.raw_flag_bits) orelse progress;
}

test "replay movement flags seed native movement flag progress" {
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        replayMovementFlagSeedProgress(0.2, 0x01).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.2),
        replayMovementFlagSeedProgress(0.2, 0x02).?,
        0.0001,
    );
    try std.testing.expectEqual(@as(?f32, null), replayMovementFlagSeedProgress(0.2, 0x00));
}

test "native movement flag progress advances before replay flags are consulted" {
    const replay = ReplayState{
        .raw_flag_bits = 0x01,
        .track_state_latch = true,
    };

    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        stepReplayMovementFlagProgress(0.3, 0.2, 10, replay),
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.0),
        stepReplayMovementFlagProgress(0.9, 0.2, 10, replay),
        0.0001,
    );
}

pub fn currentRowIndex(preview: *const track.LoadedLevelPreview, row_position: f32) usize {
    return @intFromFloat(@floor(std.math.clamp(
        row_position,
        0.0,
        @as(f32, @floatFromInt(preview.total_rows - 1)),
    )));
}

pub fn laneCenterFromWorldX(preview: *const track.LoadedLevelPreview, world_x: f32) f32 {
    const width_offset = @as(f32, @floatFromInt(preview.max_width)) * 0.5;
    return world_x + width_offset;
}

pub fn laneIndexForLaneCenter(preview: *const track.LoadedLevelPreview, lane_center: f32) usize {
    if (preview.max_width == 0) return 0;
    const centered_lane = std.math.clamp(
        lane_center,
        0.5,
        @as(f32, @floatFromInt(preview.max_width)) - 0.5,
    );
    return @min(
        preview.max_width - 1,
        @as(usize, @intFromFloat(@floor(centered_lane - 0.5))),
    );
}
