const frontend = @import("../frontend.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const frontend_completion_screen = @import("../frontend/completion_screen.zig");
const frontend_high_score_screen = @import("../frontend/high_score_screen.zig");
const gameplay = @import("../gameplay.zig");
const high_score = @import("../high_score.zig");

const FrontendLevelMode = frontend.FrontendLevelMode;

pub const RespawnBridgeState = struct {
    frontend_mode: ?FrontendLevelMode,
    frontend_level_index: usize,
    runner: gameplay.Runner,
};

pub const Outcome = enum {
    completed,
    failed,
};

pub const CompletionFlowOwner = enum {
    postal_route_map,
    postal_final,
    postal_failure,
    challenge_completion,
    challenge_failure,
    time_trial_completion,
    time_trial_failure,
    tutorial_completion,
    tutorial_failure,
};

pub const Persistence = enum {
    none,
    completed,
    failed,
};

pub const Result = struct {
    outcome: Outcome = .completed,
    level_name: []const u8,
    mode: ?FrontendLevelMode,
    elapsed_millis: u32,
    parcel_count: u32,
    parcel_target: usize,
    score: u32,
    score_is_partial: bool,
    score_totals: gameplay.ScoreTotals = .{},
    visible_life_stock: u32 = 0,
    damage_gauge: f32 = 0.0,
    high_score_mode: ?high_score.Mode = null,
    high_score_rank: ?usize = null,
    time_trial_record_improved: bool = false,
    unlocked_next_route: bool = false,
    completion_owner: CompletionFlowOwner = .tutorial_completion,
    persistence: Persistence = .none,
    outer_return_target: frontend_bridge.OuterReturnTarget,
};

pub const StandalonePostLevelHighScoreEntry = struct {
    context: frontend_high_score_screen.PendingEntry,
    return_owner: frontend_bridge.OuterOwnerState,
    return_opcode: frontend_bridge.OuterBridgeOpcode,
};

pub fn outerReturnTargetForCompletionOwner(owner: CompletionFlowOwner) frontend_bridge.OuterReturnTarget {
    return switch (owner) {
        .postal_route_map => .postal_route_map,
        .postal_final => .thanks_screen,
        .postal_failure => .new_game_menu,
        .challenge_completion => .challenge_setup_menu,
        .challenge_failure => .challenge_setup_menu,
        .time_trial_completion => .time_trial_route_map,
        .time_trial_failure => .time_trial_route_map,
        .tutorial_completion => .new_game_menu,
        .tutorial_failure => .main_menu,
    };
}

pub fn completionFlowOwnerForOutcome(outcome: Outcome, mode: ?FrontendLevelMode) CompletionFlowOwner {
    if (outcome == .failed) {
        return switch (mode orelse .postal) {
            .postal => .postal_failure,
            .challenge => .challenge_failure,
            .time_trial => .time_trial_failure,
            .tutorial => .tutorial_failure,
        };
    }
    return switch (mode orelse .postal) {
        .postal => .postal_route_map,
        .challenge => .challenge_completion,
        .time_trial => .time_trial_completion,
        .tutorial => .tutorial_completion,
    };
}

pub fn outerReturnTargetForOutcome(outcome: Outcome, mode: ?FrontendLevelMode) frontend_bridge.OuterReturnTarget {
    return outerReturnTargetForCompletionOwner(completionFlowOwnerForOutcome(outcome, mode));
}

pub fn postalCompletionOwner(current_index: usize, highest_available: usize) CompletionFlowOwner {
    return if (postalCompletionCommitsHighScore(current_index, highest_available))
        .postal_final
    else
        .postal_route_map;
}

pub fn postalCompletionReturnTarget(current_index: usize, highest_available: usize) frontend_bridge.OuterReturnTarget {
    return outerReturnTargetForCompletionOwner(postalCompletionOwner(current_index, highest_available));
}

pub fn postalCompletionCommitsHighScore(current_index: usize, highest_available: usize) bool {
    if (highest_available == 0) return false;
    return current_index >= highest_available;
}

pub fn previewPostalRouteUnlock(current_index: usize, highest_available: usize, saved_limit: usize) bool {
    if (highest_available == 0) return false;
    const clamped_saved = clampUsize(saved_limit, 1, highest_available);
    const clamped_current = clampUsize(current_index, 1, highest_available);
    const next_unlock_limit = nextPostalUnlockLimit(clamped_current, highest_available, clamped_saved);
    return clamped_current < highest_available and next_unlock_limit > clamped_saved;
}

pub fn nextPostalUnlockLimit(current_index: usize, highest_available: usize, saved_limit: usize) usize {
    if (highest_available == 0) return 0;
    const clamped_saved = clampUsize(saved_limit, 1, highest_available);
    const clamped_current = clampUsize(current_index, 1, highest_available);
    if (clamped_current < highest_available) {
        return @max(clamped_saved, clamped_current + 1);
    }
    return clamped_saved;
}

pub fn summary(result: Result) frontend_completion_screen.Summary {
    return .{
        .outcome = switch (result.outcome) {
            .completed => .completed,
            .failed => .failed,
        },
        .level_name = result.level_name,
        .mode = result.mode,
        .elapsed_millis = result.elapsed_millis,
        .parcel_count = result.parcel_count,
        .parcel_target = result.parcel_target,
        .score = result.score,
        .score_is_partial = result.score_is_partial,
        .score_totals = result.score_totals,
        .visible_life_stock = result.visible_life_stock,
        .damage_gauge = result.damage_gauge,
        .high_score_rank = result.high_score_rank,
        .time_trial_record_improved = result.time_trial_record_improved,
        .unlocked_next_route = result.unlocked_next_route,
    };
}

pub fn previewDescendingHighScoreRank(entries: []const high_score.Entry, score: u32) ?usize {
    const visible = @min(high_score.visible_entry_count, entries.len);
    var rank: usize = 0;
    while (rank < visible and score <= entries[rank].score and entries[rank].isActive()) : (rank += 1) {}
    if (rank >= visible) return null;
    return rank;
}

pub fn commitIfNeeded(state: anytype, result: Result) !Result {
    if (result.persistence == .none) return result;
    var updated = result;
    switch (result.persistence) {
        .none => return result,
        .completed => switch (result.completion_owner) {
            .postal_route_map => {
                updated.unlocked_next_route = try state.commitPostalRouteProgress();
            },
            .postal_final => {
                const entry = state.currentRunHighScoreEntry(result.score);
                const insert = state.high_score_tables.addArcade(state.allocator, entry);
                updated.high_score_mode = .postal;
                updated.high_score_rank = insert.rank;
                updated.unlocked_next_route = try state.commitPostalRouteProgress();
                try state.saveHighScoreTables();
            },
            .postal_failure,
            .challenge_failure,
            .time_trial_failure,
            .tutorial_failure,
            => unreachable,
            .challenge_completion => {
                const entry = state.currentRunHighScoreEntry(result.score);
                const insert = state.high_score_tables.addSurvival(state.allocator, entry);
                updated.high_score_mode = .challenge;
                updated.high_score_rank = insert.rank;
                try state.saveHighScoreTables();
            },
            .time_trial_completion => {
                const entry = state.currentRunHighScoreEntry(result.score);
                const insert = state.high_score_tables.addTimeTrial(
                    state.allocator,
                    state.active_frontend_level_index,
                    entry,
                    true,
                );
                updated.time_trial_record_improved = insert.improved;
                try state.saveHighScoreTables();
            },
            .tutorial_completion => {},
        },
        .failed => switch (result.completion_owner) {
            .postal_failure => {
                const entry = state.currentRunHighScoreEntry(result.score);
                const insert = state.high_score_tables.addArcade(state.allocator, entry);
                updated.high_score_mode = .postal;
                updated.high_score_rank = insert.rank;
                try state.saveHighScoreTables();
            },
            .challenge_failure => {
                const entry = state.currentRunHighScoreEntry(result.score);
                const insert = state.high_score_tables.addSurvival(state.allocator, entry);
                updated.high_score_mode = .challenge;
                updated.high_score_rank = insert.rank;
                try state.saveHighScoreTables();
            },
            .postal_route_map,
            .postal_final,
            .challenge_completion,
            .time_trial_completion,
            .tutorial_completion,
            => unreachable,
            .time_trial_failure, .tutorial_failure => {},
        },
    }
    updated.persistence = .none;
    return updated;
}

pub fn commitPendingIfNeeded(state: anytype) !void {
    const result = state.pending_run_result orelse return;
    if (result.persistence == .none) return;
    state.pending_run_result = try commitIfNeeded(state, result);
}

pub fn resetCompletionScreenReveal(state: anytype) void {
    const result = state.pending_run_result orelse {
        state.completion_screen_reveal_progress = 0.0;
        return;
    };
    const result_summary = summary(result);
    state.completion_screen_reveal_progress = if (result.outcome == .completed) 0.0 else frontend_completion_screen.revealTarget(result_summary);
}

pub fn completionScreenActive(state: anytype) bool {
    return state.pending_run_result != null and
        (state.game_phase == .completion_screen or completionScreenOverlayActive(state));
}

pub fn completionScreenOverlayActive(state: anytype) bool {
    return state.game_phase == .level and state.completion_overlay_active and state.pending_run_result != null;
}

pub fn completionScreenInteractive(state: anytype) bool {
    return state.game_phase == .completion_screen and
        state.pending_run_result != null and
        !state.frontend_transition.blocksInput();
}

pub fn stepCompletionScreenReveal(state: anytype) void {
    if (!completionScreenActive(state)) return;
    const result = state.pending_run_result orelse return;
    const target = frontend_completion_screen.revealTarget(summary(result));
    if (state.completion_screen_reveal_progress >= target) return;
    state.completion_screen_reveal_progress = clampF32(
        state.completion_screen_reveal_progress + frontend_completion_screen.reveal_step,
        0.0,
        target,
    );
}

pub fn completionBonusVisible(state: anytype, result: Result) bool {
    return frontend_completion_screen.bonusVisibleAtProgress(summary(result), state.completion_screen_reveal_progress);
}

pub fn completionContinueVisible(state: anytype) bool {
    const result = state.pending_run_result orelse return false;
    return frontend_completion_screen.continueVisibleAtProgress(summary(result), state.completion_screen_reveal_progress);
}

fn clampUsize(value: usize, low: usize, high: usize) usize {
    return @min(@max(value, low), high);
}

fn clampF32(value: f32, low: f32, high: f32) f32 {
    return @min(@max(value, low), high);
}
