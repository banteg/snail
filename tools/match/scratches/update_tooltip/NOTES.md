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

2026-06-20 frontend type pass: `FrontendWidgetTooltip` is now shared through
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

2026-06-20 state-2 layout pass: spelling the armed-owner path as the positive
branch keeps the reset-to-state-1 block physically late, matching native's
state-2 branch layout instead of inlining the reset before the allocation body.
Focused Wibo improves to `89.70%`, still `219/218` candidate/target
instructions with `23 ok` masked operands. The remaining leading residual is
the extra `test eax, eax` after the third state-dispatch decrement; native
reuses the `dec` flags directly.

2026-06-21 dispatch follow-up: spelling the nested state checks with
pre-decrement expressions is codegen-neutral at 89.70% and still emits the
extra `test eax, eax`. A label-based dispatch that preserves the native physical
case order (`state 3`, then `state 2`, then `state 1`) requires scoped case
bodies in C++ and regresses to 75.97% by disturbing the layout body. Keep the
nested source shape; the remaining leading `dec`/`test` split is not fixed by
surface dispatch syntax.

2026-07-12 authored state-machine closure:

- Expressing the three states as the natural `switch (state)` recovers VC6's
  native `dec`/branch dispatch and removes the one extra candidate `test`.
  This is the authored control-flow shape, not a synthetic register constraint.
- The iOS `Border.o` symbol set names this exact embedded controller
  `cRToolTip`. The shared C++ owner is now `FrontendWidgetTooltip`, matching the
  Binary Ninja and C analysis types: the enclosing widget owns the 0x40-byte
  controller, its two widget backlinks are borrowed, and its live tooltip
  handle refers to a `BorderManager`-owned widget that the controller releases.
- Focused matching is proof-grade at 100.00%, 218/218 instructions, a 218/218
  prefix, and 23 clean masked operands.

2026-07-14 root-client consolidation: tooltip allocation and release now use
`GameRoot::border_manager`; mouse-anchored tooltips read
`GameRoot::players[0].mouse_cursor.saved_x/saved_y`. This proves root
+0x29c/+0x2a0 are the saved cursor pair and remains exact at 218/218
instructions with 23 clean operands.
