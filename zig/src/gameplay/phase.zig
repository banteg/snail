const runner_state = @import("runner_state.zig");
const track = @import("../track.zig");

pub const completion_handoff_timer_step: f32 = 1.0 / 60.0;
pub const completion_handoff_voice_delay_seconds: f32 = 2.0;
pub const completion_handoff_release_seconds: f32 = 5.0;
pub const completion_handoff_release_force_seconds: f32 = 5.1;

const cutscene_none_id = runner_state.cutscene_none_id;
const cutscene_intro_id = runner_state.cutscene_intro_id;
const cutscene_completion_id = runner_state.cutscene_completion_id;
const cutscene_death_id = runner_state.cutscene_death_id;
const intro_cutscene_duration_ticks = @import("camera.zig").intro_cutscene_duration_ticks;
const completion_cutscene_duration_ticks = @import("camera.zig").completion_cutscene_duration_ticks;
const death_cutscene_duration_ticks = @import("camera.zig").death_cutscene_duration_ticks;

pub fn beginCompletionCutscene(runner: anytype) void {
    if (runner.phase != .active) return;
    runner.finished = true;
    runner.phase = .completion_handoff;
    runner.completion_handoff_timer = 0.0;
    runner.completion_handoff_timer_step = completion_handoff_timer_step;
    runner.completion_handoff_voice_gate = false;
    runner.completion_screen_init_sent = false;
    runner.setCutscene(cutscene_completion_id);
}

pub fn maybeBeginCompletionCutscene(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (runner.attachment_exit_pending) return;
    if (runner.movement_mode == .attachment and runner.attachment_follow.active) return;
    if (!routeEndReached(runner, preview)) return;
    beginCompletionCutscene(runner);
}

pub fn updateCompletionHandoff(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    _ = advanceCutsceneTicks(runner);
    runner.completion_handoff_timer += runner.completion_handoff_timer_step;
    if (!runner.completion_handoff_voice_gate and
        runner.completion_handoff_timer >= completion_handoff_voice_delay_seconds)
    {
        runner.completion_handoff_voice_gate = true;
    }
    if (!runner.completion_screen_init_sent and
        (runner.cutscene_camera.state == .completion_arm or runner.cutscene_camera.state == .completion_blend) and
        runner.completion_handoff_timer >= completion_handoff_timer_step)
    {
        runner.completion_screen_init_sent = true;
        runner.pending_handoff = .completion_screen_init;
    }
    if (runner.row_event_display.gate_18 != 0 and
        runner.currentRowEventCompletionCellActive(preview))
    {
        runner.completion_handoff_timer = @max(
            runner.completion_handoff_timer,
            completion_handoff_release_force_seconds,
        );
    }
    if (runner.row_event_display.state == .complete) {
        runner.completion_handoff_timer = @max(
            runner.completion_handoff_timer,
            completion_handoff_release_force_seconds,
        );
    }
    if (runner.completion_handoff_timer < completion_handoff_release_seconds) return;
    if (completionHandoffRequiresRowEventResolution(runner) and
        runner.row_event_display.state != .complete)
    {
        runner.completion_handoff_timer = @max(
            0.0,
            runner.completion_handoff_timer - runner.completion_handoff_timer_step,
        );
        return;
    }
    if (runner.pending_handoff != .none) return;
    runner.pending_handoff = .completion_finalize;
}

pub fn advanceCutsceneTicks(runner: anytype) bool {
    const duration_ticks = cutsceneDurationTicks(runner.cutscene_id) orelse return false;
    if (runner.cutscene_ticks >= duration_ticks) return true;
    runner.cutscene_ticks +|= 1;
    if (runner.cutscene_ticks > duration_ticks) {
        runner.cutscene_ticks = duration_ticks;
    }
    return runner.cutscene_ticks >= duration_ticks;
}

pub fn routeEndReached(runner: anytype, preview: *const track.LoadedLevelPreview) bool {
    if (preview.total_rows == 0) return false;
    return runner.row_position >= preview.course_end_threshold;
}

fn completionHandoffRequiresRowEventResolution(runner: anytype) bool {
    return switch (runner.session_mode) {
        // PORT(verified): native `update_subgoldy` only keeps the late completion
        // handoff pinned behind the row-event controller when `game + 64 <= 1`
        // (postal and challenge). Time trial and tutorial skip that wait even if
        // the row-event controller still has pending work.
        .postal, .challenge => runner.row_event_display.parcel_target_count != 0,
        .time_trial, .tutorial, .debug => false,
    };
}

fn cutsceneDurationTicks(cutscene_id: u8) ?u16 {
    return switch (cutscene_id) {
        cutscene_intro_id => intro_cutscene_duration_ticks,
        cutscene_completion_id => completion_cutscene_duration_ticks,
        cutscene_death_id => death_cutscene_duration_ticks,
        cutscene_none_id => null,
        else => null,
    };
}
