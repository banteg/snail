---
name: zig
description: Write, review, refactor, migrate, or debug idiomatic Zig 0.16.0 code. Use for Zig source, build.zig/build.zig.zon, std.Io migrations, allocator ownership, error handling, tests, C interop, and code-review checklists.
---

# Idiomatic Zig 0.16.0 Cookbook

Use this skill whenever a task involves Zig 0.16.0 code or a repository that appears to target Zig 0.16.x. Zig is still pre-1.0, so treat version-specific APIs as part of the task, not trivia. Favor code that is explicit, resource-safe, allocation-aware, testable, and easy to cross-compile.

## Operating mode for Codex

1. Establish the target Zig version.
   - If shell access exists, run `zig version` or inspect `build.zig.zon`, lockfiles, CI, README, and release scripts.
   - If the project is not on Zig 0.16.x, do not blindly apply this skill's API recipes. Use this skill only for style principles and explain version differences when relevant.
   - If no Zig executable is available, still make the best patch, but state that examples or changes were not compiled.

2. Inspect the project before editing.
   - Read `build.zig`, `build.zig.zon`, `src/`, tests, CI, and any repository instructions.
   - Identify whether the project is an executable, library, freestanding target, WASI target, C interop wrapper, or build-tool-heavy package.
   - Check whether the project uses `std.Io`, `std.process.Init`, `.empty` containers, and Zig 0.16 build APIs.

3. Prefer the smallest correct change.
   - Do not rewrite architecture unless the user asks.
   - Preserve public API unless the task is a migration or API redesign.
   - Keep ownership rules and error behavior explicit.

4. Validate.
   - Always run `zig fmt` on changed `.zig` files when possible.
   - Prefer `zig build test`, then `zig build`, then targeted `zig test path/to/file.zig` depending on the project.
   - For dependency or cross-target changes, run the same commands CI runs if feasible.
   - For build-script changes, run `zig build --summary all` or the relevant step.
   - For slow or flaky tests, consider `zig build test --test-timeout <duration>`.

5. Report honestly.
   - Mention exactly what was changed, which commands passed, which commands failed, and whether any snippets were uncompiled.
   - If using a compatibility workaround, say why.

## Definition of done

A Zig 0.16 solution is done when:

- Code is `zig fmt` formatted.
- Allocated memory has one clear owner and one clear cleanup path.
- I/O-capable functions accept or use an appropriate `std.Io` value instead of reaching for global state.
- Error handling uses `try`, `catch`, `errdefer`, and explicit error sets deliberately.
- Tests cover the changed behavior, or the response explains why tests were not added.
- Build-system changes expose standard `-Dtarget` and `-Doptimize` options when appropriate.
- New public declarations have useful doc comments when they form part of the API.

## High-level Zig style

Write Zig as Zig, not as C, Rust, Go, or C++.

- Prefer plain data and plain functions over elaborate abstractions.
- Prefer `const` by default. Use `var` only when the binding itself changes or a mutable pointer to it is needed.
- Keep function signatures honest: parameters should reveal allocation, I/O, ownership, and failure.
- Prefer slices (`[]T`, `[]const T`) over raw pointers when a length exists.
- Prefer optionals (`?T`) over sentinel or magic values.
- Prefer error unions (`Error!T`) over bool-success outputs or global error state.
- Prefer `defer` and `errdefer` immediately after resource acquisition.
- Prefer comptime generics only when they improve type safety or performance. Do not make every helper generic.
- Avoid hidden allocation. If a function allocates, it should usually accept a `std.mem.Allocator` and document who frees.
- Avoid hidden I/O. If a function may block, touch the file system, get time, read entropy, run network operations, or spawn processes, it should usually accept `io: std.Io` or be called from a context that has one.
- Avoid global mutable state. Pass state through parameters or explicit structs.
- Avoid clever control flow. Zig rewards obvious resource lifetimes.

## Naming and layout conventions

Use the style found in the Zig standard library:

- Types: `PascalCase` (`Parser`, `TokenKind`, `Config`).
- Functions and methods: `camelCase` (`parseFile`, `writeAll`, `initCapacity`).
- Variables and fields: `snake_case` (`read_buffer`, `max_bytes`, `file_path`).
- Constants that are values: usually `snake_case` unless they are types or namespaces.
- Namespaces are structs or files; keep them short and purposeful.
- In methods, name the receiver `self`.
- Inside generic structs, define `const Self = @This();` near the top.
- File names are usually `snake_case.zig` for modules and `main.zig` for executables.

Prefer this order inside source files:

```zig
const std = @import("std");
const Io = std.Io;

const Self = @This(); // only inside a struct-like container

pub const PublicType = struct { ... };
const PrivateType = struct { ... };

pub fn publicFunction(...) ... { ... }
fn privateFunction(...) ... { ... }

test "behavior being tested" { ... }
```

## Main functions in Zig 0.16

Use `std.process.Init` when you need `io`, allocator conveniences, CLI arguments, environment variables, preopens, or other process initialization data.

Minimal stdout:

