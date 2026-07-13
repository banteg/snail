# initialize_blink_random @ 0x4408c0

Exact match: 100.00%, 21/21 instructions.

This helper resets the blink cadence index at `+0x3bb700` and fills the
24-entry table at `+0x3bb704` with random reciprocal intervals:

`1.0 / (((float)next_math_random_value() * 0.000030517578 + 1.0) * 60.0)`.

2026-07-11 ownership recovery: the synthetic whole-subgame
`BlinkRandomTable` view was removed. `blink_random_index` and
`blink_random_samples` now live directly on `SubgameRuntime` at `+0x3bb700`
and `+0x3bb704`; the table ends exactly where the owned player begins.
Focused VC6 remains exact at 100.00%, 21/21 instructions, with five clean
masked operands. The only native xref is the root-world bootstrap.

2026-07-13 analysis propagation: the path-template runtime view now closes the
entire preceding owner band as `GarbageHazardPool`,
`RingOrSpecialEffectPool`, `SlugVoiceManager`, HUD handles, and the exact
`FringeManager`. Its terminal count lands at `+0x3bb6fc`; the index and 24
samples then still end exactly at `Player +0x3bb764`. Binary Ninja declaration
preview verifies the complete enclosing layout and reverts. Focused matching
remains exact at 21/21 with all five operands clean.
