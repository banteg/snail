const std = @import("std");

const assets = @import("assets.zig");
const gameplay_assets = @import("gameplay/assets.zig");
const x2 = @import("x2.zig");

pub const SpriteArt = struct {
    slug_frames: [gameplay_assets.gameplay_slug_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_assets.gameplay_slug_sprite_paths.len,
    garbage_variants: [gameplay_assets.gameplay_garbage_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_assets.gameplay_garbage_sprite_paths.len,
    health: ?assets.LoadedTexture = null,
    life: ?assets.LoadedTexture = null,
    jetpack_frames: [gameplay_assets.gameplay_jetpack_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_assets.gameplay_jetpack_sprite_paths.len,
    parcel: ?assets.LoadedTexture = null,
    ring: ?assets.LoadedTexture = null,
    ring_big: ?assets.LoadedTexture = null,
    slow_ring: ?assets.LoadedTexture = null,
    powerup: ?assets.LoadedTexture = null,
    progress_bar: ?assets.LoadedTexture = null,
    progress_bar_lit: ?assets.LoadedTexture = null,
    progress_cursor: ?assets.LoadedTexture = null,
    damage_gauge: ?assets.LoadedTexture = null,
    damage_gauge_full: ?assets.LoadedTexture = null,
    damage_gauge_bright: ?assets.LoadedTexture = null,
    warning: ?assets.LoadedTexture = null,
    explode_big: ?assets.LoadedTexture = null,
    explode_small: ?assets.LoadedTexture = null,
    slug_goo: ?assets.LoadedTexture = null,
    smoke: ?assets.LoadedTexture = null,

    pub fn unload(self: *SpriteArt) void {
        for (&self.slug_frames) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        for (&self.garbage_variants) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        if (self.health) |*texture| {
            texture.unload();
            self.health = null;
        }
        if (self.life) |*texture| {
            texture.unload();
            self.life = null;
        }
        for (&self.jetpack_frames) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        if (self.parcel) |*texture| {
            texture.unload();
            self.parcel = null;
        }
        if (self.ring) |*texture| {
            texture.unload();
            self.ring = null;
        }
        if (self.ring_big) |*texture| {
            texture.unload();
            self.ring_big = null;
        }
        if (self.slow_ring) |*texture| {
            texture.unload();
            self.slow_ring = null;
        }
        if (self.powerup) |*texture| {
            texture.unload();
            self.powerup = null;
        }
        if (self.progress_bar) |*texture| {
            texture.unload();
            self.progress_bar = null;
        }
        if (self.progress_bar_lit) |*texture| {
            texture.unload();
            self.progress_bar_lit = null;
        }
        if (self.progress_cursor) |*texture| {
            texture.unload();
            self.progress_cursor = null;
        }
        if (self.damage_gauge) |*texture| {
            texture.unload();
            self.damage_gauge = null;
        }
        if (self.damage_gauge_full) |*texture| {
            texture.unload();
            self.damage_gauge_full = null;
        }
        if (self.damage_gauge_bright) |*texture| {
            texture.unload();
            self.damage_gauge_bright = null;
        }
        if (self.warning) |*texture| {
            texture.unload();
            self.warning = null;
        }
        if (self.explode_big) |*texture| {
            texture.unload();
            self.explode_big = null;
        }
        if (self.explode_small) |*texture| {
            texture.unload();
            self.explode_small = null;
        }
        if (self.slug_goo) |*texture| {
            texture.unload();
            self.slug_goo = null;
        }
        if (self.smoke) |*texture| {
            texture.unload();
            self.smoke = null;
        }
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

pub fn loadSpriteArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !SpriteArt {
    var art = SpriteArt{};
    errdefer art.unload();

    for (gameplay_assets.gameplay_slug_sprite_paths, 0..) |path, index| {
        art.slug_frames[index] = try catalog.loadTextureByPath(allocator, path);
    }
    for (gameplay_assets.gameplay_garbage_sprite_paths, 0..) |path, index| {
        art.garbage_variants[index] = try catalog.loadTextureByPath(allocator, path);
    }
    art.health = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_health_sprite_path);
    art.life = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_life_sprite_path);
    for (gameplay_assets.gameplay_jetpack_sprite_paths, 0..) |path, index| {
        art.jetpack_frames[index] = try catalog.loadTextureByPath(allocator, path);
    }
    art.parcel = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_parcel_sprite_path);
    art.ring = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_ring_sprite_path);
    art.ring_big = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_ring_big_sprite_path);
    art.slow_ring = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_slow_ring_sprite_path);
    art.powerup = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_powerup_sprite_path);
    art.progress_bar = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_progress_bar_sprite_path);
    art.progress_bar_lit = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_progress_bar_lit_sprite_path);
    art.progress_cursor = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_progress_cursor_sprite_path);
    art.damage_gauge = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_damage_gauge_sprite_path);
    art.damage_gauge_full = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_damage_gauge_full_sprite_path);
    art.damage_gauge_bright = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_damage_gauge_bright_sprite_path);
    art.warning = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_warning_sprite_path);
    art.explode_big = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_explode_big_sprite_path);
    art.explode_small = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_explode_small_sprite_path);
    art.slug_goo = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_slug_goo_sprite_path);
    art.smoke = try catalog.loadTextureByPath(allocator, gameplay_assets.gameplay_smoke_sprite_path);

    return art;
}

