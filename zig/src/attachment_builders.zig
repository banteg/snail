const std = @import("std");
const native_matrix_math = @import("gameplay/native/matrix_math.zig");
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
    nonlinear_42,
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
            .nonlinear_42 => "nonlinear_42",
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
    template_kind: ?u8 = null,
    sample_count: ?u16 = null,
    subdivision_count: ?u16 = null,
};

pub const template_kind_worm: u8 = 24;
pub const template_kind_cage2_detour: u8 = 15;
pub const template_kind_supertramp: u8 = 31;
pub const template_kind_nonlinear_42: u8 = 42;
pub const template_kind_start: u8 = 36;
pub const template_kind_twister: u8 = 43;
pub const template_kind_twister2: u8 = 45;

// PORT(partial): this is the current Zig-side sampled template shape for the public
// attachment builder scaffold. It is informed by the recovered Windows sample records,
// but it is still not the exact installed runtime-bank layout.
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

// PORT(partial): the builder scaffold now populates these from the recovered public
// attachment families and uses them in the segment viewer and gameplay. The remaining
// gap is the exact Windows installed-bank/owner-record layout.
pub const Template = struct {
    spec: TemplateSpec,
    mirror_or_variant: bool = false,
    width_cells: u16 = 0,
    sample_count: u16 = 0,
    installed_heading_delta: f32 = 0.0,
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

fn mirrorVectorX(v: Vec3) Vec3 {
    return .{
        .x = -v.x,
        .y = v.y,
        .z = v.z,
    };
}

fn mirrorTemplateXInPlace(template: *Template) void {
    template.mirror_or_variant = !template.mirror_or_variant;
    // PORT(partial): Windows begin copies `installed_heading_delta` from the source row-cell
    // record, not the static template header. Live traces still show mirrored `WORM` rows
    // flipping that scalar's sign, so keep the built-template fallback aligned with the mirrored
    // source-row state until the runtime row-cell scalar is surfaced directly in preview data.
    template.installed_heading_delta = -template.installed_heading_delta;
    for (template.samples) |*sample| {
        sample.position = mirrorVectorX(sample.position);
        sample.delta_dir_to_next = mirrorVectorX(sample.delta_dir_to_next);
        sample.basis_right = mirrorVectorX(sample.basis_right);
        sample.basis_up = mirrorVectorX(sample.basis_up);
        sample.basis_forward = mirrorVectorX(sample.basis_forward);
    }
}

pub const AttachmentPose = struct {
    position: Vec3,
    center_x: f32,
    lateral_scale: f32,
    basis_right: Vec3,
    basis_up: Vec3,
    basis_forward: Vec3,
    special_scalar: f32,
};

pub const WorldPose = struct {
    position: Vec3,
    basis_right: Vec3,
    basis_up: Vec3,
    basis_forward: Vec3,
};

const VerticalLoopParams = struct {
    radius: f32,
    subdivision_count: u16,
    bow_scalar: f32,
    template_kind: u8,
};

const HillValleyParams = struct {
    width_cells: u16,
    height_scalar: f32,
    length: u16,
    centered: bool,
};

const HumpDumpParams = struct {
    template_kind: u8,
    width_cells: u16,
    path_length: f32,
    height_scalar: f32,
};

const LoopoutParams = struct {
    radius: f32,
    width_cells: u16,
};

const TurnoverParams = struct {
    template_kind: u8,
    radius: f32,
    width_cells: u16,
    turn_count: f32,
    start_sign: f32,
};

const WaveParams = struct {
    template_kind: ?u8 = null,
    width_cells: u16,
    sample_count: u16,
    subdivision_count: ?u16 = null,
    lateral_amplitude: f32 = 0.0,
    lateral_cycles: f32 = 0.0,
    vertical_amplitude: f32 = 0.0,
    vertical_cycles: f32 = 0.0,
    roll_cycles: f32 = 0.0,
    installed_heading_delta: f32 = 0.0,
    start_z: f32 = 0.0,
    center_bias: f32 = 0.0,
    // native template width_or_scale (+0x50): 1.0 in every constructor
    // except WORM's 4.0; the exhaust placement adds it past the terminal
    // sample (pinned update_track_attachment_follow_state)
    exit_tail_extra: f32 = 1.0,
};

const PFamilyParams = struct {
    template_kind: u8,
    center_curve_scalar: f32,
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

pub const InstalledAttachmentIndexSlots = struct {
    primary: ?usize = null,
    secondary: ?usize = null,

    pub fn append(self: *InstalledAttachmentIndexSlots, built_index: usize) void {
        if (self.primary == built_index or self.secondary == built_index) return;
        if (self.primary == null) {
            self.primary = built_index;
            return;
        }
        if (self.secondary == null) {
            self.secondary = built_index;
        }
    }
};

pub const InstalledBuiltAttachmentSlots = struct {
    primary: ?*const BuiltAttachment = null,
    secondary: ?*const BuiltAttachment = null,

    pub fn any(self: InstalledBuiltAttachmentSlots) bool {
        return self.primary != null or self.secondary != null;
    }
};

pub const Scaffold = struct {
    allocator: std.mem.Allocator,
    authored_rows: []AuthoredPathRow,
    built_attachments: []BuiltAttachment,
    installed_attachment_rows: []InstalledAttachmentIndexSlots,

    pub fn collect(
        allocator: std.mem.Allocator,
        segments: []const segment.Definition,
        row_offsets: []const usize,
        runtime_tiles: []const u8,
        total_rows: usize,
        max_width: usize,
        source_row_mirror_states: []const bool,
    ) !Scaffold {
        _ = runtime_tiles;
        _ = max_width;

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
            var template = (try buildTemplate(allocator, spec)) orelse continue;
            if (row.global_row < source_row_mirror_states.len and source_row_mirror_states[row.global_row]) {
                mirrorTemplateXInPlace(&template);
            }
            try built_attachments.append(allocator, .{
                .row = row,
                .template = template,
            });
        }

        const installed_attachment_rows = try allocator.alloc(InstalledAttachmentIndexSlots, total_rows);
        errdefer allocator.free(installed_attachment_rows);
        for (installed_attachment_rows) |*slot_row| {
            slot_row.* = .{};
        }

        for (built_attachments.items, 0..) |built, index| {
            const attachment_end = @min(total_rows, built.row.global_row + built.template.sample_count + 1);
            var global_row = built.row.global_row;
            while (global_row < attachment_end) : (global_row += 1) {
                // Windows row records expose two installed-owner slots at +0xa4/+0xa8.
                installed_attachment_rows[global_row].append(index);
            }
        }

        return .{
            .allocator = allocator,
            .authored_rows = try rows.toOwnedSlice(allocator),
            .built_attachments = try built_attachments.toOwnedSlice(allocator),
            .installed_attachment_rows = installed_attachment_rows,
        };
    }

    pub fn deinit(self: *Scaffold) void {
        for (self.built_attachments) |*built| {
            built.deinit(self.allocator);
        }
        self.allocator.free(self.installed_attachment_rows);
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

    fn resolveInstalledBuiltAttachment(self: *const Scaffold, built_index: ?usize) ?*const BuiltAttachment {
        const index = built_index orelse return null;
        return &self.built_attachments[index];
    }

    pub fn installedBuiltAttachmentsAtRow(self: *const Scaffold, global_row: usize) InstalledBuiltAttachmentSlots {
        if (global_row >= self.installed_attachment_rows.len) return .{};
        const row_slots = self.installed_attachment_rows[global_row];
        return .{
            .primary = self.resolveInstalledBuiltAttachment(row_slots.primary),
            .secondary = self.resolveInstalledBuiltAttachment(row_slots.secondary),
        };
    }

    pub fn installedBuiltAttachmentAtRow(self: *const Scaffold, global_row: usize) ?*const BuiltAttachment {
        if (global_row >= self.installed_attachment_rows.len) return null;
        return self.installedBuiltAttachmentsAtRow(global_row).primary;
    }
};

pub fn samplePoseAtProgress(template: *const Template, progress: f32) AttachmentPose {
    if (template.samples.len == 0) {
        return .{
            .position = .{},
            .center_x = 0.0,
            .lateral_scale = 1.0,
            .basis_right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
            .basis_up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .basis_forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
            .special_scalar = 0.0,
        };
    }

    const clamped_progress = std.math.clamp(progress, 0.0, @as(f32, @floatFromInt(template.sample_count)));
    const base_index: usize = @intFromFloat(@floor(clamped_progress));
    const terminal_index = @min(
        @as(usize, @max(template.sample_count, 1)) - 1,
        template.samples.len - 1,
    );
    if (base_index >= terminal_index) {
        // PORT(verified): the native output path (pinned
        // update_track_attachment_follow_state, terminal-segment branch)
        // EXTENDS the position along delta_dir_to_next by the raw local
        // progress past the terminal sample. The old clamp-at-terminal
        // model parked riders at the last sample and the natural-exit
        // commit then teleported them past the tail — the lockstep oracle
        // showed a +1.7 z jump per exit while the recorded native
        // trajectory never steps more than 0.41 in one tick.
        // SEAM: native's follow OUTPUT rotation is identity across the
        // terminal segment (set_matrix_identity at segment == count-1);
        // geometry consumers (renderers, the supertramp launch basis) read
        // the sample transform, so the basis stays geometric here and the
        // identity lane belongs to the cluster-1 output routing.
        const sample = template.samples[terminal_index];
        const local_distance =
            (clamped_progress - @as(f32, @floatFromInt(terminal_index))) * sample.delta_length;
        return .{
            .position = .{
                .x = sample.position.x + sample.delta_dir_to_next.x * local_distance,
                .y = sample.position.y + sample.delta_dir_to_next.y * local_distance,
                .z = sample.position.z + sample.delta_dir_to_next.z * local_distance,
            },
            .center_x = sample.center_x,
            .lateral_scale = sample.lateral_scale,
            .basis_right = sample.basis_right,
            .basis_up = sample.basis_up,
            .basis_forward = sample.basis_forward,
            .special_scalar = sample.special_scalar,
        };
    }

    const t = clamped_progress - @as(f32, @floatFromInt(base_index));
    const lhs = template.samples[base_index];
    const rhs = template.samples[base_index + 1];
    // PORT(verified): native sample-pose interpolation is rotation-space
    // (linear_interpolate_matrix @ 0x44da90, pinned) with position rows
    // zeroed before the matrix lerp — see gameplay/native/matrix_math.zig
    // and the 2026-06-12 invalidation-ledger entry replacing the old
    // per-basis-vector lerp+normalize model.
    const interpolated = native_matrix_math.linearInterpolateMatrix(
        sampleBasisMat(lhs),
        sampleBasisMat(rhs),
        t,
    );
    return .{
        .position = Vec3.lerp(lhs.position, rhs.position, t),
        .center_x = std.math.lerp(lhs.center_x, rhs.center_x, t),
        .lateral_scale = std.math.lerp(lhs.lateral_scale, rhs.lateral_scale, t),
        .basis_right = fromMathVec(interpolated.right),
        .basis_up = fromMathVec(interpolated.up),
        .basis_forward = fromMathVec(interpolated.forward),
        .special_scalar = std.math.lerp(lhs.special_scalar, rhs.special_scalar, t),
    };
}

fn sampleBasisMat(sample: TemplateSample) native_matrix_math.Mat {
    // native zeroes the position rows before the rotation lerp; positions
    // blend separately (memset(&copy.position, 0, 12) in the boss scratch)
    return .{
        .right = .{ .x = sample.basis_right.x, .y = sample.basis_right.y, .z = sample.basis_right.z },
        .up = .{ .x = sample.basis_up.x, .y = sample.basis_up.y, .z = sample.basis_up.z },
        .forward = .{ .x = sample.basis_forward.x, .y = sample.basis_forward.y, .z = sample.basis_forward.z },
        .position = .{},
    };
}

fn fromMathVec(v: native_matrix_math.Vec3) Vec3 {
    return .{ .x = v.x, .y = v.y, .z = v.z };
}

pub fn worldPositionForTemplate(
    template: *const Template,
    progress: f32,
    source_cell_row: usize,
    lateral_offset: f32,
    vertical_offset: f32,
) Vec3 {
    return worldPoseForTemplate(template, progress, source_cell_row, lateral_offset, vertical_offset).position;
}

pub fn worldPoseForTemplate(
    template: *const Template,
    progress: f32,
    source_cell_row: usize,
    lateral_offset: f32,
    vertical_offset: f32,
) WorldPose {
    const pose = samplePoseAtProgress(template, progress);
    const local_lateral = lateral_offset * pose.lateral_scale;
    const base_row: f32 = @floatFromInt(source_cell_row);
    if (template.spec.family == .nonlinear_42) {
        const local_transform = nonlinear42LocalTransform(pose.special_scalar, local_lateral, nonlinear_42_rider_height + vertical_offset);
        return .{
            .position = .{
                .x = pose.position.x + (pose.basis_right.x * (pose.center_x + local_transform.position.x)) + (pose.basis_up.x * local_transform.position.y),
                .y = pose.position.y + (pose.basis_right.y * (pose.center_x + local_transform.position.x)) + (pose.basis_up.y * local_transform.position.y),
                .z = base_row + pose.position.z + (pose.basis_right.z * (pose.center_x + local_transform.position.x)) + (pose.basis_up.z * local_transform.position.y),
            },
            .basis_right = Vec3.normalize(Vec3.add(
                Vec3.scale(pose.basis_right, local_transform.right.x),
                Vec3.scale(pose.basis_up, local_transform.right.y),
            )),
            .basis_up = Vec3.normalize(Vec3.add(
                Vec3.scale(pose.basis_right, local_transform.up.x),
                Vec3.scale(pose.basis_up, local_transform.up.y),
            )),
            .basis_forward = pose.basis_forward,
        };
    }

    const centered_lateral = pose.center_x + local_lateral;

    return .{
        .position = .{
            .x = pose.position.x + (pose.basis_right.x * centered_lateral) + (pose.basis_up.x * vertical_offset),
            .y = pose.position.y + (pose.basis_right.y * centered_lateral) + (pose.basis_up.y * vertical_offset),
            .z = base_row + pose.position.z + (pose.basis_right.z * centered_lateral) + (pose.basis_up.z * vertical_offset),
        },
        .basis_right = pose.basis_right,
        .basis_up = pose.basis_up,
        .basis_forward = pose.basis_forward,
    };
}

pub fn deltaLengthAtProgress(template: *const Template, progress: f32) f32 {
    if (template.samples.len == 0) return 1.0;
    const clamped_progress = std.math.clamp(progress, 0.0, @as(f32, @floatFromInt(template.sample_count)));
    const base_index: usize = @intFromFloat(@floor(clamped_progress));
    const sample_index = @min(base_index, template.samples.len - 1);
    return @max(template.samples[sample_index].delta_length, 1.0);
}

const SurfaceBasis = struct {
    right: Vec3,
    up: Vec3,
    forward: Vec3,
};

pub const nonlinear_42_rider_height: f32 = 0.49;

const Nonlinear42LocalTransform = struct {
    position: Vec3,
    right: Vec3,
    up: Vec3,
};

fn nonlinear42LocalTransform(radius: f32, lateral_offset: f32, rider_height: f32) Nonlinear42LocalTransform {
    if (radius <= 4.0001) {
        const angle = std.math.clamp(lateral_offset * (std.math.pi * 0.125), -std.math.pi * 0.5, std.math.pi * 0.5);
        return nonlinear42LocalTransformForAngle(radius, angle, rider_height);
    }

    const chord = std.math.sqrt(@max(0.0, (radius * radius) - 16.0));
    const lateral_angle = std.math.atan2(4.0, chord) * lateral_offset * 0.25;
    return nonlinear42LocalTransformForAngle(radius, lateral_angle, rider_height);
}

fn nonlinear42LocalTransformForAngle(radius: f32, lateral_angle: f32, rider_height: f32) Nonlinear42LocalTransform {
    const travel_radius = @max(0.0, radius - rider_height);
    const sin_angle = std.math.sin(lateral_angle);
    const cos_angle = std.math.cos(lateral_angle);
    return .{
        .position = .{
            .x = sin_angle * travel_radius,
            .y = radius - (cos_angle * travel_radius),
            .z = 0.0,
        },
        .right = Vec3.normalize(.{
            .x = cos_angle,
            .y = sin_angle,
            .z = 0.0,
        }),
        .up = Vec3.normalize(.{
            .x = -sin_angle,
            .y = cos_angle,
            .z = 0.0,
        }),
    };
}

fn buildTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !?Template {
    return switch (spec.public_path) {
        .start => try buildStartTemplate(allocator, spec),
        .looptheloop,
        .looptheloop2,
        .looptheloop4,
        .looptheloopt2,
        .looptheloopt3,
        .looptheloopt4,
        .looptheloopw,
        => try buildVerticalLoopTemplate(allocator, spec, verticalLoopParams(spec.public_path)),
        .loopbow => try buildLoopbowTemplate(allocator, spec),
        .hill,
        .hill4c,
        .hill4,
        .valley,
        .valley4c,
        .valley4,
        => try buildHillValleyTemplate(allocator, spec, hillValleyParams(spec.public_path)),
        .hump,
        .humpsmall,
        .dump,
        .dumpsmall,
        => try buildHumpDumpTemplate(allocator, spec, humpDumpParams(spec.public_path)),
        .loopout,
        .loopout3,
        .loopoutbig,
        => try buildLoopoutTemplate(allocator, spec, loopoutParams(spec.public_path)),
        .turnover,
        .turnoverdouble,
        .turnunder,
        => try buildTurnoverTemplate(allocator, spec, turnoverParams(spec.public_path)),
        .supertramp => try buildSupertrampTemplate(allocator, spec),
        .p0, .p1, .p2 => try buildPFamilyTemplate(allocator, spec, pFamilyParams(spec.public_path)),
        .sbend => try buildWaveTemplate(allocator, spec, .{ .template_kind = 14, .width_cells = 8, .sample_count = 28, .lateral_amplitude = 2.5, .lateral_cycles = 1.0 }),
        .cage2 => try buildWaveTemplate(allocator, spec, .{ .template_kind = 15, .width_cells = 3, .sample_count = 24, .vertical_amplitude = 2.5, .vertical_cycles = 1.0, .roll_cycles = 0.5 }),
        .dip => try buildWaveTemplate(allocator, spec, .{ .template_kind = 20, .width_cells = 2, .sample_count = 22, .vertical_amplitude = -3.0, .vertical_cycles = 1.0 }),
        .screw => try buildWaveTemplate(allocator, spec, .{ .template_kind = 21, .width_cells = 3, .sample_count = 24, .roll_cycles = 1.0 }),
        .slalom => try buildWaveTemplate(allocator, spec, .{ .template_kind = 22, .width_cells = 4, .sample_count = 32, .lateral_amplitude = 2.5, .lateral_cycles = 2.0 }),
        .slalombig => try buildWaveTemplate(allocator, spec, .{ .template_kind = 23, .width_cells = 4, .sample_count = 32, .lateral_amplitude = 3.5, .lateral_cycles = 2.0 }),
        .worm => try buildWaveTemplate(allocator, spec, .{
            .template_kind = template_kind_worm,
            .width_cells = 4,
            .sample_count = 24,
            .subdivision_count = 16,
            .lateral_amplitude = 1.75,
            .lateral_cycles = 2.0,
            .vertical_amplitude = 1.75,
            .vertical_cycles = 2.0,
            .installed_heading_delta = 6.2831855,
            // native initialize_worm_path_template_pair: width_or_scale = 4.0
            .exit_tail_extra = 4.0,
        }),
        .sweep => try buildWaveTemplate(allocator, spec, .{ .template_kind = 28, .width_cells = 4, .sample_count = 30, .lateral_amplitude = 3.0, .lateral_cycles = 0.5 }),
        .snake => try buildWaveTemplate(allocator, spec, .{ .template_kind = 29, .width_cells = 4, .sample_count = 27, .lateral_amplitude = 2.25, .lateral_cycles = 1.5 }),
        .warp, .halfpipe => try buildNonlinear42Template(allocator, spec),
        .slalomdouble => try buildWaveTemplate(allocator, spec, .{ .template_kind = 32, .width_cells = 4, .sample_count = 70, .lateral_amplitude = 2.5, .lateral_cycles = 4.0 }),
        .wibble => try buildWaveTemplate(allocator, spec, .{ .template_kind = 40, .width_cells = 8, .sample_count = 32, .lateral_amplitude = 1.5, .lateral_cycles = 3.0, .vertical_amplitude = 0.75, .vertical_cycles = 2.0 }),
        .invert => try buildWaveTemplate(allocator, spec, .{ .template_kind = 41, .width_cells = 8, .sample_count = 34, .roll_cycles = 0.5 }),
        .twistera, .twisterb => try buildWaveTemplate(allocator, spec, .{ .template_kind = template_kind_twister, .width_cells = 3, .sample_count = 48, .roll_cycles = 1.5, .lateral_amplitude = 0.5 }),
        .twister2a, .twister2b => try buildWaveTemplate(allocator, spec, .{ .template_kind = template_kind_twister2, .width_cells = 3, .sample_count = 52, .roll_cycles = 2.0, .lateral_amplitude = 0.75 }),
        .toad0, .toad1, .toadpair0, .toadpair1 => try buildWaveTemplate(allocator, spec, .{ .template_kind = 47, .width_cells = 3, .sample_count = 24, .vertical_amplitude = 1.5, .vertical_cycles = if (spec.public_path == .toadpair0 or spec.public_path == .toadpair1) 2.0 else 1.0 }),
    };
}

fn buildStartTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !Template {
    const curve_steps: usize = @intFromFloat(@floor(4.0 * std.math.pi));
    const curve_radius = @as(f32, @floatFromInt(curve_steps)) / std.math.pi;
    const top_flat_height = curve_radius * 2.0;
    const sample_count: usize = curve_steps + 15;
    const point_count: usize = sample_count + 1;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    for (0..5) |index| {
        samples[index].position = .{
            .x = 0.0,
            .y = top_flat_height,
            .z = @floatFromInt(index),
        };
    }

    const curve_steps_f: f32 = @floatFromInt(curve_steps);
    for (0..curve_steps) |step| {
        const angle = (@as(f32, @floatFromInt(step)) * std.math.pi) / curve_steps_f;
        const index = 5 + step;
        samples[index].position = .{
            .x = 0.0,
            .y = (std.math.cos(angle) + 1.0) * curve_radius,
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
            .template_kind = spec.template_kind,
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
    return buildVerticalLoopTemplate(allocator, spec, .{
        .radius = 6.0,
        .subdivision_count = 4,
        .bow_scalar = 0.5,
        .template_kind = 0,
    });
}

fn buildVerticalLoopTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: VerticalLoopParams,
) !Template {
    const curve_steps: usize = @intFromFloat(@floor(params.radius * (2.0 * std.math.pi)));
    const sample_count: usize = curve_steps + 14;
    const point_count: usize = sample_count + 1;
    const start_flat_count: usize = 7;
    const end_flat_count: usize = 7;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    for (0..start_flat_count) |index| {
        const row_offset = @as(f32, @floatFromInt(index));
        samples[index].position = .{
            .x = (@as(f32, @floatFromInt(params.subdivision_count)) * 0.5) - 4.0 - (row_offset * 0.14285715 * params.bow_scalar),
            .y = 0.0,
            .z = row_offset,
        };
    }

    const curve_steps_f: f32 = @floatFromInt(curve_steps);
    const radius = curve_steps_f * 0.15915494;
    const start_x = samples[0].position.x;
    const end_x = 4.0 - (@as(f32, @floatFromInt(params.subdivision_count)) * 0.5);
    for (0..curve_steps) |step| {
        const step_f: f32 = @floatFromInt(step);
        const t = step_f / curve_steps_f;
        const angle = (step_f * 2.0 * std.math.pi) / curve_steps_f;
        const index = start_flat_count + step;
        const linear_x = std.math.lerp(start_x, end_x, t);
        samples[index].position = .{
            .x = linear_x + (-std.math.cos(angle * 0.5) * params.bow_scalar),
            .y = radius * (1.0 - std.math.cos(angle)),
            .z = (std.math.sin(angle) * radius) + 7.0,
        };
    }

    for (0..end_flat_count) |offset| {
        const index = curve_steps + start_flat_count + offset;
        const row_offset = @as(f32, @floatFromInt(offset));
        samples[index].position = .{
            .x = (1.0 - (row_offset * 0.16666667)) * params.bow_scalar + end_x,
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
            .template_kind = params.template_kind,
            .sample_count = @intCast(sample_count),
            .subdivision_count = params.subdivision_count,
        },
        .width_cells = params.subdivision_count,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn verticalLoopParams(public_path: PublicPath) VerticalLoopParams {
    return switch (public_path) {
        .looptheloop => .{ .radius = 6.0, .subdivision_count = 3, .bow_scalar = 0.0, .template_kind = 0 },
        .looptheloop2 => .{ .radius = 6.0, .subdivision_count = 2, .bow_scalar = 0.0, .template_kind = 0 },
        .looptheloop4 => .{ .radius = 8.0, .subdivision_count = 4, .bow_scalar = 0.3, .template_kind = 0 },
        .looptheloopt2 => .{ .radius = 3.0, .subdivision_count = 2, .bow_scalar = 0.0, .template_kind = 0 },
        .looptheloopt3 => .{ .radius = 3.0, .subdivision_count = 3, .bow_scalar = 0.0, .template_kind = 0 },
        .looptheloopt4 => .{ .radius = 3.0, .subdivision_count = 4, .bow_scalar = 0.3, .template_kind = 0 },
        .looptheloopw => .{ .radius = 8.0, .subdivision_count = 4, .bow_scalar = 0.3, .template_kind = 6 },
        else => unreachable,
    };
}

fn buildHillValleyTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: HillValleyParams,
) !Template {
    const sample_count: usize = params.length + 2;
    const point_count: usize = sample_count + 1;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    const center_x = if (params.centered) 0.0 else (@as(f32, @floatFromInt(params.width_cells)) * 0.5) - 4.0;
    samples[0].center_x = center_x;
    samples[0].position = .{ .x = 0.0, .y = 0.0, .z = 0.0 };

    const length_f: f32 = @floatFromInt(params.length);
    for (0..params.length) |step| {
        const progress = @as(f32, @floatFromInt(step)) / length_f;
        const angle = progress * (2.0 * std.math.pi);
        const sample = &samples[step + 1];
        sample.center_x = center_x;
        sample.position = .{
            .x = 0.0,
            .y = (1.0 - std.math.cos(angle)) * 0.5 * params.height_scalar,
            .z = @floatFromInt(step + 1),
        };
    }

    samples[params.length + 1].center_x = center_x;
    samples[params.length + 1].position = .{
        .x = 0.0,
        .y = 0.0,
        .z = @floatFromInt(params.length + 1),
    };
    samples[point_count - 1] = samples[params.length + 1];

    finalizeTemplateSamples(samples[0 .. params.length + 2]);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = 16,
            .sample_count = @intCast(sample_count),
            .subdivision_count = params.width_cells,
        },
        .width_cells = params.width_cells,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn hillValleyParams(public_path: PublicPath) HillValleyParams {
    return switch (public_path) {
        .hill => .{ .width_cells = 8, .height_scalar = 4.0, .length = 20, .centered = true },
        .hill4c => .{ .width_cells = 4, .height_scalar = 4.0, .length = 20, .centered = false },
        .hill4 => .{ .width_cells = 4, .height_scalar = 4.0, .length = 20, .centered = true },
        .valley => .{ .width_cells = 8, .height_scalar = -4.0, .length = 20, .centered = true },
        .valley4c => .{ .width_cells = 4, .height_scalar = -4.0, .length = 20, .centered = false },
        .valley4 => .{ .width_cells = 4, .height_scalar = -4.0, .length = 20, .centered = true },
        else => unreachable,
    };
}

fn buildHumpDumpTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: HumpDumpParams,
) !Template {
    const dynamic_count: usize = @intFromFloat(@floor(params.path_length * 4.0));
    const sample_count: usize = dynamic_count + 14;
    const point_count: usize = sample_count + 1;
    const start_flat_count: usize = 7;
    const end_flat_count: usize = 7;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    const edge_center = (@as(f32, @floatFromInt(params.width_cells)) * 0.5) - 4.0;
    const start_center = if (params.template_kind == 16) edge_center else -edge_center;
    const end_center = -start_center;
    const height_sign: f32 = if (params.template_kind == 16) 1.0 else -1.0;
    const curve_height_scale = @as(f32, @floatFromInt(dynamic_count)) * 0.095492966 * params.height_scalar;

    for (0..start_flat_count) |index| {
        const z: f32 = @floatFromInt(index);
        const sample = &samples[index];
        sample.center_x = start_center;
        sample.position = .{ .x = 0.0, .y = 0.0, .z = z };
    }

    const dynamic_count_f: f32 = @floatFromInt(dynamic_count);
    for (0..dynamic_count) |step| {
        const theta = (@as(f32, @floatFromInt(step)) * 2.0 * std.math.pi) / dynamic_count_f;
        const sample = &samples[start_flat_count + step];
        sample.center_x = std.math.cos(theta * 0.5) * start_center;
        sample.position = .{
            .x = 0.0,
            .y = (1.0 - std.math.cos(theta)) * curve_height_scale * height_sign,
            .z = @floatFromInt(step + start_flat_count),
        };
    }

    for (0..end_flat_count) |offset| {
        const index = dynamic_count + start_flat_count + offset;
        const z: f32 = @floatFromInt(index);
        const sample = &samples[index];
        sample.center_x = end_center;
        sample.position = .{ .x = 0.0, .y = 0.0, .z = z };
    }

    samples[point_count - 1].center_x = end_center;
    samples[point_count - 1].position = .{
        .x = 0.0,
        .y = 0.0,
        .z = @floatFromInt(sample_count),
    };

    finalizeTemplateSamples(samples);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = params.template_kind,
            .sample_count = @intCast(sample_count),
            .subdivision_count = params.width_cells,
        },
        .width_cells = params.width_cells,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn humpDumpParams(public_path: PublicPath) HumpDumpParams {
    return switch (public_path) {
        .hump => .{ .template_kind = 16, .width_cells = 3, .path_length = 4.0, .height_scalar = 1.0 },
        .humpsmall => .{ .template_kind = 16, .width_cells = 3, .path_length = 4.0, .height_scalar = 0.30000001 },
        .dump => .{ .template_kind = 17, .width_cells = 3, .path_length = 4.0, .height_scalar = 1.0 },
        .dumpsmall => .{ .template_kind = 17, .width_cells = 3, .path_length = 4.0, .height_scalar = 0.30000001 },
        else => unreachable,
    };
}

fn buildLoopoutTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: LoopoutParams,
) !Template {
    const dynamic_count: usize = @intFromFloat(@floor(params.radius * (2.0 * std.math.pi)));
    const sample_count: usize = dynamic_count + 14;
    const point_count: usize = sample_count + 1;
    const start_flat_count: usize = 10;
    const end_flat_count: usize = 4;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    const start_x_base = (@as(f32, @floatFromInt(params.width_cells)) * 0.5) - 4.0;
    const end_x_base = 4.0 - (@as(f32, @floatFromInt(params.width_cells)) * 0.5);
    const backface_radius = params.radius + 0.49000001;

    for (0..start_flat_count) |index| {
        const row_offset: f32 = @floatFromInt(index);
        const sample = &samples[index];
        sample.center_x = start_x_base - (row_offset * 0.11111111 * 0.30000001);
        sample.position = .{
            .x = 0.0,
            .y = 0.0,
            .z = row_offset,
        };
    }

    const dynamic_count_f: f32 = @floatFromInt(dynamic_count);
    const start_x = samples[0].center_x;
    const end_x = (1.0 * 0.30000001) + end_x_base;
    for (0..dynamic_count) |step| {
        const step_f: f32 = @floatFromInt(step);
        const theta = (step_f * 2.0 * std.math.pi) / dynamic_count_f;
        const sample = &samples[start_flat_count + step];
        const linear_x = std.math.lerp(start_x, end_x, step_f / dynamic_count_f);
        sample.center_x = linear_x + std.math.sin((theta * 0.5) + 4.712389) * 0.30000001;
        sample.position = .{
            .x = 0.0,
            .y = (std.math.cos(theta) * params.radius) - params.radius,
            .z = (std.math.sin(theta) * params.radius) + 10.0,
        };
        sample.special_scalar = backface_radius;
    }

    for (0..end_flat_count) |offset| {
        const index = dynamic_count + start_flat_count + offset;
        const row_offset: f32 = @floatFromInt(offset);
        const sample = &samples[index];
        sample.center_x = ((1.0 - (row_offset * 0.33333334)) * 0.30000001) + end_x_base;
        sample.position = .{
            .x = 0.0,
            .y = 0.0,
            .z = @floatFromInt(offset + 10),
        };
    }

    samples[point_count - 1] = samples[dynamic_count + start_flat_count + end_flat_count - 1];
    finalizeTemplateSamples(samples);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = 25,
            .sample_count = @intCast(sample_count),
            .subdivision_count = params.width_cells,
        },
        .width_cells = params.width_cells,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn loopoutParams(public_path: PublicPath) LoopoutParams {
    return switch (public_path) {
        .loopout => .{ .radius = 3.0, .width_cells = 4 },
        .loopout3 => .{ .radius = 3.0, .width_cells = 3 },
        .loopoutbig => .{ .radius = 5.0, .width_cells = 4 },
        else => unreachable,
    };
}

fn buildTurnoverTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: TurnoverParams,
) !Template {
    const dynamic_count: usize = @intFromFloat(@floor(params.radius * (params.turn_count * std.math.pi)));
    const sample_count: usize = dynamic_count + 8;
    const point_count: usize = sample_count + 1;
    const start_flat_count: usize = 6;
    const end_flat_count: usize = 2;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    const edge_center = (@as(f32, @floatFromInt(params.width_cells)) * 0.5) - 4.0;
    const start_center = edge_center * params.start_sign;
    const end_center = -start_center;

    for (0..start_flat_count) |index| {
        const sample = &samples[index];
        sample.center_x = start_center;
        sample.position = .{
            .x = 0.0,
            .y = 0.0,
            .z = @floatFromInt(index),
        };
    }

    const dynamic_count_f: f32 = @floatFromInt(dynamic_count);
    for (0..dynamic_count) |step| {
        const step_f: f32 = @floatFromInt(step);
        const theta = (step_f * params.turn_count * std.math.pi) / dynamic_count_f;
        const sample = &samples[start_flat_count + step];
        sample.center_x = std.math.lerp(start_center, end_center, step_f / dynamic_count_f);
        sample.position = .{
            .x = 0.0,
            .y = (params.radius - (std.math.cos(theta) * params.radius)) * 0.4,
            .z = @floatFromInt(step + start_flat_count),
        };
    }

    for (0..end_flat_count) |offset| {
        const index = dynamic_count + start_flat_count + offset;
        const sample = &samples[index];
        sample.center_x = end_center;
        sample.position = .{
            .x = 0.0,
            .y = 0.0,
            .z = @floatFromInt(index),
        };
    }

    samples[point_count - 1].center_x = end_center;
    samples[point_count - 1].position = .{
        .x = 0.0,
        .y = 0.0,
        .z = @floatFromInt(sample_count),
    };

    finalizeTemplateSamples(samples);
    applyRoll(samples, turnoverRollCycles(params), 0.0);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = params.template_kind,
            .sample_count = @intCast(sample_count),
            .subdivision_count = params.width_cells,
        },
        .width_cells = params.width_cells,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn turnoverParams(public_path: PublicPath) TurnoverParams {
    return switch (public_path) {
        .turnover => .{ .template_kind = 37, .radius = 6.0, .width_cells = 4, .turn_count = 2.0, .start_sign = 1.0 },
        .turnoverdouble => .{ .template_kind = 38, .radius = 6.0, .width_cells = 4, .turn_count = 3.0, .start_sign = 1.0 },
        .turnunder => .{ .template_kind = 39, .radius = 6.0, .width_cells = 4, .turn_count = 2.0, .start_sign = -1.0 },
        else => unreachable,
    };
}

fn turnoverRollCycles(params: TurnoverParams) f32 {
    return switch (params.template_kind) {
        37 => 0.5,
        38 => 1.0,
        39 => -0.5,
        else => 0.0,
    };
}

fn buildWaveTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: WaveParams,
) !Template {
    const point_count: usize = params.sample_count + 1;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    const sample_count_f: f32 = @floatFromInt(params.sample_count);
    for (samples, 0..) |*sample, index| {
        const t = if (params.sample_count == 0) 0.0 else @as(f32, @floatFromInt(index)) / sample_count_f;
        const z = @as(f32, @floatFromInt(index)) + params.start_z;
        const lateral_angle = t * params.lateral_cycles * (2.0 * std.math.pi);
        const vertical_angle = t * params.vertical_cycles * (2.0 * std.math.pi);
        sample.* = .{
            .center_x = params.center_bias + (std.math.sin(lateral_angle) * params.lateral_amplitude),
            .position = .{
                .x = 0.0,
                .y = std.math.sin(vertical_angle) * params.vertical_amplitude,
                .z = z,
            },
        };
    }

    finalizeTemplateSamples(samples);
    if (params.roll_cycles != 0.0) {
        applyRoll(samples, params.roll_cycles, 0.0);
    }

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = params.template_kind,
            .sample_count = params.sample_count,
            .subdivision_count = params.subdivision_count orelse params.width_cells,
        },
        .width_cells = params.width_cells,
        .sample_count = params.sample_count,
        .installed_heading_delta = params.installed_heading_delta,
        .exit_tail_extra = params.exit_tail_extra,
        .samples = samples,
    };
}

