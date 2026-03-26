/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: premultiply_matrix_in_place @ 0x44d1e0 */
/* selector: premultiply_matrix_in_place */

TransformMatrix *__thiscall premultiply_matrix_in_place(TransformMatrix *lhs, TransformMatrix *rhs)
{
  float v3[16]; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(v3, lhs, sizeof(v3));
  return (TransformMatrix *)multiply_matrices(&lhs->basis_right.x, &rhs->basis_right.x, v3);
}

