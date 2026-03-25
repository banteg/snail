/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */
/* selector: set_frontend_widget_shortcut_key */

// Stores one keyboard shortcut code on a front-end widget and enables the matching flag so `update_frontend_widget_interaction` dispatches the widget when `read_pressed_text_input_key_code()` returns that code.
int __thiscall sub_402790(_DWORD *this, int a2)
{
  int result; // eax

  *(this + 101) = a2;
  result = *(this + 104) | 0x80000;
  *(this + 104) = result;
  return result;
}

