/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rotate_matrix_world_z @ 0x44cf50 */
/* selector: rotate_matrix_world_z */

void __thiscall sub_44CF50(float *this, float a2)
{
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st6
  double v8; // st7
  float v9; // [esp+Ch] [ebp+4h]

  v9 = cosine(a2);
  v4 = sine(a2);
  v5 = v9 * *this + v4 * *(this + 4);
  *(this + 4) = v9 * *(this + 4) - v4 * *this;
  *this = v5;
  v6 = v4 * *(this + 5) + v9 * *(this + 1);
  *(this + 5) = v9 * *(this + 5) - v4 * *(this + 1);
  *(this + 1) = v6;
  v7 = v9 * *(this + 6) - v4 * *(this + 2);
  v8 = v4 * *(this + 6) + v9 * *(this + 2);
  *(this + 6) = v7;
  *(this + 2) = v8;
}