```zig
const std = @import("std");
const Io = std.Io;

pub fn main(init: std.process.Init) !void {
    try Io.File.stdout().writeStreamingAll(init.io, "hello world\n");
}
```

Formatted stdout:

```zig
const std = @import("std");
const Io = std.Io;

pub fn main(init: std.process.Init) !void {
    const io = init.io;

    var buffer: [4096]u8 = undefined;
    var file_writer = Io.File.stdout().writer(io, &buffer);
    const stdout = &file_writer.interface;

    try stdout.print("answer={d}\n", .{42});
    try stdout.flush();
}
```

Use `std.debug.print` for quick diagnostics and logging-like messages to stderr. Do not use it when the program's stdout is meaningful output.

```zig
pub fn main() void {
    std.debug.print("debug: {s}\n", .{"starting"});
}
```

CLI arguments:

```zig
pub fn main(init: std.process.Init) !void {
    const arena = init.arena.allocator();
    const args = try init.minimal.args.toSlice(arena);

    if (args.len != 2) {
        std.log.err("usage: {s} <path>", .{args[0]});
        return error.InvalidArguments;
    }

    try run(init.io, init.gpa, args[1]);
}
```

When writing libraries, do not require `std.process.Init`; accept only the capabilities needed:

```zig
pub fn loadConfig(io: std.Io, allocator: std.mem.Allocator, path: []const u8) !Config {
    const bytes = try std.Io.Dir.cwd().readFileAlloc(io, path, allocator, .limited(1 << 20));
    errdefer allocator.free(bytes);
    return parseConfig(allocator, bytes);
}
```

If upgrading old code and no `Io` is available, create one at the boundary, not deep inside reusable logic:

```zig
var threaded: std.Io.Threaded = .init_single_threaded;
const io = threaded.io();
```

## `std.Io` rules for Zig 0.16

Zig 0.16 moves I/O into an explicit interface. Treat `std.Io` as a capability object for operations that may block, suspend, cancel, or depend on nondeterminism.

Common rules:

- Pass `io: std.Io` into functions that perform file, network, process, time, entropy, or cancelable operations.
- Prefer accepting `io` as a parameter over creating `Io.Threaded` internally.
- Use `init.io` in `main(init: std.process.Init)`.
- Use `std.testing.io` in tests that need I/O.
- Update old `std.fs.File` and `std.fs.Dir` usage to `std.Io.File` and `std.Io.Dir` where applicable.
- Most old file methods now take `io` explicitly.
- Use `std.Io.Reader` and `std.Io.Writer`; do not use old `std.io.GenericReader`, `std.io.AnyReader`, or `std.io.fixedBufferStream` patterns.

Old-to-new examples:

```zig
// Old-ish pattern:
// try std.io.getStdOut().writer().print("{d}\n", .{n});

// Zig 0.16 pattern:
var buf: [1024]u8 = undefined;
var writer = std.Io.File.stdout().writer(io, &buf);
try writer.interface.print("{d}\n", .{n});
try writer.interface.flush();
```

```zig
// Old fixed-buffer stream pattern:
// var fbs = std.io.fixedBufferStream(data);
// const reader = fbs.reader();

// Zig 0.16:
var reader: std.Io.Reader = .fixed(data);
```

```zig
// Old read-file allocation shape:
// const contents = try std.fs.cwd().readFileAlloc(allocator, file_name, max_bytes);

// Zig 0.16:
const contents = try std.Io.Dir.cwd().readFileAlloc(io, file_name, allocator, .limited(max_bytes));
defer allocator.free(contents);
```

File write:

```zig
pub fn writeTextFile(io: std.Io, path: []const u8, text: []const u8) !void {
    var file = try std.Io.Dir.cwd().createFile(io, path, .{});
    defer file.close(io);

    try file.writeStreamingAll(io, text);
}
```

File read with maximum size:

```zig
pub fn readSmallFile(
    io: std.Io,
    allocator: std.mem.Allocator,
    path: []const u8,
) ![]u8 {
    return std.Io.Dir.cwd().readFileAlloc(io, path, allocator, .limited(64 * 1024));
    // Caller owns returned memory and must allocator.free(result).
}
```

Current path:

```zig
const cwd_path = try std.process.currentPathAlloc(io, allocator);
defer allocator.free(cwd_path);
```

Entropy:

```zig
var seed: [32]u8 = undefined;
io.random(&seed); // may use process-local RNG state, depending on implementation

var secure: [32]u8 = undefined;
try io.randomSecure(&secure); // fresh external entropy; may fail
```

Time:

- Prefer `std.Io.Timestamp` APIs in 0.16 code paths that need the current time.
- Keep time retrieval near the boundary and pass concrete timestamps into pure logic.

Concurrency:

- Replace `std.Thread.Pool` with `std.Io` concurrency primitives when migrating 0.15-era code.
- Use `std.Io.Group` for grouped async work.
- Convert synchronization primitives consistently: `std.Thread.Mutex` -> `std.Io.Mutex`, `std.Thread.Condition` -> `std.Io.Condition`, and so on, when synchronized code participates in `std.Io` concurrency.

