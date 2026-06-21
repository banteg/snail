# queue_axis_aligned_textured_quad_uv

Initial scratch for the explicit-UV 2D textured quad queue helper at
`0x44a9b0`.

Wibo result: 76.12%, 66 target instructions versus 68 candidate instructions.
The helper matches the non-UV queue shape; remaining residual is the same
shared-zero epilogue distance, color alpha/count store scheduling, and stack
argument register choice for the UV/layer/blend stores.

Recovered relationships:

- The active byte at `data_4b7236` is the broader render queue gate, not a
  font-only flag.
- Shares the same `FontQueueEntry` layout and validation gates as
  `queue_axis_aligned_textured_quad`.
- Stores caller-provided UV bounds at `+0x5c..+0x68`.
- Used by front-end widgets, progress bars, damage gauge, galaxy display, and
  gameplay HUD quads.

2026-06-20 render-queue chunk: the same missing-final-return probe used on the
default-UV and corner queue helpers cannot be kept here either. It likely models
native's shared incidental skip return, but under Wibo the MSVC warning path
aborts on a missing `lstrcpynA` import before producing a comparable object.
Keep the runnable explicit `return 0` until a real source spelling avoids the
extra epilogue without entering the warning path.

2026-06-21 color-copy split retry: replacing `entry->color = *color` with
integer-lane copies, including variants that write RGB, update
`g_font_queue_count`, then write alpha, regresses this helper to the mid-40%
range and adds/moves masked queue-offset mismatches. The aggregate `Color4f`
copy remains the only source-plausible shape that preserves the saved-register
copy sequence.
