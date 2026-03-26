/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_squidge_z @ 0x4449a0 */
/* selector: start_squidge_z */

void __thiscall start_squidge_z(SquidgeState *squidge, float value)
{
  squidge->z_phase = value;
  squidge->z_velocity = value * -0.003;
}

