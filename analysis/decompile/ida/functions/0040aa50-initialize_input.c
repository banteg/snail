/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_input @ 0x40aa50 */
/* selector: initialize_input */

int __thiscall initialize_input(InputState *state)
{
  state->inverse_current_buttons = -1;
  state->current_buttons = 0;
  state->pressed_buttons = 0;
  state->released_buttons = 0;
  state->previous_buttons = 0;
  state->axis_x = 0.0;
  state->axis_y = 0.0;
  state->authored_x = 320.0;
  state->authored_y = 240.0;
  state->pointer_value = 0.0;
  return 0;
}

