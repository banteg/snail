# initialize_global_noop_renderable_bods_thunk

One-instruction CRT initializer-table thunk at `0x406bc0`. The table entry at
`0x4a1004` points here; the thunk tail-jumps over 11 alignment nops to the
constructor body at `0x406bd0`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`StartupNoopRenderableBods g_startup_noop_renderable_bods`, which replaces the
hand-written wrapper and initializer function. Both scratches compile the one
source file, the body as `_$E1` and the thunk as `_$E2` in the whole G0 TU (VC6
numbers each initialized declaration's pair in steps of three). Here a
`RenderableBod` array emits a counted loop, but the native body constructs the
three records unrolled, so they are three members of one aggregate;
`StartupNoopRenderableBod a, b, c;` emits the same body, and the aggregate
keeps the proven contiguous 0x24c extent under one symbol. The inline
constructor's callback-table store stands in for the vptr store of the
unrecovered derived class. Both functions stay exact, with every masked operand
resolved through the `function_alias` reference entries.
