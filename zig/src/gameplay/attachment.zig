const std = @import("std");

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
