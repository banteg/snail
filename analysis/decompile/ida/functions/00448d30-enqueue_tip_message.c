/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enqueue_tip_message @ 0x448d30 */
/* selector: enqueue_tip_message */

// Exact `cRTipManager::TipNew(cRTipData*, ...)` member: selects one of the three inline Tips, initializes it from authored TipData, returns the selected Tip, and warns if all three are active.
Tip *__thiscall enqueue_tip_message(TipManager *manager, TipData *definition, int32_t hide_disable_button)
{
  int v3; // eax
  Tip *i; // edx
  Tip *v6; // esi

  v3 = 0;
  for ( i = manager->tips; i->active; ++i )
  {
    if ( ++v3 >= 3 )
    {
      report_errorf(aRunOutOfTips);
      return nullptr;
    }
  }
  v6 = &manager->tips[v3];
  initialize_tip(v6, definition, hide_disable_button);
  return v6;
}
