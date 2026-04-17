---
name: zig
description: "Idiomatic Zig 0.16.0 guidance for writing, reviewing, debugging, refactoring, and explaining Zig code. Use when working on `.zig` files, Zig build/test flows, allocator ownership questions, error unions, optionals, slices, tests, modern I/O APIs, C interop, or Zig API design."
---

# Zig

Use this skill to keep Zig code explicit about ownership, allocation, failure, lifetimes, and I/O boundaries. Format with `zig fmt`, use `zig test <path>` or the repo's normal build entrypoint for checks, and verify standard-library details against Zig 0.16.0 docs and release notes when touching I/O, build scripts, C interop, or other churn-heavy APIs.

## 1. The core mindset

The shortest way to sound "Zig-ish" is this: **be explicit about bytes, failure, ownership, and boundaries with the outside world**. Zig's design emphasizes precise intent, readable code, explicit resource handling, and the idea that allocation can fail while deallocation must succeed. In Zig 0.16, that same explicitness now shows up even more clearly at application boundaries such as I/O, process setup, and environment access.

If you keep asking these questions, your code will usually end up idiomatic:

* where are the bytes?
* who owns them?
* how long are they valid?
* what can fail?
* what external capability does this operation require?

A good Zig API usually makes these things visible at the call site:

* whether it allocates
* whether it can fail
* whether it mutates
* whether the caller owns the result
* whether returned data is borrowed or owned
* whether it depends on I/O, process state, or other ambient resources

## 2. Zig 0.16 surface changes that matter in real code

Zig 0.16.0 keeps the language philosophy the same, but several surfaces changed enough that old examples can now be misleading.

### I/O is now an explicit interface

Starting in 0.16, input and output functionality is organized around an `Io` instance. For direct stream I/O in `main`, prefer taking `std.process.Init` and passing `init.io` into the operation:

```zig
const std = @import("std");

pub fn main(init: std.process.Init) !void {
    try std.Io.File.stdout().writeStreamingAll(init.io, "Hello, World!\n");
}
```

For quick diagnostics, small CLIs, and debugging output, `std.debug.print` is still the simplest and most idiomatic choice:

```zig
const std = @import("std");

pub fn main() void {
    std.debug.print("Hello, {s}!\n", .{"World"});
}
```

When upgrading older standard-library code, expect many file-system and process APIs to pick up an explicit `io` parameter. The diffs can be large, but they are often mechanical.

### `main` is a better dependency injection point now

In 0.16, application setup is intentionally more explicit. `std.process.Init` gives `main` convenient access to things like `io`, `gpa`, args, and environment data. Code that needs CLI args or environment variables should generally accept the needed values from `main` instead of reaching into global process state.

That means application setup often looks like this:

```zig
const std = @import("std");

pub fn main(init: std.process.Init) !void {
    const gpa = init.gpa;
    const io = init.io;

    const ptr = try gpa.create(i32);
    defer gpa.destroy(ptr);

    try std.Io.File.stdout().writeStreamingAll(io, "Hello, world!\n");
}
```

The exact helper signatures will vary by program, but the design direction is clear: pass capabilities in; do not hide them.

### Prefer build-system C translation over `@cImport`

`@cImport` is deprecated in 0.16. For new code, prefer translating C in `build.zig` and importing the resulting module.

```zig
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

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
                .{
                    .name = "c",
                    .module = translate_c.createModule(),
                },
            },
        }),
    });

    b.installArtifact(exe);
}
```

Then in Zig source:

```zig
const c = @import("c");
```

### `@Type` is gone; use the dedicated builtins

Zig 0.16 removed `@Type` in favor of dedicated type-creating builtins. In new code, reach for things like:

* `@Int`
* `@Struct`
* `@Union`
* `@Pointer`
* `@Fn`
* `@Tuple`
* `@EnumLiteral`

This usually makes meta code clearer anyway, because the intent is visible in the builtin name instead of being packed into one generic reification entry point.

### A few language-level changes are worth remembering

These are not the center of idiomatic Zig, but they matter when reviewing or rewriting code:

* explicitly aligned pointer types are now distinct from naturally aligned pointer types, so write the exact alignment you mean in low-level code
* small integers can coerce to floats when the conversion is lossless
* `@floor`, `@ceil`, `@round`, and `@trunc` can now convert directly to integer result types; prefer the builtin that states the rounding rule you want
* some obviously invalid returns of local addresses are now compile errors, but you still own lifetime correctness overall

## 3. Names, files, and formatting

Use the standard naming conventions:

* **camelCase** for functions and methods
* **TitleCase** for types
* **snake_case** for most other identifiers
* **snake_case** for namespace files and directories
* **TitleCase** for files that define a type with top-level fields

