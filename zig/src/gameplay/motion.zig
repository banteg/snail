const std = @import("std");

const track = @import("../track.zig");

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
