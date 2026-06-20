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
