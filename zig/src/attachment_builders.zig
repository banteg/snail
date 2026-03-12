const std = @import("std");
const segment = @import("segment.zig");

pub const PublicPath = enum(u8) {
    looptheloop = 0,
    looptheloop2,
    looptheloop4,
    looptheloopt2,
    looptheloopt3,
    looptheloopt4,
    looptheloopw,
    loopbow,
    hill,
    hill4c,
    hill4,
    valley,
    valley4c,
    valley4,
    sbend,
    cage2,
    hump,
    dump,
    humpsmall,
    dumpsmall,
    dip,
    screw,
    slalom,
    slalombig,
    worm,
    loopout,
    loopout3,
    loopoutbig,
    sweep,
    snake,
    warp,
    supertramp,
    slalomdouble,
    p0,
    p1,
    p2,
    start,
    turnover,
    turnoverdouble,
    turnunder,
    wibble,
    invert,
    halfpipe,
    twistera,
    twisterb,
    twister2a,
    twister2b,
    toad0,
    toad1,
    toadpair0,
    toadpair1,

    pub fn authoredName(self: PublicPath) []const u8 {
        return public_path_names[@intFromEnum(self)];
    }
};

pub const BuilderFamily = enum {
    looptheloop,
    looptheloopw,
    loopbow,
    hill_valley,
    sbend,
    cage2,
    hump,
    dump,
    dip,
    screw,
    slalom,
    slalombig,
    worm,
    loopout,
    sweep,
    snake,
    kind42,
    supertramp,
    slalomdouble,
    p_family,
    start,
    turnover,
    turnoverdouble,
    turnunder,
    wibble,
    invert,
    twister,
    twister2,
    toad,

    pub fn label(self: BuilderFamily) []const u8 {
        return switch (self) {
            .looptheloop => "looptheloop",
            .looptheloopw => "looptheloopw",
            .loopbow => "loopbow",
            .hill_valley => "hill_valley",
            .sbend => "sbend",
            .cage2 => "cage2",
            .hump => "hump",
            .dump => "dump",
            .dip => "dip",
            .screw => "screw",
            .slalom => "slalom",
            .slalombig => "slalombig",
            .worm => "worm",
            .loopout => "loopout",
            .sweep => "sweep",
            .snake => "snake",
            .kind42 => "kind42",
            .supertramp => "supertramp",
            .slalomdouble => "slalomdouble",
            .p_family => "p_family",
            .start => "start",
            .turnover => "turnover",
            .turnoverdouble => "turnoverdouble",
            .turnunder => "turnunder",
            .wibble => "wibble",
            .invert => "invert",
            .twister => "twister",
            .twister2 => "twister2",
            .toad => "toad",
        };
    }
};

pub const PortStatus = enum {
    scaffold,
    partial,
    ported,

    pub fn label(self: PortStatus) []const u8 {
        return switch (self) {
            .scaffold => "scaffold",
            .partial => "partial",
            .ported => "ported",
        };
    }
};

pub const TemplateSpec = struct {
    public_path: PublicPath,
    family: BuilderFamily,
    status: PortStatus,
    runtime_kind: ?u8 = null,
    sample_count: ?u16 = null,
    subdivision_count: ?u16 = null,
};

// PORT(scaffold): this is the future shared shape for Windows-style installed path
// templates. The current port only fills the authored-path registry and dispatch.
pub const TemplateSample = struct {
    position: [3]f32 = .{ 0.0, 0.0, 0.0 },
    delta_dir_to_next: [3]f32 = .{ 0.0, 0.0, 0.0 },
    delta_length: f32 = 0.0,
    center_x: f32 = 0.0,
    lateral_scale: f32 = 1.0,
    special_scalar: f32 = 0.0,
};

// PORT(scaffold): the builder scaffold will eventually populate these from the
// recovered Windows constructor families instead of row-local metadata.
pub const Template = struct {
    spec: TemplateSpec,
    samples: []const TemplateSample = &.{},
};

pub const AuthoredPathRow = struct {
    global_row: usize,
    segment_index: usize,
    row_index: usize,
    raw_name: []const u8,
    public_path: ?PublicPath,

    pub fn spec(self: AuthoredPathRow) ?TemplateSpec {
        return if (self.public_path) |public_path| specForPublicPath(public_path) else null;
    }
};

