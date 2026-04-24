const std = @import("std");
const rl = @import("raylib");
const assets = @import("../assets.zig");
const attachment_builders = @import("../attachment_builders.zig");
const audio_volume = @import("audio_volume.zig");
const math_random = @import("math_random.zig");
const voice_audio = @import("voice_audio.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_assets = @import("../gameplay/assets.zig");
const gameplay_audio_cues = @import("../gameplay/audio_cues.zig");
const track = @import("../track.zig");

pub fn playGameplayRunnerAudio(
    state: anytype,
    previous: gameplay.Runner,
    current: gameplay.Runner,
    preview: *const track.LoadedLevelPreview,
    _: gameplay.RunnerInput,
) void {
    if (!state.audio_ready) return;
    const voices = voice_audio.context(state);
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
        voice_audio.tryPlayNativeSet(voices, .start, .interrupt_current) catch {};
    }
    if (native_voice_cues.package_pickup) {
        voice_audio.tryPlayNativeSet(voices, .package, .wait_for_frequency) catch {};
    }
    if (native_voice_cues.weapon_upgrade) {
        voice_audio.tryPlayNativeSet(voices, .powerup, .wait_for_frequency) catch {};
    }
    if (native_voice_cues.damage_entry) {
        // PORT(verified): native `apply_damage_gauge_delta`
        // (`artifacts/ida/functions/004413f0-apply_damage_gauge_delta.c:17-29`)
        // tries the `damage_entry` voice first; when it returns zero the
        // ouch-fallback plays. The damaged animation id 6 is still gated
        // by native byte `game + 0x430054`; the base animation is queued
        // from the same fallback branch either way.
        const played_damage = voice_audio.tryPlayNativeSetPlayed(voices, .damage, .wait_for_frequency) catch false;
        if (!played_damage) {
            voice_audio.tryPlayNativeSet(voices, .ouch, .wait_for_idle) catch {};
            if (state.level_runner) |*runner| {
                if (!state.native_damage_entry_animation_blocked) {
                    runner.dispatchCutsceneAnimation(.damaged, true, null);
                }
                runner.dispatchCutsceneAnimation(.base, false, null);
            }
        }
    }
    if (native_voice_cues.damage_escalation) {
        voice_audio.tryPlayNativeSet(voices, .postal, .wait_for_idle) catch {};
    }
    if (native_voice_cues.slow) {
        voice_audio.tryPlayNativeSet(voices, .slow, .wait_for_frequency) catch {};
    }
    const death_cutscene_voice_cues = gameplay_audio_cues.nativeDeathCutsceneVoiceCues(previous, current);
    if (death_cutscene_voice_cues.entry) {
        voice_audio.tryPlayNativeSet(voices, .fall, .interrupt_current) catch {};
    }
    if (death_cutscene_voice_cues.fallback) {
        voice_audio.tryPlayNativeSet(voices, .slugged, .interrupt_current) catch {};
    }

    const previous_attachment_template_kind = previous.currentAttachmentTemplateKind(preview);
    if (!previous.attachment.follow.active and current.attachment.follow.active and
        current.movement_mode == .attachment)
    {
        if (current.currentAttachmentTemplateKind(preview)) |template_kind| {
            if (template_kind == attachment_builders.template_kind_worm) {
                voice_audio.tryPlayNativeSet(voices, .worm_tunnel, .wait_for_idle) catch {};
            }
        }
    }
    if (gameplay_audio_cues.nativeGameplaySupertrampExitVoice(current, previous_attachment_template_kind)) {
        voice_audio.tryPlayNativeSet(voices, .supertramp, .wait_for_idle) catch {};
    }
    if (!previous.handoff.completion_voice_gate and current.handoff.completion_voice_gate) {
        voice_audio.tryPlayNativeSet(voices, .victory, .interrupt_current) catch {};
    }
    if (!previous.attachment.exit.gate_a and current.attachment.exit.gate_a) {
        voice_audio.tryPlayNativeSet(voices, .fall, .wait_for_idle) catch {};
    }
    if (!previous.attachment.exit.gate_b and current.attachment.exit.gate_b) {
        voice_audio.tryPlayNativeSet(voices, .dying, .interrupt_current) catch {};
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
            current.attachment.exit.pending,
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
        voice_audio.tryPlayVariant(
            voices,
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
        voice_audio.tryPlayVariant(
            voices,
            gameplay_assets.gameplay_slug_death_voice_paths.len,
            gameplay_assets.gameplay_slug_death_voice_paths,
        ) catch {};
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
    const base_volume = audio_volume.soundVolume(audio_volume.context(state));
    const scaled_volume = std.math.clamp(base_volume * gain, 0.0, 1.0);
    rl.setSoundVolume(loaded.sound, scaled_volume);
    rl.playSound(loaded.sound);
    rl.setSoundVolume(loaded.sound, base_volume);
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

fn nextGameplaySoundVariantIndex(state: anytype, comptime count: usize) usize {
    const index = @as(usize, @intCast(state.gameplay_audio_variant_counter % count));
    state.gameplay_audio_variant_counter +%= 1;
    return index;
}

fn countGameplayProjectiles(runner: gameplay.Runner, kind: gameplay.Projectile.Kind) usize {
    var count: usize = 0;
    for (runner.activeProjectiles()) |projectile| {
        if (projectile.kind == kind) count += 1;
    }
    return count;
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
