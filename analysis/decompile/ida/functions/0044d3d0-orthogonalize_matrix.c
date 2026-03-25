/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: orthogonalize_matrix @ 0x44d3d0 */
/* selector: orthogonalize_matrix */

int32_t __fastcall orthogonalize_matrix(TransformMatrix *transform)
{
  Vec3 *p_basis_up; // edi
  Vec3 *p_basis_forward; // ebx

  p_basis_up = (Vec3 *)&transform->basis_up;
  p_basis_forward = (Vec3 *)&transform->basis_forward;
  normalize_vector((Vec3 *)transform);
  normalize_vector(p_basis_up);
  normalize_vector(p_basis_forward);
  cross_vectors((Vec3 *)transform, p_basis_up, p_basis_forward);
  return cross_vectors(p_basis_forward, (Vec3 *)transform, p_basis_up);
}