fn buildPFamilyTemplate(
    allocator: std.mem.Allocator,
    spec: TemplateSpec,
    params: PFamilyParams,
) !Template {
    const sample_count: usize = 16;
    const point_count: usize = sample_count + 1;
    const width_cells: u16 = 3;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples, 0..) |*sample, index| {
        const t = @as(f32, @floatFromInt(index)) / @as(f32, @floatFromInt(sample_count));
        const theta = t * std.math.pi;
        sample.* = .{
            .center_x = std.math.sin(theta) * params.center_curve_scalar,
            .position = .{
                .x = 0.0,
                .y = std.math.sin(theta) * 1.5,
                .z = @floatFromInt(index),
            },
        };
    }

    finalizeTemplateSamples(samples);
    applyRoll(samples, 0.25, 0.0);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = params.template_kind,
            .sample_count = 16,
            .subdivision_count = width_cells,
        },
        .width_cells = width_cells,
        .sample_count = 16,
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn pFamilyParams(public_path: PublicPath) PFamilyParams {
    return switch (public_path) {
        .p0 => .{ .template_kind = 33, .center_curve_scalar = 0.75 },
        .p1 => .{ .template_kind = 34, .center_curve_scalar = 1.25 },
        .p2 => .{ .template_kind = 35, .center_curve_scalar = 1.75 },
        else => unreachable,
    };
}

