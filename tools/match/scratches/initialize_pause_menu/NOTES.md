# initialize_pause_menu @ 0x440660

First scratch for the authored `cRSubPause::Init()` member.

- Allocates `End Game`, `Options`, and `Resume` widgets from the global border
  manager.
- Confirms the `SubPause` slot order as `options_widget +0x00`,
  `end_game_widget +0x04`, and `resume_widget +0x08`.
- Assigns shortcut keys 11, 111, and 5, stacks Options below End Game, stacks
  Resume below Options, and captures the shared mouse cursor.
- Focused Wibo result: 2026-06-18, 100.00%, 88/88 instructions, masked
  operands 23 ok.

Source-shape note:

- Do not keep a local `BorderManager*`; native reloads `g_game_base + 0xb4c`
  for each allocation. A saved manager pointer keeps the value in `edi` and
  regresses to 83.62%.

2026-07-13 root-owner cleanup: each allocation now reloads the typed global
and follows `GameRoot::border_manager`; no manager local is retained. Mouse
capture follows `players[0].mouse_cursor`. This canonical spelling preserves
the exact 88/88 stream and all 23 clean operands.

2026-07-14 owner closure: leaked iOS symbols place `cRSubPause::Init()` in
`SubGame.o`, while the Android body independently stores the three allocated
widgets at `+0x00/+0x04/+0x08` and captures the mouse cursor. The owner is the
0x0c-byte `SubPause` embedded at `SubgameRuntime +0x14`; the method is `void`
and remains exact at 88/88 instructions with all 23 operands clean.

2026-07-18 focused replay closure: the `SubgameRuntime` replay now owns the
three `cRSubPause` lifecycle symbols, prototypes, and reanalysis targets while
the broader path-template header remains the aggregate structural source.
Tracked Binary Ninja and IDA output both recover the three widget fields,
`GameRoot::border_manager`, and `players[0].mouse_cursor`; no raw receiver or
root offset remains.
