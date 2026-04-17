# Idiomatic Zig 0.16.0 cheatsheet

This targets **Zig 0.16.0**. In practice, “idiomatic Zig” means writing code that follows the language reference, style guide, and Zig Zen: make intent explicit, keep control flow visible, treat edge cases as first-class, and make ownership and lifetime obvious from the code and API surface. ([Zig Programming Language])

## 1. The core mindset

The shortest way to sound “Zig-ish” is this: **be explicit about bytes, failure, and ownership**. Zig’s design emphasizes precise intent, readable code, explicit resource handling, and the idea that allocation can fail while deallocation must succeed. If you keep asking “where are the bytes, who owns them, and how long are they valid?”, your code will usually end up idiomatic. ([Zig Programming Language])

A good Zig API usually makes these things visible at the call site:

* whether it allocates
* whether it can fail
* whether it mutates
* whether the caller owns the result
* whether the returned data is borrowed or owned. ([Zig Programming Language])

## 2. Names, files, and formatting

Use the standard naming conventions:

* **camelCase** for functions and methods
* **TitleCase** for types
* **snake_case** for most other identifiers
* **snake_case** filenames for ordinary modules; files that define a type with fields are commonly **TitleCase**. ([Zig Programming Language])

Avoid redundant names. Files are already namespaces, and importing a Zig file gives you that file’s namespace. That means `json/parser.zig` exporting `Parser` is more idiomatic than exporting `JsonParser` from a module already called `parser`. Let the path and namespace carry context instead of repeating it in every symbol. ([Zig Programming Language])

Use `zig fmt` and do not fight it. Zig’s style guidance explicitly leans on the formatter so teams do not waste energy on brace placement or whitespace debates. ([Zig Programming Language])

## 3. Default to `const`, not `var`

Prefer `const` unless you are actually mutating the value later. In Zig, `const` is the default mental model and `var` is the exception. That keeps mutation visible and makes code easier to reason about. ([Zig Programming Language])

Function parameters are immutable, and for large values the compiler may pass them by value or by reference as it sees fit. Treat parameters as incoming values, not scratch storage, and do not take the address of a parameter and assume that gives you some durable object identity. ([Zig Programming Language])

Zig also forbids shadowing. That sounds restrictive at first, but it is a style win: one name should keep one meaning within a scope. If a value changes meaning, give it a new name. ([Zig Programming Language])

## 4. Prefer expression-oriented code

Idiomatic Zig often computes values with expressions instead of mutable temporaries. Blocks are expressions, and a labeled block can `break` a value. `while` can also be used in an expression-oriented way. ([Zig Programming Language])

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

The block version makes the final value explicit and reduces incidental mutation. ([Zig Programming Language])

## 5. Model data explicitly: structs, enums, tagged unions

Use:

* `struct` for related fields
* `enum` for a closed set of states
* **tagged unions** when the active payload depends on the state. ([Zig Programming Language])

When you switch on an enum or tagged union, prefer an **exhaustive `switch`** over a fallback `else` when the set of cases is known. Exhaustiveness is one of Zig’s best readability and maintenance tools. Use `_` only when you are intentionally handling a non-exhaustive case set. ([Zig Programming Language])

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

This is more idiomatic than a chain of `if` statements for discrete states, because the compiler checks that every case is handled. ([Zig Programming Language])

## 6. Optionals and error unions are normal control flow

In Zig, `?T` and `!T` are not “advanced features”; they are the normal way to model absence and failure. Prefer them over sentinel values, magic booleans, or out-parameters. ([Zig Programming Language])

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

These forms keep success and failure paths local and readable. ([Zig Programming Language])

Use `try` for ordinary propagation. Use `catch` when you are truly providing a default, translating an error, or handling a boundary case. Prefer a **precise error set** over `anyerror`; the language reference explicitly says `anyerror` should generally be avoided because it erases useful information. ([Zig Programming Language])

```zig
const port = try std.fmt.parseInt(u16, text, 10);
```

```zig
const port = std.fmt.parseInt(u16, text, 10) catch 8080;
```

The first says “this function propagates parse failure.” The second says “this call site chooses a fallback.” That distinction is very Zig-ish. ([Zig Programming Language])

Put `errdefer` immediately after acquiring something that needs rollback on error. That keeps the unhappy path correct without pushing cleanup far away from the acquisition site. ([Zig Programming Language])

