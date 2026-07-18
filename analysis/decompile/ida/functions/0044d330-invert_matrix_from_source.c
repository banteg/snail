/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: invert_matrix_from_source @ 0x44d330 */
/* selector: invert_matrix_from_source */

// Void `tMatrix::Invert(tMatrix const&)` implementation: writes the inverse of a source orthonormal transform into a destination matrix. Its ordinary callers discard the result register, while cRPlayer/cROverlay AI only tail-call it under their independently void callback contracts.
void __thiscall invert_matrix_from_source(TransformMatrix *out, const TransformMatrix *source)
{
  out->position.x = -(source->position.y * source->basis_right.y
                    + source->basis_right.z * source->position.z
                    + source->position.x * source->basis_right.x);
  out->position.y = -(source->position.y * source->basis_up.y
                    + source->basis_up.z * source->position.z
                    + source->position.x * source->basis_up.x);
  out->position.z = -(source->position.y * source->basis_forward.y
                    + source->position.x * source->basis_forward.x
                    + source->position.z * source->basis_forward.z);
  out->basis_right.x = source->basis_right.x;
  out->basis_right.y = source->basis_up.x;
  out->basis_right.z = source->basis_forward.x;
  out->basis_up.x = source->basis_right.y;
  out->basis_up.y = source->basis_up.y;
  out->basis_up.z = source->basis_forward.y;
  out->basis_forward.x = source->basis_right.z;
  out->basis_forward.y = source->basis_up.z;
  out->basis_forward.z = source->basis_forward.z;
  out->basis_forward.w = 0.0;
  out->basis_up.w = 0.0;
  out->basis_right.w = 0.0;
  out->position.w = 1.0;
}