Pattern for grouped work:

```zig
fn doAllTheWork(io: std.Io, first: WorkItem) !void {
    var group: std.Io.Group = .init;
    errdefer group.cancel(io);

    group.async(io, doOneWorkItem, .{ io, &group, first });
    try group.await(io);
}

fn doOneWorkItem(io: std.Io, group: *std.Io.Group, item: WorkItem) void {
    item.doTheThing();
    for (item.new_work_items) |new_item| {
        group.async(io, doOneWorkItem, .{ io, group, new_item });
    }
}
```

Use `defer` cancellation patterns for tasks that must be joined or canceled before returning.

## Allocators and ownership

Allocator use is a core part of Zig API design. Any function that allocates should usually accept a `std.mem.Allocator` parameter and document ownership.

Good signatures:

```zig
pub fn parseOwned(allocator: std.mem.Allocator, source: []const u8) !Document
pub fn readConfig(io: std.Io, allocator: std.mem.Allocator, path: []const u8) ![]u8
pub fn render(allocator: std.mem.Allocator, doc: Document) ![]u8
```

Document ownership in comments:

```zig
/// Returns an owned UTF-8 buffer. Caller must free it with `allocator.free`.
pub fn renderTitle(allocator: std.mem.Allocator, title: []const u8) ![]u8 {
    return std.fmt.allocPrint(allocator, "# {s}\n", .{title});
}
```

Use `defer` immediately after acquisition:

```zig
const bytes = try allocator.dupe(u8, input);
defer allocator.free(bytes);
```

Use `errdefer` after acquisition when ownership transfers on success:

```zig
pub fn makeBuffer(allocator: std.mem.Allocator, text: []const u8) ![]u8 {
    const out = try allocator.alloc(u8, text.len);
    errdefer allocator.free(out);

    @memcpy(out, text);
    return out; // caller owns
}
```

For multiple owned fields, clean up in reverse acquisition order:

```zig
pub const User = struct {
    name: []u8,
    email: []u8,

    pub fn deinit(self: *User, allocator: std.mem.Allocator) void {
        allocator.free(self.email);
        allocator.free(self.name);
        self.* = undefined;
    }
};

pub fn makeUser(allocator: std.mem.Allocator, name: []const u8, email: []const u8) !User {
    const owned_name = try allocator.dupe(u8, name);
    errdefer allocator.free(owned_name);

    const owned_email = try allocator.dupe(u8, email);
    errdefer allocator.free(owned_email);

    return .{ .name = owned_name, .email = owned_email };
}
```

Use allocator types intentionally:

- `std.testing.allocator` in tests to catch leaks.
- `std.heap.DebugAllocator(.{}){}` for debug builds or tools where leak/double-free detection is valuable.
- `std.heap.ArenaAllocator` for many same-lifetime allocations that can be freed together.
- `std.heap.page_allocator` sparingly; it is simple but not always appropriate.
- Avoid storing allocators in structs unless the struct truly owns allocations and methods must allocate without callers passing an allocator.

Debug allocator pattern:

```zig
pub fn main() !void {
    var debug_allocator = std.heap.DebugAllocator(.{}){};
    defer std.debug.assert(debug_allocator.deinit() == .ok);

    const allocator = debug_allocator.allocator();
    try run(allocator);
}
```

Arena pattern:

```zig
var arena_state = std.heap.ArenaAllocator.init(parent_allocator);
defer arena_state.deinit();
const arena = arena_state.allocator();

const tmp = try arena.dupe(u8, input);
_ = tmp;
// no individual frees; arena_state.deinit frees all arena allocations
```

## Containers in Zig 0.16

Zig 0.16 moves standard containers toward the unmanaged style: containers often no longer store an allocator, and methods that allocate take an allocator argument.

ArrayList pattern:

```zig
const std = @import("std");

pub fn collectBytes(allocator: std.mem.Allocator) ![]u8 {
    var list: std.ArrayList(u8) = .empty;
    defer list.deinit(allocator);

    try list.appendSlice(allocator, "hello");
    try list.append(allocator, ' ');
    try list.appendSlice(allocator, "world");

    return list.toOwnedSlice(allocator); // caller owns; list becomes empty
}
```

Rules:

- Initialize empty containers with `.empty` when provided.
- Pass the allocator to allocating methods such as `append`, `appendSlice`, `ensureTotalCapacity`, `deinit`, and `toOwnedSlice` when the API requires it.
- Do not keep pointers into container storage across calls that may reallocate.
- If appending during iteration, reserve capacity first or use indices carefully.
- Prefer `toOwnedSlice` when returning accumulated data to the caller.
- Use `clearRetainingCapacity` for reuse without returning memory; use `clearAndFree(allocator)` to release backing memory.

Priority queue migration hints:

- Prefer `.empty` initialization.
- Use `push`/`pop` terminology rather than `add`/`remove` terminology where Zig 0.16 APIs have changed.
- Use `initContext` when a priority queue requires non-void comparison context.

