/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enqueue_tip_message @ 0x448d30 */
/* selector: enqueue_tip_message */

// Allocates one of the three small gameplay tip-message slots, seeds it with the requested text payload, and warns if all slots are already occupied.
TipSlot *__thiscall enqueue_tip_message(
        TipManager *manager,
        TipMessageDefinition *definition,
        int32_t show_disable_button)
{
  int v3; // eax
  TipSlot *i; // edx
  TipSlot *v6; // esi

  v3 = 0;
  for ( i = manager->slots; i->active; ++i )
  {
    if ( ++v3 >= 3 )
    {
      report_errorf(aRunOutOfTips);
      return nullptr;
    }
  }
  v6 = &manager->slots[v3];
  initialize_tip(v6, definition, show_disable_button);
  return v6;
}

