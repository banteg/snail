const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const raylib_dep = b.dependency("raylib_zig", .{
        .target = target,
        .optimize = optimize,
    });
    const raylib = raylib_dep.module("raylib");
    const raylib_artifact = raylib_dep.artifact("raylib");
    raylib_artifact.root_module.addCMacro("SUPPORT_FILEFORMAT_TGA", "1");
    raylib_artifact.root_module.addCMacro("SUPPORT_FILEFORMAT_OGG", "1");

    const exe = b.addExecutable(.{
        .name = "snail",
        .root_module = b.createModule(.{
            .root_source_file = b.path("zig/src/main.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    exe.root_module.linkLibrary(raylib_artifact);
    exe.root_module.addImport("raylib", raylib);

    b.installArtifact(exe);

    const run_step = b.step("run", "Run the snail runtime");
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    run_step.dependOn(&run_cmd.step);

    const exe_tests = b.addTest(.{
        .root_module = b.createModule(.{
            .root_source_file = b.path("zig/src/tests.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    exe_tests.root_module.linkLibrary(raylib_artifact);
    exe_tests.root_module.addImport("raylib", raylib);

    const run_exe_tests = b.addRunArtifact(exe_tests);
    const test_step = b.step("test", "Run Zig tests");
    test_step.dependOn(&run_exe_tests.step);
}
