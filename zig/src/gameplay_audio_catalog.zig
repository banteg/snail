const std = @import("std");
const app = @import("app.zig");
const gameplay_assets = @import("gameplay_assets.zig");
const gameplay_voice = @import("gameplay_voice.zig");

pub const native_global_audio_bank_paths = [_][]const u8{
    gameplay_assets.gameplay_cheers_sound_path,
    gameplay_assets.gameplay_powerup_pickup_sound_paths[0],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[1],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[2],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[3],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[4],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[5],
    gameplay_assets.gameplay_powerup_pickup_sound_paths[6],
    app.frontend_select_sound_path,
    app.frontend_highlight_sound_path,
    gameplay_assets.gameplay_native_voice_ouch_paths[0],
    gameplay_assets.gameplay_native_voice_ouch_paths[1],
    gameplay_assets.gameplay_native_voice_ouch_paths[2],
    gameplay_assets.gameplay_native_voice_ouch_paths[3],
    gameplay_assets.gameplay_heart_sound_path,
    gameplay_assets.gameplay_enemy_fire_sound_path,
    gameplay_assets.gameplay_jetpack_sound_path,
    gameplay_assets.gameplay_turbo_fire_sound_paths[0],
    gameplay_assets.gameplay_turbo_fire_sound_paths[1],
    gameplay_assets.gameplay_laser_sound_paths[0],
    gameplay_assets.gameplay_laser_sound_paths[1],
    gameplay_assets.gameplay_laser_sound_paths[2],
    gameplay_assets.gameplay_rocket_sound_paths[0],
    gameplay_assets.gameplay_rocket_sound_paths[1],
    gameplay_assets.gameplay_rocket_sound_paths[2],
    gameplay_assets.gameplay_weapon_change_sound_path,
    gameplay_assets.gameplay_jetpack_shutoff_sound_path,
    gameplay_assets.gameplay_place_package_sound_path,
    gameplay_assets.gameplay_slug_death_voice_paths[0],
    gameplay_assets.gameplay_slug_death_voice_paths[1],
    "VOICE/SLUG-DESTROY.OGG",
    "VOICE/SLUG-GOTHIM.OGG",
    "VOICE/SLUG-HESTOOFAST.OGG",
    "VOICE/SLUG-SNAILALERT.OGG",
    "VOICE/SLUG-VICTORY.OGG",
    "VOICE/SLUG-VICTORY2.OGG",
    gameplay_assets.gameplay_slug_hit_voice_paths[0],
    gameplay_assets.gameplay_slug_hit_voice_paths[1],
    gameplay_assets.gameplay_slug_hit_voice_paths[2],
    gameplay_assets.gameplay_asteroid_impact_sound_paths[0],
    gameplay_assets.gameplay_asteroid_impact_sound_paths[1],
    gameplay_assets.gameplay_boing_sound_path,
    gameplay_assets.gameplay_explode_ring_sound_path,
    gameplay_assets.gameplay_slow_ring_sound_path,
    gameplay_assets.gameplay_extra_life_sound_path,
    gameplay_assets.gameplay_package_count_sound_path,
    gameplay_assets.gameplay_completion_init_sound_path,
    gameplay_assets.gameplay_wall_hit_sound_path,
    gameplay_assets.gameplay_invincible_sound_path,
    gameplay_assets.gameplay_perfect_sound_path,
    gameplay_assets.gameplay_postal_warning_sound_path,
};

pub const native_global_voice_set_paths = .{
    gameplay_assets.gameplay_native_voice_damage_paths[0..],
    gameplay_assets.gameplay_native_voice_dying_paths[0..],
    gameplay_assets.gameplay_native_voice_enemies_paths[0..],
    gameplay_assets.gameplay_native_voice_fall_paths[0..],
    gameplay_assets.gameplay_native_voice_misc_paths[0..],
    gameplay_assets.gameplay_native_voice_powerup_paths[0..],
    gameplay_assets.gameplay_native_voice_slow_paths[0..],
    gameplay_assets.gameplay_native_voice_start_paths[0..],
    gameplay_assets.gameplay_native_voice_victory_paths[0..],
    gameplay_assets.gameplay_native_voice_ouch_paths[0..],
    gameplay_assets.gameplay_native_voice_package_paths[0..],
    gameplay_assets.gameplay_native_voice_slugged_paths[0..],
    gameplay_assets.gameplay_native_voice_worm_tunnel_paths[0..],
    gameplay_assets.gameplay_native_voice_tutorial_paths[0..],
    gameplay_assets.gameplay_native_voice_postal_paths[0..],
    gameplay_assets.gameplay_native_voice_supertramp_paths[0..],
};

pub fn nativeGlobalAudioSamplePath(sample_index: usize) ?[]const u8 {
    if (sample_index < native_global_audio_bank_paths.len) {
        return native_global_audio_bank_paths[sample_index];
    }

    var remaining = sample_index - native_global_audio_bank_paths.len;
    inline for (native_global_voice_set_paths) |paths| {
        if (remaining < paths.len) return paths[remaining];
        remaining -= paths.len;
    }
    return null;
}

pub fn nativeGlobalAudioSampleIndexForPath(sample_path: []const u8) ?usize {
    for (native_global_audio_bank_paths, 0..) |path, index| {
        if (std.ascii.eqlIgnoreCase(path, sample_path)) return index;
    }

    var base_index = native_global_audio_bank_paths.len;
    inline for (native_global_voice_set_paths) |paths| {
        for (paths, 0..) |path, index| {
            if (std.ascii.eqlIgnoreCase(path, sample_path)) return base_index + index;
        }
        base_index += paths.len;
    }
    return null;
}

pub fn nativeGameplayVoicePaths(set_id: gameplay_voice.NativeSet) []const []const u8 {
    return switch (set_id) {
        .damage => gameplay_assets.gameplay_native_voice_damage_paths[0..],
        .dying => gameplay_assets.gameplay_native_voice_dying_paths[0..],
        .enemies => gameplay_assets.gameplay_native_voice_enemies_paths[0..],
        .fall => gameplay_assets.gameplay_native_voice_fall_paths[0..],
        .misc => gameplay_assets.gameplay_native_voice_misc_paths[0..],
        .package => gameplay_assets.gameplay_native_voice_package_paths[0..],
        .postal => gameplay_assets.gameplay_native_voice_postal_paths[0..],
        .powerup => gameplay_assets.gameplay_native_voice_powerup_paths[0..],
        .slow => gameplay_assets.gameplay_native_voice_slow_paths[0..],
        .slugged => gameplay_assets.gameplay_native_voice_slugged_paths[0..],
        .start => gameplay_assets.gameplay_native_voice_start_paths[0..],
        .supertramp => gameplay_assets.gameplay_native_voice_supertramp_paths[0..],
        .tutorial => gameplay_assets.gameplay_native_voice_tutorial_paths[0..],
        .ouch => gameplay_assets.gameplay_native_voice_ouch_paths[0..],
        .victory => gameplay_assets.gameplay_native_voice_victory_paths[0..],
        .worm_tunnel => gameplay_assets.gameplay_native_voice_worm_tunnel_paths[0..],
    };
}
