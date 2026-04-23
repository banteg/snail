const std = @import("std");

const archive = @import("archive.zig");
const assets = @import("assets.zig");

pub const Store = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
    audio_ready: bool,
    texture_cache: archive.CaseInsensitiveStringHashMap(assets.LoadedTexture),
    sound_cache: archive.CaseInsensitiveStringHashMap(assets.LoadedSound),

    pub fn init(allocator: std.mem.Allocator, archive_path: []const u8, audio_ready: bool) !Store {
        var catalog = try assets.Catalog.init(allocator, archive_path);
        errdefer catalog.deinit();

        return .{
            .allocator = allocator,
            .catalog = catalog,
            .audio_ready = audio_ready,
            .texture_cache = archive.CaseInsensitiveStringHashMap(assets.LoadedTexture).init(allocator),
            .sound_cache = archive.CaseInsensitiveStringHashMap(assets.LoadedSound).init(allocator),
        };
    }

    pub fn deinit(self: *Store) void {
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
};