Hash-map notes:

- Confirm the exact 0.16 map type in the project before editing. Some `ArrayHashMap` names changed in 0.16.
- Avoid unnecessary hash maps for small fixed sets; arrays plus linear scans are often clearer and faster enough.

## Strings, bytes, slices, and sentinels

Zig has no separate string type. Treat text as UTF-8 by convention, usually `[]const u8`.

- `[]const u8`: borrowed read-only byte slice, often a string.
- `[]u8`: mutable byte slice.
- `[:0]const u8`: sentinel-terminated string slice for C-like APIs.
- `[*:0]const u8`: sentinel-terminated pointer, often from or to C.
- `[]const []const u8`: slice of string slices, often argv-like data.

Prefer slices over pointers:

```zig
fn countNewlines(bytes: []const u8) usize {
    var count: usize = 0;
    for (bytes) |b| {
        if (b == '\n') count += 1;
    }
    return count;
}
```

When a buffer is owned, say so:

```zig
/// Takes ownership of `bytes` and frees it in `deinit`.
pub const Blob = struct {
    bytes: []u8,

    pub fn deinit(self: *Blob, allocator: std.mem.Allocator) void {
        allocator.free(self.bytes);
        self.* = undefined;
    }
};
```

Do not return slices into stack arrays:

```zig
fn bad() []const u8 {
    var local: [4]u8 = .{ 'b', 'a', 'd', '\n' };
    return local[0..]; // invalid lifetime
}
```

Instead, write into a caller-provided buffer or allocate:

```zig
fn formatInto(buf: []u8, value: u32) ![]u8 {
    return std.fmt.bufPrint(buf, "{d}", .{value});
}

fn formatAlloc(allocator: std.mem.Allocator, value: u32) ![]u8 {
    return std.fmt.allocPrint(allocator, "{d}", .{value});
}
```

## Errors and cleanup

Use errors for expected failure modes, not panics. Use panics for programmer bugs and impossible states.

Good error-union API:

```zig
const ParseError = error{
    Empty,
    InvalidDigit,
    Overflow,
};

fn parsePort(text: []const u8) ParseError!u16 {
    if (text.len == 0) return error.Empty;
    return std.fmt.parseInt(u16, text, 10) catch |err| switch (err) {
        error.InvalidCharacter => error.InvalidDigit,
        error.Overflow => error.Overflow,
    };
}
```

Use `try` for normal propagation:

```zig
const value = try parsePort(input);
```

Use `catch` when recovering or translating errors:

```zig
const value = parsePort(input) catch |err| switch (err) {
    error.Empty => 8080,
    else => return err,
};
```

Use `errdefer` for cleanup only on failure:

```zig
var file = try std.Io.Dir.cwd().createFile(io, path, .{});
errdefer file.close(io);

try file.writeStreamingAll(io, contents);
file.close(io); // or use defer if it must close on both success and failure
```

Prefer exact error sets at public boundaries when reasonable:

```zig
pub const LoadError = error{
    FileNotFound,
    AccessDenied,
    InvalidConfig,
    OutOfMemory,
};

pub fn load(...) LoadError!Config { ... }
```

Avoid overusing `anyerror` in public APIs. It hides intent and makes callers harder to write. `anyerror` can be acceptable for application `main`, broad adapters, tests, or generic forwarding where narrowing would add noise.

Use `unreachable` only for invariants proven by program structure or exhaustive handling. Do not use `unreachable` as error handling.

## Optionals

Use optionals for absence.

```zig
fn findUser(users: []const User, id: u64) ?User {
    for (users) |user| {
        if (user.id == id) return user;
    }
    return null;
}
```

Unwrap with `if`:

```zig
if (findUser(users, id)) |user| {
    try writeUser(stdout, user);
} else {
    std.log.warn("user {d} not found", .{id});
}
```

Unwrap with `orelse` for fallback or early return:

```zig
const home = init.environ_map.get("HOME") orelse return error.MissingHome;
```

