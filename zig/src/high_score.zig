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
const compact_record_replay_level_index_offset = 0x2c;
const compact_record_replay_mode_id_offset = 0x30;
const compact_record_runtime_build_flags_offset = 0x38;
const compact_record_replay_speed_scalar_offset = 0x48;
const compact_record_challenge_speed_value_offset = 0x4c;
const compact_record_challenge_difficulty_value_offset = 0x50;
const compact_record_challenge_difficulty_scalar_offset = 0x54;
const compact_record_runtime_build_seed_offset = 0x70;
const compact_record_garbage_scalar_offset = 0x78;
const compact_record_salt_scalar_offset = 0x7c;
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
    replay_level_index: u32 = 0,
    replay_mode_id: u32 = 0,
    challenge_speed_value: u32 = 0,
    runtime_build_flags: u32 = 0,
    replay_speed_scalar: f32 = 0.0,
    challenge_difficulty_value: u32 = 0,
    challenge_difficulty_scalar: f32 = 0.0,
    runtime_build_seed: u32 = 0,
    garbage_scalar: f32 = 0.0,
    salt_scalar: f32 = 0.0,
    has_replay: bool = false,
    name_len: usize = 0,
    name_buf: [name_capacity]u8 = [_]u8{0} ** name_capacity,
    raw_record: ?[]u8 = null,

    pub fn name(self: *const Entry) []const u8 {
        return self.name_buf[0..self.name_len];
    }

    pub fn replaySampleCount(self: *const Entry) usize {
        const record = self.raw_record orelse return 0;
        if (record.len < compact_record_header_size) return 0;
        return @intCast(readU32(record, compact_record_replay_sample_count_offset));
    }

    pub fn replaySampleAt(self: *const Entry, index: usize) ?ReplaySample {
        const record = self.raw_record orelse return null;
        const sample_count = self.replaySampleCount();
        if (index >= sample_count) return null;

        const required_len = compact_record_header_size + (sample_count * 5);
        if (record.len < required_len) return null;

        const lateral_offset = compact_record_header_size + (index * 2);
        const ghost_delta_z_offset = compact_record_header_size + (sample_count * 2) + (index * 2);
        const flags_offset = compact_record_header_size + (sample_count * 4) + index;
        return .{
            .lateral = readI16(record, lateral_offset),
            .ghost_delta_z = readI16(record, ghost_delta_z_offset),
            .flags = record[flags_offset],
        };
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

pub const ReplaySample = struct {
    lateral: i16,
    ghost_delta_z: i16,
    flags: u8,
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

    pub fn addArcade(self: *Tables, allocator: std.mem.Allocator, entry: Entry) InsertResult {
        return .{
            .rank = insertDescending(self.postal[0..], allocator, entry),
            .improved = false,
        };
    }

    pub fn addSurvival(self: *Tables, allocator: std.mem.Allocator, entry: Entry) InsertResult {
        return .{
            .rank = insertDescending(self.challenge[0..], allocator, entry),
            .improved = false,
        };
    }

    pub fn addTimeTrial(self: *Tables, allocator: std.mem.Allocator, route_index: usize, entry: Entry, completed: bool) InsertResult {
        var incoming = entry;
        defer incoming.deinit(allocator);

        const completion_index = completionIndexForRouteIndex(route_index) orelse return .{};

        self.scratch.deinit(allocator);
        self.scratch = .{
            .score = incoming.score,
            .replay_level_index = incoming.replay_level_index,
            .replay_mode_id = incoming.replay_mode_id,
            .challenge_speed_value = incoming.challenge_speed_value,
            .runtime_build_flags = incoming.runtime_build_flags,
            .replay_speed_scalar = incoming.replay_speed_scalar,
            .challenge_difficulty_value = incoming.challenge_difficulty_value,
            .challenge_difficulty_scalar = incoming.challenge_difficulty_scalar,
            .runtime_build_seed = incoming.runtime_build_seed,
            .garbage_scalar = incoming.garbage_scalar,
            .salt_scalar = incoming.salt_scalar,
            .has_replay = incoming.has_replay,
            .name_len = incoming.name_len,
            .name_buf = incoming.name_buf,
            .raw_record = null,
        };
        if (incoming.raw_record) |raw_record| {
            self.scratch.raw_record = allocator.dupe(u8, raw_record) catch null;
        }

        if (!completed) {
            return .{};
        }

        const current = &self.completion[completion_index];
        if (!current.isActive() or entry.score < current.score) {
            if (!current.isActive()) {
                current.deinit(allocator);
                current.* = incoming;
                incoming.raw_record = null;
            } else {
                current.score = incoming.score;
                current.replay_level_index = incoming.replay_level_index;
                current.replay_mode_id = incoming.replay_mode_id;
                current.challenge_speed_value = incoming.challenge_speed_value;
                current.runtime_build_flags = incoming.runtime_build_flags;
                current.replay_speed_scalar = incoming.replay_speed_scalar;
                current.challenge_difficulty_value = incoming.challenge_difficulty_value;
                current.challenge_difficulty_scalar = incoming.challenge_difficulty_scalar;
                current.runtime_build_seed = incoming.runtime_build_seed;
                current.garbage_scalar = incoming.garbage_scalar;
                current.salt_scalar = incoming.salt_scalar;
                if (incoming.name_len != 0) {
                    current.setName(incoming.name());
                }
                if (incoming.raw_record != null) {
                    current.deinit(allocator);
                    current.raw_record = incoming.raw_record;
                    incoming.raw_record = null;
                    current.has_replay = incoming.has_replay;
                } else {
                    // PORT(partial): Windows promotes the whole new time-trial snapshot into the
                    // per-route completion slot. When the port only has a scalar time update and
                    // no fresh compact overlay, keeping the old replay/raw payload would mislabel
                    // the new best as still having the previous run's replay blob.
                    current.deinit(allocator);
                    current.has_replay = false;
                }
            }
            return .{
                .rank = completion_index,
                .improved = true,
            };
        }

        return .{};
    }

    // PORT(partial): this reads the compact score overlays from ScoreA/B/C.dat,
    // but only surfaces the recovered seed/header lanes, replay presence, name,
    // and raw record preservation in the current port.
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
    entry.replay_level_index = readU32(record, compact_record_replay_level_index_offset);
    entry.replay_mode_id = readU32(record, compact_record_replay_mode_id_offset);
    entry.challenge_speed_value = readU32(record, compact_record_challenge_speed_value_offset);
    entry.runtime_build_flags = readU32(record, compact_record_runtime_build_flags_offset);
    entry.replay_speed_scalar = @bitCast(readU32(record, compact_record_replay_speed_scalar_offset));
    entry.challenge_difficulty_value = readU32(record, compact_record_challenge_difficulty_value_offset);
    entry.challenge_difficulty_scalar = @bitCast(readU32(record, compact_record_challenge_difficulty_scalar_offset));
    entry.runtime_build_seed = readU32(record, compact_record_runtime_build_seed_offset);
    entry.garbage_scalar = @bitCast(readU32(record, compact_record_garbage_scalar_offset));
    entry.salt_scalar = @bitCast(readU32(record, compact_record_salt_scalar_offset));
    entry.has_replay = replay_sample_count > 0;
    entry.setName(name);
    try entry.setRawRecord(allocator, record);
}

// PORT(partial): the current port still treats frontend route indices as 1-based external values
// that map onto 0-based ScoreC completion slots. The supplied Windows replay/save decompiles prove
// the persisted bank layout, but they do not fully settle whether any remaining layer rewrites the
// route number before it reaches the completion bank. Keep this assumption centralized until the
// ScoreC indexing bridge is recovered.
pub fn completionIndexForRouteIndex(route_index: usize) ?usize {
    if (route_index == 0) return null;
    const completion_index = route_index - 1;
    if (completion_index >= completion_entry_count) return null;
    return completion_index;
}

fn insertDescending(entries: []Entry, allocator: std.mem.Allocator, entry: Entry) ?usize {
    var incoming = entry;
    const visible = @min(visible_entry_count, entries.len);
    var rank: usize = 0;
    while (rank < visible and incoming.score <= entries[rank].score and entries[rank].isActive()) : (rank += 1) {}
    if (rank >= visible) {
        incoming.deinit(allocator);
        return null;
    }

    for (rank..entries.len) |index| {
        std.mem.swap(Entry, &entries[index], &incoming);
    }
    incoming.deinit(allocator);
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
        std.mem.writeInt(u32, owned_record[compact_record_replay_level_index_offset .. compact_record_replay_level_index_offset + 4], entry.replay_level_index, .little);
        std.mem.writeInt(u32, owned_record[compact_record_replay_mode_id_offset .. compact_record_replay_mode_id_offset + 4], entry.replay_mode_id, .little);
        std.mem.writeInt(u32, owned_record[compact_record_challenge_speed_value_offset .. compact_record_challenge_speed_value_offset + 4], entry.challenge_speed_value, .little);
        std.mem.writeInt(u32, owned_record[compact_record_runtime_build_flags_offset .. compact_record_runtime_build_flags_offset + 4], entry.runtime_build_flags, .little);
        std.mem.writeInt(u32, owned_record[compact_record_replay_speed_scalar_offset .. compact_record_replay_speed_scalar_offset + 4], @bitCast(entry.replay_speed_scalar), .little);
        std.mem.writeInt(u32, owned_record[compact_record_challenge_difficulty_value_offset .. compact_record_challenge_difficulty_value_offset + 4], entry.challenge_difficulty_value, .little);
        std.mem.writeInt(u32, owned_record[compact_record_challenge_difficulty_scalar_offset .. compact_record_challenge_difficulty_scalar_offset + 4], @bitCast(entry.challenge_difficulty_scalar), .little);
        std.mem.writeInt(u32, owned_record[compact_record_runtime_build_seed_offset .. compact_record_runtime_build_seed_offset + 4], entry.runtime_build_seed, .little);
        std.mem.writeInt(u32, owned_record[compact_record_garbage_scalar_offset .. compact_record_garbage_scalar_offset + 4], @bitCast(entry.garbage_scalar), .little);
        std.mem.writeInt(u32, owned_record[compact_record_salt_scalar_offset .. compact_record_salt_scalar_offset + 4], @bitCast(entry.salt_scalar), .little);
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

fn readI16(buffer: []const u8, offset: usize) i16 {
    return std.mem.readInt(i16, @as(*const [2]u8, @ptrCast(buffer[offset .. offset + 2].ptr)), .little);
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
    std.mem.writeInt(u32, payload[0x2c..0x30], 17, .little);
    std.mem.writeInt(u32, payload[0x30..0x34], 4, .little);
    std.mem.writeInt(u32, payload[0x38..0x3c], 0x00f5cfff, .little);
    std.mem.writeInt(u32, payload[0x48..0x4c], @bitCast(@as(f32, 0.56)), .little);
    std.mem.writeInt(u32, payload[0x4c..0x50], 55, .little);
    std.mem.writeInt(u32, payload[0x50..0x54], 40, .little);
    std.mem.writeInt(u32, payload[0x54..0x58], @bitCast(@as(f32, 0.4)), .little);
    std.mem.writeInt(u32, payload[0x70..0x74], 123, .little);
    std.mem.writeInt(u32, payload[0x78..0x7c], @bitCast(@as(f32, 0.32)), .little);
    std.mem.writeInt(u32, payload[0x7c..0x80], @bitCast(@as(f32, 0.45)), .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], (4242 *% 4242) ^ 0xdeadbabe, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 0, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 2, .little);
    std.mem.writeInt(u32, payload[0x74..0x78], 3, .little);
    @memcpy(payload[0x5c .. 0x5c + "Turbo".len], "Turbo");

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try parseCompactRecord(&tables, std.testing.allocator, &payload);

    try std.testing.expectEqual(@as(u32, 4242), tables.postal[2].score);
    try std.testing.expectEqual(@as(u32, 17), tables.postal[2].replay_level_index);
    try std.testing.expectEqual(@as(u32, 4), tables.postal[2].replay_mode_id);
    try std.testing.expectEqual(@as(u32, 55), tables.postal[2].challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), tables.postal[2].runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.56), tables.postal[2].replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 40), tables.postal[2].challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), tables.postal[2].challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 123), tables.postal[2].runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), tables.postal[2].garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.45), tables.postal[2].salt_scalar, 0.0001);
    try std.testing.expect(tables.postal[2].has_replay);
    try std.testing.expectEqualStrings("Turbo", tables.postal[2].name());
    try std.testing.expect(tables.postal[2].raw_record != null);
    try std.testing.expectEqual(@as(u32, 0), tables.challenge[2].score);
}

