// Direct3DRenderer::direct3d_renderer_set_fullscreen_mode @ 0x414270

#include "authored_view_state.h"
#include "direct3d_renderer.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall GetWindowRect(HWND window, Rect* rect);
extern "C" __declspec(dllimport) BOOL __stdcall SetWindowPos(HWND window,
    HWND insert_after, int x, int y, int width, int height, UINT flags);
extern "C" __declspec(dllimport) int __stdcall ShowCursor(BOOL show);
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND window, int command);
extern "C" __declspec(dllimport) BOOL __stdcall SetForegroundWindow(HWND window);
extern "C" __declspec(dllimport) HWND __stdcall SetFocus(HWND window);
extern "C" __declspec(dllimport) BOOL __stdcall SetCursorPos(int x, int y);

extern int debug_report_stub(char* message); // @ 0x449c00

void Direct3DRenderer::direct3d_renderer_set_fullscreen_mode(int enabled)
{
    if (device_initialized == 0) {
        return;
    }

    char fullscreen = (char)enabled;
    present.windowed = fullscreen == 0;
    if (fullscreen != 0) {
        GetWindowRect(g_main_window, &g_saved_window_rect);
        g_saved_window_rect_valid = 1;
        present.fullscreen_refresh_rate_hz = 0;
        present.fullscreen_presentation_interval = 1;
        present.back_buffer_format = 0x16;
    } else {
        present.fullscreen_refresh_rate_hz = 0;
        present.fullscreen_presentation_interval = 0;
        present.back_buffer_format = display_format;
    }

    debug_report_stub("Full Screen Reset\n");
    device->vtbl->Reset(device, &present);
    restore_texture_ref_stage_states();
    reset_direct3d_render_state();

    if (fullscreen == 0 && g_saved_window_rect_valid == 1) {
        SetWindowPos(g_main_window, 0,
            g_saved_window_rect.left,
            g_saved_window_rect.top,
            g_saved_window_rect.right - g_saved_window_rect.left,
            g_saved_window_rect.bottom - g_saved_window_rect.top,
            0x40);
    } else {
        ShowCursor(0);
    }

    ShowWindow(g_main_window, 5);
    SetForegroundWindow(g_main_window);
    SetFocus(g_main_window);
    SetCursorPos(
        (int)(g_authored_view_width * 0.5f),
        (int)(g_authored_view_height * 0.5f));
}
