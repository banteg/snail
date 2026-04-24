const rl = @import("raylib");

const app = @import("../app.zig");
const config = @import("../config.zig");
const ui = @import("../ui.zig");

pub const Context = struct {
    runtime_config: *config.Blob,
    window_size: app.WindowSize,
};

pub const ViewContext = struct {
    mouse_local_override: ?app.MouseLocalOverride,
};

pub fn context(state: anytype) Context {
    return .{
        .runtime_config = &state.runtime_config,
        .window_size = state.window_size,
    };
}

pub fn viewContext(state: anytype) ViewContext {
    return .{
        .mouse_local_override = state.mouse_local_override,
    };
}

// PORT(verified): the original window bootstrap falls back to a 640x480 client area
// in windowed mode, while its fullscreen presets are also all 4:3.
// Evidence: sub_4119d0.
pub fn screenWidth() i32 {
    return rl.getScreenWidth();
}

pub fn screenHeight() i32 {
    return rl.getScreenHeight();
}

pub fn currentUiLayout() ui.VirtualLayout {
    return ui.virtualLayout(.{
        .x = 0.0,
        .y = 0.0,
        .width = @floatFromInt(screenWidth()),
        .height = @floatFromInt(screenHeight()),
    });
}

pub fn currentMouseLocal(window: ViewContext) ?rl.Vector2 {
    if (window.mouse_local_override) |mouse| {
        return .{ .x = mouse.x, .y = mouse.y };
    }
    const layout = currentUiLayout();
    const mouse_x = @as(f32, @floatFromInt(rl.getMouseX()));
    const mouse_y = @as(f32, @floatFromInt(rl.getMouseY()));
    if (!layout.containsScreenPoint(mouse_x, mouse_y)) return null;
    return layout.unmapPoint(mouse_x, mouse_y);
}

pub fn toggleFullscreenPreference(window: Context) void {
    window.runtime_config.setFullscreenEnabled(!window.runtime_config.fullscreenEnabled());
    syncFullscreenPreference(window);
}

pub fn syncFullscreenPreference(window: Context) void {
    const want_fullscreen = window.runtime_config.fullscreenEnabled();
    const is_fullscreen = rl.isWindowFullscreen();
    if (want_fullscreen == is_fullscreen) return;

    rl.toggleFullscreen();
    if (!want_fullscreen) {
        rl.setWindowSize(window.window_size.width, window.window_size.height);
    }
}
