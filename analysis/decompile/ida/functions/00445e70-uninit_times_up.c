/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_times_up @ 0x445e70 */
/* selector: uninit_times_up */

// Exact Windows `cRTimesUp::UnInit()` (`uninit_times_up`): returns the borrowed message widget to BorderManager whenever the embedded owner is active. Android independently retains the authored class-qualified member.
void __thiscall uninit_times_up(cRTimesUp *times_up)
{
  if ( times_up->state != TIMES_UP_STATE_INACTIVE )
    kill_border(&g_game_base->border_manager, times_up->border);
}
