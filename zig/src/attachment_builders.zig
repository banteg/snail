const std = @import("std");
const segment = @import("segment.zig");

pub const Vec3 = struct {
    x: f32 = 0.0,
    y: f32 = 0.0,
    z: f32 = 0.0,

    pub fn add(a: Vec3, b: Vec3) Vec3 {
        return .{ .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
    }

    pub fn sub(a: Vec3, b: Vec3) Vec3 {
        return .{ .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
    }

    pub fn scale(v: Vec3, scalar: f32) Vec3 {
        return .{ .x = v.x * scalar, .y = v.y * scalar, .z = v.z * scalar };
    }

    pub fn lerp(a: Vec3, b: Vec3, t: f32) Vec3 {
        const inv_t = 1.0 - t;
        return .{
            .x = (a.x * inv_t) + (b.x * t),
            .y = (a.y * inv_t) + (b.y * t),
            .z = (a.z * inv_t) + (b.z * t),
        };
    }

    pub fn cross(a: Vec3, b: Vec3) Vec3 {
        return .{
            .x = (a.y * b.z) - (a.z * b.y),
            .y = (a.z * b.x) - (a.x * b.z),
            .z = (a.x * b.y) - (a.y * b.x),
        };
    }

    pub fn length(v: Vec3) f32 {
        return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    pub fn normalize(v: Vec3) Vec3 {
        const len = length(v);
        if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
        return scale(v, 1.0 / len);
    }
};

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
    basis_right: Vec3 = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    basis_up: Vec3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    basis_forward: Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    position: Vec3 = .{},
    delta_dir_to_next: Vec3 = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    delta_length: f32 = 0.0,
    center_x: f32 = 0.0,
    lateral_scale: f32 = 1.0,
    special_scalar: f32 = 0.0,
};

// PORT(scaffold): the builder scaffold will eventually populate these from the
// recovered Windows constructor families instead of row-local metadata.
pub const Template = struct {
    spec: TemplateSpec,
    width_cells: u16 = 0,
    sample_count: u16 = 0,
    exit_tail_extra: f32 = 0.0,
    samples: []TemplateSample = &.{},

    pub fn deinit(self: *Template, allocator: std.mem.Allocator) void {
        allocator.free(self.samples);
        self.samples = &.{};
    }

    pub fn pointCount(self: *const Template) usize {
        return self.samples.len;
    }
};

pub const BuiltAttachment = struct {
    row: AuthoredPathRow,
    template: Template,

    pub fn deinit(self: *BuiltAttachment, allocator: std.mem.Allocator) void {
        self.template.deinit(allocator);
    }
};

pub const AttachmentPose = struct {
    position: Vec3,
    center_x: f32,
    lateral_scale: f32,
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
    built_attachments: []BuiltAttachment,

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

        var built_attachments: std.ArrayList(BuiltAttachment) = .empty;
        defer built_attachments.deinit(allocator);
        errdefer {
            for (built_attachments.items) |*built| {
                built.deinit(allocator);
            }
        }

        for (rows.items) |row| {
            const spec = row.spec() orelse continue;
            const template = (try buildTemplate(allocator, spec)) orelse continue;
            try built_attachments.append(allocator, .{
                .row = row,
                .template = template,
            });
        }

        return .{
            .allocator = allocator,
            .authored_rows = try rows.toOwnedSlice(allocator),
            .built_attachments = try built_attachments.toOwnedSlice(allocator),
        };
    }

    pub fn deinit(self: *Scaffold) void {
        for (self.built_attachments) |*built| {
            built.deinit(self.allocator);
        }
        self.allocator.free(self.built_attachments);
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

    pub fn activeBuiltAttachmentAtRow(self: *const Scaffold, global_row: usize) ?*const BuiltAttachment {
        var active_index: ?usize = null;
        for (self.built_attachments, 0..) |built, index| {
            if (built.row.global_row > global_row) break;
            active_index = index;
        }
        if (active_index) |index| {
            return &self.built_attachments[index];
        }
        return null;
    }
};

pub fn samplePoseAtProgress(template: *const Template, progress: f32) AttachmentPose {
    if (template.samples.len == 0) {
        return .{
            .position = .{},
            .center_x = 0.0,
            .lateral_scale = 1.0,
        };
    }

    const clamped_progress = std.math.clamp(progress, 0.0, @as(f32, @floatFromInt(template.sample_count)));
    const base_index: usize = @intFromFloat(@floor(clamped_progress));
    if (base_index >= template.samples.len - 1) {
        const sample = template.samples[template.samples.len - 1];
        return .{
            .position = sample.position,
            .center_x = sample.center_x,
            .lateral_scale = sample.lateral_scale,
        };
    }

    const t = clamped_progress - @as(f32, @floatFromInt(base_index));
    const lhs = template.samples[base_index];
    const rhs = template.samples[base_index + 1];
    return .{
        .position = Vec3.lerp(lhs.position, rhs.position, t),
        .center_x = std.math.lerp(lhs.center_x, rhs.center_x, t),
        .lateral_scale = std.math.lerp(lhs.lateral_scale, rhs.lateral_scale, t),
    };
}

fn buildTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !?Template {
    return switch (spec.public_path) {
        .start => try buildStartTemplate(allocator, spec),
        .loopbow => try buildLoopbowTemplate(allocator, spec),
        else => null,
    };
}

fn buildStartTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !Template {
    const curve_steps: usize = @intFromFloat(@floor(4.0 * std.math.pi));
    const sample_count: usize = curve_steps + 15;
    const point_count: usize = sample_count + 1;
    var samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    for (0..5) |index| {
        samples[index].position = .{
            .x = 0.0,
            .y = 8.0,
            .z = @floatFromInt(index),
        };
    }

    const curve_steps_f: f32 = @floatFromInt(curve_steps);
    for (0..curve_steps) |step| {
        const angle = (@as(f32, @floatFromInt(step)) * std.math.pi) / curve_steps_f;
        const index = 5 + step;
        samples[index].position = .{
            .x = 0.0,
            .y = (std.math.cos(angle) + 1.0) * 4.0,
            .z = @floatFromInt(5 + step),
        };
    }

    for (0..11) |offset| {
        const index = curve_steps + 5 + offset;
        samples[index].position = .{
            .x = 0.0,
            .y = 0.0,
            .z = @floatFromInt(curve_steps + 5 + offset),
        };
    }

    finalizeTemplateSamples(samples);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .ported,
            .runtime_kind = spec.runtime_kind,
            .sample_count = spec.sample_count,
            .subdivision_count = spec.subdivision_count,
        },
        .width_cells = 8,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn buildLoopbowTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !Template {
    const loop_radius: f32 = 6.0;
    const subdivision_count: usize = 4;
    const curve_steps: usize = @intFromFloat(@floor(loop_radius * (2.0 * std.math.pi)));
    const sample_count: usize = curve_steps + 14;
    const point_count: usize = sample_count + 1;
    const bow_scalar: f32 = 0.5;
    const start_flat_count: usize = 7;
    const end_flat_count: usize = 7;
    var samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    for (0..start_flat_count) |index| {
        const row_offset = @as(f32, @floatFromInt(index));
        samples[index].position = .{
            .x = -2.0 - (row_offset * 0.071428575),
            .y = 0.0,
            .z = row_offset,
        };
    }

    const curve_steps_f: f32 = @floatFromInt(curve_steps);
    const radius = curve_steps_f * 0.15915494;
    const start_x = samples[0].position.x;
    const end_x = 4.0 - (@as(f32, @floatFromInt(subdivision_count)) * 0.5);
    for (0..curve_steps) |step| {
        const step_f: f32 = @floatFromInt(step);
        const t = step_f / curve_steps_f;
        const angle = (step_f * 2.0 * std.math.pi) / curve_steps_f;
        const index = start_flat_count + step;
        const linear_x = std.math.lerp(start_x, end_x, t);
        samples[index].position = .{
            .x = linear_x + (-std.math.cos(angle * 0.5) * bow_scalar),
            .y = radius * (1.0 - std.math.cos(angle)),
            .z = (std.math.sin(angle) * radius) + 7.0,
        };
    }

    for (0..end_flat_count) |offset| {
        const index = curve_steps + start_flat_count + offset;
        const row_offset = @as(f32, @floatFromInt(offset));
        samples[index].position = .{
            .x = (1.0 - (row_offset * 0.16666667)) * bow_scalar + end_x,
            .y = 0.0,
            .z = @as(f32, @floatFromInt(curve_steps + start_flat_count + offset)),
        };
    }

    samples[point_count - 1].position = .{
        .x = end_x,
        .y = 0.0,
        .z = @as(f32, @floatFromInt(sample_count)),
    };

    finalizeTemplateSamples(samples);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .runtime_kind = spec.runtime_kind,
            .sample_count = @intCast(sample_count),
            .subdivision_count = subdivision_count,
        },
        .width_cells = subdivision_count,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn finalizeTemplateSamples(samples: []TemplateSample) void {
    if (samples.len == 0) return;
    var last_forward = Vec3{ .x = 0.0, .y = 0.0, .z = 1.0 };
    const right = Vec3{ .x = 1.0, .y = 0.0, .z = 0.0 };

    for (samples, 0..) |*sample, index| {
        if (index + 1 < samples.len) {
            const delta = Vec3.sub(samples[index + 1].position, sample.position);
            const delta_length = Vec3.length(delta);
            const forward = if (delta_length > 0.0001) Vec3.scale(delta, 1.0 / delta_length) else last_forward;
            sample.delta_dir_to_next = forward;
            sample.delta_length = delta_length;
            sample.basis_forward = forward;
            last_forward = forward;
        } else {
            sample.delta_dir_to_next = last_forward;
            sample.delta_length = 0.0;
            sample.basis_forward = last_forward;
        }

        const up = Vec3.cross(sample.basis_forward, right);
        sample.basis_right = right;
        sample.basis_up = if (Vec3.length(up) > 0.0001) Vec3.normalize(up) else .{ .x = 0.0, .y = 1.0, .z = 0.0 };
        sample.center_x = 0.0;
        sample.lateral_scale = 1.0;
        sample.special_scalar = 0.0;
    }
}

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
        .loopbow => .{ .public_path = public_path, .family = .loopbow, .status = .partial, .runtime_kind = 0, .sample_count = 51, .subdivision_count = 4 },
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
        .start => .{ .public_path = public_path, .family = .start, .status = .ported, .runtime_kind = 36, .sample_count = 27, .subdivision_count = 8 },
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
    const rows = [_]segment.Row{
        .{ .cells = "..........", .annotation = .{ .path = "START" } },
        .{ .cells = "PPPPPPPPPP" },
        .{ .cells = "..........", .annotation = .{ .path = "HALFPIPE" } },
        .{ .cells = "pppppppppp" },
    };
    var segments = [_]segment.Definition{.{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "SEGMENTS/SCAFFOLD.TXT",
        .segment_id = 1,
        .name = "Scaffold",
        .width = 10,
        .height = rows.len,
        .rows = &rows,
    }};
    defer segments[0].deinit();
    const row_offsets = [_]usize{0};
    var scaffold = try Scaffold.collect(std.testing.allocator, &segments, &row_offsets);
    defer scaffold.deinit();

    try std.testing.expectEqual(@as(usize, 2), scaffold.authored_rows.len);
    try std.testing.expectEqual(PublicPath.start, scaffold.activePathAtRow(1).?.public_path.?);
    try std.testing.expectEqual(PublicPath.halfpipe, scaffold.activePathAtRow(3).?.public_path.?);
}

test "collect scaffold builds start template" {
    const rows = [_]segment.Row{
        .{ .cells = "..........", .annotation = .{ .path = "START" } },
        .{ .cells = "PPPPPPPPPP" },
    };
    var segments = [_]segment.Definition{.{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "SEGMENTS/START.TXT",
        .segment_id = 1,
        .name = "Start",
        .width = 10,
        .height = rows.len,
        .rows = &rows,
    }};
    defer segments[0].deinit();
    const row_offsets = [_]usize{0};
    var scaffold = try Scaffold.collect(std.testing.allocator, &segments, &row_offsets);
    defer scaffold.deinit();

    try std.testing.expectEqual(@as(usize, 1), scaffold.built_attachments.len);
    const built = scaffold.built_attachments[0];
    try std.testing.expectEqual(PublicPath.start, built.row.public_path.?);
    try std.testing.expectEqual(@as(u16, 27), built.template.sample_count);
    try std.testing.expectEqual(@as(usize, 28), built.template.pointCount());
    try std.testing.expectApproxEqAbs(@as(f32, 8.0), built.template.samples[0].position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), built.template.samples[17].position.y, 0.0001);
}

test "start template interpolation follows recovered descent" {
    const spec = specForPublicPath(.start);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    const mid = samplePoseAtProgress(&template, 10.5);
    try std.testing.expect(mid.position.y < 8.0);
    try std.testing.expect(mid.position.y > 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 10.5), mid.position.z, 0.0001);
}

test "build loopbow template from recovered ordinary family shape" {
    const spec = specForPublicPath(.loopbow);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    try std.testing.expectEqual(@as(u16, 51), template.sample_count);
    try std.testing.expectEqual(@as(u16, 4), template.width_cells);
    try std.testing.expectEqual(@as(usize, 52), template.pointCount());
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), template.samples[0].position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), template.samples[template.samples.len - 1].position.y, 0.0001);

    const mid = samplePoseAtProgress(&template, 25.5);
    try std.testing.expect(mid.position.y > 10.0);
    try std.testing.expect(mid.position.x > -3.0);
    try std.testing.expect(mid.position.x < 3.0);
}
