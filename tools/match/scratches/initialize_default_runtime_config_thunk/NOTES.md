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
