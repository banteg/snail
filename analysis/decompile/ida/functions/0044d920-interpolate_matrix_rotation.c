/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: interpolate_matrix_rotation @ 0x44d920 */
/* selector: interpolate_matrix_rotation */

void __thiscall sub_44D920(float *this, float a2)
{
  float v3; // [esp+8h] [ebp-70h] BYREF
  float v4; // [esp+Ch] [ebp-6Ch]
  float v5; // [esp+10h] [ebp-68h]
  float v6; // [esp+14h] [ebp-64h]
  float v7[4]; // [esp+18h] [ebp-60h] BYREF
  float v8[3]; // [esp+28h] [ebp-50h] BYREF
  float v9; // [esp+34h] [ebp-44h]
  float v10[16]; // [esp+38h] [ebp-40h] BYREF

  Iostream_init::Iostream_init((#93 *)&v3);
  Iostream_init::Iostream_init((#93 *)v8);
  initialize_quaternion_from_matrix(v7, this);
  v3 = v7[0];
  v4 = v7[1];
  v6 = v7[3];
  v5 = v7[2];
  if ( v7[0] > -0.001 && v7[0] < 0.001 )
    v3 = 0.0;
  if ( v4 > -0.001 && v4 < 0.001 )
    v4 = 0.0;
  if ( v5 > -0.001 && v5 < 0.001 )
    v5 = 0.0;
  if ( v3 == 0.0 && v4 == 0.0 && v5 == 0.0 )
  {
    initialize_matrix_from_quaternion(v10, &v3);
    qmemcpy(this, v10, 0x40u);
  }
  else
  {
    initialize_axis_from_quaternion(v8, &v3);
    if ( v9 != 0.0 )
    {
      v9 = v9 * a2;
      initialize_quaternion_from_axis(&v3, v8);
      initialize_matrix_from_quaternion(v10, &v3);
      qmemcpy(this, v10, 0x40u);
    }
  }
}

