# uninit_thanks_screen @ 0x4340c0

The exact teardown releases its message widget through
`GameRoot::border_manager`, then returns the front-end state machine through
`GameRoot::players[0].frontend_state = 14`. This proves the former root +0x1b8
store belongs to the first root `GamePlayer`, not to the screen controller.

Focused Wibo remains exact at 8/8 instructions with three clean operands.

2026-07-18 live-analysis lifecycle pass: IDA's unnamed incidental-return
prototype and Binary Ninja's raw `arg1` form are now the exact void
`uninit_thanks_screen(ThanksScreen*)` ABI. Both exports recover the borrowed
`message_widget` teardown and the root-owned player front-end transition.
