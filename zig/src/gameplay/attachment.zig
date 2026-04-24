const std = @import("std");
const attachment_builders = @import("../attachment_builders.zig");
const track = @import("../track.zig");
const motion = @import("motion.zig");

pub const entry_rider_height: f32 = 0.49;
pub const side_exit_margin: f32 = 0.3;
pub const entry_start_y_tolerance: f32 = -0.2;
pub const entry_end_y_tolerance: f32 = 0.001;
pub const exit_progress_step_default: f32 = 1.0 / 60.0;
pub const exit_gate_a_progress_threshold: f32 = 0.7;

// PORT(verified): native jetpack late clear lane `0x43ce75` in
// `artifacts/ida/functions/0043b120-update_subgoldy.c` only retires
// `attachment_exit_pending` when `jetpack_gauge.state == 1 AND
// live_matrix.position.y < 1.0` (IDA 0x43ce47). Above `1.0`, active jetpack
// flight keeps the gate armed so the airborne progress/gate-A lanes run.
pub const native_jetpack_altitude_cap: f32 = 1.0;

pub fn stepExitState(runner: anytype) void {
    if (!runner.attachment_exit_pending) return;
    if (runner.phase == .active and runner.jetpack.active and runner.position_y < native_jetpack_altitude_cap) {
        runner.attachment_exit_pending = false;
        return;
    }

    // PORT(verified): `attachment_exit_progress` advances in frame-sized
    // increments. If `attachment_exit_progress_step` is zero (native can clear the
    // lane while preserving the pending latch), the gate remains in its previous state.
    const progress_step = runner.attachment_exit_progress_step;
    runner.attachment_exit_progress = std.math.clamp(
        runner.attachment_exit_progress + progress_step,
        0.0,
        1.0,
    );
    if (!runner.attachment_exit_gate_a and runner.attachment_exit_progress > exit_gate_a_progress_threshold) {
        runner.attachment_exit_gate_a = true;
    }
}

pub fn beginExitState(runner: anytype, anchor_z: f32) void {
    runner.attachment_exit_pending = true;
    runner.attachment_exit_anchor_z = anchor_z;
    runner.attachment_exit_progress = 0.0;
    runner.attachment_exit_progress_step = exit_progress_step_default;
    runner.attachment_exit_gate_a = false;
    runner.attachment_exit_gate_b = false;
}

pub fn seedExitStateFromCurrentExit(runner: anytype, anchor_z: f32) void {
    const post_follow_value_a = runner.post_follow_value_a;
    const post_follow_value_b = runner.post_follow_value_b;
    beginExitState(runner, anchor_z);
    runner.post_follow_value_a = post_follow_value_a;
    runner.post_follow_value_b = post_follow_value_b;
}

pub fn seedExitStateZeroed(runner: anytype, anchor_z: f32) void {
    beginExitState(runner, anchor_z);
    runner.post_follow_value_a = 0.0;
    runner.post_follow_value_b = 0.0;
}

pub fn trackEntryWorldPosition(preview: *const track.LoadedLevelPreview, row_position: f32, lane_center: f32) attachment_builders.Vec3 {
    const lane_index = motion.laneIndexForLaneCenter(preview, lane_center);
    const global_row = motion.currentRowIndex(preview, row_position);
    const floor_y = preview.sampleFloorHeightAtGridPosition(global_row, lane_index, row_position) orelse 0.0;
    const world_position = preview.worldPositionForLane(lane_center, row_position, floor_y + entry_rider_height);
    return .{
        .x = world_position.x,
        .y = world_position.y,
        .z = world_position.z,
    };
}

pub fn worldPositionFromLocal(
    pose: attachment_builders.WorldPose,
    local_position: attachment_builders.Vec3,
) attachment_builders.Vec3 {
    return .{
        .x = pose.position.x +
            (pose.basis_right.x * local_position.x) +
            (pose.basis_up.x * local_position.y) +
            (pose.basis_forward.x * local_position.z),
        .y = pose.position.y +
            (pose.basis_right.y * local_position.x) +
            (pose.basis_up.y * local_position.y) +
            (pose.basis_forward.y * local_position.z),
        .z = pose.position.z +
            (pose.basis_right.z * local_position.x) +
            (pose.basis_up.z * local_position.y) +
            (pose.basis_forward.z * local_position.z),
    };
}

pub fn localPosition(pose: attachment_builders.WorldPose, world_position: attachment_builders.Vec3) attachment_builders.Vec3 {
    const delta = attachment_builders.Vec3.sub(world_position, pose.position);
    return .{
        .x = (delta.x * pose.basis_right.x) + (delta.y * pose.basis_right.y) + (delta.z * pose.basis_right.z),
        .y = (delta.x * pose.basis_up.x) + (delta.y * pose.basis_up.y) + (delta.z * pose.basis_up.z),
        .z = (delta.x * pose.basis_forward.x) + (delta.y * pose.basis_forward.y) + (delta.z * pose.basis_forward.z),
    };
}

pub fn entryVerticalOffset(family: attachment_builders.BuilderFamily, local_y: f32) f32 {
    return switch (family) {
        // Windows seeds nonlinear kind-42 follow height from the raw local rider offset.
        // That path legitimately reaches `-0.49` once Goldy is riding the trough floor.
        .nonlinear_42 => local_y,
        else => @max(0.0, local_y - entry_rider_height),
    };
}

pub fn templateHalfSpan(built: *const attachment_builders.BuiltAttachment) f32 {
    // PORT(verified): native entry and side-exit checks use template `+0x54`, which
    // constructor traces show is the wide template span lane (`WORM`: 16), not the
    // narrower Zig-side builder width (`WORM`: 4).
    const span_cells = built.template.spec.subdivision_count orelse built.template.width_cells;
    return @as(f32, @floatFromInt(span_cells)) * 0.5;
}

pub fn lateralOffsetFromLocalX(
    built_template: *const attachment_builders.Template,
    progress: f32,
    local_x: f32,
) f32 {
    const pose = attachment_builders.samplePoseAtProgress(built_template, progress);
    return if (@abs(pose.lateral_scale) > 0.0001)
        local_x / pose.lateral_scale
    else
        local_x;
}

pub fn shouldSideExit(
    built: *const attachment_builders.BuiltAttachment,
    jetpack_active: bool,
    vertical_offset: f32,
    template_progress: f32,
    source_cell_row: usize,
    lateral_offset: f32,
) bool {
    if (jetpack_active) return false;
    if (vertical_offset > 0.0) return false;

    const pose = attachment_builders.samplePoseAtProgress(&built.template, template_progress);
    const world_pose = attachment_builders.worldPoseForTemplate(
        &built.template,
        template_progress,
        source_cell_row,
        lateral_offset,
        vertical_offset,
    );
    const world_delta_x = @abs(world_pose.position.x - pose.center_x);
    return world_delta_x > templateHalfSpan(built) + side_exit_margin;
}
