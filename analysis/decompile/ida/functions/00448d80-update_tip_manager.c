/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip_manager @ 0x448d80 */
/* selector: update_tip_manager */

// Exact `cRTipManager::AI()` member that advances each active inline Tip.
void __thiscall update_tip_manager(TipManager *manager)
{
  Tip *tips; // esi
  int v2; // edi

  tips = manager->tips;
  v2 = 3;
  do
  {
    if ( tips->active == 1 )
      update_tip(tips);
    ++tips;
    --v2;
  }
  while ( v2 );
}
