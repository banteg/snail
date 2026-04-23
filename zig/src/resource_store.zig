const std = @import("std");

const archive = @import("archive.zig");
const assets = @import("assets.zig");
const x2 = @import("x2.zig");

pub const ModelOptions = struct {
    flip_v: bool = true,
    toon_outline: bool = false,
};

pub const Store = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
    audio_ready: bool,
    texture_cache: archive.CaseInsensitiveStringHashMap(assets.LoadedTexture),
    sound_cache: archive.CaseInsensitiveStringHashMap(assets.LoadedSound),
    model_cache: [2]archive.CaseInsensitiveStringHashMap(x2.Uploaded),

    pub fn init(allocator: std.mem.Allocator, archive_path: []const u8, audio_ready: bool) !Store {
        var catalog = try assets.Catalog.init(allocator, archive_path);
        errdefer catalog.deinit();

        return .{
            .allocator = allocator,
            .catalog = catalog,
            .audio_ready = audio_ready,
            .texture_cache = archive.CaseInsensitiveStringHashMap(assets.LoadedTexture).init(allocator),
            .sound_cache = archive.CaseInsensitiveStringHashMap(assets.LoadedSound).init(allocator),
            .model_cache = .{
                archive.CaseInsensitiveStringHashMap(x2.Uploaded).init(allocator),
                archive.CaseInsensitiveStringHashMap(x2.Uploaded).init(allocator),
            },
        };
    }

    pub fn deinit(self: *Store) void {
        for (&self.model_cache) |*cache| {
            var model_values = cache.valueIterator();
            while (model_values.next()) |loaded_model| {
                loaded_model.deinit();
            }
            cache.deinit();
        }

        var sound_values = self.sound_cache.valueIterator();
        while (sound_values.next()) |loaded_sound| {
            loaded_sound.unload();
        }
        self.sound_cache.deinit();

        var texture_values = self.texture_cache.valueIterator();
        while (texture_values.next()) |loaded_texture| {
            loaded_texture.unload();
        }
        self.texture_cache.deinit();

        self.catalog.deinit();
    }

    pub fn texture(self: *Store, path: []const u8) !assets.LoadedTexture {
        const entry = self.catalog.findTextureEntry(path) orelse return error.EntryNotFound;
        if (self.texture_cache.getPtr(entry.path)) |loaded| return loaded.borrowed();

        const loaded = try self.catalog.loadTexture(self.allocator, entry);
        errdefer {
            var owned = loaded;
            owned.unload();
        }
        try self.texture_cache.put(entry.path, loaded);
        return self.texture_cache.getPtr(entry.path).?.borrowed();
    }

    pub fn sound(self: *Store, path: []const u8) !?assets.LoadedSound {
        if (!self.audio_ready) return null;

        const entry = self.catalog.findAudioEntry(path) orelse return error.EntryNotFound;
        if (self.sound_cache.getPtr(entry.path)) |loaded| return loaded.borrowed();

        const loaded = try self.catalog.loadSound(self.allocator, entry);
        errdefer {
            var owned = loaded;
            owned.unload();
        }
        try self.sound_cache.put(entry.path, loaded);
        return self.sound_cache.getPtr(entry.path).?.borrowed();
    }

    pub fn model(self: *Store, path: []const u8, options: ModelOptions) !x2.Uploaded {
        const entry_index = self.catalog.findModelIndex(path) orelse return error.EntryNotFound;
        const entry = self.catalog.model_entries[entry_index];
        const cache = &self.model_cache[@intFromBool(options.flip_v)];

        if (cache.getPtr(entry.path)) |loaded| {
            if (options.toon_outline) try loaded.enableToonOutline();
            return loaded.borrowed();
        }

        var loaded = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            options.flip_v,
        );
        errdefer loaded.deinit();
        if (options.toon_outline) try loaded.enableToonOutline();
        try cache.put(entry.path, loaded);
        return cache.getPtr(entry.path).?.borrowed();
    }
};
