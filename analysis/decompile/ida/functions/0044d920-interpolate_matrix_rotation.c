/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: interpolate_matrix_rotation @ 0x44d920 */
/* selector: interpolate_matrix_rotation */

TransformMatrix *__thiscall interpolate_matrix_rotation(TransformMatrix *transform, float alpha)
{
  TransformMatrix *result; // eax
  __int16 v4; // fps
  bool v5; // c0
  char v6; // c2
  bool v7; // c3
  float v8; // [esp+8h] [ebp-70h] BYREF
  float v9; // [esp+Ch] [ebp-6Ch]
  float v10; // [esp+10h] [ebp-68h]
  float v11; // [esp+14h] [ebp-64h]
  float v12[4]; // [esp+18h] [ebp-60h] BYREF
  float v13[3]; // [esp+28h] [ebp-50h] BYREF
  float v14; // [esp+34h] [ebp-44h]
  float v15[16]; // [esp+38h] [ebp-40h] BYREF

  Iostream_init::Iostream_init((#93 *)&v8);
  Iostream_init::Iostream_init((#93 *)v13);
  initialize_quaternion_from_matrix(v12, &transform->basis_right.x);
  v8 = v12[0];
  v9 = v12[1];
  v11 = v12[3];
  v10 = v12[2];
  if ( v12[0] > -0.001 && v12[0] < 0.001 )
    v8 = 0.0;
  if ( v9 > -0.001 && v9 < 0.001 )
    v9 = 0.0;
  if ( v10 > -0.001 && v10 < 0.001 )
    v10 = 0.0;
  if ( v8 == 0.0 && v9 == 0.0 && v10 == 0.0 )
  {
    result = (TransformMatrix *)initialize_matrix_from_quaternion(v15, &v8);
    qmemcpy(transform, v15, sizeof(TransformMatrix));
  }
  else
  {
    initialize_axis_from_quaternion(v13, &v8);
    v5 = v14 < 0.0;
    v6 = 0;
    v7 = v14 == 0.0;
    LOWORD(result) = v4;
    if ( v14 != 0.0 )
    {
      v14 = v14 * alpha;
      initialize_quaternion_from_axis(&v8, v13);
      result = (TransformMatrix *)initialize_matrix_from_quaternion(v15, &v8);
      qmemcpy(transform, v15, sizeof(TransformMatrix));
    }
  }
  return result;
}

