# initialize_global_noop_renderable_bods_thunk

One-instruction CRT initializer-table thunk at `0x406bc0`. The table entry at
`0x4a1004` points here; the thunk tail-jumps over 11 alignment nops to the
constructor body at `0x406bd0`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for one declaration of
three globals, `StartupNoopRenderableBod g_startup_noop_renderable_bod_0,
g_startup_noop_renderable_bod_1, g_startup_noop_renderable_bod_2`, which
replaces the hand-written wrapper and initializer function. Both scratches
compile the one source file, the body as `_$E1` and the thunk as `_$E2` in the
whole G0 TU (VC6 numbers each initialized declaration's pair in steps of
three). A `StartupNoopRenderableBod[3]` array emits a counted loop, while one
declaration of three objects emits the native single initializer with three
unrolled constructions, so no aggregate owner is invented. The inline
constructor's callback-table store stands in for the vptr store of the
unrecovered derived class. Both functions stay exact, with every masked
operand resolved through the `function_alias` and per-object global reference
entries.
