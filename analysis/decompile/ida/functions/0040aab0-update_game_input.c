/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_game_input @ 0x40aab0 */
/* selector: update_game_input */

// Runs cRGameInput::AI() for one root-owned BodBase-derived input record: when the root sampling gate is live, copies the selected controller's buttons, axes, pointer values, and authored x/y into the trailing cRInput-compatible state and derives the current-frame button edges.
void __thiscall update_game_input(GameInput *game_input)
{
  InputState *p_input; // esi

  if ( g_game_base->input_sampling_gate )
  {
    p_input = &game_input->input;
    copy_active_input_controller_state(
      game_input->input.controller_slot,
      &game_input->input.current_buttons,
      &game_input->input.axis_x,
      &game_input->input.axis_y,
      &game_input->input.authored_x,
      &game_input->input.authored_y,
      &game_input->input.pointer_value,
      &game_input->input.pointer_x,
      &game_input->input.pointer_y);
    update_input(p_input);
  }
}
