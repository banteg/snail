/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_global_noop_renderable_bods @ 0x406bd0 */
/* selector: initialize_global_noop_renderable_bods */

// Constructs the RenderableBod prefix of three 0xc4-byte global records at 0x4b6fb4, 0x4b7078, and 0x4b713c, then installs the shared no-op runtime callback table on each. No post-startup consumer is present in the Windows image.
RenderableBod *initialize_global_noop_renderable_bods()
{
  RenderableBod *result; // eax

  initialize_renderable_bod(&g_startup_noop_renderable_bods);
  g_startup_noop_renderable_bods.bod.bod.vtable = &g_noop_runtime_callback_table;
  initialize_renderable_bod(&stru_4B7078);
  stru_4B7078.bod.bod.vtable = &g_noop_runtime_callback_table;
  result = initialize_renderable_bod(&stru_4B713C);
  stru_4B713C.bod.bod.vtable = &g_noop_runtime_callback_table;
  return result;
}
