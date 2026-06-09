const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("../attachment_builders.zig");
const track = @import("../track.zig");
const attachment = @import("attachment.zig");

pub const intro_cutscene_duration_ticks: u16 = 240;
pub const completion_cutscene_duration_ticks: u16 = 72;
pub const death_cutscene_duration_ticks: u16 = 72;
pub const intro_cutscene_hold_ticks: u16 = intro_cutscene_duration_ticks / 2;
pub const intro_cutscene_blend_ticks: u16 = intro_cutscene_duration_ticks - intro_cutscene_hold_ticks;
pub const completion_cutscene_blend_ticks: u16 = completion_cutscene_duration_ticks / 2;
pub const death_cutscene_blend_ticks: u16 = death_cutscene_duration_ticks / 2;

pub const completion_cutscene_x_offset: f32 = 0.5;
pub const death_cutscene_x_offset: f32 = 2.0;
pub const death_cutscene_y_floor: f32 = 0.0;

pub const cameraman_base_right = rl.Vector3{ .x = 1.0, .y = 0.0, .z = 0.0 };
pub const cameraman_base_up = rl.Vector3{ .x = 0.0, .y = 0.946000993, .z = 0.324162006 };
pub const cameraman_base_forward = rl.Vector3{ .x = 0.0, .y = -0.324162006, .z = 0.946000993 };
pub const cameraman_identity_matrix = rl.Matrix{
    .m0 = 1.0,
    .m4 = 0.0,
    .m8 = 0.0,
    .m12 = 0.0,
    .m1 = 0.0,
    .m5 = 1.0,
    .m9 = 0.0,
    .m13 = 0.0,
    .m2 = 0.0,
    .m6 = 0.0,
    .m10 = 1.0,
    .m14 = 0.0,
    .m3 = 0.0,
    .m7 = 0.0,
    .m11 = 0.0,
    .m15 = 1.0,
};
pub const cameraman_base_translation_y: f32 = 1.8;
pub const cameraman_base_translation_z: f32 = -0.5;
pub const cameraman_lateral_follow_scale: f32 = 0.333333343;
pub const cameraman_vertical_lift_early_weight: f32 = 1.15;
pub const cameraman_vertical_lift_late_weight: f32 = 0.35;
pub const cameraman_deadzone_min_z_delta: f32 = 1.70000005;
pub const cameraman_deadzone_max_z_delta: f32 = 3.0;
pub const cameraman_fov_blend: f32 = 0.3;
pub const cameraman_matrix_blend_scale: f32 = 0.3;
pub const cameraman_lift_blend: f32 = 0.1;
pub const cameraman_attachment_lift_scale: f32 = 0.35;
pub const cameraman_launch_lift_scale: f32 = 0.24;
pub const cameraman_worm_fov_bonus: f32 = 50.0;
pub const native_hotspot_camera_skid_stop_index: u8 = 12;
pub const native_hotspot_camera_slug_death_index: u8 = 17;
pub const native_hotspot_camera_intro_talk_index: u8 = 18;
pub const hotspot_camera_skid_stop_local = rl.Vector3{ .x = -0.54505, .y = 0.0, .z = 1.8749 };
pub const hotspot_camera_slug_death_local = rl.Vector3{ .x = -0.0088, .y = 0.7189, .z = -5.4915 };
pub const hotspot_camera_intro_talk_local = rl.Vector3{ .x = 0.862, .y = -0.13765, .z = 1.87215 };

pub const attachment_entry_rider_height: f32 = attachment.entry_rider_height;

pub const CameraHotspotWorldState = struct {
    camera_skid_stop: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    camera_slug_death: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    camera_intro_talk: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

pub const CutsceneCameraState = enum(u8) {
    none = 0,
    intro_arm = 1,
    intro_hold = 2,
    completion_arm = 5,
    completion_blend = 6,
    completion_hold = 7,
    intro_blend = 8,
    intro_release = 9,
    death_arm = 10,
    death_blend = 11,
    death_hold = 12,
};

pub const CutsceneCameraController = struct {
    state: CutsceneCameraState = .none,
    matrix: rl.Matrix = cameraman_identity_matrix,
    snap_next: bool = false,
    ticks: u16 = 0,
};

pub const CameramanState = struct {
    live_matrix: rl.Matrix = cameraman_identity_matrix,
    desired_matrix: rl.Matrix = cameraman_identity_matrix,
    previous_desired_matrix: rl.Matrix = cameraman_identity_matrix,
    snap_next: bool = false,
    fov_degrees: f32 = 110.0,
    attachment_lift_envelope: f32 = 0.0,
    smoothed_attachment_lift_envelope: f32 = 0.0,
};

pub const CameraTransform = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
};

