# read_right_mouse_button_state

Exact process-level right-button reader at `0x407830`.

The native body preserves the integer slot in `eax`, clears
`g_right_mouse_button_latch[slot]`, and replaces only `al` with
`g_right_mouse_button_state[slot]`. The exact 4/4-instruction scratch therefore
supports an unsigned-byte return without assigning semantics to the untouched
upper return-register bits.

The reader proves indexed byte storage, while
`handle_game_window_activate` and `show_and_focus_game_window` clear both
slots. That independent writer evidence bounds each global to two bytes and
leaves the surrounding gaps unclaimed.
