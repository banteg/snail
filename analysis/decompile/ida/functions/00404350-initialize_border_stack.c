/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_border_stack @ 0x404350 */
/* selector: initialize_border_stack */

// Exact Windows cRBorderStack::Init(): resets the generation and borrowed-entry count of the BorderManager-owned visibility transition stack. Windows folds the same two-zero-store body with the root-owned cRFade::Init() projection; Android independently preserves both authored owners and their identical initializer bodies.
void __thiscall initialize_border_stack(BorderStack *stack)
{
  stack->generation = 0;
  stack->entry_count = 0;
}
