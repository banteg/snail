// Shared Direct3DRenderer ABI view.
#ifndef DIRECT3D_RENDERER_H
#define DIRECT3D_RENDERER_H

#include "direct3d_device8_view.h"
#include "render_buffer_factories.h"

struct Direct3D8;

struct D3DPresentParameters {
    unsigned int back_buffer_width;
    unsigned int back_buffer_height;
    unsigned int back_buffer_format;
    unsigned int back_buffer_count;
    unsigned int multisample_type;
    unsigned int swap_effect;
    int device_window;
    int windowed;
    int enable_auto_depth_stencil;
    unsigned int auto_depth_stencil_format;
    unsigned int flags;
    unsigned int fullscreen_refresh_rate_hz;
    unsigned int fullscreen_presentation_interval;
};

struct D3DDeviceCaps8 {
    char unknown_00[0x58];
    unsigned int max_texture_width;  // +0x58
    unsigned int max_texture_height; // +0x5c
    char unknown_60[0xd4 - 0x60];
};

struct D3DDisplayMode {
    unsigned int width;
    unsigned int height;
    unsigned int refresh_rate;
    unsigned int format;
};

struct Direct3D8Vtbl {
    char unknown_00[0x08];
    int (__stdcall* Release)(Direct3D8* self);
    char unknown_0c[0x20 - 0x0c];
    int (__stdcall* GetAdapterDisplayMode)(
        Direct3D8* self, unsigned int adapter, D3DDisplayMode* mode);
    char unknown_24[0x34 - 0x24];
    int (__stdcall* GetDeviceCaps)(Direct3D8* self, unsigned int adapter,
        unsigned int device_type, D3DDeviceCaps8* caps);
    char unknown_38[0x3c - 0x38];
    int (__stdcall* CreateDevice)(Direct3D8* self, unsigned int adapter,
        unsigned int device_type, int focus_window, unsigned int behavior_flags,
        D3DPresentParameters* parameters, Direct3DDevice8** out_device);
};

struct Direct3D8 {
    Direct3D8Vtbl* vtbl;
};

class Direct3DRenderer {
public:
    void initialize_direct3d_renderer_defaults(); // @ 0x411630
    void release_direct3d_renderer_resources(); // @ 0x4116f0
    void release_direct3d_device_interfaces(); // @ 0x411960
    int direct3d_renderer_set_cull_mode(char cull_front); // @ 0x411700
    void initialize_d3d8_device(char use_present_interval_one); // @ 0x411730
    void reset_direct3d_render_state(); // @ 0x4118b0
    void direct3d_renderer_set_fullscreen_mode(int enabled); // @ 0x414270
    void restore_texture_ref_stage_states(); // @ 0x4143c0
    void query_direct3d_device_caps(); // @ 0x414600

    VertexBufferFactory vertex_buffer_factory; // +0x0000, 3000 entries
    IndexBufferFactory index_buffer_factory; // +0x8ca4, 3000 entries
    ObjectRenderBuffers* renderer_state; // +0xbb88, borrowed factory slot
    unsigned char device_initialized; // +0xbb8c
    char unknown_bb8d[0xbb90 - 0xbb8d];
    Direct3D8* d3d;                  // +0xbb90
    Direct3DDevice8* device;         // +0xbb94
    D3DPresentParameters present;    // +0xbb98
    D3DDeviceCaps8 device_caps;       // +0xbbcc
    unsigned int display_format;     // +0xbca0
    unsigned int requested_width;    // +0xbca4
    unsigned int requested_height;   // +0xbca8
    unsigned int create_device_flags; // +0xbcac
    char unknown_bcb0[0xbcb8 - 0xbcb0];
    unsigned int depth_stencil_format; // +0xbcb8
    unsigned int multisample_type;   // +0xbcbc
};

typedef char D3DPresentParameters_must_be_0x34[
    (sizeof(D3DPresentParameters) == 0x34) ? 1 : -1];
typedef char D3DDeviceCaps8_must_be_0xd4[
    (sizeof(D3DDeviceCaps8) == 0xd4) ? 1 : -1];
typedef char D3DDisplayMode_must_be_0x10[
    (sizeof(D3DDisplayMode) == 0x10) ? 1 : -1];
typedef char Direct3D8Vtbl_must_cover_0x40[
    (sizeof(Direct3D8Vtbl) == 0x40) ? 1 : -1];
typedef char Direct3D8_must_be_0x04[
    (sizeof(Direct3D8) == 0x04) ? 1 : -1];
typedef char Direct3DRenderer_must_be_0xbcc0[
    (sizeof(Direct3DRenderer) == 0xbcc0) ? 1 : -1];

extern Direct3DRenderer g_direct3d_renderer; // data_4f7458

#endif