Use `.?' only when null is a programmer bug and the invariant is obvious nearby.

## Control flow idioms

Use `for` for slices and arrays:

```zig
for (items, 0..) |item, index| {
    std.log.info("{d}: {any}", .{ index, item });
}
```

Use `while` when state changes in the loop expression:

```zig
var i: usize = 0;
while (i < bytes.len) : (i += 1) {
    if (bytes[i] == 0) break;
}
```

Use labeled blocks for expression-style initialization:

```zig
const mode = blk: {
    if (debug) break :blk Mode.debug;
    if (fast) break :blk Mode.fast;
    break :blk Mode.default;
};
```

Use `switch` for exhaustive enum and error handling:

```zig
switch (token.kind) {
    .identifier => try parseIdentifier(token),
    .number => try parseNumber(token),
    .eof => return,
}
```

Do not force expression style when a simple `if` or `switch` statement is clearer.

## `comptime`, generics, and reflection

Zig generics are usually functions that accept `comptime` parameters and return a type or operate on a type.

Generic container pattern:

```zig
pub fn Stack(comptime T: type) type {
    return struct {
        const Self = @This();

        items: []T,
        len: usize = 0,

        pub fn init(storage: []T) Self {
            return .{ .items = storage };
        }

        pub fn push(self: *Self, value: T) !void {
            if (self.len == self.items.len) return error.NoSpaceLeft;
            self.items[self.len] = value;
            self.len += 1;
        }

        pub fn pop(self: *Self) ?T {
            if (self.len == 0) return null;
            self.len -= 1;
            return self.items[self.len];
        }
    };
}
```

Use `anytype` sparingly:

```zig
fn writeLine(writer: anytype, text: []const u8) !void {
    try writer.print("{s}\n", .{text});
}
```

Prefer a concrete interface, such as `*std.Io.Writer`, when that is the real requirement:

```zig
fn writeLine(writer: *std.Io.Writer, text: []const u8) !void {
    try writer.print("{s}\n", .{text});
}
```

Zig 0.16 removed `@Type` in favor of individual type-creating builtins. When generating types, use the relevant builtin such as `@Int`, `@Struct`, `@Union`, `@Enum`, `@Pointer`, `@Fn`, `@Tuple`, or `@EnumLiteral` rather than old `@Type` recipes.

Avoid reflection-heavy code unless it clearly improves the API. Reflection is powerful, but plain explicit code is often better.

## Numeric code

Be explicit with integer widths and casts.

- Use `usize` for indexing and lengths.
- Use fixed-width integers (`u32`, `i64`) for file formats, protocols, hashes, and FFI.
- Use `@as(T, value)` to provide a result type when needed.
- Use `@intCast` for value-changing integer casts when the compiler needs help.
- Use `std.math.cast(T, value)` when runtime failure should be handled as an error or optional.
- Use `@truncate` only when truncation is intended and documented.
- Avoid silent wraparound. Use standard math helpers or wrapping operators deliberately.

Example:

```zig
const len_u32 = std.math.cast(u32, bytes.len) orelse return error.TooLarge;
```

## Build system cookbook

Prefer a `build.zig` that exposes target and optimization choices and defines clear steps.

Basic executable with run and test steps:

```zig
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "app",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    if (b.args) |args| run_cmd.addArgs(args);

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);

    const unit_tests = b.addTest(.{
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });

    const run_unit_tests = b.addRunArtifact(unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_unit_tests.step);
}
```

Expose feature flags with `b.option`:

```zig
const enable_tracing = b.option(bool, "tracing", "Enable tracing logs") orelse false;

const options = b.addOptions();
options.addOption(bool, "enable_tracing", enable_tracing);
exe.root_module.addOptions("config", options);
```

Then in Zig code:

```zig
const config = @import("config");

if (config.enable_tracing) {
    std.log.info("trace enabled", .{});
}
```

Package/dependency guidance:

- Keep `build.zig.zon` committed.
- Do not commit `.zig-cache` or `zig-out`.
- In Zig 0.16, fetched packages are placed in a project-local `zig-pkg` directory; normally do not commit it unless the project intentionally vendors dependencies.
- Use `zig build --fork=/path/to/local/package` for temporary local overrides while fixing dependency breakage.
- Keep build scripts deterministic; avoid shelling out unless necessary. Prefer build tools written in Zig when feasible.
- Avoid hardcoding output paths. Use install steps and build-system paths.

Useful build commands:

```sh
zig fmt build.zig src/**/*.zig
zig build --summary all
zig build test --summary all
zig build test --test-timeout 500ms
zig build -Dtarget=x86_64-linux -Doptimize=ReleaseSafe
zig build --fork=/path/to/dependency
zig build -fincremental --watch
```

## Testing cookbook

Prefer tests close to the code under test. Use named tests with behavior-oriented names.

```zig
const std = @import("std");

fn addOne(x: i32) i32 {
    return x + 1;
}

test "addOne increments positive values" {
    try std.testing.expectEqual(@as(i32, 42), addOne(41));
}
```

Use `std.testing.allocator` for allocation tests:

```zig
test "renderTitle returns owned markdown" {
    const allocator = std.testing.allocator;

    const out = try renderTitle(allocator, "Hello");
    defer allocator.free(out);

    try std.testing.expectEqualStrings("# Hello\n", out);
}
```

Use `std.testing.io` for I/O tests:

```zig
test "read fixture" {
    const io = std.testing.io;
    _ = io;
    // Use io when calling functions that require std.Io.
}
```

Use temporary directories/files when testing filesystem code. Clean up even on failure.

```zig
test "writes output file" {
    const io = std.testing.io;
    const allocator = std.testing.allocator;
    _ = allocator;

    // Prefer project-specific helpers for temp directories if the repo has them.
    // Always close files and delete temp paths with defer/errdefer.
    try writeTextFile(io, "test-output.tmp", "hello");
    defer std.Io.Dir.cwd().deleteFile(io, "test-output.tmp") catch {};
}
```

Use `expectError` for error behavior:

```zig
test "parsePort rejects empty input" {
    try std.testing.expectError(error.Empty, parsePort(""));
}
```

Use `error.SkipZigTest` only when the test truly cannot run on the current target or environment.

Avoid writing to stdout from unit tests. The build system and test runner use stdout/stdin coordination for test reporting; use stderr logging only when needed, and keep it minimal.

## C interop in Zig 0.16

For tiny FFI calls, direct `extern` declarations are often clearer than translated headers:

```zig
const win = @import("std").os.windows;