pub fn lerpVector3(a: rl.Vector3, b: rl.Vector3, t: f32) rl.Vector3 {
    return .{
        .x = std.math.lerp(a.x, b.x, t),
        .y = std.math.lerp(a.y, b.y, t),
        .z = std.math.lerp(a.z, b.z, t),
    };
}

pub fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

pub fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

pub fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const length_squared = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    if (length_squared <= 0.000001) {
        return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    }
    const inv_length = @as(f32, 1.0) / @sqrt(length_squared);
    return .{
        .x = v.x * inv_length,
        .y = v.y * inv_length,
        .z = v.z * inv_length,
    };
}

pub fn rotateVectorWorldX(v: rl.Vector3, radians: f32) rl.Vector3 {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return .{
        .x = v.x,
        .y = (v.y * cos_theta) + (v.z * sin_theta),
        .z = (v.z * cos_theta) - (v.y * sin_theta),
    };
}

pub fn rotateVectorWorldZ(v: rl.Vector3, radians: f32) rl.Vector3 {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return .{
        .x = (v.x * cos_theta) - (v.y * sin_theta),
        .y = (v.x * sin_theta) + (v.y * cos_theta),
        .z = v.z,
    };
}

pub fn cameraMatrixFromTransform(transform: CameraTransform) rl.Matrix {
    return .{
        .m0 = transform.right.x,
        .m4 = transform.up.x,
        .m8 = transform.forward.x,
        .m12 = transform.position.x,
        .m1 = transform.right.y,
        .m5 = transform.up.y,
        .m9 = transform.forward.y,
        .m13 = transform.position.y,
        .m2 = transform.right.z,
        .m6 = transform.up.z,
        .m10 = transform.forward.z,
        .m14 = transform.position.z,
        .m3 = 0.0,
        .m7 = 0.0,
        .m11 = 0.0,
        .m15 = 1.0,
    };
}

pub fn cameraTransformFromMatrix(matrix: rl.Matrix) CameraTransform {
    return .{
        .position = .{ .x = matrix.m12, .y = matrix.m13, .z = matrix.m14 },
        .right = .{ .x = matrix.m0, .y = matrix.m1, .z = matrix.m2 },
        .up = .{ .x = matrix.m4, .y = matrix.m5, .z = matrix.m6 },
        .forward = .{ .x = matrix.m8, .y = matrix.m9, .z = matrix.m10 },
    };
}

pub fn normalizeCameraTransform(transform: CameraTransform) CameraTransform {
    const forward = normalizeVector3(transform.forward);
    var right = crossVector3(transform.up, forward);
    if ((right.x * right.x) + (right.y * right.y) + (right.z * right.z) <= 0.000001) {
        right = normalizeVector3(transform.right);
    } else {
        right = normalizeVector3(right);
    }
    const up = normalizeVector3(crossVector3(forward, right));
    return .{
        .position = transform.position,
        .right = right,
        .up = up,
        .forward = forward,
    };
}

pub fn rotateCameraTransformWorldX(transform: CameraTransform, radians: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = rotateVectorWorldX(transform.right, radians),
        .up = rotateVectorWorldX(transform.up, radians),
        .forward = rotateVectorWorldX(transform.forward, radians),
    });
}

pub fn rotateCameraTransformWorldZ(transform: CameraTransform, radians: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = rotateVectorWorldZ(transform.right, radians),
        .up = rotateVectorWorldZ(transform.up, radians),
        .forward = rotateVectorWorldZ(transform.forward, radians),
    });
}

pub fn rotateCameraTransformLocalZ(transform: CameraTransform, radians: f32) CameraTransform {
    const sin_theta = std.math.sin(radians);
    const cos_theta = std.math.cos(radians);
    return normalizeCameraTransform(.{
        .position = transform.position,
        .right = .{
            .x = (transform.right.x * cos_theta) + (transform.up.x * sin_theta),
            .y = (transform.right.y * cos_theta) + (transform.up.y * sin_theta),
            .z = (transform.right.z * cos_theta) + (transform.up.z * sin_theta),
        },
        .up = .{
            .x = (transform.up.x * cos_theta) - (transform.right.x * sin_theta),
            .y = (transform.up.y * cos_theta) - (transform.right.y * sin_theta),
            .z = (transform.up.z * cos_theta) - (transform.right.z * sin_theta),
        },
        .forward = transform.forward,
    });
}

