/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_matrix_from_values @ 0x44cfe0 */
/* selector: initialize_matrix_from_values */

// Stable Windows harness identity for the authored 16-float `tMatrix::tMatrix(float, ..., float)` constructor retained by Android and iOS. The exact constructor writes all four matrix rows and returns its receiver only through the ordinary VC6 constructor ABI.
TransformMatrix *__thiscall initialize_matrix_from_values(
        TransformMatrix *transform,
        float m00,
        float m01,
        float m02,
        float m03,
        float m10,
        float m11,
        float m12,
        float m13,
        float m20,
        float m21,
        float m22,
        float m23,
        float m30,
        float m31,
        float m32,
        float m33)
{
  transform->basis_right.x = m00;
  transform->basis_right.y = m01;
  transform->basis_right.z = m02;
  transform->basis_right.w = m03;
  transform->basis_up.x = m10;
  transform->basis_up.y = m11;
  transform->basis_up.z = m12;
  transform->basis_up.w = m13;
  transform->basis_forward.x = m20;
  transform->basis_forward.y = m21;
  transform->basis_forward.z = m22;
  transform->basis_forward.w = m23;
  transform->position.x = m30;
  transform->position.y = m31;
  transform->position.z = m32;
  transform->position.w = m33;
  return transform;
}
