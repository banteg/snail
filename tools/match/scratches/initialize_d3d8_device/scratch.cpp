// initialize_d3d8_device @ 0x411730 (thiscall, ret 0x4)

#include <string.h>

typedef unsigned int UINT;
typedef int HRESULT;
typedef int HWND;

struct D3DDisplayMode {
    UINT width;
    UINT height;
    UINT refresh_rate;
    UINT format;
};

struct D3DPresentParameters {
    UINT back_buffer_width;
    UINT back_buffer_height;
    UINT back_buffer_format;
    UINT back_buffer_count;
    UINT multisample_type;
    UINT swap_effect;
    HWND device_window;
    int windowed;
    int enable_auto_depth_stencil;
    UINT auto_depth_stencil_format;
    UINT flags;
    UINT fullscreen_refresh_rate_hz;
    UINT fullscreen_presentation_interval;
};

typedef char D3DPresentParameters_must_be_0x34[
    (sizeof(D3DPresentParameters) == 0x34) ? 1 : -1];

struct Direct3D8;
struct Direct3DDevice8;

struct Direct3DDevice8Vtbl {
    char unknown_000[0xc8];
    HRESULT (__stdcall* SetRenderState)(
        Direct3DDevice8* self, UINT state, UINT value);
};

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

struct Direct3D8Vtbl {
    char unknown_00[0x20];
    HRESULT (__stdcall* GetAdapterDisplayMode)(
        Direct3D8* self, UINT adapter, D3DDisplayMode* mode);
    char unknown_24[0x3c - 0x24];
    HRESULT (__stdcall* CreateDevice)(
        Direct3D8* self,
        UINT adapter,
        UINT device_type,
        HWND focus_window,
        UINT behavior_flags,
        D3DPresentParameters* parameters,
        Direct3DDevice8** out_device);
};

struct Direct3D8 {
    Direct3D8Vtbl* vtbl;
};

class Direct3DRenderer {
public:
    int initialize_d3d8_device(char use_present_interval_one);
    void reset_direct3d_render_state(); // @ 0x4118b0
    int query_direct3d_device_caps();   // @ 0x414600

    char unknown_0000[0xbb8c];
    unsigned char device_initialized; // +0xbb8c
    char unknown_bb8d[0xbb90 - 0xbb8d];
    Direct3D8* d3d;                 // +0xbb90
    Direct3DDevice8* device;        // +0xbb94
    D3DPresentParameters present;   // +0xbb98
    char unknown_bbcc[0xbca0 - 0xbbcc];
    UINT display_format;            // +0xbca0
    UINT requested_width;           // +0xbca4
    UINT requested_height;          // +0xbca8
    UINT create_device_flags;       // +0xbcac
    char unknown_bcb0[0xbcb8 - 0xbcb0];
    UINT depth_stencil_format;      // +0xbcb8
    UINT multisample_type;          // +0xbcbc
};

extern Direct3D8* __stdcall Direct3DCreate8(UINT sdk_version);
extern int abort_startup_with_3d_error(); // @ 0x4088a0
extern int debug_report_stub(const char* format, ...); // @ 0x449c00
extern int g_main_window; // data_4dfaf0
extern Direct3DDevice8* g_d3d_device; // data_502fec

int Direct3DRenderer::initialize_d3d8_device(char use_present_interval_one)
{
    Direct3D8* d3d8 = Direct3DCreate8(0xdc);
    d3d = d3d8;
    if (d3d8 == 0) {
        abort_startup_with_3d_error();
        device_initialized = 0;
    }

    D3DDisplayMode display_mode;
    if (d3d->vtbl->GetAdapterDisplayMode(d3d, 0, &display_mode) < 0) {
        int result = abort_startup_with_3d_error();
        device_initialized = 0;
        return result;
    }

    display_format = display_mode.format;
    memset(&present, 0, sizeof(present));
    present.windowed = 1;
    present.swap_effect = 4;
    present.enable_auto_depth_stencil = 1;
    present.auto_depth_stencil_format = depth_stencil_format;
    present.back_buffer_format = display_mode.format;
    present.device_window = g_main_window;
    present.back_buffer_width = requested_width;
    present.multisample_type = multisample_type;
    present.back_buffer_height = requested_height;
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
    int result = query_direct3d_device_caps();
    device_initialized = 1;
    return result;
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