pub fn blendCameraTransforms(lhs: CameraTransform, rhs: CameraTransform, t: f32) CameraTransform {
    return normalizeCameraTransform(.{
        .position = lerpVector3(lhs.position, rhs.position, t),
        .right = lerpVector3(lhs.right, rhs.right, t),
        .up = lerpVector3(lhs.up, rhs.up, t),
        .forward = lerpVector3(lhs.forward, rhs.forward, t),
    });
}

pub fn orthonormalFrameFromForwardUp(forward: rl.Vector3, up_hint: rl.Vector3) CameraTransform {
    const normalized_forward = normalizeVector3(forward);
    var right = crossVector3(up_hint, normalized_forward);
    if ((right.x * right.x) + (right.y * right.y) + (right.z * right.z) <= 0.000001) {
        right = cameraman_base_right;
    } else {
        right = normalizeVector3(right);
    }
    const up = normalizeVector3(crossVector3(normalized_forward, right));
    return .{
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .right = right,
        .up = up,
        .forward = normalized_forward,
    };
}

pub fn pointCameraTransformAt(position: rl.Vector3, target: rl.Vector3, up_hint: rl.Vector3) CameraTransform {
    var transform = orthonormalFrameFromForwardUp(.{
        .x = target.x - position.x,
        .y = target.y - position.y,
        .z = target.z - position.z,
    }, up_hint);
    transform.position = position;
    return transform;
}

pub fn cameraMatrixWithPosition(matrix: rl.Matrix, position: rl.Vector3) rl.Matrix {
    var result = matrix;
    result.m12 = position.x;
    result.m13 = position.y;
    result.m14 = position.z;
    return result;
}

pub fn lookAtPoint(matrix: rl.Matrix, target: rl.Vector3, up_hint: rl.Vector3) rl.Matrix {
    const position = rl.Vector3{
        .x = matrix.m12,
        .y = matrix.m13,
        .z = matrix.m14,
    };
    return cameraMatrixFromTransform(pointCameraTransformAt(position, target, up_hint));
}

pub fn normalizeCameraMatrix(matrix: rl.Matrix) rl.Matrix {
    const translation = rl.Vector3{
        .x = matrix.m12,
        .y = matrix.m13,
        .z = matrix.m14,
    };
    var result = cameraMatrixFromTransform(normalizeCameraTransform(cameraTransformFromMatrix(matrix)));
    result.m12 = translation.x;
    result.m13 = translation.y;
    result.m14 = translation.z;
    return result;
}

pub fn interpolateCameraMatrixRotation(matrix: rl.Matrix, t: f32) rl.Matrix {
    const amount = std.math.clamp(t, 0.0, 1.0);
    var rotation = rl.math.quaternionNormalize(rl.math.quaternionFromMatrix(cameraMatrixWithPosition(matrix, .{
        .x = 0.0,
        .y = 0.0,
        .z = 0.0,
    })));
    if (@abs(rotation.x) <= 0.00001) rotation.x = 0.0;
    if (@abs(rotation.y) <= 0.00001) rotation.y = 0.0;
    if (@abs(rotation.z) <= 0.00001) rotation.z = 0.0;
    if (rotation.x == 0.0 and rotation.y == 0.0 and rotation.z == 0.0) {
        return normalizeCameraMatrix(rl.math.quaternionToMatrix(rotation));
    }

    var axis: rl.Vector3 = undefined;
    var angle: f32 = 0.0;
    rl.math.quaternionToAxisAngle(rotation, &axis, &angle);
    return normalizeCameraMatrix(rl.math.quaternionToMatrix(rl.math.quaternionFromAxisAngle(axis, angle * amount)));
}

pub fn linearInterpolateCameraMatrices(lhs: rl.Matrix, rhs: rl.Matrix, t: f32) rl.Matrix {
    const amount = std.math.clamp(t, 0.0, 1.0);
    const lhs_rotation = cameraMatrixWithPosition(lhs, .{ .x = 0.0, .y = 0.0, .z = 0.0 });
    const rhs_rotation = cameraMatrixWithPosition(rhs, .{ .x = 0.0, .y = 0.0, .z = 0.0 });
    const relative_rotation = rl.math.matrixMultiply(rl.math.matrixInvert(lhs_rotation), rhs_rotation);

    var result = interpolateCameraMatrixRotation(relative_rotation, amount);
    result = rl.math.matrixMultiply(lhs_rotation, result);
    result = normalizeCameraMatrix(result);
    result.m12 = std.math.lerp(lhs.m12, rhs.m12, amount);
    result.m13 = std.math.lerp(lhs.m13, rhs.m13, amount);
    result.m14 = std.math.lerp(lhs.m14, rhs.m14, amount);
    return result;
}

pub fn normalizeRadians(radians: f32) f32 {
    var angle = radians;
    while (angle > std.math.pi) angle -= std.math.tau;
    while (angle < -std.math.pi) angle += std.math.tau;
    return angle;
}