fn buildSupertrampTemplate(allocator: std.mem.Allocator, spec: TemplateSpec) !Template {
    const width_cells: u16 = 2;
    const sample_count: usize = 32;
    const point_count: usize = sample_count + 1;
    const start_flat_count: usize = 7;
    const dynamic_count: usize = sample_count - start_flat_count;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples) |*sample| {
        sample.* = .{};
    }

    for (0..start_flat_count) |index| {
        samples[index].position = .{
            .x = 0.0,
            .y = 0.0,
            .z = @floatFromInt(index),
        };
    }

    const dynamic_count_f: f32 = @floatFromInt(dynamic_count);
    for (0..dynamic_count + 1) |step| {
        const t = @as(f32, @floatFromInt(step)) / dynamic_count_f;
        const theta = t * (0.5 * std.math.pi);
        const index = start_flat_count + step;
        if (index >= samples.len) break;
        samples[index].position = .{
            .x = 0.0,
            .y = (1.0 - std.math.cos(theta)) * 8.0,
            .z = @as(f32, @floatFromInt(start_flat_count)) + (std.math.sin(theta) * 18.0),
        };
    }

    finalizeTemplateSamples(samples);
    applyRoll(samples[start_flat_count..], -0.25, 0.0);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = template_kind_supertramp,
            .sample_count = @intCast(sample_count),
            .subdivision_count = width_cells,
        },
        .width_cells = width_cells,
        .sample_count = @intCast(sample_count),
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn buildNonlinear42Template(allocator: std.mem.Allocator, spec: TemplateSpec) !Template {
    const width_cells: u16 = 8;
    const sample_count: usize = 66;
    const point_count: usize = sample_count + 1;
    const samples = try allocator.alloc(TemplateSample, point_count);
    errdefer allocator.free(samples);

    for (samples, 0..) |*sample, index| {
        sample.* = .{
            .position = .{
                .x = 0.0,
                .y = 0.0,
                .z = @floatFromInt(index),
            },
            .special_scalar = switch (spec.public_path) {
                // PORT(partial): Android `BuildHalfPipe` is a straight longitudinal strip with a
                // tapered halfpipe cross-section at the entry/exit and a constant-radius trough in
                // the middle. Windows `HALFPIPE` now proves live template kind 42, while public
                // `WARP` is still unresolved, so only `HALFPIPE` takes the tapered branch here.
                .halfpipe => halfpipeRadiusForPoint(index, sample_count),
                .warp => 4.0,
                else => 4.0,
            },
        };
    }

    finalizeTemplateSamples(samples);

    return .{
        .spec = .{
            .public_path = spec.public_path,
            .family = spec.family,
            .status = .partial,
            .template_kind = template_kind_nonlinear_42,
            .sample_count = 66,
            .subdivision_count = width_cells,
        },
        .width_cells = width_cells,
        .sample_count = 66,
        .exit_tail_extra = 1.0,
        .samples = samples,
    };
}

