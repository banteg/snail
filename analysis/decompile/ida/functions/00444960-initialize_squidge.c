/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_squidge @ 0x444960 */
/* selector: initialize_squidge */

// Exact Windows `cRSquidge::Init()`. The sole caller passes the inline `Player + 0x4344` Squidge owner, and the helper clears its six Y/Z spring floats; Goldy's score buckets are separate at `Player + 0x310`, while mobile `cRSubGoldy::ScoreStatsInit()` remains a distinct symbol without a proven Windows mapping.
void __thiscall initialize_squidge(Squidge *squidge)
{
  squidge->y_velocity = 0.0;
  squidge->y_phase = 0.0;
  squidge->y_output = 0.0;
  squidge->z_velocity = 0.0;
  squidge->z_phase = 0.0;
  squidge->z_output = 0.0;
}
