# uninit_thanks_screen @ 0x4340c0

The exact teardown releases its message widget through
`GameRoot::border_manager`, then returns the front-end state machine through
`GameRoot::players[0].frontend_state = 14`. This proves the former root +0x1b8
store belongs to the first root `GamePlayer`, not to the screen controller.

Focused Wibo remains exact at 8/8 instructions with three clean operands.

2026-07-18 live-analysis lifecycle pass: IDA's unnamed incidental-return
prototype and Binary Ninja's raw `arg1` form are now the exact void screen
teardown ABI. Both exports recover the borrowed
`message_widget` teardown and the root-owned player front-end transition.

2026-08-12 cRSplash ownership recovery: Android `cRSplash::UnInit()` at
`0x6a8c0` performs the same two effects as Windows: kill the owner-held message
border and set front-end state 14. iOS has no standalone teardown export;
`cRSplash::AI()` inlines both effects. The exact mobile lifecycle establishes
the authored owner name `cRSplash` without importing its different field
offsets into the 0x14-byte Windows controller.
