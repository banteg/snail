/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: flush_row_event_display @ 0x404830 */
/* selector: flush_row_event_display */

// Exact Windows `Completion::flush_row_event_display` teardown for the embedded 0x50-byte `cRCompletion`: pays any remaining parcel awards, destroys its five widgets, restores the display token, and clears state. Android and iOS retain this member as `cRCompletion::UnInit()`.
void __thiscall flush_row_event_display(Completion *completion)
{
  int32_t delivered_parcel_count; // eax
  int32_t parcel_target_count; // ecx
  int32_t v4; // ecx
  int32_t v5; // eax
  int32_t display_token; // eax
  FrontendWidget *widget_a; // [esp-4h] [ebp-8h]

  if ( completion->state )
  {
    delivered_parcel_count = completion->delivered_parcel_count;
    parcel_target_count = completion->parcel_target_count;
    if ( delivered_parcel_count != parcel_target_count )
    {
      if ( delivered_parcel_count < parcel_target_count )
      {
        do
        {
          add_subgoldy_score((Player *)((char *)&g_player_block + (_DWORD)g_game_base), 4, 0);
          v4 = completion->parcel_target_count;
          v5 = completion->delivered_parcel_count + 1;
          completion->delivered_parcel_count = v5;
        }
        while ( v5 < v4 );
      }
      if ( completion->bonus_enabled )
        add_subgoldy_score((Player *)((char *)&g_player_block + (_DWORD)g_game_base), completion->bonus_score, 0);
    }
    widget_a = completion->widget_a;
    ++completion->delivered_parcel_count;
    kill_border(widget_a);
    kill_border(&completion->delivered_count_widget->list_kind);
    kill_border(&completion->widget_d->list_kind);
    kill_border(&completion->bonus_widget->list_kind);
    kill_border(&completion->continue_widget->list_kind);
    display_token = completion->display_token;
    if ( g_game_base->subgame.player.total_score != display_token )
      g_game_base->subgame.player.total_score = display_token;
  }
  completion->state = COMPLETION_STATE_INACTIVE;
}
