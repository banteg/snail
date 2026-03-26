/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: invert_matrix_from_source @ 0x44d330 */
/* selector: invert_matrix_from_source */

// Writes the inverse of a source orthonormal transform into a destination matrix. Android symbols match this helper to `tMatrix::Invert(const tMatrix&)`.
TransformMatrix *__fastcall invert_matrix_from_source(TransformMatrix *out, TransformMatrix *source)
{
  float *v3; // [esp+4h] [ebp+4h]

  out->position.x = -(v3[13] * v3[1] + v3[2] * v3[14] + v3[12] * *v3);
  out->position.y = -(v3[13] * v3[5] + v3[6] * v3[14] + v3[12] * v3[4]);
  out->position.z = -(v3[13] * v3[9] + v3[12] * v3[8] + v3[14] * v3[10]);
  out->basis_right.x = *v3;
  out->basis_right.y = v3[4];
  out->basis_right.z = v3[8];
  out->basis_up.x = v3[1];
  out->basis_up.y = v3[5];
  out->basis_up.z = v3[9];
  out->basis_forward.x = v3[2];
  out->basis_forward.y = v3[6];
  out->basis_forward.z = v3[10];
  out->basis_forward.w = 0.0;
  out->basis_up.w = 0.0;
  out->basis_right.w = 0.0;
  out->position.w = 1.0;
  return nullptr;
}

