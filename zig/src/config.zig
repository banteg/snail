const std = @import("std");
const runtime_state = @import("runtime_state.zig");

pub const byte_len: usize = 0xc4;

const sound_volume_offset = 0x00;
const music_volume_offset = 0x04;
const fullscreen_offset = 0x08;
const legacy_display_mode_offset = 0x1c;
const legacy_display_mode_default: u32 = 0x5fe;
const startup_flag_offset = 0x31;
const gameplay_tuning_offset = 0x34;
const postal_progress_offset = 0xa0;
const challenge_progress_offset = 0xa4;
const runtime_flag_offset = 0xa8;
const camera_tuning_offset = 0xac;

const default_gameplay_tuning = [_]u8{
    0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x3f,
    0x00, 0x00, 0x40, 0x3f,
    0x28, 0x00, 0x00, 0x00,
    0x9a, 0x99, 0x99, 0x3e,
    0x28, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

const default_camera_tuning = [_]u8{
    0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x41,
    0x00, 0x00, 0x20, 0x40,
    0x00, 0x00, 0xc0, 0xbf,
    0x00, 0x00, 0x80, 0xbf,
    0x00,
};

pub const LoadResult = struct {
    blob: Blob,
    loaded_from_file: bool,
};

// PORT(partial): this preserves the full 0xc4-byte SnailMail.cfg blob while only exposing the
// sound volume, music volume, and fullscreen fields we have recovered with confidence so far.
// Evidence: initialize_default_runtime_config, build_frontend_options_menu,
// commit_frontend_options_menu, and apply_audio_config_volumes.
pub const Blob = struct {
    bytes: [byte_len]u8,

    pub fn initDefault() Blob {
        var blob = Blob{ .bytes = [_]u8{0} ** byte_len };
        blob.setSoundVolume(0.6);
        blob.setMusicVolume(0.6);
        blob.setFullscreenEnabled(true);
        writeU32(blob.bytes[legacy_display_mode_offset .. legacy_display_mode_offset + 4], legacy_display_mode_default);
        blob.bytes[startup_flag_offset] = 1;
        @memcpy(blob.bytes[gameplay_tuning_offset .. gameplay_tuning_offset + default_gameplay_tuning.len], &default_gameplay_tuning);
        writeU32(blob.bytes[postal_progress_offset .. postal_progress_offset + 4], 1);
        writeU32(blob.bytes[challenge_progress_offset .. challenge_progress_offset + 4], 1);
        writeU32(blob.bytes[runtime_flag_offset .. runtime_flag_offset + 4], 0);
        @memcpy(blob.bytes[camera_tuning_offset .. camera_tuning_offset + default_camera_tuning.len], &default_camera_tuning);
        return blob;
    }

    pub fn loadFromRuntimeRoot(allocator: std.mem.Allocator, root_path: []const u8) !LoadResult {
        var blob = Blob.initDefault();
        var path_buffer: [std.fs.max_path_bytes]u8 = undefined;
        const path = try runtime_state.filePath(&path_buffer, root_path, .config);
        const bytes = std.fs.cwd().readFileAlloc(allocator, path, byte_len) catch |err| switch (err) {
            error.FileNotFound => {
                return .{
                    .blob = blob,
                    .loaded_from_file = false,
                };
            },
            else => return err,
        };
        defer allocator.free(bytes);

        if (bytes.len > blob.bytes.len) return error.InvalidConfigFile;
        @memcpy(blob.bytes[0..bytes.len], bytes);
        return .{
            .blob = blob,
            .loaded_from_file = true,
        };
    }

    pub fn saveToRuntimeRoot(self: *const Blob, root_path: []const u8) !void {
        try runtime_state.ensureRootExists(root_path);

        var path_buffer: [std.fs.max_path_bytes]u8 = undefined;
        const path = try runtime_state.filePath(&path_buffer, root_path, .config);
        var file = try std.fs.cwd().createFile(path, .{});
        defer file.close();
        try file.writeAll(&self.bytes);
    }

    pub fn soundVolume(self: *const Blob) f32 {
        return clampUnit(readF32(self.bytes[sound_volume_offset .. sound_volume_offset + 4]));
    }

    pub fn setSoundVolume(self: *Blob, value: f32) void {
        writeF32(self.bytes[sound_volume_offset .. sound_volume_offset + 4], clampUnit(value));
    }

    pub fn musicVolume(self: *const Blob) f32 {
        return clampUnit(readF32(self.bytes[music_volume_offset .. music_volume_offset + 4]));
    }

    pub fn setMusicVolume(self: *Blob, value: f32) void {
        writeF32(self.bytes[music_volume_offset .. music_volume_offset + 4], clampUnit(value));
    }

    pub fn fullscreenEnabled(self: *const Blob) bool {
        return self.bytes[fullscreen_offset] != 0;
    }

    pub fn setFullscreenEnabled(self: *Blob, enabled: bool) void {
        self.bytes[fullscreen_offset] = @intFromBool(enabled);
    }
};

fn clampUnit(value: f32) f32 {
    return std.math.clamp(value, 0.0, 1.0);
}

fn readU32(buffer: []const u8) u32 {
    return std.mem.readInt(u32, @as(*const [4]u8, @ptrCast(buffer.ptr)), .little);
}

fn writeU32(buffer: []u8, value: u32) void {
    std.mem.writeInt(u32, buffer[0..4], value, .little);
}

fn readF32(buffer: []const u8) f32 {
    return @bitCast(readU32(buffer));
}

fn writeF32(buffer: []u8, value: f32) void {
    writeU32(buffer, @bitCast(value));
}

test "default config blob matches recovered startup defaults" {
    const blob = Blob.initDefault();

    try std.testing.expectApproxEqAbs(@as(f32, 0.6), blob.soundVolume(), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.6), blob.musicVolume(), 0.0001);
    try std.testing.expect(blob.fullscreenEnabled());
    try std.testing.expectEqual(@as(u32, legacy_display_mode_default), readU32(blob.bytes[legacy_display_mode_offset .. legacy_display_mode_offset + 4]));
    try std.testing.expectEqual(@as(u8, 1), blob.bytes[startup_flag_offset]);
    try std.testing.expectEqualSlices(u8, &default_gameplay_tuning, blob.bytes[gameplay_tuning_offset .. gameplay_tuning_offset + default_gameplay_tuning.len]);
    try std.testing.expectEqual(@as(u32, 1), readU32(blob.bytes[postal_progress_offset .. postal_progress_offset + 4]));
    try std.testing.expectEqual(@as(u32, 1), readU32(blob.bytes[challenge_progress_offset .. challenge_progress_offset + 4]));
    try std.testing.expectEqual(@as(u32, 0), readU32(blob.bytes[runtime_flag_offset .. runtime_flag_offset + 4]));
    try std.testing.expectEqualSlices(u8, &default_camera_tuning, blob.bytes[camera_tuning_offset .. camera_tuning_offset + default_camera_tuning.len]);
}

