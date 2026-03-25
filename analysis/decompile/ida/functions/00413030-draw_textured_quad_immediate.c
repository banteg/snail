/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_textured_quad_immediate @ 0x413030 */
/* selector: draw_textured_quad_immediate */

// Builds one immediate 2D textured quad in the transient UI vertex buffer, supporting explicit corner coordinates, axis-aligned size, or centered rotation before submitting the quad as a six-index primitive.
int __cdecl sub_413030(
        int a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11,
        float a12,
        float a13,
        float a14,
        float a15,
        float *a16,
        int a17,
        float a18)
{
  char v19; // c3
  char v21; // c3
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st6
  double v26; // st7
  int result; // eax
  float v28; // [esp+20h] [ebp-14h]
  int v29; // [esp+2Ch] [ebp-8h] BYREF
  float v30; // [esp+30h] [ebp-4h] BYREF
  float v31; // [esp+3Ch] [ebp+8h]
  float v32; // [esp+40h] [ebp+Ch]
  float v33; // [esp+5Ch] [ebp+28h]
  float v34; // [esp+5Ch] [ebp+28h]
  float v35; // [esp+60h] [ebp+2Ch]

  (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 22, 1);
  sub_414500(a1);
  sub_412E50(a17);
  Iostream_init::Iostream_init((#93 *)&v30);
  pack_color_rgba_u8(&v30, a16);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD))(**(_DWORD **)(MEMORY[0x502FE0] + 8) + 44))(
    *(_DWORD *)(MEMORY[0x502FE0] + 8),
    0,
    96,
    &v29,
    0);
  if ( v19 )
  {
    *(float *)v29 = a2;
    *(float *)(v29 + 4) = a3;
    *(_DWORD *)(v29 + 8) = 0;
    *(float *)(v29 + 16) = a12;
    *(float *)(v29 + 20) = a13;
    if ( v21 )
    {
      *(float *)(v29 + 12) = v30;
      *(float *)(v29 + 24) = a4;
      *(float *)(v29 + 28) = a5;
      *(_DWORD *)(v29 + 32) = 0;
      *(float *)(v29 + 40) = a14;
      *(float *)(v29 + 44) = a13;
      *(float *)(v29 + 36) = v30;
      *(float *)(v29 + 48) = a6;
      *(float *)(v29 + 52) = a7;
      *(_DWORD *)(v29 + 56) = 0;
      *(float *)(v29 + 64) = a14;
      *(float *)(v29 + 68) = a15;
      *(float *)(v29 + 60) = v30;
      *(float *)(v29 + 72) = a8;
      *(float *)(v29 + 76) = a9;
    }
    else
    {
      v22 = a2 + a10;
      *(float *)(v29 + 12) = v30;
      *(float *)(v29 + 24) = v22;
      *(float *)(v29 + 28) = a3;
      *(_DWORD *)(v29 + 32) = 0;
      *(float *)(v29 + 40) = a14;
      *(float *)(v29 + 44) = a13;
      *(float *)(v29 + 36) = v30;
      *(float *)(v29 + 48) = v22;
      v23 = a3 + a11;
      *(float *)(v29 + 52) = v23;
      *(_DWORD *)(v29 + 56) = 0;
      *(float *)(v29 + 64) = a14;
      *(float *)(v29 + 68) = a15;
      *(float *)(v29 + 60) = v30;
      *(float *)(v29 + 72) = a2;
      *(float *)(v29 + 76) = v23;
    }
    *(_DWORD *)(v29 + 80) = 0;
    *(float *)(v29 + 88) = a12;
    *(float *)(v29 + 92) = a15;
    *(float *)(v29 + 84) = v30;
  }
  else
  {
    v24 = a10 * 0.5;
    v31 = v24 + a2;
    v25 = a11 * 0.5;
    v33 = v25;
    v32 = v25 + a3;
    v28 = v33 * v33 + v24 * v24;
    v35 = square_root(v28) * 1.414;
    v34 = sine(a18) * v35;
    v26 = cosine(a18) * v35;
    *(float *)v29 = v34 + v31;
    *(float *)(v29 + 4) = v26 + v32;
    *(_DWORD *)(v29 + 8) = 0;
    *(float *)(v29 + 16) = a12;
    *(float *)(v29 + 20) = a13;
    *(float *)(v29 + 12) = v30;
    *(float *)(v29 + 24) = v31 - v26;
    *(float *)(v29 + 28) = v34 + v32;
    *(_DWORD *)(v29 + 32) = 0;
    *(float *)(v29 + 40) = a14;
    *(float *)(v29 + 44) = a13;
    *(float *)(v29 + 36) = v30;
    *(float *)(v29 + 48) = v31 - v34;
    *(float *)(v29 + 52) = v32 - v26;
    *(_DWORD *)(v29 + 56) = 0;
    *(float *)(v29 + 64) = a14;
    *(float *)(v29 + 68) = a15;
    *(float *)(v29 + 60) = v30;
    *(float *)(v29 + 72) = v26 + v31;
    *(float *)(v29 + 76) = v32 - v34;
    *(_DWORD *)(v29 + 80) = 0;
    *(float *)(v29 + 88) = a12;
    *(float *)(v29 + 92) = a15;
    *(float *)(v29 + 84) = v30;
  }
  (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(MEMORY[0x502FE0] + 8) + 48))(*(_DWORD *)(MEMORY[0x502FE0] + 8));
  (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 332))(
    MEMORY[0x502FEC],
    0,
    *(_DWORD *)(MEMORY[0x502FE0] + 8),
    24);
  (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 304))(MEMORY[0x502FEC], 322);
  result = (*(int (__stdcall **)(int, int, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 280))(MEMORY[0x502FEC], 6, 0, 2);
  MEMORY[0x4F7450] += 2;
  ++MEMORY[0x503170];
  if ( result )
    return report_errorf(aDrawPrimitiveF);
  ++MEMORY[0x4F7454];
  return result;
}

