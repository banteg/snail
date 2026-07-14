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

2026-06-20 local view naming: direct inclusion of the shared pause-menu header is
rejected here because this exact tail-return shape needs a release call view
whose `release_mouse_cursor()` returns `int`; `mouse_cursor_state.h` models the
shared helper as `void`. The teardown now names that call surface
`PauseMenuMouseCursorReleaseView` instead of overloading `MouseCursorState`,
keeps its local `PauseMenuTeardownView`, remains `100.00%`, `22/22`, with `8
ok` masked operands, and no longer appears as a promotable `PauseMenu` or
`MouseCursorState` duplicate in the type report.

2026-07-14 root-client consolidation: the exact tail call now traverses the
canonical root/player/cursor graph while retaining the local return-value view
needed by native codegen. Focused matching remains 22/22 with eight clean
operands.
