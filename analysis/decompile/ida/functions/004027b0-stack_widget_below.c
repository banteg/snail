/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stack_widget_below @ 0x4027b0 */
/* selector: stack_widget_below */

// Exact void `cRBorder::SetBelow(cRBorder*)`: chains one shell-font widget below another, then tail-calls `RePosition()`. All 36 Windows callers discard EAX.
void __thiscall stack_widget_below(FrontendWidget *widget, FrontendWidget *previous_widget)
{
  widget->layout_anchor_x = previous_widget->layout_anchor_x;
  widget->layout_anchor_y = previous_widget->layout_anchor_y + widget->stack_gap + previous_widget->layout_height;
  layout_frontend_widget(widget);
}
