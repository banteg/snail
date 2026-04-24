const rl = @import("raylib");

const audio = @import("audio.zig");
const frontend_activation = @import("../frontend/activation.zig");
const frontend_flow = @import("frontend_flow.zig");

const frontend_activation_delay_step: f32 = 1.0 / 12.0;

pub fn setHoverTarget(state: anytype, target: ?frontend_activation.HoverTarget) void {
    if (state.hovered_frontend_target == target) return;
    state.hovered_frontend_target = target;
    if (target != null) {
        state.keyboard_frontend_focus_visible = false;
        audio.playFrontendHoverSound(state);
    }
}

pub fn noteKeyboardNavigation(state: anytype) void {
    state.keyboard_frontend_focus_visible = true;
}

pub fn activeButtonTarget(state: anytype) ?frontend_activation.HoverTarget {
    if (state.pending_frontend_activation) |pending| {
        return pending.target;
    }
    return state.hovered_frontend_target;
}

pub fn buttonHot(state: anytype, target: frontend_activation.HoverTarget, fallback_selected: bool) bool {
    if (activeButtonTarget(state)) |active_target| {
        return active_target == target;
    }
    return state.keyboard_frontend_focus_visible and fallback_selected;
}

pub fn queueActivation(state: anytype, action: frontend_activation.QueuedAction) void {
    if (state.pending_frontend_activation != null) return;
    audio.playFrontendSelectSound(state);
    const requires_fade = frontend_activation.queuedActivationRequiresFade(action);
    if (requires_fade) {
        state.frontend_transition.beginOverlayFadeOut();
    }
    state.pending_frontend_activation = .{
        .action = action,
        .target = frontend_activation.queuedActivationTarget(action),
        .requires_fade = requires_fade,
    };
}

pub fn dispatchActivation(state: anytype, action: frontend_activation.QueuedAction) !void {
    switch (action) {
        .main_menu => |item| try frontend_flow.performMainMenuItem(state, item),
        .new_game_menu => |item| try frontend_flow.performNewGameMenuItem(state, item),
        .challenge_setup_menu => |item| try frontend_flow.performChallengeSetupMenuItem(state, item),
        .options_menu => |item| try frontend_flow.performOptionsMenuItem(state, item),
        .pause_menu => |item| try frontend_flow.performPauseMenuItem(state, item),
        .route_map_menu => |item| try frontend_flow.performRouteMenuAction(state, item),
        .help_menu => |item| try frontend_flow.performHelpMenuItem(state, item),
        .high_scores_menu => |item| try frontend_flow.performHighScoreMenuAction(state, item),
        .high_score_replay => |index| try frontend_flow.performHighScoreReplay(state, index),
        .post_level_high_scores => |item| try frontend_flow.performPostLevelHighScoreAction(state, item),
        .completion_screen => |item| try frontend_flow.performCompletionAction(state, item),
        .exit_prompt => |choice| try frontend_flow.performExitPromptChoice(state, choice),
    }
}

pub fn updatePendingActivation(state: anytype) !bool {
    if (state.pending_frontend_activation) |*pending| {
        pending.progress = @min(pending.progress + frontend_activation_delay_step, 1.0);
        const fade_ready = !pending.requires_fade or state.frontend_transition.state == .black_idle;
        if (pending.progress >= 0.999 and fade_ready) {
            const action = pending.action;
            const should_fade_in = pending.requires_fade and state.frontend_transition.state == .black_idle;
            state.pending_frontend_activation = null;
            try dispatchActivation(state, action);
            if (should_fade_in) {
                state.frontend_transition.completeHandoff();
            }
            return true;
        }
    }
    return false;
}

pub fn readPressedWidgetShortcutCode() ?u8 {
    // PORT(partial): this currently implements only the native text-input codes that
    // recovered widget shortcuts actually use in the shipped front-end: Escape (`11`),
    // Enter (`5` / `6`), and lowercase `o` (`111`).
    if (rl.isKeyPressed(.escape)) return 11;
    if (rl.isKeyPressed(.enter)) {
        return if (rl.isKeyDown(.left_control) or rl.isKeyDown(.right_control)) 6 else 5;
    }
    if (rl.isKeyPressed(.o)) return 111;
    return null;
}

pub fn shortcutActivationForCode(state: anytype, code: u8) ?frontend_activation.QueuedAction {
    return switch (state.game_phase) {
        .pause_menu => switch (code) {
            11 => .{ .pause_menu = .end_game },
            111 => .{ .pause_menu = .options },
            5, 6 => .{ .pause_menu = .@"resume" },
            else => null,
        },
        .high_scores_menu => if (state.high_score_screen_owner == .post_level_entry) switch (code) {
            11 => .{ .post_level_high_scores = .cancel },
            5, 6 => .{ .post_level_high_scores = .submit },
            else => null,
        } else null,
        else => null,
    };
}

pub fn handleWidgetShortcutInput(state: anytype) !bool {
    if (state.frontend_transition.blocksInput()) return false;
    if (state.pending_frontend_activation != null) return false;
    const code = readPressedWidgetShortcutCode() orelse return false;
    const action = shortcutActivationForCode(state, code) orelse return false;
    noteKeyboardNavigation(state);
    queueActivation(state, action);
    return true;
}
