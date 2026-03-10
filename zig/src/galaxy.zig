const std = @import("std");
const archive = @import("archive.zig");
const assets = @import("assets.zig");

pub const map_galaxy_count = 10;
// PORT(verified): `sub_4088E0` walks a flat 100-point Star Map table at `0x4A1D1C`,
// sampling each galaxy's authored 10-point block according to its live `StarNumber`.
// This is route-point capacity, not the shipped route count from `_GALAXY.TXT`.
pub const map_route_count = 100;

pub const Point = struct {
    x: f32,
    y: f32,
};

pub const Definition = struct {
    arena: std.heap.ArenaAllocator,
    names: []const []const u8,
    star_counts: []const usize,

    pub fn deinit(self: *Definition) void {
        self.arena.deinit();
    }

    pub fn nameForRouteIndex(self: *const Definition, route_index: usize) ?[]const u8 {
        const galaxy_index = self.galaxyIndexForRouteIndex(route_index) orelse return null;
        return self.names[galaxy_index];
    }

    pub fn starCountForGalaxyIndex(self: *const Definition, galaxy_index: usize) ?usize {
        if (galaxy_index >= self.star_counts.len) return null;
        return self.star_counts[galaxy_index];
    }

    pub fn galaxyIndexForRouteIndex(self: *const Definition, route_index: usize) ?usize {
        if (route_index == 0) return null;

        var remaining = route_index;
        for (self.star_counts, 0..) |star_count, galaxy_index| {
            if (remaining <= star_count) return galaxy_index;
            remaining -= star_count;
        }
        return null;
    }

    pub fn routePointForRouteIndex(self: *const Definition, route_index: usize) ?Point {
        const raw_slot = self.rawRoutePointSlotForRouteIndex(route_index) orelse return null;
        return routePoint(raw_slot);
    }

    // PORT(verified): `sub_4088E0` does not assign route stars sequentially. Each galaxy
    // owns a 10-point authored block, and the local route index samples that block with
    // `floor(local_index * 10 / star_count)`.
    pub fn rawRoutePointSlotForRouteIndex(self: *const Definition, route_index: usize) ?usize {
        const galaxy_index = self.galaxyIndexForRouteIndex(route_index) orelse return null;
        const star_count = self.starCountForGalaxyIndex(galaxy_index) orelse return null;
        if (star_count == 0) return null;

        const local_route_index = route_index - self.firstRouteIndexForGalaxyIndex(galaxy_index);
        if (local_route_index >= star_count) return null;

        const group_base = galaxy_index * 10;
        const slot = group_base + @divFloor(local_route_index * 10, star_count);
        if (slot >= raw_route_points.len) return null;
        return slot;
    }

    fn firstRouteIndexForGalaxyIndex(self: *const Definition, galaxy_index: usize) usize {
        var route_index: usize = 1;
        for (self.star_counts[0..galaxy_index]) |star_count| {
            route_index += star_count;
        }
        return route_index;
    }
};

// PORT(verified): the Windows Star Map initializer at `sub_4088E0` scales these authored
// route and galaxy coordinates before `initialize_galaxy` and `update_galaxy` consume them.
// The route points come from the flat float table starting at `0x4A1D1C`, and the galaxy
// centers come from the ten pairs starting at `0x4A1C4C`.
const raw_galaxy_centers = [_]Point{
    .{ .x = 104.0, .y = 253.0 },
    .{ .x = 239.0, .y = 149.0 },
    .{ .x = 415.0, .y = 95.0 },
    .{ .x = 583.0, .y = 111.0 },
    .{ .x = 715.0, .y = 211.0 },
    .{ .x = 703.0, .y = 374.0 },
    .{ .x = 592.0, .y = 506.0 },
    .{ .x = 368.0, .y = 523.0 },
    .{ .x = 275.0, .y = 395.0 },
    .{ .x = 428.0, .y = 292.0 },
};

