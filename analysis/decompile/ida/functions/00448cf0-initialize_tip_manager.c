/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip_manager @ 0x448cf0 */
/* selector: initialize_tip_manager */

// Exact `cRTipManager::Init()` member that clears the three inline Tips at TipManager +0x38.
void __thiscall initialize_tip_manager(cRTipManager *manager)
{
  cRTip *tips; // eax
  int i; // ecx

  tips = manager->tips;
  for ( i = 3; i != 0; --i )
  {
    tips->active = 0;
    ++tips;
  }
}
