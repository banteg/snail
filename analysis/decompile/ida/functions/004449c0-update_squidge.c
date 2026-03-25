/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_squidge @ 0x4449c0 */
/* selector: update_squidge */

void __thiscall sub_4449C0(float *this)
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

  if ( *(this + 1) != 0.0 )
  {
    v1 = *(this + 2) + *(this + 1);
    *(this + 2) = v1;
    v2 = (*(this + 1) - v1 * 0.15000001) * 0.81999999;
    *(this + 1) = v2;
    v11 = -*(this + 2);
    *this = v11;
    if ( v2 < 0.0 )
      v2 = -v2;
    if ( v2 < 0.001 )
    {
      v4 = v11;
      if ( v5 )
        v4 = -v4;
      if ( v4 < 0.001 )
      {
        *(this + 1) = 0.0;
        *this = 0.0;
      }
    }
  }
  if ( *(this + 4) != 0.0 )
  {
    v6 = *(this + 5) + *(this + 4);
    *(this + 5) = v6;
    v7 = (*(this + 4) - v6 * 0.15000001) * 0.81999999;
    *(this + 4) = v7;
    v12 = -*(this + 5);
    *(this + 3) = v12;
    if ( v7 < 0.0 )
      v7 = -v7;
    if ( v7 < 0.001 )
    {
      v9 = v12;
      if ( v10 )
        v9 = -v9;
      if ( v9 < 0.001 )
      {
        *(this + 4) = 0.0;
        *(this + 3) = 0.0;
      }
    }
  }
}