A useful nuance from the style guide: a zero-field `struct` that is only being used as a namespace should be `snake_case`, not `TitleCase`.

Avoid redundant names. Files are already namespaces, and importing a Zig file gives you that file's namespace. That means `json/parser.zig` exporting `Parser` is more idiomatic than exporting `JsonParser` from a module already called `parser`. Let the path and namespace carry context instead of repeating it in every symbol.

Use `zig fmt` and do not fight it. Zig's style guidance explicitly leans on the formatter so teams do not waste energy on whitespace or brace-placement debates.

## 4. Build and test flows in 0.16

Prefer modern `build.zig` patterns that make target, optimize mode, and module wiring explicit.

A small executable build looks like this:

```zig
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "hello",
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/main.zig"),
            .target = target,
            .optimize = optimize,
        }),
    });

    b.installArtifact(exe);
}
```

For test steps inside `build.zig`, use `b.addTest` and `b.addRunArtifact`:

```zig
const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

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

At the command line, `zig test <path>` remains the simplest way to test a file or package.

Two 0.16 build ergonomics notes that are easy to miss:

* `--prominent-compile-errors` is gone; the 0.16 replacement is `--error-style minimal`
* `zig build` now also has `--multiline-errors`

## 5. Default to `const`, not `var`

Prefer `const` unless you are actually mutating the value later. In Zig, `const` is the default mental model and `var` is the exception. That keeps mutation visible and makes code easier to reason about.

Function parameters are immutable, and for larger values the compiler may pass them by value or by reference as it sees fit. Treat parameters as incoming values, not scratch storage, and do not take the address of a parameter and assume that gives you some durable object identity.

Zig also forbids shadowing. That sounds restrictive at first, but it is a style win: one name should keep one meaning within a scope. If a value changes meaning, give it a new name.

## 6. Prefer expression-oriented code

Idiomatic Zig often computes values with expressions instead of mutable temporaries. Blocks are expressions, and a labeled block can `break` a value. `while` and `for` can also be used in an expression-oriented way.

```zig
const mode = blk: {
    if (fast) break :blk .fast;
    if (safe) break :blk .safe;
    break :blk .default;
};
```

This is usually better than:

```zig
var mode = .default;
if (fast) mode = .fast;
if (safe) mode = .safe;
```

The block version makes the final value explicit and reduces incidental mutation.

## 7. Model data explicitly: structs, enums, tagged unions

Use:

* `struct` for related fields
* `enum` for a closed set of states
* tagged unions when the active payload depends on the state

When you switch on an enum or tagged union, prefer an **exhaustive `switch`** over a fallback `else` when the set of cases is known. Exhaustiveness is one of Zig's best readability and maintenance tools. Use `_` or `else` only when you are intentionally handling a non-exhaustive case set.

```zig
const State = enum { idle, busy, done };

fn label(state: State) []const u8 {
    return switch (state) {
        .idle => "idle",
        .busy => "busy",
        .done => "done",
    };
}
```

This is more idiomatic than a chain of `if` statements for discrete states, because the compiler checks that every case is handled.

Zig 0.16 expands what can appear in switch prongs, but the style rule is unchanged: use `switch` to model discrete states clearly, and let exhaustiveness work for you.

## 8. Optionals and error unions are normal control flow

In Zig, `?T` and `!T` are not "advanced features"; they are the normal way to model absence and failure. Prefer them over sentinel values, magic booleans, or out-parameters.

The most idiomatic patterns are payload capture:

```zig
if (maybe_name) |name| {
    // have name: T
} else {
    // was null
}
```

```zig
if (result) |value| {
    // success payload
} else |err| {
    // error payload
}
```

```zig
while (iter.next()) |item| {
    // item from optional-producing iterator
}
```

These forms keep success and failure paths local and readable.

Use `try` for ordinary propagation. Use `catch` when you are truly providing a default, translating an error, or handling a boundary case. Prefer a **precise error set** over `anyerror`; `anyerror` is the global error set and usually throws away useful information.

```zig
const port = try std.fmt.parseInt(u16, text, 10);
```

```zig
const port = std.fmt.parseInt(u16, text, 10) catch 8080;
```

The first says "this function propagates parse failure." The second says "this call site chooses a fallback." That distinction is very Zig-ish.

Put `errdefer` immediately after acquiring something that needs rollback on error. That keeps the unhappy path correct without pushing cleanup far away from the acquisition site.

```zig
const out = try allocator.alloc(u8, len);
errdefer allocator.free(out);
```

Treat `.?`, `orelse unreachable`, and `catch unreachable` as **assertions**, not routine control flow. They are fine when the invariant is genuinely guaranteed; they are not a substitute for normal null or error handling.

## 9. Strings are bytes; use slices

Zig does **not** have a built-in string type. By convention, text is UTF-8 bytes, usually represented as `[]const u8`. Use `[]u8` only when you intend to mutate the bytes.

That leads to one of the most common idioms:

* accept text input as `[]const u8`
* return borrowed text as `[]const u8`
* allocate a new mutable buffer only when you really need owned, writable bytes

Prefer **slices** over many-item or sentinel-terminated pointers when possible. Slices carry a length and benefit from bounds checking, which is usually the right default in Zig code. Use sentinel-terminated forms when the sentinel is actually part of the contract, such as C interop or an API that truly requires it.

String literals are immutable global data. They are null-terminated arrays that coerce naturally to `[]const u8`, but not to `[]u8`. That is why this is right:

```zig
const s: []const u8 = "hello";
```

and this is wrong in spirit and in type terms:

```zig
// const s: []u8 = "hello"; // not allowed
```

because the bytes are not writable.

Never return a slice or pointer into stack storage:

```zig
fn bad() []const u8 {
    var buf = [_]u8{ 'o', 'k' };
    return &buf; // wrong: buf dies at return
}
```

Zig 0.16 catches some trivial local-address returns at compile time, but that is not a substitute for understanding lifetimes. Pointer lifetime is still the programmer's responsibility.

## 10. Allocators are part of the API

By convention, Zig libraries do **not** assume a default allocator. If a function allocates, the idiomatic signature takes an allocator parameter. That makes allocation policy the caller's choice instead of an invisible library decision.

A good template looks like this:

```zig
const std = @import("std");
const Allocator = std.mem.Allocator;

