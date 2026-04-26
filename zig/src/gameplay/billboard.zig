const std = @import("std");
const rl = @import("raylib");

const alpha_cutout_fragment_shader: [:0]const u8 =
    \\#version 330
    \\in vec2 fragTexCoord;
    \\in vec4 fragColor;
    \\uniform sampler2D texture0;
    \\uniform vec4 colDiffuse;
    \\out vec4 finalColor;
    \\
    \\void main() {
    \\    vec4 color = texture(texture0, fragTexCoord) * colDiffuse * fragColor;
    \\    if (color.a <= 0.05) discard;
    \\    finalColor = color;
    \\}
;

pub fn loadAlphaCutoutShader() !rl.Shader {
    return try rl.loadShaderFromMemory(null, alpha_cutout_fragment_shader);
}

const Uv = struct {
    left: f32,
    top: f32,
    right: f32,
    bottom: f32,
};

pub fn drawTexture(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    drawTextureRect(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        camera,
        shader,
        tint,
    );
}

pub fn drawTextureRectRolled(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
) void {
    const forward = normalizeVector3(.{
        .x = camera.target.x - camera.position.x,
        .y = camera.target.y - camera.position.y,
        .z = camera.target.z - camera.position.z,
    });
    var right = crossVector3(forward, camera.up);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    var up = crossVector3(right, forward);
    if (vectorLength(up) <= 0.0001) {
        up = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    } else {
        up = normalizeVector3(up);
    }

    if (@abs(roll_radians) > 0.0001) {
        const roll_cos = std.math.cos(roll_radians);
        const roll_sin = std.math.sin(roll_radians);
        const rotated_right: rl.Vector3 = .{
            .x = (right.x * roll_cos) - (up.x * roll_sin),
            .y = (right.y * roll_cos) - (up.y * roll_sin),
            .z = (right.z * roll_cos) - (up.z * roll_sin),
        };
        const rotated_up: rl.Vector3 = .{
            .x = (right.x * roll_sin) + (up.x * roll_cos),
            .y = (right.y * roll_sin) + (up.y * roll_cos),
            .z = (right.z * roll_sin) + (up.z * roll_cos),
        };
        right = rotated_right;
        up = rotated_up;
    }

    const half_width = width * 0.5;
    const half_height = height * 0.5;
    const top_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) + (up.x * half_height),
        .y = position.y - (right.y * half_width) + (up.y * half_height),
        .z = position.z - (right.z * half_width) + (up.z * half_height),
    };
    const bottom_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) - (up.x * half_height),
        .y = position.y - (right.y * half_width) - (up.y * half_height),
        .z = position.z - (right.z * half_width) - (up.z * half_height),
    };
    const bottom_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) - (up.x * half_height),
        .y = position.y + (right.y * half_width) - (up.y * half_height),
        .z = position.z + (right.z * half_width) - (up.z * half_height),
    };
    const top_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) + (up.x * half_height),
        .y = position.y + (right.y * half_width) + (up.y * half_height),
        .z = position.z + (right.z * half_width) + (up.z * half_height),
    };
    const uv = Uv{
        .left = source.x / @as(f32, @floatFromInt(texture.width)),
        .top = source.y / @as(f32, @floatFromInt(texture.height)),
        .right = (source.x + source.width) / @as(f32, @floatFromInt(texture.width)),
        .bottom = (source.y + source.height) / @as(f32, @floatFromInt(texture.height)),
    };
    drawQuad(texture, top_left, bottom_left, bottom_right, top_right, uv, shader, tint);
}

pub fn drawTextureRect(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    drawTextureRectRolled(texture, source, position, width, height, camera, shader, 0.0, tint);
}

fn drawQuad(
    texture: rl.Texture2D,
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: Uv,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    rl.beginBlendMode(.alpha);
    defer rl.endBlendMode();
    if (shader) |cutout_shader| {
        rl.beginShaderMode(cutout_shader);
        defer rl.endShaderMode();
    }
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();
    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rl.gl.rlTexCoord2f(uv.left, uv.top);
    rl.gl.rlVertex3f(top_left.x, top_left.y, top_left.z);
    rl.gl.rlTexCoord2f(uv.left, uv.bottom);
    rl.gl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);
    rl.gl.rlTexCoord2f(uv.right, uv.bottom);
    rl.gl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);
    rl.gl.rlTexCoord2f(uv.right, uv.top);
    rl.gl.rlVertex3f(top_right.x, top_right.y, top_right.z);
}

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 1.0, .z = 0.0 };
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
