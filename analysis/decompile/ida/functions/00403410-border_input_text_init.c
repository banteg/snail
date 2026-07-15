/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_input_text_init @ 0x403410 */
/* selector: border_input_text_init */

// Stable Windows harness identity for the authored void cRBorder::InputTextInit(int, char*, int) member. It initializes the complete inline editor tail through input_capacity at +0x714, relayouts the border, and optionally initializes its embedded cRInputOK overlay.
void __thiscall border_input_text_init(FrontendWidget *widget, int32_t capacity, char *text, int32_t flags)
{
  FrontendWidgetTextBuffer *p_text_buffer; // eax

  widget->input_flags = flags;
  rstrcpy_checked_ascii((char *)&widget->text_buffer.raw[1024], text);
  p_text_buffer = &widget->text_buffer;
  widget->input_cursor = 0;
  widget->input_length = 0;
  if ( widget->text_buffer.raw[0] )
  {
    do
    {
      p_text_buffer = (FrontendWidgetTextBuffer *)((char *)p_text_buffer + 1);
      ++widget->input_length;
      ++widget->input_cursor;
    }
    while ( p_text_buffer->raw[0] );
  }
  widget->text_buffer.raw[widget->input_cursor] = 124;
  widget->text_buffer.raw[widget->input_cursor + 1] = 0;
  widget->input_cursor_blink_progress = 0.0;
  widget->input_cursor_visible = 1;
  widget->input_capacity = capacity;
  widget->input_cursor_blink_step = 0.083333336;
  layout_frontend_widget(widget);
  if ( (flags & 0xC) != 0 )
    initialize_input_ok(&widget->tooltip.input_ok_state);
}
