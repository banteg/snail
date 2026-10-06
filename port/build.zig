//! Snail Mail port: the recovered source (decomp/) plus the platform shell.
//!
//! Stage 2 builds a headless wasm32-wasi program. Before building, generate the
//! local inputs from the original executable:
//!
//!     uv run snail port link && uv run snail port data
//!     zig build
//!     node shell/run.mjs zig-out/bin/snail.wasm
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{
        .default_target = .{ .cpu_arch = .wasm32, .os_tag = .wasi },
    });
    const optimize = b.standardOptimizeOption(.{});

    const module = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });
    module.addIncludePath(b.path("../tools/match/include"));
    module.addIncludePath(b.path("compat"));

    // Recovered source compiles as-is; the flags and file list are shared with
    // `snail port` (cflags.txt, sources.txt).
    module.addCSourceFiles(.{
        .files = lines(b, @embedFile("sources.txt")),
        .flags = lines(b, @embedFile("cflags.txt")),
    });
    module.addCSourceFiles(.{
        .files = &.{
            "shell/main.cpp",
            "shell/runtime.cpp",
            "shell/files.cpp",
            "shell/render_null.cpp",
            "shell/audio_null.cpp",
            "shell/input_null.cpp",
            "shell/abi_shims.cpp",
        },
        .flags = &.{
            "-std=c++17",
            "-fms-extensions",
            "-fdeclspec",
            "-fno-exceptions",
            "-fno-rtti",
            "-fno-sanitize=all",
            "-DSNAIL_PORT",
            "-Wno-everything",
        },
    });
    // Generated locally from the original executable; never committed.
    module.addAssemblyFile(b.path("generated/image_data.s"));
    module.addAssemblyFile(b.path("generated/link_aliases.s"));

    const exe = b.addExecutable(.{ .name = "snail", .root_module = module });
    exe.stack_size = 16 * 1024 * 1024;
    // The game allocates a 19.8 MB root object plus multi-megabyte workspaces.
    exe.max_memory = 1024 * 1024 * 1024;
    b.installArtifact(exe);
}

/// Non-empty, non-comment lines of an embedded list file.
fn lines(b: *std.Build, text: []const u8) []const []const u8 {
    var list: std.ArrayList([]const u8) = .empty;
    var it = std.mem.tokenizeAny(u8, text, "\r\n");
    while (it.next()) |line| {
        if (line[0] == '#') continue;
        list.append(b.allocator, line) catch @panic("out of memory");
    }
    return list.items;
}
