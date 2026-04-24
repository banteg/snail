const background = @import("../background.zig");
const subgame_camera = @import("subgame_camera.zig");

pub const default_light_streak_camera = background.LightStreakCamera{
    .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    .right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    .forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    .fov_degrees = 38.0,
};

pub fn usesGameplayBackdrop(state: anytype) bool {
    return switch (state.game_phase) {
        .pause_menu => true,
        .options_menu => state.options_return_phase == .pause_menu,
        .exit_prompt => state.exit_prompt_return_phase == .pause_menu,
        else => false,
    };
}

pub fn lightStreaksVisible(state: anytype) bool {
    if (usesGameplayBackdrop(state)) return true;
    return switch (state.game_phase) {
        .intro, .credits, .level => true,
        else => false,
    };
}

pub fn lightStreakCamera(state: anytype) background.LightStreakCamera {
    if (lightStreaksVisible(state) and state.subgame_camera.source != .identity) {
        const transform = subgame_camera.normalizeTransform(subgame_camera.transformFromMatrix(state.subgame_camera.shared_matrix));
        return .{
            .position = transform.position,
            .right = transform.right,
            .up = transform.up,
            .forward = transform.forward,
            .fov_degrees = default_light_streak_camera.fov_degrees,
        };
    }
    return default_light_streak_camera;
}

pub fn frontendUsesCanvas(state: anytype) bool {
    if (usesGameplayBackdrop(state)) return false;
    return switch (state.game_phase) {
        .main_menu,
        .new_game_menu,
        .challenge_setup_menu,
        .options_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .thanks_screen,
        .help,
        => true,
        .boot, .intro, .credits, .pause_menu, .level => false,
    };
}
