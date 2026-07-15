# draw_frontend_widget @ 0x401130

Recovered scratch for the front-end border/widget renderer.

Models the recovered render gate, slider track quads, sprite/icon branch,
nine-slice border body, optional focus glow, and the real `queue_axis_aligned_textured_quad_uv`
and color helpers. The shared `FrontendWidget` view owns the render fields, and
the native function ends after the delayed glow; there is no missing text or
special-widget tail.

Expected residuals:
- register selection and some x87/argument scheduling remain source-shape
  residuals;
- color lane names are relationship-first and need promotion only after exact
  layout confidence improves.

2026-06-20 code-shape pass:

- Spelling the selected-widget icon wobble inversion as `wobble * -1.0f`
  recovers the native multiply form instead of VC6's `fchs`, removing the
  `-1.0f` masked constant mismatch and improving the focused match from
  `39.42%` to `39.71%`.
- Explicitly no-op constructing the four local `tColour` temporaries matches
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
- The native frame contains four `tColour` objects constructed in the prologue
  plus a fifth branch-local slot. The latter is written directly for the
  shadow and then reused as a newly constructed delayed-glow color. Its
  constructor at the delayed-glow gate is now represented explicitly, moving
  the focused match to `40.43%`, `688/712`, with `48 ok / 1 mismatch` masked
  operands. Splitting the scratch's persistent color placeholders into those
  exact lifetimes remains honest residual work.

2026-07-13 extended-sprite ownership pass:

- Exact `border_sprite_extend` proves the contextual sprite lane at
  `FrontendWidget+0x5c..+0x68`: enable and wobble-direction bytes, the hot
  texture at `+0x60`, hit-mask texture at `+0x64`, and a third stored texture
  at `+0x68`. The draw path consumes the enable, direction, and hot texture;
  `border_mouse_test` independently consumes the enable and hit-mask aliases.
- Replacing the remaining raw-offset render reads with the shared owner is
  codegen-neutral: the focused result remains the honest `40.43%`, `688/712`,
  with `48 ok / 1 mismatch` masked operands.
- Re-testing the native slider-color value copy changes the candidate to
  `38.44%`, `698/712`, without recovering the target's larger frame. It remains
  reverted at this point in the history until the surrounding stack-object
  lifetimes can be recovered as a coherent source shape.

2026-07-13 render-lifetime closure:

- Live Binary Ninja disassembly proves the complete native extent ends at
  `0x401a60`, immediately after the delayed-glow quads. The earlier note about
  an unrecovered text/special-widget tail was stale.
- The native frame has five distinct 16-byte `tColour` slots: white and slider
  objects, two additional prologue-constructed objects, and one branch-local
  slot shared by the shadow constructor and the later delayed-glow default
  constructor. The slider now truthfully owns a value copy of
  `current_text_color`; shadow and glow use non-overlapping lexical objects that
  VC6 reuses at the same stack address.
- Width and height have one lifetime from the first slider test through the
  nine-slice body. Right and bottom begin only before their first respective
  quad, while the nine-slice texture and fill color are read directly from the
  owning widget. These are native lifetime/ownership facts, not register
  coercions.
- The recovered candidate now uses the exact native `0x78` frame and exact four
  prologue constructor receivers. It improves the focused result from
  `40.43%`, `688/712`, `48 ok / 1 mismatch` to `67.28%`, `694/712`, with
  `61 ok / 0 mismatch` masked operands. The two `reserved_color_*` names remain
  explicit placeholders because the binary proves their storage and lifetime,
  but not their authored names.

## 2026-07-14 root ownership closure

Both delayed-glow paths now reach the canonical `GameRoot*` and its embedded
`BorderManager` without a repeated cast from a scratch-local `char*` global.
The manager owns the delayed-widget handle, active latch, and progress scalar;
the widget only borrows that state while drawing. Focused output is unchanged
at 67.28%, 694/712 instructions, with all 61 operands clean.

## 2026-07-15 authored draw replay

iOS and Android both retain this renderer as `cRBorder::Draw()`, with the same
slider, sprite, nine-slice, shadow, and selected-widget glow branches. The sole
Windows call at `0x4030ea` loads the widget into `ecx`, calls this function,
and immediately overwrites `eax`; the mobile exits likewise preserve unrelated
constructor or quad-queue results. The authored contract is therefore a void
member on the complete `FrontendWidget` owner, not a scalar render result.

The IDA front-end lane now replays that receiver and ABI. Binary Ninja exposes
one unique register-backed `ecx` parameter after bounded timeout reanalysis, so
the width-gated narrow lane safely replays its `FrontendWidget* widget`
annotation and the complete field graph. Binary Ninja still retains a stale
explicit return/calling-convention shell; the authored void ABI remains guarded
function-recreation debt instead of being claimed without verification. This is
ownership recovery only: the focused scratch remains honestly partial at
67.28%, 694/712 instructions, prefix 3/712, with all 61 operands clean and no
source-shape coercion.
