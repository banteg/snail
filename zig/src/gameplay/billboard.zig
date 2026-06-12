const std = @import("std");
const rl = @import("raylib");

const render_blend = @import("../render_blend.zig");

// PORT(partial): native `render_camera` @ 0x411fa0 enables D3D linear range
// fog (`D3DRS_FOGENABLE/FOGCOLOR/FOGVERTEXMODE=LINEAR/FOGSTART/FOGEND/
// RANGEFOGENABLE`) for every gameplay camera pass. The start/end lanes are
// seeded once in `initialize_game_assets_and_world` @ 0x40acf0 (30/50, range
// fog on), and the color comes from the active background script's `Fog:`
// line via `activate_landscape_entry` @ 0x418870.
pub const native_fog_start: f32 = 30.0;
pub const native_fog_end: f32 = 50.0;

pub const FogState = struct {
    enabled: bool = false,
    color: rl.Color = .white,
    camera_position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
};

// Batched/billboard geometry is emitted with world-space vertices, so the
// vertex position doubles as the fog sample point.
const world_space_vertex_shader: [:0]const u8 =
    \\#version 330
    \\in vec3 vertexPosition;
    \\in vec2 vertexTexCoord;
    \\in vec4 vertexColor;
    \\uniform mat4 mvp;
    \\out vec2 fragTexCoord;
    \\out vec4 fragColor;
    \\out vec3 fragWorldPosition;
    \\
    \\void main() {
    \\    fragTexCoord = vertexTexCoord;
    \\    fragColor = vertexColor;
    \\    fragWorldPosition = vertexPosition;
    \\    gl_Position = mvp * vec4(vertexPosition, 1.0);
    \\}
;

// Mesh draws carry a model transform, which raylib binds as `matModel`.
const model_space_vertex_shader: [:0]const u8 =
    \\#version 330
    \\in vec3 vertexPosition;
    \\in vec2 vertexTexCoord;
    \\in vec4 vertexColor;
    \\uniform mat4 mvp;
    \\uniform mat4 matModel;
    \\out vec2 fragTexCoord;
    \\out vec4 fragColor;
    \\out vec3 fragWorldPosition;
    \\
    \\void main() {
    \\    fragTexCoord = vertexTexCoord;
    \\    fragColor = vertexColor;
    \\    fragWorldPosition = vec3(matModel * vec4(vertexPosition, 1.0));
    \\    gl_Position = mvp * vec4(vertexPosition, 1.0);
    \\}
;

// Native D3D linear fog: factor = clamp((end - distance) / (end - start)),
// output = factor * color + (1 - factor) * fogColor, alpha untouched.
// `RANGEFOGENABLE` is set, so distance is the euclidean range from the
// camera rather than view depth.
const alpha_cutout_fragment_shader: [:0]const u8 =
    \\#version 330
    \\in vec2 fragTexCoord;
    \\in vec4 fragColor;
    \\in vec3 fragWorldPosition;
    \\uniform sampler2D texture0;
    \\uniform vec4 colDiffuse;
    \\uniform float alphaCutoff;
    \\uniform float fogEnabled;
    \\uniform vec3 fogColor;
    \\uniform vec2 fogRange;
    \\uniform vec3 fogCameraPosition;
    \\out vec4 finalColor;
    \\
    \\void main() {
    \\    vec4 color = texture(texture0, fragTexCoord) * colDiffuse * fragColor;
    \\    if (color.a <= alphaCutoff) discard;
    \\    float fogDistance = length(fragWorldPosition - fogCameraPosition);
    \\    float fogFactor = clamp((fogRange.y - fogDistance) / (fogRange.y - fogRange.x), 0.0, 1.0);
    \\    fogFactor = mix(1.0, fogFactor, fogEnabled);
    \\    finalColor = vec4(mix(fogColor, color.rgb, fogFactor), color.a);
    \\}
;

pub const default_alpha_cutoff: f32 = 0.05;
pub const soft_alpha_cutoff: f32 = 0.0;
pub const hard_alpha_cutoff: f32 = 0.5;

pub const BlendMode = enum {
    alpha,
    additive,
    src_alpha_src_color,
};

pub fn loadAlphaCutoutShader() !rl.Shader {
    return loadFogAlphaCutoutShader(world_space_vertex_shader);
}

pub fn loadModelAlphaCutoutShader() !rl.Shader {
    return loadFogAlphaCutoutShader(model_space_vertex_shader);
}

