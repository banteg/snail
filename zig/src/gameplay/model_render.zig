const std = @import("std");
const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const track = @import("../track.zig");
const x2 = @import("../x2.zig");

pub const TurboPose = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    transform: rl.Matrix,
};

const gameplay_turbo_body_height: f32 = 0.02;
const tutorial_click_start_body_height: f32 = 0.08;

pub fn drawUploadedModel(
    model: x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
    tint: ?rl.Color,
) void {
    const transform = uploadedModelTransform(&model, position, right, up, forward, scale);
    if (tint) |tint_color| {
        drawUploadedModelTinted(&model, transform, tint_color);
    } else {
        model.drawEx(transform);
    }
}

pub fn drawUploadedModelWithToonOutline(
    model: *const x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
    camera: rl.Camera3D,
) void {
    const transform = uploadedModelTransform(model, position, right, up, forward, scale);
    model.drawEx(transform);
    model.drawToonOutlineEx(transform, camera, .black);
}

pub fn drawUploadedModelWithToonOutlineEx(
    model: *const x2.Uploaded,
    transform: rl.Matrix,
    camera: rl.Camera3D,
) void {
    model.drawEx(transform);
    model.drawToonOutlineEx(transform, camera, .black);
}

pub fn uploadedModelTransform(
    model: *const x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
) rl.Matrix {
    const world_transform = transformFromBasis(position, right, up, forward);
    const local_offset = rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
    const model_scale = rl.Matrix.scale(scale.x, scale.y, scale.z);
    return world_transform.multiply(local_offset).multiply(model_scale);
}

pub fn drawUploadedModelTinted(model: *const x2.Uploaded, transform: rl.Matrix, tint: rl.Color) void {
    model.drawTintedEx(transform, tint);
}

pub fn turboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) TurboPose {
    const forward = normalizeVector3(runner.worldForward(loaded_track_preview));
    const up = normalizeVector3(runner.worldUp(loaded_track_preview));
    var right = crossVector3(up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    const corrected_up = normalizeVector3(crossVector3(forward, right));
    const position = runner.worldPosition(loaded_track_preview, gameplay_turbo_body_height);
    const world_transform = transformFromBasis(position, right, corrected_up, forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = right,
        .up = corrected_up,
        .forward = forward,
        .transform = world_transform.multiply(local_offset),
    };
}

pub fn tutorialClickStartTurboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) TurboPose {
    const base_pose = turboPose(model, loaded_track_preview, runner);
    const position = runner.worldPosition(loaded_track_preview, tutorial_click_start_body_height);
    const world_transform = transformFromBasis(position, base_pose.right, base_pose.up, base_pose.forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = base_pose.right,
        .up = base_pose.up,
        .forward = base_pose.forward,
        .transform = world_transform.multiply(local_offset),
    };
}

pub fn groundedCharacterModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.min.y,
        -model.bounds.center.z,
    );
}

pub fn centeredModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
}

pub fn offsetPosition(
    origin: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    local_x: f32,
    local_y: f32,
    local_z: f32,
) rl.Vector3 {
    return .{
        .x = origin.x + (right.x * local_x) + (up.x * local_y) + (forward.x * local_z),
        .y = origin.y + (right.y * local_x) + (up.y * local_y) + (forward.y * local_z),
        .z = origin.z + (right.z * local_x) + (up.z * local_y) + (forward.z * local_z),
    };
}

pub fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

pub fn addVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
    };
}

pub fn scaleVector3(v: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{
        .x = v.x * scalar,
        .y = v.y * scalar,
        .z = v.z * scalar,
    };
}

pub fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

pub fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

pub fn lerpVector3(a: rl.Vector3, b: rl.Vector3, t: f32) rl.Vector3 {
    return .{
        .x = std.math.lerp(a.x, b.x, t),
        .y = std.math.lerp(a.y, b.y, t),
        .z = std.math.lerp(a.z, b.z, t),
    };
}

pub fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

pub fn transformFromBasis(position: rl.Vector3, right: rl.Vector3, up: rl.Vector3, forward: rl.Vector3) rl.Matrix {
    return .{
        .m0 = right.x,
        .m4 = up.x,
        .m8 = forward.x,
        .m12 = position.x,
        .m1 = right.y,
        .m5 = up.y,
        .m9 = forward.y,
        .m13 = position.y,
        .m2 = right.z,
        .m6 = up.z,
        .m10 = forward.z,
        .m14 = position.z,
        .m3 = 0.0,
        .m7 = 0.0,
        .m11 = 0.0,
        .m15 = 1.0,
    };
}
