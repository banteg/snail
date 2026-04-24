const std = @import("std");
const rl = @import("raylib");
const ui = @import("../ui.zig");

const fragment_shader: [:0]const u8 =
    \\#version 330
    \\in vec2 fragTexCoord;
    \\in vec4 fragColor;
    \\out vec4 finalColor;
    \\
    \\void main() {
    \\    float coreHalfPixels = fragTexCoord.x;
    \\    float distancePixels = abs(fragTexCoord.y);
    \\    float alpha = 1.0 - smoothstep(coreHalfPixels, coreHalfPixels + 1.0, distancePixels);
    \\    finalColor = vec4(fragColor.rgb, fragColor.a * alpha);
    \\}
;

var shared_shader: ?rl.Shader = null;

const StripCase = struct {
    label: []const u8,
    z: f32,
    color: rl.Color,
    use_shader: bool = false,
    use_default_texture: bool = false,
    reset_shader: bool = false,
};

pub fn draw(state: anytype) void {
    rl.clearBackground(.ray_white);

    const camera = rl.Camera3D{
        .position = .{ .x = 0.0, .y = 4.0, .z = 7.0 },
        .target = .{ .x = 0.0, .y = 0.2, .z = 0.0 },
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .fovy = 45.0,
        .projection = .perspective,
    };

    camera.begin();
    rl.drawGrid(12, 0.5);
    rl.drawCube(.{ .x = 0.0, .y = 0.25, .z = -1.2 }, 1.0, 0.5, 0.7, .light_gray);
    rl.drawCubeWires(.{ .x = 0.0, .y = 0.25, .z = -1.2 }, 1.0, 0.5, 0.7, .dark_gray);

    drawCylinderReference(.{ .x = -2.0, .y = 1.05, .z = 1.8 }, .{ .x = 2.0, .y = 1.05, .z = 1.8 }, .green);
    drawHardcodedQuad();
    drawStrip(camera, .{ .label = "rlgl texture 0, default shader", .z = 1.1, .color = .red });
    drawStrip(camera, .{ .label = "rlgl default texture, default shader", .z = 0.4, .color = .blue, .use_default_texture = true });
    drawStrip(camera, .{ .label = "rlgl default texture, toon fragment shader", .z = -0.3, .color = .black, .use_default_texture = true, .use_shader = true });
    drawStrip(camera, .{ .label = "rlgl after explicit shader reset", .z = -1.0, .color = .purple, .use_default_texture = true, .reset_shader = true });

    rl.endMode3D();

    drawText(state, "toon outline lab", 24, 24, 28, .black);
    drawText(state, "green cylinder is the known-visible baseline; colored strips isolate rlgl texture/shader state.", 24, 58, 18, .dark_gray);
    drawText(state, "A missing row means that state combination cannot be trusted for the game outline pass.", 24, 82, 18, .dark_gray);

    drawLabel(state, "known visible cylinder", 28, 186, .green);
    drawLabel(state, "hardcoded rlgl triangles", 28, 230, .orange);
    drawLabel(state, "texture 0 + default shader", 28, 265, .red);
    drawLabel(state, "default texture + default shader", 28, 340, .blue);
    drawLabel(state, "default texture + toon shader", 28, 414, .black);
    drawLabel(state, "explicit shader reset + default texture", 28, 490, .purple);
}

fn drawCylinderReference(start: rl.Vector3, end: rl.Vector3, color: rl.Color) void {
    rl.drawCylinderEx(start, end, 0.035, 0.035, 12, color);
}

fn drawHardcodedQuad() void {
    rl.gl.rlDrawRenderBatchActive();
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    rl.gl.rlDisableDepthTest();
    defer rl.gl.rlEnableDepthTest();
    rl.gl.rlSetTexture(rl.gl.rlGetTextureIdDefault());
    defer rl.gl.rlSetTexture(0);
    rl.gl.rlBegin(rl.gl.rl_triangles);
    defer rl.gl.rlEnd();
    rl.gl.rlColor4ub(255, 165, 0, 255);
    rl.gl.rlNormal3f(0.0, 0.0, 1.0);
    rl.gl.rlTexCoord2f(0.0, 0.0);
    rl.gl.rlVertex3f(-2.0, 1.2, 1.45);
    rl.gl.rlTexCoord2f(1.0, 0.0);
    rl.gl.rlVertex3f(2.0, 1.2, 1.45);
    rl.gl.rlTexCoord2f(1.0, 1.0);
    rl.gl.rlVertex3f(2.0, 0.9, 1.45);
    rl.gl.rlTexCoord2f(0.0, 0.0);
    rl.gl.rlVertex3f(-2.0, 1.2, 1.45);
    rl.gl.rlTexCoord2f(1.0, 1.0);
    rl.gl.rlVertex3f(2.0, 0.9, 1.45);
    rl.gl.rlTexCoord2f(0.0, 1.0);
    rl.gl.rlVertex3f(-2.0, 0.9, 1.45);
    rl.gl.rlDrawRenderBatchActive();
}

