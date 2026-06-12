//! Mirror of the native tMatrix/tQuaternian interpolation chain.
//!
//! Transcribed from pinned/exported sources (tools/match scratches for
//! linear_interpolate_matrix @ 0x44da90 and interpolate_matrix_rotation
//! @ 0x44d920; decompile exports for the helpers @ 0x44d1a0..0x44d820).
//! Native pose interpolation is rotation-space: relative = invert(from) * to,
//! the relative rotation's axis-angle scaled by alpha, recomposed,
//! premultiplied by `from`, then re-orthogonalized; translation blends
//! linearly. This replaces the runner's per-basis-vector lerp+normalize
//! (invalidation ledger, 2026-06-12).

const std = @import("std");

pub const Vec3 = struct { x: f32 = 0, y: f32 = 0, z: f32 = 0 };

pub const Mat = struct {
    right: Vec3 = .{ .x = 1 },
    up: Vec3 = .{ .y = 1 },
    forward: Vec3 = .{ .z = 1 },
    position: Vec3 = .{},
};

pub const Quat = struct { x: f32 = 0, y: f32 = 0, z: f32 = 0, w: f32 = 1 };
pub const AxisAngle = struct { x: f32 = 0, y: f32 = 0, z: f32 = 0, angle: f32 = 0 };