pub fn rollRadiansFromForwardUp(forward: rl.Vector3, up: rl.Vector3) f32 {
    const normalized_forward = normalizeVector3(forward);
    var reference_right = crossVector3(.{ .x = 0.0, .y = 1.0, .z = 0.0 }, normalized_forward);
    if (dotVector3(reference_right, reference_right) <= 0.000001) {
        reference_right = crossVector3(.{ .x = 1.0, .y = 0.0, .z = 0.0 }, normalized_forward);
    }
    reference_right = normalizeVector3(reference_right);
    const reference_up = normalizeVector3(crossVector3(normalized_forward, reference_right));
    const normalized_up = normalizeVector3(up);
    return std.math.atan2(
        dotVector3(normalized_up, reference_right),
        dotVector3(normalized_up, reference_up),
    );
}

pub fn interpolateWrappedRadians(lhs: f32, rhs: f32, amount: f32) f32 {
    return normalizeRadians(lhs + (normalizeRadians(rhs - lhs) * amount));
}

pub fn attachmentVec3ToVector3(vector: attachment_builders.Vec3) rl.Vector3 {
    return .{ .x = vector.x, .y = vector.y, .z = vector.z };
}

pub fn attachmentSampleOrientationA(sample: *const attachment_builders.TemplateSample) f32 {
    return rollRadiansFromForwardUp(
        attachmentVec3ToVector3(sample.basis_forward),
        attachmentVec3ToVector3(sample.basis_up),
    );
}

pub fn buildNormalCameramanTransform(
    translation_x: f32,
    translation_y: f32,
    translation_z: f32,
    intro_pitch_radians: f32,
    anchor_pitch_radians: f32,
) CameraTransform {
    var transform: CameraTransform = .{
        .position = .{
            .x = translation_x,
            .y = translation_y,
            .z = translation_z,
        },
        .right = cameraman_base_right,
        .up = cameraman_base_up,
        .forward = cameraman_base_forward,
    };
    transform = rotateCameraTransformWorldX(transform, intro_pitch_radians);
    transform = rotateCameraTransformWorldX(transform, anchor_pitch_radians);
    return transform;
}

pub fn cameramanVerticalLiftFromCachedTarget(anchor_y: f32, progress_blend: f32) f32 {
    return std.math.lerp(
        anchor_y * cameraman_vertical_lift_early_weight,
        anchor_y * cameraman_vertical_lift_late_weight,
        progress_blend,
    );
}

pub fn cameramanPitchRadiansFromCachedTarget(anchor_y: f32) f32 {
    return std.math.clamp(
        (-2.0 - ((anchor_y - 0.49) * 5.0)) * 0.0174499992,
        -1.22149992,
        1.22149992,
    );
}

pub fn clampedPreviousDesiredCameraZ(desired_camera_z: f32, previous_z: f32) f32 {
    const previous_delta_z = desired_camera_z - previous_z;
    if (previous_delta_z > cameraman_deadzone_max_z_delta) {
        return desired_camera_z - cameraman_deadzone_max_z_delta;
    }
    if (previous_delta_z < cameraman_deadzone_min_z_delta) {
        return desired_camera_z - cameraman_deadzone_min_z_delta;
    }
    return previous_z;
}

fn attachmentCameraEnvelope(progress: f32) f32 {
    return 0.5 - (std.math.cos(std.math.clamp(progress, 0.0, 1.0) * std.math.tau) * 0.5);
}

fn launchCameraEnvelope(progress: f32) f32 {
    return 0.5 - (std.math.cos((std.math.clamp(progress, 0.0, 1.0) * 4.712389) + 1.5707964) * 0.5);
}

fn attachmentCameraLiftTemplateKindEnabled(template_kind: u8) bool {
    return switch (template_kind) {
        8, 9, 10, 14, 16, 36, 43, 45 => true,
        else => false,
    };
}

pub fn refreshRunnerCameraState(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    refreshRunnerCachedCameraTarget(runner, preview);
    refreshRunnerCameraHotspots(runner, preview);
    refreshRunnerCameraRollState(runner, preview);
    updateRunnerCameraman(runner, preview);
    updateRunnerCutsceneCamera(runner, preview);
}