fn drawStrip(camera: rl.Camera3D, case: StripCase) void {
    const start = rl.Vector3{ .x = -2.0, .y = 1.05, .z = case.z };
    const end = rl.Vector3{ .x = 2.0, .y = 1.05, .z = case.z };
    const side = stripSide(start, end, camera) orelse return;
    const midpoint = scale(add(start, end), 0.5);
    const half_width_world = 20.0 * worldUnitsPerPixelAtPoint(camera, midpoint);

    rl.gl.rlDrawRenderBatchActive();
    if (case.reset_shader) {
        rl.gl.rlDisableShader();
    }
    if (case.use_shader) {
        if (ensureShader()) |shader| {
            rl.beginShaderMode(shader);
            defer rl.endShaderMode();
        }
    }

    rl.beginBlendMode(.alpha);
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthTest();
    defer rl.gl.rlEnableDepthTest();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    if (case.use_default_texture) {
        rl.gl.rlSetTexture(rl.gl.rlGetTextureIdDefault());
    } else {
        rl.gl.rlSetTexture(0);
    }
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_triangles);
    defer rl.gl.rlEnd();
    emitStrip(start, end, side, half_width_world, case.color);
    rl.gl.rlDrawRenderBatchActive();
}

fn emitStrip(start: rl.Vector3, end: rl.Vector3, side: rl.Vector3, half_width_world: f32, color: rl.Color) void {
    const a0 = addScaled(start, side, -half_width_world);
    const b0 = addScaled(end, side, -half_width_world);
    const b1 = addScaled(end, side, half_width_world);
    const a1 = addScaled(start, side, half_width_world);
    const core_half_pixels: f32 = 10.0;

    rl.gl.rlColor4ub(color.r, color.g, color.b, color.a);
    rl.gl.rlNormal3f(0.0, 0.0, 1.0);
    rl.gl.rlTexCoord2f(core_half_pixels, -20.0);
    rl.gl.rlVertex3f(a0.x, a0.y, a0.z);
    rl.gl.rlTexCoord2f(core_half_pixels, -20.0);
    rl.gl.rlVertex3f(b0.x, b0.y, b0.z);
    rl.gl.rlTexCoord2f(core_half_pixels, 20.0);
    rl.gl.rlVertex3f(b1.x, b1.y, b1.z);
    rl.gl.rlTexCoord2f(core_half_pixels, -20.0);
    rl.gl.rlVertex3f(a0.x, a0.y, a0.z);
    rl.gl.rlTexCoord2f(core_half_pixels, 20.0);
    rl.gl.rlVertex3f(b1.x, b1.y, b1.z);
    rl.gl.rlTexCoord2f(core_half_pixels, 20.0);
    rl.gl.rlVertex3f(a1.x, a1.y, a1.z);
}

fn ensureShader() ?rl.Shader {
    if (shared_shader) |shader| return shader;
    const shader = rl.loadShaderFromMemory(null, fragment_shader) catch return null;
    shared_shader = shader;
    return shader;
}

fn stripSide(start: rl.Vector3, end: rl.Vector3, camera: rl.Camera3D) ?rl.Vector3 {
    const line_direction = normalize(subtract(end, start));
    if (length(line_direction) <= 0.0001) return null;
    const midpoint = scale(add(start, end), 0.5);
    const view_direction = normalize(subtract(camera.position, midpoint));
    const side = normalize(cross(line_direction, view_direction));
    if (length(side) <= 0.0001) return null;
    return side;
}

fn worldUnitsPerPixelAtPoint(camera: rl.Camera3D, point: rl.Vector3) f32 {
    const screen_height = @max(rl.getScreenHeight(), 1);
    const screen_height_float: f32 = @floatFromInt(screen_height);
    const distance = @max(length(subtract(camera.position, point)), 0.001);
    const fovy_radians = camera.fovy * std.math.pi / 180.0;
    return (2.0 * distance * @tan(fovy_radians * 0.5)) / screen_height_float;
}

fn add(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{ .x = lhs.x + rhs.x, .y = lhs.y + rhs.y, .z = lhs.z + rhs.z };
}

fn subtract(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{ .x = lhs.x - rhs.x, .y = lhs.y - rhs.y, .z = lhs.z - rhs.z };
}

fn scale(value: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{ .x = value.x * scalar, .y = value.y * scalar, .z = value.z * scalar };
}

fn addScaled(lhs: rl.Vector3, rhs: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{ .x = lhs.x + rhs.x * scalar, .y = lhs.y + rhs.y * scalar, .z = lhs.z + rhs.z * scalar };
}

fn cross(lhs: rl.Vector3, rhs: rl.Vector3) rl.Vector3 {
    return .{
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x,
    };
}

fn length(value: rl.Vector3) f32 {
    return std.math.sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
}

fn normalize(value: rl.Vector3) rl.Vector3 {
    const value_length = length(value);
    if (value_length <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 0.0 };
    return .{ .x = value.x / value_length, .y = value.y / value_length, .z = value.z / value_length };
}

fn drawText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    ui.drawText(.{ .font = &state.ui_font }, text, x, y, font_size, color);
}

fn drawLabel(state: anytype, text: []const u8, x: i32, y: i32, color: rl.Color) void {
    rl.drawRectangle(x, y + 6, 18, 6, color);
    drawText(state, text, x + 28, y, 18, .dark_gray);
}
