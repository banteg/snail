const std = @import("std");
const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const track = @import("../track.zig");

pub const identity_matrix = rl.Matrix{
    .m0 = 1.0,
    .m4 = 0.0,
    .m8 = 0.0,
    .m12 = 0.0,
    .m1 = 0.0,
    .m5 = 1.0,
    .m9 = 0.0,
    .m13 = 3.0,
    .m2 = 0.0,
    .m6 = 0.0,
    .m10 = 1.0,
    .m14 = 0.0,
    .m3 = 0.0,
    .m7 = 0.0,
    .m11 = 0.0,
    .m15 = 1.0,
};

pub const blend_factor: f32 = 0.9;

pub const Source = enum {
    live,
    override,
    identity,
};

pub const State = struct {
    shared_matrix: rl.Matrix = identity_matrix,
    fov_degrees: f32 = 110.0,
    source: Source = .identity,
    snap_next: bool = true,
};

pub const Selection = struct {
    source: Source,
    matrix: rl.Matrix,
    fov_degrees: f32,
    snap_next: bool,
};

pub const WorldTransform = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
};

pub fn transformFromMatrix(matrix: rl.Matrix) WorldTransform {
    return .{
        .position = .{ .x = matrix.m12, .y = matrix.m13, .z = matrix.m14 },
        .right = .{ .x = matrix.m0, .y = matrix.m1, .z = matrix.m2 },
        .up = .{ .x = matrix.m4, .y = matrix.m5, .z = matrix.m6 },
        .forward = .{ .x = matrix.m8, .y = matrix.m9, .z = matrix.m10 },
    };
}

pub fn normalizeTransform(transform: WorldTransform) WorldTransform {
    const forward = normalizeVector3(transform.forward);
    var right = crossVector3(transform.up, forward);
    if (vectorLength(right) <= 0.0001) {
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

pub fn fovDegreesForSource(source: Source, live_fov_degrees: f32) f32 {
    return switch (source) {
        .live => live_fov_degrees,
        .override, .identity => 110.0,
    };
}

pub fn selectionForRunner(runner: *gameplay.Runner) Selection {
    if (runner.cutsceneCameraActive()) {
        return .{
            .source = .override,
            .matrix = runner.cutsceneCameraMatrix(),
            .fov_degrees = fovDegreesForSource(.override, runner.cameramanFovDegrees()),
            .snap_next = runner.takeCutsceneCameraSnap(),
        };
    }
    return .{
        .source = .live,
        .matrix = runner.cameramanMatrix(),
        .fov_degrees = fovDegreesForSource(.live, runner.cameramanFovDegrees()),
        .snap_next = runner.takeCameramanSnap(),
    };
}

pub fn updateState(state: *State, selection: Selection) void {
    if (state.snap_next or selection.snap_next) {
        state.shared_matrix = selection.matrix;
        state.fov_degrees = selection.fov_degrees;
        state.source = selection.source;
        state.snap_next = false;
        return;
    }
    state.shared_matrix = gameplay.linearInterpolateCameraMatrices(state.shared_matrix, selection.matrix, blend_factor);
    state.fov_degrees = selection.fov_degrees;
    state.source = selection.source;
}

pub fn camera3DFromMatrix(matrix: rl.Matrix, fov_degrees: f32) rl.Camera3D {
    const transform = transformFromMatrix(matrix);
    return .{
        .position = transform.position,
        .target = .{
            .x = transform.position.x + transform.forward.x,
            .y = transform.position.y + transform.forward.y,
            .z = transform.position.z + transform.forward.z,
        },
        .up = transform.up,
        .fovy = fov_degrees,
        .projection = .perspective,
    };
}

pub fn levelCamera(state: *const State, loaded_track_preview: *const track.LoadedLevelPreview, fov_degrees: f32) rl.Camera3D {
    if (loaded_track_preview.total_rows == 0) {
        return loaded_track_preview.previewCamera(0.0, 0);
    }
    return camera3DFromMatrix(state.shared_matrix, fov_degrees);
}

pub fn laneCenterTargetForMouseX(
    loaded_track_preview: track.LoadedLevelPreview,
    mouse_x: f32,
    screen_width: f32,
    bounds: track.LaneBounds,
) f32 {
    const width_offset = @as(f32, @floatFromInt(loaded_track_preview.max_width)) * 0.5;
    const authored_mouse_x = authoredMouseXForScreen(mouse_x, screen_width);
    // PORT(verified): native `update_subgoldy` steers toward
    // `clamp((320.0 - mouse_x) * 0.0125, -3.7, 3.7)` in authored mouse space.
    const target_world_x = std.math.clamp((320.0 - authored_mouse_x) * (8.0 / 640.0), -3.7, 3.7);
    const lane_center = width_offset + target_world_x;
    return std.math.clamp(
        lane_center,
        @as(f32, @floatFromInt(bounds.min)) + 0.5,
        @as(f32, @floatFromInt(bounds.max)) + 0.5,
    );
}

pub fn authoredMouseXForScreen(mouse_x: f32, screen_width: f32) f32 {
    if (screen_width <= 1.0) return 320.0;
    return (std.math.clamp(mouse_x, 0.0, screen_width - 1.0) / (screen_width - 1.0)) * 639.0;
}

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}
