/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_all_borders @ 0x4033f0 */
/* selector: hide_all_borders */

// Exact void cRBorderManager::HideBorders() wrapper that pushes a nested 0x1000 visibility transition through the embedded BorderStack.
void __thiscall hide_all_borders(BorderManager *manager)
{
  apply_all_border_visibility_mode(&manager->border_stack.generation, 0);
}