fn halfpipeRadiusForPoint(point_index: usize, sample_count: usize) f32 {
    const edge_count: usize = 16;
    const middle_start = edge_count;
    const exit_start = sample_count - edge_count;

    if (point_index < middle_start) {
        return halfpipeEntryScalar(point_index);
    }
    if (point_index >= exit_start) {
        return halfpipeExitScalar(@min(point_index - exit_start, edge_count - 1));
    }
    return 4.0;
}

fn halfpipeEntryScalar(step_index: usize) f32 {
    const phase = (@as(f32, @floatFromInt(step_index)) * 0.0625 * std.math.pi) + (0.5 * std.math.pi);
    return halfpipeScalarFromPhase(phase);
}

fn halfpipeExitScalar(step_index: usize) f32 {
    const phase = ((1.0 - (@as(f32, @floatFromInt(step_index)) * 0.0625)) * std.math.pi) + (0.5 * std.math.pi);
    return halfpipeScalarFromPhase(phase);
}

fn halfpipeScalarFromPhase(phase: f32) f32 {
    const local_depth = (((std.math.sin(phase) * -0.5) + 0.5) * 0.95 + 0.05) * 4.0;
    return ((local_depth * local_depth) + 16.0) / (local_depth * 2.0);
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
    }
}

fn applyRoll(samples: []TemplateSample, cycles: f32, phase_offset: f32) void {
    if (samples.len == 0) return;
    const world_up = Vec3{ .x = 0.0, .y = 1.0, .z = 0.0 };
    const denom = @as(f32, @floatFromInt(@max(samples.len - 1, 1)));
    for (samples, 0..) |*sample, index| {
        const t = @as(f32, @floatFromInt(index)) / denom;
        const angle = phase_offset + (cycles * 2.0 * std.math.pi * t);
        var base_right = Vec3.cross(world_up, sample.basis_forward);
        if (Vec3.length(base_right) <= 0.0001) {
            base_right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
        } else {
            base_right = Vec3.normalize(base_right);
        }
        const base_up = Vec3.normalize(Vec3.cross(sample.basis_forward, base_right));
        const sin_angle = std.math.sin(angle);
        const cos_angle = std.math.cos(angle);
        sample.basis_right = Vec3.normalize(Vec3.add(
            Vec3.scale(base_right, cos_angle),
            Vec3.scale(base_up, sin_angle),
        ));
        sample.basis_up = Vec3.normalize(Vec3.sub(
            Vec3.scale(base_up, cos_angle),
            Vec3.scale(base_right, sin_angle),
        ));
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
        => blk: {
            const params = verticalLoopParams(public_path);
            const sample_count: u16 = @as(u16, @intFromFloat(@floor(params.radius * (2.0 * std.math.pi)))) + 14;
            break :blk .{
                .public_path = public_path,
                .family = .looptheloop,
                .status = .partial,
                .template_kind = params.template_kind,
                .sample_count = sample_count,
                .subdivision_count = params.subdivision_count,
            };
        },
        .looptheloopw => blk: {
            const params = verticalLoopParams(public_path);
            const sample_count: u16 = @as(u16, @intFromFloat(@floor(params.radius * (2.0 * std.math.pi)))) + 14;
            break :blk .{
                .public_path = public_path,
                .family = .looptheloopw,
                .status = .partial,
                .template_kind = params.template_kind,
                .sample_count = sample_count,
                .subdivision_count = params.subdivision_count,
            };
        },
        .loopbow => .{ .public_path = public_path, .family = .loopbow, .status = .partial, .template_kind = 0, .sample_count = 51, .subdivision_count = 4 },
        .hill,
        .hill4c,
        .hill4,
        .valley,
        .valley4c,
        .valley4,
        => .{
            .public_path = public_path,
            .family = .hill_valley,
            .status = .partial,
            .template_kind = 16,
            .sample_count = 22,
            .subdivision_count = hillValleyParams(public_path).width_cells,
        },
        .sbend => .{ .public_path = public_path, .family = .sbend, .status = .partial, .template_kind = 14, .sample_count = 28, .subdivision_count = 8 },
        .cage2 => .{ .public_path = public_path, .family = .cage2, .status = .partial, .template_kind = 15, .sample_count = 24, .subdivision_count = 3 },
        .hump, .humpsmall => .{
            .public_path = public_path,
            .family = .hump,
            .status = .partial,
            .template_kind = 16,
            .sample_count = 30,
            .subdivision_count = 3,
        },
        .dump, .dumpsmall => .{
            .public_path = public_path,
            .family = .dump,
            .status = .partial,
            .template_kind = 17,
            .sample_count = 30,
            .subdivision_count = 3,
        },
        .dip => .{ .public_path = public_path, .family = .dip, .status = .partial, .template_kind = 20, .sample_count = 22, .subdivision_count = 2 },
        .screw => .{ .public_path = public_path, .family = .screw, .status = .partial, .template_kind = 21, .sample_count = 24, .subdivision_count = 3 },
        .slalom => .{ .public_path = public_path, .family = .slalom, .status = .partial, .template_kind = 22, .sample_count = 32, .subdivision_count = 4 },
        .slalombig => .{ .public_path = public_path, .family = .slalombig, .status = .partial, .template_kind = 23, .sample_count = 32, .subdivision_count = 4 },
        .worm => .{ .public_path = public_path, .family = .worm, .status = .partial, .template_kind = template_kind_worm, .sample_count = 24, .subdivision_count = 16 },
        .loopout, .loopout3, .loopoutbig => blk: {
            const params = loopoutParams(public_path);
            break :blk .{
                .public_path = public_path,
                .family = .loopout,
                .status = .partial,
                .template_kind = 25,
                .sample_count = @as(u16, @intFromFloat(@floor(params.radius * (2.0 * std.math.pi)))) + 14,
                .subdivision_count = params.width_cells,
            };
        },
        .sweep => .{ .public_path = public_path, .family = .sweep, .status = .partial, .template_kind = 28, .sample_count = 30, .subdivision_count = 4 },
        .snake => .{ .public_path = public_path, .family = .snake, .status = .partial, .template_kind = 29, .sample_count = 27, .subdivision_count = 4 },
        .warp, .halfpipe => .{ .public_path = public_path, .family = .nonlinear_42, .status = .partial, .template_kind = template_kind_nonlinear_42, .sample_count = 66, .subdivision_count = 8 },
        .supertramp => .{ .public_path = public_path, .family = .supertramp, .status = .partial, .template_kind = template_kind_supertramp, .sample_count = 32, .subdivision_count = 2 },
        .slalomdouble => .{ .public_path = public_path, .family = .slalomdouble, .status = .partial, .template_kind = 32, .sample_count = 70, .subdivision_count = 4 },
        .p0 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .template_kind = 33, .sample_count = 16, .subdivision_count = 3 },
        .p1 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .template_kind = 34, .sample_count = 16, .subdivision_count = 3 },
        .p2 => .{ .public_path = public_path, .family = .p_family, .status = .partial, .template_kind = 35, .sample_count = 16, .subdivision_count = 3 },
        .start => .{ .public_path = public_path, .family = .start, .status = .ported, .template_kind = template_kind_start, .sample_count = 27, .subdivision_count = 8 },
        .turnover => .{ .public_path = public_path, .family = .turnover, .status = .partial, .template_kind = 37, .sample_count = 45, .subdivision_count = 4 },
        .turnoverdouble => .{ .public_path = public_path, .family = .turnoverdouble, .status = .partial, .template_kind = 38, .sample_count = 64, .subdivision_count = 4 },
        .turnunder => .{ .public_path = public_path, .family = .turnunder, .status = .partial, .template_kind = 39, .sample_count = 45, .subdivision_count = 4 },
        .wibble => .{ .public_path = public_path, .family = .wibble, .status = .partial, .template_kind = 40, .sample_count = 32, .subdivision_count = 8 },
        .invert => .{ .public_path = public_path, .family = .invert, .status = .partial, .template_kind = 41, .sample_count = 34, .subdivision_count = 8 },
        .twistera, .twisterb => .{ .public_path = public_path, .family = .twister, .status = .partial, .template_kind = template_kind_twister, .sample_count = 48, .subdivision_count = 3 },
        .twister2a, .twister2b => .{ .public_path = public_path, .family = .twister2, .status = .partial, .template_kind = template_kind_twister2, .sample_count = 52, .subdivision_count = 3 },
        .toad0, .toad1, .toadpair0, .toadpair1 => .{ .public_path = public_path, .family = .toad, .status = .partial, .template_kind = 47, .sample_count = 24, .subdivision_count = 3 },
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
        .{ .cells = "PPPPPPPPPP", .annotation = .{ .path = "START" } },
        .{ .cells = ".........." },
        .{ .cells = "pppppppppp", .annotation = .{ .path = "HALFPIPE" } },
        .{ .cells = ".........." },
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
    const runtime_tiles = [_]u8{
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    const source_row_mirror_states = [_]bool{ false, false, false, false };
    var scaffold = try Scaffold.collect(
        std.testing.allocator,
        &segments,
        &row_offsets,
        &runtime_tiles,
        rows.len,
        10,
        &source_row_mirror_states,
    );
    defer scaffold.deinit();

    try std.testing.expectEqual(@as(usize, 2), scaffold.authored_rows.len);
    try std.testing.expectEqual(PublicPath.start, scaffold.activePathAtRow(1).?.public_path.?);
    try std.testing.expectEqual(PublicPath.halfpipe, scaffold.activePathAtRow(3).?.public_path.?);
    try std.testing.expectEqual(PublicPath.start, scaffold.installedBuiltAttachmentAtRow(1).?.row.public_path.?);
    const overlap = scaffold.installedBuiltAttachmentsAtRow(3);
    try std.testing.expectEqual(PublicPath.start, overlap.primary.?.row.public_path.?);
    try std.testing.expectEqual(PublicPath.halfpipe, overlap.secondary.?.row.public_path.?);
}

