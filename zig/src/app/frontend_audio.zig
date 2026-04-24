const rl = @import("raylib");

const frontend_art = @import("../frontend/art.zig");

pub const Context = struct {
    audio_ready: bool,
    sound_fx: *const frontend_art.FrontendSoundFx,
};

pub fn context(state: anytype) Context {
    return .{
        .audio_ready = state.audio_ready,
        .sound_fx = &state.frontend_sound_fx,
    };
}

pub fn playHoverSound(audio: Context) void {
    if (!audio.audio_ready) return;
    if (audio.sound_fx.highlight) |sound| {
        rl.stopSound(sound.sound);
        rl.playSound(sound.sound);
    }
}

pub fn playSelectSound(audio: Context) void {
    if (!audio.audio_ready) return;
    if (audio.sound_fx.select) |sound| {
        rl.stopSound(sound.sound);
        rl.playSound(sound.sound);
    }
}