fn loadFogAlphaCutoutShader(vertex_shader: [:0]const u8) !rl.Shader {
    const shader = try rl.loadShaderFromMemory(vertex_shader, alpha_cutout_fragment_shader);
    setAlphaCutoff(shader, default_alpha_cutoff);
    configureFog(shader, .{});
    return shader;
}

pub fn configureFog(shader: rl.Shader, fog: FogState) void {
    setShaderFloat(shader, "fogEnabled", if (fog.enabled) 1.0 else 0.0);
    setShaderVec3(shader, "fogColor", .{
        @as(f32, @floatFromInt(fog.color.r)) / 255.0,
        @as(f32, @floatFromInt(fog.color.g)) / 255.0,
        @as(f32, @floatFromInt(fog.color.b)) / 255.0,
    });
    setShaderVec2(shader, "fogRange", .{ native_fog_start, native_fog_end });
    setShaderVec3(shader, "fogCameraPosition", .{
        fog.camera_position.x,
        fog.camera_position.y,
        fog.camera_position.z,
    });
}

fn setShaderFloat(shader: rl.Shader, name: [:0]const u8, value: f32) void {
    const location = rl.getShaderLocation(shader, name);
    if (location < 0) return;
    var scalar = value;
    rl.setShaderValue(shader, location, &scalar, .float);
}

fn setShaderVec2(shader: rl.Shader, name: [:0]const u8, value: [2]f32) void {
    const location = rl.getShaderLocation(shader, name);
    if (location < 0) return;
    var vector = value;
    rl.setShaderValue(shader, location, &vector, .vec2);
}

fn setShaderVec3(shader: rl.Shader, name: [:0]const u8, value: [3]f32) void {
    const location = rl.getShaderLocation(shader, name);
    if (location < 0) return;
    var vector = value;
    rl.setShaderValue(shader, location, &vector, .vec3);
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
    drawTextureBlended(texture, position, width, height, camera, shader, tint, .alpha);
}

pub fn drawTextureBlended(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
    blend_mode: BlendMode,
) void {
    drawTextureRectBlended(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        camera,
        shader,
        tint,
        blend_mode,
    );
}

