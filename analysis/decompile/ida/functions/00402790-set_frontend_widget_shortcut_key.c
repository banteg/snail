/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */
/* selector: set_frontend_widget_shortcut_key */

// Stores one keyboard shortcut code on a front-end widget and enables the matching flag so `update_frontend_widget_interaction` dispatches the widget when `read_pressed_text_input_key_code()` returns that code.
int32_t __thiscall set_frontend_widget_shortcut_key(FrontendWidget *widget, int32_t shortcut_key_code)
{
  int32_t result; // eax

  widget->shortcut_key_code = shortcut_key_code;
  result = widget->widget_flags | 0x80000;
  widget->widget_flags = result;
  return result;
}

