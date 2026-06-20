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

2026-06-20 frontend type pass: `initialize_frontend_widget` and
`layout_frontend_widget` are modeled as returning the same word result, not a
widget pointer. This matches the exact `layout_frontend_widget` helper and the
exact `initialize_exit_prompt` branches that return the initializer result in
`eax`. Focused matcher evidence for this scratch stayed unchanged at `45.21%`,
`270/429` candidate/target instructions, with the same `38 ok / 1 unresolved /
1 mismatch` masked audit.
