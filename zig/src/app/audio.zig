const std = @import("std");
const rl = @import("raylib");
const app = @import("../app.zig");
const assets = @import("../assets.zig");
const attachment_builders = @import("../attachment_builders.zig");
const math_random = @import("math_random.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_assets = @import("../gameplay/assets.zig");
const gameplay_audio_catalog = @import("../gameplay/audio_catalog.zig");
const gameplay_audio_cues = @import("../gameplay/audio_cues.zig");
const gameplay_art = @import("../gameplay_art.zig");
const gameplay_voice = @import("../gameplay/voice.zig");
const level = @import("../level.zig");
const track = @import("../track.zig");

const default_audio_path = app.default_audio_path;
const intro_music_path = app.intro_music_path;
const GameplaySoundFx = gameplay_art.SoundFx;

pub fn playGameplayRunnerAudio(
    state: anytype,
    previous: gameplay.Runner,
    current: gameplay.Runner,
    preview: *const track.LoadedLevelPreview,
    _: gameplay.RunnerInput,
) void {
    if (!state.audio_ready) return;
    const native_sound_cues = gameplay_audio_cues.nativeGameplaySoundCues(previous, current);
    const native_jetpack_sound_cues = gameplay_audio_cues.nativeJetpackSoundCues(previous, current);
    const native_voice_cues = gameplay_audio_cues.nativeGameplayVoiceCues(previous, current, preview.runtime_build_flags);

    if (native_sound_cues.completion_arm_cheers) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.cheers);
    }
    if (native_sound_cues.extra_life) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.extra_life);
    }
    if (native_sound_cues.trampoline_bounce) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.boing);
    }
    if (native_sound_cues.wall_barrier_hit) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.wall_hit);
    }
    if (native_sound_cues.parcel_pickup) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.place_package);
    }
    if (native_sound_cues.parcel_delivery) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.package_count);
    }
    if (native_sound_cues.parcel_bonus) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.perfect);
    }
    if (native_sound_cues.row_event_confirm) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.row_event_confirm);
    }
    if (native_jetpack_sound_cues.activate) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.jetpack);
    }
    if (native_jetpack_sound_cues.deactivate) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.jetpack_shutoff);
    }
    if (gameplay_audio_cues.nativeRingPickupSoundIndex(previous, current)) |sound_index| {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.powerup_pickup[sound_index]);
    }
    if (native_voice_cues.start) {
        tryPlayNativeGameplayVoiceSet(state, .start, .interrupt_current) catch {};
    }
    if (native_voice_cues.package_pickup) {
        tryPlayNativeGameplayVoiceSet(state, .package, .wait_for_frequency) catch {};
    }
    if (native_voice_cues.weapon_upgrade) {
        tryPlayNativeGameplayVoiceSet(state, .powerup, .wait_for_frequency) catch {};
    }
    if (native_voice_cues.damage_entry) {
        // PORT(verified): native `apply_damage_gauge_delta`
        // (`artifacts/ida/functions/004413f0-apply_damage_gauge_delta.c:17-29`)
        // tries the `damage_entry` voice first; when it returns zero the
        // ouch-fallback plays. The damaged animation id 6 is still gated
        // by native byte `game + 0x430054`; the base animation is queued
        // from the same fallback branch either way.
        const played_damage = tryPlayNativeGameplayVoiceSetPlayed(state, .damage, .wait_for_frequency) catch false;
        if (!played_damage) {
            tryPlayNativeGameplayVoiceSet(state, .ouch, .wait_for_idle) catch {};
            if (state.level_runner) |*runner| {
                if (!state.native_damage_entry_animation_blocked) {
                    runner.dispatchCutsceneAnimation(.damaged, true, null);
                }
                runner.dispatchCutsceneAnimation(.base, false, null);
            }
        }
    }
    if (native_voice_cues.damage_escalation) {
        tryPlayNativeGameplayVoiceSet(state, .postal, .wait_for_idle) catch {};
    }
    if (native_voice_cues.slow) {
        tryPlayNativeGameplayVoiceSet(state, .slow, .wait_for_frequency) catch {};
    }
    const death_cutscene_voice_cues = gameplay_audio_cues.nativeDeathCutsceneVoiceCues(previous, current);
    if (death_cutscene_voice_cues.entry) {
        tryPlayNativeGameplayVoiceSet(state, .fall, .interrupt_current) catch {};
    }
    if (death_cutscene_voice_cues.fallback) {
        tryPlayNativeGameplayVoiceSet(state, .slugged, .interrupt_current) catch {};
    }

    const previous_attachment_template_kind = previous.currentAttachmentTemplateKind(preview);
    if (!previous.attachment_follow.active and current.attachment_follow.active and
        current.movement_mode == .attachment)
    {
        if (current.currentAttachmentTemplateKind(preview)) |template_kind| {
            if (template_kind == attachment_builders.template_kind_worm) {
                tryPlayNativeGameplayVoiceSet(state, .worm_tunnel, .wait_for_idle) catch {};
            }
        }
    }
    if (gameplay_audio_cues.nativeGameplaySupertrampExitVoice(current, previous_attachment_template_kind)) {
        tryPlayNativeGameplayVoiceSet(state, .supertramp, .wait_for_idle) catch {};
    }
    if (!previous.completion_handoff_voice_gate and current.completion_handoff_voice_gate) {
        tryPlayNativeGameplayVoiceSet(state, .victory, .interrupt_current) catch {};
    }
    if (!previous.attachment_exit_gate_a and current.attachment_exit_gate_a) {
        tryPlayNativeGameplayVoiceSet(state, .fall, .wait_for_idle) catch {};
    }
    if (!previous.attachment_exit_gate_b and current.attachment_exit_gate_b) {
        tryPlayNativeGameplayVoiceSet(state, .dying, .interrupt_current) catch {};
    }

    if (gameplay_audio_cues.nativeGameplayWarningLoopTriggered(previous, current)) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.postal_warning);
    }

    if (previous.shot_cooldown_ticks == 0 and current.shot_cooldown_ticks > 0) {
        const fired_sound = switch (gameplay_audio_cues.nativeMovementStateSoundFamily(current)) {
            .turbo => pickNativeMovementSoundVariant(
                state,
                gameplay_assets.gameplay_turbo_fire_sound_paths.len,
                state.gameplay_resources.sound_fx.turbo_fire,
            ),
            .laser => pickNativeMovementSoundVariant(
                state,
                gameplay_assets.gameplay_laser_sound_paths.len,
                state.gameplay_resources.sound_fx.laser,
            ),
            .rocket => pickNativeMovementSoundVariant(
                state,
                gameplay_assets.gameplay_rocket_sound_paths.len,
                state.gameplay_resources.sound_fx.rocket,
            ),
        };
        const camera_position = rl.Vector3{
            .x = state.subgame_camera.shared_matrix.m12,
            .y = state.subgame_camera.shared_matrix.m13,
            .z = state.subgame_camera.shared_matrix.m14,
        };
        if (gameplay_audio_cues.nativeMovementStateAttachmentExitGain(
            camera_position,
            current.worldPosition(preview, 0.0),
            current.attachment_exit_pending,
        )) |gain| {
            playGameplayEffectScaled(state, fired_sound, gain);
        } else {
            playGameplayEffect(state, fired_sound);
        }
    }
    if (countGameplayProjectiles(previous, .enemy_laser) < countGameplayProjectiles(current, .enemy_laser)) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.enemy_fire);
    }
    if (gameplay_audio_cues.nativeWeaponPresentationChanged(previous, current)) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.weapon_change);
    }
    if (current.counters.health_pickups > previous.counters.health_pickups) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.heart);
    }
    if (current.invincible_ticks > previous.invincible_ticks) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.invincible);
    }
    if (gameplay_audio_cues.nativeSlowRingSoundTriggered(previous, current)) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.slow_ring);
    }
    if (gameplay_audio_cues.nativeExplodeRingSoundTriggered(previous, current)) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.explode_ring);
    }
    if (current.counters.garbage_hits > previous.counters.garbage_hits) {
        playGameplayEffect(state, pickGameplaySoundVariant(
            state,
            gameplay_assets.gameplay_asteroid_impact_sound_paths.len,
            state.gameplay_resources.sound_fx.asteroid_impact,
        ));
    }
    if (current.counters.salt_hits > previous.counters.salt_hits) {
        playGameplayEffect(state, pickGameplaySoundVariant(
            state,
            gameplay_assets.gameplay_asteroid_impact_sound_paths.len,
            state.gameplay_resources.sound_fx.asteroid_impact,
        ));
    }
    if (current.counters.turret_hits > previous.counters.turret_hits) {
        playGameplayEffect(state, state.gameplay_resources.sound_fx.wall_hit);
    }
    if (current.counters.slug_hits > previous.counters.slug_hits) {
        tryPlayGameplayVoiceVariant(
            state,
            gameplay_assets.gameplay_slug_hit_voice_paths.len,
            gameplay_assets.gameplay_slug_hit_voice_paths,
        ) catch {};
    }
    if (current.defeated_slug_cell_count > previous.defeated_slug_cell_count) {
        playGameplayEffect(state, pickGameplaySoundVariant(
            state,
            gameplay_assets.gameplay_asteroid_impact_sound_paths.len,
            state.gameplay_resources.sound_fx.asteroid_impact,
        ));
        tryPlayGameplayVoiceVariant(
            state,
            gameplay_assets.gameplay_slug_death_voice_paths.len,
            gameplay_assets.gameplay_slug_death_voice_paths,
        ) catch {};
    }
}

