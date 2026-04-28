const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("../attachment_builders.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_assets = @import("assets.zig");
const track = @import("../track.zig");

const native_runtime_tile_wall: u8 = 0x0e;

pub const NativeGameplaySoundCues = struct {
    completion_arm_cheers: bool = false,
    extra_life: bool = false,
    trampoline_bounce: bool = false,
    wall_barrier_hit: bool = false,
    parcel_pickup: bool = false,
    parcel_delivery: bool = false,
    parcel_bonus: bool = false,
    row_event_confirm: bool = false,
    sub_lazer_fire_position: ?rl.Vector3 = null,
};

pub const NativeJetpackSoundCues = struct {
    activate: bool = false,
    deactivate: bool = false,
};

pub const NativeGameplayVoiceCues = struct {
    start: bool = false,
    slow: bool = false,
    package_pickup: bool = false,
    weapon_upgrade: bool = false,
    damage_entry: bool = false,
    damage_escalation: bool = false,
    slug_engagement: bool = false,
};

pub const NativeMovementStateSoundFamily = enum {
    turbo,
    laser,
    rocket,
};

pub const NativeDeathCutsceneVoiceCues = struct {
    entry: bool = false,
    fallback: bool = false,
};

fn runnerInCompletionHandoff(runner: gameplay.Runner) bool {
    return switch (runner.phase) {
        .completion_handoff => true,
        else => false,
    };
}

fn vectorLength(v: rl.Vector3) f32 {
    return @sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

pub fn nativeGameplaySoundCues(previous: gameplay.Runner, current: gameplay.Runner) NativeGameplaySoundCues {
    return .{
        .completion_arm_cheers = !runnerInCompletionHandoff(previous) and runnerInCompletionHandoff(current),
        .extra_life = current.score.total > previous.score.total and current.visible_life_stock > previous.visible_life_stock,
        .trampoline_bounce = current.counters.trampoline_bounces > previous.counters.trampoline_bounces,
        .wall_barrier_hit = previous.current_runtime_tile_hint != native_runtime_tile_wall and
            current.current_runtime_tile_hint == native_runtime_tile_wall,
        .parcel_pickup = current.counters.parcels > previous.counters.parcels,
        .parcel_delivery = current.registeredParcelCount() > previous.registeredParcelCount(),
        .parcel_bonus = current.row_event_display.bonus_enabled and
            current.row_event_display.parcel_target_count != 0 and
            previous.registeredParcelCount() < current.row_event_display.parcel_target_count and
            current.registeredParcelCount() == current.row_event_display.parcel_target_count,
        .row_event_confirm = previous.row_event_display.state != .complete and
            current.row_event_display.state == .complete,
        .sub_lazer_fire_position = if (previous.runtime.sub_lazers.fire_generation != current.runtime.sub_lazers.fire_generation)
            current.runtime.sub_lazers.last_fire_position
        else
            null,
    };
}

pub fn nativeRingEffectKindTriggered(previous: gameplay.Runner, current: gameplay.Runner) ?u8 {
    if (current.native_ring_effect_token == previous.native_ring_effect_token) return null;
    return current.last_native_ring_effect_kind;
}

pub fn nativeRingPickupSoundIndex(previous: gameplay.Runner, current: gameplay.Runner) ?usize {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return switch (effect_kind) {
            1 => 0,
            4, 5, 8 => @min(
                gameplay_assets.gameplay_powerup_pickup_sound_paths.len - 1,
                @as(usize, @intCast(@max(current.presentation.movement_flag_selector, 1) - 1)),
            ),
            else => null,
        };
    }

    if (current.counters.ring_powerup <= previous.counters.ring_powerup) return null;
    return @min(
        gameplay_assets.gameplay_powerup_pickup_sound_paths.len - 1,
        @as(usize, current.counters.ring_powerup - 1),
    );
}

pub fn nativeSlowRingSoundTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return effect_kind == 3 or effect_kind == 7;
    }
    return current.presentation.slow_ticks > previous.presentation.slow_ticks;
}

pub fn nativeExplodeRingSoundTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return effect_kind == 2 or effect_kind == 6;
    }
    return current.counters.ring_explode > previous.counters.ring_explode;
}

pub fn nativeWeaponPresentationChanged(previous: gameplay.Runner, current: gameplay.Runner) bool {
    return current.presentation.movement_flags != previous.presentation.movement_flags;
}