test "collect scaffold builds start template" {
    const rows = [_]segment.Row{
        .{ .cells = "PPPPPPPPPP", .annotation = .{ .path = "START" } },
        .{ .cells = ".........." },
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
    const runtime_tiles = [_]u8{
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
    };
    const source_row_mirror_states = [_]bool{ false, false };
    var scaffold = try Scaffold.collect(
        std.testing.allocator,
        &segments,
        &row_offsets,
        &runtime_tiles,
        rows.len,
        10,
        &source_row_mirror_states,
    );
    defer scaffold.deinit();

    try std.testing.expectEqual(@as(usize, 1), scaffold.built_attachments.len);
    const built = scaffold.built_attachments[0];
    const expected_top_height = (@as(f32, @floatFromInt(@as(usize, @intFromFloat(@floor(4.0 * std.math.pi))))) / std.math.pi) * 2.0;
    try std.testing.expectEqual(PublicPath.start, built.row.public_path.?);
    try std.testing.expectEqual(@as(u16, 27), built.template.sample_count);
    try std.testing.expectEqual(@as(usize, 28), built.template.pointCount());
    try std.testing.expectApproxEqAbs(expected_top_height, built.template.samples[0].position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), built.template.samples[17].position.y, 0.0001);
}

test "collect scaffold mirrors installed template variant from source-row state" {
    const base_spec = specForPublicPath(.p0);
    var base_template = (try buildTemplate(std.testing.allocator, base_spec)).?;
    defer base_template.deinit(std.testing.allocator);

    const rows = [_]segment.Row{
        .{ .cells = "PPPPPPPPPP", .annotation = .{ .path = "P0" } },
    };
    var segments = [_]segment.Definition{.{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "SEGMENTS/P0.TXT",
        .segment_id = 1,
        .name = "P0",
        .width = 10,
        .height = rows.len,
        .rows = &rows,
    }};
    defer segments[0].deinit();
    const row_offsets = [_]usize{0};
    const runtime_tiles = [_]u8{
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
    };
    const source_row_mirror_states = [_]bool{true};
    var scaffold = try Scaffold.collect(
        std.testing.allocator,
        &segments,
        &row_offsets,
        &runtime_tiles,
        rows.len,
        10,
        &source_row_mirror_states,
    );
    defer scaffold.deinit();

    const built = scaffold.built_attachments[0];
    try std.testing.expect(built.template.mirror_or_variant);
    try std.testing.expectApproxEqAbs(-base_template.samples[0].position.x, built.template.samples[0].position.x, 0.0001);
    try std.testing.expectApproxEqAbs(-base_template.samples[0].basis_right.x, built.template.samples[0].basis_right.x, 0.0001);
}

