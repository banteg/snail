const std = @import("std");

pub const default_duration_ticks: u32 = 180;
pub const capacity: usize = 3;

pub const Entry = struct {
    message: []const u8,
    ticks_remaining: u32,
    interactive: bool = false,
};

pub const Options = struct {
    interactive: bool = false,
};

pub const Queue = struct {
    entries: [capacity]?Entry = [_]?Entry{null} ** capacity,

    pub fn clear(self: *Queue) void {
        self.* = .{};
    }

    pub fn active(self: *const Queue) ?Entry {
        for (self.entries) |slot| {
            if (slot) |entry| return entry;
        }
        return null;
    }

    pub fn tick(self: *Queue) void {
        for (&self.entries) |*slot| {
            if (slot.*) |*entry| {
                if (entry.interactive) continue;
                if (entry.ticks_remaining > 0) {
                    entry.ticks_remaining -= 1;
                }
                if (entry.ticks_remaining == 0) {
                    slot.* = null;
                }
            }
        }
        self.compact();
    }

    pub fn enqueue(self: *Queue, message: []const u8, duration_ticks: u32) void {
        self.enqueueWithOptions(message, duration_ticks, .{});
    }

    pub fn enqueueWithOptions(self: *Queue, message: []const u8, duration_ticks: u32, options: Options) void {
        if (message.len == 0) return;

        for (&self.entries) |*slot| {
            if (slot.* == null) {
                slot.* = .{
                    .message = message,
                    .ticks_remaining = @max(duration_ticks, 1),
                    .interactive = options.interactive,
                };
                return;
            }
        }
    }

    pub fn replaceSingle(self: *Queue, message: []const u8, duration_ticks: u32) void {
        self.replaceSingleWithOptions(message, duration_ticks, .{});
    }

    pub fn replaceSingleWithOptions(self: *Queue, message: []const u8, duration_ticks: u32, options: Options) void {
        self.clear();
        self.enqueueWithOptions(message, duration_ticks, options);
    }

    pub fn dismissActive(self: *Queue) void {
        for (&self.entries) |*slot| {
            if (slot.* != null) {
                slot.* = null;
                break;
            }
        }
        self.compact();
    }

    fn compact(self: *Queue) void {
        var next_index: usize = 0;
        for (self.entries) |slot| {
            if (slot) |entry| {
                self.entries[next_index] = entry;
                next_index += 1;
            }
        }
        while (next_index < capacity) : (next_index += 1) {
            self.entries[next_index] = null;
        }
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

test "queue ticks entries in parallel and compacts expired slots" {
    var queue = Queue{};
    queue.enqueue("One", 1);
    queue.enqueue("Two", 3);
    queue.enqueue("Three", 2);

    queue.tick();
    try std.testing.expectEqualStrings("Two", queue.entries[0].?.message);
    try std.testing.expectEqualStrings("Three", queue.entries[1].?.message);
    try std.testing.expect(queue.entries[2] == null);

    queue.tick();
    try std.testing.expectEqualStrings("Two", queue.entries[0].?.message);
    try std.testing.expect(queue.entries[1] == null);
}

test "replace single clears older entries before showing the new one" {
    var queue = Queue{};
    queue.enqueue("One", 5);
    queue.enqueue("Two", 5);

    queue.replaceSingle("Three", 7);

    try std.testing.expectEqualStrings("Three", queue.active().?.message);
    try std.testing.expect(queue.entries[1] == null);
    try std.testing.expect(queue.entries[2] == null);
}

test "entry options are preserved when enqueued" {
    var queue = Queue{};
    queue.enqueueWithOptions("Prompt", 12, .{ .interactive = true });

    try std.testing.expect(queue.active().?.interactive);
}

test "interactive entries do not expire while ticking" {
    var queue = Queue{};
    queue.enqueueWithOptions("Prompt", 2, .{ .interactive = true });

    queue.tick();
    queue.tick();
    queue.tick();

    try std.testing.expect(queue.active() != null);
    try std.testing.expectEqualStrings("Prompt", queue.active().?.message);
}

test "duration ticks use authored seconds when present" {
    try std.testing.expectEqual(default_duration_ticks, durationTicks(null));
    try std.testing.expectEqual(@as(u32, 330), durationTicks(5.5));
    try std.testing.expectEqual(@as(u32, 1), durationTicks(0.0));
}
