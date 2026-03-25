/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_blink_random @ 0x4408c0 */
/* selector: initialize_blink_random */

int __thiscall sub_4408C0(float *this)
{
  float *v1; // esi
  int v2; // edi
  int result; // eax

  *(this + 978368) = 0.0;
  v1 = this + 978369;
  v2 = 24;
  do
  {
    result = next_math_random_value();
    ++v1;
    --v2;
    *(v1 - 1) = 1.0 / (((double)result * 0.000030517578 + 1.0) * 60.0);
  }
  while ( v2 );
  return result;
}

