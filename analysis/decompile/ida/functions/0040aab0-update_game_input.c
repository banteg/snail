/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_game_input @ 0x40aab0 */
/* selector: update_game_input */

void *__thiscall update_game_input(GameInputOwner *owner)
{
  void *result; // eax
  InputState *p_input; // esi

  result = g_game_base;
  if ( *((_BYTE *)g_game_base + 1312) )
  {
    p_input = &owner->input;
    copy_active_input_controller_state(
      owner->input.controller_slot,
      &owner->input.current_buttons,
      &owner->input.axis_x,
      &owner->input.axis_y,
      &owner->input.authored_x,
      &owner->input.authored_y,
      &owner->input.pointer_value,
      &owner->input.pointer_x,
      &owner->input.pointer_y);
    return (void *)update_input(p_input);
  }
  return result;
}