pub fn nativeMovementStateSoundFamily(current: gameplay.Runner) NativeMovementStateSoundFamily {
    if ((current.presentation.movement_flags & 0x7) != 0) return .turbo;
    if ((current.presentation.movement_flags & 0x18) != 0) return .laser;
    if ((current.presentation.movement_flags & 0x60) != 0) return .rocket;
    return .turbo;
}

pub fn nativeMovementStateAttachmentExitGain(
    camera_position: rl.Vector3,
    player_position: rl.Vector3,
    attachment_exit_pending: bool,
) ?f32 {
    if (!attachment_exit_pending) return null;
    const delta = rl.Vector3{
        .x = camera_position.x - player_position.x,
        .y = camera_position.y - player_position.y,
        .z = camera_position.z - player_position.z,
    };
    return std.math.clamp(1.0 - (vectorLength(delta) * (1.0 / 60.0)), 0.0, 1.0);
}

pub fn nativePositionalSoundGain(camera_position: rl.Vector3, sound_position: rl.Vector3) ?f32 {
    const delta = rl.Vector3{
        .x = sound_position.x - camera_position.x,
        .y = sound_position.y - camera_position.y,
        .z = sound_position.z - camera_position.z,
    };
    const distance = vectorLength(delta);
    if (distance > 25.0) return null;
    return 1.0 - distance * 0.039999999;
}

pub fn nativeMovementSoundVariantIndexForSample(sample: u32, comptime count: usize) usize {
    return @min(count - 1, @as(usize, @intCast((@as(u64, sample) * count) / 0x8000)));
}

pub fn nativeJetpackSoundCues(previous: gameplay.Runner, current: gameplay.Runner) NativeJetpackSoundCues {
    return .{
        .activate = !previous.jetpack.thrust_visual_active and current.jetpack.thrust_visual_active,
        .deactivate = previous.jetpack.thrust_visual_active and !current.jetpack.thrust_visual_active,
    };
}

fn nativeGameplayWeaponUpgradeVoiceCue(
    previous: gameplay.Runner,
    current: gameplay.Runner,
    runtime_build_flags: u32,
) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return (effect_kind == 4 or effect_kind == 5) and
            (runtime_build_flags & 0x10) != 0 and
            current.session_mode != .time_trial;
    }
    return current.presentation.weapon_level > previous.presentation.weapon_level;
}

pub fn nativeGameplayVoiceCues(
    previous: gameplay.Runner,
    current: gameplay.Runner,
    runtime_build_flags: u32,
) NativeGameplayVoiceCues {
    return .{
        .start = previous.tick_count < gameplay_assets.native_gameplay_start_voice_tick and
            current.tick_count >= gameplay_assets.native_gameplay_start_voice_tick,
        .slow = previous.presentation.slow_commentary_voice_token != current.presentation.slow_commentary_voice_token,
        .package_pickup = current.counters.parcels > previous.counters.parcels,
        .weapon_upgrade = nativeGameplayWeaponUpgradeVoiceCue(previous, current, runtime_build_flags),
        .damage_entry = previous.damage.gauge <= 0.0 and current.damage.gauge > 0.0,
        .damage_escalation = previous.damage.warning_state != .draining and
            current.damage.warning_state == .draining,
        .slug_engagement = previous.slug_engagement_voice_token != current.slug_engagement_voice_token,
    };
}

pub fn nativeGameplayWarningLoopTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    return previous.damage.warning_actor.sample_generation != current.damage.warning_actor.sample_generation;
}

pub fn nativeSlugAmbientVoiceIndex(previous: gameplay.Runner, current: gameplay.Runner) ?usize {
    if (previous.slug_ambient_voice_token == current.slug_ambient_voice_token) return null;
    return @min(current.slug_ambient_voice_variant, gameplay_assets.gameplay_slug_ambient_voice_paths.len - 1);
}

pub fn nativeSlugHitVoiceIndex(previous: gameplay.Runner, current: gameplay.Runner) ?usize {
    if (previous.slug_hit_voice_token == current.slug_hit_voice_token) return null;
    return @min(current.slug_hit_voice_variant, gameplay_assets.gameplay_slug_hit_voice_paths.len - 1);
}

pub fn nativeSlugDeathVoiceIndex(previous: gameplay.Runner, current: gameplay.Runner) ?usize {
    if (previous.slug_death_voice_token == current.slug_death_voice_token) return null;
    return @min(current.slug_death_voice_variant, gameplay_assets.gameplay_slug_death_voice_paths.len - 1);
}

