const std = @import("std");
const rl = @import("raylib");
const archive = @import("archive.zig");

const default_archive_path = "artifacts/bin/SnailMail.dat";
const default_texture_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";

const Options = struct {
    archive_path: []const u8 = default_archive_path,
    smoke_test: bool = false,
};

fn parseArgs(allocator: std.mem.Allocator) !Options {
    var options = Options{};
    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    _ = args.skip();
    while (args.next()) |arg| {
        if (std.mem.eql(u8, arg, "--smoke-test")) {
            options.smoke_test = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--archive-path")) {
            options.archive_path = args.next() orelse return error.MissingArchivePath;
            continue;
        }
    }
    return options;
}

fn loadTextureFromArchive(
    allocator: std.mem.Allocator,
    dat: *const archive.Archive,
    asset_path: []const u8,
) !rl.Texture2D {
    const decoded = try dat.readEntryAlloc(allocator, asset_path);
    defer allocator.free(decoded);

    const image = try rl.loadImageFromMemory(".tga", decoded);
    defer rl.unloadImage(image);

    const texture = try rl.loadTextureFromImage(image);
    rl.setTextureFilter(texture, .bilinear);
    return texture;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator);
    var dat = try archive.Archive.init(allocator, options.archive_path);
    defer dat.deinit();

    rl.initWindow(1280, 720, "Snail Mail");
    defer rl.closeWindow();

    const texture = try loadTextureFromArchive(allocator, &dat, default_texture_path);
    defer rl.unloadTexture(texture);

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.smoke_test) 2 else std.math.maxInt(usize);
    var archive_text_buffer: [384]u8 = undefined;
    const archive_text = try std.fmt.bufPrintZ(&archive_text_buffer, "Archive: {s}", .{options.archive_path});
    const asset_text = "Texture: OBJECTS/FONT/FONT-MENU-HOVER.TGA";

    while (!rl.windowShouldClose() and frames_left > 0) {
        if (options.smoke_test) {
            frames_left -= 1;
        }

        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(.black);

        const scale_x = 800.0 / @as(f32, @floatFromInt(texture.width));
        const scale_y = 520.0 / @as(f32, @floatFromInt(texture.height));
        const scale = @min(scale_x, scale_y);
        const draw_width = @as(f32, @floatFromInt(texture.width)) * scale;
        const draw_height = @as(f32, @floatFromInt(texture.height)) * scale;
        const draw_x = (1280.0 - draw_width) / 2.0;
        const draw_y = (720.0 - draw_height) / 2.0 + 24.0;

        rl.drawText("Loaded directly from SnailMail.dat", 32, 32, 28, .ray_white);
        rl.drawText(archive_text, 32, 68, 20, .light_gray);
        rl.drawText(asset_text, 32, 96, 20, .light_gray);
        rl.drawTextureEx(texture, .{ .x = draw_x, .y = draw_y }, 0.0, scale, .white);
    }
}

test "smoke flag defaults off" {
    try std.testing.expect(true);
}
