/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_times_up @ 0x445e20 */
/* selector: update_times_up */

// Exact Windows `cRTimesUp::AI()` (`update_times_up`): advances the message timer, tears the message down, and kills Goldy when the terminal phase completes. Android and iOS independently retain the authored class-qualified member.
void __thiscall update_times_up(cRTimesUp *times_up)
{
  double v2; // st7

  if ( times_up->state != TIMES_UP_STATE_INACTIVE )
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
      kill_subgoldy(&g_game_base->subgame.player);
      times_up->state = TIMES_UP_STATE_INACTIVE;
    }
  }
}
