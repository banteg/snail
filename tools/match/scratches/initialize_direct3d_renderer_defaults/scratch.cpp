// Direct3DRenderer::initialize_direct3d_renderer_defaults @ 0x411630

#include "direct3d_renderer.h"
#include "mouse_window_state.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) BOOL __stdcall AdjustWindowRectEx(
    Rect* rect, UINT style, BOOL menu, UINT ex_style);

extern float g_authored_view_width; // data_4df85c
extern float g_authored_view_height; // data_4b7760
extern UINT g_windowed_adjust_style; // data_4a16d8

void Direct3DRenderer::initialize_direct3d_renderer_defaults()
{
    int authored_height = (int)g_authored_view_height;
    g_mouse_uncaptured_clip_rect.bottom = authored_height;
    g_mouse_uncaptured_clip_rect.top = 0;
    g_mouse_uncaptured_clip_rect.left = 0;

    int authored_width = (int)g_authored_view_width;
    g_mouse_uncaptured_clip_rect.right = authored_width;
    g_mouse_captured_client_rect.right = authored_width;
    g_mouse_captured_client_rect.bottom = authored_height;
    g_mouse_captured_client_rect.top = 0;
    g_mouse_captured_client_rect.left = 0;

    AdjustWindowRectEx(
        &g_mouse_uncaptured_clip_rect, g_windowed_adjust_style, 0, 0);

    d3d = 0;
    device = 0;
    requested_width = 640;
    requested_height = 480;
    *(unsigned int*)((char*)this + 0xbcb4) = 0x17;
    depth_stencil_format = 0x50;
    create_device_flags = 0x20;
    multisample_type = 0;
    *(unsigned int*)((char*)this + 0xbcb0) = 0;
    device_initialized = 0;
}
