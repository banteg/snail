/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: flush_row_event_display @ 0x404830 */
/* selector: flush_row_event_display */

// Fast-forwards the active gameplay row-event display by paying out any remaining row score awards, destroying its widget actors, and clearing the owning controller state.
int32_t __fastcall flush_row_event_display(RowEventDisplayController *controller)
{
  int32_t result; // eax
  int32_t delivered_parcel_count; // eax
  int32_t parcel_target_count; // ecx
  int32_t v5; // ecx
  int32_t v6; // eax
  _DWORD *widget_a; // [esp-4h] [ebp-8h]

  result = controller->state;
  if ( result )
  {
    delivered_parcel_count = controller->delivered_parcel_count;
    parcel_target_count = controller->parcel_target_count;
    if ( delivered_parcel_count != parcel_target_count )
    {
      if ( delivered_parcel_count < parcel_target_count )
      {
        do
        {
          add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), 4, 0);
          v5 = controller->parcel_target_count;
          v6 = controller->delivered_parcel_count + 1;
          controller->delivered_parcel_count = v6;
        }
        while ( v6 < v5 );
      }
      if ( controller->bonus_enabled )
        add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), controller->bonus_score, 0);
    }
    widget_a = controller->widget_a;
    ++controller->delivered_parcel_count;
    kill_border(widget_a);
    kill_border((_DWORD *)controller->widget_b);
    kill_border((_DWORD *)controller->widget_d);
    kill_border((_DWORD *)controller->widget_c);
    kill_border((_DWORD *)controller->widget_e);
    result = controller->display_token;
    if ( *((_DWORD *)MEMORY[0x4DF904] + 1097752) != result )
      *((_DWORD *)MEMORY[0x4DF904] + 1097752) = result;
  }
  controller->state = 0;
  return result;
}

