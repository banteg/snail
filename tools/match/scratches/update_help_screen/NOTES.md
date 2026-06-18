# update_help_screen

Handles the Help-screen Back button. The owner object currently only proves a
single `FrontendWidget*` at `+0x00`; when its click flag `0x20` is set, the
helper clears the flag, destroys the Help screen, routes the frontend back to
state `2`, and marks the frontend state dirty.

Focused Wibo is 75.00%, 12/12 instructions, with three clean masked operands.
The only residual is register allocation for the back-button pointer: native
uses `edx`, while VC6 keeps the pointer in `ecx`. A free `__fastcall` spelling
compiled identically, and an explicit integer return regressed by adding a
non-native `xor eax, eax`, so keep the clearer member shape.
