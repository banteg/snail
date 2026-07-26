/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_all_borders @ 0x4033f0 */
/* selector: hide_all_borders */

// Exact void `cRBorderManager::HideBorders()` wrapper that pushes a nested hidden-state transition through the embedded `cRBorderStack`. Android calls `Perform(0)` directly; iOS inlines the same operation over its pointer-backed border pool.
void __thiscall hide_all_borders(BorderManager *manager)
{
  apply_all_border_visibility_mode(&manager->border_stack, 0);
}
