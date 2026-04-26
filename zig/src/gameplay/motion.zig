const std = @import("std");

const track = @import("../track.zig");

pub const ReplayState = struct {
    world_x_override: ?f32 = null,
    raw_flag_bits: u8 = 0,
    track_state_latch: bool = false,
    fade_requested: bool = false,
};

const fresh_replay_movement_flag_offset: f32 = 0.30000001;

pub fn movementFlagFireStartProgress(progress_step: f32, fresh: bool) f32 {
    return if (fresh) progress_step + fresh_replay_movement_flag_offset else progress_step;
}

pub fn replayMovementFlagStartProgress(progress_step: f32, raw_flag_bits: u8) ?f32 {
    if ((raw_flag_bits & 0x01) != 0) return movementFlagFireStartProgress(progress_step, true);
    if ((raw_flag_bits & 0x02) != 0) return progress_step;
    return null;
}

pub const TrackPosition = struct {
    runtime_track_index: usize = 0,
    row_progress: f32 = 0.0,
    row_position: f32 = 0.0,
};

pub fn syncTrackPosition(
    preview: *const track.LoadedLevelPreview,
    runtime_track_index: usize,
    row_progress: f32,
) TrackPosition {
    if (preview.total_rows == 0) return .{};

    const last_row = preview.total_rows - 1;
    var synced_index = runtime_track_index;
    var synced_progress = row_progress;
    if (synced_index > last_row) {
        synced_index = last_row;
        synced_progress = 0.999;
    }

    return .{
        .runtime_track_index = synced_index,
        .row_progress = synced_progress,
        .row_position = @as(f32, @floatFromInt(synced_index)) + synced_progress,
    };
}

pub fn advanceTrackPosition(
    preview: *const track.LoadedLevelPreview,
    runtime_track_index: usize,
    row_progress: f32,
    step_rows: f32,
) TrackPosition {
    if (preview.total_rows == 0) return .{};

    const last_row = preview.total_rows - 1;
    const max_progress: f32 = 0.999;
    var advanced_index = runtime_track_index;
    var advanced_progress = row_progress;
    var remaining = step_rows;

    if (remaining >= 0.0) {
        while (remaining > 0.0) {
            const progress_limit: f32 = if (advanced_index >= last_row) max_progress else 1.0;
            const available_progress = progress_limit - advanced_progress;
            if (available_progress <= 0.0) break;

            if (remaining < available_progress) {
                advanced_progress += remaining;
                remaining = 0.0;
                break;
            }

            remaining -= available_progress;
            if (advanced_index >= last_row) {
                advanced_progress = max_progress;
                remaining = 0.0;
                break;
            }

            advanced_index += 1;
            advanced_progress = 0.0;
        }
    } else {
        while (remaining < 0.0) {
            const available_progress = advanced_progress;
            if (-remaining <= available_progress) {
                advanced_progress += remaining;
                remaining = 0.0;
                break;
            }

            remaining += available_progress;
            if (advanced_index == 0) {
                advanced_progress = 0.0;
                remaining = 0.0;
                break;
            }

            advanced_index -= 1;
            advanced_progress = 1.0;
        }
    }

    return syncTrackPosition(preview, advanced_index, advanced_progress);
}

pub fn trackPositionFromWorldZ(preview: *const track.LoadedLevelPreview, world_z: f32) TrackPosition {
    if (preview.total_rows == 0) return .{};

    const max_row = @max(@as(f32, @floatFromInt(preview.total_rows)) - 0.001, 0.0);
    const clamped_row_position = std.math.clamp(world_z, 0.0, max_row);
    const runtime_track_index = preview.rowIndexAtWorldZ(clamped_row_position);
    return .{
        .runtime_track_index = runtime_track_index,
        .row_progress = std.math.clamp(
            clamped_row_position - @as(f32, @floatFromInt(runtime_track_index)),
            0.0,
            0.999,
        ),
        .row_position = clamped_row_position,
    };
}

test "replay movement flags seed native movement fire progress" {
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        replayMovementFlagStartProgress(0.2, 0x01).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.2),
        replayMovementFlagStartProgress(0.2, 0x02).?,
        0.0001,
    );
    try std.testing.expectEqual(@as(?f32, null), replayMovementFlagStartProgress(0.2, 0x00));
}

test "fresh movement fire starts ahead of repeat fire" {
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.37407407),
        movementFlagFireStartProgress(0.0740740746, true),
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.074074075),
        movementFlagFireStartProgress(0.0740740746, false),
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
