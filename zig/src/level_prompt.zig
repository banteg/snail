const std = @import("std");

pub const default_duration_ticks: u32 = 180;
pub const capacity: usize = 3;

pub const Entry = struct {
    message: []const u8,
    ticks_remaining: u32,
};

pub const Queue = struct {
    entries: [capacity]?Entry = [_]?Entry{null} ** capacity,

    pub fn clear(self: *Queue) void {
        self.* = .{};
    }

    pub fn active(self: *const Queue) ?Entry {
        return self.entries[0];
    }

    pub fn tick(self: *Queue) void {
        if (self.entries[0]) |*entry| {
            if (entry.ticks_remaining > 0) {
                entry.ticks_remaining -= 1;
            }
            if (entry.ticks_remaining == 0) {
                self.popFront();
            }
        }
    }

    pub fn enqueue(self: *Queue, message: []const u8, duration_ticks: u32) void {
        if (message.len == 0) return;

        for (&self.entries) |*slot| {
            if (slot.* == null) {
                slot.* = .{
                    .message = message,
                    .ticks_remaining = @max(duration_ticks, 1),
                };
                return;
            }
        }
    }

    fn popFront(self: *Queue) void {
        var index: usize = 0;
        while (index + 1 < capacity) : (index += 1) {
            self.entries[index] = self.entries[index + 1];
        }
        self.entries[capacity - 1] = null;
    }
};

pub fn durationTicks(duration_seconds: ?f32) u32 {
    const seconds = duration_seconds orelse return default_duration_ticks;
    const clamped_seconds = @max(seconds, 1.0 / 60.0);
    return @max(@as(u32, @intFromFloat(@round(clamped_seconds * 60.0))), 1);
}

test "queue displays entries in order until they expire" {
    var queue = Queue{};
    queue.enqueue("First", 2);
    queue.enqueue("Second", 3);

    try std.testing.expectEqualStrings("First", queue.active().?.message);
    queue.tick();
    try std.testing.expectEqualStrings("First", queue.active().?.message);
    queue.tick();
    try std.testing.expectEqualStrings("Second", queue.active().?.message);
}

test "queue ignores new entries when all slots are occupied" {
    var queue = Queue{};
    queue.enqueue("One", 5);
    queue.enqueue("Two", 5);
    queue.enqueue("Three", 5);
    queue.enqueue("Four", 5);

    try std.testing.expectEqualStrings("One", queue.entries[0].?.message);
    try std.testing.expectEqualStrings("Two", queue.entries[1].?.message);
    try std.testing.expectEqualStrings("Three", queue.entries[2].?.message);
}

test "duration ticks use authored seconds when present" {
    try std.testing.expectEqual(default_duration_ticks, durationTicks(null));
    try std.testing.expectEqual(@as(u32, 330), durationTicks(5.5));
    try std.testing.expectEqual(@as(u32, 1), durationTicks(0.0));
}
