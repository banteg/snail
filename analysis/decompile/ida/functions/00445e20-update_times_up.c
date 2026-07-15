/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_times_up @ 0x445e20 */
/* selector: update_times_up */

// Exact Windows `TimesUp::update_times_up` state machine: advances the message timer, tears the message down, and kills Goldy when the terminal phase completes. Android and iOS retain this member as `cRTimesUp::AI()`.
void __thiscall update_times_up(int this)
{
  double v2; // st7

  if ( *(_DWORD *)this )
  {
    if ( *(_DWORD *)this == 1 )
    {
      v2 = *(float *)(this + 12) + *(float *)(this + 8);
      *(float *)(this + 8) = v2;
      if ( v2 > 1.0 )
        *(_DWORD *)this = 2;
    }
    else if ( *(_DWORD *)this == 2 )
    {
      uninit_times_up((_DWORD **)this);
      kill_subgoldy((Player *)((char *)&g_player_block + (_DWORD)g_game_base));
      *(_DWORD *)this = 0;
    }
  }
}
