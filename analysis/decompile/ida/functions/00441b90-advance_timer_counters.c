/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_timer_counters @ 0x441b90 */
/* selector: advance_timer_counters */

// Exact void `cRTime::Add(float)`: accumulates a 60 Hz-scaled delta, rolls seconds into minutes at 60, and refreshes the derived hundredths and thousandths fields. The final Windows EAX value is incidental, not a semantic return.
void __thiscall advance_timer_counters(cRTime *time, float delta_ticks)
{
  double v2; // st7
  double v3; // st7
  char v5; // c0
  int32_t v6; // edx
  double v7; // st7

  v2 = delta_ticks * 0.016666668;
  time->total_seconds = v2 + time->total_seconds;
  v3 = v2 + time->second_fraction;
  time->second_fraction = v3;
  if ( v5 == 0 )
  {
    v6 = time->seconds + 1;
    time->seconds = v6;
    time->second_fraction = v3 - 1.0;
    if ( v6 >= 60 )
    {
      time->seconds = v6 - 60;
      ++time->minutes;
    }
  }
  v7 = time->second_fraction * 1000.0;
  time->display_hundredths = (__int64)(time->second_fraction * 100.0);
  time->display_thousandths = (__int64)v7;
}
