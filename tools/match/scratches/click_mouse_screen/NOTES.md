# click_mouse_screen @ 0x44c060

Updates the two-slot mouse coordinate caches. In non-fullscreen captured mode,
slot 0 also forwards to `SetCursorPos` when the main window is active and the
window-deactivation latch is clear.

The final `g_game_base` reload is source-shaped as a `result` local so VC6
reuses `eax` for both the owner `mouse_y` store and the return value.
