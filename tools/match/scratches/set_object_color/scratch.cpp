// set_object_color @ 0x4141d0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

struct ObjectVertexBufferVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectVertexBuffer* self, int offset, int size,
        ObjectRenderVertex** vertices, int flags);
    int (__stdcall* Unlock)(ObjectVertexBuffer* self);
};

struct ObjectColorRenderView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    char unknown_14[0xc0 - 0x14];
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
};

extern int g_object_grouped_vertex_cursor; // data_5031bc

ColorBGRA8* set_object_color(ObjectColorRenderView* object, Color4f color)
{
    ColorBGRA8 out;
    ObjectRenderVertex* vertices;

    out.noop_this_constructor();
    ColorBGRA8* result = out.pack_color_rgba_u8(&color);

    if ((object->flags & 0x80000) != 0) {
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18,
            &vertices, 0);

        int i = 0;
        if (object->grouped_vertex_count > 0) {
            do {
                vertices[i].diffuse = *(unsigned int*)&out;
                ++i;
            } while (i < object->grouped_vertex_count);
        }

        return (ColorBGRA8*)object->render_buffers->vertex_buffer->vtbl->Unlock(
            object->render_buffers->vertex_buffer);
    }

    return result;
}
