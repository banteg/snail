/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_game_input @ 0x40aab0 */
/* selector: update_game_input */

void __thiscall update_game_input(GameInput *game_input)
{
  InputState *p_input; // esi

  if ( *((_BYTE *)g_game_base + 1312) )
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