/// Caller owns the returned buffer and must free it with `allocator.free`.
fn join(allocator: Allocator, a: []const u8, b: []const u8) ![]u8 {
    const out = try allocator.alloc(u8, a.len + b.len);
    errdefer allocator.free(out);

    @memcpy(out[0..a.len], a);
    @memcpy(out[a.len..], b);
    return out;
}
```

Why this is idiomatic:

* the allocator is explicit
* the inputs are borrowed immutable slices
* the return type shows allocation may fail
* the doc comment states ownership
* `errdefer` cleans up if something later fails
* the mutable destination for `@memcpy` is obvious

When you return memory, document who frees it. Similarly, borrowed container views have lifetimes too: for example, `std.ArrayList(T).items` is only valid until the list is resized.

Zig 0.16 continues the standard-library move toward container APIs that do **not** store an allocator field. In modern code, it is normal to see something like this:

```zig
const std = @import("std");

test "array list with explicit allocator" {
    const gpa = std.testing.allocator;

    var list: std.ArrayList(u8) = .empty;
    defer list.deinit(gpa);

    try list.append(gpa, 'a');
    try list.append(gpa, 'b');

    try std.testing.expectEqualStrings("ab", list.items);
}
```

This is not "unmanaged as a special case" anymore; it is part of the direction of the standard library.

## 11. Put cleanup next to acquisition

A very Zig habit is: **acquire something, then immediately state its cleanup rule**. Use `defer` for unconditional cleanup and `errdefer` for rollback-on-error cleanup. This keeps resource management local instead of forcing the reader to scan the whole function.

That style is especially important because memory is only one resource. Files, locks, temporary buffers, and partially built state all benefit from the same "cleanup lives next to acquisition" rule.

## 12. Mutate with pointer capture instead of index-heavy loops

When you need in-place mutation, Zig gives you pointer capture in loops. This is usually cleaner than indexing manually.

```zig
for (&items) |*item| {
    item.* += 1;
}
```

That says exactly what is happening: iterate over the collection by pointer and mutate each element. For read-only iteration, drop the `&` and the pointer capture.

Pointer capture also composes nicely with optionals and error unions:

```zig
var maybe_count: ?u32 = 1;
if (maybe_count) |*count| {
    count.* += 1;
}
```

## 13. Lean on result-type propagation for casts

Zig's cast builtins often use the **expected result type**. That means this is idiomatic:

```zig
const small: u8 = @intCast(big);
```

If the target type is not obvious from context, anchor it with `@as`:

```zig
const small = @as(u8, @intCast(big));
```

The style here is "let the surrounding type carry the intent when it is clear; add `@as` when it is not."

A useful 0.16 update: float builtins now forward result types better, and `@floor`, `@ceil`, `@round`, and `@trunc` can convert directly to integer result types. Prefer the builtin that expresses the rounding rule you want.

```zig
const rounded: u8 = @round(value);
const chopped: u8 = @trunc(value);
```

Likewise, small integer types may now coerce directly to floats when the conversion is provably lossless. When it is not clearly lossless, keep using `@floatFromInt`.

## 14. Use `anytype`, `inline`, and feature detection sparingly and deliberately

`anytype` is idiomatic when you want the caller's argument type inferred and the generic surface is small. It is a convenience, not a reason to make APIs vague. Prefer simple inferred generics over complicated explicit metaprogramming when the type relationship is obvious.

Use `inline` only when you genuinely need it: comptime-known values to propagate, stack-frame/debugging reasons, or measured performance reasons. Let the compiler decide inlining unless you have a clear reason to force it.

If you are writing code that spans Zig versions, prefer **feature detection** with `@hasDecl` or `@hasField` rather than checking `builtin.zig_version_string`.

## 15. Be explicit about overflow and `undefined`

For fixed-width integers, ordinary arithmetic can overflow. When wrapping or saturating behavior is the intended semantics, spell that intent explicitly with wrapping operators (`+%`, `-%`, `*%`) or saturating operators (`+|`, `-|`, `*|`). That is much more idiomatic than relying on accidental behavior.

`undefined` is **not** a default value and should not be used as one. Use it only when you know every byte will be overwritten before any read.

A good use is something like a scratch buffer that an API fully writes before you read it; a bad use is "initialize later maybe" business logic.

In safe builds Zig fills undefined memory with a recognizable byte pattern to help catch bugs. That is a hint about intent: `undefined` means "this value will not be meaningfully observed before it is overwritten," not "I do not care what it is."

## 16. Tests and docs are part of idiomatic Zig

Keep tests close to the code with `test` declarations. Zig's tooling is built around this style, and `zig test` works naturally on files or packages.

Use `std.testing.allocator` in tests when allocations are involved; it helps detect leaks. Also exercise failure paths with `std.testing.FailingAllocator` so your OOM handling is tested instead of just assumed.

Use `///` for declaration doc comments and `//!` for top-level file or module docs. Zig can emit docs from source, so clear comments and ownership notes in APIs pay off directly.

