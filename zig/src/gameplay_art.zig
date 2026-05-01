const std = @import("std");

const assets = @import("assets.zig");
const gameplay_assets = @import("gameplay/assets.zig");
const resource_store = @import("resource_store.zig");
const x2 = @import("x2.zig");

pub const SpriteArt = struct {
    loaded: bool = false,
    slug_frames: [gameplay_assets.gameplay_slug_sprite_paths.len]assets.LoadedTexture = undefined,
    slug_mask: assets.LoadedTexture = undefined,
    ghost: assets.LoadedTexture = undefined,
    garbage_variants: [gameplay_assets.gameplay_garbage_sprite_paths.len]assets.LoadedTexture = undefined,
    health: assets.LoadedTexture = undefined,
    life: assets.LoadedTexture = undefined,
    jetpack_frames: [gameplay_assets.gameplay_jetpack_sprite_paths.len]assets.LoadedTexture = undefined,
    parcel: assets.LoadedTexture = undefined,
    ring: assets.LoadedTexture = undefined,
    ring_big: assets.LoadedTexture = undefined,
    slow_ring: assets.LoadedTexture = undefined,
    slow_ring_big: assets.LoadedTexture = undefined,
    blaster_projectile: assets.LoadedTexture = undefined,
    blaster_trail: assets.LoadedTexture = undefined,
    progress_bar: assets.LoadedTexture = undefined,
    progress_bar_lit: assets.LoadedTexture = undefined,
    progress_cursor: assets.LoadedTexture = undefined,
    damage_gauge: assets.LoadedTexture = undefined,
    damage_gauge_full: assets.LoadedTexture = undefined,
    damage_gauge_bright: assets.LoadedTexture = undefined,
    warning: assets.LoadedTexture = undefined,
    explode_big: assets.LoadedTexture = undefined,
    explode_small: assets.LoadedTexture = undefined,
    slug_goo: assets.LoadedTexture = undefined,
    smoke: assets.LoadedTexture = undefined,

    pub fn unload(self: *SpriteArt) void {
        if (!self.loaded) return;
        for (&self.slug_frames) |*texture| texture.unload();
        self.slug_mask.unload();
        self.ghost.unload();
        for (&self.garbage_variants) |*texture| texture.unload();
        self.health.unload();
        self.life.unload();
        for (&self.jetpack_frames) |*texture| texture.unload();
        self.parcel.unload();
        self.ring.unload();
        self.ring_big.unload();
        self.slow_ring.unload();
        self.slow_ring_big.unload();
        self.blaster_projectile.unload();
        self.blaster_trail.unload();
        self.progress_bar.unload();
        self.progress_bar_lit.unload();
        self.progress_cursor.unload();
        self.damage_gauge.unload();
        self.damage_gauge_full.unload();
        self.damage_gauge_bright.unload();
        self.warning.unload();
        self.explode_big.unload();
        self.explode_small.unload();
        self.slug_goo.unload();
        self.smoke.unload();
        self.loaded = false;
    }
};