test "collect scaffold mirrors row scalar a sign for mirrored worm source rows" {
    const rows = [_]segment.Row{
        .{ .cells = "PPPPPPPPPP", .annotation = .{ .path = "WORM" } },
    };
    var segments = [_]segment.Definition{.{
        .arena = std.heap.ArenaAllocator.init(std.testing.allocator),
        .source_path = "SEGMENTS/WORM.TXT",
        .segment_id = 1,
        .name = "WORM",
        .width = 10,
        .height = rows.len,
        .rows = &rows,
    }};
    defer segments[0].deinit();
    const row_offsets = [_]usize{0};
    const runtime_tiles = [_]u8{
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
    };
    const source_row_mirror_states = [_]bool{true};
    var scaffold = try Scaffold.collect(
        std.testing.allocator,
        &segments,
        &row_offsets,
        &runtime_tiles,
        rows.len,
        10,
        &source_row_mirror_states,
    );
    defer scaffold.deinit();

    const built = scaffold.built_attachments[0];
    try std.testing.expect(built.template.mirror_or_variant);
    try std.testing.expectApproxEqAbs(@as(f32, -6.2831855), built.template.installed_heading_delta, 0.0001);
}

test "start template interpolation follows recovered descent" {
    const spec = specForPublicPath(.start);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    const mid = samplePoseAtProgress(&template, 10.5);
    try std.testing.expect(mid.position.y < template.samples[0].position.y);
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

test "build halfpipe template with tapered halfpipe radius" {
    const spec = specForPublicPath(.halfpipe);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    try std.testing.expectEqual(@as(u16, 66), template.sample_count);
    try std.testing.expectEqual(@as(u16, 8), template.width_cells);
    try std.testing.expectEqual(@as(usize, 67), template.pointCount());

    const start_radius = template.samples[0].special_scalar;
    const edge_radius = template.samples[15].special_scalar;
    const middle_radius = template.samples[16].special_scalar;
    const exit_start_radius = template.samples[50].special_scalar;
    const end_radius = template.samples[66].special_scalar;

    try std.testing.expectApproxEqAbs(@as(f32, 40.1), start_radius, 0.0001);
    try std.testing.expectApproxEqAbs(halfpipeEntryScalar(15), edge_radius, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 4.0), exit_start_radius, 0.0001);
    try std.testing.expect(end_radius > middle_radius);
    try std.testing.expectApproxEqAbs(@as(f32, 4.0), middle_radius, 0.0001);
}

