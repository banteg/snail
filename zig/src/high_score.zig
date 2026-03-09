const std = @import("std");
const archive = @import("archive.zig");
const runtime_state = @import("runtime_state.zig");

pub const visible_entry_count = 10;
pub const bank_entry_count = 11;
pub const completion_entry_count = 0x33;
pub const name_capacity = 32;
const compact_record_header_size = 0x88;

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

    pub fn name(self: *const Entry) []const u8 {
        return self.name_buf[0..self.name_len];
    }

    fn setName(self: *Entry, value: []const u8) void {
        const clipped = value[0..@min(value.len, self.name_buf.len)];
        @memset(&self.name_buf, 0);
        @memcpy(self.name_buf[0..clipped.len], clipped);
        self.name_len = clipped.len;
    }
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

    pub fn entries(self: *const Tables, mode: Mode) []const Entry {
        return switch (mode) {
            .postal => self.postal[0..],
            .challenge => self.challenge[0..],
        };
    }

    pub fn visibleEntries(self: *const Tables, mode: Mode) []const Entry {
        return self.entries(mode)[0..visible_entry_count];
    }

    // PORT(partial): this reads the compact score overlays from ScoreA/B/C.dat,
    // but only surfaces score, name, and replay presence in the current port.
    pub fn loadFromRuntimeRoot(self: *Tables, allocator: std.mem.Allocator, root_path: []const u8) !void {
        try loadBankFile(allocator, root_path, .score_a, self);
        try loadBankFile(allocator, root_path, .score_b, self);
        try loadBankFile(allocator, root_path, .score_c, self);
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
        parseCompactRecord(tables, bytes[offset .. offset + record_size]);
        offset += record_size;
    }
}

fn parseCompactRecord(tables: *Tables, record: []const u8) void {
    if (record.len < compact_record_header_size) return;

    const score = readU32(record, 0x04);
    const checksum = readU32(record, 0x28);
    if (checksum != ((score *% score) ^ 0xdeadbabe)) return;

    const bank_selector = readU32(record, 0x3c);
    const entry_index = readU32(record, 0x40);
    const replay_sample_count = readU32(record, 0x74);
    const name_end = std.mem.indexOfScalar(u8, record[0x5c..0x70], 0) orelse (0x70 - 0x5c);
    const name = std.mem.trimRight(u8, record[0x5c .. 0x5c + name_end], " ");

    const entry = switch (bank_selector) {
        0 => if (entry_index < tables.postal.len) &tables.postal[entry_index] else return,
        1 => if (entry_index < tables.challenge.len) &tables.challenge[entry_index] else return,
        2 => if (entry_index < tables.completion.len) &tables.completion[entry_index] else return,
        else => return,
    };

    entry.score = score;
    entry.has_replay = replay_sample_count > 0;
    entry.setName(name);
}

fn readU32(buffer: []const u8, offset: usize) u32 {
    return std.mem.readInt(u32, @as(*const [4]u8, @ptrCast(buffer[offset .. offset + 4].ptr)), .little);
}

test "default tables seed the recovered startup bank shape" {
    const tables = Tables.initDefault();
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
    parseCompactRecord(&tables, &payload);

    try std.testing.expectEqual(@as(u32, 4242), tables.postal[2].score);
    try std.testing.expect(tables.postal[2].has_replay);
    try std.testing.expectEqualStrings("Turbo", tables.postal[2].name());
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
    parseCompactRecord(&tables, &payload);

    try std.testing.expectEqual(@as(u32, 0), tables.challenge[0].score);
    try std.testing.expectEqual(@as(usize, 0), tables.challenge[0].name().len);
}
