/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_click_start_controller_runtime @ 0x408670 */
/* selector: initialize_click_start_controller_runtime */

// Exact Windows constructor for the 0xac-byte authored `ClickStart` (`cRClickStart`) child: constructs its RenderableBod base and installs the callback table whose first entry is `update_click_start`.
ClickStart *__thiscall initialize_click_start_controller_runtime(ClickStart *click_start)
{
  initialize_renderable_bod(&click_start->bod);
  click_start->bod.bod.bod.vtable = &g_click_start_controller_vtable;
  return click_start;
}