pub fn refreshRunnerCachedCameraTarget(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (preview.total_rows == 0) {
        runner.cached_camera_target_world = .{ .x = 0.0, .y = 0.0, .z = 0.0 };
        return;
    }

    const base_position = playerWorldPosition(runner, preview);
    const frame = orthonormalFrameFromForwardUp(runner.worldForward(preview), runner.worldUp(preview));
    // PORT(verified): raw `update_subgoldy` disassembly @ 0x43cb50 applies the
    // jetpack warning wobble as x/right, y/up, alpha/forward. IDA's temporary
    // labels around this block are misleading because the FPU stack is reused.
    const local_offset = rl.Vector3{
        .x = runner.jetpack.wobble_x,
        .y = runner.jetpack.wobble_y,
        .z = runner.jetpack.wobble_alpha,
    };
    runner.cached_camera_target_world = .{
        .x = base_position.x + (frame.right.x * local_offset.x) + (frame.up.x * local_offset.y) + (frame.forward.x * local_offset.z),
        .y = base_position.y + (frame.right.y * local_offset.x) + (frame.up.y * local_offset.y) + (frame.forward.y * local_offset.z),
        .z = base_position.z + (frame.right.z * local_offset.x) + (frame.up.z * local_offset.y) + (frame.forward.z * local_offset.z),
    };
}

pub fn cameramanProgressBlend(runner: anytype, preview: *const track.LoadedLevelPreview) f32 {
    if (preview.total_rows == 0 or preview.runtime_active_row_start == 0) return 1.0;
    const intro_transition_rows = @as(f32, @floatFromInt(preview.runtime_active_row_start));
    const cached_target_z = runner.cached_camera_target_world.z;
    return std.math.clamp(((cached_target_z / intro_transition_rows) * 1.4) - 0.4, 0.0, 1.0);
}

pub fn cameramanMatrixBlendFactor(runner: anytype) f32 {
    return std.math.clamp(runner.track_center_x * cameraman_matrix_blend_scale, 0.0, 1.0);
}

pub fn cameramanAttachmentLiftEnvelope(runner: anytype, preview: *const track.LoadedLevelPreview) f32 {
    var envelope: f32 = 0.0;
    if (runner.currentAttachmentCameraProgress(preview)) |attachment_camera| {
        if (attachmentCameraLiftTemplateKindEnabled(attachment_camera.template_kind)) {
            envelope += attachmentCameraEnvelope(attachment_camera.template_progress) * cameraman_attachment_lift_scale;
        }
    }
    if (runner.attachment.launch.active and runner.attachment.launch.camera_progress > 0.0) {
        envelope += launchCameraEnvelope(runner.attachment.launch.camera_progress) * cameraman_launch_lift_scale;
    }
    return envelope;
}

pub fn cameramanDesiredFovDegrees(runner: anytype, preview: *const track.LoadedLevelPreview) f32 {
    const attachment_camera = runner.currentAttachmentCameraProgress(preview) orelse return 110.0;
    if (attachment_camera.template_kind != attachment_builders.template_kind_worm) return 110.0;
    return 110.0 + (attachmentCameraEnvelope(attachment_camera.template_progress) * cameraman_worm_fov_bonus);
}

pub fn refreshRunnerCameraRollState(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    runner.attachment.camera.orientation_a = 0.0;
    runner.attachment.camera.orientation_b = 0.0;
    runner.attachment.follow.exit_carryover_a = 0.0;
    runner.attachment.follow.exit_carryover_b = 0.0;

    if (runner.movement_mode == .attachment and runner.attachment.follow.active) {
        runner.attachment.camera.orientation_a = runner.attachment.follow.camera_orientation_a;
        runner.attachment.camera.orientation_b = runner.attachment.follow.camera_orientation_b;
        const exit_carryover = runner.attachmentExitCarryoverFromFollow(preview);
        runner.attachment.follow.exit_carryover_a = exit_carryover.carryover_a;
        runner.attachment.follow.exit_carryover_b = exit_carryover.carryover_b;
        runner.attachment.exit.carryover_a = exit_carryover.carryover_a;
        runner.attachment.exit.carryover_b = exit_carryover.carryover_b;
        return;
    }

    if (runner.attachment.launch.active) {
        runner.attachment.camera.previous_heading_roll_sample = rollRadiansFromForwardUp(runner.worldForward(preview), runner.worldUp(preview));
        return;
    }

    if (runner.phase == .fall) return;
    runner.attachment.camera.previous_heading_roll_sample = 0.0;
}

pub fn playerWorldPosition(runner: anytype, preview: *const track.LoadedLevelPreview) rl.Vector3 {
    if (runner.phase == .fall) return runner.worldPosition(preview, 0.0);
    if (runner.movement_mode == .attachment and runner.attachment.follow.active) {
        return runner.worldPosition(preview, 0.0);
    }
    if (runner.attachment.launch.active) return runner.worldPosition(preview, 0.0);
    return runner.worldPosition(preview, attachment_entry_rider_height);
}

