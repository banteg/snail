/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_matrix_from_quaternion @ 0x44d820 */
/* selector: initialize_matrix_from_quaternion */

// Stable Windows harness identity for the authored `tMatrix::tMatrix(const tQuaternian&)` constructor retained by Android. The exact typed const-reference constructor builds the rotation basis and resets translation and homogeneous slots to identity values.
TransformMatrix *__thiscall initialize_matrix_from_quaternion(TransformMatrix *out, const Quaternion *quaternion)
{
  TransformMatrix *result; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  float v7; // [esp+0h] [ebp-14h]
  float v8; // [esp+4h] [ebp-10h]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]
  float v11; // [esp+10h] [ebp-4h]
  float quaterniona; // [esp+18h] [ebp+4h]

  result = out;
  v4 = quaternion->x * quaternion->x;
  v5 = quaternion->y * quaternion->x;
  v7 = quaternion->z * quaternion->x;
  v10 = quaternion->w * quaternion->x;
  v11 = quaternion->y * quaternion->y;
  v9 = quaternion->z * quaternion->y;
  v8 = quaternion->w * quaternion->y;
  quaterniona = quaternion->z * quaternion->z;
  v6 = quaternion->w * quaternion->z;
  result->basis_right.x = 1.0 - (quaterniona + v11 + quaterniona + v11);
  result->basis_up.x = v5 - v6 + v5 - v6;
  result->basis_forward.x = v8 + v7 + v8 + v7;
  result->basis_right.y = v6 + v5 + v6 + v5;
  result->basis_up.y = 1.0 - (quaterniona + v4 + quaterniona + v4);
  result->basis_forward.y = v9 - v10 + v9 - v10;
  result->basis_right.z = v7 - v8 + v7 - v8;
  result->basis_up.z = v9 + v10 + v9 + v10;
  result->basis_forward.z = 1.0 - (v11 + v4 + v11 + v4);
  result->basis_forward.w = 0.0;
  result->basis_up.w = 0.0;
  result->basis_right.w = 0.0;
  result->position.z = 0.0;
  result->position.y = 0.0;
  result->position.x = 0.0;
  result->position.w = 1.0;
  return result;
}