extern "user32" fn MessageBoxA(
    ?win.HWND,
    [*:0]const u8,
    [*:0]const u8,
    u32,
) callconv(.winapi) i32;
```

For larger header translation in Zig 0.16, prefer moving C translation to the build system rather than using `@cImport` directly in source.

`src/c.h`:

```c
#include <stdio.h>
#include <math.h>
```

`build.zig`:

```zig
const translate_c = b.addTranslateC(.{
    .root_source_file = b.path("src/c.h"),
    .target = target,
    .optimize = optimize,
});

const exe = b.addExecutable(.{
    .name = "app",
    .root_module = b.createModule(.{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
        .imports = &.{
            .{ .name = "c", .module = translate_c.createModule() },
        },
    }),
});
```

`src/main.zig`:

```zig
const c = @import("c");
```

FFI rules:

- Use `extern fn` for imported C functions.
- Use `export fn` for Zig functions exposed to C or other languages.
- Use explicit calling conventions (`callconv(.C)`, `.winapi`) when needed.
- Use sentinel-terminated strings for C strings.
- Be careful with alignment and pointer casts: use `@alignCast` when alignment is not statically known, then `@ptrCast`.
- Keep unsafe pointer manipulation at the boundary. Convert to slices or typed structs as soon as possible.
- Link system libraries through `build.zig`, not ad hoc shell flags, unless the user specifically wants a one-file command.

## Logging and output

Use the right channel:

- Program output: stdout via `std.Io.File.stdout()` and `std.Io.Writer`.
- Diagnostics/logging: `std.log` or `std.debug.print` to stderr.
- Tests: prefer assertions; keep logs minimal.

Logging example:

```zig
std.log.info("loaded {d} records", .{records.len});
std.log.err("failed to parse {s}: {s}", .{ path, @errorName(err) });
```

For libraries, avoid logging unless the library's API explicitly includes logging behavior. Return errors and let applications decide how to report them.

## Migration checklist: Zig 0.15-ish to 0.16

When migrating code to 0.16, scan for these patterns.

### Main/process

- Old code may use `pub fn main() !void` and then query global args/env. In 0.16, use `pub fn main(init: std.process.Init) !void` when args/env/io are needed.
- Environment variables and process arguments are no longer treated as convenient global state. Accept needed values as parameters in library code.

### I/O and filesystem

- `std.io` -> `std.Io` in many places.
- `std.fs.File` -> `std.Io.File`.
- `std.fs.Dir` -> `std.Io.Dir`.
- Many methods now require `io`.
- `file.writeAll(...)` -> `file.writeStreamingAll(io, ...)`.
- `file.read(...)` -> `file.readStreaming(io, ...)` or a reader-based API.
- `std.fs.cwd()` -> `std.Io.Dir.cwd()` for 0.16 I/O APIs.
- `std.process.getCwdAlloc(allocator)` -> `std.process.currentPathAlloc(io, allocator)`.
- `std.fs.cwd().readFileAlloc(allocator, name, max)` -> `std.Io.Dir.cwd().readFileAlloc(io, name, allocator, .limited(max))`.

### Readers/writers

- `std.io.fixedBufferStream(data)` -> `var reader: std.Io.Reader = .fixed(data)` for reading.
- `std.io.fixedBufferStream(buffer)` -> `var writer: std.Io.Writer = .fixed(buffer)` for writing.
- `std.Io.GenericReader` and `std.Io.AnyReader` -> `std.Io.Reader`.
- `std.fmt.format` style output often becomes `std.Io.Writer.print`.

### Containers

- `ArrayList(T).init(allocator)` -> `var list: std.ArrayList(T) = .empty`.
- `list.deinit()` -> `list.deinit(allocator)` for unmanaged containers.
- `list.append(item)` -> `list.append(allocator, item)` where the API requires an allocator.
- `PriorityQueue.add`/`remove` -> `push`/`pop` where APIs changed.
- `ArrayHashMap` family names changed; inspect exact 0.16 APIs before patching.

### Concurrency

- `std.Thread.Pool` removed; migrate to `std.Io.async`, `std.Io.Group`, or lower-level batch APIs as appropriate.
- Convert `std.Thread` synchronization primitives to `std.Io` equivalents when used with `std.Io` concurrency.

### Entropy/time

- `std.crypto.random.bytes(&buf)` -> `io.random(&buf)`.
- Use `io.randomSecure(&buf)` when fresh external cryptographic entropy is required.
- `std.time.Instant`/`Timer`-style usage may need `std.Io.Timestamp` equivalents in 0.16 code.

### C translation and reflection

- `@cImport` is deprecated for future direction; prefer `b.addTranslateC` plus `@import("c")`.
- `@Type` removed; use individual type-creating builtins such as `@Int`, `@Struct`, `@Union`, `@Enum`, `@Pointer`, `@Fn`, and `@Tuple`.

### Build/package workflow

- Use `b.createModule` with `root_module` in build artifacts.
- Keep `standardTargetOptions` and `standardOptimizeOption` for normal packages.
- Use `zig build --fork=/path/to/package` for local package overrides while iterating.
- Be aware of project-local `zig-pkg` dependency directories in 0.16.
- Consider `zig build -fincremental --watch` for iterative development.

## Review checklist for Zig code

When reviewing or generating Zig code, check:

1. Version/API correctness
   - Is this Zig 0.16 code, or did it accidentally use 0.14/0.15 APIs?
   - Are `std.Io`, `std.process.Init`, and unmanaged containers used correctly?

2. Ownership
   - Who owns every allocated slice or object?
   - Is every allocation paired with `free`, `deinit`, ownership transfer, or arena lifetime?
   - Are `errdefer` cleanup paths present after partial initialization?

3. Lifetimes
   - Are any returned slices/pointers referencing stack memory or temporary container storage?
   - Are pointers into `ArrayList.items` kept across reallocating operations?

4. Error behavior
   - Are expected failures returned as errors rather than panics?
   - Are errors narrowed or translated at API boundaries?
   - Are `catch unreachable` and `.?' justified?

