const std = @import("std");
const frontend = @import("frontend.zig");
const runtime_state = @import("runtime_state.zig");

pub const original_game_client_width = 640;
pub const original_game_client_height = 480;
pub const game_window_width = 1024;
pub const game_window_height = 768;
pub const debug_window_width = 1280;
pub const debug_window_height = 720;

pub const default_archive_path = "artifacts/bin/SnailMail.dat";
pub const default_screenshot_dir = "artifacts/screenshots";
pub const intro_background_path = "BACKGROUNDS/SPACERED.TXT";
pub const main_menu_background_path = "BACKGROUNDS/MENUBG.TXT";
pub const help_background_path = "BACKGROUNDS/HELP.TXT";
pub const route_map_background_path = "BACKGROUNDS/STARMAP.TXT";
pub const intro_script_path = "INTRO/INTRO.TXT";
pub const credits_script_path = "INTRO/CREDITS.TXT";
pub const intro_music_path = "MUSIC/INTROTEXT.OGG";
pub const default_texture_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";
pub const default_audio_path = "MUSIC/MAINMENU.OGG";
pub const default_model_path = "X/TURBO-BOBALONG-000.X2";
pub const default_object_path = "OBJECTS/FONT3D/_OBJECT.TXT";
pub const default_level_path = "LEVELS/TUTORIAL.TXT";

pub const AppCommand = enum {
    game,
    debug,
    smoke,
};

pub const AutoScreenshot = struct {
    phase: frontend.GamePhase,
    tick: u64,
};

pub const Options = struct {
    archive_path: []const u8 = default_archive_path,
    runtime_root_path: []const u8 = runtime_state.default_root_path,
    screenshot_dir: []const u8 = default_screenshot_dir,
    auto_screenshot: ?AutoScreenshot = null,
    fullscreen: bool = false,
    command: AppCommand = .game,
};

pub const WindowSize = struct {
    width: i32,
    height: i32,
};

pub fn parseArgs(allocator: std.mem.Allocator) !Options {
    var argv = std.ArrayList([]const u8).empty;
    defer argv.deinit(allocator);

    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    _ = args.skip();
    while (args.next()) |arg| {
        try argv.append(allocator, arg);
    }

    return parseArgsFromSlice(argv.items);
}

pub fn parseArgsFromSlice(args: []const []const u8) !Options {
    var options = Options{};

    var index: usize = 0;
    while (index < args.len) : (index += 1) {
        const arg = args[index];
        if (std.mem.eql(u8, arg, "--archive-path")) {
            index += 1;
            if (index >= args.len) return error.MissingArchivePath;
            options.archive_path = args[index];
            continue;
        }
        if (std.mem.eql(u8, arg, "--runtime-dir")) {
            index += 1;
            if (index >= args.len) return error.MissingRuntimeDir;
            options.runtime_root_path = args[index];
            continue;
        }
        if (std.mem.eql(u8, arg, "--screenshot-dir")) {
            index += 1;
            if (index >= args.len) return error.MissingScreenshotDir;
            options.screenshot_dir = args[index];
            continue;
        }
        if (std.mem.eql(u8, arg, "--screenshot-at")) {
            index += 1;
            if (index >= args.len) return error.MissingScreenshotSpec;
            options.auto_screenshot = try parseAutoScreenshot(args[index]);
            continue;
        }
        if (std.mem.eql(u8, arg, "--fullscreen")) {
            options.fullscreen = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "game")) {
            options.command = .game;
            continue;
        }
        if (std.mem.eql(u8, arg, "debug")) {
            options.command = .debug;
            continue;
        }
        if (std.mem.eql(u8, arg, "browser")) {
            if (options.command != .debug) return error.UnknownCommand;
            continue;
        }
        if (std.mem.eql(u8, arg, "smoke")) {
            options.command = .smoke;
            continue;
        }
        return error.UnknownCommand;
    }

    return options;
}

