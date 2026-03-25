/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: vector_magnitude @ 0x44ccf0 */
/* selector: vector_magnitude */

void __thiscall vector_magnitude(float *this)
{
  float v1; // [esp+0h] [ebp-4h]

  v1 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  square_root(v1);
}

