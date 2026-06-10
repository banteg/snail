/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip_manager @ 0x448d80 */
/* selector: update_tip_manager */

void __fastcall update_tip_manager(TipManager *manager)
{
  TipSlot *slots; // esi
  int v2; // edi

  slots = manager->slots;
  v2 = 3;
  do
  {
    if ( slots->active == 1 )
      update_tip(slots);
    ++slots;
    --v2;
  }
  while ( v2 );
}