const raw_route_points = [_]Point{
    .{ .x = 80.0, .y = 311.0 },
    .{ .x = 83.0, .y = 302.0 },
    .{ .x = 67.0, .y = 249.0 },
    .{ .x = 123.0, .y = 285.0 },
    .{ .x = 131.0, .y = 253.0 },
    .{ .x = 116.0, .y = 212.0 },
    .{ .x = 83.0, .y = 179.0 },
    .{ .x = 142.0, .y = 186.0 },
    .{ .x = 150.0, .y = 223.0 },
    .{ .x = 199.0, .y = 224.0 },
    .{ .x = 202.0, .y = 177.0 },
    .{ .x = 238.0, .y = 193.0 },
    .{ .x = 258.0, .y = 169.0 },
    .{ .x = 223.0, .y = 158.0 },
    .{ .x = 218.0, .y = 125.0 },
    .{ .x = 256.0, .y = 81.0 },
    .{ .x = 274.0, .y = 111.0 },
    .{ .x = 279.0, .y = 149.0 },
    .{ .x = 314.0, .y = 154.0 },
    .{ .x = 327.0, .y = 111.0 },
    .{ .x = 375.0, .y = 125.0 },
    .{ .x = 386.0, .y = 152.0 },
    .{ .x = 421.0, .y = 129.0 },
    .{ .x = 372.0, .y = 84.0 },
    .{ .x = 402.0, .y = 64.0 },
    .{ .x = 419.0, .y = 30.0 },
    .{ .x = 442.0, .y = 82.0 },
    .{ .x = 458.0, .y = 118.0 },
    .{ .x = 493.0, .y = 79.0 },
    .{ .x = 509.0, .y = 112.0 },
    .{ .x = 530.0, .y = 131.0 },
    .{ .x = 544.0, .y = 95.0 },
    .{ .x = 573.0, .y = 61.0 },
    .{ .x = 562.0, .y = 135.0 },
    .{ .x = 602.0, .y = 130.0 },
    .{ .x = 594.0, .y = 87.0 },
    .{ .x = 633.0, .y = 104.0 },
    .{ .x = 603.0, .y = 185.0 },
    .{ .x = 643.0, .y = 157.0 },
    .{ .x = 687.0, .y = 149.0 },
    .{ .x = 708.0, .y = 177.0 },
    .{ .x = 668.0, .y = 191.0 },
    .{ .x = 676.0, .y = 236.0 },
    .{ .x = 771.0, .y = 140.0 },
    .{ .x = 756.0, .y = 186.0 },
    .{ .x = 758.0, .y = 217.0 },
    .{ .x = 731.0, .y = 245.0 },
    .{ .x = 768.0, .y = 266.0 },
    .{ .x = 736.0, .y = 286.0 },
    .{ .x = 778.0, .y = 321.0 },
    .{ .x = 752.0, .y = 347.0 },
    .{ .x = 758.0, .y = 397.0 },
    .{ .x = 754.0, .y = 460.0 },
    .{ .x = 711.0, .y = 409.0 },
    .{ .x = 700.0, .y = 339.0 },
    .{ .x = 654.0, .y = 339.0 },
    .{ .x = 639.0, .y = 386.0 },
    .{ .x = 670.0, .y = 423.0 },
    .{ .x = 670.0, .y = 464.0 },
    .{ .x = 622.0, .y = 426.0 },
    .{ .x = 637.0, .y = 471.0 },
    .{ .x = 629.0, .y = 504.0 },
    .{ .x = 616.0, .y = 534.0 },
    .{ .x = 560.0, .y = 541.0 },
    .{ .x = 552.0, .y = 503.0 },
    .{ .x = 582.0, .y = 472.0 },
    .{ .x = 536.0, .y = 414.0 },
    .{ .x = 533.0, .y = 474.0 },
    .{ .x = 509.0, .y = 527.0 },
    .{ .x = 486.0, .y = 485.0 },
    .{ .x = 440.0, .y = 530.0 },
    .{ .x = 411.0, .y = 519.0 },
    .{ .x = 396.0, .y = 558.0 },
    .{ .x = 332.0, .y = 568.0 },
    .{ .x = 292.0, .y = 536.0 },
    .{ .x = 324.0, .y = 512.0 },
    .{ .x = 386.0, .y = 482.0 },
    .{ .x = 383.0, .y = 443.0 },
    .{ .x = 340.0, .y = 483.0 },
    .{ .x = 310.0, .y = 456.0 },
    .{ .x = 304.0, .y = 424.0 },
    .{ .x = 264.0, .y = 439.0 },
    .{ .x = 210.0, .y = 468.0 },
    .{ .x = 197.0, .y = 421.0 },
    .{ .x = 236.0, .y = 402.0 },
    .{ .x = 218.0, .y = 368.0 },
    .{ .x = 281.0, .y = 344.0 },
    .{ .x = 308.0, .y = 363.0 },
    .{ .x = 327.0, .y = 383.0 },
    .{ .x = 342.0, .y = 248.0 },
    .{ .x = 376.0, .y = 309.0 },
    .{ .x = 417.0, .y = 345.0 },
    .{ .x = 472.0, .y = 357.0 },
    .{ .x = 461.0, .y = 311.0 },
    .{ .x = 486.0, .y = 298.0 },
    .{ .x = 521.0, .y = 232.0 },
    .{ .x = 483.0, .y = 252.0 },
    .{ .x = 448.0, .y = 236.0 },
    .{ .x = 418.0, .y = 219.0 },
    .{ .x = 376.0, .y = 268.0 },
};

