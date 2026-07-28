# initialize_blink_random @ 0x4408c0

## 2026-07-26 void ABI and authored owner

Android and iOS `cRSubGame::BlinkRandInit()` both reset the owned cursor and
fill exactly 24 samples with reciprocal random intervals derived from
`1 / (((rand / 32768) + 1) * 60)`. Both mobile bodies return void. Removing the
stale Windows integer return preserves the exact 21/21 instruction match while
recovering the authored ABI instead of treating the final random residue as a
result.

Exact match: 100.00%, 21/21 instructions.

This helper resets the blink cadence index at `+0x3bb700` and fills the
24-entry table at `+0x3bb704` with random reciprocal intervals:

`1.0 / (((float)next_math_random_value() * 0.000030517578 + 1.0) * 60.0)`.

2026-07-11 ownership recovery: the synthetic whole-subgame
`BlinkRandomTable` view was removed. `blink_random_index` and
`blink_random_samples` now live directly on `cRSubGame` at `+0x3bb700`
and `+0x3bb704`; the table ends exactly where the owned player begins.
Focused VC6 remains exact at 100.00%, 21/21 instructions, with five clean
masked operands. The only native xref is the root-world bootstrap.

2026-07-25 sample cursor ownership: native ESI starts at
`cRSubGame::blink_random_samples`, advances by one four-byte float, and
stores through `[esi-4]` for exactly 24 iterations. It borrows one table
element at a time; it is not a pointer to the complete 24-float array and does
not recover the enclosing runtime through a negative bias.

Binary Ninja's exact ESI lifetime (`RegisterVariableSourceType`, index `13`,
storage `72`) now replays as `float* blink_sample_cursor`. IDA independently
preserves the same `float*` increment and previous-element store, while the
guarded replay also verifies the index at `+0x3bb700`, the table at
`+0x3bb704`, and the adjacent `Player` boundary at `+0x3bb764`.
No matcher source changes: the initializer remains exact at 21/21
instructions with all five operands clean.

2026-07-13 analysis propagation: the path-template runtime view now closes the
entire preceding owner band as `GarbageHazardPool`,
`RingOrSpecialEffectPool`, `SlugVoiceManager`, HUD handles, and the exact
`FringeManager`. Its terminal count lands at `+0x3bb6fc`; the index and 24
samples then still end exactly at `Player +0x3bb764`. Binary Ninja declaration
preview verifies the complete enclosing layout and reverts. Focused matching
remains exact at 21/21 with all five operands clean.
