# advance_blink_random @ 0x4408a0

Exact match: 100.00%, 10/10 instructions.

This helper advances the 24-entry blink cadence table index at `+0x3bb700`
and returns the selected float sample from `+0x3bb704`. Slug AI uses the
returned cadence to schedule its next blink.