pub const SoundFx = struct {
    turbo_fire: [gameplay_assets.gameplay_turbo_fire_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_assets.gameplay_turbo_fire_sound_paths.len,
    laser: [gameplay_assets.gameplay_laser_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_assets.gameplay_laser_sound_paths.len,
    rocket: [gameplay_assets.gameplay_rocket_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_assets.gameplay_rocket_sound_paths.len,
    cheers: ?assets.LoadedSound = null,
    extra_life: ?assets.LoadedSound = null,
    weapon_change: ?assets.LoadedSound = null,
    heart: ?assets.LoadedSound = null,
    jetpack: ?assets.LoadedSound = null,
    jetpack_shutoff: ?assets.LoadedSound = null,
    slow_ring: ?assets.LoadedSound = null,
    invincible: ?assets.LoadedSound = null,
    explode_ring: ?assets.LoadedSound = null,
    enemy_fire: ?assets.LoadedSound = null,
    boing: ?assets.LoadedSound = null,
    completion_init: ?assets.LoadedSound = null,
    row_event_confirm: ?assets.LoadedSound = null,
    place_package: ?assets.LoadedSound = null,
    package_count: ?assets.LoadedSound = null,
    perfect: ?assets.LoadedSound = null,
    powerup_pickup: [gameplay_assets.gameplay_powerup_pickup_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_assets.gameplay_powerup_pickup_sound_paths.len,
    asteroid_impact: [gameplay_assets.gameplay_asteroid_impact_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_assets.gameplay_asteroid_impact_sound_paths.len,
    wall_hit: ?assets.LoadedSound = null,
    postal_warning: ?assets.LoadedSound = null,

    pub fn unload(self: *SoundFx) void {
        inline for (comptime std.meta.fieldNames(SoundFx)) |field_name| {
            const field = &@field(self, field_name);
            switch (@typeInfo(@TypeOf(field.*))) {
                .array => {
                    for (field) |*entry| {
                        if (entry.*) |*sound| {
                            sound.unload();
                            entry.* = null;
                        }
                    }
                },
                else => {
                    if (field.*) |*sound| {
                        sound.unload();
                        field.* = null;
                    }
                },
            }
        }
    }
};

pub const max_mount_draw_frames = 6;

pub const WeaponModelSet = struct {
    base: ?x2.Uploaded = null,
    draw_frames: [max_mount_draw_frames]?x2.Uploaded = [_]?x2.Uploaded{null} ** max_mount_draw_frames,
    draw_frame_count: u8 = 0,
    fire: ?x2.Uploaded = null,

    pub fn unload(self: *WeaponModelSet) void {
        if (self.base) |*model| {
            model.deinit();
            self.base = null;
        }
        for (&self.draw_frames) |*model| {
            if (model.*) |*loaded| {
                loaded.deinit();
                model.* = null;
            }
        }
        if (self.fire) |*model| {
            model.deinit();
            self.fire = null;
        }
        self.draw_frame_count = 0;
    }

    pub fn currentModel(self: *const WeaponModelSet, draw_ticks: u8, fire_ticks: u8, hide_ticks: u8) ?*const x2.Uploaded {
        if (fire_ticks > 0) {
            if (self.fire) |*model| return model;
        }
        if (draw_ticks > 0 and self.draw_frame_count > 0) {
            const capped_ticks = @min(draw_ticks, self.draw_frame_count);
            const frame_index = self.draw_frame_count - capped_ticks;
            if (self.draw_frames[frame_index]) |*model| return model;
        }
        if (hide_ticks > 0 and self.draw_frame_count > 0) {
            const capped_ticks = @min(hide_ticks, self.draw_frame_count);
            const frame_index = capped_ticks - 1;
            if (self.draw_frames[frame_index]) |*model| return model;
        }
        if (self.base) |*model| return model;
        return null;
    }
};

pub const InvincibleModelSet = struct {
    frames: [gameplay_assets.gameplay_invincible_model_paths.len]?x2.Uploaded = [_]?x2.Uploaded{null} ** gameplay_assets.gameplay_invincible_model_paths.len,

    pub fn unload(self: *InvincibleModelSet) void {
        for (&self.frames) |*model| {
            if (model.*) |*loaded| {
                loaded.deinit();
                model.* = null;
            }
        }
    }

    pub fn currentModel(self: *const InvincibleModelSet, render_time_seconds: f64) ?*const x2.Uploaded {
        const frame_count = comptime gameplay_assets.gameplay_invincible_model_paths.len;
        const frame_index: usize = @intFromFloat(@mod(@floor(render_time_seconds * 10.0), @as(f64, @floatFromInt(frame_count))));
        if (self.frames[frame_index]) |*model| return model;
        if (self.frames[0]) |*model| return model;
        return null;
    }
};

pub const JetpackModelSet = struct {
    frames: [gameplay_assets.gameplay_jetpack_thrust_model_paths.len]?x2.Uploaded = [_]?x2.Uploaded{null} ** gameplay_assets.gameplay_jetpack_thrust_model_paths.len,

    pub fn unload(self: *JetpackModelSet) void {
        for (&self.frames) |*model| {
            if (model.*) |*loaded| {
                loaded.deinit();
                model.* = null;
            }
        }
    }

    pub fn currentModel(
        self: *const JetpackModelSet,
        draw_ticks: u8,
        active: bool,
        hide_ticks: u8,
        render_time_seconds: f64,
    ) ?*const x2.Uploaded {
        const frame_count = comptime gameplay_assets.gameplay_jetpack_thrust_model_paths.len;
        if (draw_ticks > 0) {
            const capped_ticks = @min(draw_ticks, frame_count);
            const frame_index = frame_count - capped_ticks;
            if (self.frames[frame_index]) |*model| return model;
        }
        if (active) {
            const frame_index: usize = @intFromFloat(@mod(@floor(render_time_seconds * 10.0), @as(f64, @floatFromInt(frame_count))));
            if (self.frames[frame_index]) |*model| return model;
        }
        if (hide_ticks > 0) {
            const capped_ticks = @min(hide_ticks, frame_count);
            const frame_index = capped_ticks - 1;
            if (self.frames[frame_index]) |*model| return model;
        }
        return null;
    }
};

pub fn loadSpriteArt(store: *resource_store.Store) !SpriteArt {
    var art = SpriteArt{};
    errdefer art.unload();

    for (gameplay_assets.gameplay_slug_sprite_paths, 0..) |path, index| {
        art.slug_frames[index] = try store.texture(path);
    }
    art.slug_mask = try store.texture(gameplay_assets.gameplay_slug_mask_sprite_path);
    art.ghost = try store.texture(gameplay_assets.gameplay_ghost_sprite_path);
    for (gameplay_assets.gameplay_garbage_sprite_paths, 0..) |path, index| {
        art.garbage_variants[index] = try store.texture(path);
    }
    art.health = try store.texture(gameplay_assets.gameplay_health_sprite_path);
    art.life = try store.texture(gameplay_assets.gameplay_life_sprite_path);
    for (gameplay_assets.gameplay_jetpack_sprite_paths, 0..) |path, index| {
        art.jetpack_frames[index] = try store.texture(path);
    }
    art.parcel = try store.texture(gameplay_assets.gameplay_parcel_sprite_path);
    art.ring = try store.texture(gameplay_assets.gameplay_ring_sprite_path);
    art.ring_big = try store.texture(gameplay_assets.gameplay_ring_big_sprite_path);
    art.slow_ring = try store.texture(gameplay_assets.gameplay_slow_ring_sprite_path);
    art.slow_ring_big = try store.texture(gameplay_assets.gameplay_slow_ring_big_sprite_path);
    art.blaster_projectile = try store.texture(gameplay_assets.gameplay_blaster_projectile_sprite_path);
    art.blaster_trail = try store.texture(gameplay_assets.gameplay_blaster_trail_sprite_path);
    art.progress_bar = try store.texture(gameplay_assets.gameplay_progress_bar_sprite_path);
    art.progress_bar_lit = try store.texture(gameplay_assets.gameplay_progress_bar_lit_sprite_path);
    art.progress_cursor = try store.texture(gameplay_assets.gameplay_progress_cursor_sprite_path);
    art.damage_gauge = try store.texture(gameplay_assets.gameplay_damage_gauge_sprite_path);
    art.damage_gauge_full = try store.texture(gameplay_assets.gameplay_damage_gauge_full_sprite_path);
    art.damage_gauge_bright = try store.texture(gameplay_assets.gameplay_damage_gauge_bright_sprite_path);
    art.warning = try store.texture(gameplay_assets.gameplay_warning_sprite_path);
    art.explode_big = try store.texture(gameplay_assets.gameplay_explode_big_sprite_path);
    art.explode_small = try store.texture(gameplay_assets.gameplay_explode_small_sprite_path);
    art.slug_goo = try store.texture(gameplay_assets.gameplay_slug_goo_sprite_path);
    art.smoke = try store.texture(gameplay_assets.gameplay_smoke_sprite_path);

    art.loaded = true;
    return art;
}

pub fn loadSoundFx(store: *resource_store.Store) !SoundFx {
    var sound_fx = SoundFx{};
    errdefer sound_fx.unload();

    for (gameplay_assets.gameplay_turbo_fire_sound_paths, 0..) |path, index| {
        sound_fx.turbo_fire[index] = try store.sound(path);
    }
    for (gameplay_assets.gameplay_laser_sound_paths, 0..) |path, index| {
        sound_fx.laser[index] = try store.sound(path);
    }
    for (gameplay_assets.gameplay_rocket_sound_paths, 0..) |path, index| {
        sound_fx.rocket[index] = try store.sound(path);
    }
    sound_fx.cheers = try store.sound(gameplay_assets.gameplay_cheers_sound_path);
    sound_fx.extra_life = try store.sound(gameplay_assets.gameplay_extra_life_sound_path);
    sound_fx.weapon_change = try store.sound(gameplay_assets.gameplay_weapon_change_sound_path);
    sound_fx.heart = try store.sound(gameplay_assets.gameplay_heart_sound_path);
    sound_fx.jetpack = try store.sound(gameplay_assets.gameplay_jetpack_sound_path);
    sound_fx.jetpack_shutoff = try store.sound(gameplay_assets.gameplay_jetpack_shutoff_sound_path);
    sound_fx.slow_ring = try store.sound(gameplay_assets.gameplay_slow_ring_sound_path);
    sound_fx.invincible = try store.sound(gameplay_assets.gameplay_invincible_sound_path);
    sound_fx.explode_ring = try store.sound(gameplay_assets.gameplay_explode_ring_sound_path);
    sound_fx.enemy_fire = try store.sound(gameplay_assets.gameplay_enemy_fire_sound_path);
    sound_fx.boing = try store.sound(gameplay_assets.gameplay_boing_sound_path);
    sound_fx.completion_init = try store.sound(gameplay_assets.gameplay_completion_init_sound_path);
    sound_fx.row_event_confirm = try store.sound(gameplay_assets.gameplay_row_event_confirm_sound_path);
    sound_fx.place_package = try store.sound(gameplay_assets.gameplay_place_package_sound_path);
    sound_fx.package_count = try store.sound(gameplay_assets.gameplay_package_count_sound_path);
    sound_fx.perfect = try store.sound(gameplay_assets.gameplay_perfect_sound_path);
    for (gameplay_assets.gameplay_powerup_pickup_sound_paths, 0..) |path, index| {
        sound_fx.powerup_pickup[index] = try store.sound(path);
    }
    for (gameplay_assets.gameplay_asteroid_impact_sound_paths, 0..) |path, index| {
        sound_fx.asteroid_impact[index] = try store.sound(path);
    }
    sound_fx.wall_hit = try store.sound(gameplay_assets.gameplay_wall_hit_sound_path);
    sound_fx.postal_warning = try store.sound(gameplay_assets.gameplay_postal_warning_sound_path);

    return sound_fx;
}

pub fn loadWeaponModelSet(
    store: *resource_store.Store,
    set: *WeaponModelSet,
    base_path: []const u8,
    draw_paths: []const []const u8,
    fire_path: ?[]const u8,
) !void {
    if (store.catalog.findModelIndex(base_path) != null) {
        set.base = try store.model(base_path, .{ .toon_outline = true });
    }
    set.draw_frame_count = @intCast(draw_paths.len);
    for (draw_paths, 0..) |path, index| {
        if (store.catalog.findModelIndex(path) != null) {
            set.draw_frames[index] = try store.model(path, .{ .toon_outline = true });
        }
    }
    if (fire_path) |path| {
        if (store.catalog.findModelIndex(path) != null) {
            set.fire = try store.model(path, .{ .toon_outline = true });
        }
    }
}
