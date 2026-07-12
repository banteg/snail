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

2026-07-12 border-tail ownership pass: the transition gate, target widget, and
progress at root `+0x440ec/+0x440f8/+0x440f0` are now typed as the embedded
`BorderManager` delayed-widget lane at manager
`+0x435a0/+0x435ac/+0x435a4`. The typed owner is codegen-neutral and preserves
`40.34%`, `686/712`, and `46 ok / 2 mismatch`.

2026-07-12 color-lifetime pass:

- The iOS `Border.o` symbol proves this routine is authored
  `cRBorder::Draw()`; the manifest now records that provenance and no longer
  claims a text draw that is absent from the native function.
- Native copies the widget color at `FrontendWidget+0x1dc` into a stack-owned
  16-byte slider color before either slider-strip call. This is real value
  ownership, not a borrowed pointer; the current scratch still keeps the
  pointer form because introducing the copy before recovering the surrounding
  lifetimes destabilizes the whole register schedule.
- The native frame contains four `Color4f` objects constructed in the prologue
  plus a fifth branch-local slot. The latter is written directly for the
  shadow and then reused as a newly constructed delayed-glow color. Its
  constructor at the delayed-glow gate is now represented explicitly, moving
  the focused match to `40.43%`, `688/712`, with `48 ok / 1 mismatch` masked
  operands. Splitting the scratch's persistent color placeholders into those
  exact lifetimes remains honest residual work.
