/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_slider_to_rate @ 0x437e80 */
/* selector: calc_slider_to_rate */

double __stdcall sub_437E80(float a1)
{
  if ( a1 == 1.0 )
    return 1.1;
  else
    return a1 * 0.90000004 + 0.2;
}

