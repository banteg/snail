# draw_frontend_overlay_color_lerp @ 0x40ab40

Small front-end overlay fade update/draw helper.

- The function proves the `cRFlash` color layout:
  `target` lives at `+0x04` and `current` lives at `+0x14`.
- Each channel moves 14.5% of the remaining distance toward the target each
  update.
- The overlay quad is only queued while the current alpha is above `0.01f`.
  The state word contributes the high-byte render flags through
  `state & RENDER_SCENE_MASK`.
- Full Wibo result: 2026-06-18, 100.00%, 38/38 instructions, 6 masked operands
  ok.

The shared name is codegen-neutral and ties this producer to the same scene
selection used by camera slots, BODs, sprites, and queued font entries.

Android `cRFlash::AI()` preserves the complete 0x24-byte owner, all four
14.5% channel lerps, the alpha threshold, scene mask, and current-color draw.
That body independently proves this helper is a void `cRFlash` member and that
both color fields use the shared `tColour` type.

## 2026-08-09 authored-owner promotion

The exact Windows leaf now uses primary authored `cRFlash::AI()` with
`FrontendOverlayColorLerp` retained as compatibility vocabulary. The stable
matcher target remains `draw_frontend_overlay_color_lerp`, and the exact MSVC
symbol is `?AI@cRFlash@@QAEXXZ`.

Live raw Windows xrefs show one direct call at `0x40a3ae` from
`run_frame_update`, using the same player-owned `cRFlash` initialized by the
paired leaf. Matching remains exact at 38/38 instructions with all six masked
references clean. No frontend render/state-machine or widget lane was
reopened.