pub fn cameraHotspotSourceFrameA(runner: anytype, preview: *const track.LoadedLevelPreview) CameraTransform {
    var frame = orthonormalFrameFromForwardUp(runner.worldForward(preview), runner.worldUp(preview));
    frame.position = runner.worldPosition(preview, attachment_entry_rider_height);
    return frame;
}

pub fn cameraHotspotSourceFrameB(runner: anytype, preview: *const track.LoadedLevelPreview) CameraTransform {
    var frame = orthonormalFrameFromForwardUp(runner.worldForward(preview), runner.worldUp(preview));
    frame.position = playerWorldPosition(runner, preview);
    return frame;
}

fn transformLocalPointByMatrix(matrix: rl.Matrix, local: rl.Vector3) rl.Vector3 {
    return .{
        .x = matrix.m12 + (matrix.m0 * local.x) + (matrix.m4 * local.y) + (matrix.m8 * local.z),
        .y = matrix.m13 + (matrix.m1 * local.x) + (matrix.m5 * local.y) + (matrix.m9 * local.z),
        .z = matrix.m14 + (matrix.m2 * local.x) + (matrix.m6 * local.y) + (matrix.m10 * local.z),
    };
}

pub fn refreshRunnerCameraHotspots(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (preview.total_rows == 0) {
        runner.camera_hotspots_world = .{};
        return;
    }

    const source_matrix_a = cameraMatrixFromTransform(cameraHotspotSourceFrameA(runner, preview));
    const source_matrix_b = cameraMatrixFromTransform(cameraHotspotSourceFrameB(runner, preview));

    const hotspotSourceMatrix = struct {
        fn select(source_a: rl.Matrix, source_b: rl.Matrix, hotspot_index: u8) rl.Matrix {
            return switch (hotspot_index) {
                0...10 => source_b,
                else => source_a,
            };
        }
    }.select;

    runner.camera_hotspots_world.camera_skid_stop = transformLocalPointByMatrix(
        hotspotSourceMatrix(source_matrix_a, source_matrix_b, native_hotspot_camera_skid_stop_index),
        hotspot_camera_skid_stop_local,
    );
    runner.camera_hotspots_world.camera_slug_death = transformLocalPointByMatrix(
        hotspotSourceMatrix(source_matrix_a, source_matrix_b, native_hotspot_camera_slug_death_index),
        hotspot_camera_slug_death_local,
    );
    runner.camera_hotspots_world.camera_intro_talk = transformLocalPointByMatrix(
        hotspotSourceMatrix(source_matrix_a, source_matrix_b, native_hotspot_camera_intro_talk_index),
        hotspot_camera_intro_talk_local,
    );
}

pub fn cutsceneTargetPoint(runner: anytype, preview: *const track.LoadedLevelPreview) rl.Vector3 {
    return playerWorldPosition(runner, preview);
}

pub fn cutsceneLookAtMatrix(runner: anytype, preview: *const track.LoadedLevelPreview, position: rl.Vector3) rl.Matrix {
    return lookAtPoint(
        cameraMatrixWithPosition(cameraman_identity_matrix, position),
        cutsceneTargetPoint(runner, preview),
        cameraHotspotSourceFrameA(runner, preview).up,
    );
}

pub fn introCutsceneHoldMatrix(runner: anytype, preview: *const track.LoadedLevelPreview) rl.Matrix {
    return cutsceneLookAtMatrix(runner, preview, runner.camera_hotspots_world.camera_intro_talk);
}

pub fn introCutsceneBlendMatrix(runner: anytype, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
    const alpha = std.math.sin(progress * (std.math.pi / 2.0));
    return linearInterpolateCameraMatrices(
        cutsceneLookAtMatrix(runner, preview, runner.camera_hotspots_world.camera_intro_talk),
        runner.cameraman.live_matrix,
        alpha,
    );
}

pub fn completionCutsceneBlendPosition(runner: anytype, progress: f32) rl.Vector3 {
    var position = lerpVector3(
        runner.camera_hotspots_world.camera_skid_stop,
        runner.camera_hotspots_world.camera_intro_talk,
        progress,
    );
    position.x -= std.math.sin(progress * std.math.pi) * completion_cutscene_x_offset;
    return position;
}

pub fn completionCutsceneBlendMatrix(runner: anytype, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
    const alpha = std.math.sin(progress * (std.math.pi / 2.0));
    return linearInterpolateCameraMatrices(
        runner.cameraman.live_matrix,
        cutsceneLookAtMatrix(runner, preview, completionCutsceneBlendPosition(runner, progress)),
        alpha,
    );
}