pub fn playLevelSegmentSample(state: anytype, segment_entry: *const level.SegmentEntry) !void {
    const sample_path = segment_entry.sample orelse return;
    if (std.ascii.startsWithIgnoreCase(sample_path, "VOICE/")) {
        if (gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath(sample_path)) |payload_index| {
            _ = try tryPlayNativeGameplayVoicePayload(state, .tutorial, .interrupt_current, payload_index);
        } else {
            try playVoiceByPath(state, sample_path);
        }
    } else {
        try playSoundByPath(state, sample_path);
    }
}

pub fn playMusicByPath(state: anytype, path: []const u8) !void {
    if (!state.audio_ready) return;
    if (state.current_music) |music| {
        if (std.ascii.eqlIgnoreCase(music.path, path)) {
            applyAudioConfigVolumes(state);
            if (!rl.isMusicStreamPlaying(music.music)) {
                rl.playMusicStream(music.music);
            }
            return;
        }
    }

    stopAudioPreview(state);
    state.current_music = if (takePreloadedMusic(state, path)) |music|
        music
    else
        try state.resources.catalog.loadMusicByPath(state.allocator, path);
    applyAudioConfigVolumes(state);
    rl.playMusicStream(state.current_music.?.music);
}

fn playSoundByPath(state: anytype, path: []const u8) !void {
    if (!state.audio_ready) return;
    const sound = (try state.current_sound.loadPath(&state.resources, path)) orelse return;
    applyAudioConfigVolumes(state);
    rl.playSound(sound.sound);
}

