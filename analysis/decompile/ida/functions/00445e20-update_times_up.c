/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_times_up @ 0x445e20 */
/* selector: update_times_up */

// Exact Windows `TimesUp::update_times_up` state machine: advances the message timer, tears the message down, and kills Goldy when the terminal phase completes. Android and iOS retain this member as `cRTimesUp::AI()`.
void __thiscall update_times_up(TimesUp *times_up)
{
  double v2; // st7

  if ( times_up->state )
  {
    if ( times_up->state == TIMES_UP_STATE_DISPLAYING )
    {
      v2 = times_up->progress_step + times_up->progress;
      times_up->progress = v2;
      if ( v2 > 1.0 )
        times_up->state = TIMES_UP_STATE_EXPIRED;
    }
    else if ( times_up->state == TIMES_UP_STATE_EXPIRED )
    {
      uninit_times_up(times_up);
      kill_subgoldy((Player *)((char *)&g_player_block + (_DWORD)g_game_base));
      times_up->state = TIMES_UP_STATE_INACTIVE;
    }
  }
}
