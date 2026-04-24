const std = @import("std");

pub const life_threshold: u32 = 50_000;
pub const starting_visible_life_stock: u32 = 3;
pub const maximum_visible_life_stock: u32 = 9;

pub const Totals = struct {
    total: u32 = 0,
    ring_collect: u32 = 0,
    garbage_collision: u32 = 0,
    health_collect: u32 = 0,
    parcel_pickup: u32 = 0,
    parcel_register: u32 = 0,
    completion_bonus: u32 = 0,
};

pub fn add(score: *Totals, slot: *u32, points: u32) void {
    slot.* = std.math.add(u32, slot.*, points) catch std.math.maxInt(u32);
    score.total = std.math.add(u32, score.total, points) catch std.math.maxInt(u32);
}

// PORT(partial): Windows `populate_runtime_track_cells_from_segments` seeds Goldy's
// visible life stock to 3, and `cRSubGoldy::ScoreAdd` awards one more whenever total
// score crosses another 50,000-point bucket, capped at 9. Postal respawn consumption is
// now committed by the runner's death/resurrect handoff, not the app reload path.
pub fn visibleLifeStockAfterScore(previous_stock: u32, previous_total: u32, current_total: u32) u32 {
    const previous_bucket = @divTrunc(previous_total, life_threshold);
    const current_bucket = @divTrunc(current_total, life_threshold);
    if (current_bucket <= previous_bucket) return previous_stock;
    const crossed_buckets = current_bucket - previous_bucket;
    const updated_lives = std.math.add(u32, previous_stock, crossed_buckets) catch std.math.maxInt(u32);
    return @min(maximum_visible_life_stock, updated_lives);
}
