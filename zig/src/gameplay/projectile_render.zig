const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const object = @import("../object.zig");
const x2 = @import("../x2.zig");
const model_render = @import("model_render.zig");

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
            const loaded_object = resources.vapour_lazer_object orelse resources.lazer_object orelse return;
            drawObjectProjectile(
                loaded_object,
                world_transform,
                0.22,
                .{ .r = 180, .g = 255, .b = 255, .a = 236 },
            );
        },
        .enemy_laser => {
            const loaded_object = resources.vapour_lazer_object orelse resources.lazer_object orelse return;
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
