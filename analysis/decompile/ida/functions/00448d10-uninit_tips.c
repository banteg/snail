/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tips @ 0x448d10 */
/* selector: uninit_tips */

// Exact `cRTipManager::UnInitTips()` member that tears down widgets for each active inline Tip.
void __thiscall uninit_tips(cRTipManager *manager)
{
  cRTip *tips; // esi
  int i; // edi

  tips = manager->tips;
  for ( i = 3; i != 0; --i )
  {
    if ( tips->active == 1 )
      kill_tip_widgets(tips);
    ++tips;
  }
}
