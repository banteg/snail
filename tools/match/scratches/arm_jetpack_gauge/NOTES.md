# arm_jetpack_gauge

Exact at `100.00%`, `18/18`, with four clean masked operands.

2026-07-11 ownership closure: arming calls `set_snail_jetpack(1)` on the
presentation embedded in `GameRoot::subgame`'s owned player. The synthetic
`ArmJetpackPresentationView` is retired without moving codegen.

Android identifies this exact transition as `cRSubHover::On()`: it writes the
same state/progress/wobble lanes, calls `cRSnail::SetJetPack(1)`, and tail-calls
`cRSubHover::JetInit()`. The Windows `SubHover` member and both callees now use
their authored void contracts while preserving the exact 18/18 instructions.