test "compact high-score record exposes replay payload lanes" {
    var payload: [compact_record_header_size + 15]u8 = [_]u8{0} ** (compact_record_header_size + 15);
    std.mem.writeInt(u32, payload[0x00..0x04], payload.len, .little);
    std.mem.writeInt(u32, payload[0x04..0x08], 9001, .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], (9001 *% 9001) ^ 0xdeadbabe, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 0, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 0, .little);
    std.mem.writeInt(u32, payload[0x74..0x78], 3, .little);
    std.mem.writeInt(i16, payload[0x88..0x8a], -12, .little);
    std.mem.writeInt(i16, payload[0x8a..0x8c], 7, .little);
    std.mem.writeInt(i16, payload[0x8c..0x8e], 25, .little);
    std.mem.writeInt(i16, payload[0x8e..0x90], 100, .little);
    std.mem.writeInt(i16, payload[0x90..0x92], 200, .little);
    std.mem.writeInt(i16, payload[0x92..0x94], 300, .little);
    payload[0x94] = 0x01;
    payload[0x95] = 0x04;
    payload[0x96] = 0x0a;

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try parseCompactRecord(&tables, std.testing.allocator, &payload);

    const entry = &tables.postal[0];
    try std.testing.expectEqual(@as(usize, 3), entry.replaySampleCount());
    try std.testing.expectEqualDeep(ReplaySample{
        .lateral = -12,
        .ghost_delta_z = 100,
        .flags = 0x01,
    }, entry.replaySampleAt(0).?);
    try std.testing.expectEqualDeep(ReplaySample{
        .lateral = 7,
        .ghost_delta_z = 200,
        .flags = 0x04,
    }, entry.replaySampleAt(1).?);
    try std.testing.expectEqualDeep(ReplaySample{
        .lateral = 25,
        .ghost_delta_z = 300,
        .flags = 0x0a,
    }, entry.replaySampleAt(2).?);
    try std.testing.expect(entry.replaySampleAt(3) == null);
}

