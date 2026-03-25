/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_bod_position @ 0x42f680 */
/* selector: apply_bod_position */

int __thiscall sub_42F680(_DWORD *this, float *a2)
{
  int v3; // ebx
  int result; // eax
  int v5; // esi
  float *v6; // eax
  _DWORD *v7; // ecx
  float v8[3]; // [esp+8h] [ebp-Ch] BYREF

  v3 = 0;
  result = *(this + 9);
  if ( *(int *)(result + 44) > 0 )
  {
    v5 = 0;
    do
    {
      v6 = multiply_vector_by_matrix_copy((float *)(v5 + *(_DWORD *)(result + 56)), v8, a2);
      v7 = (_DWORD *)(v5 + *(_DWORD *)(*(this + 9) + 56));
      ++v3;
      v5 += 12;
      *v7 = *(_DWORD *)v6;
      v7[1] = *((_DWORD *)v6 + 1);
      v7[2] = *((_DWORD *)v6 + 2);
      result = *(this + 9);
    }
    while ( v3 < *(_DWORD *)(result + 44) );
  }
  return result;
}