pub fn nativeGameplaySupertrampExitVoice(current: gameplay.Runner, previous_attachment_template_kind: ?u8) bool {
    if (previous_attachment_template_kind != attachment_builders.template_kind_supertramp) return false;
    if (current.movement_mode == .attachment or current.attachment.follow.active) return false;
    return current.attachment.launch.active and current.attachment.launch.vertical_velocity > 0.0;
}

pub fn nativeDeathCutsceneVoiceCues(previous: gameplay.Runner, current: gameplay.Runner) NativeDeathCutsceneVoiceCues {
    const death_cutscene_active = current.cutscene.id == gameplay.cutscene_death_id and current.deathCause() == .hazard;
    if (!death_cutscene_active) return .{};

    return .{
        .entry = previous.cutscene.camera.state != .death_blend and current.cutscene.camera.state == .death_blend,
        .fallback = previous.cutscene.camera.state != .death_hold and
            current.cutscene.camera.state == .death_hold and
            !current.attachment.exit.gate_b,
    };
}

test "native gameplay sound cues fire for completion-arm and score-bucket life gain" {
    var previous = gameplay.Runner{};
    var current = previous;

    try std.testing.expectEqual(NativeGameplaySoundCues{}, nativeGameplaySoundCues(previous, current));

    current.phase = .completion_handoff;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).completion_arm_cheers);

    previous = current;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).completion_arm_cheers);

    previous = gameplay.Runner{};
    current = previous;
    current.score.total = 50_000;
    current.visible_life_stock = previous.visible_life_stock + 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).extra_life);

    current.score.total = previous.score.total;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).extra_life);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.trampoline_bounces = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).trampoline_bounce);

    previous = gameplay.Runner{};
    current = previous;
    current.current_runtime_tile_hint = native_runtime_tile_wall;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).wall_barrier_hit);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.parcels = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_pickup);

    previous = gameplay.Runner{};
    current = previous;
    current.row_event_display.delivered_parcel_count = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_delivery);

    previous = gameplay.Runner{};
    current = previous;
    current.row_event_display.parcel_target_count = 1;
    current.row_event_display.bonus_enabled = true;
    current.row_event_display.delivered_parcel_count = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_bonus);

    current.row_event_display.bonus_enabled = false;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).parcel_bonus);

    previous = gameplay.Runner{};
    current = previous;
    previous.row_event_display.state = .bonus_prompt;
    current.row_event_display.state = .complete;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).row_event_confirm);

    previous = gameplay.Runner{};
    current = previous;
    _ = current.runtime.sub_lazers.shoot(
        8,
        3,
        .{ .x = 0.0, .y = 8.0, .z = 24.0 },
        .{ .x = 0.0, .y = 0.0, .z = -0.40000001 },
        0.0,
    ).?;
    try std.testing.expectEqualDeep(
        @as(?rl.Vector3, .{ .x = 0.0, .y = 8.0, .z = 24.0 }),
        nativeGameplaySoundCues(previous, current).sub_lazer_fire_position,
    );

    previous = current;
    try std.testing.expectEqual(@as(?rl.Vector3, null), nativeGameplaySoundCues(previous, current).sub_lazer_fire_position);

    current.runtime.sub_lazers.destroy(&current.runtime.sub_lazers.slots[0]);
    _ = current.runtime.sub_lazers.shoot(
        12,
        4,
        .{ .x = 1.0, .y = 8.0, .z = 28.0 },
        .{ .x = 0.0, .y = 0.0, .z = -0.40000001 },
        0.0,
    ).?;
    try std.testing.expectEqual(@as(usize, 1), previous.runtime.sub_lazers.countActive());
    try std.testing.expectEqual(@as(usize, 1), current.runtime.sub_lazers.countActive());
    try std.testing.expectEqualDeep(
        @as(?rl.Vector3, .{ .x = 1.0, .y = 8.0, .z = 28.0 }),
        nativeGameplaySoundCues(previous, current).sub_lazer_fire_position,
    );

    try std.testing.expectApproxEqAbs(
        @as(f32, 1.0),
        nativePositionalSoundGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        ).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        nativePositionalSoundGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 12.5, .y = 0.0, .z = 0.0 },
        ).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.0),
        nativePositionalSoundGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 25.0, .y = 0.0, .z = 0.0 },
        ).?,
        0.0001,
    );
    try std.testing.expectEqual(
        @as(?f32, null),
        nativePositionalSoundGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 25.1, .y = 0.0, .z = 0.0 },
        ),
    );

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expectEqual(@as(?usize, null), nativeRingPickupSoundIndex(previous, current));

    current.last_native_ring_effect_kind = 1;
    current.native_ring_effect_token = 1;
    try std.testing.expectEqual(@as(?usize, 0), nativeRingPickupSoundIndex(previous, current));
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = current;
    current.last_native_ring_effect_kind = 8;
    current.native_ring_effect_token +%= 1;
    current.presentation.movement_flag_selector = 8;
    try std.testing.expectEqual(
        @as(?usize, gameplay_assets.gameplay_powerup_pickup_sound_paths.len - 1),
        nativeRingPickupSoundIndex(previous, current),
    );
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 3;
    current.native_ring_effect_token = 1;
    try std.testing.expectEqual(@as(?usize, null), nativeRingPickupSoundIndex(previous, current));
    try std.testing.expect(nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 2;
    current.native_ring_effect_token = 1;
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(nativeExplodeRingSoundTriggered(previous, current));

    try std.testing.expectEqual(
        @as(?f32, null),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 30.0 },
            false,
        ),
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 30.0 },
            true,
        ).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.0),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 120.0 },
            true,
        ).?,
        0.0001,
    );
    try std.testing.expectEqual(@as(usize, 0), nativeMovementSoundVariantIndexForSample(0, 2));
    try std.testing.expectEqual(@as(usize, 0), nativeMovementSoundVariantIndexForSample(16383, 2));
    try std.testing.expectEqual(@as(usize, 1), nativeMovementSoundVariantIndexForSample(16384, 2));
    try std.testing.expectEqual(@as(usize, 2), nativeMovementSoundVariantIndexForSample(32767, 3));
    previous = gameplay.Runner{};
    current = previous;
    current.presentation.movement_flags = 8;
    try std.testing.expectEqualDeep(
        gameplay.WeaponChannelStates{ .right = 2 },
        gameplay.nativeWeaponChannelStates(current.presentation.movement_flags),
    );
    try std.testing.expect(nativeWeaponPresentationChanged(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.presentation.movement_flags = 2;
    try std.testing.expectEqualDeep(
        gameplay.WeaponChannelStates{ .left = 1, .right = 1 },
        gameplay.nativeWeaponChannelStates(current.presentation.movement_flags),
    );
    try std.testing.expect(nativeWeaponPresentationChanged(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expect(!nativeWeaponPresentationChanged(previous, current));
    try std.testing.expectEqual(NativeMovementStateSoundFamily.turbo, nativeMovementStateSoundFamily(current));

    current.presentation.weapon_level = 2;
    current.presentation.movement_flags = 144;
    try std.testing.expectEqual(NativeMovementStateSoundFamily.laser, nativeMovementStateSoundFamily(current));

    current.presentation.movement_flags = 192;
    try std.testing.expectEqual(NativeMovementStateSoundFamily.rocket, nativeMovementStateSoundFamily(current));

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expectEqual(NativeJetpackSoundCues{}, nativeJetpackSoundCues(previous, current));

    current.jetpack.arm();
    try std.testing.expect(nativeJetpackSoundCues(previous, current).activate);
    try std.testing.expect(!nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{};
    previous.jetpack.arm();
    previous.jetpack.progress = gameplay_assets.native_jetpack_visual_shutoff_threshold;
    current = previous;
    current.jetpack.update(false, false);
    try std.testing.expect(nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{};
    previous.jetpack.arm();
    current = previous;
    current.jetpack.disarm();
    try std.testing.expect(nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{};
    previous.jetpack.arm();
    previous.jetpack.progress = gameplay_assets.native_jetpack_visual_shutoff_threshold;
    previous.jetpack.update(false, false);
    current = previous;
    current.jetpack.disarm();
    try std.testing.expect(!nativeJetpackSoundCues(previous, current).deactivate);
}

test "native gameplay voice cues fire on the recovered startup timer" {
    var previous = gameplay.Runner{};
    var current = previous;
    const runtime_build_flags = track.postalChallengeRuntimeBuildFlags;

    current.tick_count = gameplay_assets.native_gameplay_start_voice_tick - 1;
    try std.testing.expectEqual(NativeGameplayVoiceCues{}, nativeGameplayVoiceCues(previous, current, runtime_build_flags));

    previous = current;
    current.tick_count = gameplay_assets.native_gameplay_start_voice_tick;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).start);

    previous = gameplay.Runner{};
    current = previous;
    current.presentation.slow_commentary_voice_token = 1;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).slow);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.parcels = 1;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).package_pickup);

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 4;
    current.native_ring_effect_token = 1;
    current.session_mode = .postal;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).weapon_upgrade);

    current = previous;
    current.last_native_ring_effect_kind = 8;
    current.native_ring_effect_token = 1;
    current.session_mode = .postal;
    try std.testing.expect(!nativeGameplayVoiceCues(previous, current, runtime_build_flags).weapon_upgrade);

    previous = gameplay.Runner{};
    current = previous;
    current.damage.gauge = 0.04;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).damage_entry);

    previous = gameplay.Runner{ .damage = .{ .warning_state = .filling } };
    current = previous;
    current.damage.warning_state = .draining;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).damage_escalation);

    previous = gameplay.Runner{};
    current = previous;
    current.slug_engagement_voice_token = 1;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).slug_engagement);

    previous = current;
    try std.testing.expectEqual(NativeGameplayVoiceCues{}, nativeGameplayVoiceCues(previous, current, runtime_build_flags));
}

