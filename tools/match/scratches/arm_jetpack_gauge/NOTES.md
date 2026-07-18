# arm_jetpack_gauge

Exact at `100.00%`, `18/18`, with four clean masked operands.

2026-07-11 ownership closure: arming calls `set_snail_jetpack(1)` on the
presentation embedded in `GameRoot::subgame`'s owned player. The synthetic
`ArmJetpackPresentationView` is retired without moving codegen.

Android identifies this exact transition as `cRSubHover::On()`: it writes the
same state/progress/wobble lanes, calls `cRSnail::SetJetPack(1)`, and tail-calls
`cRSubHover::JetInit()`. The Windows `SubHover` member and both callees now use
their authored void contracts while preserving the exact 18/18 instructions.

## 2026-07-14 hover lifecycle ownership

The authored `On` edge now explicitly transitions the child from
`SUB_HOVER_STATE_INACTIVE` to `SUB_HOVER_STATE_ACTIVE`. Focused output remains
exact at 18/18 instructions with all four operands clean.

## 2026-07-18 durable SubHover replay

The focused BN/IDA lane now preserves the authored void `SubHover*` receiver,
inactive-to-active state edge, root-owned Snail presentation call, and direct
JetInit member call in both tracked artifacts. Exact owner-size verification
covers the 0x214-byte child and its complete 0xb4-byte Sprite dependency. The
matcher remains exact at 18/18 with all four operands clean; the improvement is
analysis-only and introduces no fakematch.
