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

## 2026-08-09 primary cRWarning ownership

The matcher now emits this transition as `cRWarning::Start()` and binds the
owner-qualified VC6 symbol `?Start@cRWarning@@QAEXXZ`; `Warning` remains a
compatibility typedef. The live Windows view confirms the void `thiscall`
receiver and sole direct call at `0x4411a8` from the damage-gauge controller.
Android independently exports the same authored method and caller edge. The
promotion is codegen-neutral: focused matching remains exact at 4/4
instructions with its one masked operand clean.

## 2026-08-13 canonical analysis-owner replay

Both decompilers now render the receiver and its `Player +0x3f4` embed as
`cRWarning`, after guarded retirement of the layout-equivalent generic record.
The replay also refreshes the damage-gauge caller that supplies the embedded
owner. Focused matching remains exact at 4/4 instructions with its one operand
clean.