test "build vertical loop family templates from recovered public slot params" {
    const cases = [_]struct {
        path: PublicPath,
        sample_count: u16,
        width_cells: u16,
        template_kind: u8,
    }{
        .{ .path = .looptheloop, .sample_count = 51, .width_cells = 3, .template_kind = 0 },
        .{ .path = .looptheloop4, .sample_count = 64, .width_cells = 4, .template_kind = 0 },
        .{ .path = .looptheloopt2, .sample_count = 32, .width_cells = 2, .template_kind = 0 },
        .{ .path = .looptheloopw, .sample_count = 64, .width_cells = 4, .template_kind = 6 },
    };

    for (cases) |case| {
        const spec = specForPublicPath(case.path);
        var template = (try buildTemplate(std.testing.allocator, spec)).?;
        defer template.deinit(std.testing.allocator);

        try std.testing.expectEqual(case.sample_count, template.sample_count);
        try std.testing.expectEqual(case.width_cells, template.width_cells);
        try std.testing.expectEqual(case.template_kind, template.spec.template_kind.?);
        try std.testing.expectEqual(@as(usize, case.sample_count) + 1, template.pointCount());
        try std.testing.expect(template.samples[0].position.y == 0.0);
        try std.testing.expect(template.samples[template.samples.len - 1].position.y == 0.0);
    }
}

