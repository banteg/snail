# initialize_global_trivial_object_thunk

One-instruction CRT initializer-table thunk at `0x406d10`. The table entry at
`0x4a100c` points here; the thunk tail-jumps over 11 alignment nops to the
constructor body at `0x406d20`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.

The thunk is the `0x4a100c` CRT entry for the adjacent `Mac.o` constructor
body. It follows the directly anchored `gConfig` thunk/body at
`0x406c10..0x406d07`; the earlier unrelated initializer ends at `0x406c0c`.
This recovers compilation-unit provenance without assigning the folded callee
or the otherwise-unused global a speculative authored class.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`StartupTrivialObject g_startup_trivial_object`, which replaces the
hand-written wrapper and initializer function. Both scratches compile the one
source file, the body as `_$E7` and the thunk as `_$E8` in the whole G0 TU (VC6
numbers each initialized declaration's pair in steps of three). Here the
generic owner now declares the folded no-op default constructor at `0x44db50`
(`??0StartupTrivialObject@@QAE@XZ`). Both functions stay exact, with every
masked operand resolved through the `function_alias` reference entries.
