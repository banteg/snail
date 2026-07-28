/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sub_lazer_pool @ 0x441650 */
/* selector: initialize_sub_lazer_pool */

// Exact void Windows `cRSubLazerManager::Init()`: clears the 32-bit SubLazerState of all 20 owned inline actors at `cRSubGame +0x356b00` to SUB_LAZER_STATE_INACTIVE before a level build. Android preserves the same manager method and loop; the end pointer left in EAX is incidental.
void __thiscall initialize_sub_lazer_pool(SubLazerManager *manager)
{
  SubLazerState *p_state; // eax
  int i; // ecx

  p_state = &manager->slots[0].state;
  for ( i = 20; i != 0; --i )
  {
    *p_state = SUB_LAZER_STATE_INACTIVE;
    p_state += 44;
  }
}