test "config blob load overlays saved bytes onto recovered defaults" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    try temp_dir.dir.makePath("runtime");
    const config_path = "runtime/SnailMail.cfg";
    var saved = Blob.initDefault();
    saved.setSoundVolume(0.25);
    saved.setMusicVolume(0.75);
    saved.setFullscreenEnabled(false);
    writeU32(saved.bytes[postal_progress_offset .. postal_progress_offset + 4], 7);

    var file = try temp_dir.dir.createFile(config_path, .{});
    defer file.close();
    try file.writeAll(&saved.bytes);

    var previous_dir = try std.fs.cwd().openDir(".", .{});
    defer previous_dir.close();

    try temp_dir.dir.setAsCwd();
    defer previous_dir.setAsCwd() catch unreachable;

    const loaded = try Blob.loadFromRuntimeRoot(std.testing.allocator, "runtime");
    try std.testing.expect(loaded.loaded_from_file);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), loaded.blob.soundVolume(), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.75), loaded.blob.musicVolume(), 0.0001);
    try std.testing.expect(!loaded.blob.fullscreenEnabled());
    try std.testing.expectEqual(@as(u32, 7), readU32(loaded.blob.bytes[postal_progress_offset .. postal_progress_offset + 4]));
    try std.testing.expectEqualSlices(u8, &default_camera_tuning, loaded.blob.bytes[camera_tuning_offset .. camera_tuning_offset + default_camera_tuning.len]);
}

test "config blob save writes the exact raw bytes" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var blob = Blob.initDefault();
    blob.setSoundVolume(0.1);
    blob.setMusicVolume(0.9);
    blob.setFullscreenEnabled(false);

    var previous_dir = try std.fs.cwd().openDir(".", .{});
    defer previous_dir.close();

    try temp_dir.dir.setAsCwd();
    defer previous_dir.setAsCwd() catch unreachable;

    try blob.saveToRuntimeRoot("runtime");
    const bytes = try std.fs.cwd().readFileAlloc(std.testing.allocator, "runtime/SnailMail.cfg", byte_len);
    defer std.testing.allocator.free(bytes);

    try std.testing.expectEqual(@as(usize, byte_len), bytes.len);
    try std.testing.expectEqualSlices(u8, &blob.bytes, bytes);
}
