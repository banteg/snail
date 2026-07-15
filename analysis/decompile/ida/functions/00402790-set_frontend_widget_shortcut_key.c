/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */
/* selector: set_frontend_widget_shortcut_key */

// Exact void `cRBorder::SetKeyLeft(int)`: stores one keyboard shortcut code and enables the matching dispatch flag. All five Windows callers discard the updated flags left incidentally in EAX.
void __thiscall set_frontend_widget_shortcut_key(FrontendWidget *widget, int32_t shortcut_key_code)
{
  widget->shortcut_key_code = shortcut_key_code;
  widget->widget_flags |= 0x80000u;
}
