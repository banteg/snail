const std = @import("std");
const archive = @import("archive.zig");
const runtime_state = @import("runtime_state.zig");

pub const visible_entry_count = 10;
pub const bank_entry_count = 11;
pub const completion_entry_count = 0x33;
pub const name_capacity = 32;
pub const compact_name_capacity = 0x14;
const compact_record_header_size = 0x88;
const compact_record_name_offset = 0x5c;
const compact_record_name_len = compact_name_capacity;
const compact_record_bank_selector_offset = 0x3c;
const compact_record_entry_index_offset = 0x40;
const compact_record_score_offset = 0x04;
const compact_record_checksum_offset = 0x28;
const compact_record_replay_sample_count_offset = 0x74;

pub const Mode = enum {
    postal,
    challenge,

    pub fn label(self: Mode) []const u8 {
        return switch (self) {
            .postal => "Postal Scores",
            .challenge => "Challenge Scores",
        };
    }
};

pub const Entry = struct {
    score: u32 = 0,
    has_replay: bool = false,
    name_len: usize = 0,
    name_buf: [name_capacity]u8 = [_]u8{0} ** name_capacity,
    raw_record: ?[]u8 = null,

    pub fn name(self: *const Entry) []const u8 {
        return self.name_buf[0..self.name_len];
    }

    pub fn setName(self: *Entry, value: []const u8) void {
        const clipped = value[0..@min(value.len, self.name_buf.len)];
        @memset(&self.name_buf, 0);
        @memcpy(self.name_buf[0..clipped.len], clipped);
        self.name_len = clipped.len;
    }

    pub fn isActive(self: *const Entry) bool {
        return self.score != 0 or self.name_len != 0 or self.has_replay;
    }

    pub fn deinit(self: *Entry, allocator: std.mem.Allocator) void {
        if (self.raw_record) |record| {
            allocator.free(record);
            self.raw_record = null;
        }
    }

    fn setRawRecord(self: *Entry, allocator: std.mem.Allocator, record: []const u8) !void {
        self.deinit(allocator);
        self.raw_record = try allocator.dupe(u8, record);
    }
};

pub const InsertResult = struct {
    rank: ?usize = null,
    improved: bool = false,
};

// PORT(partial): this matches the recovered startup table layout more closely:
// 11-entry postal and challenge banks, a 51-entry completion bank, plus a scratch entry.
// We still do not port the full cRSubHighScore save/edit/runtime overlay yet.
pub const Tables = struct {
    postal: [bank_entry_count]Entry,
    challenge: [bank_entry_count]Entry,
    completion: [completion_entry_count]Entry,
    scratch: Entry,

    pub fn initDefault() Tables {
        return .{
            .postal = blankEntries(),
            .challenge = blankEntries(),
            .completion = blankCompletionEntries(),
            .scratch = .{},
        };
    }

    pub fn deinit(self: *Tables, allocator: std.mem.Allocator) void {
        for (&self.postal) |*entry| entry.deinit(allocator);
        for (&self.challenge) |*entry| entry.deinit(allocator);
        for (&self.completion) |*entry| entry.deinit(allocator);
        self.scratch.deinit(allocator);
    }

    pub fn entries(self: *const Tables, mode: Mode) []const Entry {
        return switch (mode) {
            .postal => self.postal[0..],
            .challenge => self.challenge[0..],
        };
    }

    pub fn visibleEntries(self: *const Tables, mode: Mode) []const Entry {
        return self.entries(mode)[0..visible_entry_count];
    }

    pub fn addArcade(self: *Tables, entry: Entry) InsertResult {
        return .{
            .rank = insertDescending(self.postal[0..], entry),
            .improved = false,
        };
    }

    pub fn addSurvival(self: *Tables, entry: Entry) InsertResult {
        return .{
            .rank = insertDescending(self.challenge[0..], entry),
            .improved = false,
        };
    }

    pub fn addTimeTrial(self: *Tables, route_index: usize, entry: Entry) InsertResult {
        if (route_index == 0) return .{};
        const completion_index = route_index - 1;
        if (completion_index >= self.completion.len) return .{};

        const current = &self.completion[completion_index];
        if (!current.isActive() or entry.score < current.score) {
            current.* = entry;
            return .{
                .rank = completion_index,
                .improved = true,
            };
        }

        return .{};
    }

    // PORT(partial): this reads the compact score overlays from ScoreA/B/C.dat,
    // but only surfaces score, name, replay presence, and raw record preservation in the current port.
    pub fn loadFromRuntimeRoot(self: *Tables, allocator: std.mem.Allocator, root_path: []const u8) !void {
        self.deinit(allocator);
        self.* = Tables.initDefault();
        try loadBankFile(allocator, root_path, .score_a, self);
        try loadBankFile(allocator, root_path, .score_b, self);
        try loadBankFile(allocator, root_path, .score_c, self);
    }

    // PORT(partial): this writes compact ScoreA/B/C overlays back to the runtime root,
    // while preserving unknown raw record tails for existing entries. The port still does not
    // synthesize new replay payload arrays or the full cRSubHighScore metadata.
    pub fn saveToRuntimeRoot(self: *const Tables, allocator: std.mem.Allocator, root_path: []const u8) !void {
        try runtime_state.ensureRootExists(root_path);
        try saveBankFile(allocator, root_path, .score_a, self.postal[0..], 0);
        try saveBankFile(allocator, root_path, .score_b, self.challenge[0..], 1);
        try saveBankFile(allocator, root_path, .score_c, self.completion[0..], 2);
    }
};

