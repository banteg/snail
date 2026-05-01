const std = @import("std");
const rl = @import("raylib");
const archive = @import("archive.zig");

pub const Catalog = struct {
    allocator: std.mem.Allocator,
    dat: archive.Archive,
    texture_entries: []archive.Entry,
    texture_index_by_path: archive.CaseInsensitiveStringHashMap(usize),
    audio_entries: []archive.Entry,
    audio_index_by_path: archive.CaseInsensitiveStringHashMap(usize),
    model_entries: []archive.Entry,
    model_index_by_path: archive.CaseInsensitiveStringHashMap(usize),
    object_entries: []archive.Entry,
    object_index_by_path: archive.CaseInsensitiveStringHashMap(usize),
    segment_entries: []archive.Entry,
    segment_index_by_path: archive.CaseInsensitiveStringHashMap(usize),
    level_entries: []archive.Entry,
    level_index_by_path: archive.CaseInsensitiveStringHashMap(usize),

    pub fn init(allocator: std.mem.Allocator, archive_path: []const u8) !Catalog {
        var dat = try archive.Archive.init(allocator, archive_path);
        errdefer dat.deinit();

        const texture_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".tga");
        errdefer allocator.free(texture_entries);
        var texture_index_by_path = try indexEntriesByPathAlloc(allocator, texture_entries);
        errdefer texture_index_by_path.deinit();

        const audio_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".ogg");
        errdefer allocator.free(audio_entries);
        var audio_index_by_path = try indexEntriesByPathAlloc(allocator, audio_entries);
        errdefer audio_index_by_path.deinit();

        const model_entries = try filterEntriesBySuffixAlloc(allocator, dat.entries, ".x2");
        errdefer allocator.free(model_entries);
        var model_index_by_path = try indexEntriesByPathAlloc(allocator, model_entries);
        errdefer model_index_by_path.deinit();

        const object_entries = try filterObjectEntriesAlloc(allocator, dat.entries);
        errdefer allocator.free(object_entries);
        var object_index_by_path = try indexEntriesByPathAlloc(allocator, object_entries);
        errdefer object_index_by_path.deinit();

        const segment_entries = try filterEntriesByPrefixAndSuffixAlloc(allocator, dat.entries, "SEGMENTS/", ".txt");
        errdefer allocator.free(segment_entries);
        var segment_index_by_path = try indexEntriesByPathAlloc(allocator, segment_entries);
        errdefer segment_index_by_path.deinit();

        const level_entries = try filterEntriesByPrefixAndSuffixAlloc(allocator, dat.entries, "LEVELS/", ".txt");
        errdefer allocator.free(level_entries);
        var level_index_by_path = try indexEntriesByPathAlloc(allocator, level_entries);
        errdefer level_index_by_path.deinit();

        return .{
            .allocator = allocator,
            .dat = dat,
            .texture_entries = texture_entries,
            .texture_index_by_path = texture_index_by_path,
            .audio_entries = audio_entries,
            .audio_index_by_path = audio_index_by_path,
            .model_entries = model_entries,
            .model_index_by_path = model_index_by_path,
            .object_entries = object_entries,
            .object_index_by_path = object_index_by_path,
            .segment_entries = segment_entries,
            .segment_index_by_path = segment_index_by_path,
            .level_entries = level_entries,
            .level_index_by_path = level_index_by_path,
        };
    }

    pub fn deinit(self: *Catalog) void {
        self.level_index_by_path.deinit();
        self.segment_index_by_path.deinit();
        self.object_index_by_path.deinit();
        self.model_index_by_path.deinit();
        self.audio_index_by_path.deinit();
        self.texture_index_by_path.deinit();
        self.allocator.free(self.level_entries);
        self.allocator.free(self.segment_entries);
        self.allocator.free(self.object_entries);
        self.allocator.free(self.model_entries);
        self.allocator.free(self.audio_entries);
        self.allocator.free(self.texture_entries);
        self.dat.deinit();
    }

    pub fn findTextureIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.texture_index_by_path.get(path);
    }

    pub fn findTextureEntry(self: *const Catalog, path: []const u8) ?archive.Entry {
        const index = self.findTextureIndex(path) orelse return null;
        return self.texture_entries[index];
    }

    pub fn findAudioIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.audio_index_by_path.get(path);
    }

    pub fn findAudioEntry(self: *const Catalog, path: []const u8) ?archive.Entry {
        const index = self.findAudioIndex(path) orelse return null;
        return self.audio_entries[index];
    }

    pub fn findModelIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.model_index_by_path.get(path);
    }

    pub fn findObjectIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.object_index_by_path.get(path);
    }

    pub fn findSegmentIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.segment_index_by_path.get(path);
    }

    pub fn findLevelIndex(self: *const Catalog, path: []const u8) ?usize {
        return self.level_index_by_path.get(path);
    }

    pub fn readEntryAlloc(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) ![]u8 {
        return self.dat.readEntryAtAlloc(allocator, entry);
    }

    pub fn readEntryBytes(self: *const Catalog, entry: archive.Entry) ![]const u8 {
        return self.dat.readEntryBytes(entry);
    }

    pub fn loadTexture(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedTexture {
        const decoded = try self.readEntryBytes(entry);

        var image = try rl.loadImageFromMemory(".tga", decoded);
        defer rl.unloadImage(image);
        try bleedTransparentRgb(allocator, &image);

        const texture = try rl.loadTextureFromImage(image);
        rl.setTextureWrap(texture, .clamp);
        rl.setTextureFilter(texture, .bilinear);

        return .{
            .path = entry.path,
            .texture = texture,
        };
    }

    pub fn loadTextureByPath(self: *const Catalog, allocator: std.mem.Allocator, path: []const u8) !LoadedTexture {
        const entry = self.findTextureEntry(path) orelse return error.EntryNotFound;
        return self.loadTexture(allocator, entry);
    }

    pub fn loadSound(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedSound {
        _ = allocator;
        const decoded = try self.readEntryBytes(entry);

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

    pub fn loadSoundByPath(self: *const Catalog, allocator: std.mem.Allocator, path: []const u8) !LoadedSound {
        const entry = self.findAudioEntry(path) orelse return error.EntryNotFound;
        return self.loadSound(allocator, entry);
    }

    pub fn loadMusic(self: *const Catalog, allocator: std.mem.Allocator, entry: archive.Entry) !LoadedMusic {
        _ = allocator;
        const decoded = try self.readEntryBytes(entry);

        const music = try rl.loadMusicStreamFromMemory(".ogg", decoded);
        return .{
            .path = entry.path,
            .music = music,
        };
    }

    pub fn loadMusicByPath(self: *const Catalog, allocator: std.mem.Allocator, path: []const u8) !LoadedMusic {
        const entry = self.findAudioEntry(path) orelse return error.EntryNotFound;
        return self.loadMusic(allocator, entry);
    }
};

fn bleedTransparentRgb(allocator: std.mem.Allocator, image: *rl.Image) !void {
    rl.imageFormat(image, .uncompressed_r8g8b8a8);

    const width: usize = @intCast(image.width);
    const height: usize = @intCast(image.height);
    if (width == 0 or height == 0) return;

    const pixels = @as([*]u8, @ptrCast(image.data))[0 .. width * height * 4];
    try bleedTransparentRgbPixels(allocator, pixels, width, height);
}

fn bleedTransparentRgbPixels(
    allocator: std.mem.Allocator,
    pixels: []u8,
    width: usize,
    height: usize,
) !void {
    std.debug.assert(pixels.len == width * height * 4);

    const source = try allocator.dupe(u8, pixels);
    defer allocator.free(source);

    for (0..height) |y| {
        for (0..width) |x| {
            const offset = ((y * width) + x) * 4;
            if (source[offset + 3] != 0) continue;

            var red_sum: u16 = 0;
            var green_sum: u16 = 0;
            var blue_sum: u16 = 0;
            var count: u16 = 0;

            const y_min = if (y == 0) y else y - 1;
            const y_max = @min(y + 1, height - 1);
            const x_min = if (x == 0) x else x - 1;
            const x_max = @min(x + 1, width - 1);
            for (y_min..y_max + 1) |ny| {
                for (x_min..x_max + 1) |nx| {
                    if (nx == x and ny == y) continue;
                    const neighbor_offset = ((ny * width) + nx) * 4;
                    if (source[neighbor_offset + 3] == 0) continue;
                    red_sum += source[neighbor_offset + 0];
                    green_sum += source[neighbor_offset + 1];
                    blue_sum += source[neighbor_offset + 2];
                    count += 1;
                }
            }
            if (count == 0) continue;

            pixels[offset + 0] = @intCast(red_sum / count);
            pixels[offset + 1] = @intCast(green_sum / count);
            pixels[offset + 2] = @intCast(blue_sum / count);
        }
    }
}

pub const LoadedTexture = struct {
    path: []const u8,
    texture: rl.Texture2D,
    owns_handle: bool = true,

    pub fn borrowed(self: LoadedTexture) LoadedTexture {
        var copy = self;
        copy.owns_handle = false;
        return copy;
    }

    pub fn unload(self: *LoadedTexture) void {
        if (!self.owns_handle) return;
        rl.unloadTexture(self.texture);
        self.owns_handle = false;
    }
};

pub const LoadedSound = struct {
    path: []const u8,
    sound: rl.Sound,
    owns_handle: bool = true,

    pub fn borrowed(self: LoadedSound) LoadedSound {
        var copy = self;
        copy.owns_handle = false;
        return copy;
    }

    pub fn unload(self: *LoadedSound) void {
        if (!self.owns_handle) return;
        if (rl.isSoundPlaying(self.sound)) {
            rl.stopSound(self.sound);
        }
        rl.unloadSound(self.sound);
        self.owns_handle = false;
    }
};

pub const SoundSlot = struct {
    current: ?LoadedSound = null,

    pub fn unload(self: *SoundSlot) void {
        if (self.current) |*sound| {
            sound.unload();
            self.current = null;
        }
    }

    pub fn loadPath(
        self: *SoundSlot,
        store: anytype,
        path: []const u8,
    ) !?*LoadedSound {
        if (self.current) |*sound| {
            if (std.ascii.eqlIgnoreCase(sound.path, path)) return sound;
        }

        self.unload();
        self.current = (try store.sound(path)) orelse return null;
        return &self.current.?;
    }
};

pub const LoadedMusic = struct {
    path: []const u8,
    music: rl.Music,

    pub fn unload(self: *LoadedMusic) void {
        if (rl.isMusicStreamPlaying(self.music)) {
            rl.stopMusicStream(self.music);
        }
        rl.unloadMusicStream(self.music);
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

fn indexEntriesByPathAlloc(
    allocator: std.mem.Allocator,
    entries: []const archive.Entry,
) !archive.CaseInsensitiveStringHashMap(usize) {
    var index_by_path = archive.CaseInsensitiveStringHashMap(usize).init(allocator);
    errdefer index_by_path.deinit();

    for (entries, 0..) |entry, index| {
        try index_by_path.put(entry.path, index);
    }

    return index_by_path;
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

fn filterEntriesByPrefixAndSuffixAlloc(
    allocator: std.mem.Allocator,
    entries: []const archive.Entry,
    prefix: []const u8,
    suffix: []const u8,
) ![]archive.Entry {
    var list: std.ArrayList(archive.Entry) = .empty;
    defer list.deinit(allocator);

    for (entries) |entry| {
        if (std.ascii.startsWithIgnoreCase(entry.path, prefix) and std.ascii.endsWithIgnoreCase(entry.path, suffix)) {
            try list.append(allocator, entry);
        }
    }

    return list.toOwnedSlice(allocator);
}

fn filterObjectEntriesAlloc(
    allocator: std.mem.Allocator,
    entries: []const archive.Entry,
) ![]archive.Entry {
    var list: std.ArrayList(archive.Entry) = .empty;
    defer list.deinit(allocator);

    for (entries) |entry| {
        if (!std.ascii.startsWithIgnoreCase(entry.path, "OBJECTS/")) continue;
        if (!std.ascii.endsWithIgnoreCase(entry.path, "/_OBJECT.TXT")) continue;
        try list.append(allocator, entry);
    }

    return list.toOwnedSlice(allocator);
}

test "transparent texture pixels borrow neighboring color for filtered edges" {
    var pixels = [_]u8{
        255, 255, 255, 0,
        10,  20,  30,  255,
    };

    try bleedTransparentRgbPixels(std.testing.allocator, &pixels, 2, 1);

    try std.testing.expectEqualSlices(u8, &.{ 10, 20, 30, 0 }, pixels[0..4]);
    try std.testing.expectEqualSlices(u8, &.{ 10, 20, 30, 255 }, pixels[4..8]);
}

test "transparent texture pixels average all opaque neighbors" {
    var pixels = [_]u8{
        10,  20,  30,  255,
        255, 255, 255, 0,
        40,  50,  60,  255,
    };

    try bleedTransparentRgbPixels(std.testing.allocator, &pixels, 3, 1);

    try std.testing.expectEqualSlices(u8, &.{ 25, 35, 45, 0 }, pixels[4..8]);
}

test "catalog groups archive entries by asset type" {
    var catalog = try Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    try std.testing.expectEqual(@as(usize, 121), catalog.texture_entries.len);
    try std.testing.expectEqual(@as(usize, 153), catalog.audio_entries.len);
    try std.testing.expectEqual(@as(usize, 124), catalog.model_entries.len);
    try std.testing.expectEqual(@as(usize, 4), catalog.object_entries.len);
    try std.testing.expectEqual(@as(usize, 133), catalog.segment_entries.len);
    try std.testing.expectEqual(@as(usize, 53), catalog.level_entries.len);
}
