# update_options_menu @ 0x41af60

First scratch for options-menu dispatch.

- Copies the two slider values into the saved sample and stream config globals.
- Rewrites the fullscreen label from `RuntimeConfig::fullscreen_enabled` each frame.
- Fullscreen clicks clear the widget click bit and toggle the saved fullscreen
  config through `set_fullscreen_mode`.
- Back clicks tear down the options menu, clear the frontend link latch, and
  restore `previous_frontend_state`.
- The audio apply helper is source-shaped as an `Options` member call even
  though the callee ignores `this`; this preserves the native `mov ecx, esi`
  setup.
- Native only updates `previous_sample_volume` when the sample volume changed
  and the preview tick sound is played.
- The source spells this as a `void` member. Earlier `int` probes only matched by
  falling through without a deliberate value on the unchanged-volume path, which
  also drives Wibo into VC6's diagnostic path.
- Focused Wibo result: 2026-06-18, 100.00%, 73/73 instructions, masked operands
  19 ok.

2026-07-11 cROptions ownership: Android and iOS preserve this state machine as
`cROptions::AI()`. Promoting the root field and receiver to `Options` is
codegen-neutral at the exact 73/73 baseline.

2026-07-14 canonical root transition: the Back path's short reloads now borrow
the typed `GameRoot` directly to clear `frontend_link_latch` and restore
`players[0].frontend_state`. The function remains exact at 73/73 instructions
with all 19 operands clean.
