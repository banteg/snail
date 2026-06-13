# Matched

`hit_slug_hazard` matches exactly. It decrements `hit_points` at `+0xc8`,
clamps and routes through `kill_slug_hazard` on underflow, otherwise latches
`hit_flash_pending` at `+0xcc` and plays `play_slug_voice(36 - variant)`.

The voice variant uses the native float-scale idiom:
`(float)next_math_random_value() * -0.000091552734f`. A first-pass double
constant emitted a qword multiply and did not match.
