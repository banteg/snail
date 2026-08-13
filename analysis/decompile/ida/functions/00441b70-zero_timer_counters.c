/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: zero_timer_counters @ 0x441b70 */
/* selector: zero_timer_counters */

// Exact void `cRTime::Zero()`: clears all six fields of the authored 0x18-byte time value shared by player, level, and high-score state. iOS and Android preserve the owner and method name.
void __thiscall zero_timer_counters(cRTime *time)
{
  time->total_seconds = 0.0;
  time->minutes = 0;
  time->seconds = 0;
  time->display_hundredths = 0;
  time->display_thousandths = 0;
  time->second_fraction = 0.0;
}
