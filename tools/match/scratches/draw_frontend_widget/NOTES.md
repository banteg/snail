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
