/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_vapour_point @ 0x442560 */
/* selector: add_vapour_point */

_DWORD *__thiscall sub_442560(_DWORD *this, const void *a2)
{
  _DWORD *result; // eax
  int v3; // edi
  int v4; // ecx
  int v5; // ebx
  int v6; // edx
  int v7; // ecx
  const void *v8; // esi
  void *v9; // edi
  int v10; // edx

  result = this;
  v3 = *(this + 32);
  v4 = *(this + 33);
  if ( v3 >= v4 )
  {
    v5 = 0;
    if ( v4 - 1 > 0 )
    {
      v6 = 0;
      do
      {
        v7 = result[36];
        ++v5;
        v8 = (const void *)(v6 + v7 + 64);
        v9 = (void *)(v6 + v7);
        v6 += 64;
        qmemcpy(v9, v8, 0x40u);
      }
      while ( v5 < result[33] - 1 );
    }
    v10 = result[32];
    result = (_DWORD *)result[36];
    qmemcpy(&result[16 * v10 - 16], a2, 0x40u);
  }
  else
  {
    qmemcpy((void *)(result[36] + (v3 << 6)), a2, 0x40u);
    ++result[32];
  }
  return result;
}

