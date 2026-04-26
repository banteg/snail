const frontend = @import("../frontend.zig");
const frontend_bridge = @import("../frontend/bridge.zig");
const gameplay = @import("../gameplay.zig");
const high_score = @import("../high_score.zig");

const FrontendLevelMode = frontend.FrontendLevelMode;

pub fn entryForSource(state: anytype, source: frontend_bridge.SelectedLevelRecordSource) ?*const high_score.Entry {
    return switch (source) {
        .postal => |index| if (index < state.high_score_tables.postal.len) &state.high_score_tables.postal[index] else null,
        .challenge => |index| if (index < state.high_score_tables.challenge.len) &state.high_score_tables.challenge[index] else null,
        .challenge_setup => &state.high_score_tables.challenge_setup_replay,
        .completion => |index| if (index < state.high_score_tables.completion.len) &state.high_score_tables.completion[index] else null,
    };
}

pub fn entry(state: anytype) ?*const high_score.Entry {
    const source = state.selected_level_record_source orelse return null;
    return entryForSource(state, source);
}

pub fn playbackActive(state: anytype) bool {
    if (state.selected_replay_cache) |replay| return replay.samples.len != 0;
    const replay_entry = entry(state) orelse return false;
    return replay_entry.replaySampleCount() != 0;
}

pub fn postRunOpcode(state: anytype, outcome: anytype) frontend_bridge.OuterBridgeOpcode {
    const source = state.selected_level_record_source orelse return .destroy_return;
    if (state.selected_level_record_persistent) return .destroy_return;

    return switch (source) {
        // PORT(verified): `update_galaxy` / `update_challenge_setup_screen` seed the active
        // selected-level-record lane without touching the separate persistent bit, and the
        // corresponding `update_subgoldy` post-run completion path uses state `0x1b` for
        // those transient returns. BN plus IDA now also show `complete_subgame` only arms
        // app byte `+0x30d` while `selected_level_record_active == 0`, so transient postal
        // replay final loss keeps the native `0x1a -> owner 2` destroy-return override
        // instead of reusing the postal high-score continuation lane.
        .completion, .challenge, .challenge_setup => .rebuild_return,
        .postal => switch (outcome) {
            .completed => .rebuild_return,
            .failed => .destroy_return,
        },
    };
}

pub fn directiveForDecodedReplay(replay: *const high_score.DecodedReplay, runtime_track_index: usize) gameplay.ReplayDirective {
    if (replay.samples.len == 0) return .{};
    const sample = replay.sampleAt(runtime_track_index) orelse return .{ .active = true };
    return .{
        .active = true,
        .lateral_world_x = high_score.mathType16To32(sample.lateral, 16.0),
        .raw_flag_bits = sample.flags,
    };
}

pub fn directiveForRunner(state: anytype, runner: *const gameplay.Runner) gameplay.ReplayDirective {
    const replay = state.selected_replay_cache orelse return .{};
    return directiveForDecodedReplay(&replay, runner.runtime_track_index);
}

pub fn launchOuterReturnTarget(state: anytype) ?frontend_bridge.OuterReturnTarget {
    if (state.saved_replay_return_outer_owner) |saved_state| {
        return frontend_bridge.outerReturnTargetForSavedReplayReturnOuterOwner(saved_state);
    }
    if (state.selected_level_record_outer_return_target) |target| return target;
    const source = state.selected_level_record_source orelse return null;
    return frontend_bridge.defaultSelectedLevelRecordLaunchOuterReturnTarget(source);
}

pub fn launchMode(state: anytype) ?FrontendLevelMode {
    if (state.selected_level_record_override) |record| return record.mode;
    if (state.active_frontend_mode) |mode| return mode;
    const source = state.selected_level_record_source orelse return null;
    return switch (source) {
        .postal => .postal,
        .challenge, .challenge_setup => .challenge,
        .completion => .time_trial,
    };
}

pub fn launchOwnerState(state: anytype) ?frontend_bridge.OuterOwnerState {
    const source = state.selected_level_record_source orelse return null;
    const mode = launchMode(state) orelse return null;
    if (state.saved_replay_return_outer_owner) |return_state| {
        return switch (return_state) {
            .new_game_menu => frontend_bridge.outerOwnerStateNewGameMenu(frontend_bridge.newGameMenuItemForBridgeMode(mode)),
            .high_scores_menu => frontend_bridge.outerOwnerStateHighScores(switch (source) {
                .challenge => .challenge,
                else => .postal,
            }),
        };
    }
    const outer_return_target = launchOuterReturnTarget(state) orelse return null;
    return frontend_bridge.outerOwnerStateForSelectedReplayLaunch(mode, source, outer_return_target, state.active_frontend_level_index);
}

pub fn outerOwnerForMarker(
    state: anytype,
    opcode: *frontend_bridge.OuterBridgeOpcode,
) ?frontend_bridge.OuterOwnerState {
    const source = state.selected_level_record_source orelse return null;
    const record = state.selected_level_record_override orelse blk: {
        const replay_entry = entryForSource(state, source) orelse return null;
        break :blk frontend_bridge.SelectedLevelRecordOverride.fromHighScoreEntry(replay_entry) orelse return null;
    };
    // PORT(verified): `update_subgoldy` consumes selected-record replay flag bit `0x8`
    // directly. When it hits, Windows writes `app + 0x1b8 = 0x1a`,
    // `app + 0x1bc = 10`, sets app byte `+0x30c = 1`, and starts the
    // front-end fade. State `10` is the front-end subgame-init owner, so
    // this marker loops back into the current replay rather than returning
    // to the launch surface.
    opcode.* = .destroy_return;
    return frontend_bridge.outerOwnerStateReplay(.{
        .mode = record.mode,
        .level_index = record.level_index,
        .selected_level_record_override = record,
        .selected_level_record_launch = .{
            .source = source,
            .persistent = state.selected_level_record_persistent,
            .outer_return_target = launchOuterReturnTarget(state) orelse frontend_bridge.defaultSelectedLevelRecordLaunchOuterReturnTarget(source),
        },
    });
}
