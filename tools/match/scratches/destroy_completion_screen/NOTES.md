# destroy_completion_screen

Small exit-prompt teardown helper at 0x406060. Both BN and IDA decompiles
show it killing the three prompt widgets at `+0x10/+0x14/+0x18`, unhiding all
global borders, restoring the previous frontend state at `data_4df904+0x1b8`,
and returning with no authored value.

Exact match: 100.00%, 25/25 instructions, with all border-manager and
frontend-state operands resolved.

2026-06-17 correction: this helper belongs with the `Exit` /
`initialize_exit_prompt` / `update_completion_screen` object at `game+0x4f3ac`.
It is not the same field layout as the delivery-complete result object
initialized by `initialize_completion_screen` at `game+0x12e6df0`.

2026-07-11 authored owner: Android retains this sibling as
`cRExit::UnInit()`. The root-owned `Exit` rename remains exact at 25/25
with all nine operands clean.

2026-07-13 canonical root graph: widget teardown now follows the root-owned
`BorderManager`, and the restored state follows `players[0]`. The typed global
reload spelling preserves the exact 25/25 stream and all nine clean operands.

2026-07-14 return-contract correction: Android retains this lifecycle edge as
`cRExit::UnInit()`, all callers discard EAX, and the native tail only leaks the
incidental result of the preceding border-stack call. Modeling both methods as
`void` preserves the exact instruction stream without assigning ownership to
that register accident.
