# initialize_global_noop_renderable_bods

CRT constructor body at `0x406bd0` for three global records at `0x4b6fb4`,
`0x4b7078`, and `0x4b713c`. Their `0xc4` stride proves a common aggregate; each
record owns a normal `RenderableBod` prefix and then receives the shared
`noop_runtime_ai` callback table.

No instruction outside this initializer addresses any of the three records, so
the `0x4c` tail and original gameplay class remain deliberately unnamed. The
aggregate begins 0x64 bytes after the independently bounded 0x4000-byte
`g_animation_directory`, correcting the former overlapping global extent.
The three prefix constructions compile to the native 10/10 instructions
exactly, with all 9 masked operands resolved.

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