pub fn loadSoundFx(allocator: std.mem.Allocator, catalog: *const assets.Catalog, audio_ready: bool) !SoundFx {
    if (!audio_ready) return .{};

    var sound_fx = SoundFx{};
    errdefer sound_fx.unload();

    for (gameplay_assets.gameplay_turbo_fire_sound_paths, 0..) |path, index| {
        sound_fx.turbo_fire[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_assets.gameplay_laser_sound_paths, 0..) |path, index| {
        sound_fx.laser[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_assets.gameplay_rocket_sound_paths, 0..) |path, index| {
        sound_fx.rocket[index] = try catalog.loadSoundByPath(allocator, path);
    }
    sound_fx.cheers = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_cheers_sound_path);
    sound_fx.extra_life = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_extra_life_sound_path);
    sound_fx.weapon_change = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_weapon_change_sound_path);
    sound_fx.heart = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_heart_sound_path);
    sound_fx.jetpack = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_jetpack_sound_path);
    sound_fx.jetpack_shutoff = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_jetpack_shutoff_sound_path);
    sound_fx.slow_ring = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_slow_ring_sound_path);
    sound_fx.invincible = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_invincible_sound_path);
    sound_fx.explode_ring = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_explode_ring_sound_path);
    sound_fx.enemy_fire = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_enemy_fire_sound_path);
    sound_fx.boing = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_boing_sound_path);
    sound_fx.completion_init = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_completion_init_sound_path);
    sound_fx.row_event_confirm = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_row_event_confirm_sound_path);
    sound_fx.place_package = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_place_package_sound_path);
    sound_fx.package_count = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_package_count_sound_path);
    sound_fx.perfect = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_perfect_sound_path);
    for (gameplay_assets.gameplay_powerup_pickup_sound_paths, 0..) |path, index| {
        sound_fx.powerup_pickup[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_assets.gameplay_asteroid_impact_sound_paths, 0..) |path, index| {
        sound_fx.asteroid_impact[index] = try catalog.loadSoundByPath(allocator, path);
    }
    sound_fx.wall_hit = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_wall_hit_sound_path);
    sound_fx.postal_warning = try catalog.loadSoundByPath(allocator, gameplay_assets.gameplay_postal_warning_sound_path);

    return sound_fx;
}

pub fn loadWeaponModelSet(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    set: *WeaponModelSet,
    base_path: []const u8,
    draw_paths: []const []const u8,
    fire_path: ?[]const u8,
) !void {
    if (catalog.findModelIndex(base_path)) |entry_index| {
        set.base = try x2.Uploaded.loadFromArchive(
            allocator,
            catalog,
            catalog.model_entries[entry_index],
            true,
        );
        try set.base.?.enableToonOutline();
    }
    set.draw_frame_count = @intCast(draw_paths.len);
    for (draw_paths, 0..) |path, index| {
        if (catalog.findModelIndex(path)) |entry_index| {
            set.draw_frames[index] = try x2.Uploaded.loadFromArchive(
                allocator,
                catalog,
                catalog.model_entries[entry_index],
                true,
            );
            try set.draw_frames[index].?.enableToonOutline();
        }
    }
    if (fire_path) |path| {
        if (catalog.findModelIndex(path)) |entry_index| {
            set.fire = try x2.Uploaded.loadFromArchive(
                allocator,
                catalog,
                catalog.model_entries[entry_index],
                true,
            );
            try set.fire.?.enableToonOutline();
        }
    }
}
