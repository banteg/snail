# `layout_frontend_widget` notes

- Scratch-local `FrontendWidget` names only the fields touched by this layout
  pass. Shared `frontend_widget.h` has overlapping but not yet exact layout
  names for all of these offsets.
- The render flag passed into `layout_and_queue_wrapped_font_text` is
  `(g_render_flags >> 8) & 1`, matching the native load from `data_4df934`.
- 2026-06-20 layout-tail pass: focused Wibo improves from 78.06% to 86.44%,
  with 177/177 instructions and the same 20 clean masked operands. Moving the
  `layout_top_bits` read after the `widget_flags` reload recovers the native
  post-text-layout schedule (`texture_hit_x` store, flags reload, then
  `texture_hit_y` store). Computing `result = flags & 0x100000` while driving
  the slider-hit rectangle from the preserved `flags` value also restores the
  native separate `test eax, eax` before recursive child layout. Rejected
  probes: reordering the authored-frame locals regressed to 77.97%, naming all
  wrapped-text call arguments overgrew the frame to 0x1c and regressed to
  74.73%, and lane-view/output-pointer locals were codegen-neutral. Remaining
  residuals are authored-frame load scheduling, wrapped-text argument register
  assignment, and the recursive self-call target spelling (`call L0` versus
  candidate relocation), with no unresolved operands.
- 2026-06-20 larger-chunk audit: moving only the `authored_width` declaration
  after the layout pointer setup is codegen-neutral at 86.44% and leaves the
  same width-load hoist. Staging only `layout_mode`, `layout_center_x`, and
  `idle_text_color` before the wrapped-text call regresses to 72.11% by growing
  the frame to 0x0c. Loading `layout_top_bits` before storing
  `texture_hit_x` regresses to 78.53% by moving the preserved flags owner from
  `ecx` to `edx` and disturbing the recursive tail. Keep the current
  post-call read/store schedule.
- 2026-06-21 authored-frame pass: delaying the frame-width read until after the
  authored-left store and reading that lane through a narrow volatile view
  improves focused Wibo from 86.44% to 97.18%, keeps 177/177 instructions, and
  keeps all 20 masked operands clean. Reusing `result` for the authored-height
  temporary restores the wrapped-text call argument setup. Forcing the
  authored-left load volatile makes the authored-frame branch exact through
  instruction 32, but regresses the full function to 88.14% by disturbing the
  wrapped-text call registers. Pointer/ref spellings for the retained width and
  height lanes are codegen-neutral at 97.18%; the remaining local residual is
  the width load/store placement plus the known recursive self-call relocation
  spelling.
- 2026-06-21 width/top scheduling follow-up: moving the authored width load and
  layout-width store toward the addressed native order regresses to
  96.05%-96.61% by shortening the exact prefix to 21 instructions. Moving the
  `layout_top_bits` load before `texture_hit_x` store is worse (89.27% on the
  retained branch shape), while placing it between the X store and flags reload
  is codegen-neutral at 97.18%. The current volatile-width ordering remains the
  best whole-function tradeoff despite the local diff.
- 2026-07-12 caller agreement: `update_frontend_widget_interaction` now passes
  this same `+0x238/+0x23c/+0x248/+0x24c` layout block to the wrapped-text
  helper. The later `+0x240/+0x244` pair remains the derived/clamped hit-test
  position owned by this member, closing the previously conflicting caller
  view.
