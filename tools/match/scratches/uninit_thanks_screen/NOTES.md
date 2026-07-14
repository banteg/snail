# uninit_thanks_screen @ 0x4340c0

The exact teardown releases its message widget through
`GameRoot::border_manager`, then returns the front-end state machine through
`GameRoot::players[0].frontend_state = 14`. This proves the former root +0x1b8
store belongs to the first root `GamePlayer`, not to the screen controller.

Focused Wibo remains exact at 8/8 instructions with three clean operands.
