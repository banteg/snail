const frontend_bridge = @import("../frontend/bridge.zig");
const run_result = @import("run_result.zig");

const PendingRunResult = run_result.Result;

pub fn ownerForAbandonActiveRun(
    state: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) frontend_bridge.OuterOwnerState {
    if (state.selected_level_record_persistent) {
        const owner = state.selectedReplayLaunchOwnerState() orelse state.saved_outer_owner;
        opcode.* = .destroy_return;
        return owner;
    }

    if (state.selectedReplayPlaybackActive()) {
        const owner = state.selectedReplayLaunchOwnerState() orelse frontend_bridge.outerOwnerStateMainMenu();
        // PORT(verified): when `app + 0x1066be9` is clear, BN `update_pause_menu` falls
        // through to completion state `2`. BN plus IDA then show `update_completion_screen`
        // state `2` destroying subgame, and on the Time Trial replay path
        // (`level_mode == FrontendLevelMode.time_trial`) reinitializing subgame without
        // using bridge state `0x1c`. `initialize_subgame` then rebuilds the route-map owner
        // from the preserved nonzero continuation selector, so transient route-map replay
        // abandon matches opcode `27`, not respawn-only `28`.
        opcode.* = .rebuild_return;
        return owner;
    }

    if (state.saved_outer_owner.owner == .challenge_setup_menu) {
        opcode.* = .rebuild_return;
        return frontend_bridge.outerOwnerStateChallengeSetupMenu();
    }

    opcode.* = .destroy_return;
    return state.saved_outer_owner;
}

pub fn ownerForRespawnActiveRun(
    state: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) ?frontend_bridge.OuterOwnerState {
    var previous_runner = state.level_runner orelse return null;
    previous_runner.flushPendingParcelDeliveries();
    state.pending_respawn_bridge_state = .{
        .frontend_mode = state.active_frontend_mode,
        .frontend_level_index = state.active_frontend_level_index,
        .runner = previous_runner,
    };
    // PORT(verified): ordinary respawn rebuild uses direct owner `0x1c`, not the
    // `0x1a/0x1b` saved-owner bridge family. Keep the existing effect endpoint but store
    // the direct selector as authoritative bridge state.
    opcode.* = .rebuild_clear_replay_return;
    state.subgame_rebuild_selector = 0x1c;
    return frontend_bridge.outerOwnerStateResumeActiveRun();
}

pub fn ownerForPendingRunResult(
    state: anytype,
    result: PendingRunResult,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) frontend_bridge.OuterOwnerState {
    const selected_level_record_result_opcode = state.postRunSelectedLevelRecordOpcode(result.outcome);
    const selected_level_record_return = state.selected_level_record_source != null;
    const outer_return_target = postRunSelectedLevelRecordOuterReturnTargetOverride(state, result) orelse result.outer_return_target;
    return switch (outer_return_target) {
        .main_menu => blk: {
            opcode.* = .destroy_return;
            break :blk frontend_bridge.outerOwnerStateMainMenu();
        },
        .new_game_menu => blk: {
            opcode.* = .destroy_return;
            break :blk frontend_bridge.outerOwnerStateNewGameMenu(frontend_bridge.newGameMenuItemForBridgeMode(result.mode));
        },
        .challenge_setup_menu => blk: {
            opcode.* = if (selected_level_record_return)
                selected_level_record_result_opcode
            else
                .rebuild_return;
            break :blk frontend_bridge.outerOwnerStateChallengeSetupMenu();
        },
        .postal_route_map => blk: {
            opcode.* = .destroy_return;
            break :blk frontend_bridge.outerOwnerStateRouteMap(.{
                .mode = .postal,
                .screen_mode = .post_completion_exit,
            });
        },
        .time_trial_route_map => blk: {
            // PORT(verified): `update_galaxy` only seeds `selected_level_record_active`,
            // while `update_subgoldy` uses state `0x1b` unless the separate persistent lane
            // is armed. The current Zig selected-level launch path is therefore transient
            // until the native persistent writer is recovered.
            opcode.* = selected_level_record_result_opcode;
            break :blk frontend_bridge.outerOwnerStateRouteMap(.{
                .mode = .time_trial,
                .screen_mode = frontend_bridge.defaultRouteMapScreenMode(.time_trial),
                .start_route_override = if (selected_level_record_return)
                    state.active_frontend_level_index
                else
                    null,
            });
        },
        .high_scores_menu => blk: {
            opcode.* = selected_level_record_result_opcode;
            break :blk frontend_bridge.outerOwnerStateHighScores(if (state.selected_level_record_source) |source|
                switch (source) {
                    .postal => .postal,
                    .challenge => .challenge,
                    .challenge_setup => result.high_score_mode orelse .challenge,
                    .completion => result.high_score_mode orelse .postal,
                }
            else
                result.high_score_mode orelse .postal);
        },
        .replay_current_level => blk: {
            if (state.selected_level_record_override) |record| {
                opcode.* = .rebuild_return;
                break :blk frontend_bridge.outerOwnerStateReplay(.{
                    .mode = record.mode,
                    .level_index = record.level_index,
                    .selected_level_record_override = record,
                    .selected_level_record_launch = if (state.selected_level_record_source) |source|
                        .{
                            .source = source,
                            .persistent = state.selected_level_record_persistent,
                            .outer_return_target = state.selectedReplayLaunchOuterReturnTarget() orelse frontend_bridge.defaultSelectedLevelRecordLaunchOuterReturnTarget(source),
                        }
                    else
                        null,
                });
            }
            if (result.mode) |mode| {
                opcode.* = .rebuild_return;
                break :blk frontend_bridge.outerOwnerStateReplay(.{
                    .mode = mode,
                    .level_index = state.active_frontend_level_index,
                });
            }
            opcode.* = .destroy_return;
            break :blk frontend_bridge.outerOwnerStateMainMenu();
        },
        .thanks_screen => blk: {
            opcode.* = .init_thanks_screen;
            break :blk frontend_bridge.outerOwnerStateThanksScreen();
        },
    };
}

pub fn transitionClearsSelectedReplayContext(
    state: anytype,
    opcode: frontend_bridge.OuterBridgeOpcode,
    next_owner: frontend_bridge.OuterOwnerState,
) bool {
    if (opcode == .rebuild_clear_replay_return) return true;
    if (state.selected_level_record_source == null) return false;
    return switch (next_owner.owner) {
        .route_map, .high_scores_menu => true,
        else => false,
    };
}

fn postRunSelectedLevelRecordOuterReturnTargetOverride(state: anytype, result: PendingRunResult) ?frontend_bridge.OuterReturnTarget {
    const source = state.selected_level_record_source orelse return null;
    if (state.selected_level_record_persistent) return null;

    return switch (source) {
        .postal => switch (result.outcome) {
            // PORT(verified): `update_subgoldy_resurrect` only takes the postal
            // `0x1b` branch when app byte `+0x30d` is set, and `complete_subgame`
            // only seeds that high-score continuation flag when
            // `selected_level_record_active == 0`. Transient selected-record
            // postal failures therefore keep the native `0x1a -> owner 2`
            // New Game return instead of jumping back to the postal high-score
            // browser.
            .failed => .new_game_menu,
            .completed => null,
        },
        .challenge, .challenge_setup, .completion => null,
    };
}
