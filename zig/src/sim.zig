const std = @import("std");

pub const FixedStepClock = struct {
    step_seconds: f64,
    max_frame_delta_seconds: f64 = 0.25,
    max_ticks_per_frame: usize = 8,
    accumulator_seconds: f64 = 0.0,
    simulation_time_seconds: f64 = 0.0,
    tick_count: u64 = 0,

    pub fn init(step_seconds: f64) FixedStepClock {
        std.debug.assert(step_seconds > 0.0);
        return .{ .step_seconds = step_seconds };
    }

    pub fn beginFrame(self: *FixedStepClock, frame_delta_seconds: f64) usize {
        const clamped = std.math.clamp(frame_delta_seconds, 0.0, self.max_frame_delta_seconds);
        self.accumulator_seconds += clamped;

        var ticks: usize = 0;
        while (self.accumulator_seconds + 0.000000000001 >= self.step_seconds and ticks < self.max_ticks_per_frame) {
            self.accumulator_seconds -= self.step_seconds;
            self.simulation_time_seconds += self.step_seconds;
            self.tick_count += 1;
            ticks += 1;
        }

        if (ticks == self.max_ticks_per_frame and self.accumulator_seconds >= self.step_seconds) {
            self.accumulator_seconds = @mod(self.accumulator_seconds, self.step_seconds);
        }

        return ticks;
    }

    pub fn renderAlpha(self: *const FixedStepClock) f64 {
        return std.math.clamp(self.accumulator_seconds / self.step_seconds, 0.0, 1.0);
    }
};

test "fixed step clock accumulates ticks deterministically" {
    var clock = FixedStepClock.init(1.0 / 60.0);

    try std.testing.expectEqual(@as(usize, 0), clock.beginFrame(1.0 / 120.0));
    try std.testing.expectEqual(@as(usize, 1), clock.beginFrame(1.0 / 120.0));
    try std.testing.expectEqual(@as(u64, 1), clock.tick_count);
    try std.testing.expectApproxEqAbs(@as(f64, 1.0 / 60.0), clock.simulation_time_seconds, 0.0000001);
}

test "fixed step clock is insensitive to render pacing" {
    var coarse = FixedStepClock.init(1.0 / 60.0);
    var fine = FixedStepClock.init(1.0 / 60.0);

    _ = coarse.beginFrame(1.0 / 30.0);
    try std.testing.expectEqual(@as(u64, 2), coarse.tick_count);

    var fine_ticks: usize = 0;
    fine_ticks += fine.beginFrame(1.0 / 120.0);
    fine_ticks += fine.beginFrame(1.0 / 120.0);
    fine_ticks += fine.beginFrame(1.0 / 120.0);
    fine_ticks += fine.beginFrame(1.0 / 120.0);

    try std.testing.expectEqual(@as(usize, 2), fine_ticks);
    try std.testing.expectEqual(coarse.tick_count, fine.tick_count);
    try std.testing.expectApproxEqAbs(coarse.simulation_time_seconds, fine.simulation_time_seconds, 0.0000001);
}

test "fixed step clock clamps runaway frames" {
    var clock = FixedStepClock.init(1.0 / 60.0);
    clock.max_ticks_per_frame = 4;

    try std.testing.expectEqual(@as(usize, 4), clock.beginFrame(1.0));
    try std.testing.expectEqual(@as(u64, 4), clock.tick_count);
    try std.testing.expect(clock.accumulator_seconds < clock.step_seconds);
}
