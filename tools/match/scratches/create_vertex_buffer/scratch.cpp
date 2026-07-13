// Direct3DRenderer::create_vertex_buffer @ 0x4114b0 (thiscall, ret 0x8)

#include "direct3d_renderer.h"

extern int report_errorf(char* format, ...); // @ 0x431cc0
extern int debug_report_stub(char* format, ...); // @ 0x449c00

ObjectRenderBuffers* Direct3DRenderer::create_vertex_buffer(
    int vertex_count, int fvf)
{
    vertex_buffers[vertex_buffer_count].fvf = fvf;

    int result;
    switch (fvf) {
    case 0x142:
        result = g_d3d_device->vtbl->CreateVertexBuffer(g_d3d_device,
            vertex_count * 24, 8, 0x142, 1,
            &vertex_buffers[vertex_buffer_count].vertex_buffer);
        goto created;
    case 0x102:
        result = g_d3d_device->vtbl->CreateVertexBuffer(g_d3d_device,
            vertex_count * 20, 8, 0x102, 1,
            &vertex_buffers[vertex_buffer_count].vertex_buffer);
        goto created;
    case 2:
        result = g_d3d_device->vtbl->CreateVertexBuffer(g_d3d_device,
            vertex_count * 12, 8, 2, 1,
            &vertex_buffers[vertex_buffer_count].vertex_buffer);
        goto created;
    default:
        result = vertex_count;
        break;
    }

created:
    if (result != 0) {
        report_errorf("Vertex Buffer Request fail");
        if (result == (int)0x8876017c) {
            debug_report_stub("\tOut of video memory\n");
        } else if (result == (int)0x8007000e) {
            debug_report_stub("\tOut of memory\n");
        } else if (result == (int)0x8876086c) {
            debug_report_stub("\tInvalid call\n");
        }
    }

    ++vertex_buffer_count;
    if (vertex_buffer_count == 3000) {
        report_errorf("DX_VERTEXBUFFER_MAX Overflow");
        for (;;) {
        }
    }
    return &vertex_buffers[vertex_buffer_count - 1];
}
