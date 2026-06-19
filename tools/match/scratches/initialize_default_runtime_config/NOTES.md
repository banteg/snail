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
naked/asm shim or fake prologue. Several config slots remain as raw `data_`
globals until their meanings are recovered from consumers.

Current retained Wibo result: 85.71%, 48 target instructions vs 36 candidate
instructions. The missing 12 instructions are the leading `jmp` plus padding.
Masked operand audit noise is from unrecovered config-slot names and three
neighboring globals whose current reference aliases point at adjacent fields.
