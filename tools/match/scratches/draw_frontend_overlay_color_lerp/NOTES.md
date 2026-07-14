# draw_frontend_overlay_color_lerp @ 0x40ab40

Small front-end overlay fade update/draw helper.

- The function proves the `FrontendOverlayColorLerp` color layout:
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
