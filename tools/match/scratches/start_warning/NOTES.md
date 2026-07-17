# Authored owner — `cRWarning::Start`

Android `cRDamageGuage::AI()` calls `cRWarning::Start()` through the embedded
warning owner. Both ports seed the phase, enter state 2, and unhide the owned
border; the wider Android layout also resets a mobile-only phase lane.

2026-07-11 focused Wibo verifies an exact 100.00% match, 4/4 instructions,
with one clean masked operand.

## 2026-07-14 warning lifecycle ownership

`Start` now enters `WARNING_STATE_FADING` explicitly. Seeding `phase` to 1.0
means the next AI tick immediately wraps into the opaque state and plays the
warning sample. Matching remains exact at 4/4 instructions with one clean
operand.

2026-07-17 paired replay: IDA now agrees with Binary Ninja on the authored
`void __thiscall(Warning*)` ABI, including `warning->phase`, `state`, and owned
`border`. Focused matching remains exact at 4/4 instructions with one clean
masked operand.
