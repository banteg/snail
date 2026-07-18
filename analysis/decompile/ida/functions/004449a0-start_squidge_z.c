/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_squidge_z @ 0x4449a0 */
/* selector: start_squidge_z */

// Authored `cRSquidge::StartZ(float)`: seeds the Z spring phase and velocity on the inline `Player + 0x4344` Squidge owner.
void __thiscall start_squidge_z(Squidge *squidge, float value)
{
  squidge->z_phase = value;
  squidge->z_velocity = value * -0.003;
}
