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

pub const FollowUpdateMode = enum(i32) {
    /// also what a BLOCKED side exit returns natively (side_exit_mode != 0):
    /// the side effects (snap, clamp, heading roll) happen but the caller
    /// cannot distinguish it from following — verified from the boss asm
    /// (all three side-exit paths: test [template+0x40]; sete al)
    following = 0,
    side_exit = 1, // side_exit_mode == 0
    natural_end = 3,
    // update_subgoldy's case 2 for this call is dead code (unreachable —
    // the function only returns 0, 1, or 3), same class as the voice-4 lane
};

pub const FollowUpdateDeps = struct {
    /// player jetpack gauge state (state 1 skips the side-exit test)
    jetpack_state_is_hover: bool,
    /// template kind ids per the native table
    kind: u8,
    width_cells: i32,
    width_or_scale: f32,
    side_exit_mode_zero: bool,
    special_runtime_flag: bool,
    installed_heading_delta: f32,
    segment_count: u32,
    context: *anyopaque,
    /// voice 4 (dead lane, index+1 == 2*count) and voice 15 (supertramp)
    play_voice_fn: *const fn (context: *anyopaque, voice: u8) void,
    /// milestone row writes at count-1 (value 1.0) and 3*count/7 (0.6 + flag 0x80)
    milestone_fn: *const fn (context: *anyopaque, terminal: bool) void,
    /// heading roll accumulation on the player
    add_heading_roll_fn: *const fn (context: *anyopaque, delta: f32) void,
    /// supertramp pitch-cycle seed (subgame_rate / 72)
    seed_pitch_cycle_fn: *const fn (context: *anyopaque) void,
};

/// update_track_attachment_follow_state @ 0x420cb0 (pinned scratch,
/// tools/match). Progress stepping, milestone lanes, exhaust handling and
/// the exit gates; the transform/lerp output lanes stay runner-side until
/// the matrix-lerp seam is settled (native linear_interpolate_matrix does
/// not obviously normalize; the runner's pose lerp does — flagged in the
/// campaign notes).
pub fn updateTrackAttachmentFollowState(
    state: *FollowState,
    template: *Template,
    path_factor: f32,
    out_lateral_x: f32,
    lateral_center: f32,
    motion_y: *f32,
    motion_z: *f32,
    deps: FollowUpdateDeps,
) FollowUpdateMode {
    const samples = template.samples;
    const count: u32 = deps.segment_count;
    var index: u32 = @intCast(state.sample_index);
    if (index >= samples.len) return .following;
    var step = path_factor * samples[index].delta_length;

    if (step + state.progress > samples[index].delta_length) {
        while (true) {
            step -= samples[index].delta_length - state.progress;
            index += 1;
            state.progress = 0.0;
            state.sample_index = @intCast(index);
            if (index == 2 * count) deps.play_voice_fn(deps.context, 4); // dead lane, kept faithful
            if (deps.special_runtime_flag) {
                if (index == count - 1) {
                    deps.milestone_fn(deps.context, true);
                } else if (index == (3 * count) / 7) {
                    deps.milestone_fn(deps.context, false);
                }
            }
            if (index == count) {
                // exhaustion: natural end
                state.active = false;
                if (step >= 1.0) step = 0.99900001;
                var launch = path_factor * samples[count - 1].delta_length;
                if (launch > 1.0) launch = 1.0;
                motion_z.* = launch;
                if (deps.kind == 31) {
                    motion_y.* = launch * 0.7;
                    deps.seed_pitch_cycle_fn(deps.context);
                    deps.play_voice_fn(deps.context, 15);
                }
                _ = deps.width_or_scale; // exhaust z-position lane stays runner-side
                deps.add_heading_roll_fn(deps.context, deps.installed_heading_delta);
                return .natural_end;
            }
            if (index < samples.len and step + state.progress <= samples[index].delta_length) break;
            if (index >= samples.len) return .following;
        }
    }

    state.progress = step + state.progress;
    const alpha = if (samples[index].delta_length <= 0.0001)
        0.0
    else
        state.progress / samples[index].delta_length;

    // orientation phase lane (the native rotation-scalar lerp into b is dead)
    const index_f: f32 = @floatFromInt(index);
    const count_f: f32 = @floatFromInt(count);
    state.vertical_offset += motion_y.*;

    const orientation_b = (alpha + index_f) * deps.installed_heading_delta / count_f;
    _ = orientation_b; // published runner-side until orientation fields route

    // exit gates
    if (!deps.jetpack_state_is_hover) {
        var lateral = out_lateral_x - lateral_center;
        if (lateral < 0.0) lateral = -lateral;
        const half: f32 = @floatFromInt(deps.width_cells);
        if (!(lateral <= half * 0.5 + 0.30000001 or state.vertical_offset > 0.0)) {
            deps.add_heading_roll_fn(deps.context, deps.installed_heading_delta);
            return if (deps.side_exit_mode_zero) .side_exit else .following;
        }
    }
    if (state.vertical_offset < 0.0) {
        state.vertical_offset = 0.0;
        motion_y.* = 0.0;
    }
    return .following;
}

