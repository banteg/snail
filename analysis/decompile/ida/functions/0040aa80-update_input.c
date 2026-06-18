/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input @ 0x40aa80 */
/* selector: update_input */

int __thiscall update_input(InputState *state)
{
  int result; // eax
  int v2; // edx

  result = state->current_buttons;
  v2 = result ^ state->previous_buttons;
  state->previous_buttons = result;
  state->pressed_buttons = result & v2;
  state->inverse_current_buttons = ~result;
  state->current_buttons = 0;
  state->released_buttons = v2 & ~result;
  return result;
}

