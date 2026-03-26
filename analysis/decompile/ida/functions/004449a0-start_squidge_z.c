/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_squidge_z @ 0x4449a0 */
/* selector: start_squidge_z */

float __thiscall start_squidge_z(SquidgeState *squidge, float value)
{
  double v2; // st7

  v2 = value * -0.003;
  squidge->z_phase = value;
  squidge->z_velocity = v2;
  return v2;
}