pub fn parseAutoScreenshot(spec: []const u8) !AutoScreenshot {
    const colon_index = std.mem.indexOfScalar(u8, spec, ':') orelse return error.InvalidScreenshotSpec;
    if (colon_index == 0 or colon_index + 1 >= spec.len) return error.InvalidScreenshotSpec;

    const phase = parseGamePhase(spec[0..colon_index]) orelse return error.InvalidScreenshotPhase;
    const tick = try std.fmt.parseUnsigned(u64, spec[colon_index + 1 ..], 10);
    return .{
        .phase = phase,
        .tick = tick,
    };
}

fn parseGamePhase(name: []const u8) ?frontend.GamePhase {
    inline for (std.meta.fields(frontend.GamePhase)) |field| {
        if (std.ascii.eqlIgnoreCase(name, field.name)) {
            return @field(frontend.GamePhase, field.name);
        }
    }
    return null;
}

// PORT(verified): the original window bootstrap falls back to a 640x480 client area
// in windowed mode, while its fullscreen presets are also all 4:3.
// Evidence: initialize_game_window_and_input.
pub fn defaultWindowSizeForCommand(command: AppCommand) WindowSize {
    return switch (command) {
        .game => .{ .width = game_window_width, .height = game_window_height },
        .debug, .smoke => .{ .width = debug_window_width, .height = debug_window_height },
    };
}

test "default window sizes split game and debug paths" {
    const game_size = defaultWindowSizeForCommand(.game);
    try std.testing.expectEqual(@as(i32, 1024), game_size.width);
    try std.testing.expectEqual(@as(i32, 768), game_size.height);

    const debug_size = defaultWindowSizeForCommand(.debug);
    try std.testing.expectEqual(@as(i32, 1280), debug_size.width);
    try std.testing.expectEqual(@as(i32, 720), debug_size.height);

    const smoke_size = defaultWindowSizeForCommand(.smoke);
    try std.testing.expectEqual(debug_size.width, smoke_size.width);
    try std.testing.expectEqual(debug_size.height, smoke_size.height);
}

test "parse args defaults to game shell" {
    const options = try parseArgsFromSlice(&.{});
    try std.testing.expectEqual(AppCommand.game, options.command);
    try std.testing.expectEqualStrings(default_archive_path, options.archive_path);
    try std.testing.expectEqualStrings(runtime_state.default_root_path, options.runtime_root_path);
    try std.testing.expectEqualStrings(default_screenshot_dir, options.screenshot_dir);
    try std.testing.expectEqual(@as(?AutoScreenshot, null), options.auto_screenshot);
    try std.testing.expectEqual(false, options.fullscreen);
}

test "parse args handles debug and smoke subcommands" {
    var options = try parseArgsFromSlice(&.{ "debug", "--archive-path", "custom.dat", "--runtime-dir", "tmp/snail-runtime", "--screenshot-dir", "artifacts/test-shots", "--screenshot-at", "intro:60", "--fullscreen" });
    try std.testing.expectEqual(AppCommand.debug, options.command);
    try std.testing.expectEqualStrings("custom.dat", options.archive_path);
    try std.testing.expectEqualStrings("tmp/snail-runtime", options.runtime_root_path);
    try std.testing.expectEqualStrings("artifacts/test-shots", options.screenshot_dir);
    try std.testing.expectEqual(frontend.GamePhase.intro, options.auto_screenshot.?.phase);
    try std.testing.expectEqual(@as(u64, 60), options.auto_screenshot.?.tick);
    try std.testing.expectEqual(true, options.fullscreen);

    options = try parseArgsFromSlice(&.{"smoke"});
    try std.testing.expectEqual(AppCommand.smoke, options.command);
}

test "parse args rejects unknown commands" {
    try std.testing.expectError(error.UnknownCommand, parseArgsFromSlice(&.{"weird"}));
    try std.testing.expectError(error.UnknownCommand, parseArgsFromSlice(&.{"browser"}));
}

test "parse auto screenshot validates phase and tick" {
    const capture = try parseAutoScreenshot("credits:120");
    try std.testing.expectEqual(frontend.GamePhase.credits, capture.phase);
    try std.testing.expectEqual(@as(u64, 120), capture.tick);

    try std.testing.expectError(error.InvalidScreenshotSpec, parseAutoScreenshot("intro"));
    try std.testing.expectError(error.InvalidScreenshotPhase, parseAutoScreenshot("weird:30"));
}