test "replay payload access rejects truncated compact records" {
    var payload: [compact_record_header_size]u8 = [_]u8{0} ** compact_record_header_size;
    std.mem.writeInt(u32, payload[0x00..0x04], payload.len, .little);
    std.mem.writeInt(u32, payload[0x04..0x08], 77, .little);
    std.mem.writeInt(u32, payload[0x28..0x2c], (77 *% 77) ^ 0xdeadbabe, .little);
    std.mem.writeInt(u32, payload[0x3c..0x40], 0, .little);
    std.mem.writeInt(u32, payload[0x40..0x44], 0, .little);
    std.mem.writeInt(u32, payload[0x74..0x78], 1, .little);

    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);
    try parseCompactRecord(&tables, std.testing.allocator, &payload);

    const entry = &tables.postal[0];
    try std.testing.expectEqual(@as(usize, 1), entry.replaySampleCount());
    try std.testing.expect(entry.replaySampleAt(0) == null);
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

    const result = tables.addArcade(std.testing.allocator, .{ .score = 955 });
    try std.testing.expectEqual(@as(?usize, 5), result.rank);
    try std.testing.expectEqual(@as(u32, 955), tables.postal[5].score);
    try std.testing.expectEqual(@as(u32, 950), tables.postal[6].score);
    try std.testing.expectEqual(@as(u32, 910), tables.postal[10].score);
}

