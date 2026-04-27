const std = @import("std");

pub const life_threshold: u32 = 50_000;
pub const starting_visible_life_stock: u32 = 3;
pub const maximum_visible_life_stock: u32 = 9;

pub const Totals = struct {
    total: u32 = 0,
    garbage: u32 = 0,
    slug: u32 = 0,
    ring: u32 = 0,
    parcel_collect: u32 = 0,
    parcel_deliver: u32 = 0,
    bonus: u32 = 0,
};

pub const Event = enum(u3) {
    garbage = 0,
    slug = 1,
    ring = 2,
    parcel_collect = 3,
    parcel_deliver = 4,
    bonus = 5,
};

pub fn nativeEventPoints(event: Event, bonus_points: u32) u32 {
    return switch (event) {
        .garbage => 10,
        .slug => 500,
        .ring, .parcel_collect, .parcel_deliver => 100,
        .bonus => bonus_points,
    };
}

pub fn bucket(score: *Totals, event: Event) *u32 {
    return switch (event) {
        .garbage => &score.garbage,
        .slug => &score.slug,
        .ring => &score.ring,
        .parcel_collect => &score.parcel_collect,
        .parcel_deliver => &score.parcel_deliver,
        .bonus => &score.bonus,
    };
}

pub fn add(score: *Totals, event: Event, bonus_points: u32) u32 {
    const points = nativeEventPoints(event, bonus_points);
    const slot = bucket(score, event);
    slot.* = std.math.add(u32, slot.*, points) catch std.math.maxInt(u32);
    score.total = std.math.add(u32, score.total, points) catch std.math.maxInt(u32);
    return points;
}

// PORT(verified): Windows `cRSubGoldy::ScoreAdd(int,int)` owns the six score buckets
// at offsets 0x310..0x324, applies the fixed event point table above, and awards one
// visible life whenever total score crosses another 50,000-point bucket, capped at 9.
// Postal respawn consumption is committed by the runner's death/resurrect handoff.
pub fn visibleLifeStockAfterScore(previous_stock: u32, previous_total: u32, current_total: u32) u32 {
    const previous_bucket = @divTrunc(previous_total, life_threshold);
    const current_bucket = @divTrunc(current_total, life_threshold);
    if (current_bucket <= previous_bucket) return previous_stock;
    const crossed_buckets = current_bucket - previous_bucket;
    const updated_lives = std.math.add(u32, previous_stock, crossed_buckets) catch std.math.maxInt(u32);
    return @min(maximum_visible_life_stock, updated_lives);
}
