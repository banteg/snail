# Authored owner — `cRWarning::Stop`

Android and iOS retain `cRWarning::Stop()`. Android
`cRDamageGuage::AI()` calls it through the embedded warning owner, matching
Windows; both clear the state and hide the owned border.

2026-07-11 focused Wibo verifies an exact 100.00% match, 3/3 instructions,
with one clean masked operand.

## 2026-07-14 warning lifecycle ownership

`Stop` now returns the owned actor to `WARNING_STATE_INACTIVE` before hiding
its border. Matching remains exact at 3/3 instructions with one clean operand.

2026-07-17 paired replay: IDA now agrees with Binary Ninja on the authored
`void __thiscall(Warning*)` ABI and renders the inactive state plus owned border
directly. Focused matching remains exact at 3/3 instructions with one clean
masked operand.
