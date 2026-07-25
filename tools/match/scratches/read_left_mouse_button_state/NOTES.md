# read_left_mouse_button_state

Exact process-level left-button reader at `0x407810`.

The native body preserves the integer slot in `eax`, clears
`g_left_mouse_button_latch[slot]`, and replaces only `al` with
`g_left_mouse_button_state[slot]`. The exact 4/4-instruction scratch therefore
supports an unsigned-byte return without pretending that the untouched upper
return-register bits are meaningful.

The reader alone proves indexed byte storage; `handle_game_window_activate`
and `show_and_focus_game_window` independently clear offsets zero and one of
both globals. Together they bound each owner to exactly two bytes. The replay
does not claim the gaps after either array.
