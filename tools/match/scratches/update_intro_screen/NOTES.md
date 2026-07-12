# update_intro_screen @ 0x4199e0

Advances the intro/credits text screen state machine. While the shared
frontend fade is idle, pressing the skip key (`0xb`) or seeing the active input
controller skip flag (`0x4000`) begins a fade out. Fade state `4` tears down the
intro renderables.

State `0` initializes normalized scroll progress and state `1` increments it by
`1 / (duration_seconds * 60)`, beginning a fade once progress exceeds `1.0`.

Focused proof:

```text
./match.sh scratches/update_intro_screen --full
match: 100.00%
target: 51 insns, candidate: 51 insns
prefix: 51/51 target insns
masked operands: 11 ok, 0 unresolved, 0 mismatch
```

2026-07-12 authored-owner correction: the symbol-bearing ARM body is
`cRLogo::AI()`, with the same skip input, fade state, normalized crawl, and
active-letter teardown. The old cRIntro association was false; cRIntro::AI is
a separate border-driven screen. Promoting the receiver to `Logo` preserves the
exact 51/51 Windows body and all 11 clean operands.
