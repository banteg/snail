// IndexBufferFactory::create_index_buffer @ 0x4115d0 (thiscall, ret 0x4)

#include "render_buffer_factories.h"
#include "direct3d_device8_view.h"

extern int report_errorf(char* format, ...); // @ 0x431cc0

ObjectIndexBuffer* IndexBufferFactory::create_index_buffer(int index_count)
{
    int result = g_d3d_device->vtbl->CreateIndexBuffer(
        g_d3d_device,
        index_count * 2,
        0x28,
        0x65,
        1,
        &buffers[count].buffer);

    ++count;
    if (count == 3000)
        report_errorf("Too many Index Buffers, Increase DX_INDEXBUFFER_MAX in GDX.h");
    if (result != 0)
        report_errorf("Vertex Buffer Request fail");
    return &buffers[count - 1];
}
