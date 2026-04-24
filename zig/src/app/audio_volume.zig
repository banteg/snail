const std = @import("std");
const rl = @import("raylib");

const assets = @import("../assets.zig");
const config = @import("../config.zig");
const frontend_art = @import("../frontend/art.zig");
const gameplay_art = @import("../gameplay_art.zig");

const GameplaySoundFx = gameplay_art.SoundFx;

pub const Context = struct {
    audio_ready: bool,
    audio_muted: bool,
    runtime_config: *const config.Blob,
    current_sound: *const assets.SoundSlot,
    current_voice_sound: *const assets.SoundSlot,
    frontend_sound_fx: *const frontend_art.FrontendSoundFx,
    gameplay_sound_fx: *const GameplaySoundFx,
    current_music: *const ?assets.LoadedMusic,
};

pub fn context(state: anytype) Context {
    return .{
        .audio_ready = state.audio_ready,
        .audio_muted = state.audio_muted,
        .runtime_config = &state.runtime_config,
        .current_sound = &state.current_sound,
        .current_voice_sound = &state.current_voice_sound,
        .frontend_sound_fx = &state.frontend_sound_fx,
        .gameplay_sound_fx = &state.gameplay_resources.sound_fx,
        .current_music = &state.current_music,
    };
}

pub fn soundVolume(audio: Context) f32 {
    return if (audio.audio_muted) 0.0 else audio.runtime_config.soundVolume();
}

pub fn applyConfigVolumes(audio: Context) void {
    if (!audio.audio_ready) return;

    const sound_volume = soundVolume(audio);
    const music_volume = if (audio.audio_muted) 0.0 else audio.runtime_config.musicVolume();

    if (audio.current_sound.current) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (audio.current_voice_sound.current) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (audio.frontend_sound_fx.highlight) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (audio.frontend_sound_fx.select) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    inline for (comptime std.meta.fieldNames(GameplaySoundFx)) |field_name| {
        const field = &@field(audio.gameplay_sound_fx.*, field_name);
        switch (@typeInfo(@TypeOf(field.*))) {
            .array => {
                for (field) |entry| {
                    if (entry) |sound| {
                        rl.setSoundVolume(sound.sound, sound_volume);
                    }
                }
            },
            else => {
                if (field.*) |sound| {
                    rl.setSoundVolume(sound.sound, sound_volume);
                }
            },
        }
    }
    if (audio.current_music.*) |music| {
        rl.setMusicVolume(music.music, music_volume);
    }
}
