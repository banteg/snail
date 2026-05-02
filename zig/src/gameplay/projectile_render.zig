const std = @import("std");
const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const object = @import("../object.zig");
const render_blend = @import("../render_blend.zig");
const x2 = @import("../x2.zig");
const model_render = @import("model_render.zig");

const io = std.Options.debug_io;
const native_vapour_trail_width = 0.16;

pub const Resources = struct {
    lazer_object: *const object.LoadedObject,
    vapour_lazer_object: *const object.LoadedObject,
    rocket_model: *const x2.Uploaded,
};

pub fn draw(resources: Resources, projectile: gameplay.Projectile) void {
    const forward = model_render.normalizeVector3(.{
        .x = projectile.dir_x,
        .y = projectile.dir_y,
        .z = projectile.dir_z,
    });
    var up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    if (@abs(model_render.dotVector3(forward, up)) > 0.95) {
        up = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    }

    var right = model_render.crossVector3(up, forward);
    if (model_render.vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = model_render.normalizeVector3(right);
    }
    const corrected_up = model_render.normalizeVector3(model_render.crossVector3(forward, right));
    const position: rl.Vector3 = .{
        .x = projectile.world_x,
        .y = projectile.world_y,
        .z = projectile.world_z,
    };
    const world_transform = model_render.transformFromBasis(position, right, corrected_up, forward);

    switch (projectile.kind) {
        .turbo => return,
        .laser => {
            if (drawVapourTrail(resources, projectile, right)) return;
            drawObjectProjectile(
                resources.lazer_object,
                world_transform,
                0.22,
                .{ .r = 180, .g = 255, .b = 255, .a = 236 },
            );
        },
        .sub_lazer => {
            if (drawVapourTrail(resources, projectile, right)) return;
            drawObjectProjectile(
                resources.lazer_object,
                world_transform,
                0.18,
                .{ .r = 255, .g = 136, .b = 96, .a = 236 },
            );
        },
        .rocket => {
            model_render.drawUploadedModel(
                resources.rocket_model.*,
                position,
                right,
                corrected_up,
                forward,
                .{ .x = 0.16, .y = 0.16, .z = 0.16 },
                null,
            );
        },
    }
}

fn activeLaserProjectileObject(resources: Resources) *const object.LoadedObject {
    return resources.vapour_lazer_object;
}

fn drawObjectProjectile(
    loaded_object: *const object.LoadedObject,
    world_transform: rl.Matrix,
    scale_factor: f32,
    tint: rl.Color,
) void {
    const offset = rl.Matrix.translate(
        -loaded_object.center.x,
        -loaded_object.center.y,
        -loaded_object.center.z,
    );
    const scale = rl.Matrix.scale(scale_factor, scale_factor, scale_factor);
    loaded_object.drawTintedEx(world_transform.multiply(offset).multiply(scale), tint);
}

fn drawVapourTrail(resources: Resources, projectile: gameplay.Projectile, right: rl.Vector3) bool {
    if (projectile.trail_count < 2) return false;
    const texture = vapourTrailTexture(resources) orelse return false;

    render_blend.beginAlphaPreservingFramebufferAlpha();
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);

    const segment_count: usize = @intCast(projectile.trail_count - 1);
    for (0..segment_count) |index| {
        const start = pointToVector(projectile.trail_points[index]);
        const end = pointToVector(projectile.trail_points[index + 1]);
        const start_v, const end_v = nativeTrailVRange(index, segment_count);
        emitTrailSegment(start, end, right, native_vapour_trail_width, start_v, end_v);
    }
    rl.gl.rlEnd();
    rl.gl.rlDrawRenderBatchActive();
    return true;
}

fn vapourTrailTexture(resources: Resources) ?rl.Texture2D {
    const loaded_object = activeLaserProjectileObject(resources);
    for (loaded_object.submeshes) |submesh| {
        if (submesh.texture) |loaded_texture| return loaded_texture.texture;
    }
    return null;
}

fn pointToVector(point: gameplay.Projectile.TrailPoint) rl.Vector3 {
    return .{ .x = point.x, .y = point.y, .z = point.z };
}

fn nativeTrailVRange(segment_index: usize, segment_count: usize) struct { f32, f32 } {
    if (segment_count <= 1) return .{ 0.0, 1.0 };
    if (segment_index == 0) return .{ 0.0, 0.5 };
    if (segment_index + 1 == segment_count) return .{ 0.5, 1.0 };
    return .{ 0.5, 0.5 };
}

