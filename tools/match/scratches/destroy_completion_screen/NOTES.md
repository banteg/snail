# destroy_completion_screen

Small exit-prompt teardown helper at 0x406060. Both BN and IDA decompiles
show it killing the three prompt widgets at `+0x10/+0x14/+0x18`, unhiding all
global borders, restoring the previous frontend state at `data_4df904+0x1b8`,
and returning the unhide result.

Exact match: 100.00%, 25/25 instructions, with all border-manager and
frontend-state operands resolved.

2026-06-17 correction: this helper belongs with the `ExitPrompt` /
`initialize_exit_prompt` / `update_completion_screen` object at `game+0x4f3ac`.
It is not the same field layout as the delivery-complete result object
initialized by `initialize_completion_screen` at `game+0x12e6df0`.

2026-07-11 authored owner: Android retains this sibling as
`cRExit::UnInit()`. The root-owned `ExitPrompt` rename remains exact at 25/25
with all nine operands clean.