For tiny CLIs and debugging output, `std.debug.print` to stderr is often the simplest and most idiomatic choice. Not every program needs a fully abstracted stdout writer path for basic diagnostic printing.

Here is a small test that matches the earlier `join` example:

```zig
test "join concatenates and caller frees result" {
    const std = @import("std");
    const allocator = std.testing.allocator;

    const out = try join(allocator, "ab", "cd");
    defer allocator.free(out);

    try std.testing.expectEqualStrings("abcd", out);
}
```

This keeps ownership and cleanup visible inside the test itself.

## 17. Common anti-patterns in non-idiomatic Zig

These patterns usually make Zig code feel "ported from another language" instead of native to Zig:

* taking `[]u8` for text that is never mutated instead of `[]const u8`
* returning slices into stack memory or undocumented borrowed memory
* hiding allocation inside a helper without taking an allocator parameter
* using `anyerror` everywhere and throwing away useful error information
* using `catch unreachable` or `.?` as normal business logic
* scattering cleanup far away from acquisition instead of using `defer` / `errdefer` locally
* indexing by hand when pointer capture expresses the mutation more directly
* using mutable temporaries where an expression block or `switch` result would be clearer
* writing version checks instead of feature checks for compatibility code
* fighting `zig fmt` or inventing alternate naming conventions
* writing new 0.16 C interop around `@cImport` instead of the build system
* reaching for `@Type` in 0.16 code
* hiding I/O, args, or environment access behind global state when the capability can be passed in explicitly
* assuming old pre-0.16 standard-library signatures for filesystem or process APIs without checking whether they now require `io`

## 18. A one-screen "idiomatic Zig" checklist

Your Zig code is probably idiomatic if most of these are true:

* it uses `const` by default and mutation is easy to spot
* it uses `?T` and `!T` instead of magic sentinels and boolean status flags
* it prefers exhaustive `switch` for discrete states
* text parameters are usually `[]const u8`
* slices are preferred over raw pointer forms unless the pointer form is semantically required
* allocating APIs take an allocator parameter
* ownership and lifetime are stated in docs or obvious from the signature
* `defer` and `errdefer` appear right after acquisition sites
* casts lean on result types instead of noisy annotation everywhere
* overflow behavior is spelled explicitly when wrapping or saturation is intended
* `undefined` is used only for "definitely overwritten before read" cases
* tests use `std.testing.allocator` and include unhappy paths, especially OOM paths
* formatting is left to `zig fmt` and names follow the standard conventions
* new code uses the 0.16 I/O model instead of assuming ambient global I/O access
* C interop is routed through the build system when appropriate
* multi-version support uses feature detection, not version string branching, unless there is no better option