test "time trial score only improves when the new route time is better" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    const first = tables.addTimeTrial(std.testing.allocator, 3, .{ .score = 42000, .replay_level_index = 3 }, true);
    try std.testing.expect(first.improved);
    try std.testing.expectEqual(@as(?usize, 2), first.rank);
    try std.testing.expectEqual(@as(u32, 42000), tables.completion[2].score);
    try std.testing.expectEqual(@as(u32, 3), tables.completion[2].replay_level_index);

    const worse = tables.addTimeTrial(std.testing.allocator, 3, .{ .score = 45000, .replay_level_index = 3 }, true);
    try std.testing.expect(!worse.improved);
    try std.testing.expectEqual(@as(u32, 42000), tables.completion[2].score);

    const better = tables.addTimeTrial(std.testing.allocator, 3, .{ .score = 41000, .replay_level_index = 3 }, true);
    try std.testing.expect(better.improved);
    try std.testing.expectEqual(@as(u32, 41000), tables.completion[2].score);
}

test "arcade insertion shifts opaque records without duplicating ownership" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    for (tables.postal[0..visible_entry_count], 0..) |*entry, index| {
        entry.score = @as(u32, @intCast(1000 - index * 10));
        var raw_record = try std.testing.allocator.alloc(u8, 1);
        raw_record[0] = @as(u8, @intCast(index));
        entry.raw_record = raw_record;
    }

    const overflow_before = tables.postal[visible_entry_count].raw_record;
    try std.testing.expect(overflow_before == null);

    const result = tables.addArcade(std.testing.allocator, .{ .score = 955 });
    try std.testing.expectEqual(@as(?usize, 5), result.rank);
    try std.testing.expectEqual(@as(u32, 955), tables.postal[5].score);
    try std.testing.expect(tables.postal[5].raw_record == null);
    try std.testing.expect(tables.postal[6].raw_record != null);
    try std.testing.expectEqual(@as(u8, 5), tables.postal[6].raw_record.?[0]);
    try std.testing.expect(tables.postal[10].raw_record != null);
    try std.testing.expectEqual(@as(u8, 9), tables.postal[10].raw_record.?[0]);
}

