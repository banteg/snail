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

class Direct3DRenderer {
public:
    ObjectRenderBuffers* create_vertex_buffer(
        int vertex_count, int fvf); // @ 0x4114b0
    void release_direct3d_renderer_resources(); // @ 0x4116f0
    void release_direct3d_device_interfaces(); // @ 0x411960
    int direct3d_renderer_set_cull_mode(char cull_front); // @ 0x411700
    int initialize_d3d8_device(char use_present_interval_one); // @ 0x411730
    void reset_direct3d_render_state(); // @ 0x4118b0
    int direct3d_renderer_set_fullscreen_mode(int enabled);
    int query_direct3d_device_caps(); // @ 0x414600

    int vertex_buffer_count; // +0x0000
    ObjectRenderBuffers vertex_buffers[0xbb8]; // +0x0004, 3000 entries
    IndexBufferFactory index_buffer_factory; // +0x8ca4, 3000 entries
    RendererState* renderer_state; // +0xbb88
    unsigned char device_initialized; // +0xbb8c
    char unknown_bb8d[0xbb90 - 0xbb8d];
    Direct3D8* d3d;                  // +0xbb90
    Direct3DDevice8* device;         // +0xbb94
    D3DPresentParameters present;    // +0xbb98
    char unknown_bbcc[0xbca0 - 0xbbcc];
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
typedef char Direct3DRenderer_must_be_0xbcc0[
    (sizeof(Direct3DRenderer) == 0xbcc0) ? 1 : -1];

extern Direct3DRenderer g_direct3d_renderer; // data_4f7458

#endif