```zig
const out = try allocator.alloc(u8, len);
errdefer allocator.free(out);
```

Treat `.?`, `orelse unreachable`, and `catch unreachable` as **assertions**, not routine control flow. They are fine when the invariant is genuinely guaranteed; they are not a substitute for normal null or error handling. Zig’s docs explicitly show testing for null or errors instead of assuming impossibility when the value can actually be absent or fail. ([Zig Programming Language])

## 7. Strings are bytes; use slices

Zig does **not** have a built-in string type. By convention, text is UTF-8 bytes, usually represented as `[]const u8`. Use `[]u8` only when you intend to mutate the bytes. ([Zig Programming Language])

That leads to one of the most common idioms:

* accept text input as `[]const u8`
* return borrowed text as `[]const u8`
* allocate a new mutable buffer only when you really need owned, writable bytes. ([Zig Programming Language])

Prefer **slices** over many-item or sentinel-terminated pointers when possible. Slices carry a length and benefit from bounds checking, which is usually the right default in Zig code. Use sentinel-terminated forms when the sentinel is actually part of the contract, such as C interop or an API that truly requires it. ([Zig Programming Language])

String literals are immutable global data. They are null-terminated arrays that coerce naturally to `[]const u8`, but not to `[]u8`. That is why this is right:

```zig
const s: []const u8 = "hello";
```

and this is wrong in spirit and in type terms:

```zig
// const s: []u8 = "hello"; // not allowed
```

because the bytes are not writable. ([Zig Programming Language])

Never return a slice or pointer into stack storage:

```zig
fn bad() []const u8 {
    var buf = [_]u8{ 'o', 'k' };
    return &buf; // wrong: buf dies at return
}
```

Pointer lifetime is the programmer’s responsibility in Zig, and local stack memory stops being valid when the function returns. ([Zig Programming Language])

## 8. Allocators are part of the API

By convention, Zig libraries do **not** assume a default allocator. If a function allocates, the idiomatic signature takes an allocator parameter. That makes allocation policy the caller’s choice instead of an invisible library decision. ([Zig Programming Language])

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
* the mutable destination for `@memcpy` is obvious. ([Zig Programming Language])

When you return memory, document who frees it. Zig’s language reference explicitly says returned pointer lifetimes and ownership should be described in docs. Similarly, borrowed container views have lifetimes too: for example, `std.ArrayList(T).items` is only valid until the list is resized. ([Zig Programming Language])

## 9. Put cleanup next to acquisition

A very Zig habit is: **acquire something, then immediately state its cleanup rule**. Use `defer` for unconditional cleanup and `errdefer` for rollback-on-error cleanup. This keeps resource management local instead of forcing the reader to scan the whole function. ([Zig Programming Language])

That style is especially important because memory is only one resource. Files, locks, temporary buffers, and partially built state all benefit from the same “cleanup lives next to acquisition” rule. ([Zig Programming Language])

## 10. Mutate with pointer capture instead of index-heavy loops

When you need in-place mutation, Zig gives you pointer capture in loops. This is usually cleaner than indexing manually. ([Zig Programming Language])

```zig
for (&items) |*item| {
    item.* += 1;
}
```

That says exactly what is happening: iterate over the collection by pointer and mutate each element. For read-only iteration, drop the `&` and the pointer capture. ([Zig Programming Language])

## 11. Lean on result-type propagation for casts

Zig’s cast builtins often use the **expected result type**. That means this is idiomatic:

```zig
const small: u8 = @intCast(big);
```

If the target type is not obvious from context, anchor it with `@as`:

```zig
const small = @as(u8, @intCast(big));
```

The style here is “let the surrounding type carry the intent when it is clear; add `@as` when it is not.” ([Zig Programming Language])

## 12. Use `anytype` and `inline` sparingly and deliberately

`anytype` is idiomatic when you want the caller’s argument type inferred and the generic surface is small. It is a convenience, not a reason to make APIs vague. Prefer simple inferred generics over complicated explicit metaprogramming when the type relationship is obvious. ([Zig Programming Language])

Use `inline` only when you genuinely need it: comptime-known values to propagate, stack-frame/debugging reasons, or measured performance reasons. Zig’s docs explicitly recommend letting the compiler make inlining decisions unless you have a clear reason, because forced inlining can hurt compile time, code size, and even runtime performance. ([Zig Programming Language])

