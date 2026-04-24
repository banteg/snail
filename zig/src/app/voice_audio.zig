const std = @import("std");
const rl = @import("raylib");

const assets = @import("../assets.zig");
const audio_volume = @import("audio_volume.zig");
const frontend = @import("../frontend.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_assets = @import("../gameplay/assets.zig");
const gameplay_audio_catalog = @import("../gameplay/audio_catalog.zig");
const gameplay_voice = @import("../gameplay/voice.zig");
const level = @import("../level.zig");
const level_prompt = @import("../level_prompt.zig");
const resource_store = @import("../resource_store.zig");
const track = @import("../track.zig");

pub const Context = struct {
    resources: *resource_store.Store,
    audio_ready: bool,
    current_sound: *assets.SoundSlot,
    current_voice_sound: *assets.SoundSlot,
    gameplay_audio_variant_counter: *u32,
    gameplay_click_start_active: bool,
    gameplay_voice_manager: *gameplay_voice.VoiceManager,
    native_gameplay_voice_manager: *gameplay_voice.NativeManager,
    announced_slug_voice_cells: []gameplay.RowTarget,
    announced_slug_voice_cell_count: *usize,
    level_prompt_queue: *level_prompt.Queue,
    active_frontend_mode: ?frontend.FrontendLevelMode,
    level_runner: ?*const gameplay.Runner,
    current_level: ?*const level.Definition,
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
        .announced_slug_voice_cells = state.announced_slug_voice_cells[0..],
        .announced_slug_voice_cell_count = &state.announced_slug_voice_cell_count,
        .level_prompt_queue = &state.level_prompt_queue,
        .active_frontend_mode = state.active_frontend_mode,
        .level_runner = if (state.level_runner) |*runner| runner else null,
        .current_level = if (state.current_level) |*loaded_level| loaded_level else null,
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
    if (!audio.audio_ready) return;
    if (audio.gameplay_click_start_active) return;
    if (audio.level_prompt_queue.active() != null) return;
    if (audio.gameplay_voice_manager.active) return;
    if (busy(audio)) return;

    const index = nextGameplaySoundVariantIndex(audio, count);
    try playByPath(audio, variants[index]);
    audio.gameplay_voice_manager.arm();
}

pub fn updateAmbient(audio: Context, runner: gameplay.Runner, preview: *const track.LoadedLevelPreview) void {
    if (!isTutorialGameplay(audio)) return;
    if (runner.paused or audio.gameplay_click_start_active) return;
    if (audio.level_prompt_queue.active() != null) return;
    if (audio.gameplay_voice_manager.active or busy(audio)) return;

    const current_row_floor = @as(usize, @intFromFloat(@floor(runner.row_position)));
    const bark_row_limit = @min(preview.total_rows, current_row_floor + 2);
    var row = current_row_floor;
    while (row < bark_row_limit) : (row += 1) {
        for (0..preview.max_width) |lane| {
            if (runner.isSlugDefeated(row, lane)) continue;
            const sample = preview.gameplayCellSampleAt(row, lane) orelse continue;
            if (sample.kind != .slug) continue;
            if (slugVoiceCellAnnounced(audio, row, lane)) continue;

            noteSlugVoiceCell(audio, row, lane);
            if (deterministicAmbientSlugRoll(row, lane) > 0.6) {
                tryPlayVariant(
                    audio,
                    gameplay_assets.gameplay_slug_ambient_voice_paths.len,
                    gameplay_assets.gameplay_slug_ambient_voice_paths,
                ) catch {};
            }
            return;
        }
    }
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

fn slugVoiceCellAnnounced(audio: Context, row: usize, lane: usize) bool {
    for (0..audio.announced_slug_voice_cell_count.*) |index| {
        const announced = audio.announced_slug_voice_cells[index];
        if (announced.row == row and announced.lane == lane) return true;
    }
    return false;
}

fn noteSlugVoiceCell(audio: Context, row: usize, lane: usize) void {
    if (slugVoiceCellAnnounced(audio, row, lane)) return;
    if (audio.announced_slug_voice_cell_count.* >= audio.announced_slug_voice_cells.len) return;
    audio.announced_slug_voice_cells[audio.announced_slug_voice_cell_count.*] = .{ .row = row, .lane = lane };
    audio.announced_slug_voice_cell_count.* += 1;
}

fn isTutorialGameplay(audio: Context) bool {
    if (audio.active_frontend_mode == .tutorial) return true;
    if (audio.level_runner) |runner| {
        if (runner.session_mode == .tutorial) return true;
    }
    const loaded_level = audio.current_level orelse return false;
    return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
}

fn deterministicAmbientSlugRoll(row: usize, lane: usize) f32 {
    const mixed = (@as(u64, row) *% 0x9e3779b97f4a7c15) ^ (@as(u64, lane) *% 0xc2b2ae3d27d4eb4f);
    const normalized = @as(f64, @floatFromInt(mixed & 0xffff)) / 65535.0;
    return @floatCast(normalized);
}
