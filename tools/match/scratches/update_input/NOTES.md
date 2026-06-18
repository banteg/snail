# update_input

Partial `InputState` edge updater at `0x40aa80`.

The function folds `current_buttons` and `previous_buttons` into per-frame
`pressed_buttons` and `released_buttons`, stores `~current_buttons` at
`inverse_current_buttons`, and clears `current_buttons` for the next input
sampling pass.

Current Wibo result is 34.29%. The recovered semantics and member spelling are
clear from `update_game_input`, but VC6 currently collapses the native `edx`,
`esi`, and `edi` lifetimes into a shorter register schedule.
