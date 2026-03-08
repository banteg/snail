const std = @import("std");

test {
    std.testing.refAllDecls(@import("archive.zig"));
    std.testing.refAllDecls(@import("assets.zig"));
    std.testing.refAllDecls(@import("level.zig"));
    std.testing.refAllDecls(@import("main.zig"));
    std.testing.refAllDecls(@import("object.zig"));
    std.testing.refAllDecls(@import("segment.zig"));
    std.testing.refAllDecls(@import("track.zig"));
    std.testing.refAllDecls(@import("x2.zig"));
    std.testing.refAllDecls(@import("xanim.zig"));
}
