/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_uniform_scale_matrix @ 0x44cde0 */
/* selector: initialize_uniform_scale_matrix */

// Initializes a matrix from one scalar by writing the same value across the xyz diagonal, zeroing the off-diagonal and translation slots, and setting homogeneous `w` to 1.0. Android symbols match this helper to the single-float `tMatrix::tMatrix(float)` constructor.
_DWORD *__thiscall sub_44CDE0(_DWORD *this, int a2)
{
  *this = a2;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = a2;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = a2;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 1065353216;
  return this;
}

