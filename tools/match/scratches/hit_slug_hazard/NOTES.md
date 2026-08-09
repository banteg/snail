# Matched

`hit_slug_hazard` matches exactly. It decrements `hit_points` at `+0xc8`,
clamps and routes through `kill_slug_hazard` on underflow, otherwise latches
`hit_flash_pending` at `+0xcc` and plays `play_slug_voice(36 - variant)`.

The voice variant uses the native float-scale idiom:
`(float)next_math_random_value() * -0.000091552734f`. A first-pass double
constant emitted a qword multiply and did not match.

2026-07-11 ownership: the exact 25-instruction body now lives on the primary
`cRSlug` type. Android and iOS both retain `cRSlug::Hit(int)`; the former also
preserves the calls to the same `Kill` and `VoicePlay` siblings.

## 2026-07-28 mobile-backed voice range

iOS `cRSlug::Hit(int)` explicitly preserves a unit-random draw multiplied by
three before selecting voice 36..38. Android independently preserves the same
draw-to-`VoicePlay` path, although its high-level decompiler drops the call
operands. The Windows spelling still uses its native negative multiply and
subtraction, but now factors that folded constant as the unit factor times
`-3.0f`. The result remains exactly 25/25 with all five operands clean.