fn emitTrailSegment(
    start: rl.Vector3,
    end: rl.Vector3,
    right: rl.Vector3,
    half_width: f32,
    start_v: f32,
    end_v: f32,
) void {
    const offset = model_render.scaleVector3(right, half_width);
    const start_left = model_render.addVector3(start, offset);
    const start_right = model_render.addVector3(start, model_render.scaleVector3(offset, -1.0));
    const end_left = model_render.addVector3(end, offset);
    const end_right = model_render.addVector3(end, model_render.scaleVector3(offset, -1.0));

    rl.gl.rlColor4ub(255, 255, 255, 252);
    rl.gl.rlTexCoord2f(0.0, start_v);
    rl.gl.rlVertex3f(start_left.x, start_left.y, start_left.z);
    rl.gl.rlTexCoord2f(1.0, start_v);
    rl.gl.rlVertex3f(start_right.x, start_right.y, start_right.z);
    rl.gl.rlTexCoord2f(1.0, end_v);
    rl.gl.rlVertex3f(end_right.x, end_right.y, end_right.z);
    rl.gl.rlTexCoord2f(0.0, end_v);
    rl.gl.rlVertex3f(end_left.x, end_left.y, end_left.z);
}

test "laser projectile rendering prefers the dynamic vapour object" {
    var lazer_object: object.LoadedObject = undefined;
    var vapour_lazer_object: object.LoadedObject = undefined;
    var rocket_model: x2.Uploaded = undefined;

    try std.testing.expect(activeLaserProjectileObject(.{
        .lazer_object = &lazer_object,
        .vapour_lazer_object = &vapour_lazer_object,
        .rocket_model = &rocket_model,
    }) == &vapour_lazer_object);
}

test "vapour trail keeps native endpoint texture ranges" {
    try std.testing.expectEqualDeep(@as(struct { f32, f32 }, .{ 0.0, 1.0 }), nativeTrailVRange(0, 1));
    try std.testing.expectEqualDeep(@as(struct { f32, f32 }, .{ 0.0, 0.5 }), nativeTrailVRange(0, 3));
    try std.testing.expectEqualDeep(@as(struct { f32, f32 }, .{ 0.5, 0.5 }), nativeTrailVRange(1, 3));
    try std.testing.expectEqualDeep(@as(struct { f32, f32 }, .{ 0.5, 1.0 }), nativeTrailVRange(2, 3));
}

test "shipped projectile lazer objects split static and dynamic trail geometry" {
    const lazer_data = try std.Io.Dir.cwd().readFileAlloc(
        io,
        "artifacts/extracted/SnailMail.dat/OBJECTS/LAZER/_OBJECT.TXT",
        std.testing.allocator,
        .limited(1 << 14),
    );
    defer std.testing.allocator.free(lazer_data);
    const vapour_data = try std.Io.Dir.cwd().readFileAlloc(
        io,
        "artifacts/extracted/SnailMail.dat/OBJECTS/VAPOURLAZER/_OBJECT.TXT",
        std.testing.allocator,
        .limited(1 << 14),
    );
    defer std.testing.allocator.free(vapour_data);

    var lazer = try object.parseObject(std.testing.allocator, lazer_data, "OBJECTS/LAZER/_OBJECT.TXT");
    defer lazer.deinit();
    var vapour = try object.parseObject(std.testing.allocator, vapour_data, "OBJECTS/VAPOURLAZER/_OBJECT.TXT");
    defer vapour.deinit();

    try std.testing.expect(objectMaxExtent(&lazer) > 1.0);
    try std.testing.expect(objectMaxExtent(&vapour) <= 0.0001);
    try std.testing.expectEqual(@as(usize, 3), vapour.faces.len);
}

fn objectMaxExtent(parsed: *const object.ParsedObject) f32 {
    if (parsed.vertices.len == 0) return 0.0;
    var min = parsed.vertices[0].position;
    var max = min;
    for (parsed.vertices[1..]) |vertex| {
        min.x = @min(min.x, vertex.position.x);
        min.y = @min(min.y, vertex.position.y);
        min.z = @min(min.z, vertex.position.z);
        max.x = @max(max.x, vertex.position.x);
        max.y = @max(max.y, vertex.position.y);
        max.z = @max(max.z, vertex.position.z);
    }
    return @max(max.x - min.x, @max(max.y - min.y, max.z - min.z));
}