fn dot(a: Vec3, b: Vec3) f32 {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

fn cross(a: Vec3, b: Vec3) Vec3 {
    return .{ .x = a.y * b.z - a.z * b.y, .y = a.z * b.x - a.x * b.z, .z = a.x * b.y - a.y * b.x };
}

fn normalize(v: Vec3) Vec3 {
    const len = @sqrt(dot(v, v));
    if (len <= 0.0) return v;
    return .{ .x = v.x / len, .y = v.y / len, .z = v.z / len };
}

/// invert_matrix_from_source @ 0x44d330: orthonormal inverse —
/// transposed basis, position = -(p projected onto the source columns).
pub fn invertFromSource(source: Mat) Mat {
    return .{
        .right = .{ .x = source.right.x, .y = source.up.x, .z = source.forward.x },
        .up = .{ .x = source.right.y, .y = source.up.y, .z = source.forward.y },
        .forward = .{ .x = source.right.z, .y = source.up.z, .z = source.forward.z },
        .position = .{
            .x = -(source.position.y * source.right.y + source.position.z * source.right.z + source.position.x * source.right.x),
            .y = -(source.position.y * source.up.y + source.position.z * source.up.z + source.position.x * source.up.x),
            .z = -(source.position.y * source.forward.y + source.position.x * source.forward.x + source.position.z * source.forward.z),
        },
    };
}

/// multiply_matrices row-vector convention: row_i(out) = row_i(a) * B.
pub fn multiply(a: Mat, b: Mat) Mat {
    const rowMul = struct {
        fn apply(row: Vec3, m: Mat) Vec3 {
            return .{
                .x = row.x * m.right.x + row.y * m.up.x + row.z * m.forward.x,
                .y = row.x * m.right.y + row.y * m.up.y + row.z * m.forward.y,
                .z = row.x * m.right.z + row.y * m.up.z + row.z * m.forward.z,
            };
        }
    }.apply;
    const p = rowMul(a.position, b);
    return .{
        .right = rowMul(a.right, b),
        .up = rowMul(a.up, b),
        .forward = rowMul(a.forward, b),
        .position = .{ .x = p.x + b.position.x, .y = p.y + b.position.y, .z = p.z + b.position.z },
    };
}

/// orthogonalize_matrix @ 0x44d3d0: normalize all rows, right = up x forward,
/// forward = right x up — exactly that order.
pub fn orthogonalize(m: Mat) Mat {
    var out = m;
    out.right = normalize(out.right);
    out.up = normalize(out.up);
    out.forward = normalize(out.forward);
    out.right = cross(out.up, out.forward);
    out.forward = cross(out.right, out.up);
    return out;
}

/// initialize_quaternion_from_matrix @ 0x44d5d0 (Shoemake extraction; trace
/// case verified against the export, major-diagonal cases follow it).
pub fn quatFromMatrix(m: Mat) Quat {
    const trace = m.right.x + m.up.y + m.forward.z + 1.0;
    if (trace > 0.000001) {
        const s = 0.5 / @sqrt(trace);
        return .{
            .w = 0.25 / s,
            .x = (m.up.z - m.forward.y) * s,
            .y = (m.forward.x - m.right.z) * s,
            .z = (m.right.y - m.up.x) * s,
        };
    }
    if (m.right.x >= m.up.y and m.right.x >= m.forward.z) {
        const s = 2.0 * @sqrt(@max(0.0, m.right.x + 1.0 - m.up.y - m.forward.z));
        return .{ .x = s * 0.25, .y = (m.up.x + m.right.y) / s, .z = (m.forward.x + m.right.z) / s, .w = (m.up.z - m.forward.y) / s };
    }
    if (m.up.y >= m.forward.z) {
        const s = 2.0 * @sqrt(@max(0.0, m.up.y + 1.0 - m.right.x - m.forward.z));
        return .{ .x = (m.up.x + m.right.y) / s, .y = s * 0.25, .z = (m.forward.y + m.up.z) / s, .w = (m.forward.x + m.right.z) / s };
    }
    const s = 2.0 * @sqrt(@max(0.0, m.forward.z + 1.0 - m.right.x - m.up.y));
    return .{ .x = (m.forward.x + m.right.z) / s, .y = (m.forward.y + m.up.z) / s, .z = s * 0.25, .w = (m.right.y - m.up.x) / s };
}

/// initialize_matrix_from_quaternion @ 0x44d820.
pub fn matrixFromQuat(q: Quat) Mat {
    const xx = q.x * q.x;
    const yy = q.y * q.y;
    const zz = q.z * q.z;
    const xy = q.y * q.x;
    const xz = q.z * q.x;
    const yz = q.z * q.y;
    const wx = q.w * q.x;
    const wy = q.w * q.y;
    const wz = q.w * q.z;
    return .{
        .right = .{ .x = 1.0 - 2.0 * (zz + yy), .y = 2.0 * (xy + wz), .z = 2.0 * (xz - wy) },
        .up = .{ .x = 2.0 * (xy - wz), .y = 1.0 - 2.0 * (zz + xx), .z = 2.0 * (yz + wx) },
        .forward = .{ .x = 2.0 * (xz + wy), .y = 2.0 * (yz - wx), .z = 1.0 - 2.0 * (yy + xx) },
        .position = .{},
    };
}

/// initialize_axis_from_quaternion @ 0x44d580: angle = 2*acos(w).
pub fn axisFromQuat(q: Quat) AxisAngle {
    const half = std.math.acos(std.math.clamp(q.w, -1.0, 1.0));
    const s = @sin(half);
    if (s == 0.0) return .{ .angle = half + half };
    return .{ .x = q.x / s, .y = q.y / s, .z = q.z / s, .angle = half + half };
}

/// initialize_quaternion_from_axis @ 0x44d530.
pub fn quatFromAxis(a: AxisAngle) Quat {
    const half = a.angle * 0.5;
    const s = @sin(half);
    return .{ .x = s * a.x, .y = s * a.y, .z = s * a.z, .w = @cos(half) };
}

/// interpolate_matrix_rotation @ 0x44d920 (pinned 71.9%): epsilon-snap the
/// quaternion's imaginary lanes, scale the axis-angle by alpha, recompose.
/// Zero angle leaves the matrix untouched (native quirk preserved).
pub fn interpolateMatrixRotation(m: Mat, alpha: f32) Mat {
    var q = quatFromMatrix(m);
    if (q.x > -0.001 and q.x < 0.001) q.x = 0.0;
    if (q.y > -0.001 and q.y < 0.001) q.y = 0.0;
    if (q.z > -0.001 and q.z < 0.001) q.z = 0.0;
    if (q.x == 0.0 and q.y == 0.0 and q.z == 0.0) {
        return matrixFromQuat(q);
    }
    var axis = axisFromQuat(q);
    if (axis.angle == 0.0) return m;
    axis.angle *= alpha;
    return matrixFromQuat(quatFromAxis(axis));
}

/// linear_interpolate_matrix @ 0x44da90 (pinned 49.6%): rotation in matrix
/// space, translation linear.
pub fn linearInterpolateMatrix(from: Mat, to: Mat, alpha: f32) Mat {
    var out = invertFromSource(from);
    out = multiply(out, to);
    out = interpolateMatrixRotation(out, alpha);
    out = multiply(from, out);
    out = orthogonalize(out);
    const inv = 1.0 - alpha;
    out.position = .{
        .x = inv * from.position.x + alpha * to.position.x,
        .y = inv * from.position.y + alpha * to.position.y,
        .z = inv * from.position.z + alpha * to.position.z,
    };
    return out;
}

fn rotZ(angle: f32) Mat {
    const c = @cos(angle);
    const s = @sin(angle);
    return .{ .right = .{ .x = c, .y = s }, .up = .{ .x = -s, .y = c }, .forward = .{ .z = 1 } };
}

test "halfway interpolation yields half the rotation angle (constant angular velocity)" {
    const from = Mat{};
    const to = rotZ(1.6);
    const mid = linearInterpolateMatrix(from, to, 0.5);
    // the lerp+normalize model would NOT land on cos(0.8) for this angle
    try std.testing.expectApproxEqAbs(@cos(@as(f32, 0.8)), mid.right.x, 0.001);
    try std.testing.expectApproxEqAbs(@sin(@as(f32, 0.8)), mid.right.y, 0.001);
}

test "interpolation preserves orthonormality and blends translation linearly" {
    var from = rotZ(0.3);
    from.position = .{ .x = 2.0 };
    var to = rotZ(1.1);
    to.position = .{ .x = 4.0, .z = 1.0 };
    const mid = linearInterpolateMatrix(from, to, 0.25);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), dot(mid.right, mid.right), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), dot(mid.right, mid.up), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), mid.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), mid.position.z, 0.0001);
}

test "zero relative rotation leaves the basis untouched" {
    const m = rotZ(0.7);
    const same = linearInterpolateMatrix(m, m, 0.5);
    try std.testing.expectApproxEqAbs(m.right.x, same.right.x, 0.0001);
    try std.testing.expectApproxEqAbs(m.right.y, same.right.y, 0.0001);
}