fn playVoiceByPath(state: anytype, path: []const u8) !void {
    if (!state.audio_ready) return;
    stopVoicePlayback(state);
    const sound = (try state.current_voice_sound.loadPath(&state.resources, path)) orelse return;
    applyAudioConfigVolumes(state);
    rl.playSound(sound.sound);
}

fn tryPlayNativeGameplayVoiceSet(state: anytype, set_id: gameplay_voice.NativeSet, mode: gameplay_voice.NativeMode) !void {
    _ = try tryPlayNativeGameplayVoiceSetPlayed(state, set_id, mode);
}

fn tryPlayNativeGameplayVoiceSetPlayed(state: anytype, set_id: gameplay_voice.NativeSet, mode: gameplay_voice.NativeMode) !bool {
    if (!state.audio_ready) return false;
    const paths = gameplay_audio_catalog.nativeGameplayVoicePaths(set_id);
    if (paths.len == 0) return false;

    const sample_index = state.native_gameplay_voice_manager.requestPlay(
        set_id,
        mode,
        gameplayVoiceBusy(state),
        paths.len,
    ) orelse return false;
    try playVoiceByPath(state, paths[sample_index]);
    return true;
}

fn tryPlayNativeGameplayVoicePayload(
    state: anytype,
    set_id: gameplay_voice.NativeSet,
    mode: gameplay_voice.NativeMode,
    payload_index: usize,
) !bool {
    if (!state.audio_ready) return false;

    const sample_index = state.native_gameplay_voice_manager.requestPayloadPlay(
        set_id,
        mode,
        gameplayVoiceBusy(state),
        payload_index,
    ) orelse return false;
    const sample_path = gameplay_audio_catalog.nativeGlobalAudioSamplePath(sample_index) orelse return false;
    try playVoiceByPath(state, sample_path);
    return true;
}