5. I/O behavior
   - Does code accept `std.Io` where it performs I/O?
   - Does it avoid hidden global args/env/time/randomness?
   - Does it flush writers when needed?

6. Cross-platform behavior
   - Are path assumptions portable?
   - Is libc/system library usage explicit in `build.zig`?
   - Does target-specific code use `builtin.target` or build options carefully?

7. Tests
   - Do tests use `std.testing.allocator` for allocations?
   - Do tests cover errors and edge cases?
   - Are tests target-aware without silently skipping too much?

8. Build system
   - Are build steps deterministic and cache-friendly?
   - Are generated files represented as build steps instead of ad hoc writes?
   - Are standard target/optimize options exposed?

9. Simplicity
   - Is comptime/reflection justified?
   - Could a small explicit function replace a generic abstraction?
   - Is the code easy to audit for resource lifetimes?

## Common anti-patterns and fixes

### Hidden allocation

Bad:

```zig
fn makeName(input: []const u8) ![]u8 {
    return std.fmt.allocPrint(std.heap.page_allocator, "name:{s}", .{input});
}
```

Good:

```zig
fn makeName(allocator: std.mem.Allocator, input: []const u8) ![]u8 {
    return std.fmt.allocPrint(allocator, "name:{s}", .{input});
}
```

### Leaking on multi-step initialization

Bad:

```zig
const a = try allocator.dupe(u8, name);
const b = try allocator.dupe(u8, email); // if this fails, a leaks
return .{ .name = a, .email = b };
```

Good:

```zig
const a = try allocator.dupe(u8, name);
errdefer allocator.free(a);

const b = try allocator.dupe(u8, email);
errdefer allocator.free(b);

return .{ .name = a, .email = b };
```

### Old stdout APIs

Bad for Zig 0.16:

```zig
// try std.io.getStdOut().writer().print("hello\n", .{});
```

Good:

```zig
try std.Io.File.stdout().writeStreamingAll(io, "hello\n");
```

### Treating null as a pointer value

Bad:

```zig
// Do not model nullable references with raw pointer sentinels.
```

Good:

```zig
fn maybeFind(...) ?*Item { ... }
```

### Overusing `anytype`

Bad:

```zig
fn save(x: anytype) !void { ... }
```

Good:

```zig
fn save(writer: *std.Io.Writer, item: Item) !void { ... }
```

### Panic instead of returning an error

Bad:

```zig
if (input.len == 0) @panic("empty input");
```

Good:

```zig
if (input.len == 0) return error.EmptyInput;
```

### Global mutable configuration

Bad:

```zig
var global_config: Config = .{};
```

Good:

```zig
pub fn run(io: std.Io, allocator: std.mem.Allocator, config: Config) !void { ... }
```

## Cookbook snippets

### Parse a small config file

```zig
const std = @import("std");
const Io = std.Io;

pub const Config = struct {
    name: []u8,

    pub fn deinit(self: *Config, allocator: std.mem.Allocator) void {
        allocator.free(self.name);
        self.* = undefined;
    }
};

pub fn loadConfig(io: Io, allocator: std.mem.Allocator, path: []const u8) !Config {
    const bytes = try Io.Dir.cwd().readFileAlloc(io, path, allocator, .limited(64 * 1024));
    defer allocator.free(bytes);

    const trimmed = std.mem.trim(u8, bytes, " \t\r\n");
    if (trimmed.len == 0) return error.EmptyConfig;

    const name = try allocator.dupe(u8, trimmed);
    errdefer allocator.free(name);

    return .{ .name = name };
}
```