test "native gameplay warning loop keys from the warning actor cadence" {
    const previous = gameplay.Runner{};
    var current = previous;
    try std.testing.expect(!nativeGameplayWarningLoopTriggered(previous, current));

    current.damage.warning_actor.sample_generation = 1;
    try std.testing.expect(nativeGameplayWarningLoopTriggered(previous, current));
}

test "slug direct voice cue indices are runner-owned" {
    var previous = gameplay.Runner{};
    var current = previous;

    current.slug_ambient_voice_token = 1;
    current.slug_ambient_voice_variant = gameplay_assets.gameplay_slug_ambient_voice_paths.len - 1;
    try std.testing.expectEqual(
        current.slug_ambient_voice_variant,
        nativeSlugAmbientVoiceIndex(previous, current).?,
    );

    previous = current;
    current.slug_hit_voice_token = 1;
    current.slug_hit_voice_variant = gameplay_assets.gameplay_slug_hit_voice_paths.len - 1;
    try std.testing.expectEqual(
        current.slug_hit_voice_variant,
        nativeSlugHitVoiceIndex(previous, current).?,
    );

    previous = current;
    current.slug_death_voice_token = 1;
    current.slug_death_voice_variant = gameplay_assets.gameplay_slug_death_voice_paths.len - 1;
    try std.testing.expectEqual(
        current.slug_death_voice_variant,
        nativeSlugDeathVoiceIndex(previous, current).?,
    );
}

