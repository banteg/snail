/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip_manager @ 0x448cf0 */
/* selector: initialize_tip_manager */

// Exact `cRTipManager::Init()` member that clears the three inline Tips at TipManager +0x38.
void __thiscall initialize_tip_manager(TipManager *manager)
{
  Tip *tips; // eax
  int v2; // ecx

  tips = manager->tips;
  v2 = 3;
  do
  {
    tips->active = 0;
    ++tips;
    --v2;
  }
  while ( v2 );
}
