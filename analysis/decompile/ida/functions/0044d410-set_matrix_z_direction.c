/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_matrix_z_direction @ 0x44d410 */
/* selector: set_matrix_z_direction */

void __userpurge sub_44D410(int a1@<ecx>, double a2@<st0>, _DWORD *a3)
{
  bool v4; // c3
  float v5; // ecx
  float v6; // edx
  int v7; // eax
  float v8; // ecx
  int v9; // [esp+8h] [ebp-18h] BYREF
  int v10; // [esp+Ch] [ebp-14h]
  float v11; // [esp+10h] [ebp-10h]
  float v12[2]; // [esp+14h] [ebp-Ch] BYREF
  float v13; // [esp+1Ch] [ebp-4h]

  normalize_vector_from_source((int)v12, a3);
  if ( a2 != 0.0 )
  {
    v4 = v12[0] == 0.0;
    v5 = v12[0];
    v6 = v12[1];
    *(float *)(a1 + 40) = v13;
    *(float *)(a1 + 32) = v5;
    *(float *)(a1 + 36) = v6;
    if ( v4 && v13 == 0.0 )
    {
      v9 = 1065353216;
      v11 = 0.0;
    }
    else
    {
      v11 = -v12[0];
      v9 = LODWORD(v13);
    }
    v10 = 0;
    normalize_vector((float *)&v9);
    v7 = v10;
    v8 = v11;
    *(_DWORD *)a1 = v9;
    *(_DWORD *)(a1 + 4) = v7;
    *(float *)(a1 + 8) = v8;
    cross_vectors((float *)(a1 + 16), v12, (float *)&v9);
  }
}

