/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_quaternion_from_matrix @ 0x44d5d0 */
/* selector: initialize_quaternion_from_matrix */

// Stable Windows harness identity for the authored `tQuaternian::tQuaternian(const tMatrix&)` constructor retained by Android. The typed const-reference constructor builds a quaternion from the matrix's rotational basis.
Quaternion *__thiscall initialize_quaternion_from_matrix(Quaternion *out, const TransformMatrix *matrix)
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
  float matrixd; // [esp+14h] [ebp+4h]
  float matrixa; // [esp+14h] [ebp+4h]
  float matrixb; // [esp+14h] [ebp+4h]
  float matrixc; // [esp+14h] [ebp+4h]

  v4 = matrix->basis_up.y + matrix->basis_right.x + matrix->basis_forward.z + 1.0;
  if ( v4 > 0.000001 )
  {
    matrixd = v4;
    v5 = 0.5 / square_root(matrixd);
    out->w = 0.25 / v5;
    out->x = (matrix->basis_up.z - matrix->basis_forward.y) * v5;
    out->y = (matrix->basis_forward.x - matrix->basis_right.z) * v5;
    out->z = (matrix->basis_right.y - matrix->basis_up.x) * v5;
    return out;
  }
  if ( matrix->basis_right.x < (double)matrix->basis_up.y )
  {
    if ( matrix->basis_up.y >= (double)matrix->basis_forward.z )
    {
LABEL_14:
      v13 = matrix->basis_up.y + 1.0 - matrix->basis_right.x - matrix->basis_forward.z;
      matrixc = v13;
      if ( v13 < 0.0 )
      {
        debug_report_stub();
        matrixc = 0.0;
      }
      v14 = square_root(matrixc);
      v15 = v14 + v14;
      out->x = (matrix->basis_up.x + matrix->basis_right.y) / v15;
      out->y = v15 * 0.25;
      out->z = (matrix->basis_forward.y + matrix->basis_up.z) / v15;
      out->w = (matrix->basis_forward.x + matrix->basis_right.z) / v15;
      return out;
    }
    if ( matrix->basis_right.x <= (double)matrix->basis_forward.z )
      goto LABEL_6;
  }
  else if ( matrix->basis_right.x <= (double)matrix->basis_forward.z )
  {
    if ( matrix->basis_up.y <= (double)matrix->basis_forward.z )
    {
LABEL_6:
      v7 = matrix->basis_forward.z + 1.0 - matrix->basis_right.x - matrix->basis_up.y;
      matrixa = v7;
      if ( v7 < 0.0 )
      {
        debug_report_stub();
        matrixa = 0.0;
      }
      v8 = square_root(matrixa);
      v9 = v8 + v8;
      out->x = (matrix->basis_forward.x + matrix->basis_right.z) / v9;
      out->y = (matrix->basis_forward.y + matrix->basis_up.z) / v9;
      out->z = v9 * 0.25;
      out->w = (matrix->basis_up.x + matrix->basis_right.y) / v9;
      return out;
    }
    goto LABEL_14;
  }
  v10 = matrix->basis_right.x + 1.0 - matrix->basis_up.y - matrix->basis_forward.z;
  matrixb = v10;
  if ( v10 < 0.0 )
  {
    debug_report_stub();
    matrixb = 0.0;
  }
  v11 = square_root(matrixb);
  v12 = v11 + v11;
  out->x = v12 * 0.25;
  out->y = (matrix->basis_up.x + matrix->basis_right.y) / v12;
  out->z = (matrix->basis_forward.x + matrix->basis_right.z) / v12;
  out->w = (matrix->basis_forward.y + matrix->basis_up.z) / v12;
  return out;
}