test "time trial improvements clear stale replay payloads without a fresh snapshot" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    tables.completion[2].score = 42000;
    tables.completion[2].replay_level_index = 3;
    tables.completion[2].has_replay = true;
    tables.completion[2].setName("Turbo");
    const raw_record = try std.testing.allocator.alloc(u8, compact_record_header_size + 4);
    @memset(raw_record, 0xaa);
    tables.completion[2].raw_record = raw_record;

    const improved = tables.addTimeTrial(std.testing.allocator, 3, .{
        .score = 41000,
        .replay_level_index = 3,
        .replay_mode_id = 4,
        .replay_speed_scalar = 0.56,
    }, true);
    try std.testing.expect(improved.improved);
    try std.testing.expectEqual(@as(u32, 41000), tables.completion[2].score);
    try std.testing.expectEqual(@as(u32, 3), tables.completion[2].replay_level_index);
    try std.testing.expectEqualStrings("Turbo", tables.completion[2].name());
    try std.testing.expect(!tables.completion[2].has_replay);
    try std.testing.expect(tables.completion[2].raw_record == null);
}

test "failed time trial attempt only updates scratch and preserves best route time" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    tables.completion[2].score = 42000;
    tables.completion[2].replay_level_index = 3;
    tables.completion[2].setName("Turbo");

    const expected_raw = [_]u8{0xbb} ** (compact_record_header_size + 2);
    const owned_raw = try std.testing.allocator.dupe(u8, &expected_raw);

    const failed = tables.addTimeTrial(std.testing.allocator, 3, .{
        .score = 2000,
        .replay_level_index = 3,
        .replay_mode_id = 4,
        .challenge_speed_value = 55,
        .runtime_build_flags = 0x00f5cfff,
        .replay_speed_scalar = 0.56,
        .challenge_difficulty_value = 40,
        .challenge_difficulty_scalar = 0.4,
        .runtime_build_seed = 55,
        .garbage_scalar = 0.32,
        .salt_scalar = 0.45,
        .has_replay = true,
        .raw_record = owned_raw,
    }, false);
    try std.testing.expect(!failed.improved);
    try std.testing.expectEqual(@as(u32, 42000), tables.completion[2].score);
    try std.testing.expectEqual(@as(u32, 2000), tables.scratch.score);
    try std.testing.expectEqual(@as(u32, 3), tables.scratch.replay_level_index);
    try std.testing.expectEqual(@as(u32, 4), tables.scratch.replay_mode_id);
    try std.testing.expectEqual(@as(u32, 55), tables.scratch.challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), tables.scratch.runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.56), tables.scratch.replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 40), tables.scratch.challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), tables.scratch.challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 55), tables.scratch.runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), tables.scratch.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.45), tables.scratch.salt_scalar, 0.0001);
    try std.testing.expect(tables.scratch.has_replay);
    try std.testing.expect(tables.scratch.raw_record != null);
    try std.testing.expectEqualSlices(u8, &expected_raw, tables.scratch.raw_record.?);
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
    tables.postal[0].replay_level_index = 7;
    tables.postal[0].replay_mode_id = 0;
    tables.postal[0].challenge_speed_value = 0;
    tables.postal[0].runtime_build_flags = 0x00f5cfff;
    tables.postal[0].replay_speed_scalar = 0.65;
    tables.postal[0].challenge_difficulty_scalar = 0.0;
    tables.postal[0].runtime_build_seed = 101;
    tables.postal[0].garbage_scalar = 0.25;
    tables.postal[0].salt_scalar = 0.5;
    tables.postal[0].setName("Turbo");
    tables.challenge[1].score = 777;
    tables.challenge[1].replay_level_index = 9;
    tables.challenge[1].replay_mode_id = 1;
    tables.challenge[1].challenge_speed_value = 55;
    tables.challenge[1].runtime_build_flags = 0x0000ffff;
    tables.challenge[1].replay_speed_scalar = 0.56;
    tables.challenge[1].challenge_difficulty_value = 40;
    tables.challenge[1].challenge_difficulty_scalar = 0.4;
    tables.challenge[1].runtime_build_seed = 202;
    tables.challenge[1].garbage_scalar = 0.32;
    tables.challenge[1].salt_scalar = 0.32;
    tables.challenge[1].setName("Slug");
    tables.completion[2].score = 54321;
    tables.completion[2].replay_level_index = 3;
    tables.completion[2].replay_mode_id = 4;
    tables.completion[2].challenge_speed_value = 0;
    tables.completion[2].runtime_build_flags = 0x00001234;
    tables.completion[2].replay_speed_scalar = 0.74;
    tables.completion[2].challenge_difficulty_scalar = 0.0;
    tables.completion[2].runtime_build_seed = 303;
    tables.completion[2].garbage_scalar = 0.65;
    tables.completion[2].salt_scalar = 0.35;
    tables.completion[2].setName("Route");

    try tables.saveToRuntimeRoot(std.testing.allocator, "runtime");

    var loaded = Tables.initDefault();
    defer loaded.deinit(std.testing.allocator);
    try loaded.loadFromRuntimeRoot(std.testing.allocator, "runtime");

    try std.testing.expectEqual(@as(u32, 12345), loaded.postal[0].score);
    try std.testing.expectEqual(@as(u32, 7), loaded.postal[0].replay_level_index);
    try std.testing.expectEqual(@as(u32, 0), loaded.postal[0].replay_mode_id);
    try std.testing.expectEqual(@as(u32, 0), loaded.postal[0].challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), loaded.postal[0].runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.65), loaded.postal[0].replay_speed_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), loaded.postal[0].challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 101), loaded.postal[0].runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), loaded.postal[0].garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), loaded.postal[0].salt_scalar, 0.0001);
    try std.testing.expectEqualStrings("Turbo", loaded.postal[0].name());
    try std.testing.expectEqual(@as(u32, 777), loaded.challenge[1].score);
    try std.testing.expectEqual(@as(u32, 9), loaded.challenge[1].replay_level_index);
    try std.testing.expectEqual(@as(u32, 1), loaded.challenge[1].replay_mode_id);
    try std.testing.expectEqual(@as(u32, 55), loaded.challenge[1].challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0x0000ffff), loaded.challenge[1].runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.56), loaded.challenge[1].replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 40), loaded.challenge[1].challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), loaded.challenge[1].challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 202), loaded.challenge[1].runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), loaded.challenge[1].garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), loaded.challenge[1].salt_scalar, 0.0001);
    try std.testing.expectEqualStrings("Slug", loaded.challenge[1].name());
    try std.testing.expectEqual(@as(u32, 54321), loaded.completion[2].score);
    try std.testing.expectEqual(@as(u32, 3), loaded.completion[2].replay_level_index);
    try std.testing.expectEqual(@as(u32, 4), loaded.completion[2].replay_mode_id);
    try std.testing.expectEqual(@as(u32, 0), loaded.completion[2].challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0x00001234), loaded.completion[2].runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.74), loaded.completion[2].replay_speed_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), loaded.completion[2].challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 303), loaded.completion[2].runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.65), loaded.completion[2].garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.35), loaded.completion[2].salt_scalar, 0.0001);
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
    std.mem.writeInt(u32, payload[0x2c..0x30], 11, .little);
    std.mem.writeInt(u32, payload[0x30..0x34], 1, .little);
    std.mem.writeInt(u32, payload[0x38..0x3c], 0x00f5cfff, .little);
    std.mem.writeInt(u32, payload[0x48..0x4c], @bitCast(@as(f32, 0.75)), .little);
    std.mem.writeInt(u32, payload[0x4c..0x50], 55, .little);
    std.mem.writeInt(u32, payload[0x50..0x54], 40, .little);
    std.mem.writeInt(u32, payload[0x54..0x58], @bitCast(@as(f32, 0.4)), .little);
    std.mem.writeInt(u32, payload[0x70..0x74], 88, .little);
    std.mem.writeInt(u32, payload[0x78..0x7c], @bitCast(@as(f32, 0.2)), .little);
    std.mem.writeInt(u32, payload[0x7c..0x80], @bitCast(@as(f32, 0.9)), .little);
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
    try std.testing.expectEqual(@as(u32, 11), readU32(saved_bytes, compact_record_replay_level_index_offset));
    try std.testing.expectEqual(@as(u32, 1), readU32(saved_bytes, compact_record_replay_mode_id_offset));
    try std.testing.expectEqual(@as(u32, 55), readU32(saved_bytes, compact_record_challenge_speed_value_offset));
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), readU32(saved_bytes, compact_record_runtime_build_flags_offset));
    try std.testing.expectEqual(@as(u32, @bitCast(@as(f32, 0.75))), readU32(saved_bytes, compact_record_replay_speed_scalar_offset));
    try std.testing.expectEqual(@as(u32, 40), readU32(saved_bytes, compact_record_challenge_difficulty_value_offset));
    try std.testing.expectEqual(@as(u32, @bitCast(@as(f32, 0.4))), readU32(saved_bytes, compact_record_challenge_difficulty_scalar_offset));
    try std.testing.expectEqual(@as(u32, 88), readU32(saved_bytes, compact_record_runtime_build_seed_offset));
    try std.testing.expectEqual(@as(u32, @bitCast(@as(f32, 0.2))), readU32(saved_bytes, compact_record_garbage_scalar_offset));
    try std.testing.expectEqual(@as(u32, @bitCast(@as(f32, 0.9))), readU32(saved_bytes, compact_record_salt_scalar_offset));
    try std.testing.expectEqual(@as(u32, (5000 *% 5000) ^ 0xdeadbabe), readU32(saved_bytes, compact_record_checksum_offset));
    try std.testing.expectEqual(@as(u32, 7), readU32(saved_bytes, compact_record_replay_sample_count_offset));
    try std.testing.expectEqualStrings("Turb0", std.mem.trimRight(u8, saved_bytes[compact_record_name_offset .. compact_record_name_offset + 5], " "));
    try std.testing.expectEqualSlices(u8, &[_]u8{ 1, 2, 3, 4, 5, 6, 7, 8 }, saved_bytes[compact_record_header_size..]);
}

