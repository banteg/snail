const std = @import("std");
const rl = @import("raylib");
const archive = @import("archive.zig");

pub const Catalog = struct {
    allocator: std.mem.Allocator,
    dat: archive.Archive,
    texture_entries: []archive.Entry,
    audio_entries: []archive.Entry,
    model_entries: []archive.Entry,

    pub fn init(allocator: std.mem.Allocator, archive_path: []const u8) !Catalog {
        var dat = try archive.Archive.init(allocator, archive_path);
        errdefer dat.deinit();

        const texture_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".tga");
        errdefer allocator.free(texture_entries);

        const audio_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".ogg");
        errdefer allocator.free(audio_entries);

        const model_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".x2");
        errdefer allocator.free(model_entries);

        return .{
            .allocator = allocator,
            .dat = dat,
            .texture_entries = texture_entries,
            .audio_entries = audio_entries,
            .model_entries = model_entries,
        };
    }

    pub fn deinit(self: *Catalog) void {
        self.allocator.free(self.model_entries);
        self.allocator.free(self.audio_entries);
        self.allocator.free(self.texture_entries);
        self.dat.deinit();
    }

    pub fn findTextureIndex(self: *const Catalog, path: []const u8) ?usize {
        return findEntryIndexByPath(self.texture_entries, path);
    }

    pub fn findAudioIndex(self: *const Catalog, path: []const u8) ?usize {
        return findEntryIndexByPath(self.audio_entries, path);
    }

    pub fn findModelIndex(self: *const Catalog, path: []const u8) ?usize {
        return findEntryIndexByPath(self.model_entries, path);
    }

    pub fn readEntryAlloc(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) ![]u8 {
        return self.dat.readEntryAtAlloc(allocator, entry);
    }

    pub fn loadTexture(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedTexture {
        const decoded = try self.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        const image = try rl.loadImageFromMemory(".tga", decoded);
        defer rl.unloadImage(image);

        const texture = try rl.loadTextureFromImage(image);
        rl.setTextureFilter(texture, .bilinear);

        return .{
            .path = entry.path,
            .texture = texture,
        };
    }

    pub fn loadSound(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedSound {
        const decoded = try self.readEntryAlloc(allocator, entry);
        defer allocator.free(decoded);

        const wave = try rl.loadWaveFromMemory(".ogg", decoded);
        defer rl.unloadWave(wave);

        const sound = rl.loadSoundFromWave(wave);
        if (!rl.isSoundValid(sound)) {
            return error.LoadSound;
        }

        return .{
            .path = entry.path,
            .sound = sound,
        };
    }

    pub fn loadMusic(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedMusic {
        const decoded = try self.readEntryAlloc(allocator, entry);
        errdefer allocator.free(decoded);

        const music = try rl.loadMusicStreamFromMemory(".ogg", decoded);
        return .{
            .allocator = allocator,
            .path = entry.path,
            .bytes = decoded,
            .music = music,
        };
    }
};

pub const LoadedTexture = struct {
    path: []const u8,
    texture: rl.Texture2D,

    pub fn unload(self: *LoadedTexture) void {
        rl.unloadTexture(self.texture);
    }
};

pub const LoadedSound = struct {
    path: []const u8,
    sound: rl.Sound,

    pub fn unload(self: *LoadedSound) void {
        if (rl.isSoundPlaying(self.sound)) {
            rl.stopSound(self.sound);
        }
        rl.unloadSound(self.sound);
    }
};

pub const LoadedMusic = struct {
    allocator: std.mem.Allocator,
    path: []const u8,
    bytes: []u8,
    music: rl.Music,

    pub fn unload(self: *LoadedMusic) void {
        if (rl.isMusicStreamPlaying(self.music)) {
            rl.stopMusicStream(self.music);
        }
        rl.unloadMusicStream(self.music);
        self.allocator.free(self.bytes);
    }
};

pub fn findEntryIndexByPath(entries: []const archive.Entry, path: []const u8) ?usize {
    for (entries, 0..) |entry, index| {
        if (std.ascii.eqlIgnoreCase(entry.path, path)) {
            return index;
        }
    }
    return null;
}

fn filterEntriesBySuffixAlloc(
    allocator: std.mem.Allocator,
    entries: []const archive.Entry,
    suffix: []const u8,
) ![]archive.Entry {
    var list: std.ArrayList(archive.Entry) = .empty;
    defer list.deinit(allocator);

    for (entries) |entry| {
        if (std.ascii.endsWithIgnoreCase(entry.path, suffix)) {
            try list.append(allocator, entry);
        }
    }

    return list.toOwnedSlice(allocator);
}

test "catalog groups archive entries by asset type" {
    var catalog = try Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    try std.testing.expectEqual(@as(usize, 121), catalog.texture_entries.len);
    try std.testing.expectEqual(@as(usize, 153), catalog.audio_entries.len);
    try std.testing.expectEqual(@as(usize, 124), catalog.model_entries.len);
}
