/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_window_and_input @ 0x4119d0 */
/* selector: initialize_game_window_and_input */

// Registers the SnailMail window class, applies the recovered 4:3 resolution presets, falls back to a 640x480 windowed client, and initializes keyboard, controller, and mouse input.
int __cdecl initialize_game_window_and_input(int lpWindowName)
{
  int v1; // esi
  int v2; // ebp
  int v3; // ebx
  float v4; // eax
  int v5; // edi
  unsigned int v6; // esi
  int v7; // eax
  float v9; // [esp+0h] [ebp-FCh]
  float v10; // [esp+4h] [ebp-F8h]
  int v11; // [esp+1Ch] [ebp-E0h]
  int X; // [esp+20h] [ebp-DCh]
  int Y; // [esp+24h] [ebp-D8h]
  __int64 Rect; // [esp+28h] [ebp-D4h] BYREF
  int Rect_8; // [esp+30h] [ebp-CCh]
  int Rect_12; // [esp+34h] [ebp-C8h]
  _DWORD WndClass[10]; // [esp+38h] [ebp-C4h] BYREF
  _DWORD DevMode[39]; // [esp+60h] [ebp-9Ch] BYREF

  v1 = (byte_4DF934 & 0x400) != 0 ? 32 : 16;
  switch ( unk_4DF94C )
  {
    case 0:
      v2 = 320;
      v3 = 240;
      v11 = 320;
      break;
    case 1:
      goto LABEL_7;
    case 2:
      v2 = 800;
      v3 = 600;
      v11 = 800;
      break;
    case 3:
      v2 = 1024;
      v3 = 768;
      v11 = 1024;
      break;
    case 4:
      v2 = 1600;
      v3 = 1200;
      v11 = 1600;
      break;
    default:
      unk_4DF94C = 1;
LABEL_7:
      v2 = 640;
      v3 = 480;
      v11 = 640;
      break;
  }
  v4 = flt_4DFAFC[36320];
  unk_4DFAF4 = 0;
  if ( !LODWORD(flt_4DFAFC[36320]) )
  {
    v4 = COERCE_FLOAT(((int (__stdcall *)(_DWORD))GetModuleHandleA)(0));
    flt_4DFAFC[36320] = v4;
  }
  WndClass[0] = 3;
  WndClass[1] = game_window_proc;
  WndClass[2] = 0;
  WndClass[3] = 0;
  *(float *)&WndClass[4] = v4;
  WndClass[5] = ((int (__stdcall *)(_DWORD, int))LoadIconA)(LODWORD(v4), 103);
  memset(&WndClass[6], 0, 12);
  WndClass[9] = szClass;
  if ( !(unsigned __int16)((int (__stdcall *)(_DWORD *))RegisterClassA)(WndClass) )
    abort_startup_with_3d_error();
  if ( !unk_4DFAF4 )
    goto LABEL_15;
  memset(DevMode, 0, sizeof(DevMode));
  LOWORD(DevMode[9]) = 156;
  DevMode[27] = v2;
  DevMode[28] = v3;
  DevMode[26] = v1;
  DevMode[10] = 1835008;
  if ( ((int (__stdcall *)(_DWORD *, int))ChangeDisplaySettingsA)(DevMode, 4) )
  {
    unk_4DFAF4 = 0;
LABEL_15:
    v5 = 262400;
    v6 = 281673728;
    X = 100;
    Y = 100;
    v2 = 640;
    v3 = 480;
    goto LABEL_16;
  }
  if ( !unk_4DFAF4 )
    goto LABEL_15;
  v5 = 0x40000;
  v6 = 0x80000000;
  ((void (__stdcall *)(_DWORD))ShowCursor)(0);
  X = 0;
  Y = 0;
  v10 = (float)v3;
  v9 = (float)v11;
  update_mouse_authored_scale(v9, v10);
LABEL_16:
  Rect = 0;
  Rect_8 = v2;
  Rect_12 = v3;
  ((void (__stdcall *)(__int64 *, unsigned int, _DWORD, int))AdjustWindowRectEx)(&Rect, v6, 0, v5);
  v7 = ((int (__stdcall *)(int, char *, int, unsigned int, int, int, _DWORD, int, _DWORD, _DWORD, _DWORD, _DWORD))CreateWindowExA)(
         v5,
         szClass,
         lpWindowName,
         v6 | 0x6000000,
         X,
         Y,
         Rect_8 - Rect,
         Rect_12 - HIDWORD(Rect),
         0,
         0,
         LODWORD(flt_4DFAFC[36320]),
         0);
  MEMORY[0x4DFAF0] = v7;
  if ( !v7 )
  {
    unknown_libname_2();
    abort_startup_with_3d_error();
  }
  unk_4DFAEC = ((int (__stdcall *)(int))GetDC)(v7);
  if ( !unk_4DFAEC )
  {
    unknown_libname_2();
    abort_startup_with_3d_error();
  }
  ((void (__stdcall *)(_DWORD, int))ShowWindow)(MEMORY[0x4DFAF0], 5);
  ((void (__stdcall *)(_DWORD))SetForegroundWindow)(MEMORY[0x4DFAF0]);
  ((void (__stdcall *)(_DWORD))SetFocus)(MEMORY[0x4DFAF0]);
  if ( !sub_4129C0() )
  {
    unknown_libname_2();
    abort_startup_with_3d_error();
  }
  if ( (int)initialize_keyboard_input(MEMORY[0x4DFAF0]) < 0 )
    abort_startup_with_3d_error();
  if ( (int)enumerate_input_controllers(MEMORY[0x4DFAF0], &unk_4B776C) < 0 )
    abort_startup_with_3d_error();
  if ( (int)initialize_mouse_input(MEMORY[0x4DFAF0]) < 0 )
    abort_startup_with_3d_error();
  ((void (__stdcall *)(_DWORD))SetFocus)(MEMORY[0x4DFAF0]);
  sub_4129F0(1);
  return 1;
}

