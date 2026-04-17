const std = @import("std");

const io = std.Options.debug_io;

pub const default_root_path = "artifacts/runtime";
pub const config_file_name = "SnailMail.cfg";

pub const FileKind = enum {
    config,
    score_a,
    score_b,
    score_c,
};

pub fn ensureRootExists(root_path: []const u8) !void {
    try std.Io.Dir.cwd().createDirPath(io, root_path);
}

pub fn fileName(kind: FileKind) []const u8 {
    return switch (kind) {
        .config => config_file_name,
        .score_a => "ScoreA.dat",
        .score_b => "ScoreB.dat",
        .score_c => "ScoreC.dat",
    };
}

pub fn filePath(buffer: []u8, root_path: []const u8, kind: FileKind) ![]const u8 {
    const normalized_root = trimRight(u8, root_path, "/\\");
    if (normalized_root.len == 0) return fileName(kind);
    return std.fmt.bufPrint(buffer, "{s}/{s}", .{ normalized_root, fileName(kind) });
}

fn trimRight(comptime T: type, slice: []const T, values_to_strip: []const T) []const T {
    var end = slice.len;
    while (end > 0) : (end -= 1) {
        if (std.mem.indexOfScalar(T, values_to_strip, slice[end - 1]) == null) break;
    }
    return slice[0..end];
}

test "runtime file paths default to artifacts runtime" {
    var buffer: [128]u8 = undefined;
    try std.testing.expectEqualStrings("artifacts/runtime/SnailMail.cfg", try filePath(&buffer, default_root_path, .config));
    try std.testing.expectEqualStrings("artifacts/runtime/ScoreA.dat", try filePath(&buffer, default_root_path, .score_a));
}

test "runtime file path trims trailing separators" {
    var buffer: [128]u8 = undefined;
    try std.testing.expectEqualStrings("custom/runtime/ScoreC.dat", try filePath(&buffer, "custom/runtime/", .score_c));
    try std.testing.expectEqualStrings("custom/runtime/ScoreB.dat", try filePath(&buffer, "custom/runtime\\", .score_b));
}
