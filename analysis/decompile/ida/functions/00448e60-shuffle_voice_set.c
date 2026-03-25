/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shuffle_voice_set @ 0x448e60 */
/* selector: shuffle_voice_set */

int __thiscall sub_448E60(int *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // ecx
  __int64 v5; // rax

  v2 = 100;
  do
  {
    v3 = (__int64)((double)next_math_random_value() * (double)*this * 0.000030517578);
    v5 = (__int64)((double)next_math_random_value() * (double)*this * 0.000030517578);
    v4 = *(this + 2);
    --v2;
    HIDWORD(v5) = *(_DWORD *)(v4 + 4 * v3);
    *(_DWORD *)(v4 + 4 * v3) = *(_DWORD *)(v4 + 4 * v5);
    *(_DWORD *)(*(this + 2) + 4 * v5) = HIDWORD(v5);
  }
  while ( v2 );
  return v5;
}

