//! Mirror of the native attachment-follow runtime.
//!
//! This module follows the matched native shape: one function per native
//! function, native names, native statement order, fields per the recovered
//! layout. Transcribed from proven sources in tools/match/scratches/
//! (begin_track_attachment_follow_state @ 0x420c40, 94.55% match;
//! try_enter_track_attachment_from_swept_motion @ 0x42c770, structure-aligned
//! scratch with fully recovered semantics). Cross-reference
//! tools/match/include/track_attachment.h for the C++ twin.
//!
//! RULE: do not refactor this module for taste. It exists to be diffable
//! against matched source. Cleanliness belongs in the layers above; invented
//! abstractions here are how the old model accumulated wrong assumptions.
//!
//! Zig seams (documented, intentional):
//! - the native TrackRowCell*/PathTemplate* pointers become the built
//!   template reference plus the source row index
//! - the native per-row heading table read (game base + 0x64118c + 244*row)
//!   becomes a caller-supplied value; the table itself is asset-derived
//! - the validating update_track_attachment_follow_state call at the end of
//!   the swept entry stays caller-side until that function is matched
//! - the native player y snap is returned to the caller instead of written
//!   through a global Player pointer

const std = @import("std");
const attachment_builders = @import("../../attachment_builders.zig");

const Vec3 = attachment_builders.Vec3;
const Template = attachment_builders.Template;

pub const rider_height: f32 = 0.49;
pub const entry_margin: f32 = 0.3;
pub const entry_min_local_y: f64 = -0.2; // native compares against a double constant
pub const entry_accept_max_y: f32 = 0.001;

/// Native FollowState, one global instance at game+0x430100.
pub const FollowState = struct {
    active: bool = false, // +0x00
    /// +0x04 PathTemplate*; mutated by begin (installed_heading_delta)
    template_record: ?*Template = null,
    source_cell_row: ?usize = null, // +0x08 TrackRowCell*
    sample_index: i32 = 0, // +0x0c
    progress: f32 = 0.0, // +0x10
    vertical_offset: f32 = 0.0, // +0x14
    field_18: f32 = 0.0, // +0x18, zeroed on swept entry, meaning unrecovered
    field_1c: f32 = 0.0, // +0x1c, zeroed on swept entry, meaning unrecovered
    // +0x20..+0x38 unrecovered; +0x38 Player* lives runner-side
    squidge_scratch: f32 = 0.0, // +0x90, consumed then zeroed by swept entry
    update_rate: f32 = 0.0, // +0x94, first arg of the validating follow update
    live_flag: bool = false, // +0x99, cleared by swept entry
};

/// begin_track_attachment_follow_state @ 0x420c40 (matched 94.55%).
/// Statement order mirrors the matched source.
pub fn beginTrackAttachmentFollowState(
    state: *FollowState,
    template: *Template,
    source_cell_row: usize,
    cell_anchor_z: f32,
    world_position: Vec3,
    row_heading_delta: f32,
) *Template {
    state.active = true;
    state.template_record = template;
    state.source_cell_row = source_cell_row;
    state.sample_index = 0;
    state.progress = world_position.z - cell_anchor_z;
    const height = world_position.y - rider_height;
    state.vertical_offset = height;
    template.installed_heading_delta = row_heading_delta;
    return template;
}

pub const SweptEntryAcceptance = struct {
    sample_index: i32,
    /// rotated local y of the first probe; native snaps player world y to this
    snap_player_y: f32,
};

/// try_enter_track_attachment_from_swept_motion @ 0x42c770.
/// Backward sample scan with two rotated probes; on acceptance seeds the
/// shared FollowState exactly like native and reports the player y snap.
/// The caller must run one follow update in the same tick (native calls
/// update_track_attachment_follow_state(state.update_rate, ...) here).
pub fn tryEnterTrackAttachmentFromSweptMotion(
    state: *FollowState,
    template: *Template,
    source_cell_row: usize,
    cell_anchor: Vec3,
    position: Vec3,
    sweep: Vec3,
    row_heading_delta: f32,
) ?SweptEntryAcceptance {
    const sample_count = @min(@as(usize, template.sample_count), template.samples.len);
    if (sample_count == 0) return null;

    var idx: usize = sample_count;
    while (idx > 0) {
        idx -= 1;
        const sample = &template.samples[idx];
        // native: fcomp + test ah,0x41 skips when the gate float is <= 0
        if (sample.basis_up.y <= 0.0) continue;

        const world = Vec3{
            .x = cell_anchor.x + sample.position.x,
            .y = cell_anchor.y + sample.position.y,
            .z = cell_anchor.z + sample.position.z,
        };
        const local = rotateIntoSampleFrame(sample, .{
            .x = position.x - world.x,
            .y = position.y - world.y,
            .z = position.z - world.z,
        });

        // native half-span: signed INTEGER division of width_cells, then ±0.3
        const half_span: f32 = @floatFromInt(@divTrunc(@as(i32, template.width_cells), 2));
        if (!(-half_span - entry_margin < local.x)) continue;
        if (!(half_span + entry_margin > local.x)) continue;
        if (@as(f64, local.y) < entry_min_local_y) continue;
        if (!(local.z > 0.0)) continue;
        if (!(local.z < sample.delta_length)) continue;

        const probe = rotateIntoSampleFrame(sample, .{
            .x = sweep.x + position.x - world.x,
            .y = (position.y + sweep.y) - world.y,
            .z = (position.z + sweep.z) - world.z,
        });
        if (probe.y <= entry_accept_max_y) {
            // seed order mirrors the matched source
            state.live_flag = false;
            // native: player.start_squidge_y(state.squidge_scratch) — caller-side
            state.active = true;
            state.template_record = template;
            state.source_cell_row = source_cell_row;
            state.sample_index = @intCast(idx);
            state.progress = local.z;
            state.vertical_offset = 0.0;
            state.squidge_scratch = 0.0;
            template.installed_heading_delta = row_heading_delta;
            state.field_1c = 0.0;
            state.field_18 = 0.0;
            return .{
                .sample_index = @intCast(idx),
                .snap_player_y = local.y,
            };
        }
    }
    return null;
}