test "build hill and valley family templates from recovered shared constructor params" {
    const cases = [_]struct {
        path: PublicPath,
        width_cells: u16,
        template_kind: u8,
        expect_peak_positive: bool,
        expected_center_x: f32,
    }{
        .{ .path = .hill, .width_cells = 8, .template_kind = 16, .expect_peak_positive = true, .expected_center_x = 0.0 },
        .{ .path = .hill4c, .width_cells = 4, .template_kind = 16, .expect_peak_positive = true, .expected_center_x = -2.0 },
        .{ .path = .valley4, .width_cells = 4, .template_kind = 16, .expect_peak_positive = false, .expected_center_x = 0.0 },
    };

    for (cases) |case| {
        const spec = specForPublicPath(case.path);
        var template = (try buildTemplate(std.testing.allocator, spec)).?;
        defer template.deinit(std.testing.allocator);

        try std.testing.expectEqual(@as(u16, 22), template.sample_count);
        try std.testing.expectEqual(case.width_cells, template.width_cells);
        try std.testing.expectEqual(case.template_kind, template.spec.template_kind.?);
        try std.testing.expectApproxEqAbs(case.expected_center_x, template.samples[0].center_x, 0.0001);

        const mid = samplePoseAtProgress(&template, 10.5);
        if (case.expect_peak_positive) {
            try std.testing.expect(mid.position.y > 0.0);
        } else {
            try std.testing.expect(mid.position.y < 0.0);
        }
    }
}

test "build hump and dump family templates from recovered shared constructor params" {
    const cases = [_]struct {
        path: PublicPath,
        template_kind: u8,
        width_cells: u16,
        expected_start_center: f32,
        expect_peak_positive: bool,
    }{
        .{ .path = .hump, .template_kind = 16, .width_cells = 3, .expected_start_center = -2.5, .expect_peak_positive = true },
        .{ .path = .humpsmall, .template_kind = 16, .width_cells = 3, .expected_start_center = -2.5, .expect_peak_positive = true },
        .{ .path = .dump, .template_kind = 17, .width_cells = 3, .expected_start_center = 2.5, .expect_peak_positive = false },
        .{ .path = .dumpsmall, .template_kind = 17, .width_cells = 3, .expected_start_center = 2.5, .expect_peak_positive = false },
    };

    for (cases) |case| {
        const spec = specForPublicPath(case.path);
        var template = (try buildTemplate(std.testing.allocator, spec)).?;
        defer template.deinit(std.testing.allocator);

        try std.testing.expectEqual(case.template_kind, template.spec.template_kind.?);
        try std.testing.expectEqual(@as(u16, 30), template.sample_count);
        try std.testing.expectEqual(case.width_cells, template.width_cells);
        try std.testing.expectApproxEqAbs(case.expected_start_center, template.samples[0].center_x, 0.0001);
        try std.testing.expectApproxEqAbs(-case.expected_start_center, template.samples[template.sample_count].center_x, 0.0001);

        const mid = samplePoseAtProgress(&template, 15.0);
        if (case.expect_peak_positive) {
            try std.testing.expect(mid.position.y > 0.1);
        } else {
            try std.testing.expect(mid.position.y < -0.1);
        }
    }
}

test "build loopout family templates from recovered public slot params" {
    const cases = [_]struct {
        path: PublicPath,
        sample_count: u16,
        width_cells: u16,
        radius: f32,
    }{
        .{ .path = .loopout, .sample_count = 32, .width_cells = 4, .radius = 3.0 },
        .{ .path = .loopout3, .sample_count = 32, .width_cells = 3, .radius = 3.0 },
        .{ .path = .loopoutbig, .sample_count = 45, .width_cells = 4, .radius = 5.0 },
    };

    for (cases) |case| {
        const spec = specForPublicPath(case.path);
        var template = (try buildTemplate(std.testing.allocator, spec)).?;
        defer template.deinit(std.testing.allocator);

        try std.testing.expectEqual(@as(u8, 25), template.spec.template_kind.?);
        try std.testing.expectEqual(case.sample_count, template.sample_count);
        try std.testing.expectEqual(case.width_cells, template.width_cells);
        try std.testing.expect(template.samples[10].position.y <= 0.0);

        const mid = samplePoseAtProgress(&template, 10.0 + (case.radius * std.math.pi));
        try std.testing.expect(mid.position.y < -(case.radius * 1.5));
    }
}

test "worm template matches traced runtime metadata" {
    const spec = specForPublicPath(.worm);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    try std.testing.expectEqual(template_kind_worm, template.spec.template_kind.?);
    try std.testing.expectEqual(@as(u16, 24), template.sample_count);
    try std.testing.expectEqual(@as(u16, 4), template.width_cells);
    try std.testing.expectEqual(@as(u16, 16), template.spec.subdivision_count.?);
    try std.testing.expectApproxEqAbs(@as(f32, 6.2831855), template.installed_heading_delta, 0.0001);
}

test "snake template matches traced runtime metadata" {
    const spec = specForPublicPath(.snake);
    var template = (try buildTemplate(std.testing.allocator, spec)).?;
    defer template.deinit(std.testing.allocator);

    try std.testing.expectEqual(@as(u8, 29), template.spec.template_kind.?);
    try std.testing.expectEqual(@as(u16, 27), template.sample_count);
    try std.testing.expectEqual(@as(u16, 4), template.width_cells);
    try std.testing.expectEqual(@as(u16, 4), template.spec.subdivision_count.?);
}

test "all recovered public paths build attachment templates" {
    inline for (std.meta.tags(PublicPath)) |public_path| {
        const spec = specForPublicPath(public_path);
        var template = (try buildTemplate(std.testing.allocator, spec)).?;
        defer template.deinit(std.testing.allocator);

        try std.testing.expectEqual(public_path, template.spec.public_path);
        try std.testing.expect(template.sample_count > 0);
        try std.testing.expect(template.width_cells > 0);
        try std.testing.expectEqual(@as(usize, template.sample_count) + 1, template.pointCount());
        try std.testing.expectEqual(spec.template_kind, template.spec.template_kind);
        try std.testing.expectEqual(spec.subdivision_count, template.spec.subdivision_count);
    }
}
