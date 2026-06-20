# draw_frontend_widget @ 0x401130

Starter scratch for the front-end border/widget renderer.

Models the recovered render gate, slider track quads, sprite/icon branch,
nine-slice border body, optional focus glow, and the real `queue_axis_aligned_textured_quad_uv`
and color helpers. It intentionally keeps the view scratch-local because the
shared `FrontendWidget` header does not yet expose the full render block.

Expected residuals:
- stack-local and x87 scheduling are still decompiler-shaped;
- the tail text/special-widget paths are incomplete;
- color lane names are relationship-first and need promotion only after exact
  layout confidence improves.

2026-06-20 code-shape pass:

- Spelling the selected-widget icon wobble inversion as `wobble * -1.0f`
  recovers the native multiply form instead of VC6's `fchs`, removing the
  `-1.0f` masked constant mismatch and improving the focused match from
  `39.42%` to `39.71%`.
- Explicitly no-op constructing the four local `Color4f` temporaries matches
  the native prologue constructor calls and moves the focused match to
  `40.34%`, `686/712` candidate/target instructions, with masked operands at
  `46 ok / 2 mismatch`.
- The remaining `8.0f` versus `6.0f` special-border mismatch is an alignment
  artifact: both IDA and the scratch keep the source-level `width -= 8.0f` and
  `height -= 6.0f` order. The remaining constructor call mismatch is tied to
  stack-slot/register ownership in the incomplete tail, not a reason to remove
  the explicit local constructors.
