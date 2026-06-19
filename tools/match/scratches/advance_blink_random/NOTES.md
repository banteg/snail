# advance_blink_random @ 0x4408a0

Exact match: 100.00%, 10/10 instructions.

This helper advances the 24-entry blink cadence table index at `+0x3bb700`
and returns the selected float sample from `+0x3bb704`. Slug AI uses the
returned cadence to schedule its next blink.

2026-06-20 type consolidation: `BlinkRandomTable` now lives in
`include/blink_random_table.h` with the large `+0x3bb700` index and
`+0x3bb704` sample table layout. Focused rerun remains exact at 100.00%,
10/10 instructions. The slug AI callsite also includes the shared header and
keeps its existing 66.15% residual profile.
