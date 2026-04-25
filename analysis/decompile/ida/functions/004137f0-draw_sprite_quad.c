/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_sprite_quad @ 0x4137f0 */
/* selector: draw_sprite_quad */

// Builds and submits one textured sprite quad from the sprite color, scale, angle, and stretch lanes. The star-field pass at `initialize_star_field` and `update_star_positions` reaches this helper through the shared sprite renderer.
int __cdecl sub_4137F0(int a1, float a2)
{
  int v2; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st6
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  double v10; // st6
  int result; // eax
  float v12; // [esp+18h] [ebp-5Ch]
  float v13; // [esp+1Ch] [ebp-58h]
  float v14; // [esp+20h] [ebp-54h]
  int v15; // [esp+20h] [ebp-54h]
  float v16; // [esp+20h] [ebp-54h]
  float v17; // [esp+20h] [ebp-54h]
  int v18; // [esp+2Ch] [ebp-48h] BYREF
  float v19; // [esp+30h] [ebp-44h]
  int v20[16]; // [esp+34h] [ebp-40h] BYREF

  v14 = *(float *)(a1 + 8);
  v13 = *(float *)(a1 + 4);
  v12 = *(float *)a1;
  memset(&v20[11], 0, 16);
  memset(&v20[6], 0, 16);
  memset(&v20[1], 0, 16);
  v20[15] = 1065353216;
  v20[10] = 1065353216;
  v20[5] = 1065353216;
  v20[0] = 1065353216;
  sub_44FD8A((int)v20, v12, v13, v14);
  (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)MEMORY[0x502FEC] + 148))(MEMORY[0x502FEC], 2, v20);
  v2 = LODWORD(a2);
  v15 = *(_DWORD *)(LODWORD(a2) + 28);
  a2 = (1.0 - *(float *)(LODWORD(a2) + 104)) * *(float *)(LODWORD(a2) + 96)
     + *(float *)(LODWORD(a2) + 100) * *(float *)(LODWORD(a2) + 104);
  bind_texture_ref(v15);
  configure_sprite_render_state(v2);
  if ( (*(_DWORD *)(v2 + 4) & 0x1000) != 0 )
    v19 = 1.0;
  else
    v19 = (1.0 - *(float *)(v2 + 104)) * *(float *)(v2 + 56);
  Iostream_init::Iostream_init((#93 *)&v18);
  pack_color_rgba_u8(&v18, (float *)(v2 + 44));
  HIBYTE(v18) = (__int64)(v19 * 255.0);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD))(**(_DWORD **)(MEMORY[0x502FE0] + 8) + 44))(
    *(_DWORD *)(MEMORY[0x502FE0] + 8),
    0,
    96,
    &a1,
    0);
  if ( *(float *)(v2 + 124) == 0.0 )
  {
    v3 = -a2;
    *(float *)a1 = v3;
    *(float *)(a1 + 4) = a2;
    v4 = a2;
    *(_DWORD *)(a1 + 8) = 0;
    *(_DWORD *)(a1 + 16) = 0;
    *(_DWORD *)(a1 + 20) = 0;
    *(_DWORD *)(a1 + 12) = v18;
    *(float *)(a1 + 24) = v4;
    *(float *)(a1 + 28) = a2;
    v5 = a2;
    *(_DWORD *)(a1 + 32) = 0;
    *(_DWORD *)(a1 + 40) = 1065353216;
    *(_DWORD *)(a1 + 44) = 0;
    *(_DWORD *)(a1 + 36) = v18;
    *(float *)(a1 + 48) = v5;
    *(float *)(a1 + 52) = v3;
    *(_DWORD *)(a1 + 56) = 0;
    *(_DWORD *)(a1 + 64) = 1065353216;
    *(_DWORD *)(a1 + 68) = 1065353216;
    *(_DWORD *)(a1 + 60) = v18;
    *(float *)(a1 + 72) = v3;
  }
  else
  {
    v16 = *(float *)(v2 + 124) + 0.78539819;
    v6 = cosine(v16);
    v19 = v6 * a2 * 1.414;
    v17 = *(float *)(v2 + 124) + 0.78539819;
    v7 = sine(v17);
    v8 = v7 * a2 * 1.414;
    *(float *)a1 = -v8;
    *(float *)(a1 + 4) = v19;
    v9 = v19;
    *(_DWORD *)(a1 + 8) = 0;
    *(_DWORD *)(a1 + 16) = 0;
    *(_DWORD *)(a1 + 20) = 0;
    *(_DWORD *)(a1 + 12) = v18;
    *(float *)(a1 + 24) = v9;
    *(float *)(a1 + 28) = v8;
    *(_DWORD *)(a1 + 32) = 0;
    *(_DWORD *)(a1 + 40) = 1065353216;
    *(_DWORD *)(a1 + 44) = 0;
    *(_DWORD *)(a1 + 36) = v18;
    *(float *)(a1 + 48) = v8;
    *(float *)(a1 + 52) = -v19;
    v10 = v19;
    *(_DWORD *)(a1 + 56) = 0;
    *(_DWORD *)(a1 + 64) = 1065353216;
    *(_DWORD *)(a1 + 68) = 1065353216;
    *(_DWORD *)(a1 + 60) = v18;
    *(float *)(a1 + 72) = -(v10 * *(float *)(v2 + 136));
    v3 = -(v8 * *(float *)(v2 + 136));
  }
  *(float *)(a1 + 76) = v3;
  *(_DWORD *)(a1 + 80) = 0;
  *(_DWORD *)(a1 + 88) = 0;
  *(_DWORD *)(a1 + 92) = 1065353216;
  *(_DWORD *)(a1 + 84) = v18;
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
  return result;
}

