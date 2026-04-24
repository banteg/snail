const camera = @import("camera.zig");
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
const intro_cutscene_duration_ticks = camera.intro_cutscene_duration_ticks;
const completion_cutscene_duration_ticks = camera.completion_cutscene_duration_ticks;
const death_cutscene_duration_ticks = camera.death_cutscene_duration_ticks;

pub const CutsceneState = struct {
    id: u8 = cutscene_none_id,
    ticks: u16 = 0,
    camera: camera.CutsceneCameraController = .{},
    anim: runner_state.AnimDispatchState = .{},

    pub fn set(self: *CutsceneState, cutscene_id: u8) void {
        self.id = cutscene_id;
        self.ticks = 0;
        self.camera.ticks = 0;
        self.camera.snap_next = cutscene_id != cutscene_none_id;
        self.camera.state = switch (cutscene_id) {
            cutscene_intro_id => .intro_arm,
            cutscene_completion_id => .completion_arm,
            cutscene_death_id => .death_arm,
            else => .none,
        };
    }

    pub fn clear(self: *CutsceneState) void {
        self.id = cutscene_none_id;
        self.ticks = 0;
        self.camera = .{};
    }
};

pub const HandoffState = struct {
    pending: runner_state.RunnerHandoff = .none,
    completion_timer: f32 = 0.0,
    completion_timer_step: f32 = completion_handoff_timer_step,
    completion_voice_gate: bool = false,
    completion_screen_init_sent: bool = false,

    pub fn resetCompletion(self: *HandoffState) void {
        self.completion_timer = 0.0;
        self.completion_timer_step = completion_handoff_timer_step;
        self.completion_voice_gate = false;
        self.completion_screen_init_sent = false;
    }
};

pub fn beginCompletionCutscene(runner: anytype) void {
    if (runner.phase != .active) return;
    runner.finished = true;
    runner.phase = .completion_handoff;
    runner.handoff.resetCompletion();
    runner.setCutscene(cutscene_completion_id);
}

pub fn maybeBeginCompletionCutscene(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (runner.attachment.exit.pending) return;
    if (runner.movement_mode == .attachment and runner.attachment.follow.active) return;
    if (!routeEndReached(runner, preview)) return;
    beginCompletionCutscene(runner);
}

pub fn updateCompletionHandoff(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    _ = advanceCutsceneTicks(runner);
    runner.handoff.completion_timer += runner.handoff.completion_timer_step;
    if (!runner.handoff.completion_voice_gate and
        runner.handoff.completion_timer >= completion_handoff_voice_delay_seconds)
    {
        runner.handoff.completion_voice_gate = true;
    }
    if (!runner.handoff.completion_screen_init_sent and
        (runner.cutscene.camera.state == .completion_arm or runner.cutscene.camera.state == .completion_blend) and
        runner.handoff.completion_timer >= completion_handoff_timer_step)
    {
        runner.handoff.completion_screen_init_sent = true;
        runner.handoff.pending = .completion_screen_init;
    }
    if (runner.row_event_display.gate_18 != 0 and
        runner.currentRowEventCompletionCellActive(preview))
    {
        runner.handoff.completion_timer = @max(
            runner.handoff.completion_timer,
            completion_handoff_release_force_seconds,
        );
    }
    if (runner.row_event_display.state == .complete) {
        runner.handoff.completion_timer = @max(
            runner.handoff.completion_timer,
            completion_handoff_release_force_seconds,
        );
    }
    if (runner.handoff.completion_timer < completion_handoff_release_seconds) return;
    if (completionHandoffRequiresRowEventResolution(runner) and
        runner.row_event_display.state != .complete)
    {
        runner.handoff.completion_timer = @max(
            0.0,
            runner.handoff.completion_timer - runner.handoff.completion_timer_step,
        );
        return;
    }
    if (runner.handoff.pending != .none) return;
    runner.handoff.pending = .completion_finalize;
}

pub fn advanceCutsceneTicks(runner: anytype) bool {
    const duration_ticks = cutsceneDurationTicks(runner.cutscene.id) orelse return false;
    if (runner.cutscene.ticks >= duration_ticks) return true;
    runner.cutscene.ticks +|= 1;
    if (runner.cutscene.ticks > duration_ticks) {
        runner.cutscene.ticks = duration_ticks;
    }
    return runner.cutscene.ticks >= duration_ticks;
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
