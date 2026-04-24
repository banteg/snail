const frontend_bridge = @import("../frontend/bridge.zig");
const frontend_flow = @import("frontend_flow.zig");

pub fn cardIsOpen(state: anytype) bool {
    return state.route_map_open_index != null;
}

// PORT(verified): `open_galaxy_route` stores the active route index at `this + 69504`,
// while `close_galaxy_route` clears that slot back to `-1`. Model the open-card route
// separately instead of assuming the saved/default route is always the open one.
pub fn currentOpenIndex(state: anytype) ?usize {
    return state.route_map_open_index;
}

// PORT(verified): the late `update_galaxy` close-card branch only fires when the
// open-route flag is set and the authored route count is greater than `1`
// (`dword_4DF9B8 > 1`). Preserve that gate so the first available route stays pinned
// open instead of letting the user dismiss the card into an empty Star Map.
pub fn canCloseCard(state: anytype) bool {
    if (!cardIsOpen(state)) return false;
    if (!frontend_bridge.routeMapAllowsRouteSwitching(state.route_map_screen_mode)) return false;
    const mode = state.frontend_route_mode orelse return false;
    return state.availableFrontendRouteLimit(mode) > 1;
}

pub fn openCard(state: anytype, route_index: usize) !void {
    state.route_map_open_index = route_index;
    state.route_map_hover_state = .none;
    state.route_map_hovered_index = null;
    state.frontend_route_index = route_index;
    syncHighlightTargets(state);
    try state.reloadFrontendRouteLevel();
    state.route_menu_action_index = frontend_flow.routeMenuActionIndexForAction(state, .play) orelse 0;
}

pub fn closeCard(state: anytype) void {
    state.route_map_open_index = null;
    state.route_map_hover_state = .none;
    state.route_map_hovered_index = null;
    state.route_menu_action_index = 0;
    syncHighlightTargets(state);
}

pub fn resetHighlightAnimations(state: anytype) void {
    @memset(&state.route_map_route_highlight_alpha, 0.0);
    @memset(&state.route_map_route_highlight_target, 0.0);
}

// PORT(verified): `update_galaxy` ticks each route entry through `sub_409BD0`, which
// eases the current highlight alpha at `+40` toward the target at `+44` with a `0.1`
// step. The target is `1.0` for the hovered route in hover state `2`, otherwise for the
// open route while the card is up.
pub fn syncHighlightTargets(state: anytype) void {
    @memset(&state.route_map_route_highlight_target, 0.0);
    const highlighted_route_index = switch (state.route_map_hover_state) {
        .route => state.route_map_hovered_index,
        .card, .none => currentOpenIndex(state),
    } orelse return;
    if (highlighted_route_index < state.route_map_route_highlight_target.len) {
        state.route_map_route_highlight_target[highlighted_route_index] = 1.0;
    }
}

pub fn stepHighlightAnimations(state: anytype) void {
    for (1..state.route_map_route_highlight_alpha.len) |route_index| {
        const current = state.route_map_route_highlight_alpha[route_index];
        const target = state.route_map_route_highlight_target[route_index];
        state.route_map_route_highlight_alpha[route_index] = current + (target - current) * 0.1;
    }
}
