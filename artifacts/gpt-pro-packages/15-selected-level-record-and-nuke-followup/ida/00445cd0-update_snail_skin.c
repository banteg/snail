/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin @ 0x445cd0 */
/* selector: update_snail_skin */

int __fastcall sub_445CD0(_DWORD *a1)
{
  int v1; // ebx
  _DWORD *v2; // ebp
  const void *v3; // esi
  int result; // eax
  _DWORD *v5; // ecx
  int v6; // edx
  float v7[16]; // [esp-40h] [ebp-60h] BYREF
  _DWORD *v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+14h] [ebp-Ch] BYREF
  int v10; // [esp+18h] [ebp-8h]
  int v11; // [esp+1Ch] [ebp-4h]

  v8 = a1;
  v1 = 0;
  v2 = a1 + 1516;
  while ( 1 )
  {
    v3 = a1 + 1441;
    v9 = *(v2 - 57);
    v10 = *(v2 - 56);
    v11 = *(v2 - 55);
    if ( v1 >= 11 )
      v3 = a1 + 1409;
    qmemcpy(v7, v3, sizeof(v7));
    multiply_vector_by_matrix(
      (float *)&v9,
      v7[0],
      v7[1],
      v7[2],
      SLODWORD(v7[3]),
      v7[4],
      v7[5],
      v7[6],
      SLODWORD(v7[7]),
      v7[8],
      v7[9],
      v7[10],
      SLODWORD(v7[11]),
      v7[12],
      v7[13],
      v7[14],
      SLODWORD(v7[15]));
    result = v10;
    v5 = v2;
    ++v1;
    v2 += 3;
    *v5 = v9;
    v6 = v11;
    v5[1] = result;
    v5[2] = v6;
    if ( v1 >= 19 )
      break;
    a1 = v8;
  }
  return result;
}
