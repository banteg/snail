# uninit_pause_menu

Small pause-menu teardown helper at 0x440600. Both BN and IDA decompiles show
it killing the three stored pause-menu borders through the global border manager
and then releasing the shared mouse cursor state at data_4df904+0x290.

Exact match: 100.00%, 22/22 instructions, with all border-manager and
mouse-cursor operands resolved.

2026-06-18 naming correction: `initialize_pause_menu` proves the slot order is
`options_widget +0x00`, `end_game_widget +0x04`, and `resume_widget +0x08`.
The earlier local names `title/resume/quit` were misleading but codegen-neutral.
