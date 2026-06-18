# update_help_screen

Handles the Help-screen Back button. The owner object currently only proves a
single `FrontendWidget*` at `+0x00`; when its click flag `0x20` is set, the
helper clears the flag, destroys the Help screen, routes the frontend back to
state `2`, and marks the frontend state dirty.

The source-shape correction is that `destroy_help_screen` is a `HelpScreen`
member, not a free helper. Keeping `this` live in `ecx` makes VC6 load the
Back button into `edx`, matching native without register tricks.

Full Wibo result: 2026-06-18, 100.00%, 12/12 instructions, 3 masked operands
ok.
