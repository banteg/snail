# initialize_default_runtime_config_thunk

One-instruction CRT initializer-table thunk at `0x406c10`. The table entry at
`0x4a1008` points here; the thunk tail-jumps over 11 alignment nops to the
`SnailMail.cfg` default-state initializer at `0x406c20`.
The source-level tail call matches the native 1/1 instruction exactly, with its
single masked target resolved.

## 2026-08-12 cross-port source provenance

The initialized `gConfig` global is assigned to `Mac.o` by the iPhone v1.5
STABS inventory. That binary retains a direct static-initializer wrapper named
`__GLOBAL__I_MACAppPath`, while Android retains `_GLOBAL__I_Ad.cpp`; both reach
the same cross-port config-default sequence documented on the body scratch.
This recovers `Mac.o` provenance for the Windows CRT thunk without treating a
platform-specific wrapper name as a one-to-one mobile function mapping. The
exact Windows 1/1 thunk is unchanged.

## 2026-10-17 compiler-generated pair

The thunk and body are VC6's dynamic-initializer pair for the global definition
`RuntimeConfig g_runtime_config`, which replaces the hand-written wrapper and
initializer function. Both scratches compile the one source file, the body as
`_$E4` and the thunk as `_$E5` in the whole G0 TU (VC6 numbers each initialized
declaration's pair in steps of three). Here the defaults are `RuntimeConfig`'s
inline constructor; its body is the former initializer's, register idiom
included. Both functions stay exact, with every masked operand resolved through
the `function_alias` reference entries.