pub fn galaxyCenter(index: usize) Point {
    return transformAuthoredPoint(raw_galaxy_centers[index]);
}

pub fn routePoint(index: usize) Point {
    return transformAuthoredPoint(raw_route_points[index]);
}

pub fn routePointForRouteIndex(route_index: usize) ?Point {
    if (route_index == 0 or route_index > raw_route_points.len) return null;
    return routePoint(route_index - 1);
}

fn transformAuthoredPoint(raw: Point) Point {
    return .{
        .x = raw.x * 0.8,
        .y = (raw.y * 0.8 - 240.0) * 0.93 + 250.0,
    };
}

pub fn loadByPath(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    path: []const u8,
) !Definition {
    const entry = catalog.dat.entryByPath(path) orelse return error.EntryNotFound;
    return loadFromArchive(allocator, catalog, entry);
}

pub fn loadFromArchive(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    entry: archive.Entry,
) !Definition {
    const decoded = try catalog.readEntryAlloc(allocator, entry);
    defer allocator.free(decoded);
    return parseText(allocator, decoded);
}

pub fn parseText(allocator: std.mem.Allocator, data: []const u8) !Definition {
    var arena = std.heap.ArenaAllocator.init(allocator);
    errdefer arena.deinit();
    const arena_allocator = arena.allocator();

    var names = std.ArrayList([]const u8).empty;
    defer names.deinit(arena_allocator);
    var star_counts = std.ArrayList(usize).empty;
    defer star_counts.deinit(arena_allocator);

    var lines = std.mem.splitScalar(u8, data, '\n');
    while (lines.next()) |raw_line| {
        const line = std.mem.trim(u8, raw_line, " \t\r");

        if (std.mem.startsWith(u8, line, "Galaxy")) {
            const colon_index = std.mem.indexOfScalar(u8, line, ':') orelse continue;
            const quoted = std.mem.trim(u8, line[colon_index + 1 ..], " \t");
            if (quoted.len < 2 or quoted[0] != '"' or quoted[quoted.len - 1] != '"') {
                return error.InvalidGalaxyScript;
            }
            try names.append(arena_allocator, try arena_allocator.dupe(u8, quoted[1 .. quoted.len - 1]));
            continue;
        }

        if (std.mem.startsWith(u8, line, "StarNumber")) {
            const equals_index = std.mem.indexOfScalar(u8, line, '=') orelse return error.InvalidGalaxyScript;
            const value = std.mem.trim(u8, line[equals_index + 1 ..], " \t");
            try star_counts.append(arena_allocator, try std.fmt.parseUnsigned(usize, value, 10));
        }
    }

    if (names.items.len != star_counts.items.len) {
        return error.InvalidGalaxyScript;
    }

    return .{
        .arena = arena,
        .names = try names.toOwnedSlice(arena_allocator),
        .star_counts = try star_counts.toOwnedSlice(arena_allocator),
    };
}

