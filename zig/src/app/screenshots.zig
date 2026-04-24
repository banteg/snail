const std = @import("std");
const rl = @import("raylib");
const render_phase = @import("render_phase.zig");

pub const Request = struct {
    relative_path_z: [:0]u8,
    exit_after_capture: bool,

    pub fn deinit(self: *Request, allocator: std.mem.Allocator) void {
        allocator.free(self.relative_path_z);
    }
};

pub fn maybeQueueAuto(state: anytype) !void {
    const auto_screenshot = state.auto_screenshot orelse return;
    if (state.auto_screenshot_taken) return;
    if (state.game_phase != auto_screenshot.phase) return;
    if (state.game_phase_ticks < auto_screenshot.tick) return;

    state.auto_screenshot_taken = true;
    try queue(state, true);
}

pub fn queue(state: anytype, exit_after_capture: bool) !void {
    if (state.pending_screenshot != null) return;

    state.frame_capture_index += 1;
    const relative_path = try std.fmt.allocPrint(
        state.allocator,
        "{s}/snail-{s}-{s}-{d:0>6}-{d:0>3}.png",
        .{
            state.screenshot_dir,
            @tagName(state.command),
            @tagName(state.game_phase),
            state.game_phase_ticks,
            state.frame_capture_index,
        },
    );
    errdefer state.allocator.free(relative_path);
    const relative_path_z = try state.allocator.dupeZ(u8, relative_path);
    defer state.allocator.free(relative_path);
    errdefer state.allocator.free(relative_path_z);

    state.pending_screenshot = .{
        .relative_path_z = relative_path_z,
        .exit_after_capture = exit_after_capture,
    };
}

pub fn flushQueued(state: anytype) !void {
    var request = state.pending_screenshot orelse return;
    state.pending_screenshot = null;
    defer request.deinit(state.allocator);

    const use_frontend_canvas = state.command == .game and render_phase.frontendUsesCanvas(state) and state.frontend_canvas != null;
    var screenshot = if (use_frontend_canvas)
        try rl.loadImageFromTexture(state.frontend_canvas.?.texture)
    else
        try rl.loadImageFromScreen();
    defer screenshot.unload();
    if (use_frontend_canvas) {
        screenshot.flipVertical();
    }
    if (!rl.exportImage(screenshot, request.relative_path_z)) {
        return error.ScreenshotExportFailed;
    }
    std.log.info("captured screenshot {s}", .{request.relative_path_z});

    if (request.exit_after_capture) {
        state.should_exit = true;
    }
}
