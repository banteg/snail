const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");

pub const texture_path = "SPRITES/LOADING.TGA";
pub const bar_texture_path = "SPRITES/LOADINGBARON.TGA";

const base_width: f32 = 640.0;
const base_height: f32 = 480.0;
const bar_origin_x: f32 = 192.0;
const bar_origin_y: f32 = 289.0;
const bar_width: f32 = 256.0;
const bar_height: f32 = 32.0;

pub const Layout = struct {
    x: f32,
    y: f32,
    width: f32,
    height: f32,
    scale: f32,

    pub fn mapRect(self: Layout, local_x: f32, local_y: f32, local_width: f32, local_height: f32) rl.Rectangle {
        return .{
            .x = self.x + local_x * self.scale,
            .y = self.y + local_y * self.scale,
            .width = local_width * self.scale,
            .height = local_height * self.scale,
        };
    }
};

pub const Loaded = struct {
    background_texture: assets.LoadedTexture,
    bar_texture: assets.LoadedTexture,

    pub fn load(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !Loaded {
        return .{
            .background_texture = try catalog.loadTextureByPath(allocator, texture_path),
            .bar_texture = try catalog.loadTextureByPath(allocator, bar_texture_path),
        };
    }

    pub fn deinit(self: *Loaded) void {
        self.bar_texture.unload();
        self.background_texture.unload();
    }

    pub fn fittedLayout(self: *const Loaded, bounds: rl.Rectangle) Layout {
        _ = self;
        const scale = @min(bounds.width / base_width, bounds.height / base_height);
        const width = base_width * scale;
        const height = base_height * scale;
        return .{
            .x = bounds.x + (bounds.width - width) * 0.5,
            .y = bounds.y + (bounds.height - height) * 0.5,
            .width = width,
            .height = height,
            .scale = scale,
        };
    }

    // PORT(verified): the shipped loader draws Loading.tga full-screen and clips
    // LoadingBarOn.tga into the recovered 192,289 -> 448,321 window, including
    // the near-complete stall where the bar only reaches full width at the end.
    // Evidence: sub_418b50 and sub_418e80.
    pub fn draw(self: *const Loaded, bounds: rl.Rectangle, progress: f32) void {
        const layout = self.fittedLayout(bounds);
        rl.drawRectangleRec(bounds, .black);
        drawTextureScaled(self.background_texture.texture, layout.mapRect(0.0, 0.0, base_width, base_height));

        const recovered_percent = displayedPercent(progress);
        if (recovered_percent <= 0.0) return;

        const width_ratio = recovered_percent / 100.0;
        const clipped_source_width = @as(f32, @floatFromInt(self.bar_texture.texture.width)) * width_ratio;
        const clipped_dest = layout.mapRect(bar_origin_x, bar_origin_y, bar_width * width_ratio, bar_height);
        rl.drawTexturePro(
            self.bar_texture.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = clipped_source_width,
                .height = @floatFromInt(self.bar_texture.texture.height),
            },
            clipped_dest,
            .{ .x = 0.0, .y = 0.0 },
            0.0,
            .white,
        );
    }
};

fn displayedPercent(progress: f32) f32 {
    const actual_percent = std.math.clamp(progress, 0.0, 1.0) * 100.0;
    if (actual_percent > 98.0) return 100.0;
    return actual_percent * 0.92;
}

fn drawTextureScaled(texture: rl.Texture2D, destination: rl.Rectangle) void {
    rl.drawTexturePro(
        texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(texture.width),
            .height = @floatFromInt(texture.height),
        },
        destination,
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        .white,
    );
}

test "displayed percent stalls until the end" {
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), displayedPercent(0.0), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 46.0), displayedPercent(0.5), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 90.16), displayedPercent(0.98), 0.01);
    try std.testing.expectApproxEqAbs(@as(f32, 100.0), displayedPercent(0.99), 0.001);
}
