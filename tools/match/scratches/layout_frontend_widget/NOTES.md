# `layout_frontend_widget` notes

- Scratch-local `FrontendWidget` names only the fields touched by this layout
  pass. Shared `frontend_widget.h` has overlapping but not yet exact layout
  names for all of these offsets.
- The render flag passed into `layout_and_queue_wrapped_font_text` is
  `(g_render_flags >> 8) & 1`, matching the native load from `data_4df934`.