test "follow update returns natural end and caps the launch lanes" {
    var samples = [_]attachment_builders.TemplateSample{ .{ .delta_length = 1.0 }, .{ .delta_length = 1.0 } };
    var template = Template{
        .spec = .{ .public_path = .looptheloop, .family = .start, .status = .ported },
        .sample_count = 2,
        .samples = &samples,
    };
    var state = FollowState{ .active = true, .sample_index = 1, .progress = 0.9 };
    var calls = TestFollowDeps{};
    var my: f32 = 0.0;
    var mz: f32 = 0.0;
    const mode = updateTrackAttachmentFollowState(&state, &template, 2.0, 0.0, 0.0, &my, &mz, calls.deps(.{ .kind = 31, .segment_count = 2 }));
    try std.testing.expectEqual(FollowUpdateMode.natural_end, mode);
    try std.testing.expect(!state.active);
    try std.testing.expectEqual(@as(f32, 1.0), mz); // capped
    try std.testing.expectApproxEqAbs(@as(f32, 0.7), my, 0.0001); // supertramp 0.7 * z
    try std.testing.expect(calls.voice_15);
    try std.testing.expect(calls.pitch_seeded);
    try std.testing.expect(calls.heading_rolls == 1);
}

test "follow update accumulates motion y into vertical offset and clamps at zero" {
    var samples = [_]attachment_builders.TemplateSample{.{ .delta_length = 10.0 }};
    var template = Template{
        .spec = .{ .public_path = .looptheloop, .family = .start, .status = .ported },
        .sample_count = 1,
        .samples = &samples,
    };
    var state = FollowState{ .active = true, .sample_index = 0, .progress = 0.0, .vertical_offset = 0.05 };
    var calls = TestFollowDeps{};
    var my: f32 = -0.2;
    var mz: f32 = 0.0;
    const mode = updateTrackAttachmentFollowState(&state, &template, 0.01, 0.0, 0.0, &my, &mz, calls.deps(.{}));
    try std.testing.expectEqual(FollowUpdateMode.following, mode);
    // 0.05 + (-0.2) = -0.15 -> clamped to 0 with motion y zeroed
    try std.testing.expectEqual(@as(f32, 0.0), state.vertical_offset);
    try std.testing.expectEqual(@as(f32, 0.0), my);
}

test "follow update side-exits outside the float half span" {
    var samples = [_]attachment_builders.TemplateSample{.{ .delta_length = 10.0 }};
    var template = Template{
        .spec = .{ .public_path = .looptheloop, .family = .start, .status = .ported },
        .sample_count = 1,
        .samples = &samples,
    };
    var state = FollowState{ .active = true, .sample_index = 0, .vertical_offset = -0.1 };
    var calls = TestFollowDeps{};
    var my: f32 = 0.0;
    var mz: f32 = 0.0;
    // width 4 -> half span 2.0 + 0.3; |x - center| = 2.4 exits
    const mode = updateTrackAttachmentFollowState(&state, &template, 0.01, 2.4, 0.0, &my, &mz, calls.deps(.{ .width_cells = 4 }));
    try std.testing.expectEqual(FollowUpdateMode.side_exit, mode);
    try std.testing.expect(calls.heading_rolls == 1);
}

const TestFollowDeps = struct {
    voice_15: bool = false,
    pitch_seeded: bool = false,
    heading_rolls: u32 = 0,
    milestones: u32 = 0,

    const Overrides = struct {
        kind: u8 = 0,
        width_cells: i32 = 4,
        segment_count: u32 = 1,
    };

    fn deps(self: *TestFollowDeps, overrides: Overrides) FollowUpdateDeps {
        return .{
            .jetpack_state_is_hover = false,
            .kind = overrides.kind,
            .width_cells = overrides.width_cells,
            .width_or_scale = 0.0,
            .side_exit_mode_zero = true,
            .special_runtime_flag = false,
            .installed_heading_delta = 0.5,
            .segment_count = overrides.segment_count,
            .context = self,
            .play_voice_fn = playVoice,
            .milestone_fn = milestone,
            .add_heading_roll_fn = addHeadingRoll,
            .seed_pitch_cycle_fn = seedPitch,
        };
    }

    fn playVoice(context: *anyopaque, voice: u8) void {
        const self: *TestFollowDeps = @ptrCast(@alignCast(context));
        if (voice == 15) self.voice_15 = true;
    }
    fn milestone(context: *anyopaque, terminal: bool) void {
        _ = terminal;
        const self: *TestFollowDeps = @ptrCast(@alignCast(context));
        self.milestones += 1;
    }
    fn addHeadingRoll(context: *anyopaque, delta: f32) void {
        _ = delta;
        const self: *TestFollowDeps = @ptrCast(@alignCast(context));
        self.heading_rolls += 1;
    }
    fn seedPitch(context: *anyopaque) void {
        const self: *TestFollowDeps = @ptrCast(@alignCast(context));
        self.pitch_seeded = true;
    }
};
