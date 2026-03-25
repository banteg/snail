/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_mouse @ 0x44bc50 */
/* selector: update_mouse */

int __cdecl update_mouse(int hWnd)
{
  int v1; // ecx
  int v2; // eax
  int v3; // edi
  int v4; // edx
  int v6; // [esp-1Ch] [ebp-74h]
  int v7; // [esp-18h] [ebp-70h]
  int v8; // [esp-14h] [ebp-6Ch]
  int v9; // [esp-10h] [ebp-68h]
  int v10; // [esp-10h] [ebp-68h]
  char v11; // [esp-Ch] [ebp-64h]
  char v12; // [esp-Ch] [ebp-64h]
  char v13; // [esp-8h] [ebp-60h]
  char v14; // [esp-8h] [ebp-60h]
  char v15; // [esp+0h] [ebp-58h]
  char v16; // [esp+0h] [ebp-58h]
  char v17; // [esp+4h] [ebp-54h]
  char v18; // [esp+4h] [ebp-54h]
  __int64 Rect; // [esp+14h] [ebp-44h] BYREF
  __int64 Rect_8; // [esp+1Ch] [ebp-3Ch]
  int v21; // [esp+24h] [ebp-34h] BYREF
  int v22; // [esp+28h] [ebp-30h]
  int v23; // [esp+2Ch] [ebp-2Ch]
  int v24; // [esp+30h] [ebp-28h]
  int v25; // [esp+34h] [ebp-24h] BYREF
  int v26; // [esp+38h] [ebp-20h]
  int v27; // [esp+3Ch] [ebp-1Ch]
  int v28; // [esp+40h] [ebp-18h]
  int v29; // [esp+44h] [ebp-14h] BYREF
  int v30; // [esp+48h] [ebp-10h]
  int v31; // [esp+4Ch] [ebp-Ch]
  int v32; // [esp+50h] [ebp-8h]
  int v33; // [esp+54h] [ebp-4h]

  if ( dword_777B2C[156] )
  {
    v29 = 0;
    v30 = 0;
    v31 = 0;
    v32 = 0;
    v33 = 0;
    if ( (*(int (__stdcall **)(int, int, int *))(*(_DWORD *)dword_777B2C[156] + 36))(dword_777B2C[156], 20, &v29) < 0 )
    {
      while ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_777B2C[156] + 28))(dword_777B2C[156]) == -2147024866 )
        ;
    }
  }
  if ( !((int (__stdcall *)(int, __int64 *))GetWindowRect)(hWnd, &Rect)
    || !((int (__stdcall *)(int, int *))GetClientRect)(hWnd, &v21) )
  {
    Rect = 0;
    Rect_8 = 0;
  }
  if ( unk_4DFAF4 || !is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
  {
    *(float *)&dword_777B2C[139] = (double)v29 + *(float *)&dword_777B2C[139];
    *(float *)&dword_777B2C[141] = (double)v30 + *(float *)&dword_777B2C[141];
    if ( *(float *)&dword_777B2C[139] >= 0.0 )
    {
      if ( *(float *)&dword_777B2C[139] > 639.0 )
        dword_777B2C[139] = 1142931456;
    }
    else
    {
      dword_777B2C[139] = 0;
    }
    if ( *(float *)&dword_777B2C[141] >= 0.0 )
    {
      if ( *(float *)&dword_777B2C[141] > 479.0 )
        dword_777B2C[141] = 1139769344;
    }
    else
    {
      dword_777B2C[141] = 0;
    }
  }
  else
  {
    convert_mouse_screen_xy(0, &dword_777B2C[139], &dword_777B2C[141]);
  }
  if ( unk_4DFAF4 || !is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
  {
    ((void (__stdcall *)(_DWORD))ClipCursor)(0);
    if ( !is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
    {
      v25 = Rect + v21 - MEMORY[0x4B7780];
      v27 = Rect_8 + v23 - unk_4B7788;
      v26 = HIDWORD(Rect) + v22 - unk_4B7784;
      v28 = HIDWORD(Rect_8) + v24 - unk_4B778C;
      ((void (__stdcall *)(int *))ClipCursor)(&v25);
      v18 = unk_4DFAF4;
      v16 = is_mouse_captured((char *)MEMORY[0x4DF904] + 656);
      v14 = read_right_mouse_button_state(0);
      v12 = read_left_mouse_button_state(0);
      v10 = consume_mouse_wheel_delta(0);
      update_input_controller_pointer_region(
        0,
        0,
        0,
        640,
        480,
        (__int64)*(float *)&dword_777B2C[139],
        (__int64)*(float *)&dword_777B2C[141],
        v10,
        v12,
        v14,
        0,
        v16,
        v18);
      goto LABEL_29;
    }
    v17 = unk_4DFAF4;
    v15 = is_mouse_captured((char *)MEMORY[0x4DF904] + 656);
    v13 = read_right_mouse_button_state(0);
    v11 = read_left_mouse_button_state(0);
    v9 = consume_mouse_wheel_delta(0);
    v8 = (__int64)*(float *)&dword_777B2C[141];
    v1 = HIDWORD(Rect);
    v7 = (__int64)*(float *)&dword_777B2C[139];
    v2 = unk_4B7774;
    v3 = v23;
    v6 = HIDWORD(Rect) + v24 - unk_4B7774;
    v4 = unk_4B7770;
  }
  else
  {
    if ( is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
    {
      ((void (__stdcall *)(_DWORD))ClipCursor)(0);
    }
    else
    {
      v25 = Rect + v21 - MEMORY[0x4B7780];
      v27 = Rect_8 + v23 - unk_4B7788;
      v26 = HIDWORD(Rect) + v22 - unk_4B7784;
      v28 = HIDWORD(Rect_8) + v24 - unk_4B778C;
      ((void (__stdcall *)(int *))ClipCursor)(&v25);
    }
    v17 = unk_4DFAF4;
    v15 = is_mouse_captured((char *)MEMORY[0x4DF904] + 656);
    v13 = read_right_mouse_button_state(0);
    v11 = read_left_mouse_button_state(0);
    v9 = consume_mouse_wheel_delta(0);
    v8 = (__int64)*(float *)&dword_777B2C[141];
    v1 = HIDWORD(Rect);
    v7 = (__int64)*(float *)&dword_777B2C[139];
    v2 = unk_4B7784;
    v3 = v23;
    v6 = HIDWORD(Rect) + v24 - unk_4B7784;
    v4 = MEMORY[0x4B7780];
  }
  update_input_controller_pointer_region(
    0,
    Rect + v21 - v4,
    v1 + v22 - v2,
    Rect + v3 - v4,
    v6,
    v7,
    v8,
    v9,
    v11,
    v13,
    0,
    v15,
    v17);
LABEL_29:
  if ( LOBYTE(dword_777B2C[145]) )
    ((void (__stdcall *)(_DWORD))SetCursor)(0);
  return 0;
}