If you are writing code that spans Zig versions, prefer **feature detection** with `@hasDecl` or `@hasField` rather than checking `builtin.zig_version_string`. The language reference recommends that style for multi-version support. ([Zig Programming Language])

## 13. Be explicit about overflow and `undefined`

For fixed-width integers, ordinary arithmetic can overflow. When wrapping or saturating behavior is the intended semantics, spell that intent explicitly with wrapping operators (`+%`, `-%`, `*%`) or saturating operators (`+|`, `-|`, `*|`). That is much more idiomatic than relying on accidental behavior. ([Zig Programming Language])

`undefined` is **not** a default value and should not be used as one. Use it only when you know every byte will be overwritten before any read. In safe builds Zig fills `undefined` memory with a recognizable pattern to help catch bugs, which is a strong hint that it is for “will be initialized later,” not “I do not care.” ([Zig Programming Language])

A good use is something like a scratch buffer that an API fully writes before you read it; a bad use is “initialize later maybe” business logic. ([Zig Programming Language])

## 14. Tests and docs are part of idiomatic Zig

Keep tests close to the code with `test` declarations. Zig’s tooling is built around this style, and `zig test` works naturally on files or packages. ([Zig Programming Language])

Use `std.testing.allocator` in tests when allocations are involved; it helps detect leaks. Also exercise failure paths with `std.testing.FailingAllocator` so your OOM handling is tested instead of just assumed. ([Zig Programming Language])

Use `///` for declaration doc comments and `//!` for top-level file or module docs. Zig can emit docs from source, so clear comments and ownership notes in APIs pay off directly. ([Zig Programming Language])

For tiny CLIs and debugging output, `std.debug.print` to stderr is often the simplest and most idiomatic choice. Not every program needs a fully abstracted stdout writer path for basic diagnostic printing. ([Zig Programming Language])

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

This keeps ownership and cleanup visible inside the test itself. ([Zig Programming Language])

## 15. Common anti-patterns in non-idiomatic Zig

These patterns usually make Zig code feel “ported from another language” instead of native to Zig:

* taking `[]u8` for text that is never mutated instead of `[]const u8` ([Zig Programming Language])
* returning slices into stack memory or undocumented borrowed memory ([Zig Programming Language])
* hiding allocation inside a helper without taking an allocator parameter ([Zig Programming Language])
* using `anyerror` everywhere and throwing away useful error information ([Zig Programming Language])
* using `catch unreachable` or `.?` as normal business logic ([Zig Programming Language])
* scattering cleanup far away from acquisition instead of using `defer` / `errdefer` locally ([Zig Programming Language])
* indexing by hand when pointer capture expresses the mutation more directly ([Zig Programming Language])
* using mutable temporaries where an expression block or `switch` result would be clearer ([Zig Programming Language])
* writing version checks instead of feature checks for compatibility code ([Zig Programming Language])
* fighting `zig fmt` or inventing alternate naming conventions ([Zig Programming Language])

## 16. A one-screen “idiomatic Zig” checklist

Your Zig code is probably idiomatic if most of these are true:

* it uses `const` by default and mutation is easy to spot ([Zig Programming Language])
* it uses `?T` and `!T` instead of magic sentinels and boolean status flags ([Zig Programming Language])
* it prefers exhaustive `switch` for discrete states ([Zig Programming Language])
* text parameters are usually `[]const u8` ([Zig Programming Language])
* slices are preferred over raw pointer forms unless the pointer form is semantically required ([Zig Programming Language])
* allocating APIs take an allocator parameter ([Zig Programming Language])
* ownership and lifetime are stated in docs or obvious from the signature ([Zig Programming Language])
* `defer` and `errdefer` appear right after acquisition sites ([Zig Programming Language])
* casts lean on result types instead of noisy annotation everywhere ([Zig Programming Language])
* overflow behavior is spelled explicitly when wrapping or saturation is intended ([Zig Programming Language])
* `undefined` is used only for “definitely overwritten before read” cases ([Zig Programming Language])
* tests use `std.testing.allocator` and include unhappy paths, especially OOM paths ([Zig Programming Language])
* formatting is left to `zig fmt` and names follow the standard conventions ([Zig Programming Language])
