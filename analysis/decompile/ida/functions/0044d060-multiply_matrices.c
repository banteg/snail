/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: multiply_matrices @ 0x44d060 */
/* selector: multiply_matrices */

// Exact void `TransformMatrix::multiply_matrices(const TransformMatrix&, const TransformMatrix&)` member: writes `this = lhs * rhs` for the 3x3 basis and translated origin row. Android retains `tMatrix::Multiply(const tMatrix&, const tMatrix&)`; the right operand left in EAX is incidental.
void __thiscall multiply_matrices(TransformMatrix *out, const TransformMatrix *lhs, const TransformMatrix *rhs)
{
  out->basis_right.x = lhs->basis_right.x * rhs->basis_right.x
                     + lhs->basis_right.y * rhs->basis_up.x
                     + lhs->basis_right.z * rhs->basis_forward.x;
  out->basis_right.y = lhs->basis_right.y * rhs->basis_up.y
                     + rhs->basis_right.y * lhs->basis_right.x
                     + rhs->basis_forward.y * lhs->basis_right.z;
  out->basis_right.z = lhs->basis_right.y * rhs->basis_up.z
                     + rhs->basis_right.z * lhs->basis_right.x
                     + rhs->basis_forward.z * lhs->basis_right.z;
  out->basis_up.x = lhs->basis_up.z * rhs->basis_forward.x
                  + lhs->basis_up.y * rhs->basis_up.x
                  + lhs->basis_up.x * rhs->basis_right.x;
  out->basis_up.y = lhs->basis_up.z * rhs->basis_forward.y
                  + lhs->basis_up.y * rhs->basis_up.y
                  + lhs->basis_up.x * rhs->basis_right.y;
  out->basis_up.z = lhs->basis_up.z * rhs->basis_forward.z
                  + lhs->basis_up.y * rhs->basis_up.z
                  + lhs->basis_up.x * rhs->basis_right.z;
  out->basis_forward.x = lhs->basis_forward.x * rhs->basis_right.x
                       + lhs->basis_forward.z * rhs->basis_forward.x
                       + lhs->basis_forward.y * rhs->basis_up.x;
  out->basis_forward.y = rhs->basis_forward.y * lhs->basis_forward.z
                       + rhs->basis_up.y * lhs->basis_forward.y
                       + rhs->basis_right.y * lhs->basis_forward.x;
  out->basis_forward.z = rhs->basis_forward.z * lhs->basis_forward.z
                       + rhs->basis_up.z * lhs->basis_forward.y
                       + rhs->basis_right.z * lhs->basis_forward.x;
  out->position.x = lhs->position.z * rhs->basis_forward.x
                  + lhs->position.y * rhs->basis_up.x
                  + lhs->position.x * rhs->basis_right.x
                  + rhs->position.x;
  out->position.y = lhs->position.z * rhs->basis_forward.y
                  + lhs->position.y * rhs->basis_up.y
                  + lhs->position.x * rhs->basis_right.y
                  + rhs->position.y;
  out->position.z = lhs->position.z * rhs->basis_forward.z
                  + lhs->position.y * rhs->basis_up.z
                  + lhs->position.x * rhs->basis_right.z
                  + rhs->position.z;
}