### Write many formatted lines efficiently

```zig
pub fn writeNumbers(io: std.Io, numbers: []const u32) !void {
    var buffer: [8192]u8 = undefined;
    var file_writer = std.Io.File.stdout().writer(io, &buffer);
    const out = &file_writer.interface;

    for (numbers) |n| {
        try out.print("{d}\n", .{n});
    }
    try out.flush();
}
```

### Accumulate and return owned bytes

```zig
pub fn joinWithComma(allocator: std.mem.Allocator, parts: []const []const u8) ![]u8 {
    var out: std.ArrayList(u8) = .empty;
    defer out.deinit(allocator);

    for (parts, 0..) |part, i| {
        if (i != 0) try out.appendSlice(allocator, ",");
        try out.appendSlice(allocator, part);
    }

    return out.toOwnedSlice(allocator);
}
```

### Caller-provided buffer API

```zig
pub fn makeGreeting(buf: []u8, name: []const u8) ![]u8 {
    return std.fmt.bufPrint(buf, "Hello, {s}!", .{name});
}
```

### Build option controls code

`build.zig`:

```zig
const verbose = b.option(bool, "verbose", "Enable verbose logs") orelse false;
const options = b.addOptions();
options.addOption(bool, "verbose", verbose);
exe.root_module.addOptions("config", options);
```

`src/main.zig`:

```zig
const config = @import("config");

if (config.verbose) {
    std.log.info("verbose mode", .{});
}
```

### Minimal library API with explicit dependencies

```zig
pub const Engine = struct {
    allocator: std.mem.Allocator,
    cache: std.ArrayList(u8) = .empty,

    pub fn init(allocator: std.mem.Allocator) Engine {
        return .{ .allocator = allocator };
    }

    pub fn deinit(self: *Engine) void {
        self.cache.deinit(self.allocator);
        self.* = undefined;
    }

    pub fn load(self: *Engine, io: std.Io, path: []const u8) !void {
        const bytes = try std.Io.Dir.cwd().readFileAlloc(io, path, self.allocator, .limited(1 << 20));
        defer self.allocator.free(bytes);

        try self.cache.appendSlice(self.allocator, bytes);
    }
};
```

### Test allocation and ownership

```zig
test "joinWithComma returns owned joined bytes" {
    const allocator = std.testing.allocator;
    const parts = [_][]const u8{ "a", "b", "c" };

    const joined = try joinWithComma(allocator, &parts);
    defer allocator.free(joined);

    try std.testing.expectEqualStrings("a,b,c", joined);
}
```

## Troubleshooting compiler errors

### `struct 'array_list.Aligned(... )' has no member named 'init'`

You are likely using old managed `ArrayList` style. Use `.empty`, pass the allocator to allocating methods, and call `deinit(allocator)`.

```zig
var list: std.ArrayList(u8) = .empty;
defer list.deinit(allocator);
try list.append(allocator, 'x');
```

### `root source file struct 'Io' has no member named 'getStdOut'`

You are mixing old `std.io` examples with Zig 0.16. Use `std.Io.File.stdout()` and `std.Io.Writer`.

### Missing `io` parameter on file operations

Many filesystem methods now require `io`:

```zig
file.close(io);
try file.writeStreamingAll(io, bytes);
```

### `@Type` not found or rejected

Use the individual type-creating builtins available in Zig 0.16 (`@Int`, `@Struct`, `@Union`, `@Enum`, `@Pointer`, `@Fn`, `@Tuple`, etc.).

### C import warnings or migration requests

Move header translation to `build.zig` with `b.addTranslateC`, import it as a module, and use `const c = @import("c");` in Zig source.

### Tests hang

- Add a test timeout through `zig build test --test-timeout <duration>`.
- Check for unclosed I/O tasks, missing cancellation, blocked readers, or test code writing to stdout.
- Prefer `std.testing.io` and deterministic in-memory readers/writers where possible.

## Final response template for Codex

When completing a Zig task, respond with:

- What changed.
- Which Zig 0.16 idioms/APIs were used, if relevant.
- Validation commands and results.
- Any uncompiled or uncertain parts.
- Any follow-up risk, especially version/API drift, target-specific behavior, or dependency constraints.

Example:

```text
Implemented the config loader using Zig 0.16 `std.Io` and explicit allocator ownership. `loadConfig` now accepts `io` and `allocator`, returns an owned `Config`, and uses `errdefer` for partial-init cleanup.

Validation:
- `zig fmt src/main.zig src/config.zig`
- `zig build test --summary all` passed

Note: I kept the public CLI behavior unchanged.
```

## Source links for future maintenance

When updating this skill, verify against the current official docs first:

- Zig 0.16.0 documentation: https://ziglang.org/documentation/0.16.0/
- Zig 0.16.0 release notes: https://ziglang.org/download/0.16.0/release-notes.html
- Zig build system guide: https://ziglang.org/learn/build-system/
- Zig samples: https://ziglang.org/learn/samples/
- Codex Agent Skills docs: https://developers.openai.com/codex/skills
