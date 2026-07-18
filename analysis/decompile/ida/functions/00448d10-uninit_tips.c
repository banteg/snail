/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tips @ 0x448d10 */
/* selector: uninit_tips */

// Exact `cRTipManager::UnInitTips()` member that tears down widgets for each active inline Tip.
void __thiscall uninit_tips(TipManager *manager)
{
  Tip *tips; // esi
  int v2; // edi

  tips = manager->tips;
  v2 = 3;
  do
  {
    if ( tips->active == 1 )
      kill_tip_widgets(tips);
    ++tips;
    --v2;
  }
  while ( v2 );
}
