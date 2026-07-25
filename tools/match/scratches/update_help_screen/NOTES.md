# update_help_screen

Handles the Help-screen Back button. The owner object currently only proves a
single `FrontendWidget*` at `+0x00`; when its click flag `0x20` is set, the
helper clears the flag, destroys the Help screen, routes the frontend back to
state `2`, and marks the frontend state dirty.

The source-shape correction is that `destroy_help_screen` is a `Help`
member, not a free helper. Keeping `this` live in `ecx` makes VC6 load the
Back button into `edx`, matching native without register tricks.

Full Wibo result: 2026-06-18, 100.00%, 12/12 instructions, 3 masked operands
ok.

2026-07-11 cRHelp ownership: Android and iOS name this exact method
`cRHelp::AI()`. The shared four-byte `Help` owner preserves the 12/12 body and
the root front-end transition relationship.

2026-07-14 canonical root transition: the Back action now reaches
`GameRoot::players[0]` from a typed process root, preserving both the frontend
state and redispatch ownership while remaining exact at 12/12 instructions
with all three operands clean.

2026-07-25 lifecycle replay closure: Binary Ninja and IDA now both render the
four-byte owner as `Help*`, borrow `help->back_button`, retain
`destroy_help_screen(help)`, and route through typed
`GameRoot::players[0]` fields. Strict tracked canaries reject the former
`void*`/raw-root output in either lane.
