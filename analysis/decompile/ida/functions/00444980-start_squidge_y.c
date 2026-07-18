/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: start_squidge_y @ 0x444980 */
/* selector: start_squidge_y */

// Authored `cRSquidge::StartY(float)`: resets the Y spring phase and seeds its velocity on the inline `Player + 0x4344` Squidge owner.
void __thiscall start_squidge_y(Squidge *squidge, float value)
{
  squidge->y_phase = 0.0;
  squidge->y_velocity = value * 0.5;
}
