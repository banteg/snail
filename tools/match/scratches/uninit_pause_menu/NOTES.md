# uninit_pause_menu

Small pause-menu teardown helper at 0x440600. Both BN and IDA decompiles show
it killing the three stored pause-menu borders through
`GameRoot::border_manager` and then releasing
`GameRoot::players[0].mouse_cursor`.

Exact match: 100.00%, 22/22 instructions, with all border-manager and
mouse-cursor operands resolved.

2026-06-18 naming correction: `initialize_pause_menu` proves the slot order is
`options_widget +0x00`, `end_game_widget +0x04`, and `resume_widget +0x08`.
The earlier local names `title/resume/quit` were misleading but codegen-neutral.

2026-07-14 ownership correction: leaked iOS symbols place
`cRSubPause::UnInit()` in `SubGame.o`, and Android independently consumes the
same three-pointer owner at `+0x00/+0x04/+0x08`. The owner is the 0x0c-byte
`SubPause` embedded at `SubgameRuntime +0x14`. Every recovered Windows caller
ignores a result, and the final 8-instruction
`MouseCursorState::release_mouse_cursor()` helper does not establish `EAX`;
any apparent integer return was incidental register state. Expressing the
side-effect-only `void` method and both real owners directly preserves VC6's
native final-call sequence at 22/22 instructions with all eight masked
operands clean, so the former `PauseMenuTeardownView` and
`PauseMenuMouseCursorReleaseView` shells were removed.
