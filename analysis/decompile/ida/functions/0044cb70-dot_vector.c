/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dot_vector @ 0x44cb70 */
/* selector: dot_vector */

// Computes the 3D dot product of one vector against another through the member-style overload `tVector::Dot(const tVector&)`.
double __thiscall sub_44CB70(float *this, float *a2)
{
  return a2[2] * *(this + 2) + a2[1] * *(this + 1) + *a2 * *this;
}

