/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_border @ 0x403360 */
/* selector: kill_border */

// Exact cRBorderManager::Kill(cRBorder*) recursive teardown request over the manager-owned widget tree. Every audited Windows caller discards EAX, and the native exits leave incompatible incidental values, but a direct VC6 void transcription tail-recurses the third child and falls to 73.33%; the matcher therefore keeps its isolated result-shaped compiler harness until a natural authored source shape is recovered.
void __thiscall kill_border(BorderManager *manager, FrontendWidget *widget)
{
  FrontendWidgetFlag widget_flags; // eax

  if ( widget )
  {
    widget_flags = widget->widget_flags;
    if ( widget_flags )
    {
      if ( (BYTE1(widget_flags) & 4) == 0 )
      {
        LOBYTE(widget_flags) = widget_flags & 1;
        BYTE1(widget_flags) |= 2u;
        widget->widget_flags = widget_flags;
        if ( (widget_flags & 0x100000) != 0 )
        {
          kill_border(manager, widget->slider_less_widget);
          kill_border(manager, widget->slider_more_widget);
          kill_border(manager, widget->slider_value_widget);
        }
      }
    }
  }
}
