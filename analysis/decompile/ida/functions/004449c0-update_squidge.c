/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_squidge @ 0x4449c0 */
/* selector: update_squidge */

// Authored `cRSquidge::AI()`: advances and damps the inline owner's independent Y/Z spring oscillators and publishes their output lanes.
void __thiscall update_squidge(Squidge *squidge)
{
  double v1; // st7
  double v2; // st7
  double v4; // st7
  char v5; // c0
  double v6; // st7
  double v7; // st7
  double v9; // st7
  char v10; // c0
  float v11; // [esp+0h] [ebp-4h]
  float v12; // [esp+0h] [ebp-4h]

  if ( squidge->y_velocity != 0.0 )
  {
    v1 = squidge->y_phase + squidge->y_velocity;
    squidge->y_phase = v1;
    v2 = (squidge->y_velocity - v1 * 0.15000001) * 0.81999999;
    squidge->y_velocity = v2;
    v11 = -squidge->y_phase;
    squidge->y_output = v11;
    if ( v2 < 0.0 )
      v2 = -v2;
    if ( v2 < 0.001 )
    {
      v4 = v11;
      if ( v5 )
        v4 = -v4;
      if ( v4 < 0.001 )
      {
        squidge->y_velocity = 0.0;
        squidge->y_output = 0.0;
      }
    }
  }
  if ( squidge->z_velocity != 0.0 )
  {
    v6 = squidge->z_phase + squidge->z_velocity;
    squidge->z_phase = v6;
    v7 = (squidge->z_velocity - v6 * 0.15000001) * 0.81999999;
    squidge->z_velocity = v7;
    v12 = -squidge->z_phase;
    squidge->z_output = v12;
    if ( v7 < 0.0 )
      v7 = -v7;
    if ( v7 < 0.001 )
    {
      v9 = v12;
      if ( v10 )
        v9 = -v9;
      if ( v9 < 0.001 )
      {
        squidge->z_velocity = 0.0;
        squidge->z_output = 0.0;
      }
    }
  }
}
