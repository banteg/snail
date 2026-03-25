/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_x @ 0x44ce30 */
/* selector: rotate_matrix_world_x */

void __thiscall sub_44CE30(float *this, float a2)
{
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st6
  double v8; // st7
  float v9; // [esp+Ch] [ebp+4h]

  v9 = cosine(a2);
  v4 = sine(a2);
  v5 = v4 * *(this + 8) + v9 * *(this + 4);
  *(this + 8) = v9 * *(this + 8) - v4 * *(this + 4);
  *(this + 4) = v5;
  v6 = v4 * *(this + 9) + v9 * *(this + 5);
  *(this + 9) = v9 * *(this + 9) - v4 * *(this + 5);
  *(this + 5) = v6;
  v7 = v9 * *(this + 10) - v4 * *(this + 6);
  v8 = v4 * *(this + 10) + v9 * *(this + 6);
  *(this + 10) = v7;
  *(this + 6) = v8;
}

