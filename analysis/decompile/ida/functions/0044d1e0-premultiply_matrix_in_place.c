/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: premultiply_matrix_in_place @ 0x44d1e0 */
/* selector: premultiply_matrix_in_place */

// Exact void `TransformMatrix::premultiply_matrix_in_place(const TransformMatrix&)` member: snapshots its receiver and writes `this = lhs * saved_this`. The core's incidental EAX points at the dead stack snapshot, proving no meaningful return contract.
void __thiscall premultiply_matrix_in_place(TransformMatrix *matrix, const TransformMatrix *lhs)
{
  TransformMatrix v2; // [esp+8h] [ebp-40h] BYREF

  qmemcpy(&v2, matrix, sizeof(v2));
  multiply_matrices(matrix, lhs, &v2);
}
