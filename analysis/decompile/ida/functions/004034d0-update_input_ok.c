/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_ok @ 0x4034d0 */
/* selector: update_input_ok */

// Exact void layout helper for the 0x24-byte InputOkState overlay reused at FrontendWidget::tooltip +0x1c. It borrows the source and manager-owned OK widgets at +0x1c/+0x20; both native callers ignore EAX, whose final source-widget value is incidental.
void __thiscall update_input_ok(InputOkState *input_ok)
{
  FrontendWidget *source_widget; // eax
  uint32_t input_flags; // edx
  FrontendWidget *ok_widget; // edx
  double v4; // st7

  source_widget = input_ok->source_widget;
  input_flags = source_widget->input_flags;
  if ( (input_flags & 4) != 0 )
  {
    ok_widget = input_ok->ok_widget;
    v4 = ok_widget->hot_padding + source_widget->layout_width + source_widget->layout_left + source_widget->hot_padding;
  }
  else
  {
    if ( (input_flags & 8) == 0 )
      return;
    ok_widget = input_ok->ok_widget;
    v4 = source_widget->layout_left
       - ok_widget->layout_width
       - source_widget->hot_padding
       - (ok_widget->hot_padding
        + ok_widget->hot_padding);
  }
  ok_widget->layout_left = v4;
  input_ok->ok_widget->layout_top = input_ok->source_widget->layout_top;
  input_ok->ok_widget->layout_anchor_x = input_ok->ok_widget->layout_left;
  input_ok->ok_widget->layout_anchor_y = input_ok->source_widget->layout_anchor_y;
}
