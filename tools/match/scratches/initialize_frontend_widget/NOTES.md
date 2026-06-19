# initialize_frontend_widget @ 0x401d30

Starter scratch for the shell-font front-end widget constructor.

Models list insertion, tooltip owner reset, border style presets 20-23, text
copy/layout anchors, highlight state, slider child creation, and the final
layout call. It uses local offsets because the complete widget render/layout
block is not yet promoted to the shared header.

Expected residuals:
- stack-local color ordering is still decompiler-shaped;
- color lane names and a few padding fields need cross-checking against
  `draw_frontend_widget` and `update_frontend_widget_interaction`;
- slider child calls are semantic but not scheduled to match.
