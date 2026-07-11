/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input @ 0x40aa80 */
/* selector: update_input */

void __thiscall update_input(InputState *state)
{
  int32_t current_buttons; // eax
  int v2; // edx

  current_buttons = state->current_buttons;
  v2 = current_buttons ^ state->previous_buttons;
  state->previous_buttons = current_buttons;
  state->pressed_buttons = current_buttons & v2;
  state->inverse_current_buttons = ~current_buttons;
  state->current_buttons = 0;
  state->released_buttons = v2 & ~current_buttons;
}

