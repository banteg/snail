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

## 2026-08-09 slot-0 fire consumer

Exact `update_mouse` is this helper's only gameplay publication path: it reads
index `0` and supplies the returned byte as the pointer adapter's `button_a`,
which sets slot-0 `INPUT_BUTTON_PRIMARY`. That slot is copied into the
root-owned `InputState` borrowed by Goldy and gates `PlayShootSfx()`. This
consumer relationship does not change the exact 4/4 helper or broaden its
two-byte state owner.
