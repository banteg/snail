/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_input_ok @ 0x403560 */
/* selector: initialize_input_ok */

// Exact void cRInputOK::Init() member: allocates the manager-owned OK widget, binds it to the borrowed source widget, initializes its presentation, and finishes by calling the void layout helper. Its only native caller discards EAX.
void __thiscall initialize_input_ok(InputOkState *input_ok)
{
  FrontendWidget *border; // eax
  FrontendWidget *source_widget; // ecx

  border = allocate_border(&g_game_base->border_manager);
  source_widget = input_ok->source_widget;
  input_ok->ok_widget = border;
  initialize_frontend_widget(
    border,
    0x14u,
    aOk,
    source_widget->widget_type,
    0.0,
    0.0,
    &source_widget->idle_fill_color,
    0,
    0.0);
  update_input_ok(input_ok);
}
