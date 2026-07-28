# advance_blink_random @ 0x4408a0

## 2026-07-26 authored BlinkRand method

Android `cRSubGame::BlinkRand()` advances its owned cursor modulo `0x18`,
stores it, and returns the indexed sample from the adjacent table. This exact
method body confirms both the SubGame receiver and the 24-sample ownership.

Exact match: 100.00%, 10/10 instructions.

This helper advances the 24-entry blink cadence table index at `+0x3bb700`
and returns the selected float sample from `+0x3bb704`. Slug AI uses the
returned cadence to schedule its next blink.

2026-07-11 ownership recovery: the temporary `BlinkRandomTable` view was
retired. The cursor and 24 samples are the final `0x64` bytes before the
embedded `cRSubGame::player`, and the helper is now a direct
`cRSubGame` method. Focused VC6 remains exact at 100.00%, 10/10
instructions. The only native xref is the slug-AI callsite, which passes the
root's embedded subgame at `GameRoot +0x74618`.
