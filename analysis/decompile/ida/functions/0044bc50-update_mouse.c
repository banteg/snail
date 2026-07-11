/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_mouse @ 0x44bc50 */
/* selector: update_mouse */

int __cdecl update_mouse(int window_handle)
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
  char left_mouse_button_state; // [esp-Ch] [ebp-64h]
  char v13; // [esp-8h] [ebp-60h]
  char right_mouse_button_state; // [esp-8h] [ebp-60h]
  uint8_t v15; // [esp+0h] [ebp-58h]
  uint8_t v16; // [esp+0h] [ebp-58h]
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

  if ( g_mouse_device )
  {
    v29 = 0;
    v30 = 0;
    v31 = 0;
    v32 = 0;
    v33 = 0;
    if ( (*(int (__stdcall **)(void *, int, int *))(*(_DWORD *)g_mouse_device + 36))(g_mouse_device, 20, &v29) < 0 )
    {
      while ( (*(int (__stdcall **)(void *))(*(_DWORD *)g_mouse_device + 28))(g_mouse_device) == -2147024866 )
        ;
    }
  }
  if ( !((int (__stdcall *)(int, __int64 *))GetWindowRect)(window_handle, &Rect)
    || !((int (__stdcall *)(int, int *))GetClientRect)(window_handle, &v21) )
  {
    Rect = 0;
    Rect_8 = 0;
  }
  if ( g_fullscreen_active || !is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
  {
    g_mouse_live_x[0] = (double)v29 + g_mouse_live_x[0];
    g_mouse_live_y[0] = (double)v30 + g_mouse_live_y[0];
    if ( g_mouse_live_x[0] >= 0.0 )
    {
      if ( g_mouse_live_x[0] > 639.0 )
        g_mouse_live_x[0] = 639.0;
    }
    else
    {
      g_mouse_live_x[0] = 0.0;
    }
    if ( g_mouse_live_y[0] >= 0.0 )
    {
      if ( g_mouse_live_y[0] > 479.0 )
        g_mouse_live_y[0] = 479.0;
    }
    else
    {
      g_mouse_live_y[0] = 0.0;
    }
  }
  else
  {
    convert_mouse_screen_xy(0, g_mouse_live_x, g_mouse_live_y);
  }
  if ( g_fullscreen_active || !is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
  {
    ClipCursor(nullptr);
    if ( !is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
    {
      v25 = Rect + v21 - g_mouse_uncaptured_clip_left;
      v27 = Rect_8 + v23 - g_mouse_uncaptured_clip_right;
      v26 = HIDWORD(Rect) + v22 - g_mouse_uncaptured_clip_top;
      v28 = HIDWORD(Rect_8) + v24 - g_mouse_uncaptured_clip_bottom;
      ClipCursor((const RECT *)&v25);
      v18 = g_fullscreen_active;
      v16 = is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656));
      right_mouse_button_state = read_right_mouse_button_state(0);
      left_mouse_button_state = read_left_mouse_button_state(0);
      v10 = consume_mouse_wheel_delta(0);
      update_input_controller_pointer_region(
        0,
        0,
        0,
        640,
        480,
        (__int64)g_mouse_live_x[0],
        (__int64)g_mouse_live_y[0],
        v10,
        left_mouse_button_state,
        right_mouse_button_state,
        0,
        v16,
        v18);
      goto LABEL_29;
    }
    v17 = g_fullscreen_active;
    v15 = is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656));
    v13 = read_right_mouse_button_state(0);
    v11 = read_left_mouse_button_state(0);
    v9 = consume_mouse_wheel_delta(0);
    v8 = (__int64)g_mouse_live_y[0];
    v1 = HIDWORD(Rect);
    v7 = (__int64)g_mouse_live_x[0];
    v2 = g_mouse_captured_client_top;
    v3 = v23;
    v6 = HIDWORD(Rect) + v24 - g_mouse_captured_client_top;
    v4 = g_mouse_captured_client_left;
  }
  else
  {
    if ( is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656)) )
    {
      ClipCursor(nullptr);
    }
    else
    {
      v25 = Rect + v21 - g_mouse_uncaptured_clip_left;
      v27 = Rect_8 + v23 - g_mouse_uncaptured_clip_right;
      v26 = HIDWORD(Rect) + v22 - g_mouse_uncaptured_clip_top;
      v28 = HIDWORD(Rect_8) + v24 - g_mouse_uncaptured_clip_bottom;
      ClipCursor((const RECT *)&v25);
    }
    v17 = g_fullscreen_active;
    v15 = is_mouse_captured((MouseCursorState *)((char *)g_game_base + 656));
    v13 = read_right_mouse_button_state(0);
    v11 = read_left_mouse_button_state(0);
    v9 = consume_mouse_wheel_delta(0);
    v8 = (__int64)g_mouse_live_y[0];
    v1 = HIDWORD(Rect);
    v7 = (__int64)g_mouse_live_x[0];
    v2 = g_mouse_uncaptured_clip_top;
    v3 = v23;
    v6 = HIDWORD(Rect) + v24 - g_mouse_uncaptured_clip_top;
    v4 = g_mouse_uncaptured_clip_left;
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
  if ( g_hide_system_cursor_flag )
    ((void (__stdcall *)(_DWORD))SetCursor)(0);
  return 0;
}

