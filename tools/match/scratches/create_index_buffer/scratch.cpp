// IndexBufferFactory::create_index_buffer @ 0x4115d0 (thiscall, ret 0x4)

#include "render_buffer_factories.h"
#include "direct3d_device8_view.h"

struct Direct3DIndexFactoryDevice;

struct Direct3DIndexFactoryVtbl {
    char unknown_00[0x60];
    int (__stdcall* CreateIndexBuffer)(
        Direct3DIndexFactoryDevice* self,
        unsigned int length,
        unsigned int usage,
        unsigned int format,
        unsigned int pool,
        ObjectIndexBufferResource** out_buffer);
};

struct Direct3DIndexFactoryDevice {
    Direct3DIndexFactoryVtbl* vtbl;
};

extern int report_errorf(char* format, ...); // @ 0x431cc0

ObjectIndexBuffer* IndexBufferFactory::create_index_buffer(int index_count)
{
    Direct3DIndexFactoryDevice* factory =
        (Direct3DIndexFactoryDevice*)g_d3d_device;
    int result = factory->vtbl->CreateIndexBuffer(
        factory,
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
