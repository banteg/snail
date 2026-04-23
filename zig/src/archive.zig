const std = @import("std");

const io = std.Options.debug_io;

pub const probe_size = 0x7c;
pub const entry_size = 12;

pub const Entry = struct {
    path: []const u8,
    data_offset: usize,
    size: usize,
};

pub const CaseInsensitiveStringContext = struct {
    pub fn hash(_: @This(), value: []const u8) u64 {
        var hasher = std.hash.Wyhash.init(0);
        for (value) |byte| {
            const lower = std.ascii.toLower(byte);
            hasher.update(&[_]u8{lower});
        }
        return hasher.final();
    }

    pub fn eql(_: @This(), a: []const u8, b: []const u8) bool {
        return std.ascii.eqlIgnoreCase(a, b);
    }
};

pub fn CaseInsensitiveStringHashMap(comptime V: type) type {
    return std.HashMap([]const u8, V, CaseInsensitiveStringContext, std.hash_map.default_max_load_percentage);
}

pub const Archive = struct {
    allocator: std.mem.Allocator,
    source_path: []const u8,
    index_blob: []u8,
    entries: []Entry,
    entry_bytes: [][]u8,
    path_index: CaseInsensitiveStringHashMap(usize),

    pub fn init(allocator: std.mem.Allocator, path: []const u8) !Archive {
        const source_path = try allocator.dupe(u8, path);
        errdefer allocator.free(source_path);

        const file_bytes = try std.Io.Dir.cwd().readFileAlloc(io, path, allocator, .limited(std.math.maxInt(usize)));
        defer allocator.free(file_bytes);

        if (file_bytes.len < 12) {
            return error.InvalidArchive;
        }

        var probe_buf: [probe_size]u8 = [_]u8{0} ** probe_size;
        const probe_len = @min(file_bytes.len, probe_buf.len);
        @memcpy(probe_buf[0..probe_len], file_bytes[0..probe_len]);
        xorDecodeInPlace(probe_buf[0..probe_len], 0);

        const entry_count = readU32(probe_buf[0..4]);
        const index_size = readU32(probe_buf[8..12]);
        const minimum_size = 4 + entry_count * entry_size;
        if (entry_count == 0 or index_size < minimum_size or index_size > file_bytes.len) {
            return error.InvalidArchive;
        }

        const index_blob = try allocator.dupe(u8, file_bytes[0..index_size]);
        errdefer allocator.free(index_blob);
        xorDecodeInPlace(index_blob, 0);

        const entries = try allocator.alloc(Entry, entry_count);
        errdefer allocator.free(entries);
        const entry_bytes = try allocator.alloc([]u8, entry_count);
        errdefer allocator.free(entry_bytes);
        var decoded_entry_count: usize = 0;
        errdefer {
            for (entry_bytes[0..decoded_entry_count]) |decoded| {
                allocator.free(decoded);
            }
        }
        var path_index = CaseInsensitiveStringHashMap(usize).init(allocator);
        errdefer path_index.deinit();

        for (entries, 0..) |*entry, entry_index| {
            const record_offset = 4 + entry_index * entry_size;
            const path_offset = readU32(index_blob[record_offset..][0..4]);
            const data_offset = readU32(index_blob[record_offset + 4 ..][0..4]);
            const size = readU32(index_blob[record_offset + 8 ..][0..4]);

            const end_offset = try std.math.add(usize, data_offset, size);
            if (path_offset >= index_blob.len or end_offset > file_bytes.len) {
                return error.InvalidArchive;
            }

            entry.* = .{
                .path = try readCString(index_blob, path_offset),
                .data_offset = data_offset,
                .size = size,
            };

            try path_index.put(entry.path, entry_index);
        }

        for (entries, 0..) |entry, entry_index| {
            const start = entry.data_offset;
            const end = start + entry.size;
            entry_bytes[entry_index] = try allocator.dupe(u8, file_bytes[start..end]);
            xorDecodeInPlace(entry_bytes[entry_index], start);
            decoded_entry_count += 1;
        }

        return .{
            .allocator = allocator,
            .source_path = source_path,
            .index_blob = index_blob,
            .entries = entries,
            .entry_bytes = entry_bytes,
            .path_index = path_index,
        };
    }

    pub fn deinit(self: *Archive) void {
        self.path_index.deinit();
        for (self.entry_bytes) |decoded| {
            self.allocator.free(decoded);
        }
        self.allocator.free(self.entry_bytes);
        self.allocator.free(self.entries);
        self.allocator.free(self.index_blob);
        self.allocator.free(self.source_path);
    }

    pub fn entryByPath(self: *const Archive, asset_path: []const u8) ?Entry {
        const entry_index = self.path_index.get(asset_path) orelse return null;
        return self.entries[entry_index];
    }

    pub fn readEntryAlloc(self: *const Archive, allocator: std.mem.Allocator, asset_path: []const u8) ![]u8 {
        const entry = self.entryByPath(asset_path) orelse return error.EntryNotFound;
        return self.readEntryAtAlloc(allocator, entry);
    }

    pub fn readEntryAtAlloc(self: *const Archive, allocator: std.mem.Allocator, entry: Entry) ![]u8 {
        const entry_index = self.path_index.get(entry.path) orelse return error.EntryNotFound;
        return allocator.dupe(u8, self.entry_bytes[entry_index]);
    }
};

pub fn xorMask(index: usize) u8 {
    const low: u8 = @truncate(index);
    return (low *% low) ^ (low *% 3);
}

pub fn xorDecodeInPlace(buffer: []u8, start_offset: usize) void {
    for (buffer, 0..) |*byte, offset| {
        byte.* ^= xorMask(start_offset + offset);
    }
}

fn readCString(blob: []const u8, offset: usize) ![]const u8 {
    const relative_end = std.mem.indexOfScalar(u8, blob[offset..], 0) orelse return error.InvalidArchive;
    return blob[offset .. offset + relative_end];
}

fn readU32(buffer: []const u8) usize {
    return std.mem.readInt(u32, buffer[0..4], .little);
}

test "parse known archive layout" {
    var archive = try Archive.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer archive.deinit();

    try std.testing.expectEqual(@as(usize, 603), archive.entries.len);
    try std.testing.expectEqualStrings("MUSIC/1.OGG", archive.entries[0].path);
    try std.testing.expectEqual(@as(usize, 20789), archive.entries[0].data_offset);
    try std.testing.expectEqual(@as(usize, 246566), archive.entries[0].size);
    try std.testing.expectEqualStrings("BASS.DLL", archive.entries[archive.entries.len - 1].path);
}

test "decode representative archive members" {
    var archive = try Archive.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer archive.deinit();

    const ogg = try archive.readEntryAlloc(std.testing.allocator, "MUSIC/1.OGG");
    defer std.testing.allocator.free(ogg);
    try std.testing.expectEqualSlices(u8, "OggS", ogg[0..4]);

    const texture = try archive.readEntryAlloc(std.testing.allocator, "OBJECTS/FONT/FONT-MENU-HOVER.TGA");
    defer std.testing.allocator.free(texture);
    try std.testing.expectEqual(@as(u8, 0), texture[0]);
    try std.testing.expectEqual(@as(u8, 0), texture[1]);
    try std.testing.expectEqual(@as(u8, 2), texture[2]);

    const dll = try archive.readEntryAlloc(std.testing.allocator, "BASS.DLL");
    defer std.testing.allocator.free(dll);
    try std.testing.expectEqualSlices(u8, "MZ", dll[0..2]);

    try std.testing.expect(archive.entryByPath("music/1.ogg") != null);
}
