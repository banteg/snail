const std = @import("std");
const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const object = @import("../object.zig");
const x2 = @import("../x2.zig");
const model_render = @import("model_render.zig");

const io = std.Options.debug_io;

pub const Resources = struct {
    lazer_object: ?*const object.LoadedObject,
    vapour_lazer_object: ?*const object.LoadedObject,
    rocket_model: ?*const x2.Uploaded,
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
        .turbo => {
            const loaded_object = resources.lazer_object orelse return;
            drawObjectProjectile(
                loaded_object,
                world_transform,
                0.18,
                .{ .r = 170, .g = 220, .b = 255, .a = 232 },
            );
        },
        .laser => {
            const loaded_object = activeLaserProjectileObject(resources) orelse return;
            drawObjectProjectile(
                loaded_object,
                world_transform,
                0.22,
                .{ .r = 180, .g = 255, .b = 255, .a = 236 },
            );
        },
        .enemy_laser => {
            const loaded_object = activeLaserProjectileObject(resources) orelse return;
            drawObjectProjectile(
                loaded_object,
                world_transform,
                0.18,
                .{ .r = 255, .g = 136, .b = 96, .a = 236 },
            );
        },
        .rocket => {
            const model = resources.rocket_model orelse {
                const loaded_object = resources.lazer_object orelse return;
                drawObjectProjectile(
                    loaded_object,
                    world_transform,
                    0.22,
                    .{ .r = 255, .g = 224, .b = 164, .a = 236 },
                );
                return;
            };
            model_render.drawUploadedModel(
                model.*,
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

fn activeLaserProjectileObject(resources: Resources) ?*const object.LoadedObject {
    return resources.lazer_object orelse resources.vapour_lazer_object;
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

test "laser projectile rendering prefers the drawable lazer object" {
    var lazer_object: object.LoadedObject = undefined;
    var vapour_lazer_object: object.LoadedObject = undefined;

    try std.testing.expect(activeLaserProjectileObject(.{
        .lazer_object = &lazer_object,
        .vapour_lazer_object = &vapour_lazer_object,
        .rocket_model = null,
    }) == &lazer_object);
    try std.testing.expect(activeLaserProjectileObject(.{
        .lazer_object = null,
        .vapour_lazer_object = &vapour_lazer_object,
        .rocket_model = null,
    }) == &vapour_lazer_object);
}

test "shipped projectile lazer object is the drawable laser mesh" {
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
