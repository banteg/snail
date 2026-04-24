const std = @import("std");

const app = @import("../app.zig");
const background = @import("../background.zig");
const boot_assets = @import("boot_assets.zig");
const intro = @import("../intro.zig");
const loading_screen = @import("../loading_screen.zig");
const resource_store = @import("../resource_store.zig");

const credits_script_path = app.credits_script_path;

pub const Context = struct {
    allocator: std.mem.Allocator,
    resources: *resource_store.Store,
    credits_with_remake: bool,
    current_game_background: *?background.Loaded,
    current_game_background_runtime: *?background.Runtime,
    current_loading_screen: *?loading_screen.Loaded,
    current_text_script: *?intro.Loaded,
    boot: boot_assets.Context,
};

pub const ViewContext = struct {
    game_phase_ticks: u64,
    current_text_script: *const ?intro.Loaded,
};

pub fn context(state: anytype) Context {
    return .{
        .allocator = state.allocator,
        .resources = &state.resources,
        .credits_with_remake = state.credits_with_remake,
        .current_game_background = &state.current_game_background,
        .current_game_background_runtime = &state.current_game_background_runtime,
        .current_loading_screen = &state.current_loading_screen,
        .current_text_script = &state.current_text_script,
        .boot = boot_assets.context(state),
    };
}

pub fn viewContext(state: anytype) ViewContext {
    return .{
        .game_phase_ticks = state.game_phase_ticks,
        .current_text_script = &state.current_text_script,
    };
}

pub fn loadGameBackground(screen: Context, script_path: []const u8) !void {
    unloadGameBackground(screen);
    var loaded = if (boot_assets.takeBackground(screen.boot, script_path)) |preloaded|
        preloaded
    else
        try background.Loaded.loadByPath(screen.allocator, screen.resources, script_path);
    screen.current_game_background_runtime.* = background.Runtime.init(&loaded);
    screen.current_game_background.* = loaded;
}

pub fn unloadGameBackground(screen: Context) void {
    if (screen.current_game_background.*) |*loaded| {
        loaded.deinit();
        screen.current_game_background.* = null;
    }
    screen.current_game_background_runtime.* = null;
}

pub fn loadLoadingScreen(screen: Context) !void {
    unloadLoadingScreen(screen);
    screen.current_loading_screen.* = try loading_screen.Loaded.load(screen.resources);
}

pub fn unloadLoadingScreen(screen: Context) void {
    if (screen.current_loading_screen.*) |*loaded_screen| {
        loaded_screen.deinit();
        screen.current_loading_screen.* = null;
    }
}

pub fn loadTextScript(screen: Context, path: []const u8) !void {
    unloadTextScript(screen);
    screen.current_text_script.* = if (boot_assets.takeTextScript(screen.boot, path)) |loaded|
        loaded
    else
        try loadConfiguredTextScriptEntry(screen, path);
}

pub fn loadConfiguredTextScriptEntry(screen: Context, path: []const u8) !intro.Loaded {
    if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
        return try intro.loadByPathWithOptions(
            screen.allocator,
            screen.resources,
            path,
            .{ .add_remake_credit = screen.credits_with_remake },
        );
    }
    return try intro.loadByPath(screen.allocator, screen.resources, path);
}

pub fn unloadTextScript(screen: Context) void {
    if (screen.current_text_script.*) |*script| {
        script.deinit(screen.allocator);
        screen.current_text_script.* = null;
    }
}

pub fn currentTextScriptDurationTicks(screen: ViewContext) ?u64 {
    const script = screen.current_text_script.* orelse return null;
    return script.durationTicks();
}

pub fn currentTextScriptProgress(screen: ViewContext) ?f32 {
    const script = screen.current_text_script.* orelse return null;
    return script.progressForTicks(screen.game_phase_ticks);
}

pub fn currentTextScript(screen: ViewContext) ?*const intro.Loaded {
    if (screen.current_text_script.*) |*script| {
        return script;
    }
    return null;
}
