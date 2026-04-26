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
pub const thanks_screen_background_path = "BACKGROUNDS/SPLASH.TXT";
pub const route_map_logo_texture_path = "GALAXY/SPACEMAPLOGO.TGA";
pub const route_map_border_texture_path = "GALAXY/BORDERSPACEMAP.TGA";
pub const route_map_galaxy_select_texture_path = "GALAXY/GALAXYSELECT.TGA";
pub const route_map_level_select_texture_path = "GALAXY/LEVELSELECT.TGA";
pub const route_map_level_star_texture_path = "GALAXY/LEVELSTAR.TGA";
pub const route_map_line_texture_path = "GALAXY/LINE.TGA";
pub const route_map_line_star_texture_path = "GALAXY/LINESTAR.TGA";
pub const route_map_galaxy_texture_paths = [_][]const u8{
    "GALAXY/GALAXY000.TGA",
    "GALAXY/GALAXY001.TGA",
    "GALAXY/GALAXY002.TGA",
    "GALAXY/GALAXY003.TGA",
    "GALAXY/GALAXY004.TGA",
    "GALAXY/GALAXY005.TGA",
    "GALAXY/GALAXY006.TGA",
    "GALAXY/GALAXY007.TGA",
    "GALAXY/GALAXY008.TGA",
    "GALAXY/GALAXY009.TGA",
};
pub const frontend_cursor_texture_path = "SPRITES/MOUSE.TGA";
pub const widget_border_texture_path = "SPRITES/BORDER.TGA";
pub const completion_parcel_icon_texture_path = "SPRITES/PARCELICON.TGA";
pub const frontend_highlight_sound_path = "SFX2/HIGHLIGHT.OGG";
pub const frontend_select_sound_path = "SFX2/SELECT.OGG";
pub const slider_less_texture_path = "SPRITES/LESS.TGA";
pub const slider_less_hover_texture_path = "SPRITES/LESSHOVER.TGA";
pub const slider_more_texture_path = "SPRITES/MORE.TGA";
pub const slider_more_hover_texture_path = "SPRITES/MOREHOVER.TGA";
pub const slider_bar_texture_path = "SPRITES/SLIDERBAR.TGA";
pub const slider_bar_full_texture_path = "SPRITES/SLIDERBARFULL.TGA";
pub const galaxy_names_path = "GALAXY/_GALAXY.TXT";
pub const intro_script_path = "INTRO/INTRO.TXT";
pub const credits_script_path = "INTRO/CREDITS.TXT";
pub const intro_music_path = "MUSIC/INTROTEXT.OGG";
pub const default_texture_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";
pub const default_audio_path = "MUSIC/MAINMENU.OGG";
pub const default_model_path = "X/TURBO-MOVE-000.X2";
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

pub const MouseLocalOverride = struct {
    x: f32,
    y: f32,
};

pub const Options = struct {
    archive_path: []const u8 = default_archive_path,
    runtime_root_path: []const u8 = runtime_state.default_root_path,
    screenshot_dir: []const u8 = default_screenshot_dir,
    auto_screenshot: ?AutoScreenshot = null,
    mouse_local_override: ?MouseLocalOverride = null,
    start_phase: ?frontend.GamePhase = null,
    start_level_intro: bool = false,
    auto_dismiss_click_start: bool = false,
    start_route_index: ?usize = null,
    debug_start_level_path: ?[]const u8 = null,
    debug_start_row: ?f32 = null,
    debug_start_lane: ?f32 = null,
    pause_context: bool = false,
    timeout_seconds: ?u32 = null,
    window_size_override: ?WindowSize = null,
    fullscreen: bool = false,
    hidden_window: bool = false,
    credits_with_remake: bool = true,
    debug_mode: ?[]const u8 = null,
    command: AppCommand = .game,
};

pub const WindowSize = struct {
    width: i32,
    height: i32,
};

