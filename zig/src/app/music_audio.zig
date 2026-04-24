const std = @import("std");
const rl = @import("raylib");

const app = @import("../app.zig");
const assets = @import("../assets.zig");
const resource_store = @import("../resource_store.zig");
const audio_volume = @import("audio_volume.zig");

const default_audio_path = app.default_audio_path;
const intro_music_path = app.intro_music_path;

pub const Context = struct {
    allocator: std.mem.Allocator,
    resources: *resource_store.Store,
    audio_ready: bool,
    current_sound: *assets.SoundSlot,
    current_music: *?assets.LoadedMusic,
    preloaded_intro_music: *?assets.LoadedMusic,
    preloaded_menu_music: *?assets.LoadedMusic,
    volume: audio_volume.Context,
};

pub fn context(state: anytype) Context {
    return .{
        .allocator = state.allocator,
        .resources = &state.resources,
        .audio_ready = state.audio_ready,
        .current_sound = &state.current_sound,
        .current_music = &state.current_music,
        .preloaded_intro_music = &state.preloaded_intro_music,
        .preloaded_menu_music = &state.preloaded_menu_music,
        .volume = audio_volume.context(state),
    };
}

pub fn playByPath(audio: Context, path: []const u8) !void {
    if (!audio.audio_ready) return;
    if (audio.current_music.*) |music| {
        if (std.ascii.eqlIgnoreCase(music.path, path)) {
            audio_volume.applyConfigVolumes(audio.volume);
            if (!rl.isMusicStreamPlaying(music.music)) {
                rl.playMusicStream(music.music);
            }
            return;
        }
    }

    stopPreview(audio);
    audio.current_music.* = if (takePreloadedMusic(audio, path)) |music|
        music
    else
        try audio.resources.catalog.loadMusicByPath(audio.allocator, path);
    audio_volume.applyConfigVolumes(audio.volume);
    rl.playMusicStream(audio.current_music.*.?.music);
}

pub fn stopPreview(audio: Context) void {
    audio.current_sound.unload();
    if (audio.current_music.*) |*music| {
        music.unload();
        audio.current_music.* = null;
    }
}

fn takePreloadedMusic(audio: Context, path: []const u8) ?assets.LoadedMusic {
    if (std.ascii.eqlIgnoreCase(path, intro_music_path)) {
        return takeOptional(assets.LoadedMusic, audio.preloaded_intro_music);
    }
    if (std.ascii.eqlIgnoreCase(path, default_audio_path)) {
        return takeOptional(assets.LoadedMusic, audio.preloaded_menu_music);
    }
    return null;
}

fn takeOptional(comptime T: type, slot: *?T) ?T {
    if (slot.*) |value| {
        slot.* = null;
        return value;
    }
    return null;
}