fn blankEntries() [bank_entry_count]Entry {
    return [_]Entry{Entry{}} ** bank_entry_count;
}

fn blankCompletionEntries() [completion_entry_count]Entry {
    return [_]Entry{Entry{}} ** completion_entry_count;
}

fn loadBankFile(allocator: std.mem.Allocator, root_path: []const u8, kind: runtime_state.FileKind, tables: *Tables) !void {
    var path_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const path = try runtime_state.filePath(&path_buffer, root_path, kind);
    const bytes = std.fs.cwd().readFileAlloc(allocator, path, 1 << 20) catch |err| switch (err) {
        error.FileNotFound => return,
        else => return err,
    };
    defer allocator.free(bytes);
    if (bytes.len == 0) return;

    archive.xorDecodeInPlace(bytes, 0);

    var offset: usize = 0;
    while (offset < bytes.len) {
        if (bytes.len - offset < @sizeOf(u32)) return error.InvalidHighScoreFile;
        const record_size = readU32(bytes, offset);
        if (record_size < compact_record_header_size or offset + record_size > bytes.len) {
            return error.InvalidHighScoreFile;
        }
        try parseCompactRecord(tables, allocator, bytes[offset .. offset + record_size]);
        offset += record_size;
    }
}

fn parseCompactRecord(tables: *Tables, allocator: std.mem.Allocator, record: []const u8) !void {
    if (record.len < compact_record_header_size) return;

    const score = readU32(record, compact_record_score_offset);
    const checksum = readU32(record, compact_record_checksum_offset);
    if (checksum != ((score *% score) ^ 0xdeadbabe)) return;

    const bank_selector = readU32(record, compact_record_bank_selector_offset);
    const entry_index = readU32(record, compact_record_entry_index_offset);
    const replay_sample_count = readU32(record, compact_record_replay_sample_count_offset);
    const name_end = std.mem.indexOfScalar(u8, record[compact_record_name_offset .. compact_record_name_offset + compact_record_name_len], 0) orelse compact_record_name_len;
    const name = std.mem.trimRight(u8, record[compact_record_name_offset .. compact_record_name_offset + name_end], " ");

    const entry = switch (bank_selector) {
        0 => if (entry_index < tables.postal.len) &tables.postal[entry_index] else return,
        1 => if (entry_index < tables.challenge.len) &tables.challenge[entry_index] else return,
        2 => if (entry_index < tables.completion.len) &tables.completion[entry_index] else return,
        else => return,
    };

    entry.score = score;
    entry.has_replay = replay_sample_count > 0;
    entry.setName(name);
    try entry.setRawRecord(allocator, record);
}

fn insertDescending(entries: []Entry, entry: Entry) ?usize {
    const visible = @min(visible_entry_count, entries.len);
    var rank: usize = 0;
    while (rank < visible and entry.score <= entries[rank].score and entries[rank].isActive()) : (rank += 1) {}
    if (rank >= visible) return null;

    var index = entries.len - 1;
    while (index > rank) : (index -= 1) {
        entries[index] = entries[index - 1];
    }
    entries[rank] = entry;
    return rank;
}

