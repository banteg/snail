/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input @ 0x40aa80 */
/* selector: update_input */

// Void Windows cRInput::Update(): derives pressed and released button edges from current versus previous state, stores the inverse mask, advances previous state, and clears the current word. Android preserves the same edge algebra and cRInput owner; the honest Windows scratch remains 52.94% because of an extra native EDI lifetime.
void __thiscall update_input(cRInput *state)
{
  InputButtonFlag current_buttons; // eax
  __int32 v2; // edx

  current_buttons = state->current_buttons;
  v2 = current_buttons ^ state->previous_buttons;
  state->previous_buttons = current_buttons;
  state->pressed_buttons = current_buttons & v2;
  state->inverse_current_buttons = ~current_buttons;
  state->current_buttons = 0;
  state->released_buttons = v2 & ~current_buttons;
}
