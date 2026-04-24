const std = @import("std");

const app = @import("../app.zig");
const assets = @import("../assets.zig");
const background = @import("../background.zig");
const frontend = @import("../frontend.zig");
const high_score = @import("../high_score.zig");
const intro = @import("../intro.zig");
const resource_store = @import("../resource_store.zig");

const boot_tasks = frontend.boot_tasks;

const intro_background_path = app.intro_background_path;
const main_menu_background_path = app.main_menu_background_path;
const route_map_background_path = app.route_map_background_path;
const help_background_path = app.help_background_path;
const intro_script_path = app.intro_script_path;
const credits_script_path = app.credits_script_path;
const intro_music_path = app.intro_music_path;
const default_audio_path = app.default_audio_path;

pub const Context = struct {
    allocator: std.mem.Allocator,
    resources: *resource_store.Store,
    runtime_root_path: []const u8,
    credits_with_remake: bool,
    high_score_tables: *high_score.Tables,
    task_index: *usize,
    intro_background: *?background.Loaded,
    main_menu_background: *?background.Loaded,
    route_map_background: *?background.Loaded,
    help_background: *?background.Loaded,
    intro_script: *?intro.Loaded,
    credits_script: *?intro.Loaded,
    intro_music: *?assets.LoadedMusic,
    menu_music: *?assets.LoadedMusic,
};

pub fn context(state: anytype) Context {
    return .{
        .allocator = state.allocator,
        .resources = &state.resources,
        .runtime_root_path = state.runtime_root_path,
        .credits_with_remake = state.credits_with_remake,
        .high_score_tables = &state.high_score_tables,
        .task_index = &state.boot_task_index,
        .intro_background = &state.preloaded_intro_background,
        .main_menu_background = &state.preloaded_main_menu_background,
        .route_map_background = &state.preloaded_route_map_background,
        .help_background = &state.preloaded_help_background,
        .intro_script = &state.preloaded_intro_script,
        .credits_script = &state.preloaded_credits_script,
        .intro_music = &state.preloaded_intro_music,
        .menu_music = &state.preloaded_menu_music,
    };
}

pub fn advance(boot: Context) !bool {
    if (boot.task_index.* >= boot_tasks.len) return true;

    switch (boot_tasks[boot.task_index.*]) {
        .load_high_scores => try boot.high_score_tables.loadFromRuntimeRoot(boot.allocator, boot.runtime_root_path),
        .load_intro_background => {
            unloadBackground(boot.intro_background);
            boot.intro_background.* = try background.Loaded.loadByPath(boot.allocator, boot.resources, intro_background_path);
        },
        .load_main_menu_background => {
            unloadBackground(boot.main_menu_background);
            boot.main_menu_background.* = try background.Loaded.loadByPath(boot.allocator, boot.resources, main_menu_background_path);
        },
        .load_route_map_background => {
            unloadBackground(boot.route_map_background);
            boot.route_map_background.* = try background.Loaded.loadByPath(boot.allocator, boot.resources, route_map_background_path);
        },
        .load_help_background => {
            unloadBackground(boot.help_background);
            boot.help_background.* = try background.Loaded.loadByPath(boot.allocator, boot.resources, help_background_path);
        },
        .load_intro_script => {
            unloadTextScript(boot.allocator, boot.intro_script);
            boot.intro_script.* = try loadConfiguredTextScriptEntry(boot, intro_script_path);
        },
        .load_credits_script => {
            unloadTextScript(boot.allocator, boot.credits_script);
            boot.credits_script.* = try loadConfiguredTextScriptEntry(boot, credits_script_path);
        },
        .load_intro_music => {
            unloadMusic(boot.intro_music);
            boot.intro_music.* = try boot.resources.catalog.loadMusicByPath(boot.allocator, intro_music_path);
        },
        .load_menu_music => {
            unloadMusic(boot.menu_music);
            boot.menu_music.* = try boot.resources.catalog.loadMusicByPath(boot.allocator, default_audio_path);
        },
    }

    boot.task_index.* += 1;
    return boot.task_index.* >= boot_tasks.len;
}

pub fn unload(boot: Context) void {
    unloadBackground(boot.intro_background);
    unloadBackground(boot.main_menu_background);
    unloadBackground(boot.route_map_background);
    unloadBackground(boot.help_background);
    unloadTextScript(boot.allocator, boot.intro_script);
    unloadTextScript(boot.allocator, boot.credits_script);
    unloadMusic(boot.intro_music);
    unloadMusic(boot.menu_music);
}

pub fn takeBackground(boot: Context, script_path: []const u8) ?background.Loaded {
    if (std.ascii.eqlIgnoreCase(script_path, intro_background_path)) {
        return takeOptional(background.Loaded, boot.intro_background);
    }
    if (std.ascii.eqlIgnoreCase(script_path, main_menu_background_path)) {
        return takeOptional(background.Loaded, boot.main_menu_background);
    }
    if (std.ascii.eqlIgnoreCase(script_path, route_map_background_path)) {
        return takeOptional(background.Loaded, boot.route_map_background);
    }
    if (std.ascii.eqlIgnoreCase(script_path, help_background_path)) {
        return takeOptional(background.Loaded, boot.help_background);
    }
    return null;
}

pub fn takeTextScript(boot: Context, path: []const u8) ?intro.Loaded {
    if (std.ascii.eqlIgnoreCase(path, intro_script_path)) {
        return takeOptional(intro.Loaded, boot.intro_script);
    }
    if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
        return takeOptional(intro.Loaded, boot.credits_script);
    }
    return null;
}

pub fn loadConfiguredTextScriptEntry(boot: Context, path: []const u8) !intro.Loaded {
    if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
        return try intro.loadByPathWithOptions(
            boot.allocator,
            boot.resources,
            path,
            .{ .add_remake_credit = boot.credits_with_remake },
        );
    }
    return try intro.loadByPath(boot.allocator, boot.resources, path);
}

pub fn progress(task_index: usize) f32 {
    if (boot_tasks.len == 0) return 1.0;
    return std.math.clamp(
        @as(f32, @floatFromInt(task_index)) / @as(f32, @floatFromInt(boot_tasks.len)),
        0.0,
        1.0,
    );
}

fn unloadBackground(slot: *?background.Loaded) void {
    if (slot.*) |*loaded| {
        loaded.deinit();
        slot.* = null;
    }
}

fn unloadTextScript(allocator: std.mem.Allocator, slot: *?intro.Loaded) void {
    if (slot.*) |*loaded| {
        loaded.deinit(allocator);
        slot.* = null;
    }
}

fn unloadMusic(slot: *?assets.LoadedMusic) void {
    if (slot.*) |*loaded| {
        loaded.unload();
        slot.* = null;
    }
}

fn takeOptional(comptime T: type, slot: *?T) ?T {
    if (slot.*) |value| {
        slot.* = null;
        return value;
    }
    return null;
}
