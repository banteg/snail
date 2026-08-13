# Authored owner — `cRWarning::UnInit`

Android exports `cRWarning::UnInit()` and calls it from
`cRSubGame::UnInit()`, matching the Windows SubGame teardown edge. The exact
Windows method releases the border at `Warning +0x0c`; the wider Android owner
stores its border at +0x14.

2026-07-11 focused Wibo verifies an exact 100.00% match, 6/6 instructions,
with two clean masked operands.

2026-07-17 paired replay: both databases now retain the authored
`void __thiscall(Warning*)` ABI and release `warning->border` through the exact
`0x10` owner. Focused matching remains exact at 6/6 instructions with two clean
masked operands.

## 2026-08-09 primary cRWarning ownership

The matcher now emits this teardown as `cRWarning::UnInit()` and binds the
owner-qualified VC6 symbol `?UnInit@cRWarning@@QAEXXZ`; `Warning` remains a
compatibility typedef. The live Windows view confirms the void `thiscall`
receiver and sole direct call at `0x43888b` from subgame teardown. Android
independently exports the same authored method and border-release edge. The
promotion is codegen-neutral: focused matching remains exact at 6/6
instructions with both masked operands clean.

## 2026-08-13 canonical analysis-owner replay

Both analysis databases now expose this receiver as `cRWarning*`; the generic
`Warning` record is retired after exact 0x10-byte layout equivalence and the
`Player +0x3f4` embed is read back as `cRWarning`. Android's exact authored
teardown remains the independent ownership witness. Focused matching stays
exact at 6/6 instructions with both operands clean.