pub fn parseArgs(allocator: std.mem.Allocator, args_source: std.process.Args) !Options {
    var argv = std.ArrayList([]const u8).empty;
    defer argv.deinit(allocator);

    var args = try args_source.iterateAllocator(allocator);
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
        if (std.mem.eql(u8, arg, "--mouse-local")) {
            index += 1;
            if (index >= args.len) return error.MissingMouseLocal;
            options.mouse_local_override = try parseMouseLocal(args[index]);
            continue;
        }
        if (std.mem.eql(u8, arg, "--start-phase")) {
            index += 1;
            if (index >= args.len) return error.MissingStartPhase;
            options.start_phase = parseGamePhase(args[index]) orelse return error.InvalidStartPhase;
            continue;
        }
        if (std.mem.eql(u8, arg, "--start-level-intro")) {
            options.start_level_intro = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--auto-dismiss-click-start")) {
            options.auto_dismiss_click_start = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--start-route-index")) {
            index += 1;
            if (index >= args.len) return error.MissingStartRouteIndex;
            options.start_route_index = try parseRouteIndex(args[index]);
            continue;
        }
        if (std.mem.eql(u8, arg, "--debug-start-level")) {
            index += 1;
            if (index >= args.len) return error.MissingDebugStartLevel;
            options.debug_start_level_path = args[index];
            continue;
        }
        if (std.mem.eql(u8, arg, "--debug-start-row")) {
            index += 1;
            if (index >= args.len) return error.MissingDebugStartRow;
            options.debug_start_row = try parseDebugStartFloat(args[index], error.InvalidDebugStartRow);
            continue;
        }
        if (std.mem.eql(u8, arg, "--debug-start-lane")) {
            index += 1;
            if (index >= args.len) return error.MissingDebugStartLane;
            options.debug_start_lane = try parseDebugStartFloat(args[index], error.InvalidDebugStartLane);
            continue;
        }
        if (std.mem.eql(u8, arg, "--pause-context")) {
            options.pause_context = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--timeout-seconds")) {
            index += 1;
            if (index >= args.len) return error.MissingTimeoutSeconds;
            options.timeout_seconds = try parseTimeoutSeconds(args[index]);
            continue;
        }
        if (std.mem.eql(u8, arg, "--window-size")) {
            index += 1;
            if (index >= args.len) return error.MissingWindowSize;
            options.window_size_override = try parseWindowSize(args[index]);
            continue;
        }
        if (std.mem.eql(u8, arg, "--fullscreen")) {
            options.fullscreen = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--hidden-window")) {
            options.hidden_window = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--vanilla-credits")) {
            options.credits_with_remake = false;
            continue;
        }
        if (std.mem.eql(u8, arg, "--debug-mode")) {
            index += 1;
            if (index >= args.len) return error.MissingDebugMode;
            options.debug_mode = args[index];
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

    if (options.hidden_window and options.timeout_seconds == null) {
        return error.HiddenWindowRequiresTimeout;
    }
    if (options.debug_start_level_path != null and options.debug_start_row == null) {
        return error.MissingDebugStartRow;
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

fn parseMouseLocal(spec: []const u8) !MouseLocalOverride {
    const sep_index = std.mem.indexOfScalar(u8, spec, ',') orelse return error.InvalidMouseLocal;
    if (sep_index == 0 or sep_index + 1 >= spec.len) return error.InvalidMouseLocal;

    return .{
        .x = try std.fmt.parseFloat(f32, spec[0..sep_index]),
        .y = try std.fmt.parseFloat(f32, spec[sep_index + 1 ..]),
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

fn parseWindowSize(spec: []const u8) !WindowSize {
    const sep_index = std.mem.indexOfScalar(u8, spec, 'x') orelse
        std.mem.indexOfScalar(u8, spec, 'X') orelse
        return error.InvalidWindowSize;
    if (sep_index == 0 or sep_index + 1 >= spec.len) return error.InvalidWindowSize;

    const width = try std.fmt.parseInt(i32, spec[0..sep_index], 10);
    const height = try std.fmt.parseInt(i32, spec[sep_index + 1 ..], 10);
    if (width <= 0 or height <= 0) return error.InvalidWindowSize;

    return .{
        .width = width,
        .height = height,
    };
}

fn parseTimeoutSeconds(spec: []const u8) !u32 {
    const seconds = try std.fmt.parseUnsigned(u32, spec, 10);
    if (seconds == 0) return error.InvalidTimeoutSeconds;
    return seconds;
}

fn parseRouteIndex(spec: []const u8) !usize {
    const route_index = try std.fmt.parseUnsigned(usize, spec, 10);
    if (route_index == 0) return error.InvalidStartRouteIndex;
    return route_index;
}

fn parseDebugStartFloat(spec: []const u8, invalid_error: anyerror) !f32 {
    const value = std.fmt.parseFloat(f32, spec) catch return invalid_error;
    if (!std.math.isFinite(value)) return invalid_error;
    return value;
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
    try std.testing.expectEqual(@as(?MouseLocalOverride, null), options.mouse_local_override);
    try std.testing.expectEqual(@as(?frontend.GamePhase, null), options.start_phase);
    try std.testing.expectEqual(false, options.start_level_intro);
    try std.testing.expectEqual(false, options.auto_dismiss_click_start);
    try std.testing.expectEqual(@as(?usize, null), options.start_route_index);
    try std.testing.expectEqual(@as(?[]const u8, null), options.debug_start_level_path);
    try std.testing.expectEqual(@as(?f32, null), options.debug_start_row);
    try std.testing.expectEqual(@as(?f32, null), options.debug_start_lane);
    try std.testing.expectEqual(false, options.pause_context);
    try std.testing.expectEqual(@as(?u32, null), options.timeout_seconds);
    try std.testing.expectEqual(@as(?WindowSize, null), options.window_size_override);
    try std.testing.expectEqual(false, options.fullscreen);
    try std.testing.expectEqual(false, options.hidden_window);
    try std.testing.expectEqual(true, options.credits_with_remake);
    try std.testing.expectEqual(@as(?[]const u8, null), options.debug_mode);
}

test "parse args handles debug and smoke subcommands" {
    var options = try parseArgsFromSlice(&.{ "debug", "--archive-path", "custom.dat", "--runtime-dir", "tmp/snail-runtime", "--screenshot-dir", "artifacts/test-shots", "--screenshot-at", "intro:60", "--window-size", "640x480", "--fullscreen", "--hidden-window", "--timeout-seconds", "5", "--vanilla-credits", "--debug-mode", "models" });
    try std.testing.expectEqual(AppCommand.debug, options.command);
    try std.testing.expectEqualStrings("custom.dat", options.archive_path);
    try std.testing.expectEqualStrings("tmp/snail-runtime", options.runtime_root_path);
    try std.testing.expectEqualStrings("artifacts/test-shots", options.screenshot_dir);
    try std.testing.expectEqual(frontend.GamePhase.intro, options.auto_screenshot.?.phase);
    try std.testing.expectEqual(@as(u64, 60), options.auto_screenshot.?.tick);
    try std.testing.expectEqual(@as(u32, 5), options.timeout_seconds.?);
    try std.testing.expectEqual(@as(i32, 640), options.window_size_override.?.width);
    try std.testing.expectEqual(@as(i32, 480), options.window_size_override.?.height);
    try std.testing.expectEqual(true, options.fullscreen);
    try std.testing.expectEqual(true, options.hidden_window);
    try std.testing.expectEqual(false, options.credits_with_remake);
    try std.testing.expectEqualStrings("models", options.debug_mode.?);

    options = try parseArgsFromSlice(&.{"smoke"});
    try std.testing.expectEqual(AppCommand.smoke, options.command);
}

test "parse args accepts start phase override" {
    const options = try parseArgsFromSlice(&.{ "--start-phase", "main_menu" });
    try std.testing.expectEqual(frontend.GamePhase.main_menu, options.start_phase.?);
}

test "parse args accepts level intro override" {
    const options = try parseArgsFromSlice(&.{ "--start-level-intro", "--auto-dismiss-click-start" });
    try std.testing.expectEqual(true, options.start_level_intro);
    try std.testing.expectEqual(true, options.auto_dismiss_click_start);
}

test "parse args accepts start route index override" {
    const options = try parseArgsFromSlice(&.{ "--start-route-index", "3" });
    try std.testing.expectEqual(@as(usize, 3), options.start_route_index.?);
}

test "parse args accepts debug level row start override" {
    const options = try parseArgsFromSlice(&.{
        "--debug-start-level",
        "LEVELS/TUTORIAL.TXT",
        "--debug-start-row",
        "320.5",
        "--debug-start-lane",
        "5.5",
    });
    try std.testing.expectEqualStrings("LEVELS/TUTORIAL.TXT", options.debug_start_level_path.?);
    try std.testing.expectApproxEqAbs(@as(f32, 320.5), options.debug_start_row.?, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 5.5), options.debug_start_lane.?, 0.001);
}

test "parse args accepts pause context override" {
    const options = try parseArgsFromSlice(&.{
        "--pause-context",
        "--start-phase",
        "options_menu",
    });
    try std.testing.expectEqual(true, options.pause_context);
    try std.testing.expectEqual(frontend.GamePhase.options_menu, options.start_phase.?);
}

test "parse args requires timeout for hidden window" {
    try std.testing.expectError(error.HiddenWindowRequiresTimeout, parseArgsFromSlice(&.{"--hidden-window"}));
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

test "parse args accepts mouse local override" {
    const options = try parseArgsFromSlice(&.{ "--mouse-local", "392.5,95.0" });
    try std.testing.expectApproxEqAbs(@as(f32, 392.5), options.mouse_local_override.?.x, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 95.0), options.mouse_local_override.?.y, 0.001);
}

test "parse args validates start phase" {
    try std.testing.expectError(error.MissingStartPhase, parseArgsFromSlice(&.{"--start-phase"}));
    try std.testing.expectError(error.InvalidStartPhase, parseArgsFromSlice(&.{ "--start-phase", "weird" }));
}

test "parse args validates start route index" {
    try std.testing.expectError(error.MissingStartRouteIndex, parseArgsFromSlice(&.{"--start-route-index"}));
    try std.testing.expectError(error.InvalidStartRouteIndex, parseArgsFromSlice(&.{ "--start-route-index", "0" }));
}

test "parse args validates debug level row start" {
    try std.testing.expectError(error.MissingDebugStartRow, parseArgsFromSlice(&.{ "--debug-start-level", "LEVELS/TUTORIAL.TXT" }));
    try std.testing.expectError(error.MissingDebugStartLevel, parseArgsFromSlice(&.{"--debug-start-level"}));
    try std.testing.expectError(error.MissingDebugStartRow, parseArgsFromSlice(&.{"--debug-start-row"}));
    try std.testing.expectError(error.InvalidDebugStartRow, parseArgsFromSlice(&.{ "--debug-start-row", "nan" }));
    try std.testing.expectError(error.MissingDebugStartLane, parseArgsFromSlice(&.{"--debug-start-lane"}));
    try std.testing.expectError(error.InvalidDebugStartLane, parseArgsFromSlice(&.{ "--debug-start-row", "10", "--debug-start-lane", "inf" }));
}

test "parse args validates timeout seconds" {
    try std.testing.expectError(error.MissingTimeoutSeconds, parseArgsFromSlice(&.{"--timeout-seconds"}));
    try std.testing.expectError(error.InvalidTimeoutSeconds, parseArgsFromSlice(&.{ "--timeout-seconds", "0" }));
}

test "parse window size validates dimensions" {
    const size = try parseWindowSize("1024x768");
    try std.testing.expectEqual(@as(i32, 1024), size.width);
    try std.testing.expectEqual(@as(i32, 768), size.height);

    const uppercase = try parseWindowSize("640X480");
    try std.testing.expectEqual(@as(i32, 640), uppercase.width);
    try std.testing.expectEqual(@as(i32, 480), uppercase.height);

    try std.testing.expectError(error.InvalidWindowSize, parseWindowSize("640"));
    try std.testing.expectError(error.InvalidWindowSize, parseWindowSize("0x480"));
}
