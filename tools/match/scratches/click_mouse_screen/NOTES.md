# click_mouse_screen @ 0x44c060

Updates the two-slot mouse coordinate caches. In non-fullscreen captured mode,
slot 0 also forwards to `SetCursorPos` when the main window is active and the
window-deactivation latch is clear.

The final `g_game_base` reload is source-shaped as a `result` local so VC6
reuses `eax` for both the owner `mouse_y` store and the return value.

2026-07-11 input-owner pass: root initialization proves the pointer at player
`+0x168` borrows the corresponding root-owned `GameInput` record. The final
stores are therefore `game_input->input.authored_x/y`, not an anonymous mouse
owner at `+0x60/+0x64`. The typed source preserves the exact 43/43 result with
13 clean masked operands.
