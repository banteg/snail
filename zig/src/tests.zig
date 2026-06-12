const std = @import("std");

test {
    std.testing.refAllDecls(@import("archive.zig"));
    std.testing.refAllDecls(@import("assets.zig"));
    std.testing.refAllDecls(@import("config.zig"));
    std.testing.refAllDecls(@import("gameplay.zig"));
    std.testing.refAllDecls(@import("gameplay/native/attachment_follow.zig"));
    std.testing.refAllDecls(@import("gameplay/native/matrix_math.zig"));
    std.testing.refAllDecls(@import("gameplay/native/player_motion.zig"));
    std.testing.refAllDecls(@import("level.zig"));
    std.testing.refAllDecls(@import("main.zig"));
    std.testing.refAllDecls(@import("object.zig"));
    std.testing.refAllDecls(@import("resource_store.zig"));
    std.testing.refAllDecls(@import("sim.zig"));
    std.testing.refAllDecls(@import("segment.zig"));
    std.testing.refAllDecls(@import("track.zig"));
    std.testing.refAllDecls(@import("x2.zig"));
    std.testing.refAllDecls(@import("xanim.zig"));
}