pub const Scaffold = struct {
    allocator: std.mem.Allocator,
    authored_rows: []AuthoredPathRow,

    pub fn collect(
        allocator: std.mem.Allocator,
        segments: []const segment.Definition,
        row_offsets: []const usize,
    ) !Scaffold {
        var rows: std.ArrayList(AuthoredPathRow) = .empty;
        defer rows.deinit(allocator);

        for (segments, 0..) |loaded_segment, segment_index| {
            const row_base = row_offsets[segment_index];
            for (loaded_segment.rows, 0..) |row, row_index| {
                const annotation = row.annotation orelse continue;
                const raw_name = switch (annotation) {
                    .path => |path_name| path_name,
                    else => continue,
                };
                try rows.append(allocator, .{
                    .global_row = row_base + row_index,
                    .segment_index = segment_index,
                    .row_index = row_index,
                    .raw_name = raw_name,
                    .public_path = publicPathFromName(raw_name),
                });
            }
        }

        return .{
            .allocator = allocator,
            .authored_rows = try rows.toOwnedSlice(allocator),
        };
    }

    pub fn deinit(self: *Scaffold) void {
        self.allocator.free(self.authored_rows);
    }

    pub fn activePathAtRow(self: *const Scaffold, global_row: usize) ?AuthoredPathRow {
        var active: ?AuthoredPathRow = null;
        for (self.authored_rows) |row| {
            if (row.global_row > global_row) break;
            active = row;
        }
        return active;
    }

    pub fn pathCountForSegment(self: *const Scaffold, segment_index: usize) usize {
        var count: usize = 0;
        for (self.authored_rows) |row| {
            if (row.segment_index == segment_index) count += 1;
        }
        return count;
    }

    pub fn firstPathForSegment(self: *const Scaffold, segment_index: usize) ?AuthoredPathRow {
        for (self.authored_rows) |row| {
            if (row.segment_index == segment_index) return row;
        }
        return null;
    }
};

pub fn publicPathFromName(name: []const u8) ?PublicPath {
    inline for (public_path_names, 0..) |candidate, index| {
        if (std.ascii.eqlIgnoreCase(name, candidate)) {
            return @enumFromInt(index);
        }
    }
    return null;
}

pub fn specForPublicPath(public_path: PublicPath) TemplateSpec {
    return switch (public_path) {
        .looptheloop,
        .looptheloop2,
        .looptheloop4,
        .looptheloopt2,
        .looptheloopt3,
        .looptheloopt4,
        => .{ .public_path = public_path, .family = .looptheloop, .status = .scaffold },
        .looptheloopw => .{ .public_path = public_path, .family = .looptheloopw, .status = .scaffold },
        .loopbow => .{ .public_path = public_path, .family = .loopbow, .status = .scaffold, .runtime_kind = 0 },
        .hill, .hill4c, .hill4, .valley, .valley4c, .valley4 => .{ .public_path = public_path, .family = .hill_valley, .status = .scaffold },
        .sbend => .{ .public_path = public_path, .family = .sbend, .status = .scaffold },
        .cage2 => .{ .public_path = public_path, .family = .cage2, .status = .scaffold },
        .hump, .humpsmall => .{ .public_path = public_path, .family = .hump, .status = .scaffold },
        .dump, .dumpsmall => .{ .public_path = public_path, .family = .dump, .status = .scaffold },
        .dip => .{ .public_path = public_path, .family = .dip, .status = .scaffold },
        .screw => .{ .public_path = public_path, .family = .screw, .status = .scaffold },
        .slalom => .{ .public_path = public_path, .family = .slalom, .status = .scaffold },
        .slalombig => .{ .public_path = public_path, .family = .slalombig, .status = .partial, .runtime_kind = 23 },
        .worm => .{ .public_path = public_path, .family = .worm, .status = .scaffold },
        .loopout, .loopout3, .loopoutbig => .{ .public_path = public_path, .family = .loopout, .status = .partial },
        .sweep => .{ .public_path = public_path, .family = .sweep, .status = .partial },
        .snake => .{ .public_path = public_path, .family = .snake, .status = .partial },
        .warp, .halfpipe => .{ .public_path = public_path, .family = .kind42, .status = .partial, .runtime_kind = 42, .sample_count = 66, .subdivision_count = 8 },
        .supertramp => .{ .public_path = public_path, .family = .supertramp, .status = .partial, .runtime_kind = 31 },
        .slalomdouble => .{ .public_path = public_path, .family = .slalomdouble, .status = .partial, .runtime_kind = 32, .sample_count = 70, .subdivision_count = 4 },
        .p0 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .runtime_kind = 33, .sample_count = 16, .subdivision_count = 3 },
        .p1 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .runtime_kind = 34, .sample_count = 16, .subdivision_count = 3 },
        .p2 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .runtime_kind = 35, .sample_count = 16, .subdivision_count = 3 },
        .start => .{ .public_path = public_path, .family = .start, .status = .partial, .runtime_kind = 36, .sample_count = 27, .subdivision_count = 8 },
        .turnover => .{ .public_path = public_path, .family = .turnover, .status = .partial, .runtime_kind = 39 },
        .turnoverdouble => .{ .public_path = public_path, .family = .turnoverdouble, .status = .partial },
        .turnunder => .{ .public_path = public_path, .family = .turnunder, .status = .partial, .runtime_kind = 39, .sample_count = 45, .subdivision_count = 4 },
        .wibble => .{ .public_path = public_path, .family = .wibble, .status = .partial, .runtime_kind = 40 },
        .invert => .{ .public_path = public_path, .family = .invert, .status = .partial },
        .twistera, .twisterb => .{ .public_path = public_path, .family = .twister, .status = .partial },
        .twister2a, .twister2b => .{ .public_path = public_path, .family = .twister2, .status = .partial },
        .toad0, .toad1, .toadpair0, .toadpair1 => .{ .public_path = public_path, .family = .toad, .status = .partial },
    };
}

