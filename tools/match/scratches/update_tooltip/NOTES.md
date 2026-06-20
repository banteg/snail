# update_tooltip

First source-shaped scratch for `update_tooltip @ 0x403c20`.

This recovers the tooltip state machine using the shared frontend widget and
tooltip-state headers:

- state `1` arms the delay when the owner has `0x20000` set;
- state `2` advances `delay_progress` by `delay_step`, allocates the tooltip
  border once the delay exceeds `1.0f`, and positions it according to
  `mode_flags`;
- state `3` kills the allocated tooltip border after the owner clears
  `0x20000`;
- the final layout clamp adjusts the tooltip's anchor against the left and
  right screen edges before calling `layout_frontend_widget`.

Offsets are aligned with `include/frontend_widget.h`: `active_padding +0x220`,
`layout_x/y +0x238/+0x23c`, `layout_width/height +0x248/+0x24c`,
`layout_mode +0x25c`, `layout_center_x +0x260`, `stack_gap +0x26c`, and
`layout_anchor_x/y +0x6f4/+0x6f8`.

The return value is leftover register state in native code, so the scratch is
written as a `void` updater.

2026-06-20 frontend type pass: `TooltipState` is now shared through
`include/tooltip_state.h` as the 0x40 subobject embedded at
`FrontendWidget+0x28c`. The shared tooltip layout covers `mode_flags`, owner
pointers, delay counters, and the allocated tooltip widget pointer. Focused
matcher evidence stayed unchanged at `87.87%`, `219/218` candidate/target
instructions, `5/218` prefix, and `23 ok` masked operands.

2026-06-20 shared frontend header pass: the local `FrontendWidget` field slice
was replaced with `include/frontend_widget.h`, mapping the local names above to
the shared field names. Focused matcher evidence stayed unchanged at `87.87%`,
`219/218` candidate/target instructions, `5/218` prefix, and `23 ok` masked
operands.
