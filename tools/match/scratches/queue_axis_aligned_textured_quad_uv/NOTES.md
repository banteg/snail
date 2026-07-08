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

2026-06-21 count-store sweep: moving the `g_font_queue_count` publish after the
entry field stores improves focused Wibo from 76.12% to 92.54%, with 68
candidate instructions versus 66 target instructions and all 19 masked operands
clean. Intermediate placements monotonically recovered the queue-field offsets;
the retained after-`blend` spelling removes the previous masked offset
mismatches while preserving the aggregate color copy. The residual is now only
the moved count store plus the known shared zero-return epilogue.

2026-06-21 granular count-store retry: placements before color and after each
field through `layer` were retested. Scores rise monotonically from 59.09% to
89.55% as the store moves later, but only the retained after-`blend` placement
reaches 92.54% and keeps all 19 masked operands clean. Native's earlier count
publish remains a scheduling tradeoff; moving it back reintroduces field-offset
mismatches.

2026-06-21 signature/tail retry: a `void` helper removes the explicit zero
return in source, but it also changes the saved-register set and drops the
focused match to 24.43%. Removing only the success `return offset` keeps the
`int` signature but falls to 67.67% and dirties the queue-offset audit. Keep the
current runnable `int` source with the explicit skip return despite the native
incidental return register.

2026-07-09 family sync: count-before-blend (axis-aligned non-UV order) drops to
89.55%. Early-out rewrite is neutral at 92.54%. Keep blend-before-count.