fn gameplayVoiceBusy(state: anytype) bool {
    if (state.current_voice_sound.current) |sound| {
        return rl.isSoundPlaying(sound.sound);
    }
    return false;
}

fn tryPlayGameplayVoiceVariant(state: anytype, comptime count: usize, variants: [count][]const u8) !void {
    if (!state.audio_ready) return;
    if (state.gameplay_click_start_active) return;
    if (state.level_prompt_queue.active() != null) return;
    if (state.gameplay_voice_manager.active) return;
    if (gameplayVoiceBusy(state)) return;

    const index = nextGameplaySoundVariantIndex(state, count);
    try playVoiceByPath(state, variants[index]);
    state.gameplay_voice_manager.arm();
}

pub fn updateGameplayAmbientVoices(state: anytype, runner: gameplay.Runner, preview: *const track.LoadedLevelPreview) void {
    if (!isTutorialGameplay(state)) return;
    if (runner.paused or state.gameplay_click_start_active) return;
    if (state.level_prompt_queue.active() != null) return;
    if (state.gameplay_voice_manager.active or gameplayVoiceBusy(state)) return;

    const current_row_floor = @as(usize, @intFromFloat(@floor(runner.row_position)));
    const bark_row_limit = @min(preview.total_rows, current_row_floor + 2);
    var row = current_row_floor;
    while (row < bark_row_limit) : (row += 1) {
        for (0..preview.max_width) |lane| {
            if (runner.isSlugDefeated(row, lane)) continue;
            const sample = preview.gameplayCellSampleAt(row, lane) orelse continue;
            if (sample.kind != .slug) continue;
            if (gameplaySlugVoiceCellAnnounced(state, row, lane)) continue;

            noteGameplaySlugVoiceCell(state, row, lane);
            if (deterministicGameplayAmbientSlugRoll(row, lane) > 0.6) {
                tryPlayGameplayVoiceVariant(
                    state,
                    gameplay_assets.gameplay_slug_ambient_voice_paths.len,
                    gameplay_assets.gameplay_slug_ambient_voice_paths,
                ) catch {};
            }
            return;
        }
    }
}

pub fn playGameplayEffect(state: anytype, sound: ?assets.LoadedSound) void {
    if (!state.audio_ready) return;
    const loaded = sound orelse return;
    rl.playSound(loaded.sound);
}

pub fn playGameplayEffectScaled(state: anytype, sound: ?assets.LoadedSound, gain: f32) void {
    if (!state.audio_ready) return;
    const loaded = sound orelse return;
    const base_volume = gameplaySoundBaseVolume(state);
    const scaled_volume = std.math.clamp(base_volume * gain, 0.0, 1.0);
    rl.setSoundVolume(loaded.sound, scaled_volume);
    rl.playSound(loaded.sound);
    rl.setSoundVolume(loaded.sound, base_volume);
}

fn nextGameplaySoundVariantIndex(state: anytype, comptime count: usize) usize {
    const index = @as(usize, @intCast(state.gameplay_audio_variant_counter % count));
    state.gameplay_audio_variant_counter +%= 1;
    return index;
}

fn pickGameplaySoundVariant(state: anytype, comptime count: usize, variants: [count]?assets.LoadedSound) ?assets.LoadedSound {
    var start = nextGameplaySoundVariantIndex(state, count);
    var remaining = count;
    while (remaining > 0) : (remaining -= 1) {
        if (variants[start]) |loaded| return loaded;
        start = (start + 1) % count;
    }
    return null;
}

