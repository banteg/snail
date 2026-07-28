/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_slider_to_rate @ 0x437e80 */
/* selector: calc_slider_to_rate */

// Exact Windows `cRSubGame::CalcSliderToRate(float)`: maps a normalized challenge-speed slider through `x * 0.90000004 + 0.2`, with the authored maximum slider receiving the special 1.1 rate. Android preserves the same receiver, branch, and constants.
float __thiscall calc_slider_to_rate(cRSubGame *game, float slider)
{
  if ( slider == 1.0 )
    return 1.1;
  else
    return slider * 0.90000004 + 0.2;
}
