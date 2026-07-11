# destroy_challenge_setup_screen @ 0x4161f0

First structured scratch for the challenge setup/front-end level selection
teardown.

- Full Wibo result: 2026-06-18, 100.00%, 96/96 instructions, 32 masked
  operands ok.
- The controller stores a borrowed `SubgameRuntime*` at `+0x00`; the mode
  selector is the runtime's `level_mode` at `+0x40`.
- Mode `0` tears down the postal level navigation/play/back widgets.
- Mode `1` tears down the challenge speed/difficulty/play/replay/back widgets.
- Mode `4` tears down the time-trial level navigation/play/replay/back widgets.
- The sparse `switch` is source-shaped: VC6 emits the native `sub/dec/sub`
  dispatch for modes `0`, `1`, and `4`.

2026-07-11 ownership closure: removing the synthetic game view and reading the
mode through `SubgameRuntime` is codegen-neutral. Focused Wibo remains exact at
96/96 instructions with 32 clean masked operands.

2026-07-11 cRGUI ownership: Android and iOS retain `cRGUI::UnInit()`, and the
Android body independently branches on modes 0, 1, and 4 while killing the
same +0x04 through +0x24 widget slots. Windows stays exact at 96/96.