pub fn applyAudioConfigVolumes(state: anytype) void {
    if (!state.audio_ready) return;

    const sound_volume = gameplaySoundBaseVolume(state);
    const music_volume = if (state.audio_muted) 0.0 else state.runtime_config.musicVolume();

    if (state.current_sound.current) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (state.current_voice_sound.current) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (state.frontend_sound_fx.highlight) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    if (state.frontend_sound_fx.select) |sound| {
        rl.setSoundVolume(sound.sound, sound_volume);
    }
    inline for (comptime std.meta.fieldNames(GameplaySoundFx)) |field_name| {
        const field = &@field(state.gameplay_resources.sound_fx, field_name);
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
    if (state.current_music) |music| {
        rl.setMusicVolume(music.music, music_volume);
    }
}

pub fn stopAudioPreview(state: anytype) void {
    state.current_sound.unload();
    if (state.current_music) |*music| {
        music.unload();
        state.current_music = null;
    }
}

pub fn stopVoicePlayback(state: anytype) void {
    state.current_voice_sound.unload();
}

fn countGameplayProjectiles(runner: gameplay.Runner, kind: gameplay.Projectile.Kind) usize {
    var count: usize = 0;
    for (runner.activeProjectiles()) |projectile| {
        if (projectile.kind == kind) count += 1;
    }
    return count;
}

fn gameplaySlugVoiceCellAnnounced(state: anytype, row: usize, lane: usize) bool {
    for (0..state.announced_slug_voice_cell_count) |index| {
        const announced = state.announced_slug_voice_cells[index];
        if (announced.row == row and announced.lane == lane) return true;
    }
    return false;
}

fn noteGameplaySlugVoiceCell(state: anytype, row: usize, lane: usize) void {
    if (gameplaySlugVoiceCellAnnounced(state, row, lane)) return;
    if (state.announced_slug_voice_cell_count >= state.announced_slug_voice_cells.len) return;
    state.announced_slug_voice_cells[state.announced_slug_voice_cell_count] = .{ .row = row, .lane = lane };
    state.announced_slug_voice_cell_count += 1;
}

fn gameplaySoundBaseVolume(state: anytype) f32 {
    return if (state.audio_muted) 0.0 else state.runtime_config.soundVolume();
}

fn nextNativeMovementSoundVariantIndex(state: anytype, comptime count: usize) usize {
    return gameplay_audio_cues.nativeMovementSoundVariantIndexForSample(nextMathRandomInt15(state), count);
}

fn pickNativeMovementSoundVariant(state: anytype, comptime count: usize, variants: [count]?assets.LoadedSound) ?assets.LoadedSound {
    var start = nextNativeMovementSoundVariantIndex(state, count);
    var remaining = count;
    while (remaining > 0) : (remaining -= 1) {
        if (variants[start]) |loaded| return loaded;
        start = (start + 1) % count;
    }
    return null;
}

fn nextMathRandomInt15(state: anytype) u32 {
    return math_random.nextInt15(&state.math_random_state);
}

fn takePreloadedMusic(state: anytype, path: []const u8) ?assets.LoadedMusic {
    if (std.ascii.eqlIgnoreCase(path, intro_music_path)) {
        return takeOptional(assets.LoadedMusic, &state.preloaded_intro_music);
    }
    if (std.ascii.eqlIgnoreCase(path, default_audio_path)) {
        return takeOptional(assets.LoadedMusic, &state.preloaded_menu_music);
    }
    return null;
}

fn isTutorialGameplay(state: anytype) bool {
    if (state.active_frontend_mode == .tutorial) return true;
    if (state.level_runner) |runner| {
        if (runner.session_mode == .tutorial) return true;
    }
    const loaded_level = state.current_level orelse return false;
    return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
}

fn deterministicGameplayAmbientSlugRoll(row: usize, lane: usize) f32 {
    const mixed = (@as(u64, row) *% 0x9e3779b97f4a7c15) ^ (@as(u64, lane) *% 0xc2b2ae3d27d4eb4f);
    const normalized = @as(f64, @floatFromInt(mixed & 0xffff)) / 65535.0;
    return @floatCast(normalized);
}

fn takeOptional(comptime T: type, slot: *?T) ?T {
    if (slot.*) |value| {
        slot.* = null;
        return value;
    }
    return null;
}