test "parse galaxy names" {
    const data =
        \\/* Galaxy map script file */
        \\
        \\Galaxy0:"Pomacea cuprina"
        \\StarNumber=5
        \\
        \\Galaxy1:"Ferrissia rivularis"
        \\StarNumber=5
    ;

    var parsed = try parseText(std.testing.allocator, data);
    defer parsed.deinit();

    try std.testing.expectEqual(@as(usize, 2), parsed.names.len);
    try std.testing.expectEqualStrings("Pomacea cuprina", parsed.names[0]);
    try std.testing.expectEqualStrings("Ferrissia rivularis", parsed.nameForRouteIndex(6).?);
    try std.testing.expectEqual(@as(usize, 5), parsed.starCountForGalaxyIndex(0).?);
    try std.testing.expectEqual(@as(usize, 5), parsed.starCountForGalaxyIndex(1).?);
}

test "route point slots sample each galaxy block by star count" {
    const data =
        \\Galaxy0:"Pomacea cuprina"
        \\StarNumber=5
        \\Galaxy1:"Ferrissia rivularis"
        \\StarNumber=4
    ;

    var parsed = try parseText(std.testing.allocator, data);
    defer parsed.deinit();

    const first_galaxy_slots = [_]usize{ 0, 2, 4, 6, 8 };
    for (first_galaxy_slots, 0..) |expected_slot, local_index| {
        try std.testing.expectEqual(expected_slot, parsed.rawRoutePointSlotForRouteIndex(local_index + 1).?);
    }

    const second_galaxy_slots = [_]usize{ 10, 12, 15, 17 };
    for (second_galaxy_slots, 0..) |expected_slot, local_index| {
        try std.testing.expectEqual(expected_slot, parsed.rawRoutePointSlotForRouteIndex(6 + local_index).?);
    }
}

test "route point slots reach later authored galaxy blocks" {
    const data =
        \\Galaxy0:"Pomacea cuprina"
        \\StarNumber=5
        \\Galaxy1:"Ferrissia rivularis"
        \\StarNumber=5
        \\Galaxy2:"Marisa rotula"
        \\StarNumber=5
        \\Galaxy3:"Planoribis rubrum"
        \\StarNumber=5
        \\Galaxy4:"Viviparis malleatus"
        \\StarNumber=5
        \\Galaxy5:"Melanoides tuberculata"
        \\StarNumber=5
        \\Galaxy6:"Helisoma"
        \\StarNumber=5
        \\Galaxy7:"Planorbis corneus"
        \\StarNumber=5
        \\Galaxy8:"Segmentina victoriae"
        \\StarNumber=5
        \\Galaxy9:"Pomacea cuprina aurea"
        \\StarNumber=5
    ;

    var parsed = try parseText(std.testing.allocator, data);
    defer parsed.deinit();

    try std.testing.expectEqual(@as(usize, 50), parsed.rawRoutePointSlotForRouteIndex(26).?);
    try std.testing.expectEqual(@as(usize, 58), parsed.rawRoutePointSlotForRouteIndex(30).?);
    try std.testing.expectEqual(@as(usize, 90), parsed.rawRoutePointSlotForRouteIndex(46).?);
    try std.testing.expectEqual(@as(usize, 98), parsed.rawRoutePointSlotForRouteIndex(50).?);
}
