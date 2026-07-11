# `initialize_default_runtime_config` recovery notes

Target: `initialize_default_runtime_config @ 0x406c10` (`cdecl` startup
initializer).

The function has no code xrefs; BN reports a data xref from `0x4a1008`, which
fits a startup-initializer table entry. The manifest starts at `0x406c10`, but
the first bytes are a jump over 11 bytes of padding:

```asm
00406c10  jmp 0x406c20
00406c15  nop ... 00406c1f
```

The retained C source models the real initializer body from `0x406c20` onward:
it seeds the saved config blob, render flags, completion-score defaults,
high-score state, loading-screen budget values, and tutorial latch. The native
body and candidate body match instruction-for-instruction after the jump/padding
stub.

The scratch deliberately keeps the startup stub unmatched instead of using a
naked/asm shim or fake prologue. The saved `SnailMail.cfg` blob slots now have
curated references when their consumers are known; fields with no recovered
consumer are named as explicit reserved config offsets instead of anonymous
`data_` globals.

Current retained Wibo result: 85.71%, 48 target instructions vs 36 candidate
instructions. The missing 12 instructions are the leading `jmp` plus padding.
Focused matcher now reports 32 clean masked operands, 0 unresolved, and 0
mismatched. The config-tail validation helper at `0x42f5b0` is recovered as
`validate_config_tail_stub`; it ignores its argument and returns true.

2026-07-11 ownership recovery: the persisted bytes are now represented by one
`RuntimeConfig` object whose asserted size is the `0xc4` passed to every load
and save call. Address spacing fixes the 64-byte name field at `+0x60`, followed
by the route limit, landscape selector, high-score bank, and loading budget at
`+0xa0` through `+0xac`. The render flags are a dword at `+0x1c`: low-byte
feature tests had produced misleading byte declarations, but the default
`0x5fe` store and the window code's `0x400` test require the full word. Moving
the initializer, blob save sites, and all three conflicted field families onto
the aggregate preserves every focused instruction stream and leaves this
scratch at the same 85.71% structural result.

2026-07-11 consumer closure: all remaining volume, fullscreen, display-mode,
steering, completion-slider, route-limit, high-score-bank, loading-budget, and
tutorial users now address fields through `g_runtime_config`. The focused
metrics of all 25 affected scratches are unchanged, including every exact
consumer. Naming the landscape selector in the still-sparse world initializer
also converts one raw-symbol mismatch into a resolved operand: 74 clean and 17
expected mismatches, versus 73/18 before the ownership pass.
