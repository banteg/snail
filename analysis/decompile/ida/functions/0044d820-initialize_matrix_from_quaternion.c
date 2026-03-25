/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_matrix_from_quaternion @ 0x44d820 */
/* selector: initialize_matrix_from_quaternion */

// Builds a rotation matrix from a quaternion and resets translation and homogeneous slots to their identity values. Android symbols match this helper to `tMatrix::tMatrix(const tQuaternian&)`.
float *__thiscall sub_44D820(float *this, float *a2)
{
  float *result; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+4h] [ebp-10h]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]
  float v11; // [esp+10h] [ebp-4h]
  float v12; // [esp+18h] [ebp+4h]

  result = this;
  v4 = *a2 * *a2;
  v5 = a2[1] * *a2;
  v7 = a2[2] * *a2;
  v10 = a2[3] * *a2;
  v11 = a2[1] * a2[1];
  v9 = a2[2] * a2[1];
  v8 = a2[3] * a2[1];
  v12 = a2[2] * a2[2];
  v6 = a2[3] * a2[2];
  *result = 1.0 - (v12 + v11 + v12 + v11);
  result[4] = v5 - v6 + v5 - v6;
  result[8] = v8 + v7 + v8 + v7;
  result[1] = v6 + v5 + v6 + v5;
  result[5] = 1.0 - (v12 + v4 + v12 + v4);
  result[9] = v9 - v10 + v9 - v10;
  result[2] = v7 - v8 + v7 - v8;
  result[6] = v9 + v10 + v9 + v10;
  result[10] = 1.0 - (v11 + v4 + v11 + v4);
  result[11] = 0.0;
  result[7] = 0.0;
  result[3] = 0.0;
  result[14] = 0.0;
  result[13] = 0.0;
  result[12] = 0.0;
  result[15] = 1.0;
  return result;
}

