const std = @import("std");
const rl = @import("raylib");

const assets = @import("../assets.zig");
const audio_volume = @import("audio_volume.zig");
const gameplay_audio_catalog = @import("../gameplay/audio_catalog.zig");
const gameplay_voice = @import("../gameplay/voice.zig");
const level = @import("../level.zig");
const level_prompt = @import("../level_prompt.zig");
const resource_store = @import("../resource_store.zig");

pub const Context = struct {
    resources: *resource_store.Store,
    audio_ready: bool,
    current_sound: *assets.SoundSlot,
    current_voice_sound: *assets.SoundSlot,
    gameplay_audio_variant_counter: *u32,
    gameplay_click_start_active: bool,
    gameplay_voice_manager: *gameplay_voice.VoiceManager,
    native_gameplay_voice_manager: *gameplay_voice.NativeManager,
    level_prompt_queue: *level_prompt.Queue,
    volume: audio_volume.Context,
};

pub fn context(state: anytype) Context {
    return .{
        .resources = &state.resources,
        .audio_ready = state.audio_ready,
        .current_sound = &state.current_sound,
        .current_voice_sound = &state.current_voice_sound,
        .gameplay_audio_variant_counter = &state.gameplay_audio_variant_counter,
        .gameplay_click_start_active = state.gameplay_click_start_active,
        .gameplay_voice_manager = &state.gameplay_voice_manager,
        .native_gameplay_voice_manager = &state.native_gameplay_voice_manager,
        .level_prompt_queue = &state.level_prompt_queue,
        .volume = audio_volume.context(state),
    };
}

pub fn playLevelSegmentSample(audio: Context, segment_entry: *const level.SegmentEntry) !void {
    const sample_path = segment_entry.sample orelse return;
    if (std.ascii.startsWithIgnoreCase(sample_path, "VOICE/")) {
        if (gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath(sample_path)) |payload_index| {
            _ = try tryPlayNativePayload(audio, .tutorial, .interrupt_current, payload_index);
        } else {
            try playByPath(audio, sample_path);
        }
    } else {
        try playSoundByPath(audio, sample_path);
    }
}

pub fn playByPath(audio: Context, path: []const u8) !void {
    if (!audio.audio_ready) return;
    stopPlayback(audio);
    const sound = (try audio.current_voice_sound.loadPath(audio.resources, path)) orelse return;
    audio_volume.applyConfigVolumes(audio.volume);
    rl.playSound(sound.sound);
}

pub fn tryPlayNativeSet(audio: Context, set_id: gameplay_voice.NativeSet, mode: gameplay_voice.NativeMode) !void {
    _ = try tryPlayNativeSetPlayed(audio, set_id, mode);
}

pub fn tryPlayNativeSetPlayed(audio: Context, set_id: gameplay_voice.NativeSet, mode: gameplay_voice.NativeMode) !bool {
    if (!audio.audio_ready) return false;
    const paths = gameplay_audio_catalog.nativeGameplayVoicePaths(set_id);
    if (paths.len == 0) return false;

    const sample_index = audio.native_gameplay_voice_manager.requestPlay(
        set_id,
        mode,
        busy(audio),
        paths.len,
    ) orelse return false;
    try playByPath(audio, paths[sample_index]);
    return true;
}

pub fn tryPlayNativePayload(
    audio: Context,
    set_id: gameplay_voice.NativeSet,
    mode: gameplay_voice.NativeMode,
    payload_index: usize,
) !bool {
    if (!audio.audio_ready) return false;

    const sample_index = audio.native_gameplay_voice_manager.requestPayloadPlay(
        set_id,
        mode,
        busy(audio),
        payload_index,
    ) orelse return false;
    const sample_path = gameplay_audio_catalog.nativeGlobalAudioSamplePath(sample_index) orelse return false;
    try playByPath(audio, sample_path);
    return true;
}

pub fn tryPlayVariant(audio: Context, comptime count: usize, variants: [count][]const u8) !void {
    if (!canPlayGameplayVariant(audio)) return;
    const index = nextGameplaySoundVariantIndex(audio, count);
    try playByPath(audio, variants[index]);
    audio.gameplay_voice_manager.arm();
}

pub fn tryPlayVariantIndex(audio: Context, comptime count: usize, variants: [count][]const u8, index: usize) !void {
    if (!canPlayGameplayVariant(audio)) return;

    try playByPath(audio, variants[index % count]);
    audio.gameplay_voice_manager.arm();
}

pub fn stopPlayback(audio: Context) void {
    audio.current_voice_sound.unload();
}

pub fn busy(audio: Context) bool {
    if (audio.current_voice_sound.current) |sound| {
        return rl.isSoundPlaying(sound.sound);
    }
    return false;
}

fn playSoundByPath(audio: Context, path: []const u8) !void {
    if (!audio.audio_ready) return;
    const sound = (try audio.current_sound.loadPath(audio.resources, path)) orelse return;
    audio_volume.applyConfigVolumes(audio.volume);
    rl.playSound(sound.sound);
}

fn nextGameplaySoundVariantIndex(audio: Context, comptime count: usize) usize {
    const index = @as(usize, @intCast(audio.gameplay_audio_variant_counter.* % count));
    audio.gameplay_audio_variant_counter.* +%= 1;
    return index;
}

fn canPlayGameplayVariant(audio: Context) bool {
    if (!audio.audio_ready) return false;
    if (audio.gameplay_click_start_active) return false;
    if (audio.level_prompt_queue.active() != null) return false;
    if (audio.gameplay_voice_manager.active) return false;
    return !busy(audio);
}
