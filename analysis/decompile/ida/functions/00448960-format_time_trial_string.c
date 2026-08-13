/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: format_time_trial_string @ 0x448960 */
/* selector: format_time_trial_string */

// Implements `cRTimeTrial::TimeString(cRTime&)`: formats one authored cRTime value into the shared Time Trial HUD buffer. The receiver is the exact 0x330-byte TimeTrial owner embedded at cRSubGame +0xff25e0, although the body does not read receiver fields.
char *__thiscall format_time_trial_string(TimeTrial *time_trial, cRTime *timer)
{
  if ( timer->total_seconds == 0.0 )
  {
    sprintf(g_time_trial_string, asc_4AC5BC);
  }
  else
  {
    sprintf(g_time_trial_string, "%1i:%02i:%03i", timer->minutes, timer->seconds, timer->display_thousandths);
    sprintf(g_time_trial_string, "%1i:%02i:%02i", timer->minutes, timer->seconds, timer->display_hundredths);
  }
  return g_time_trial_string;
}
