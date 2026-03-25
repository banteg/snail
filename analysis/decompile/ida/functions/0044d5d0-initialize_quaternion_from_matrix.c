/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_quaternion_from_matrix @ 0x44d5d0 */
/* selector: initialize_quaternion_from_matrix */

// Builds a quaternion from the rotational basis of a transform matrix. Android symbols match this helper to `tQuaternian::tQuaternian(const tMatrix&)`.
float *__thiscall sub_44D5D0(float *this, float *a2)
{
  double v4; // st7
  long double v5; // st7
  double v7; // st7
  long double v8; // st7
  long double v9; // st7
  double v10; // st7
  long double v11; // st7
  long double v12; // st7
  double v13; // st7
  long double v14; // st7
  long double v15; // st7
  float v16; // [esp+14h] [ebp+4h]
  float v17; // [esp+14h] [ebp+4h]
  float v18; // [esp+14h] [ebp+4h]
  float v19; // [esp+14h] [ebp+4h]

  v4 = a2[5] + *a2 + a2[10] + 1.0;
  if ( v4 > 0.000001 )
  {
    v16 = v4;
    v5 = 0.5 / square_root(v16);
    *(this + 3) = 0.25 / v5;
    *this = (a2[6] - a2[9]) * v5;
    *(this + 1) = (a2[8] - a2[2]) * v5;
    *(this + 2) = (a2[1] - a2[4]) * v5;
    return this;
  }
  if ( *a2 < (double)a2[5] )
  {
    if ( a2[5] >= (double)a2[10] )
    {
LABEL_14:
      v13 = a2[5] + 1.0 - *a2 - a2[10];
      v19 = v13;
      if ( v13 < 0.0 )
      {
        sub_449C00();
        v19 = 0.0;
      }
      v14 = square_root(v19);
      v15 = v14 + v14;
      *this = (a2[4] + a2[1]) / v15;
      *(this + 1) = v15 * 0.25;
      *(this + 2) = (a2[9] + a2[6]) / v15;
      *(this + 3) = (a2[8] + a2[2]) / v15;
      return this;
    }
    if ( *a2 <= (double)a2[10] )
      goto LABEL_6;
  }
  else if ( *a2 <= (double)a2[10] )
  {
    if ( a2[5] <= (double)a2[10] )
    {
LABEL_6:
      v7 = a2[10] + 1.0 - *a2 - a2[5];
      v17 = v7;
      if ( v7 < 0.0 )
      {
        sub_449C00();
        v17 = 0.0;
      }
      v8 = square_root(v17);
      v9 = v8 + v8;
      *this = (a2[8] + a2[2]) / v9;
      *(this + 1) = (a2[9] + a2[6]) / v9;
      *(this + 2) = v9 * 0.25;
      *(this + 3) = (a2[4] + a2[1]) / v9;
      return this;
    }
    goto LABEL_14;
  }
  v10 = *a2 + 1.0 - a2[5] - a2[10];
  v18 = v10;
  if ( v10 < 0.0 )
  {
    sub_449C00();
    v18 = 0.0;
  }
  v11 = square_root(v18);
  v12 = v11 + v11;
  *this = v12 * 0.25;
  *(this + 1) = (a2[4] + a2[1]) / v12;
  *(this + 2) = (a2[8] + a2[2]) / v12;
  *(this + 3) = (a2[9] + a2[6]) / v12;
  return this;
}