const public_path_names = [_][]const u8{
    "LOOPTHELOOP",
    "LOOPTHELOOP2",
    "LOOPTHELOOP4",
    "LOOPTHELOOPT2",
    "LOOPTHELOOPT3",
    "LOOPTHELOOPT4",
    "LOOPTHELOOPW",
    "LOOPBOW",
    "HILL",
    "HILL4C",
    "HILL4",
    "VALLEY",
    "VALLEY4C",
    "VALLEY4",
    "SBEND",
    "CAGE2",
    "HUMP",
    "DUMP",
    "HUMPSMALL",
    "DUMPSMALL",
    "DIP",
    "SCREW",
    "SLALOM",
    "SLALOMBIG",
    "WORM",
    "LOOPOUT",
    "LOOPOUT3",
    "LOOPOUTBIG",
    "SWEEP",
    "SNAKE",
    "WARP",
    "SUPERTRAMP",
    "SLALOMDOUBLE",
    "P0",
    "P1",
    "P2",
    "START",
    "TURNOVER",
    "TURNOVERDOUBLE",
    "TURNUNDER",
    "WIBBLE",
    "INVERT",
    "HALFPIPE",
    "TWISTERA",
    "TWISTERB",
    "TWISTER2A",
    "TWISTER2B",
    "TOAD0",
    "TOAD1",
    "TOADPAIR0",
    "TOADPAIR1",
};

test "public path lookup matches recovered windows table" {
    try std.testing.expectEqual(PublicPath.start, publicPathFromName("START").?);
    try std.testing.expectEqual(PublicPath.halfpipe, publicPathFromName("halfpipe").?);
    try std.testing.expectEqual(PublicPath.warp, publicPathFromName("WARP").?);
    try std.testing.expect(publicPathFromName("HALFPOLE") == null);
}

test "collect scaffold keeps active authored path row" {
    const source =
        \\ID: 1
        \\Name: 'Scaffold'
        \\Data:
        \\.......... Path=START
        \\PPPPPPPPPP
        \\.......... Path=HALFPIPE
        \\pppppppppp
    ;

    var parsed = try segment.parseText(std.testing.allocator, source, "SEGMENTS/SCAFFOLD.TXT");
    defer parsed.deinit();

    const segments = [_]segment.Definition{parsed};
    const row_offsets = [_]usize{0};
    var scaffold = try Scaffold.collect(std.testing.allocator, &segments, &row_offsets);
    defer scaffold.deinit();

    try std.testing.expectEqual(@as(usize, 2), scaffold.authored_rows.len);
    try std.testing.expectEqual(PublicPath.start, scaffold.activePathAtRow(1).?.public_path.?);
    try std.testing.expectEqual(PublicPath.halfpipe, scaffold.activePathAtRow(3).?.public_path.?);
}
