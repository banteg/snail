// initialize_game_window_and_input @ 0x4119d0 (cdecl)

#include "rect.h"
#include "runtime_config.h"
#include "win32_window_state.h"

#include <string.h>

extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(char* module_name);
extern "C" __declspec(dllimport) HICON __stdcall LoadIconA(HINSTANCE instance, int icon_name);
extern "C" __declspec(dllimport) ATOM __stdcall RegisterClassA(WndClassA* wnd_class);
extern "C" __declspec(dllimport) int __stdcall ChangeDisplaySettingsA(DevModeA* dev_mode, int flags);
extern "C" __declspec(dllimport) int __stdcall ShowCursor(BOOL show);
extern "C" __declspec(dllimport) BOOL __stdcall AdjustWindowRectEx(
    Rect* rect, UINT style, BOOL menu, UINT ex_style);
extern "C" __declspec(dllimport) HWND __stdcall CreateWindowExA(
    UINT ex_style,
    char* class_name,
    char* window_name,
    UINT style,
    int x,
    int y,
    int width,
    int height,
    HWND parent,
    HMENU menu,
    HINSTANCE instance,
    void* param);
extern "C" __declspec(dllimport) HDC __stdcall GetDC(HWND hwnd);
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND hwnd, int command);
extern "C" __declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND hwnd);
extern "C" __declspec(dllimport) HWND __stdcall SetFocus(HWND hwnd);
extern "C" __declspec(dllimport) BOOL __stdcall EndDialog(HWND dialog, int result);

extern int g_config_display_mode_index;
extern int g_controller_count_view; // data_4b776c

int __stdcall game_window_proc(HWND hwnd, UINT message, UINT wparam, int lparam);
int abort_startup_with_3d_error(); // @ 0x4088a0
int release_global_direct3d_renderer_resources(); // @ 0x411d70
void update_mouse_authored_scale(float width, float height); // @ 0x44bbd0
char initialize_direct3d_renderer(); // @ 0x4129c0
int initialize_keyboard_input(HWND hwnd); // @ 0x44b7d0
void release_keyboard_input(); // @ 0x44b670
int enumerate_input_controllers(HWND hwnd, int* out_count); // @ 0x44b3c0
int initialize_mouse_input(HWND hwnd, unsigned char fullscreen_active); // @ 0x44c310 caller shape
int set_cull_mode(int cull_front); // @ 0x4129f0

int initialize_game_window_and_input(char* window_name)
{
    int bits_per_pixel = ((g_runtime_config.render_flags & 0x400) != 0) ? 32 : 16;

    int width;
    int height;
    int authored_width;

    switch (g_config_display_mode_index) {
    case 0:
        authored_width = 320;
        width = 320;
        height = 240;
        break;
    case 1:
        goto use_640x480;
    case 2:
        authored_width = 800;
        width = 800;
        height = 600;
        break;
    case 3:
        authored_width = 1024;
        width = 1024;
        height = 768;
        break;
    case 4:
        authored_width = 1600;
        width = 1600;
        height = 1200;
        break;
    default:
        g_config_display_mode_index = 1;
use_640x480:
        authored_width = 640;
        width = 640;
        height = 480;
        break;
    }

    HINSTANCE instance = g_game_window_instance;
    g_fullscreen_active = 0;
    if (instance == 0) {
        instance = GetModuleHandleA(0);
        g_game_window_instance = instance;
    }

    WndClassA wnd_class;
    wnd_class.style = 3;
    wnd_class.wnd_proc = game_window_proc;
    wnd_class.cls_extra = 0;
    wnd_class.wnd_extra = 0;
    wnd_class.instance = instance;
    wnd_class.icon = LoadIconA(instance, 103);
    wnd_class.cursor = 0;
    wnd_class.background = 0;
    wnd_class.menu_name = 0;
    wnd_class.class_name = "SnailMailWindowClass";

    if (RegisterClassA(&wnd_class) == 0) {
        abort_startup_with_3d_error();
        return 0;
    }

    UINT ex_style;
    UINT style;
    int x;
    int y;

    if (g_fullscreen_active != 0) {
        DevModeA dev_mode;
        memset(&dev_mode, 0, sizeof(dev_mode));
        dev_mode.size = sizeof(dev_mode);
        dev_mode.pels_width = width;
        dev_mode.pels_height = height;
        dev_mode.bits_per_pel = bits_per_pixel;
        dev_mode.fields = 0x1c0000;

        if (ChangeDisplaySettingsA(&dev_mode, 4) != 0)
            g_fullscreen_active = 0;
    }

    if (g_fullscreen_active != 0) {
        ex_style = 0x40000;
        style = 0x80000000;
        ShowCursor(0);
        x = 0;
        y = 0;
        update_mouse_authored_scale((float)authored_width, (float)height);
    } else {
        ex_style = 0x40100;
        style = 0x10ca0000;
        x = 100;
        y = 100;
        width = 640;
        height = 480;
    }

    Rect rect;
    rect.left = 0;
    rect.right = width;
    rect.top = 0;
    rect.bottom = height;
    AdjustWindowRectEx(&rect, style, 0, ex_style);

    g_main_window = CreateWindowExA(
        ex_style,
        "SnailMailWindowClass",
        window_name,
        style | 0x06000000,
        x,
        y,
        rect.right - rect.left,
        rect.bottom - rect.top,
        0,
        0,
        g_game_window_instance,
        0);

    if (g_main_window == 0) {
        release_global_direct3d_renderer_resources();
        abort_startup_with_3d_error();
        return 0;
    }

    g_main_window_dc = GetDC(g_main_window);
    if (g_main_window_dc == 0) {
        release_global_direct3d_renderer_resources();
        abort_startup_with_3d_error();
        return 0;
    }

    ShowWindow(g_main_window, 5);
    SetForegroundWindow(g_main_window);
    SetFocus(g_main_window);

    if (initialize_direct3d_renderer() == 0) {
        release_global_direct3d_renderer_resources();
        abort_startup_with_3d_error();
        return 0;
    }

    if (initialize_keyboard_input(g_main_window) < 0) {
        abort_startup_with_3d_error();
        release_keyboard_input();
        return 0;
    }

    if (enumerate_input_controllers(g_main_window, &g_controller_count_view) < 0) {
        abort_startup_with_3d_error();
        EndDialog(g_main_window, 0);
        return 0;
    }

    if (initialize_mouse_input(g_main_window, g_fullscreen_active) < 0) {
        abort_startup_with_3d_error();
        EndDialog(g_main_window, 0);
        return 0;
    }

    SetFocus(g_main_window);
    set_cull_mode(1);
    return 1;
}