pub fn completionCutsceneFixedMatrix(runner: anytype, preview: *const track.LoadedLevelPreview) rl.Matrix {
    return cutsceneLookAtMatrix(runner, preview, runner.camera_hotspots_world.camera_intro_talk);
}

pub fn deathCutsceneBlendPosition(runner: anytype, progress: f32) rl.Vector3 {
    var position = runner.camera_hotspots_world.camera_intro_talk;
    position.x += std.math.sin(progress * std.math.pi) * death_cutscene_x_offset;
    position.y = @max(position.y, death_cutscene_y_floor);
    return position;
}

pub fn deathCutsceneBlendMatrix(runner: anytype, preview: *const track.LoadedLevelPreview, progress: f32) rl.Matrix {
    const alpha = std.math.sin(progress * (std.math.pi / 2.0));
    return linearInterpolateCameraMatrices(
        runner.cameraman.live_matrix,
        cutsceneLookAtMatrix(runner, preview, deathCutsceneBlendPosition(runner, progress)),
        alpha,
    );
}

pub fn deathCutsceneFixedMatrix(runner: anytype, preview: *const track.LoadedLevelPreview) rl.Matrix {
    return cutsceneLookAtMatrix(runner, preview, deathCutsceneBlendPosition(runner, 0.0));
}

fn progressForTicks(ticks: u16, total_ticks: u16) f32 {
    if (total_ticks == 0) return 1.0;
    return std.math.clamp(@as(f32, @floatFromInt(ticks)) / @as(f32, @floatFromInt(total_ticks)), 0.0, 1.0);
}

pub fn updateRunnerCutsceneCamera(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (preview.total_rows == 0 or runner.cutscene.camera.state == .none) return;

    while (true) {
        switch (runner.cutscene.camera.state) {
            .intro_arm => {
                runner.cutscene.camera.snap_next = true;
                runner.cutscene.camera.ticks = 0;
                runner.cutscene.ticks = 0;
                runner.cutscene.camera.state = .intro_hold;
                continue;
            },
            .intro_hold => {
                runner.cutscene.camera.matrix = introCutsceneHoldMatrix(runner, preview);
                runner.cutscene.camera.ticks +|= 1;
                runner.cutscene.ticks = @min(runner.cutscene.ticks +| 1, intro_cutscene_duration_ticks);
                if (runner.cutscene.camera.ticks >= intro_cutscene_hold_ticks) {
                    runner.cutscene.camera.state = .intro_blend;
                    runner.cutscene.camera.ticks = 0;
                }
                break;
            },
            .intro_blend => {
                const progress = progressForTicks(runner.cutscene.camera.ticks, intro_cutscene_blend_ticks);
                runner.cutscene.camera.matrix = introCutsceneBlendMatrix(runner, preview, progress);
                runner.cutscene.camera.ticks +|= 1;
                runner.cutscene.ticks = @min(runner.cutscene.ticks +| 1, intro_cutscene_duration_ticks);
                if (runner.cutscene.camera.ticks >= intro_cutscene_blend_ticks) {
                    runner.cutscene.camera.state = .intro_release;
                    runner.cutscene.camera.ticks = 0;
                }
                break;
            },
            .intro_release => {
                if (runner.cutscene.camera.ticks == 0) {
                    runner.cutscene.camera.matrix = runner.cameraman.live_matrix;
                    runner.cutscene.camera.ticks = 1;
                } else {
                    runner.clearCutscene();
                }
                break;
            },
            .completion_arm => {
                runner.cutscene.camera.snap_next = true;
                runner.cutscene.camera.ticks = 0;
                runner.cutscene.camera.state = .completion_blend;
                continue;
            },
            .completion_blend => {
                const progress = progressForTicks(runner.cutscene.camera.ticks, completion_cutscene_blend_ticks);
                runner.cutscene.camera.matrix = completionCutsceneBlendMatrix(runner, preview, progress);
                runner.cutscene.camera.ticks +|= 1;
                if (runner.cutscene.camera.ticks >= completion_cutscene_blend_ticks) {
                    runner.cutscene.camera.state = .completion_hold;
                }
                break;
            },
            .completion_hold => {
                runner.cutscene.camera.matrix = completionCutsceneFixedMatrix(runner, preview);
                break;
            },
            .death_arm => {
                runner.cutscene.camera.snap_next = true;
                runner.cutscene.camera.ticks = 0;
                runner.cutscene.camera.state = .death_blend;
                continue;
            },
            .death_blend => {
                const progress = progressForTicks(runner.cutscene.camera.ticks, death_cutscene_blend_ticks);
                runner.cutscene.camera.matrix = deathCutsceneBlendMatrix(runner, preview, progress);
                runner.cutscene.camera.ticks +|= 1;
                if (runner.cutscene.camera.ticks >= death_cutscene_blend_ticks) {
                    runner.cutscene.camera.state = .death_hold;
                }
                break;
            },
            .death_hold => {
                runner.cutscene.camera.matrix = deathCutsceneFixedMatrix(runner, preview);
                break;
            },
            else => {
                runner.cutscene.camera.state = .none;
                break;
            },
        }
        break;
    }
}

