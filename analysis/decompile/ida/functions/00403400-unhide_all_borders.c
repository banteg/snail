/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_all_borders @ 0x403400 */
/* selector: unhide_all_borders */

// Exact void `cRBorderManager::UnHideBorders()` wrapper that unwinds the newest hidden-state transition through the embedded `cRBorderStack`, restoring idle padding and hover state. Android calls `Perform(1)` directly; iOS inlines the same operation.
void __thiscall unhide_all_borders(BorderManager *manager)
{
  apply_all_border_visibility_mode(&manager->border_stack, 1);
}