fn saveBankFile(
    allocator: std.mem.Allocator,
    root_path: []const u8,
    kind: runtime_state.FileKind,
    entries: []const Entry,
    bank_selector: u32,
) !void {
    var encoded: std.ArrayList(u8) = .empty;
    defer encoded.deinit(allocator);

    for (entries, 0..) |entry, entry_index| {
        if (!entry.isActive()) continue;

        const owned_record = if (entry.raw_record) |raw_record|
            try allocator.dupe(u8, raw_record)
        else
            try allocator.alloc(u8, compact_record_header_size);
        defer allocator.free(owned_record);

        if (entry.raw_record == null) {
            @memset(owned_record, 0);
            std.mem.writeInt(u32, owned_record[compact_record_replay_sample_count_offset .. compact_record_replay_sample_count_offset + 4], 0, .little);
        } else if (owned_record.len < compact_record_header_size) {
            return error.InvalidHighScoreFile;
        }

        std.mem.writeInt(u32, owned_record[0x00..0x04], @intCast(owned_record.len), .little);
        std.mem.writeInt(u32, owned_record[compact_record_score_offset .. compact_record_score_offset + 4], entry.score, .little);
        std.mem.writeInt(u32, owned_record[compact_record_checksum_offset .. compact_record_checksum_offset + 4], (entry.score *% entry.score) ^ 0xdeadbabe, .little);
        std.mem.writeInt(u32, owned_record[compact_record_bank_selector_offset .. compact_record_bank_selector_offset + 4], bank_selector, .little);
        std.mem.writeInt(u32, owned_record[compact_record_entry_index_offset .. compact_record_entry_index_offset + 4], @intCast(entry_index), .little);

        const name = entry.name()[0..@min(entry.name().len, compact_record_name_len)];
        @memset(owned_record[compact_record_name_offset .. compact_record_name_offset + compact_record_name_len], 0);
        @memcpy(owned_record[compact_record_name_offset .. compact_record_name_offset + name.len], name);
        try encoded.appendSlice(allocator, owned_record);
    }

    archive.xorDecodeInPlace(encoded.items, 0);

    var path_buffer: [std.fs.max_path_bytes]u8 = undefined;
    const path = try runtime_state.filePath(&path_buffer, root_path, kind);
    var file = try std.fs.cwd().createFile(path, .{});
    defer file.close();
    try file.writeAll(encoded.items);
}

fn readU32(buffer: []const u8, offset: usize) u32 {
    return std.mem.readInt(u32, @as(*const [4]u8, @ptrCast(buffer[offset .. offset + 4].ptr)), .little);
}

test "default tables seed the recovered startup bank shape" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try std.testing.expectEqual(@as(usize, bank_entry_count), tables.postal.len);
    try std.testing.expectEqual(@as(usize, bank_entry_count), tables.challenge.len);
    try std.testing.expectEqual(@as(usize, completion_entry_count), tables.completion.len);
    try std.testing.expectEqual(@as(u32, 0), tables.postal[0].score);
    try std.testing.expectEqual(@as(usize, 0), tables.challenge[bank_entry_count - 1].name().len);
    try std.testing.expectEqual(@as(usize, visible_entry_count), tables.visibleEntries(.postal).len);
    try std.testing.expectEqual(@as(usize, 0), tables.scratch.name().len);
}

test "parse compact high-score record into recovered bank slots" {
    var payload: [compact_record_header_size]u8 = [_]u8{0} ** compact_record_header_size;
    std.mem.writeInt(u32, payload[0x00..0x04], compact_record_header_size, .little);
    std.mem.writeInt(u32, payload[0x04..0x08], 4242, .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], (4242 *% 4242) ^ 0xdeadbabe, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 0, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 2, .little);
    std.mem.writeInt(u32, payload[0x74..0x78], 3, .little);
    @memcpy(payload[0x5c .. 0x5c + "Turbo".len], "Turbo");

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try parseCompactRecord(&tables, std.testing.allocator, &payload);

    try std.testing.expectEqual(@as(u32, 4242), tables.postal[2].score);
    try std.testing.expect(tables.postal[2].has_replay);
    try std.testing.expectEqualStrings("Turbo", tables.postal[2].name());
    try std.testing.expect(tables.postal[2].raw_record != null);
    try std.testing.expectEqual(@as(u32, 0), tables.challenge[2].score);
}

test "ignore compact high-score records with invalid checksum" {
    var payload: [compact_record_header_size]u8 = [_]u8{0} ** compact_record_header_size;
    std.mem.writeInt(u32, payload[0x00..0x04], compact_record_header_size, .little);
    std.mem.writeInt(u32, payload[0x04..0x08], 99, .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], 0x12345678, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 1, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 0, .little);
    @memcpy(payload[0x5c .. 0x5c + "Nope".len], "Nope");

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try parseCompactRecord(&tables, std.testing.allocator, &payload);

    try std.testing.expectEqual(@as(u32, 0), tables.challenge[0].score);
    try std.testing.expectEqual(@as(usize, 0), tables.challenge[0].name().len);
}

test "insert arcade score into visible top ten with overflow row" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    for (tables.postal[0..visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(1000 - index * 10)) };
    }

    const result = tables.addArcade(.{ .score = 955 });
    try std.testing.expectEqual(@as(?usize, 5), result.rank);
    try std.testing.expectEqual(@as(u32, 955), tables.postal[5].score);
    try std.testing.expectEqual(@as(u32, 950), tables.postal[6].score);
    try std.testing.expectEqual(@as(u32, 910), tables.postal[10].score);
}