pub fn drawTextureBlendedAlphaCutoff(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
    blend_mode: BlendMode,
    alpha_cutoff: f32,
) void {
    drawTextureRectRolledBlendedAlphaCutoff(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        camera,
        shader,
        0.0,
        tint,
        blend_mode,
        alpha_cutoff,
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
    drawTextureRectRolledBlendedAlphaCutoff(texture, source, position, width, height, camera, shader, roll_radians, tint, .alpha, default_alpha_cutoff);
}

pub fn drawTextureRectRolledAlphaCutoff(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
    alpha_cutoff: f32,
) void {
    drawTextureRectRolledBlendedAlphaCutoff(texture, source, position, width, height, camera, shader, roll_radians, tint, .alpha, alpha_cutoff);
}

pub fn drawTextureRectRolledBlended(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
    blend_mode: BlendMode,
) void {
    drawTextureRectRolledBlendedAlphaCutoff(texture, source, position, width, height, camera, shader, roll_radians, tint, blend_mode, default_alpha_cutoff);
}

pub fn drawTextureRectRolledBlendedAlphaCutoff(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
    blend_mode: BlendMode,
    alpha_cutoff: f32,
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

    drawTextureRectBasisBlendedAlphaCutoff(texture, source, position, width, height, right, up, shader, tint, blend_mode, alpha_cutoff);
}

pub fn drawTextureRectWorldXyRolledBlendedAlphaCutoff(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
    blend_mode: BlendMode,
    alpha_cutoff: f32,
) void {
    const basis = worldXyRolledBasis(roll_radians);
    drawTextureRectBasisBlendedAlphaCutoff(texture, source, position, width, height, basis.right, basis.up, shader, tint, blend_mode, alpha_cutoff);
}

pub fn drawTextureWorldXyBlendedAlphaCutoff(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    shader: ?rl.Shader,
    tint: rl.Color,
    blend_mode: BlendMode,
    alpha_cutoff: f32,
) void {
    drawTextureRectWorldXyRolledBlendedAlphaCutoff(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        shader,
        0.0,
        tint,
        blend_mode,
        alpha_cutoff,
    );
}

pub fn drawTextureRectBasis(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    right: rl.Vector3,
    up: rl.Vector3,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    drawTextureRectBasisBlendedAlphaCutoff(texture, source, position, width, height, right, up, shader, tint, .alpha, default_alpha_cutoff);
}

pub fn drawTextureRectBasisAlphaCutoff(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    basis_right: rl.Vector3,
    basis_up: rl.Vector3,
    shader: ?rl.Shader,
    tint: rl.Color,
    alpha_cutoff: f32,
) void {
    drawTextureRectBasisBlendedAlphaCutoff(texture, source, position, width, height, basis_right, basis_up, shader, tint, .alpha, alpha_cutoff);
}

pub fn drawTextureRectBasisBlendedAlphaCutoff(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    basis_right: rl.Vector3,
    basis_up: rl.Vector3,
    shader: ?rl.Shader,
    tint: rl.Color,
    blend_mode: BlendMode,
    alpha_cutoff: f32,
) void {
    const right = normalizeVector3(basis_right);
    const up = normalizeVector3(basis_up);
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
    drawQuad(texture, top_left, bottom_left, bottom_right, top_right, uv, shader, tint, blend_mode, alpha_cutoff);
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
    drawTextureRectRolledBlended(texture, source, position, width, height, camera, shader, 0.0, tint, .alpha);
}

pub fn drawTextureRectBlended(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
    blend_mode: BlendMode,
) void {
    drawTextureRectRolledBlended(texture, source, position, width, height, camera, shader, 0.0, tint, blend_mode);
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
    blend_mode: BlendMode,
    alpha_cutoff: f32,
) void {
    switch (blend_mode) {
        .alpha => render_blend.beginAlphaPreservingFramebufferAlpha(),
        .additive => render_blend.beginAdditivePreservingFramebufferAlpha(),
        .src_alpha_src_color => {
            // Native sprite render state 13 maps D3DBLEND_SRCALPHA over
            // D3DBLEND_SRCCOLOR. Explode/slow ring particles use this lane.
            render_blend.beginSrcAlphaSrcColorPreservingFramebufferAlpha();
        },
    }
    defer rl.endBlendMode();
    if (shader) |cutout_shader| {
        setAlphaCutoff(cutout_shader, alpha_cutoff);
        rl.beginShaderMode(cutout_shader);
        defer rl.endShaderMode();
    }
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rl.gl.rlTexCoord2f(uv.left, uv.top);
    rl.gl.rlVertex3f(top_left.x, top_left.y, top_left.z);
    rl.gl.rlTexCoord2f(uv.left, uv.bottom);
    rl.gl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);
    rl.gl.rlTexCoord2f(uv.right, uv.bottom);
    rl.gl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);
    rl.gl.rlTexCoord2f(uv.right, uv.top);
    rl.gl.rlVertex3f(top_right.x, top_right.y, top_right.z);

    rl.gl.rlEnd();
    rl.gl.rlDrawRenderBatchActive();
}

const Basis = struct {
    right: rl.Vector3,
    up: rl.Vector3,
};

// The gameplay camera looks down +Z, so raylib's look-at basis maps world -X
// to screen-right. The world-XY sprite basis mirrors X to match the
// camera-facing billboard basis (`right = forward x up = -X`): the quad winds
// front-facing for the +Z camera (a `right = +X` basis is back-face culled —
// every world-XY sprite was invisible), keeps the texture unmirrored relative
// to the rest of the scene, and rolls the same screen direction as the rolled
// camera-billboard path. Native `draw_sprite_quad` quads are also single-sided
// under D3D's default CCW culling.
fn worldXyRolledBasis(roll_radians: f32) Basis {
    const roll_cos = std.math.cos(roll_radians);
    const roll_sin = std.math.sin(roll_radians);
    return .{
        .right = .{
            .x = -roll_cos,
            .y = roll_sin,
            .z = 0.0,
        },
        .up = .{
            .x = roll_sin,
            .y = roll_cos,
            .z = 0.0,
        },
    };
}

pub fn setAlphaCutoff(shader: rl.Shader, alpha_cutoff: f32) void {
    const location = rl.getShaderLocation(shader, "alphaCutoff");
    if (location < 0) return;
    var cutoff = alpha_cutoff;
    rl.setShaderValue(shader, location, &cutoff, .float);
}

test "world XY rolled basis matches the camera-facing billboard winding" {
    const unrolled = worldXyRolledBasis(0.0);
    try std.testing.expectApproxEqAbs(@as(f32, -1.0), unrolled.right.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), unrolled.right.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), unrolled.right.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), unrolled.up.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), unrolled.up.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), unrolled.up.z, 0.0001);

    const quarter = worldXyRolledBasis(std.math.pi / 2.0);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quarter.right.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), quarter.right.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), quarter.up.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), quarter.up.y, 0.0001);
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
