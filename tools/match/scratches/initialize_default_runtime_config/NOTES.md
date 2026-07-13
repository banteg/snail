# `initialize_default_runtime_config` recovery notes

Target: `initialize_default_runtime_config @ 0x406c20` (`cdecl` startup
initializer).

The body has no independent code xrefs. The CRT initializer table at `0x4a1008`
points to a thunk at `0x406c10`, which tail-jumps over 11 bytes of alignment
padding to this body:

```asm
00406c10  jmp 0x406c20
00406c15  nop ... 00406c1f
```

The retained C source models the real initializer body: it seeds the saved
config blob, render flags, completion-score defaults, high-score state,
loading-screen budget values, and tutorial latch. Splitting the thunk and body
at the two aligned boundaries makes the initializer exact at 36/36
instructions with all 32 masked operands resolved; the one-instruction thunk is
tracked independently. The saved `SnailMail.cfg` blob slots have curated
references when their consumers are known, while fields with no recovered
consumer remain explicit reserved config offsets. The config-tail validation
helper at `0x42f5b0` is recovered as `validate_config_tail_stub`; it ignores its
argument and returns true.

2026-07-11 ownership recovery: the persisted bytes are now represented by one
`RuntimeConfig` object whose asserted size is the `0xc4` passed to every load
and save call. Address spacing fixes the 64-byte name field at `+0x60`, followed
by the route limit, landscape selector, high-score bank, and loading budget at
`+0xa0` through `+0xac`. The render flags are a dword at `+0x1c`: low-byte
feature tests had produced misleading byte declarations, but the default
`0x5fe` store and the window code's `0x400` test require the full word. Moving
the initializer, blob save sites, and all three conflicted field families onto
the aggregate preserved every focused instruction stream and left this scratch
at the then-current 85.71% combined thunk/body result. The later boundary split
above proves the body itself exact without changing those field owners.

2026-07-11 consumer closure: all remaining volume, fullscreen, display-mode,
steering, completion-slider, route-limit, high-score-bank, loading-budget, and
tutorial users now address fields through `g_runtime_config`. The focused
metrics of all 25 affected scratches are unchanged, including every exact
consumer. Naming the landscape selector in the still-sparse world initializer
also converts one raw-symbol mismatch into a resolved operand: 74 clean and 17
expected mismatches, versus 73/18 before the ownership pass.
