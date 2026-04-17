const std = @import("std");
const raylib_pkg = "zig-pkg/raylib-5.6.0-dev-whq8uGJqKQUEDd38DCov-XG29PYzw3kM_LNbPUkcDGyM";
const raylib_zig_pkg = "zig-pkg/raylib_zig-5.6.0-dev-KE8REKNmBQDek2Sz27ULioxYpY9IYR0K0CeIC-iJRLCI";

fn addRaylibLibrary(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
) *std.Build.Step.Compile {
    const raylib = b.addLibrary(.{
        .name = "raylib",
        .linkage = .static,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
        }),
    });

    raylib.root_module.addIncludePath(b.path(raylib_pkg ++ "/src"));
    raylib.root_module.addIncludePath(b.path(raylib_pkg ++ "/src/platforms"));
    raylib.root_module.addIncludePath(b.path(raylib_pkg ++ "/src/external/glfw/include"));

    raylib.root_module.addCMacro("PLATFORM_DESKTOP_GLFW", "1");
    raylib.root_module.addCMacro("SUPPORT_MODULE_RSHAPES", "1");
    raylib.root_module.addCMacro("SUPPORT_MODULE_RTEXTURES", "1");
    raylib.root_module.addCMacro("SUPPORT_MODULE_RTEXT", "1");
    raylib.root_module.addCMacro("SUPPORT_MODULE_RMODELS", "1");
    raylib.root_module.addCMacro("SUPPORT_MODULE_RAUDIO", "1");
    raylib.root_module.addCMacro("SUPPORT_FILEFORMAT_TGA", "1");
    raylib.root_module.addCMacro("SUPPORT_FILEFORMAT_OGG", "1");

    const common_sources = &.{
        "rcore.c",
        "rshapes.c",
        "rtextures.c",
        "rtext.c",
        "rmodels.c",
        "raudio.c",
    };
    const desktop_sources = &.{
        "rcore.c",
        "rshapes.c",
        "rtextures.c",
        "rtext.c",
        "rmodels.c",
        "raudio.c",
        "rglfw.c",
    };

    switch (target.result.os.tag) {
        .windows => {
            raylib.root_module.addCSourceFiles(.{
                .root = b.path(raylib_pkg ++ "/src"),
                .files = desktop_sources,
                .flags = &.{"-std=gnu99"},
            });
            raylib.root_module.linkSystemLibrary("winmm", .{});
            raylib.root_module.linkSystemLibrary("gdi32", .{});
            raylib.root_module.linkSystemLibrary("opengl32", .{});
        },
        .linux => {
            raylib.root_module.addCMacro("_GNU_SOURCE", "1");
            raylib.root_module.addCMacro("_GLFW_X11", "1");
            raylib.root_module.addCSourceFiles(.{
                .root = b.path(raylib_pkg ++ "/src"),
                .files = desktop_sources,
                .flags = &.{"-std=gnu99"},
            });
            raylib.root_module.linkSystemLibrary("GLX", .{});
            raylib.root_module.linkSystemLibrary("X11", .{});
            raylib.root_module.linkSystemLibrary("Xcursor", .{});
            raylib.root_module.linkSystemLibrary("Xext", .{});
            raylib.root_module.linkSystemLibrary("Xfixes", .{});
            raylib.root_module.linkSystemLibrary("Xi", .{});
            raylib.root_module.linkSystemLibrary("Xinerama", .{});
            raylib.root_module.linkSystemLibrary("Xrandr", .{});
            raylib.root_module.linkSystemLibrary("Xrender", .{});
        },
        .macos => {
            raylib.root_module.addCMacro("GL_SILENCE_DEPRECATION", "199309L");
            raylib.root_module.addCSourceFiles(.{
                .root = b.path(raylib_pkg ++ "/src"),
                .files = common_sources,
                .flags = &.{"-std=gnu99"},
            });
            raylib.root_module.addCSourceFile(.{
                .file = b.path(raylib_pkg ++ "/src/rglfw.c"),
                .flags = &.{ "-std=gnu99", "-ObjC" },
            });
            raylib.root_module.linkFramework("Foundation", .{});
            raylib.root_module.linkFramework("CoreServices", .{});
            raylib.root_module.linkFramework("CoreGraphics", .{});
            raylib.root_module.linkFramework("AppKit", .{});
            raylib.root_module.linkFramework("IOKit", .{});
        },
        else => @panic("unsupported OS for raylib build"),
    }

    return raylib;
}

fn linkRaylibSystemDeps(root_module: *std.Build.Module, target: std.Build.ResolvedTarget) void {
    switch (target.result.os.tag) {
        .windows => {
            root_module.linkSystemLibrary("winmm", .{});
            root_module.linkSystemLibrary("gdi32", .{});
            root_module.linkSystemLibrary("opengl32", .{});
        },
        .linux => {
            root_module.linkSystemLibrary("GL", .{});
            root_module.linkSystemLibrary("GLX", .{});
            root_module.linkSystemLibrary("rt", .{});
            root_module.linkSystemLibrary("dl", .{});
            root_module.linkSystemLibrary("m", .{});
            root_module.linkSystemLibrary("X11", .{});
            root_module.linkSystemLibrary("Xcursor", .{});
            root_module.linkSystemLibrary("Xext", .{});
            root_module.linkSystemLibrary("Xfixes", .{});
            root_module.linkSystemLibrary("Xi", .{});
            root_module.linkSystemLibrary("Xinerama", .{});
            root_module.linkSystemLibrary("Xrandr", .{});
            root_module.linkSystemLibrary("Xrender", .{});
            root_module.linkSystemLibrary("Xxf86vm", .{});
        },
        .macos => {
            root_module.linkFramework("Foundation", .{});
            root_module.linkFramework("CoreServices", .{});
            root_module.linkFramework("CoreGraphics", .{});
            root_module.linkFramework("AppKit", .{});
            root_module.linkFramework("Cocoa", .{});
            root_module.linkFramework("OpenGL", .{});
            root_module.linkFramework("CoreAudio", .{});
            root_module.linkFramework("CoreVideo", .{});
            root_module.linkFramework("IOKit", .{});
        },
        else => @panic("unsupported OS for raylib linkage"),
    }
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const raylib_artifact = addRaylibLibrary(b, target, optimize);
    const raylib = b.createModule(.{
        .root_source_file = b.path(raylib_zig_pkg ++ "/lib/raylib.zig"),
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

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
    linkRaylibSystemDeps(exe.root_module, target);

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
    linkRaylibSystemDeps(exe_tests.root_module, target);

    const run_exe_tests = b.addRunArtifact(exe_tests);
    const test_step = b.step("test", "Run Zig tests");
    test_step.dependOn(&run_exe_tests.step);
}
