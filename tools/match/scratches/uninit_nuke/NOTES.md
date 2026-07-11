# uninit_nuke

- Exact match: 100.00%, 18/18 instructions.
- Uses a typed `Nuke` layout: active `state` at `+0x00` and the
  25 sprite-owner slots at `+0x18`.
- Semantics: only active state `1` tears down the effect; it kills all 25
  orbit sprites and then clears the controller state to `0`.
- This is the teardown anchor for the ring/special-effect controller armed by
  `initialize_nuke` and advanced by `update_nuke`.

2026-07-11 authored-owner recovery: Android and iOS retain
`cRNuke::UnInit()`. Android uses the same state and 25-slot offsets, and
`cRSubGoldy::AI()` owns the teardown edge. The shared exact 0x7c-byte Windows
type is now `Nuke`. Focused Wibo remains exact at 18/18 instructions with one
clean masked operand.
