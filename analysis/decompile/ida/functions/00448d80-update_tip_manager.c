/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip_manager @ 0x448d80 */
/* selector: update_tip_manager */

// Exact `cRTipManager::AI()` member that advances each active inline Tip.
void __thiscall update_tip_manager(cRTipManager *manager)
{
  cRTip *tips; // esi
  int i; // edi

  tips = manager->tips;
  for ( i = 3; i != 0; --i )
  {
    if ( tips->active == 1 )
      update_tip(tips);
    ++tips;
  }
}
