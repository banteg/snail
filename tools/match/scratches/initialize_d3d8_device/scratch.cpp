// initialize_d3d8_device @ 0x411730 (thiscall, ret 0x4)

#include "direct3d_renderer.h"
#include "win32_window_state.h"

#include <string.h>

extern Direct3D8* __stdcall Direct3DCreate8(unsigned int sdk_version);
extern int abort_startup_with_3d_error(); // @ 0x4088a0
extern int debug_report_stub(const char* format, ...); // @ 0x449c00
extern Direct3DDevice8* g_d3d_device; // data_502fec

void Direct3DRenderer::initialize_d3d8_device(char use_present_interval_one)
{
    Direct3D8* d3d8 = Direct3DCreate8(0xdc);
    d3d = d3d8;
    if (d3d8 == 0) {
        abort_startup_with_3d_error();
        device_initialized = 0;
    }

    D3DDisplayMode display_mode;
    if (d3d->vtbl->GetAdapterDisplayMode(d3d, 0, &display_mode) < 0) {
        abort_startup_with_3d_error();
        device_initialized = 0;
        return;
    }

    display_format = display_mode.format;
    memset(&present, 0, sizeof(present));
    present.windowed = 1;
    present.swap_effect = 4;
    present.enable_auto_depth_stencil = 1;
    present.auto_depth_stencil_format = depth_stencil_format;
    present.device_window = g_main_window;
    present.back_buffer_width = requested_width;
    present.back_buffer_height = requested_height;
    present.back_buffer_format = display_mode.format;
    present.multisample_type = multisample_type;
    present.fullscreen_refresh_rate_hz = 0;
    if (use_present_interval_one != 0) {
        present.fullscreen_presentation_interval = 1;
    } else {
        present.fullscreen_presentation_interval = 0;
    }

    create_device_flags = 0x40;
    if (d3d->vtbl->CreateDevice(
            d3d, 0, 1, g_main_window, 0x40, &present, &device) < 0) {
        create_device_flags = 0x20;
        if (d3d->vtbl->CreateDevice(
                d3d, 0, 1, g_main_window, 0x20, &present, &device) < 0) {
            abort_startup_with_3d_error();
            device_initialized = 0;
        } else {
            debug_report_stub("Using Software Vertex Processing\n");
        }
    } else {
        debug_report_stub("Using Hardware Vertex Processing\n");
    }

    reset_direct3d_render_state();
    query_direct3d_device_caps();
    device_initialized = 1;
}

void Direct3DRenderer::reset_direct3d_render_state()
{
    device->vtbl->SetRenderState(device, 0x8b, 0x00ffffff);
    device->vtbl->SetRenderState(device, 0x89, 0);
    device->vtbl->SetRenderState(device, 0x16, 1);
    device->vtbl->SetRenderState(device, 7, 1);

    Direct3DDevice8* local_device = device;
    local_device->vtbl->SetRenderState(local_device, 0x10, 1);

    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x0f, 1);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x18, 0);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x19, 5);
}
