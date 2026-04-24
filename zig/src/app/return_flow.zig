const frontend_activation = @import("../frontend/activation.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const level_loader = @import("level_loader.zig");
const outer_bridge = @import("outer_bridge.zig");

pub fn ownerForAbandonActiveRun(
    state: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) frontend_bridge.OuterOwnerState {
    return outer_bridge.ownerForAbandonActiveRun(state, opcode);
}

pub fn ownerForRespawnActiveRun(
    state: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) ?frontend_bridge.OuterOwnerState {
    return outer_bridge.ownerForRespawnActiveRun(state, opcode);
}

pub fn ownerForPendingRunResult(
    state: anytype,
    result: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) frontend_bridge.OuterOwnerState {
    return outer_bridge.ownerForPendingRunResult(state, result, opcode);
}

pub fn applyOuterBridgeTeardown(
    state: anytype,
    opcode: frontend_bridge.OuterBridgeOpcode,
    next_owner: frontend_bridge.OuterOwnerState,
) !void {
    state.active_frontend_mode = null;
    state.active_frontend_level_index = 0;
    if (outer_bridge.transitionClearsSelectedReplayContext(state, opcode, next_owner)) {
        try state.setSelectedLevelRecordContext(null, null);
    }
}

pub fn resumeActiveRunAfterRespawnBridge(state: anytype) !void {
    const bridge_state = state.pending_respawn_bridge_state orelse return;
    state.pending_respawn_bridge_state = null;

    state.active_frontend_mode = bridge_state.frontend_mode;
    state.active_frontend_level_index = bridge_state.frontend_level_index;
    try level_loader.reloadLevel(state);
    if (state.current_track_preview) |*loaded_track_preview| {
        if (state.level_runner) |*runner| {
            runner.* = bridge_state.runner;
            runner.applyRespawn(loaded_track_preview);
        }
    }
    state.level_prompt_queue.clear();
    try level_loader.syncActiveLevelSegment(state);
}

pub fn runOuterBridgeTransition(
    state: anytype,
    opcode: frontend_bridge.OuterBridgeOpcode,
    next_owner: frontend_bridge.OuterOwnerState,
) !void {
    state.subgame_rebuild_selector = @intFromEnum(opcode);
    try applyOuterBridgeTeardown(state, opcode, next_owner);
    state.current_outer_owner = next_owner;

    switch (next_owner.owner) {
        .main_menu => try state.enterGamePhase(.main_menu),
        .new_game_menu => {
            state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(next_owner.new_game_menu_item);
            try state.enterGamePhase(.new_game_menu);
        },
        .challenge_setup_menu => try state.enterChallengeSetupMenu(),
        .route_map => {
            state.start_route_index_override = next_owner.route_map.start_route_override;
            try state.enterRouteMapMenuWithScreenMode(next_owner.route_map.mode, next_owner.route_map.screen_mode);
        },
        .high_scores_menu => try state.enterHighScoreBrowseScreen(next_owner.high_score_mode),
        .replay_current_level => {
            try state.beginFrontendLevelPath(
                next_owner.replay.mode,
                next_owner.replay.level_index,
                next_owner.replay.selected_level_record_override,
                next_owner.replay.selected_level_record_launch,
            );
        },
        .thanks_screen => try state.enterGamePhase(.thanks_screen),
        .resume_active_run => try resumeActiveRunAfterRespawnBridge(state),
    }
}
