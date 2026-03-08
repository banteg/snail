const std = @import("std");

pub const visible_entry_count = 10;
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

// PORT(partial): this seeds the recovered 10-row postal/challenge table shape,
// but not the full cRSubHighScore save/edit/runtime overlay yet.
pub const Tables = struct {
    postal: [visible_entry_count]Entry,
    challenge: [visible_entry_count]Entry,

    pub fn initDefault() Tables {
        return .{
            .postal = blankEntries(),
            .challenge = blankEntries(),
        };
    }

    pub fn entries(self: *const Tables, mode: Mode) []const Entry {
        return switch (mode) {
            .postal => self.postal[0..],
            .challenge => self.challenge[0..],
        };
    }
};

fn blankEntries() [visible_entry_count]Entry {
    return [_]Entry{Entry{}} ** visible_entry_count;
}

test "default tables seed the recovered 10-row screen shape" {
    const tables = Tables.initDefault();
    try std.testing.expectEqual(@as(usize, visible_entry_count), tables.postal.len);
    try std.testing.expectEqual(@as(usize, visible_entry_count), tables.challenge.len);
    try std.testing.expectEqual(@as(u32, 0), tables.postal[0].score);
    try std.testing.expectEqual(@as(usize, 0), tables.challenge[9].name().len);
}
