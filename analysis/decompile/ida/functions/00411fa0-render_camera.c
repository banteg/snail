/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_camera @ 0x411fa0 */
/* selector: render_camera */

// Configures one 3D scene viewport, projection, view transform, depth state, fog state, and the after-sprites lane before world objects render. Cross-port Android symbols match this helper to `G0RenderCamera`.
int __usercall sub_411FA0@<eax>(
        int a1@<esi>,
        float a2,
        float a3,
        float a4,
        float a5,
        int a6,
        float a7,
        int a8,
        int a9,
        char a10,
        char a11)
{
  double v11; // st7
  double v12; // st7
  float v13; // edx
  int v14; // eax
  float v15; // ecx
  double v16; // st7
  float v17; // edx
  float v18; // eax
  double v19; // st7
  int v20; // edx
  int v21; // ecx
  float v23; // [esp+70h] [ebp-C4h] BYREF
  float v24; // [esp+74h] [ebp-C0h]
  int v25; // [esp+78h] [ebp-BCh]
  float v26[3]; // [esp+7Ch] [ebp-B8h] BYREF
  float v27[3]; // [esp+88h] [ebp-ACh] BYREF
  float v28[2]; // [esp+94h] [ebp-A0h] BYREF
  _DWORD v29[7]; // [esp+9Ch] [ebp-98h] BYREF
  int v30[16]; // [esp+B8h] [ebp-7Ch] BYREF
  float v31[15]; // [esp+F8h] [ebp-3Ch] BYREF

  v29[0] = (__int64)a2;
  v29[1] = (__int64)a3;
  v11 = a5 * 480.0;
  v29[2] = (__int64)(a4 * 640.0);
  v23 = v11;
  v29[3] = (__int64)v11;
  v29[4] = 0;
  v29[5] = 1065353216;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)MEMORY[0x502FEC] + 160))(MEMORY[0x502FEC], v29, a1);
  MEMORY[0x5031CC] = 0.30000001;
  MEMORY[0x5031D0] = 52.0;
  MEMORY[0x5031D4] = a7 * 0.017453292;
  MEMORY[0x50316C] = v23 / v24;
  build_perspective_projection_matrix((int)v30, MEMORY[0x5031D4], MEMORY[0x50316C], 0.30000001, 52.0);
  (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)MEMORY[0x502FEC] + 148))(MEMORY[0x502FEC], 3, v30);
  MEMORY[0x503260] = a11;
  v12 = *(float *)(a8 + 32) + *(float *)(a8 + 48);
  v13 = *(float *)(a8 + 52);
  v14 = *(_DWORD *)(a8 + 56);
  v28[0] = *(float *)(a8 + 48);
  v15 = *(float *)(a8 + 16);
  v28[1] = v13;
  v26[0] = v12;
  v16 = *(float *)(a8 + 36) + *(float *)(a8 + 52);
  v17 = *(float *)(a8 + 20);
  v29[0] = v14;
  v18 = *(float *)(a8 + 24);
  v27[0] = v15;
  v27[1] = v17;
  v26[1] = v16;
  v19 = *(float *)(a8 + 40) + *(float *)(a8 + 56);
  v27[2] = v18;
  v26[2] = v19;
  build_camera_view_matrix(v31, v28, v26, v27);
  (*(void (__stdcall **)(int, int, float *))(*(_DWORD *)MEMORY[0x502FEC] + 148))(MEMORY[0x502FEC], 2, v31);
  (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 7, 1);
  (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 14, 1);
  (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 23, 4);
  if ( a10 && *((_BYTE *)MEMORY[0x4DF904] + 4) )
  {
    v20 = *((_DWORD *)MEMORY[0x4DF904] + 3);
    v24 = *((float *)MEMORY[0x4DF904] + 2);
    v21 = *(_DWORD *)MEMORY[0x502FEC];
    v25 = v20;
    (*(void (__stdcall **)(int, int, int))(v21 + 200))(MEMORY[0x502FEC], 28, 1);
    Iostream_init::Iostream_init((#93 *)&v23);
    pack_color_rgba_u8(&v23, (float *)MEMORY[0x4DF904] + 5);
    HIBYTE(v23) = 0;
    (*(void (__stdcall **)(int, int, float))(*(_DWORD *)MEMORY[0x502FEC] + 200))(
      MEMORY[0x502FEC],
      34,
      COERCE_FLOAT(LODWORD(v23)));
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 140, 3);
    (*(void (__stdcall **)(int, int, float))(*(_DWORD *)MEMORY[0x502FEC] + 200))(
      MEMORY[0x502FEC],
      36,
      COERCE_FLOAT(LODWORD(v24)));
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 37, v25);
    (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 38);
  }
  else
  {
    (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 28);
  }
  MEMORY[0x5031B8] = a8;
  MEMORY[0x503218] = a8;
  MEMORY[0x503174] = 0;
  return a8;
}