pub fn updateRunnerCameraman(runner: anytype, preview: *const track.LoadedLevelPreview) void {
    if (preview.total_rows == 0) {
        runner.cameraman = .{};
        return;
    }

    const desired_fov = cameramanDesiredFovDegrees(runner, preview);
    runner.cameraman.fov_degrees += (desired_fov - runner.cameraman.fov_degrees) * cameraman_fov_blend;

    const anchor_x = runner.cached_camera_target_world.x;
    const anchor_y = runner.cached_camera_target_world.y;
    const anchor_z = runner.cached_camera_target_world.z;
    const progress_blend = cameramanProgressBlend(runner, preview);
    const vertical_lift = cameramanVerticalLiftFromCachedTarget(anchor_y, progress_blend);
    const anchor_pitch_radians = cameramanPitchRadiansFromCachedTarget(anchor_y);
    const intro_pitch_radians = (1.0 - progress_blend) * 0.8725;
    const lateral_roll_radians = anchor_x * (-8.0 * 0.0174499992 * 0.170000002);
    const lane_lean_roll_radians =
        (0.5 - (std.math.cos(runner.attachment.lane_lean.progress * std.math.pi) * 0.5)) *
        runner.attachment.lane_lean.amplitude *
        std.math.tau;
    runner.cameraman.attachment_lift_envelope = cameramanAttachmentLiftEnvelope(runner, preview);
    runner.cameraman.smoothed_attachment_lift_envelope +=
        (runner.cameraman.attachment_lift_envelope - runner.cameraman.smoothed_attachment_lift_envelope) * cameraman_lift_blend;

    var desired_transform = buildNormalCameramanTransform(
        anchor_x * 0.4,
        cameraman_base_translation_y,
        cameraman_base_translation_z,
        intro_pitch_radians,
        anchor_pitch_radians,
    );
    desired_transform.position.y += vertical_lift + (runner.cameraman.smoothed_attachment_lift_envelope * anchor_y);
    desired_transform.position.x += anchor_x * cameraman_lateral_follow_scale;
    desired_transform.position.z += anchor_z + 0.4;
    desired_transform = rotateCameraTransformWorldZ(desired_transform, lane_lean_roll_radians + lateral_roll_radians);
    if (runner.attachment.follow.active) {
        desired_transform = rotateCameraTransformLocalZ(desired_transform, runner.attachment.camera.orientation_a);
        desired_transform = rotateCameraTransformWorldZ(desired_transform, runner.attachment.camera.orientation_b);
    }
    if (runner.attachment.exit.pending) {
        desired_transform = rotateCameraTransformWorldZ(desired_transform, runner.attachment.exit.post_follow_value_a);
    }
    desired_transform = rotateCameraTransformWorldZ(desired_transform, runner.attachment.camera.heading_roll);

    const desired_matrix = cameraMatrixFromTransform(desired_transform);
    if (runner.cameraman.desired_matrix.m15 == 1.0 and
        runner.cameraman.desired_matrix.m0 == 1.0 and
        runner.cameraman.desired_matrix.m5 == 1.0 and
        runner.cameraman.desired_matrix.m10 == 1.0 and
        runner.cameraman.desired_matrix.m12 == 0.0 and
        runner.cameraman.desired_matrix.m13 == 0.0 and
        runner.cameraman.desired_matrix.m14 == 0.0 and
        runner.tick_count == 0)
    {
        runner.cameraman.live_matrix = desired_matrix;
        runner.cameraman.desired_matrix = desired_matrix;
        runner.cameraman.previous_desired_matrix = desired_matrix;
        runner.cameraman.snap_next = false;
        return;
    }

    var previous_desired_matrix = runner.cameraman.previous_desired_matrix;
    previous_desired_matrix.m14 = clampedPreviousDesiredCameraZ(desired_matrix.m14, previous_desired_matrix.m14);

    runner.cameraman.live_matrix = linearInterpolateCameraMatrices(
        previous_desired_matrix,
        desired_matrix,
        cameramanMatrixBlendFactor(runner),
    );
    runner.cameraman.desired_matrix = desired_matrix;
    runner.cameraman.previous_desired_matrix = runner.cameraman.desired_matrix;
}