test "native supertramp exit voice keys from the launch handoff" {
    var launched = gameplay.Runner{ .movement_mode = .track };
    launched.attachment.launch = .{
        .active = true,
        .vertical_velocity = 1.0,
    };
    try std.testing.expect(nativeGameplaySupertrampExitVoice(launched, 31));
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(launched, 24));

    var settled = gameplay.Runner{ .movement_mode = .track };
    settled.attachment.launch = .{
        .active = true,
        .vertical_velocity = 0.0,
    };
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(settled, 31));

    var attached = gameplay.Runner{ .movement_mode = .attachment };
    attached.attachment.follow = .{ .active = true };
    attached.attachment.launch = .{
        .active = true,
        .vertical_velocity = 1.0,
    };
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(attached, 31));
}

test "native death cutscene voice cues key from states 11 and 12" {
    var previous = gameplay.Runner{};
    var current = previous;
    current.cutscene.id = gameplay.cutscene_death_id;
    current.phase = .{ .fall = .{
        .cause = .hazard,
        .world_x = 0.0,
        .world_y = 0.0,
        .world_z = 0.0,
        .vertical_velocity = 0.0,
        .basis_forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .basis_up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    } };
    current.cutscene.camera.state = .death_blend;
    try std.testing.expect(nativeDeathCutsceneVoiceCues(previous, current).entry);
    try std.testing.expect(!nativeDeathCutsceneVoiceCues(previous, current).fallback);

    previous = current;
    current.cutscene.camera.state = .death_hold;
    try std.testing.expect(nativeDeathCutsceneVoiceCues(previous, current).fallback);

    current.attachment.exit.gate_b = true;
    try std.testing.expect(!nativeDeathCutsceneVoiceCues(previous, current).fallback);
}
