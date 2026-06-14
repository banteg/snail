# initialize_blink_random @ 0x4408c0

Exact match: 100.00%, 21/21 instructions.

This helper resets the blink cadence index at `+0x3bb700` and fills the
24-entry table at `+0x3bb704` with random reciprocal intervals:

`1.0 / (((float)next_math_random_value() * 0.000030517578 + 1.0) * 60.0)`.