test "time trial score only improves when the new route time is better" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    const first = tables.addTimeTrial(3, .{ .score = 42000 });
    try std.testing.expect(first.improved);
    try std.testing.expectEqual(@as(?usize, 2), first.rank);
    try std.testing.expectEqual(@as(u32, 42000), tables.completion[2].score);

    const worse = tables.addTimeTrial(3, .{ .score = 45000 });
    try std.testing.expect(!worse.improved);
    try std.testing.expectEqual(@as(u32, 42000), tables.completion[2].score);

    const better = tables.addTimeTrial(3, .{ .score = 41000 });
    try std.testing.expect(better.improved);
    try std.testing.expectEqual(@as(u32, 41000), tables.completion[2].score);
}

test "save and load compact high-score tables roundtrip score and names" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.fs.cwd().openDir(".", .{});
    defer previous_dir.close();

    try temp_dir.dir.setAsCwd();
    defer previous_dir.setAsCwd() catch unreachable;

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    tables.postal[0].score = 12345;
    tables.postal[0].setName("Turbo");
    tables.challenge[1].score = 777;
    tables.challenge[1].setName("Slug");
    tables.completion[2].score = 54321;
    tables.completion[2].setName("Route");

    try tables.saveToRuntimeRoot(std.testing.allocator, "runtime");

    var loaded = Tables.initDefault();
    defer loaded.deinit(std.testing.allocator);
    try loaded.loadFromRuntimeRoot(std.testing.allocator, "runtime");

    try std.testing.expectEqual(@as(u32, 12345), loaded.postal[0].score);
    try std.testing.expectEqualStrings("Turbo", loaded.postal[0].name());
    try std.testing.expectEqual(@as(u32, 777), loaded.challenge[1].score);
    try std.testing.expectEqualStrings("Slug", loaded.challenge[1].name());
    try std.testing.expectEqual(@as(u32, 54321), loaded.completion[2].score);
    try std.testing.expectEqualStrings("Route", loaded.completion[2].name());
}

test "saveback preserves unknown compact record tails for loaded entries" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.fs.cwd().openDir(".", .{});
    defer previous_dir.close();

    try temp_dir.dir.setAsCwd();
    defer previous_dir.setAsCwd() catch unreachable;

    const record_len = compact_record_header_size + 8;
    var payload: [record_len]u8 = [_]u8{0} ** record_len;
    std.mem.writeInt(u32, payload[0x00..0x04], record_len, .little);
    std.mem.writeInt(u32, payload[0x04..0x08], 4242, .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], (4242 *% 4242) ^ 0xdeadbabe, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 0, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 0, .little);
    std.mem.writeInt(u32, payload[0x74..0x78], 7, .little);
    @memcpy(payload[0x5c .. 0x5c + "Turbo".len], "Turbo");
    @memcpy(payload[compact_record_header_size..], &[_]u8{ 1, 2, 3, 4, 5, 6, 7, 8 });

    var encoded = payload;
    archive.xorDecodeInPlace(&encoded, 0);
    try runtime_state.ensureRootExists("runtime");
    try std.fs.cwd().writeFile(.{ .sub_path = "runtime/ScoreA.dat", .data = &encoded });

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try tables.loadFromRuntimeRoot(std.testing.allocator, "runtime");
    tables.postal[0].score = 5000;
    tables.postal[0].setName("Turb0");
    try tables.saveToRuntimeRoot(std.testing.allocator, "runtime");

    const saved_bytes = try std.fs.cwd().readFileAlloc(std.testing.allocator, "runtime/ScoreA.dat", 1 << 20);
    defer std.testing.allocator.free(saved_bytes);
    archive.xorDecodeInPlace(saved_bytes, 0);

    try std.testing.expectEqual(@as(usize, record_len), saved_bytes.len);
    try std.testing.expectEqual(@as(u32, record_len), readU32(saved_bytes, 0));
    try std.testing.expectEqual(@as(u32, 5000), readU32(saved_bytes, compact_record_score_offset));
    try std.testing.expectEqual(@as(u32, (5000 *% 5000) ^ 0xdeadbabe), readU32(saved_bytes, compact_record_checksum_offset));
    try std.testing.expectEqual(@as(u32, 7), readU32(saved_bytes, compact_record_replay_sample_count_offset));
    try std.testing.expectEqualStrings("Turb0", std.mem.trimRight(u8, saved_bytes[compact_record_name_offset .. compact_record_name_offset + 5], " "));
    try std.testing.expectEqualSlices(u8, &[_]u8{ 1, 2, 3, 4, 5, 6, 7, 8 }, saved_bytes[compact_record_header_size..]);
}
