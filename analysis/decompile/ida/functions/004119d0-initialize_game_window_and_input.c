/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_window_and_input @ 0x4119d0 */
/* selector: initialize_game_window_and_input */

// Registers the SnailMail window class, applies the recovered 4:3 resolution presets, falls back to a 640x480 windowed client, and initializes keyboard, controller, and mouse input.
int __cdecl initialize_game_window_and_input(char *window_name)
{
  unsigned int v1; // esi
  int v2; // ebp
  int v3; // ebx
  int v4; // eax
  int v5; // edi
  unsigned int v6; // esi
  HWND v7; // eax
  float authored_width; // [esp+0h] [ebp-FCh]
  float authored_height; // [esp+4h] [ebp-F8h]
  int v11; // [esp+1Ch] [ebp-E0h]
  int X; // [esp+20h] [ebp-DCh]
  int Y; // [esp+24h] [ebp-D8h]
  struct Rect window_rect; // [esp+28h] [ebp-D4h] BYREF
  struct WndClassA window_class; // [esp+38h] [ebp-C4h] BYREF
  struct DevModeA display_mode; // [esp+60h] [ebp-9Ch] BYREF

  v1 = (g_runtime_config.render_flags & 0x400) != 0 ? 32 : 16;
  switch ( g_runtime_config.display_mode_index )
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
      g_runtime_config.display_mode_index = 1;
LABEL_7:
      v2 = 640;
      v3 = 480;
      v11 = 640;
      break;
  }
  v4 = g_game_window_instance;
  g_fullscreen_active = 0;
  if ( g_game_window_instance == 0 )
  {
    v4 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
    g_game_window_instance = v4;
  }
  window_class.style = 3;
  window_class.wnd_proc = game_window_proc;
  window_class.cls_extra = 0;
  window_class.wnd_extra = 0;
  window_class.instance = v4;
  window_class.icon = ((int (__stdcall *)(int, int))LoadIconA)(v4, 103);
  memset(&window_class.cursor, 0, 12);
  window_class.class_name = (char *)szClass;
  if ( (unsigned __int16)((int (__stdcall *)(struct WndClassA *))RegisterClassA)(&window_class) == 0 )
    abort_startup_with_3d_error();
  if ( g_fullscreen_active == 0 )
    goto LABEL_15;
  memset(&display_mode, 0, sizeof(display_mode));
  display_mode.size = 156;
  display_mode.pels_width = v2;
  display_mode.pels_height = v3;
  display_mode.bits_per_pel = v1;
  display_mode.fields = 1835008;
  if ( ((int (__stdcall *)(struct DevModeA *, int))ChangeDisplaySettingsA)(&display_mode, 4) != 0 )
  {
    g_fullscreen_active = 0;
LABEL_15:
    v5 = 262400;
    v6 = 281673728;
    X = 100;
    Y = 100;
    v2 = 640;
    v3 = 480;
    goto LABEL_16;
  }
  if ( g_fullscreen_active == 0 )
    goto LABEL_15;
  v5 = 0x40000;
  v6 = 0x80000000;
  ShowCursor(false);
  X = 0;
  Y = 0;
  authored_height = (float)v3;
  authored_width = (float)v11;
  update_mouse_authored_scale(authored_width, authored_height);
LABEL_16:
  *(_QWORD *)&window_rect.left = 0;
  window_rect.right = v2;
  window_rect.bottom = v3;
  ((void (__stdcall *)(struct Rect *, unsigned int, _DWORD, int))AdjustWindowRectEx)(&window_rect, v6, 0, v5);
  v7 = ((int (__stdcall *)(int, ObjectFaceQuad *, char *, unsigned int, int, int, int, int, _DWORD, _DWORD, HINSTANCE, _DWORD))CreateWindowExA)(
         v5,
         szClass,
         window_name,
         v6 | 0x6000000,
         X,
         Y,
         window_rect.right - window_rect.left,
         window_rect.bottom - window_rect.top,
         0,
         0,
         g_game_window_instance,
         0);
  g_main_window = v7;
  if ( v7 == 0 )
  {
    release_global_direct3d_renderer_resources();
    abort_startup_with_3d_error();
  }
  g_main_window_dc = GetDC(v7);
  if ( g_main_window_dc == 0 )
  {
    release_global_direct3d_renderer_resources();
    abort_startup_with_3d_error();
  }
  ShowWindow(g_main_window, 5);
  SetForegroundWindow(g_main_window);
  SetFocus(g_main_window);
  if ( initialize_direct3d_renderer() == 0 )
  {
    release_global_direct3d_renderer_resources();
    abort_startup_with_3d_error();
  }
  if ( initialize_keyboard_input(g_main_window) < 0 )
    abort_startup_with_3d_error();
  if ( enumerate_input_controllers(g_main_window, &g_controller_count_view) < 0 )
    abort_startup_with_3d_error();
  if ( initialize_mouse_input(g_main_window) < 0 )
    abort_startup_with_3d_error();
  SetFocus(g_main_window);
  set_cull_mode(1);
  return 1;
}
