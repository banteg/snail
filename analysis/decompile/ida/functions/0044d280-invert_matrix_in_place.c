/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: invert_matrix_in_place @ 0x44d280 */
/* selector: invert_matrix_in_place */

// Void `tMatrix::Invert()` implementation: inverts one orthonormal transform matrix in place by transposing the basis and recomputing the negated translated origin. Windows and Android callers discard the incidental receiver register.
void __thiscall invert_matrix_in_place(TransformMatrix *transform)
{
  double v2; // st7
  float v3; // edx
  float v4; // ecx
  double v5; // st7
  double v6; // st6
  float v7; // edx
  float v8; // ecx
  double v9; // st7
  double v10; // st6
  float v11; // edx
  float v12[16]; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(v12, transform, sizeof(v12));
  v2 = v12[2] * transform->position.z + v12[13] * v12[1] + v12[12] * v12[0];
  v3 = v12[8];
  transform->basis_right.y = v12[4];
  v4 = v12[1];
  transform->position.x = -v2;
  v5 = v12[6] * transform->position.z;
  v6 = v12[5] * v12[13];
  transform->basis_right.z = v3;
  v7 = v12[9];
  transform->basis_up.x = v4;
  v8 = v12[2];
  v9 = v5 + v6;
  v10 = v12[4] * v12[12];
  transform->basis_up.z = v7;
  v11 = v12[6];
  transform->basis_forward.x = v8;
  transform->basis_forward.y = v11;
  transform->position.y = -(v9 + v10);
  transform->position.z = -(v12[10] * transform->position.z + v12[9] * v12[13] + v12[8] * v12[12]);
}
