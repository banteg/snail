//! Snail Mail port: the recovered source (decomp/) plus the platform shell.
//!
//! Two wasm32-wasi programs share the recovered source and the shell:
//! `snail` runs headless from the command line (input scripts, no output),
//! `snail-web` is a WASI reactor that port/web/ drives in a browser with
//! WebGL2. Before building, generate the local inputs from the original
//! executable:
//!
//!     uv run snail port link && uv run snail port data
//!     zig build
//!     node shell/run.mjs zig-out/bin/snail.wasm --keys scripts/tutorial.keys
//!     uv run snail port serve
const std = @import("std");

const shell_flags = [_][]const u8{
    "-std=c++17",
    "-fms-extensions",
    "-fdeclspec",
    "-fno-exceptions",
    "-fno-rtti",
    "-fno-sanitize=all",
    "-DSNAIL_PORT",
    "-Wno-everything",
};

const shared_shell = [_][]const u8{
    "shell/game_session.cpp",
    "shell/runtime.cpp",
    "shell/files.cpp",
    "shell/win32.cpp",
    "shell/d3d8_device.cpp",
    "shell/d3dx_texture.cpp",
    "shell/d3dx_math.cpp",
    "shell/bass_emu.cpp",
    "shell/input_state.cpp",
    "shell/abi_shims.cpp",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{
        .default_target = .{ .cpu_arch = .wasm32, .os_tag = .wasi },
    });
    const optimize = b.standardOptimizeOption(.{});

    const headless = program(b, target, optimize, "snail", &.{
        "shell/main.cpp",
        "shell/input_script.cpp",
        "shell/backend_null.cpp",
    });
    b.installArtifact(headless);

    const web = program(b, target, optimize, "snail-web", &.{
        "shell/web_main.cpp",
        "shell/backend_web.cpp",
    });
    web.entry = .disabled;
    web.wasi_exec_model = .reactor;
    b.installArtifact(web);
}

fn program(
    b: *std.Build,
    target: std.Build.ResolvedTarget,
    optimize: std.builtin.OptimizeMode,
    name: []const u8,
    entry_files: []const []const u8,
) *std.Build.Step.Compile {
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
    module.addCSourceFiles(.{ .files = &shared_shell, .flags = &shell_flags });
    module.addCSourceFiles(.{ .files = entry_files, .flags = &shell_flags });
    // Generated locally from the original executable; never committed.
    module.addAssemblyFile(b.path("generated/image_data.s"));
    module.addAssemblyFile(b.path("generated/link_aliases.s"));

    const exe = b.addExecutable(.{ .name = name, .root_module = module });
    exe.stack_size = 16 * 1024 * 1024;
    // The game allocates a 19.8 MB root object plus multi-megabyte workspaces.
    exe.max_memory = 1024 * 1024 * 1024;
    return exe;
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