test "time trial improvement replaces zero-valued runtime fields" {
    var tables = Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    tables.completion[2].score = 42000;
    tables.completion[2].replay_level_index = 3;
    tables.completion[2].replay_mode_id = 4;
    tables.completion[2].challenge_speed_value = 55;
    tables.completion[2].runtime_build_flags = 0x00f5cfff;
    tables.completion[2].replay_speed_scalar = 0.74;
    tables.completion[2].challenge_difficulty_value = 40;
    tables.completion[2].challenge_difficulty_scalar = 0.4;
    tables.completion[2].runtime_build_seed = 123;
    tables.completion[2].garbage_scalar = 0.32;
    tables.completion[2].salt_scalar = 0.45;

    const improved = tables.addTimeTrial(std.testing.allocator, 3, .{
        .score = 41000,
        .replay_level_index = 0,
        .replay_mode_id = 0,
        .challenge_speed_value = 0,
        .runtime_build_flags = 0,
        .replay_speed_scalar = 0.2,
        .challenge_difficulty_value = 0,
        .challenge_difficulty_scalar = 0.0,
        .runtime_build_seed = 0,
        .garbage_scalar = 0.0,
        .salt_scalar = 0.0,
    }, true);
    try std.testing.expect(improved.improved);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].replay_level_index);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].replay_mode_id);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), tables.completion[2].replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), tables.completion[2].challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), tables.completion[2].runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), tables.completion[2].garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), tables.completion[2].salt_scalar, 0.0001);
}
