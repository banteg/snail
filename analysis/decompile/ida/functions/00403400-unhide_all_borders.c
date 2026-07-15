/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_all_borders @ 0x403400 */
/* selector: unhide_all_borders */

// Exact void cRBorderManager::UnHideBorders() wrapper that unwinds the newest 0x1000 visibility transition through the embedded BorderStack.
void __thiscall unhide_all_borders(BorderManager *manager)
{
  apply_all_border_visibility_mode(&manager->border_stack.generation, 1);
}