/// rotate_vector_by_matrix on the sample's local frame (native matrix at
/// sample+0x40): project the world-delta onto the basis vectors.
fn rotateIntoSampleFrame(sample: *const attachment_builders.TemplateSample, delta: Vec3) Vec3 {
    return .{
        .x = (delta.x * sample.basis_right.x) + (delta.y * sample.basis_right.y) + (delta.z * sample.basis_right.z),
        .y = (delta.x * sample.basis_up.x) + (delta.y * sample.basis_up.y) + (delta.z * sample.basis_up.z),
        .z = (delta.x * sample.basis_forward.x) + (delta.y * sample.basis_forward.y) + (delta.z * sample.basis_forward.z),
    };
}

fn testTemplate(allocator: std.mem.Allocator, width_cells: u16, samples: []const attachment_builders.TemplateSample) !Template {
    return .{
        .spec = .{ .public_path = .looptheloop, .family = .start, .status = .ported },
        .width_cells = width_cells,
        .sample_count = @intCast(samples.len),
        .samples = try allocator.dupe(attachment_builders.TemplateSample, samples),
    };
}

test "begin seeds follow state in native order with raw world height" {
    var template = try testTemplate(std.testing.allocator, 4, &.{.{}});
    defer template.deinit(std.testing.allocator);
    var state = FollowState{ .live_flag = true };
    const returned = beginTrackAttachmentFollowState(
        &state,
        &template,
        7,
        3.0,
        .{ .x = 0.0, .y = 0.2, .z = 3.5 },
        0.125,
    );
    try std.testing.expect(returned == &template);
    try std.testing.expect(state.active);
    try std.testing.expectEqual(@as(i32, 0), state.sample_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), state.progress, 0.0001);
    // raw world y - 0.49, unclamped: legitimately negative below rider height
    try std.testing.expectApproxEqAbs(@as(f32, 0.2 - 0.49), state.vertical_offset, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.125), template.installed_heading_delta, 0.0001);
    // begin does NOT touch the swept-entry-only fields
    try std.testing.expect(state.live_flag);
}

test "swept entry truncates odd width spans with integer division" {
    const sample = attachment_builders.TemplateSample{ .delta_length = 1.0 };
    var template = try testTemplate(std.testing.allocator, 5, &.{sample});
    defer template.deinit(std.testing.allocator);
    var state = FollowState{};
    // width 5 truncates to half-span 2: |x| must be < 2.3, so x = 2.4 misses
    const miss = tryEnterTrackAttachmentFromSweptMotion(
        &state,
        &template,
        0,
        .{},
        .{ .x = 2.4, .y = 0.0, .z = 0.5 },
        .{},
        0.0,
    );
    try std.testing.expect(miss == null);
    const hit = tryEnterTrackAttachmentFromSweptMotion(
        &state,
        &template,
        0,
        .{},
        .{ .x = 2.2, .y = 0.0, .z = 0.5 },
        .{},
        0.0,
    );
    try std.testing.expect(hit != null);
}

test "swept entry seeds zero vertical offset and reports the player y snap" {
    const sample = attachment_builders.TemplateSample{ .delta_length = 2.0 };
    var template = try testTemplate(std.testing.allocator, 4, &.{sample});
    defer template.deinit(std.testing.allocator);
    var state = FollowState{
        .live_flag = true,
        .squidge_scratch = 0.7,
        .field_18 = 9.0,
        .field_1c = 9.0,
    };
    const acceptance = tryEnterTrackAttachmentFromSweptMotion(
        &state,
        &template,
        3,
        .{},
        .{ .x = 0.1, .y = 0.05, .z = 0.5 },
        .{ .x = 0.0, .y = -0.1, .z = 0.0 },
        0.25,
    ) orelse return error.TestUnexpectedResult;
    try std.testing.expect(state.active);
    try std.testing.expectEqual(@as(i32, 0), acceptance.sample_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), state.progress, 0.0001);
    try std.testing.expectEqual(@as(f32, 0.0), state.vertical_offset);
    try std.testing.expectApproxEqAbs(@as(f32, 0.05), acceptance.snap_player_y, 0.0001);
    try std.testing.expect(!state.live_flag);
    try std.testing.expectEqual(@as(f32, 0.0), state.squidge_scratch);
    try std.testing.expectEqual(@as(f32, 0.0), state.field_18);
    try std.testing.expectEqual(@as(f32, 0.0), state.field_1c);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), template.installed_heading_delta, 0.0001);
}

test "swept entry skips samples whose gate float is exactly zero" {
    var gated = attachment_builders.TemplateSample{ .delta_length = 1.0 };
    gated.basis_up = .{ .x = 0.0, .y = 0.0, .z = 0.0 };
    var template = try testTemplate(std.testing.allocator, 4, &.{gated});
    defer template.deinit(std.testing.allocator);
    var state = FollowState{};
    const result = tryEnterTrackAttachmentFromSweptMotion(
        &state,
        &template,
        0,
        .{},
        .{ .x = 0.0, .y = 0.0, .z = 0.5 },
        .{},
        0.0,
    );
    try std.testing.expect(result == null);
}
