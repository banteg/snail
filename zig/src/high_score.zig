const std = @import("std");

pub const visible_entry_count = 10;
pub const bank_entry_count = 11;
pub const completion_entry_count = 0x33;
pub const name_capacity = 32;

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
};

fn blankEntries() [bank_entry_count]Entry {
    return [_]Entry{Entry{}} ** bank_entry_count;
}

fn blankCompletionEntries() [completion_entry_count]Entry {
    return [_]Entry{Entry{}} ** completion_entry_count;
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
